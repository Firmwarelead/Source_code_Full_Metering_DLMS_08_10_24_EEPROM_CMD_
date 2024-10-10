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
* File Name    : bl_platform.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
***********************************************************************************************************************/
#ifndef __BL_PLATFORM_H
#define __BL_PLATFORM_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"
#include "compiler.h"
#include "bl_core.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define DEVICE_FLASH_ROM_SIZE                           (0x80000)
#define DEVICE_FLASH_BANK_SIZE                          (DEVICE_FLASH_ROM_SIZE / 2)

/* 
 * User app range in memory
 * Rule to define these area:
 *  + Start_address     : multiple of DEVICE_FLASH_BLOCK_SIZE
 *  + End_address + 1   : multiple of DEVICE_FLASH_BLOCK_SIZE
 *  + Near End_address  :  < __RAM_ADDR_START
 *  + No area overlap with debug monitor area (check .map file for details) (this cannot auto check)
*/

#define USER_APP_START_ADDRESS          (0x01000)
#define USER_APP_END_ADDRESS            (0x34BFF)

/* User app range definition checking -- Do not edit this part */

#if ((USER_APP_START_ADDRESS % DEVICE_FLASH_BLOCK_SIZE != 0))
  #error "Start address must be multiple of device flash block size"
#endif

#if (((USER_APP_END_ADDRESS+1) % DEVICE_FLASH_BLOCK_SIZE != 0))
    #error "End address + 1 must be multiple of device flash block size"
#endif

#define USER_APP_HEADER_ADDRESS         (USER_APP_START_ADDRESS)
#define USER_APP_HEADER_SIZE            (0x100)

#define USER_APP_BRANCH_TABLE_ADDRESS   (USER_APP_HEADER_ADDRESS + USER_APP_HEADER_SIZE)
#define USER_APP_BRANCH_TABLE_SIZE      (0x100)

/* Offset for image information + branch table, each part 256 byte */
#define USER_APP_ENTRY_ADDRESS          (USER_APP_BRANCH_TABLE_ADDRESS + USER_APP_BRANCH_TABLE_SIZE)

/***********************************************************************************************************************
Typedef definitions (required defined macro)
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* __BL_PLATFORM_H */