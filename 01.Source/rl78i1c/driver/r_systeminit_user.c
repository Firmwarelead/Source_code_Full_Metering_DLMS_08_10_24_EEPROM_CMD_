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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_systeminit_user.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements system initializing function.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
/* Start user code for include. Do not edit comment generated here */
#include <stddef.h>
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
#define SIZEOF_HEAP  0x10
char _REL_sysheap[SIZEOF_HEAP];
const uint16_t g_cnst_REL_sizeof_sysheap = SIZEOF_HEAP;

#ifdef __CCRL__

size_t _REL_sizeof_sysheap = SIZEOF_HEAP;

#if   ( (defined __R5F10NPJIODEFINE_HEADER__) || (defined __R5F10NMJIODEFINE_HEADER__) )
    const uint16_t ram_start_addr = (0xBF00);
    const uint16_t ram_end_addr = (0xFE1F);
#elif ( (defined __R5F10NLGIODEFINE_HEADER__) || (defined __R5F10NMGIODEFINE_HEADER__) || (defined __R5F10NPGIODEFINE_HEADER__) )
    const uint16_t ram_start_addr = (0xDF00);
    const uint16_t ram_end_addr = (0xFE1F);
#elif ( (defined __R5F10NLEIODEFINE_HEADER__) || (defined __R5F10NMEIODEFINE_HEADER__) )
    const uint16_t ram_start_addr = (0xE700);
    const uint16_t ram_end_addr = (0xFE1F);
#elif ( (defined __R5F10NPLIODEFINE_HEADER__) )
    const uint16_t ram_start_addr = (0x7F00);
    const uint16_t ram_end_addr = (0xFE1F);
#endif

#endif /* __CCRL__ */ 

#ifdef __ICCRL78__

#if   ( (defined __IOR5F10NPJ_H__) || (defined __IOR5F10NMJ_H__) )
    const uint16_t ram_start_addr = (0xBF00);
    const uint16_t ram_end_addr = (0xFE1F);
#elif ( (defined __IOR5F10NLG_H__) || (defined __IOR5F10NMG_H__) || (defined __IOR5F10NPG_H__) )
    const uint16_t ram_start_addr = (0xDF00);
    const uint16_t ram_end_addr = (0xFE1F);
#elif ( (defined __IOR5F10NLE_H__) || (defined __IOR5F10NME_H__) )
    const uint16_t ram_start_addr = (0xE700);
    const uint16_t ram_end_addr = (0xFE1F);
#elif ( (defined __IOR5F10NPL_H__) )
    const uint16_t ram_start_addr = (0x7F00);
    const uint16_t ram_end_addr = (0xFE1F);
#endif

#endif /* __ICCRL78__ */

/* End user code. Do not edit comment generated here */
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
