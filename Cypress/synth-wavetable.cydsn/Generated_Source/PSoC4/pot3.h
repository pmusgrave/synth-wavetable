/*******************************************************************************
* File Name: pot3.h  
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

#if !defined(CY_PINS_pot3_H) /* Pins pot3_H */
#define CY_PINS_pot3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "pot3_aliases.h"


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
} pot3_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   pot3_Read(void);
void    pot3_Write(uint8 value);
uint8   pot3_ReadDataReg(void);
#if defined(pot3__PC) || (CY_PSOC4_4200L) 
    void    pot3_SetDriveMode(uint8 mode);
#endif
void    pot3_SetInterruptMode(uint16 position, uint16 mode);
uint8   pot3_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void pot3_Sleep(void); 
void pot3_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(pot3__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define pot3_DRIVE_MODE_BITS        (3)
    #define pot3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - pot3_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the pot3_SetDriveMode() function.
         *  @{
         */
        #define pot3_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define pot3_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define pot3_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define pot3_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define pot3_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define pot3_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define pot3_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define pot3_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define pot3_MASK               pot3__MASK
#define pot3_SHIFT              pot3__SHIFT
#define pot3_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in pot3_SetInterruptMode() function.
     *  @{
     */
        #define pot3_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define pot3_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define pot3_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define pot3_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(pot3__SIO)
    #define pot3_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(pot3__PC) && (CY_PSOC4_4200L)
    #define pot3_USBIO_ENABLE               ((uint32)0x80000000u)
    #define pot3_USBIO_DISABLE              ((uint32)(~pot3_USBIO_ENABLE))
    #define pot3_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define pot3_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define pot3_USBIO_ENTER_SLEEP          ((uint32)((1u << pot3_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << pot3_USBIO_SUSPEND_DEL_SHIFT)))
    #define pot3_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << pot3_USBIO_SUSPEND_SHIFT)))
    #define pot3_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << pot3_USBIO_SUSPEND_DEL_SHIFT)))
    #define pot3_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(pot3__PC)
    /* Port Configuration */
    #define pot3_PC                 (* (reg32 *) pot3__PC)
#endif
/* Pin State */
#define pot3_PS                     (* (reg32 *) pot3__PS)
/* Data Register */
#define pot3_DR                     (* (reg32 *) pot3__DR)
/* Input Buffer Disable Override */
#define pot3_INP_DIS                (* (reg32 *) pot3__PC2)

/* Interrupt configuration Registers */
#define pot3_INTCFG                 (* (reg32 *) pot3__INTCFG)
#define pot3_INTSTAT                (* (reg32 *) pot3__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define pot3_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(pot3__SIO)
    #define pot3_SIO_REG            (* (reg32 *) pot3__SIO)
#endif /* (pot3__SIO_CFG) */

/* USBIO registers */
#if !defined(pot3__PC) && (CY_PSOC4_4200L)
    #define pot3_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define pot3_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define pot3_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define pot3_DRIVE_MODE_SHIFT       (0x00u)
#define pot3_DRIVE_MODE_MASK        (0x07u << pot3_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins pot3_H */


/* [] END OF FILE */
