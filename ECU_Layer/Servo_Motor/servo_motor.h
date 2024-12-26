/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : servo_motor.h   *******************
*********************	Date  : 13 AUG, 2023	*******************
*******************************************************************/

#ifndef SERVO_MOTOR_H
#define	SERVO_MOTOR_H


/**************************** Includes ****************************/
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/CCP/hal_ccp.h"
#include "../../MCAL_Layer/Timer2/hal_timer2.h"

/************************ Macro Declarations **********************/


/********************* Data Types Declarations ********************/


/********************** Function Declarations *********************/
Std_ReturnType Servo_Motor_Initialize();
Std_ReturnType Servo_Motor_Set_Angle(uint8 angle);

#endif	/* SERVO_MOTOR_H */

