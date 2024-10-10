/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class42.h
* Version      : 1.00
* Description  : Class 42 definition
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.03.2018 
******************************************************************************/

#ifndef _R_DLMS_CLASS42_H
#define _R_DLMS_CLASS42_H
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
typedef uint32_t class42_IP_Address_t;

/* ATTRIBUTE */
typedef struct tag_class42_ip_pption_t
{
	uint8_t type;
	uint8_t length;
	FixedString data;
} class42_ip_option_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class42_ip_option_t, class42_ip_option_array_t);

/* METHOD */
typedef union tag_class42_action_data_t
{
    class42_IP_Address_t	*p_ip_address;
	uint8_t					*p_data;
} class42_action_data_t;


/* child record for 1 object of class 42 */
typedef struct tag_class42_child_record_t
{
	uint8_t								logical_name[6];				/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;				/* Access right definition for 1 object    */
	FixedString							*p_dl_reference;				/* References a Data link layer setup object by its logical name */
	uint32_t							*p_ip_address;					/* Defines the IPv4 address */
	VariantArrayUint32_t				*p_multicast_ip_address;		/* Contains an array of IPv4 addresses used for multicast */
	class42_ip_option_array_t			*p_option_array;				/* Contains the necessary parameters to support the selected IP options */
	uint32_t							*p_subnet_mask;					/* Contains the subnet mask. */
	uint32_t							*p_gateway_ipv4_address;		/* Contains the IP Address of the gateway device. */
	uint8_t								*p_use_dhcp_flag;				/* When this flag is set to TRUE, the device uses DHCP */
	uint32_t							*p_primary_dns_address;			/* The IP Address of the primary Domain Name Server */
	uint32_t							*p_secondary_dns_address;		/* The IP Address of the secondary Domain Name Server */
} class42_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class42_child_record_t g_objects_child_table_class42[];			/* Import from objects : child table defintion for class 42 */
extern const uint16_t				g_objects_child_table_class42_length;		/* Import from objects : length of child table defintion of class 42 */

/******************************************************************************
Functions Prototypes
******************************************************************************/
void R_DLMS_Ipv4_ConverterByteArrayToUint32(uint8_t * p_u8, uint32_t * p_u32);
void R_DLMS_Ipv4_ConverterUint32ToByteArray(uint32_t * p_u32, uint8_t * p_u8);
void R_DLMS_CLASSES_DistributeAbstractClass42(distributor_params_t *p_params);
class42_ip_option_array_t *R_DLMS_CLASSES_Redirect_IpOptionArray(distributor_params_t *p_params, class42_ip_option_array_t *p_object, uint16_t size);

/* Declare redirect function */
/* Macro for simple attribute */
#define R_DLMS_IC42_REDIRECT_02(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_CreatNew_Fixedstring(p_params, 6)
#define R_DLMS_IC42_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC42_REDIRECT_06(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC42_REDIRECT_07(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC42_REDIRECT_08(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectUnsigned(p_params, p_attribute)
#define R_DLMS_IC42_REDIRECT_09(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC42_REDIRECT_10(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
/* Macro for complex attribute */
#define R_DLMS_IC42_REDIRECT_04(p_params, p_attribute, size)	p_attribute = R_DLMS_CLASSES_CreatNew_VariantArray_DoubleLongUnsigned(p_params, size)
#define R_DLMS_IC42_REDIRECT_05(p_params, p_attribute, size)	p_attribute = R_DLMS_CLASSES_Redirect_IpOptionArray(p_params, p_attribute, size)

void R_DLMS_CLASSES_Class42Init(void);
void R_DLMS_CLASSES_Class42PollingProcessing(void);
void R_DLMS_CLASSES_Class42AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class42AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass42(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS42_H */

