/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : bl_image.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Image processing
***********************************************************************************************************************/

#ifndef __BL_IMAGE_H
#define __BL_IMAGE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hr;
    uint8_t day;
    uint8_t wk;
    uint8_t mon;
    uint16_t yr;
} bl_time_stamp;

/* 4byte aligned fields */
typedef struct {
    uint8_t identifier[32];
    uint8_t software_version[4];
    uint32_t user_app_size;
    uint32_t user_app_hash;
    bl_time_stamp transfer_time;
    bl_time_stamp activate_time;
} bl_image_header_t;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define BL_IMAGE_CURRENT_BANK               (0)
#define BL_IMAGE_REWRITE_BANK               (1)

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_GetBankContent
 * Description  : Get content for address in requested bank from addr to addr+size-1
 * Arguments    : addr: raw address
 *              : buffer: input buffer to hold read content
 *              : size: size of buffer
 *              : bank: either BL_IMAGE_CURRENT_BANK or BL_IMAGE_REWRITE_BANK
 * Return Value : uint16_t
 *                  BL_OK: normal, means content get and put to buffer
 *                  BL_ERROR_ADDRESS_RANGE: addr + size > bank size
 *                  BL_ERROR_NULL_POINTER: buffer is NULL
 *                  BL_ERROR_ZERO_SIZE: size is 0
 *                  BL_ERROR_UNKNOWN_BANK_SELECTION: bank not BL_IMAGE_CURRENT_BANK and BL_IMAGE_REWRITE_BANK
 **********************************************************************************************************************/
uint16_t BL_IMAGE_GetBankContent(
    uint32_t addr, 
    uint8_t * buffer, 
    uint16_t size, 
    uint8_t bank
);

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_GetHeaderInfo
 * Description  : Get image header info in requested bank
 * Arguments    : p_header: address of bl_hashing_info structure
 *              : bank: either BL_IMAGE_CURRENT_BANK or BL_IMAGE_REWRITE_BANK
 * Return Value : uint16_t
 *                  BL_OK: normal, means image header get completed
 *                  BL_ERROR_NULL_POINTER: p_header is NULL
 *                  BL_ERROR_UNKNOWN_BANK_SELECTION: bank not BL_IMAGE_CURRENT_BANK and BL_IMAGE_REWRITE_BANK
 **********************************************************************************************************************/
uint16_t BL_IMAGE_GetHeaderInfo(
    bl_image_header_t * p_header, 
    uint8_t bank
);

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_SetSoftwareVersion
 * Description  : Set software version into rewrite bank (using bank programming)
 * Arguments    : p_version: pointer to version info
 * Return Value : uint16_t
 *                  BL_OK: normal, means set to rewrite bank correctly
 *                  Other error: refer to BL_FLASH_BankProgramming API
 **********************************************************************************************************************/
uint16_t BL_IMAGE_SetSoftwareVersion(uint8_t * p_version);

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_SetTransferTime
 * Description  : Set image transfer time into rewrite bank (using bank programming)
 * Arguments    : p_time: pointer to time info
 * Return Value : uint16_t
 *                  BL_OK: normal, means set to rewrite bank correctly
 *                  Other error: refer to BL_FLASH_BankProgramming API
 **********************************************************************************************************************/
uint16_t BL_IMAGE_SetTransferTime(bl_time_stamp * p_time);

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_SetActivationTime
 * Description  : Set image activation time into rewrite bank (using bank programming)
 * Arguments    : p_time: pointer to time info
 * Return Value : uint16_t
 *                  BL_OK: normal, means set to rewrite bank correctly
 *                  Other error: refer to BL_FLASH_BankProgramming API
 **********************************************************************************************************************/
uint16_t BL_IMAGE_SetActivationTime(bl_time_stamp * p_time);

#endif /* __BL_IMAGE_H */
