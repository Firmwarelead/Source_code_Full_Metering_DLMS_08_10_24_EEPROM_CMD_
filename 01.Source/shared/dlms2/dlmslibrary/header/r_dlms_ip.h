/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_ip.h
* Version      : 1.00
* Description  : IP definition for UDP and TCP port
*              : DLMS Library v2.0 will not store the IP inside,
*              : Please take care to store IP address on TCP/UDP Wrapper and OBIS
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 01.10.2018 
******************************************************************************/

#ifndef _R_DLMS_IP_H
#define _R_DLMS_IP_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include <string.h>

/******************************************************************************
Macro definitions
******************************************************************************/

#define IP_ADDR_BUFF_MAX_SIZE				(16)
#define IP_ADDR_IS_EQUAL(ip_dest, ip_src)	((ip_dest).size == (ip_src).size && memcmp((ip_dest).p_addr, (ip_src).p_addr, (ip_src).size) == 0)
#define IP_ADDR_COPY(ip_dest, ip_src)	{							  \
	if ((ip_dest).size == (ip_src).size) {							  \
		memcpy((ip_dest).p_addr, (ip_src).p_addr, (ip_src).size);	  \
	}																  \
}

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Variant IP address type for IPv4 and IPv6, IPv4 (size = 4), IPv6 (size = 16) */
typedef struct
{
	uint8_t     *p_addr;
	uint16_t    size;
} IpAddress;

typedef IpAddress *IpAddressPtr;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _R_DLMS_IP_H */
