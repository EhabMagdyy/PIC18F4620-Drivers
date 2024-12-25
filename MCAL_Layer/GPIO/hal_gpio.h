/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : stepper_motor.c *******************
*********************	Date  : 28 Aug, 2023	*******************
*******************************************************************/
#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/**************************** Includes ****************************/
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/************************ Macro Declarations **********************/
#define GPIO_LOW        0
#define GPIO_HIGH       1

#define GPIO_OUTPUT     0
#define GPIO_INPUT      1

#define GPIO_PIN0       0
#define GPIO_PIN1       1
#define GPIO_PIN2       2
#define GPIO_PIN3       3
#define GPIO_PIN4       4
#define GPIO_PIN5       5
#define GPIO_PIN6       6
#define GPIO_PIN7       7


#define PORTA_INDEX     0
#define PORTB_INDEX     1
#define PORTC_INDEX     2
#define PORTD_INDEX     3
#define PORTE_INDEX     4

#define BIT_MASK    (uint8)  1
#define PORT_PIN_MAX_NUMBER  8
#define PORT_MAX_NUMBER      5

#define PORT_MASK 0xFF

/********************  Macro Function Declarations ****************/
#define     HWREG8(_x)       (*((volatile uint8_t*)(_x)))

#define     SET_BIT(REG_ADDRESS, BIT_POS)       (REG_ADDRESS |=  (BIT_MASK << BIT_POS))   
#define     CLEAR_BIT(REG_ADDRESS, BIT_POS)     (REG_ADDRESS &= ~(BIT_MASK << BIT_POS))   
#define     TOGGLE_BIT(REG_ADDRESS, BIT_POS)    (REG_ADDRESS ^=  (BIT_MASK << BIT_POS))
#define     READ_BIT(REG_ADDRESS, BIT_POS)      ((REG_ADDRESS >> BIT_POS) & BIT_MASK)

/********************* Data Types Declarations ********************/
typedef struct{
    uint8 port      :3;
    uint8 pin       :3;
    uint8 direction :1;
    uint8 logic     :1;
}pin_config_t;

/********************** Function Declarations *********************/
Std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t *_pin_config, uint8 *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, uint8 logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, uint8 *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_intialize(uint8 port, uint8 direction);
Std_ReturnType gpio_port_get_direction_status(uint8 port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(uint8 port, uint8 logic);
Std_ReturnType gpio_port_read_logic(uint8 port, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(uint8 port);

#endif	/* HAL_GPIO_H */

