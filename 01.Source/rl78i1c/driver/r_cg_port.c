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
* Copyright (C) 2015, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_port.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Port module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    /*  SMART METER BOARD PINS MAPPING---Changed by XQ on Jan-19-2017. Updated by VN on Nov-08-2017
     *  VCC-1:          EEPROM power supply
     *  VCC-2:          IR TX Led power supply
     *  VCC-3:          IR RX Opto-transistor power supply
     *  VDD_CTRL:       control FET for to supply power to peripheral [LED0, LED1, FLASH, MAG_SENSOR]
     *  POWER_SWITCH:   control FET for VBAT supply to VCC before sleep. 0 is enable VBAT supply
     
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *              7               6               5               4               3               2               1               0
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P0  MCU     TXD0            RXD0            SCK00           PORT_IO         PORT_O          PORT_O             
     *      NAME    FEA_SOUT        FEA_SIN         FEA_SCLK        FEA_INOUT       FEA_RFRESETB    FEA_LED1
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P1  MCU     SEG11           SEG10           SEG9            SEG8            SEG7            SEG6            SEG5            SEG4
     *      NAME    FEA_LCD_SEG11   FEA_LCD_SEG10   FEA_LCD_SEG9    FEA_LCD_SEG8    FEA_LCD_SEG7    FEA_LCD_SEG6    FEA_LCD_SEG5    FEA_LCD_SEG4
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P2  MCU                                     NA         	    PORT_I          PORT_I          INTVDDEXLVD     NA              NA
     *      NAME                                    NA              RLY_SENSE_1     RLY_SENSE_0     MAIN_FAIL       NA              NA
     *--------------------------------------------------------------------------------------------------------------------------------------------      
     *  P3  MCU     COM0            COM1            COM2            COM3            PORT_PW         PORT_O          PORT_O          PORT_PW
     *      NAME    FEA_LCD_COM0    FEA_LCD_COM1    FEA_LCD_COM2    FEA_LCD_COM3    VCC-2           VDD_CTRL        POWER_SWITCH    VCC_1   
     *--------------------------------------------------------------------------------------------------------------------------------------------      
     *  P4  MCU                                                                     NA              PORT_O                          E1
     *      NAME                                                                    NA              FEA_LED0                        TOOL0*
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P5  MCU     SCK30           TXD2            RXD2            NA              PORT_PW         NA              NA              PORT_O
     *      NAME    FEA_SPI_CLK     FEA_IR_TXD      FEA_IR_RXD      NA              VCC-3           NA    	        NA              FEA_SPI_CE
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P6  MCU                                                                                     PORT_O          SDAA0           SCLA0
     *      NAME                                                                                    FEA_IIC0_WP     FEA_IIC0_SDA    FEA_IIC0_SCL
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P7  MCU     SEG23           SEG22           SEG21           SEG20           SEG19           SEG18           SEG17           SEG16
     *      NAME    FEA_LCD_SEG23   FEA_LCD_SEG22   FEA_LCD_SEG21   FEA_LCD_SEG20   FEA_LCD_SEG19   FEA_LCD_SEG18   FEA_LCD_SEG17   FEA_LCD_SEG16
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P8  MCU                                     SO30            SI30            SEG15           SEG14           SEG13           SEG12
     *      NAME                                    FEA_SPI_SO      FEA_SPI_SI      FEA_LCD_SEG15   FEA_LCD_SEG14   FEA_LCD_SEG13   FEA_LCD_SEG12   
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P9  MCU     SEG24           SEG25           SEG26            SEG27          PORT_O          PORT_O          PORT_O          PORT_O
     *      NAME    FEA_LCD_SEG3    FEA_LCD_SEG2    FEA_LCD_SEG1     FEA_LCD_SEG0   FEA_RELAY_11    FEA_RELAY_10    FEA_RELAY_01    FEA_RELAY_00   
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P12 MCU     CAPH            CAPL            PORT_I           XT2             XT1             NA              NA
     *      NAME    CAPH            CAPL            FEA_HALL_SENS    XT2             XT1             NA              NA
     *--------------------------------------------------------------------------------------------------------------------------------------------      
     *  P13 MCU     NA
     *      NAME    NA
     *--------------------------------------------------------------------------------------------------------------------------------------------
     *  P15 MCU                                                                                     RTCIC2          RTCIC1          RTCOUT
     *      NAME                                                                                    FEA_SW1         FEA_CASE        NA 
     *--------------------------------------------------------------------------------------------------------------------------------------------
    */
    PFSEG0 = _08_PFCOM3_COM | _04_PFCOM2_COM | _02_PFCOM1_COM | _01_PFCOM0_COM;
    PFSEG1 = _80_PFSEG07_SEG | _40_PFSEG06_SEG | _20_PFSEG05_SEG | _10_PFSEG04_SEG | 
             _00_PFSEG03_PORT | _00_PFSEG02_PORT | _00_PFSEG01_PORT | _00_PFSEG00_PORT;
    PFSEG2 = _80_PFSEG15_SEG | _40_PFSEG14_SEG | _20_PFSEG13_SEG | _10_PFSEG12_SEG | 
             _08_PFSEG11_SEG | _04_PFSEG10_SEG | _02_PFSEG09_SEG | _01_PFSEG08_SEG;
    PFSEG3 = _00_PFSEG23_PORT | _00_PFSEG22_PORT | _20_PFSEG21_SEG | _10_PFSEG20_SEG |
             _08_PFSEG19_SEG | _04_PFSEG18_SEG | _02_PFSEG17_SEG | _01_PFSEG16_SEG;
    PFSEG4 = _00_PFSEG31_PORT | _00_PFSEG30_PORT | _00_PFSEG29_PORT | _00_PFSEG28_PORT |
             _00_PFSEG27_PORT | _00_PFSEG26_PORT | _00_PFSEG25_PORT | _00_PFSEG24_PORT;
    PFSEG5 = _00_PFSEG39_PORT | _00_PFSEG38_PORT | _00_PFSEG37_PORT | _00_PFSEG37_PORT |
             _00_PFSEG36_PORT | _00_PFSEG34_PORT | _00_PFSEG33_PORT | _00_PFSEG32_PORT;
    PFSEG6 = _00_PFSEG41_PORT | _00_PFSEG40_PORT;
    
	ISCLCD = _02_VL3_BUFFER_VALID;
   
    P0 = _80_Pn7_OUTPUT_1 | _00_Pn5_OUTPUT_0 | _00_Pn4_OUTPUT_0 | _00_Pn3_OUTPUT_0 | _04_Pn2_OUTPUT_1;
     
    P3 = _08_Pn3_OUTPUT_1 | _04_Pn2_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _01_Pn0_OUTPUT_1;//P3.0:VCC_1 ; P3.3:VCC_2   
    
    P4 = _04_Pn2_OUTPUT_1;
    
    P5 =  _80_Pn7_OUTPUT_1 | _40_Pn6_OUTPUT_1 | _08_Pn3_OUTPUT_1| _10_Pn4_OUTPUT_1 | _02_Pn1_OUTPUT_1; //*P5.3: VCC-5 for LED 0; P5.4 LED1 
    
    P6 = _01_POMn0_NCH_ON | _02_POMn1_NCH_ON | _04_POMn2_NCH_ON;
    P7 = _80_PMn7_MODE_INPUT;  //p77 added by vikram for magnet.
	
    P8 = _20_Pn5_OUTPUT_1;
    P9 = _00_Pn3_OUTPUT_0| _00_Pn2_OUTPUT_0| _00_Pn1_OUTPUT_0|_00_Pn0_OUTPUT_0;

     P4 = _08_Pn3_OUTPUT_1;    // P43   added by peeyush
    
    P15 = _04_Pn2_OUTPUT_1 | _02_Pn1_OUTPUT_1 | _00_Pn0_OUTPUT_0;
    
    POM0 = _00_POMn5_NCH_OFF | _00_POMn4_NCH_OFF | _00_POMn3_NCH_OFF | _00_POMn2_NCH_OFF;
	
    PMC2 = _20_PMCn5_NOT_USE|_00_PMCn4_DI_ON|_00_PMCn3_DI_ON|_04_PMCn2_NOT_USE|_02_PMCn1_NOT_USE|_01_PMCn0_NOT_USE;
	
    PM0 = _03_PM0_DEFAULT_VALUE | _00_PMn7_MODE_OUTPUT | _40_PMn6_MODE_INPUT | _20_PMn5_MODE_INPUT | 
          _00_PMn4_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT;
		  
    PM1 = _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
          _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
		  
    PM3 = _00_PMn4_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | 
          _00_PMn0_MODE_OUTPUT |_00_PMn5_MODE_OUTPUT|_00_PMn7_MODE_OUTPUT|_00_PMn6_MODE_OUTPUT;
		  
  //  PM4 = _01_PMn0_MODE_INPUT|_08_PMn3_MODE_INPUT | _00_PMn2_MODE_OUTPUT  ;  
PM4 = _01_PMn0_MODE_INPUT|_00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT  ;
 	
    PM5 = _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _20_PMn5_MODE_INPUT |
          _00_PMn3_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
    
    PM6 = _F8_PM6_DEFAULT_VALUE | _00_PMn2_MODE_OUTPUT| _00_PMn1_MODE_OUTPUT| _00_PMn0_MODE_OUTPUT;
	
    PM7 = _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
          _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
		  
    PM8 = _00_PMn5_MODE_OUTPUT | _10_PMn4_MODE_INPUT | _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT |
		  _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
		  
    PM9 = _00_PMn7_MODE_OUTPUT | _00_PMn6_MODE_OUTPUT | _00_PMn5_MODE_OUTPUT | _00_PMn4_MODE_OUTPUT |
          _00_PMn3_MODE_OUTPUT | _00_PMn2_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _00_PMn0_MODE_OUTPUT;
		  
    PM15 = _04_PMn2_MODE_INPUT | _02_PMn1_MODE_INPUT | _00_PMn0_MODE_OUTPUT;
	
    PM12 = _20_PMn5_MODE_INPUT;
	
	
}

/* Start user code for adding. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_PORT_StopCreate
* Description  : This function turn off unnesccesary port pin before stopping to conserve power
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_StopCreate(void)
{
    /*  Turn off un necessarcy port before sleeping 
    *   Only keep below items:
    *       1. EEPROM
    *       2. LCD
    *       3. SW1, CASE
    */

    P0 = 0x00;
    P1 = 0x00;
    P2 = 0x10;
    P3 = 0x04;
    P4 = 0x01;
    P5 = 0x00;
    P6 = 0x00;
    P7 = 0x00;
    P8 = 0x00;
    P13 = 0x00;
}
/* End user code. Do not edit comment generated here */
