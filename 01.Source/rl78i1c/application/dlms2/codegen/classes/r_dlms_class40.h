/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class40.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS40_H
#define _R_DLMS_CLASS40_H
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

typedef enum tag_class40_attribute_t
{
    CLASS40_ATTRIBUTE_02_PUSH_OBJECT_LIST = 2,
    CLASS40_ATTRIBUTE_03_SEND_DESTINATION_AND_METHOD,
    CLASS40_ATTRIBUTE_04_COMMUNICATION_WINDOW,
    CLASS40_ATTRIBUTE_05_RANDOMISATION_START_INTERVAL,
    CLASS40_ATTRIBUTE_06_NUMBER_OF_RETRIES,
    CLASS40_ATTRIBUTE_07_REPETITION_DELAY,
} class40_attribute_t;

typedef enum tag_class40_method_t
{
    CLASS40_METHOD_01_PUSH = 1,
} class40_method_t;

typedef union tag_class40_action_data_t
{
    void                                    * p_all;
    int8_t                                  * p_m1_push;
} class40_action_data_t;

/* class40 object definition type */
typedef struct tag_class40_push_object_t
{
	uint16_t 		class_id;				/* Class ID          */
	FixedString		logical_name;			/* The logical name  */
	int8_t			attribute_index;		/* Atrribute index   */
	uint16_t		data_index;				/* Data index		 */
} class40_push_object_t;

/* class06 object definition array type */
typedef OBIS_DECLARE_FIXED_ARRAY(class40_push_object_t, class40_push_object_array_t);

typedef enum tag_class40_transport_service_t
{
	CLASS_40_TRANSPORT_SERVICE_TCP,
	CLASS_40_TRANSPORT_SERVICE_UDP,
	CLASS_40_TRANSPORT_SERVICE_FTP,
	CLASS_40_TRANSPORT_SERVICE_MTP,
	CLASS_40_TRANSPORT_SERVICE_SMS,
	CLASS_40_TRANSPORT_SERVICE_HDLC,
	CLASS_40_TRANSPORT_SERVICE_M_Bus,
	CLASS_40_TRANSPORT_SERVICE_ZigBee,
} class40_transport_service_t;

typedef enum tag_class40_message_type_t
{	
	CLASS_40_MESSAGE_TYPE_A_XDR_ENC_xDLMS_APDU = 0,
	CLASS_40_MESSAGE_TYPE_XML_ENC_xDLMS_APDU = 1,
} class40_message_type_t;

typedef struct tag_class40_send_destination_and_method_t
{	
	uint8_t transport_service;
	OctetString destination;
    class40_message_type_t message;
} class40_send_destination_and_method_t;

typedef struct tag_class40_comm_window_t
{
	date_time_t start_time;
	date_time_t end_time;
} class40_comm_window_t;

typedef OBIS_DECLARE_FIXED_ARRAY(class40_comm_window_t, class40_comm_window_array_t);

/* child record for 1 object of class 40 */
typedef struct tag_class40_child_record_t
{
	uint8_t									logical_name[6];		            /* Logical name (OBIS code) of the object. */
	access_right_t                          *p_access_right;		            /* Access right definition for 1 object */
    class40_push_object_array_t             *p_push_object_list;	            /* Defines the list of attributes to be pushed */
	class40_send_destination_and_method_t	*p_send_destination_and_method;	            /* Contains the destination address and sending method */
	class40_comm_window_array_t             *p_communication_window;		            /* Defines the time points when the communication window */
	uint16_t                                *p_randomisation_start_interval;
	uint8_t                                 *p_number_of_retries;
	uint16_t                                *p_repetition_delay;
} class40_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class40_child_record_t g_objects_child_table_class40[];			/* Import from objects : child table defintion for class 40 */
extern const uint16_t				g_objects_child_table_class40_length;		/* Import from objects : length of child table defintion of class 40 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass40(distributor_params_t *p_params);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40PushObjectList, class40_push_object_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40PushObjectList, class40_push_object_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass40PushObjectList, class40_push_object_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40PushObjectListArray, class40_push_object_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40PushObjectListArray, class40_push_object_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass40PushObjectListArray, class40_push_object_array_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40SendDestAndMethod, class40_send_destination_and_method_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40SendDestAndMethod, class40_send_destination_and_method_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass40SendDestAndMethod, class40_send_destination_and_method_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40CommunicationWindow, class40_comm_window_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40CommunicationWindow, class40_comm_window_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass40CommunicationWindowArray, class40_comm_window_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass40CommunicationWindowArray, class40_comm_window_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass40CommunicationWindowArray, class40_comm_window_array_t);

/* Declare header for Redirection Fucntion */
//OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass40PushObjectList, class40_push_object_array_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass40SendDestAndMethod, class40_send_destination_and_method_t);
class40_comm_window_array_t *R_DLMS_CLASSES_RedirectClass40CommunicationWindowArray(distributor_params_t *p_params, class40_comm_window_array_t *p_object, uint16_t array_size);
class40_push_object_array_t *R_DLMS_CLASSES_RedirectClass40PushObjectList(distributor_params_t *p_params, class40_push_object_array_t *p_object, uint16_t array_size);
/* Declare redirect function */
/* Macro for simple attribute */
#define R_DLMS_IC40_REDIRECT_05(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC40_REDIRECT_06(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)
#define R_DLMS_IC40_REDIRECT_07(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectLongUnsigned(p_params, p_attribute)
/* Macro for complex attribute */
#define R_DLMS_IC40_REDIRECT_02(p_params, p_attribute, array_size)			p_attribute = R_DLMS_CLASSES_RedirectClass40PushObjectList(p_params, p_attribute, array_size)
#define R_DLMS_IC40_REDIRECT_03(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectClass40SendDestAndMethod(p_params, p_attribute)
#define R_DLMS_IC40_REDIRECT_04(p_params, p_attribute, array_size)			p_attribute = R_DLMS_CLASSES_RedirectClass40CommunicationWindowArray(p_params, p_attribute, array_size)

void R_DLMS_CLASSES_Class40Init(void);
void R_DLMS_CLASSES_Class40PollingProcessing(void);
void R_DLMS_CLASSES_Class40AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class40AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass40(distributor_params_t *p_params);


#endif /* _R_DLMS_CLASS40_H */

