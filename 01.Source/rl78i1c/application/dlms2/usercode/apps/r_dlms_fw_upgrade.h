/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_firware_upgrade
* Version      : 1.00
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-03-29 New create

#ifndef _R_DLMS_FIRMWARE_UPGRADE_H
#define _R_DLMS_FIRMWARE_UPGRADE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* DLMS */
#include "typedef.h"
#include "r_cg_macrodriver.h"           /* Macro Driver Definitions */
#include "r_cg_rtc.h"
#include "r_dlms_config.h"
#include "bl_platform.h"
#include "bl_run_on_ram.h"
#include "bl_header.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define IMAGE_TRANSFER_ENABLE          (1)

/* Configure optimum value for block transfer size: 
 *  + In units of 4 bytes (RL78 FSL)
*/
#define IMAGE_BLOCK_TRANSFER_SIZE           (256)
#define IMAGE_ALLOCATED_SIZE                (DEVICE_FLASH_ROM_SIZE / 2)

#define HASHING_LENGTH                      (2)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef union tag_dlms_fwu_self_check_t
{
    struct {
        uint8_t image_incomplete : 1;
        uint8_t hash_value:1;
        uint8_t img_size_not_match:1;
    } bit_st;
    uint8_t errors;
} dlms_fwu_self_check_t;

typedef enum tagUpdateStatus
{
    PASSED,
    FAILED_FLASH_ERROR,
    FAILED_IMAGE_CANNOT_START,
    FAILED_UNCLEAR_REASON,
    NO_UPDATE = 0xFF,
} bl_image_update_status;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
uint8_t R_DLMS_FWU_GetImgTransferStatus(uint8_t * p_status);
uint8_t R_DLMS_FWU_GetImgBlockTransferStatus(uint8_t * p_status, uint16_t * p_len);
uint8_t R_DLMS_FWU_GetImgFirstNotTransfferedBlock(uint32_t * p_block_no);
uint8_t R_DLMS_FWU_GetImgSize(uint32_t * p_image_size);
uint8_t R_DLMS_FWU_GetImgId(uint8_t * p_id, uint16_t * p_len);
uint8_t R_DLMS_FWU_GetImgSignature(uint8_t * p_signature, uint16_t * p_len);
uint8_t R_DLMS_FWU_SetAssociatingStatus(uint8_t status);

uint8_t R_DLMS_FWU_ImageTransferInitiate(uint8_t * p_identifier, uint16_t length, uint32_t * p_image_size);
uint8_t R_DLMS_FWU_ImageBlockTransfer(uint32_t * p_block_number, uint8_t * p_block_data, uint16_t block_data_length);
uint8_t R_DLMS_FWU_ImageVerify(void);
uint8_t R_DLMS_FWU_ImageActivate(void);

uint8_t R_DLMS_FWU_Init(void);
void R_DLMS_FWU_PollingProcess(void);

#endif /* _R_DLMS_FIRMWARE_UPGRADE_H */