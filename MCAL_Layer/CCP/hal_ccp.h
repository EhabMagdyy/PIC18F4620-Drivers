/* 
 * File:   hal_ccp.h
 * Author: Ehab
 *
 * Created on 18 ?????, 2023, 10:11 ?
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/* ------------- Includes ------------- */
#include "../Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "hal_ccp_cfg.h"

/*------------------ Macro Declarations --------------------*/
/* CCP1 Modes */
#define CCP_MODULE_DISABLE                              0x00

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE || CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
#define CCP_CAPTURE_MODE_FALLING_EDGE                   0x04
#define CCP_CAPTURE_MODE_RISING_EDGE                    0x05
#define CCP_CAPTURE_MODE_4TH_RISING_EDGE                0x06
#define CCP_CAPTURE_MODE_16TH_RISING_EDGE               0x07
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE || CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
#define CCP_COMPARE_MODE_TOGGLE_OUTPUT                  0x02
#define CCP_COMPARE_MODE_CLEAR_CCP_PIN                  0x08
#define CCP_COMPARE_MODE_SET_CCP_PIN                    0x09
#define CCP_COMPARE_MODE_GENERATE_SOFTWARE_INTERRUPT    0x0A
#define CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT          0x0B
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE || CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
#define CCP_PWM_MODE                                    0x0F
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE || CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
/* Cheacking if Capture is ready */
#define CAPTURE_READY           0X01
#define CAPTURE_NOT_READY       0X00
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE || CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
/* Cheacking if Compare is ready */
#define COMPARE_READY           0X01
#define COMPARE_NOT_READY       0X00
#endif

/* -------------------- Macro Function Declarations -------------------- */
#define CCP1_SELECT_MODE(_MODE)             do{ CCP1CONbits.CCP1M = _MODE;\
                                                CCP1_INTERRUPT_CLEAR_FLAG();\
                                            }while(0);
#define CCP2_SELECT_MODE(_MODE)             do{ CCP2CONbits.CCP2M = _MODE;\
                                                CCP2_INTERRUPT_CLEAR_FLAG();\
                                            }while(0);

/* --------------------- Data Types Declarations ---------------------- */
#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)\
    || (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)\
    || (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)\
    || (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE))
typedef union{
    struct{
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16bit;
    };
} ccp_reg_t;
#endif

#if ((CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)\
    || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE))
/* Prescaler values */
typedef enum{
    CCP_TIMER2_PRESCALER_DIV_1 = 1,
    CCP_TIMER2_PRESCALER_DIV_4 = 4,
    CCP_TIMER2_PRESCALER_DIV_16 = 16
} ccp_prescaler_value_t;

/* Postscaler values */
typedef enum{
    CCP_TIMER2_POSTSCALER_DIV_1 = 1,
    CCP_TIMER2_POSTSCALER_DIV_2,
    CCP_TIMER2_POSTSCALER_DIV_3,
    CCP_TIMER2_POSTSCALER_DIV_4,
    CCP_TIMER2_POSTSCALER_DIV_5,
    CCP_TIMER2_POSTSCALER_DIV_6,
    CCP_TIMER2_POSTSCALER_DIV_7,
    CCP_TIMER2_POSTSCALER_DIV_8,
    CCP_TIMER2_POSTSCALER_DIV_9,
    CCP_TIMER2_POSTSCALER_DIV_10,
    CCP_TIMER2_POSTSCALER_DIV_11,
    CCP_TIMER2_POSTSCALER_DIV_12,
    CCP_TIMER2_POSTSCALER_DIV_13,
    CCP_TIMER2_POSTSCALER_DIV_14,
    CCP_TIMER2_POSTSCALER_DIV_15,
    CCP_TIMER2_POSTSCALER_DIV_16
} ccp_postscaler_value_t;
#endif

typedef enum{
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3
} ccp_cature_compare_timer_t;

typedef struct{
    #if CCP1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*CCP1_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t priority;
    #endif
    #endif
    uint8 mode;
    #if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
    uint32 pwm_frequency;
    ccp_postscaler_value_t timer2_postscaler_value;
    ccp_prescaler_value_t timer2_prescaler_value;
    #else
    ccp_cature_compare_timer_t ccp_timer;
    #endif
} ccp1_t;

typedef struct{
    #if CCP2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*CCP2_InterruptHandler)(void);
    #if INTERRUPT_PRIORITY_LEVELS == INTERRUPT_FEATURE_ENABLE
    interrupt_priority_t priority;
    #endif
    #endif
    uint8 mode;
    #if (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
    uint32 pwm_frequency;
    ccp_postscaler_value_t timer2_postscaler_value;
    ccp_prescaler_value_t timer2_prescaler_value;
    #else
    ccp_cature_compare_timer_t ccp_timer;
    #endif
} ccp2_t;

/* --------------------- Function Declarations ----------------------- */
/* CCP1 interfaces */
Std_ReturnType CCP1_intialize(const ccp1_t *ccp);
Std_ReturnType CCP1_DeIntialize(const ccp1_t *ccp);

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
Std_ReturnType CCP1_IsCapturedDataReady(uint8 *capture_status);
Std_ReturnType CCP1_CaptureModeReadValue(uint16 *captured_value);
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
Std_ReturnType CCP1_IsCompareComplete(uint8 *compare_status);
Std_ReturnType CCP1_CompareModeSetValue(uint16 captured_value);
#endif

#if (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
Std_ReturnType CCP1_PWM_Set_Duty(uint8 duty);
Std_ReturnType CCP1_PWM_Start();
Std_ReturnType CCP1_PWM_Stop();
#endif

/* CCP2 interfaces */
Std_ReturnType CCP2_intialize(const ccp2_t *ccp);
Std_ReturnType CCP2_DeIntialize(const ccp2_t *ccp);

#if (CCP2_CFG_SELECTED_MODE == CCP_CFG_CAPTURE_MODE)
Std_ReturnType CCP2_IsCapturedDataReady(uint16 *capture_status);
Std_ReturnType CCP2_CaptureModeReadValue(uint16 *captured_value);
#endif

#if (CCP2_CFG_SELECTED_MODE == CCP_CFG_COMPARE_MODE)
Std_ReturnType CCP2_IsCompareComplete(uint8 *compare_status);
Std_ReturnType CCP2_CompareModeSetValue(uint16 captured_value);
#endif

#if (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWM_MODE)
Std_ReturnType CCP2_PWM_Set_Duty(uint8 duty);
Std_ReturnType CCP2_PWM_Start();
Std_ReturnType CCP2_PWM_Stop();
#endif

#endif	/* HAL_CCP_H */
