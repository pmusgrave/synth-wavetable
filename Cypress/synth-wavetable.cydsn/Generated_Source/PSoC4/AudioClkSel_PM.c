/*******************************************************************************
* File Name: AudioClkSel_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "AudioClkSel.h"

/* Check for removal by optimization */
#if !defined(AudioClkSel_Sync_ctrl_reg__REMOVED)

static AudioClkSel_BACKUP_STRUCT  AudioClkSel_backup = {0u};

    
/*******************************************************************************
* Function Name: AudioClkSel_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AudioClkSel_SaveConfig(void) 
{
    AudioClkSel_backup.controlState = AudioClkSel_Control;
}


/*******************************************************************************
* Function Name: AudioClkSel_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void AudioClkSel_RestoreConfig(void) 
{
     AudioClkSel_Control = AudioClkSel_backup.controlState;
}


/*******************************************************************************
* Function Name: AudioClkSel_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AudioClkSel_Sleep(void) 
{
    AudioClkSel_SaveConfig();
}


/*******************************************************************************
* Function Name: AudioClkSel_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void AudioClkSel_Wakeup(void)  
{
    AudioClkSel_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
