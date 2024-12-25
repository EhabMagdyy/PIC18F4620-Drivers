/* 
 * File:   hal_usart.c
 * Author: Ehab
 *
 * Created on 30 ?????, 2023, 07:13 ?
 */

#include "hal_usart.h"

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TxInterruptHandler)(void) = NULL;
void EUSART_TX_ISR(void);
#endif
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RxInterruptHandler)(void) = NULL;
static void (*EUSART_FramingErrorHandler)(void) = NULL;
static void (*EUSART_OverrunErrorHandler)(void) = NULL;
void EUSART_RX_ISR(void);
#endif

static inline Std_ReturnType EUSART_Baud_Rate_Calculation(const usart_t* usart);
static inline Std_ReturnType EUSART_ASYNC_TX_Intialize(const usart_t* usart);
static inline Std_ReturnType EUSART_ASYNC_RX_Intialize(const usart_t* usart);

Std_ReturnType EUSART_ASYNC_Intialize(const usart_t* usart)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != usart)
    {
        ret = E_OK;
        /* Disable EUSART */
        RCSTAbits.SPEN = EUSART_MODULE_DISABLE;
        /* Configure EUSART bits as input */
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        /* Configure baud rate, speed, mood and size of SPBRG */
        EUSART_Baud_Rate_Calculation(usart);
        /* Configure TX */
        if(EUSART_ASYNCHRONOUS_TX_ENABLE == usart->tx_config.tx_enable){
            ret = EUSART_ASYNC_TX_Intialize(usart);
        }
        else{/* Nothing */}
        /* Configure RX */
        if(EUSART_ASYNCHRONOUS_RX_ENABLE == usart->rx_config.rx_enable){
            ret = EUSART_ASYNC_RX_Intialize(usart);
        }
        else{/* Nothing */}
        /* Enable EUSART */
        RCSTAbits.SPEN = EUSART_MODULE_ENABLE;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_DeIntialize(const usart_t* usart)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != usart)
    {
        ret = E_OK;
        
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_ReceiveByteBlocking(uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != data)
    {
        ret = E_OK;
        /* wait until the data  */
        while(!PIR1bits.RCIF);
        *data = RCREG;
    }
    return ret;
}

Std_ReturnType EUSART_ASYNC_ReceiveByteNonBlocking(uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    /* Return the data if the received */
    if(INTERRUPT_OCCURED == PIR1bits.RCIF){
        ret = E_OK;
        *data = RCREG;
    }
    
    return ret;
}

Std_ReturnType EUSART_ASYNC_Rx_Restart()
{
    Std_ReturnType ret = E_OK;
    /* Restart Rx when overrun error ocurred */
    RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_DISABLE;
    RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
    
    return ret;
}

Std_ReturnType EUSART_ASYNC_SendByteBlocking(uint8 data)
{
    Std_ReturnType ret = E_OK;
    
    while(!TXSTAbits.TRMT);
    TXREG = data;
    
    #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_ENABLE();
    #endif

    return ret;
}

Std_ReturnType EUSART_ASYNC_SendStringBlocking(uint8 *str, uint8 length){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != str){
        ret = E_OK;
        for(uint8 index = 0 ; index < length ; index++){
            ret = EUSART_ASYNC_SendByteBlocking(str[index]);
        }
    }
    
    return ret;
}

Std_ReturnType EUSART_ASYNC_SendByteNonBlocking(uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(EUSART_TX_SHIFT_REGISTER_EMPTY == TXSTAbits.TRMT){
        TXREG = data;
    }
    
    #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    EUSART_TX_INTERRUPT_ENABLE();
    #endif

    return ret;
}

Std_ReturnType EUSART_ASYNC_SendStringNonBlocking(uint8 *str, uint8 length){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != str){
        ret = E_OK;
        for(uint8 index = 0 ; index < length ; index++){
            ret = EUSART_ASYNC_SendByteNonBlocking(str[index]);
        }
    }
    
    return ret;
}

static inline Std_ReturnType EUSART_Baud_Rate_Calculation(const usart_t* usart)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != usart)
    {
        ret = E_OK;
        uint16 baud_rate = 0;
    
        switch(usart->baudrate_config)
        {
            case BAUDRATE_ASYN_8BIT_lOW_SPEED:
                BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                baud_rate = round(((_XTAL_FREQ / (float)usart->baudrate) / 64) - 1);
                break;
            case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
                BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                baud_rate = round(((_XTAL_FREQ / (float)usart->baudrate) / 16) - 1);
                break;
            case BAUDRATE_ASYN_16BIT_lOW_SPEED:
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                baud_rate = round(((_XTAL_FREQ / (float)usart->baudrate) / 16) - 1);
                break;
            case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                baud_rate = round(((_XTAL_FREQ / (float)usart->baudrate) / 4) - 1);
                break;
            case BAUDRATE_SYN_8BIT:
                BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                baud_rate = round(((_XTAL_FREQ / (float)usart->baudrate) / 4) - 1);
                break;
            case BAUDRATE_SYN_16BIT:
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                baud_rate = round(((_XTAL_FREQ / (float)usart->baudrate) / 4) - 1);
                break;
            default : ret = E_NOT_OK; 
        }
        SPBRG = (uint8)baud_rate;
        SPBRGH = (uint8)(baud_rate >> 8);
    }
    
    return ret;
}

static inline Std_ReturnType EUSART_ASYNC_TX_Intialize(const usart_t* usart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != usart)
    {
        ret = E_OK;
        /* Interrupt Configuration */
        #if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        EUSART_TxInterruptHandler = usart->EUSART_TxDefaultInterruptHandler;
        EUSART_TX_INTERRUPT_ENABLE();
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PEIORITY_LEVELS_ENABLe();
        if(INTERRUPT_LOW_PRIORITY == usart->tx_config.tx_priority){
            EUSART_TX_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowPriority_Enable();
        }
        else if(INTERRUPT_HIGH_PRIORITY == usart->tx_config.tx_priority){
            EUSART_TX_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighPriority_Enable();
        }
        else{ret = E_NOT_OK;}
        #else
        INTERRUPT_PEIORITY_LEVELS_DISABLE();
        INTERRUPT_GlobalInterrupt_Enable();
        INTERRUPT_PeripheraInterrupt_Enable();
        #endif
        #endif
        /* parity bit config */
        TXSTAbits.TX9 = usart->tx_config.tx_8bit_9bit;
        /* Enable Transmission */
        TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
    }
    return ret;
}

static inline Std_ReturnType EUSART_ASYNC_RX_Intialize(const usart_t* usart){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != usart)
    {
        ret = E_OK;
        /* Interrupt Configuration */
        #if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        EUSART_RxInterruptHandler = usart->EUSART_RxDefaultInterruptHandler;
        EUSART_FramingErrorHandler = usart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = usart->EUSART_OverrunErrorHandler;
        EUSART_RX_INTERRUPT_ENABLE();
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PEIORITY_LEVELS_ENABLe();
        if(INTERRUPT_LOW_PRIORITY == usart->rx_config.rx_priority){
            EUSART_RX_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowPriority_Enable();
        }
        else if(INTERRUPT_HIGH_PRIORITY == usart->rx_config.rx_priority){
            EUSART_RX_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighPriority_Enable();
        }
        else{ret = E_NOT_OK;}
        #else
        INTERRUPT_PEIORITY_LEVELS_DISABLE();
        INTERRUPT_GlobalInterrupt_Enable();
        INTERRUPT_PeripheraInterrupt_Enable();
        #endif
        #endif
        /* parity bit config */
        RCSTAbits.RX9 = usart->rx_config.rx_8bit_9bit;
        /* Enable Transmission */
        RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
    }
    return ret;
}

#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void EUSART_TX_ISR(void)
{
    EUSART_TX_INTERRUPT_DISABLE();
    
    if(EUSART_TxInterruptHandler){
        EUSART_TxInterruptHandler();
    }
}
#endif
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void EUSART_RX_ISR(void)
{
    if(EUSART_RxInterruptHandler){
        EUSART_RxInterruptHandler();
    }
    else{/* Nothing */}
    
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    else{/* Nothing */}
    
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
    else{/* Nothing */}
}
#endif
