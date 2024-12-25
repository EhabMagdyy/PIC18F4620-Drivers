/* 
 * File:   mcal_external_interrupt.h
 * Author: Ehab
 *
 * Created on 07 ?????, 2023, 03:25 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* ------------- Section: Includes -------------- */
#include "mcal_interrupt_config.h"

/* ------------- Section: Macro Declarations --------------------- */

/* ------------- Section: Macro Function Declarations ------------ */
/* ------ INTx ------- */
#if     INTERRUPT_FEATURE_ENABLE ==   EXT_INTERRUPT_INTx_FEATURE_ENABLE

#define EXT_INTERRUPT_INT0_ENABLE()            (INTCONbits.INT0IE = 1)
#define EXT_INTERRUPT_INT0_DISABLE()           (INTCONbits.INT0IE = 0)
#define EXT_INTERRUPT_INT0_FlagSet()           (INTCONbits.INT0IF = 1)
#define EXT_INTERRUPT_INT0_FlagClear()         (INTCONbits.INT0IF = 0)
#define EXT_INTERRUPT_INT0_RisingEdge()        (INTCON2bits.INTEDG0 = 1)
#define EXT_INTERRUPT_INT0_FallingEdge()       (INTCON2bits.INTEDG0 = 0)

#define EXT_INTERRUPT_INT1_ENABLE()            (INTCON3bits.INT1IE = 1)
#define EXT_INTERRUPT_INT1_DISABLE()           (INTCON3bits.INT1IE = 0)
#define EXT_INTERRUPT_INT1_FlagSet()           (INTCON3bits.INT1IF = 1)
#define EXT_INTERRUPT_INT1_FlagClear()         (INTCON3bits.INT1IF = 0)
#define EXT_INTERRUPT_INT1_RisingEdge()        (INTCON2bits.INTEDG1 = 1)
#define EXT_INTERRUPT_INT1_FallingEdge()       (INTCON2bits.INTEDG1 = 0)

#define EXT_INTERRUPT_INT2_ENABLE()            (INTCON3bits.INT2IE = 1)
#define EXT_INTERRUPT_INT2_DISABLE()           (INTCON3bits.INT2IE = 0)
#define EXT_INTERRUPT_INT2_FlagSet()           (INTCON3bits.INT2IF = 1)
#define EXT_INTERRUPT_INT2_FlagClear()         (INTCON3bits.INT2IF = 0)
#define EXT_INTERRUPT_INT2_RisingEdge()        (INTCON2bits.INTEDG2 = 1)
#define EXT_INTERRUPT_INT2_FallingEdge()       (INTCON2bits.INTEDG2 = 0)

#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS

/* Notice: INT0 Has a Fixed High Priority */

#define EXT_INTERRUPT_INT1_HighPriority()      (INTCON3bits.INT1IP = 1)
#define EXT_INTERRUPT_INT1_LowPriority()       (INTCON3bits.INT1IP = 0)

#define EXT_INTERRUPT_INT2_HighPriority()      (INTCON3bits.INT2IP = 1)
#define EXT_INTERRUPT_INT2_LowPriority()       (INTCON3bits.INT2IP = 0)

#endif

#endif

/* ------ RBx ------- */
#if     INTERRUPT_FEATURE_ENABLE ==   EXT_INTERRUPT_RBx_FEATURE_ENABLE

#define EXT_INTERRUPT_RBx_ENABLE()             (INTCONbits.RBIE = 1)
#define EXT_INTERRUPT_RBx_DISABLE()            (INTCONbits.RBIE = 0)
#define EXT_INTERRUPT_RBx_FlagSet()            (INTCONbits.RBIF = 1)
#define EXT_INTERRUPT_RBx_FlagClear()          (INTCONbits.RBIF = 0)

#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS

#define EXT_INTERRUPT_RBx_HighPriority()      (INTCON2bits.RBIP = 1)
#define EXT_INTERRUPT_RBx_LowPriority()       (INTCON2bits.RBIP = 0)

#endif

#endif


/* ----------------- Data Types Declarations -------------------- */
typedef void (*InterrptHandler_FunctionPointer_t)(void);

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISINGING_EDGE
} interrupt_edge_t;

typedef enum{
    INTERRUPT_INT0 = 0,
    INTERRUPT_INT1,
    INTERRUPT_INT2
} interrupt_source_t;

typedef struct{
    void (* EXT_INTERRUPT_HANDLER)(void);
    pin_config_t mcu_pin;
    interrupt_source_t source;
    interrupt_priority_t priority;
    interrupt_edge_t edge;
} interrupt_INTx_t;

typedef struct{
    void (* EXT_INTERRUPT_HANDLER_HIGH)(void);
    void (* EXT_INTERRUPT_HANDLER_LOW)(void);
    pin_config_t mcu_pin;
    interrupt_priority_t priority;
} interrupt_RBx_t;

/* ----------------- Function Declarations -------------------- */
Std_ReturnType interrupt_INTx_intialize(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_INTx_DeIntialize(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_RBx_intialize(const interrupt_RBx_t *int_obj);
Std_ReturnType interrupt_RBx_DeIntialize(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

