/* 
 * File:   hal_eeprom.h
 * Author: Ehab
 *
 * Created on 10 ?????, 2023, 04:07 ?
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* Section: Includes */
//#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* Section: Macro Declarations */
#define EEPROM_WRITE_OPERATION_COMPLETED   0

/* Section: Macro Function Declarations */
#define EEPROM_ACCESS_FLASH_OR_EEPROM_MEMORY()  (EECON1bits.CFGS = 0)
#define EEPROM_ACCESS_DATA_EEPROM_MEMORY()      (EECON1bits.EEPGD = 0)
#define EEPROM_WRITE_ENABLE()                   (EECON1bits.WREN = 1)
#define EEPROM_WRITE_DISABLE()                  (EECON1bits.WREN = 0)
#define EEPROM_WRITE_INTIALIZE()                (EECON1bits.WR = 1)
#define EEPROM_READ_INTIALIZE()                 (EECON1bits.RD = 1)
#define EEPROM_StartWriteOperation_1()          (EECON2 = 0x55)
#define EEPROM_StartWriteOperation_2()          (EECON2 = 0x0AA)

/* Data Types Declarations */

/* Function Declarations */
Std_ReturnType EEPROM_WriteByte(uint16 address, uint8 data);
Std_ReturnType EEPROM_ReadByte(uint16 address, uint8 *data);

#endif	/* HAL_EEPROM_H */

