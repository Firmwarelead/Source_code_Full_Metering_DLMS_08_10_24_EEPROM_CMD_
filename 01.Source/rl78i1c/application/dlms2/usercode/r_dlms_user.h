/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_user.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef _R_DLMS_USER_H
#define _R_DLMS_USER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_USER_Init(void);
void R_DLMS_USER_PollingProcessing(void);
void R_DLMS_USER_AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_USER_AsscClosing(AsscConnectionSession *p_assc_session);

#endif /* _R_DLMS_USERCODE_H */