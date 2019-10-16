/*******************************************************************************
* File Name: spi_ss.h  
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

#if !defined(CY_PINS_spi_ss_H) /* Pins spi_ss_H */
#define CY_PINS_spi_ss_H

#include "cytypes.h"
#include "cyfitter.h"
#include "spi_ss_aliases.h"


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
} spi_ss_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   spi_ss_Read(void);
void    spi_ss_Write(uint8 value);
uint8   spi_ss_ReadDataReg(void);
#if defined(spi_ss__PC) || (CY_PSOC4_4200L) 
    void    spi_ss_SetDriveMode(uint8 mode);
#endif
void    spi_ss_SetInterruptMode(uint16 position, uint16 mode);
uint8   spi_ss_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void spi_ss_Sleep(void); 
void spi_ss_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(spi_ss__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define spi_ss_DRIVE_MODE_BITS        (3)
    #define spi_ss_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - spi_ss_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the spi_ss_SetDriveMode() function.
         *  @{
         */
        #define spi_ss_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define spi_ss_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define spi_ss_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define spi_ss_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define spi_ss_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define spi_ss_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define spi_ss_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define spi_ss_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define spi_ss_MASK               spi_ss__MASK
#define spi_ss_SHIFT              spi_ss__SHIFT
#define spi_ss_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in spi_ss_SetInterruptMode() function.
     *  @{
     */
        #define spi_ss_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define spi_ss_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define spi_ss_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define spi_ss_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(spi_ss__SIO)
    #define spi_ss_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(spi_ss__PC) && (CY_PSOC4_4200L)
    #define spi_ss_USBIO_ENABLE               ((uint32)0x80000000u)
    #define spi_ss_USBIO_DISABLE              ((uint32)(~spi_ss_USBIO_ENABLE))
    #define spi_ss_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define spi_ss_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define spi_ss_USBIO_ENTER_SLEEP          ((uint32)((1u << spi_ss_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << spi_ss_USBIO_SUSPEND_DEL_SHIFT)))
    #define spi_ss_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << spi_ss_USBIO_SUSPEND_SHIFT)))
    #define spi_ss_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << spi_ss_USBIO_SUSPEND_DEL_SHIFT)))
    #define spi_ss_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(spi_ss__PC)
    /* Port Configuration */
    #define spi_ss_PC                 (* (reg32 *) spi_ss__PC)
#endif
/* Pin State */
#define spi_ss_PS                     (* (reg32 *) spi_ss__PS)
/* Data Register */
#define spi_ss_DR                     (* (reg32 *) spi_ss__DR)
/* Input Buffer Disable Override */
#define spi_ss_INP_DIS                (* (reg32 *) spi_ss__PC2)

/* Interrupt configuration Registers */
#define spi_ss_INTCFG                 (* (reg32 *) spi_ss__INTCFG)
#define spi_ss_INTSTAT                (* (reg32 *) spi_ss__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define spi_ss_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(spi_ss__SIO)
    #define spi_ss_SIO_REG            (* (reg32 *) spi_ss__SIO)
#endif /* (spi_ss__SIO_CFG) */

/* USBIO registers */
#if !defined(spi_ss__PC) && (CY_PSOC4_4200L)
    #define spi_ss_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define spi_ss_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define spi_ss_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define spi_ss_DRIVE_MODE_SHIFT       (0x00u)
#define spi_ss_DRIVE_MODE_MASK        (0x07u << spi_ss_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins spi_ss_H */


/* [] END OF FILE */
