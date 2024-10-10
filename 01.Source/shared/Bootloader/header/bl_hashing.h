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
* File Name    : bl_hashing.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Hashing function for ROM code and external storage memory
***********************************************************************************************************************/

#ifndef __BL_HASHING_H
#define __BL_HASHING_H

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

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_HASHING_CalculateOnce
 * Description  : Calculate hash in address range using RL78 General purpose CRC 
 * Arguments    : uint32_t start_addr: Start address. start_addr need to be 4-byte alignment
 *              : uint32_t end_addr: End address. (end_addr + 1) need to be 4-byte alignment
 *              : uint16_t * p_out_crc: Pointer to output calculated hash value
 * Return Value : uint16_t
 *                  BL_OK: normal, means calculation completed without error
 *                  BL_ERROR_NULL_POINTER: p_out_crc is NULL
 *                  BL_ERROR_ADDRESS_RANGE: start_addr or (end_addr + 1) not 4 byte alignment, or end_addr <= start_addr 
 **********************************************************************************************************************/
uint16_t BL_HASHING_CalculateOnce(uint32_t start_addr, uint32_t end_addr, uint16_t * p_out_crc);

#endif /* __BL_HASHING_H */
