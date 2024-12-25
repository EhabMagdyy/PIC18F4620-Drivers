/* 
 * File:   hal_timer1.h
 * Author: Ehab
 *
 * Created on 16 ?????, 2023, 06:05 ?
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* -------------Section: Includes-------------- */
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* --------------Section: Macro Declarations-------------- */
#define TIMER1_COUNTER_MODE             1
#define TIMER1_TIMER_MODE               0

#define TIMER1_OSCILLATOR_ENABLE        1
#define TIMER1_OSCILLATOR_DISABLE       0

#define TIMER1_ASYNCHRONIZE_COUNTER_CLOCK       1
#define TIMER1_SYNCHRONIZE_COUNTER_CLOCK        0

#define TIMER1_READ_WRITE_16BIT_MODE            1
#define TIMER1_READ_WRITE_8BIT_MODE             0

/*-------------- Section: Macro Function Declarations -----------------*/
#define TIMER1_MODULE_ENABLE()                      (T1CONbits.TMR1ON = 1)
#define TIMER1_MODULE_DISABLE()                     (T1CONbits.TMR1ON = 0)

#define TIMER1_SET_COUNTER_MODE()                   (T1CONbits.TMR1CS = 1)
#define TIMER1_SET_TIMER_MODE()                     (T1CONbits.TMR1CS = 0)

#define TIMER1_SET_ASYNCHRONIZE_COUNTER_CLOCK()     (T1CONbits.T1SYNC = 1)
#define TIMER1_SET_SYNCHRONIZE_COUNTER_CLOCK()      (T1CONbits.T1SYNC = 0)

#define TIMER1_SET_OSCILLATOR_ENABLE()              (T1CONbits.T1OSCEN = 1)
#define TIMER1_SET_OSCILLATOR_DISABLE()             (T1CONbits.T1OSCEN = 0)

#define TIMER1_READ_CLOCK_STATUS()                  (T1CONbits.T1RUN)   

#define TIMER1_SET_READ_WRITE_16BIT_MODE()          (T1CONbits.RD16 = 1)
#define TIMER1_SET_READ_WRITE_8BIT_MODE()           (T1CONbits.RD16 = 0)

#define TIMER1_PRESCALER_WRITE_VALUE(prescaler_value)   (T1CONbits.T1CKPS = prescaler_value)

#define TIMER1_WRITE_VALUE(value)       do{ TMR1H = (value >> 8) & 0xFF;\
                                            TMR1L = value & 0xFF;\
                                        } while(0);
                                                    

/*-------------- Data Types Declarations---------------- */
typedef enum{
    TIMER1_PRESCALER_DIV_1 = 0,
    TIMER1_PRESCALER_DIV_2,
    TIMER1_PRESCALER_DIV_4,
    TIMER1_PRESCALER_DIV_8
} timer1_prescaler_value_t;

typedef struct{
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*TMR1_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t priority;
#endif
#endif
    uint16 preload_value;
    timer1_prescaler_value_t prescaler_value;
    uint8 mode                  : 1;
    uint8 oscillator_enable     : 1;
    uint8 synchronization       : 1;
    uint8 rw_mode               : 1;
    uint8 reserved              : 4;
} timer1_t;

/*-------------- Function Declarations-------------- */
Std_ReturnType timer1_intialize(const timer1_t *_timer);
Std_ReturnType timer1_deIntialize(const timer1_t *_timer);
Std_ReturnType timer1_write_value(const timer1_t *_timer, uint16 value);
Std_ReturnType timer1_read_value(const timer1_t *_timer, uint16 *value);

#endif	/* HAL_TIMER1_H */

