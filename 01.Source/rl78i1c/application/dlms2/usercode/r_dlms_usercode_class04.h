/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class04.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS04_H
#define R_DLMS_USERCODE_CLASS04_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class04.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: Maximum Demand  kVA; Logical name: 1.0.9.6.0.255 */
/* Attribute 02 */
#define  CLASS04_OBJ00_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ00_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/* Index: 01; Name: Maximum Demand kW; Logical name: 1.0.1.6.0.255 */
/* Attribute 02 */
#define  CLASS04_OBJ01_ATTR02_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ01_ATTR02_SET_USERFUNCTION_ENABLE                  (FALSE)
/* Attribute 04 */
#define  CLASS04_OBJ01_ATTR04_GET_USERFUNCTION_ENABLE                  (TRUE)
#define  CLASS04_OBJ01_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const scaler_unit_t g_dlms_ic04_obj00_att03_Scaler_Unit;
extern const scaler_unit_t g_dlms_ic04_obj01_att03_Scaler_Unit;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic04_obj00_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj00_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic04_obj01_att02_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att02_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att04_get(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att04_set(distributor_params_t * p_params, choice_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_att05_get(distributor_params_t * p_params, date_time_t * p_attribute_get);
uint8_t R_DLMS_USER_ic04_obj01_meth01_action(distributor_params_t * p_params, int8_t * p_data_from_client);

#endif /* R_DLMS_USERCODE_CLASS04_H */