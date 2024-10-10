/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class47.h
* Version      : 1.00
* Version OCG  : OBIS code generator 1.0.5 - Jul 09 2021
* Description  : user code header file of class 47
******************************************************************************
* History : DD.MM.YYYY Version Description
* Generated date       : 09/08/2021
*
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS47_H
#define R_DLMS_USERCODE_CLASS47_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class47.h"
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
extern const uint16_t r_dlms_ic47_obj00_att02_Operator_string_length;
extern const uint16_t r_dlms_ic47_obj00_att07_array_length;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic47_obj00_att02_get(distributor_params_t * p_params, OctetString * p_attribute_get);
uint8_t R_DLMS_USER_ic47_obj00_att03_get(distributor_params_t * p_params, class47_status_t * p_attribute_get);
uint8_t R_DLMS_USER_ic47_obj00_att04_get(distributor_params_t * p_params, class47_cs_attachment_t * p_attribute_get);
uint8_t R_DLMS_USER_ic47_obj00_att05_get(distributor_params_t * p_params, class47_ps_status_t * p_attribute_get);
uint8_t R_DLMS_USER_ic47_obj00_att06_get(distributor_params_t * p_params, class47_cell_info_type_t * p_attribute_get);
uint8_t R_DLMS_USER_ic47_obj00_att07_get(distributor_params_t * p_params, class47_adjacent_cells_t * p_attribute_get);
uint8_t R_DLMS_USER_ic47_obj00_att08_get(distributor_params_t * p_params, date_time_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS47_H */