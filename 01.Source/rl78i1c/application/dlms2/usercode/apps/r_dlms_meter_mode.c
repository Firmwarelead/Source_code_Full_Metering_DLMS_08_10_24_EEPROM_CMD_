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
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dlms_meter_mode.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*                16.04.2018 v1.0.1
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"
#include "r_dlms_meter_mode.h"
#include "r_dlms_date_time.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

#define NOT_SPECIFIED (0xFF)

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

uint8_t				g_dlms_metering_mode					= 0;
uint8_t				g_dlms_payment_mode						= 0;
const uint32_t		g_dlms_last_token_recharge_amount		= 0;
const date_time_t	g_dlms_last_token_recharge_time			= DATE_TIME_NOT_SPECIFIED;
const uint32_t 		g_dlms_total_amount_at_last_recharge 	= 0;
const uint32_t 		g_dlms_current_balance_amount			= 0;
const date_time_t 	g_dlms_current_balance_time				= DATE_TIME_NOT_SPECIFIED;
