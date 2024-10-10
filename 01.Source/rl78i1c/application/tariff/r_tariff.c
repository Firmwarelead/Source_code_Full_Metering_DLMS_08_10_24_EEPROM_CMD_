/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.  */
/****************************************************************************** 
* File Name    : r_tariff.c
* Version      : 1.00
* Device(s)    : RL78/I1C
* Tool-Chain   : 
* H/W Platform : RL78/I1C Energy Meter Platform
* Description  : Platform energy tariff functions
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_wdt.h"

#include <string.h>
#include <math.h>

/* Application */
#include "r_tariff.h"
#include "r_meter_format.h"
#include "r_scheduler.h"
#include "inst_read.h"
#include "storage.h"

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Macro definitions
******************************************************************************/
/* Macro to specify the energy direction */
#define IMPORT_DIRECTION                    0
#define EXPORT_DIRECTION                    1
/* Scaling for energy when reading via measurement APIs */
#define TARIFF_SCALING_DIVISOR              (1000.0f)

TARIFF_FUNC uint8_t r_tariff_check_measurement_condition(uint8_t tariff, void *p_energy);
TARIFF_FUNC void r_tariff_add_counter(r_tariff_counter_t * p_result, r_tariff_counter_t * p_left, r_tariff_counter_t * p_right);
TARIFF_FUNC void r_tariff_sync_accumulated_energy_to_tariff(uint8_t tariff_no);
TARIFF_FUNC void r_tariff_get_accumulated_total_energy_counter(r_tariff_counter_t * p_counter);
TARIFF_FUNC float32_t r_tariff_measurement_get_tariff_energy_by_energy_type(uint8_t tariff_no, uint8_t energy_direction, uint16_t offset);
TARIFF_FUNC float32_t r_tariff_measurement_get_total_energy_by_energy_type(uint8_t energy_direction, uint16_t offset);

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
r_tariff_t g_tariff;

/* Lookup table to get tariff number of a specific timeslot (both index 0) */
uint8_t g_tariff_lookup_timeslot_tariff_number[SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX];

/******************************************************************************
* Function Name: uint8_t r_tariff_check_measurement_condition(uint8_t tariff, void *p_energy)
* Description  : Energy checking tariff and pointer input. Common when reading tariff energy counter
* Arguments    : uint8_t tariff: tariff number
*              : void *p_energy: input pointer to energy buffer
* Return Value : uint8_t: checking status
******************************************************************************/
TARIFF_FUNC uint8_t r_tariff_check_measurement_condition(uint8_t tariff, void *p_energy)
{
    if (tariff > (SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX - 1) || p_energy == NULL) {
        return TARIFF_RET_ERROR_PARAMS;
    }
    else {
        return TARIFF_RET_OK;
    }
}

/******************************************************************************
* Function Name: void r_tariff_add_counter(r_tariff_counter_t * p_result, r_tariff_counter_t * p_left, r_tariff_counter_t * p_right)
* Description  : Energy counter add function (to reduce code size when calling macro multiple time)
* Arguments    : r_tariff_counter_t * p_tariff_counter: pointer to total tariff counter
* Return Value : None
******************************************************************************/
TARIFF_FUNC void r_tariff_add_counter(r_tariff_counter_t * p_result, r_tariff_counter_t * p_left, r_tariff_counter_t * p_right)
{
    p_result->active_imp = p_left->active_imp + p_right->active_imp;
    p_result->active_exp = p_left->active_exp + p_right->active_exp;
    p_result->reactive_cap_imp = p_left->reactive_cap_imp + p_right->reactive_cap_imp;
    p_result->reactive_cap_exp = p_left->reactive_cap_exp + p_right->reactive_cap_exp;
    p_result->reactive_ind_imp = p_left->reactive_ind_imp + p_right->reactive_ind_imp;
    p_result->reactive_ind_exp = p_left->reactive_ind_exp + p_right->reactive_ind_exp;
    p_result->apparent_imp = p_left->apparent_imp + p_right->apparent_imp;
    p_result->apparent_exp = p_left->apparent_exp + p_right->apparent_exp;
}

/******************************************************************************
* Function Name: void r_tariff_sync_accumulated_energy_to_tariff(uint8_t tariff_no)
* Description  : Sync accumulated energy to tariff counter
*              :    Total energy tariff counter
*              :    Current time slot tariff counter
* Arguments    : None
* Return Value : None
******************************************************************************/
TARIFF_FUNC void r_tariff_sync_accumulated_energy_to_tariff(uint8_t tariff_no)
{
    r_tariff_counter_t tariff_counter, current_tariff_counter;

    /* Get current accumulated energy */
    r_tariff_get_accumulated_total_energy_counter(&tariff_counter);

    /* Get tariff counter and total tariff counter */
    EPR_Read(
        STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR + ((uint32_t)tariff_no * sizeof(r_tariff_counter_t)),
        (uint8_t *)&current_tariff_counter,
        sizeof(r_tariff_counter_t)
    );

    /* Add the accumulated energy to tariff counter and total tariff counter */
    r_tariff_add_counter(&current_tariff_counter, &current_tariff_counter, &tariff_counter);
    r_tariff_add_counter(&g_tariff.last_synced_total_energy_counter, &g_tariff.last_synced_total_energy_counter, &tariff_counter);

    /* Backup new tariff counter to storage */
    EPR_Write(
        STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR + (sizeof(r_tariff_counter_t) * tariff_no),
        (uint8_t *)&current_tariff_counter,
        sizeof(r_tariff_counter_t)
    );

    /* Update the last snapshot params (only update on changing tariff period) */
    g_tariff.last_synced_energy_counter_snapshot = g_tariff.last_read_energy_counter_snapshot;
}

/******************************************************************************
* Function Name: float32_t r_tariff_measurement_get_tariff_energy_by_energy_type(uint8_t tariff_no, uint8_t energy_direction, uint16_t offset)
* Description  : Measurement APIs: Get tariff slot energy by specific energy type 
*              : Notes: this APIs scale down energy and mask off energy export under forwarded only and export direction
* Arguments    : uint8_t tariff_no: tariff number to get
*              : uint8_t energy_direction: using either
*              :        IMPORT_DIRECTION
*              :        EXPORT_DIRECTION
*              : uint16_t offset: using offsetof to get offset of energy type in r_tariff_counter_t structure
* Return Value : float32_t
******************************************************************************/
TARIFF_FUNC float32_t r_tariff_measurement_get_tariff_energy_by_energy_type(uint8_t tariff_no, uint8_t energy_direction, uint16_t offset)
{
    r_tariff_counter_t tariff_counter;
    float32_t energy;

    if (g_tariff.metering_mode == TARIFF_METERING_MODE_FORWARDED_ONLY && energy_direction == EXPORT_DIRECTION)
    {
        energy = 0.0f;
    }
    else
    {
        EPR_Read(
            STORAGE_EEPROM_ENERGY_TARIFF_TZ_ADDR + ((tariff_no * sizeof(r_tariff_counter_t)) + offset),
            (uint8_t *)&energy,
            sizeof(float32_t)
        );
        
        /* Request tariff is active tariff? */
        if (tariff_no == g_tariff.current_tariff_no) 
        {
            r_tariff_get_accumulated_total_energy_counter(&tariff_counter);
            energy = energy + *((float32_t *)(void *)((uint8_t *)&tariff_counter + offset));
        }
        energy /= TARIFF_SCALING_DIVISOR;
    }

    return energy;
}

/******************************************************************************
* Function Name: float32_t r_tariff_measurement_get_total_energy_by_energy_type(uint8_t tariff_no, uint8_t energy_direction, uint16_t offset)
* Description  : Measurement APIs: Get total energy by specific energy type (notes, this APIs scale energy when reading)
* Arguments    : uint8_t energy_direction: using either
*              :        IMPORT_DIRECTION
*              :        EXPORT_DIRECTION
*              : uint16_t offset: using offsetof to get offset of energy type in r_tariff_counter_t structure
* Return Value : float32_t
******************************************************************************/
TARIFF_FUNC float32_t r_tariff_measurement_get_total_energy_by_energy_type(uint8_t energy_direction, uint16_t offset)
{
    r_tariff_counter_t tariff_counter;
    float32_t energy;

    if (g_tariff.metering_mode == TARIFF_METERING_MODE_FORWARDED_ONLY && energy_direction == EXPORT_DIRECTION)
    {
        energy = 0.0f;
    }
    else
    {
        R_TARIFF_GetTotalEnergyCounter(&tariff_counter);
        energy = *((float32_t *)(void *)((uint8_t *)&tariff_counter + offset));
        energy /= TARIFF_SCALING_DIVISOR;
    }
    
    return energy;
}

/******************************************************************************
* Function Name: void r_tariff_get_accumulated_total_energy_counter(r_tariff_counter_t * p_counter)
* Description  : Energy get tariff counter (converted from metrology accumulated counter)
* Arguments    : r_tariff_counter_t * p_energy: output snapshot of energy counter
* Return Value : None
******************************************************************************/
TARIFF_FUNC void r_tariff_get_accumulated_total_energy_counter(r_tariff_counter_t * p_counter)
{
    r_tariff_counter_t tariff_counter;
    
    /* Find the accumulated value */
    tariff_counter.active_imp       = g_tariff.last_read_energy_counter_snapshot.active_imp         - g_tariff.last_synced_energy_counter_snapshot.active_imp;
    tariff_counter.active_exp       = g_tariff.last_read_energy_counter_snapshot.active_exp         - g_tariff.last_synced_energy_counter_snapshot.active_exp;
    tariff_counter.reactive_cap_imp = g_tariff.last_read_energy_counter_snapshot.reactive_cap_imp   - g_tariff.last_synced_energy_counter_snapshot.reactive_cap_imp;
    tariff_counter.reactive_cap_exp = g_tariff.last_read_energy_counter_snapshot.reactive_cap_exp   - g_tariff.last_synced_energy_counter_snapshot.reactive_cap_exp;
    tariff_counter.reactive_ind_imp = g_tariff.last_read_energy_counter_snapshot.reactive_ind_imp   - g_tariff.last_synced_energy_counter_snapshot.reactive_ind_imp;
    tariff_counter.reactive_ind_exp = g_tariff.last_read_energy_counter_snapshot.reactive_ind_exp   - g_tariff.last_synced_energy_counter_snapshot.reactive_ind_exp;
    tariff_counter.apparent_imp     = g_tariff.last_read_energy_counter_snapshot.apparent_imp       - g_tariff.last_synced_energy_counter_snapshot.apparent_imp;
    tariff_counter.apparent_exp     = g_tariff.last_read_energy_counter_snapshot.apparent_exp       - g_tariff.last_synced_energy_counter_snapshot.apparent_exp;

    /* Translate the energy counter from metrology depends on metering mode */
    if (g_tariff.metering_mode == TARIFF_METERING_MODE_FORWARDED_ONLY) 
    {
        /* In FORWARDED only mode
        *   Import = import + export
        *   Export will be cleared to 0
        */
        /* Count both import and export as import  */
        tariff_counter.active_imp           += tariff_counter.active_exp;
        tariff_counter.reactive_ind_imp     += tariff_counter.reactive_ind_exp;
        tariff_counter.reactive_cap_imp     += tariff_counter.reactive_cap_exp;
        tariff_counter.apparent_imp         += tariff_counter.apparent_exp;
        /* Clear all export counter */
        tariff_counter.active_exp           = 0;
        tariff_counter.reactive_ind_exp     = 0;
        tariff_counter.reactive_cap_exp     = 0;
        tariff_counter.apparent_exp         = 0;
    }
    else 
    {
        /* Leave as is in NET mode, the import and export accumulate separately */
    }
    
    /* Assign to output tariff counter */
    *p_counter = tariff_counter;
}

/******************************************************************************
* Function Name: void R_TARIFF_Init(void)
* Description  : Initialization for tariff application
* Arguments    : None
* Return Value : None
******************************************************************************/
TARIFF_FUNC void R_TARIFF_Init(void)
{
    
}

/******************************************************************************
* Function Name: void R_TARIFF_PollingProcessing(void)
* Description  : Polling processing for tariff
* Arguments    : None
* Return Value : None
******************************************************************************/
TARIFF_FUNC void R_TARIFF_PollingProcessing(void)
{
    /* Update counter from snapshot */
    if (gp_inst_DataPop != NULL)
    {
        g_tariff.last_read_energy_counter_snapshot.active_imp = gp_inst_DataPop->value.active_energy_total_import;
        g_tariff.last_read_energy_counter_snapshot.active_exp = gp_inst_DataPop->value.active_energy_total_export;
        g_tariff.last_read_energy_counter_snapshot.reactive_cap_imp = gp_inst_DataPop->value.reactive_energy_lead_total_import;
        g_tariff.last_read_energy_counter_snapshot.reactive_cap_exp = gp_inst_DataPop->value.reactive_energy_lead_total_export;
        g_tariff.last_read_energy_counter_snapshot.reactive_ind_imp = gp_inst_DataPop->value.reactive_energy_lag_total_import;
        g_tariff.last_read_energy_counter_snapshot.reactive_ind_exp = gp_inst_DataPop->value.reactive_energy_lag_total_export;
        g_tariff.last_read_energy_counter_snapshot.apparent_imp = gp_inst_DataPop->value.apparent_energy_total_import;
        g_tariff.last_read_energy_counter_snapshot.apparent_exp = gp_inst_DataPop->value.apparent_energy_total_export;
    }

    /* Is tariff changed? */
	if (g_event_request_flag.is_tariff_changed)
	{
        r_tariff_sync_accumulated_energy_to_tariff(g_tariff.current_tariff_no);
        
        /* Update with new tariff number lookup from scheduler new time slot */
        {
            uint8_t new_tariff = g_tariff_lookup_timeslot_tariff_number[g_scheduler_match_context[SCHEDULER_ID_TARIFF].exe_time_id];
            if (new_tariff < SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX)
            {
                g_tariff.current_tariff_no = new_tariff;
            }
            else
            {
                /* Out of range tariff number, not updating the current_tariff_no */
            }
        }

        /* Acknowlede the request flag */
        g_event_request_flag.is_tariff_changed = 0;
	}
}

/******************************************************************************
* Function Name: r_tariff_metering_mode_t R_TARIFF_GetMeteringMode(void)
* Description  : Get the current metering mode
* Arguments    : None
* Return Value : r_tariff_metering_mode_t : current metering mode
******************************************************************************/
TARIFF_FUNC r_tariff_metering_mode_t R_TARIFF_GetMeteringMode(void)
{
    return g_tariff.metering_mode;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_SetMeteringMode(r_tariff_metering_mode_t mode)
* Description  : Set the energy metering mode
* Arguments    : r_tariff_metering_mode_t : metering mode
* Return Value : uint8_t : set success or not
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_SetMeteringMode(r_tariff_metering_mode_t mode)
{
    if (mode != TARIFF_METERING_MODE_FORWARDED_ONLY && mode != TARIFF_METERING_MODE_NET) 
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    else 
    {
        /* Synchronize energy tariff start data  */
        r_tariff_sync_accumulated_energy_to_tariff(g_tariff.current_tariff_no);

        /* Param valid, set to profile */
        g_tariff.metering_mode = mode;

        return TARIFF_RET_OK;
    }
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetImportActiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the import active energy for a specific tariff (represent in KWh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetImportActiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        IMPORT_DIRECTION, 
        offsetof(r_tariff_counter_t, active_imp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: TARIFF_RET R_TARIFF_GetExportActiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the export active energy for a specific tariff (represent in KWh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetExportActiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        EXPORT_DIRECTION, 
        offsetof(r_tariff_counter_t, active_exp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetImportCapacitiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the import capacitive reactive energy for a specific tariff (represent in KVarh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetImportCapacitiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        IMPORT_DIRECTION,
        offsetof(r_tariff_counter_t, reactive_cap_imp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetExportCapacitiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the export capacitive reactive energy for a specific tariff (represent in KVarh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetExportCapacitiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        EXPORT_DIRECTION,
        offsetof(r_tariff_counter_t, reactive_cap_exp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetImportInductiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the import inductive reactive energy for a specific tariff (represent in KWh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetImportInductiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        IMPORT_DIRECTION,
        offsetof(r_tariff_counter_t, reactive_ind_imp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetExportInductiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the export inductive reactive energy for a specific tariff (represent in KWh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetExportInductiveReactiveEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        EXPORT_DIRECTION,
        offsetof(r_tariff_counter_t, reactive_ind_exp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetImportApparentEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the import apparent energy for a specific tariff (represent in KWh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetImportApparentEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        IMPORT_DIRECTION,
        offsetof(r_tariff_counter_t, apparent_imp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetExportApparentEnergyTariff(uint8_t tariff, float32_t *p_energy)
* Description  : Measurement API. Get the export apparent energy for a specific tariff (represent in KWh)
* Arguments    : float32_t *p_energy: Buffer to store energy data
*              : uint8_t tariff: Specific tariff number to get energy. Based index from 0.
* Return Value : Function execution status
*              : TARIFF_RET_OK: Normal end
*              : TARIFF_RET_ERROR_PARAMS: Parameter is invalid.
*                                 Maybe the pointer p_energy is invalid (null)
*                                 Or the tariff number (specified by [tariff]) is out of range
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetExportApparentEnergyTariff(uint8_t tariff, float32_t *p_energy)
{
    if (r_tariff_check_measurement_condition(tariff, p_energy) != TARIFF_RET_OK)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }
    *p_energy = r_tariff_measurement_get_tariff_energy_by_energy_type(
        tariff, 
        EXPORT_DIRECTION,
        offsetof(r_tariff_counter_t, apparent_exp)
    );
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetImportActiveEnergyTotal(void)
* Description  : Measurement API. Get the total import active energy (sum of all tariff) (represent in KWh)
* Arguments    : None
* Return Value : Active energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetImportActiveEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(IMPORT_DIRECTION, offsetof(r_tariff_counter_t, active_imp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetExportActiveEnergyTotal(void)
* Description  : Measurement API. Get the total export active energy (sum of all tariff) (represent in KWh)
* Arguments    : None
* Return Value : Active energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetExportActiveEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(EXPORT_DIRECTION, offsetof(r_tariff_counter_t, active_exp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetImportCapacitiveReactiveEnergyTotal(void)
* Description  : Measurement API. Get the total import capacitive reactive energy (sum of all tariff) (represent in KVArh)
* Arguments    : None
* Return Value : Reactive energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetImportCapacitiveReactiveEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(IMPORT_DIRECTION, offsetof(r_tariff_counter_t, reactive_cap_imp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetExportCapacitiveReactiveEnergyTotal(void)
* Description  : Measurement API. Get the total export capacitive reactive energy (sum of all tariff) (represent in KVArh)
* Arguments    : None
* Return Value : Reactive energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetExportCapacitiveReactiveEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(EXPORT_DIRECTION, offsetof(r_tariff_counter_t, reactive_cap_exp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetImportInductiveReactiveEnergyTotal(void)
* Description  : Measurement API. Get the total import inductive reactive energy (sum of all tariff) (represent in KVArh)
* Arguments    : None
* Return Value : Reactive energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetImportInductiveReactiveEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(IMPORT_DIRECTION, offsetof(r_tariff_counter_t, reactive_ind_imp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetExportInductiveReactiveEnergyTotal(void)
* Description  : Measurement API. Get the total export inductive reactive energy (sum of all tariff) (represent in KVArh)
* Arguments    : None
* Return Value : Reactive energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetExportInductiveReactiveEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(EXPORT_DIRECTION, offsetof(r_tariff_counter_t, reactive_ind_exp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetImportApparentEnergyTotal(void)
* Description  : Measurement API. Get the total apparent energy (sum of all tariff) (represent in KVAh)
* Arguments    : None
* Return Value : apparent energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetImportApparentEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(IMPORT_DIRECTION, offsetof(r_tariff_counter_t, apparent_imp));
}

/******************************************************************************
* Function Name: float32_t R_TARIFF_GetExportApparentEnergyTotal(void)
* Description  : Measurement API. Get the total apparent energy (sum of all tariff) (represent in KVAh)
* Arguments    : None
* Return Value : apparent energy of total
******************************************************************************/
TARIFF_FUNC float32_t R_TARIFF_GetExportApparentEnergyTotal(void)
{
    return r_tariff_measurement_get_total_energy_by_energy_type(EXPORT_DIRECTION, offsetof(r_tariff_counter_t, apparent_exp));
}

/******************************************************************************
* Function Name: uint8_t R_TARIFF_GetTotalEnergyCounter(r_tariff_counter_t * p_counter)
* Description  : Energy get tariff counter (converted from metrology counter)
* Arguments    : r_tariff_counter_t * p_energy: output snapshot of energy counter
* Return Value : uint8_t: operation status
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_GetTotalEnergyCounter(r_tariff_counter_t * p_counter)
{
    r_tariff_counter_t tariff_counter, total;
    
    if (p_counter == NULL)
    {
        return TARIFF_RET_ERROR_PARAMS;
    }

    r_tariff_get_accumulated_total_energy_counter(&tariff_counter);
    r_tariff_add_counter(&total, &g_tariff.last_synced_total_energy_counter, &tariff_counter);

    /* Copy to output pointer */
    *p_counter = total;
    
    return TARIFF_RET_OK;
}

/******************************************************************************
* Function Name : R_TARIFF_Format
* Interface     : uint8_t R_TARIFF_Format(void)
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
TARIFF_FUNC uint8_t R_TARIFF_Format(void)
{
	uint32_t    eeprom_addr;
    uint8_t     empty_page[STORAGE_EEPROM_PAGESIZE];
    uint16_t    size;
	r_tariff_t 	default_tariff;
    uint8_t     default_lookup_timeslot_tariff_number[SCHEDULER_NUMBER_OF_TARIFF_TIMESLOT_MAX] = {DEFAULT_LOOKUP_TIMESLOT_TARIFF_NUMBER};
	
    /* Create empty_page */
    memset(empty_page, 0, sizeof(empty_page));

    /* Clear Whole EEPROM */
    eeprom_addr = STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR;
    while (eeprom_addr < STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR)
    {
        if ((STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR - eeprom_addr) < STORAGE_EEPROM_PAGESIZE) {
            size = STORAGE_EEPROM_ENERGY_TARIFF_LAST_ADDR - eeprom_addr;
        }
        else {
            size = STORAGE_EEPROM_PAGESIZE;
        }

        if (EPR_Write(eeprom_addr, empty_page, size) != EPR_OK)
        {
            return STORAGE_ERROR;
        }

        eeprom_addr += size;

        R_WDT_Restart();
    }
	
	/* Write default value for Tariff state  */ 
    default_tariff.metering_mode = TARIFF_DEFAULT_METERING_MODE; 
    default_tariff.current_tariff_no = 0;
	memset(&default_tariff.last_synced_total_energy_counter, 0 ,sizeof(r_tariff_counter_t));
	memset(&default_tariff.last_synced_energy_counter_snapshot, 0 ,sizeof(r_tariff_counter_t));
	memset(&default_tariff.last_read_energy_counter_snapshot, 0 ,sizeof(r_tariff_counter_t));
	
	EPR_Write(STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR, (uint8_t *)&default_tariff, sizeof(r_tariff_t));	

    /* Default lookup timeslot - tariff_number */
    EPR_Write(
        STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR, 
        (uint8_t *)&default_lookup_timeslot_tariff_number[0], 
        sizeof(default_lookup_timeslot_tariff_number)
    );

    /* Formatted */
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_TARIFF_Restore
* Interface     : uint8_t R_TARIFF_Restore(void)
* Description   :
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
TARIFF_FUNC uint8_t	R_TARIFF_Restore(void)
{
	/* Read data of Tariff state: g_tariff from EEPROM */
	EPR_Read(STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR, (uint8_t *)&g_tariff, sizeof(r_tariff_t));
    EPR_Read(
        STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR,
        (uint8_t *)&g_tariff_lookup_timeslot_tariff_number[0],
        sizeof(g_tariff_lookup_timeslot_tariff_number)
    );
	
	return STORAGE_OK;
}

/******************************************************************************
* Function Name : R_TARIFF_Backup
* Interface     : uint8_t R_TARIFF_Backup(void)
* Description   : 
* Arguments     :
* Return Value  : uint8_t
******************************************************************************/
TARIFF_FUNC uint8_t	R_TARIFF_Backup(void)
{
	/* Write data of Tariff state: g_tariff to EEPROM */
	EPR_Write(STORAGE_EEPROM_ENERGY_TARIFF_STATE_ADDR, (uint8_t *)&g_tariff, sizeof(r_tariff_t));
    EPR_Write(
        STORAGE_EEPROM_ENERGY_TARIFF_LOOKUP_TIMESLOT_TARIFF_NUMBER_ADDR,
        (uint8_t *)&g_tariff_lookup_timeslot_tariff_number[0],
        sizeof(g_tariff_lookup_timeslot_tariff_number)
    );

	return STORAGE_OK;
}