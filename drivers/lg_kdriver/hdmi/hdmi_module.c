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

/*! \file HDMI_module.c
 * \brief HDMI module control Drivers linux module
 */


/**
 *	Necessary includes for device drivers
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/workqueue.h>		/**< For working queue */
#include <linux/interrupt.h>


#include "os_util.h"

#include "hdmi_drv.h"
#include "hdmi_kapi.h"
#include "hdmi_module.h"
#ifdef INCLUDE_L9_CHIP_KDRV
#include "l9/hdmi_hw_l9.h"
#endif

#ifdef INCLUDE_H13_CHIP_KDRV
#include "h13/hdmi_hw_h13.h"
#endif
//#include "hdmi_phy_reg.h"


/******************************************************************************
 *				DEFINES
 *****************************************************************************/

/**
 *	Global variables of the driver
 */
/******************************************************************************
 *				DATA STRUCTURES
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */

/* for HDMI Switch */
HDMI_DATA_T gCfgBootData[] =
{
	 // for LG1151(L9) A0/1 & B0
	 {
	 	1,			// hdmi_switch
		0,			// SWport
		{ 1},	// LX_HDMI_HPD_T

		0,			// mode
		0,			// port
		0,			// Pixel Repetition
		{4,	4},		// connectCn[2]
		{21, 8},	// timingCn[2]
		{20, 4},	// hdmiCn[2]
	    	{3,	2}		// dviCn[2]
	  }
};

HDMI_DATA_T *gBootData = &gCfgBootData[0];	// for Real.

/******************************************************************************
 *				Local function
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */




/**
* ADC Module exit
*
* @parm void
* @return int
*/
int HDMI_exit(void)
{
	int ret = 0;

	// power down


//	iounmap(pstHdmiPhyReg);
	HDMI_DisableInterrupt();
	
	return ret;
}


/**
* HDMI Module initialize
*
* @parm void
* @return int
*/
int HDMI_Initialize(LX_HDMI_INIT_T *param)
{
	int ret = RET_OK;

	//HDMI_ERROR("HDMI initializ = %d \n", param->bHdmiSW);

#if 0
	/* access to register */
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))			pHdmiRegCfg = &gRegCfgHdmi[1];	// 1 : L9 Ax & Bx for Real
	else if (lx_chip_rev() >= LX_CHIP_REV(L8, A0))		pHdmiRegCfg = &gRegCfgHdmi[0];	// 0 : L8 A1 & B0 for Real.
	else return -1;	// Unkown chip revision

	HDMI_PRINT("HDMI REG CFG \n");
	HDMI_PRINT("HDMI REG CFG vport base 0x%08x\n", pHdmiRegCfg->vport_reg_base_addr);
	HDMI_PRINT("HDMI REG CFG vport size 0x%08x\n", pHdmiRegCfg->vport_reg_size);
	HDMI_PRINT("HDMI REG CFG vport Qumu 0x%08x\n", pHdmiRegCfg->vport_qemu_base_addr);

	HDMI_ERROR("HDMI REG CFG PHy base 0x%08x\n", pHdmiRegCfg->phy_reg_base_addr);
	HDMI_ERROR("HDMI REG CFG Phy size 0x%08x\n", pHdmiRegCfg->phy_reg_size);
	HDMI_ERROR("HDMI REG CFG Phy Qumu 0x%08x\n", pHdmiRegCfg->phy_qemu_base_addr);
#endif

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		HDMI_H13_HWInitial();
	} else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
	{
		gBootData = &gCfgBootData[0];	// 1 : L9 Ax & Bx for Real
		// for HDMI Switch H/W
		gBootData->hdmi_switch = param->bHdmiSW;

		// initialize
		HDMI_L9_HWInitial();

		// power down
		HDMI_L9_SetPowerControl(0);

		if(gBootData->hdmi_switch)
		{
			HDMI_L9_SetPowerControl(1);
			HDMI_L9_SetHPD(&gBootData->hpd);
		}
	} else
#endif
		ret = RET_ERROR;	// Unkown chip revision

	return ret;
}

int HDMI_SetPort(UINT32 *port)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_SetPort(port);
	 else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_SetPort(port);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}


int HDMI_GetMode(LX_HDMI_MODE_T *mode)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetMode(mode);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetMode(mode);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}
int HDMI_GetAspectRatio(LX_HDMI_ASPECTRATIO_T *ratio)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetAspectRatio(ratio);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetAspectRatio(ratio);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}
int HDMI_GetColorDomain(LX_HDMI_COLOR_DOMAIN_T *color)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetColorDomain(color);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;

}
int HDMI_GetTimingInfo(LX_HDMI_TIMING_INFO_T *info)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetTimingInfo(info);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetTimingInfo(info);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetAviPacket_L9(LX_HDMI_AVI_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetAviPacket(packet);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetVsiPacket_L9(LX_HDMI_VSI_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetVsiPacket(packet);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetSpdPacket_L9(LX_HDMI_SPD_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetSpdPacket(packet);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}


int HDMI_GetAviPacket(LX_HDMI_INFO_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetAviPacket(packet);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() > LX_CHIP_REV(L9, B0))
		ret = RET_NOT_SUPPORTED;
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetVsiPacket(LX_HDMI_INFO_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetVsiPacket(packet);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetSpdPacket(LX_HDMI_INFO_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetSpdPacket(packet);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetInfoPacket(LX_HDMI_INFO_PACKET_T *packet)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetInfoPacket(packet);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = RET_NOT_SUPPORTED;
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetStatus(LX_HDMI_STATUS_T *status)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetStatus(status);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetStatus(status);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}
int HDMI_SetHPD(LX_HDMI_HPD_T *hpd)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_SetHPD(hpd);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_SetHPD(hpd);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_PowerConsumption(UINT32 power)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_SetPowerControl(power);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_PowerConsumption(power);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_SetUDn3DControl(LX_HDMI_UD_3D_MODE_T *udn3d)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		HDMI_DEBUG("[%d] %s : Not support H13_HDMI => Support H13_DE \n", __LINE__, __func__);
		ret = RET_NOT_SUPPORTED;
	}
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_SetUDn3DControl(udn3d);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

//audio related
int HDMI_GetAudioInfo(LX_HDMI_AUDIO_INFO_T *pAudioInfo)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetAudioInfo(pAudioInfo);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetAudioInfo(pAudioInfo);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetAudioCopyInfo(LX_HDMI_AUDIO_COPY_T *pCopyInfo)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetAudioCopyInfo(pCopyInfo);
	else
#endif

	ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_SetArc(LX_HDMI_ARC_CTRL_T *pArcCtrl)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_SetArc(pArcCtrl);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_SetArc(pArcCtrl);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_SetMute(LX_HDMI_MUTE_CTRL_T *pMuteCtrl)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_SetMute(pMuteCtrl);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_SetMute(pMuteCtrl);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_GetAudioDebugInfo(LX_HDMI_DEBUG_AUDIO_INFO_T *pAudioDebugInfo)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetAudioDebugInfo(pAudioDebugInfo);
	else
#endif

	ret = RET_ERROR;		// Unkown chip revision

	return ret;
}


int HDMI_DisableInterrupt(void)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_DisableInterrupt();
	else
#endif

	ret = RET_ERROR;		// Unkown chip revision

	return ret;
}


int HDMI_GetRegister(UINT32 addr , UINT32 *value)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_GetRegister(addr , value);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_GetRegister(addr , value);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

int HDMI_SetRegister(UINT32 addr , UINT32 value)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_SetRegister(addr, value);
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_SetRegister(addr, value);
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}

#ifdef	KDRV_CONFIG_PM
int HDMI_RunSuspend(void)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_RunSuspend( );
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_RunSuspend( );
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}
int HDMI_RunResume(void)
{
	int ret = RET_OK;

#ifdef INCLUDE_H13_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		ret = HDMI_H13_RunResume( );
	else
#endif

#ifdef INCLUDE_L9_CHIP_KDRV
	if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
		ret = HDMI_L9_RunResume( );
	else
#endif
		ret = RET_ERROR;		// Unkown chip revision

	return ret;
}
#endif
