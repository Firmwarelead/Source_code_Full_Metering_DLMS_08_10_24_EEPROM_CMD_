/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class23.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS23_H
#define _R_DLMS_CLASS23_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum tag_class23_com_speed_t
{
	BAUD_RATE_300,
	BAUD_RATE_600,
	BAUD_RATE_1200,
	BAUD_RATE_2400,
	BAUD_RATE_4800,
	BAUD_RATE_9600,
	BAUD_RATE_19200,
	BAUD_RATE_38400,
	BAUD_RATE_57600,
	BAUD_RATE_115200
} class23_comm_speed_t;

/* child record for 1 object of class 23 */
typedef struct tag_class23_child_record_t
{
	uint8_t								logical_name[6];				/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;				/* Access right definition for 1 object    */
	class23_comm_speed_t				*p_comm_speed;					/* COM speed */
	uint8_t								*p_window_size_transmit;		/* Window size transmit */
	uint8_t								*p_window_size_receive;		/* Window size receive */
	uint16_t							*p_max_info_field_length_transmit;	/* Max info field length transmit */
	uint16_t							*p_max_info_field_length_receive;	/* Max info field length receive */
	uint16_t							*p_inter_octet_time_out;			/* Inter octet timeout */
	uint16_t							*p_inactivity_time_out;			/* Inactivity timeout */
	uint16_t							*p_device_address;				/* Device address */
} class23_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class23_child_record_t g_objects_child_table_class23[];			/* Import from objects : child table defintion for class 23 */
extern const uint16_t				g_objects_child_table_class23_length;		/* Import from objects : length of child table defintion of class 23 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass23(distributor_params_t *p_params);


void R_DLMS_CLASSES_Class23Init(void);
void R_DLMS_CLASSES_Class23PollingProcessing(void);
void R_DLMS_CLASSES_Class23AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class23AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass23(distributor_params_t *p_params);

/* Macro for redirect function */
#define R_DLMS_IC23_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_05(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_06(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_07(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_08(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC23_REDIRECT_09(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)

#endif /* _R_DLMS_CLASS23_H */

