/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class41.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS41_H
#define _R_DLMS_CLASS41_H
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

/* child record for 1 object of class 41 */
typedef struct tag_class41_child_record_t
{
	uint8_t			logical_name[6];		/* Logical name (OBIS code) of the object. */
	access_right_t	*p_access_right;		/* Access right definition for 1 object    */
	uint16_t		*p_tcp_udp_port;		/* TCP-UDP Port */
	FixedString		*p_ip_reference;		/* IP reference object (logical name) */
	uint16_t		*p_mss;					/* (TCP only) Maximum Segment Size */
	uint8_t			*p_nb_of_sim_conn;		/* Number of simultaneous connnection */
	uint16_t		*p_inactivity_time_out;	/* Inactivity timeout (second) */
} class41_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class41_child_record_t g_objects_child_table_class41[];			/* Import from objects : child table defintion for class 41 */
extern const uint16_t				g_objects_child_table_class41_length;		/* Import from objects : length of child table defintion of class 41 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass41(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class41Init(void);
void R_DLMS_CLASSES_Class41PollingProcessing(void);
void R_DLMS_CLASSES_Class41AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class41AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass41(distributor_params_t *p_params);

/* Macro redirect */
#define R_DLMS_IC41_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC41_REDIRECT_03(p_params, p_attribute, size)	p_attribute = R_DLMS_CLASSES_CreatNew_Fixedstring(p_params, size)
#define R_DLMS_IC41_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC41_REDIRECT_05(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)
#define R_DLMS_IC41_REDIRECT_06(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)

#endif /* _R_DLMS_CLASS41_H */