/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class07.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS07_H
#define R_DLMS_USERCODE_CLASS07_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class07.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: Billing profile; Logical name: 1.0.98.1.0.255 */

#define DECREASE_SELECTIVE_VALUE(x)			{ if ( (x) > 0) { (x)--;} }

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class07_obj_def_array_t g_dlms_ic07_obj00_att03_capture_objects;
extern const class07_sort_method_t g_dlms_ic07_obj00_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj00_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj01_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj01_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj01_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj01_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj01_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj01_att08_profile_entries;
extern const class07_obj_def_array_t g_dlms_ic07_obj02_att03_capture_objects;
extern const class07_sort_method_t g_dlms_ic07_obj02_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj02_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj03_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj03_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj03_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj03_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj03_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj03_att08_profile_entries;
extern const class07_obj_def_array_t g_dlms_ic07_obj04_att03_capture_objects;
extern const class07_sort_method_t g_dlms_ic07_obj04_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj04_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj05_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj05_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj05_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj05_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj05_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj05_att08_profile_entries;
extern const class07_obj_def_array_t g_dlms_ic07_obj06_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj06_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj06_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj06_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj06_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj06_att08_profile_entries;
extern const class07_obj_def_array_t g_dlms_ic07_obj07_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj07_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj07_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj07_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj08_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj08_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj08_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj08_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj09_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj09_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj09_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj09_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj10_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj10_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj10_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj10_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj11_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj11_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj11_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj11_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj12_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj12_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj12_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj12_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj13_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj13_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj13_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj13_att06_sort_object;
extern const class07_obj_def_array_t g_dlms_ic07_obj14_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj14_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj14_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj14_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj14_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj14_att08_profile_entries;
extern const class07_obj_def_array_t g_dlms_ic07_obj15_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj15_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj15_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj15_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj15_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj15_att08_profile_entries;
extern const class07_obj_def_array_t g_dlms_ic07_obj16_att03_capture_objects;
extern const uint32_t g_dlms_ic07_obj16_att04_capture_period;
extern const class07_sort_method_t g_dlms_ic07_obj16_att05_sort_method;
extern const class07_obj_def_t g_dlms_ic07_obj16_att06_sort_object;
extern const uint32_t g_dlms_ic07_obj16_att07_entries_in_use;
extern const uint32_t g_dlms_ic07_obj16_att08_profile_entries;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic07_obj00_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj00_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj00_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj00_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj00_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj01_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj02_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj02_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj02_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj02_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj02_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj02_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj03_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj04_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj04_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj04_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj04_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj04_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj04_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj05_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj06_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj07_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj07_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj07_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj07_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj07_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj08_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj08_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj08_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj08_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj08_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj09_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj09_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj09_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj09_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj09_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj10_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj10_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj10_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj10_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj10_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj11_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj11_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj11_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj11_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj11_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj12_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj12_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj12_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj12_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj12_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj13_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj13_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj13_att08_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj13_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj13_meth02_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic07_obj14_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj15_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic07_obj16_att02_get(distributor_params_t * p_params, class07_buffer_array_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS07_H */