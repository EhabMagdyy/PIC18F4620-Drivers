/* 
 * File:   ecu_seven_segment.h
 * Author: Ehab
 *
 * Created on 19 ?????, 2023, 12:41 ?
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Section: Includes */
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */
typedef enum{
    SEGMENT_PIN_0 = 0,
    SEGMENT_PIN_1,
    SEGMENT_PIN_2,
    SEGMENT_PIN_3
}segment_pin_index_t;

typedef struct{
    pin_config_t segment_pins[4];
}segment_t;

/* Function Declarations */
Std_ReturnType seven_segment_intialize(const segment_t* segment);
Std_ReturnType seven_segment_write_number(const segment_t* segment, uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

