/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : stepper_motor.c *******************
*********************	Date  : 28 Aug, 2023	*******************
*******************************************************************/

#include "stepper_motor.h"

Std_ReturnType StepperMotor_Init(const stepper_motor_t* stepper_motor)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != stepper_motor)
    {
        ret = E_OK;
        ret = gpio_pin_intialize(&(stepper_motor->StepperMotor_BluePin));
        ret = gpio_pin_intialize(&(stepper_motor->StepperMotor_PinkPin));
        ret = gpio_pin_intialize(&(stepper_motor->StepperMotor_YellowPin));
        ret = gpio_pin_intialize(&(stepper_motor->StepperMotor_OrangePin));
    }
    
    return ret;
}

Std_ReturnType StepperMotor_Rotate(const stepper_motor_t* stepper_motor, uint16 angle, uint8 direction)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != stepper_motor && 360 > angle)
    {
        ret = E_OK;
        uint16 num_of_4steps = (angle / STEP_ANGLE) / 4;
        
        switch(direction)
        {
            case CW:
                for(uint16 steps_itertion = 0 ; steps_itertion < num_of_4steps ; steps_itertion++)
                {
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_BluePin), GPIO_HIGH);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_PinkPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_YellowPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_OrangePin), GPIO_LOW);
                    __delay_ms(STEP_TIME);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_BluePin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_PinkPin), GPIO_HIGH);
                    __delay_ms(STEP_TIME);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_PinkPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_YellowPin), GPIO_HIGH);
                    __delay_ms(STEP_TIME);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_YellowPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_OrangePin), GPIO_HIGH);
                    __delay_ms(STEP_TIME);
                }
                break;
            case CCW:
                for(uint16 steps_itertion = 0 ; steps_itertion < num_of_4steps ; steps_itertion++)
                {
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_OrangePin), GPIO_HIGH);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_YellowPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_PinkPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_BluePin), GPIO_LOW);
                    __delay_ms(STEP_TIME);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_OrangePin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_YellowPin), GPIO_HIGH);
                    __delay_ms(STEP_TIME);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_YellowPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_PinkPin), GPIO_HIGH);
                    __delay_ms(STEP_TIME);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_PinkPin), GPIO_LOW);
                    ret = gpio_pin_write_logic(&(stepper_motor->StepperMotor_BluePin), GPIO_HIGH);
                    __delay_ms(STEP_TIME);
                }
                break;
            default:    break;
        }
    }
    
    return ret;
}
