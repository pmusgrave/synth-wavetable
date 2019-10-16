/*******************************************************************************
* File Name: USB_Dp.h  
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

#if !defined(CY_PINS_USB_Dp_H) /* Pins USB_Dp_H */
#define CY_PINS_USB_Dp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "USB_Dp_aliases.h"


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
} USB_Dp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   USB_Dp_Read(void);
void    USB_Dp_Write(uint8 value);
uint8   USB_Dp_ReadDataReg(void);
#if defined(USB_Dp__PC) || (CY_PSOC4_4200L) 
    void    USB_Dp_SetDriveMode(uint8 mode);
#endif
void    USB_Dp_SetInterruptMode(uint16 position, uint16 mode);
uint8   USB_Dp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void USB_Dp_Sleep(void); 
void USB_Dp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(USB_Dp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define USB_Dp_DRIVE_MODE_BITS        (3)
    #define USB_Dp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - USB_Dp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the USB_Dp_SetDriveMode() function.
         *  @{
         */
        #define USB_Dp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define USB_Dp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define USB_Dp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define USB_Dp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define USB_Dp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define USB_Dp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define USB_Dp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define USB_Dp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define USB_Dp_MASK               USB_Dp__MASK
#define USB_Dp_SHIFT              USB_Dp__SHIFT
#define USB_Dp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in USB_Dp_SetInterruptMode() function.
     *  @{
     */
        #define USB_Dp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define USB_Dp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define USB_Dp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define USB_Dp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(USB_Dp__SIO)
    #define USB_Dp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(USB_Dp__PC) && (CY_PSOC4_4200L)
    #define USB_Dp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define USB_Dp_USBIO_DISABLE              ((uint32)(~USB_Dp_USBIO_ENABLE))
    #define USB_Dp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define USB_Dp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define USB_Dp_USBIO_ENTER_SLEEP          ((uint32)((1u << USB_Dp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << USB_Dp_USBIO_SUSPEND_DEL_SHIFT)))
    #define USB_Dp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << USB_Dp_USBIO_SUSPEND_SHIFT)))
    #define USB_Dp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << USB_Dp_USBIO_SUSPEND_DEL_SHIFT)))
    #define USB_Dp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(USB_Dp__PC)
    /* Port Configuration */
    #define USB_Dp_PC                 (* (reg32 *) USB_Dp__PC)
#endif
/* Pin State */
#define USB_Dp_PS                     (* (reg32 *) USB_Dp__PS)
/* Data Register */
#define USB_Dp_DR                     (* (reg32 *) USB_Dp__DR)
/* Input Buffer Disable Override */
#define USB_Dp_INP_DIS                (* (reg32 *) USB_Dp__PC2)

/* Interrupt configuration Registers */
#define USB_Dp_INTCFG                 (* (reg32 *) USB_Dp__INTCFG)
#define USB_Dp_INTSTAT                (* (reg32 *) USB_Dp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define USB_Dp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(USB_Dp__SIO)
    #define USB_Dp_SIO_REG            (* (reg32 *) USB_Dp__SIO)
#endif /* (USB_Dp__SIO_CFG) */

/* USBIO registers */
#if !defined(USB_Dp__PC) && (CY_PSOC4_4200L)
    #define USB_Dp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define USB_Dp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define USB_Dp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define USB_Dp_DRIVE_MODE_SHIFT       (0x00u)
#define USB_Dp_DRIVE_MODE_MASK        (0x07u << USB_Dp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins USB_Dp_H */


/* [] END OF FILE */
