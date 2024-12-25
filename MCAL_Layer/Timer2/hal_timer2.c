/* 
 * File:   hal_timer2.c
 * Author: Ehab
 *
 * Created on 17 ?????, 2023, 03:17 ?
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType timer2_interrupt_handle(const timer2_t *_timer);
static void (*TMR2_InterruptHandler)(void) = NULL;
void TMR2_ISR(void);
#endif

static uint8 tmr2_preload_value; 

Std_ReturnType timer2_intialize(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        /* Disable Timer1 Module */
        TIMER2_MODULE_DISABLE();
        
        /* Set Prescaler Value */
        TIMER2_PRESCALER_WRITE_VALUE(_timer->prescaler_value);
        
        /* Set Postscaler Value */
        TIMER2_POSTSCALER_WRITE_VALUE(_timer->postscaler_value);
        
        /* Write preload value */
        TIMER2_WRITE_VALUE(_timer->preload_value);
        tmr2_preload_value = _timer->preload_value;
        
        /* Interrupt Handling */
        #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        timer2_interrupt_handle(_timer);
        #endif
        
        /* Enable Timer1 Module */
        TIMER2_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType timer2_deIntialize(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        /* Disable Timer0 Module */
        TIMER2_MODULE_DISABLE();
        
        /* Disable Interrupt */
        #if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            TMR2_InterruptHandler = NULL;
            TIMER2_INTERRUPT_DISABLE();
            TIMER2_INTERRUPT_CLEAR_FLAG();
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            if(INTERRUPT_LOW_PRIORITY == _timer->priority){
                INTERRUPT_GlobalInterruptLowPriority_Disable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _timer->priority){
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

Std_ReturnType timer2_write_value(const timer2_t *_timer, uint8 value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        TIMER2_WRITE_VALUE(value);
    }
    return ret;
}

Std_ReturnType timer2_read_value(const timer2_t *_timer, uint8 *value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer && NULL != value){
        ret = E_OK;
        *value = TMR2;
    }
    return ret;
}

#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType timer2_interrupt_handle(const timer2_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        TMR2_InterruptHandler = _timer->TMR2_InterruptHandler;
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
        
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PEIORITY_LEVELS_ENABLe();
            if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                TIMER2_INTERRUPT_SET_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowPriority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                TIMER2_INTERRUPT_SET_HIGH_PRIORITY();
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

void TMR2_ISR(void)
{
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TIMER2_WRITE_VALUE(tmr2_preload_value);
    if(NULL != TMR2_InterruptHandler){
        TMR2_InterruptHandler();
    }
}
#endif
