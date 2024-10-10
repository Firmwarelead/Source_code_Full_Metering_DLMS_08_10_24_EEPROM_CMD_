/******************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_tariff.h
* Version      : 1.00
* Description  : Tariff management Header file
******************************************************************************
* History : DD.MM.YYYY Version Description
******************************************************************************/

#ifndef _R_TARIFF_H
#define _R_TARIFF_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct st_r_tariff_counter_t
{
    float32_t   active_imp;
    float32_t   active_exp;
    float32_t   reactive_ind_imp;
    float32_t   reactive_ind_exp;
    float32_t   reactive_cap_imp;
    float32_t   reactive_cap_exp;
    float32_t   apparent_imp;
    float32_t   apparent_exp;
} r_tariff_counter_t;
typedef enum e_r_tariff_metering_mode_t
{
    TARIFF_METERING_MODE_FORWARDED_ONLY = 0,
    TARIFF_METERING_MODE_NET,
} r_tariff_metering_mode_t;

typedef struct st_r_tariff_t
{
    r_tariff_metering_mode_t    metering_mode;                          /* Tariff metering mode: NET or Forwarded only */
    uint8_t                     current_tariff_no;                      /* Not cleared on usage yet */
    r_tariff_counter_t          last_synced_total_energy_counter;       /* Reference point for tariff total energy counter */
    r_tariff_counter_t          last_synced_energy_counter_snapshot;    /* Reference point for energy counter in snapshot (tariff counter type) */
    r_tariff_counter_t          last_read_energy_counter_snapshot;      /* Last reading of instantaneous snapshot: energy counters params (tariff counter type) */

} r_tariff_t;

/******************************************************************************
Macro definitions
******************************************************************************/
/* No special function attribute */
#define TARIFF_FUNC

#define TARIFF_RET_OK                       0
#define TARIFF_RET_ERROR                    1
#define TARIFF_RET_ERROR_PARAMS             2

/* Default metering mode */
#define TARIFF_DEFAULT_METERING_MODE            TARIFF_METERING_MODE_NET

/* Default lookup timeslot-tariff */
#define DEFAULT_LOOKUP_TIMESLOT_TARIFF_NUMBER   0,  /* Timeslot 0 */\
                                                1,  /* Timeslot 1 */\
                                                2,  /* Timeslot 2 */\
                                                3,  /* Timeslot 3 */\
                                                4,  /* Timeslot 4 */\
                                                5,  /* Timeslot 5 */\
                                                6,  /* Timeslot 6 */\
                                                7,  /* Timeslot 7 */

/******************************************************************************
Variable Externs
******************************************************************************/
extern r_tariff_t g_tariff;
extern uint8_t g_tariff_lookup_timeslot_tariff_number[];

/******************************************************************************
Functions Prototypes
*****************************************************************************/

/* Operation control */
TARIFF_FUNC void R_TARIFF_Init(void);
TARIFF_FUNC void R_TARIFF_PollingProcessing(void);

/* Control metering mode (net or forwarded only) */
TARIFF_FUNC r_tariff_metering_mode_t R_TARIFF_GetMeteringMode(void);
TARIFF_FUNC uint8_t R_TARIFF_SetMeteringMode(r_tariff_metering_mode_t mode);

/* Internal operation data */
TARIFF_FUNC uint8_t R_TARIFF_GetTotalEnergyCounter(r_tariff_counter_t * p_counter);          /* Tariff total counter */

/* Measurement APIs: energy for each tariff (in kWh, kVarh or kVAh), export mask off when metering mode is forwarded only */
TARIFF_FUNC uint8_t R_TARIFF_GetImportActiveEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetExportActiveEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetImportCapacitiveReactiveEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetExportCapacitiveReactiveEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetImportInductiveReactiveEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetExportInductiveReactiveEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetImportApparentEnergyTariff(uint8_t tariff, float32_t *energy);
TARIFF_FUNC uint8_t R_TARIFF_GetExportApparentEnergyTariff(uint8_t tariff, float32_t *energy);

/* Measurement APIs: energy total (sum of all tariffs) (in kWh, kVarh or kVAh), export mask off when metering mode is forwarded only */
TARIFF_FUNC float32_t R_TARIFF_GetImportActiveEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetExportActiveEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetImportCapacitiveReactiveEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetExportCapacitiveReactiveEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetImportInductiveReactiveEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetExportInductiveReactiveEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetImportApparentEnergyTotal(void);
TARIFF_FUNC float32_t R_TARIFF_GetExportApparentEnergyTotal(void);

/* Storage */
TARIFF_FUNC uint8_t R_TARIFF_Format(void);
TARIFF_FUNC uint8_t	R_TARIFF_Restore(void);
TARIFF_FUNC uint8_t	R_TARIFF_Backup(void);

#endif /* _R_TARIFF_H */

