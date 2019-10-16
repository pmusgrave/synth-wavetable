/*******************************************************************************
* File Name: wr_en.c  
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
#include "wr_en.h"

static wr_en_BACKUP_STRUCT  wr_en_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: wr_en_Sleep
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
*  \snippet wr_en_SUT.c usage_wr_en_Sleep_Wakeup
*******************************************************************************/
void wr_en_Sleep(void)
{
    #if defined(wr_en__PC)
        wr_en_backup.pcState = wr_en_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            wr_en_backup.usbState = wr_en_CR1_REG;
            wr_en_USB_POWER_REG |= wr_en_USBIO_ENTER_SLEEP;
            wr_en_CR1_REG &= wr_en_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(wr_en__SIO)
        wr_en_backup.sioState = wr_en_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        wr_en_SIO_REG &= (uint32)(~wr_en_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: wr_en_Wakeup
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
*  Refer to wr_en_Sleep() for an example usage.
*******************************************************************************/
void wr_en_Wakeup(void)
{
    #if defined(wr_en__PC)
        wr_en_PC = wr_en_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            wr_en_USB_POWER_REG &= wr_en_USBIO_EXIT_SLEEP_PH1;
            wr_en_CR1_REG = wr_en_backup.usbState;
            wr_en_USB_POWER_REG &= wr_en_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(wr_en__SIO)
        wr_en_SIO_REG = wr_en_backup.sioState;
    #endif
}


/* [] END OF FILE */
