/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_nameplate.h
* Version      : Version
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

#ifndef _R_NAMEPLATE_H
#define _R_NAMEPLATE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Driver */
#include "r_cg_macrodriver.h"

/* Common */
#include "typedef.h"
#include "compiler.h"

/* EMSDK */
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define NAMEPLATE_ID_LDN                        (0)    /* NAMEPLATE ID: 0 , Logical device name */
#define NAMEPLATE_ID_SN                         (1)    /* NAMEPLATE ID: 1 , Meter serial number */
#define NAMEPLATE_ID_MFR                        (2)    /* NAMEPLATE ID: 2 , Manufacturer name */
#define NAMEPLATE_ID_DEVICE_ID                  (3)    /* NAMEPLATE ID: 3 , Device ID */
#define NAMEPLATE_ID_CATEGORY                   (4)    /* NAMEPLATE ID: 4 , Meter Category */
#define NAMEPLATE_ID_CURRENT_RATING             (5)    /* NAMEPLATE ID: 5 , Ib-Imax */
#define NAMEPLATE_ID_YEAR_OF_MANUFACTURE        (6)    /* NAMEPLATE ID: 6 , Meter Year of Manufacture */
#define NAMEPLATE_ID_TYPE                       (7)    /* NAMEPLATE ID: 7 , Meter type */
#define NAMEPLATE_ID_FIRMWARE_VERSION           (8)    /* NAMEPLATE ID: 8 , Firmware version */
#define NAMEPLATE_ID_FLAGID                     (9)    /* NAMEPLATE ID: 9 , Flag ID */


/* String length */
#define G_DLMS_LDN_NAME_SIZE                    (sizeof(METER_LOGICAL_DEVICE_NAME)   -1)
#define G_DLMS_SERIAL_NUMBER_SIZE               (sizeof(METER_SERIAL_NUMBER)         -1)
#define G_DLMS_MANUFACTURER_NAME_SIZE           (sizeof(METER_MANUFACTURE)           -1)
#define G_DLMS_DEVICE_ID_SIZE                   (sizeof(METER_LOGICAL_DEVICE_NAME)   -1)
#define G_DLMS_CATEGORY_NAME_SIZE               (sizeof(METER_CATEGORY)              -1)
#define G_DLMS_CURRENT_RATING_SIZE              (sizeof(METER_CURRENT_RATING)        -1)
#define G_DLMS_YEAR_OF_MANUFACTURE_SIZE         (sizeof(METER_YEAR_OF_MANUFACTURE)   -1)
#define G_DLMS_METER_TYPE_SIZE                  (sizeof(METER_TYPE)                  -1)
#define G_DLMS_METER_TYPE_SIZE                  (sizeof(METER_TYPE)                  -1)
#define G_DLMS_METER_VERSION_SIZE               (sizeof(METER_FIRMWARE_VERSION)      -1)

#define MSN_LENGTH_MAX          (16)
#define MFR_NAME_LENGTH_MAX     (50)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef struct tag_meter_nameplate_t
{
    uint8_t FlagID[3];
    uint8_t MSN_Len;
    uint8_t MSN[MSN_LENGTH_MAX];
    uint8_t Category[2];
    uint8_t MeterType;
    uint8_t Ib;
    uint8_t IMax;
    uint8_t Year;
    uint8_t ManufacturerNameLen;
    uint8_t ManufacturerName[MFR_NAME_LENGTH_MAX];
    uint16_t CheckCode;
} meter_nameplate_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
void R_NAMEPLATE_Restore(void);
void R_NAMEPLATE_Backup(void);
uint8_t R_NAMEPLATE_Format(void);

uint8_t R_NAMEPLATE_WriteToStorage(meter_nameplate_t *p_nameplate);
uint8_t R_NAMEPLATE_WriteByID(uint8_t item_id, uint8_t *p_buffer, uint16_t len);
void R_NAMEPLATE_GetByID(const uint8_t nameplate_id, uint8_t *p_buffer, uint16_t *p_len);

#ifdef __DEBUG
void R_NAMEPLATE_DEBUG_PrintInformation(void);
#endif

#endif /* _R_NAMEPLATE_H */