/* 
 * File:   hal_timer0.c
 * Author: Ehab
 *
 * Created on 15 ?????, 2023, 10:50 ?
 */

#include "hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
static void (*TMR0_InterruptHandler)(void) = NULL;
void TMR0_ISR(void);
#endif

static uint16 tmr0_preload_value;

Std_ReturnType timer0_intialize(const timer0_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        
        /* Disable Timer0 Module */
        TIMER0_MODULE_DISABLE();
        
        /* Set Register Size */
        if(TIMER0_8BIT_SIZE == _timer->register_size){ TIMER0_SET_8BIT_SIZE(); }
        else if(TIMER0_16BIT_SIZE == _timer->register_size){ TIMER0_SET_16BIT_SIZE(); }
        else{ ret = E_NOT_OK; }
        
        /* Set Clock source */
        if(TIMER0_COUNTER_MODE == _timer->mode)
        { 
            TIMER0_SET_COUNTER_MODE(); 
            
            /* Set Edge Selected (Rising / Falling) */
            if(TIMER0_FALLING_EDGE == _timer->edge){TIMER0_SET_FALLING_EDGE();}
            else if(TIMER0_RISING_EDGE == _timer->edge){TIMER0_SET_RISING_EDGE();}
            else{ ret = E_NOT_OK; }
        }
        else if(TIMER0_TIMER_MODE == _timer->mode){ TIMER0_SET_TIMER_MODE(); }
        else{ ret = E_NOT_OK; }
        
        /* Write preload value */
        TIMER0_WRITE_VALUE(_timer->preload_value);
        tmr0_preload_value = _timer->preload_value;
        
        /* Set Prescaler Configuration */
        if(TIMER0_PRESCALER_ENABLE == _timer->prescaler_enble)
        {
            TIMER0_SET_PRESCALER_ENABLE();
            TIMER0_PRESCALER_WRITE_VALUE(_timer->prescaler_value);
        }
        else if(TIMER0_PRESCALER_DISABLE == _timer->prescaler_enble){TIMER0_SET_PRESCALER_DISABLE();}
        else{ ret = E_NOT_OK; }
        
        /* Interrupt Handling */
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TMR0_InterruptHandler = _timer->TMR0_InterruptHandler;
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PEIORITY_LEVELS_ENABLe();
        if(INTERRUPT_LOW_PRIORITY == _timer->priority)
        {
            TIMER0_INTERRUPT_SET_LOW_PRIORITY();
            INTERRUPT_GlobalInterruptLowPriority_Enable();
        }
        else if(INTERRUPT_HIGH_PRIORITY == _timer->priority)
        {
            TIMER0_INTERRUPT_SET_HIGH_PRIORITY();
            INTERRUPT_GlobalInterruptHighPriority_Enable();
        }
        else{ ret = E_NOT_OK; }
#else
        INTERRUPT_PEIORITY_LEVELS_DISABLE();
        INTERRUPT_GlobalInterrupt_Enable();
        INTERRUPT_PeripheraInterrupt_Enable();
#endif
#endif
        
        /* Enable Timer0 Module */
        TIMER0_MODULE_ENABLE();
    }
    return ret;
}

Std_ReturnType timer0_deIntialize(const timer0_t *_timer)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        /* Disable Timer0 Module */
        TIMER0_MODULE_DISABLE();
        
        /* Disable Interrupt */
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TMR0_InterruptHandler = NULL;
        TIMER0_INTERRUPT_DISABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
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

Std_ReturnType timer0_write_value(const timer0_t *_timer, uint16 value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer){
        ret = E_OK;
        TMR0H = (value >> 8) & 0xFF;
        TMR0L = value & 0xFF;
    }
    return ret;
}

Std_ReturnType timer0_read_value(const timer0_t *_timer, uint16 *value)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != _timer && NULL != value){
        ret = E_OK;
        uint8 low_byte = TMR0L;
        uint8 high_byte = TMR0H;
        *value = (uint16)(low_byte + (high_byte << 8));
    }
    return ret;
}

#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
void TMR0_ISR(void)
{
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TIMER0_WRITE_VALUE(tmr0_preload_value);
    if(NULL != TMR0_InterruptHandler){
        TMR0_InterruptHandler();
    }
}
#endif
