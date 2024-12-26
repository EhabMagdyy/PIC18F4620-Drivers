/* 
 * File:   ecu_layer_int.h
 * Author: Ehab
 *
 * Created on 06 ????, 2023, 09:21 ?
 */

#ifndef ECU_LAYER_INT_H
#define	ECU_LAYER_INT_H

/* Section: Includes */
#include "LED/ecu_led.h"
#include "Button/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "Motor/ecu_motor.h"
#include "Seven_segment/ecu_seven_segment.h"
#include "Keypad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */
extern lcd_4bit_t lcd_4bit;
extern motor_t motor_1;
extern motor_t motor_2;

/* Function Declarations */
void ecu_layer_intialize(void);

#endif	/* ECU_LAYER_INT_H */

