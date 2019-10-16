/*******************************************************************************
* File Name: SPIByteCounter.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SPIByteCounter
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_SPIByteCounter_H)
#define CY_TCPWM_SPIByteCounter_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} SPIByteCounter_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SPIByteCounter_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SPIByteCounter_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SPIByteCounter_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SPIByteCounter_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SPIByteCounter_QUAD_ENCODING_MODES            (0lu)
#define SPIByteCounter_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SPIByteCounter_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SPIByteCounter_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SPIByteCounter_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SPIByteCounter_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SPIByteCounter_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SPIByteCounter_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SPIByteCounter_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SPIByteCounter_TC_RUN_MODE                    (0lu)
#define SPIByteCounter_TC_COUNTER_MODE                (0lu)
#define SPIByteCounter_TC_COMP_CAP_MODE               (2lu)
#define SPIByteCounter_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SPIByteCounter_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SPIByteCounter_TC_COUNT_SIGNAL_MODE           (0lu)
#define SPIByteCounter_TC_START_SIGNAL_MODE           (0lu)
#define SPIByteCounter_TC_STOP_SIGNAL_MODE            (0lu)
#define SPIByteCounter_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SPIByteCounter_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SPIByteCounter_TC_COUNT_SIGNAL_PRESENT        (1lu)
#define SPIByteCounter_TC_START_SIGNAL_PRESENT        (0lu)
#define SPIByteCounter_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SPIByteCounter_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SPIByteCounter_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SPIByteCounter_PWM_KILL_EVENT                 (0lu)
#define SPIByteCounter_PWM_STOP_EVENT                 (0lu)
#define SPIByteCounter_PWM_MODE                       (4lu)
#define SPIByteCounter_PWM_OUT_N_INVERT               (0lu)
#define SPIByteCounter_PWM_OUT_INVERT                 (0lu)
#define SPIByteCounter_PWM_ALIGN                      (0lu)
#define SPIByteCounter_PWM_RUN_MODE                   (0lu)
#define SPIByteCounter_PWM_DEAD_TIME_CYCLE            (0lu)
#define SPIByteCounter_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SPIByteCounter_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SPIByteCounter_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SPIByteCounter_PWM_START_SIGNAL_MODE          (0lu)
#define SPIByteCounter_PWM_STOP_SIGNAL_MODE           (0lu)
#define SPIByteCounter_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SPIByteCounter_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SPIByteCounter_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SPIByteCounter_PWM_START_SIGNAL_PRESENT       (0lu)
#define SPIByteCounter_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SPIByteCounter_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SPIByteCounter_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SPIByteCounter_TC_PERIOD_VALUE                (31lu)
#define SPIByteCounter_TC_COMPARE_VALUE               (65535lu)
#define SPIByteCounter_TC_COMPARE_BUF_VALUE           (65535lu)
#define SPIByteCounter_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SPIByteCounter_PWM_PERIOD_VALUE               (65535lu)
#define SPIByteCounter_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SPIByteCounter_PWM_PERIOD_SWAP                (0lu)
#define SPIByteCounter_PWM_COMPARE_VALUE              (65535lu)
#define SPIByteCounter_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SPIByteCounter_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SPIByteCounter__LEFT 0
#define SPIByteCounter__RIGHT 1
#define SPIByteCounter__CENTER 2
#define SPIByteCounter__ASYMMETRIC 3

#define SPIByteCounter__X1 0
#define SPIByteCounter__X2 1
#define SPIByteCounter__X4 2

#define SPIByteCounter__PWM 4
#define SPIByteCounter__PWM_DT 5
#define SPIByteCounter__PWM_PR 6

#define SPIByteCounter__INVERSE 1
#define SPIByteCounter__DIRECT 0

#define SPIByteCounter__CAPTURE 2
#define SPIByteCounter__COMPARE 0

#define SPIByteCounter__TRIG_LEVEL 3
#define SPIByteCounter__TRIG_RISING 0
#define SPIByteCounter__TRIG_FALLING 1
#define SPIByteCounter__TRIG_BOTH 2

#define SPIByteCounter__INTR_MASK_TC 1
#define SPIByteCounter__INTR_MASK_CC_MATCH 2
#define SPIByteCounter__INTR_MASK_NONE 0
#define SPIByteCounter__INTR_MASK_TC_CC 3

#define SPIByteCounter__UNCONFIG 8
#define SPIByteCounter__TIMER 1
#define SPIByteCounter__QUAD 3
#define SPIByteCounter__PWM_SEL 7

#define SPIByteCounter__COUNT_UP 0
#define SPIByteCounter__COUNT_DOWN 1
#define SPIByteCounter__COUNT_UPDOWN0 2
#define SPIByteCounter__COUNT_UPDOWN1 3


/* Prescaler */
#define SPIByteCounter_PRESCALE_DIVBY1                ((uint32)(0u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY2                ((uint32)(1u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY4                ((uint32)(2u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY8                ((uint32)(3u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY16               ((uint32)(4u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY32               ((uint32)(5u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY64               ((uint32)(6u << SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_PRESCALE_DIVBY128              ((uint32)(7u << SPIByteCounter_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SPIByteCounter_MODE_TIMER_COMPARE             ((uint32)(SPIByteCounter__COMPARE         <<  \
                                                                  SPIByteCounter_MODE_SHIFT))
#define SPIByteCounter_MODE_TIMER_CAPTURE             ((uint32)(SPIByteCounter__CAPTURE         <<  \
                                                                  SPIByteCounter_MODE_SHIFT))
#define SPIByteCounter_MODE_QUAD                      ((uint32)(SPIByteCounter__QUAD            <<  \
                                                                  SPIByteCounter_MODE_SHIFT))
#define SPIByteCounter_MODE_PWM                       ((uint32)(SPIByteCounter__PWM             <<  \
                                                                  SPIByteCounter_MODE_SHIFT))
#define SPIByteCounter_MODE_PWM_DT                    ((uint32)(SPIByteCounter__PWM_DT          <<  \
                                                                  SPIByteCounter_MODE_SHIFT))
#define SPIByteCounter_MODE_PWM_PR                    ((uint32)(SPIByteCounter__PWM_PR          <<  \
                                                                  SPIByteCounter_MODE_SHIFT))

/* Quad Modes */
#define SPIByteCounter_MODE_X1                        ((uint32)(SPIByteCounter__X1              <<  \
                                                                  SPIByteCounter_QUAD_MODE_SHIFT))
#define SPIByteCounter_MODE_X2                        ((uint32)(SPIByteCounter__X2              <<  \
                                                                  SPIByteCounter_QUAD_MODE_SHIFT))
#define SPIByteCounter_MODE_X4                        ((uint32)(SPIByteCounter__X4              <<  \
                                                                  SPIByteCounter_QUAD_MODE_SHIFT))

/* Counter modes */
#define SPIByteCounter_COUNT_UP                       ((uint32)(SPIByteCounter__COUNT_UP        <<  \
                                                                  SPIByteCounter_UPDOWN_SHIFT))
#define SPIByteCounter_COUNT_DOWN                     ((uint32)(SPIByteCounter__COUNT_DOWN      <<  \
                                                                  SPIByteCounter_UPDOWN_SHIFT))
#define SPIByteCounter_COUNT_UPDOWN0                  ((uint32)(SPIByteCounter__COUNT_UPDOWN0   <<  \
                                                                  SPIByteCounter_UPDOWN_SHIFT))
#define SPIByteCounter_COUNT_UPDOWN1                  ((uint32)(SPIByteCounter__COUNT_UPDOWN1   <<  \
                                                                  SPIByteCounter_UPDOWN_SHIFT))

/* PWM output invert */
#define SPIByteCounter_INVERT_LINE                    ((uint32)(SPIByteCounter__INVERSE         <<  \
                                                                  SPIByteCounter_INV_OUT_SHIFT))
#define SPIByteCounter_INVERT_LINE_N                  ((uint32)(SPIByteCounter__INVERSE         <<  \
                                                                  SPIByteCounter_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SPIByteCounter_TRIG_RISING                    ((uint32)SPIByteCounter__TRIG_RISING)
#define SPIByteCounter_TRIG_FALLING                   ((uint32)SPIByteCounter__TRIG_FALLING)
#define SPIByteCounter_TRIG_BOTH                      ((uint32)SPIByteCounter__TRIG_BOTH)
#define SPIByteCounter_TRIG_LEVEL                     ((uint32)SPIByteCounter__TRIG_LEVEL)

/* Interrupt mask */
#define SPIByteCounter_INTR_MASK_TC                   ((uint32)SPIByteCounter__INTR_MASK_TC)
#define SPIByteCounter_INTR_MASK_CC_MATCH             ((uint32)SPIByteCounter__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SPIByteCounter_CC_MATCH_SET                   (0x00u)
#define SPIByteCounter_CC_MATCH_CLEAR                 (0x01u)
#define SPIByteCounter_CC_MATCH_INVERT                (0x02u)
#define SPIByteCounter_CC_MATCH_NO_CHANGE             (0x03u)
#define SPIByteCounter_OVERLOW_SET                    (0x00u)
#define SPIByteCounter_OVERLOW_CLEAR                  (0x04u)
#define SPIByteCounter_OVERLOW_INVERT                 (0x08u)
#define SPIByteCounter_OVERLOW_NO_CHANGE              (0x0Cu)
#define SPIByteCounter_UNDERFLOW_SET                  (0x00u)
#define SPIByteCounter_UNDERFLOW_CLEAR                (0x10u)
#define SPIByteCounter_UNDERFLOW_INVERT               (0x20u)
#define SPIByteCounter_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SPIByteCounter_PWM_MODE_LEFT                  (SPIByteCounter_CC_MATCH_CLEAR        |   \
                                                         SPIByteCounter_OVERLOW_SET           |   \
                                                         SPIByteCounter_UNDERFLOW_NO_CHANGE)
#define SPIByteCounter_PWM_MODE_RIGHT                 (SPIByteCounter_CC_MATCH_SET          |   \
                                                         SPIByteCounter_OVERLOW_NO_CHANGE     |   \
                                                         SPIByteCounter_UNDERFLOW_CLEAR)
#define SPIByteCounter_PWM_MODE_ASYM                  (SPIByteCounter_CC_MATCH_INVERT       |   \
                                                         SPIByteCounter_OVERLOW_SET           |   \
                                                         SPIByteCounter_UNDERFLOW_CLEAR)

#if (SPIByteCounter_CY_TCPWM_V2)
    #if(SPIByteCounter_CY_TCPWM_4000)
        #define SPIByteCounter_PWM_MODE_CENTER                (SPIByteCounter_CC_MATCH_INVERT       |   \
                                                                 SPIByteCounter_OVERLOW_NO_CHANGE     |   \
                                                                 SPIByteCounter_UNDERFLOW_CLEAR)
    #else
        #define SPIByteCounter_PWM_MODE_CENTER                (SPIByteCounter_CC_MATCH_INVERT       |   \
                                                                 SPIByteCounter_OVERLOW_SET           |   \
                                                                 SPIByteCounter_UNDERFLOW_CLEAR)
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */
#else
    #define SPIByteCounter_PWM_MODE_CENTER                (SPIByteCounter_CC_MATCH_INVERT       |   \
                                                             SPIByteCounter_OVERLOW_NO_CHANGE     |   \
                                                             SPIByteCounter_UNDERFLOW_CLEAR)
#endif /* (SPIByteCounter_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SPIByteCounter_CMD_CAPTURE                    (0u)
#define SPIByteCounter_CMD_RELOAD                     (8u)
#define SPIByteCounter_CMD_STOP                       (16u)
#define SPIByteCounter_CMD_START                      (24u)

/* Status */
#define SPIByteCounter_STATUS_DOWN                    (1u)
#define SPIByteCounter_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SPIByteCounter_Init(void);
void   SPIByteCounter_Enable(void);
void   SPIByteCounter_Start(void);
void   SPIByteCounter_Stop(void);

void   SPIByteCounter_SetMode(uint32 mode);
void   SPIByteCounter_SetCounterMode(uint32 counterMode);
void   SPIByteCounter_SetPWMMode(uint32 modeMask);
void   SPIByteCounter_SetQDMode(uint32 qdMode);

void   SPIByteCounter_SetPrescaler(uint32 prescaler);
void   SPIByteCounter_TriggerCommand(uint32 mask, uint32 command);
void   SPIByteCounter_SetOneShot(uint32 oneShotEnable);
uint32 SPIByteCounter_ReadStatus(void);

void   SPIByteCounter_SetPWMSyncKill(uint32 syncKillEnable);
void   SPIByteCounter_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SPIByteCounter_SetPWMDeadTime(uint32 deadTime);
void   SPIByteCounter_SetPWMInvert(uint32 mask);

void   SPIByteCounter_SetInterruptMode(uint32 interruptMask);
uint32 SPIByteCounter_GetInterruptSourceMasked(void);
uint32 SPIByteCounter_GetInterruptSource(void);
void   SPIByteCounter_ClearInterrupt(uint32 interruptMask);
void   SPIByteCounter_SetInterrupt(uint32 interruptMask);

void   SPIByteCounter_WriteCounter(uint32 count);
uint32 SPIByteCounter_ReadCounter(void);

uint32 SPIByteCounter_ReadCapture(void);
uint32 SPIByteCounter_ReadCaptureBuf(void);

void   SPIByteCounter_WritePeriod(uint32 period);
uint32 SPIByteCounter_ReadPeriod(void);
void   SPIByteCounter_WritePeriodBuf(uint32 periodBuf);
uint32 SPIByteCounter_ReadPeriodBuf(void);

void   SPIByteCounter_WriteCompare(uint32 compare);
uint32 SPIByteCounter_ReadCompare(void);
void   SPIByteCounter_WriteCompareBuf(uint32 compareBuf);
uint32 SPIByteCounter_ReadCompareBuf(void);

void   SPIByteCounter_SetPeriodSwap(uint32 swapEnable);
void   SPIByteCounter_SetCompareSwap(uint32 swapEnable);

void   SPIByteCounter_SetCaptureMode(uint32 triggerMode);
void   SPIByteCounter_SetReloadMode(uint32 triggerMode);
void   SPIByteCounter_SetStartMode(uint32 triggerMode);
void   SPIByteCounter_SetStopMode(uint32 triggerMode);
void   SPIByteCounter_SetCountMode(uint32 triggerMode);

void   SPIByteCounter_SaveConfig(void);
void   SPIByteCounter_RestoreConfig(void);
void   SPIByteCounter_Sleep(void);
void   SPIByteCounter_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SPIByteCounter_BLOCK_CONTROL_REG              (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SPIByteCounter_BLOCK_CONTROL_PTR              ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SPIByteCounter_COMMAND_REG                    (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SPIByteCounter_COMMAND_PTR                    ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SPIByteCounter_INTRRUPT_CAUSE_REG             (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SPIByteCounter_INTRRUPT_CAUSE_PTR             ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SPIByteCounter_CONTROL_REG                    (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__CTRL )
#define SPIByteCounter_CONTROL_PTR                    ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__CTRL )
#define SPIByteCounter_STATUS_REG                     (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__STATUS )
#define SPIByteCounter_STATUS_PTR                     ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__STATUS )
#define SPIByteCounter_COUNTER_REG                    (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__COUNTER )
#define SPIByteCounter_COUNTER_PTR                    ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__COUNTER )
#define SPIByteCounter_COMP_CAP_REG                   (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__CC )
#define SPIByteCounter_COMP_CAP_PTR                   ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__CC )
#define SPIByteCounter_COMP_CAP_BUF_REG               (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define SPIByteCounter_COMP_CAP_BUF_PTR               ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define SPIByteCounter_PERIOD_REG                     (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__PERIOD )
#define SPIByteCounter_PERIOD_PTR                     ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__PERIOD )
#define SPIByteCounter_PERIOD_BUF_REG                 (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SPIByteCounter_PERIOD_BUF_PTR                 ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SPIByteCounter_TRIG_CONTROL0_REG              (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SPIByteCounter_TRIG_CONTROL0_PTR              ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SPIByteCounter_TRIG_CONTROL1_REG              (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SPIByteCounter_TRIG_CONTROL1_PTR              ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SPIByteCounter_TRIG_CONTROL2_REG              (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SPIByteCounter_TRIG_CONTROL2_PTR              ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SPIByteCounter_INTERRUPT_REQ_REG              (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR )
#define SPIByteCounter_INTERRUPT_REQ_PTR              ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR )
#define SPIByteCounter_INTERRUPT_SET_REG              (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR_SET )
#define SPIByteCounter_INTERRUPT_SET_PTR              ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR_SET )
#define SPIByteCounter_INTERRUPT_MASK_REG             (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define SPIByteCounter_INTERRUPT_MASK_PTR             ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define SPIByteCounter_INTERRUPT_MASKED_REG           (*(reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SPIByteCounter_INTERRUPT_MASKED_PTR           ( (reg32 *) SPIByteCounter_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SPIByteCounter_MASK                           ((uint32)SPIByteCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SPIByteCounter_RELOAD_CC_SHIFT                (0u)
#define SPIByteCounter_RELOAD_PERIOD_SHIFT            (1u)
#define SPIByteCounter_PWM_SYNC_KILL_SHIFT            (2u)
#define SPIByteCounter_PWM_STOP_KILL_SHIFT            (3u)
#define SPIByteCounter_PRESCALER_SHIFT                (8u)
#define SPIByteCounter_UPDOWN_SHIFT                   (16u)
#define SPIByteCounter_ONESHOT_SHIFT                  (18u)
#define SPIByteCounter_QUAD_MODE_SHIFT                (20u)
#define SPIByteCounter_INV_OUT_SHIFT                  (20u)
#define SPIByteCounter_INV_COMPL_OUT_SHIFT            (21u)
#define SPIByteCounter_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SPIByteCounter_RELOAD_CC_MASK                 ((uint32)(SPIByteCounter_1BIT_MASK        <<  \
                                                                            SPIByteCounter_RELOAD_CC_SHIFT))
#define SPIByteCounter_RELOAD_PERIOD_MASK             ((uint32)(SPIByteCounter_1BIT_MASK        <<  \
                                                                            SPIByteCounter_RELOAD_PERIOD_SHIFT))
#define SPIByteCounter_PWM_SYNC_KILL_MASK             ((uint32)(SPIByteCounter_1BIT_MASK        <<  \
                                                                            SPIByteCounter_PWM_SYNC_KILL_SHIFT))
#define SPIByteCounter_PWM_STOP_KILL_MASK             ((uint32)(SPIByteCounter_1BIT_MASK        <<  \
                                                                            SPIByteCounter_PWM_STOP_KILL_SHIFT))
#define SPIByteCounter_PRESCALER_MASK                 ((uint32)(SPIByteCounter_8BIT_MASK        <<  \
                                                                            SPIByteCounter_PRESCALER_SHIFT))
#define SPIByteCounter_UPDOWN_MASK                    ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                            SPIByteCounter_UPDOWN_SHIFT))
#define SPIByteCounter_ONESHOT_MASK                   ((uint32)(SPIByteCounter_1BIT_MASK        <<  \
                                                                            SPIByteCounter_ONESHOT_SHIFT))
#define SPIByteCounter_QUAD_MODE_MASK                 ((uint32)(SPIByteCounter_3BIT_MASK        <<  \
                                                                            SPIByteCounter_QUAD_MODE_SHIFT))
#define SPIByteCounter_INV_OUT_MASK                   ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                            SPIByteCounter_INV_OUT_SHIFT))
#define SPIByteCounter_MODE_MASK                      ((uint32)(SPIByteCounter_3BIT_MASK        <<  \
                                                                            SPIByteCounter_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SPIByteCounter_CAPTURE_SHIFT                  (0u)
#define SPIByteCounter_COUNT_SHIFT                    (2u)
#define SPIByteCounter_RELOAD_SHIFT                   (4u)
#define SPIByteCounter_STOP_SHIFT                     (6u)
#define SPIByteCounter_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SPIByteCounter_CAPTURE_MASK                   ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                  SPIByteCounter_CAPTURE_SHIFT))
#define SPIByteCounter_COUNT_MASK                     ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                  SPIByteCounter_COUNT_SHIFT))
#define SPIByteCounter_RELOAD_MASK                    ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                  SPIByteCounter_RELOAD_SHIFT))
#define SPIByteCounter_STOP_MASK                      ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                  SPIByteCounter_STOP_SHIFT))
#define SPIByteCounter_START_MASK                     ((uint32)(SPIByteCounter_2BIT_MASK        <<  \
                                                                  SPIByteCounter_START_SHIFT))

/* MASK */
#define SPIByteCounter_1BIT_MASK                      ((uint32)0x01u)
#define SPIByteCounter_2BIT_MASK                      ((uint32)0x03u)
#define SPIByteCounter_3BIT_MASK                      ((uint32)0x07u)
#define SPIByteCounter_6BIT_MASK                      ((uint32)0x3Fu)
#define SPIByteCounter_8BIT_MASK                      ((uint32)0xFFu)
#define SPIByteCounter_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SPIByteCounter_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SPIByteCounter_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SPIByteCounter_QUAD_ENCODING_MODES     << SPIByteCounter_QUAD_MODE_SHIFT))       |\
         ((uint32)(SPIByteCounter_CONFIG                  << SPIByteCounter_MODE_SHIFT)))

#define SPIByteCounter_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SPIByteCounter_PWM_STOP_EVENT          << SPIByteCounter_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SPIByteCounter_PWM_OUT_INVERT          << SPIByteCounter_INV_OUT_SHIFT))         |\
         ((uint32)(SPIByteCounter_PWM_OUT_N_INVERT        << SPIByteCounter_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SPIByteCounter_PWM_MODE                << SPIByteCounter_MODE_SHIFT)))

#define SPIByteCounter_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SPIByteCounter_PWM_RUN_MODE         << SPIByteCounter_ONESHOT_SHIFT))
            
#define SPIByteCounter_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SPIByteCounter_PWM_ALIGN            << SPIByteCounter_UPDOWN_SHIFT))

#define SPIByteCounter_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SPIByteCounter_PWM_KILL_EVENT      << SPIByteCounter_PWM_SYNC_KILL_SHIFT))

#define SPIByteCounter_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SPIByteCounter_PWM_DEAD_TIME_CYCLE  << SPIByteCounter_PRESCALER_SHIFT))

#define SPIByteCounter_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SPIByteCounter_PWM_PRESCALER        << SPIByteCounter_PRESCALER_SHIFT))

#define SPIByteCounter_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SPIByteCounter_TC_PRESCALER            << SPIByteCounter_PRESCALER_SHIFT))       |\
         ((uint32)(SPIByteCounter_TC_COUNTER_MODE         << SPIByteCounter_UPDOWN_SHIFT))          |\
         ((uint32)(SPIByteCounter_TC_RUN_MODE             << SPIByteCounter_ONESHOT_SHIFT))         |\
         ((uint32)(SPIByteCounter_TC_COMP_CAP_MODE        << SPIByteCounter_MODE_SHIFT)))
        
#define SPIByteCounter_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SPIByteCounter_QUAD_PHIA_SIGNAL_MODE   << SPIByteCounter_COUNT_SHIFT))           |\
         ((uint32)(SPIByteCounter_QUAD_INDEX_SIGNAL_MODE  << SPIByteCounter_RELOAD_SHIFT))          |\
         ((uint32)(SPIByteCounter_QUAD_STOP_SIGNAL_MODE   << SPIByteCounter_STOP_SHIFT))            |\
         ((uint32)(SPIByteCounter_QUAD_PHIB_SIGNAL_MODE   << SPIByteCounter_START_SHIFT)))

#define SPIByteCounter_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SPIByteCounter_PWM_SWITCH_SIGNAL_MODE  << SPIByteCounter_CAPTURE_SHIFT))         |\
         ((uint32)(SPIByteCounter_PWM_COUNT_SIGNAL_MODE   << SPIByteCounter_COUNT_SHIFT))           |\
         ((uint32)(SPIByteCounter_PWM_RELOAD_SIGNAL_MODE  << SPIByteCounter_RELOAD_SHIFT))          |\
         ((uint32)(SPIByteCounter_PWM_STOP_SIGNAL_MODE    << SPIByteCounter_STOP_SHIFT))            |\
         ((uint32)(SPIByteCounter_PWM_START_SIGNAL_MODE   << SPIByteCounter_START_SHIFT)))

#define SPIByteCounter_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SPIByteCounter_TC_CAPTURE_SIGNAL_MODE  << SPIByteCounter_CAPTURE_SHIFT))         |\
         ((uint32)(SPIByteCounter_TC_COUNT_SIGNAL_MODE    << SPIByteCounter_COUNT_SHIFT))           |\
         ((uint32)(SPIByteCounter_TC_RELOAD_SIGNAL_MODE   << SPIByteCounter_RELOAD_SHIFT))          |\
         ((uint32)(SPIByteCounter_TC_STOP_SIGNAL_MODE     << SPIByteCounter_STOP_SHIFT))            |\
         ((uint32)(SPIByteCounter_TC_START_SIGNAL_MODE    << SPIByteCounter_START_SHIFT)))
        
#define SPIByteCounter_TIMER_UPDOWN_CNT_USED                                                          \
                ((SPIByteCounter__COUNT_UPDOWN0 == SPIByteCounter_TC_COUNTER_MODE)                  ||\
                 (SPIByteCounter__COUNT_UPDOWN1 == SPIByteCounter_TC_COUNTER_MODE))

#define SPIByteCounter_PWM_UPDOWN_CNT_USED                                                            \
                ((SPIByteCounter__CENTER == SPIByteCounter_PWM_ALIGN)                               ||\
                 (SPIByteCounter__ASYMMETRIC == SPIByteCounter_PWM_ALIGN))               
        
#define SPIByteCounter_PWM_PR_INIT_VALUE              (1u)
#define SPIByteCounter_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SPIByteCounter_H */

/* [] END OF FILE */
