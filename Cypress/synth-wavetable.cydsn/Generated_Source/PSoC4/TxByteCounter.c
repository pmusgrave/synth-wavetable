/*******************************************************************************
* File Name: TxByteCounter.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the TxByteCounter
*  component
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

#include "TxByteCounter.h"

uint8 TxByteCounter_initVar = 0u;


/*******************************************************************************
* Function Name: TxByteCounter_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TxByteCounter configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TxByteCounter__QUAD == TxByteCounter_CONFIG)
        TxByteCounter_CONTROL_REG = TxByteCounter_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TxByteCounter_TRIG_CONTROL1_REG  = TxByteCounter_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TxByteCounter_SetInterruptMode(TxByteCounter_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TxByteCounter_SetCounterMode(TxByteCounter_COUNT_DOWN);
        TxByteCounter_WritePeriod(TxByteCounter_QUAD_PERIOD_INIT_VALUE);
        TxByteCounter_WriteCounter(TxByteCounter_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TxByteCounter__QUAD == TxByteCounter_CONFIG) */

    #if (TxByteCounter__TIMER == TxByteCounter_CONFIG)
        TxByteCounter_CONTROL_REG = TxByteCounter_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TxByteCounter_TRIG_CONTROL1_REG  = TxByteCounter_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TxByteCounter_SetInterruptMode(TxByteCounter_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TxByteCounter_WritePeriod(TxByteCounter_TC_PERIOD_VALUE );

        #if (TxByteCounter__COMPARE == TxByteCounter_TC_COMP_CAP_MODE)
            TxByteCounter_WriteCompare(TxByteCounter_TC_COMPARE_VALUE);

            #if (1u == TxByteCounter_TC_COMPARE_SWAP)
                TxByteCounter_SetCompareSwap(1u);
                TxByteCounter_WriteCompareBuf(TxByteCounter_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TxByteCounter_TC_COMPARE_SWAP) */
        #endif  /* (TxByteCounter__COMPARE == TxByteCounter_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TxByteCounter_CY_TCPWM_V2 && TxByteCounter_TIMER_UPDOWN_CNT_USED && !TxByteCounter_CY_TCPWM_4000)
            TxByteCounter_WriteCounter(1u);
        #elif(TxByteCounter__COUNT_DOWN == TxByteCounter_TC_COUNTER_MODE)
            TxByteCounter_WriteCounter(TxByteCounter_TC_PERIOD_VALUE);
        #else
            TxByteCounter_WriteCounter(0u);
        #endif /* (TxByteCounter_CY_TCPWM_V2 && TxByteCounter_TIMER_UPDOWN_CNT_USED && !TxByteCounter_CY_TCPWM_4000) */
    #endif  /* (TxByteCounter__TIMER == TxByteCounter_CONFIG) */

    #if (TxByteCounter__PWM_SEL == TxByteCounter_CONFIG)
        TxByteCounter_CONTROL_REG = TxByteCounter_CTRL_PWM_BASE_CONFIG;

        #if (TxByteCounter__PWM_PR == TxByteCounter_PWM_MODE)
            TxByteCounter_CONTROL_REG |= TxByteCounter_CTRL_PWM_RUN_MODE;
            TxByteCounter_WriteCounter(TxByteCounter_PWM_PR_INIT_VALUE);
        #else
            TxByteCounter_CONTROL_REG |= TxByteCounter_CTRL_PWM_ALIGN | TxByteCounter_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TxByteCounter_CY_TCPWM_V2 && TxByteCounter_PWM_UPDOWN_CNT_USED && !TxByteCounter_CY_TCPWM_4000)
                TxByteCounter_WriteCounter(1u);
            #elif (TxByteCounter__RIGHT == TxByteCounter_PWM_ALIGN)
                TxByteCounter_WriteCounter(TxByteCounter_PWM_PERIOD_VALUE);
            #else 
                TxByteCounter_WriteCounter(0u);
            #endif  /* (TxByteCounter_CY_TCPWM_V2 && TxByteCounter_PWM_UPDOWN_CNT_USED && !TxByteCounter_CY_TCPWM_4000) */
        #endif  /* (TxByteCounter__PWM_PR == TxByteCounter_PWM_MODE) */

        #if (TxByteCounter__PWM_DT == TxByteCounter_PWM_MODE)
            TxByteCounter_CONTROL_REG |= TxByteCounter_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TxByteCounter__PWM_DT == TxByteCounter_PWM_MODE) */

        #if (TxByteCounter__PWM == TxByteCounter_PWM_MODE)
            TxByteCounter_CONTROL_REG |= TxByteCounter_CTRL_PWM_PRESCALER;
        #endif  /* (TxByteCounter__PWM == TxByteCounter_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TxByteCounter_TRIG_CONTROL1_REG  = TxByteCounter_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TxByteCounter_SetInterruptMode(TxByteCounter_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TxByteCounter__PWM_PR == TxByteCounter_PWM_MODE)
            TxByteCounter_TRIG_CONTROL2_REG =
                    (TxByteCounter_CC_MATCH_NO_CHANGE    |
                    TxByteCounter_OVERLOW_NO_CHANGE      |
                    TxByteCounter_UNDERFLOW_NO_CHANGE);
        #else
            #if (TxByteCounter__LEFT == TxByteCounter_PWM_ALIGN)
                TxByteCounter_TRIG_CONTROL2_REG = TxByteCounter_PWM_MODE_LEFT;
            #endif  /* ( TxByteCounter_PWM_LEFT == TxByteCounter_PWM_ALIGN) */

            #if (TxByteCounter__RIGHT == TxByteCounter_PWM_ALIGN)
                TxByteCounter_TRIG_CONTROL2_REG = TxByteCounter_PWM_MODE_RIGHT;
            #endif  /* ( TxByteCounter_PWM_RIGHT == TxByteCounter_PWM_ALIGN) */

            #if (TxByteCounter__CENTER == TxByteCounter_PWM_ALIGN)
                TxByteCounter_TRIG_CONTROL2_REG = TxByteCounter_PWM_MODE_CENTER;
            #endif  /* ( TxByteCounter_PWM_CENTER == TxByteCounter_PWM_ALIGN) */

            #if (TxByteCounter__ASYMMETRIC == TxByteCounter_PWM_ALIGN)
                TxByteCounter_TRIG_CONTROL2_REG = TxByteCounter_PWM_MODE_ASYM;
            #endif  /* (TxByteCounter__ASYMMETRIC == TxByteCounter_PWM_ALIGN) */
        #endif  /* (TxByteCounter__PWM_PR == TxByteCounter_PWM_MODE) */

        /* Set other values from customizer */
        TxByteCounter_WritePeriod(TxByteCounter_PWM_PERIOD_VALUE );
        TxByteCounter_WriteCompare(TxByteCounter_PWM_COMPARE_VALUE);

        #if (1u == TxByteCounter_PWM_COMPARE_SWAP)
            TxByteCounter_SetCompareSwap(1u);
            TxByteCounter_WriteCompareBuf(TxByteCounter_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TxByteCounter_PWM_COMPARE_SWAP) */

        #if (1u == TxByteCounter_PWM_PERIOD_SWAP)
            TxByteCounter_SetPeriodSwap(1u);
            TxByteCounter_WritePeriodBuf(TxByteCounter_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TxByteCounter_PWM_PERIOD_SWAP) */
    #endif  /* (TxByteCounter__PWM_SEL == TxByteCounter_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TxByteCounter_Enable
********************************************************************************
*
* Summary:
*  Enables the TxByteCounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TxByteCounter_BLOCK_CONTROL_REG |= TxByteCounter_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TxByteCounter__PWM_SEL == TxByteCounter_CONFIG)
        #if (0u == TxByteCounter_PWM_START_SIGNAL_PRESENT)
            TxByteCounter_TriggerCommand(TxByteCounter_MASK, TxByteCounter_CMD_START);
        #endif /* (0u == TxByteCounter_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TxByteCounter__PWM_SEL == TxByteCounter_CONFIG) */

    #if (TxByteCounter__TIMER == TxByteCounter_CONFIG)
        #if (0u == TxByteCounter_TC_START_SIGNAL_PRESENT)
            TxByteCounter_TriggerCommand(TxByteCounter_MASK, TxByteCounter_CMD_START);
        #endif /* (0u == TxByteCounter_TC_START_SIGNAL_PRESENT) */
    #endif /* (TxByteCounter__TIMER == TxByteCounter_CONFIG) */
    
    #if (TxByteCounter__QUAD == TxByteCounter_CONFIG)
        #if (0u != TxByteCounter_QUAD_AUTO_START)
            TxByteCounter_TriggerCommand(TxByteCounter_MASK, TxByteCounter_CMD_RELOAD);
        #endif /* (0u != TxByteCounter_QUAD_AUTO_START) */
    #endif  /* (TxByteCounter__QUAD == TxByteCounter_CONFIG) */
}


/*******************************************************************************
* Function Name: TxByteCounter_Start
********************************************************************************
*
* Summary:
*  Initializes the TxByteCounter with default customizer
*  values when called the first time and enables the TxByteCounter.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TxByteCounter_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TxByteCounter_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TxByteCounter_Start() routine.
*
*******************************************************************************/
void TxByteCounter_Start(void)
{
    if (0u == TxByteCounter_initVar)
    {
        TxByteCounter_Init();
        TxByteCounter_initVar = 1u;
    }

    TxByteCounter_Enable();
}


/*******************************************************************************
* Function Name: TxByteCounter_Stop
********************************************************************************
*
* Summary:
*  Disables the TxByteCounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_BLOCK_CONTROL_REG &= (uint32)~TxByteCounter_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TxByteCounter. This function is used when
*  configured as a generic TxByteCounter and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TxByteCounter to operate in
*   Values:
*   - TxByteCounter_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TxByteCounter_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TxByteCounter_MODE_QUAD - Quadrature decoder
*         - TxByteCounter_MODE_PWM - PWM
*         - TxByteCounter_MODE_PWM_DT - PWM with dead time
*         - TxByteCounter_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_MODE_MASK;
    TxByteCounter_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TxByteCounter_MODE_X1 - Counts on phi 1 rising
*         - TxByteCounter_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TxByteCounter_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_QUAD_MODE_MASK;
    TxByteCounter_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TxByteCounter_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TxByteCounter_PRESCALE_DIVBY2    - Divide by 2
*         - TxByteCounter_PRESCALE_DIVBY4    - Divide by 4
*         - TxByteCounter_PRESCALE_DIVBY8    - Divide by 8
*         - TxByteCounter_PRESCALE_DIVBY16   - Divide by 16
*         - TxByteCounter_PRESCALE_DIVBY32   - Divide by 32
*         - TxByteCounter_PRESCALE_DIVBY64   - Divide by 64
*         - TxByteCounter_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_PRESCALER_MASK;
    TxByteCounter_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TxByteCounter runs
*  continuously or stops when terminal count is reached.  By default the
*  TxByteCounter operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_ONESHOT_MASK;
    TxByteCounter_CONTROL_REG |= ((uint32)((oneShotEnable & TxByteCounter_1BIT_MASK) <<
                                                               TxByteCounter_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPWMMode(uint32 modeMask)
{
    TxByteCounter_TRIG_CONTROL2_REG = (modeMask & TxByteCounter_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TxByteCounter_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_PWM_SYNC_KILL_MASK;
    TxByteCounter_CONTROL_REG |= ((uint32)((syncKillEnable & TxByteCounter_1BIT_MASK)  <<
                                               TxByteCounter_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_PWM_STOP_KILL_MASK;
    TxByteCounter_CONTROL_REG |= ((uint32)((stopOnKillEnable & TxByteCounter_1BIT_MASK)  <<
                                                         TxByteCounter_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_PRESCALER_MASK;
    TxByteCounter_CONTROL_REG |= ((uint32)((deadTime & TxByteCounter_8BIT_MASK) <<
                                                          TxByteCounter_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - TxByteCounter_INVERT_LINE   - Inverts the line output
*         - TxByteCounter_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_INV_OUT_MASK;
    TxByteCounter_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TxByteCounter_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_WriteCounter(uint32 count)
{
    TxByteCounter_COUNTER_REG = (count & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 TxByteCounter_ReadCounter(void)
{
    return (TxByteCounter_COUNTER_REG & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TxByteCounter_COUNT_UP       - Counts up
*     - TxByteCounter_COUNT_DOWN     - Counts down
*     - TxByteCounter_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TxByteCounter_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_UPDOWN_MASK;
    TxByteCounter_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_WritePeriod(uint32 period)
{
    TxByteCounter_PERIOD_REG = (period & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 TxByteCounter_ReadPeriod(void)
{
    return (TxByteCounter_PERIOD_REG & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_RELOAD_CC_MASK;
    TxByteCounter_CONTROL_REG |= (swapEnable & TxByteCounter_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_WritePeriodBuf(uint32 periodBuf)
{
    TxByteCounter_PERIOD_BUF_REG = (periodBuf & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 TxByteCounter_ReadPeriodBuf(void)
{
    return (TxByteCounter_PERIOD_BUF_REG & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_CONTROL_REG &= (uint32)~TxByteCounter_RELOAD_PERIOD_MASK;
    TxByteCounter_CONTROL_REG |= ((uint32)((swapEnable & TxByteCounter_1BIT_MASK) <<
                                                            TxByteCounter_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void TxByteCounter_WriteCompare(uint32 compare)
{
    #if (TxByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TxByteCounter_CY_TCPWM_4000) */

    #if (TxByteCounter_CY_TCPWM_4000)
        currentMode = ((TxByteCounter_CONTROL_REG & TxByteCounter_UPDOWN_MASK) >> TxByteCounter_UPDOWN_SHIFT);

        if (((uint32)TxByteCounter__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TxByteCounter__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TxByteCounter_CY_TCPWM_4000) */
    
    TxByteCounter_COMP_CAP_REG = (compare & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 TxByteCounter_ReadCompare(void)
{
    #if (TxByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TxByteCounter_CY_TCPWM_4000) */

    #if (TxByteCounter_CY_TCPWM_4000)
        currentMode = ((TxByteCounter_CONTROL_REG & TxByteCounter_UPDOWN_MASK) >> TxByteCounter_UPDOWN_SHIFT);
        
        regVal = TxByteCounter_COMP_CAP_REG;
        
        if (((uint32)TxByteCounter__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TxByteCounter__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TxByteCounter_16BIT_MASK);
    #else
        return (TxByteCounter_COMP_CAP_REG & TxByteCounter_16BIT_MASK);
    #endif /* (TxByteCounter_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TxByteCounter_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void TxByteCounter_WriteCompareBuf(uint32 compareBuf)
{
    #if (TxByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TxByteCounter_CY_TCPWM_4000) */

    #if (TxByteCounter_CY_TCPWM_4000)
        currentMode = ((TxByteCounter_CONTROL_REG & TxByteCounter_UPDOWN_MASK) >> TxByteCounter_UPDOWN_SHIFT);

        if (((uint32)TxByteCounter__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TxByteCounter__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TxByteCounter_CY_TCPWM_4000) */
    
    TxByteCounter_COMP_CAP_BUF_REG = (compareBuf & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 TxByteCounter_ReadCompareBuf(void)
{
    #if (TxByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TxByteCounter_CY_TCPWM_4000) */

    #if (TxByteCounter_CY_TCPWM_4000)
        currentMode = ((TxByteCounter_CONTROL_REG & TxByteCounter_UPDOWN_MASK) >> TxByteCounter_UPDOWN_SHIFT);

        regVal = TxByteCounter_COMP_CAP_BUF_REG;
        
        if (((uint32)TxByteCounter__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TxByteCounter__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TxByteCounter_16BIT_MASK);
    #else
        return (TxByteCounter_COMP_CAP_BUF_REG & TxByteCounter_16BIT_MASK);
    #endif /* (TxByteCounter_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 TxByteCounter_ReadCapture(void)
{
    return (TxByteCounter_COMP_CAP_REG & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 TxByteCounter_ReadCaptureBuf(void)
{
    return (TxByteCounter_COMP_CAP_BUF_REG & TxByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TxByteCounter_TRIG_LEVEL     - Level
*     - TxByteCounter_TRIG_RISING    - Rising edge
*     - TxByteCounter_TRIG_FALLING   - Falling edge
*     - TxByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_TRIG_CONTROL1_REG &= (uint32)~TxByteCounter_CAPTURE_MASK;
    TxByteCounter_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TxByteCounter_TRIG_LEVEL     - Level
*     - TxByteCounter_TRIG_RISING    - Rising edge
*     - TxByteCounter_TRIG_FALLING   - Falling edge
*     - TxByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_TRIG_CONTROL1_REG &= (uint32)~TxByteCounter_RELOAD_MASK;
    TxByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TxByteCounter_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TxByteCounter_TRIG_LEVEL     - Level
*     - TxByteCounter_TRIG_RISING    - Rising edge
*     - TxByteCounter_TRIG_FALLING   - Falling edge
*     - TxByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_TRIG_CONTROL1_REG &= (uint32)~TxByteCounter_START_MASK;
    TxByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TxByteCounter_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TxByteCounter_TRIG_LEVEL     - Level
*     - TxByteCounter_TRIG_RISING    - Rising edge
*     - TxByteCounter_TRIG_FALLING   - Falling edge
*     - TxByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_TRIG_CONTROL1_REG &= (uint32)~TxByteCounter_STOP_MASK;
    TxByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TxByteCounter_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TxByteCounter_TRIG_LEVEL     - Level
*     - TxByteCounter_TRIG_RISING    - Rising edge
*     - TxByteCounter_TRIG_FALLING   - Falling edge
*     - TxByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_TRIG_CONTROL1_REG &= (uint32)~TxByteCounter_COUNT_MASK;
    TxByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TxByteCounter_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - TxByteCounter_CMD_CAPTURE    - Trigger Capture/Switch command
*     - TxByteCounter_CMD_RELOAD     - Trigger Reload/Index command
*     - TxByteCounter_CMD_STOP       - Trigger Stop/Kill command
*     - TxByteCounter_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TxByteCounter_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TxByteCounter_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TxByteCounter.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TxByteCounter_STATUS_DOWN    - Set if counting down
*     - TxByteCounter_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TxByteCounter_ReadStatus(void)
{
    return ((TxByteCounter_STATUS_REG >> TxByteCounter_RUNNING_STATUS_SHIFT) |
            (TxByteCounter_STATUS_REG & TxByteCounter_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TxByteCounter_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TxByteCounter_INTR_MASK_TC       - Terminal count mask
*     - TxByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetInterruptMode(uint32 interruptMask)
{
    TxByteCounter_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TxByteCounter_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - TxByteCounter_INTR_MASK_TC       - Terminal count mask
*     - TxByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TxByteCounter_GetInterruptSourceMasked(void)
{
    return (TxByteCounter_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TxByteCounter_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - TxByteCounter_INTR_MASK_TC       - Terminal count mask
*     - TxByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TxByteCounter_GetInterruptSource(void)
{
    return (TxByteCounter_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TxByteCounter_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TxByteCounter_INTR_MASK_TC       - Terminal count mask
*     - TxByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_ClearInterrupt(uint32 interruptMask)
{
    TxByteCounter_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TxByteCounter_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TxByteCounter_INTR_MASK_TC       - Terminal count mask
*     - TxByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TxByteCounter_SetInterrupt(uint32 interruptMask)
{
    TxByteCounter_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
