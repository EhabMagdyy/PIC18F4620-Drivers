/* 
 * File:   hal_eeprom.c
 * Author: Ehab
 *
 * Created on 10 ?????, 2023, 04:07 ?
 */

#include "hal_eeprom.h"

Std_ReturnType EEPROM_WriteByte(uint16 address, uint8 data)
{
    Std_ReturnType ret = E_OK;
    /* Write Address */
    EEADRH = ((address >> 8) & 0x03);
    EEADR = (address & 0xFF);
    /* Write Data */
    EEDATA = data;

    /* Clear EPGD for accessing Data EEPROM memory */
    EEPROM_ACCESS_DATA_EEPROM_MEMORY();
    /* Clear CFGS for accessing Data EEPROM memory Or Flash memory */
    EEPROM_ACCESS_FLASH_OR_EEPROM_MEMORY();
    /* Enable write operation */
    EEPROM_WRITE_ENABLE();

    /* Read Interrupt status And Disable Interrupt */
    uint8 interrupt_state = 0;
    interrupt_state = INTCONbits.GIE;
    INTCONbits.GIE = INTERRUPT_DISABLE;
    
    /* Start writing operation */
    EEPROM_StartWriteOperation_1();
    EEPROM_StartWriteOperation_2();
    EEPROM_WRITE_INTIALIZE();
    while(EEPROM_WRITE_OPERATION_COMPLETED != EECON1bits.WR);

    /* Disable write operation */
    EEPROM_WRITE_DISABLE();
    
    /* Restore Interrupt Statue "Enabled / Disabled" */
    INTCONbits.GIE = interrupt_state;
    
    return ret;
}

Std_ReturnType EEPROM_ReadByte(uint16 address, uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != data){
        ret = E_OK;
        Std_ReturnType ret = E_OK;
        
        /* Write Address */
        EEADRH = ((address >> 8) & 0x03);
        EEADR = (address & 0xFF);

        /* Clear EPGD for accessing Data EEPROM memory */
        EEPROM_ACCESS_DATA_EEPROM_MEMORY();
        /* Clear CFGS for accessing Data EEPROM memory Or Flash memory */
        EEPROM_ACCESS_FLASH_OR_EEPROM_MEMORY();

        /* Start Reading operation */
        EEPROM_READ_INTIALIZE();
        /* (No Operation) This needed for High Frequency crystal oscillator (>8 MHZ) */
        NOP(); NOP();

        /* Read Data */
        *data = EEDATA;
    }
    return ret;
}
