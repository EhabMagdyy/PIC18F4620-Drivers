/* 
 * File:   mcal_internal_interrupt.h
 * Author: Ehab
 *
 * Created on 07 ?????, 2023, 03:24 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section: Includes */
#include "mcal_interrupt_config.h"

/* ----------------Section: Macro Function Declarations----------------- */
/**
 ***********      ADC Interrupt       ************
 */
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_ENABLE()             (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()            (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_CLEAR_FLAG()         (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_SET_HIGH_PRIORITY()        (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_SET_LOW_PRIORITY()         (IPR1bits.ADIP = 0)

#endif
#endif

/**
 ***********      TIMER0 Interrupt        *************
 */
#if TIMER0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_ENABLE()             (INTCONbits.TMR0IE = 1)
#define TIMER0_INTERRUPT_DISABLE()            (INTCONbits.TMR0IE = 0)
#define TIMER0_INTERRUPT_CLEAR_FLAG()         (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_SET_HIGH_PRIORITY()         (INTCON2bits.TMR0IP = 1)
#define TIMER0_INTERRUPT_SET_LOW_PRIORITY()         (INTCON2bits.TMR0IP = 0)

#endif
#endif

/**
 ***********      TIMER1 Interrupt        *************
 */
#if TIMER1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER1_INTERRUPT_ENABLE()             (PIE1bits.TMR1IE = 1)
#define TIMER1_INTERRUPT_DISABLE()            (PIE1bits.TMR1IE = 0)
#define TIMER1_INTERRUPT_CLEAR_FLAG()         (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define TIMER1_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.TMR1IP = 1)
#define TIMER1_INTERRUPT_SET_LOW_PRIORITY()         (IPR1bits.TMR1IP = 0)

#endif
#endif

/**
 ***********      TIMER2 Interrupt        *************
 */
#if TIMER2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER2_INTERRUPT_ENABLE()             (PIE1bits.TMR2IE = 1)
#define TIMER2_INTERRUPT_DISABLE()            (PIE1bits.TMR2IE = 0)
#define TIMER2_INTERRUPT_CLEAR_FLAG()         (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define TIMER2_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.TMR2IP = 1)
#define TIMER2_INTERRUPT_SET_LOW_PRIORITY()         (IPR1bits.TMR2IP = 0)

#endif
#endif

/**
 ***********      TIMER3 Interrupt        *************
 */
#if TIMER3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define TIMER3_INTERRUPT_ENABLE()             (PIE2bits.TMR3IE = 1)
#define TIMER3_INTERRUPT_DISABLE()            (PIE2bits.TMR3IE = 0)
#define TIMER3_INTERRUPT_CLEAR_FLAG()         (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define TIMER3_INTERRUPT_SET_HIGH_PRIORITY()         (IPR2bits.TMR3IP = 1)
#define TIMER3_INTERRUPT_SET_LOW_PRIORITY()          (IPR2bits.TMR3IP = 0)

#endif
#endif

/**
 ***********      CCP1 Interrupt        *************
 */
#if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_ENABLE()             (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()            (PIE1bits.CCP1IE = 0)
#define CCP1_INTERRUPT_CLEAR_FLAG()         (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_SET_LOW_PRIORITY()          (IPR1bits.CCP1IP = 0)

#endif
#endif

/**
 ***********      CCP2 Interrupt        *************
 */
#if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define CCP2_INTERRUPT_ENABLE()             (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE()            (PIE2bits.CCP2IE = 0)
#define CCP2_INTERRUPT_CLEAR_FLAG()         (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define CCP2_INTERRUPT_SET_HIGH_PRIORITY()         (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_SET_LOW_PRIORITY()          (IPR2bits.CCP2IP = 0)

#endif
#endif

/**
 ***********      EUSART TX Interrupt        *************
 */
#if EUSART_TX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_ENABLE()             (PIE1bits.TXIE = 1)
#define EUSART_TX_INTERRUPT_DISABLE()            (PIE1bits.TXIE = 0)
/* TXIF Cleared when you write new data */

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define EUSART_TX_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.TXIP = 1)
#define EUSART_TX_INTERRUPT_SET_LOW_PRIORITY()          (IPR1bits.TXIP = 0)

#endif
#endif

/**
 ***********      EUSART RX Interrupt        *************
 */
#if EUSART_RX_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define EUSART_RX_INTERRUPT_ENABLE()             (PIE1bits.RCIE = 1)
#define EUSART_RX_INTERRUPT_DISABLE()            (PIE1bits.RCIE = 0)
/* RCIF Cleared when reading the register data */

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define EUSART_RX_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.RCIP = 1)
#define EUSART_RX_INTERRUPT_SET_LOW_PRIORITY()          (IPR1bits.RCIP = 0)

#endif
#endif

/**
 ***********      MSSP I2C Interrupt        *************
 */
#if MSSP_I2C_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_ENABLE()             (PIE1bits.SSPIE = 1)
#define MSSP_I2C_INTERRUPT_DISABLE()            (PIE1bits.SSPIE = 0)
#define MSSP_I2C_FLAG_CLEAR()                   (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.SSPIP = 1)
#define MSSP_I2C_INTERRUPT_SET_LOW_PRIORITY()          (IPR1bits.SSPIP = 0)

#endif
#endif

/**
 ***********      MSSP I2C Bus Collision Interrupt        *************
 */
#if MSSP_I2C_BUS_COL_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_BUS_COL_INTERRUPT_ENABLE()     (PIE2bits.BCLIE = 1)
#define MSSP_I2C_BUS_COL_INTERRUPT_DISABLE()    (PIE2bits.BCLIE = 0)
#define MSSP_I2C_BUS_COL_FLAG_CLEAR()           (PIR2bits.BCLIF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_BUS_COL_INTERRUPT_SET_HIGH_PRIORITY()  (IPR2bits.BCLIP = 1)
#define MSSP_I2C_BUS_COL_INTERRUPT_SET_LOW_PRIORITY()   (IPR2bits.BCLIP = 0)

#endif
#endif

/**
 ***********      MSSP SPI Interrupt        *************
 */
#if MSSP_SPI_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE

#define MSSP_SPI_INTERRUPT_ENABLE()             (PIE1bits.SSPIE = 1)
#define MSSP_SPI_INTERRUPT_DISABLE()            (PIE1bits.SSPIE = 0)
#define MSSP_SPI_FLAG_CLEAR()                   (PIR1bits.SSPIF = 0)

#if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE

#define MSSP_SPI_INTERRUPT_SET_HIGH_PRIORITY()         (IPR1bits.SSPIP = 1)
#define MSSP_SPI_INTERRUPT_SET_LOW_PRIORITY()          (IPR1bits.SSPIP = 0)

#endif
#endif


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

