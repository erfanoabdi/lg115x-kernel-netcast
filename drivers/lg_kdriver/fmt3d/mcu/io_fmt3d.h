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

#ifndef  IO_FMT3D_INC
#define  IO_FMT3D_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_LINUX_KERNEL
#define OK     RET_OK
#define NOT_OK RET_ERROR
#define DTV_STATUS_T int
#endif

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
DTV_STATUS_T MCU_FMT3D_IO_Init(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetProcessMode(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_GetProcessMode(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetInImgInfo(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_GetInImgInfo(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_GetOutImgInfo(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetRunmode(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_ToggleLrInOrder(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_ToggleLrOutOrder(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetInImgFmt(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetDisFmt(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetInFrRate(char *strBuff) DE_CODEDDR; // L8 does not have input_fr field
DTV_STATUS_T MCU_FMT3D_IO_SetOutFrRate(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetConvergence(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetImgDoublePic(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetSampleMode(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetSrcMux(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetImgScanType(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetFrcOutType(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetFrcOutOrder(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_T3_IO_SetConvergence(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_T3_IO_SetDepthCtrl(char *strBuff) DE_CODEDDR;
DTV_STATUS_T MCU_FMT3D_IO_SetFprFhd(char *strBuff) DE_CODEDDR;
#ifdef USE_XTENSA
LX_3D_OUT_TYPE_T FMT3D_GetFrcOutType(void);
#ifdef USE_XTENSA_FRC
DTV_STATUS_T FMT3D_SetFrcOutType(LX_3D_OUT_TYPE_T outType) DE_CODEDDR;
DTV_STATUS_T FMT3D_SetFrcOutOrder(LX_3D_LR_ORDER_T lrOrder) DE_CODEDDR;
DTV_STATUS_T FMT3D_SetFrcOutput(void) DE_CODEDDR;
#endif
#endif

#endif   /* ----- #ifndef IO_FMT3D_INC  ----- */

