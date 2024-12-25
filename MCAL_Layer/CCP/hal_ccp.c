/* 
 * File:   hal_ccp.c
 * Author: Ehab
 *
 * Created on 18 ?????, 2023, 10:11 ?
 */

#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType CCP1_interrupt_handle(const ccp1_t *ccp);
static void (*CCP1_InterruptHandler)(void) = NULL;
void CCP1_ISR(void);
#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType CCP2_interrupt_handle(const ccp2_t *ccp);
static void (*CCP2_InterruptHandler)(void) = NULL;
void CCP2_ISR(void);
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE\
    || CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE\
    || CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE\
    || CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
static inline Std_ReturnType CCP_Select_Timer(ccp_cature_compare_timer_t ccp_timer);
#endif

/**
 ****      CCP1 Interfaces    ****
 */
Std_ReturnType CCP1_intialize(const ccp1_t *ccp)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != ccp){
        ret = E_OK;
        
        /* Disable CCP1 mode */
        CCP1_SELECT_MODE(CCP_MODULE_DISABLE);
        
        /* Setting CCP1 Selected Mode */
        #if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
        /* Setting CCP1 bit <input> */
        TRISCbits.RC2 = 1;
        
        /* Configure mode */
        switch(ccp->mode){
            case CCP_CAPTURE_MODE_FALLING_EDGE:
                CCP1_SELECT_MODE(CCP_CAPTURE_MODE_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_RISING_EDGE:
                CCP1_SELECT_MODE(CCP_CAPTURE_MODE_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4TH_RISING_EDGE:
                CCP1_SELECT_MODE(CCP_CAPTURE_MODE_4TH_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16TH_RISING_EDGE:
                CCP1_SELECT_MODE(CCP_CAPTURE_MODE_16TH_RISING_EDGE);
                break;
            default: ret = E_NOT_OK;
        }
        
        /* Select CCP1 Timer */
        ret = CCP_Select_Timer(ccp->ccp_timer);
        
        #endif

        #if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
        /* Clearing CCP1 bit <output> */
        TRISCbits.RC2 = 0;
                
        /* Configure mode */
        switch(ccp->mode){
            case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                CCP1_SELECT_MODE(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                break;
            case CCP_COMPARE_MODE_CLEAR_CCP_PIN:
                CCP1_SELECT_MODE(CCP_COMPARE_MODE_CLEAR_CCP_PIN);
                break;
            case CCP_COMPARE_MODE_SET_CCP_PIN:
                CCP1_SELECT_MODE(CCP_COMPARE_MODE_SET_CCP_PIN);
                break;
            case CCP_COMPARE_MODE_GENERATE_SOFTWARE_INTERRUPT:
                CCP1_SELECT_MODE(CCP_COMPARE_MODE_GENERATE_SOFTWARE_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT:
                CCP1_SELECT_MODE(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);
                break;
            default: ret = E_NOT_OK;
        }
        
        /* Select CCP1 Timer */
        ret = CCP_Select_Timer(ccp->ccp_timer);
        
        #endif

        #if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
        /* Clearing CCP1 bit <output> */
        TRISCbits.RC2 = 0;
        
        /* Write Period value */
        PR2 = (uint8)((_XTAL_FREQ / ((uint32)4 * (ccp->pwm_frequency) *
                     (ccp->timer2_postscaler_value) * (ccp->timer2_prescaler_value))) - 1);
        #endif
        
        /* CCP1 Interrupt handling */
        #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        CCP1_interrupt_handle(ccp);
        #endif
    }
    return ret;
}

Std_ReturnType CCP1_DeIntialize(const ccp1_t *ccp)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != ccp){
        ret = E_OK;
        /* Disable CCP1 Module */
        CCP1_SELECT_MODE(CCP_MODULE_DISABLE);

        /* Disable Interrupt */
        #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            CCP1_InterruptHandler = NULL;
            CCP1_INTERRUPT_DISABLE();
            CCP1_INTERRUPT_CLEAR_FLAG();
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            if(INTERRUPT_LOW_PRIORITY == ccp->priority){
                INTERRUPT_GlobalInterruptLowPriority_Disable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == ccp->priority){
                INTERRUPT_GlobalInterruptHighPriority_Disable();
            }
            else{ ret = E_NOT_OK; }
        #else
            INTERRUPT_GlobalInterrupt_Disable();
            INTERRUPT_PeripheraInterrupt_Disable();
        #endif
        #endif
    }

    return ret;
}

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *capture_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != capture_status){
        ret = E_OK;
        if(CAPTURE_READY == PIR1bits.CCP1IF){
            *capture_status = CAPTURE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else{
            *capture_status = CAPTURE_NOT_READY;
        }
    }
    return ret;
}

Std_ReturnType CCP1_CaptureModeReadValue(uint16 *captured_value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != captured_value){
        ret = E_OK;
        ccp_reg_t ccpr = {.ccpr_low = CCPR1L, .ccpr_high = CCPR1H};
        *captured_value = ccpr.ccpr_16bit;
    }
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
Std_ReturnType CCP1_IsCompareComplete(uint8 *compare_status)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != compare_status){
        ret = E_OK;
        if(COMPARE_READY == PIR1bits.CCP1IF){
            *compare_status = COMPARE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else{
            *compare_status = COMPARE_NOT_READY;
        }
    }
    return ret;
}

Std_ReturnType CCP1_CompareModeSetValue(uint16 captured_value)
{
    Std_ReturnType ret = E_OK;
    ccp_reg_t ccpr = {.ccpr_low = 0, .ccpr_high = 0};
    ccpr.ccpr_16bit = captured_value;
    CCPR1L = ccpr.ccpr_low;
    CCPR1H = ccpr.ccpr_high;
    return ret;
}
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
Std_ReturnType CCP1_PWM_Set_Duty(uint8 duty)
{
    Std_ReturnType ret = E_NOT_OK;

    if(100 >= duty){
        ret = E_OK;
        duty = 100 - duty;  
        
        uint16 duty_cycle = (uint16)((PR2 + 1) * (duty / 100.0) * 4);
        
        CCP1CONbits.DC1B = (uint8)(duty_cycle & 0x03);
        CCPR1L = (uint8)(duty_cycle >> 2);
    }
    
    return ret;
}

Std_ReturnType CCP1_PWM_Start()
{
    Std_ReturnType ret = E_OK;
    CCP1_SELECT_MODE(CCP_PWM_MODE);
    return ret;
}

Std_ReturnType CCP1_PWM_Stop()
{
    Std_ReturnType ret = E_OK;
    CCP1_SELECT_MODE(CCP_MODULE_DISABLE);
    return ret;
}
#endif


#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType CCP1_interrupt_handle(const ccp1_t *ccp)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != ccp){
        ret = E_OK;
        
        CCP1_InterruptHandler = ccp->CCP1_InterruptHandler;
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG();
        
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PEIORITY_LEVELS_ENABLe();
            if(INTERRUPT_LOW_PRIORITY == ccp->priority)
            {
                CCP1_INTERRUPT_SET_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowPriority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == ccp->priority)
            {
                CCP1_INTERRUPT_SET_HIGH_PRIORITY();
                INTERRUPT_GlobalInterruptHighPriority_Enable();
            }
            else{ ret = E_NOT_OK; }
        #else
            INTERRUPT_PEIORITY_LEVELS_DISABLE();
            INTERRUPT_GlobalInterrupt_Enable();
            INTERRUPT_PeripheraInterrupt_Enable();
        #endif
    }
    return ret;
}

void CCP1_ISR(void)
{
    CCP1_INTERRUPT_CLEAR_FLAG();
    
    if(NULL != CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}
#endif


/**
 ****      CCP2 Interfaces    ****
 */
Std_ReturnType CCP2_intialize(const ccp2_t *ccp){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != ccp){
        ret = E_OK;
        
        /* Disable CCP2 mode */
        CCP2_SELECT_MODE(CCP_MODULE_DISABLE);
        
        /* Setting CCP2 Selected Mode */
        #if (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
        /* Setting CCP2 bit <input> */
        TRISCbits.RC1 = 1;
        
        /* Configure mode */
        switch(ccp->mode){
            case CCP_CAPTURE_MODE_FALLING_EDGE:
                CCP2_SELECT_MODE(CCP_CAPTURE_MODE_FALLING_EDGE);
                break;
            case CCP_CAPTURE_MODE_RISING_EDGE:
                CCP2_SELECT_MODE(CCP_CAPTURE_MODE_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_4TH_RISING_EDGE:
                CCP2_SELECT_MODE(CCP_CAPTURE_MODE_4TH_RISING_EDGE);
                break;
            case CCP_CAPTURE_MODE_16TH_RISING_EDGE:
                CCP2_SELECT_MODE(CCP_CAPTURE_MODE_16TH_RISING_EDGE);
                break;
            default: ret = E_NOT_OK;
        }
        
        /* Select CCP2 Timer */
        ret = CCP_Select_Timer(ccp->ccp_timer);
        
        #endif

        #if (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
        /* Clearing CCP2 bit <output> */
        TRISCbits.RC1 = 0;
        
        /* Configure mode */
        switch(ccp->mode){
            case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                CCP2_SELECT_MODE(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                break;
            case CCP_COMPARE_MODE_CLEAR_CCP_PIN:
                CCP2_SELECT_MODE(CCP_COMPARE_MODE_CLEAR_CCP_PIN);
                break;
            case CCP_COMPARE_MODE_SET_CCP_PIN:
                CCP2_SELECT_MODE(CCP_COMPARE_MODE_SET_CCP_PIN);
                break;
            case CCP_COMPARE_MODE_GENERATE_SOFTWARE_INTERRUPT:
                CCP2_SELECT_MODE(CCP_COMPARE_MODE_GENERATE_SOFTWARE_INTERRUPT);
                break;
            case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT:
                CCP2_SELECT_MODE(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);
                break;
            default: ret = E_NOT_OK;
        }
        
        /* Select CCP1 Timer */
        ret = CCP_Select_Timer(ccp->ccp_timer);
        
        #endif

        #if (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
        /* Clearing CCP2 bit <output> */
        TRISCbits.RC1 = 0;
        
        /* Write Period value */
        PR2 = (uint8)((_XTAL_FREQ / ((uint32)4 * (ccp->pwm_frequency) * 
                     (ccp->timer2_postscaler_value) * (ccp->timer2_prescaler_value))) - 1);
        #endif

        /* CCP2 Interrupt handling */
        CCP2_interrupt_handle(ccp);
    }
    return ret;
}
Std_ReturnType CCP2_DeIntialize(const ccp2_t *ccp){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != ccp){
        ret = E_OK;
        /* Disable CCP2 Module */
        CCP2_SELECT_MODE(CCP_MODULE_DISABLE);

        /* Disable Interrupt */
        #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            CCP2_InterruptHandler = NULL;
            CCP2_INTERRUPT_DISABLE();
            CCP2_INTERRUPT_CLEAR_FLAG();
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            if(INTERRUPT_LOW_PRIORITY == ccp->priority){
                INTERRUPT_GlobalInterruptLowPriority_Disable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == ccp->priority){
                INTERRUPT_GlobalInterruptHighPriority_Disable();
            }
            else{ ret = E_NOT_OK; }
        #else
            INTERRUPT_GlobalInterrupt_Disable();
            INTERRUPT_PeripheraInterrupt_Disable();
        #endif
        #endif
    }
    
    return ret;
}

#if (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
Std_ReturnType CCP2_IsCapturedDataReady(uint16 *capture_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != capture_status){
        ret = E_OK;
        if(CAPTURE_READY == PIR2bits.CCP2IF){
            *capture_status = CAPTURE_READY;
            CCP2_INTERRUPT_CLEAR_FLAG();
        }
        else{
            *capture_status = CAPTURE_NOT_READY;
        }
    }
    return ret;
}

Std_ReturnType CCP2_CaptureModeReadValue(uint16 *captured_value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != captured_value){
        ret = E_OK;
        ccp_reg_t ccpr = {.ccpr_low = CCPR2L, .ccpr_high = CCPR2H};
        *captured_value = ccpr.ccpr_16bit;
    }
    return ret;
}
#endif

#if (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
Std_ReturnType CCP2_IsCompareComplete(uint8 *compare_status){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != compare_status){
        ret = E_OK;
        if(COMPARE_READY == PIR2bits.CCP2IF){
            *compare_status = COMPARE_READY;
            CCP2_INTERRUPT_CLEAR_FLAG();
        }
        else{
            *compare_status = COMPARE_NOT_READY;
        }
    }
    return ret;
}

Std_ReturnType CCP2_CompareModeSetValue(uint16 captured_value){
    Std_ReturnType ret = E_OK;
    ccp_reg_t ccpr = {.ccpr_low = 0, .ccpr_high = 0};
    ccpr.ccpr_16bit = captured_value;
    CCPR2L = ccpr.ccpr_low;
    CCPR2H = ccpr.ccpr_high;
    return ret;
}
#endif

#if (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
Std_ReturnType CCP2_PWM_Set_Duty(uint8 duty){
    Std_ReturnType ret = E_NOT_OK;
    
    if(100 >= duty){
        ret = E_OK;
        uint16 duty_cycle = (uint16)((PR2 + 1) * (duty / 100.0) * 4.0);
        CCP2CONbits.DC2B = duty_cycle & (uint8)0x03;
        CCPR2L = (uint8)(duty_cycle >> 2);
    }
    
    return ret;
}

Std_ReturnType CCP2_PWM_Start(){
    Std_ReturnType ret = E_OK;
    CCP2_SELECT_MODE(CCP_PWM_MODE);
    return ret;
}

Std_ReturnType CCP2_PWM_Stop(){
    Std_ReturnType ret = E_OK;
    CCP2_SELECT_MODE(CCP_MODULE_DISABLE);
    return ret;
}
#endif

#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType CCP2_interrupt_handle(const ccp2_t *ccp){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != ccp){
        ret = E_OK;
        
        CCP2_InterruptHandler = ccp->CCP2_InterruptHandler;
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG();
        
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PEIORITY_LEVELS_ENABLe();
            if(INTERRUPT_LOW_PRIORITY == ccp->priority)
            {
                CCP2_INTERRUPT_SET_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowPriority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == ccp->priority)
            {
                CCP2_INTERRUPT_SET_HIGH_PRIORITY();
                INTERRUPT_GlobalInterruptHighPriority_Enable();
            }
            else{ ret = E_NOT_OK; }
        #else
            INTERRUPT_PEIORITY_LEVELS_DISABLE();
            INTERRUPT_GlobalInterrupt_Enable();
            INTERRUPT_PeripheraInterrupt_Enable();
        #endif
    }
    return ret;
}

void CCP2_ISR(void){
   CCP2_INTERRUPT_CLEAR_FLAG();
    
    if(NULL != CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    } 
}
#endif

/* Select Timer1/Timer3 for CCP1/CCP2 */
#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE\
    || CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE\
    || CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE\
    || CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
static inline Std_ReturnType CCP_Select_Timer(ccp_cature_compare_timer_t ccp_timer){
    Std_ReturnType ret = E_OK;
    if(CCP1_CCP2_TIMER1 == ccp_timer){
        /* Timer1 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp_timer){
        /* Timer3 is the capture/compare clock source for CCP2 */
        /* Timer1 is the capture/compare clock source for CCP1 */
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER3 == ccp_timer){
        /* Timer3 is the capture/compare clock source for the CCP modules */
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else{ret = E_NOT_OK;}
    return ret;
}
#endif
