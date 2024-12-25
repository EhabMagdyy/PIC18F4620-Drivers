/* 
 * File:   hal_timer3.c
 * Author: Ehab
 *
 * Created on 17 ?????, 2023, 05:14 ?
 */

#include "hal_timer3.h"

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType timer3_interrupt_handle(const timer3_t *_timer);
static void (*TMR3_InterruptHandler)(void) = NULL;
void TMR3_ISR(void);
#endif

static uint16 tmr3_preload_value; 

static inline Std_ReturnType timer3_select_mode(const timer3_t *_timer);


Std_ReturnType timer3_intialize(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        /* Disable Timer3 Module */
        TIMER3_MODULE_DISABLE();
        
        /* Select mode (counter "Sync / Async" / timer) */
        ret = timer3_select_mode(_timer);
        
        /* Set Prescaler Value */
        TIMER3_PRESCALER_WRITE_VALUE(_timer->prescaler_value);
        
        /* Write preload value */
        TIMER3_WRITE_VALUE(_timer->preload_value);
        tmr3_preload_value = _timer->preload_value;
        
        /* Set Read/Write Register size */
        if(TIMER3_READ_WRITE_16BIT_MODE == _timer->rw_mode){
            TIMER3_SET_READ_WRITE_16BIT_MODE();
        }
        else if(TIMER3_READ_WRITE_8BIT_MODE == _timer->rw_mode){
            TIMER3_SET_READ_WRITE_8BIT_MODE();
        }
        else{ ret = E_NOT_OK; }
        
        /* Interrupt Handling */
        #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        timer3_interrupt_handle(_timer);
        #endif
        
        /* Enable Timer3 Module */
        TIMER3_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType timer3_deIntialize(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        /* Disable Timer0 Module */
        TIMER3_MODULE_DISABLE();
        
        /* Disable Interrupt */
        #if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            TMR3_InterruptHandler = NULL;
            TIMER3_INTERRUPT_DISABLE();
            TIMER3_INTERRUPT_CLEAR_FLAG();
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

Std_ReturnType timer3_write_value(const timer3_t *_timer, uint16 value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        TMR3H = (value >> 8) & 0xFF;
        TMR3L = value & 0xFF;
    }
    return ret;
}

Std_ReturnType timer3_read_value(const timer3_t *_timer, uint16 *value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer && NULL != value){
        ret = E_OK;
        uint8 low_byte = TMR3L;
        uint8 high_byte = TMR3H;
        *value = (uint16)(low_byte + (high_byte << 8));
    }
    return ret;
}

static inline Std_ReturnType timer3_select_mode(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        if(TIMER3_COUNTER_MODE == _timer->mode)
        { 
            TIMER3_SET_COUNTER_MODE();
            
            if(TIMER3_ASYNCHRONIZE_COUNTER_CLOCK == _timer->synchronization){
                TIMER3_SET_ASYNCHRONIZE_COUNTER_CLOCK();
            }
            else if(TIMER3_SYNCHRONIZE_COUNTER_CLOCK == _timer->synchronization){
                TIMER3_SET_SYNCHRONIZE_COUNTER_CLOCK();
            }
            else{ ret = E_NOT_OK; }
        }
        else if(TIMER3_TIMER_MODE == _timer->mode){ 
            TIMER3_SET_TIMER_MODE(); 
        }
        else{ ret = E_NOT_OK; }
    }
    return ret;
}

#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static inline Std_ReturnType timer3_interrupt_handle(const timer3_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        TMR3_InterruptHandler = _timer->TMR3_InterruptHandler;
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PEIORITY_LEVELS_ENABLe();
            if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                TIMER3_INTERRUPT_SET_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowPriority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                TIMER3_INTERRUPT_SET_HIGH_PRIORITY();
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

void TMR3_ISR(void)
{
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TIMER3_WRITE_VALUE(tmr3_preload_value);
    if(NULL != TMR3_InterruptHandler){
        TMR3_InterruptHandler();
    }
}

#endif

