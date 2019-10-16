/*******************************************************************************
* File Name: new_sample.h  
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

#if !defined(CY_PINS_new_sample_H) /* Pins new_sample_H */
#define CY_PINS_new_sample_H

#include "cytypes.h"
#include "cyfitter.h"
#include "new_sample_aliases.h"


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
} new_sample_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   new_sample_Read(void);
void    new_sample_Write(uint8 value);
uint8   new_sample_ReadDataReg(void);
#if defined(new_sample__PC) || (CY_PSOC4_4200L) 
    void    new_sample_SetDriveMode(uint8 mode);
#endif
void    new_sample_SetInterruptMode(uint16 position, uint16 mode);
uint8   new_sample_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void new_sample_Sleep(void); 
void new_sample_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(new_sample__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define new_sample_DRIVE_MODE_BITS        (3)
    #define new_sample_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - new_sample_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the new_sample_SetDriveMode() function.
         *  @{
         */
        #define new_sample_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define new_sample_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define new_sample_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define new_sample_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define new_sample_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define new_sample_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define new_sample_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define new_sample_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define new_sample_MASK               new_sample__MASK
#define new_sample_SHIFT              new_sample__SHIFT
#define new_sample_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in new_sample_SetInterruptMode() function.
     *  @{
     */
        #define new_sample_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define new_sample_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define new_sample_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define new_sample_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(new_sample__SIO)
    #define new_sample_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(new_sample__PC) && (CY_PSOC4_4200L)
    #define new_sample_USBIO_ENABLE               ((uint32)0x80000000u)
    #define new_sample_USBIO_DISABLE              ((uint32)(~new_sample_USBIO_ENABLE))
    #define new_sample_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define new_sample_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define new_sample_USBIO_ENTER_SLEEP          ((uint32)((1u << new_sample_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << new_sample_USBIO_SUSPEND_DEL_SHIFT)))
    #define new_sample_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << new_sample_USBIO_SUSPEND_SHIFT)))
    #define new_sample_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << new_sample_USBIO_SUSPEND_DEL_SHIFT)))
    #define new_sample_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(new_sample__PC)
    /* Port Configuration */
    #define new_sample_PC                 (* (reg32 *) new_sample__PC)
#endif
/* Pin State */
#define new_sample_PS                     (* (reg32 *) new_sample__PS)
/* Data Register */
#define new_sample_DR                     (* (reg32 *) new_sample__DR)
/* Input Buffer Disable Override */
#define new_sample_INP_DIS                (* (reg32 *) new_sample__PC2)

/* Interrupt configuration Registers */
#define new_sample_INTCFG                 (* (reg32 *) new_sample__INTCFG)
#define new_sample_INTSTAT                (* (reg32 *) new_sample__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define new_sample_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(new_sample__SIO)
    #define new_sample_SIO_REG            (* (reg32 *) new_sample__SIO)
#endif /* (new_sample__SIO_CFG) */

/* USBIO registers */
#if !defined(new_sample__PC) && (CY_PSOC4_4200L)
    #define new_sample_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define new_sample_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define new_sample_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define new_sample_DRIVE_MODE_SHIFT       (0x00u)
#define new_sample_DRIVE_MODE_MASK        (0x07u << new_sample_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins new_sample_H */


/* [] END OF FILE */
