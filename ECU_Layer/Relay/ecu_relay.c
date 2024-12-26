/* 
 * File:   ecu_relay.c
 * Author: Ehab
 *
 * Created on 12 ?????, 2023, 12:44 ?
 */

#include "ecu_relay.h"

/**
 * 
 * @param relay
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType relay_intialize(const relay_t *relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != relay){
        ret = E_OK;
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin ,
                            .logic = relay->relay_status , .direction = GPIO_OUTPUT};
        ret = gpio_pin_intialize(&pin_obj);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType relay_turn_on(const relay_t *relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != relay){
        ret = E_OK;
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin ,
                            .logic = relay->relay_status , .direction = GPIO_OUTPUT};
        ret = gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType relay_turn_off(const relay_t *relay){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != relay){
        ret = E_OK;
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin ,
                            .logic = relay->relay_status , .direction = GPIO_OUTPUT};
        ret = gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;
}