/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : servo_motor.c   *******************
*********************	Date  : 13 AUG, 2023	*******************
*******************************************************************/

#include "servo_motor.h"

static timer2_t timer2_pwm = {
    .TMR2_InterruptHandler = NULL,
    .prescaler_value = TIMER2_PRESCALER_DIV_4,
    .postscaler_value = TIMER2_POSTSCALER_DIV_1,
    .preload_value = 0
};

static ccp1_t ccp_pwm = {
    .CCP1_InterruptHandler = NULL,
    .mode = CCP_PWM_MODE,
    .pwm_frequency = 50,
    .timer2_postscaler_value = CCP_TIMER2_POSTSCALER_DIV_1,
    .timer2_prescaler_value = CCP_TIMER2_PRESCALER_DIV_4
};

Std_ReturnType Servo_Motor_Initialize()
{
    Std_ReturnType ret = E_NOT_OK;
    
    ret = timer2_intialize(&timer2_pwm);
    ret = CCP1_intialize(&ccp_pwm);
    CCPR1L = PR2 - 0;
    ret = CCP1_PWM_Start();
    
    return ret;
}

Std_ReturnType Servo_Motor_Set_Angle(uint8 angle)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(180 >= angle)
    {
        ret = E_OK;
        angle = 180 - angle;
        // Map angle to PWM duty cycle values
        uint16 dutyCycle = (uint16)((angle / 180.0) * 250) + 25;
        // Set PWM duty cycle
        CCP1CONbits.DC1B = (uint8)(dutyCycle & 0x03);
        CCPR1L = (uint8)(dutyCycle >> 2);
    }
    return ret; 
}
