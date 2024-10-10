/************************************************************************************************************************
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
* File Name    : ram_acc.c
* Version      : 1.0
* Description  : Description
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 09.04.2020  1.0  Initial release
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include <string.h>
#include "bl_header.h"
#include "fsl.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Local Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Private (static) variables and functions: RAM execution
***********************************************************************************************************************/

/* =================================================== Code in RAM ================================================== */
#if (WARMBOOT == 1)
#pragma section text BLRamTx

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
FAR_FUNC uint16_t BL_FLASH_RAM_SwapBankWithRamIsr(void * p_ram_isr)
{
    uint16_t status;

    /* Switch to RamIsr */
    status = BL_FLASH_Prepare();
    if (status != BL_OK) { return status; }
    
    /* Swap flow:
     * ISR --> RAM (preset function pointer set in BL_FLASH_SetRamIsrFunction)
     * Swap
     * ISR --> ROM
     * Jump bankswap entry
     * ** If bank swap error, return status code
    */
	
    DI();
    FSL_ChangeInterruptTable((fsl_u16)p_ram_isr);
    EI();
	
    status = FSL_SwapActiveBootCluster();
    if (status != FSL_OK) 
    { 
        status |= BL_ERROR_FUNC_FSL_SwapActiveBootCluster; 
    }
    else
    {
        status = BL_OK;
    }
	
    DI();
    FSL_RestoreInterruptTable();
    EI();

    BL_FLASH_CleanUp();

    /* May not reach here if jumped to bankswap entry */
    return status;
}
/***********************************************************************************************************************
 End of function BL_FLASH_RAM_SwapBankAndReinitializeMemory
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: BL_FLASH_RAM_JumpBankSwapEntry
 * Description  : Call to bl_properties_t.entry_func.bl_bswap (bank swap entry function)
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
FAR_FUNC void BL_FLASH_RAM_JumpBankSwapEntry(void)
{
    g_bl_properties.entry_func.bl_bswap();
}
/***********************************************************************************************************************
 End of function BL_FLASH_RAM_JumpBankSwapEntry
***********************************************************************************************************************/

#pragma section

#endif /* WARMBOOT == 1 */

