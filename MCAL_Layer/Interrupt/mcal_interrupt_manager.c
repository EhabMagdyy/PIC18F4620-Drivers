/* 
 * File:   mcal_interrupt_manager.c
 * Author: Ehab
 *
 * Created on 07 ?????, 2023, 03:28 ?
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
void __interrupt() InterruptManegerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCURED == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCURED == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else { /* Nothing */ }
}

void __interrupt(low_priority) InterruptManegerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCURED == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else { /* Nothing */ }
}

#else
void __interrupt() InterruptManeger(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCURED == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCURED == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCURED == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else { /* Nothing */ }
    
    /* For Rising To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_HIGH == PORTBbits.RB4) && (1 == RB4_Flag))
    {
        RB4_Flag = 0;
        RB4_ISR(1);    /* High (Rising Edge) */
    }
    else { /* Nothing */ }
    /* For Falling To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_LOW == PORTBbits.RB4) && (0 == RB4_Flag))
    {
        RB4_Flag = 1;
        RB4_ISR(0);     /* Low (Falling Edge) */
    }
    else { /* Nothing */ }
    
    /* For Rising To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_HIGH == PORTBbits.RB5) && (1 == RB5_Flag))
    {
        RB5_Flag = 0;
        RB5_ISR(1);     /* High (Rising Edge) */
    }
    else { /* Nothing */ }
    /* For Falling To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_LOW == PORTBbits.RB5) && (0 == RB5_Flag))
    {
        RB5_Flag = 1;
        RB5_ISR(0);     /* Low (Falling Edge) */
    }
    else { /* Nothing */ }
    
    /* For Rising To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_HIGH == PORTBbits.RB6) && (1 == RB6_Flag))
    {
        RB6_Flag = 0;
        RB6_ISR(1);     /* High (Rising Edge) */
    }
    else { /* Nothing */ }
    /* For Falling To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_LOW == PORTBbits.RB6) && (0 == RB6_Flag))
    {
        RB6_Flag = 1;
        RB6_ISR(0);     /* Low (Falling Edge) */
    }
    else { /* Nothing */ }
    
    /* For Rising To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_HIGH == PORTBbits.RB7) && (1 == RB7_Flag))
    {
        RB7_Flag = 0;
        RB7_ISR(1);     /* High (Rising Edge) */
    }
    else { /* Nothing */ }
    /* For Falling To Solve the optimization of 'Flag' problem */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCURED == INTCONbits.RBIF) 
            && (GPIO_LOW == PORTBbits.RB7) && (0 == RB7_Flag))
    {
        RB7_Flag = 1;
        RB7_ISR(0);     /* Low (Falling Edge) */
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCURED == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCURED == INTCONbits.TMR0IF)){
        TMR0_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCURED == PIR1bits.TMR1IF)){
        TMR1_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCURED == PIR1bits.TMR2IF)){
        TMR2_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCURED == PIR2bits.TMR3IF)){
        TMR3_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCURED == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCURED == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCURED == PIR1bits.TXIF)){
        EUSART_TX_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCURED == PIR1bits.RCIF)){
        EUSART_RX_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCURED == PIR1bits.SSPIF)){
        MSSP_I2C_ISR();
    }
    else { /* Nothing */ }
    
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCURED == PIR2bits.BCLIF)){
        MSSP_I2C_Bus_Collision_ISR();
    }
    else { /* Nothing */ }
}
#endif
