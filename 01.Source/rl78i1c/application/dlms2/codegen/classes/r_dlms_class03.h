/******************************************************************************
  Copyright (C) 2018 Renesas Electronics Corporation, All Rights Reserved.
*******************************************************************************
* File Name    : r_dlms_class03.h
* Version OCG  : 1.0.7 - Dec 30 2022 - 523f50b0cadaf461e67e821551f18ee49d82598e
* Device(s)    : RL78I1C
* Tool-Chain   : CCRL 1.05
* H/W Platform : None
* Description  : Config for OBIS layer and DLMS Library DLMS_LIB_V23
******************************************************************************
* History			: DD.MM.YYYY Version Description
* Generated date    : 03/01/2023
******************************************************************************/

#ifndef _R_DLMS_CLASS03_H
#define _R_DLMS_CLASS03_H
#include "r_dlms_config.h"

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "typedef.h"
#include "r_dlms_classes.h"
#include "r_dlms_class01.h"
/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Physical unit */
typedef enum tag_physical_unit_t
{
	PHY_UNIT_YEAR                          = 1  , /* Year                                         */
	PHY_UNIT_MONTH                         = 2  , /* Month                                        */
	PHY_UNIT_WEEK                          = 3  , /* Week. 7*24*60*60 s                           */
	PHY_UNIT_DAY                           = 4  , /* Day. 24*60*60 s                              */
	PHY_UNIT_HOUR                          = 5  , /* Hour. 60*60 s                                */
	PHY_UNIT_MIN                           = 6  , /* Minute. 60 s                                 */
	PHY_UNIT_SECOND                        = 7  , /* Second                                       */
	PHY_UNIT_DEGREE                        = 8  , /* Phase angle in degree                        */
	PHY_UNIT_DEGREE_CELSIUS                = 9  , /* Temperature (T) in C = K - 273.15            */
	PHY_UNIT_CURRENCY                      = 10 , /* (local) Currency                             */
	PHY_UNIT_METRE                         = 11 , /* Metre (m)                                    */
	PHY_UNIT_METRE_PER_SEC                 = 12 , /* Metre per second (m/s)                       */
	PHY_UNIT_CUBIC_METRE_V                 = 13 , /* Cubic metre (m^3) for volume (V).            */
	PHY_UNIT_CUBIC_METRE_C                 = 14 , /* Cubic metre (m^3). Corrected volume          */
	PHY_UNIT_CUBIC_METRE_PER_HOUR_V        = 15 , /* Cubic metre (m^3) per hour.                  */
	PHY_UNIT_CUBIC_METRE_PER_HOUR_C        = 16 , /* Corrected cubic metre (m^3) per hour.        */
	PHY_UNIT_CUBIC_METRE_PER_DAY_V         = 17 , /* Cubic metre (m^3) per day.                   */
	PHY_UNIT_CUBIC_METRE_PER_DAY_C         = 18 , /* Corrected cubic metre (m^3) per day.         */
	PHY_UNIT_LITRE                         = 19 , /* Litre (l). 10^-3 m^3                         */
	PHY_UNIT_KILOGRAM                      = 20 , /* Kilogram (kg).                               */
	PHY_UNIT_NEWTON                        = 21 , /* Newton (N). Unit of force (F)                */
	PHY_UNIT_NEWTON_METER                  = 22 , /* Newtonmeter (Nm). J = Nm = Ws                */
	PHY_UNIT_PASCAL                        = 23 , /* Pascal (Pa). N/m^2                           */
	PHY_UNIT_BAR                           = 24 , /* Bar. 10^5 (N/m^2)                            */
	PHY_UNIT_JOULE                         = 25 , /* Joule. J = Nm = Ws                           */
	PHY_UNIT_JOULE_PER_HOUR                = 26 , /* Joule per hour. J/(60*60s)                   */
	PHY_UNIT_WATT                          = 27 , /* Watt (W). W = J/s                            */
	PHY_UNIT_VOLT_AMPERE                   = 28 , /* Volt-Ampere (VA).                            */
	PHY_UNIT_VAR                           = 29 , /* Var (of reactive power)                      */
	PHY_UNIT_WATT_HOUR                     = 30 , /* Watt-hour (Wh). W*(60*60s)                   */
	PHY_UNIT_VOLT_AMPERE_HOUR              = 31 , /* Volt-ampere-hour (VAh). VA*(60*60s)          */
	PHY_UNIT_VAR_HOUR                      = 32 , /* VAr-hour (VArh). VAr*(60*60s)                */
	PHY_UNIT_AMPERE                        = 33 , /* Ampere (A)                                   */
	PHY_UNIT_COULOMB                       = 34 , /* Coulomb. C = As                              */
	PHY_UNIT_VOLT                          = 35 , /* Volt (V)                                     */
	PHY_UNIT_VOLT_PER_METRE                = 36 , /* Volt per metre (V/m).                        */
	PHY_UNIT_FARAD                         = 37 , /* Farad (F). C/V = As/V                        */
	PHY_UNIT_OHM                           = 38 , /* Ohm. O = V/A                                 */
	PHY_UNIT_OHM_METRE                     = 39 , /* Ohm metre (Om)                               */
	PHY_UNIT_WEBER                         = 40 , /* Weber. Wb = Vs                               */
	PHY_UNIT_TESLA                         = 41 , /* Tesla (T). Wb/m^2                            */
	PHY_UNIT_AMPERE_PER_METRE              = 42 , /* Ampere per metre. A/m                        */
	PHY_UNIT_HENRY                         = 43 , /* Henry. H = Wb/A                              */
	PHY_UNIT_HERTZ                         = 44 , /* Hertz (Hz).                                  */
	PHY_UNIT_PULSE_PER_WATT_HOUR           = 45 , /* 1Pulse/Wh                                    */
	PHY_UNIT_PULSE_PER_VAR_HOUR            = 46 , /* 1Pulse/VArh                                  */
	PHY_UNIT_PULSE_PER_VA_HOUR             = 47 , /* 1Pulse/VAh                                   */
	PHY_UNIT_VOLT_SQUARED_HOURS            = 48 , /* Volt-squared-hours. V^2(60*60s)              */
	PHY_UNIT_AMPERE_SQUARED_HOURS          = 49 , /* Ampere-squared-hours. A^2(60*60s)            */
	PHY_UNIT_KILOGRAM_PER_SECOND           = 50 , /* Kilogram per second. Kg/s                    */
	PHY_UNIT_SIEMENS                       = 51 , /* Siemens (S). 1/O                             */
	PHY_UNIT_KELVIN                        = 52 , /* Kelvin (K)                                   */
	PHY_UNIT_PULSE_PER_VOLT_SQUARED_HOUR   = 53 , /* 1/(V^2h)                                     */
	PHY_UNIT_PULSE_PER_AMPERE_SQUARED_HOUR = 54 , /* 1/(A^2h)                                     */
	PHY_UNIT_PULSE_PER_VOLUME              = 55 , /* 1/m^3                                        */
	PHY_UNIT_PERCENTAGE                    = 56 , /* %                                            */
	PHY_UNIT_AMPERE_HOUR                   = 57 , /* Ah                                           */
	PHY_UNIT_WATT_HOUR_PER_VOLUME          = 60 , /* Wh/m^3. 3,6*103 J/m3                         */
	PHY_UNIT_JOULE_PER_VOLUME              = 61 , /* J/m^3                                        */
	PHY_UNIT_MOLE_PERCENT                  = 62 , /* Mole percent                                 */
	PHY_UNIT_G_PER_VOLUME                  = 63 , /* g/m^3                                        */
	PHY_UNIT_PASCAL_SECOND                 = 64 , /* Pa s                                         */
	PHY_UNIT_JOULE_PER_KILOGRAM            = 65 , /* J/kg                                         */
	PHY_UNIT_DECIBELS_METRE                = 70 , /* dBm                                          */
	PHY_UNIT_RESERVED                      = 253, /* Reserved                                     */
	PHY_UNIT_OTHER_UNIT                    = 254, /* Other unit                                   */
	PHY_UNIT_NONE                          = 255, /* No unit                                      */
} physical_unit_t;

/* Scaler Unit */
typedef struct tag_scaler_unit_t
{
	int8_t			scaler;			/* This is the exponent (to the base of 10) of the multiplication factor. */
	physical_unit_t	unit;			/* Enumeration defining the physical unit. See 4.5.3.6 for more detail.   */
} scaler_unit_t;
/* action data of class03 */
typedef union tag_class03_action_data_t
{
	void		*p_all;
	int8_t		*p_m1_reset;
} class03_action_data_t;

/* child record for 1 register object definition */
typedef struct tag_class03_child_record_t
{
	uint8_t			logical_name[6];	/* Logical name (OBIS code) of the object. */
	access_right_t	*p_access_right;	/* Access right definition for 1 object    */
	choice_t		value;				/* Value                                   */
	scaler_unit_t	*p_scaler_unit;		/* Scaler, unit                            */
} class03_child_record_t;

/******************************************************************************
Variable Externs
******************************************************************************/

extern const class03_child_record_t g_objects_child_table_class03[];			/* Import from objects : child table defintion for class 03 */
extern const uint16_t				g_objects_child_table_class03_length;		/* Import from objects : length of child table defintion of class 03 */

/******************************************************************************
Functions Prototypes
******************************************************************************/

uint16_t R_DLMS_CLASSES_EncodeScalerUnit(
	MandatoryString	out_data,
	scaler_unit_t   *p_scaler_unit
);

uint16_t R_DLMS_CLASSES_DecodeScalerUnit(
	scaler_unit_t   *p_scaler_unit,
	MandatoryString	in_data
);
/* Declare scaler unit */
OBIS_DECLARE_TYPE_DISTRIBUTOR_FUNC_HEADER(R_DLMS_CLASSES_DistributeScalerUnit, scaler_unit_t);
OBIS_DECLARE_REDIRECT_FUNC_HEADER(R_DLMS_CLASSES_RedirectScalerUnit, scaler_unit_t);
void R_DLMS_CLASSES_DistributeAbstractClass03(distributor_params_t *p_params);
void R_DLMS_CLASSES_Redirect_Att03(distributor_params_t * p_params, scaler_unit_t * p_attributte);

/* Declare redirect function */
/* Macro for simple attribute */
#define R_DLMS_IC03_REDIRECT_02(p_params, p_attribute)			R_DLMS_CLASSES_Redirect_ChoiceAttribute(p_params, &p_attribute)
/* Macro for complex attribute */
#define R_DLMS_IC03_REDIRECT_03(p_params, p_attribute)			p_attribute = R_DLMS_CLASSES_RedirectScalerUnit(p_params, p_attribute)

void R_DLMS_CLASSES_Class03Init(void);
void R_DLMS_CLASSES_Class03PollingProcessing(void);
void R_DLMS_CLASSES_Class03AsscOpened(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_Class03AsscClosing(AsscConnectionSession *p_assc_session);
void R_DLMS_CLASSES_DistributeClass03(distributor_params_t *p_params);

#endif /* _R_DLMS_CLASS03_H */

