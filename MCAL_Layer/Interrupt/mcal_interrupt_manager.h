/* 
 * File:   mcal_interrupt_manager.h
 * Author: Ehab
 *
 * Created on 07 ?????, 2023, 03:28 ?
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section: Includes */
#include "mcal_interrupt_config.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Data Types Declarations */

/* Function Declarations */
void __interrupt() InterruptManegerHigh(void);
void __interrupt(low_priority) InterruptManegerLow(void);
void __interrupt() InterruptManeger(void);

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 state);
void RB5_ISR(uint8 state);
void RB6_ISR(uint8 state);
void RB7_ISR(uint8 state);

void ADC_ISR(void);

void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);

void MSSP_I2C_ISR(void);
void MSSP_I2C_Bus_Collision_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

