/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : stepper_motor.h *******************
*********************	Date  : 28 Aug, 2023	*******************
*******************************************************************/

#ifndef STEPPER_MOTOR_H
#define	STEPPER_MOTOR_H

/**************************** Includes ****************************/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/mcal_std_types.h"

/************************ Macro Declarations **********************/
#define CW    0
#define CCW   1

#define STEP_ANGLE  0.1f
#define STEP_TIME   10

/********************* Data Types Declarations ********************/
typedef struct{
    pin_config_t StepperMotor_BluePin;
    pin_config_t StepperMotor_PinkPin;
    pin_config_t StepperMotor_YellowPin;
    pin_config_t StepperMotor_OrangePin;
} stepper_motor_t;

/********************** Function Declarations *********************/
Std_ReturnType StepperMotor_Init(const stepper_motor_t* stepper_motor);
Std_ReturnType StepperMotor_Rotate(const stepper_motor_t* stepper_motor, uint16 angle, uint8 direction);

#endif	/* STEPPER_MOTOR_H */

