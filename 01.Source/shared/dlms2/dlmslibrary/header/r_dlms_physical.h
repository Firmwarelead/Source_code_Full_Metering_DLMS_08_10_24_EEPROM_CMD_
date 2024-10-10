/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_physical.h
* Version      : 1.00
* Description  : Physical layer of DLMS Client
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 11.05.2016 
******************************************************************************/

#ifndef _R_DLMS_PHYSICAL_H
#define _R_DLMS_PHYSICAL_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_physical_wrapper.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

typedef enum
{
	PHY_BAUDRATE_300 = '0',
	PHY_BAUDRATE_600,
	PHY_BAUDRATE_1200,
	PHY_BAUDRATE_2400,
	PHY_BAUDRATE_4800,
	PHY_BAUDRATE_9600,
	PHY_BAUDRATE_19200,
	PHY_BAUDRATE_38400,
	PHY_BAUDRATE_NOT_SPECIFIED = 0xFF,
} PhBaudrate;

typedef enum
{
	PHY_DISCONNECTED = 0,
	PHY_CONNECTED
} PhStatus;

typedef enum
{
	PHY_OK = 0,
	PHY_ERROR,
} PhResult;

typedef struct tagIecDeviceInfo
{
	uint8_t *device_address;
	uint8_t *device_id;
	uint8_t *manufacture_id;
} iec_device_info;

typedef EXTERN_C void (*R_PHY_CONNECT_INDICATION_FUNC)(PhyChannel phy_channel);							/* Physical CONNECT service callback */
typedef EXTERN_C void (*R_PHY_DATA_INDICATION_FUNC)(PhyChannel phy_channel, uint8_t received_byte);		/* Physical DATA service callback */
typedef EXTERN_C void (*R_PHY_ABORT_INDICATION_FUNC)(PhyChannel phy_channel);							/* Physical ABORT service callback */

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

/* PHY Control */
EXTERN_C void		R_PHY_Init(void);					/* For all channels */
EXTERN_C void		R_PHY_PollingProcessing(void);		/* For all channels */
EXTERN_C uint8_t	R_PHY_ConfigChannel(PhyChannel phy_channel, PhBaudrate baudrate, uint8_t use_iec, iec_device_info* p_iec_dev_info);
EXTERN_C uint8_t	R_PHY_ResetChannel(PhyChannel phy_channel);

EXTERN_C PhStatus	R_PHY_GetStatus(PhyChannel phy_channel);
EXTERN_C uint8_t	R_PHY_ActivateChannel(PhyChannel phy_channel);
EXTERN_C uint8_t	R_PHY_DeactivateChannel(PhyChannel phy_channel);
EXTERN_C uint8_t	R_PHY_GetChannelActivationStatus(PhyChannel phy_channel);

/* PHY Services callback registration */
EXTERN_C void	R_PHY_RegisterConnectIndication	(R_PHY_CONNECT_INDICATION_FUNC func);
EXTERN_C void	R_PHY_RegisterDataIndication	(R_PHY_DATA_INDICATION_FUNC func);
EXTERN_C void	R_PHY_RegisterAbortIndication	(R_PHY_ABORT_INDICATION_FUNC func);

/* PHY Services */
EXTERN_C uint8_t	R_PHY_DATA_Request(PhyChannel phy_channel, uint8_t *p_data, uint16_t length);

/* PHY Driver callback, register to lower layer (UART, SCI, etc.) */
EXTERN_C void	R_PHY_DeviceSendEnd(PhyChannel phy_channel);
EXTERN_C void	R_PHY_DeviceReceiveEnd(PhyChannel phy_channel, uint8_t rx_byte);
EXTERN_C void	R_PHY_DeviceReceiveError(PhyChannel phy_channel);
EXTERN_C void	R_PHY_DeviceTimeOutCount(void);

#endif /* _R_DLMS_PHYSICAL_H */

