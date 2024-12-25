/* 
 * File:   hal_timer0.h
 * Author: Ehab
 *
 * Created on 15 ?????, 2023, 10:50 ?
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* -------------Section: Includes-------------- */
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* --------------Section: Macro Declarations-------------- */
#define TIMER0_FALLING_EDGE             1
#define TIMER0_RISING_EDGE              0

#define TIMER0_8BIT_SIZE                1
#define TIMER0_16BIT_SIZE               0

#define TIMER0_COUNTER_MODE             1
#define TIMER0_TIMER_MODE               0

#define TIMER0_PRESCALER_DISABLE        1
#define TIMER0_PRESCALER_ENABLE         0

/*-------------- Section: Macro Function Declarations -----------------*/
#define TIMER0_MODULE_ENABLE()                  (T0CONbits.TMR0ON = 1)
#define TIMER0_MODULE_DISABLE()                 (T0CONbits.TMR0ON = 0)

#define TIMER0_SET_8BIT_SIZE()                  (T0CONbits.T08BIT = 1)
#define TIMER0_SET_16BIT_SIZE()                 (T0CONbits.T08BIT = 0)

#define TIMER0_SET_COUNTER_MODE()               (T0CONbits.T0CS = 1)
#define TIMER0_SET_TIMER_MODE()                 (T0CONbits.T0CS = 0)

#define TIMER0_SET_FALLING_EDGE()               (T0CONbits.T0SE = 1)
#define TIMER0_SET_RISING_EDGE()                (T0CONbits.T0SE = 0)

#define TIMER0_SET_PRESCALER_DISABLE()          (T0CONbits.PSA = 1)
#define TIMER0_SET_PRESCALER_ENABLE()           (T0CONbits.PSA = 0)

#define TIMER0_PRESCALER_WRITE_VALUE(prescaler_value)      (T0CONbits.T0PS = prescaler_value)

#define TIMER0_WRITE_VALUE(value)       do{ TMR0H = (value >> 8) & 0xFF;\
                                            TMR0L = value & 0xFF;\
                                        } while(0);
                                                    

/*-------------- Data Types Declarations---------------- */
typedef enum{
    TIMER0_PRESCALER_DIV_2 = 0,
    TIMER0_PRESCALER_DIV_4,
    TIMER0_PRESCALER_DIV_8,
    TIMER0_PRESCALER_DIV_16,
    TIMER0_PRESCALER_DIV_32,
    TIMER0_PRESCALER_DIV_64,
    TIMER0_PRESCALER_DIV_128,
    TIMER0_PRESCALER_DIV_256
} timer0_prescaler_value_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*TMR0_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t priority;
#endif
#endif
    uint16 preload_value;
    timer0_prescaler_value_t prescaler_value;
    uint8 prescaler_enble   : 1;
    uint8 edge              : 1;
    uint8 register_size     : 1;
    uint8 mode              : 1;
    uint8 reserved          : 4;
} timer0_t;

/*-------------- Function Declarations-------------- */
Std_ReturnType timer0_intialize(const timer0_t *_timer);
Std_ReturnType timer0_deIntialize(const timer0_t *_timer);
Std_ReturnType timer0_write_value(const timer0_t *_timer, uint16 value);
Std_ReturnType timer0_read_value(const timer0_t *_timer, uint16 *value);

#endif	/* HAL_TIMER0_H */

