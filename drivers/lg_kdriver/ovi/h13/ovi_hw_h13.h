/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2010 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 


/** @file
 *
 *	OVI module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */
 
#ifndef  OVI_HW_H13_INC
#define  OVI_HW_H13_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ovi_kapi.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int OVI_HW_H13_Initialize(void);
int OVI_HW_H13_Close(void);

int OVI_HW_H13_SetLvds(LX_OVI_LVDS_T *pstParams);
int OVI_HW_H13_SetVx1(LX_OVI_VX1_T *pstParams);
int OVI_HW_H13_SetEpi(LX_OVI_EPI_T *pstParams);
int OVI_HW_H13_SetDarkScreen(BOOLEAN bParam);
int OVI_HW_H13_SetReverse(BOOLEAN bParam);
int OVI_HW_H13_GetTconBaseAddr(UINT32 *pstParams);
int OVI_HW_H13_GetInfo(LX_OVI_INFO_T *pstParams);
int OVI_HW_H13_GetConfigVer(LX_OVI_CONFIG_VER_T *pstParams);
int OVI_HW_H13_SetCombination(UINT32 eParam);
int OVI_HW_H13_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T stParam);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_HW_H13_INC  ----- */
/**  @} */

