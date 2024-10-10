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
* Copyright (C) 2015, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : bl_run_on_ram.c
* Version      : 
* Device(s)    : 
* Tool-Chain   : 
* Description  : 
* Creation Date: 
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <string.h>
#include "bl_header.h"
#include "fsl.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
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

/* =================================================== Code in ROM ================================================== */
#if (WARMBOOT == 1)
/***********************************************************************************************************************
* Function Name: void BL_RunOnRam_PrepareFunctions(void)
* Description  : Prepare to run wrapper and metrology on RAM
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
void BL_RunOnRam_PrepareFunctions(void)
{
    BL_ROMIZING_SECTION("BLRamTx_f", "BLRamTxR_n");
    memset(__sectop("Prefetch"), 0, 10);
}

/***********************************************************************************************************************
* Function Name: void BL_RunOnRam_DisableInterruptsExceptMetrology(void)
* Description  : Mask off all other interrupts except metrology
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint16_t BL_StopInterruptAndBankSwap(void)
{
    uint16_t status;

    /* Prepare functions on RAM */
    BL_RunOnRam_PrepareFunctions();
    
    /* Swap with interrupt run on RAM */
    status = BL_FLASH_Prepare();
	
    if (status != BL_OK) { 
		return status; 
	}
    else {			
	    /* Swap flow:
	     * ISR --> RAM (preset function pointer set in BL_FLASH_SetRamIsrFunction)
	     * Swap
	     * ISR --> ROM
	     * Jump bankswap entry
	     * ** If bank swap error, return status code
	    */
	    DI();
	    
	    status = FSL_SwapActiveBootCluster();
		BL_FLASH_CleanUp();
	    if (status != FSL_OK) 
	    { 
	        status |= BL_ERROR_FUNC_FSL_SwapActiveBootCluster;			
			EI();			
	    }
	    else
	    {
	        status = BL_OK;		
			/* Jump to branch bank swap entry */
	        BL_FLASH_RAM_JumpBankSwapEntry();
	    }
	     		
	    return status;
		}

}

#else

/***********************************************************************************************************************
* Function Name: void BL_StopInterruptAndBankSwapReset(void)
* Description  : Invert boot flag and reset
* Arguments    : None
* Return Value : uint16_t
***********************************************************************************************************************/
#ifdef __ICCRL78__
__root
#endif
uint16_t BL_StopInterruptAndBankSwapReset(void)
{
    uint16_t status;
    
    status = BL_FLASH_Prepare();
	
    if (status != BL_OK) 
    { 
		return status; 
	}
    else 
    {
	    /* Swap flow: Invert boot flag then reset MCU to swap the bank
	    */
	    DI();
	    
	    status = FSL_InvertBootFlag();
		BL_FLASH_CleanUp();
        
	    if (status != FSL_OK) 
	    { 
	        status |= BL_ERROR_FUNC_FSL_InvertBootFlag;			
			EI();
	    }
	    else
	    {
	        status = BL_OK;
			/* Force reset, no need presetting when calling FSL_ForceReset */
            BL_OPERATION_RequestUserReset();
            #if (RST_CHOICE == 1)
            FSL_ForceReset();
            #elif (RST_CHOICE == 0)
            WDTE = 0; while(1);
            #endif
	    }
        
	    return status;
	}
}
#endif /* WARMBOOT == 1 */
