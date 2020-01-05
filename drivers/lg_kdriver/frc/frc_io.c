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



/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>

#include <mach/platform.h>

#include "os_util.h"
#include "frc_ipc_def.h"
#include "frc_kapi.h"

extern int DE_IPC_SetData(UINT32 cmd, void *pMsg, UINT32 msgCnt);
extern int DE_KIPC_SetData(UINT32 cmd, void *pMsg, UINT32 msgCnt);
extern int DE_IPC_GetData(void *pMsg, UINT32 msgCnt);

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

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
int FRC_IO_Init(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_INIT_T *pstParams = (LX_FRC_INIT_T*)arg;
	UINT32 msgCnt = sizeof(LX_FRC_INIT_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_INIT;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IO_ResetSW(void)
{
#ifdef INCLUDE_KDRV_DE
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_RESET_SW;

	return DE_IPC_SetData(ipcCmd, NULL, 0);
#else
	return RET_OK;
#endif
}

int FRC_IOR_IsStable(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	int ret;
	LX_FRC_STABLE_T	*pstParams = (LX_FRC_STABLE_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_STABLE_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_IS_STABLE;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
//		if (ret) break;
		ret = DE_IPC_GetData(pstParams, msgCnt);
	} while (0);

	return ret;
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetMEMC(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN*)arg;
	UINT32 msgCnt = sizeof(BOOLEAN);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_MEMC;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetMEMCType(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_MC_TYPE_T *pstParams = (LX_FRC_MC_TYPE_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_MC_TYPE_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_MEMC_TYPE;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetTrueMotionDemo(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN*)arg;
	UINT32 msgCnt = sizeof(BOOLEAN);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_TRUEMOTION_DEMO;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetTrueMotionDemoBar(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_DEMO_BAR_CTRL_T *pstParams = (LX_FRC_DEMO_BAR_CTRL_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_DEMO_BAR_CTRL_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_TRUEMOTION_DEMO_BAR;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetScanDirection(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN*)arg;
	UINT32 msgCnt = sizeof(BOOLEAN);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_SCAN_DIRECTION;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetFreeze(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN*)arg;
	UINT32 msgCnt = sizeof(BOOLEAN);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_FREEZE;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetOSDControl(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_OSD_CTRL_T *pstParams = (LX_FRC_OSD_CTRL_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_OSD_CTRL_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_OSD_CONTROL;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetSpreadSpectrum(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_SPREAD_SPECTRUM_T *pstParams = (LX_FRC_SPREAD_SPECTRUM_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_SPREAD_SPECTRUM_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_SPREAD_SPECTRUM;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetPWMDutyCycle(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_PWM_PARAM_T *pstParams = (LX_FRC_PWM_PARAM_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_PWM_PARAM_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_PWM_DUTY_CYCLE;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetPWMControl(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_PWM_CTRL_T *pstParams = (LX_FRC_PWM_CTRL_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_PWM_CTRL_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_PWM_CONTROL;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetLowDelayMode(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_LOW_DELAY_T *pstParams = (LX_FRC_LOW_DELAY_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_LOW_DELAY_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_LOW_DELAY_MODE;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetDisplayOutput(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN*)arg;
	UINT32 msgCnt = sizeof(BOOLEAN);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_DISPLAY_OUTPUT;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetFHDMode(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_FHD_MODE_T *pstParams = (LX_FRC_FHD_MODE_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_FHD_MODE_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_FHD_MODE;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetRgbYuvMode(unsigned long arg, bool is_user_call)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_RGBYUV_MODE_T *pstParams = (LX_FRC_RGBYUV_MODE_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_RGBYUV_MODE_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_RGBYUV_MODE;

	if(is_user_call)
	{ return DE_IPC_SetData(ipcCmd, pstParams, msgCnt); }
	else
	{ return DE_KIPC_SetData(ipcCmd, pstParams, msgCnt); }
#else
	return RET_OK;
#endif
}

int FRC_IOR_GetFirmwareVersion(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	int ret;
	LX_FRC_FIRMWARE_INFO_T *pstParams = (LX_FRC_FIRMWARE_INFO_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_FIRMWARE_INFO_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_GET_FIRMWARE_VERSION;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
//		if (ret) break;
		ret = DE_IPC_GetData(pstParams, msgCnt);
	} while (0);

	return ret;
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetJudderLevel(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	UINT8 *pstParams = (UINT8 *)arg;
	UINT32 msgCnt = sizeof(UINT8);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_JUDDER_LEVEL;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetBlurLevel(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	UINT8 *pstParams = (UINT8 *)arg;
	UINT32 msgCnt = sizeof(UINT8);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_BLUR_LEVEL;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOR_RegRd(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	int ret;
	UINT32 *pstParams = (UINT32 *)arg;
	UINT32 msgCnt = sizeof(UINT32);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_REG_RD;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
//		if (ret) break;
		ret = DE_IPC_GetData(pstParams, msgCnt);
	} while (0);

	return ret;
#else
	return RET_OK;
#endif
}

int FRC_IOW_RegWr(unsigned long arg)
{
#ifdef INCLUDE_KDRV_DE
	LX_FRC_REG_WRITE_T *pstParams = (LX_FRC_REG_WRITE_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_REG_WRITE_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_REG_WR;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
#else
	return RET_OK;
#endif
}

int FRC_IOW_SetDisplayMute(unsigned long arg)
{
	LX_FRC_MUTE_CTRL_T *pstParams = (LX_FRC_MUTE_CTRL_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_MUTE_CTRL_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_DISPLAY_MUTE;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
}

#if 0
int FRC_IOW_Set3DMode(unsigned long arg)
{
	LX_FRC_3D_MODE_T *pstParams = (LX_FRC_3D_MODE_T *)arg;
	UINT32 msgCnt = sizeof(LX_FRC_3D_MODE_T);
	FRC_IPC_CMD_T ipcCmd = FRC_IPC_SET_3D_MODE;

	return DE_IPC_SetData(ipcCmd, pstParams, msgCnt);
}
#endif

/**  @} */
