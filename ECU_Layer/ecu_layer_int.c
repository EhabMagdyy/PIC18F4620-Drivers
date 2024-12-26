/* 
 * File:   ecu_layer_int.c
 * Author: Ehab
 *
 * Created on 06 ????, 2023, 09:21 ?
 */

#include "ecu_layer_int.h"

lcd_4bit_t lcd_4bit = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_enable.port = PORTC_INDEX,
    .lcd_enable.pin = GPIO_PIN1,
    .lcd_enable.direction = GPIO_OUTPUT,
    .lcd_enable.logic = GPIO_LOW,
    .data_lines[0].port = PORTC_INDEX,
    .data_lines[0].pin = GPIO_PIN2,
    .data_lines[0].direction = GPIO_OUTPUT,
    .data_lines[0].logic = GPIO_LOW,
    .data_lines[1].port = PORTC_INDEX,
    .data_lines[1].pin = GPIO_PIN3,
    .data_lines[1].direction = GPIO_OUTPUT,
    .data_lines[1].logic = GPIO_LOW,
    .data_lines[2].port = PORTC_INDEX,
    .data_lines[2].pin = GPIO_PIN4,
    .data_lines[2].direction = GPIO_OUTPUT,
    .data_lines[2].logic = GPIO_LOW,
    .data_lines[3].port = PORTC_INDEX,
    .data_lines[3].pin = GPIO_PIN5,
    .data_lines[3].direction = GPIO_OUTPUT,
    .data_lines[3].logic = GPIO_LOW,
};

motor_t motor_1 = {
    .motor_pin[0].port = PORTD_INDEX,
    .motor_pin[0].pin = GPIO_PIN0,
    .motor_pin[0].direction = GPIO_OUTPUT,
    .motor_pin[0].logic = GPIO_LOW,
    .motor_pin[1].port = PORTD_INDEX,
    .motor_pin[1].pin = GPIO_PIN1,
    .motor_pin[1].direction = GPIO_OUTPUT,
    .motor_pin[1].logic = GPIO_LOW,
};

motor_t motor_2 = {
    .motor_pin[0].port = PORTD_INDEX,
    .motor_pin[0].pin = GPIO_PIN2,
    .motor_pin[0].direction = GPIO_OUTPUT,
    .motor_pin[0].logic = GPIO_LOW,
    .motor_pin[1].port = PORTD_INDEX,
    .motor_pin[1].pin = GPIO_PIN3,
    .motor_pin[1].direction = GPIO_OUTPUT,
    .motor_pin[1].logic = GPIO_LOW,
};

void ecu_layer_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_intialize(&lcd_4bit);
    ret = motor_intialize(&motor_1);
    ret = motor_intialize(&motor_2);
}
