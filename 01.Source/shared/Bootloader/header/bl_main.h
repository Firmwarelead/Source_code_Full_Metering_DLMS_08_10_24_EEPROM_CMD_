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
* File Name    : bl_main.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
***********************************************************************************************************************/
#ifndef __BL_MAIN_H
#define __BL_MAIN_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"
#include "compiler.h"
#include "bl_core.h"

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef union tagImageUpdateStatus
{
    uint16_t value;
    struct tagImageUpdateDetails
    {
        uint16_t new_update_info : 1;
        uint16_t update_sucess : 1;
        uint16_t update_failed_new_image_not_work : 1;
        uint16_t reserved : 13;
        
    } details;
} bl_image_update_status_t;

typedef struct tagBLInformation
{
    uint8_t reset_count;
    uint8_t is_user_reset;
    bl_image_update_status_t image_update;
} BL_INFORMATION;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions (required defined macro)
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern uint8_t g_bl_resf;
extern uint8_t g_bl_porsr;
#if (WARMBOOT == 1)
extern uint8_t g_bl_bankswap_startup;
#endif
extern BL_INFORMATION g_bl_info;

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
/***********************************************************************************************************************
 * Function Name: BL_IncreaseSoftwareVersion
 * Description  : Sample implementation to increase software version in 3 byte buffer
 * Arguments    : uint8_t * p_version
 * Return Value : void
 **********************************************************************************************************************/
void BL_IncreaseSoftwareVersion(uint8_t * p_version);

/***********************************************************************************************************************
 * Function Name: BL_AcknowledgeImageUpdateStatus
 * Description  : Clear image update status
 * Arguments    : void
 * Return Value : void
 **********************************************************************************************************************/
void BL_AcknowledgeImageUpdateStatus(void);

/***********************************************************************************************************************
 * Function Name: BL_GetImageUpdateStatus
 * Description  : Get image update status
 * Arguments    : void
 * Return Value : bl_image_update_status_t
 **********************************************************************************************************************/
bl_image_update_status_t BL_GetImageUpdateStatus(void);

#endif /* __BL_MAIN_H */