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
* File Name    : em_run_on_ram.c
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
#include "compiler.h"

/* Standard library */
#include <string.h>

#include "bl_core.h"
#include "bl_run_on_ram.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
extern void EM_ADC_RAM_InterruptCallback(void);

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

/* =================================================== Code in RAM ================================================== */

/* RAM ISR */
#pragma section text EMRamTx

#pragma interrupt EM_RunOnRam_RamIsr
void EM_RunOnRam_RamIsr(void)
{
    if (DSAIF)
    {
		EM_ADC_RAM_InterruptCallback();

        /* Acknowledge interrupt flag */
        DSAIF = 0;
    }
    
    /* Ignore (acknowledge but not process) other interrupts */
    IICAIF0 = 0;
    TMIF02 = 0;
    MACIF = 0;
}

#pragma section

/* =================================================== Code in ROM ================================================== */

#ifdef __CCRL__
#pragma section text    EMText
#endif

/***********************************************************************************************************************
* Function Name: void EM_RunOnRam_PrepareFunctions(void)
* Description  : Prepare to run wrapper and metrology on RAM
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void EM_RunOnRam_PrepareFunctions(void)
{
    /* Prepare RAM memory containing code */
    BL_ROMIZING_SECTION("WrpRamTx_f", "WrpRamTxR_n");
    BL_ROMIZING_SECTION("EMRamTx_f", "EMRamTxR_n");
    memset(__sectop("Prefetch"), 0, 10);
}
/***********************************************************************************************************************
 End of function EM_RunOnRam_PrepareFunctions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: void EM_RunOnRam_DisableInterruptsExceptMetrology(void)
* Description  : Mask off all other interrupts except metrology
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void EM_RunOnRam_DisableInterruptsExceptMetrology(void)
{
    /* Turn on interrupt mask for other interrupt except interrupt managed by fixed metrology
    * Only DSAD interrupt would be process in RAM by checking flag
    */
    MK0L = 0xFF;
    MK0H = 0xBF;    //bit6: IICAMK0
    MK1L = 0xFF;
    MK1H = 0xFE;    //bit8: TMMK02
    MK2L = 0xFE;    //bit0: DSAMK
    MK2H = 0xDF;    //bit5: MACMK
    MK3L = 0xFF;
    MK3H = 0xFF;
}
/***********************************************************************************************************************
 End of function EM_RunOnRam_DisableInterruptsExceptMetrology
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: void EM_RunOnRam_DisableInterruptsExceptMetrology(void)
* Description  : Mask off all other interrupts except metrology
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint16_t EM_RunOnRam_NonStopBankSwap(void)
{
    uint16_t status;

    /* Prepare functions on RAM */
    EM_RunOnRam_PrepareFunctions();
    EM_RunOnRam_DisableInterruptsExceptMetrology();
    BL_RunOnRam_PrepareFunctions();
    
    /* Swap with interrupt run on RAM */
    status = BL_FLASH_RAM_SwapBankWithRamIsr((void *)&EM_RunOnRam_RamIsr);
    if (status == BL_OK)
    {
        /* Jump to branch bank swap entry */
        BL_FLASH_RAM_JumpBankSwapEntry();
    }
    else
    {
        /* Inform status by return */
    }

    return status;
}
