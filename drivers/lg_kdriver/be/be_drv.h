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
 *  drv header file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.02.07
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_DRV_H_
#define _BE_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */
	
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void		BE_PreInit(void);
extern int		BE_Init(void);
extern void		BE_Cleanup(void);

int				BE_TOP_Ioctl(unsigned int cmd, unsigned long arg);

int BE_Reset_SW(void);
int BE_Set_UartForMcu(unsigned long arg);
int BE_Set_DebugPrint(unsigned long arg);
int BE_TOP_Set_Bypass(unsigned long arg);
int BE_TOP_Get_Bypass(unsigned long arg);
int BE_TOP_Get_Status(unsigned long arg);
int BE_TOP_Toggle_3D_LR(unsigned long arg);
int BE_TOP_Set_3D_In_Format(unsigned long arg);
int BE_TOP_Get_3D_In_Format(unsigned long arg);
int BE_TOP_Set_3D_Out_Format(unsigned long arg);
int BE_TOP_Set_3D_Sync_Delay(unsigned long arg);
int BE_TOP_Set_3D_Convergence(unsigned long arg);
int BE_TOP_Set_Black_Bar(unsigned long arg);
int BE_TOP_Set_Video_Mute(unsigned long arg);
int BE_TOP_Set_Mute_Color(unsigned long arg);
int BE_TOP_Set_Display_Type(unsigned long arg);
int BE_TOP_Set_Debug_Display(unsigned long arg);
int BE_TOP_Set_VID_Operation(unsigned long arg);
int BE_TOP_Set_Input_Src_Type(unsigned long arg);
int BE_TOP_Set_Active_Window_Start(unsigned long arg);
int BE_TOP_Set_Active_Window_Size(unsigned long arg);
int BE_TOP_Firmware_Debug(unsigned long arg);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _BE_DRV_H_ */

/** @} */


