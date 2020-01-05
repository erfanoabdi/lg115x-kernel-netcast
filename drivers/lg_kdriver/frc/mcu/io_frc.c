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

#ifdef USE_XTENSA_FRC
#define USE_FRC_TEST_MCU_IN_CPU
#elif defined(USE_VIDEO_IOCTL_CALLING)
#ifdef USE_QEMU_SYSTEM
#define USE_FRC_TEST_MCU_IN_CPU
#endif
#endif

#ifdef USE_FRC_TEST_MCU_IN_CPU

#ifdef USE_XTENSA
#include <string.h>
#include <stdlib.h>
#include <BSP/UART/stdio.h>

#include <Common/DDI_DTV.h>
#include <Common/MEM_DTV.h>

#include <XDE/CFG_VIDEO.h>
#include <XDE/IPC_VIDEO.h>
#include <XDE/REG_DLR.h>
#include <XDE/MEM_VIDEO.h>
#include <XDE/MCU_VIDEO.h>
//#include <XDE/de_kapi.h>
//#include <XDE/IO_VIDEO.h>
#include <FRC/frc_ipc_def.h>
#include <FRC/frc_kapi.h>
#include <FRC/FRC_DDI.h>
#else
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "os_util.h"
//#include "de_drv.h"

#include "base_types.h"

//#include "de_def.h"
//#include "de_ipc.h"
//#include "de_reg.h"
//#include "mcu/mcu_test.h"
#include "frc_ipc_def.h"
#include "frc_kapi.h"
#include "../../de/de_model.h"
#include "../../de/de_ipc_def.h"
#include "../../de/mcu/io_video.h"

#endif

extern char gaSendBuffOfIPC[VIDEO_MSG_STR_MAX];
extern int VIDEO_MCU_PutData(char *msgBuff, UINT32 msgCnt);

DTV_STATUS_T MCU_FRC_IO_Init(char *strBuff)
{
	DTV_STATUS_T ret;

	printk("MCU_FRC_IO_Init\n");
	ret = OK;
#ifdef USE_XTENSA

	FRC_InitSW();
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IO_ResetSW(char *strBuff)
{
	DTV_STATUS_T ret;

	printk("MCU_FRC_IO_ResetSW\n");
	ret = OK;
#ifdef USE_XTENSA

	FRC_ResetSW();
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOR_IsStable(char *strBuff)
{
	DTV_STATUS_T ret;
	LX_FRC_STABLE_T	is_stable;

	printk("MCU_FRC_IOR_IsStable\n");
	ret = OK;
#ifdef USE_XTENSA
	is_stable = FRC_IsStable();

	memcpy(gaSendBuffOfIPC, &is_stable, sizeof(LX_FRC_STABLE_T));
	ret = VIDEO_MCU_PutData(gaSendBuffOfIPC, sizeof(LX_FRC_STABLE_T));
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetMEMC(char *strBuff)
{
	DTV_STATUS_T	ret;
	BOOLEAN			bEnable;

	memcpy(&bEnable, strBuff, sizeof(BOOLEAN));
	printk("MCU_FRC_IOW_SetMEMC : %d\n", bEnable);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetMeMc(bEnable);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetMEMCType(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_MC_TYPE_T mc_type;

	memcpy(&mc_type, strBuff, sizeof(LX_FRC_MC_TYPE_T));
	printk("MCU_FRC_IOW_SetMEMCType : blurLevel=%d\n", mc_type.blurLevel);
	printk("MCU_FRC_IOW_SetMEMCType : judderLevel=%d\n", mc_type.judderLevel);
	printk("MCU_FRC_IOW_SetMEMCType : eFrcMCLevel=%d\n", mc_type.eFrcMCLevel);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetMeMcType(mc_type);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetTrueMotionDemo(char *strBuff)
{
	DTV_STATUS_T	ret;
	BOOLEAN			bEnable;

	memcpy(&bEnable, strBuff, sizeof(BOOLEAN));
	printk("MCU_FRC_IOW_SetTrueMotionDemo : %d\n", bEnable);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetTrueMotionDemo(bEnable);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetTrueMotionDemoBar(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_DEMO_BAR_CTRL_T	demo_bar_ctrl;

	memcpy(&demo_bar_ctrl, strBuff, sizeof(LX_FRC_DEMO_BAR_CTRL_T));
	printk("MCU_FRC_IOW_SetTrueMotionDemoBar : bEnable=%d\n", demo_bar_ctrl.bEnable);
	printk("MCU_FRC_IOW_SetTrueMotionDemoBar : rBar=%d\n", demo_bar_ctrl.rBar);
	printk("MCU_FRC_IOW_SetTrueMotionDemoBar : gBar=%d\n", demo_bar_ctrl.gBar);
	printk("MCU_FRC_IOW_SetTrueMotionDemoBar : bBar=%d\n", demo_bar_ctrl.bBar);
	printk("MCU_FRC_IOW_SetTrueMotionDemoBar : thick=%d\n", demo_bar_ctrl.thick);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetTrueMotionDemoBar(demo_bar_ctrl);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetScanDirection(char *strBuff)
{
	DTV_STATUS_T	ret;
	BOOLEAN			bDirection;

	memcpy(&bDirection, strBuff, sizeof(BOOLEAN));
	printk("MCU_FRC_IOW_SetScanDirection : %d\n", bDirection);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetScanDirection(bDirection);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetFreeze(char *strBuff)
{
	DTV_STATUS_T	ret;
	BOOLEAN			bEnable;

	memcpy(&bEnable, strBuff, sizeof(BOOLEAN));
	printk("MCU_FRC_IOW_SetFreeze : %d\n", bEnable);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetFreeze(bEnable);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetOSDControl(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_OSD_CTRL_T osd_ctrl;

	memcpy(&osd_ctrl, strBuff, sizeof(LX_FRC_OSD_CTRL_T));
	printk("MCU_FRC_IOW_SetOSDControl : bOnOff=%d\n", osd_ctrl.bOnOff);
	printk("MCU_FRC_IOW_SetOSDControl : eOSDRegion=%d\n", osd_ctrl.eOSDRegion);
	printk("MCU_FRC_IOW_SetOSDControl : tOSDRect.u16Hsize=%d\n", osd_ctrl.tOSDRect.u16Hsize);
	printk("MCU_FRC_IOW_SetOSDControl : tOSDRect.u16Vsize=%d\n", osd_ctrl.tOSDRect.u16Vsize);
	printk("MCU_FRC_IOW_SetOSDControl : tOSDRect.u16Hstart=%d\n", osd_ctrl.tOSDRect.u16Hstart);
	printk("MCU_FRC_IOW_SetOSDControl : tOSDRect.u16Vstart=%d\n", osd_ctrl.tOSDRect.u16Vstart);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetOSDControl(osd_ctrl);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetSpreadSpectrum(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_SPREAD_SPECTRUM_T spread_spectrum;

	memcpy(&spread_spectrum, strBuff, sizeof(LX_FRC_SPREAD_SPECTRUM_T));
	printk("MCU_FRC_IOW_SetSpreadSpectrum : u16Period=%d\n", spread_spectrum.u16Period);
	printk("MCU_FRC_IOW_SetSpreadSpectrum : u16Percent=%d\n", spread_spectrum.u16Percent);
	printk("MCU_FRC_IOW_SetSpreadSpectrum : bEnable=%d\n", spread_spectrum.bEnable);
	printk("MCU_FRC_IOW_SetSpreadSpectrum : bMiuLVDS=%d\n", spread_spectrum.bMiuLVDS);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetSpreadSpectrum(spread_spectrum);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetPWMDutyCycle(char *strBuff)
{
	DTV_STATUS_T		ret;
	LX_FRC_PWM_PARAM_T	pwm_param;

	memcpy(&pwm_param, strBuff, sizeof(LX_FRC_PWM_PARAM_T));
	printk("MCU_FRC_IOW_SetPWMDutyCycle : ePWMindex=%d\n", pwm_param.ePWMIndex);
	printk("MCU_FRC_IOW_SetPWMDutyCycle : u16Duty=%d\n", pwm_param.u16Duty);
	printk("MCU_FRC_IOW_SetPWMDutyCycle : u16StartPosition=%d\n", pwm_param.u16StartPosition);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetPwmDutyCycle(pwm_param);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetPWMControl(char *strBuff)
{
	DTV_STATUS_T		ret;
	LX_FRC_PWM_CTRL_T	pwm_ctrl;

	memcpy(&pwm_ctrl, strBuff, sizeof(LX_FRC_PWM_CTRL_T));
	printk("MCU_FRC_IOW_SetPWMControl : ePWMindex=%d\n", pwm_ctrl.ePWMIndex);
	printk("MCU_FRC_IOW_SetPWMControl : ePWMOutput=%d\n", pwm_ctrl.ePWMOutput);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetPwmDutyControl(pwm_ctrl);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetLowDelayMode(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_LOW_DELAY_T low_delay;

	memcpy(&low_delay, strBuff, sizeof(LX_FRC_LOW_DELAY_T));
	printk("MCU_FRC_IOW_SetLowDelayMode : %d\n", low_delay);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetLowDelayMode(low_delay);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetDisplayOutput(char *strBuff)
{
	DTV_STATUS_T	ret;
	BOOLEAN			bEnable;

	memcpy(&bEnable, strBuff, sizeof(BOOLEAN));
	printk("MCU_FRC_IOW_SetDisplayOutput : %d\n", bEnable);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetDisplayOutput(bEnable);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetFHDMode(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_FHD_MODE_T fhd_mode;

	memcpy(&fhd_mode, strBuff, sizeof(LX_FRC_FHD_MODE_T));
	printk("MCU_FRC_IOW_SetFHDMode : %d\n", fhd_mode);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetFhdMode(fhd_mode);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetRgbYuvMode(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_RGBYUV_MODE_T rgbyuv_mode;

	memcpy(&rgbyuv_mode, strBuff, sizeof(LX_FRC_FHD_MODE_T));
	printk("MCU_FRC_IOW_SetRgbYuvMode : %d\n", rgbyuv_mode);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetRgbYuvMode(rgbyuv_mode);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetJudderLevel(char *strBuff)
{
	DTV_STATUS_T	ret;
	UINT8			judder_level;

	memcpy(&judder_level, strBuff, sizeof(UINT8));
	printk("MCU_FRC_IOW_SetJudderLevel : %d\n", judder_level);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetJudderLevel(judder_level);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_SetBlurLevel(char *strBuff)
{
	DTV_STATUS_T	ret;
	UINT8			blur_level;

	memcpy(&blur_level, strBuff, sizeof(UINT8));
	printk("MCU_FRC_IOW_SetBlurLevel : %d\n", blur_level);
	ret = OK;
#ifdef USE_XTENSA

	FRC_SetBlurLevel(blur_level);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOR_RegRd(char *strBuff)
{
	DTV_STATUS_T ret;
	UINT32 rd_addr;
	UINT32 rd_data;

	memcpy(&rd_addr, strBuff, sizeof(UINT32));
	printk("MCU_FRC_IOW_RegRd : rd_addr=%d\n", rd_addr);
	ret = OK;
#ifdef USE_XTENSA
	rd_data = FRC_RegRead(rd_addr);

	memcpy(gaSendBuffOfIPC, &rd_data, sizeof(UINT32));
	ret = VIDEO_MCU_PutData(gaSendBuffOfIPC, sizeof(UINT32));
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_RegWr(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_REG_WRITE_T	write_struct;

	memcpy(&write_struct, strBuff, sizeof(LX_FRC_REG_WRITE_T));
	printk("MCU_FRC_IOW_RegWr : wr_addr=%d\n", write_struct.wr_addr);
	printk("MCU_FRC_IOW_RegWr : wr_data=%d\n", write_struct.wr_data);
	ret = OK;
#ifdef USE_XTENSA

	FRC_RegWrite(write_struct);
#endif

	return ret;
}

#if 0
DTV_STATUS_T MCU_FRC_IOW_SetDisplayMute(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_MUTE_CTRL_T	mute_ctrl;

	memcpy(&mute_ctrl, strBuff, sizeof(LX_FRC_MUTE_CTRL_T));
	printk("MCU_FRC_IOW_SetDisplayMute : bEnable=%d\n", mute_ctrl.bEnable);
	printk("MCU_FRC_IOW_SetDisplayMute : eFrcMute=%d\n", mute_ctrl.eFrcMute);
	ret = OK;
#ifdef USE_XTENSA

//	ret = MCU_SetPanelType(stParams);
#endif

	return ret;
}

DTV_STATUS_T MCU_FRC_IOW_Set3DMode(char *strBuff)
{
	DTV_STATUS_T	ret;
	LX_FRC_3D_MODE_T	mode_3d;

	memcpy(&mode_3d, strBuff, sizeof(LX_FRC_3D_MODE_T));
	printk("MCU_FRC_IOW_Set3DMode : %d\n", mode_3d);
	ret = OK;
#ifdef USE_XTENSA

//	ret = MCU_SetPanelType(stParams);
#endif

	return ret;
}
#endif

DTV_STATUS_T MCU_FRC_IPC_IOCTL(char *cliBuff, UINT32 strLen)
{
	DTV_STATUS_T	ret = NOT_OK;
	UINT32			ipcCmd;
	int				cmdSize = sizeof(ipcCmd);
	char			*strBuff = cliBuff;

	do {
		if (!strBuff)
		{
			printk("cliBuff is Null\n");
			break;
		}
		memcpy(&ipcCmd, strBuff, cmdSize);
		strBuff += cmdSize;
		switch (ipcCmd)
		{
			case FRC_IPC_INIT :
				ret = MCU_FRC_IO_Init(strBuff);
				break;
			case FRC_IPC_RESET_SW:
				ret = MCU_FRC_IO_ResetSW(strBuff);
				break;
			case FRC_IPC_IS_STABLE:
				ret = MCU_FRC_IOR_IsStable(strBuff);
				break;
			case FRC_IPC_SET_MEMC:
				ret = MCU_FRC_IOW_SetMEMC(strBuff);
				break;
			case FRC_IPC_SET_MEMC_TYPE:
				ret = MCU_FRC_IOW_SetMEMCType(strBuff);
				break;
			case FRC_IPC_SET_TRUEMOTION_DEMO:
				ret = MCU_FRC_IOW_SetTrueMotionDemo(strBuff);
				break;
			case FRC_IPC_SET_TRUEMOTION_DEMO_BAR:
				ret = MCU_FRC_IOW_SetTrueMotionDemoBar(strBuff);
				break;
			case FRC_IPC_SET_SCAN_DIRECTION:
				ret = MCU_FRC_IOW_SetScanDirection(strBuff);
				break;
			case FRC_IPC_SET_FREEZE:
				ret = MCU_FRC_IOW_SetFreeze(strBuff);
				break;
			case FRC_IPC_SET_OSD_CONTROL:
				ret = MCU_FRC_IOW_SetOSDControl(strBuff);
				break;
			case FRC_IPC_SET_SPREAD_SPECTRUM:
				ret = MCU_FRC_IOW_SetSpreadSpectrum(strBuff);
				break;
			case FRC_IPC_SET_PWM_DUTY_CYCLE:
				ret = MCU_FRC_IOW_SetPWMDutyCycle(strBuff);
				break;
			case FRC_IPC_SET_PWM_CONTROL:
				ret = MCU_FRC_IOW_SetPWMControl(strBuff);
				break;
			case FRC_IPC_SET_LOW_DELAY_MODE:
				ret = MCU_FRC_IOW_SetLowDelayMode(strBuff);
				break;
			case FRC_IPC_SET_DISPLAY_OUTPUT:
				ret = MCU_FRC_IOW_SetDisplayOutput(strBuff);
				break;
			case FRC_IPC_SET_FHD_MODE:
				ret = MCU_FRC_IOW_SetFHDMode(strBuff);
				break;
			case FRC_IPC_SET_RGBYUV_MODE:
				ret = MCU_FRC_IOW_SetRgbYuvMode(strBuff);
				break;
			case FRC_IPC_SET_JUDDER_LEVEL:
				ret = MCU_FRC_IOW_SetJudderLevel(strBuff);
				break;
			case FRC_IPC_SET_BLUR_LEVEL:
				ret = MCU_FRC_IOW_SetBlurLevel(strBuff);
				break;
			case FRC_IPC_REG_RD:
				ret = MCU_FRC_IOR_RegRd(strBuff);
				break;
			case FRC_IPC_REG_WR:
				ret = MCU_FRC_IOW_RegWr(strBuff);
				break;
#if 0
			case FRC_IPC_SET_DISPLAY_MUTE:
				ret = MCU_FRC_IOW_SetDisplayMute(strBuff);
				break;
			case FRC_IPC_SET_3D_MODE:
				ret = MCU_FRC_IOW_Set3DMode(strBuff);
				break;
#endif
			default :
				printk("Wrong ipcCmd(%d)\n", ipcCmd);
				break;
		}
		if (ret) break;
	} while (0);


	return ret;
}

#endif
