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
* File Name    : bl_hashing.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Hashing function for ROM code and external storage memory
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "bl_header.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define R_WDT_Restart()                     {WDTE = 0xACU;}

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
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
uint16_t BL_HASHING_CalculateOnce(uint32_t start_addr, uint32_t end_addr, uint16_t * p_out_crc)
{
    uint16_t hw_crc_backup;
    uint32_t read_buffer;
    
    if (p_out_crc == NULL)
    {
        return BL_ERROR_NULL_POINTER;
    }
    
    /* Address alignment 4 checking */
    if (((start_addr % 4) != 0) || (((end_addr + 1) % 4) != 0) || (end_addr <= start_addr))
    {
        return BL_ERROR_ADDRESS_RANGE;
    }
    
    start_addr += g_bl_properties.device.bank_size;
    end_addr += g_bl_properties.device.bank_size;
    
    /* Backup and initialize CRC value to 0 */
    hw_crc_backup = CRCD;
    CRCD = 0;
    
    /* Read in chunk of 4 byte and input data to hardware CRC calculation register */
    while (start_addr < end_addr)
    {
        read_buffer = *((uint32_t FAR_PTR *)start_addr);
        
        CRCIN = (uint8_t)((read_buffer & 0x000000FF) >> 0 );
        CRCIN = (uint8_t)((read_buffer & 0x0000FF00) >> 8 );
        CRCIN = (uint8_t)((read_buffer & 0x00FF0000) >> 16);
        CRCIN = (uint8_t)((read_buffer & 0xFF000000) >> 24);
        
        start_addr += sizeof(read_buffer);
    
        R_WDT_Restart();
    }
    
    /* Assign to output value */
    *p_out_crc = CRCD;
    
    /* Load back CRC data register to CRC calculation result */
    CRCD = hw_crc_backup;
    
    return BL_OK;
}

