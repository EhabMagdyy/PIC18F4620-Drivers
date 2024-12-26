/* 
 * File:   ecu_motor.c
 * Author: Ehab
 *
 * Created on 13 ?????, 2023, 11:20 ?
 */

#include "ecu_motor.h"

/**
 * 
 * @param motor
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType motor_intialize(const motor_t* motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != motor){
        ret = E_OK;
        ret = gpio_pin_intialize(&motor->motor_pin[MOTOR_PIN_1]);
        ret = gpio_pin_intialize(&motor->motor_pin[MOTOR_PIN_2]);
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType motor_move_right(const motor_t* motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != motor){
        ret = E_OK;
        ret = gpio_pin_write_logic(&motor->motor_pin[MOTOR_PIN_1], GPIO_HIGH);
        ret = gpio_pin_write_logic(&motor->motor_pin[MOTOR_PIN_2], GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType motor_move_left(const motor_t* motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != motor){
        ret = E_OK;
        ret = gpio_pin_write_logic(&motor->motor_pin[MOTOR_PIN_1], GPIO_LOW);
        ret = gpio_pin_write_logic(&motor->motor_pin[MOTOR_PIN_2], GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType motor_stop(const motor_t* motor){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != motor){
        ret = E_OK;
        ret = gpio_pin_write_logic(&motor->motor_pin[MOTOR_PIN_1], GPIO_LOW);
        ret = gpio_pin_write_logic(&motor->motor_pin[MOTOR_PIN_2], GPIO_LOW);
    }
    return ret;
}