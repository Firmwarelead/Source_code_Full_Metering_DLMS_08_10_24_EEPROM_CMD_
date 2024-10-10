/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_type.h
* Version      : 2.00
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_TYPE_H
#define _R_DLMS_TYPE_H

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
/* Type define: ActiveRelayTime, size: 9, number element: 3 */
#ifndef _ActiveRelayTime_t_
typedef struct tag_ActiveRelayTime
{
	uint32_t                                duration;
	uint32_t                                lockout_period;
	uint8_t                                 number_of_repeat;
} ActiveRelayTime_t;
#define _ActiveRelayTime_t_
#endif



/* Type define: PassiveRelayTime, size: 21, number element: 4 */
#ifndef _PassiveRelayTime_t_
typedef struct tag_PassiveRelayTime
{
	uint32_t                                duration;
	uint32_t                                lockout_period;
	uint8_t                                 number_of_repeat;
	OctetString                             execution_time;
} PassiveRelayTime_t;
#define _PassiveRelayTime_t_
#endif




/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_Encode_ActiveRelayTime, ActiveRelayTime_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_Decode_ActiveRelayTime, ActiveRelayTime_t);
ActiveRelayTime_t  * R_DLMS_Redirect_ActiveRelayTime(distributor_params_t * p_params, ActiveRelayTime_t * p_object);
OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_Encode_PassiveRelayTime, PassiveRelayTime_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_Decode_PassiveRelayTime, PassiveRelayTime_t);
PassiveRelayTime_t  * R_DLMS_Redirect_PassiveRelayTime(distributor_params_t * p_params, PassiveRelayTime_t * p_object);


#endif /* _R_DLMS_TYPE_H */