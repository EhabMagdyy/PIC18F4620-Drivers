/* 
 * File:   hal_timer1.c
 * Author: Ehab
 *
 * Created on 16 ?????, 2023, 06:05 ?
 */

#include "hal_timer1.h"

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static inline Std_ReturnType timer1_interrupt_handle(const timer1_t *_timer);
static void (*TMR1_InterruptHandler)(void) = NULL;
void TMR1_ISR(void);
#endif

static uint16 tmr1_preload_value; 

static inline Std_ReturnType timer1_select_mode(const timer1_t *_timer);


Std_ReturnType timer1_intialize(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        /* Disable Timer1 Module */
        TIMER1_MODULE_DISABLE();
        
        /* Select mode (counter "Sync / Async" / timer) */
        ret = timer1_select_mode(_timer);
        
        /* Set Prescaler Value */
        TIMER1_PRESCALER_WRITE_VALUE(_timer->prescaler_value);
        
        /* Write preload value */
        TIMER1_WRITE_VALUE(_timer->preload_value);
        tmr1_preload_value = _timer->preload_value;
        
        /* Timer1 Oscillator Clock */
        if(TIMER1_OSCILLATOR_ENABLE == _timer->oscillator_enable){TIMER1_SET_OSCILLATOR_ENABLE();}
        else if(TIMER1_OSCILLATOR_DISABLE == _timer->oscillator_enable){TIMER1_SET_OSCILLATOR_DISABLE();}
        else{ ret = E_NOT_OK; }
        
        /* Set Read/Write Register size */
        if(TIMER1_READ_WRITE_16BIT_MODE == _timer->rw_mode){
            TIMER1_SET_READ_WRITE_16BIT_MODE();
        }
        else if(TIMER1_READ_WRITE_8BIT_MODE == _timer->rw_mode){
            TIMER1_SET_READ_WRITE_8BIT_MODE();
        }
        else{ ret = E_NOT_OK; }
        
        /* Interrupt Handling */
        #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        timer1_interrupt_handle(_timer);
        #endif
        
        /* Enable Timer1 Module */
        TIMER1_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType timer1_deIntialize(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        /* Disable Timer0 Module */
        TIMER1_MODULE_DISABLE();
        
        /* Disable Interrupt */
        #if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
            TMR1_InterruptHandler = NULL;
            TIMER1_INTERRUPT_DISABLE();
            TIMER1_INTERRUPT_CLEAR_FLAG();
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

Std_ReturnType timer1_write_value(const timer1_t *_timer, uint16 value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        TMR1H = (value >> 8) & 0xFF;
        TMR1L = value & 0xFF;
    }
    return ret;
}

Std_ReturnType timer1_read_value(const timer1_t *_timer, uint16 *value){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer && NULL != value){
        ret = E_OK;
        uint8 low_byte = TMR1L;
        uint8 high_byte = TMR1H;
        *value = (uint16)(low_byte + (high_byte << 8));
    }
    return ret;
}

static inline Std_ReturnType timer1_select_mode(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        if(TIMER1_COUNTER_MODE == _timer->mode)
        { 
            TIMER1_SET_COUNTER_MODE();
            
            if(TIMER1_ASYNCHRONIZE_COUNTER_CLOCK == _timer->synchronization){
                TIMER1_SET_ASYNCHRONIZE_COUNTER_CLOCK();
            }
            else if(TIMER1_SYNCHRONIZE_COUNTER_CLOCK == _timer->synchronization){
                TIMER1_SET_SYNCHRONIZE_COUNTER_CLOCK();
            }
            else{ ret = E_NOT_OK; }
        }
        else if(TIMER1_TIMER_MODE == _timer->mode){ 
            TIMER1_SET_TIMER_MODE(); 
        }
        else{ ret = E_NOT_OK; }
    }
    return ret;
}

#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

static inline Std_ReturnType timer1_interrupt_handle(const timer1_t *_timer){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        TMR1_InterruptHandler = _timer->TMR1_InterruptHandler;
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        
        #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PEIORITY_LEVELS_ENABLe();
            if(INTERRUPT_LOW_PRIORITY == _timer->priority)
            {
                TIMER1_INTERRUPT_SET_LOW_PRIORITY();
                INTERRUPT_GlobalInterruptLowPriority_Enable();
            }
            else if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
            {
                TIMER1_INTERRUPT_SET_HIGH_PRIORITY();
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

void TMR1_ISR(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TIMER1_WRITE_VALUE(tmr1_preload_value);
    if(NULL != TMR1_InterruptHandler){
        TMR1_InterruptHandler();
    }
}

#endif
