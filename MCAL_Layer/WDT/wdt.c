/******************************************************************
*********************   Author: Ehab Magdy		*******************
*********************	File  : wdt.c           *******************
*********************	Date  : 13 AUG, 2023	*******************
*******************************************************************/

#include "wdt.h"

void WDT_Start_Count(void)
{
   WDTCONbits.SWDTEN = WDT_ENABLE;
}

void WDT_Disable(void)
{
    WDTCONbits.SWDTEN = WDT_DISABLE;
}
