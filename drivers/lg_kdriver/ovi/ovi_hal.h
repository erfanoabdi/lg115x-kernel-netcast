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
 *  OVI module
 *
 *  author      dj911.kim@lge.com
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg115x_ovi
 *  @{
 */

#ifndef _OVI_HW_H_
#define _OVI_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "ovi_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int OVI_HAL_Init(void);

int OVI_HAL_SetLvds(LX_OVI_LVDS_T *pstParams);
int OVI_HAL_SetVx1(LX_OVI_VX1_T *pstParams);
int OVI_HAL_SetEpi(LX_OVI_EPI_T *pstParams);
int OVI_HAL_SetDarkScreen(BOOLEAN bParam);
int OVI_HAL_SetReverse(BOOLEAN bParam);
int OVI_HAL_GetTconBaseAddr(UINT32 *pstParams);
int OVI_HAL_GetInfo(LX_OVI_INFO_T *pstParams);
int OVI_HAL_GetConfigVer(LX_OVI_CONFIG_VER_T *pstParams);
int OVI_HAL_SetCombination(UINT32 eParam);
int OVI_HAL_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T stParam);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _OVI_HW_H_ */

/** @} */

