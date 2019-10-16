/***************************************************************************//**
* \file CodecI2CM_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_CodecI2CM_H)
#define CY_SCB_BOOT_CodecI2CM_H

#include "CodecI2CM_PVT.h"

#if (CodecI2CM_SCB_MODE_I2C_INC)
    #include "CodecI2CM_I2C.h"
#endif /* (CodecI2CM_SCB_MODE_I2C_INC) */

#if (CodecI2CM_SCB_MODE_EZI2C_INC)
    #include "CodecI2CM_EZI2C.h"
#endif /* (CodecI2CM_SCB_MODE_EZI2C_INC) */

#if (CodecI2CM_SCB_MODE_SPI_INC || CodecI2CM_SCB_MODE_UART_INC)
    #include "CodecI2CM_SPI_UART.h"
#endif /* (CodecI2CM_SCB_MODE_SPI_INC || CodecI2CM_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define CodecI2CM_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CodecI2CM) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (CodecI2CM_SCB_MODE_I2C_INC)
    #define CodecI2CM_I2C_BTLDR_COMM_ENABLED     (CodecI2CM_BTLDR_COMM_ENABLED && \
                                                            (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             CodecI2CM_I2C_SLAVE_CONST))
#else
     #define CodecI2CM_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (CodecI2CM_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (CodecI2CM_SCB_MODE_EZI2C_INC)
    #define CodecI2CM_EZI2C_BTLDR_COMM_ENABLED   (CodecI2CM_BTLDR_COMM_ENABLED && \
                                                         CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define CodecI2CM_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (CodecI2CM_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (CodecI2CM_SCB_MODE_SPI_INC)
    #define CodecI2CM_SPI_BTLDR_COMM_ENABLED     (CodecI2CM_BTLDR_COMM_ENABLED && \
                                                            (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             CodecI2CM_SPI_SLAVE_CONST))
#else
        #define CodecI2CM_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (CodecI2CM_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (CodecI2CM_SCB_MODE_UART_INC)
       #define CodecI2CM_UART_BTLDR_COMM_ENABLED    (CodecI2CM_BTLDR_COMM_ENABLED && \
                                                            (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (CodecI2CM_UART_RX_DIRECTION && \
                                                              CodecI2CM_UART_TX_DIRECTION)))
#else
     #define CodecI2CM_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (CodecI2CM_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define CodecI2CM_BTLDR_COMM_MODE_ENABLED    (CodecI2CM_I2C_BTLDR_COMM_ENABLED   || \
                                                     CodecI2CM_SPI_BTLDR_COMM_ENABLED   || \
                                                     CodecI2CM_EZI2C_BTLDR_COMM_ENABLED || \
                                                     CodecI2CM_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void CodecI2CM_I2CCyBtldrCommStart(void);
    void CodecI2CM_I2CCyBtldrCommStop (void);
    void CodecI2CM_I2CCyBtldrCommReset(void);
    cystatus CodecI2CM_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus CodecI2CM_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (CodecI2CM_SCB_MODE_I2C_CONST_CFG)
        #define CodecI2CM_CyBtldrCommStart   CodecI2CM_I2CCyBtldrCommStart
        #define CodecI2CM_CyBtldrCommStop    CodecI2CM_I2CCyBtldrCommStop
        #define CodecI2CM_CyBtldrCommReset   CodecI2CM_I2CCyBtldrCommReset
        #define CodecI2CM_CyBtldrCommRead    CodecI2CM_I2CCyBtldrCommRead
        #define CodecI2CM_CyBtldrCommWrite   CodecI2CM_I2CCyBtldrCommWrite
    #endif /* (CodecI2CM_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void CodecI2CM_EzI2CCyBtldrCommStart(void);
    void CodecI2CM_EzI2CCyBtldrCommStop (void);
    void CodecI2CM_EzI2CCyBtldrCommReset(void);
    cystatus CodecI2CM_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus CodecI2CM_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (CodecI2CM_SCB_MODE_EZI2C_CONST_CFG)
        #define CodecI2CM_CyBtldrCommStart   CodecI2CM_EzI2CCyBtldrCommStart
        #define CodecI2CM_CyBtldrCommStop    CodecI2CM_EzI2CCyBtldrCommStop
        #define CodecI2CM_CyBtldrCommReset   CodecI2CM_EzI2CCyBtldrCommReset
        #define CodecI2CM_CyBtldrCommRead    CodecI2CM_EzI2CCyBtldrCommRead
        #define CodecI2CM_CyBtldrCommWrite   CodecI2CM_EzI2CCyBtldrCommWrite
    #endif /* (CodecI2CM_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void CodecI2CM_SpiCyBtldrCommStart(void);
    void CodecI2CM_SpiCyBtldrCommStop (void);
    void CodecI2CM_SpiCyBtldrCommReset(void);
    cystatus CodecI2CM_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus CodecI2CM_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (CodecI2CM_SCB_MODE_SPI_CONST_CFG)
        #define CodecI2CM_CyBtldrCommStart   CodecI2CM_SpiCyBtldrCommStart
        #define CodecI2CM_CyBtldrCommStop    CodecI2CM_SpiCyBtldrCommStop
        #define CodecI2CM_CyBtldrCommReset   CodecI2CM_SpiCyBtldrCommReset
        #define CodecI2CM_CyBtldrCommRead    CodecI2CM_SpiCyBtldrCommRead
        #define CodecI2CM_CyBtldrCommWrite   CodecI2CM_SpiCyBtldrCommWrite
    #endif /* (CodecI2CM_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void CodecI2CM_UartCyBtldrCommStart(void);
    void CodecI2CM_UartCyBtldrCommStop (void);
    void CodecI2CM_UartCyBtldrCommReset(void);
    cystatus CodecI2CM_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus CodecI2CM_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (CodecI2CM_SCB_MODE_UART_CONST_CFG)
        #define CodecI2CM_CyBtldrCommStart   CodecI2CM_UartCyBtldrCommStart
        #define CodecI2CM_CyBtldrCommStop    CodecI2CM_UartCyBtldrCommStop
        #define CodecI2CM_CyBtldrCommReset   CodecI2CM_UartCyBtldrCommReset
        #define CodecI2CM_CyBtldrCommRead    CodecI2CM_UartCyBtldrCommRead
        #define CodecI2CM_CyBtldrCommWrite   CodecI2CM_UartCyBtldrCommWrite
    #endif /* (CodecI2CM_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_BTLDR_COMM_ENABLED)
    #if (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void CodecI2CM_CyBtldrCommStart(void);
        void CodecI2CM_CyBtldrCommStop (void);
        void CodecI2CM_CyBtldrCommReset(void);
        cystatus CodecI2CM_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus CodecI2CM_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (CodecI2CM_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CodecI2CM)
        #define CyBtldrCommStart    CodecI2CM_CyBtldrCommStart
        #define CyBtldrCommStop     CodecI2CM_CyBtldrCommStop
        #define CyBtldrCommReset    CodecI2CM_CyBtldrCommReset
        #define CyBtldrCommWrite    CodecI2CM_CyBtldrCommWrite
        #define CyBtldrCommRead     CodecI2CM_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_CodecI2CM) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (CodecI2CM_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define CodecI2CM_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define CodecI2CM_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define CodecI2CM_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define CodecI2CM_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef CodecI2CM_SPI_BYTE_TO_BYTE
    #define CodecI2CM_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef CodecI2CM_UART_BYTE_TO_BYTE
    #define CodecI2CM_UART_BYTE_TO_BYTE  (2500u)
#endif /* CodecI2CM_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_CodecI2CM_H) */


/* [] END OF FILE */
