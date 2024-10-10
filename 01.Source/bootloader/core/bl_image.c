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
* File Name    : bl_image.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : Image processing
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <string.h>
#include "bl_header.h"
#include "fsl.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

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
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_IMAGE_GetBankContent(uint32_t addr, uint8_t * buffer, uint16_t size, uint8_t bank)
{
    /* check the address range if still within 1 bank */
    if( (addr + size) > g_bl_properties.device.bank_size )
    {
        return BL_ERROR_ADDRESS_RANGE;
    }

    /* Check user buffer */
    if (buffer == NULL)
    {
        return BL_ERROR_NULL_POINTER;
    }
    
    /* Stop if size is zero */
    if (size == 0)
    {
        return BL_ERROR_ZERO_SIZE;
    }

    if (bank != BL_IMAGE_CURRENT_BANK && bank != BL_IMAGE_REWRITE_BANK)
    {
        return BL_ERROR_UNKNOWN_BANK_SELECTION;
    }

    /* Shift address if needed */
    if (bank == BL_IMAGE_REWRITE_BANK)
    {
        addr += g_bl_properties.device.bank_size;
    }

    BL_memcpy_nf(buffer, (const void FAR_PTR *)addr, size);

    return BL_OK;
}

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
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_IMAGE_GetHeaderInfo(bl_image_header_t * p_header, uint8_t bank)
{
    uint32_t start_addr;

    if (p_header == NULL) 
    {
        return BL_ERROR_NULL_POINTER;
    }

    if (bank != BL_IMAGE_CURRENT_BANK && bank != BL_IMAGE_REWRITE_BANK)
    {
        return BL_ERROR_UNKNOWN_BANK_SELECTION;
    }

    start_addr = g_bl_properties.user_app.start_addr;
    if (bank == BL_IMAGE_REWRITE_BANK)
    {
        start_addr += g_bl_properties.device.bank_size;
    }

    /* Copy each element to avoid unmatch packing on image header and struct packing option */
    BL_memcpy_nf(p_header, (const void FAR_PTR *)start_addr , sizeof(bl_image_header_t));
    
    return BL_OK;
}
/***********************************************************************************************************************
 End of function BL_IMAGE_GetHeaderInfo
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_SetSoftwareVersion
 * Description  : Set software version into rewrite bank (using bank programming)
 * Arguments    : p_version: pointer to version info
 * Return Value : uint16_t
 *                  BL_OK: normal, means set to rewrite bank correctly
 *                  Other error: refer to BL_FLASH_BankProgramming API
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_IMAGE_SetSoftwareVersion(uint8_t * p_version)
{
    if (p_version == NULL) 
    {
        return BL_ERROR_NULL_POINTER;
    }
    
    return BL_FLASH_BankProgramming(
        g_bl_properties.user_app.start_addr + offsetof(bl_image_header_t, software_version), 
        (uint8_t *)p_version, 
        sizeof(((bl_image_header_t *)0)->software_version)
    );
}
/***********************************************************************************************************************
 End of function BL_IMAGE_SetTransferTime
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_SetTransferTime
 * Description  : Set image transfer time into rewrite bank (using bank programming)
 * Arguments    : p_time: pointer to time info
 * Return Value : uint16_t
 *                  BL_OK: normal, means set to rewrite bank correctly
 *                  Other error: refer to BL_FLASH_BankProgramming API
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_IMAGE_SetTransferTime(bl_time_stamp * p_time)
{
    if (p_time == NULL) 
    {
        return BL_ERROR_NULL_POINTER;
    }
    
    return BL_FLASH_BankProgramming(
        g_bl_properties.user_app.start_addr + offsetof(bl_image_header_t, transfer_time), 
        (uint8_t *)p_time, 
        sizeof(bl_time_stamp)
    );
}
/***********************************************************************************************************************
 End of function BL_IMAGE_SetTransferTime
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_IMAGE_SetActivationTime
 * Description  : Set image activation time into rewrite bank (using bank programming)
 * Arguments    : p_time: pointer to time info
 * Return Value : uint16_t
 *                  BL_OK: normal, means set to rewrite bank correctly
 *                  Other error: refer to BL_FLASH_BankProgramming API
 **********************************************************************************************************************/
 #ifdef __ICCRL78__
__root
#endif
uint16_t BL_IMAGE_SetActivationTime(bl_time_stamp * p_time)
{
    if (p_time == NULL) 
    {
        return BL_ERROR_NULL_POINTER;
    }
    
    return BL_FLASH_BankProgramming(
        g_bl_properties.user_app.start_addr + offsetof(bl_image_header_t, activate_time), 
        (uint8_t *)p_time, 
        sizeof(bl_time_stamp)
    );
}
/***********************************************************************************************************************
 End of function BL_IMAGE_SetActivationTime
***********************************************************************************************************************/