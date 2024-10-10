/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : bl_core.h
* Version      : 1.0
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY  Version  Description
*         : 25.05.2020  1.0  Initial release
***********************************************************************************************************************/

#ifndef __BL_CORE_H
#define __BL_CORE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "compiler.h"

#include "bl_flash.h"
#include "bl_hashing.h"
#include "bl_image.h"
#include "bl_operation.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Error code for bootloader APIs */
#define BL_OK                                           (0x0000)
#define BL_ERROR_NULL_POINTER                           (0x0100)
#define BL_ERROR_ZERO_SIZE                              (0x0200)
#define BL_ERROR_ADDRESS_RANGE                          (0x0300)
#define BL_ERROR_DATA_CORRUPT                           (0x0400)
#define BL_ERROR_UNKNOWN_BANK_SELECTION                 (0x0500)

/* Error code for FSL related operation */
#define BL_ERROR_FUNC_FSL_Init                          (0x8100)
#define BL_ERROR_FUNC_FSL_BlankCheck                    (0x8200)
#define BL_ERROR_FUNC_FSL_Erase                         (0x8300)
#define BL_ERROR_FUNC_FSL_IVerify                       (0x8400)
#define BL_ERROR_FUNC_FSL_Write                         (0x8500)
#define BL_ERROR_FUNC_FSL_StatusCheck                   (0x8600)
#define BL_ERROR_FUNC_FSL_StandBy                       (0x8700)
#define BL_ERROR_FUNC_FSL_WakeUp                        (0x8800)
#define BL_ERROR_FUNC_FSL_GetSecurityFlags              (0x8900)
#define BL_ERROR_FUNC_FSL_GetBootFlag                   (0x8A00)
#define BL_ERROR_FUNC_FSL_GetSwapState                  (0x8B00)
#define BL_ERROR_FUNC_FSL_GetBlockEndAddr               (0x8C00)
#define BL_ERROR_FUNC_FSL_GetFlashShieldWindow          (0x8D00)
#define BL_ERROR_FUNC_FSL_SetBlockEraseProtectFlag      (0x8E00)
#define BL_ERROR_FUNC_FSL_SetWriteProtectFlag           (0x8F00)
#define BL_ERROR_FUNC_FSL_SetBootClusterProtectFlag     (0x9000)
#define BL_ERROR_FUNC_FSL_InvertBootFlag                (0x9100)
#define BL_ERROR_FUNC_FSL_SetFlashShieldWindow          (0x9200)
#define BL_ERROR_FUNC_FSL_SwapBootCluster               (0x9300)
#define BL_ERROR_FUNC_FSL_SwapActiveBootCluster         (0x9400)

/***********************************************************************************************************************
Global Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
External global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions
***********************************************************************************************************************/

#endif /* __BL_CORE_H */
