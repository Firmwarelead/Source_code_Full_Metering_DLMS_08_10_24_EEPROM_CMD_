/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_mac.h
* Version      : 1.00
* Description  : Datalink MAC sublayer of DLMS Client
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 19.05.2016 
******************************************************************************/

#ifndef _R_DLMS_MAC_H
#define _R_DLMS_MAC_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_hdlc.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/* Default MAC timeout & retries settings */
#define		MAC_PARAMS_DEFAULT_RESPONSE_TIMEOUT					2000
#define		MAC_PARAMS_DEFAULT_INACTIVITY_TIMEOUT				10000
#define		MAC_PARAMS_DEFAULT_INTERFRAME_TIMEOUT				100

/* Default MAC params */
#define		MAC_PARAMS_DEFAULT_MAX_INFO_FIELD_LENGTH_TRANSMIT	128
#define		MAC_PARAMS_DEFAULT_MAX_INFO_FIELD_LENGTH_RECEIVE	128
#define		MAC_PARAMS_DEFAULT_WINDOW_SIZE_TRANSMIT				1
#define		MAC_PARAMS_DEFAULT_WINDOW_SIZE_RECEIVE				1

/* Maximum MAC params */
#define		MAC_PARAMS_MAX_INFO_FIELD_LENGTH_TRANSMIT			2030
#define		MAC_PARAMS_MAX_INFO_FIELD_LENGTH_RECEIVE			2030
#define		MAC_PARAMS_MAX_WINDOW_SIZE_TRANSMIT					7
#define		MAC_PARAMS_MAX_WINDOW_SIZE_RECEIVE					7

/* Minimum MAC params */
#define		MAC_PARAMS_MIN_INFO_FIELD_LENGTH_TRANSMIT			32
#define		MAC_PARAMS_MIN_INFO_FIELD_LENGTH_RECEIVE			32
#define		MAC_PARAMS_MIN_WINDOW_SIZE_TRANSMIT					1
#define		MAC_PARAMS_MIN_WINDOW_SIZE_RECEIVE					1

/* MAC Address is defined as HDLC address */
#define		MAC_EMPTY_ADDRESS(address)		HDLC_EMPTY_ADDRESS(address)
#define		MAC_IS_ADDR_EQUAL(addr1, addr2)	R_HDLC_IsAddrEqual(addr1, addr2)
#define		MAC_IS_SCHEME_EXIST(src, dest)	HDLC_IS_SCHEME_EXIST(src, dest)

#define		MAC_CHANNEL_UNDEFINED								(0xFF)

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef uint8_t	HdlcChannel;

/* MAC CONNECT service result */
typedef enum
{
	MAC_CONNECT_OK = 0,
	MAC_CONNECT_NOK_REMOTE,
} MacConnectResult;

/* MAC DISCONNECT service result */
typedef enum
{
	MAC_DISCONNECT_OK = 0,
	MAC_DISCONNECT_NOK,
} MacDisconnectResult;

/* MAC DISCONNECT reason */
typedef enum
{
	MAC_DISCONNECT_REMOTE = 0,
	MAC_DISCONNECT_LOCAL_DATALINK,
	MAC_DISCONNECT_PHY,
} MacDisconnectReason;

/* MAC frame type */
typedef enum
{
	MAC_FRAME_I_COMPLETE = 0,
	MAC_FRAME_I_FIRST_FRAGMENT,
	MAC_FRAME_I_FRAGMENT,
	MAC_FRAME_I_LAST_FRAGMENT,
	MAC_FRAME_UI,
} MacFrameType;

typedef enum
{
	MAC_NDM = 0,
	MAC_NRM,
} MacConnectionState;

typedef enum
{
	MAC_EVENT_NONE = 0,
	MAC_EVENT_INVALID_FRAME,
	MAC_EVENT_ADDRESS_ERROR,
	MAC_EVENT_RECEIVE_BUFFER_TOO_BIG,
	MAC_EVENT_I_FRAME_SEQUENCE_ERROR,
	MAC_EVENT_I_FRAME_INFO_TOO_LONG,
	MAC_EVENT_UI_FRAME_ERROR,
	MAC_EVENT_RR_FRAME_SEGMENT,
	MAC_EVENT_RR_FRAME_SEQUENCE_ERROR,
	MAC_EVENT_I_SEGMENT_TRANSMIT_ERROR,
	MAC_EVENT_RNR_FRAME_SEGMENT,
	MAC_EVENT_RNR_SEQUENCE_ERROR,
	MAC_EVENT_FRAME_NOT_SUPPORT,
	MAC_EVENT_SNRM_FRAME_SEGMENT,
	MAC_EVENT_UA_FRAME_SEGMENT,
	MAC_EVENT_DM_FRAME_SEGMENT,
	MAC_EVENT_UI_FRAME_SEGMENT,
} MacLmEvent;

/* MAC address, inherit from HdlcAddress */
typedef HdlcAddress MacAddress;

/* MAC layer parameter */
typedef struct
{
	/* Mac negotiation parameters */
	uint16_t	max_info_field_length_transmit;
	uint16_t	max_info_field_length_receive;
	uint32_t	window_size_transmit;
	uint32_t	window_size_receive;
	
} MacParameter;

/* Mac API result */
typedef enum
{
	MAC_OK = 0,
	MAC_ERROR
} MacResult;

/*
 * Service callback for upper layer use
 */

/* MAC CONNECT indication callback */
typedef EXTERN_C void (*R_MAC_CONNECT_INDICATION_FUNC)(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	uint8_t *info,
	uint16_t info_length
);

/* MAC DISCONNECT indication callback */
typedef EXTERN_C void (*R_MAC_DISCONNECT_INDICATION_FUNC)(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacDisconnectReason reason,
	uint8_t unnumbered_send_status,
	uint8_t *info,
	uint16_t info_length
);

/* MAC DATA indication callback */
typedef EXTERN_C void (*R_MAC_DATA_INDICATION_FUNC)(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacFrameType frame_type,
	uint8_t *data,
	uint16_t data_length
);

/* MAC DATA confirm callback */
typedef EXTERN_C void(*R_MAC_DATA_CONFIRM_FUNC)(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacFrameType frame_type,
	MacResult result
);

/* MAC LM EVENT occurred report */
typedef EXTERN_C void (*R_MAC_LM_EVENT_OCCURRED)(
	HdlcChannel hdlc_channel,
	MacLmEvent event_id,
	uint8_t *msg,
	uint16_t msg_length
);

/* For debugging, a notification from MAC of HDLC msg that going to send to PHY */
typedef EXTERN_C void (*R_MAC_DEBUG_HDLC_MSG_SEND)(
	HdlcChannel hdlc_channel,
	uint8_t *msg,
	uint16_t msg_length
);

/* For debugging, a notification from MAC of HDLC msg received from PHY, before decoding */
typedef EXTERN_C void (*R_MAC_DEBUG_HDLC_MSG_RECEIVE)(
	HdlcChannel hdlc_channel,
	uint8_t *msg,
	uint16_t msg_length
);

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* Control */
EXTERN_C void 		R_MAC_Init(void);					/* For all channels */
EXTERN_C void		R_MAC_PollingProcessing(void);		/* For all channels */
EXTERN_C MacResult	R_MAC_ConfigChannel(
	HdlcChannel hdlc_channel,
	MacAddress	src_msap,
	MacParameter parameters,
	uint16_t	inactivity_timeout_ms,
	uint8_t *hdlc_transmit_buff,
	uint16_t hdlc_transmit_buff_length,
	uint8_t *unnumbered_frame_buff,
	uint16_t unnumbered_frame_buff_length
);
EXTERN_C MacResult	R_MAC_ConfigPhyChannelReceiver(
	PhyChannel phy_channel,
	uint16_t   interframe_ms,
	uint8_t *hdlc_receive_buff,
	uint16_t hdlc_receive_buff_length,
	uint8_t *apdu_buff,
	uint16_t apdu_buff_length
);
EXTERN_C MacResult	R_MAC_ActivateChannel(HdlcChannel channel);
EXTERN_C MacResult	R_MAC_DeactivateChannel(HdlcChannel channel);
EXTERN_C MacResult	R_MAC_ResetChannel(HdlcChannel channel);

/* Get */
EXTERN_C uint8_t			R_PHY_GetChannelActivationStatus(HdlcChannel channel);
EXTERN_C MacConnectionState	R_MAC_GetConnectionState(HdlcChannel channel);
EXTERN_C const MacParameter	*R_MAC_GetNegotiatedParameter(HdlcChannel channel);
EXTERN_C uint8_t			R_MAC_GetUnnumberedSendStatus(HdlcChannel channel);
EXTERN_C uint8_t			*R_MAC_GetReceivedApduBuffer(HdlcChannel channel);
EXTERN_C uint16_t			R_MAC_GetReceivedApduBufferLength(HdlcChannel channel);

/* Callback registration */
EXTERN_C void	R_MAC_RegisterDisconnectIndication	(R_MAC_DISCONNECT_INDICATION_FUNC func);
EXTERN_C void	R_MAC_RegisterConnectIndication		(R_MAC_CONNECT_INDICATION_FUNC func);
EXTERN_C void	R_MAC_RegisterDataConfirm			(R_MAC_DATA_CONFIRM_FUNC func);
EXTERN_C void	R_MAC_RegisterDataIndication		(R_MAC_DATA_INDICATION_FUNC func);
/* For debugging */
EXTERN_C void	R_MAC_RegisterLmEventOccurred		(R_MAC_LM_EVENT_OCCURRED func);
EXTERN_C void	R_MAC_RegisterDebugHdlcMsgSend		(R_MAC_DEBUG_HDLC_MSG_SEND func);
EXTERN_C void	R_MAC_RegisterDebugHdlcMsgReceive	(R_MAC_DEBUG_HDLC_MSG_RECEIVE func);

/* CONNECT service API */
EXTERN_C MacResult R_MAC_CONNECT_Response(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacConnectResult result,
	uint8_t *info,
	uint16_t info_length
);

/* DISCONNECT service API */
EXTERN_C MacResult R_MAC_DISCONNECT_Response(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacDisconnectResult result
);

/* DATA service API */
EXTERN_C MacResult R_MAC_DATA_Request(
	HdlcChannel hdlc_channel,
	MacAddress dest_msap,
	MacAddress src_msap,
	MacFrameType frame_type,
	uint8_t *data,
	uint16_t data_length
);

#endif /* _R_DLMS_MAC_H */

