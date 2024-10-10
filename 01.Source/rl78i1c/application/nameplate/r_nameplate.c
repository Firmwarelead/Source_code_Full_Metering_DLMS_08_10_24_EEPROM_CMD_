/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dlms_nameplate.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

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
#include "dataflash.h"

/* Application */
#include "r_meter_format.h"
#include "r_nameplate.h"

#if defined(FAST_FOTA)
#include "bl_image.h"
#endif

/* Standard library */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#ifdef __DEBUG
//#include "debug.h"
//#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* EEPROM ADDRESS MAPPING */
#define NAMEPLATE_STORAGE_START_ADDRESS     (STORAGE_CONFIG_NAMEPLATE_FLAGID_ADDR)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
const meter_nameplate_t g_nameplate_default =
{
    /* FlagID              = */ METER_DEFAULT_FLAG_ID,
    /* MSN_Len             = */ sizeof(METER_DEFAULT_SERIAL_NUMBER) - 1,
    /* MSN                 = */ METER_DEFAULT_SERIAL_NUMBER,
    /* Category            = */ METER_DEFAULT_CATEGORY,
    /* MeterType           = */ METER_DEFAULT_TYPE,
    /* Ib                  = */ METER_DEFAULT_IB,
    /* IMax                = */ METER_DEFAULT_IMAX,
    /* Year                = */ METER_DEFAULT_YEAR_OF_MANUFACTURE,
    /* ManufacturerNameLen = */ sizeof(METER_DEFAULT_MANUFACTURE) - 1,
    /* ManufacturerName    = */ METER_DEFAULT_MANUFACTURE
};

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/
const uint8_t g_nameplate_firmware_version[]        = METER_DEFAULT_FIRMWARE_VERSION;      /* Firmware version */

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

meter_nameplate_t R_NAMEPLATE_ReadFromStorage(void);
/******************************************************************************
* Function Name : R_NAMEPLATE_ReadFromStorage
* Interface     : meter_nameplate_t R_NAMEPLATE_ReadFromStorage(void)
* Description   :
* Arguments     :
* Return Value  : meter_nameplate_t
******************************************************************************/
meter_nameplate_t R_NAMEPLATE_ReadFromStorage(void)
{
    meter_nameplate_t nameplate;

    DATAFLASH_Read(
            NAMEPLATE_STORAGE_START_ADDRESS,
            (uint8_t *) &nameplate,
            sizeof(meter_nameplate_t)
    );
    /* Check length of meter serial number */
    if(nameplate.MSN_Len > MSN_LENGTH_MAX)
    {
        /* Assign maximum if length is over buffer length */
        nameplate.MSN_Len  = MSN_LENGTH_MAX;
    }
    else
    {
        
    }
    /* Check length of manufacturer name */
    if(nameplate.ManufacturerNameLen > MFR_NAME_LENGTH_MAX)
    {
        /* Assign maximum if length is over buffer length */
        nameplate.ManufacturerNameLen  = MFR_NAME_LENGTH_MAX;
    }
    else
    {
        
    }
    

    return nameplate;
}


/******************************************************************************
* Function Name : R_NAMEPLATE_WriteToStorage
* Interface     : meter_nameplate_t R_NAMEPLATE_WriteToStorage(void)
* Description   :
* Arguments     :
* Return Value  : meter_nameplate_t
******************************************************************************/
uint8_t R_NAMEPLATE_WriteToStorage(meter_nameplate_t *p_nameplate)
{
    uint8_t write_result;
    meter_nameplate_t nameplate;

    write_result = DATAFLASH_Write(
                        NAMEPLATE_STORAGE_START_ADDRESS,
                        (uint8_t *) p_nameplate,
                        sizeof(meter_nameplate_t)
                    ) == DATAFLASH_OK;

    return write_result;
}

/******************************************************************************
* Function Name : R_NAMEPLATE_WriteByID
* Interface     : void R_NAMEPLATE_WriteByID(uint8_t item_id, uint8_t *p_buffer, uint16_t len)
* Description   :
* Arguments     :
*               : nameplate_id: Input, acceptable value is from 0 to 9 as below
*                                                   (0)    : Logical device name
*                                                   (1)    : Meter serial number
*                                                   (2)    : Manufacturer name
*                                                   (3)    : Device ID
*                                                   (4)    : Meter Category
*                                                   (5)    : Ib-Imax
*                                                   (6)    : Meter Year of Manufacture
*                                                   (7)    : Meter type
*                                                   (8)    : Firmware version
*                                                   (9)    : Flag ID     
* Return Value  : void
******************************************************************************/
uint8_t R_NAMEPLATE_WriteByID(uint8_t nameplate_id, uint8_t *p_buffer, uint16_t len)
{
    uint32_t addr_data;
    uint32_t design_len;
    uint8_t operation_result = FALSE;
    uint8_t buffer[100];

    uint32_t u32_temp_value;

    meter_nameplate_t nameplate;
    nameplate = R_NAMEPLATE_ReadFromStorage();

    switch (nameplate_id)
    {
        case NAMEPLATE_ID_YEAR_OF_MANUFACTURE:                      /* Year of manufature */
            u32_temp_value = atoi((char *)p_buffer);
            u32_temp_value %= 2000;
            nameplate.Year = u32_temp_value;
            break;

        case NAMEPLATE_ID_FIRMWARE_VERSION:                         /* Firmware version of meter */
            /* FW Version is not stored in Dataflash */
            return FALSE;

        case NAMEPLATE_ID_LDN:                                      /* Logical device name */
            /* Logical device name is not writable */
              return FALSE;

        case NAMEPLATE_ID_SN:                                       /* Meter serial number */
            memcpy(nameplate.MSN, p_buffer, len);
            nameplate.MSN_Len = len;
            break;

        case NAMEPLATE_ID_MFR:                                      /* Manufacturer name */
            memcpy(nameplate.ManufacturerName, p_buffer, len);
            nameplate.ManufacturerNameLen = len;
            break;

        case NAMEPLATE_ID_DEVICE_ID:                                /* Device ID */
            return FALSE;
            
        case NAMEPLATE_ID_CATEGORY:                                 /* Meter Category */
            memcpy(nameplate.Category, p_buffer, 2);
            break;

        case NAMEPLATE_ID_CURRENT_RATING:                           /* Current rating */
            len = sprintf_tiny((char *)p_buffer, (const char *)"%d(%d) (A)", nameplate.Ib, nameplate.IMax);
            break;

        case NAMEPLATE_ID_TYPE:                                     /* Meter type */
            nameplate.MeterType = p_buffer[0];
            break;

        case NAMEPLATE_ID_FLAGID:                                   /* FLAG ID */
            memcpy(nameplate.FlagID, p_buffer, 3);
            break;

        default:
            return FALSE;
    }

    R_NAMEPLATE_WriteToStorage(&nameplate);

    return operation_result;
}

/******************************************************************************
* Function Name : R_NAMEPLATE_GetById
* Interface     : void R_NAMEPLATE_GetById(uint8_t item_id)
* Description   :
* Arguments     :
*               : nameplate_id: Input, acceptable value is from 0 to 9 as below
*                                                   (0)    : Logical device name
*                                                   (1)    : Meter serial number
*                                                   (2)    : Manufacturer name
*                                                   (3)    : Device ID
*                                                   (4)    : Meter Category
*                                                   (5)    : Ib-Imax
*                                                   (6)    : Meter Year of Manufacture
*                                                   (7)    : Meter type
*                                                   (8)    : Firmware version
*                                                   (9)    : Flag ID
* Return Value  : void
******************************************************************************/
void R_NAMEPLATE_GetByID(const uint8_t nameplate_id, uint8_t *p_buffer, uint16_t *p_len)
{
    uint32_t addr_data;
    uint32_t design_len;
    uint16_t len;
    uint8_t operation_result;
    uint8_t buffer[100];

    uint32_t u32_temp_value;

    meter_nameplate_t nameplate;
    
    if (p_buffer == NULL || p_len == NULL)
    {
        return;
    }

    nameplate = R_NAMEPLATE_ReadFromStorage();

    switch (nameplate_id)
    {
        case NAMEPLATE_ID_YEAR_OF_MANUFACTURE:                      /* Year of manufature */
            u32_temp_value = 2000 + nameplate.Year; 
            sprintf((char *)p_buffer, "%lu", u32_temp_value);
            *p_len = 4;
            break;

        case NAMEPLATE_ID_FIRMWARE_VERSION:                         /* Firmware version of meter */
            {
            
                len = sizeof(g_nameplate_firmware_version);
                memcpy(p_buffer, g_nameplate_firmware_version, len);
                *p_len = len - 1;

#if defined(FAST_FOTA)
                /* Overwrite firmware verion by using firmware version from bootloader */
                {
                    bl_image_header_t image_header;
                    /* For Smart meter, get value from bootloader */
                    BL_IMAGE_GetHeaderInfo(&image_header, BL_IMAGE_CURRENT_BANK);
                    //Convert firmware version bytes to readable ASCII string. Example: "V1.2.2 (Ind)"
                    *p_len =  sprintf_tiny((char *)p_buffer, (const char *)"v%d.%d.%d (Ind)",
                                    image_header.software_version[2],
                                    image_header.software_version[1],
                                    image_header.software_version[0]
                            );
                }
#endif
            }

            break;

        case NAMEPLATE_ID_LDN:                                      /* Logical device name */
            memcpy(p_buffer, nameplate.FlagID, 3);
            memcpy(p_buffer+3, nameplate.MSN + 11, 5);
            *p_len = 8;
            break;
        case NAMEPLATE_ID_SN:                                       /* Meter serial number */
            memcpy(p_buffer, nameplate.MSN, nameplate.MSN_Len);
            *p_len = nameplate.MSN_Len;
            break;

        case NAMEPLATE_ID_MFR:                                      /* Manufacturer name */
            memcpy(p_buffer, nameplate.ManufacturerName, nameplate.ManufacturerNameLen);
            *p_len = nameplate.ManufacturerNameLen;
            break;

        case NAMEPLATE_ID_DEVICE_ID:                                /* Device ID */
            memcpy(p_buffer, nameplate.FlagID, 3);
            memcpy(p_buffer+3, nameplate.MSN, nameplate.MSN_Len);
            *p_len = 3 + nameplate.MSN_Len;
            break;
            
        case NAMEPLATE_ID_CATEGORY:                                 /* Meter Category */
            memcpy(p_buffer, nameplate.Category, 2);
            *p_len = 2;
            break;

        case NAMEPLATE_ID_CURRENT_RATING:                           /* Current rating */
            // Extract value that read from Dataflash
            len = sprintf_tiny((char *)p_buffer, (const char *)"%d(%d) (A)", nameplate.Ib, nameplate.IMax);
            *p_len = len;
            break;

        case NAMEPLATE_ID_TYPE:                                     /* Meter type */
            // Extract value that read from Dataflash
            p_buffer[0] = nameplate.MeterType;
            *p_len = 1;
            break;

        case NAMEPLATE_ID_FLAGID:                                   /* FLAG ID */
            memcpy(p_buffer,  nameplate.FlagID, 3);
            *p_len = 3;

            break;
        default:
            break;
    }

}

/******************************************************************************
* Function Name : R_NAMEPLATE_Backup
* Interface     : void R_NAMEPLATE_Backup(
*               :     void
*               : );
* Description   : store data from RAM to storage
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
void R_NAMEPLATE_Backup(void)
{
    /* Don't need backup, nameplate is one-time writing when format */
}

/******************************************************************************
* Function Name : R_NAMEPLATE_Format
* Interface     : uint8_t R_NAMEPLATE_Format(
*               :     uint8_t
*               : );
* Description   : format data, write default data to storage.
* Arguments     : 
* Function Calls: 
* Return Value  : 
******************************************************************************/
uint8_t R_NAMEPLATE_Format(void)
{
    return R_NAMEPLATE_WriteToStorage((meter_nameplate_t *)&g_nameplate_default);
}



#ifdef __DEBUG
/******************************************************************************
* Function Name : R_NAMEPLATE_DEBUG_PrintInformation
* Interface     : void R_NAMEPLATE_DEBUG_PrintInformation(void)
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_NAMEPLATE_DEBUG_PrintInformation(void)
{
    uint8_t i, count;
    uint8_t buffer[100];
    uint16_t len;

    CMD_SendString((uint8_t *)"NAMEPLATE \n\r");

    //for(i = 0; i < 10; i++)
    //{
    //    R_NAMEPLATE_GetById((const uint8_t)i, buffer, &len);
    //    CMD_Printf((uint8_t *)"%s\n\r", buffer);
    //}

}
#endif