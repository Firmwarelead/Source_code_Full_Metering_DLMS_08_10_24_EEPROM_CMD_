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
* File Name    : bl_flash.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   :
* H/W Platform :
* Description  : Internal memory flashing
***********************************************************************************************************************/

#ifndef __BL_FLASH_H
#define __BL_FLASH_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"        /* GSCE Standard Typedef */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/*
 * RL78 Flash information
*/
#define DEVICE_FLASH_BLOCK_SIZE                         (1024)

#define DEVICE_FLASH_WRITE_WORD_SIZE                    (4)
#define MAX_NUMBER_OF_WORDS_EACH_WRITE                  (64)
#define MAX_NUMBER_OF_BYTE_EACH_WRITE                   (MAX_NUMBER_OF_WORDS_EACH_WRITE * DEVICE_FLASH_WRITE_WORD_SIZE)

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
 * ROM SECTION APIs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_FLASH_Prepare
 * Description  : Call functions:
 *                  FSL_Init
 *                  FSL_Open
 *                  FSL_PrepareFunctions
 *                  FSL_PrepareExtFunctions
 * Arguments    : p_fsl_descriptor: in pointer (accept up to far) to descriptor structure on user code
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means FSL_Init sucessfully
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 **********************************************************************************************************************/
uint16_t BL_FLASH_Prepare(void);

/***********************************************************************************************************************
 * Function Name: BL_FLASH_CleanUp
 * Description  : Call to FSL_Close
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void BL_FLASH_CleanUp(void);

/***********************************************************************************************************************
 * Function Name: BL_FLASH_BankProgramming
 * Description  : Execute bank programming function (for device supported bank programming only)
 *                The input address will auto shifted to rewrite bank region (+ bl_properties_t.device.bank_size)
 *                Max 16bit calculation range, this API will split into chunk within 1 flash block (1024 bytes)
 *                Internal 2 type of operation:  Fast-write operation and RMEW operation (read-modify-erase-write)
 *                  Condition for trying fast-write:
 *                      + Both address and size must be in units of 4 bytes
 *                      + Data within writing area must be all FFs (state after erased for RL78 flash)
 *                  Fast-write: any write-verify failure during fast-write will fall back to RMEW
 *                  RMEW: contain 4 operations
 *                      + Read back content of current block into temporary buffer (1024 bytes)
 *                      + Modify the content based on address on the buffer block
 *                      + Write entire buffer content to flash
 *                      + Verify write state again
 *                  Any failure in operation of RMEW will return immediately with error code
 *                  Common for either operation : content in write area is read back and compare byte-by-byte
 * Arguments    : addr: ROM address to write new content (note, address will shifted to rewrite bank region)
 *              : buffer: content to write to ROM address in rewrite bank
 *              : size: size of write content
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means all operations sucessfully, ensure written ROM content same as input buffer
 *                  BL_ERROR_NULL_POINTER: buffer is NULL
 *                  BL_ERROR_ZERO_SIZE: size is zero
 *                  BL_ERROR_ADDRESS_RANGE: addr + size > bl_properties_t.device.bank_size
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 *                  BL_ERROR_FUNC_FSL_Erase | fsl_status: error on FSL_Erase
 *                  BL_ERROR_FUNC_FSL_Write | fsl_status: error on FSL_Write
 *                  BL_ERROR_FUNC_FSL_IVerify | fsl_status: error on FSL_IVerify
 *                  BL_ERROR_DATA_CORRUPT: read back written ROM content not same as input buffer
 **********************************************************************************************************************/
uint16_t BL_FLASH_BankProgramming(
    uint32_t addr,
    uint8_t * buffer,
    uint16_t size
);

/***********************************************************************************************************************
 * Function Name: BL_FLASH_GetBootFlag
 * Description  : Get boot flag utility function, call to BL_FLASH_GetBootFlag
 * Arguments    : p_boot_flag: pointer to return boot flag
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means buffer input pointer point to has boot flag info
 *                  BL_ERROR_NULL_POINTER: p_boot_flag_u08 is NULL
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 *                  BL_ERROR_FUNC_FSL_GetBootFlag | fsl_u08: error on FSL_GetBootFlag
 **********************************************************************************************************************/
uint16_t BL_FLASH_GetBootFlag(uint8_t * p_boot_flag);

/***********************************************************************************************************************
 * RAM SECTION APIs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_FLASH_RAM_SwapBankWithRamIsr
 * Description  : Swap active boot cluster with running interrupt service routine on RAM
 *                      + Call FSL_ChangeInterruptTable to change vector table to input ram_isr
 *                      + Call FSL_SwapActiveBootCluster to swap accordingly
 *                      + Call FSL_RestoreInterruptTable to restore vector table to ROM
 * Arguments    : p_ram_isr: pointer to RAM ISR function
 * Return Value : uint16_t: error code of the below
 *                  BL_OK: normals, means buffer input pointer point to has boot flag info
 *                  BL_ERROR_NULL_POINTER: p_boot_flag_u08 is NULL
 *                  BL_ERROR_FUNC_FSL_Init | fsl_u08: error on FSL_Init
 *                  BL_ERROR_FUNC_FSL_GetBootFlag | fsl_u08: error on FSL_GetBootFlag
 **********************************************************************************************************************/
FAR_FUNC uint16_t BL_FLASH_RAM_SwapBankWithRamIsr(void * p_ram_isr);

/***********************************************************************************************************************
 * Function Name: BL_FLASH_RAM_JumpBankSwapEntry
 * Description  : Call to bl_properties_t.entry_func.bl_bswap (bank swap entry function)
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
FAR_FUNC void BL_FLASH_RAM_JumpBankSwapEntry(void);

#endif /* __BL_FLASH_H */
