/*******************************************************************************
* File Name: Codec_DACDAT.c  
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
#include "Codec_DACDAT.h"

static Codec_DACDAT_BACKUP_STRUCT  Codec_DACDAT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Codec_DACDAT_Sleep
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
*  \snippet Codec_DACDAT_SUT.c usage_Codec_DACDAT_Sleep_Wakeup
*******************************************************************************/
void Codec_DACDAT_Sleep(void)
{
    #if defined(Codec_DACDAT__PC)
        Codec_DACDAT_backup.pcState = Codec_DACDAT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Codec_DACDAT_backup.usbState = Codec_DACDAT_CR1_REG;
            Codec_DACDAT_USB_POWER_REG |= Codec_DACDAT_USBIO_ENTER_SLEEP;
            Codec_DACDAT_CR1_REG &= Codec_DACDAT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Codec_DACDAT__SIO)
        Codec_DACDAT_backup.sioState = Codec_DACDAT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Codec_DACDAT_SIO_REG &= (uint32)(~Codec_DACDAT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Codec_DACDAT_Wakeup
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
*  Refer to Codec_DACDAT_Sleep() for an example usage.
*******************************************************************************/
void Codec_DACDAT_Wakeup(void)
{
    #if defined(Codec_DACDAT__PC)
        Codec_DACDAT_PC = Codec_DACDAT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Codec_DACDAT_USB_POWER_REG &= Codec_DACDAT_USBIO_EXIT_SLEEP_PH1;
            Codec_DACDAT_CR1_REG = Codec_DACDAT_backup.usbState;
            Codec_DACDAT_USB_POWER_REG &= Codec_DACDAT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Codec_DACDAT__SIO)
        Codec_DACDAT_SIO_REG = Codec_DACDAT_backup.sioState;
    #endif
}


/* [] END OF FILE */
