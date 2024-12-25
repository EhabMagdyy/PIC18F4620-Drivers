/* 
 * File:   hal_usart.h
 * Author: Ehab
 *
 * Created on 30 ?????, 2023, 07:13 ?
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/* -------------Section: Includes-------------- */
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* --------------Section: Macro Declarations-------------- */
/* Enable / Disable EUSART Module */
#define EUSART_MODULE_ENABLE                1
#define EUSART_MODULE_DISABLE               0

/* Selecting EUSART Working Mode */
#define EUSART_SYNCHRONOUS_MODE             1
#define EUSART_ASYNCHRONOUS_MODE            0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED      1
#define EUSART_ASYNCHRONOUS_LOW_SPEED       0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN           1
#define EUSART_08BIT_BAUDRATE_GEN           0

/* EUSART Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE       1
#define EUSART_ASYNCHRONOUS_TX_DISABLE      0
/* EUSART 9-Bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9Bit_TX         1
#define EUSART_ASYNCHRONOUS_8Bit_TX         0
/* Transimmit shift register empty or full */
#define EUSART_TX_SHIFT_REGISTER_EMPTY      1
#define EUSART_TX_SHIFT_REGISTER_FULL       0

/* EUSART Receiver Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE       1
#define EUSART_ASYNCHRONOUS_RX_DISABLE      0
/* EUSART 9-Bit Receiver Enable */
#define EUSART_ASYNCHRONOUS_9Bit_RX         1
#define EUSART_ASYNCHRONOUS_8Bit_RX         0
/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED       1
#define EUSART_FRAMING_ERROR_CLEARED        0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED       1
#define EUSART_OVERRUN_ERROR_CLEARED        0

/*-------------- Section: Macro Function Declarations -----------------*/


/*-------------- Data Types Declarations---------------- */
typedef enum{
    BAUDRATE_ASYN_8BIT_lOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_lOW_SPEED,   
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT
} baudrate_gen_t;

typedef struct{
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t tx_priority;
#endif
    uint8 tx_enable     : 1;
    uint8 tx_8bit_9bit  : 1;
    uint8 reserved      : 6;
} usart_tx_t;

typedef struct{
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t rx_priority;
#endif
    uint8 rx_enable     : 1;
    uint8 rx_8bit_9bit  : 1;
    uint8 reserved      : 6;
} usart_rx_t;

typedef union{
	struct{
		uint8 reserved   : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
} usart_rx_error_status_t;

typedef struct{
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*EUSART_TxDefaultInterruptHandler)(void);
#endif
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
#endif
    uint32 baudrate;
    baudrate_gen_t baudrate_config;
    usart_tx_t tx_config;
    usart_rx_t rx_config;
    usart_rx_error_status_t error_status;
} usart_t;

/*-------------- Function Declarations-------------- */
Std_ReturnType EUSART_ASYNC_Intialize(const usart_t* usart);
Std_ReturnType EUSART_ASYNC_DeIntialize(const usart_t* usart);

Std_ReturnType EUSART_ASYNC_ReceiveByteBlocking(uint8 *data);
Std_ReturnType EUSART_ASYNC_ReceiveByteNonBlocking(uint8 *data);
Std_ReturnType EUSART_ASYNC_Rx_Restart();

Std_ReturnType EUSART_ASYNC_SendByteBlocking(uint8 data);
Std_ReturnType EUSART_ASYNC_SendStringBlocking(uint8 *str, uint8 length);
Std_ReturnType EUSART_ASYNC_SendByteNonBlocking(uint8 data);
Std_ReturnType EUSART_ASYNC_SendStringNonBlocking(uint8 *str, uint8 length);

#endif	/* HAL_USART_H */
