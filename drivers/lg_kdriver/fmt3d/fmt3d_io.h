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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.03.15
 * note       Additional information.
 *
 * @addtogroup lg1150_fmt3d
 * @{
 */

#ifndef  FMT3D_IO_INC
#define  FMT3D_IO_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

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
int FMT3D_IO_Init(unsigned long arg);
int FMT3D_IO_SetProcessMode(unsigned long arg);
int FMT3D_IO_GetProcessMode(unsigned long arg);
int FMT3D_IO_SetInImgInfo(unsigned long arg);
int FMT3D_IO_GetInImgInfo(unsigned long arg);
int FMT3D_IO_GetOutImgInfo(unsigned long arg);
int FMT3D_IO_SetRunmode(unsigned long arg);
int FMT3D_IO_ToggleLrInOrder(unsigned long arg);
int FMT3D_IO_ToggleLrOutOrder(unsigned long arg);
int FMT3D_IO_SetInImgFmt(unsigned long arg);
int FMT3D_IO_SetDisFmt(unsigned long arg);
int FMT3D_IO_SetInFrRate(unsigned long arg);
int FMT3D_IO_SetOutFrRate(unsigned long arg);
int FMT3D_IO_SetConvergence(signed long arg);
int FMT3D_IO_SetImgDoublePic(unsigned long arg);
int FMT3D_IO_SetSampleMode(unsigned long arg);
int FMT3D_IO_SetSrcMux(unsigned long arg);
int FMT3D_IO_SetImgScanType(unsigned long arg);
int FMT3D_IO_SetFrcOutType(unsigned long arg);
int FMT3D_IO_SetFrcOutLrOrder(unsigned long arg);
int FMT3D_T3_IO_SetConvergence(unsigned long arg);
int FMT3D_T3_IO_SetDepthCtrl(unsigned long arg);
int FMT3D_IO_SetFprFhd(unsigned long arg);
int FMT3D_IO_SetInOutCtrl(unsigned long arg);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef FMT3D_IO_INC  ----- */
/**  @} */
