/******************************************************************************
  Copyright (C) 2016 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_cosem_apdu_security.h
* Version      : 1.00
* Description  : DLMS COSEM APDU Security Suite
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 05.07.2016 
******************************************************************************/

#ifndef _R_DLMS_COSEM_APDU_SECURITY_H
#define _R_DLMS_COSEM_APDU_SECURITY_H

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_library_config.h"
#include "r_dlms_cosem_apdu.h"

/******************************************************************************
Macro definitions
******************************************************************************/

#define SC_KEYSET_UNICAST			(0)
#define SC_KEYSET_BROADCAST			(1)

/* Length in bytes of Suite 0 : AES-GCM-128 */
#define LENGTH_SYSTITLE				(8)
#define LENGTH_FC					(4)
#define LENGTH_IV					(LENGTH_SYSTITLE + LENGTH_FC)
#define LENGTH_KEY					(16)
#define LENGTH_CIPHER_KEY			(LENGTH_KEY)
#define LENGTH_AUTHEN_KEY			(LENGTH_KEY)
#define LENGTH_SC					(1)
#define LENGTH_ATAG					(12)

/******************************************************************************
Typedef definitions
******************************************************************************/

/******************************************************************************
Variable Externs
******************************************************************************/

/******************************************************************************
Functions Prototypes
******************************************************************************/

EXTERN_C uint8_t R_APDU_AesGcmEncrypt(
	SCByte security_control,
	MandatoryString *p_plain_apdu,
	MandatoryString *p_system_title,
	MandatoryString *p_encryption_key,
	MandatoryString *p_authentication_key,
	MandatoryString *p_ciphered_content,
	uint32_t frame_counter,
	MandatoryString *p_temp_buffer
);

EXTERN_C uint8_t R_APDU_AesGcmDecrypt(
	MandatoryString *p_ciphered_content,
	MandatoryString *p_system_title,
	MandatoryString *p_encryption_key,
	MandatoryString *p_authentication_key,
	MandatoryString *p_plain_apdu,
	MandatoryString *p_atag,
	uint32_t		*p_fc,
	MandatoryString *p_temp_buffer
);

EXTERN_C uint8_t R_APDU_RebuildProtectionlayers(ApduDispatchContext *p_dispatch_context);
EXTERN_C SCByte  R_APDU_BuildSecurityControlByte(SecurityContext *p_security_context, uint8_t attribute_access_right, uint8_t method_access_right);
EXTERN_C SecurityOptionElement *R_APDU_PushProtectionLayer(SecurityOptionList *p_security_options);
EXTERN_C SecurityOptionElement *R_APDU_PopProtectionLayer(SecurityOptionList *p_security_options);
EXTERN_C SecurityOptionElement *R_APDU_GetTopProtectionLayer(SecurityOptionList *p_security_options);
EXTERN_C uint8_t R_APDU_IsCipheringOrSigingNeeded(ApduDispatchContext *p_dispatch_context);
EXTERN_C uint16_t R_APDU_CipherOrSign(MandatoryString *p_apdu, MandatoryString *output, ApduDispatchContext *p_dispatch_context);
EXTERN_C uint16_t R_APDU_DecipherOrVerifySignature(MandatoryString *p_apdu, MandatoryString *output, ApduDispatchContext *p_dispatch_context);

#endif /* _R_DLMS_COSEM_APDU_SECURITY_H */

