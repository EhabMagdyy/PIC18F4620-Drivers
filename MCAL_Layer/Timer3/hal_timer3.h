/* 
 * File:   hal_timer3.h
 * Author: Ehab
 *
 * Created on 17 ?????, 2023, 05:14 ?
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* -------------Section: Includes-------------- */
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* --------------Section: Macro Declarations-------------- */
#define TIMER3_COUNTER_MODE             1
#define TIMER3_TIMER_MODE               0

#define TIMER3_ASYNCHRONIZE_COUNTER_CLOCK       1
#define TIMER3_SYNCHRONIZE_COUNTER_CLOCK        0

#define TIMER3_READ_WRITE_16BIT_MODE            1
#define TIMER3_READ_WRITE_8BIT_MODE             0

/*-------------- Section: Macro Function Declarations -----------------*/
#define TIMER3_MODULE_ENABLE()                      (T3CONbits.TMR3ON = 1)
#define TIMER3_MODULE_DISABLE()                     (T3CONbits.TMR3ON = 0)

#define TIMER3_SET_COUNTER_MODE()                   (T3CONbits.TMR3CS = 1)
#define TIMER3_SET_TIMER_MODE()                     (T3CONbits.TMR3CS = 0)

#define TIMER3_SET_ASYNCHRONIZE_COUNTER_CLOCK()     (T3CONbits.T3SYNC = 1)
#define TIMER3_SET_SYNCHRONIZE_COUNTER_CLOCK()      (T3CONbits.T3SYNC = 0)

#define TIMER3_SET_READ_WRITE_16BIT_MODE()          (T3CONbits.RD16 = 1)
#define TIMER3_SET_READ_WRITE_8BIT_MODE()           (T3CONbits.RD16 = 0)

#define TIMER3_PRESCALER_WRITE_VALUE(prescaler_value)   (T3CONbits.T3CKPS = prescaler_value)

#define TIMER3_WRITE_VALUE(value)       do{ TMR3H = (value >> 8) & 0xFF;\
                                            TMR3L = value & 0xFF;\
                                        } while(0);
                                                    

/*-------------- Data Types Declarations---------------- */
typedef enum{
    TIMER3_PRESCALER_DIV_1 = 0,
    TIMER3_PRESCALER_DIV_2,
    TIMER3_PRESCALER_DIV_4,
    TIMER3_PRESCALER_DIV_8
} timer3_prescaler_value_t;

typedef struct{
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*TMR3_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t priority;
#endif
#endif
    uint16 preload_value;
    timer3_prescaler_value_t prescaler_value;
    uint8 mode                  : 1;
    uint8 synchronization       : 1;
    uint8 rw_mode               : 1;
    uint8 reserved              : 5;
} timer3_t;

/*-------------- Function Declarations-------------- */
Std_ReturnType timer3_intialize(const timer3_t *_timer);
Std_ReturnType timer3_deIntialize(const timer3_t *_timer);
Std_ReturnType timer3_write_value(const timer3_t *_timer, uint16 value);
Std_ReturnType timer3_read_value(const timer3_t *_timer, uint16 *value);


#endif	/* HAL_TIMER3_H */

