/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class64.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS64_H
#define _R_DLMS_CLASS64_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"
#include "r_aes_keywrap.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef uint8_t class64_security_activate_data_t;

typedef struct tag_class64_key_transfer_data_t
{
	uint8_t			key_id;
	OctetString		key_wrapped;
} class64_key_transfer_data_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class64_key_transfer_data_t, class64_key_transfer_data_array_t);

typedef struct tag_class64_key_unwrapped_transfer_data_t
{
	uint8_t			key_id;
	OctetString		key_unwrapped;
} class64_key_unwrapped_transfer_data_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class64_key_unwrapped_transfer_data_t, class64_key_unwrapped_transfer_data_array_t);

#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1

typedef enum tag_certificate_entity_t
{
	CERTIFICATE_ENTITY_SERVER,
	CERTIFICATE_ENTITY_CLIENT,
	CERTIFICATE_ENTITY_CERTIFICATION_AUTHORITY,
	CERTIFICATE_ENTITY_OTHER
} certificate_entity_t;

typedef enum tag_certificate_type_t
{
	CERTIFICATE_TYPE_DIGITAL_SIGNATURE,
	CERTIFICATE_TYPE_KEY_AGREEMENT,
	CERTIFICATE_TYPE_TLS,
	CERTIFICATE_TYPE_OTHER
} certificate_type_t;
typedef struct tag_class64_certificate_info_t
{
	certificate_entity_t certificate_entity;
	certificate_type_t	certificate_type;
	OctetString	serial_number;
	OctetString	issuer;
	OctetString	subject;
	OctetString	subject_alt_name;
} class64_certificate_info_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class64_certificate_info_t, class64_certificate_info_array_t);

typedef struct tag_class64_key_agreement_data_t
{
	uint8_t			key_id;
	OctetString		key_data;
} class64_key_agreement_data_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class64_key_agreement_data_t, class64_key_agreement_data_array_t);

typedef uint8_t class64_generate_key_pair_data_t;
typedef uint8_t class64_generate_certificate_request_data_t;
typedef OctetString	class64_import_certificate_data_t;

typedef struct tag_class64_export_certificate_data_t
{
	uint8_t	type;
	union {
		struct {
			uint8_t		entity;
			uint8_t		type;
			OctetString	title;
		} by_entity;
		struct {
			OctetString	serial_number;
			OctetString issuer;
		} by_serial;
	} options;
} class64_export_certificate_data_t;

typedef class64_export_certificate_data_t	class64_remove_certificate_data_t;

OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass64CertificateInfoArray, class64_certificate_info_array_t);
class64_certificate_info_array_t *R_DLMS_CLASSES_RedirectClass64CertificateInfoArray(distributor_params_t *p_params, class64_certificate_info_array_t *p_object, uint16_t size);
#endif

/* class64 action data */
typedef union tag_class64_action_data_t
{
	void										*p_all;
	class64_security_activate_data_t			*p_m1_security_activate;
	class64_key_transfer_data_array_t			*p_m2_key_transfer;
#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
	class64_key_agreement_data_array_t			*p_m3_key_agreement;
	class64_generate_key_pair_data_t			*p_m4_generate_key_pair;
	class64_generate_certificate_request_data_t	*p_m5_generate_certificate_request;
	class64_import_certificate_data_t			*p_m6_import_certificate;
	class64_export_certificate_data_t			*p_m7_export_certificate;
	class64_remove_certificate_data_t			*p_m8_remove_certificate;
#endif
} class64_action_data_t;
typedef enum tag_class64_security_policy_t
{
	AUTHENTICATED_REQUEST = 2,
	ENCRYPTED_REQUEST,
	DIGITALLY_SIGNED_REQUEST,
	AUTHENTICATED_RESPONSE,
	ENCRYPTED_RESPONSE,
	DIGITALLY_SIGNED_RESPONSE
} class64_security_policy_t;
typedef enum tag_class64_security_suite_t
{
	GROUP_SECURITY_SUITE_0,
	GROUP_SECURITY_SUITE_1
} class64_security_suite_t;
/* child record for 1 object of class 64 */
typedef struct tag_class64_child_record_t
{
	uint8_t								logical_name[6];			/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;			/* Access right definition for 1 object    */
	class64_security_policy_t			*p_security_policy;			/* Enforces authentication and/or encryption algorithm provided with security_suite */
	class64_security_suite_t			*p_security_suite;			/* Specifies authentication, encryption and key transport algorithm */
	FixedString							*p_client_system_title;		/* Client system title */
	FixedString							*p_server_system_title;		/* Server system title */
#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
	class64_certificate_info_array_t	*p_certificates;			/* Carries X.509 v3 certificates available and stored in the server */
#endif
} class64_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class64_child_record_t g_objects_child_table_class64[];			/* Import from objects : child table defintion for class 64 */
extern const uint16_t				g_objects_child_table_class64_length;		/* Import from objects : length of child table defintion of class 64 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass64(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class64Init(void);
void R_DLMS_CLASSES_Class64PollingProcessing(void);
void R_DLMS_CLASSES_Class64AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class64AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass64(distributor_params_t *p_params);

/* Declare redirect function */
class64_key_unwrapped_transfer_data_array_t *R_DLMS_CLASSES_RedirectKeyTransferDataAction02(distributor_params_t *p_params, class64_key_transfer_data_array_t *p_object);
/* Macro for simple attribute */
#define R_DLMS_IC64_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC64_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC64_REDIRECT_04(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectFixedString(p_params, p_attribute)
#define R_DLMS_IC64_REDIRECT_05(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectFixedString(p_params, p_attribute)
#if defined(CLASS_64_VERSION) && CLASS_64_VERSION >= 1
/* Macro for complex attribute */
#define R_DLMS_IC64_REDIRECT_06(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass64CertificateInfoArray(p_params, p_attribute, size)
#endif
#endif /* _R_DLMS_CLASS64_H */

