/*******************************************************************************
* File Name: CodecI2CM_SCBCLK.c
* Version 2.20
*
*  Description:
*   Provides system API for the clocking, interrupts and watchdog timer.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <cydevice_trm.h>
#include "CodecI2CM_SCBCLK.h"

#if defined CYREG_PERI_DIV_CMD

/*******************************************************************************
* Function Name: CodecI2CM_SCBCLK_StartEx
********************************************************************************
*
* Summary:
*  Starts the clock, aligned to the specified running clock.
*
* Parameters:
*  alignClkDiv:  The divider to which phase alignment is performed when the
*    clock is started.
*
* Returns:
*  None
*
*******************************************************************************/
void CodecI2CM_SCBCLK_StartEx(uint32 alignClkDiv)
{
    /* Make sure any previous start command has finished. */
    while((CodecI2CM_SCBCLK_CMD_REG & CodecI2CM_SCBCLK_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and enable. */
    CodecI2CM_SCBCLK_CMD_REG =
        ((uint32)CodecI2CM_SCBCLK__DIV_ID << CodecI2CM_SCBCLK_CMD_DIV_SHIFT)|
        (alignClkDiv << CodecI2CM_SCBCLK_CMD_PA_DIV_SHIFT) |
        (uint32)CodecI2CM_SCBCLK_CMD_ENABLE_MASK;
}

#else

/*******************************************************************************
* Function Name: CodecI2CM_SCBCLK_Start
********************************************************************************
*
* Summary:
*  Starts the clock.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/

void CodecI2CM_SCBCLK_Start(void)
{
    /* Set the bit to enable the clock. */
    CodecI2CM_SCBCLK_ENABLE_REG |= CodecI2CM_SCBCLK__ENABLE_MASK;
}

#endif /* CYREG_PERI_DIV_CMD */


/*******************************************************************************
* Function Name: CodecI2CM_SCBCLK_Stop
********************************************************************************
*
* Summary:
*  Stops the clock and returns immediately. This API does not require the
*  source clock to be running but may return before the hardware is actually
*  disabled.
*
* Parameters:
*  None
*
* Returns:
*  None
*
*******************************************************************************/
void CodecI2CM_SCBCLK_Stop(void)
{
#if defined CYREG_PERI_DIV_CMD

    /* Make sure any previous start command has finished. */
    while((CodecI2CM_SCBCLK_CMD_REG & CodecI2CM_SCBCLK_CMD_ENABLE_MASK) != 0u)
    {
    }
    
    /* Specify the target divider and it's alignment divider, and disable. */
    CodecI2CM_SCBCLK_CMD_REG =
        ((uint32)CodecI2CM_SCBCLK__DIV_ID << CodecI2CM_SCBCLK_CMD_DIV_SHIFT)|
        ((uint32)CodecI2CM_SCBCLK_CMD_DISABLE_MASK);

#else

    /* Clear the bit to disable the clock. */
    CodecI2CM_SCBCLK_ENABLE_REG &= (uint32)(~CodecI2CM_SCBCLK__ENABLE_MASK);
    
#endif /* CYREG_PERI_DIV_CMD */
}


/*******************************************************************************
* Function Name: CodecI2CM_SCBCLK_SetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Modifies the clock divider and the fractional divider.
*
* Parameters:
*  clkDivider:  Divider register value (0-65535). This value is NOT the
*    divider; the clock hardware divides by clkDivider plus one. For example,
*    to divide the clock by 2, this parameter should be set to 1.
*  fracDivider:  Fractional Divider register value (0-31).
* Returns:
*  None
*
*******************************************************************************/
void CodecI2CM_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional)
{
    uint32 maskVal;
    uint32 regVal;
    
#if defined (CodecI2CM_SCBCLK__FRAC_MASK) || defined (CYREG_PERI_DIV_CMD)
    
	/* get all but divider bits */
    maskVal = CodecI2CM_SCBCLK_DIV_REG & 
                    (uint32)(~(uint32)(CodecI2CM_SCBCLK_DIV_INT_MASK | CodecI2CM_SCBCLK_DIV_FRAC_MASK)); 
	/* combine mask and new divider vals into 32-bit value */
    regVal = maskVal |
        ((uint32)((uint32)clkDivider <<  CodecI2CM_SCBCLK_DIV_INT_SHIFT) & CodecI2CM_SCBCLK_DIV_INT_MASK) |
        ((uint32)((uint32)clkFractional << CodecI2CM_SCBCLK_DIV_FRAC_SHIFT) & CodecI2CM_SCBCLK_DIV_FRAC_MASK);
    
#else
    /* get all but integer divider bits */
    maskVal = CodecI2CM_SCBCLK_DIV_REG & (uint32)(~(uint32)CodecI2CM_SCBCLK__DIVIDER_MASK);
    /* combine mask and new divider val into 32-bit value */
    regVal = clkDivider | maskVal;
    
#endif /* CodecI2CM_SCBCLK__FRAC_MASK || CYREG_PERI_DIV_CMD */

    CodecI2CM_SCBCLK_DIV_REG = regVal;
}


/*******************************************************************************
* Function Name: CodecI2CM_SCBCLK_GetDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Divide value of the clock minus 1. For example, if the clock is set to
*  divide by 2, the return value will be 1.
*
*******************************************************************************/
uint16 CodecI2CM_SCBCLK_GetDividerRegister(void)
{
    return (uint16)((CodecI2CM_SCBCLK_DIV_REG & CodecI2CM_SCBCLK_DIV_INT_MASK)
        >> CodecI2CM_SCBCLK_DIV_INT_SHIFT);
}


/*******************************************************************************
* Function Name: CodecI2CM_SCBCLK_GetFractionalDividerRegister
********************************************************************************
*
* Summary:
*  Gets the clock fractional divider register value.
*
* Parameters:
*  None
*
* Returns:
*  Fractional Divide value of the clock
*  0 if the fractional divider is not in use.
*
*******************************************************************************/
uint8 CodecI2CM_SCBCLK_GetFractionalDividerRegister(void)
{
#if defined (CodecI2CM_SCBCLK__FRAC_MASK)
    /* return fractional divider bits */
    return (uint8)((CodecI2CM_SCBCLK_DIV_REG & CodecI2CM_SCBCLK_DIV_FRAC_MASK)
        >> CodecI2CM_SCBCLK_DIV_FRAC_SHIFT);
#else
    return 0u;
#endif /* CodecI2CM_SCBCLK__FRAC_MASK */
}


/* [] END OF FILE */
