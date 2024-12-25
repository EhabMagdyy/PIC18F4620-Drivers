/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : wdt.h           *******************
*********************	Date  : 13 AUG, 2023	*******************
*******************************************************************/

#ifndef WDT_H
#define	WDT_H

/**************************** Includes ****************************/
#include "../../MCAL_Layer/mcal_std_types.h"

/************************ Macro Declarations **********************/
/* Software Controlled Watchdog Timer Enable 'SWDTEN' */
#define WDT_DISABLE          0
#define WDT_ENABLE           1

/* Watchdog Timer Postscaler Select bits */
// MS -> millisecond
/* 
 * WDT_POSTSCALER_4_MS         1
 * WDT_POSTSCALER_8_MS         2
 * WDT_POSTSCALER_16_MS        4
 * WDT_POSTSCALER_32_MS        8
 * WDT_POSTSCALER_64_MS        16
 * WDT_POSTSCALER_128_MS       32
 * WDT_POSTSCALER_256_MS       64
 * WDT_POSTSCALER_512_MS       128
 * WDT_POSTSCALER_1024_MS      256
 * WDT_POSTSCALER_2048_MS      512
 * WDT_POSTSCALER_4096_MS      1024
 * WDT_POSTSCALER_8192_MS      2048
 * WDT_POSTSCALER_16384_MS     4096
 * WDT_POSTSCALER_32768_MS     8192
 * WDT_POSTSCALER_65536_MS     16384
 * WDT_POSTSCALER_131072_MS    32768
*/

/********************** Function Declarations *********************/
void WDT_Start_Count(void);
void WDT_Disable(void);

#endif	/* WDT_H */

