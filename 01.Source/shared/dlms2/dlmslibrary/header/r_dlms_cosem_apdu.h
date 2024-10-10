/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_cosem_apdu.h
* Version      : 1.00
* Description  : DLMS Cosem Application Layer APDU
******************************************************************************
* History : DD.MM.YYYY Version               Description
*         : 16.06.2016 1.0 Green Book 7th    Initial version (Client)
*         : 16.08.2017 1.1 Green Book 8th    Support all Client & Server APDU
******************************************************************************/

#ifndef _R_DLMS_COSEM_APDU_H
#define _R_DLMS_COSEM_APDU_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_cosem_apdutag.h"

/******************************************************************************
Macro definitions (module optimization)
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/

/* Consider to increase max support of protection layer if required */
#define	COSEM_MAX_PROTECTION_LEVEL		(3)

/* Size specified for GET/SET/ACTION request/response list */
#define	COSEM_GET_LIST_MAX_SIZE		    10
#define	COSEM_SET_LIST_MAX_SIZE		    10
#define	COSEM_ACTION_LIST_MAX_SIZE	    10

/* For comformance bit definition */
#define CONFORMANCE_BYTE0_NONE						(0x00)	/* All byte 0 are marked as none support for all  */
#define CONFORMANCE_BYTE0_RESERVED0					(0x80)	/* Bit 00 (Reserved 0)                            */
#define CONFORMANCE_BYTE0_GENERAL_PROTECTION		(0x40)  /* Bit 01 general-protection                      */
#define CONFORMANCE_BYTE0_GENERAL_BLOCK_TRANSFER	(0x20)  /* Bit 02 general-block-transfer                  */
#define CONFORMANCE_BYTE0_SN_READ					(0x10)	/* Bit 03 read                 (SN Referencing)   */
#define CONFORMANCE_BYTE0_SN_WRITE					(0x08)  /* Bit 04 write                (SN Referencing)   */
#define CONFORMANCE_BYTE0_SN_UNCONFIRMED_WRITE		(0x04)  /* Bit 05 unconfirmed-write    (SN Referencing)   */
#define CONFORMANCE_BYTE0_RESERVED6					(0x02)  /* Bit 06 (Reserved 6)                            */
#define CONFORMANCE_BYTE0_RESERVED7					(0x01)  /* Bit 07 (Reserved 7)                            */
#define CONFORMANCE_BYTE0_LN_ALL					(0x60)	/* All bits are marked as all support for LN      */
#define CONFORMANCE_BYTE0_SN_ALL					(0x7C)	/* All bits are marked as all support for SN      */

#define CONFORMANCE_BYTE1_NONE						(0x00)	/* All byte 1 are marked as none support for all  */
#define CONFORMANCE_BYTE1_LN_ATTR0_SET				(0x80)	/* Bit 08 attribute0-supported-with-set (LN)      */
#define CONFORMANCE_BYTE1_LN_PRIORITY_MGMT			(0x40)  /* Bit 09 priority_mgmt_supported       (LN)      */
#define CONFORMANCE_BYTE1_LN_ATTR0_GET				(0x20)  /* Bit 10 attribute0-supported-with-get (LN)      */
#define CONFORMANCE_BYTE1_BLOCK_TRANSFER_GET		(0x10)  /* Bit 11 block-transfer-with-get                 */
#define CONFORMANCE_BYTE1_BLOCK_TRANSFER_SET		(0x08)  /* Bit 12 block-transfer-with-set                 */
#define CONFORMANCE_BYTE1_LN_BLOCK_TRANSFER_ACTION	(0x04)  /* Bit 13 block-transfer-with-action    (LN)      */
#define CONFORMANCE_BYTE1_MULTI_REFERENCES			(0x02)  /* Bit 14 multiple-references                     */
#define CONFORMANCE_BYTE1_SN_INFORMATION_REPORT		(0x01)  /* Bit 15 information-report   (SN Referencing)   */
#define CONFORMANCE_BYTE1_LN_ALL					(0xFE)	/* All bits are marked as all support for LN      */
#define CONFORMANCE_BYTE1_SN_ALL					(0x1B)	/* All bits are marked as all support for SN      */

#define CONFORMANCE_BYTE2_NONE						(0x00)	/* All byte 2 are marked as none support for all  */
#define CONFORMANCE_BYTE2_DATA_NOTIFICATION  		(0x80)	/* Bit 16 data-notification                       */
#define CONFORMANCE_BYTE2_LN_ACCESS					(0x40)  /* Bit 17 access                                  */
#define CONFORMANCE_BYTE2_SN_PARAMETERIZED_ACCESS	(0x20)  /* Bit 18 parameterized-access (SN Referencing)   */
#define CONFORMANCE_BYTE2_LN_GET					(0x10)  /* Bit 19 get                           (LN)      */
#define CONFORMANCE_BYTE2_LN_SET					(0x08)  /* Bit 20 set                           (LN)      */
#define CONFORMANCE_BYTE2_LN_SELECTIVE_ACCESS		(0x04)  /* Bit 21 selective-access              (LN)      */
#define CONFORMANCE_BYTE2_LN_EVENT_NOTIFICATION		(0x02)  /* Bit 22 event-notification            (LN)      */
#define CONFORMANCE_BYTE2_LN_ACTION					(0x01)  /* Bit 23 action                        (LN)      */
#define CONFORMANCE_BYTE2_LN_ALL					(0xDF)	/* All bits are marked as all support for LN      */
#define CONFORMANCE_BYTE2_SN_ALL					(0xA0)	/* All bits are marked as all support for SN      */

/* For context_id of application context name */
#define CONTEXT_ID1_LN_NO_CIPHERING					(1)		/* Logical_Name_Referencing_No_Ciphering   - context_id(1) */
#define CONTEXT_ID2_SN_NO_CIPHERING					(2)		/* Short_Name_Referencing_No_Ciphering     - context_id(2) */
#define CONTEXT_ID3_LN_WITH_CIPHERING				(3)		/* Logical_Name_Referencing_With_Ciphering - context_id(3) */
#define CONTEXT_ID4_SN_WITH_CIPHERING				(4)		/* Short_Name_Referencing_With_Ciphering   - context_id(4) */

/* For mechanism_id of mechanism context name */
#define MECHANISM_ID0_LOWEST_SECURITY				(0)		/* COSEM_lowest_level_security_mechanism_name              - mechanism_id(0) */
#define MECHANISM_ID1_LOW_SECURITY					(1)		/* COSEM_low_level_security_mechanism_name                 - mechanism_id(1) */
#define MECHANISM_ID2_HIGH_SECURITY					(2)		/* COSEM_high_level_security_mechanism_name                - mechanism_id(2) */
#define MECHANISM_ID3_HIGH_SECURITY_MD5				(3)		/* COSEM_high_level_security_mechanism_name_using_MD5      - mechanism_id(3) */
#define MECHANISM_ID4_HIGH_SECURITY_SHA1			(4)		/* COSEM_high_level_security_mechanism_name_using_SHA-1    - mechanism_id(4) */
#define MECHANISM_ID5_HIGH_SECURITY_GMAC			(5)		/* COSEM_High_Level_Security_Mechanism_Name_Using_GMAC     - mechanism_id(5) */
#define MECHANISM_ID6_HIGH_SECURITY_SHA256			(6)		/* COSEM_High_Level_Security_Mechanism_Name_Using_SHA-256  - mechanism_id(6) */
#define MECHANISM_ID7_HIGH_SECURITY_ECDSA			(7)		/* COSEM_High_Level_Security_Mechanism_Name_Using_ECDSA    - mechanism_id(7) */

#define ENCODE_LENGTH_AND_MOVE_CONTENT(tag, buffer_length, length_byte) {	\
	(length_byte) = R_BER_LengthEncode(&((tag)->Length0), buffer_length);   \
	if ((length_byte) < BER_MAX_LENGTH_BYTE) {                              \
		memmove(                                                             \
			(&(tag)->Tail) - (BER_MAX_LENGTH_BYTE - (length_byte)),         \
			(&(tag)->Tail),                                                 \
			buffer_length                                                   \
		);                                                                  \
	}																	    \
}

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Mandatory string */
typedef struct
{
	uint8_t  *p_content;
	uint16_t length;
} MandatoryString;

/* Optional string */
typedef struct
{
	uint8_t	 use;
	uint8_t  *p_content;
	uint16_t length;
} OptionalString;

/* Optional integer */
typedef struct
{
	uint8_t use;
	uint8_t value;
} OptionalInteger;

/* Security policy */
typedef enum
{
    /*
     * Version 0 - Value base selection, select one only
     */
    SECURITY_NONE = 0,                      /* nothing */
    SECURITY_AUTHENTICATED = 1,             /* all messages to be authenticated */
    SECURITY_ENCRYPTED = 2,                 /* all messages to be encrypted */
    SECURITY_AUTHENTICATED_ENCRYPTED = 3,   /* all messages to be authenticated and encrypted  */

    /*
     * Version 1 - Bitwise selection, multiple selections are allowable
     */
    SECURITY_V1_NONE = 0x00,                            /* nothing */
    SECURITY_V1_BIT2_AUTHENTICATED_REQUEST = 0x04,      /* authenticated request */
    SECURITY_V1_BIT3_ENCRYPTED_REQUEST = 0x08,          /* encrypted request */
    SECURITY_V1_BIT4_DIGITAL_SIGNED_REQUEST = 0x10,     /* digital signed request */
    SECURITY_V1_BIT5_AUTHENTICATED_RESPONSE = 0x20,     /* authenticated response */
    SECURITY_V1_BIT6_ENCRYPTED_RESPONSE = 0x40,         /* encrypted response */
    SECURITY_V1_BIT7_DIGITAL_SIGNED_RESPONSE = 0x80,    /* digital signed response */
} SecurityPolicy;

typedef struct
{
	uint8_t		v0_authentication			: 1;	/* Version 0, authentication required for request and response */
	uint8_t		v0_encryption				: 1;	/* Version 0, encryption required for request and response */
	uint8_t		v1_authenticated_request	: 1;	/* Version 1, Authenticated request */
	uint8_t		v1_encrypted_request		: 1;	/* Version 1, Encrypted request */
	uint8_t		v1_digital_signed_request	: 1;	/* Version 1, Digital signed request */
	uint8_t		v1_authenticated_response	: 1;	/* Version 1, Authenticated response */
	uint8_t		v1_encrypted_response		: 1;	/* Version 1, Encrypted response */
	uint8_t		v1_digital_signed_response	: 1;	/* Version 1, Digital signed response */
} SecurityPolicyBits;

/*
 * This structure is defined by Blue Book 12.2
 * Bitwise definition for access right across v0 - v3 of Association LN, class 15
 */
typedef union
{
	uint8_t			byte;

	struct {
		uint8_t		read		: 1;	/* Read */
		uint8_t		write		: 1;	/* Write */
		uint8_t		reserved	: 6;	/* Reserved */
	} class15_v0;

	struct {
		uint8_t		read			: 1;	/* Read */
		uint8_t		write			: 1;	/* Write */
		uint8_t		authenticated	: 1;	/* Need authentication for request and response */
		uint8_t		reserved		: 5;	/* Reserved */
	} class15_v1_v2;

	struct {
		uint8_t		read_access				: 1;	/* Read access */
		uint8_t		write_access			: 1;	/* Write access */
		uint8_t		authenticated_request	: 1;	/* Authenticated request */
		uint8_t		encrypted_request		: 1;	/* Encrypted request */
		uint8_t		digital_signed_request	: 1;	/* Digital signed request */
		uint8_t		authenticated_response	: 1;	/* Authenticated response */
		uint8_t		encrypted_response		: 1;	/* Encrypted response */
		uint8_t		digital_signed_response : 1;	/* Digital signed response */
	} class15_v3;

} AttributeAccessRights;

typedef union
{
	uint8_t			byte;

	struct {
		uint8_t		access		: 1;	/* Access */
		uint8_t		reserved	: 7;	/* Reserved */
	} class15_v0;

	struct {
		uint8_t		access			: 1;	/* Access */
		uint8_t		no_use0			: 1;	/* (No-use) */
		uint8_t		authenticated	: 1;	/* Need authentication for request and response */
		uint8_t		reserved		: 5;	/* Reserved */
	} class15_v1_v2;

	struct {
		uint8_t		access					: 1;	/* Access */
		uint8_t		no_use					: 1;	/* (no-use) */
		uint8_t		authenticated_request	: 1;	/* Authenticated request */
		uint8_t		encrypted_request		: 1;	/* Encrypted request */
		uint8_t		digital_signed_request	: 1;	/* Digital signed request */
		uint8_t		authenticated_response	: 1;	/* Authenticated response */
		uint8_t		encrypted_response		: 1;	/* Encrypted response */
		uint8_t		digital_signed_response : 1;	/* Digital signed response */
	} class15_v3;

} MethodAccessRights;

/* Security suit */
typedef enum
{
	SECURITY_AES_SUIT = 0,				/* Suite 0 - AES-GCM-128 for authenticated encryption and AES-128 for key wrapping */
	SECURITY_AES_SUIT_1,				/* Suite 1 - ECDH-ECDSA-AES-GCM-128-SHA256 */
	SECURITY_AES_SUIT_2,				/* Suite 2 - ECDH-ECDSA-AES-GCM-256-SHA384 */
} SecuritySuit;

/* AES-GCM Invocation Counters Pair */
typedef struct
{
	uint32_t    encryption;             /* FC for encryption, internally increased after cipher a frame */
	uint32_t    decryption;             /* FC for decryption, stored the "FC (received from Client) + 1" for verification */
} AesGcmInvocationCounters;

/* AES-GCM Encryption Key with ICs */
typedef struct
{
	MandatoryString             key;                        /* Encryption key used for AES-GCM (buffer, length) */
	AesGcmInvocationCounters    *p_invocation_counters;     /* A pair of Invocation Counters */
} AesGcmEkWithCounters;

/* Security context */
typedef struct
{
	SecurityPolicy			security_policy;			/* Security policy						*/
	SecuritySuit			security_suit;				/* Security suit						*/
	MandatoryString			client_title;				/* Client System title					*/
	MandatoryString			server_title;				/* Server System title					*/

	MandatoryString			master_key;					/* The master key (KEK)					*/
	uint8_t					use_dedicated_key;			/* Use Dedicated Keys or Global keys	*/
	uint8_t					use_broadcast_key;			/* Use Global Broadcast Keys or Unicast */
	AesGcmEkWithCounters	global_unicast_key;			/* Global unicast key					*/
	AesGcmEkWithCounters	global_broadcast_key;		/* Global broadcast key					*/
	AesGcmEkWithCounters	dedicated_unicast_key;		/* Dedicated unicast key				*/
	MandatoryString			authentication_key;			/* Authentication key					*/
} SecurityContext;

/* Security control byte */
typedef union
{
	uint8_t byte;
	struct {
		uint8_t suite_id       : 4;		/* Suite Id */
		uint8_t authentication : 1;		/* Authentication */
		uint8_t encryption     : 1;		/* Encryption */
		uint8_t keyset         : 1;		/* Keyset */
		uint8_t compression    : 1;		/* Compression */
	} bits;
} SCByte;

/* Conformance block of association */
/* Bit field info is from LSB first */
typedef union
{
	struct
	{
		uint8_t	bytes0;								/* byte 0 of conformance block                    */
		uint8_t	bytes1;								/* byte 1 of conformance block                    */
		uint8_t	bytes2;								/* byte 2 of conformance block                    */
	} bytes;
	
	struct
	{
		uint8_t	reserved7                     :1;	/* Bit 07 (Reserved 7)                            */
		uint8_t	reserved6                     :1;	/* Bit 06 (Reserved 6)                            */
		uint8_t	unconfirmed_write             :1;	/* Bit 05 unconfirmed-write    (SN Referencing)   */
		uint8_t	write                         :1;	/* Bit 04 write                (SN Referencing)   */
		uint8_t	read                          :1;	/* Bit 03 read                 (SN Referencing)   */
		uint8_t	general_block_transfer        :1;	/* Bit 02 general-block-transfer                  */		
		uint8_t	general_protection            :1;	/* Bit 01 general-protection                      */
		uint8_t	reserved0                     :1;	/* Bit 00 (Reserved 0)                            */
		
		uint8_t	information_report            :1;	/* Bit 15 information-report   (SN Referencing)   */
		uint8_t	multiple_references           :1;	/* Bit 14 multiple-references                     */
		uint8_t	block_transfer_with_action    :1;	/* Bit 13 block-transfer-with-action    (LN)      */
		uint8_t	block_transfer_with_set       :1;	/* Bit 12 block-transfer-with-set                 */
		uint8_t	block_transfer_with_get       :1;	/* Bit 11 block-transfer-with-get                 */
		uint8_t	attribute0_supported_with_get :1;	/* Bit 10 attribute0-supported-with-get (LN)      */
		uint8_t	priority_mgmt_supported       :1;	/* Bit 09 priority_mgmt_supported       (LN)      */
		uint8_t	attribute0_supported_with_set :1;	/* Bit 08 attribute0-supported-with-set (LN)      */

		uint8_t	action                        :1;	/* Bit 23 action                        (LN)      */
		uint8_t	event_notification            :1;	/* Bit 22 event-notification            (LN)      */
		uint8_t	selective_access              :1;	/* Bit 21 selective-access              (LN)      */
		uint8_t	set                           :1;	/* Bit 20 set                           (LN)      */
		uint8_t	get                           :1;	/* Bit 19 get                           (LN)      */
		uint8_t	parameterized_access          :1;	/* Bit 18 parameterized-access (SN Referencing)   */
		uint8_t	access                        :1;	/* Bit 17 access                        (LN)      */
		uint8_t	data_notification             :1;	/* Bit 16 data-notification                       */
	} bits;
} ConformanceBits;

typedef struct
{
	OptionalString 		dedicated_key;
	uint8_t				response_allowed;
	OptionalInteger		proposed_quality_of_service;
	uint8_t				proposed_dlms_version_number;
	ConformanceBits		proposed_conformance;
	uint16_t			client_max_receive_pdu_size;
} InitiateRequest;

/*
 * APDU For COSEM OPEN services
 */
 
typedef struct
{
	/* [APPLICATION 0] encoded tag is TAG_AARQ = 0x60 */
	
	uint8_t				protocol_version;			/* bit string: 1 bits */
	MandatoryString 	application_context_name;
	
	OptionalString		called_AP_title;
	OptionalString		called_AE_qualifier;
	OptionalInteger		called_AP_invocation_id;
	OptionalInteger		called_AE_invocation_id;
	
	OptionalString		calling_AP_title;
	OptionalString		calling_AE_qualifier;
	OptionalInteger		calling_AP_invocation_id;
	OptionalInteger		calling_AE_invocation_id;
	
	/* Not be present if only the kernel is used */
	OptionalInteger		sender_acse_requirements;	/* bit string: 1 bits */

	/* Present when authentication functional unit is used */
	OptionalString		mechanism_name;
	
	/* Present when authentication functional unit is used */
	OptionalString		calling_authentication_value;
	OptionalString		implementation_information;
	
	/* InitiateRequest that will be encoded into user information field */
	InitiateRequest		user_information;

} AARQ_Apdu;

typedef struct
{
	OptionalInteger		negotiated_quality_of_service;
	uint8_t				negotiated_dlms_version_number;
	ConformanceBits		negotiated_conformance;
	uint16_t			server_max_receive_pdu_size;
	uint16_t			vaa_name;
} InitiateResponse;

typedef struct
{
	ConfirmServiceError_Tag		confirm_service_error_choice_tag;
	ServiceError_Tag			service_error_choice_tag;
	uint8_t						error_detail_code;
} ConfirmServiceError;

typedef uint8_t	AssociationResult;

typedef struct
{
	AssociateSourceDiag_Tag		associate_source_diag_choice_tag;
	uint8_t						diag_detail_code;
} AssociateSourceDiag;

typedef struct
{
	/* [APPLICATION 1] encoded tag is TAG_AARQ = 0x61 */
	
	uint8_t				protocol_version;			/* bit string: 1 bits */
	MandatoryString 	application_context_name;
	AssociationResult	result;
	AssociateSourceDiag	result_source_diagnostic;
	OptionalString		responding_AP_title;
	OptionalString		responding_AE_qualifier;
	OptionalInteger		responding_AP_invocation_id;
	OptionalInteger		responding_AE_invocation_id;
	
	/* Not be present if only the kernel is used */
	OptionalInteger		responder_acse_requirements;	/* bit string: 1 bits */
	
	/* Only be present if the authentication functional unit is selected. */
	OptionalString		mechanism_name;
	
	/* Only be present if the authentication functional unit is selected */
	OptionalString		responding_authentication_value;
	OptionalString		implementation_information;
	
	/*
	 * xInitiateResponse or ConfirmedServiceError,
	 * user_information_tag could be TAG_INITIATERESPONSE,
	 * or TAG_CONFIRMEDSERVICEERROR only.
	 */
	xDLMS_Tag			user_information_tag;
	union
	{
		InitiateResponse	initiate_response;
		ConfirmServiceError	confirm_service_error;
	} user_information;
	
} AARE_Apdu;

/*
 * APDU For COSEM Release Services
 */
typedef struct
{
	uint8_t						use;
	ReleaseRequestReason_Value	value;
} OptionalReleaseRequestReason;

typedef struct
{
	uint8_t						use;
	ReleaseResponseReason_Value	value;
} OptionalReleaseResponseReason;

typedef struct
{
	OptionalReleaseRequestReason	reason;
	/* InitiateRequest that will be encoded into user information field when AA is ciphering context */
	struct
	{
		uint8_t						use;
		InitiateRequest				initiate_request;
	} user_information;
} RLRQ_Apdu;

typedef struct
{
	OptionalReleaseResponseReason	reason;
	/* InitiateResponse that will be encoded into user information field when AA is ciphering context */
	struct
	{
		uint8_t						use;
		InitiateResponse			initiate_response;
	} user_information;
} RLRE_Apdu;

/*
 * APDU For COSEM GET services
 */

/* Bitfields is from LSB first */
typedef union
{
	uint8_t		byte;
	struct
	{
		uint8_t invoke_id       :4;		/* (0-3),                                 */
		uint8_t reserved    	:2;		/* (4-5),                                 */
		uint8_t service_class 	:1;		/* (6), -- 0 = Unconfirmed, 1 = Confirmed */
		uint8_t priority 		:1;		/* (7), -- 0 = Normal, 1 = High           */
	} bits;
} InvokeIdAndPriority;

/* Bitfields is from LSB first */
typedef union
{
	uint32_t	u32;
	struct
	{
		uint32_t invoke_id         : 24;		/* (0-23),                                                  */
		uint32_t reserved          :  4;		/* (24-27),                                                 */
		uint32_t self_descriptive  :  1;		/* (28), -- 0 = Not-Self-Descriptive, 1 = Self-Descriptive  */
		uint32_t processing_option :  1;		/* (29), -- 0 = Continue on Error, 1 = Break on Error       */
		uint32_t service_class     :  1;		/* (30), -- 0 = Unconfirmed, 1 = Confirmed                  */
		uint32_t priority          :  1;		/* (31), -- 0 = Normal, 1 = High                            */
	} bits;
} LongInvokeIdAndPriority;

typedef struct
{
	uint16_t 	class_id;
	uint8_t		instance_id[6];
	uint8_t		attribute_id;
} CosemAttributeDescriptor;

typedef struct
{
	uint8_t			use;
	uint8_t			access_selector;
	MandatoryString	raw_access_parameters;	/* raw buffer, need encode outside */
} OptionalSelectiveAccessDescriptor;

typedef struct
{
	InvokeIdAndPriority					invoke_id_and_priority;
	CosemAttributeDescriptor			cosem_attribute_descriptor;
	OptionalSelectiveAccessDescriptor	access_selection;
} GetRequestNormal;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	uint32_t				block_number;
} GetRequestNext;

typedef struct
{
	CosemAttributeDescriptor			cosem_attribute_descriptor;
	OptionalSelectiveAccessDescriptor	access_selection;
} CosemAttributeDescriptorWithSelection;

typedef struct
{
	InvokeIdAndPriority						invoke_id_and_priority;
	CosemAttributeDescriptorWithSelection	attribute_descriptor_list[COSEM_GET_LIST_MAX_SIZE];
	uint16_t								attribute_descriptor_list_length;
} GetRequestWithList;

typedef struct
{
	GetRequest_Tag		request_tag;
	union
	{
		GetRequestNormal	normal;
		GetRequestNext		next;
		GetRequestWithList	with_list;
	} request;
} GetRequest_Apdu;

typedef struct
{
	GetDataResult_Tag		result_tag;
	union
	{
		MandatoryString				data;				/* raw data, need decode */
		DataAccessResult_Value		data_access_result;	/* enumerate */
	} result;
} GetDataResult;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	GetDataResult			result;
} GetResponseNormal;

typedef struct
{
	uint8_t					last_block;
	uint32_t				block_number;
	DataBlockGResult_Tag	result_tag;
	union
	{
		MandatoryString			raw_data;			/* OCTETSTRING, raw data */
		DataAccessResult_Value	data_access_result;	/* enumerate */
	} result;
} DataBlockG;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	DataBlockG				result;
} GetResponseWithDataBlock;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	GetDataResult			result_list[COSEM_GET_LIST_MAX_SIZE];
	uint16_t				result_list_length;
} GetResponseWithList;

typedef struct
{
	GetResponse_Tag		response_tag;
	union
	{
		GetResponseNormal			normal; 		
		GetResponseWithDataBlock	with_datablock;
		GetResponseWithList			with_list; 	
	} response;
} GetResponse_Apdu;

/*
 * APDU For COSEM SET services
 */
 
typedef struct
{
	uint8_t				last_block;
	uint32_t			block_number;
	MandatoryString		raw_data;	/* OCTETSTRING, raw data */
} DataBlockSA;

typedef struct
{
	InvokeIdAndPriority					invoke_id_and_priority;
	CosemAttributeDescriptor			cosem_attribute_descriptor;
	OptionalSelectiveAccessDescriptor	access_selection;
	MandatoryString						value;		/* raw data, need encoded outside before */
} SetRequestNormal;

typedef struct
{
	InvokeIdAndPriority					invoke_id_and_priority;
	CosemAttributeDescriptor			cosem_attribute_descriptor;
	OptionalSelectiveAccessDescriptor	access_selection;
	DataBlockSA							data_block;
} SetRequestWithFirstDataBlock;

typedef struct
{
	InvokeIdAndPriority					invoke_id_and_priority;
	DataBlockSA							data_block;
} SetRequestWithDataBlock;

typedef struct
{
	InvokeIdAndPriority						invoke_id_and_priority;
	CosemAttributeDescriptorWithSelection	attribute_descriptor_list[COSEM_SET_LIST_MAX_SIZE];
	uint16_t								attribute_descriptor_list_length;
	MandatoryString							value_list[COSEM_SET_LIST_MAX_SIZE];	/* Each Data (CHOICE) that encoded outside */
	uint16_t								value_list_length;
} SetRequestWithList;

typedef struct
{
	InvokeIdAndPriority						invoke_id_and_priority;
	CosemAttributeDescriptorWithSelection	attribute_descriptor_list[COSEM_SET_LIST_MAX_SIZE];
	uint16_t								attribute_descriptor_list_length;
	DataBlockSA								data_block;
} SetRequestWithListAndFirstDataBlock;

typedef struct
{
	SetRequest_Tag							request_tag;
	union
	{
		SetRequestNormal						normal;
		SetRequestWithFirstDataBlock			first_data_block;
		SetRequestWithDataBlock					data_block;
		SetRequestWithList						with_list;
		SetRequestWithListAndFirstDataBlock		with_list_first_data_block;
	} request;
} SetRequest_Apdu;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	DataAccessResult_Value	result;
} SetResponseNormal;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	uint32_t				block_number;
} SetResponseDataBlock;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	DataAccessResult_Value	result;
	uint32_t				block_number;
} SetResponseLastDataBlock;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	DataAccessResult_Value	result_list[COSEM_SET_LIST_MAX_SIZE];
	uint16_t				result_list_length;
	uint32_t				block_number;
} SetResponseLastDataBlockWithList;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	DataAccessResult_Value	result_list[COSEM_SET_LIST_MAX_SIZE];
	uint16_t				result_list_length;
} SetResponseWithList;

typedef struct
{
	SetResponse_Tag		response_tag;
	union
	{
		SetResponseNormal					normal; 					
		SetResponseDataBlock				data_block; 					
		SetResponseLastDataBlock			last_data_block; 			
		SetResponseLastDataBlockWithList	last_data_block_with_list; 	
		SetResponseWithList					with_list; 					
	} response;
} SetResponse_Apdu;

/*
 * APDU For COSEM ACTION services
 */

typedef struct
{
	uint16_t 	class_id;
	uint8_t		instance_id[6];
	uint8_t		method_id;
} CosemMethodDescriptor;
 
typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	CosemMethodDescriptor	cosem_method_descriptor;
	OptionalString			method_invocation_parameters;	/* raw data, need decode outside */
} ActionRequestNormal;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	uint32_t				block_number;
} ActionRequestNextPBlock;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	CosemMethodDescriptor	cosem_method_descriptor_list[COSEM_ACTION_LIST_MAX_SIZE];
	uint16_t				cosem_method_descriptor_list_length;
	MandatoryString			method_invocation_parameters_list[COSEM_ACTION_LIST_MAX_SIZE];		/* SEQUENCE OF Data (CHOICE) that encoded outside */
	uint16_t				method_invocation_parameters_list_length;
} ActionRequestWithList;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	CosemMethodDescriptor	cosem_method_descriptor;
	DataBlockSA				pblock;
} ActionRequestWithFirstPBlock;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	CosemMethodDescriptor	cosem_method_descriptor_list[COSEM_ACTION_LIST_MAX_SIZE];
	uint16_t				cosem_method_descriptor_list_length;
	DataBlockSA				pblock;
} ActionRequestWithListAndFirstPBlock;

typedef struct
{
	InvokeIdAndPriority		invoke_id_and_priority;
	DataBlockSA				pblock;
} ActionRequestWithPBlock;

typedef struct
{
	ActionRequest_Tag					request_tag;
	union
	{
		ActionRequestNormal					normal;
		ActionRequestNextPBlock				next_pblock;
		ActionRequestWithList				with_list;
		ActionRequestWithFirstPBlock		first_pblock;
		ActionRequestWithListAndFirstPBlock	with_list_first_pblock;
		ActionRequestWithPBlock				pblock;
	} request;
} ActionRequest_Apdu;

typedef struct
{
	uint8_t				use;
	GetDataResult		get_data_result;
} OptionalGetDataResult;

typedef struct
{
	ActionResult_Value		result;
	OptionalGetDataResult	return_parameters;
} ActionResponseWithOptionalData;

typedef struct
{
	InvokeIdAndPriority				invoke_id_and_priority;
	ActionResponseWithOptionalData	single_response;
} ActionResponseNormal;

typedef struct
{
	InvokeIdAndPriority				invoke_id_and_priority;
	DataBlockSA						pblock;
} ActionResponseWithPBlock;

typedef struct
{
	InvokeIdAndPriority				invoke_id_and_priority;
	ActionResponseWithOptionalData	list_of_responses_list[COSEM_ACTION_LIST_MAX_SIZE];
	uint16_t						list_of_responses_list_length;
} ActionResponseWithList;

typedef struct
{
	InvokeIdAndPriority				invoke_id_and_priority;
	uint32_t						block_number;
} ActionResponseNextPBlock;

typedef struct
{
	ActionResponse_Tag		response_tag;
	union
	{
		ActionResponseNormal		normal;
		ActionResponseWithPBlock	with_pblock;
		ActionResponseWithList		with_list;
		ActionResponseNextPBlock	next_pblock;
	} response;
} ActionResponse_Apdu;

/*
 * APDU For COSEM EventNotification services
 */

typedef struct
{
	OptionalString				time;				/* OCTETSTRING, OPTIONAL */
	CosemAttributeDescriptor	cosem_attribute_descriptor;
	MandatoryString				attribute_value;	/* Data (CHOICE), raw encoded outside */
} EventNotificationRequest;

typedef struct
{
	LongInvokeIdAndPriority		long_invoke_id_and_priority;
	MandatoryString				date_time;
	MandatoryString				notification_body;	/* Data (CHOICE), raw encoded outside */
} DataNotification;

/*
 * APDU For COSEM ExceptionResponse
 */
 
typedef struct
{
	ExceptionResponseStateError_Value	state_error;				/* enum */
	ExceptionResponseServiceError_Value	service_error;				/* enum */
	uint32_t							invocation_counter_error;	/* when service_error = invocation-counter-error, this uint32_t is used to reply to Client */
} ExceptionResponse;

/*
 * General APDUs
 */
typedef struct
{
	MandatoryString system_title;
	MandatoryString ciphered_content;
} GeneralGloCiphering;

typedef struct
{
	MandatoryString system_title;
	MandatoryString ciphered_content;
} GeneralDedCiphering;

typedef struct
{
	KeyId_Value	key_id;
} IdentifiedKey;

typedef struct
{
	KekId_Value		kek_id;
	MandatoryString	key_ciphered_data;
} WrappedKey;

typedef struct
{
	MandatoryString	key_parameters;
	MandatoryString key_ciphered_data;
} AgreedKey;

typedef struct
{
	KeyInfo_Tag	tag;
	union {
		IdentifiedKey	identified_key;
		WrappedKey		wrapped_key;
		AgreedKey		agreed_key;
	} key;
} KeyInfo;

typedef struct
{
	uint8_t		use;
	KeyInfo		key_info;
} OptionalKeyInfo;

typedef struct
{
	MandatoryString	transaction_id;
	MandatoryString originator_system_title;
	MandatoryString recipient_system_title;
	MandatoryString date_time;
	MandatoryString other_information;
	OptionalKeyInfo	optional_key_info;
	MandatoryString	ciphered_content;
} GeneralCiphering;

typedef struct
{
	MandatoryString	transaction_id;
	MandatoryString originator_system_title;
	MandatoryString recipient_system_title;
	MandatoryString date_time;
	MandatoryString other_information;
	MandatoryString	content;
	MandatoryString	signature;
} GeneralSigning;

typedef union
{
	uint8_t	byte;
	struct
	{
		uint8_t	window	   : 6;		/* bit 0-5, window advertise */
		uint8_t	streaming  : 1;		/* bit 6, 0 = No Streaming active, 1 = Streaming active */
		uint8_t	last_block : 1;		/* bit 7, 0 = Not Last Block, 1 = Last Block */
	} bits;
} BlockControl;

typedef struct
{
	BlockControl	block_control;
	uint16_t		block_number;
	uint16_t		block_number_ack;
	MandatoryString	block_data;
} GeneralBlockTransfer;

/* Service invocation type */
typedef enum
{
	INVOCATION_COMPLETE = 0,	/* Indicate service is complete or partial */
	INVOCATION_FIRST_PART,		/* Partial, first part */
	INVOCATION_ONE_PART,		/* Partial, one part (middle) */
	INVOCATION_LAST_PART		/* Partial, last part */
} InvocationType;

/* Service Protection Type */
typedef enum
{
	PROTECTION_GLO_CIPHERING = 0,		/* Service specific global ciphering */
	PROTECTION_DED_CIPHERING,			/* Service specific dedicate ciphering */
	PROTECTION_GENERAL_GLO_CIPHERING,	/* General global ciphering */
	PROTECTION_GENERAL_DED_CIPHERING,	/* General dedicate ciphering */
	PROTECTION_GENERAL_CIPHERING,		/* General ciphering */
	PROTECTION_GENERAL_SIGNING,			/* General signing */
} ProtectionType;

/* Security Option Element */
typedef struct
{
	ProtectionType	protection_type;

	/* With General-Glo-Ciphering and General-Ded-Ciphering */
	MandatoryString system_title;

	/* With General-Ciphering and General-Signing */
	MandatoryString	transaction_id;
	MandatoryString originator_system_title;
	MandatoryString recipient_system_title;
	MandatoryString date_time;
	MandatoryString other_information;

	/* With General-Ciphering */
	OptionalKeyInfo	optional_key_info;

	/* With Glo-Ciphering, Ded-Ciphering, General-Glo-Ciphering, General-Ded-Ciphering, General-Ciphering */
	SCByte			security_control;

} SecurityOptionElement;

/* Protection Element */
typedef struct
{
	uint32_t		invocation_counter;
	MandatoryString	authen_tag;
	MandatoryString signature;
} ProtectionElement;

/* General Block Transfer Parameters */
typedef struct
{
	uint8_t			block_transfer_streaming;
	uint8_t			block_transfer_window;
} GeneralBlockTransferParams;

/* Security Option List */
typedef struct
{
	SecurityOptionElement	elements[COSEM_MAX_PROTECTION_LEVEL];
	uint16_t				usage;
} SecurityOptionList;

/* Protection output list */
typedef struct
{
	ProtectionElement		elements[COSEM_MAX_PROTECTION_LEVEL];
	uint16_t				usage;
} ProtectionOutputList;

/* Additional Service Parameters, used for COSEM services */
typedef struct
{
	InvocationType				invocation_type;		/* [In(res), Out(req)] Invocation type (COMPLETE, FIRST-PART, ONE-PART, LAST-PART) */
	SecurityOptionList			security_options;		/* [In(res), Out(req)] Security options list */
	GeneralBlockTransferParams	block_transfer_params;	/* [In(res), Out(req)] GBT params */
	ProtectionOutputList		protections;			/* [Out(req)] Protection element applied on the request */
} AdditionalServiceParams;

/* APDU dispatch context */
typedef struct
{
	uint8_t						except;					/* Execption indicator */
	uint8_t						pre_established;		/* Pre-established indicator */
	uint8_t						attribute_access_right;	/* OBIS attribute access right of related GET/SET request */
	uint8_t						method_access_right;	/* OBIS method access right of related ACTION */
	MandatoryString				apdu;					/* APDU info */
	MandatoryString				tbuf;					/* Temporary buffer share among processes, create one when DLMS Library process enter, destroy when exit */
	ExceptionResponse			*p_except_pdu;			/* Exception pdu */
	SecurityContext				*p_security_context;	/* Security context */
	AdditionalServiceParams		*p_additional_params;	/* Additional params for ciphering and GBT */
} ApduDispatchContext;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* BER Common APIs */
EXTERN_C uint8_t R_BER_LengthEncode(uint8_t *p_out_buf, uint16_t length);
EXTERN_C uint8_t R_BER_LengthDecode(uint8_t *p_in_buf, uint16_t *p_length);
EXTERN_C uint16_t R_BER_EncodeLengthAndContent(uint8_t *p_out_buf, uint8_t *p_data, uint16_t length);
EXTERN_C uint16_t R_BER_DecodeLengthAndContent(uint8_t *p_in_buf, uint8_t **p_data, uint16_t *p_length);

EXTERN_C uint16_t R_APDU_GetDataSize(
	Data_Tag	data_type,
	uint8_t 	*encoded_buf,
	uint16_t 	encoded_buf_len
);

EXTERN_C uint16_t R_APDU_EncodeCommonType(
	uint8_t 	*buf,
	uint16_t 	buf_len,
	Data_Tag	data_type,
	uint8_t		*value_buf,
	uint16_t 	value_buf_len
);

EXTERN_C uint16_t R_APDU_DecodeCommonType(
	uint8_t		*value_buf,
	uint16_t 	value_buf_len,
	Data_Tag	data_type,
	uint8_t 	*encoded_buf,
	uint16_t 	encoded_buf_len
);

EXTERN_C xDLMS_Tag R_APDU_GetRelativeServiceCipheringTag(uint8_t dedicated, xDLMS_Tag normal_tag);

/*
 * COSEM-OPEN : AARQ
 */

EXTERN_C uint16_t R_APDU_DecodeInitiateRequest(xDLMS_Tag parent_tag, InitiateRequest *p_initiate_req, uint8_t *encoded_buf, uint16_t encoded_buf_length, ApduDispatchContext *p_dispatch_context);
EXTERN_C uint16_t R_APDU_DecodeAARQ(AARQ_Apdu *p_pdu, uint8_t *encoded_buf, ApduDispatchContext *p_dispatch_context);

/*
 * COSEM-OPEN : AARE
 */

EXTERN_C uint16_t R_APDU_EncodeInitiateResponse(uint8_t *buf, InitiateResponse *p_initiate_response);
EXTERN_C uint16_t R_APDU_EncodeConfirmServiceError(uint8_t *buf, ConfirmServiceError *p_confirm_service_error);
EXTERN_C uint16_t R_APDU_EncodeAARE(uint8_t *buf, AARE_Apdu *p_pdu, ApduDispatchContext *p_dispatch_context);

/*
 * COSEM-RELEASE : RLRQ
 */
EXTERN_C uint16_t R_APDU_DecodeRLRQ(RLRQ_Apdu *p_pdu, uint8_t *encoded_buf, ApduDispatchContext *p_dispatch_context);

/*
 * COSEM-RELEASE : RLRE
 */
EXTERN_C uint16_t R_APDU_EncodeRLRE(uint8_t *buf, RLRE_Apdu *p_pdu, ApduDispatchContext *p_dispatch_context);

/*
 * COSEM-GET
 */
EXTERN_C uint16_t R_APDU_DecodeGetRequestNormal(GetRequestNormal *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeGetRequestNext(GetRequestNext *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeGetRequestWithList(GetRequestWithList *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeGetRequest(GetRequest_Apdu *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);

EXTERN_C uint16_t R_APDU_EncodeGetResponseNormal(uint8_t *buf, GetResponseNormal *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeGetResponseWithDataBlock(uint8_t *buf, GetResponseWithDataBlock *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeGetResponseWithList(uint8_t *buf, GetResponseWithList *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeGetResponse(uint8_t *buf, GetResponse_Apdu *p_pdu);

/*
 * COSEM-SET
 */
EXTERN_C uint16_t R_APDU_DecodeSetRequestNormal(SetRequestNormal *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeSetRequestWithFirstDataBlock(SetRequestWithFirstDataBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeSetRequestWithDataBlock(SetRequestWithDataBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeSetRequestWithList(SetRequestWithList *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeSetRequestWithListAndFirstDataBlock(SetRequestWithListAndFirstDataBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeSetRequest(SetRequest_Apdu *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);

EXTERN_C uint16_t R_APDU_EncodeSetResponseNormal(uint8_t *buf, SetResponseNormal *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeSetResponseDataBlock(uint8_t *buf, SetResponseDataBlock *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeSetResponseLastDataBlock(uint8_t *buf, SetResponseLastDataBlock *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeSetResponseLastDataBlockWithList(uint8_t *buf, SetResponseLastDataBlockWithList *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeSetResponseWithList(uint8_t *buf, SetResponseWithList *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeSetResponse(uint8_t *buf, SetResponse_Apdu *p_pdu);

/*
 * COSEM-ACTION
 */
EXTERN_C uint16_t R_APDU_DecodeActionRequestNormal(ActionRequestNormal *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeActionRequestNextPBlock(ActionRequestNextPBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeActionRequestWithList(ActionRequestWithList *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeActionRequestWithFirstPBlock(ActionRequestWithFirstPBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeActionRequestWithListAndFirstPBlock(ActionRequestWithListAndFirstPBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeActionRequestWithPBlock(ActionRequestWithPBlock *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);
EXTERN_C uint16_t R_APDU_DecodeActionRequest(ActionRequest_Apdu *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);

EXTERN_C uint16_t R_APDU_EncodeActionResponseWithOptionalData(uint8_t *buf, ActionResponseWithOptionalData *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeActionResponseNormal(uint8_t *buf, ActionResponseNormal *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeActionResponseWithPBlock(uint8_t *buf, ActionResponseWithPBlock *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeActionResponseWithList(uint8_t *buf, ActionResponseWithList *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeActionResponseNextPBlock(uint8_t *buf, ActionResponseNextPBlock *p_pdu);
EXTERN_C uint16_t R_APDU_EncodeActionResponse(uint8_t *buf, ActionResponse_Apdu *p_pdu);

/*
 * COSEM-EventNotification
 */
EXTERN_C uint16_t R_APDU_EncodeEventNotificationRequest(uint8_t *buf, EventNotificationRequest *p_pdu);

/*
* COSEM-DataNotification
*/
EXTERN_C uint16_t R_APDU_EncodeDataNotification(uint8_t *buf, DataNotification *p_pdu);

/*
 * COSEM-ExceptionResponse
 */
EXTERN_C uint16_t R_APDU_EncodeExceptionResponse(uint8_t *buf, ExceptionResponse *p_pdu);

/*
* General APDUs
*/

/* general-glo-ciphering */
EXTERN_C uint16_t R_APDU_EncodeGeneralGloCiphering(uint8_t *buf, GeneralGloCiphering *p_pdu);
EXTERN_C uint16_t R_APDU_DecodeGeneralGloCiphering(GeneralGloCiphering *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);

/* general-ded-ciphering */
EXTERN_C uint16_t R_APDU_EncodeGeneralDedCiphering(uint8_t *buf, GeneralDedCiphering *p_pdu);
EXTERN_C uint16_t R_APDU_DecodeGeneralDedCiphering(GeneralDedCiphering *p_pdu, uint8_t *encoded_buf, uint16_t encoded_buf_len);

/* general-block-transfer */
EXTERN_C uint16_t R_APDU_EncodeGeneralBlockTransfer(uint8_t *buf, GeneralBlockTransfer *p_pdu);

#endif /* _R_DLMS_COSEM_APDU_H */

