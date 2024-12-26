/* 
 * File:   ecu_led.h
 * Author: Ehab
 *
 * Created on 15 ????, 2023, 05:25 ?
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef enum{
    LED_OFF = 0,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port          :3;
    uint8 pin           :3;
    uint8 led_status    :1;
    uint8 reserved      :1;
}led_t;

/* Function Declarations */
Std_ReturnType led_intialiaze(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

