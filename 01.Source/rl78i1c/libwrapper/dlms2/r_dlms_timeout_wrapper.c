/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_timeout_wrapper.c
* Version      : 1.00
* Device(s)    : R5F564MLCxDC
* Tool-Chain   : CCRX
* H/W Platform : RX64M RSK+
* Description  : Timeout wrapper for HDLC layer
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 18.05.2016 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_tau.h"
#include "r_cg_wdt.h"

#include "typedef.h"
#include "r_dlms_timeout_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name : TIMEOUT_DEVICE_Init
* Interface     : void TIMEOUT_DEVICE_Init(void)
* Description   : Initial Timeout device driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void TIMEOUT_DEVICE_Init(void)
{
    /* Do nothing here, initialize 1ms timeout timer outside */
}

/******************************************************************************
* Function Name : TIMEOUT_DEVICE_Start
* Interface     : void TIMEOUT_DEVICE_Start(void)
* Description   : Start Timeout device driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void TIMEOUT_DEVICE_Start(void)
{
    R_TAU0_Channel0_Start();
}

/******************************************************************************
* Function Name : TIMEOUT_DEVICE_Stop
* Interface     : void TIMEOUT_DEVICE_Stop(void)
* Description   : Stop Timeout device driver
* Arguments     : None
* Return Value  : None
******************************************************************************/
void TIMEOUT_DEVICE_Stop(void)
{
    R_TAU0_Channel0_Stop();
}

/******************************************************************************
* Function Name : TIMEOUT_DEVICE_WdtRestart
* Interface     : void TIMEOUT_DEVICE_WdtRestart(void)
* Description   : WDT restart (feed WDT) for library to continue some long processing time jobs
* Arguments     : None
* Return Value  : None
******************************************************************************/
void TIMEOUT_DEVICE_WdtRestart(void)
{
	R_WDT_Restart();
}

