/******************************************************************************
Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_usercode_class42.h
* Version      : 1.00
* Version OCG  : OBIS code generator 1.0.5 - Jul 09 2021
* Description  : user code header file of class 42
******************************************************************************
* History : DD.MM.YYYY Version Description
* Generated date       : 04/08/2021
*
******************************************************************************/

#ifndef R_DLMS_USERCODE_CLASS42_H
#define R_DLMS_USERCODE_CLASS42_H


/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_dlms_class42.h"
#include "r_dlms_user.h"
#include "r_dlms_type.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/* Index: 00; Name: IPv4 for TCP0; Logical name: 0.0.25.1.0.255 */

#define CLASS42_SUPPORT_MAX_ACTION_DATA (30)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern const FixedString g_dlms_ic42_obj00_att02_Dl_reference;
void R_DLMS_USER_ic42_obj00_att03_ChangeIpv4(void);
extern const VariantArrayUint32_t g_dlms_ic42_obj00_att04_multicast_IP_address;
extern const class42_ip_option_array_t g_dlms_ic42_obj00_att05_option_array;
extern const uint32_t g_dlms_ic42_obj00_att06_subnet_mask;
extern const uint32_t g_dlms_ic42_obj00_att07_gateway_ipv4_address;
extern const uint8_t g_dlms_ic42_obj00_att08_use_DHCP_flag;
extern const uint32_t g_dlms_ic42_obj00_att09_primary_DNS_address;
extern const uint32_t g_dlms_ic42_obj00_att10_secondary_DNS_address;

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* R_DLMS_USERCODE_CLASS42_H */