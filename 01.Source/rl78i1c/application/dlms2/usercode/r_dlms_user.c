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
* File Name    : r_dlms_classes.c
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
#include "r_dlms_user.h"
#include "r_dlms_usercode_class64.h"


/* DLMS Application */
#include "r_dlms_app.h"
#include "r_dlms_security.h"
#include "r_dlms_fw_upgrade.h"
#include "r_dlms_event.h"
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
* Function Name : R_DLMS_USER_Init
* Interface     : void R_DLMS_USER_Init()
* Description   : Initiate point for OBIS User Code
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_Init(void)
{
	R_DLMS_Security_Server_System_Title_Init();
    R_DLMS_FWU_Init();
	/* Put initialization code for all of user code here */
    R_DLMS_App_Init();
	R_DLMS_Push_Init();
}

/******************************************************************************
* Function Name : R_DLMS_USER_PollingProcessing
* Interface     : void R_DLMS_USER_PollingProcessing()
* Description   : Polling processing for all user code
* Arguments     : None
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_PollingProcessing(void)
{
	/* Put polling processing code for all of user code here */
	/* Register application polling */
	R_DLMS_App_PollingProcessing();
	R_DLMS_RTC_PollingProcessing();
	R_DLMS_Event_PollingProcessing();
	R_DLMS_FWU_PollingProcess();
	R_DLMS_Push_PollingProcessing();
}

/******************************************************************************
* Function Name : R_DLMS_USER_AsscOpened
* Interface     : void R_DLMS_USER_AsscOpened(AsscConnectionSession *p_assc_session)
* Description   : Association open event callback for OBIS User Code
* Arguments     : AsscConnectionSession * p_assc_session:
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_AsscOpened(AsscConnectionSession *p_assc_session)
{
	R_DLMS_FWU_SetAssociatingStatus(1);
}

/******************************************************************************
* Function Name : R_DLMS_USER_AsscClosing
* Interface     : void R_DLMS_USER_AsscClosing(AsscConnectionSession *p_assc_session)
* Description   : Association close event callback for OBIS User Code
* Arguments     : AsscConnectionSession * p_assc_session:
* Return Value  : None
******************************************************************************/
void R_DLMS_USER_AsscClosing(AsscConnectionSession *p_assc_session)
{
	R_DLMS_FWU_SetAssociatingStatus(0);
	R_DLMS_Security_BackupAllInvocationCounter();
}
