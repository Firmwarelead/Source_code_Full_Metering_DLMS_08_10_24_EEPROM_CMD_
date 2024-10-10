/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class48.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS48_H
#define _R_DLMS_CLASS48_H
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

typedef struct tag_class48_neighbor_discovery_setup_t
{
	uint8_t		RS_max_retry;
	uint16_t	RS_retry_wait_time;
	uint32_t	RA_send_period;
} class48_nbr_discovery_setup_t;

typedef OBIS_DECLARE_FIXED_ARRAY(class48_nbr_discovery_setup_t, class48_nbr_discovery_setup_array_t);

/* class48 action data */
typedef struct tag_class48_ip6_action_data_t
{
	uint8_t		IPv6_address_type;
	FixedString	IPv6_address;
} class48_ip6_action_data_t;

typedef union tag_class48_action_data_t
{
	void						*p_all;
	class48_ip6_action_data_t	*p_m1_add_ip6_address;
	class48_ip6_action_data_t	*p_m2_remove_ip6_address;
} class48_action_data_t;
typedef enum tag_class48_address_config_mode_t
{
	AUTO_CONFIGURATION,
	DHCPV6,
	MANUAL,
	ND
} class48_address_config_mode_t;
/* child record for 1 object of class 48 */
typedef struct tag_class48_child_record_t
{
	uint8_t								logical_name[6];				/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;				/* Access right definition for 1 object    */
	FixedString							*p_dl_reference;				/* References a Data link layer setup object by its logical name */
	class48_address_config_mode_t		*p_address_config_mode;			/* Defines the IPv6 address configuration mode */
	VariantArrayOctetString				*p_unicast_ipv6_addresses;		/* Unicast IPv6 address(es) assigned to the related interface of the physical device on the network */
	VariantArrayOctetString				*p_multicast_ipv6_addresses;	/* Contains an array of IPv6 addresses used for multicast */
	VariantArrayOctetString				*p_gateway_ipv6_addresses;		/* Contains the IPv6 addresses of the IPv6 gateway device */
	FixedString							*p_primary_dns_address;			/* Contains the IPv6 address of the primary Domain Name Server (DNS) */
	FixedString							*p_secondary_dns_address;		/* Contains the IPv6 address of the secondary Domain Name Server (DNS) */
	uint8_t								*p_traffic_class;				/* Contains the traffic class element of the IPv6 header */
	class48_nbr_discovery_setup_array_t	*p_neighbor_discovery_setup;	/* Contains the configuration to be used for both routers and hosts to support the Neighbor Discovery protocol for IPv6 */
} class48_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class48_child_record_t g_objects_child_table_class48[];			/* Import from objects : child table defintion for class 48 */
extern const uint16_t				g_objects_child_table_class48_length;		/* Import from objects : length of child table defintion of class 48 */

/******************************************************************************
Functions Prototypes
******************************************************************************/
/* Declare for attribute 10 */
void R_DLMS_CLASSES_DistributeAbstractClass48(distributor_params_t *p_params);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass48NeighborDiscoverySetup, class48_nbr_discovery_setup_t);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass48NeighborDiscoverySetupArray, class48_nbr_discovery_setup_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass48NeighborDiscoverySetupArray, class48_nbr_discovery_setup_array_t);
class48_nbr_discovery_setup_array_t *R_DLMS_CLASSES_RedirectClass48NeighborDiscoverySetupArray(distributor_params_t *p_params, class48_nbr_discovery_setup_array_t *p_object, uint16_t array_size);
VariantArrayOctetString *R_DLMS_CLASSES_RedirectClass48Ipv6Array(distributor_params_t *p_params, VariantArrayOctetString *p_object, uint16_t array_size);
OctetString * r_dlms_class48_encode_ipv6_to_string(distributor_params_t *p_params, FixedString * p_ip_address_in);
/* Declare redirect function */
/* Macro for simple attribute */
#define R_DLMS_IC48_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_CreatNew_Fixedstring(p_params, 6)
#define R_DLMS_IC48_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC48_REDIRECT_07(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_CreatNew_Fixedstring(p_params, 48)
#define R_DLMS_IC48_REDIRECT_08(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_CreatNew_Fixedstring(p_params, 48)
#define R_DLMS_IC48_REDIRECT_09(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)

/* Macro for complex attribute */
#define R_DLMS_IC48_REDIRECT_04(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass48Ipv6Array(p_params, p_attribute, size)
#define R_DLMS_IC48_REDIRECT_05(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass48Ipv6Array(p_params, p_attribute, size)
#define R_DLMS_IC48_REDIRECT_06(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass48Ipv6Array(p_params, p_attribute, size)
#define R_DLMS_IC48_REDIRECT_10(p_params, p_attribute, size)			p_attribute = R_DLMS_CLASSES_RedirectClass48NeighborDiscoverySetupArray(p_params, p_attribute, size)


void R_DLMS_CLASSES_Class48Init(void);
void R_DLMS_CLASSES_Class48PollingProcessing(void);
void R_DLMS_CLASSES_Class48AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class48AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass48(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS48_H */

