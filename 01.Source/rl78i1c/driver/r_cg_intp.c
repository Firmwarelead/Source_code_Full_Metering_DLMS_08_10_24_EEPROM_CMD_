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
* File Name    : r_cg_intp.c
* Version      : Code Generator for RL78/I1C V1.01.00.02 [15 May 2017]
* Device(s)    : R5F10NPJ
* Tool-Chain   : CCRL
* Description  : This file implements device driver for INTP module.
* Creation Date: 3/22/2019
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intp.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_INTC_Create
* Description  : This function initializes INTP module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC_Create(void)
{
    PMK0 = 1U;      /* disable INTP0 interrupt */
    PIF0 = 0U;      /* clear INTP0 interrupt flag */
    PMK1 = 1U;      /* disable INTP1 interrupt */
    PIF1 = 0U;      /* clear INTP1 interrupt flag */
    PMK2 = 1U;      /* disable INTP2 interrupt */
    PIF2 = 0U;      /* clear INTP2 interrupt flag */
    PMK3 = 1U;      /* disable INTP3 interrupt */
    PIF3 = 0U;      /* clear INTP3 interrupt flag */
    PMK4 = 1U;      /* disable INTP4 interrupt */
    PIF4 = 0U;      /* clear INTP4 interrupt flag */
    PMK5 = 1U;      /* disable INTP5 interrupt */
    PIF5 = 0U;      /* clear INTP5 interrupt flag */
    PMK6 = 1U;      /* disable INTP6 interrupt */
    PIF6 = 0U;      /* clear INTP6 interrupt flag */
    PMK7 = 1U;      /* disable INTP7 interrupt */
    PIF7 = 0U;      /* clear INTP7 interrupt flag */
    PMK8 = 1U;      /* disable INTP8 interrupt */
    PIF8 = 0U;      /* clear INTP8 interrupt flag */
    PMK9 = 1U;      /* disable INTP9 interrupt */
    PIF9 = 0U;      /* clear INTP9 interrupt flag */
    PMK12 = 1U;     /* disable INTP12 interrupt */
    PIF12 = 0U;     /* clear INTP12 interrupt flag */
    PMK13 = 1U;     /* disable INTP13 interrupt */
    PIF13 = 0U;     /* clear INTP13 interrupt flag */
    PMK14 = 1U;     /* disable INTP14 interrupt */
    PIF14 = 0U;     /* clear INTP14 interrupt flag */
    RTCIMK0 = 1U;   /* disable INTRTCIC0 interrupt */
    RTCIIF0 = 0U;   /* clear INTRTCIC0 interrupt flag */
    RTCIMK1 = 1U;   /* disable INTRTCIC1 interrupt */
    RTCIIF1 = 0U;   /* clear INTRTCIC1 interrupt flag */
    RTCIMK2 = 1U;   /* disable INTRTCIC2 interrupt */
    RTCIIF2 = 0U;   /* clear INTRTCIC2 interrupt flag */
     /* Set INTP0 low priority - key*/
    PPR10 = 1U;
    PPR00 = 1U;
     /* Set INTP0 low priority - TCP232 Flag */
    PPR13 = 1U;
    PPR03 = 1U;
    /* Set INTP1 low priority - HALL SENSOR */
    PPR11 = 1U;
    PPR01 = 1U;
    /* Set INTP6 low priority */
    PPR16 = 1U;
    PPR06 = 1U;
    /* Set INTRTCIC1 low priority - CASE OPEN*/
    RTCIPR11 = 1U;
    RTCIPR01 = 1U;
    /* Set INTRTCIC2 low priority */
    RTCIPR12 = 1U;
    RTCIPR02 = 1U;
    EGN0 = _02_INTP1_EDGE_FALLING_BOTH | _08_INTP3_EDGE_FALLING_BOTH;
    EGP0 = _02_INTP1_EDGE_RISING_BOTH |_08_INTP3_EDGE_RISING_BOTH ;
    EGN1 = _00_INTP13_INTRTCIC1_EDGE_RISING_DISABLE | _10_INTP14_INTRTCIC2_EDGE_FALLING_BOTH;
   // EGP0 = _00_INTP0_EDGE_FALLING_DISABLE | _00_INTP1_EDGE_FALLING_DISABLE | _40_INTP6_EDGE_RISING_BOTH;
    EGP1 = _20_INTP13_INTRTCIC1_EDGE_RISING_BOTH | _00_INTP14_INTRTCIC2_EDGE_FALLING_DISABLE;
    /* Set INTP0 pin */
    ISCLCD |= 0x02U;
    /* Set INTP3 pin */
    PM0 |= 0x20U;
    /* Set RTCIC1 pin */
    PM15 |= 0x02U;
    /* Set RTCIC2 pin */
    PM15 |= 0x04U;
}

/***********************************************************************************************************************
* Function Name: R_INTC1_Start: HALL --> SW1
* Description  : This function clears INTP0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC1_Start(void)
{
    PIF1 = 0U;      /* clear INTP1 interrupt flag */
    PMK1 = 0U;      /* enable INTP1 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTC1_Stop
* Description  : This function disables INTP0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC1_Stop(void)
{
    PMK1 = 1U;      /* disable INTP1 interrupt */
    PIF1 = 0U;      /* clear INTP1 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_INTC3_Start
* Description  : This function clears INTP3 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC3_Start(void)
{
    PIF3 = 0U;      /* clear INTP3 interrupt flag */
    PMK3 = 0U;      /* enable INTP3 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTC3_Stop
* Description  : This function disables INTP3 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTC3_Stop(void)
{
    PMK3 = 1U;      /* disable INTP3 interrupt */
    PIF3 = 0U;      /* clear INTP3 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_INTRTCIC0_Start
* Description  : This function clears INTRTCIC0 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTRTCIC0_Start(void)
{
    RTCIIF0 = 0U;   /* clear INTRTCIC0 interrupt flag */
    RTCIMK0 = 0U;   /* enable INTRTCIC0 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTRTCIC0_Stop
* Description  : This function disables INTRTCIC0 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTRTCIC0_Stop(void)
{
    RTCIMK0 = 1U;   /* disable INTRTCIC0 interrupt */
    RTCIIF0 = 0U;   /* clear INTRTCIC0 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_INTRTCIC1_Start
* Description  : This function clears INTRTCIC1 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTRTCIC1_Start(void)
{
    RTCIIF1 = 0U;   /* clear INTRTCIC1 interrupt flag */
    RTCIMK1 = 0U;   /* enable INTRTCIC1 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTRTCIC1_Stop
* Description  : This function disables INTRTCIC1 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTRTCIC1_Stop(void)
{
    RTCIMK1 = 1U;   /* disable INTRTCIC1 interrupt */
    RTCIIF1 = 0U;   /* clear INTRTCIC1 interrupt flag */
}
/***********************************************************************************************************************
* Function Name: R_INTRTCIC2_Start
* Description  : This function clears INTRTCIC2 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTRTCIC2_Start(void)
{
    RTCIIF2 = 0U;   /* clear INTRTCIC2 interrupt flag */
    RTCIMK2 = 0U;   /* enable INTRTCIC2 interrupt */
}
/***********************************************************************************************************************
* Function Name: R_INTRTCIC2_Stop
* Description  : This function disables INTRTCIC2 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_INTRTCIC2_Stop(void)
{
    RTCIMK2 = 1U;   /* disable INTRTCIC2 interrupt */
    RTCIIF2 = 0U;   /* clear INTRTCIC2 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
