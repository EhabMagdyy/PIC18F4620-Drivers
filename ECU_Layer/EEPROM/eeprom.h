/* 
 * File:   eeprom.h
 * Author: Ehab
 * 
 * Created on 04 ??????, 2023, 11:54 ?
 */

// 8K EEPROM

#ifndef EEPROM_H
#define	EEPROM_H

/* --------------------------- Includes ---------------------------- */
#include "../../MCAL_Layer/I2C/hal_i2c.h"
#include "../../MCAL_Layer/mcal_std_types.h"

/* ---------------------- Macro Declarations ----------------------- */
#define EEPROM_EXT_A2           0
#define EEPROM_EXT_ADDRESS      0x50

/*----------------------- Function Declarations ---------------------- */
Std_ReturnType EEPROM_EXT_Write_Byte(uint16 address, uint8 data);
Std_ReturnType EEPROM_EXT_Read_Byte(uint16 address, uint8 *data);

#endif	/* EEPROM_H */

