/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class20.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS20_H
#define R_DLMS_USERCODE_CLASS20_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class20.h"
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
extern const uint16_t r_dlms_ic20_obj00_att02_calendar_name_active_string_length;
extern const uint16_t r_dlms_ic20_obj00_att03_array_length;
extern const uint16_t r_dlms_ic20_obj00_att04_array_length;
extern const uint16_t r_dlms_ic20_obj00_att05_day_profile_array_length;
extern const uint16_t r_dlms_ic20_obj00_att05_day_schedule_maximum_array_length;
extern const uint16_t r_dlms_ic20_obj00_att06_calendar_name_passive_string_length;
extern const uint16_t r_dlms_ic20_obj00_att07_array_length;
extern const uint16_t r_dlms_ic20_obj00_att08_array_length;
extern const uint16_t r_dlms_ic20_obj00_att09_day_profile_array_length;
extern const uint16_t r_dlms_ic20_obj00_att09_day_schedule_maximum_array_length;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic20_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att03_get(distributor_params_t * p_params, class20_season_profile_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att04_get(distributor_params_t * p_params, class20_week_profile_table_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att05_get(distributor_params_t * p_params, class20_day_profile_table_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att06_get(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att06_set(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att07_get(distributor_params_t * p_params, class20_season_profile_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att07_set(distributor_params_t * p_params, class20_season_profile_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att08_get(distributor_params_t * p_params, class20_week_profile_table_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att08_set(distributor_params_t * p_params, class20_week_profile_table_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att09_get(distributor_params_t * p_params, class20_day_profile_table_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att09_set(distributor_params_t * p_params, class20_day_profile_table_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att10_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_att10_set(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic20_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);

void R_DLMS_USER_ic20_Init(void);
#endif /* R_DLMS_USERCODE_CLASS20_H */