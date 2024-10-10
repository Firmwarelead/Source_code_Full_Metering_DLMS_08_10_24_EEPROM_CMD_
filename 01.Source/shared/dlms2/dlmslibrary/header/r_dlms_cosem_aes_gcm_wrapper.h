/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_cosem_aes_gcm_wrapper.h
* Version      : 1.00
* Description  : 
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.01.2018 
******************************************************************************/

#ifndef _R_DLMS_COSEM_AES_GCM_WRAPPER_H
#define _R_DLMS_COSEM_AES_GCM_WRAPPER_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

uint16_t R_DLMS_AES_GCM_Encrypt(
    uint8_t *plain,
    uint8_t *cipher,
    uint32_t data_len,
    uint8_t *key,
    uint8_t *atag,
    uint32_t atag_len,
    uint8_t *iv,
    uint32_t iv_len,
    uint8_t *aad,
    uint32_t aad_len
);

uint16_t R_DLMS_AES_GCM_Decrypt(
    uint8_t *cipher,
    uint8_t *plain,
    uint32_t data_len,
    uint8_t *key,
    uint8_t *atag,
    uint32_t atag_len,
    uint8_t *iv,
    uint32_t iv_len,
    uint8_t *aad,
    uint32_t aad_len
);

#endif /* _R_DLMS_COSEM_AES_GCM_WRAPPER_H */

