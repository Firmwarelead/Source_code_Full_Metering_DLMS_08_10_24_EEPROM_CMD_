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
* File Name    : r_dlms_security.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/
// 2018-04-12 New creation

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"

/* DLMS Application */
#include "r_dlms_app.h"
#include "r_dlms_security.h"
#include "r_dlms_storage.h"
#include "r_dlms_factory_config.h"
#include "r_dlms_format.h"
#include <string.h>
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/
#if(defined( R_DLMS_APPS_SECURITY_STORAGE_ENABLE ) && R_DLMS_APPS_SECURITY_STORAGE_ENABLE == TRUE)

// extern uint8_t g_assc0_secret[];         /* Public Client */
// extern uint8_t g_assc0_secret[];         /* Public Client */
extern uint8_t g_assc1_secret[];            /* Meter Reader */
extern uint8_t g_assc2_secret[];            /* Utility Setting */
// extern uint8_t g_assc3_secret[];         /* Push */
extern uint8_t g_assc4_secret[16];          /* Firmware Upgrade */
// extern uint8_t g_assc5_secret[8];        /* IHD */


// const uint8_t g_assc0_secret_default[];
// const uint8_t g_assc3_secret_default[];
// const uint8_t g_assc5_secret_default[8];
extern uint8_t g_assc_shared_master_key[];              // = "RES_MasterKeyAll";

extern uint8_t	g_assc_shared_global_unicast_key[]  ;   // = "RES_UnicastAssc0";
extern uint8_t	g_assc_shared_global_broadcast_key[];   // = "RES_BroadcastKey";
extern uint8_t	g_assc_shared_authentication_key[]  ;   // = "RES_AuthenKey000";

#if(defined( IHD_ASSO_ENABLE ) && IHD_ASSO_ENABLE == 1)
extern uint8_t	g_assc5_global_unicast_key[]    ;       //= "RES_UnicastAssc5";
extern uint8_t	g_assc5_global_broadcast_key[]  ;       //= "RES_BroadKey0005";
extern uint8_t	g_assc5_authentication_key[]    ;       //= "RES_AuthenKey005";
#endif /* IHD_ASSO_ENABLE */


extern uint8_t R_DLMS_CLASSES_IsBufferWritable(uint8_t *p_buffer);

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/


/*************************************************************************
 * Default key
 *************************************************************************/
//const uint8_t g_assc0_secret_default[];
const uint8_t g_assc1_secret_default[8]     = R_DLMS_LLS_SECRET_DEFAULT;
const uint8_t g_assc2_secret_default[16]    = R_DLMS_HLS_KEY_US_DEFAULT;
// const uint8_t g_assc3_secret_default[];
const uint8_t g_assc4_secret_default[16]    = R_DLMS_HLS_KEY_FW_DEFAULT;
// const uint8_t g_assc5_secret_default[8];

const uint8_t g_assc_shared_KEK_default[16] = R_DLMS_MASTER_KEY_DEFAULT;     /* Master key */
const uint8_t g_assc_shared_GUK_default[16] = R_DLMS_SHARED_GUK_DEFAULT;     /* Global Unicast key */
const uint8_t g_assc_shared_GBK_default[16] = R_DLMS_SHARED_GBK_DEFAULT;     /* Global broadcast key */
const uint8_t g_assc_shared_AUK_default[16] = R_DLMS_SHARED_AUK_DEFAULT;     /* Authen key */

const uint8_t g_assc_IHD_GUK_default[16] = R_DLMS_IHD_GUK_DEFAULT;     /* IHD Global Unicast key */
const uint8_t g_assc_IHD_GBK_default[16] = R_DLMS_IHD_GBK_DEFAULT;     /* IHD Global broadcast key */
const uint8_t g_assc_IHD_AUK_default[16] = R_DLMS_IHD_AUK_DEFAULT;     /* IHD Authen key */


/**************************************************************************
 * Storage info
 **************************************************************************/
const DLMS_STORAGE storage_info_lls_secret  = { STORAGE_EEPROM_DLMS_LLS_SECRET_MR_ADDR,   8   };
const DLMS_STORAGE storage_info_hls_key_us  = { STORAGE_EEPROM_DLMS_HLS_KEY_US_ADDR,      16  };
const DLMS_STORAGE storage_info_hls_key_fw  = { STORAGE_EEPROM_DLMS_HLS_KEY_FW_ADDR,      16  };

const DLMS_STORAGE storage_info_shared_MK   =  { STORAGE_EEPROM_DLMS_MASTER_KEY_ADDR,     16  };

const DLMS_STORAGE storage_info_shared_GUK  = { STORAGE_EEPROM_DLMS_UNICAST_KEY_ADDR,     16  };
const DLMS_STORAGE storage_info_shared_GBK  = { STORAGE_EEPROM_DLMS_BROADCAST_KEY_ADDR,   16  };
const DLMS_STORAGE storage_info_shared_AUK  = { STORAGE_EEPROM_DLMS_AUTHEN_KEY_ADDR,      16  };

const DLMS_STORAGE storage_info_IHD_GUK = { STORAGE_EEPROM_DLMS_UNICAST_KEY_IHD_ADDR,     16  };
const DLMS_STORAGE storage_info_IHD_GBK = { STORAGE_EEPROM_DLMS_BROADCAST_KEY_IHD_ADDR,   16  };
const DLMS_STORAGE storage_info_IHD_AUK = { STORAGE_EEPROM_DLMS_AUTHEN_KEY_IHD_ADDR,      16  };

/**************************************************************************
 * Storage mapping
 **************************************************************************/
const dlms_securitykey_memmap_t backup_key_list[] = 
{
    /****************************************************************************************************************************
     * Storage location and size                        Variable                            Default value 
     ****************************************************************************************************************************/
    /* LLS key */
    { (DLMS_STORAGE *)&storage_info_lls_secret ,        g_assc1_secret,                     (uint8_t *)g_assc1_secret_default},
    /* HLS key */
    { (DLMS_STORAGE *)&storage_info_hls_key_us ,        g_assc2_secret,                     (uint8_t *)g_assc2_secret_default},
    { (DLMS_STORAGE *)&storage_info_hls_key_fw ,        g_assc4_secret,                     (uint8_t *)g_assc4_secret_default},

    /* Master key */
    { (DLMS_STORAGE *)&storage_info_shared_MK ,         g_assc_shared_master_key,           (uint8_t *)g_assc_shared_KEK_default},

    /* Global shared key */
    { (DLMS_STORAGE *)&storage_info_shared_GUK ,        g_assc_shared_global_unicast_key,   (uint8_t *)g_assc_shared_GUK_default},
    { (DLMS_STORAGE *)&storage_info_shared_GBK ,        g_assc_shared_global_broadcast_key, (uint8_t *)g_assc_shared_GBK_default},
    //{ (DLMS_STORAGE *)&storage_info_shared_AUK ,        g_assc_shared_authentication_key,   (uint8_t *)g_assc_shared_AUK_default},

#if(defined( IHD_ASSO_ENABLE ) && IHD_ASSO_ENABLE == 1)
    /* IHD key */
    { (DLMS_STORAGE *)&storage_info_IHD_GUK ,     g_assc5_global_unicast_key,   (uint8_t *)g_assc_IHD_GUK_default},
    { (DLMS_STORAGE *)&storage_info_IHD_GBK,    g_assc5_global_broadcast_key, (uint8_t *)g_assc_IHD_GBK_default},
    { (DLMS_STORAGE *)&storage_info_IHD_AUK,      g_assc5_authentication_key,   (uint8_t *)g_assc_IHD_AUK_default},
#endif /* IHD_ASSO_ENABLE */
};
const uint16_t backup_key_list_size = sizeof(backup_key_list) / sizeof(dlms_securitykey_memmap_t);

const DLMS_STORAGE storage_info_common_UK_counters = {STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_ADDR, STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK0_SIZE};
const DLMS_STORAGE storage_info_common_BK_counters = {STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_ADDR, STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK1_SIZE};

#if(defined( IHD_ASSO_ENABLE ) && IHD_ASSO_ENABLE == 1)
const DLMS_STORAGE storage_info_IHD_UK_counters = {STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_ADDR, STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK2_SIZE};
const DLMS_STORAGE storage_info_IHD_BK_counters = {STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_ADDR, STORAGE_EEPROM_DLMS_INVOCATION_COUNTER_EK3_SIZE};
#endif /* IHD_ASSO_ENABLE */
/******************************************************************************
* Function Name : R_DLMS_Security_BackupAllInvocationCounter
* Interface     : void R_DLMS_Security_BackupAllInvocationCounter(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
void R_DLMS_Security_BackupAllInvocationCounter(void)
{
	/* Common unicast key */
	R_DLMS_EEPROM_Write(storage_info_common_UK_counters, (uint8_t *)&g_assc_shared_global_unicast_key_counter);
    /* Common broadcast key */
	R_DLMS_EEPROM_Write(storage_info_common_BK_counters, (uint8_t *)&g_assc_shared_global_broadcast_key_counter);
#if (defined(IHD_ASSO_ENABLE) && IHD_ASSO_ENABLE == 1)
    /* IHD unicast key */
	R_DLMS_EEPROM_Write(storage_info_IHD_UK_counters, (uint8_t *)&g_assc5_global_unicast_key_counters);
    /* IHD broadcast key */
	R_DLMS_EEPROM_Write(storage_info_IHD_BK_counters, (uint8_t *)&g_assc5_global_broadcast_key_counters);
#endif /* IHD_ASSO_ENABLE */
}
/******************************************************************************
* Function Name : R_DLMS_Security_BackupAllInvocationCounter
* Interface     : void R_DLMS_Security_BackupAllInvocationCounter(
*               :     void
*               : );
* Description   :
* Arguments     :
* Return Value  : void
******************************************************************************/
static void R_DLMS_Security_RestoreAllInvocationCounter(void)
{
	/* Common unicast key */
	R_DLMS_EEPROM_Read(storage_info_common_UK_counters, (uint8_t *)&g_assc_shared_global_unicast_key_counter);
    /* Common broadcast key */
	R_DLMS_EEPROM_Read(storage_info_common_BK_counters, (uint8_t *)&g_assc_shared_global_broadcast_key_counter);
#if (defined(IHD_ASSO_ENABLE) && IHD_ASSO_ENABLE == 1)
    /* IHD unicast key */
	R_DLMS_EEPROM_Read(storage_info_IHD_UK_counters, (uint8_t *)&g_assc5_global_unicast_key_counters);
    /* IHD broadcast key */
	R_DLMS_EEPROM_Read(storage_info_IHD_BK_counters, (uint8_t *)&g_assc5_global_broadcast_key_counters);
#endif /* IHD_ASSO_ENABLE */
}
/******************************************************************************
* Function Name : R_DLMS_Security_Format
* Interface     : void R_DLMS_Security_Format(
*               :     void
*               : );
* Description   : This function will write the content of p_default to eeprom
*    			:       for all keys in EEPROM storage.
* Arguments     : None.
* Function Calls: This function should be called by R_DLMS_App_Format.
* Return Value  : None.
******************************************************************************/
void R_DLMS_Security_Format(void)
{
	uint8_t i;

    for (i = 0; i < backup_key_list_size; i++)
    {
        if (backup_key_list[i].p_info != NULL &&
            backup_key_list[i].p_default != NULL &&
            backup_key_list[i].p_info->length > 0 &&
            backup_key_list[i].p_info->length < 32) // TBD: MAX Key length
        {
            if (R_DLMS_Storage_IsNull((uint8_t *)backup_key_list[i].p_default, backup_key_list[i].p_info->length) != TRUE)
            {
                R_DLMS_EEPROM_Write(*backup_key_list[i].p_info, (uint8_t *)backup_key_list[i].p_default);
            }
        }
    }
}

/******************************************************************************
* Function Name : R_DLMS_Security_KeyBackup
* Interface     : void R_DLMS_Security_KeyBackup(
*               :     void
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_Security_KeyBackup ( uint8_t *p_key, uint16_t length, dlms_securitykey_memmap_t * p_keymap )
{
	uint8_t rlt;		/* Result */
    if ((p_key == NULL) ||
        (p_keymap == NULL))
    {
        return RLT_ERR_NULL;
    }
    
    if (length != p_keymap->p_info->length)
    {
        return RLT_ERR;
    }

    /* Check key input */
    if (R_DLMS_Storage_IsNull((uint8_t *)p_key, p_keymap->p_info->length) == TRUE)
    {
        return RLT_ERR_STORAGE_WEAK_PASSWORD;
    }
    /*  */
    rlt = R_DLMS_EEPROM_Write(*p_keymap->p_info, (uint8_t *)p_key);

	R_DLMS_Security_BackupAllInvocationCounter();

	return rlt;	/* Return result */
}

/******************************************************************************
* Function Name : R_DLMS_Security_RestoreAt
* Interface     : void R_DLMS_Security_RestoreAt(
*               :     uint8_t key_id
*               : );
* Description   : Restore key at key_id
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Security_RestoreAt(uint8_t key_id)
{
    uint8_t key_buffer[32];
    dlms_securitykey_memmap_t *p_keymap;

    p_keymap = (dlms_securitykey_memmap_t *)&backup_key_list[key_id];
    if (R_DLMS_EEPROM_Read(*p_keymap->p_info, (uint8_t *)key_buffer) == RLT_SUCCESS)
    {
        if (R_DLMS_CLASSES_IsBufferWritable(p_keymap->p_key) == TRUE)
        {
            if (R_DLMS_Storage_IsNull((uint8_t *)key_buffer, p_keymap->p_info->length) == TRUE)
            {
                memcpy((uint8_t *)key_buffer, (uint8_t *)p_keymap->p_default, p_keymap->p_info->length);
                R_DLMS_EEPROM_Write(*p_keymap->p_info, (uint8_t *)key_buffer);
            }

            memcpy((uint8_t *)p_keymap->p_key, (uint8_t *)key_buffer, p_keymap->p_info->length);
        }
    }
}


/******************************************************************************
* Function Name : R_DLMS_Security_Restore
* Interface     : void R_DLMS_Security_Restore(
*               :     void
*               : );
* Description   : Restore all keys from storage
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Security_Restore(void)
{
    uint8_t key_id;
    uint8_t key_buffer[32];

    dlms_securitykey_memmap_t *p_keymap;
    for (key_id = 0; key_id < backup_key_list_size; key_id++)
    {
        R_DLMS_Security_RestoreAt(key_id);
    }
    /* Restore all invocation counter */
    R_DLMS_Security_RestoreAllInvocationCounter();
}
/******************************************************************************
* Function Name : R_DLMS_Security_Backup
* Interface     : void R_DLMS_Security_Restore(
*               :     void
*               : );
* Description   : Store all invocarion counter to storage
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
void R_DLMS_Security_Backup(void)
{
    /* Restore all invocation counter */
    R_DLMS_Security_BackupAllInvocationCounter();
}

#endif /* R_DLMS_APPS_SECURITY_STORAGE_ENABLE */