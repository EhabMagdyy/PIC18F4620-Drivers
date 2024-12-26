/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : ultrasonic.c    *******************
*********************	Date  : 13 AUG, 2023	*******************
*******************************************************************/

#include "ultrasonic.h"

// Tick time = 1us
static timer0_t timer0_obj = {
    .TMR0_InterruptHandler = NULL,
    .edge = TIMER0_RISING_EDGE,
    .mode = TIMER0_TIMER_MODE,
    .preload_value = 0,
    .prescaler_enble = TIMER0_PRESCALER_ENABLE,
    .prescaler_value = TIMER0_PRESCALER_DIV_2,
    .register_size = TIMER0_16BIT_SIZE
};

Std_ReturnType Ultrasonic_Init(const ultrasonic_t *obj)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != obj)
    {
        ret = E_OK;
        ret &= gpio_pin_intialize(&(obj->Trigger_Pin));
        ret &= gpio_pin_intialize(&(obj->Echo_Pin));
        ret &= timer0_intialize(&timer0_obj);
    }
    
    return ret;
}

Std_ReturnType Ultrasonic_Calculate_Distance(const ultrasonic_t *obj, uint16 *distance)
{
    Std_ReturnType ret = E_NOT_OK;
    
    uint16 Timer0_Value = 0;
    uint8 EchoPinLogic = GPIO_LOW;
    
    if(NULL != obj)
    {
        ret = E_OK;
        /* Send Trigger Signal to the Ultrasonic Trigger Pin */
        ret &= gpio_pin_write_logic(&(obj->Trigger_Pin), GPIO_HIGH);
        __delay_us(10);
        ret &= gpio_pin_write_logic(&(obj->Trigger_Pin), GPIO_LOW);
        
        /* Wait the Echo pin to be High */
        while(GPIO_LOW == EchoPinLogic)
        {
            ret &= gpio_pin_read_logic(&(obj->Echo_Pin), &EchoPinLogic);
        }
        
        /* Clear Timer0 Ticks */
        ret &= timer0_write_value(&timer0_obj, 0);

        /* Wait the Echo pin to be Low */
        while(GPIO_HIGH == EchoPinLogic)
        {
            ret &= gpio_pin_read_logic(&(obj->Echo_Pin), &EchoPinLogic);
        }
        
        /* Read the time */
        ret &= timer0_read_value(&timer0_obj, &Timer0_Value);
        
        /* Calculate the distance */
        *distance = (uint16)((Timer0_Value - 192) / 57) + 3;
    }

    return ret;  
}
