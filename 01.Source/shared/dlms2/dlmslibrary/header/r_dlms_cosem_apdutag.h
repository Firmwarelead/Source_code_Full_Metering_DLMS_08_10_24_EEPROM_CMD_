/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_cosem_apdutag.h
* Version      : 1.00
* Description  : DLMS Cosem Application Layer APDU Tag
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 16.06.2016 
******************************************************************************/

#ifndef _R_DLMS_COSEM_APDUTAG_H
#define _R_DLMS_COSEM_APDUTAG_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define 	BER_MAX_LENGTH_BYTE		3

/******************************************************************************
Typedef definitions
******************************************************************************/

/* xDLMS_APDU tag */
typedef enum
{
	/* standardized DLMS pdus */
	TAG_INITIATEREQUEST           	= 1  ,                            
	TAG_READREQUEST           		= 5  ,                            
	TAG_WRITEREQUEST           		= 6  ,                            
	TAG_INITIATERESPONSE           	= 8  ,                            
	TAG_READRESPONSE           		= 12 ,                            
	TAG_WRITERESPONSE           	= 13 ,                            
	TAG_CONFIRMEDSERVICEERROR       = 14 ,
	TAG_DATA_NOTIFICATION           = 15 ,
	TAG_UNCONFIRMEDWRITEREQUEST     = 22 ,                            
	TAG_INFORMATIONREPORTREQUEST    = 24 ,                            
	
	/* with global ciphering */
	TAG_GLO_INITIATEREQUEST           	= 33,                            
	TAG_GLO_READREQUEST           		= 37,                            
	TAG_GLO_WRITEREQUEST           		= 38,                            
	TAG_GLO_INITIATERESPONSE           	= 40,                            
	TAG_GLO_READRESPONSE           		= 44,                            
	TAG_GLO_WRITERESPONSE           	= 45,                            
	TAG_GLO_CONFIRMEDSERVICEERROR      	= 46,                            
	TAG_GLO_UNCONFIRMEDWRITEREQUEST    	= 54,                            
	TAG_GLO_INFORMATIONREPORTREQUEST   	= 56,  
	
	/* the four ACSE APDUs */
	TAG_AARQ                            = 0x60,	/* [APPLICATION 0] == [ 60H ] = [ 96 ] */
	TAG_AARE                            = 0x61,	/* [APPLICATION 1] == [ 61H ] = [ 97 ] */
	TAG_RLRQ                            = 0x62,	/* [APPLICATION 2] == [ 62H ] = [ 98 ] */
	TAG_RLRE                            = 0x63,	/* [APPLICATION 3] == [ 63H ] = [ 99 ] */
	
	/* with no ciphering */
	TAG_GET_REQUEST           		= 192,                            
	TAG_SET_REQUEST           		= 193,                            
	TAG_EVENT_NOTIFICATION_REQUEST  = 194,                            
	TAG_ACTION_REQUEST           	= 195,                            
	TAG_GET_RESPONSE           		= 196,                            
	TAG_SET_RESPONSE           		= 197,                            
	TAG_ACTION_RESPONSE           	= 199,
	
	/* with global ciphering */
	TAG_GLO_GET_REQUEST           		= 200,                            
	TAG_GLO_SET_REQUEST           		= 201,                            
	TAG_GLO_EVENT_NOTIFICATION_REQUEST  = 202,                            
	TAG_GLO_ACTION_REQUEST           	= 203,                            
	TAG_GLO_GET_RESPONSE           		= 204,                            
	TAG_GLO_SET_RESPONSE           		= 205,                            
	TAG_GLO_ACTION_RESPONSE           	= 207, 
	
	/* with dedicated ciphering */
	TAG_DED_INITIATEREQUEST           	= 65, 
	TAG_DED_GET_REQUEST           		= 208,                            
	TAG_DED_SET_REQUEST           		= 209,                            
	TAG_DED_EVENT_NOTIFICATION_REQUEST  = 210,                            
	TAG_DED_ACTION_REQUEST           	= 211,                            
	TAG_DED_GET_RESPONSE           		= 212,                            
	TAG_DED_SET_RESPONSE           		= 213,                            
	TAG_DED_ACTION_RESPONSE           	= 215, 
	
	/* the exception response pdu */
	TAG_EXCEPTION_RESPONSE			    = 216,
	
	/* access */
	TAG_ACCESS_REQUEST					= 217,
	TAG_ACCESS_RESPONSE					= 218,

	/* general APDUs */
	TAG_GENERAL_GLO_CIPHERING			= 219,
	TAG_GENERAL_DED_CIPHERING			= 220,
	TAG_GENERAL_CIPHERING				= 221,
	TAG_GENERAL_SIGNING					= 223,
	TAG_GENERAL_BLOCK_TRANSFER			= 224,

	/* the reserved */
	TAG_RESERVED1			    		= 230,
	TAG_RESERVED2			    		= 231,
	
} xDLMS_Tag;

typedef enum
{
	TAG_AARQ_PROTOCOLVER             = 0  ,
	TAG_AARQ_APPCONTEXT              = 1  ,
	TAG_AARQ_CALLED_AP_TITLE         = 2  ,
	TAG_AARQ_CALLED_AE_QUALIFIER     = 3  ,
	TAG_AARQ_CALLED_AP_INVOCATION    = 4  ,
	TAG_AARQ_CALLED_AE_INVOCATION    = 5  ,
	TAG_AARQ_CALLING_AP_TITLE        = 6  ,
	TAG_AARQ_CALLING_AE_QUALIFIER    = 7  ,
	TAG_AARQ_CALLING_AP_INVOCATION   = 8  ,
	TAG_AARQ_CALLING_AE_INVOCATION   = 9  ,
	TAG_AARQ_SENDER_ACSE             = 10 ,
	TAG_AARQ_MECHANISMNAME           = 11 ,
	TAG_AARQ_CALLING_AUTHENTICATION  = 12 ,
	TAG_AARQ_IMPLEMENTATIONINFO      = 29 ,     
	TAG_AARQ_USERINFO                = 30 ,
	
} AARQ_Tag;

typedef enum
{
	TAG_AARE_PROTOCOLVER                     = 0 ,
	TAG_AARE_APPCONTEXT                      = 1 ,
	TAG_AARE_RESULT                          = 2 ,
	TAG_AARE_RESULT_SOURCE_DIAGNOSTIC        = 3 ,
	TAG_AARE_RESPONDING_AP_TITLE             = 4 ,
	TAG_AARE_RESPONDING_AE_QUALIFIER         = 5 ,
	TAG_AARE_RESPONDING_AP_INVOCATION_ID     = 6 ,     
	TAG_AARE_RESPONDING_AE_INVOCATION_ID     = 7 , 
	TAG_AARE_RESPONDER_ACSE_REQUIREMENTS     = 8 ,
	TAG_AARE_MECHANISM_NAME                  = 9 ,
	TAG_AARE_RESPONDING_AUTHENTICATION_VALUE = 10,        
	TAG_AARE_IMPLEMENTATION_INFORMATION      = 29,
	TAG_AARE_USER_INFORMATION                = 30,
	
} AARE_Tag;

typedef enum
{
	TAG_RLRQ_REASON           = 0 ,
	TAG_RLRQ_USER_INFORMATION = 30 ,
} RLRQ_Tag;

typedef enum
{
	TAG_RLRE_REASON           = 0 ,
	TAG_RLRE_USER_INFORMATION = 30 ,
} RLRE_Tag;

typedef enum
{
	TAG_AUTHENTICATION_CHARSTRING  =  0,
	TAG_AUTHENTICATION_BITSTRING   =  1,
	TAG_AUTHENTICATION_EXTERNAL    =  2,
	TAG_AUTHENTICATION_OTHER       =  3,
} AuthenticationValue_Tag;

typedef enum
{
	VAL_ASSOCIATION_RESULT_ACCEPTED            = 0,
	VAL_ASSOCIATION_RESULT_REJECTEDPERMANENT   = 1,
	VAL_ASSOCIATION_RESULT_REJECTEDTRANSIENT   = 2,
} AssociationResult_Value;

typedef enum
{
	TAG_ACSE_SERVICE_USER     = 1,
	TAG_ACSE_SERVICE_PROVIDER = 2,
} AssociateSourceDiag_Tag;

typedef enum
{
	VAL_ASCE_SERVICE_USER_NULL                      = 0 ,
	VAL_ASCE_SERVICE_USER_NOREASON                  = 1 ,
	VAL_ASCE_SERVICE_USER_APPCONTEXTNOTSUPPORT      = 2 ,
	VAL_ASCE_SERVICE_USER_CALLINGAPTITLENOTREG		= 3,
	VAL_ASCE_SERVICE_USER_CALLINGAPINVOCATIONNOTREG = 4,
	VAL_ASCE_SERVICE_USER_CALLINGAEQUALIFIERNOTREG  = 5,
	VAL_ASCE_SERVICE_USER_CALLINGAEINVOCATIONNOTREG = 6,
	VAL_ASCE_SERVICE_USER_CALLEDAPTITLENOTREG       = 7,
	VAL_ASCE_SERVICE_USER_CALLEDAPINVOCATIONNOTREG  = 8,
	VAL_ASCE_SERVICE_USER_CALLEDAEQUALIFIERNOTREG   = 9,
	VAL_ASCE_SERVICE_USER_CALLEDAEINVOCATIONNOTREG  = 10,
	VAL_ASCE_SERVICE_USER_MECHANISMNAMENOTSUPPORTED = 11,
	VAL_ASCE_SERVICE_USER_MECHANISMNAMEREQUIRED     = 12,
	VAL_ASCE_SERVICE_USER_AUTHENTICATIONFAILURE     = 13,
	VAL_ASCE_SERVICE_USER_AUTHENTICATIONREQUIRED    = 14,
} AsceServiceUser_Value;

typedef enum
{
	VAL_ASCE_SERVICE_PROVIDER_NULL                = 0 ,
	VAL_ASCE_SERVICE_PROVIDER_NOREASON            = 1 ,
	VAL_ASCE_SERVICE_PROVIDER_NOCOMMONACSEVERSION = 2 ,
} AsceServiceProvider_Value;

typedef enum
{
	VAL_RELEASE_REQ_REASON_NORMAL       = 0 ,
	VAL_RELEASE_REQ_REASON_URGENT       = 1 ,
	VAL_RELEASE_REQ_REASON_USER_DEFINED = 30,
} ReleaseRequestReason_Value;

typedef enum
{
	VAL_RELEASE_RESP_REASON_NORMAL       = 0 ,
	VAL_RELEASE_RESP_REASON_NOT_FINISHED = 1 ,
	VAL_RELEASE_RESP_REASON_USER_DEFINED = 30,
} ReleaseResponseReason_Value;

typedef enum
{
	TAG_CONFIRM_SERVICE_ERR_INITIATEERROR        = 1 ,
    TAG_CONFIRM_SERVICE_ERR_GETSTATUS            = 2 ,
    TAG_CONFIRM_SERVICE_ERR_GETNAMELIST          = 3 ,
    TAG_CONFIRM_SERVICE_ERR_GETVARIABLEATTRIBUTE = 4 ,
    TAG_CONFIRM_SERVICE_ERR_READ                 = 5 ,
    TAG_CONFIRM_SERVICE_ERR_WRITE                = 6 ,
    TAG_CONFIRM_SERVICE_ERR_GETDATASETATTRIBUTE  = 7 ,
    TAG_CONFIRM_SERVICE_ERR_GETTIATTRIBUTE       = 8 ,
    TAG_CONFIRM_SERVICE_ERR_CHANGESCOPE          = 9 ,
    TAG_CONFIRM_SERVICE_ERR_START                = 10, 
    TAG_CONFIRM_SERVICE_ERR_STOP                 = 11, 
    TAG_CONFIRM_SERVICE_ERR_RESUME               = 12, 
    TAG_CONFIRM_SERVICE_ERR_MAKEUSABLE           = 13, 
    TAG_CONFIRM_SERVICE_ERR_INITIATELOAD         = 14, 
    TAG_CONFIRM_SERVICE_ERR_LOADSEGMENT          = 15, 
    TAG_CONFIRM_SERVICE_ERR_TERMINATELOAD        = 16, 
    TAG_CONFIRM_SERVICE_ERR_INITIATEUPLOAD       = 17, 
    TAG_CONFIRM_SERVICE_ERR_UPLOADSEGMENT        = 18, 
    TAG_CONFIRM_SERVICE_ERR_TERMINATEUPLOAD      = 19,
} ConfirmServiceError_Tag;

typedef enum
{
	TAG_SERVICE_ERR_APPLICATION_REFERENCE        = 0 ,
    TAG_SERVICE_ERR_HARDWARE_RESOURCE            = 1 ,
    TAG_SERVICE_ERR_VDE_STATE_ERROR              = 2 ,
    TAG_SERVICE_ERR_SERVICE                      = 3 ,
    TAG_SERVICE_ERR_DEFINITION                   = 4 ,
    TAG_SERVICE_ERR_ACCESS                       = 5 ,
    TAG_SERVICE_ERR_INITIATE                     = 6 ,
    TAG_SERVICE_ERR_LOAD_DATA_SET                = 7 ,
    TAG_SERVICE_ERR_CHANGE_SCOPE                 = 8 ,
    TAG_SERVICE_ERR_TASK                         = 9 ,
    TAG_SERVICE_ERR_OTHER                        = 10, 
} ServiceError_Tag;

typedef enum
{
	VAL_APP_REF_OTHER 								= 0,
	VAL_APP_REF_TIME_ELAPSED 						= 1, /* time out since request sent                 */
	VAL_APP_REF_APPLICATION_UNREACHABLE 			= 2, /* peer AEi not reachable                      */
	VAL_APP_REF_APPLICATION_REFERENCE_INVALID 		= 3, /* addressing trouble                          */
	VAL_APP_REF_APPLICATION_CONTEXT_UNSUPPORTED 	= 4, /* application_context incompatibility         */
	VAL_APP_REF_PROVIDER_COMMUNICATION_ERROR 		= 5, /* error at the local or distant equipment     */
	VAL_APP_REF_DECIPHERING_ERROR 					= 6, /* error detected by the deciphering function  */
} ApplicationReference_Value;

typedef enum
{
	VAL_HW_RESOURCE_OTHER 							= 0,
	VAL_HW_RESOURCE_MEMORY_UNAVAILABLE 				= 1,
	VAL_HW_RESOURCE_PROCESSOR_RESOURCE_UNAVAILABLE 	= 2,
	VAL_HW_RESOURCE_MASS_STORAGE_UNAVAILABLE 		= 3,
	VAL_HW_RESOURCE_OTHER_RESOURCE_UNAVAILABLE 		= 4,
} HardwareResource_Value;

typedef enum
{
	VAL_VDE_STATE_ERR_OTHER 			= 0,
	VAL_VDE_STATE_ERR_NO_DLMS_CONTEXT 	= 1,
	VAL_VDE_STATE_ERR_LOADING_DATA_SET 	= 2,
	VAL_VDE_STATE_ERR_STATUS_NOCHANGE 	= 3,
	VAL_VDE_STATE_ERR_STATUS_INOPERABLE = 4,
} VdeStateError_Value;

typedef enum
{
	VAL_SERVICE_OTHER 				 = 0,
	VAL_SERVICE_PDU_SIZE 			 = 1, /* pdu too long                         */
	VAL_SERVICE_SERVICE_UNSUPPORTED  = 2, /* as defined in the conformance block  */
} Service_Value;

typedef enum
{
	VAL_DEFINITION_OTHER						 = 0,
	VAL_DEFINITION_OBJECT_UNDEFINED 			 = 1, /* object not defined at the VDE                   */
	VAL_DEFINITION_OBJECT_CLASS_INCONSISTENT 	 = 2, /* class of object incompatible with asked service */
	VAL_DEFINITION_OBJECT_ATTRIBUTE_INCONSISTENT = 3, /* object attributes are inconsistent              */
} Definition_Value;

typedef enum
{
	VAL_ACCESS_OTHER					= 0,
	VAL_ACCESS_SCOPE_OF_ACCESS_VIOLATED = 1, /* access denied through authorisation reason  */
	VAL_ACCESS_OBJECT_ACCESS_VIOLATED 	= 2, /* access incompatible with object attribute   */
	VAL_ACCESS_HARDWARE_FAULT 			= 3, /* access fail for hardware reason             */
	VAL_ACCESS_OBJECT_UNAVAILABLE 		= 4, /* VDE hands object for unavailable            */
} Access_Value;

typedef enum
{
	VAL_INITIATE_OTHER						= 0,
	VAL_INITIATE_DLMS_VERSION_TOO_LOW 		= 1, /* proposed DLMS version too low          */
	VAL_INITIATE_INCOMPATIBLE_CONFORMANCE 	= 2, /* proposed service not sufficient        */
	VAL_INITIATE_PDU_SIZE_TOO_SHORT 		= 3, /* proposed PDU size too short            */
	VAL_INITIATE_REFUSED_BY_THE_VDE_HANDLER = 4, /* vaa creation impossible or not allowed */
} Initiate_Value;

typedef enum
{
	VAL_LOAD_DATA_SET_OTHER 					= 0,
	VAL_LOAD_DATA_SET_PRIMITIVE_OUT_OF_SEQUENCE = 1, /* according to the DataSet loading state transitions */
	VAL_LOAD_DATA_SET_NOT_LOADABLE 				= 2, /* loadable attribute set to FALSE                    */
	VAL_LOAD_DATA_SET_DATASET_SIZE_TOO_LARGE 	= 3, /* evaluated Data Set size too large                  */
	VAL_LOAD_DATA_SET_NOT_AWAITED_SEGMENT 		= 4, /* proposed segment not awaited                       */
	VAL_LOAD_DATA_SET_INTERPRETATION_FAILURE 	= 5, /* segment interpretation error                       */
	VAL_LOAD_DATA_SET_STORAGE_FAILURE 			= 6, /* segment storage error                              */
	VAL_LOAD_DATA_SET_DATA_SET_NOT_READY 		= 7, /* Data Set not in correct state for uploading        */
} LoadDataSet_Value;

typedef enum
{
	VAL_TASK_OTHER 				= 0,
	VAL_TASK_NO_REMOTE_CONTROL 	= 1, /* Remote Control parameter set to FALSE */
	VAL_TASK_TI_STOPPED 		= 2, /* TI in stopped state                   */
	VAL_TASK_TI_RUNNING 		= 3, /* TI in running state                   */
	VAL_TASK_TI_UNUSABLE 		= 4, /* TI in unusable state                  */
} Task_Value;

typedef enum
{
	TAG_GET_REQUEST_NORMAL 		= 1,
	TAG_GET_REQUEST_NEXT 		= 2,
	TAG_GET_REQUEST_WITH_LIST 	= 3,
} GetRequest_Tag;

typedef enum
{
	TAG_GET_RESPONSE_NORMAL 		= 1,
	TAG_GET_RESPONSE_WITH_DATABLOCK = 2,
	TAG_GET_RESPONSE_WITH_LIST 		= 3,
} GetResponse_Tag;

typedef enum
{
	TAG_SET_REQUEST_NORMAL 							= 1,
	TAG_SET_REQUEST_WITH_FIRST_DATABLOCK 			= 2,
	TAG_SET_REQUEST_WITH_DATABLOCK 					= 3,
	TAG_SET_REQUEST_WITH_LIST 						= 4,
	TAG_SET_REQUEST_WITH_LIST_AND_FIRST_DATABLOCK 	= 5,
} SetRequest_Tag;

typedef enum
{
	TAG_SET_RESPONSE_NORMAL 					= 1,
	TAG_SET_RESPONSE_DATABLOCK 					= 2,
	TAG_SET_RESPONSE_LAST_DATABLOCK 			= 3,
	TAG_SET_RESPONSE_LAST_DATABLOCK_WITH_LIST 	= 4,
	TAG_SET_RESPONSE_WITH_LIST 					= 5,
} SetResponse_Tag;

typedef enum
{
	TAG_ACTION_REQUEST_NORMAL 						= 1,
	TAG_ACTION_REQUEST_NEXT_PBLOCK 					= 2,
	TAG_ACTION_REQUEST_WITH_LIST 					= 3,
	TAG_ACTION_REQUEST_WITH_FIRST_PBLOCK 			= 4,
	TAG_ACTION_REQUEST_WITH_LIST_AND_FIRST_PBLOCK 	= 5,
	TAG_ACTION_REQUEST_WITH_PBLOCK 					= 6,
} ActionRequest_Tag;

typedef enum
{
	TAG_ACTION_RESPONSE_NORMAL 		= 1,
	TAG_ACTION_RESPONSE_WITH_PBLOCK = 2,
	TAG_ACTION_RESPONSE_WITH_LIST 	= 3,
	TAG_ACTION_RESPONSE_NEXT_PBLOCK = 4,
} ActionResponse_Tag;

typedef enum
{
	TAG_EXCEPTION_RESPONSE_STATE_ERROR 		= 0,
	TAG_EXCEPTION_RESPONSE_SERVICE_ERROR 	= 1,
} ExceptionResponse_Tag;

typedef enum
{
	VAL_EXCEPTION_RESPONSE_SERVICE_NOT_ALLOWED 	= 1,
	VAL_EXCEPTION_RESPONSE_SERVICE_UNKNOWN 		= 2,
} ExceptionResponseStateError_Value;

typedef enum
{
	VAL_EXCEPTION_RESPONSE_OPERATION_NOT_POSSIBLE 	= 1,
	VAL_EXCEPTION_RESPONSE_SERVICE_NOT_SUPPORTED 	= 2,
	VAL_EXCEPTION_RESPONSE_OTHER_REASON 			= 3,
	VAL_EXCEPTION_PDU_TOO_LONG						= 4,
	VAL_EXCEPTION_DECIPHERING_ERROR					= 5,
	VAL_EXCEPTION_INVOCATION_COUNTER_ERROR			= 6,
} ExceptionResponseServiceError_Value;

typedef enum
{
	TAG_DATA_NULL_DATA 				= 0  ,
	TAG_DATA_ARRAY 					= 1  ,	/* complex data type */
	TAG_DATA_STRUCTURE 				= 2  ,	/* complex data type */
	TAG_DATA_BOOLEAN 				= 3  ,
	TAG_DATA_BIT_STRING 			= 4  ,
	TAG_DATA_DOUBLE_LONG 			= 5  ,
	TAG_DATA_DOUBLE_LONG_UNSIGNED 	= 6  ,
	TAG_DATA_FLOATING_POINT 		= 7  ,
	TAG_DATA_OCTET_STRING 			= 9  ,
	TAG_DATA_VISIBLE_STRING 		= 10 ,
	TAG_DATA_UTF8_STRING			= 12 ,
	TAG_DATA_BCD 					= 13 ,
	TAG_DATA_INTEGER 				= 15 ,
	TAG_DATA_LONG 					= 16 ,
	TAG_DATA_UNSIGNED 				= 17 ,
	TAG_DATA_LONG_UNSIGNED 			= 18 ,
	TAG_DATA_COMPACT_ARRAY 			= 19 ,	/* complex data type */
	TAG_DATA_LONG64 				= 20 ,
	TAG_DATA_LONG64_UNSIGNED 		= 21 ,
	TAG_DATA_ENUM 					= 22 ,
	TAG_DATA_FLOAT32 				= 23 ,
	TAG_DATA_FLOAT64 				= 24 ,
	TAG_DATA_DATE_TIME 				= 25 ,
	TAG_DATA_DATE 					= 26 ,
	TAG_DATA_TIME 					= 27 ,
	TAG_DATA_DONT_CARE 				= 255,
} Data_Tag;

typedef Data_Tag	TypeDescription_Tag;

typedef enum
{
	VAL_DATA_ACCESS_RESULT_SUCCESS 						= 0  ,
	VAL_DATA_ACCESS_RESULT_HARDWARE_FAULT 				= 1  ,
	VAL_DATA_ACCESS_RESULT_TEMPORARY_FAILURE 			= 2  ,
	VAL_DATA_ACCESS_RESULT_READ_WRITE_DENIED 			= 3  ,
	VAL_DATA_ACCESS_RESULT_OBJECT_UNDEFINED 			= 4  ,
	VAL_DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9  ,
	VAL_DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE 			= 11 ,
	VAL_DATA_ACCESS_RESULT_TYPE_UNMATCHED 				= 12 ,
	VAL_DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED 	= 13 ,
	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14 ,
	VAL_DATA_ACCESS_RESULT_LONG_GET_ABORTED 			= 15 ,
	VAL_DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS 		= 16 ,
	VAL_DATA_ACCESS_RESULT_LONG_SET_ABORTED 			= 17 ,
	VAL_DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS 		= 18 ,
	VAL_DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID 	= 19 ,
	VAL_DATA_ACCESS_RESULT_OTHER_REASON 				= 250,
} DataAccessResult_Value;

typedef enum
{
	VAL_ACTION_RESULT_SUCCESS 						= 0   ,
	VAL_ACTION_RESULT_HARDWARE_FAULT 				= 1   ,
	VAL_ACTION_RESULT_TEMPORARY_FAILURE 			= 2   ,
	VAL_ACTION_RESULT_READ_WRITE_DENIED 			= 3   ,
	VAL_ACTION_RESULT_OBJECT_UNDEFINED 				= 4   ,
	VAL_ACTION_RESULT_OBJECT_CLASS_INCONSISTENT 	= 9   ,
	VAL_ACTION_RESULT_OBJECT_UNAVAILABLE 			= 11  ,
	VAL_ACTION_RESULT_TYPE_UNMATCHED 				= 12  ,
	VAL_ACTION_RESULT_SCOPE_OF_ACCESS_VIOLATED 		= 13  ,
	VAL_ACTION_RESULT_DATA_BLOCK_UNAVAILABLE 		= 14  ,
	VAL_ACTION_RESULT_LONG_ACTION_ABORTED 			= 15  ,
	VAL_ACTION_RESULT_NO_LONG_ACTION_IN_PROGRESS 	= 16  ,
	VAL_ACTION_RESULT_OTHER_REASON 					= 250 ,
} ActionResult_Value;

typedef enum
{
	TAG_GET_ACCESS_RESULT_DATA 					= 0,
	TAG_GET_ACCESS_RESULT_DATA_ACCESS_RESULT 	= 1,
} GetDataResult_Tag;

typedef enum
{
	TAG_DATABLOCK_G_RESULT_RAW_DATA 			= 0,
	TAG_DATABLOCK_G_RESULT_DATA_ACCESS_RESULT 	= 1,
} DataBlockGResult_Tag;

typedef enum
{
	TAG_IDENTIFIED_KEY	= 0,
	TAG_WRAPPED_KEY		= 1,
	TAG_AGREED_KEY		= 2,
} KeyInfo_Tag;

typedef enum
{
	KEY_ID_GLOBAL_UNICAST_ENCRYPTION_KEY	= 0,
	KEY_ID_GLOBAL_BROADCAST_ENCRYPTION_KEY	= 1,
} KeyId_Value;

typedef enum
{
	KEK_ID_MASTER_KEY = 0,
} KekId_Value;

typedef union
{
	struct
	{
		uint8_t	Tag        :5;
		uint8_t	Constructed:1;
		uint8_t	Class      :2;
	} Bits;
	uint8_t	Byte;
} BER_Identifier;

typedef struct
{
	BER_Identifier	Identifier;
	uint8_t			Length0;
	uint8_t			Length1;
	uint8_t			Length2;
	uint8_t			Tail;
} BER_ApduTag;

typedef enum
{
	BER_EOC = 0,
	BER_BOOLEAN,
	BER_INTEGER,
	BER_BITSTRING,
	BER_OCTETSTRING,
	BER_NULL,
	BER_OBJECTIDENTIFIER,
	BER_OBJECTDESCRIPTOR,
	BER_EXTERNAL,
	BER_REAL,
	BER_ENUMERATED,
	BER_EMBEDDEDPDV,
	BER_UTF8,
	BER_RELATIVEOID,
	BER_SEQUENCEOF = 16,
	BER_SETOF,
	BER_NUMERICSTRING,
	BER_PRINTABLESTRING,
	BER_T61STRING,
	BER_VIDEOSTRING,
	BER_IA5STRING,
	BER_UTCTIME,
	BER_GENERALTIME,
	BER_GRAPHICSSTRING,
	BER_VISIBLESTRING,
	BER_GENERALSTRING,
	BER_UNIVERSALSTRING,
	BER_CHARACTERSTRING,
	BER_BMPSTRING
} BER_UniversalClassTag;

typedef enum
{
	PRIMITIVE = 0,
	CONTRUCTED
} BER_EncodeMode;

typedef enum
{
	UNIVERSAL = 0,
	APPLICATION,
	CONTEXTSPECIFIC,
	PRIVATE
} BER_ClassType;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _R_DLMS_COSEM_APDUTAG_H */

