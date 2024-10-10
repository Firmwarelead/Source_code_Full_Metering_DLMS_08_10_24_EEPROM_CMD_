/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class40.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS40_H
#define R_DLMS_USERCODE_CLASS40_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class40.h"
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
extern const class40_push_object_array_t g_dlms_ic40_obj00_att02_push_object_list;
extern const uint16_t r_dlms_ic40_obj00_att04_array_length;
extern const class40_push_object_array_t g_dlms_ic40_obj01_att02_push_object_list;
extern const uint16_t r_dlms_ic40_obj01_att04_array_length;
extern const class40_push_object_array_t g_dlms_ic40_obj02_att02_push_object_list;
extern const uint16_t r_dlms_ic40_obj02_att04_array_length;
extern const class40_push_object_array_t g_dlms_ic40_obj03_att02_push_object_list;
extern const uint16_t r_dlms_ic40_obj03_att04_array_length;
extern const class40_push_object_array_t g_dlms_ic40_obj04_att02_push_object_list;
extern const uint16_t r_dlms_ic40_obj04_att04_array_length;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic40_obj00_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic40_obj01_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj01_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic40_obj02_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj02_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic40_obj03_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj03_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic40_obj04_att03_get(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att03_set(distributor_params_t * p_params, class40_send_destination_and_method_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att04_get(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att04_set(distributor_params_t * p_params, class40_comm_window_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att05_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att05_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att06_get(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att06_set(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att07_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_att07_set(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic40_obj04_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);

#endif /* R_DLMS_USERCODE_CLASS40_H */