/*******************************************************************************
* File Name: trigger.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "trigger.h"

static trigger_BACKUP_STRUCT  trigger_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: trigger_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet trigger_SUT.c usage_trigger_Sleep_Wakeup
*******************************************************************************/
void trigger_Sleep(void)
{
    #if defined(trigger__PC)
        trigger_backup.pcState = trigger_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            trigger_backup.usbState = trigger_CR1_REG;
            trigger_USB_POWER_REG |= trigger_USBIO_ENTER_SLEEP;
            trigger_CR1_REG &= trigger_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(trigger__SIO)
        trigger_backup.sioState = trigger_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        trigger_SIO_REG &= (uint32)(~trigger_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: trigger_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to trigger_Sleep() for an example usage.
*******************************************************************************/
void trigger_Wakeup(void)
{
    #if defined(trigger__PC)
        trigger_PC = trigger_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            trigger_USB_POWER_REG &= trigger_USBIO_EXIT_SLEEP_PH1;
            trigger_CR1_REG = trigger_backup.usbState;
            trigger_USB_POWER_REG &= trigger_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(trigger__SIO)
        trigger_SIO_REG = trigger_backup.sioState;
    #endif
}


/* [] END OF FILE */
