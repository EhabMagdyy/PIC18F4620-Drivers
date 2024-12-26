/* 
 * File:   ecu_relay.h
 * Author: Ehab
 *
 * Created on 12 ?????, 2023, 12:44 ?
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section: Includes */
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef enum{
    RELAY_OFF = 0,
    RELAY_ON
}relay_status_t;

typedef struct{
    uint8 relay_port            :4;
    uint8 relay_pin             :3;
    uint8 relay_status :1;
}relay_t;
        
/* Function Declarations */
Std_ReturnType relay_intialize(const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

