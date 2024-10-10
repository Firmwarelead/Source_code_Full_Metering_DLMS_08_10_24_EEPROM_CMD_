/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class47.h
* Version      : 1.00
* Description  : Class 47 definition
******************************************************************************
* History : DD.MM.YYYY Version Description
*         : 29.03.2018 
******************************************************************************/

#ifndef _R_DLMS_CLASS47_H
#define _R_DLMS_CLASS47_H
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

typedef enum tag_class47_status_t
{
	CLASS47_STATUS_NOT_REGISTERED 				= 0,
	CLASS47_STATUS_REGISTERED_HOME_NETWORK 		= 1,
	CLASS47_STATUS_NOT_REGISTERED_SEARCHING 	= 2,
	CLASS47_STATUS_REGISTRATION_DENIED 			= 3,
	CLASS47_STATUS_UNKNOWN 						= 4,
	CLASS47_STATUS_REGISTERED_ROAMING			= 5,
	// Other: (6) -> (255) reserved
} class47_status_t;

typedef enum tag_class47_cs_attachment_t
{
	CLASS47_CS_ATTACHMENT_INACTIVE		= 0,
	CLASS47_CS_ATTACHMENT_INCOMING_CALL	= 1,
	CLASS47_CS_ATTACHMENT_ACTIVE			= 2,
	// Other: (3) -> (255) reserved
} class47_cs_attachment_t;


typedef enum tag_class47_ps_status_t
{
	CLASS47_PS_STATUS_INACTIVE		= 0,
	CLASS47_PS_STATUS_GPRS			= 1,
	CLASS47_PS_STATUS_EDGE			= 2,
	CLASS47_PS_STATUS_UMTS			= 3,
	CLASS47_PS_STATUS_HSDPA			= 4,
	CLASS47_PS_STATUS_LTE			= 5,
	CLASS47_PS_STATUS_CDMA			= 6,
	// Other: (7) -> (255) reserved
} class47_ps_status_t;

typedef struct tag_class47_cell_info_type_t
{
#if CLASS_47_VERSION == 0
	uint16_t		cell_ID;
#elif CLASS_47_VERSION == 1
	uint32_t		cell_ID;
#endif
	uint16_t 		location_ID;
	uint8_t			signal_quality;
	uint8_t			ber;
#if CLASS_47_VERSION == 1
	uint16_t		mcc;
	uint16_t		mnc;
	uint32_t		channel_number;
#endif
} class47_cell_info_type_t;

typedef struct tag_class47_adjacent_cell_info_t
{
#if CLASS_47_VERSION == 0
	uint16_t		cell_ID;
#elif CLASS_47_VERSION == 1
	uint32_t		cell_ID;
#endif
	uint8_t 		signal_quality;
} class47_adjacent_cell_info_t;

typedef OBIS_DECLARE_VARIANT_ARRAY(class47_adjacent_cell_info_t, class47_adjacent_cells_t);

/* child record for 1 object of class 47 */
typedef struct tag_class47_child_record_t
{
	uint8_t								logical_name[6];		/* Logical name (OBIS code) of the object. */
	access_right_t						*p_access_right;		/* Access right definition for 1 object    */					
	VisibleString						*p_operator;			/* Holds the name of the network operator e.g. "YourNetOp" */
	class47_status_t					*p_status;				/* Indicates the registration status of the modem. */
	class47_cs_attachment_t				*p_cs_attachment;		/* Indicates the current circuit switched status. */
	class47_ps_status_t					*p_ps_status;			/* The ps_status value field indicates the packet switched status of the modem. */
	class47_cell_info_type_t			*p_cell_info;			/* Represents the cell information */
	class47_adjacent_cells_t			*p_adjacent_cells;		/* Adjacent cell info */
	date_time_t							*p_capture_time;		/* Holds the date and time when the data have been last captured. */
} class47_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/
extern const class47_child_record_t g_objects_child_table_class47[];			/* Import from objects : child table defintion for class 47 */
extern const uint16_t				g_objects_child_table_class47_length;		/* Import from objects : length of child table defintion of class 47 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

void R_DLMS_CLASSES_DistributeAbstractClass47(distributor_params_t *p_params);

void R_DLMS_CLASSES_Class47Init(void);
void R_DLMS_CLASSES_Class47PollingProcessing(void);
void R_DLMS_CLASSES_Class47AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class47AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass47(distributor_params_t *p_params);

/* Redirect function */
VariantString *R_DLMS_CLASSES_RedirectClass47_Operator(distributor_params_t *p_params, VariantString *p_object, uint16_t size);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectClass47_CellInfo, class47_cell_info_type_t);
class47_adjacent_cells_t *R_DLMS_CLASSES_RedirectClass47_AdjacentCells(distributor_params_t *p_params, class47_adjacent_cells_t *p_object, uint16_t array_size);

/* Macro for simple attribute */
#define R_DLMS_IC47_REDIRECT_03(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, &p_attribute)
#define R_DLMS_IC47_REDIRECT_04(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, &p_attribute)
#define R_DLMS_IC47_REDIRECT_05(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectEnum(p_params, &p_attribute)
#define R_DLMS_IC47_REDIRECT_08(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectDateTime(p_params, &p_attribute)
/* Macro for complex attribute */
#define R_DLMS_IC47_REDIRECT_02(p_params, p_attribute,max_size)				p_attribute = R_DLMS_CLASSES_RedirectClass47_Operator(p_params, p_attribute, max_size)
#define R_DLMS_IC47_REDIRECT_06(p_params, p_attribute)						p_attribute = R_DLMS_CLASSES_RedirectClass47_CellInfo(p_params, p_attribute)
#define R_DLMS_IC47_REDIRECT_07(p_params, p_attribute,max_length)			p_attribute = R_DLMS_CLASSES_RedirectClass47_AdjacentCells(p_params, p_attribute, max_length)

#endif /* _R_DLMS_CLASS47_H */

