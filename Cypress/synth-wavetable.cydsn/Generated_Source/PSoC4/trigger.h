/*******************************************************************************
* File Name: trigger.h  
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

#if !defined(CY_PINS_trigger_H) /* Pins trigger_H */
#define CY_PINS_trigger_H

#include "cytypes.h"
#include "cyfitter.h"
#include "trigger_aliases.h"


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
} trigger_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   trigger_Read(void);
void    trigger_Write(uint8 value);
uint8   trigger_ReadDataReg(void);
#if defined(trigger__PC) || (CY_PSOC4_4200L) 
    void    trigger_SetDriveMode(uint8 mode);
#endif
void    trigger_SetInterruptMode(uint16 position, uint16 mode);
uint8   trigger_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void trigger_Sleep(void); 
void trigger_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(trigger__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define trigger_DRIVE_MODE_BITS        (3)
    #define trigger_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - trigger_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the trigger_SetDriveMode() function.
         *  @{
         */
        #define trigger_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define trigger_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define trigger_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define trigger_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define trigger_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define trigger_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define trigger_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define trigger_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define trigger_MASK               trigger__MASK
#define trigger_SHIFT              trigger__SHIFT
#define trigger_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in trigger_SetInterruptMode() function.
     *  @{
     */
        #define trigger_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define trigger_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define trigger_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define trigger_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(trigger__SIO)
    #define trigger_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(trigger__PC) && (CY_PSOC4_4200L)
    #define trigger_USBIO_ENABLE               ((uint32)0x80000000u)
    #define trigger_USBIO_DISABLE              ((uint32)(~trigger_USBIO_ENABLE))
    #define trigger_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define trigger_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define trigger_USBIO_ENTER_SLEEP          ((uint32)((1u << trigger_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << trigger_USBIO_SUSPEND_DEL_SHIFT)))
    #define trigger_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << trigger_USBIO_SUSPEND_SHIFT)))
    #define trigger_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << trigger_USBIO_SUSPEND_DEL_SHIFT)))
    #define trigger_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(trigger__PC)
    /* Port Configuration */
    #define trigger_PC                 (* (reg32 *) trigger__PC)
#endif
/* Pin State */
#define trigger_PS                     (* (reg32 *) trigger__PS)
/* Data Register */
#define trigger_DR                     (* (reg32 *) trigger__DR)
/* Input Buffer Disable Override */
#define trigger_INP_DIS                (* (reg32 *) trigger__PC2)

/* Interrupt configuration Registers */
#define trigger_INTCFG                 (* (reg32 *) trigger__INTCFG)
#define trigger_INTSTAT                (* (reg32 *) trigger__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define trigger_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(trigger__SIO)
    #define trigger_SIO_REG            (* (reg32 *) trigger__SIO)
#endif /* (trigger__SIO_CFG) */

/* USBIO registers */
#if !defined(trigger__PC) && (CY_PSOC4_4200L)
    #define trigger_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define trigger_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define trigger_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define trigger_DRIVE_MODE_SHIFT       (0x00u)
#define trigger_DRIVE_MODE_MASK        (0x07u << trigger_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins trigger_H */


/* [] END OF FILE */
