/*******************************************************************************
* File Name: Codec_LRC.c  
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
#include "Codec_LRC.h"

static Codec_LRC_BACKUP_STRUCT  Codec_LRC_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Codec_LRC_Sleep
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
*  \snippet Codec_LRC_SUT.c usage_Codec_LRC_Sleep_Wakeup
*******************************************************************************/
void Codec_LRC_Sleep(void)
{
    #if defined(Codec_LRC__PC)
        Codec_LRC_backup.pcState = Codec_LRC_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Codec_LRC_backup.usbState = Codec_LRC_CR1_REG;
            Codec_LRC_USB_POWER_REG |= Codec_LRC_USBIO_ENTER_SLEEP;
            Codec_LRC_CR1_REG &= Codec_LRC_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Codec_LRC__SIO)
        Codec_LRC_backup.sioState = Codec_LRC_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Codec_LRC_SIO_REG &= (uint32)(~Codec_LRC_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Codec_LRC_Wakeup
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
*  Refer to Codec_LRC_Sleep() for an example usage.
*******************************************************************************/
void Codec_LRC_Wakeup(void)
{
    #if defined(Codec_LRC__PC)
        Codec_LRC_PC = Codec_LRC_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Codec_LRC_USB_POWER_REG &= Codec_LRC_USBIO_EXIT_SLEEP_PH1;
            Codec_LRC_CR1_REG = Codec_LRC_backup.usbState;
            Codec_LRC_USB_POWER_REG &= Codec_LRC_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Codec_LRC__SIO)
        Codec_LRC_SIO_REG = Codec_LRC_backup.sioState;
    #endif
}


/* [] END OF FILE */
