/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class45.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS45_H
#define _R_DLMS_CLASS45_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

#define R_DLMS_IC45_REDIRECT_02(p_params, p_attribute, size)	p_attribute = R_DLMS_CLASSES_CreatNew_Octetstring(p_params, size)
#define R_DLMS_IC45_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC45_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectClass45QualityOfService(p_params, p_attribute)

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef struct tag_qos_element_t
{
	uint8_t precedence;
	uint8_t delay;
	uint8_t reliability;
	uint8_t peak_throughput;
	uint8_t mean_throughput;
} qos_element_t;

typedef struct tag_quality_of_service_t 
{
	qos_element_t *p_default;
	qos_element_t *p_requested;
} quality_of_service_t;

/* child record for 1 object of class 45 */
typedef struct tag_class45_child_record_t
{
	uint8_t								logical_name[6];		/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;		/* Access right definition for 1 object    */
	OctetString							*p_apn;					/* Defines the access point name of the network. */
	uint16_t							*p_pin_code;			/* Holds the personal identification number */
	quality_of_service_t				*p_quality_of_service;	/* Quality of service */
} class45_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class45_child_record_t g_objects_child_table_class45[];			/* Import from objects : child table defintion for class 45 */
extern const uint16_t				g_objects_child_table_class45_length;		/* Import from objects : length of child table defintion of class 45 */

/******************************************************************************
Functions Prototypes
******************************************************************************/
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass45QualityOfService, quality_of_service_t);
void R_DLMS_CLASSES_DistributeAbstractClass45(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class45Init(void);
void R_DLMS_CLASSES_Class45PollingProcessing(void);
void R_DLMS_CLASSES_Class45AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class45AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass45(distributor_params_t *p_params);


#endif /* _R_DLMS_CLASS45_H */

