/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class41.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS41_H
#define R_DLMS_USERCODE_CLASS41_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class41.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: TCP Setup 0; Logical name: 0.0.25.0.0.255 */
/* Attribute 04 */
#define  CLASS41_OBJ00_ATTR04_GET_USERFUNCTION_ENABLE                  (FALSE)
#define  CLASS41_OBJ00_ATTR04_SET_USERFUNCTION_ENABLE                  (FALSE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const uint16_t g_dlms_ic41_obj00_att02_tcp_udp_port;
extern const uint16_t g_dlms_ic41_obj00_att04_MSS;
extern const uint8_t g_dlms_ic41_obj00_att05_nb_of_sim_conn;

/******************************************************************************
Functions Prototypes
******************************************************************************/
uint8_t R_DLMS_USER_ic41_obj00_att04_get(distributor_params_t * p_params, uint16_t * p_attribute_get);
uint8_t R_DLMS_USER_ic41_obj00_att04_set(distributor_params_t * p_params, uint16_t * p_attribute_get);

#endif /* R_DLMS_USERCODE_CLASS41_H */