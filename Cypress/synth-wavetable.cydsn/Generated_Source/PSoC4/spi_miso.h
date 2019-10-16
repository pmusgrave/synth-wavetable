/*******************************************************************************
* File Name: spi_miso.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_spi_miso_H) /* Pins spi_miso_H */
#define CY_PINS_spi_miso_H

#include "cytypes.h"
#include "cyfitter.h"
#include "spi_miso_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} spi_miso_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   spi_miso_Read(void);
void    spi_miso_Write(uint8 value);
uint8   spi_miso_ReadDataReg(void);
#if defined(spi_miso__PC) || (CY_PSOC4_4200L) 
    void    spi_miso_SetDriveMode(uint8 mode);
#endif
void    spi_miso_SetInterruptMode(uint16 position, uint16 mode);
uint8   spi_miso_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void spi_miso_Sleep(void); 
void spi_miso_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(spi_miso__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define spi_miso_DRIVE_MODE_BITS        (3)
    #define spi_miso_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - spi_miso_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the spi_miso_SetDriveMode() function.
         *  @{
         */
        #define spi_miso_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define spi_miso_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define spi_miso_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define spi_miso_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define spi_miso_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define spi_miso_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define spi_miso_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define spi_miso_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define spi_miso_MASK               spi_miso__MASK
#define spi_miso_SHIFT              spi_miso__SHIFT
#define spi_miso_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in spi_miso_SetInterruptMode() function.
     *  @{
     */
        #define spi_miso_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define spi_miso_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define spi_miso_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define spi_miso_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(spi_miso__SIO)
    #define spi_miso_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(spi_miso__PC) && (CY_PSOC4_4200L)
    #define spi_miso_USBIO_ENABLE               ((uint32)0x80000000u)
    #define spi_miso_USBIO_DISABLE              ((uint32)(~spi_miso_USBIO_ENABLE))
    #define spi_miso_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define spi_miso_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define spi_miso_USBIO_ENTER_SLEEP          ((uint32)((1u << spi_miso_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << spi_miso_USBIO_SUSPEND_DEL_SHIFT)))
    #define spi_miso_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << spi_miso_USBIO_SUSPEND_SHIFT)))
    #define spi_miso_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << spi_miso_USBIO_SUSPEND_DEL_SHIFT)))
    #define spi_miso_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(spi_miso__PC)
    /* Port Configuration */
    #define spi_miso_PC                 (* (reg32 *) spi_miso__PC)
#endif
/* Pin State */
#define spi_miso_PS                     (* (reg32 *) spi_miso__PS)
/* Data Register */
#define spi_miso_DR                     (* (reg32 *) spi_miso__DR)
/* Input Buffer Disable Override */
#define spi_miso_INP_DIS                (* (reg32 *) spi_miso__PC2)

/* Interrupt configuration Registers */
#define spi_miso_INTCFG                 (* (reg32 *) spi_miso__INTCFG)
#define spi_miso_INTSTAT                (* (reg32 *) spi_miso__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define spi_miso_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(spi_miso__SIO)
    #define spi_miso_SIO_REG            (* (reg32 *) spi_miso__SIO)
#endif /* (spi_miso__SIO_CFG) */

/* USBIO registers */
#if !defined(spi_miso__PC) && (CY_PSOC4_4200L)
    #define spi_miso_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define spi_miso_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define spi_miso_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define spi_miso_DRIVE_MODE_SHIFT       (0x00u)
#define spi_miso_DRIVE_MODE_MASK        (0x07u << spi_miso_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins spi_miso_H */


/* [] END OF FILE */
