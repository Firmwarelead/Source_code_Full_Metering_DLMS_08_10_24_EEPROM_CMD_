/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_physical_wrapper.h
* Version      : 1.00
* Description  : Physical wrapper layer of DLMS Client
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016 
******************************************************************************/

#ifndef _R_DLMS_PHYSICAL_WRAPPER_H
#define _R_DLMS_PHYSICAL_WRAPPER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define PHY_CHANNEL_UNDEFINED		(0xFF)

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef enum
{
	BAUDRATE_300 = '0',
	BAUDRATE_600,
	BAUDRATE_1200,
	BAUDRATE_2400,
	BAUDRATE_4800,
	BAUDRATE_9600,
	BAUDRATE_19200,
	BAUDRATE_38400,
	BAUDRATE_57600,
	BAUDRATE_115200,
	BAUDRATE_NOT_SPECIFIED = 0xFF,
} uart_baudrate_t;

typedef uint8_t PhyChannel;

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* PHY Driver APIs */
EXTERN_C void R_PHY_DEVICE_Init(PhyChannel phy_channel);
EXTERN_C void R_PHY_DEVICE_Start(PhyChannel phy_channel);
EXTERN_C void R_PHY_DEVICE_Stop(PhyChannel phy_channel);
EXTERN_C void R_PHY_DEVICE_ChangeBaudrate(PhyChannel phy_channel, uart_baudrate_t baudrate);
EXTERN_C void R_PHY_DEVICE_ChangeSetting7E1(PhyChannel phy_channel);
EXTERN_C void R_PHY_DEVICE_ChangeSetting8N1(PhyChannel phy_channel);
EXTERN_C uint8_t R_PHY_DEVICE_SendData(PhyChannel phy_channel, uint8_t *data, uint16_t length);

/* PHY Driver callback, register to lower layer (UART, SCI, etc.) */
EXTERN_C void	R_PHY_DeviceSendEnd(PhyChannel phy_channel);
EXTERN_C void	R_PHY_DeviceReceiveEnd(PhyChannel phy_channel, uint8_t rx_byte);
EXTERN_C void	R_PHY_DeviceReceiveError(PhyChannel phy_channel);
EXTERN_C void	R_PHY_DeviceTimeOutCount(void);

#endif /* _R_DLMS_PHYSICAL_WRAPPER_H */

