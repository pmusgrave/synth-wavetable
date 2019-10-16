/*******************************************************************************
* File Name: TxByteCounter_PM.c
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

#include "TxByteCounter.h"

static TxByteCounter_BACKUP_STRUCT TxByteCounter_backup;


/*******************************************************************************
* Function Name: TxByteCounter_SaveConfig
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
void TxByteCounter_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: TxByteCounter_Sleep
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
void TxByteCounter_Sleep(void)
{
    if(0u != (TxByteCounter_BLOCK_CONTROL_REG & TxByteCounter_MASK))
    {
        TxByteCounter_backup.enableState = 1u;
    }
    else
    {
        TxByteCounter_backup.enableState = 0u;
    }

    TxByteCounter_Stop();
    TxByteCounter_SaveConfig();
}


/*******************************************************************************
* Function Name: TxByteCounter_RestoreConfig
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
void TxByteCounter_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: TxByteCounter_Wakeup
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
void TxByteCounter_Wakeup(void)
{
    TxByteCounter_RestoreConfig();

    if(0u != TxByteCounter_backup.enableState)
    {
        TxByteCounter_Enable();
    }
}


/* [] END OF FILE */
