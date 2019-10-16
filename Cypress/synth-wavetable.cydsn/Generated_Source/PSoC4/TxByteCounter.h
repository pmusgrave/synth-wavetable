/*******************************************************************************
* File Name: TxByteCounter.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TxByteCounter
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

#if !defined(CY_TCPWM_TxByteCounter_H)
#define CY_TCPWM_TxByteCounter_H


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
} TxByteCounter_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TxByteCounter_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TxByteCounter_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TxByteCounter_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TxByteCounter_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TxByteCounter_QUAD_ENCODING_MODES            (0lu)
#define TxByteCounter_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define TxByteCounter_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TxByteCounter_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TxByteCounter_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TxByteCounter_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TxByteCounter_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TxByteCounter_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TxByteCounter_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TxByteCounter_TC_RUN_MODE                    (0lu)
#define TxByteCounter_TC_COUNTER_MODE                (0lu)
#define TxByteCounter_TC_COMP_CAP_MODE               (2lu)
#define TxByteCounter_TC_PRESCALER                   (0lu)

/* Signal modes */
#define TxByteCounter_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TxByteCounter_TC_COUNT_SIGNAL_MODE           (0lu)
#define TxByteCounter_TC_START_SIGNAL_MODE           (0lu)
#define TxByteCounter_TC_STOP_SIGNAL_MODE            (0lu)
#define TxByteCounter_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TxByteCounter_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TxByteCounter_TC_COUNT_SIGNAL_PRESENT        (1lu)
#define TxByteCounter_TC_START_SIGNAL_PRESENT        (0lu)
#define TxByteCounter_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TxByteCounter_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TxByteCounter_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define TxByteCounter_PWM_KILL_EVENT                 (0lu)
#define TxByteCounter_PWM_STOP_EVENT                 (0lu)
#define TxByteCounter_PWM_MODE                       (4lu)
#define TxByteCounter_PWM_OUT_N_INVERT               (0lu)
#define TxByteCounter_PWM_OUT_INVERT                 (0lu)
#define TxByteCounter_PWM_ALIGN                      (0lu)
#define TxByteCounter_PWM_RUN_MODE                   (0lu)
#define TxByteCounter_PWM_DEAD_TIME_CYCLE            (0lu)
#define TxByteCounter_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TxByteCounter_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TxByteCounter_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TxByteCounter_PWM_START_SIGNAL_MODE          (0lu)
#define TxByteCounter_PWM_STOP_SIGNAL_MODE           (0lu)
#define TxByteCounter_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TxByteCounter_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TxByteCounter_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TxByteCounter_PWM_START_SIGNAL_PRESENT       (0lu)
#define TxByteCounter_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TxByteCounter_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TxByteCounter_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TxByteCounter_TC_PERIOD_VALUE                (31lu)
#define TxByteCounter_TC_COMPARE_VALUE               (65535lu)
#define TxByteCounter_TC_COMPARE_BUF_VALUE           (65535lu)
#define TxByteCounter_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TxByteCounter_PWM_PERIOD_VALUE               (65535lu)
#define TxByteCounter_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TxByteCounter_PWM_PERIOD_SWAP                (0lu)
#define TxByteCounter_PWM_COMPARE_VALUE              (65535lu)
#define TxByteCounter_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TxByteCounter_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TxByteCounter__LEFT 0
#define TxByteCounter__RIGHT 1
#define TxByteCounter__CENTER 2
#define TxByteCounter__ASYMMETRIC 3

#define TxByteCounter__X1 0
#define TxByteCounter__X2 1
#define TxByteCounter__X4 2

#define TxByteCounter__PWM 4
#define TxByteCounter__PWM_DT 5
#define TxByteCounter__PWM_PR 6

#define TxByteCounter__INVERSE 1
#define TxByteCounter__DIRECT 0

#define TxByteCounter__CAPTURE 2
#define TxByteCounter__COMPARE 0

#define TxByteCounter__TRIG_LEVEL 3
#define TxByteCounter__TRIG_RISING 0
#define TxByteCounter__TRIG_FALLING 1
#define TxByteCounter__TRIG_BOTH 2

#define TxByteCounter__INTR_MASK_TC 1
#define TxByteCounter__INTR_MASK_CC_MATCH 2
#define TxByteCounter__INTR_MASK_NONE 0
#define TxByteCounter__INTR_MASK_TC_CC 3

#define TxByteCounter__UNCONFIG 8
#define TxByteCounter__TIMER 1
#define TxByteCounter__QUAD 3
#define TxByteCounter__PWM_SEL 7

#define TxByteCounter__COUNT_UP 0
#define TxByteCounter__COUNT_DOWN 1
#define TxByteCounter__COUNT_UPDOWN0 2
#define TxByteCounter__COUNT_UPDOWN1 3


/* Prescaler */
#define TxByteCounter_PRESCALE_DIVBY1                ((uint32)(0u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY2                ((uint32)(1u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY4                ((uint32)(2u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY8                ((uint32)(3u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY16               ((uint32)(4u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY32               ((uint32)(5u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY64               ((uint32)(6u << TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_PRESCALE_DIVBY128              ((uint32)(7u << TxByteCounter_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TxByteCounter_MODE_TIMER_COMPARE             ((uint32)(TxByteCounter__COMPARE         <<  \
                                                                  TxByteCounter_MODE_SHIFT))
#define TxByteCounter_MODE_TIMER_CAPTURE             ((uint32)(TxByteCounter__CAPTURE         <<  \
                                                                  TxByteCounter_MODE_SHIFT))
#define TxByteCounter_MODE_QUAD                      ((uint32)(TxByteCounter__QUAD            <<  \
                                                                  TxByteCounter_MODE_SHIFT))
#define TxByteCounter_MODE_PWM                       ((uint32)(TxByteCounter__PWM             <<  \
                                                                  TxByteCounter_MODE_SHIFT))
#define TxByteCounter_MODE_PWM_DT                    ((uint32)(TxByteCounter__PWM_DT          <<  \
                                                                  TxByteCounter_MODE_SHIFT))
#define TxByteCounter_MODE_PWM_PR                    ((uint32)(TxByteCounter__PWM_PR          <<  \
                                                                  TxByteCounter_MODE_SHIFT))

/* Quad Modes */
#define TxByteCounter_MODE_X1                        ((uint32)(TxByteCounter__X1              <<  \
                                                                  TxByteCounter_QUAD_MODE_SHIFT))
#define TxByteCounter_MODE_X2                        ((uint32)(TxByteCounter__X2              <<  \
                                                                  TxByteCounter_QUAD_MODE_SHIFT))
#define TxByteCounter_MODE_X4                        ((uint32)(TxByteCounter__X4              <<  \
                                                                  TxByteCounter_QUAD_MODE_SHIFT))

/* Counter modes */
#define TxByteCounter_COUNT_UP                       ((uint32)(TxByteCounter__COUNT_UP        <<  \
                                                                  TxByteCounter_UPDOWN_SHIFT))
#define TxByteCounter_COUNT_DOWN                     ((uint32)(TxByteCounter__COUNT_DOWN      <<  \
                                                                  TxByteCounter_UPDOWN_SHIFT))
#define TxByteCounter_COUNT_UPDOWN0                  ((uint32)(TxByteCounter__COUNT_UPDOWN0   <<  \
                                                                  TxByteCounter_UPDOWN_SHIFT))
#define TxByteCounter_COUNT_UPDOWN1                  ((uint32)(TxByteCounter__COUNT_UPDOWN1   <<  \
                                                                  TxByteCounter_UPDOWN_SHIFT))

/* PWM output invert */
#define TxByteCounter_INVERT_LINE                    ((uint32)(TxByteCounter__INVERSE         <<  \
                                                                  TxByteCounter_INV_OUT_SHIFT))
#define TxByteCounter_INVERT_LINE_N                  ((uint32)(TxByteCounter__INVERSE         <<  \
                                                                  TxByteCounter_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TxByteCounter_TRIG_RISING                    ((uint32)TxByteCounter__TRIG_RISING)
#define TxByteCounter_TRIG_FALLING                   ((uint32)TxByteCounter__TRIG_FALLING)
#define TxByteCounter_TRIG_BOTH                      ((uint32)TxByteCounter__TRIG_BOTH)
#define TxByteCounter_TRIG_LEVEL                     ((uint32)TxByteCounter__TRIG_LEVEL)

/* Interrupt mask */
#define TxByteCounter_INTR_MASK_TC                   ((uint32)TxByteCounter__INTR_MASK_TC)
#define TxByteCounter_INTR_MASK_CC_MATCH             ((uint32)TxByteCounter__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TxByteCounter_CC_MATCH_SET                   (0x00u)
#define TxByteCounter_CC_MATCH_CLEAR                 (0x01u)
#define TxByteCounter_CC_MATCH_INVERT                (0x02u)
#define TxByteCounter_CC_MATCH_NO_CHANGE             (0x03u)
#define TxByteCounter_OVERLOW_SET                    (0x00u)
#define TxByteCounter_OVERLOW_CLEAR                  (0x04u)
#define TxByteCounter_OVERLOW_INVERT                 (0x08u)
#define TxByteCounter_OVERLOW_NO_CHANGE              (0x0Cu)
#define TxByteCounter_UNDERFLOW_SET                  (0x00u)
#define TxByteCounter_UNDERFLOW_CLEAR                (0x10u)
#define TxByteCounter_UNDERFLOW_INVERT               (0x20u)
#define TxByteCounter_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TxByteCounter_PWM_MODE_LEFT                  (TxByteCounter_CC_MATCH_CLEAR        |   \
                                                         TxByteCounter_OVERLOW_SET           |   \
                                                         TxByteCounter_UNDERFLOW_NO_CHANGE)
#define TxByteCounter_PWM_MODE_RIGHT                 (TxByteCounter_CC_MATCH_SET          |   \
                                                         TxByteCounter_OVERLOW_NO_CHANGE     |   \
                                                         TxByteCounter_UNDERFLOW_CLEAR)
#define TxByteCounter_PWM_MODE_ASYM                  (TxByteCounter_CC_MATCH_INVERT       |   \
                                                         TxByteCounter_OVERLOW_SET           |   \
                                                         TxByteCounter_UNDERFLOW_CLEAR)

#if (TxByteCounter_CY_TCPWM_V2)
    #if(TxByteCounter_CY_TCPWM_4000)
        #define TxByteCounter_PWM_MODE_CENTER                (TxByteCounter_CC_MATCH_INVERT       |   \
                                                                 TxByteCounter_OVERLOW_NO_CHANGE     |   \
                                                                 TxByteCounter_UNDERFLOW_CLEAR)
    #else
        #define TxByteCounter_PWM_MODE_CENTER                (TxByteCounter_CC_MATCH_INVERT       |   \
                                                                 TxByteCounter_OVERLOW_SET           |   \
                                                                 TxByteCounter_UNDERFLOW_CLEAR)
    #endif /* (TxByteCounter_CY_TCPWM_4000) */
#else
    #define TxByteCounter_PWM_MODE_CENTER                (TxByteCounter_CC_MATCH_INVERT       |   \
                                                             TxByteCounter_OVERLOW_NO_CHANGE     |   \
                                                             TxByteCounter_UNDERFLOW_CLEAR)
#endif /* (TxByteCounter_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TxByteCounter_CMD_CAPTURE                    (0u)
#define TxByteCounter_CMD_RELOAD                     (8u)
#define TxByteCounter_CMD_STOP                       (16u)
#define TxByteCounter_CMD_START                      (24u)

/* Status */
#define TxByteCounter_STATUS_DOWN                    (1u)
#define TxByteCounter_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TxByteCounter_Init(void);
void   TxByteCounter_Enable(void);
void   TxByteCounter_Start(void);
void   TxByteCounter_Stop(void);

void   TxByteCounter_SetMode(uint32 mode);
void   TxByteCounter_SetCounterMode(uint32 counterMode);
void   TxByteCounter_SetPWMMode(uint32 modeMask);
void   TxByteCounter_SetQDMode(uint32 qdMode);

void   TxByteCounter_SetPrescaler(uint32 prescaler);
void   TxByteCounter_TriggerCommand(uint32 mask, uint32 command);
void   TxByteCounter_SetOneShot(uint32 oneShotEnable);
uint32 TxByteCounter_ReadStatus(void);

void   TxByteCounter_SetPWMSyncKill(uint32 syncKillEnable);
void   TxByteCounter_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TxByteCounter_SetPWMDeadTime(uint32 deadTime);
void   TxByteCounter_SetPWMInvert(uint32 mask);

void   TxByteCounter_SetInterruptMode(uint32 interruptMask);
uint32 TxByteCounter_GetInterruptSourceMasked(void);
uint32 TxByteCounter_GetInterruptSource(void);
void   TxByteCounter_ClearInterrupt(uint32 interruptMask);
void   TxByteCounter_SetInterrupt(uint32 interruptMask);

void   TxByteCounter_WriteCounter(uint32 count);
uint32 TxByteCounter_ReadCounter(void);

uint32 TxByteCounter_ReadCapture(void);
uint32 TxByteCounter_ReadCaptureBuf(void);

void   TxByteCounter_WritePeriod(uint32 period);
uint32 TxByteCounter_ReadPeriod(void);
void   TxByteCounter_WritePeriodBuf(uint32 periodBuf);
uint32 TxByteCounter_ReadPeriodBuf(void);

void   TxByteCounter_WriteCompare(uint32 compare);
uint32 TxByteCounter_ReadCompare(void);
void   TxByteCounter_WriteCompareBuf(uint32 compareBuf);
uint32 TxByteCounter_ReadCompareBuf(void);

void   TxByteCounter_SetPeriodSwap(uint32 swapEnable);
void   TxByteCounter_SetCompareSwap(uint32 swapEnable);

void   TxByteCounter_SetCaptureMode(uint32 triggerMode);
void   TxByteCounter_SetReloadMode(uint32 triggerMode);
void   TxByteCounter_SetStartMode(uint32 triggerMode);
void   TxByteCounter_SetStopMode(uint32 triggerMode);
void   TxByteCounter_SetCountMode(uint32 triggerMode);

void   TxByteCounter_SaveConfig(void);
void   TxByteCounter_RestoreConfig(void);
void   TxByteCounter_Sleep(void);
void   TxByteCounter_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TxByteCounter_BLOCK_CONTROL_REG              (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TxByteCounter_BLOCK_CONTROL_PTR              ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TxByteCounter_COMMAND_REG                    (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TxByteCounter_COMMAND_PTR                    ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TxByteCounter_INTRRUPT_CAUSE_REG             (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TxByteCounter_INTRRUPT_CAUSE_PTR             ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TxByteCounter_CONTROL_REG                    (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__CTRL )
#define TxByteCounter_CONTROL_PTR                    ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__CTRL )
#define TxByteCounter_STATUS_REG                     (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__STATUS )
#define TxByteCounter_STATUS_PTR                     ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__STATUS )
#define TxByteCounter_COUNTER_REG                    (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__COUNTER )
#define TxByteCounter_COUNTER_PTR                    ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__COUNTER )
#define TxByteCounter_COMP_CAP_REG                   (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__CC )
#define TxByteCounter_COMP_CAP_PTR                   ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__CC )
#define TxByteCounter_COMP_CAP_BUF_REG               (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define TxByteCounter_COMP_CAP_BUF_PTR               ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__CC_BUFF )
#define TxByteCounter_PERIOD_REG                     (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__PERIOD )
#define TxByteCounter_PERIOD_PTR                     ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__PERIOD )
#define TxByteCounter_PERIOD_BUF_REG                 (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TxByteCounter_PERIOD_BUF_PTR                 ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TxByteCounter_TRIG_CONTROL0_REG              (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TxByteCounter_TRIG_CONTROL0_PTR              ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TxByteCounter_TRIG_CONTROL1_REG              (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TxByteCounter_TRIG_CONTROL1_PTR              ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TxByteCounter_TRIG_CONTROL2_REG              (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TxByteCounter_TRIG_CONTROL2_PTR              ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TxByteCounter_INTERRUPT_REQ_REG              (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR )
#define TxByteCounter_INTERRUPT_REQ_PTR              ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR )
#define TxByteCounter_INTERRUPT_SET_REG              (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR_SET )
#define TxByteCounter_INTERRUPT_SET_PTR              ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR_SET )
#define TxByteCounter_INTERRUPT_MASK_REG             (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define TxByteCounter_INTERRUPT_MASK_PTR             ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR_MASK )
#define TxByteCounter_INTERRUPT_MASKED_REG           (*(reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TxByteCounter_INTERRUPT_MASKED_PTR           ( (reg32 *) TxByteCounter_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TxByteCounter_MASK                           ((uint32)TxByteCounter_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TxByteCounter_RELOAD_CC_SHIFT                (0u)
#define TxByteCounter_RELOAD_PERIOD_SHIFT            (1u)
#define TxByteCounter_PWM_SYNC_KILL_SHIFT            (2u)
#define TxByteCounter_PWM_STOP_KILL_SHIFT            (3u)
#define TxByteCounter_PRESCALER_SHIFT                (8u)
#define TxByteCounter_UPDOWN_SHIFT                   (16u)
#define TxByteCounter_ONESHOT_SHIFT                  (18u)
#define TxByteCounter_QUAD_MODE_SHIFT                (20u)
#define TxByteCounter_INV_OUT_SHIFT                  (20u)
#define TxByteCounter_INV_COMPL_OUT_SHIFT            (21u)
#define TxByteCounter_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TxByteCounter_RELOAD_CC_MASK                 ((uint32)(TxByteCounter_1BIT_MASK        <<  \
                                                                            TxByteCounter_RELOAD_CC_SHIFT))
#define TxByteCounter_RELOAD_PERIOD_MASK             ((uint32)(TxByteCounter_1BIT_MASK        <<  \
                                                                            TxByteCounter_RELOAD_PERIOD_SHIFT))
#define TxByteCounter_PWM_SYNC_KILL_MASK             ((uint32)(TxByteCounter_1BIT_MASK        <<  \
                                                                            TxByteCounter_PWM_SYNC_KILL_SHIFT))
#define TxByteCounter_PWM_STOP_KILL_MASK             ((uint32)(TxByteCounter_1BIT_MASK        <<  \
                                                                            TxByteCounter_PWM_STOP_KILL_SHIFT))
#define TxByteCounter_PRESCALER_MASK                 ((uint32)(TxByteCounter_8BIT_MASK        <<  \
                                                                            TxByteCounter_PRESCALER_SHIFT))
#define TxByteCounter_UPDOWN_MASK                    ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                            TxByteCounter_UPDOWN_SHIFT))
#define TxByteCounter_ONESHOT_MASK                   ((uint32)(TxByteCounter_1BIT_MASK        <<  \
                                                                            TxByteCounter_ONESHOT_SHIFT))
#define TxByteCounter_QUAD_MODE_MASK                 ((uint32)(TxByteCounter_3BIT_MASK        <<  \
                                                                            TxByteCounter_QUAD_MODE_SHIFT))
#define TxByteCounter_INV_OUT_MASK                   ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                            TxByteCounter_INV_OUT_SHIFT))
#define TxByteCounter_MODE_MASK                      ((uint32)(TxByteCounter_3BIT_MASK        <<  \
                                                                            TxByteCounter_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TxByteCounter_CAPTURE_SHIFT                  (0u)
#define TxByteCounter_COUNT_SHIFT                    (2u)
#define TxByteCounter_RELOAD_SHIFT                   (4u)
#define TxByteCounter_STOP_SHIFT                     (6u)
#define TxByteCounter_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TxByteCounter_CAPTURE_MASK                   ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                  TxByteCounter_CAPTURE_SHIFT))
#define TxByteCounter_COUNT_MASK                     ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                  TxByteCounter_COUNT_SHIFT))
#define TxByteCounter_RELOAD_MASK                    ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                  TxByteCounter_RELOAD_SHIFT))
#define TxByteCounter_STOP_MASK                      ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                  TxByteCounter_STOP_SHIFT))
#define TxByteCounter_START_MASK                     ((uint32)(TxByteCounter_2BIT_MASK        <<  \
                                                                  TxByteCounter_START_SHIFT))

/* MASK */
#define TxByteCounter_1BIT_MASK                      ((uint32)0x01u)
#define TxByteCounter_2BIT_MASK                      ((uint32)0x03u)
#define TxByteCounter_3BIT_MASK                      ((uint32)0x07u)
#define TxByteCounter_6BIT_MASK                      ((uint32)0x3Fu)
#define TxByteCounter_8BIT_MASK                      ((uint32)0xFFu)
#define TxByteCounter_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TxByteCounter_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TxByteCounter_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TxByteCounter_QUAD_ENCODING_MODES     << TxByteCounter_QUAD_MODE_SHIFT))       |\
         ((uint32)(TxByteCounter_CONFIG                  << TxByteCounter_MODE_SHIFT)))

#define TxByteCounter_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TxByteCounter_PWM_STOP_EVENT          << TxByteCounter_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TxByteCounter_PWM_OUT_INVERT          << TxByteCounter_INV_OUT_SHIFT))         |\
         ((uint32)(TxByteCounter_PWM_OUT_N_INVERT        << TxByteCounter_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TxByteCounter_PWM_MODE                << TxByteCounter_MODE_SHIFT)))

#define TxByteCounter_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TxByteCounter_PWM_RUN_MODE         << TxByteCounter_ONESHOT_SHIFT))
            
#define TxByteCounter_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TxByteCounter_PWM_ALIGN            << TxByteCounter_UPDOWN_SHIFT))

#define TxByteCounter_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TxByteCounter_PWM_KILL_EVENT      << TxByteCounter_PWM_SYNC_KILL_SHIFT))

#define TxByteCounter_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TxByteCounter_PWM_DEAD_TIME_CYCLE  << TxByteCounter_PRESCALER_SHIFT))

#define TxByteCounter_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TxByteCounter_PWM_PRESCALER        << TxByteCounter_PRESCALER_SHIFT))

#define TxByteCounter_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TxByteCounter_TC_PRESCALER            << TxByteCounter_PRESCALER_SHIFT))       |\
         ((uint32)(TxByteCounter_TC_COUNTER_MODE         << TxByteCounter_UPDOWN_SHIFT))          |\
         ((uint32)(TxByteCounter_TC_RUN_MODE             << TxByteCounter_ONESHOT_SHIFT))         |\
         ((uint32)(TxByteCounter_TC_COMP_CAP_MODE        << TxByteCounter_MODE_SHIFT)))
        
#define TxByteCounter_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TxByteCounter_QUAD_PHIA_SIGNAL_MODE   << TxByteCounter_COUNT_SHIFT))           |\
         ((uint32)(TxByteCounter_QUAD_INDEX_SIGNAL_MODE  << TxByteCounter_RELOAD_SHIFT))          |\
         ((uint32)(TxByteCounter_QUAD_STOP_SIGNAL_MODE   << TxByteCounter_STOP_SHIFT))            |\
         ((uint32)(TxByteCounter_QUAD_PHIB_SIGNAL_MODE   << TxByteCounter_START_SHIFT)))

#define TxByteCounter_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TxByteCounter_PWM_SWITCH_SIGNAL_MODE  << TxByteCounter_CAPTURE_SHIFT))         |\
         ((uint32)(TxByteCounter_PWM_COUNT_SIGNAL_MODE   << TxByteCounter_COUNT_SHIFT))           |\
         ((uint32)(TxByteCounter_PWM_RELOAD_SIGNAL_MODE  << TxByteCounter_RELOAD_SHIFT))          |\
         ((uint32)(TxByteCounter_PWM_STOP_SIGNAL_MODE    << TxByteCounter_STOP_SHIFT))            |\
         ((uint32)(TxByteCounter_PWM_START_SIGNAL_MODE   << TxByteCounter_START_SHIFT)))

#define TxByteCounter_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TxByteCounter_TC_CAPTURE_SIGNAL_MODE  << TxByteCounter_CAPTURE_SHIFT))         |\
         ((uint32)(TxByteCounter_TC_COUNT_SIGNAL_MODE    << TxByteCounter_COUNT_SHIFT))           |\
         ((uint32)(TxByteCounter_TC_RELOAD_SIGNAL_MODE   << TxByteCounter_RELOAD_SHIFT))          |\
         ((uint32)(TxByteCounter_TC_STOP_SIGNAL_MODE     << TxByteCounter_STOP_SHIFT))            |\
         ((uint32)(TxByteCounter_TC_START_SIGNAL_MODE    << TxByteCounter_START_SHIFT)))
        
#define TxByteCounter_TIMER_UPDOWN_CNT_USED                                                          \
                ((TxByteCounter__COUNT_UPDOWN0 == TxByteCounter_TC_COUNTER_MODE)                  ||\
                 (TxByteCounter__COUNT_UPDOWN1 == TxByteCounter_TC_COUNTER_MODE))

#define TxByteCounter_PWM_UPDOWN_CNT_USED                                                            \
                ((TxByteCounter__CENTER == TxByteCounter_PWM_ALIGN)                               ||\
                 (TxByteCounter__ASYMMETRIC == TxByteCounter_PWM_ALIGN))               
        
#define TxByteCounter_PWM_PR_INIT_VALUE              (1u)
#define TxByteCounter_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TxByteCounter_H */

/* [] END OF FILE */
