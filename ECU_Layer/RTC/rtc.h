/* 
 * File:   rtc.h
 * Author: Ehab
 *
 * Created on 05 ??????, 2023, 05:51 ?
 */

#ifndef RTC_H
#define	RTC_H

/* --------------------------- Includes ---------------------------- */
#include "../../MCAL_Layer/I2C/hal_i2c.h"
#include "../../MCAL_Layer/mcal_std_types.h"

/* ---------------------- Macro Declarations ----------------------- */
#define RTC_ADD              0xD0

#define RTC_SECONDES_ADD     0x00
#define RTC_MINUTES_ADD      0x01
#define RTC_HOURS_ADD        0x02
#define RTC_DAY_ADD          0x04
#define RTC_MONTH_ADD        0x05
#define RTC_YEAR_ADD         0x06

/* -------------------- Data Type Declarations --------------------- */
typedef struct{
    uint8 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
    uint8 second;
} RTC_t;

/*---------------------- Function Declarations --------------------- */
Std_ReturnType RTC_Get_Date_Time(RTC_t* rtc_obj);

#endif	/* RTC_H */

