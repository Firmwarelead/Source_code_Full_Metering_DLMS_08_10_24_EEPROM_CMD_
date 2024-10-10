/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class71.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS71_H
#define R_DLMS_USERCODE_CLASS71_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class71.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: Load limit value in kW; Logical name: 0.0.17.0.0.255 */
/* Attribute 03 */
#define  CLASS71_OBJ00_ATTR03_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS71_OBJ00_ATTR03_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS71_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS71_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE                  (TRUE)
/* Attribute 05 */
#define  CLASS71_OBJ00_ATTR05_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS71_OBJ00_ATTR05_SET_USERFUNCTION_ENABLE                  (TRUE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class71_value_definition_t g_dlms_ic71_obj00_att02_monitored_value;
extern const class71_emergency_profile_t g_dlms_ic71_obj00_att08_emergency_profile;
extern const FixedArrayUint16_t g_dlms_ic71_obj00_att09_emergency_profile_group_id_list;
extern const class71_action_t g_dlms_ic71_obj00_att11_actions;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic71_obj00_att03_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att03_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att05_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att05_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att06_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att06_set(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att07_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att07_set(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic71_obj00_att10_get(distributor_params_t * p_params, uint8_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS71_H */