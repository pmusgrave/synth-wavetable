/*******************************************************************************
* File Name: Codec_LRC.h  
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

#if !defined(CY_PINS_Codec_LRC_H) /* Pins Codec_LRC_H */
#define CY_PINS_Codec_LRC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Codec_LRC_aliases.h"


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
} Codec_LRC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Codec_LRC_Read(void);
void    Codec_LRC_Write(uint8 value);
uint8   Codec_LRC_ReadDataReg(void);
#if defined(Codec_LRC__PC) || (CY_PSOC4_4200L) 
    void    Codec_LRC_SetDriveMode(uint8 mode);
#endif
void    Codec_LRC_SetInterruptMode(uint16 position, uint16 mode);
uint8   Codec_LRC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Codec_LRC_Sleep(void); 
void Codec_LRC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Codec_LRC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Codec_LRC_DRIVE_MODE_BITS        (3)
    #define Codec_LRC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Codec_LRC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Codec_LRC_SetDriveMode() function.
         *  @{
         */
        #define Codec_LRC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Codec_LRC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Codec_LRC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Codec_LRC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Codec_LRC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Codec_LRC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Codec_LRC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Codec_LRC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Codec_LRC_MASK               Codec_LRC__MASK
#define Codec_LRC_SHIFT              Codec_LRC__SHIFT
#define Codec_LRC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Codec_LRC_SetInterruptMode() function.
     *  @{
     */
        #define Codec_LRC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Codec_LRC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Codec_LRC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Codec_LRC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Codec_LRC__SIO)
    #define Codec_LRC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Codec_LRC__PC) && (CY_PSOC4_4200L)
    #define Codec_LRC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Codec_LRC_USBIO_DISABLE              ((uint32)(~Codec_LRC_USBIO_ENABLE))
    #define Codec_LRC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Codec_LRC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Codec_LRC_USBIO_ENTER_SLEEP          ((uint32)((1u << Codec_LRC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Codec_LRC_USBIO_SUSPEND_DEL_SHIFT)))
    #define Codec_LRC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Codec_LRC_USBIO_SUSPEND_SHIFT)))
    #define Codec_LRC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Codec_LRC_USBIO_SUSPEND_DEL_SHIFT)))
    #define Codec_LRC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Codec_LRC__PC)
    /* Port Configuration */
    #define Codec_LRC_PC                 (* (reg32 *) Codec_LRC__PC)
#endif
/* Pin State */
#define Codec_LRC_PS                     (* (reg32 *) Codec_LRC__PS)
/* Data Register */
#define Codec_LRC_DR                     (* (reg32 *) Codec_LRC__DR)
/* Input Buffer Disable Override */
#define Codec_LRC_INP_DIS                (* (reg32 *) Codec_LRC__PC2)

/* Interrupt configuration Registers */
#define Codec_LRC_INTCFG                 (* (reg32 *) Codec_LRC__INTCFG)
#define Codec_LRC_INTSTAT                (* (reg32 *) Codec_LRC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Codec_LRC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Codec_LRC__SIO)
    #define Codec_LRC_SIO_REG            (* (reg32 *) Codec_LRC__SIO)
#endif /* (Codec_LRC__SIO_CFG) */

/* USBIO registers */
#if !defined(Codec_LRC__PC) && (CY_PSOC4_4200L)
    #define Codec_LRC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Codec_LRC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Codec_LRC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Codec_LRC_DRIVE_MODE_SHIFT       (0x00u)
#define Codec_LRC_DRIVE_MODE_MASK        (0x07u << Codec_LRC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Codec_LRC_H */


/* [] END OF FILE */
