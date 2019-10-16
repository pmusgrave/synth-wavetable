/*******************************************************************************
* File Name: SPIByteCounter.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the SPIByteCounter
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

#include "SPIByteCounter.h"

uint8 SPIByteCounter_initVar = 0u;


/*******************************************************************************
* Function Name: SPIByteCounter_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default SPIByteCounter configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (SPIByteCounter__QUAD == SPIByteCounter_CONFIG)
        SPIByteCounter_CONTROL_REG = SPIByteCounter_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SPIByteCounter_TRIG_CONTROL1_REG  = SPIByteCounter_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        SPIByteCounter_SetInterruptMode(SPIByteCounter_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        SPIByteCounter_SetCounterMode(SPIByteCounter_COUNT_DOWN);
        SPIByteCounter_WritePeriod(SPIByteCounter_QUAD_PERIOD_INIT_VALUE);
        SPIByteCounter_WriteCounter(SPIByteCounter_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (SPIByteCounter__QUAD == SPIByteCounter_CONFIG) */

    #if (SPIByteCounter__TIMER == SPIByteCounter_CONFIG)
        SPIByteCounter_CONTROL_REG = SPIByteCounter_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SPIByteCounter_TRIG_CONTROL1_REG  = SPIByteCounter_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SPIByteCounter_SetInterruptMode(SPIByteCounter_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        SPIByteCounter_WritePeriod(SPIByteCounter_TC_PERIOD_VALUE );

        #if (SPIByteCounter__COMPARE == SPIByteCounter_TC_COMP_CAP_MODE)
            SPIByteCounter_WriteCompare(SPIByteCounter_TC_COMPARE_VALUE);

            #if (1u == SPIByteCounter_TC_COMPARE_SWAP)
                SPIByteCounter_SetCompareSwap(1u);
                SPIByteCounter_WriteCompareBuf(SPIByteCounter_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == SPIByteCounter_TC_COMPARE_SWAP) */
        #endif  /* (SPIByteCounter__COMPARE == SPIByteCounter_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (SPIByteCounter_CY_TCPWM_V2 && SPIByteCounter_TIMER_UPDOWN_CNT_USED && !SPIByteCounter_CY_TCPWM_4000)
            SPIByteCounter_WriteCounter(1u);
        #elif(SPIByteCounter__COUNT_DOWN == SPIByteCounter_TC_COUNTER_MODE)
            SPIByteCounter_WriteCounter(SPIByteCounter_TC_PERIOD_VALUE);
        #else
            SPIByteCounter_WriteCounter(0u);
        #endif /* (SPIByteCounter_CY_TCPWM_V2 && SPIByteCounter_TIMER_UPDOWN_CNT_USED && !SPIByteCounter_CY_TCPWM_4000) */
    #endif  /* (SPIByteCounter__TIMER == SPIByteCounter_CONFIG) */

    #if (SPIByteCounter__PWM_SEL == SPIByteCounter_CONFIG)
        SPIByteCounter_CONTROL_REG = SPIByteCounter_CTRL_PWM_BASE_CONFIG;

        #if (SPIByteCounter__PWM_PR == SPIByteCounter_PWM_MODE)
            SPIByteCounter_CONTROL_REG |= SPIByteCounter_CTRL_PWM_RUN_MODE;
            SPIByteCounter_WriteCounter(SPIByteCounter_PWM_PR_INIT_VALUE);
        #else
            SPIByteCounter_CONTROL_REG |= SPIByteCounter_CTRL_PWM_ALIGN | SPIByteCounter_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (SPIByteCounter_CY_TCPWM_V2 && SPIByteCounter_PWM_UPDOWN_CNT_USED && !SPIByteCounter_CY_TCPWM_4000)
                SPIByteCounter_WriteCounter(1u);
            #elif (SPIByteCounter__RIGHT == SPIByteCounter_PWM_ALIGN)
                SPIByteCounter_WriteCounter(SPIByteCounter_PWM_PERIOD_VALUE);
            #else 
                SPIByteCounter_WriteCounter(0u);
            #endif  /* (SPIByteCounter_CY_TCPWM_V2 && SPIByteCounter_PWM_UPDOWN_CNT_USED && !SPIByteCounter_CY_TCPWM_4000) */
        #endif  /* (SPIByteCounter__PWM_PR == SPIByteCounter_PWM_MODE) */

        #if (SPIByteCounter__PWM_DT == SPIByteCounter_PWM_MODE)
            SPIByteCounter_CONTROL_REG |= SPIByteCounter_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (SPIByteCounter__PWM_DT == SPIByteCounter_PWM_MODE) */

        #if (SPIByteCounter__PWM == SPIByteCounter_PWM_MODE)
            SPIByteCounter_CONTROL_REG |= SPIByteCounter_CTRL_PWM_PRESCALER;
        #endif  /* (SPIByteCounter__PWM == SPIByteCounter_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        SPIByteCounter_TRIG_CONTROL1_REG  = SPIByteCounter_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SPIByteCounter_SetInterruptMode(SPIByteCounter_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (SPIByteCounter__PWM_PR == SPIByteCounter_PWM_MODE)
            SPIByteCounter_TRIG_CONTROL2_REG =
                    (SPIByteCounter_CC_MATCH_NO_CHANGE    |
                    SPIByteCounter_OVERLOW_NO_CHANGE      |
                    SPIByteCounter_UNDERFLOW_NO_CHANGE);
        #else
            #if (SPIByteCounter__LEFT == SPIByteCounter_PWM_ALIGN)
                SPIByteCounter_TRIG_CONTROL2_REG = SPIByteCounter_PWM_MODE_LEFT;
            #endif  /* ( SPIByteCounter_PWM_LEFT == SPIByteCounter_PWM_ALIGN) */

            #if (SPIByteCounter__RIGHT == SPIByteCounter_PWM_ALIGN)
                SPIByteCounter_TRIG_CONTROL2_REG = SPIByteCounter_PWM_MODE_RIGHT;
            #endif  /* ( SPIByteCounter_PWM_RIGHT == SPIByteCounter_PWM_ALIGN) */

            #if (SPIByteCounter__CENTER == SPIByteCounter_PWM_ALIGN)
                SPIByteCounter_TRIG_CONTROL2_REG = SPIByteCounter_PWM_MODE_CENTER;
            #endif  /* ( SPIByteCounter_PWM_CENTER == SPIByteCounter_PWM_ALIGN) */

            #if (SPIByteCounter__ASYMMETRIC == SPIByteCounter_PWM_ALIGN)
                SPIByteCounter_TRIG_CONTROL2_REG = SPIByteCounter_PWM_MODE_ASYM;
            #endif  /* (SPIByteCounter__ASYMMETRIC == SPIByteCounter_PWM_ALIGN) */
        #endif  /* (SPIByteCounter__PWM_PR == SPIByteCounter_PWM_MODE) */

        /* Set other values from customizer */
        SPIByteCounter_WritePeriod(SPIByteCounter_PWM_PERIOD_VALUE );
        SPIByteCounter_WriteCompare(SPIByteCounter_PWM_COMPARE_VALUE);

        #if (1u == SPIByteCounter_PWM_COMPARE_SWAP)
            SPIByteCounter_SetCompareSwap(1u);
            SPIByteCounter_WriteCompareBuf(SPIByteCounter_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == SPIByteCounter_PWM_COMPARE_SWAP) */

        #if (1u == SPIByteCounter_PWM_PERIOD_SWAP)
            SPIByteCounter_SetPeriodSwap(1u);
            SPIByteCounter_WritePeriodBuf(SPIByteCounter_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == SPIByteCounter_PWM_PERIOD_SWAP) */
    #endif  /* (SPIByteCounter__PWM_SEL == SPIByteCounter_CONFIG) */
    
}


/*******************************************************************************
* Function Name: SPIByteCounter_Enable
********************************************************************************
*
* Summary:
*  Enables the SPIByteCounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    SPIByteCounter_BLOCK_CONTROL_REG |= SPIByteCounter_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (SPIByteCounter__PWM_SEL == SPIByteCounter_CONFIG)
        #if (0u == SPIByteCounter_PWM_START_SIGNAL_PRESENT)
            SPIByteCounter_TriggerCommand(SPIByteCounter_MASK, SPIByteCounter_CMD_START);
        #endif /* (0u == SPIByteCounter_PWM_START_SIGNAL_PRESENT) */
    #endif /* (SPIByteCounter__PWM_SEL == SPIByteCounter_CONFIG) */

    #if (SPIByteCounter__TIMER == SPIByteCounter_CONFIG)
        #if (0u == SPIByteCounter_TC_START_SIGNAL_PRESENT)
            SPIByteCounter_TriggerCommand(SPIByteCounter_MASK, SPIByteCounter_CMD_START);
        #endif /* (0u == SPIByteCounter_TC_START_SIGNAL_PRESENT) */
    #endif /* (SPIByteCounter__TIMER == SPIByteCounter_CONFIG) */
    
    #if (SPIByteCounter__QUAD == SPIByteCounter_CONFIG)
        #if (0u != SPIByteCounter_QUAD_AUTO_START)
            SPIByteCounter_TriggerCommand(SPIByteCounter_MASK, SPIByteCounter_CMD_RELOAD);
        #endif /* (0u != SPIByteCounter_QUAD_AUTO_START) */
    #endif  /* (SPIByteCounter__QUAD == SPIByteCounter_CONFIG) */
}


/*******************************************************************************
* Function Name: SPIByteCounter_Start
********************************************************************************
*
* Summary:
*  Initializes the SPIByteCounter with default customizer
*  values when called the first time and enables the SPIByteCounter.
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
*  SPIByteCounter_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time SPIByteCounter_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the SPIByteCounter_Start() routine.
*
*******************************************************************************/
void SPIByteCounter_Start(void)
{
    if (0u == SPIByteCounter_initVar)
    {
        SPIByteCounter_Init();
        SPIByteCounter_initVar = 1u;
    }

    SPIByteCounter_Enable();
}


/*******************************************************************************
* Function Name: SPIByteCounter_Stop
********************************************************************************
*
* Summary:
*  Disables the SPIByteCounter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_BLOCK_CONTROL_REG &= (uint32)~SPIByteCounter_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the SPIByteCounter. This function is used when
*  configured as a generic SPIByteCounter and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the SPIByteCounter to operate in
*   Values:
*   - SPIByteCounter_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - SPIByteCounter_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - SPIByteCounter_MODE_QUAD - Quadrature decoder
*         - SPIByteCounter_MODE_PWM - PWM
*         - SPIByteCounter_MODE_PWM_DT - PWM with dead time
*         - SPIByteCounter_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_MODE_MASK;
    SPIByteCounter_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - SPIByteCounter_MODE_X1 - Counts on phi 1 rising
*         - SPIByteCounter_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - SPIByteCounter_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_QUAD_MODE_MASK;
    SPIByteCounter_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - SPIByteCounter_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - SPIByteCounter_PRESCALE_DIVBY2    - Divide by 2
*         - SPIByteCounter_PRESCALE_DIVBY4    - Divide by 4
*         - SPIByteCounter_PRESCALE_DIVBY8    - Divide by 8
*         - SPIByteCounter_PRESCALE_DIVBY16   - Divide by 16
*         - SPIByteCounter_PRESCALE_DIVBY32   - Divide by 32
*         - SPIByteCounter_PRESCALE_DIVBY64   - Divide by 64
*         - SPIByteCounter_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_PRESCALER_MASK;
    SPIByteCounter_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the SPIByteCounter runs
*  continuously or stops when terminal count is reached.  By default the
*  SPIByteCounter operates in the continuous mode.
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
void SPIByteCounter_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_ONESHOT_MASK;
    SPIByteCounter_CONTROL_REG |= ((uint32)((oneShotEnable & SPIByteCounter_1BIT_MASK) <<
                                                               SPIByteCounter_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetPWMMode
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
void SPIByteCounter_SetPWMMode(uint32 modeMask)
{
    SPIByteCounter_TRIG_CONTROL2_REG = (modeMask & SPIByteCounter_6BIT_MASK);
}



/*******************************************************************************
* Function Name: SPIByteCounter_SetPWMSyncKill
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
void SPIByteCounter_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_PWM_SYNC_KILL_MASK;
    SPIByteCounter_CONTROL_REG |= ((uint32)((syncKillEnable & SPIByteCounter_1BIT_MASK)  <<
                                               SPIByteCounter_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetPWMStopOnKill
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
void SPIByteCounter_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_PWM_STOP_KILL_MASK;
    SPIByteCounter_CONTROL_REG |= ((uint32)((stopOnKillEnable & SPIByteCounter_1BIT_MASK)  <<
                                                         SPIByteCounter_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetPWMDeadTime
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
void SPIByteCounter_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_PRESCALER_MASK;
    SPIByteCounter_CONTROL_REG |= ((uint32)((deadTime & SPIByteCounter_8BIT_MASK) <<
                                                          SPIByteCounter_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetPWMInvert
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
*         - SPIByteCounter_INVERT_LINE   - Inverts the line output
*         - SPIByteCounter_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_INV_OUT_MASK;
    SPIByteCounter_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: SPIByteCounter_WriteCounter
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
void SPIByteCounter_WriteCounter(uint32 count)
{
    SPIByteCounter_COUNTER_REG = (count & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadCounter
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
uint32 SPIByteCounter_ReadCounter(void)
{
    return (SPIByteCounter_COUNTER_REG & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - SPIByteCounter_COUNT_UP       - Counts up
*     - SPIByteCounter_COUNT_DOWN     - Counts down
*     - SPIByteCounter_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - SPIByteCounter_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_UPDOWN_MASK;
    SPIByteCounter_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_WritePeriod
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
void SPIByteCounter_WritePeriod(uint32 period)
{
    SPIByteCounter_PERIOD_REG = (period & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadPeriod
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
uint32 SPIByteCounter_ReadPeriod(void)
{
    return (SPIByteCounter_PERIOD_REG & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetCompareSwap
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
void SPIByteCounter_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_RELOAD_CC_MASK;
    SPIByteCounter_CONTROL_REG |= (swapEnable & SPIByteCounter_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_WritePeriodBuf
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
void SPIByteCounter_WritePeriodBuf(uint32 periodBuf)
{
    SPIByteCounter_PERIOD_BUF_REG = (periodBuf & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadPeriodBuf
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
uint32 SPIByteCounter_ReadPeriodBuf(void)
{
    return (SPIByteCounter_PERIOD_BUF_REG & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetPeriodSwap
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
void SPIByteCounter_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_CONTROL_REG &= (uint32)~SPIByteCounter_RELOAD_PERIOD_MASK;
    SPIByteCounter_CONTROL_REG |= ((uint32)((swapEnable & SPIByteCounter_1BIT_MASK) <<
                                                            SPIByteCounter_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_WriteCompare
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
void SPIByteCounter_WriteCompare(uint32 compare)
{
    #if (SPIByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */

    #if (SPIByteCounter_CY_TCPWM_4000)
        currentMode = ((SPIByteCounter_CONTROL_REG & SPIByteCounter_UPDOWN_MASK) >> SPIByteCounter_UPDOWN_SHIFT);

        if (((uint32)SPIByteCounter__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)SPIByteCounter__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */
    
    SPIByteCounter_COMP_CAP_REG = (compare & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadCompare
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
uint32 SPIByteCounter_ReadCompare(void)
{
    #if (SPIByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */

    #if (SPIByteCounter_CY_TCPWM_4000)
        currentMode = ((SPIByteCounter_CONTROL_REG & SPIByteCounter_UPDOWN_MASK) >> SPIByteCounter_UPDOWN_SHIFT);
        
        regVal = SPIByteCounter_COMP_CAP_REG;
        
        if (((uint32)SPIByteCounter__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SPIByteCounter__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SPIByteCounter_16BIT_MASK);
    #else
        return (SPIByteCounter_COMP_CAP_REG & SPIByteCounter_16BIT_MASK);
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SPIByteCounter_WriteCompareBuf
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
void SPIByteCounter_WriteCompareBuf(uint32 compareBuf)
{
    #if (SPIByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */

    #if (SPIByteCounter_CY_TCPWM_4000)
        currentMode = ((SPIByteCounter_CONTROL_REG & SPIByteCounter_UPDOWN_MASK) >> SPIByteCounter_UPDOWN_SHIFT);

        if (((uint32)SPIByteCounter__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)SPIByteCounter__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */
    
    SPIByteCounter_COMP_CAP_BUF_REG = (compareBuf & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadCompareBuf
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
uint32 SPIByteCounter_ReadCompareBuf(void)
{
    #if (SPIByteCounter_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */

    #if (SPIByteCounter_CY_TCPWM_4000)
        currentMode = ((SPIByteCounter_CONTROL_REG & SPIByteCounter_UPDOWN_MASK) >> SPIByteCounter_UPDOWN_SHIFT);

        regVal = SPIByteCounter_COMP_CAP_BUF_REG;
        
        if (((uint32)SPIByteCounter__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SPIByteCounter__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SPIByteCounter_16BIT_MASK);
    #else
        return (SPIByteCounter_COMP_CAP_BUF_REG & SPIByteCounter_16BIT_MASK);
    #endif /* (SPIByteCounter_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadCapture
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
uint32 SPIByteCounter_ReadCapture(void)
{
    return (SPIByteCounter_COMP_CAP_REG & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadCaptureBuf
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
uint32 SPIByteCounter_ReadCaptureBuf(void)
{
    return (SPIByteCounter_COMP_CAP_BUF_REG & SPIByteCounter_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetCaptureMode
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
*     - SPIByteCounter_TRIG_LEVEL     - Level
*     - SPIByteCounter_TRIG_RISING    - Rising edge
*     - SPIByteCounter_TRIG_FALLING   - Falling edge
*     - SPIByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_TRIG_CONTROL1_REG &= (uint32)~SPIByteCounter_CAPTURE_MASK;
    SPIByteCounter_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SPIByteCounter_TRIG_LEVEL     - Level
*     - SPIByteCounter_TRIG_RISING    - Rising edge
*     - SPIByteCounter_TRIG_FALLING   - Falling edge
*     - SPIByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_TRIG_CONTROL1_REG &= (uint32)~SPIByteCounter_RELOAD_MASK;
    SPIByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SPIByteCounter_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SPIByteCounter_TRIG_LEVEL     - Level
*     - SPIByteCounter_TRIG_RISING    - Rising edge
*     - SPIByteCounter_TRIG_FALLING   - Falling edge
*     - SPIByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_TRIG_CONTROL1_REG &= (uint32)~SPIByteCounter_START_MASK;
    SPIByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SPIByteCounter_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SPIByteCounter_TRIG_LEVEL     - Level
*     - SPIByteCounter_TRIG_RISING    - Rising edge
*     - SPIByteCounter_TRIG_FALLING   - Falling edge
*     - SPIByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_TRIG_CONTROL1_REG &= (uint32)~SPIByteCounter_STOP_MASK;
    SPIByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SPIByteCounter_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SPIByteCounter_TRIG_LEVEL     - Level
*     - SPIByteCounter_TRIG_RISING    - Rising edge
*     - SPIByteCounter_TRIG_FALLING   - Falling edge
*     - SPIByteCounter_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_TRIG_CONTROL1_REG &= (uint32)~SPIByteCounter_COUNT_MASK;
    SPIByteCounter_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SPIByteCounter_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_TriggerCommand
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
*     - SPIByteCounter_CMD_CAPTURE    - Trigger Capture/Switch command
*     - SPIByteCounter_CMD_RELOAD     - Trigger Reload/Index command
*     - SPIByteCounter_CMD_STOP       - Trigger Stop/Kill command
*     - SPIByteCounter_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SPIByteCounter_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the SPIByteCounter.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - SPIByteCounter_STATUS_DOWN    - Set if counting down
*     - SPIByteCounter_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 SPIByteCounter_ReadStatus(void)
{
    return ((SPIByteCounter_STATUS_REG >> SPIByteCounter_RUNNING_STATUS_SHIFT) |
            (SPIByteCounter_STATUS_REG & SPIByteCounter_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - SPIByteCounter_INTR_MASK_TC       - Terminal count mask
*     - SPIByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetInterruptMode(uint32 interruptMask)
{
    SPIByteCounter_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: SPIByteCounter_GetInterruptSourceMasked
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
*     - SPIByteCounter_INTR_MASK_TC       - Terminal count mask
*     - SPIByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SPIByteCounter_GetInterruptSourceMasked(void)
{
    return (SPIByteCounter_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: SPIByteCounter_GetInterruptSource
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
*     - SPIByteCounter_INTR_MASK_TC       - Terminal count mask
*     - SPIByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SPIByteCounter_GetInterruptSource(void)
{
    return (SPIByteCounter_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: SPIByteCounter_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - SPIByteCounter_INTR_MASK_TC       - Terminal count mask
*     - SPIByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_ClearInterrupt(uint32 interruptMask)
{
    SPIByteCounter_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: SPIByteCounter_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - SPIByteCounter_INTR_MASK_TC       - Terminal count mask
*     - SPIByteCounter_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SetInterrupt(uint32 interruptMask)
{
    SPIByteCounter_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
