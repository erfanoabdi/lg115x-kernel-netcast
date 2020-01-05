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


#ifndef _FRC_IO_h
#define _FRC_IO_h
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
int FRC_IO_Init(unsigned long arg);
int FRC_IO_ResetSW(void);
int FRC_IOR_IsStable(unsigned long arg);
int FRC_IOW_SetMEMC(unsigned long arg, bool is_user_call);
int FRC_IOW_SetMEMCType(unsigned long arg, bool is_user_call);
int FRC_IOW_SetTrueMotionDemo(unsigned long arg);
int FRC_IOW_SetTrueMotionDemoBar(unsigned long arg);
int FRC_IOW_SetScanDirection(unsigned long arg, bool is_user_call);
int FRC_IOW_SetFreeze(unsigned long arg, bool is_user_call);
int FRC_IOW_SetOSDControl(unsigned long arg);
int FRC_IOW_SetSpreadSpectrum(unsigned long arg);
int FRC_IOW_SetPWMDutyCycle(unsigned long arg, bool is_user_call);
int FRC_IOW_SetPWMControl(unsigned long arg, bool is_user_call);
int FRC_IOW_SetLowDelayMode(unsigned long arg);
int FRC_IOW_SetDisplayOutput(unsigned long arg);
int FRC_IOW_SetFHDMode(unsigned long arg, bool is_user_call);
int FRC_IOW_SetRgbYuvMode(unsigned long arg, bool is_user_call);
int FRC_IOR_GetFirmwareVersion(unsigned long arg);
int FRC_IOW_SetJudderLevel(unsigned long arg);
int FRC_IOW_SetBlurLevel(unsigned long arg);
int FRC_IOR_RegRd(unsigned long arg);
int FRC_IOW_RegWr(unsigned long arg);
int FRC_IOW_SetDisplayMute(unsigned long arg);
//int FRC_IOW_Set3DMode(unsigned long arg);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif
/**  @} */
