/* 
 * File:   mcal_interrupt_config.h
 * Author: Ehab
 *
 * Created on 07 ?????, 2023, 03:22 ?
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section: Includes */
#include "mcal_interrupt_gen_cfg.h"
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../GPIO/hal_gpio.h"

/*------------ Section: Macro Declarations ------------ */
#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCURED            1
#define INTERRUPT_NOT_OCCURED        0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0

/*------------ Section: Macro Function Declarations -------------------- */
#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS

#define INTERRUPT_PEIORITY_LEVELS_ENABLe()   (RCONbits.IPEN = 1)  

#define INTERRUPT_GlobalInterruptHighPriority_Enable()   (INTCONbits.GIEH = 1)  
#define INTERRUPT_GlobalInterruptHighPriority_Disable()  (INTCONbits.GIEH = 0) 

#define INTERRUPT_GlobalInterruptLowPriority_Enable()   (INTCONbits.GIEL = 1)  
#define INTERRUPT_GlobalInterruptLowPriority_Disable()  (INTCONbits.GIEL = 0)  

#else

#define INTERRUPT_PEIORITY_LEVELS_DISABLE()  (RCONbits.IPEN = 0) 

#define INTERRUPT_GlobalInterrupt_Enable()   (INTCONbits.GIE = 1)  
#define INTERRUPT_GlobalInterrupt_Disable()  (INTCONbits.GIE = 0)  

#define INTERRUPT_PeripheraInterrupt_Enable()   (INTCONbits.PEIE = 1)  
#define INTERRUPT_PeripheraInterrupt_Disable()  (INTCONbits.PEIE = 0)  

#endif

/* Data Types Declarations */
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
} interrupt_priority_t;

/* Function Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

