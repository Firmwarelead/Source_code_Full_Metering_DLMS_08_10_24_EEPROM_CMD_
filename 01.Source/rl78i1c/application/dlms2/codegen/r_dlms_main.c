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
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_main.c
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"
#include "r_dlms_classes.h"
#include "r_dlms_objects.h"

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
* Function Name : R_DLMS_Init
* Interface     : void R_DLMS_Init()
* Description   : DLMS Initialize
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_MAIN_Init(void)
{
	/* Init DLMS Library */
	R_DLMS_Init();

	/* Init for each components */
    R_DLMS_CONFIG_Init();
    R_DLMS_CLASSES_Init();
    R_DLMS_OBJECTS_Init();
}

/******************************************************************************
* Function Name : R_DLMS_MAIN_PollingProcessing
* Interface     : void R_DLMS_MAIN_PollingProcessing()
* Description   : DLMS Polling Process for main() infinite loop
* Arguments     : None
* Function Calls: None
* Return Value  : None
******************************************************************************/
void R_DLMS_MAIN_PollingProcessing(void)
{
	/* Polling processing for library */
	R_DLMS_PollingProcessing();

	/* Polling processing for each components */
    R_DLMS_CONFIG_PollingProcessing();
    R_DLMS_CLASSES_PollingProcessing();
    R_DLMS_OBJECTS_PollingProcessing();
}
