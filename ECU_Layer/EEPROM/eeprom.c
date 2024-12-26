/* 
 * File:   eeprom.c
 * Author: Ehab
 *
 * Created on 04 ??????, 2023, 11:54 ?
 */

#include "eeprom.h"

/**
 * @breif Start- EEPROM_ADD<7> + 0(W)- Location at EEPROM "to write to"- Data- Stop
 * @param address
 * @param data
 * @return 
 */
Std_ReturnType EEPROM_EXT_Write_Byte(uint16 address, uint8 data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 ack = 0;
    ret = MSSP_I2C_Master_Send_Start();
    ret = MSSP_I2C_Master_Write_Blocking(((EEPROM_EXT_ADDRESS | (EEPROM_EXT_A2 << 2)
                                                   | (address >> 8)) << 1), &ack);
    ret = MSSP_I2C_Master_Write_Blocking((uint8)address, &ack);
    ret = MSSP_I2C_Master_Write_Blocking(data, &ack);
    ret = MSSP_I2C_Master_Send_Stop();
    
    __delay_ms(10);
    return ret;
}

/**
 * @breif Start - EEPROM_ADD<7> + 0(W)- Location at EEPROM "to read read from"
 *                  - Repeated start - EEPROM_ADD<7> + 1(R) - Data - Stop
 * @param address
 * @param data
 * @return 
 */
Std_ReturnType EEPROM_EXT_Read_Byte(uint16 address, uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    uint8 ack = 0;

    ret = MSSP_I2C_Master_Send_Start();
    ret = MSSP_I2C_Master_Write_Blocking(((EEPROM_EXT_ADDRESS | (EEPROM_EXT_A2 << 2)
                                                   | (address >> 8)) << 1), &ack);
    ret = MSSP_I2C_Master_Write_Blocking((uint8)address, &ack);
    
    ret = MSSP_I2C_Master_Send_Repeated_Satrt();
    ret = MSSP_I2C_Master_Write_Blocking(((EEPROM_EXT_ADDRESS | (EEPROM_EXT_A2 << 2)
                                                   | (address >> 8)) << 1) | 0x01, &ack);
    ret = MSSP_I2C_Master_Read_Blocking(I2C_MASTER_SEND_NACK, data);
    ret = MSSP_I2C_Master_Send_Stop();
    
    return ret;
}