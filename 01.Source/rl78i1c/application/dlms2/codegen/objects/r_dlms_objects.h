/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_objects.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023 
******************************************************************************/

#ifndef _R_DLMS_OBJECTS_H
#define _R_DLMS_OBJECTS_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_config.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define DLMS_OBIS_SET_ACCESS_RIGHT(access_right_group)		(access_right_t *)g_objects_access_right_table[access_right_group]

#define USED_CLASS_01		(TRUE)
#define USED_CLASS_03		(TRUE)
#define USED_CLASS_04		(TRUE)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern uint8_t g_dlms_security_is_key_tranferred;
extern const access_right_t g_objects_access_right_table[][OBIS_NUMBER_OF_ASSOCIATION];
extern const access_right_t			g_classes_access_right_none;
/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_OBJECTS_Init(void);
void R_DLMS_OBJECTS_PollingProcessing(void);
void R_DLMS_OBJECTS_AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_OBJECTS_AsscClosing(AsscConnectionSession *p_assc_session);

void R_DLMS_OBJECTS_Class15Init(void);
void R_DLMS_OBJECTS_Class15PollingProcessing(void);
void R_DLMS_OBJECTS_Class15AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_OBJECTS_Class15AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_OBJECTS_Class15Distributor(distributor_params_t *p_params);


void R_DLMS_OBJECTS_CosemSetIndication(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params);
void R_DLMS_OBJECTS_CosemActionIndication(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params);


/*
* Macro function to enable/disable processing of each object
*/

void R_DLMS_OBJECTS_Class01Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class03Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class04Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class07Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class08Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class09Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class15Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class18Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class20Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class22Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class23Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class40Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class41Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class45Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class48Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class64Distributor(distributor_params_t *p_params);
void R_DLMS_OBJECTS_Class64CosemSetIndication(MgmtChannel mgmt_channel, CosemSetIndication_Params* p_params);
void R_DLMS_OBJECTS_Class64CosemActionIndication(MgmtChannel mgmt_channel, CosemActionIndication_Params* p_params);
void R_DLMS_OBJECTS_Class70Distributor(distributor_params_t *p_params);

void R_DLMS_OBJECTS_Class71Distributor(distributor_params_t *p_params);



#endif /* _R_DLMS_OBJECTS_H */