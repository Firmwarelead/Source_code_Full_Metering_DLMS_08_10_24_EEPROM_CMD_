/******************************************************************************
Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class15.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

/* Noted: class 15 always used */

#ifndef _R_DLMS_CLASS15_H
#define _R_DLMS_CLASS15_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_config.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
typedef struct tag_class15_user_t
{
	uint8_t		id;
	OctetString	name;
} class15_user_t;

typedef OBIS_DECLARE_FIXED_ARRAY(class15_user_t, class15_user_list_t);
#endif /* #if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2 */

typedef union tag_class15_action_data_t
{
	void			*p_all;
	OctetString		*p_m1_reply_to_hls_authentication;
	OctetString		*p_m2_change_hls_secret;
	void			*p_m3_add_object;					/* No support yet */
	void			*p_m4_remove_object;				/* No support yet */
#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
	class15_user_t	*p_m5_add_user;
	class15_user_t	*p_m6_remove_user;
#endif /* #if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2 */
} class15_action_data_t;

/* child record for 1 register activation definition */
typedef struct tag_class15_child_record_t
{
	uint8_t						logical_name[6];			/* Logical name (OBIS code) of the object. */
	access_right_t				*p_access_right;			/* Access right definition for 1 object */
	const AssociationCfg		*p_assc_config;				/* Association configuration */
#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 1
	FixedString					*p_security_setup_ref;		/* Security setup reference object OBIS codes */
#endif
#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
	class15_user_list_t			*p_user_list;				/* User list */
	class15_user_t				*p_current_user;			/* Current user */
#endif
} class15_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class15_child_record_t g_objects_child_table_class15[];			/* Import from objects : child table defintion for class 15 */
extern const uint16_t				g_objects_child_table_class15_length;		/* Import from objects : length of child table defintion of class 15 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass15(distributor_params_t *p_params);
#if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass15UserEntry, class15_user_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass15UserEntry, class15_user_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass15UserArray, class15_user_list_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass15UserArray, class15_user_list_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass15UserEntry, class15_user_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass15UserArray, class15_user_list_t);
class15_user_list_t *R_DLMS_CLASSES_RedirectClass15_UserList(distributor_params_t *p_params, class15_user_list_t *p_object, uint16_t size);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_Redirect_Class15_UserEntry, class15_user_t);

#define R_DLMS_IC15_REDIRECT_10(p_params, p_attribute, array_size)					p_attribute = R_DLMS_CLASSES_RedirectClass15_UserList(p_params, p_attribute, array_size)
#define R_DLMS_IC15_REDIRECT_11(p_params, p_attribute)								p_attribute = R_DLMS_CLASSES_Redirect_Class15_UserEntry(p_params, p_attribute)
#endif /* #if defined(CLASS_15_VERSION) && CLASS_15_VERSION >= 2 */

void R_DLMS_CLASSES_Class15Init(void);
void R_DLMS_CLASSES_Class15PollingProcessing(void);
void R_DLMS_CLASSES_Class15AsscOpening(
	AsscChannel assc,
	uint8_t *accepted,
	const AssociationCfg *p_assc_cfg,
	CosemOpenIndication_Params *p_req_params,
	CosemOpenResponse_Params *p_res_params
);
void R_DLMS_CLASSES_Class15AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class15AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass15(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS15_H */

