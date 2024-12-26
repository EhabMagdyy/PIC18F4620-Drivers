/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : ultrasonic.h    *******************
*********************	Date  : 13 AUG, 2023	*******************
*******************************************************************/

#ifndef ULTRASONIC_H
#define	ULTRASONIC_H

/**************************** Includes ****************************/
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Timer0/hal_timer0.h"

/************************ Macro Declarations **********************/

/********************* Data Types Declarations ********************/
typedef struct{
    pin_config_t Trigger_Pin;
    pin_config_t Echo_Pin; 
}ultrasonic_t;

/********************** Function Declarations *********************/
Std_ReturnType Ultrasonic_Init(const ultrasonic_t *obj);
Std_ReturnType Ultrasonic_Calculate_Distance(const ultrasonic_t *obj, uint16 *distance);

#endif	/* ULTRASONIC_H */
