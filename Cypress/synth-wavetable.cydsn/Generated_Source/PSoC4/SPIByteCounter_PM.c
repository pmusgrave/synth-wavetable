/*******************************************************************************
* File Name: SPIByteCounter_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

static SPIByteCounter_BACKUP_STRUCT SPIByteCounter_backup;


/*******************************************************************************
* Function Name: SPIByteCounter_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SPIByteCounter_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_Sleep(void)
{
    if(0u != (SPIByteCounter_BLOCK_CONTROL_REG & SPIByteCounter_MASK))
    {
        SPIByteCounter_backup.enableState = 1u;
    }
    else
    {
        SPIByteCounter_backup.enableState = 0u;
    }

    SPIByteCounter_Stop();
    SPIByteCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: SPIByteCounter_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SPIByteCounter_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPIByteCounter_Wakeup(void)
{
    SPIByteCounter_RestoreConfig();

    if(0u != SPIByteCounter_backup.enableState)
    {
        SPIByteCounter_Enable();
    }
}


/* [] END OF FILE */
