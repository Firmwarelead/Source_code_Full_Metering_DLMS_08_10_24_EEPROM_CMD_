/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_max_demand.h
* Version      : 1.00
* Description  : Energy management Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _MAX_DEMAND_H
#define _MAX_DEMAND_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_rtc.h"

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct st_r_mdm_counter_t
{
    float32_t   active;
    float32_t   reactive_ind;
    float32_t   reactive_cap;
    float32_t   apparent;
} r_mdm_counter_t;

typedef struct st_r_mdm_t
{
    r_mdm_counter_t         last_period_counter;                /* Reference max demand counter (energy) from last period  */
    rtc_counter_value_t     start_time;                   /* Reference time from last period */
    r_mdm_counter_t         last_average_value;                 /* Last average demand counter (power) from last period  */
    rtc_counter_value_t     last_read_capture_time_snapshot;    /* Last reading of instantaneous snapshot: capture time params */
    uint16_t                period_index;                       /* Period counter for an averaging interval */
} r_mdm_t;

/******************************************************************************
Macro definitions
******************************************************************************/
/* No special function attribute */
#define MDM_FUNC

#define MDM_RET_OK                   0
#define MDM_RET_ERROR                1
#define MDM_RET_ERROR_PARAMS         2

/******************************************************************************
Variable Externs
******************************************************************************/
extern r_mdm_t g_mdm;

/******************************************************************************
Functions Prototypes
*****************************************************************************/

/* Operation control */
MDM_FUNC void R_MDM_Init(void);
MDM_FUNC void R_MDM_PollingProcessing(void);
MDM_FUNC uint8_t R_MDM_Reset(void);
MDM_FUNC void R_MDM_NextPeriod(rtc_counter_value_t *p_input_time);

/* Measurement APIs: Max Demand Value */
MDM_FUNC float32_t R_MDM_GetActiveMaxDemand(void);
MDM_FUNC float32_t R_MDM_GetCapacitiveReactiveMaxDemand(void);
MDM_FUNC float32_t R_MDM_GetInductiveReactiveMaxDemand(void);
MDM_FUNC float32_t R_MDM_GetApparentMaxDemand(void);

/* Measurement APIs: Max Demand Captured Time */
MDM_FUNC void R_MDM_GetMaxDemandCapturedTime(rtc_counter_value_t * p_rtc);

/* Storage */
MDM_FUNC uint8_t  R_MDM_Format(void);
MDM_FUNC uint8_t	R_MDM_Restore(void);
MDM_FUNC uint8_t	R_MDM_Backup(void);

#endif /* _MAX_DEMAND_H */

