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
* File Name    : r_meter_cmd_format.c
* Version      : 1.00
* Device(s)    : 
* Tool-Chain   : 
* H/W Platform : 
* Description  : Meter CMD - External memory format
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"   /* Macro Driver Definitions */
#include "r_cg_wdt.h"           /* WDT Driver */

#include "typedef.h"            /* GSCE Standard Typedef */

#include <stdlib.h>
#include <string.h>

/* Application */
#include "r_meter_cmd.h"
#include "r_meter_cmd_share.h"

#include "config_storage.h"
#include "storage.h"

#include "wrp_app_ext.h"
#ifdef _DLMS
#include "r_dlms_format.h"
#endif
#include "event.h"

#if (defined METER_ENABLE_PROPRIETARY_METER_COMMAND) && (METER_ENABLE_PROPRIETARY_METER_COMMAND == TRUE)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define METER_CMD_FORMAT_EXPECTED_ARGS_LENGTH       (2)

#define METER_CMD_FORMAT_RET_OK                     (0x01)
#define METER_CMD_FORMAT_ERROR_UNSUPPORTED_AREA     (0x02)

#define METER_CMD_FORMAT_ACTION_IMAGE_BACKUP        (0x01)

/***********************************************************************************************************************
Configures
***********************************************************************************************************************/
/* Header code address of meter */
#define METER_CMD_METER_HEADER_CODE_ADDR             (STORAGE_EEPROM_GLOBAL_HEADER_CODE_ADDR)
#define METER_CMD_METER_HEADER_CODE_SIZE             (STORAGE_EEPROM_GLOBAL_HEADER_CODE_SIZE)

#define METER_CMD_DLMS_HEADER_CODE_ADDR              (STORAGE_EEPROM_DLMS_CODE_ADDR)
#define METER_CMD_DATAFLASH_HEADER_CODE_ADDR         (0x00)

#define METER_CMD_METROLOGY_AREA_SIZE                (0x100)

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
* Function Name: r_meter_cmd_invoke_action
* Description  : Handler for invoking action (plain action without data)
* Arguments    : uint8_t action_id
* Return Value : uint8_t: 0: if ok, others: error
***********************************************************************************************************************/
uint8_t r_meter_cmd_invoke_action(uint8_t action_id)
{
    uint8_t result = TRUE;
    
    switch (action_id)
    {
        case METER_CMD_FORMAT_ACTION_IMAGE_BACKUP:
            /* This action is not availabe on RL78I1C 512K meter */

            break;
        default:
            /* Command not supported, mark as false */
            result = FALSE;
            break;
    }

    return result;
}

/***********************************************************************************************************************
* Function Name: r_meter_cmd_do_memory_format
* Description  : Handler for memory format request
* Arguments    : MeterCmdFrameInfo * p_frame_info
*              : uint8_t mem_type
*              : uint8_t area
* Return Value : uint8_t: 0: if ok, others: error
***********************************************************************************************************************/
uint8_t r_meter_cmd_do_memory_format(MeterCmdFrameInfo * p_frame_info, uint8_t mem_type, uint8_t area)
{
    uint8_t result;
    uint8_t reset_buffer[METER_CMD_METROLOGY_AREA_SIZE];

    /* EEPROM and DATAFLASH has a header to manage the memory format validity 
    * Whole memory can be triggered by clearing that header code then restart for default memory using
    * NOTE: the reset is in send end callback
    */
    memset(reset_buffer, 0, sizeof(reset_buffer));

    result = FALSE;

    /* Currently support all area of eeprom only */
    if (mem_type & METER_CMD_MEM_TYPE_EEPROM) {
        if (area == 0xFF) {

            /* Clear metrology area */
            EPR_Write(0, reset_buffer, sizeof(reset_buffer));
            result = TRUE;

            /* Clear header code to trigger format process */
            EPR_Write(METER_CMD_METER_HEADER_CODE_ADDR, reset_buffer, METER_CMD_METER_HEADER_CODE_SIZE);
            result = TRUE;

            /* Temporary DLMS support */
            #ifdef _DLMS
            EPR_Write(METER_CMD_DLMS_HEADER_CODE_ADDR, reset_buffer, METER_CMD_METER_HEADER_CODE_SIZE);
            #endif
        }
    }

    if (mem_type & METER_CMD_MEM_TYPE_DATAFLASH) {
        /* Currently support all area of data flash only */
        if (area == 0xFF) {
            /* Register to application */
            DATAFLASH_Write(METER_CMD_DATAFLASH_HEADER_CODE_ADDR, reset_buffer, sizeof(reset_buffer));
            result = TRUE;
        }
    }

    if (mem_type & METER_CMD_MEM_TYPE_INVOKING_ACTION)
    {
        result = r_meter_cmd_invoke_action(area);
    }

    /* Prepare reply buffer */
    p_frame_info->ret = METER_CMD_OK;

    if (result == TRUE) {
        R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_FORMAT_RET_OK);
    }
    else {
        R_METER_CMD_EncodeUInt8ToBuffer(&p_frame_info->data_buffer, METER_CMD_FORMAT_ERROR_UNSUPPORTED_AREA);
    }

    /* Send reply buffer */
    R_METER_CMD_PackAndSendResFrame(p_frame_info);

    /* Post action after reply */
    if (result == TRUE)
    {
        /* Reset meter to properly format the memory */
        if ((mem_type & METER_CMD_MEM_TYPE_EEPROM) ||
            (mem_type & METER_CMD_MEM_TYPE_DATAFLASH))
        {
            WRP_EXT_SoftReset();
        }
        else
        {
            /* No process */
        }
    }

    return result;
}

/***********************************************************************************************************************
* Function Name: R_METER_CMD_ProcessCmdMemoryFormat
* Description  : Entry function to process for memory format command
* Arguments    : MeterCmdDataBuffer * p_req_buffer
*              : MeterCmdFrameInfo * p_frame_info
* Return Value : uint8_t: 0: if ok, others: error
***********************************************************************************************************************/
uint8_t R_METER_CMD_ProcessCmdMemoryFormat(MeterCmdDataBuffer * p_req_buffer, MeterCmdFrameInfo * p_frame_info)
{
    /* Length: args */
    /* Arguments layout
     * 1byte: Memory frame_type
     * 1byte: Memory area mask
    */

    uint8_t mem_type;
    uint8_t area, result;

    /* Check parameter length */
    METER_CMD_CHECK_EXPECTED_LENGTH(METER_CMD_FORMAT_EXPECTED_ARGS_LENGTH);

    /* Decode parameters */
    mem_type = R_METER_CMD_DecodeBufferToUInt8(p_req_buffer);
    area = R_METER_CMD_DecodeBufferToUInt8(p_req_buffer);

    result = r_meter_cmd_do_memory_format(p_frame_info, mem_type, area);

    return 0;
}

#endif
