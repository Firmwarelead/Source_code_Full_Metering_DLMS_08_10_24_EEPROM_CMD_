/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : dataflash.h
* Version      : 1.00
* Description  : Data Flash Application Layer APIs
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _INST_READ_H
#define _INST_READ_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_wdt.h"           /* MD WDT Driver */
#include "r_cg_rtc.h"
#include "em_type.h"
#include "typedef.h"        /* GSCE Standard Typedef */

#include "em_constraint.h"
#include "em_type.h"
/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct tagEMInstantRead
{
    float32_t     vrms;
    
    float32_t     irms;
    float32_t     power_factor;
    EM_PF_SIGN    power_factor_sign;
    float32_t     active_power;
    float32_t     reactive_power;
    float32_t     apparent_power;
    float32_t     fundamental_power;
    
    float32_t     irms2;
    float32_t     power_factor2;
    EM_PF_SIGN    power_factor_sign2;
    float32_t     active_power2;
    float32_t     reactive_power2;
    float32_t     apparent_power2;
    float32_t     fundamental_power2;

    float32_t     active_energy_total_import;
    float32_t     active_energy_total_export;
    float32_t     reactive_energy_lag_total_import;
    float32_t     reactive_energy_lag_total_export;
    float32_t     reactive_energy_lead_total_import;
    float32_t     reactive_energy_lead_total_export;
    float32_t     apparent_energy_total_import;
    float32_t     apparent_energy_total_export;

    float32_t     freq;
	EM_LINE		  selected_line;
	uint8_t		  acc_mode;
	
} EM_INST_READ_PARAMS;

typedef struct tag_capture_em_data
{
    EM_INST_READ_PARAMS value;
    rtc_counter_value_t capture_time; 
} s_capture_em_data_t;

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/
extern EM_INST_READ_PARAMS g_inst_read_params;
extern s_capture_em_data_t * gp_inst_DataPop;
extern s_capture_em_data_t * gp_inst_LastDataPop;

/******************************************************************************
Functions Prototypes
******************************************************************************/
void INST_READ_RTC_InterruptCallBack(void);

s_capture_em_data_t * R_INST_DataPop(void);
s_capture_em_data_t * R_INST_LastDataPop(void);
void R_INST_DataPopAll(void);
void R_INST_SetSnapshotCaptureState(uint8_t state);

void R_INST_UpdateEnergyByPowerAndTime(float32_t power, float32_t seconds);

#endif /* _INST_READ_H */
