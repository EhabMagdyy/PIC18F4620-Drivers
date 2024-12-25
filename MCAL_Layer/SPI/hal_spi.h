/* 
 * File:   hal_spi.h
 * Author: Ehab
 *
 * Created on 02 august, 2023
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* --------------------------- Includes ---------------------------- */
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/* ---------------------- Macro Declarations ----------------------- */
/* Enable/Disable MSSP SPI Module */
#define MSSP_SPI_MODULE_ENABLE                1
#define MSSP_SPI_MODULE_DISABLE               0
/* Master Mode: input data sampled at Middle/End of data output time */
#define MSSP_SPI_SAMPLE_AT_END                1
#define MSSP_SPI_SAMPLE_AT_MID                0
/* Transmit occurs on transition from Idle to active/ active to idle */
#define MSSP_SPI_SAMPLE_ON_ACTIVE_TO_IDLE     1
#define MSSP_SPI_SAMPLE_ON_IDLE_TO_ACTIVE     0
/* Buffer Full/Empty  */
#define MSSP_SPI_DATA_BUFFER_IS_FULL          1
#define MSSP_SPI_DATA_BUFFER_IS_EMPTY         0
/* Clock polarity IDLE High/Low */
#define MSSP_SPI_IDLE_STATE_HIGH              1
#define MSSP_SPI_IDLE_STATE_LOW               0
/* Mode and Clock select */
#define MSSP_SPI_MASTER_MODE_CLK_FOSC_DIV_4   0x00
#define MSSP_SPI_MASTER_MODE_CLK_FOSC_DIV_16  0x01
#define MSSP_SPI_MASTER_MODE_CLK_FOSC_DIV_64  0x02
#define MSSP_SPI_MASTER_MODE_CLK_TMR_DIV_2    0x03
#define MSSP_SPI_SLAVE_MODE_SS_ENABLE         0x04
#define MSSP_SPI_SLAVE_MODE_SS_DISABLE        0x05

/*-------------------- Macro Function Declarations --------------------*/
/* Enable/Disable MSSP SPI Module */
#define MSSP_SPI_ENABLE()         (SSPCON1bits.SSPEN = MSSP_SPI_MODULE_ENABLE)
#define MSSP_SPI_DISABLE()        (SSPCON1bits.SSPEN = MSSP_SPI_MODULE_DISABLE)
#define MSSP_SPI_READ_DATA_BUFFER()             (SSPSTATbits.BF)
/* Master Mode: input data sampled at Middle/End of data output time */
#define MSSP_SPI_SELECT_SAMPLE(SPI_SAMPLE)      (SSPSTATbits.SMP = SPI_SAMPLE)
/* Transmit occurs on transition from Idle to active/ active to idle */
#define MSSP_SPI_SAMPLE_EDGE(SPI_SEDGE)         (SSPSTATbits.CKE = SPI_SEDGE)
/* Clock polarity IDLE High/Low */
#define MSSP_SPI_IDLE_STATE(SPI_IDLE)           (SSPCON1bits.CKP = SPI_IDLE)
/* Mode and Clock select */
#define MSSP_SPI_MODE_SELECT(SPI_MODE)          (SSPCON1bits.SSPM = SPI_MODE)

/*---------------------- Data Types Declarations --------------------- */
typedef struct{
    uint8 mode              : 3;
    uint8 idle_state        : 1;
    uint8 sample_pos        : 1;
    uint8 sampling_edge     : 1;
    uint8 reserved          : 2;
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*SPI_DefaultInterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE 
    interrupt_priority_t mssp_spi_priority;
#endif  
#endif 
} mssp_spi_t;

/*----------------------- Function Declarations ---------------------- */
Std_ReturnType MSSP_SPI_Intiailize(const mssp_spi_t* spi_obj);
Std_ReturnType MSSP_SPI_DeIntiailize(const mssp_spi_t* spi_obj);
Std_ReturnType MSSP_SPI_Trancieve(const mssp_spi_t* spi_obj, uint8 send_data, uint8* rec_data);

#endif	/* HAL_SPI_H */

