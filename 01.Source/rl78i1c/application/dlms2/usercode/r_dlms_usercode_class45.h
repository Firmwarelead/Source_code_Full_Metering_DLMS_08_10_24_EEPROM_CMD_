/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class45.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS45_H
#define R_DLMS_USERCODE_CLASS45_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class45.h"
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
extern const uint16_t r_dlms_ic45_obj00_att02_APN_string_length;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic45_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic45_obj00_att02_set(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic45_obj00_att03_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic45_obj00_att03_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic45_obj00_att04_get(distributor_params_t * p_params, quality_of_service_t * p_attribute_get);
uint8_t R_DLMS_USER_ic45_obj00_att04_set(distributor_params_t * p_params, quality_of_service_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS45_H */