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
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************	
* File Name    : r_dlms_cosem_aes_gcm_wrapper.c
* Version      : 1.00
* Device(s)    : None
* Tool-Chain   : 
* H/W Platform : Unified Energy Meter Platform
* Description  : 
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 30.01.2018 
******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_cosem_aes_gcm_wrapper.h"
#include "r_gcm_hwip.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name : R_DLMS_AES_GCM_Encrypt
* Interface     : uint16_t R_DLMS_AES_GCM_Encrypt(
*               :     uint8_t * plain  
*               :     uint8_t * cipher 
*               :     uint32_t data_len
*               :     uint8_t * key    
*               :     uint8_t * atag   
*               :     uint32_t atag_len
*               :     uint8_t * iv     
*               :     uint32_t iv_len  
*               :     uint8_t * aad    
*               :     uint32_t aad_len 
*               : );
* Description   : 
* Arguments     : uint8_t * plain  :
*               : uint8_t * cipher :
*               : uint32_t data_len:
*               : uint8_t * key    :
*               : uint8_t * atag   :
*               : uint32_t atag_len:
*               : uint8_t * iv     :
*               : uint32_t iv_len  :
*               : uint8_t * aad    :
*               : uint32_t aad_len :
* Function Calls: 
* Return Value  : int32_t
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
)
{	
	uint8_t aad_local[8];
	
	R_gcm_Init(GCM_AESKEY_LEN_128);
	
	/* To use AES-GCM lib : need aad for all cases of SC */
	if (aad == NULL || aad_len == 0) {
		aad = aad_local;
		aad_len = 8;
	}
	
	/* use the gcm library */
	if (R_gcm_enc(
			plain, 
			cipher,
			data_len,
			key,
			atag,
			atag_len,
			iv,
			iv_len,
			aad,
			aad_len) != 0)
	{
		R_gcm_Close();
		return 1;	/* Lib encrypt failure */
	}
	
	R_gcm_Close();
	
	/* OK */
	return 0;
}

/******************************************************************************
* Function Name : R_DLMS_AES_GCM_Decrypt
* Interface     : uint16_t R_DLMS_AES_GCM_Decrypt(
*               :     uint8_t * cipher 
*               :     uint8_t * plain  
*               :     uint32_t data_len
*               :     uint8_t * key    
*               :     uint8_t * atag   
*               :     uint32_t atag_len
*               :     uint8_t * iv     
*               :     uint32_t iv_len  
*               :     uint8_t * aad    
*               :     uint32_t aad_len 
*               : );
* Description   : 
* Arguments     : uint8_t * cipher :
*               : uint8_t * plain  :
*               : uint32_t data_len:
*               : uint8_t * key    :
*               : uint8_t * atag   :
*               : uint32_t atag_len:
*               : uint8_t * iv     :
*               : uint32_t iv_len  :
*               : uint8_t * aad    :
*               : uint32_t aad_len :
* Function Calls: 
* Return Value  : int32_t
******************************************************************************/
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
)
{
	uint8_t aad_local[8];
	
	R_gcm_Init(GCM_AESKEY_LEN_128);
	
	/* To use AES-GCM lib : need aad for all cases of SC */
	if (aad == NULL || aad_len == 0) {
		aad = aad_local;
		aad_len = 8;
	}
	
	/* use the gcm library */
	if (R_gcm_dec(
			cipher,
			plain, 
			data_len,
			key,
			atag,
			atag_len,
			iv,
			iv_len,
			aad,
			aad_len) != 0)
	{
		R_gcm_Close();
		return 1;	/* Lib encrypt failure */
	}
	
	R_gcm_Close();
	
	/* OK */
	return 0;
}
