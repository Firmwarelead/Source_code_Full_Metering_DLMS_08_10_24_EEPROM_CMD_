/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class15.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS15_H
#define R_DLMS_USERCODE_CLASS15_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class15.h"
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
uint8_t R_DLMS_USER_ic15_obj01_att07_set(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic15_obj02_att07_set(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic15_obj02_meth02_action(distributor_params_t * p_params, OctetString * p_data_from_client);
uint8_t R_DLMS_USER_ic15_obj04_att07_set(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic15_obj04_meth02_action(distributor_params_t * p_params, OctetString * p_data_from_client);

void R_DLMS_USER_ic15_Init(void);

#endif /* R_DLMS_USERCODE_CLASS15_H */