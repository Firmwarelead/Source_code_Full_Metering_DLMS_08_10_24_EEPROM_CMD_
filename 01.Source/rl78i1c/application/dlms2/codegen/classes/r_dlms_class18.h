/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class18.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS18_H
#define _R_DLMS_CLASS18_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/* image transfer status type */
typedef enum tag_img_transfer_status_t
{
	IMG_TRANS_NOT_INITIATED = 0,			/* Image transfer not initiated  */
	IMG_TRANS_INITIATED,					/* Image transfer initiated      */
	IMG_VERIFY_INITIATED,					/* Image verification initiated  */
	IMG_VERIFY_SUCCESSFUL,					/* Image verification successful */
	IMG_VERIFY_FAILED,						/* Image verification failed     */
	IMG_ACTIVATE_INITIATED,					/* Image activation initiated    */
	IMG_ACTIVATE_SUCCESSFUL,				/* Image activation successful   */
	IMG_ACTIVATE_FAILED,					/* Image activation failed       */
} img_transfer_status_t;

typedef enum tag_class18_attribute_t
{
    CLASS18_ATTRIBUTE_02_BLOCK_SIZE = 2,
    CLASS18_ATTRIBUTE_03_BLOCK_TRANSFER_STATUS,
    CLASS18_ATTRIBUTE_04_FIRST_NOT_TRANSFERRED_BLOCK_NUMBER,
    CLASS18_ATTRIBUTE_05_TRANSFER_ENABLED,
    CLASS18_ATTRIBUTE_06_TRANSFER_STATUS,
    CLASS18_ATTRIBUTE_07_IMAGES_TO_ACTIVATE_INFO,
} class18_attribute_t;

typedef enum tag_class18_method_t
{
    CLASS18_METHOD_01_IMAGE_TRANSFER_INITIATE = 1,
    CLASS18_METHOD_02_IMAGE_BLOCK_TRANSFER,
    CLASS18_METHOD_03_IMAGE_VERIFY,
    CLASS18_METHOD_04_IMAGE_ACTIVATE,
} class18_method_t;

typedef struct tag_class18_image_to_activate_info_t
{
	uint32_t 		*p_size;
	VariantString 	identification;
	VariantString 	signature;
} class18_image_to_activate_info_t;

typedef OBIS_DECLARE_FIXED_ARRAY(class18_image_to_activate_info_t, class18_image_to_activate_info_array_t);

typedef struct tag_class18_image_transfer_inititate_t
{
    VariantString   image_identifier;
    uint32_t 		*p_size;
} class18_image_transfer_inititate_t;

typedef struct tag_class18_image_block_transfer_t
{
    uint32_t 		*p_block_no;
    VariantString   image_block_value;
} class18_image_block_transfer_t;

typedef union tag_class18_action_data_t
{
    void                                    * p_all;
    class18_image_transfer_inititate_t      * p_m1_image_transfer_initiate;
    class18_image_block_transfer_t          * p_m2_image_block_transfer;
    int8_t                                  * p_m3_image_verify;
    int8_t                                  * p_m4_image_activate;
} class18_action_data_t;

/* child record for 1 object of class 18 */
typedef struct tag_class18_child_record_t
{
	uint8_t										logical_name[6];						/* Logical name (OBIS code) of the object. */
	access_right_t								*p_access_right;						/* Access right definition for 1 object    */
	uint32_t									*p_image_block_size;							/* 2. Image Block Size */
	BitString	                                *p_image_transferred_blocks_status;			/* 3. Image Transferred Blocks Status */
	uint32_t									*p_image_first_not_transferred_block_number;	/* 4. Image First Not Transferred Block Number */
	uint8_t										*p_image_transfer_enabled;				/* 5. Image Transfer Enabled */
	img_transfer_status_t						*p_image_transfer_status;				/* 6. Image Transfer Status */
	class18_image_to_activate_info_array_t		*p_image_to_activate_info;		/* 7. Image To Activate Info */
} class18_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class18_child_record_t g_objects_child_table_class18[];			/* Import from objects : child table defintion for class 18 */
extern const uint16_t				g_objects_child_table_class18_length;		/* Import from objects : length of child table defintion of class 18 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass18(distributor_params_t *p_params);

OBIS_DECLARE_TYPE_ENCODER_FUNC_HEADER(R_DLMS_CLASSES_EncodeClass18ImageToActivateInfoArray, class18_image_to_activate_info_array_t);
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeClass18ImageToActivateInfoArray, class18_image_to_activate_info_array_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass18ImageTransferInitiate, class18_image_transfer_inititate_t);
OBIS_DECLARE_TYPE_DECODER_FUNC_HEADER(R_DLMS_CLASSES_DecodeClass18ImageBlockTransfer, class18_image_block_transfer_t);
class18_image_to_activate_info_array_t *R_DLMS_CLASSES_RedirectClass18ImageToActivateInfoArray(distributor_params_t *p_params, class18_image_to_activate_info_array_t *p_object, uint16_t array_size);
/* Declare macro for redirect function to fill into distributor object class*/
/* Simple data type */
#define R_DLMS_IC18_REDIRECT_02(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC18_REDIRECT_03(p_params, p_attribute, size)				p_attribute = R_DLMS_CLASSES_CreatNew_Bitstring(p_params, size)
#define R_DLMS_IC18_REDIRECT_04(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectDoubleLongUnsigned(p_params, p_attribute)
#define R_DLMS_IC18_REDIRECT_05(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectBoolean(p_params, p_attribute)
#define R_DLMS_IC18_REDIRECT_06(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, p_attribute)
#define R_DLMS_IC18_REDIRECT_07(p_params, p_attribute, size_array)			p_attribute = R_DLMS_CLASSES_RedirectClass18ImageToActivateInfoArray(p_params, p_attribute, size_array)

void R_DLMS_CLASSES_Class18Init(void);
void R_DLMS_CLASSES_Class18PollingProcessing(void);
void R_DLMS_CLASSES_Class18AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class18AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass18(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS18_H */

