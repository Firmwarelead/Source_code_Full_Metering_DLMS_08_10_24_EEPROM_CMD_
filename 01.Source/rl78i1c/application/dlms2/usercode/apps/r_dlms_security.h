/***********************************************************************************************************************
  Copyright (C) 2011 Renesas Electronics Corporation, All Rights Reserved.
************************************************************************************************************************
* File Name    : r_dlms_security.h
* Version      : v1.0
* Description  : Description
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

#ifndef _R_DLMS_SECURITY_H
#define _R_DLMS_SECURITY_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"

#include "r_dlms_app.h"
#include "r_dlms_storage.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/


/* Value defined */
#define SECURITY_STORAGE_EEPROM         (0x01)
#define SECURITY_STORAGE_DATAFLASH      (0x02)

#define SECURITY_STORAGE_RAW_KEY        (0x03)
#define SECURITY_STORAGE_HASHED_KEY      (0x04)

/****************************************************************
 * Configure for security key storage
 ****************************************************************/

/* 
 * Specify where the key is storaged
 * Available options are:
 *  1. SECURITY_STORAGE_EEPROM      -> Security keys are stored in EEPROM
 *  2. SECURITY_STORAGE_DATAFLASH   -> Security keys are stored in Data flash
 */
#define R_DLMS_SECURITY_STORAGE_LOCATION          (SECURITY_STORAGE_EEPROM)


/* 
 * Specify how the key is stored
 * Available options are:
 *  1. SECURITY_STORAGE_RAW_KEY      -> Security keys are stored by raw
 *  2. SECURITY_STORAGE_HASHED_KEY   -> Security keys are hashed before stored
 */
#define R_DLMS_SECURITY_STORED_OPTION               (SECURITY_STORAGE_RAW_KEY)


/* BACKUP/RESTORE API */
#define R_DLMS_Backup_LLSSecret_MR(p_key, length)   R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_LLS])
#define R_DLMS_Backup_HLS_Key_US(p_key, length)     R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_HLS_US])
#define R_DLMS_Backup_HLS_Key_FW(p_key, length)     R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_HLS_FW])
#define R_DLMS_Backup_Shared_MK(p_key, length)      R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_SHARED_MK])
#define R_DLMS_Backup_Shared_GUK(p_key, length)     R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_SHARED_GUK])
#define R_DLMS_Backup_Shared_GBK(p_key, length)     R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_SHARED_GBK])
#define R_DLMS_Backup_Shared_AK(p_key, length)      R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_SHARED_AK])
#define R_DLMS_Backup_IHD_GUK(p_key, length)        R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_IHD_GUK])
#define R_DLMS_Backup_IHD_GBK(p_key, length)        R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_IHD_GBK])
#define R_DLMS_Backup_IHD_AK(p_key, length)         R_DLMS_Security_KeyBackup(p_key, length, (dlms_securitykey_memmap_t *)&backup_key_list[SECURITY_KEYLIST_ID_IHD_AK])

#define R_DLMS_Restore_Shared_MK()      R_DLMS_Security_RestoreAt(3)
#define R_DLMS_Restore_Shared_GUK()     R_DLMS_Security_RestoreAt(4)
#define R_DLMS_Restore_Shared_GBK()     R_DLMS_Security_RestoreAt(5)
#define R_DLMS_Restore_Shared_AK()      R_DLMS_Security_RestoreAt(6)
#define R_DLMS_Restore_IHD_GUK()        R_DLMS_Security_RestoreAt(7)
#define R_DLMS_Restore_IHD_GBK()        R_DLMS_Security_RestoreAt(8)
#define R_DLMS_Restore_IHD_AK()         R_DLMS_Security_RestoreAt(9)
#define R_DLMS_Restore_LLSKeyMR()       R_DLMS_Security_RestoreAt(0)
#define R_DLMS_Restore_HLSKeyUS()       R_DLMS_Security_RestoreAt(1)
#define R_DLMS_Restore_HLSKeyFW()       R_DLMS_Security_RestoreAt(2)


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum tag_backup_key_list_id_t
{
    SECURITY_KEYLIST_ID_LLS = 0,
    SECURITY_KEYLIST_ID_HLS_US,
    SECURITY_KEYLIST_ID_HLS_FW,
    SECURITY_KEYLIST_ID_SHARED_MK,
    SECURITY_KEYLIST_ID_SHARED_GUK,
    SECURITY_KEYLIST_ID_SHARED_GBK,
    SECURITY_KEYLIST_ID_SHARED_AK,
    SECURITY_KEYLIST_ID_IHD_GUK,
    SECURITY_KEYLIST_ID_IHD_GBK,
    SECURITY_KEYLIST_ID_IHD_AK,
} backup_key_list_id_t;

typedef struct tag_dlms_securitykey_memmap_t
{
    DLMS_STORAGE * p_info;
    uint8_t      * p_key;
    uint8_t      * p_default;
} dlms_securitykey_memmap_t;

/***********************************************************************************************************************
Variable Externs
***********************************************************************************************************************/
extern const dlms_securitykey_memmap_t backup_key_list[];
extern const uint16_t backup_key_list_size;
/***********************************************************************************************************************
Functions Prototypes
***********************************************************************************************************************/
#if(defined( R_DLMS_APPS_SECURITY_STORAGE_ENABLE ) && R_DLMS_APPS_SECURITY_STORAGE_ENABLE == TRUE)


void R_DLMS_Security_BackupAllInvocationCounter(void);
void R_DLMS_Security_Format(void);
uint8_t R_DLMS_Security_KeyBackup(uint8_t *p_key, uint16_t length, dlms_securitykey_memmap_t *p_keymap);

void R_DLMS_Security_RestoreAt(uint8_t key_id);
void R_DLMS_Security_Restore(void);
void R_DLMS_Security_PollingProcessing(void);
void R_DLMS_Security_Backup(void);
#else

R_DLMS_Security_KeyBackup(p_key,length,p_keymap)        {;}

#define R_DLMS_Security_Restore()                   {;}
#define R_DLMS_Security_PollingProcessing()             {;}

#endif /* R_DLMS_APPS_SECURITY_STORAGE_ENABLE */

#endif /* _R_DLMS_SECURITY_H */