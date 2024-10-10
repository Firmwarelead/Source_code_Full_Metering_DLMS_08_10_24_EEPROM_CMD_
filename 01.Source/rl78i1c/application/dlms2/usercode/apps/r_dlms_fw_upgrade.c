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
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dlms_fw_upgrade.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : CCRL
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : 
************************************************************************************************************************
* History      : 2018-03-12 New creation
***********************************************************************************************************************/
// 2018-03-29 New create
/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Drivers */
#include "r_cg_macrodriver.h"           /* Macro Driver Definitions */
#include "r_cg_crc.h"                   /* CG CRC Driver */
#include "r_cg_wdt.h"
#include "r_cg_rtc.h"

/* Standard library */
#include <string.h>

/* Wrapper */
#include "wrp_app_ext.h"

/* Bootloader */
#include "bl_core.h"
#include "bl_main.h"
#include "bl_run_on_ram.h"
/* Meter application */

/* DLMS */
#include "r_dlms_class18.h"
#include "r_dlms_app.h"
#include "r_dlms_storage.h"
#include "r_dlms_format.h"
#include "r_dlms_fw_upgrade.h"
#include "fsl.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct tag_dlms_fwu_flag_t
{
    uint8_t associating:1;
    uint8_t verified:1;
    uint8_t activate_start:1;
} dlms_fwu_flag_t;

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

dlms_fwu_flag_t g_Class18_fwu_flag;

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* Internal Get, Set */
static uint8_t R_DLMS_FWU_GetImgBlockTransferStatusLength(uint16_t * p_len);
static uint8_t R_DLMS_FWU_SetImgTransferStatus(uint8_t * p_status);
static uint8_t R_DLMS_FWU_SetImgSignature(uint16_t * p_signature);

/* Helper functions */
static uint8_t R_DLMS_FWU_ImageSelfCheck(void);
static void R_DLMS_FWU_CheckImageActivationStatus(void);

/******************************************************************************
* Function Name : R_DLMS_FWU_EraseFlashImageArea
* Interface     : void R_DLMS_FWU_EraseFlashImageArea(uint32_t start_addr, uint32_t end_addr)
* Description   : Erase flash iamge area
* Arguments     : uint32_t start_addr, uint32_t end_addr
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_FWU_EraseFlashImageArea(uint32_t start_addr, uint32_t end_addr)
{
    uint16_t blk;
    uint16_t blk_start = ((start_addr + DEVICE_FLASH_BANK_SIZE) / DEVICE_FLASH_BLOCK_SIZE);
    uint16_t blk_end = ((end_addr + 1 + DEVICE_FLASH_BANK_SIZE) / DEVICE_FLASH_BLOCK_SIZE);

    /* Use mixed of bl_flash and fsl to erase */
    /* Enable bank programming */
    FLMWEN = 1U;
    BANKPGEN = 1U;
    FLMWEN = 0U;
    
    BL_FLASH_Prepare();
    
    for (blk = blk_start; blk < blk_end; blk++)
    {
		R_WDT_Restart();
        FSL_Erase(blk);
    }
    
    BL_FLASH_CleanUp();
    
    /* Disable bank programming */
    FLMWEN = 1U;
    BANKPGEN = 0U;
    FLMWEN = 0U;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgBlockTransferStatusLength
* Interface     : uint8_t R_DLMS_FWU_GetImgBlockTransferStatusLength(
*               :     uint16_t * p_len
*               : );
* Description   : Get image block transfer status length from EEPROM
* Arguments     : uint16_t * p_len: pointer to length value
* Function Calls: None
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
static uint8_t R_DLMS_FWU_GetImgBlockTransferStatusLength(uint16_t * p_len)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR, STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE };

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_len);

    /* If length is out of range, consider storage not initialized, reset length to 0 */
    if( (*p_len) > (IMAGE_ALLOCATED_SIZE / IMAGE_BLOCK_TRANSFER_SIZE) )
    {
        *p_len = 0;
        R_DLMS_EEPROM_Write(info, (uint8_t *)p_len);
    }

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_SetImgTransferStatus
* Interface     : uint8_t R_DLMS_FWU_SetImgTransferStatus(
*               :     uint8_t * p_status
*               : );
* Description   : Set image transfer status to EEPROM
* Arguments     : uint8_t * p_status: pointer to image transfer status
* Function Calls: None
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
static uint8_t R_DLMS_FWU_SetImgTransferStatus(uint8_t * p_status)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR, STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE };

    // Read image size from eeprom
    R_DLMS_EEPROM_Write(info, (uint8_t *)p_status);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_SetImgSignature
* Interface     : uint8_t R_DLMS_FWU_SetImgTransferStatus(
*               :     uint16_t signature
*               : );
* Description   : Set image signature to EEPROM
* Arguments     : uint16_t signature: using 16bit value to save code size
* Function Calls: None
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
static uint8_t R_DLMS_FWU_SetImgSignature(uint16_t * p_signature)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR, STORAGE_EEPROM_DLMS_IMG_SIGNATURE_SIZE };

    // Read image size from eeprom
    R_DLMS_EEPROM_Write(info, (uint8_t *)p_signature);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageSelfCheck
* Interface     : uint8_t R_DLMS_FWU_ImageSelfCheck(void)
* Description   : Self check the downloaded Renesas proprietary image through meta data content
*               : This not included the integrity checking (verification), need to call it separately
* Arguments     : None
* Function Calls: None
* Return Value  : 0 is Pass, Other is FAIL
******************************************************************************/
static uint8_t R_DLMS_FWU_ImageSelfCheck(void)
{
    /* Check the content of image (using embedded metadata area) */
    uint16_t num_of_blocks;
    uint32_t first_not_transferred_block;
    dlms_fwu_self_check_t error_flg;
    uint32_t image_size;
    bl_image_header_t image_header;
    uint16_t embedded_hash_value;

    /* Initialize the error_flg */
    memset(&error_flg, 0, sizeof(error_flg));

    /* Get information for checking:
    * Image transfer completeness
    * Image header check
    */

    /* 1. Check image transfer completeness */
    /* Get number of calculated transfer blocks */
    R_DLMS_FWU_GetImgBlockTransferStatusLength(&num_of_blocks);
    R_DLMS_FWU_GetImgFirstNotTransfferedBlock(&first_not_transferred_block);

    /* First not transfer block must equal calculated blocks to be considered as complete */
    if (first_not_transferred_block != num_of_blocks)
    {
        error_flg.bit_st.image_incomplete = 1;
        return error_flg.errors;
    }

    /* 2. Check image format */

    /* Check if expected field is valid */
    BL_IMAGE_GetHeaderInfo(&image_header, BL_IMAGE_REWRITE_BANK);

    if (error_flg.errors == 0)
    {
        if ((image_header.user_app_hash & 0x0000FFFF) == 0x0000 || (image_header.user_app_hash & 0x0000FFFF) == 0xFFFF)
        {
            error_flg.bit_st.hash_value = 1;
            return error_flg.errors;
        }
    }
    
    /* Check if calculated size equal to what client sent */
    if (error_flg.errors == 0)
    {
        R_DLMS_FWU_GetImgSize(&image_size);

        if (image_size != (image_header.user_app_size + USER_APP_HEADER_SIZE))
        {
            error_flg.bit_st.img_size_not_match = 1;
            return error_flg.errors;
        }
    }


    /* Work around to get image signature by fetching directly from embedded hash */
    embedded_hash_value = (image_header.user_app_hash & 0x0000FFFF);
    R_DLMS_FWU_SetImgSignature(&embedded_hash_value);

    return 0; /* OK */
}

/******************************************************************************
* Function Name : R_DLMS_FWU_CheckImageActivationStatus
* Interface     : void R_DLMS_FWU_CheckImageActivationStatus(void)
* Description   : Read bootloader information to check if there's any update activity
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
static void R_DLMS_FWU_CheckImageActivationStatus(void)
{
    bl_image_update_status_t       image_status;
    bl_image_update_status  report_status;
	img_transfer_status_t	image_transfer_status;
	
    image_status = BL_GetImageUpdateStatus();

    /* Fill the image update result */
    if (image_status.details.new_update_info == 1)
    {
        if (image_status.details.update_sucess == 1)
        {
//            g_event_flag.bits.fw_activated = TRUE;
            
            image_transfer_status = IMG_ACTIVATE_SUCCESSFUL;
            report_status = PASSED;
        }
        else if (image_status.details.update_failed_new_image_not_work == 1)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_IMAGE_CANNOT_START;
            
            /* Image consider corrupt, code in current bank recovered from last working image */
            /* Erase the first block of faulty reset image (included the headers) */
            R_DLMS_FWU_EraseFlashImageArea(USER_APP_START_ADDRESS, USER_APP_START_ADDRESS + DEVICE_FLASH_BLOCK_SIZE);
        }
        else
        {
            /* Abnormal condition, should not appear */
            image_transfer_status = IMG_ACTIVATE_FAILED;
            report_status = FAILED_UNCLEAR_REASON;
        }
    }
    else
    {
        report_status = NO_UPDATE;
    }

    if (report_status != NO_UPDATE)
    {
        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
        BL_AcknowledgeImageUpdateStatus();
    }
}

/******************************************************************************
* Function Name : R_DLMS_FWU_CheckImageTransferStatus
* Interface     : void R_DLMS_FWU_CheckImageTransferStatus(void)
* Description   : Check stored image transfer status
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
static void R_DLMS_FWU_CheckImageTransferStatus(void)
{
    img_transfer_status_t image_transfer_status;

    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Check invalid transfer status */
    if (image_transfer_status > IMG_ACTIVATE_FAILED)
    {
        /* Invalid transfer status, reset and save to EEPROM */
        image_transfer_status = IMG_TRANS_NOT_INITIATED;
        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }

    /* If verify initiated return from previous step */
    if (image_transfer_status == IMG_VERIFY_INITIATED)
    {
        image_transfer_status = IMG_TRANS_INITIATED;
        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgTransferStatus
* Interface     : uint8_t R_DLMS_FWU_GetImgTransferStatus(
*               :   uint8_t * p_status
*               : );
* Description   : Get image transfer status from EEPROM
* Arguments     : uint8_t * p_status: pointer to status value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgTransferStatus(uint8_t * p_status)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_STATUS_ADDR, STORAGE_EEPROM_DLMS_IMG_STATUS_SIZE };

    ASSERT_TRUE_RET_VAL(
        p_status == NULL,
        RLT_ERR_NULL
    );

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_status);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgBlockTransferStatus
* Interface     : uint8_t R_DLMS_FWU_GetImgBlockTransferStatus(
*               :   uint8_t * p_status, uint16_t * p_len
*               : );
* Description   : Get image block transfer status from EEPROM
* Arguments     : uint8_t * p_status: pointer to block transfer status value
*               : uint16_t * p_len: pointer to number of blocks value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgBlockTransferStatus(uint8_t * p_status, uint16_t * p_len)
{
    DLMS_STORAGE info;
    uint16_t length;
    img_transfer_status_t status;

    ASSERT_TRUE_RET_VAL(
        p_status == NULL || p_len == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: not read EEPROM data unless initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_status = 0;
        *p_len = 0;
        return RLT_SUCCESS;
    }

    R_DLMS_FWU_GetImgBlockTransferStatusLength(&length);
    
    /* The length get from this API is the bit length, not byte length */
    *p_len = length;
    
    /* Convert into bit length to byte length for reading the bitstring buffer from EEPROM */
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR;
    info.length = (length + 7) / 8;

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_status);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgFirstNotTransfferedBlock
* Interface     : uint8_t R_DLMS_FWU_GetImgFirstNotTransfferedBlock(
*               :   uint32_t * p_block_no
*               : );
* Description   : Get image first not transferred block from EEPROM
* Arguments     : uint16_t * p_block_no: pointer to first not transfferd block value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgFirstNotTransfferedBlock(uint32_t * p_block_no)
{
    uint16_t len_u16, i, j;
    uint32_t blockNumber;
    uint8_t b;
    img_transfer_status_t status;
    DLMS_STORAGE info;

    ASSERT_TRUE_RET_VAL(
        p_block_no == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: not read EEPROM data unless initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_block_no = 0;
        return RLT_SUCCESS;
    }

    R_DLMS_FWU_GetImgBlockTransferStatusLength(&len_u16);

    /* Convert into bit length to byte length for reading the bitstring buffer from EEPROM */
    len_u16 = (len_u16 + 7) / 8;
    blockNumber = 0;

    /* Prepare storage information of bitstring with read length fixed to 1 */
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR;
    info.length = 1;

    /* Find first 0 in the bit-string */
    for (i = 0; i < len_u16; i++)
    {
        /* Read bitstring from eeprom */
        R_DLMS_EEPROM_Read(info, (uint8_t *)&b);

        /* Scan for 1's bit and count block number until there's 0 bit or reaching len_u16 */
        for (j = 0; j <= 7; j++)
        {
            /* Scan from MSB, each 1 bit count as 1 block number */
            if ((b & (1 << (7 - j))) != 0x00)
            {
                /* Bit 1: count as 1 block number */
                blockNumber += 1;
            }
            else
            {
                /* Bit 0: keep blockNumber, stop counting */
                break;
            }
        }
        
        /* Point to next status bit string byte */
        info.address += 1;

        /* Feed WDT while loop has eeprom operation */
        R_WDT_Restart();
    }

    *p_block_no = blockNumber;

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgSize
* Interface     : uint8_t R_DLMS_FWU_GetImgSize(
*               :   uint32_t * p_image_size
*               : );
* Description   : Get image size from EEPROM
* Arguments     : uint32_t * p_image_size: pointer to image size value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgSize(uint32_t * p_image_size)
{
    DLMS_STORAGE info = { STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR, STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE };
    img_transfer_status_t status;

    /* Check the image transfer status: signature not return before initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_image_size = 0;
        return RLT_SUCCESS;
    }

    ASSERT_TRUE_RET_VAL(
        p_image_size == NULL,
        RLT_ERR_NULL
    );

    // Read image size from eeprom
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_image_size);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgId
* Interface     : uint8_t R_DLMS_FWU_GetImgId(
*               :   uint8_t * p_id, uint16_t * p_len
*               : );
* Description   : Get image size from EEPROM
* Arguments     : uint32_t * p_image_size: pointer to image size value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgId(uint8_t * p_id, uint16_t * p_len)
{
    DLMS_STORAGE info;
    img_transfer_status_t status;

    ASSERT_TRUE_RET_VAL(
        p_id == NULL || p_len == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: signature not return before initiated */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    if (status == IMG_TRANS_NOT_INITIATED)
    {
        *p_id = 0;
        *p_len = 0;
        return RLT_SUCCESS;
    }

    /* Get length of image identification */
    info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE;
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_len);

    /* If length out of range, consider memory not initialize */
    if (*p_len > STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE)
    {
        *p_len = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE;
        memset(p_id, 0, STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE);
    }
    else
    {
        /* Get image identification */
        info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR;
        info.length = *p_len;
        R_DLMS_EEPROM_Read(info, (uint8_t *)p_id);
    }

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_GetImgSignature
* Interface     : uint8_t R_DLMS_FWU_GetImgSignature(
*               :   uint8_t * p_signature, uint16_t * p_len
*               : );
* Description   : Get image signature from EEPROM (CRC checking of image)
* Arguments     : uint8_t * p_signature: pointer to signature value
*               : uint16_t * p_len: pointer to signature length value
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL
******************************************************************************/
uint8_t R_DLMS_FWU_GetImgSignature(uint8_t * p_signature, uint16_t * p_len)
{
    DLMS_STORAGE info;
    img_transfer_status_t status;

    ASSERT_TRUE_RET_VAL(
        p_signature == NULL || p_len == NULL,
        RLT_ERR_NULL
    );

    /* Check the image transfer status: signature not return before verified */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&status);

    /* Note: assume that the status enum follow sequence as in Blue book */
    if (status < IMG_VERIFY_SUCCESSFUL)
    {
        *p_signature = 0;
        *p_len = 0;
        return RLT_SUCCESS;
    }

    /* Fixed signature length */
    *p_len = HASHING_LENGTH;

    /* Get image identification */
    info.address = STORAGE_EEPROM_DLMS_IMG_SIGNATURE_ADDR;
    info.length = HASHING_LENGTH;
    R_DLMS_EEPROM_Read(info, (uint8_t *)p_signature);

    // Return image size
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_SetAssociatingStatus
* Interface     : uint8_t R_DLMS_FWU_SetAssociatingStatus(
*               :   uint8_t status
*               : );
* Description   : Set DLMS associating status to do async image checking
* Arguments     : uint8_t status: associating status (1: associating)
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
uint8_t R_DLMS_FWU_SetAssociatingStatus(uint8_t status)
{
    g_Class18_fwu_flag.associating = status;
    
    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageTransferInitiate
* Interface     : uint8_t R_DLMS_FWU_ImageTransferInitiate(
*               :   uint8_t * p_identifier, uint16_t identifier_length, uint32_t image_size
*               : );
* Description   : Initiate the image transfer process
* Arguments     : uint8_t * p_identifier: pointer to image identifier buffer
*               : uint16_t identifier_length: length of the image identifier
*               : uint32_t * p_image_size: pointer to size of the image sent later
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL, RLT_ERR_INVALID_PARAMETER , RLT_ERR_OPERATION_CORRUPTED
******************************************************************************/
uint8_t R_DLMS_FWU_ImageTransferInitiate(uint8_t * p_identifier, uint16_t identifier_length, uint32_t * p_image_size)
{
    uint8_t pageBuff[32];
    /* Fill information: device_size and block_size */
    img_transfer_status_t image_transfer_status;
    uint8_t block_transfer_status;
    uint16_t block_transfer_status_len, block_transfer_status_len_byte, writtenLengthByte;
    uint32_t image_size;
    DLMS_STORAGE info;
    
    /* Check input parameters */
    ASSERT_TRUE_RET_VAL(
        p_identifier == NULL || p_image_size == NULL,
        RLT_ERR_NULL
    );

    image_size = *p_image_size;

    ASSERT_TRUE_RET_VAL(
        identifier_length == 0 || image_size == 0,
        RLT_ERR_INVALID_PARAMETER
    );

    /* Set image transfer status to not initiated */
    image_transfer_status = IMG_TRANS_NOT_INITIATED;
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    /*----- Validate parameter ------------------------------------------ */
    /* Check if set identifier length is larger than EEPROM allocation 
    * This is currently consider not important, so just truncate it
    */
    if (identifier_length > STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE)
    {
        identifier_length = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_SIZE;
    }
    
    /* Image sent from client should be within allocated size
    */
    if (image_size > (uint32_t)IMAGE_ALLOCATED_SIZE)
    {
        return RLT_ERR_INVALID_PARAMETER;
    }

    /* ----- Update attribute--------------------------------------------*/
    /* Save indentification to memory */
    info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_LENGTH_SIZE;
    R_DLMS_EEPROM_Write(info, (uint8_t *)&identifier_length);

    info.address = STORAGE_EEPROM_DLMS_IMG_IDENTIFICATION_ADDR;
    info.length = identifier_length;
    R_DLMS_EEPROM_Write(info, p_identifier);

    /* Save image size to memory */
    info.address = STORAGE_EEPROM_DLMS_IMG_SIZE_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_SIZE_SIZE;
    R_DLMS_EEPROM_Write(info, (uint8_t *)&image_size);

    /* ---- Initiate function -----------------------------------------------*/
    block_transfer_status_len = (image_size + (IMAGE_BLOCK_TRANSFER_SIZE - 1)) / IMAGE_BLOCK_TRANSFER_SIZE;
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_ADDR;
    info.length = STORAGE_EEPROM_DLMS_IMG_BITSTRING_LENGTH_SIZE;
    R_DLMS_EEPROM_Write(info, (uint8_t *)&block_transfer_status_len);

    R_DLMS_FWU_SetImgSignature(0);
    
    /* Init image block transfer status */
    memset(pageBuff, 0, sizeof(pageBuff));
    block_transfer_status_len_byte = (block_transfer_status_len + 7) / 8;
    info.address = STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR;
    writtenLengthByte = 0;
    while (writtenLengthByte < block_transfer_status_len_byte)
    {
        /* Using pageBuff to reduce stack size, pageBuff size check with EEPROM write cycle time */
        if ((block_transfer_status_len_byte - writtenLengthByte) < sizeof(pageBuff))
        {
            info.length = block_transfer_status_len_byte - writtenLengthByte;
        }
        else
        {
            info.length = sizeof(pageBuff);
        }

        R_DLMS_EEPROM_Write(info, pageBuff);

        info.address += info.length;
        writtenLengthByte += info.length;

        /* Feed WDT while loop has eeprom operation */
        R_WDT_Restart();
    }

    /* Erase flash area preparing for write */
    R_DLMS_FWU_EraseFlashImageArea(USER_APP_START_ADDRESS, USER_APP_END_ADDRESS);
    
    /* ----- Update attribute -------------------------------------------*/
    /* Set image transfer status to initiated */
    image_transfer_status = IMG_TRANS_INITIATED;
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* ----- Clear image translation service flag ----------------------*/
    g_Class18_fwu_flag.activate_start = 0;
    g_Class18_fwu_flag.verified = 0;

    return RLT_SUCCESS;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageBlockTransfer
* Interface     : uint8_t R_DLMS_FWU_ImageBlockTransfer(
*               :   uint32_t block_number, uint8_t * p_block_data, uint16_t block_data_length
*               : );
* Description   : Transfer image block data into storage memory
* Arguments     : uint32_t * p_block_number: pointer to block number (index 0)
*               : uint8_t * p_block_data: pointer to buffer of block data
*               : uint16_t block_data_length: length of the block data
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_NULL, RLT_ERR , RLT_ERR_OPERATION_CORRUPTED
******************************************************************************/
uint8_t R_DLMS_FWU_ImageBlockTransfer(uint32_t * p_block_number, uint8_t * p_block_data, uint16_t block_data_length)
{
    uint8_t block_transfer_status;
    uint8_t status;
    img_transfer_status_t image_transfer_status;
    uint32_t addr, block_number;
    DLMS_STORAGE info;
    uint16_t bl_status;
    dlms_app_return_error_code_t result;

    /* Check input parameters */
    ASSERT_TRUE_RET_VAL(
        p_block_data == NULL || p_block_number == NULL,
        RLT_ERR_NULL
    );

    ASSERT_TRUE_RET_VAL(
        block_data_length == 0 || block_data_length > IMAGE_BLOCK_TRANSFER_SIZE,
        RLT_ERR_INVALID_PARAMETER
    );

    block_number = *p_block_number;

    /* Check image transfer status */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Only receive block transfer if transfer initiated */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status != IMG_TRANS_INITIATED,
        RLT_ERR
    );

    {
        addr = USER_APP_START_ADDRESS + (block_number * IMAGE_BLOCK_TRANSFER_SIZE);
        /* Writing block data into external storage */
        bl_status = BL_FLASH_BankProgramming(addr, p_block_data, block_data_length);

        if (bl_status != BL_OK) 
        {
            uint16_t erase_number_of_blocks;
            uint16_t erase_block_number;
            
            /* Bank program failed after read-modify-erase-write cycle, erase block and update status again */

            /* Erase single flash block, currently image transfer block size <= flash erase size */
            R_DLMS_FWU_EraseFlashImageArea(addr, (addr + DEVICE_FLASH_BLOCK_SIZE));
            
            /* Calculate blocks to be erased in erased flash area */
            erase_number_of_blocks = (DEVICE_FLASH_BLOCK_SIZE / IMAGE_BLOCK_TRANSFER_SIZE);
            erase_block_number = (block_number / erase_number_of_blocks) * erase_number_of_blocks;
            
            /* Clear bits in bytes */
            while (erase_number_of_blocks >= 8)
            {
                info.address = (uint32_t)STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + (erase_block_number / 8);
                info.length = 1;
                block_transfer_status = 0;
                R_DLMS_EEPROM_Write(info, &block_transfer_status);
                R_WDT_Restart();

                erase_number_of_blocks -= 8;
                erase_block_number += 8;
            }

            /* Clear bits within one byte */
            if (erase_number_of_blocks > 0)
            {
                info.address = (uint32_t)STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + (erase_block_number / 8);
                info.length = 1;
                R_DLMS_EEPROM_Read(info, &block_transfer_status);
                while (erase_number_of_blocks > 0)
                {
                    block_transfer_status &= (uint8_t)(~(0x80 >> (erase_block_number % 8)));
                    erase_number_of_blocks--;
                    erase_block_number++;
                }
                R_DLMS_EEPROM_Write(info, &block_transfer_status);
            }

            result = RLT_ERR_STORAGE_ERROR;
        }
        else
        {
            /* Read the block transfer status bit string based on this block number */
            info.address = (uint32_t)STORAGE_EEPROM_DLMS_IMG_BITSTRING_ADDR + (block_number / 8);
            info.length = 1;
            R_DLMS_EEPROM_Read(info, &block_transfer_status);

            /* Bank programming done */
            
            /* Mark the block as processed and store to EEPROM */
            block_transfer_status |= (0x80 >> (block_number % 8));
            /* Check status of EEPROM_Write function */
            status = R_DLMS_EEPROM_Write(info, &block_transfer_status);
            if (status != RLT_SUCCESS) 
            {
                result = RLT_ERR_STORAGE_ERROR;
            }
            else
            {
                result = RLT_SUCCESS;
            }
        }
    }

    /* If this is first block, stamp current time to image header transfer time and increase software version */
    if (block_number == 0)
    {
        bl_image_header_t image_header;
        rtc_counter_value_t rtctime;
        bl_time_stamp timestamp;

        R_RTC_Get_CalendarCounterValue(&rtctime);

        timestamp.sec	= WRP_EXT_Bcd2Dec(rtctime.sec);
        timestamp.min	= WRP_EXT_Bcd2Dec(rtctime.min);
        timestamp.hr    = WRP_EXT_Bcd2Dec(rtctime.hour);
        timestamp.day	= WRP_EXT_Bcd2Dec(rtctime.day);
        timestamp.wk	= WRP_EXT_Bcd2Dec(rtctime.week);
        timestamp.mon	= WRP_EXT_Bcd2Dec(rtctime.month);
        timestamp.yr	= WRP_EXT_Bcd2Dec(rtctime.year);
        
        BL_IMAGE_SetTransferTime(&timestamp);

        BL_IMAGE_GetHeaderInfo(&image_header, BL_IMAGE_CURRENT_BANK);
        BL_IncreaseSoftwareVersion(&image_header.software_version[0]);
        BL_IMAGE_SetSoftwareVersion(&image_header.software_version[0]);
    }

    return result;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageVerify
* Interface     : uint8_t R_DLMS_FWU_ImageVerify(void);
* Description   : Verify image in storage memory in 2 steps:
*               :   1. Self verify the image format (synchronous)
*               :   2. Checking image integrity by hashing the image (asynchronous)
*               : If the image format is correct, it will start the asynchrnous operation
*               : Each PollingProcessing call, it will process chunk of data
*               : After hashing complete, it will update the image transfer status again (verify failed or succeeded)
* Arguments     : None
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR, RLT_OTHER 
******************************************************************************/
uint8_t R_DLMS_FWU_ImageVerify(void)
{
    img_transfer_status_t image_transfer_status;
    dlms_app_return_error_code_t result;
    
    /* Check image transfer status */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Only verify if transfer initiated */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status != IMG_TRANS_INITIATED,
        RLT_ERR
    );

    /* Set transfer status to verify initiated */
    image_transfer_status = IMG_VERIFY_INITIATED;
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Do self check image format */
    if (R_DLMS_FWU_ImageSelfCheck() != 0)
    {
        image_transfer_status = IMG_VERIFY_FAILED;
        result = RLT_OTHER;
    }
    else
    {
        /* Image self check done, consider image valid */
        image_transfer_status = IMG_VERIFY_SUCCESSFUL;
        result = RLT_SUCCESS;

        g_Class18_fwu_flag.verified = 1;
    }

    /* Update the status */
    R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);

    // Return image size
    return result;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_ImageActivate
* Interface     : uint8_t R_DLMS_FWU_ImageActivate(void);
* Description   : Activate image in storage memory
*               : If image not verify yet, it will start as implicit operation
*               : and will activate once the asynchronous verification finished
* Arguments     : None
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error or RLT_ERR_OPERATION_IN_PROGRESS, RLT_OTHER
******************************************************************************/
uint8_t R_DLMS_FWU_ImageActivate(void)
{
    img_transfer_status_t image_transfer_status;
    dlms_app_return_error_code_t result;

    /* Check image transfer status */
    R_DLMS_FWU_GetImgTransferStatus((uint8_t *)&image_transfer_status);

    /* Activating, reply as operation in progress */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status == IMG_ACTIVATE_INITIATED,
        RLT_ERR_OPERATION_IN_PROGRESS
    );

    /* Only activate if verify successfully (explicit activation) or image transfer initiated (implicit activation) */
    ASSERT_TRUE_RET_VAL(
        image_transfer_status != IMG_VERIFY_SUCCESSFUL && image_transfer_status != IMG_TRANS_INITIATED,
        RLT_ERR
    );

    /* Check current image transfer status */
    if (image_transfer_status == IMG_VERIFY_SUCCESSFUL)
    {
        /* If image verification done explicitly before, let client know meter will activate immediately */
        image_transfer_status = IMG_ACTIVATE_INITIATED;
        g_Class18_fwu_flag.verified = 1;
        g_Class18_fwu_flag.activate_start = 1;
        result = RLT_SUCCESS;

        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }
    else if ((image_transfer_status == IMG_TRANS_INITIATED))
    {
        /* If image verification is not done or , do it implicitly on image activation process */

        /* Do self check image format */
        if (R_DLMS_FWU_ImageSelfCheck() != 0)
        {
            image_transfer_status = IMG_ACTIVATE_FAILED;
            result = RLT_OTHER;
        }
        else
        {
            image_transfer_status = IMG_ACTIVATE_INITIATED;
            g_Class18_fwu_flag.verified = 1;
            g_Class18_fwu_flag.activate_start = 1;
            result = RLT_SUCCESS;
        }

        R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
    }
    else
    {
        /* For other case, consider it's not correct step, action failed */
        result = RLT_OTHER;
    }

    // Return image size
    return result;
}

/******************************************************************************
* Function Name : R_DLMS_FWU_Init
* Interface     : uint8_t R_DLMS_FWU_Init(void);
* Description   : Initialize DLMS FWU Application
*               :  . Checking image activation status from bootloader
* Arguments     : None
* Function Calls: TBD
* Return Value  : uint8_t: RLT_SUCCESS if no error
******************************************************************************/
uint8_t R_DLMS_FWU_Init(void)
{
    R_DLMS_FWU_CheckImageActivationStatus();
    R_DLMS_FWU_CheckImageTransferStatus();

    return RLT_SUCCESS;   // Default is OK
}

/******************************************************************************
* Function Name : R_DLMS_FWU_PollingProcess
* Interface     : void R_DLMS_FWU_PollingProcess(void);
* Description   : Polling processing for DLMS FWU Application
*               :  1. Do request activate image to bootloader if:
*               :       image verified (implicitly or explicitly) and 
*               :       image activated and
*               :       no current active associating on DLMS
* Arguments     : None
* Function Calls: TBD
* Return Value  : None
******************************************************************************/
void R_DLMS_FWU_PollingProcess(void)
{
    img_transfer_status_t image_transfer_status;
    bl_image_header_t rw_bank_header;
    uint16_t calculated_crc;
    uint16_t status;
    
    if (g_Class18_fwu_flag.activate_start == 1)
    {
        /* DLMS must be idle and image verification completed before */
        if (g_Class18_fwu_flag.verified == 1 &&
            g_Class18_fwu_flag.associating == 0)
        {
            /* Check image integrity on rewrite bank (user_app_size in verify stage) */
            BL_IMAGE_GetHeaderInfo(&rw_bank_header, BL_IMAGE_REWRITE_BANK);
            BL_HASHING_CalculateOnce(
                ((uint32_t)USER_APP_HEADER_ADDRESS + USER_APP_HEADER_SIZE),  //Offset to rewrite bank branch table
                ((uint32_t)USER_APP_HEADER_ADDRESS + USER_APP_HEADER_SIZE) + (rw_bank_header.user_app_size) - 1,
                &calculated_crc
            );
            
            if (calculated_crc == (rw_bank_header.user_app_hash & 0x0000FFFF))
            {
                /* Matched, image integrity passed, proceed to bankswap */
                
                /* Stamp activation time */
                {
                    rtc_counter_value_t rtctime;
                    bl_time_stamp timestamp;

                    R_RTC_Get_CalendarCounterValue(&rtctime);

                    timestamp.sec = WRP_EXT_Bcd2Dec(rtctime.sec);
                    timestamp.min = WRP_EXT_Bcd2Dec(rtctime.min);
                    timestamp.hr = WRP_EXT_Bcd2Dec(rtctime.hour);
                    timestamp.day = WRP_EXT_Bcd2Dec(rtctime.day);
                    timestamp.wk = WRP_EXT_Bcd2Dec(rtctime.week);
                    timestamp.mon = WRP_EXT_Bcd2Dec(rtctime.month);
                    timestamp.yr = WRP_EXT_Bcd2Dec(rtctime.year);

                    BL_IMAGE_SetActivationTime(&timestamp);
                }

#if (WARMBOOT == 1)
                /* Non-stop metrology firmware upgrade */
                status = BL_StopInterruptAndBankSwap();
#else
                /* Bank swap and reset firmware upgrade */
                image_transfer_status = IMG_ACTIVATE_SUCCESSFUL;
                R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
                
                status = BL_StopInterruptAndBankSwapReset();
#endif
            }
            else
            {
                /* Not matched, image integrity failed, indicate activation failed */
                status = BL_ERROR_DATA_CORRUPT;
            }
            
            /* API above if return would means error */
            if (status != BL_OK)
            {
                /* Clear activation request */
                g_Class18_fwu_flag.activate_start = 0;
                
                /* Bank swap failed FAILED_FLASH_ERROR */
                image_transfer_status = IMG_ACTIVATE_FAILED;
                R_DLMS_FWU_SetImgTransferStatus((uint8_t *)&image_transfer_status);
            }
        }
    }
}
