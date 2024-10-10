/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class64.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS64_H
#define R_DLMS_USERCODE_CLASS64_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class64.h"
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

/******************************************************************************
Functions Prototypes
******************************************************************************/
void R_DLMS_Security_FetchAllNewKey(void);
void R_DLMS_Security_Server_System_Title_Init(void);
uint8_t R_DLMS_USER_ic64_obj00_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client);
uint8_t R_DLMS_USER_ic64_obj01_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client);
uint8_t R_DLMS_USER_ic64_obj02_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client);
uint8_t R_DLMS_USER_ic64_obj03_meth02_action(distributor_params_t * p_params, class64_key_unwrapped_transfer_data_array_t * p_data_from_client);

void R_DLMS_USER_ic64_init(void);

#endif /* R_DLMS_USERCODE_CLASS64_H */