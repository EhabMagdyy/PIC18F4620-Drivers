/* 
 * File:   ecu_keypad.h
 * Author: Ehab
 *
 * Created on 06 ????, 2023, 04:50 ?
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section: Includes */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */
#define KEYPAD_ROWS     4
#define KEYPAD_COLOUMNS 4

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];
    pin_config_t keypad_coloumns_pins[KEYPAD_COLOUMNS];
}keypad_t;

/* Function Declarations */
Std_ReturnType keypad_intialize(const keypad_t *keypad);
Std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

