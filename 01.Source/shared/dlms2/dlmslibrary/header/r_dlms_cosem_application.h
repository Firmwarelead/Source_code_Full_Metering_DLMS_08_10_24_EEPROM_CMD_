/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_cosem_application.h
* Version      : 1.00
* Description  : DLMS Cosem Application Layer
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 16.06.2016 
******************************************************************************/

#ifndef _R_DLMS_COSEM_APPLICATION_H
#define _R_DLMS_COSEM_APPLICATION_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_mgmt.h"
#include "r_dlms_udp.h"
#include "r_dlms_tcp.h"
#include "r_dlms_cosem_apdu_security.h"
#include "r_dlms_cosem_apdu.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/* CF State */
typedef enum
{
	COSEM_CF_STATE_INACTIVE = 0,
	COSEM_CF_STATE_IDLE,
	COSEM_CF_STATE_ASSOCIATION_PENDING,
	COSEM_CF_STATE_ASSOCIATED,
	COSEM_CF_STATE_ASSOCIATION_RELEASE_PENDING,
} CosemCfState;

/* Service Class */
typedef enum
{
	SERVICE_CLASS_CONFIRMED = 0,	/* I frame to be sent */
	SERVICE_CLASS_UNCONFIRMED,		/* UI frame to be sent */
} ServiceClass;

typedef enum
{
	COSEM_REMOTE = 0,
	COSEM_LOCAL,
} CosemLocalOrRemote;

typedef enum
{
	COSEM_SUCCESS = 0,
	COSEM_ERROR,
} CosemResult;

typedef enum
{
	COSEM_LAYER_FAILURE_NONE = 0,
	COSEM_LAYER_FAILURE_PHY,
	COSEM_LAYER_FAILURE_DATALINK,
	COSEM_LAYER_FAILURE_APPLICATION,
} CosemLayerOfFailure;

/* COSEM-Exception Requests */
typedef struct
{
	ExceptionResponse 	exception_pdu;
} CosemExceptionRequest_Params;

/* COSEM-OPEN.Indication Parameters */
typedef struct
{
	uint8_t				protocol_version;			/* bit string: 1 bits */
	MandatoryString 	application_context_name;   /* app conext name */
	
    /* Called AP */
	OptionalString		called_AP_title;
	OptionalString		called_AE_qualifier;
	OptionalInteger		called_AP_invocation_id;
	OptionalInteger		called_AE_invocation_id;
	
    /* Calling AP */
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
	
	/* Proposed_xDLMS_Context */
	struct
	{
		OptionalString 		dedicated_key;
		uint8_t				response_allowed;
		uint8_t				proposed_dlms_version_number;
		ConformanceBits		proposed_conformance;
		uint16_t			client_max_receive_pdu_size;
	} proposed_xdlms_context;
	
	OptionalString		user_information;			/* Use for SNRM info sub field if required */
	ServiceClass		service_class;				/* Confirmed (I frame) or Unconfirmed (UI) frame */
	
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */

} CosemOpenIndication_Params;

/* COSEM-OPEN.Indication Interface Callback */
typedef void (*R_COSEM_OPEN_INDICATION_FUNC)(MgmtChannel mgmt_channel, CosemOpenIndication_Params *p_params);

/* COSEM-OPEN.Response Parameters */
typedef struct
{
	uint8_t				protocol_version;			/* bit string: 1 bits */
	MandatoryString 	application_context_name;
	AssociationResult	result;
	AssociateSourceDiag	failure_type;
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
	
	/* Negotiated_xDLMS_Context : in case of success */
	struct
	{
		uint8_t				negotiated_dlms_version_number;
		ConformanceBits		negotiated_conformance;
		uint16_t			server_max_receive_pdu_size;
		uint16_t			vaa_name;
	} negotiated_xdlms_context;
	
	/* XDLMS_Initiate_Error : in case of error */
	ConfirmServiceError		xdlms_initiate_error;
	
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */

} CosemOpenResponse_Params;

/* COSEM-RELEASE.Indication Parameters */
typedef struct
{
	uint8_t	 					    use_rlrq_rlre;	/* TRUE or FALSE */
	ReleaseRequestReason_Value		reason;			/* Value is used when use_rlrq_rlre = TRUE, else just set dummy */
	
	/* Proposed_xDLMS_Context : use if use_rlrq_rlre = TRUE & on ciphering context, else just set dummy */
	struct
	{
		OptionalString 		dedicated_key;
		uint8_t				response_allowed;
		uint8_t				proposed_dlms_version_number;
		ConformanceBits		proposed_conformance;
		uint16_t			client_max_receive_pdu_size;
	} proposed_xdlms_context;
	
	OptionalString			user_information;		/* user info for MAC disconnect */
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */

} CosemReleaseIndication_Params;

/* COSEM-RELEASE.Indication Interface Callback */
typedef void (*R_COSEM_RELEASE_INDICATION_FUNC)(MgmtChannel mgmt_channel, CosemReleaseIndication_Params *p_params);

/* COSEM-RELEASE.Response Parameters */
typedef struct
{
    uint8_t	 			use_rlrq_rlre;	/* TRUE or FALSE, use RLRQ_RLRE or not */
    
	struct
	{
		uint8_t							use;
		ReleaseResponseReason_Value		value;
	} reason;
	
	struct
	{
		uint8_t				use;
		uint8_t				negotiated_dlms_version_number;
		ConformanceBits		negotiated_conformance;
		uint16_t			server_max_receive_pdu_size;
		uint16_t			vaa_name;
	} negotiated_xdlms_context;
	CosemResult			result;					/* Mandatory */
	OptionalString		user_information;
	ApduDispatchContext	*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */

} CosemReleaseResponse_Params;

typedef struct
{
	OptionalString	diagnostics;
} CosemAbortIndication_Params;

/* COSEM-Abort.Indication Interface */
typedef void (*R_COSEM_ABORT_INDICATION_FUNC)(MgmtChannel mgmt_channel, CosemAbortIndication_Params *p_params);

/* COSEM-GET.Request Parameters */
typedef enum
{
	COSEM_GET_REQUEST_NORMAL = 0,
	COSEM_GET_REQUEST_NEXT,
	COSEM_GET_REQUEST_WITH_LIST,
} CosemGetRequestType;

typedef struct
{
	uint8_t						invoke_id;					/* use 4 low bits only */
	uint8_t						priority;					/* TRUE or FALSE */
	ServiceClass				service_class;				/* SERVICE_CLASS_CONFIRMED or SERVICE_CLASS_UNCONFIRMED */
	CosemGetRequestType			request_type;				/* NORMAL, NEXT or WITH_LIST */
	struct
	{
		CosemAttributeDescriptorWithSelection	*p_list;	/* List of attr descriptor */
		uint16_t								length;		/* List length */
	} cosem_attr_descriptor;
	uint32_t					block_number;				/* Block number in case of not use */
	ApduDispatchContext			*p_dispatch_context;		/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemGetIndication_Params;

/* COSEM-GET.Indication Interface Callback */
typedef void (*R_COSEM_GET_INDICATION_FUNC)(MgmtChannel mgmt_channel, CosemGetIndication_Params *p_params);

typedef enum
{
	COSEM_GET_RESPONSE_NORMAL = 0,
	COSEM_GET_RESPONSE_ONE_BLOCK,
	COSEM_GET_RESPONSE_LAST_BLOCK,
	COSEM_GET_RESPONSE_WITH_LIST,
} CosemGetResponseType;

typedef struct
{
	uint8_t					invoke_id;				/* use 4 low bits only */
	uint8_t					priority;				/* TRUE or FALSE */
    ServiceClass			service_class;		    /* SERVICE_CLASS_CONFIRMED or SERVICE_CLASS_UNCONFIRMED */
	CosemGetResponseType	response_type;			/* A value of CosemGetResponseType */
	union
	{
		struct
		{
			GetDataResult	*p_list;
			uint16_t		length;
		} get_data_result;
		
		DataBlockG			data_block_g;
		
	} result;
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemGetResponse_Params;

/* COSEM-Set.Request Parameters */
typedef enum
{
	COSEM_SET_REQUEST_NORMAL = 0,
	COSEM_SET_REQUEST_FIRST_BLOCK,
	COSEM_SET_REQUEST_ONE_BLOCK,
	COSEM_SET_REQUEST_LAST_BLOCK,
	COSEM_SET_REQUEST_WITH_LIST,
	COSEM_SET_REQUEST_FIRST_BLOCK_WITH_LIST,
} CosemSetRequestType;

typedef struct
{
	uint8_t					invoke_id;				/* use 4 low bits only */
	uint8_t					priority;				/* TRUE or FALSE */
	ServiceClass			service_class;			/* SERVICE_CLASS_CONFIRMED or SERVICE_CLASS_UNCONFIRMED */
	CosemSetRequestType		request_type;			/* NORMAL, FIRST_BLOCK or ONE_BLOCK, LAST_BLOCK, WITH_LIST, FIRST_BLOCK_WITH_LIST*/
	struct
	{
		CosemAttributeDescriptorWithSelection	*p_list;	/* List of attr descriptor */
		uint16_t								length;		/* List length */
	} cosem_attr_descriptor;
	struct
	{
		MandatoryString		*p_list;				/* List of data */
		uint16_t			length;					/* List length */
	} data;
	DataBlockSA				data_block_sa;			/* Data block in case of set request by block */
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemSetIndication_Params;

/* COSEM-Set.Confirm Interface */
typedef void (*R_COSEM_SET_INDICATION_FUNC)(MgmtChannel mgmt_channel, CosemSetIndication_Params *p_params);

typedef enum
{
	COSEM_SET_RESPONSE_NORMAL = 0,
	COSEM_SET_RESPONSE_ACK_BLOCK,
	COSEM_SET_RESPONSE_LAST_BLOCK,
	COSEM_SET_RESPONSE_LAST_BLOCK_WITH_LIST,
	COSEM_SET_RESPONSE_WITH_LIST,
} CosemSetResponseType;

typedef struct
{
	uint8_t					invoke_id;				/* use 4 low bits only */
	uint8_t					priority;				/* TRUE or FALSE */
    ServiceClass			service_class;			/* SERVICE_CLASS_CONFIRMED or SERVICE_CLASS_UNCONFIRMED */
	CosemSetResponseType	response_type;			/* A value of CosemSetResponseType */
	struct
	{
		DataAccessResult_Value		*p_list;
		uint16_t					length;
	} result;
	uint32_t				block_number;			/* In case of block response */
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemSetResponse_Params;

/* COSEM-Action.Request Parameters */
typedef enum
{
	COSEM_ACTION_REQUEST_NORMAL = 0,
	COSEM_ACTION_REQUEST_NEXT,
	COSEM_ACTION_REQUEST_FIRST_BLOCK,
	COSEM_ACTION_REQUEST_ONE_BLOCK,
	COSEM_ACTION_REQUEST_LAST_BLOCK,
	COSEM_ACTION_REQUEST_WITH_LIST,
	COSEM_ACTION_REQUEST_WITH_LIST_AND_FIRST_BLOCK,
} CosemActionRequestType;

typedef struct
{
	uint8_t					invoke_id;				/* use 4 low bits only */
	uint8_t					priority;				/* TRUE or FALSE */
	ServiceClass			service_class;			/* SERVICE_CLASS_CONFIRMED or SERVICE_CLASS_UNCONFIRMED */
	CosemActionRequestType	request_type;			/* NORMAL, NEXT, FIRST_BLOCK, ONE_BLOCK, LAST_BLOCK, WITH_LIST or WITH_LIST_AND_FIRST_BLOCK */
	struct
	{
		CosemMethodDescriptor		*p_list;
		uint16_t					length;
	} cosem_method_descriptor;
	struct
	{
		MandatoryString				*p_list;
		uint16_t					length;
	} method_invocation_parameters;
	DataBlockSA				data_block_sa;			/* Data block in case of action request by block */
	uint32_t				block_number;			/* Block number */
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemActionIndication_Params;

/* COSEM-Action.Confirm Interface */
typedef void (*R_COSEM_ACTION_INDICATION_FUNC)(MgmtChannel mgmt_channel, CosemActionIndication_Params *p_params);

typedef enum
{
	COSEM_ACTION_RESPONSE_NORMAL = 0,
	COSEM_ACTION_RESPONSE_ONE_BLOCK,
	COSEM_ACTION_RESPONSE_LAST_BLOCK,
	COSEM_ACTION_RESPONSE_NEXT,
	COSEM_ACTION_RESPONSE_WITH_LIST,
} CosemActionResponseType;

typedef struct
{
	uint8_t					invoke_id;				/* use 4 low bits only */
	uint8_t					priority;				/* TRUE or FALSE */
    ServiceClass			service_class;			/* SERVICE_CLASS_CONFIRMED or SERVICE_CLASS_UNCONFIRMED */
	CosemActionResponseType	response_type;			/* A value of CosemActionResponseType */
	struct
	{
		ActionResponseWithOptionalData	*p_list;
		uint16_t						length;
	} action_response;
	DataBlockSA				data_block_sa;			/* Data block in case of set request by block */
	uint32_t				block_number;			/* In case of block response */
	ApduDispatchContext		*p_dispatch_context;	/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemActionResponse_Params;

typedef struct
{
	OptionalString				time;				            /* OCTETSTRING, OPTIONAL */
	OptionalString				app_addresses;				    /* OCTETSTRING, OPTIONAL */
	CosemAttributeDescriptor	cosem_attribute_descriptor;     /* Attribute descriptor */
	MandatoryString				attribute_value;	            /* Data (CHOICE), raw encoded */
	ApduDispatchContext			*p_dispatch_context;			/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemEventNotificationRequest_Params;

typedef struct
{
	uint32_t				    long_invoke_id;				    /* Long invoke ID */
    uint8_t						priority;			            /* TRUE or FALSE */
	OptionalString				time;				            /* OCTETSTRING, OPTIONAL */
	MandatoryString				notification_body;	            /* Data (CHOICE), raw encoded */
	ApduDispatchContext			*p_dispatch_context;			/* Apdu dispatch context, including exception pdu, security context and addtional params (ciphering | GBT) */
} CosemDataNotificationRequest_Params;

/* AA session */
typedef struct tagCosemApplicationServiceData
{
	MgmtChannel			req_mgmt_channel;
	ChannelType			req_channel_type;
	MgmtChannel			req_event_mgmt_channel;
	ChannelType			req_event_channel_type;

	MgmtChannel			cnf_mgmt_channel;
	ChannelType			cnf_channel_type;
	MacResult			cnf_result;
	
	CosemCfState		state;

	SecurityContext		*p_security_context;
	ApduDispatchContext	*p_dispatch_context;

	union
	{
		struct {
			MacAddress dest_msap;
			MacAddress src_msap;
			MacFrameType frame_type;
		} hdlc;

		struct {
			WPort local_wport;
			WPort remote_wport;
			UdpPort local_udp_port;
			UdpPort remote_udp_port;
			IpAddressPtr local_ip_address;
			IpAddressPtr remote_ip_address;

			struct {
				WPort remote_wport;
				UdpPort remote_udp_port;
				IpAddressPtr remote_ip_address;
			} event;	/* UDP Destination for Event and Data Notification */

		} udp;

		struct {
			WPort local_wport;
			WPort remote_wport;
			TcpPort local_tcp_port;
			TcpPort remote_tcp_port;
			IpAddressPtr local_ip_address;
			IpAddressPtr remote_ip_address;

			struct {
				WPort remote_wport;
				TcpPort remote_tcp_port;
				IpAddressPtr remote_ip_address;
			} event;	/* TCP Destination for Event and Data Notification */

		} tcp;

	} addr;

} CosemApplicationServiceData;

typedef uint8_t AsscChannel;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

EXTERN_C void           R_COSEM_Init(void);
EXTERN_C CosemCfState   R_COSEM_GetState(MgmtChannel mgmt_channel);
EXTERN_C void           R_COSEM_PollingProcessing(void);

/* COSEM OPEN */
EXTERN_C void 			R_COSEM_OPEN_RegisterIndicationCallback(R_COSEM_OPEN_INDICATION_FUNC func);
EXTERN_C uint8_t 		R_COSEM_OPEN_Response(MgmtChannel mgmt_channel, CosemOpenResponse_Params *p_params);

/* COSEM RELEASE */
EXTERN_C void 			R_COSEM_RELEASE_RegisterIndicationCallback(R_COSEM_RELEASE_INDICATION_FUNC func);
EXTERN_C uint8_t 		R_COSEM_RELEASE_Response(MgmtChannel mgmt_channel, CosemReleaseResponse_Params *p_params);

/* COSEM ABORT */
EXTERN_C void 			R_COSEM_ABORT_RegisterIndicationCallback(R_COSEM_ABORT_INDICATION_FUNC func);

/* COSEM GET */
EXTERN_C void 			R_COSEM_GET_RegisterIndicationCallback(R_COSEM_GET_INDICATION_FUNC func);
EXTERN_C uint8_t 		R_COSEM_GET_Response(MgmtChannel mgmt_channel, CosemGetResponse_Params *p_params);

/* COSEM SET */
EXTERN_C void 			R_COSEM_SET_RegisterIndicationCallback(R_COSEM_SET_INDICATION_FUNC func);
EXTERN_C uint8_t 		R_COSEM_SET_Response(MgmtChannel mgmt_channel, CosemSetResponse_Params *p_params);

/* COSEM ACTION */
EXTERN_C void 			R_COSEM_ACTION_RegisterIndicationCallback(R_COSEM_ACTION_INDICATION_FUNC func);
EXTERN_C uint8_t 		R_COSEM_ACTION_Response(MgmtChannel mgmt_channel, CosemActionResponse_Params *p_params);

/* COSEM EventNotification */
EXTERN_C uint8_t 		R_COSEM_EVENT_NOTIFICATION_Request(MgmtChannel mgmt_channel, CosemEventNotificationRequest_Params *p_params);
EXTERN_C uint8_t 		R_COSEM_EVENT_NOTIFICATION_SetUdpDestination(
	MgmtChannel mgmt_channel,
	WPort remote_udp_wport,
	UdpPort remote_udp_port,
	IpAddressPtr remote_ip_address
);
EXTERN_C uint8_t 		R_COSEM_EVENT_NOTIFICATION_SetTcpDestination(
	MgmtChannel mgmt_channel,
	WPort remote_tcp_wport,
	TcpPort remote_tcp_port,
	IpAddressPtr remote_ip_address
);

/* COSEM DataNotification */
EXTERN_C uint8_t 		R_COSEM_DATA_NOTIFICATION_Request(MgmtChannel mgmt_channel, CosemDataNotificationRequest_Params *p_params);
#define 				R_COSEM_DATA_NOTIFICATION_SetUdpDestination		R_COSEM_EVENT_NOTIFICATION_SetUdpDestination
#define 				R_COSEM_DATA_NOTIFICATION_SetTcpDestination		R_COSEM_EVENT_NOTIFICATION_SetTcpDestination

/* COSEM Exception */
EXTERN_C uint8_t 		R_COSEM_EXCEPT_Request(MgmtChannel mgmt_channel, CosemExceptionRequest_Params *p_params);

#endif /* _R_DLMS_COSEM_APPLICATION_H */

