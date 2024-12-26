/* 
 * File:   ecu_button.c
 * Author: Ehab
 *
 * Created on 28 ????, 2023, 04:25 ?
 */

#include "ecu_button.h"

/**
 * 
 * @param btn
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType button_intialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if(btn == NULL){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(btn->button_pin));
    }
    return ret;
}

/**
 * 
 * @param btn
 * @param btn_state
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    Std_ReturnType ret = E_OK;
    if(btn == NULL || btn_state == NULL){
        ret = E_NOT_OK;
    }
    else{
        uint8 logic_state = GPIO_LOW;
        ret = gpio_pin_read_logic(&(btn->button_pin),&logic_state);
        if(btn->button_connection == BUTTON_ACTIVE_HIGH){
            if(logic_state == GPIO_HIGH){
                *btn_state = BUTTON_PRESSED;
            }
            else{
                *btn_state = BUTTON_REALEASED;
            }
        }
        else if(btn->button_connection == BUTTON_ACTIVE_LOW){
           if(logic_state == GPIO_HIGH){
                *btn_state = BUTTON_REALEASED;
            }
            else{
                *btn_state = BUTTON_PRESSED;
            } 
        }
        else{/* Nothing: E_NOT_OK */};
    }
    return ret;
}

