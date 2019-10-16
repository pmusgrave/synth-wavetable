/*******************************************************************************
* File Name: new_sample.c  
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
#include "new_sample.h"

static new_sample_BACKUP_STRUCT  new_sample_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: new_sample_Sleep
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
*  \snippet new_sample_SUT.c usage_new_sample_Sleep_Wakeup
*******************************************************************************/
void new_sample_Sleep(void)
{
    #if defined(new_sample__PC)
        new_sample_backup.pcState = new_sample_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            new_sample_backup.usbState = new_sample_CR1_REG;
            new_sample_USB_POWER_REG |= new_sample_USBIO_ENTER_SLEEP;
            new_sample_CR1_REG &= new_sample_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(new_sample__SIO)
        new_sample_backup.sioState = new_sample_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        new_sample_SIO_REG &= (uint32)(~new_sample_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: new_sample_Wakeup
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
*  Refer to new_sample_Sleep() for an example usage.
*******************************************************************************/
void new_sample_Wakeup(void)
{
    #if defined(new_sample__PC)
        new_sample_PC = new_sample_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            new_sample_USB_POWER_REG &= new_sample_USBIO_EXIT_SLEEP_PH1;
            new_sample_CR1_REG = new_sample_backup.usbState;
            new_sample_USB_POWER_REG &= new_sample_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(new_sample__SIO)
        new_sample_SIO_REG = new_sample_backup.sioState;
    #endif
}


/* [] END OF FILE */
