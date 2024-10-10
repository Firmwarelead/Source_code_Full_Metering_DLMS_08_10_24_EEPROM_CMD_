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
* File Name    : bl_header.h
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : 
* Description  : 
***********************************************************************************************************************/
#ifndef __BL_HEADER_H
#define __BL_HEADER_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"
#include "compiler.h"

#include "bl_wrp_properties.h"
#include "bl_platform.h"
#include "bl_main.h"
#include "bl_core.h"
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Define 1 to swap bank without reset on image activation
 * Define 0 to swap bank with reset on image activation
 * The same definition in bl_config.inc need to be same value with this definition
 * Note: 
 * Project options when changing from setting WARMBOOT 0 to WARMBOOT 1
 *  CCRL:
 *      Linker Section -ROm option: add
 *              BLRamTx_f=BLRamTxR_n
 *              FSL_RCD=FSL_RCDR
 *      Linker Section -STARt option: add FSL and Prefetch after BLNoInit
 *              BLNoInit_n,FSL_RCDR,Prefetch_FSL,BLRamTxR_n,Prefetch/f8300
 *      Linker Section -FSymbol: add
 *              BLRamTx_f
 */
#define WARMBOOT    (1)

/* Define 1 to swap and reset using FSL_ForceReset
 * Define 0 to swap and reset using WDT reset
 */
#define RST_CHOICE  (0)

/***********************************************************************************************************************
Typedef definitions (required defined macro)
***********************************************************************************************************************/

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/

#endif /* __BL_HEADER_H */