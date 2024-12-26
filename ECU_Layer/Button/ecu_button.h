/* 
 * File:   ecu_button.h
 * Author: Ehab
 *
 * Created on 28 ????, 2023, 04:25 ?
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section: Includes */
#include "ecu_button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_REALEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW    
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/* Function Declarations */
Std_ReturnType button_intialize(const button_t *btn);
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

