/*******************************************************************************
* File Name: cts.h  
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

#if !defined(CY_PINS_cts_H) /* Pins cts_H */
#define CY_PINS_cts_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cts_aliases.h"


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
} cts_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   cts_Read(void);
void    cts_Write(uint8 value);
uint8   cts_ReadDataReg(void);
#if defined(cts__PC) || (CY_PSOC4_4200L) 
    void    cts_SetDriveMode(uint8 mode);
#endif
void    cts_SetInterruptMode(uint16 position, uint16 mode);
uint8   cts_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void cts_Sleep(void); 
void cts_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(cts__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define cts_DRIVE_MODE_BITS        (3)
    #define cts_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - cts_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the cts_SetDriveMode() function.
         *  @{
         */
        #define cts_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define cts_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define cts_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define cts_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define cts_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define cts_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define cts_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define cts_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define cts_MASK               cts__MASK
#define cts_SHIFT              cts__SHIFT
#define cts_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in cts_SetInterruptMode() function.
     *  @{
     */
        #define cts_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define cts_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define cts_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define cts_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(cts__SIO)
    #define cts_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(cts__PC) && (CY_PSOC4_4200L)
    #define cts_USBIO_ENABLE               ((uint32)0x80000000u)
    #define cts_USBIO_DISABLE              ((uint32)(~cts_USBIO_ENABLE))
    #define cts_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define cts_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define cts_USBIO_ENTER_SLEEP          ((uint32)((1u << cts_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << cts_USBIO_SUSPEND_DEL_SHIFT)))
    #define cts_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << cts_USBIO_SUSPEND_SHIFT)))
    #define cts_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << cts_USBIO_SUSPEND_DEL_SHIFT)))
    #define cts_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(cts__PC)
    /* Port Configuration */
    #define cts_PC                 (* (reg32 *) cts__PC)
#endif
/* Pin State */
#define cts_PS                     (* (reg32 *) cts__PS)
/* Data Register */
#define cts_DR                     (* (reg32 *) cts__DR)
/* Input Buffer Disable Override */
#define cts_INP_DIS                (* (reg32 *) cts__PC2)

/* Interrupt configuration Registers */
#define cts_INTCFG                 (* (reg32 *) cts__INTCFG)
#define cts_INTSTAT                (* (reg32 *) cts__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define cts_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(cts__SIO)
    #define cts_SIO_REG            (* (reg32 *) cts__SIO)
#endif /* (cts__SIO_CFG) */

/* USBIO registers */
#if !defined(cts__PC) && (CY_PSOC4_4200L)
    #define cts_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define cts_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define cts_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define cts_DRIVE_MODE_SHIFT       (0x00u)
#define cts_DRIVE_MODE_MASK        (0x07u << cts_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins cts_H */


/* [] END OF FILE */
