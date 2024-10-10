/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class18.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS18_H
#define R_DLMS_USERCODE_CLASS18_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class18.h"
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
extern const uint16_t r_dlms_ic18_obj00_att03_image_transferred_blocks_status_bitstring_length;
extern const uint16_t r_dlms_ic18_obj00_att07_array_length;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic18_obj00_att02_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic18_obj00_att03_get(distributor_params_t * p_params, BitString * p_attribute_get);
uint8_t R_DLMS_USER_ic18_obj00_att04_get(distributor_params_t * p_params, uint32_t * p_attribute_get);
uint8_t R_DLMS_USER_ic18_obj00_att05_get(distributor_params_t * p_params, uint8_t * p_attribute_get);
uint8_t R_DLMS_USER_ic18_obj00_att06_get(distributor_params_t * p_params, img_transfer_status_t * p_attribute_get);
uint8_t R_DLMS_USER_ic18_obj00_att07_get(distributor_params_t * p_params, class18_image_to_activate_info_array_t * p_attribute_get);
uint8_t R_DLMS_USER_ic18_obj00_meth01_action(distributor_params_t * p_params, class18_image_transfer_inititate_t * p_data_from_client);
uint8_t R_DLMS_USER_ic18_obj00_meth02_action(distributor_params_t * p_params, class18_image_block_transfer_t * p_data_from_client);
uint8_t R_DLMS_USER_ic18_obj00_meth03_action(distributor_params_t * p_params, int8_t * p_data_from_client);
uint8_t R_DLMS_USER_ic18_obj00_meth04_action(distributor_params_t * p_params, int8_t * p_data_from_client);

#endif /* R_DLMS_USERCODE_CLASS18_H */