/*******************************************************************************
* File Name: USBFS_1_Dm.h  
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

#if !defined(CY_PINS_USBFS_1_Dm_H) /* Pins USBFS_1_Dm_H */
#define CY_PINS_USBFS_1_Dm_H

#include "cytypes.h"
#include "cyfitter.h"
#include "USBFS_1_Dm_aliases.h"


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
} USBFS_1_Dm_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   USBFS_1_Dm_Read(void);
void    USBFS_1_Dm_Write(uint8 value);
uint8   USBFS_1_Dm_ReadDataReg(void);
#if defined(USBFS_1_Dm__PC) || (CY_PSOC4_4200L) 
    void    USBFS_1_Dm_SetDriveMode(uint8 mode);
#endif
void    USBFS_1_Dm_SetInterruptMode(uint16 position, uint16 mode);
uint8   USBFS_1_Dm_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void USBFS_1_Dm_Sleep(void); 
void USBFS_1_Dm_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(USBFS_1_Dm__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define USBFS_1_Dm_DRIVE_MODE_BITS        (3)
    #define USBFS_1_Dm_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - USBFS_1_Dm_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the USBFS_1_Dm_SetDriveMode() function.
         *  @{
         */
        #define USBFS_1_Dm_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define USBFS_1_Dm_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define USBFS_1_Dm_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define USBFS_1_Dm_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define USBFS_1_Dm_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define USBFS_1_Dm_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define USBFS_1_Dm_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define USBFS_1_Dm_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define USBFS_1_Dm_MASK               USBFS_1_Dm__MASK
#define USBFS_1_Dm_SHIFT              USBFS_1_Dm__SHIFT
#define USBFS_1_Dm_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in USBFS_1_Dm_SetInterruptMode() function.
     *  @{
     */
        #define USBFS_1_Dm_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define USBFS_1_Dm_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define USBFS_1_Dm_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define USBFS_1_Dm_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(USBFS_1_Dm__SIO)
    #define USBFS_1_Dm_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(USBFS_1_Dm__PC) && (CY_PSOC4_4200L)
    #define USBFS_1_Dm_USBIO_ENABLE               ((uint32)0x80000000u)
    #define USBFS_1_Dm_USBIO_DISABLE              ((uint32)(~USBFS_1_Dm_USBIO_ENABLE))
    #define USBFS_1_Dm_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define USBFS_1_Dm_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define USBFS_1_Dm_USBIO_ENTER_SLEEP          ((uint32)((1u << USBFS_1_Dm_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << USBFS_1_Dm_USBIO_SUSPEND_DEL_SHIFT)))
    #define USBFS_1_Dm_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << USBFS_1_Dm_USBIO_SUSPEND_SHIFT)))
    #define USBFS_1_Dm_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << USBFS_1_Dm_USBIO_SUSPEND_DEL_SHIFT)))
    #define USBFS_1_Dm_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(USBFS_1_Dm__PC)
    /* Port Configuration */
    #define USBFS_1_Dm_PC                 (* (reg32 *) USBFS_1_Dm__PC)
#endif
/* Pin State */
#define USBFS_1_Dm_PS                     (* (reg32 *) USBFS_1_Dm__PS)
/* Data Register */
#define USBFS_1_Dm_DR                     (* (reg32 *) USBFS_1_Dm__DR)
/* Input Buffer Disable Override */
#define USBFS_1_Dm_INP_DIS                (* (reg32 *) USBFS_1_Dm__PC2)

/* Interrupt configuration Registers */
#define USBFS_1_Dm_INTCFG                 (* (reg32 *) USBFS_1_Dm__INTCFG)
#define USBFS_1_Dm_INTSTAT                (* (reg32 *) USBFS_1_Dm__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define USBFS_1_Dm_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(USBFS_1_Dm__SIO)
    #define USBFS_1_Dm_SIO_REG            (* (reg32 *) USBFS_1_Dm__SIO)
#endif /* (USBFS_1_Dm__SIO_CFG) */

/* USBIO registers */
#if !defined(USBFS_1_Dm__PC) && (CY_PSOC4_4200L)
    #define USBFS_1_Dm_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define USBFS_1_Dm_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define USBFS_1_Dm_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define USBFS_1_Dm_DRIVE_MODE_SHIFT       (0x00u)
#define USBFS_1_Dm_DRIVE_MODE_MASK        (0x07u << USBFS_1_Dm_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins USBFS_1_Dm_H */


/* [] END OF FILE */