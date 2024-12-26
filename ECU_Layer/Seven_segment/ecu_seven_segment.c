/* 
 * File:   ecu_seven_segment.c
 * Author: Ehab
 *
 * Created on 19 ?????, 2023, 12:41 ?
 */

#include "ecu_seven_segment.h"

/**
 * 
 * @param segment
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType seven_segment_intialize(const segment_t* segment){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != segment){
        ret = E_OK;
        for(int i = 0 ; i < 4 ; i++){
            ret = gpio_pin_intialize(&(segment->segment_pins[i]));
        }
    }
    return ret;
}

/**
 * 
 * @param segment
 * @param number
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t* segment, uint8 number){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL != segment) && (number < 10)){
        ret = E_OK;
        for(int i = 0 ; i < 4 ; i++){
            ret = gpio_pin_write_logic(&(segment->segment_pins[i]), (number >> i) & 0x01);
        }
    }
    return ret;
}

