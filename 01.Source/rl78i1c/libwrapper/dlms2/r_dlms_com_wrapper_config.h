/******************************************************************************
  Copyright (C) 2019 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_communication_config.h
* Version      : 2.00
* Version OCG  : OBIS code generator $VERSION_OCG$
* Description  : Config for OBIS layer and DLMS Library $DLMS_LIB_VERSION$
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : $DATE_TIME_GENERATING$
******************************************************************************/

#ifndef _R_DLMS_COMMUNICATION_CONFIG_H
#define _R_DLMS_COMMUNICATION_CONFIG_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/*
 * UDP mode selection
 */
#define UDP_MODE_DUMMY                                  0
#define UDP_MODE_RAW                                    1
#define UDP_MODE_NURATECH_WISUN_MODULE                  2
#define UDP_MODE_ETHERNET_SERIAL_RX65N                  3
#define UDP_MODE_FIBOCOM_H310                           4
#define	UDP_MODE_SELECTION                              UDP_MODE_ETHERNET_SERIAL_RX65N

/*
 * TCP mode selection
 */
#define TCP_MODE_DYMMY                                 0
#define TCP_MODE_RAW                                   2
#define TCP_MODE_ETHERNET_SERIAL_RX65N                 3
#define TCP_MODE_USR_TCP232_MODULE                     4
#define TCP_MODE_FIBOCOM_H310                          5
#define TCP_MODE_NEOWAY_WM620						   6
#define	TCP_MODE_SELECTION                             TCP_MODE_RAW



/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

#endif /* _R_DLMS_COMMUNICATION_CONFIG_H */