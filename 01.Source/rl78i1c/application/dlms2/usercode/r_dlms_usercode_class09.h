/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class09.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS09_H
#define R_DLMS_USERCODE_CLASS09_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class09.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const script_array_t g_dlms_ic09_obj00_att02_scripts;
extern const script_array_t g_dlms_ic09_obj01_att02_scripts;
extern const script_array_t g_dlms_ic09_obj02_att02_scripts;
extern const script_array_t g_dlms_ic09_obj03_att02_scripts;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic09_obj00_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client);
uint8_t R_DLMS_USER_ic09_obj01_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client);
uint8_t R_DLMS_USER_ic09_obj02_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client);
uint8_t R_DLMS_USER_ic09_obj03_meth01_action(distributor_params_t * p_params, uint16_t * p_data_from_client);

#endif /* R_DLMS_USERCODE_CLASS09_H */