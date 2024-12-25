/* 
 * File:   mcal_external_interrupt.c
 * Author: Ehab
 *
 * Created on 07 ?????, 2023, 03:25 ?
 */

#include "mcal_external_interrupt.h"

/* Pointers to ISR Functions */
static InterrptHandler_FunctionPointer_t INT0_InterrptHandler = NULL;
static InterrptHandler_FunctionPointer_t INT1_InterrptHandler = NULL;
static InterrptHandler_FunctionPointer_t INT2_InterrptHandler = NULL;

static InterrptHandler_FunctionPointer_t RB4_InterruptHandlerHigh = NULL;
static InterrptHandler_FunctionPointer_t RB4_InterruptHandlerLow = NULL;
static InterrptHandler_FunctionPointer_t RB5_InterruptHandlerHigh = NULL;
static InterrptHandler_FunctionPointer_t RB5_InterruptHandlerLow = NULL;
static InterrptHandler_FunctionPointer_t RB6_InterruptHandlerHigh = NULL;
static InterrptHandler_FunctionPointer_t RB6_InterruptHandlerLow = NULL;
static InterrptHandler_FunctionPointer_t RB7_InterruptHandlerHigh = NULL;
static InterrptHandler_FunctionPointer_t RB7_InterruptHandlerLow = NULL;
/* End of Pointers to ISR Functions */
 
static Std_ReturnType interrupt_INTx_enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_pin_initialize(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_edge_initialize(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_priority_initialize(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_clear_flag(const interrupt_INTx_t *int_obj);
static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
static Std_ReturnType INT0_SetInterruptHandler(void (*InterrptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*InterrptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*InterrptHandler)(void));
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_pin_initialize(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_priority_initialize(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t *int_obj);
static Std_ReturnType interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);
void RB4_ISR(uint8);
void RB5_ISR(uint8);
void RB6_ISR(uint8);
void RB7_ISR(uint8);


#if     INTERRUPT_FEATURE_ENABLE == EXT_INTERRUPT_INTx_FEATURE_ENABLE
/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType interrupt_INTx_intialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        ret = interrupt_INTx_disable(int_obj);
        ret = interrupt_INTx_clear_flag(int_obj);
        
        ret = interrupt_INTx_SetInterruptHandler(int_obj);
        ret = interrupt_INTx_pin_initialize(int_obj);
        ret = interrupt_INTx_edge_initialize(int_obj);
        
        #if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
        ret = interrupt_INTx_priority_initialize(int_obj);
        #endif

        ret = interrupt_INTx_enable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType interrupt_INTx_DeIntialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        ret = interrupt_INTx_disable(int_obj);
    }
    return ret;
}
#endif

#if     INTERRUPT_FEATURE_ENABLE == EXT_INTERRUPT_RBx_FEATURE_ENABLE
/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType interrupt_RBx_intialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        ret = interrupt_RBx_disable(int_obj);
        ret = interrupt_RBx_clear_flag(int_obj);
        
        ret = interrupt_RBx_SetInterruptHandler(int_obj);
        ret = interrupt_RBx_pin_initialize(int_obj);
        #if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
        ret = interrupt_RBx_priority_initialize(int_obj);
        #endif
        ret = interrupt_RBx_enable(int_obj);
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType interrupt_RBx_DeIntialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        ret = interrupt_RBx_disable(int_obj);
    }
    return ret;
}
#endif

/********    Helper Functions for INTx     ********/
//
static Std_ReturnType interrupt_INTx_enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        switch(int_obj->source){
            case INTERRUPT_INT0: 
#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
                INTERRUPT_PEIORITY_LEVELS_ENABLe();
                INTERRUPT_GlobalInterruptHighPriority_Enable();
#else
                INTERRUPT_PEIORITY_LEVELS_DISABLE();
                INTERRUPT_GlobalInterrupt_Enable();
                INTERRUPT_PeripheraInterrupt_Enable();
#endif
                EXT_INTERRUPT_INT0_ENABLE(); 
                break;
            case INTERRUPT_INT1: 
#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
                INTERRUPT_PEIORITY_LEVELS_ENABLe();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowPriority_Enable();
                }
                else {
                    INTERRUPT_GlobalInterruptHighPriority_Enable();
                }
#else
                INTERRUPT_PEIORITY_LEVELS_DISABLE();
                INTERRUPT_GlobalInterrupt_Enable();
                INTERRUPT_PeripheraInterrupt_Enable();
#endif
                EXT_INTERRUPT_INT1_ENABLE();
                break;
            case INTERRUPT_INT2: 
#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
                INTERRUPT_PEIORITY_LEVELS_ENABLe();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    INTERRUPT_GlobalInterruptLowPriority_Enable();
                }
                else {
                    INTERRUPT_GlobalInterruptHighPriority_Enable();
                }
#else
                INTERRUPT_PEIORITY_LEVELS_DISABLE();
                INTERRUPT_GlobalInterrupt_Enable();
                INTERRUPT_PeripheraInterrupt_Enable();
#endif
                EXT_INTERRUPT_INT2_ENABLE();
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        switch(int_obj->source){
            case INTERRUPT_INT0: 
                EXT_INTERRUPT_INT0_DISABLE(); 
                break;
            case INTERRUPT_INT1: 
                EXT_INTERRUPT_INT1_DISABLE();
                break;
            case INTERRUPT_INT2: 
                EXT_INTERRUPT_INT2_DISABLE();
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_pin_initialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_edge_initialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        switch(int_obj->source){
            case INTERRUPT_INT0: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INTERRUPT_INT0_FallingEdge();}
                else {EXT_INTERRUPT_INT0_RisingEdge();}
                break;
            case INTERRUPT_INT1: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INTERRUPT_INT1_FallingEdge();}
                else {EXT_INTERRUPT_INT1_RisingEdge();}
                break;
            case INTERRUPT_INT2: 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){EXT_INTERRUPT_INT2_FallingEdge();}
                else {EXT_INTERRUPT_INT2_RisingEdge();}
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

#if   INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
static Std_ReturnType interrupt_INTx_priority_initialize(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        switch(int_obj->source){
            case INTERRUPT_INT0: 
                /* Fixed Priority */
                break;
            case INTERRUPT_INT1: 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INTERRUPT_INT1_LowPriority();}
                else {EXT_INTERRUPT_INT1_HighPriority();}
                break;
            case INTERRUPT_INT2: 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){EXT_INTERRUPT_INT2_LowPriority();}
                else {EXT_INTERRUPT_INT2_HighPriority();}
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif

static Std_ReturnType interrupt_INTx_clear_flag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        switch(int_obj->source){
            case INTERRUPT_INT0: 
                EXT_INTERRUPT_INT0_FlagClear();
                break;
            case INTERRUPT_INT1: 
                EXT_INTERRUPT_INT1_FlagClear();
                break;
            case INTERRUPT_INT2: 
                EXT_INTERRUPT_INT2_FlagClear();
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

static Std_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        switch(int_obj->source){
            case INTERRUPT_INT0: 
                ret = INT0_SetInterruptHandler(int_obj->EXT_INTERRUPT_HANDLER);
                break;
            case INTERRUPT_INT1: 
                ret = INT1_SetInterruptHandler(int_obj->EXT_INTERRUPT_HANDLER);
                break;
            case INTERRUPT_INT2: 
                ret = INT2_SetInterruptHandler(int_obj->EXT_INTERRUPT_HANDLER);
                break;
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}

/* Set INTx Function pointer to it's intialized Function */
static Std_ReturnType INT0_SetInterruptHandler(void (*InterrptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != InterrptHandler){
        ret = E_OK;
        INT0_InterrptHandler = InterrptHandler;
    }
    return ret;
}

static Std_ReturnType INT1_SetInterruptHandler(void (*InterrptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != InterrptHandler){
        ret = E_OK;
        INT1_InterrptHandler = InterrptHandler;
    }
    return ret;
}

static Std_ReturnType INT2_SetInterruptHandler(void (*InterrptHandler)(void)){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != InterrptHandler){
        ret = E_OK;
        INT2_InterrptHandler = InterrptHandler;
    }
    return ret;
}
/* End of Setting INTx Function pointer to it's intialized Function */

/* INTx ISRs */
void INT0_ISR(void){
    EXT_INTERRUPT_INT0_FlagClear();
    
    if(INT0_InterrptHandler){
        INT0_InterrptHandler();
    }
    else{ /* Do Nothing */ }
}

void INT1_ISR(void){
    EXT_INTERRUPT_INT1_FlagClear();
    
    if(INT1_InterrptHandler){
        INT1_InterrptHandler();
    }
    else{ /* Do Nothing */ }
}

void INT2_ISR(void){
    EXT_INTERRUPT_INT2_FlagClear();
    
    if(INT2_InterrptHandler){
        INT2_InterrptHandler();
    }
    else{ /* Do Nothing */ }
}
/* End INTx ISRs */


/********    Helper Functions for RBx     ********/
//
static Std_ReturnType interrupt_RBx_enable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
#if     INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
        INTERRUPT_PEIORITY_LEVELS_ENABLe();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruptLowPriority_Enable();
        }
        else {
            INTERRUPT_GlobalInterruptHighPriority_Enable();
        }
#else
        INTERRUPT_PEIORITY_LEVELS_DISABLE();
        INTERRUPT_GlobalInterrupt_Enable();
        INTERRUPT_PeripheraInterrupt_Enable();
#endif
        EXT_INTERRUPT_RBx_ENABLE();
    }
    return ret;
}

static Std_ReturnType interrupt_RBx_disable(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        EXT_INTERRUPT_RBx_DISABLE();
    }
    return ret;
}

static Std_ReturnType interrupt_RBx_pin_initialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

#if   INTERRUPT_FEATURE_ENABLE == INTERRUPT_PRIORITY_LEVELS
static Std_ReturnType interrupt_RBx_priority_initialize(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            EXT_INTERRUPT_RBx_LowPriority();
        }
        else{
            EXT_INTERRUPT_RBx_HighPriority();
        }
    }
    return ret;
}
#endif

static Std_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj){
        ret = E_OK;
        EXT_INTERRUPT_RBx_FlagClear();
    }
    return ret; 
}

static Std_ReturnType interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != int_obj && PORTB_INDEX == int_obj->mcu_pin.port){
        ret = E_OK;
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4: 
                RB4_InterruptHandlerHigh = int_obj->EXT_INTERRUPT_HANDLER_HIGH; 
                RB4_InterruptHandlerLow = int_obj->EXT_INTERRUPT_HANDLER_LOW; 
                break;
            case GPIO_PIN5:
                RB5_InterruptHandlerHigh = int_obj->EXT_INTERRUPT_HANDLER_HIGH; 
                RB5_InterruptHandlerLow = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandlerHigh = int_obj->EXT_INTERRUPT_HANDLER_HIGH; 
                RB6_InterruptHandlerLow = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandlerHigh = int_obj->EXT_INTERRUPT_HANDLER_HIGH; 
                RB7_InterruptHandlerLow = int_obj->EXT_INTERRUPT_HANDLER_LOW;
                break;
            default: ret = E_NOT_OK;
        }
    }
    return ret; 
}

void RB4_ISR(uint8 state){
    EXT_INTERRUPT_RBx_FlagClear();
    
    if(0 == state){
        RB4_InterruptHandlerLow();
    }
    else if(1 == state){
        RB4_InterruptHandlerHigh();
    }
    else { /* Wrong argument */ }
}

void RB5_ISR(uint8 state){
    EXT_INTERRUPT_RBx_FlagClear();
    
    if(0 == state){
        RB5_InterruptHandlerLow();
    }
    else if(1 == state){
        RB5_InterruptHandlerHigh();
    }
    else { /* Wrong argument */ }
}

void RB6_ISR(uint8 state){
    EXT_INTERRUPT_RBx_FlagClear();
    
    if(0 == state){
        RB6_InterruptHandlerLow();
    }
    else if(1 == state){
        RB6_InterruptHandlerHigh();
    } 
    else { /* Wrong argument */ }
}

void RB7_ISR(uint8 state){
    EXT_INTERRUPT_RBx_FlagClear();
    
    if(0 == state){
        RB7_InterruptHandlerLow();
    }
    else if(1 == state){
        RB7_InterruptHandlerHigh();
    } 
    else { /* Wrong argument */ }
}
