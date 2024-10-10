/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_main.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef _R_DLMS_MAIN_H
#define _R_DLMS_MAIN_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_library_process.h"
#include "r_dlms_config.h"
#include "r_dlms_class01.h"
#include "r_dlms_class03.h"
#include "r_dlms_class04.h"
#include "r_dlms_class07.h"
#include "r_dlms_class08.h"
#include "r_dlms_class09.h"
#include "r_dlms_class15.h"
#include "r_dlms_class18.h"
#include "r_dlms_class20.h"
#include "r_dlms_class22.h"
#include "r_dlms_class23.h"
#include "r_dlms_class40.h"
#include "r_dlms_class41.h"
#include "r_dlms_class45.h"
#include "r_dlms_class48.h"
#include "r_dlms_class64.h"
#include "r_dlms_class70.h"
#include "r_dlms_class71.h"

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

void R_DLMS_MAIN_Init(void);
void R_DLMS_MAIN_PollingProcessing(void);

#endif /* _R_DLMS_MAIN_H */


