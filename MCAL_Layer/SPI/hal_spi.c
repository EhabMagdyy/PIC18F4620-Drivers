/* 
 * File:   hal_spi.c
 * Author: Ehab
 *
 * Created on 02 august, 2023
 */

#include "hal_spi.h"

Std_ReturnType MSSP_SPI_Intiailize(const mssp_spi_t* spi_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != spi_obj)
    {
        ret = E_OK;
        
        /* Disable SPI Module */
        MSSP_SPI_DISABLE();
        
        /* Pin Initialize */
        TRISCbits.RC5 = 0;
//        TRISAbits.RA5 = 1;
        // Master mode
        if(0 <= spi_obj->mode && 3 >= spi_obj->mode)
        {
            TRISCbits.RC3 = 0;
            /* Select Sample Middle/End */
            MSSP_SPI_SELECT_SAMPLE(spi_obj->sample_pos);
        }
        // Slave mode
        else if(4 <= spi_obj->mode && 5 >= spi_obj->mode)
        {
            TRISCbits.RC3 = 1;
            /* Sample bit(SMP) must be cleared at Slave mode */
            MSSP_SPI_SELECT_SAMPLE(0);
        }
        else {/* Incorrect mode */}
        
        /* Select mode */
        MSSP_SPI_MODE_SELECT(spi_obj->mode);
        
        /* Select Clock polarity */
        MSSP_SPI_IDLE_STATE(spi_obj->idle_state);
        
        /* Select Sample Edge */
        MSSP_SPI_SAMPLE_EDGE(spi_obj->sampling_edge);
        
        /* Clear the Write Collision Detect */
        SSPCON1bits.WCOL = 0;
        
        /* Clear the Receive Overflow Indicator */
        SSPCON1bits.SSPOV = 0; 
        
        /* Enable SPI Module */
        MSSP_SPI_ENABLE();
    }
    else{/* Nothing */}
    
    return ret;
}

Std_ReturnType MSSP_SPI_DeIntiailize(const mssp_spi_t* spi_obj)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != spi_obj)
    {
        ret = E_OK;
        /* Disable SPI Module */
        MSSP_SPI_DISABLE();
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_INTERRUPT_DISABLE();
#endif
    }
    else{/* Nothing */}
    
    return ret;
}

Std_ReturnType MSSP_SPI_Trancieve(const mssp_spi_t* spi_obj, uint8 send_data, uint8* rec_data)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL != spi_obj)
    {
        ret = E_OK;
        /* load data to SSPBUF */
        SSPBUF = send_data;
        /* Wait until data transfer */
        while(!PIR1bits.SSPIF);
        /* Clear flag */
        MSSP_SPI_FLAG_CLEAR();
        /* Read received data */
        *rec_data = SSPBUF;
    }
    else{/* Nothing */}
    
    return ret;
}
