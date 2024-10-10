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
* File Name    : r_cg_cgc.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for CGC module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
/* Start user code for include. Do not edit comment generated here */
#include "r_cg_tau.h"
#include "r_cg_sau.h"
#include "r_cg_iica.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_CGC_Create
* Description  : This function initializes the clock generator.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_Create(void)
{
    volatile uint32_t w_count;

    /* Set fMX */
    CMC = _00_CGC_HISYS_PORT | _10_CGC_SYSOSC_PERMITTED | _00_CGC_SYSOSC_UNDER10M;
    MSTOP = 1U;     /* X1 oscillator/external clock stopped */

    /* Set fIM */
    MIOEN = 0U;     /* middle-speed on-chip oscillator stopped */

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= CGC_FIMWAITTIME; w_count++)
    {
        NOP();
    }

    /* Set fPLL */
    PCKC = _00_CGC_fIH_STOP;
    DSCCTL = _00_CGC_PLL_STOP;

    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count <= CGC_FPLLWAITTIME; w_count++)
    {
        NOP();
    }

    MCKC = _00_CGC_fOCO_SELECTED;

    /* Set fSX */
    OSMC = _00_CGC_CLK_ENABLE | _00_CGC_IT_CLK_fSX_CLK;
    VRTCEN = 1U;    /* enables input clock supply */
    if (RTCPORSR == 0)
    {
        SCMC = _10_CGC_SUB_OSC | _02_CGC_NORMAL_OSCILLATION;
        XTSTOP = 0U;    /* XT1 oscillator operating */

        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count <= CGC_SUBWAITTIME; w_count++)
        {
            NOP();
        }
    }

    XT1SELDIS = 0U; /* enables clock supply */

    /* Set fSUB */
    SELLOSC = 0U;   /* sub clock (fSX) */
    /* Set fCLK */
    CSS = 0U;       /* main system clock (fMAIN) */
    /* Set fMAIN */
    MCM0 = 0U;      /* selects the main on-chip oscillator clock (fOCO) or PLL clock (fPLL) as the main system clock (fMAIN) */
    /* Set fMAIN Control */
    MCM1 = 0U;      /* high-speed on-chip oscillator clock */
    VRTCEN = 0U;    /* stops input clock supply */
}


/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_CGC_FclkUseFsub
* Description  : Use fSUB as fCLK and supply to CPU/peripherals
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_FclkUseFsub(void)
{
    uint16_t w_count;
    
    /* Select fSUB as fCLK */
    SELLOSC = 0U;   /* sub clock (fSX) */

    CSS = 1U;       /* subsystem clock (fSUB) */
    
    /* Stop High-speed on-chip clock */
    HIOSTOP = 1U;
}

/***********************************************************************************************************************
* Function Name: R_CGC_FclkUseFih
* Description  : Use fIH as fCLK and supply to CPU/peripherals
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CGC_FclkUseFih(void)
{
    volatile uint16_t w_count;
    
    /* Start fIH */
    HIOSTOP = 0U;
    
    /* Wait stabilization time */
    for (w_count = 0U; w_count <= CGC_FIHWAITTIME; w_count++)
    {
        NOP();
    }
    
    /* Select fMAIN as CPU/peripherals clock */
    CSS = 0U;
}

/******************************************************************************
* Function Name : R_CGC_OnHocoChanged
* Interface     : void R_CGC_OnHocoChanged(void)
* Description   : Call this function to update other peripheral setting based on HOCODIV
* Arguments     : None
* Return Value  : None
******************************************************************************/
static void R_CGC_OnHocoChanged(void)
{
    R_UART0_OnHocoChanged();
    R_UART2_OnHocoChanged();
}

/******************************************************************************
* Function Name : R_CGC_OperateAt24MHz
* Interface     : void R_CGC_OperateAt24MHz(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_CGC_OperateAt24MHz(void)
{
    HOCODIV = 0x00U;        /*  MCU operate at 24Mhz */
    TPS0 = _0000_TAU_CKM3_fCLK_8 | _0000_TAU_CKM2_fCLK_1 | _0000_TAU_CKM1_fCLK_0 | _0004_TAU_CKM0_fCLK_4;
    R_IICA0_SetTransClockAt24MHz();
    R_CGC_OnHocoChanged();
}

/******************************************************************************
* Function Name : R_CGC_OperateAt12MHz
* Interface     : void R_CGC_OperateAt12MHz(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_CGC_OperateAt12MHz(void)
{
    HOCODIV = 0x01U;        /*  MCU operate at 12Mhz */
    TPS0 = _0000_TAU_CKM3_fCLK_8 | _0000_TAU_CKM2_fCLK_1 | _0000_TAU_CKM1_fCLK_0 | _0003_TAU_CKM0_fCLK_3;
    R_IICA0_SetTransClockAt12MHz();
    R_CGC_OnHocoChanged();
}

/******************************************************************************
* Function Name : R_CRC_OperateAt6MHz
* Interface     : void R_CRC_OperateAt6MHz(void)
* Description   : 
* Arguments     : None:
* Function Calls: 
* Return Value  : None
******************************************************************************/
void R_CGC_OperateAt6MHz(void)
{
    HOCODIV = 0x02U;        /*  MCU operate at 6Mhz */
    TPS0 = _0000_TAU_CKM3_fCLK_8 | _0000_TAU_CKM2_fCLK_1 | _0000_TAU_CKM1_fCLK_0 | _0002_TAU_CKM0_fCLK_2;
    R_IICA0_SetTransClockAt6MHz();
    R_CGC_OnHocoChanged();
}
/* End user code. Do not edit comment generated here */
