/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_process.h
* Version      : 1.00
* Description  : DLMS Library Process
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 08.07.2016 
******************************************************************************/

#ifndef _R_DLMS_LIBRARY_PROCESS_H
#define _R_DLMS_LIBRARY_PROCESS_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/* Library Config Macros */
#include "r_dlms_library_config.h"
#include "r_dlms_callback.h"

/* Physical & wrapper */
#include "r_dlms_physical.h"
#include "r_dlms_physical_wrapper.h"
#include "r_dlms_timeout_wrapper.h"
#include "r_dlms_udp_wrapper.h"
#include "r_dlms_tcp_wrapper.h"
#include "r_dlms_cosem_aes_gcm_wrapper.h"

/* Datalink */
#include "r_dlms_mac.h"
#include "r_dlms_llc.h"
#include "r_dlms_udp.h"
#include "r_dlms_tcp.h"

/* Channel management */
#include "r_dlms_mgmt.h"

/* COSEM Application */
#include "r_dlms_cosem_apdu.h"
#include "r_dlms_cosem_apdutag.h"
#include "r_dlms_cosem_apdu_security.h"
#include "r_dlms_cosem_application.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define DLMS_LIB_PROCESS_TEMP_BUFFER_SIZE	(DLMS_LIB_MAX_APDU_SIZE + 64)

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef struct tagHdlcChannelCfg
{
	MacAddress		src_addr;
	MacParameter	mac_parameters;
	uint16_t		inactivity_ms;
	uint8_t			*tx_buffer;
	uint16_t		tx_buffer_size;
	uint8_t			*unnumbered_buffer;
	uint16_t		unnumbered_buffer_size;
} HdlcChannelCfg;

typedef struct tagPhyChannelCfg
{
	PhBaudrate		baudrate;
	uint8_t			use_iec;
	iec_device_info	iec_device_info;
	uint16_t		interframe_ms;
	uint8_t			*rx_buffer;
	uint16_t		rx_buffer_size;
	uint8_t			*apdu_buffer;
	uint16_t		apdu_buffer_size;
} PhyChannelCfg;

typedef struct tagUdpChannelCfg
{
	WPort			local_wport;
	uint8_t			auto_update_config;
	UdpPortConfig	*p_udp_port_config;
	uint8_t			*udp_receive_buff;
	uint16_t		udp_receive_buff_length;
	uint16_t		inactivity_ms;
	uint16_t		interframe_ms;
} UdpChannelCfg;

typedef struct tagTcpChannelCfg
{
	WPort			local_wport;
	uint8_t			auto_update_config;
	TcpPortConfig	*p_tcp_port_config;
	uint8_t			*tcp_receive_buff;
	uint16_t		tcp_receive_buff_length;
	uint16_t		inactivity_ms;
	uint16_t		interframe_ms;
} TcpChannelCfg;

typedef struct tagAssociationCfg
{
	uint8_t			pre_established;
	uint8_t			remote_mac_addr;
	WPort			remote_wport;
    uint8_t			context_id;
	SecurityContext	*p_security_context;
    uint8_t			mechanism_id;
	MandatoryString	authentication_value;
	MandatoryString	StoC;
	uint8_t			dlms_version_number;
	uint8_t			conformance_byte0;
	uint8_t			conformance_byte1;
	uint8_t			conformance_byte2;
	uint16_t		vaa_name;

} AssociationCfg;

typedef struct tagDlmsLibraryConfig
{
	/*
	 * HDLC and PHY channels direct map one on one or mesh up
	 * This parameter configure the connection of HDLC and PHY channel direct map one on one or mesh up. TRUE or FALSE
	 * - TRUE.  HDLC and PHY channels are mapped 1 on 1.
	 *          Number of HDLC and PHY should be equals.
	 *          HDLC channels can have same address.
	 * - FALSE. All PHY channels will mix with HDLC channels for processing of received HDLC frame from all PHY.
	 *          HDLC channels shall have uniqe address to distict to each others.
	 */
	volatile uint8_t		HDLC_PHY_one_one;

} DlmsLibraryConfig;

/* DLMS Library Association Opening Indication */
typedef void (*R_DLMS_LP_ASSOCIATION_OPENING_INDICATION_FUNC)(
	AsscChannel assc,
	uint8_t *accepted,
	const AssociationCfg *p_assc_cfg,
	CosemOpenIndication_Params *p_req_params,
	CosemOpenResponse_Params *p_res_params
);

/* DLMS Library Association Open Indication */
typedef void (*R_DLMS_LP_ASSOCIATION_OPEN_INDICATION_FUNC)(
	AsscChannel assc,
	uint16_t client_sap,
	uint16_t server_sap,
	const AssociationCfg *p_assc_cfg,
	MgmtChannel	channel,
	ConformanceBits negotiated_conformance,
	uint16_t client_max_pdu_size,
	MandatoryString CtoS,
	MandatoryString dedicated_key
);

/* DLMS Library Association GET Callback */
typedef void(*R_DLMS_LP_ASSOCIATION_GET_INDICATION_FUNC)(MgmtChannel channel, CosemGetIndication_Params *p_params);

/* DLMS Library Association SET Callback */
typedef void(*R_DLMS_LP_ASSOCIATION_SET_INDICATION_FUNC)(MgmtChannel channel, CosemSetIndication_Params *p_params);

/* DLMS Library Association ACTION Callback */
typedef void(*R_DLMS_LP_ASSOCIATION_ACTION_INDICATION_FUNC)(MgmtChannel channel, CosemActionIndication_Params *p_params);

/* DLMS Library Association Close Indication */
typedef void(*R_DLMS_LP_ASSOCIATION_CLOSE_INDICATION_FUNC)(
	AsscChannel assc,
	const AssociationCfg *p_assc_cfg,
	MgmtChannel	channel
);

/******************************************************************************
Variable Externs
******************************************************************************/

/*
 * Temporary buffer gp_dlms_process_share_buffer is created in R_DLMS_PollingProcessing()
 * and share for all processes of DLMS Library and OBIS
 */
extern uint8_t	*gp_dlms_process_share_buffer;

/******************************************************************************
Functions Prototypes
******************************************************************************/
EXTERN_C void    R_DLMS_Init(void);
EXTERN_C void    R_DLMS_PollingProcessing(void);

/* Channel management */
EXTERN_C uint8_t R_DLMS_ConfigPhyChannel(PhyChannel channel, PhyChannelCfg *p_cfg);
EXTERN_C uint8_t R_DLMS_ConfigHdlcChannel(HdlcChannel channel, HdlcChannelCfg *p_cfg);
EXTERN_C uint8_t R_DLMS_ConfigUdpChannel(UdpChannel channel, UdpChannelCfg *p_cfg);
EXTERN_C uint8_t R_DLMS_ConfigTcpChannel(TcpChannel channel, TcpChannelCfg *p_cfg);
EXTERN_C uint8_t R_DLMS_ActivatePhyChannel(PhyChannel channel);
EXTERN_C uint8_t R_DLMS_DeactivatePhyChannel(PhyChannel channel);
EXTERN_C uint8_t R_DLMS_ActivateChannel(MgmtChannel channel);
EXTERN_C uint8_t R_DLMS_DeactivateChannel(MgmtChannel channel);

/* Association management */
EXTERN_C void    R_DLMS_RegisterAsscOpeningIndication(R_DLMS_LP_ASSOCIATION_OPENING_INDICATION_FUNC func);
EXTERN_C void    R_DLMS_RegisterAsscOpenIndication(R_DLMS_LP_ASSOCIATION_OPEN_INDICATION_FUNC func);
EXTERN_C void    R_DLMS_RegisterAsscGetIndication(R_DLMS_LP_ASSOCIATION_GET_INDICATION_FUNC func);
EXTERN_C void    R_DLMS_RegisterAsscSetIndication(R_DLMS_LP_ASSOCIATION_SET_INDICATION_FUNC func);
EXTERN_C void    R_DLMS_RegisterAsscActionIndication(R_DLMS_LP_ASSOCIATION_ACTION_INDICATION_FUNC func);
EXTERN_C void    R_DLMS_RegisterAsscCloseIndication(R_DLMS_LP_ASSOCIATION_CLOSE_INDICATION_FUNC func);
EXTERN_C uint8_t R_DLMS_ConfigAssociation(AsscChannel assc, const AssociationCfg *p_cfg);
EXTERN_C int16_t R_DLMS_GetCurrentRequestAsscId(MgmtChannel channel);
EXTERN_C int16_t R_DLMS_GetPreEstablishedAsscBeingCall(MgmtChannel channel);
EXTERN_C uint8_t R_DLMS_OpenPreEstablishedAssc(MgmtChannel channel, AsscChannel assc);
EXTERN_C uint8_t R_DLMS_ClosePreEstablishedAssc(MgmtChannel channel, AsscChannel assc);
EXTERN_C SecurityContext *R_DLMS_GetCurrentRequestSecurityContext(MgmtChannel channel);
EXTERN_C int16_t R_DLMS_GetConnectedAsscId(MgmtChannel channel);
EXTERN_C uint8_t R_DLMS_IsAsscConnected(AsscChannel assc);

#endif /* _R_DLMS_LIBRARY_PROCESS_H */

