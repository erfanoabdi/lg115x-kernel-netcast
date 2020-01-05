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

 /*! \file HDMI_control.c
 * \brief HDMI H/W control Drivers linux module
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
#include <linux/delay.h>
#include <asm/div64.h> //do_div

#include "os_util.h"
#include "hdmi_drv.h"
#include "hdmi_kapi.h"
#include "hdmi_module.h"
#include "ctop_regs.h"
#include "hdmi_hw_l9.h"


/******************************************************************************
 *				DEFINES
 *****************************************************************************/
//#define INTERRUNT_VIDEO_DEBUG
//#define VIDEO_DEBUG
//#define SOURCE_MUTE_DEBUG
//#define AVI_MUTE_DEBUG
//#define ENABLE_HDMI_AUDIO_DEBUG


/**
 *	Global variables of the driver
 */
extern HDMI_DATA_T *gBootData;

static UINT8 _gSCDT = 0;
static UINT8 _gPortConCount = 0;
static UINT8 _gDeepColor = HDMI_DEEP_COLOR_8BIT;

static UINT8 _gTimingCnt =0;
static UINT8 _gTimingChanged = 0;

static UINT32 _gIntrSourceMute = HDMI_SOURCE_MUTE_CLEAR_STATE;
static UINT32 _gIntrVSIState = HDMI_VSI_INIT_STATE;
static UINT32 _gIntrAVIState = HDMI_AVI_INIT_STATE;
static UINT32 _gIntrVideoState = HDMI_VIDEO_INIT_STATE;
static UINT32 _gIntrAudioState = HDMI_AUDIO_INIT_STATE;
static UINT32 _gIntrAVICscState = HDMI_AVI_CSC_STABLE_STATE;
//_gHdmiAudioPrintCount is only increased in HDMI_L9Bx_GetAudioInfo function
static UINT32 _gHdmiAudioPrintCount = 0;

static UINT32 _gExtMute = 0;
static UINT32 _gAviNoPacket = 0;
static UINT32 _gAviNoPacketCount = 0;
static UINT32 _gSourceMuteCnt = 0;


static LX_HDMI_TIMING_INFO_T _gPrevTiming = {0,};
static LX_HDMI_AVI_PACKET_T _gPrevAVIPacket = {0, };
static LX_HDMI_VSI_PACKET_T _gPrevVSIPacket = {0, };
static LX_HDMI_SPD_PACKET_T _gPrevSPDPacket = {"\0", "\0", 0};
static LX_HDMI_AVI_COLORSPACE_T	_gPrevPixelEncoding = LX_HDMI_AVI_COLORSPACE_RGB;
static LX_HDMI_AVI_COLORSPACE_T	_gCurPixelEncoding = LX_HDMI_AVI_COLORSPACE_RGB;


//HDMI Audio Variables
DEFINE_SPINLOCK(_gIntrHdmiAudioLock);
DEFINE_SPINLOCK(_gIntrHdmiVideoLock);
DEFINE_SPINLOCK(_gIntrHdmiMuteLock);



static LX_HDMI_AUDIO_INFO_T _gHdmiAudioInfo = {LX_HDMI_AUDIO_DEFAULT, LX_HDMI_SAMPLING_FREQ_NONE};

#ifdef	KDRV_CONFIG_PM
static unsigned int guiPmInterruptStatus;
static unsigned int guiPmHpdStatus;
static LX_HDMI_HPD_T gstPmPortSel;
#endif

static int _HDMI_L9_Set3DFullTimingInfo(LX_HDMI_TIMING_INFO_T *info);
static void	_HDMI_L9_ClearResetLink(BOOLEAN reset);
static int _HDMI_L9_SetInternalMute(LX_HDMI_MUTE_CTRL_T *interMute);
static int _HDMI_L9_SetRGBYCbCr(LX_HDMI_AVI_COLORSPACE_T *space);

//semaphore for HDMI Module
static OS_SEM_T g_HDMI_Sema;

/******************************************************************************
 *				DATA STRUCTURES
 *****************************************************************************/
/**
 *	Structure that declares the usual file
 *	access functions
 */


/******************************************************************************
 *				Local function
 *****************************************************************************/
static void	_HDMI_L9_ClearSWResetAll(void)
{
	VPORT_I2C_Read((UINT32*)&gsoft_reset_1_bx);
	VPORT_I2C_Read((UINT32*)&gsoft_reset_2_bx);
	VPORT_I2C_Read((UINT32*)&gsoft_reset_3_bx);
	VPORT_I2C_Read((UINT32*)&gsoft_reset_5_bx);	// CVBS, CHB, VDAC
	VPORT_I2C_Read((UINT32*)&gsoft_reset_6_bx);	// UD & 3D format
	VPORT_I2C_Read((UINT32*)&gsoft_reset_8_bx);	// HDMI Audio

	gsoft_reset_1_bx.swrst_link_prt0_tmds = 0;
	gsoft_reset_1_bx.swrst_hdcp0 = 0;
	gsoft_reset_1_bx.swrst_f3m = 0;

	gsoft_reset_2_bx.swrst_link_pip0_pix = 0;
	gsoft_reset_2_bx.swrst_aw0	= 0;
	gsoft_reset_2_bx.swrst_vw0	= 0;
    gsoft_reset_2_bx.swrst_link_pip0_tmds = 0;

	gsoft_reset_3_bx.swrst_ar0 = 0;
	gsoft_reset_3_bx.swrst_link_pip0_aud = 0;
    gsoft_reset_3_bx.swrst_vr0 = 0;

	gsoft_reset_5_bx.swrst_afe3ch_cvbs = 0;
	gsoft_reset_5_bx.swrst_cvbs = 0;
	gsoft_reset_5_bx.swrst_f54m = 0;
	gsoft_reset_5_bx.swrst_chb = 0;
	gsoft_reset_5_bx.swrst_vdac = 0;

	gsoft_reset_6_bx.swrst_half_ultra = 0;
	gsoft_reset_6_bx.swrst_ultra = 0;

	gsoft_reset_8_bx.swrst_hdmi_dto0 = 0;
	gsoft_reset_8_bx.swrst_adto = 0;

	VPORT_I2C_Write((UINT32*)&gsoft_reset_1_bx);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_2_bx);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_3_bx);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_5_bx);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_6_bx);
	VPORT_I2C_Write((UINT32*)&gsoft_reset_8_bx);
}

static void	_HDMI_L9_ClearResetLink(BOOLEAN reset)
{
	VPORT_I2C_Read((UINT32*)&gsoft_reset_1_bx);
	gsoft_reset_1_bx.swrst_f3m = reset;			/* Link sys reset */
	VPORT_I2C_Write((UINT32*)&gsoft_reset_1_bx);
}

/**
* HDMI_L9Bx_SetPixelRepetition
* Pixel Repetition for 13.5MHz formats - support Pixel Repetition 2
* @parm void
* @return void
*/
void HDMI_L9_SetPixelRepetition(void)
{
	UINT8 repet = 0;

	/* L9A-L9D LVDS Connection(Over : 25MHz, No Phy Pixel PLL Dividing)
	   L9 B0 에서서는 H/W 적으로 처리함. support x2, x4 */
	VPORT_I2C_Read((UINT32*)&glink_339_bx);
	repet = glink_339_bx.reg_pr_tx_pip0;		// From Source Device

	HDMI_PRINT("Pixel Repetition from source device [%d] \n", glink_339_bx.reg_pr_tx_pip0);

	if(gBootData->pixelRepet == repet)
		return ;

	VPORT_I2C_Read((UINT32*)&glink_2_bx);
	VPORT_I2C_Read((UINT32*)&glink_338_bx);
	VPORT_I2C_Read((UINT32*)&glink_341_bx);

	if(repet > 0)
	{
		glink_338_bx.reg_pr_sel =  1;
		glink_338_bx.reg_pr_rx_pip0 = 0;		// Manual Pixel Repetition
		glink_2_bx.reg_avc_en_pip0 = 0;			// Manual Video Configuration

		if( _gCurPixelEncoding == LX_HDMI_AVI_COLORSPACE_YCBCR422)
		{
			glink_341_bx.reg_align422_rx_pip0 = 1;
			VPORT_I2C_Write((UINT32*)&glink_341_bx);
		}
		else
		{
			if(glink_341_bx.reg_align422_rx_pip0)
			{
				glink_341_bx.reg_align422_rx_pip0 = 0;
				VPORT_I2C_Write((UINT32*)&glink_341_bx);
			}
		}
		HDMI_PRINT(" Rx Pixel[%d] Auto Video Conf [%d]\n",glink_338_bx.reg_pr_rx_pip0, glink_2_bx.reg_avc_en_pip0);
	}
	else
	{
		glink_338_bx.reg_pr_sel =  0;
		glink_2_bx.reg_avc_en_pip0 = 1;		// Auto Video Configuration
		if(glink_341_bx.reg_align422_rx_pip0)
		{
			glink_341_bx.reg_align422_rx_pip0 = 0;
			VPORT_I2C_Write((UINT32*)&glink_341_bx);
		}
	}
	VPORT_I2C_Write((UINT32*)&glink_2_bx);
	VPORT_I2C_Write((UINT32*)&glink_338_bx);

	gBootData->pixelRepet = repet;
}

/**
* HDMI_L9Bx_SetAutoSyncPolarity
*
* @parm void
* @return void
*/
void HDMI_L9_SetAutoSyncPolarity(void)
{
	/* All High Polarity Setting from L9 for UD & 3D Full format*/
	VPORT_I2C_Read((UINT32*)&glink_363_bx);
	VPORT_I2C_Read((UINT32*)&glink_345_bx);

	if(glink_363_bx.reg_h_pol_pip0 == 0) // polarity Low
		glink_345_bx.reg_inv_hs_pip0 = 1;
	else
		glink_345_bx.reg_inv_hs_pip0 = 0;

	if(glink_363_bx.reg_v_pol_pip0 == 0) // polarity Low
		glink_345_bx.reg_inv_vs_pip0 = 1;
	else
		glink_345_bx.reg_inv_vs_pip0 = 0;

	glink_345_bx.reg_lbp_f2_pip0 = 0;	//

	VPORT_I2C_Write((UINT32*)&glink_345_bx);
}

/**
* HDMI_L9Bx_GetPortConnection
*
* @parm void
* @return int - 1 : connected , 0 : disconnected
*/
int HDMI_L9_GetPortConnection(void)
{
	ULONG	flags = 0;
	LX_HDMI_MUTE_CTRL_T 		muteCtrl = {0, 0, 3}; // All Clear

	VPORT_I2C_Read((UINT32*)&glink_0_bx);
	_gSCDT = glink_0_bx.reg_scdt_prt0;

	if( _gSCDT == 1)
	{
		if(_gPortConCount == 0)
		{
			_HDMI_L9_SetInternalMute(&muteCtrl);	// All Clear
			//HDMI_L9Bx_SetRGBYCbCr(&_gCurPixelEncoding);
		}
		else
			HDMI_DEBUG(" HDMI connection =%d \n", _gPortConCount);

		_gPortConCount = 0;
	}
	else
	{
		gBootData->mode = 0;
		gBootData->pixelRepet = 0;
		_gDeepColor = HDMI_DEEP_COLOR_8BIT;
		_gCurPixelEncoding = LX_HDMI_AVI_COLORSPACE_RGB;

		_gIntrAVICscState = HDMI_AVI_CSC_STABLE_STATE;;
		_gIntrAVIState = HDMI_AVI_INIT_STATE;
		_gIntrVSIState = HDMI_VSI_INIT_STATE;

		_gExtMute = 0;
		_gAviNoPacket = 1;
		_gAviNoPacketCount = 0;
		_gCurPixelEncoding = LX_HDMI_AVI_COLORSPACE_RGB;
		//HDMI_DEBUG("- [%d] %s - CSC[%d] / DeepColor[%d] Changed -\n", __LINE__, __func__, _gCurPixelEncoding, _gDeepColor);

		//spin lock for protection
		spin_lock_irqsave(&_gIntrHdmiVideoLock, flags);
		_gIntrVideoState = HDMI_VIDEO_INIT_STATE;
		spin_unlock_irqrestore(&_gIntrHdmiVideoLock, flags);

		spin_lock_irqsave(&_gIntrHdmiMuteLock, flags);
		_gIntrSourceMute = HDMI_SOURCE_MUTE_CLEAR_STATE;
		spin_unlock_irqrestore(&_gIntrHdmiMuteLock, flags);

		//HDMI_DEBUG("- [%d] %s - Mute all Clear -\n", __LINE__, __func__);

		//spin lock for protection for audio
		spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
		_gIntrAudioState = HDMI_AUDIO_INIT_STATE;
		spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

		//Clears a global value for audio info.
		memset(&_gHdmiAudioInfo, 0, sizeof(LX_HDMI_AUDIO_INFO_T));

		if(_gPortConCount < 3)
		{
			if(_gPortConCount > 0)
			{
				_HDMI_L9_SetInternalMute(&muteCtrl);	// All Clear
				//HDMI_L9Bx_SetRGBYCbCr(&_gCurPixelEncoding);
			}
#ifndef VIDEO_DEBUG
			HDMI_DEBUG(" HDMI disconnection =%d \n", _gPortConCount);
#endif
			_gPortConCount++;
		}
	}

	HDMI_PRINT("HDMI_L9_GetPortConnection [%d]\n",_gSCDT);
	return _gSCDT;
}

/**
* HDMI_L9Bx_GetMode
*
* @parm LX_HDMI_MODE_T
* @return int
*/
int HDMI_L9_GetMode(LX_HDMI_MODE_T *mode)
{
	BOOLEAN bHDMI = 0;

#if 1
	if (!_gSCDT)
		bHDMI = 0;
	else
		bHDMI = gBootData->mode;
#else
	if (!_gSCDT)
		bHDMI = 0;

	/* Port 0 */
	VPORT_I2C_Read((UINT32*)&glink_1_bx);
	bHDMI = glink_1_bx.reg_hdmi_mode_pip0;

	//Update global value for debug print
	if(bHDMI == 0)
	{
		_gHdmiAudioInfo.audioType = LX_HDMI_AUDIO_DVI;
	}
#endif
	HDMI_PRINT(" HDMI_L8Bx_GetMode =[%s] \n", bHDMI?"HDMI":"DVI");

	mode->bHDMI 	= bHDMI;

	return 0;
}

/**
* HDMI_L9Bx_GetAspectRatio
*
* @parm LX_HDMI_ASPECTRATIO_T
* @return int
*/
int HDMI_L9_GetAspectRatio(LX_HDMI_ASPECTRATIO_T *ratio)
{
	LX_HDMI_AVI_PICTURE_ARC_T aspectRatio = 0; // 0 : ARC_NO_DATA

	if( (!_gSCDT) || (_gIntrVideoState == HDMI_VIDEO_INIT_STATE) )
	{
		memset((void *)ratio , 0 , sizeof(LX_HDMI_ASPECTRATIO_T));
		goto func_exit;
	}

	if(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
	{
		aspectRatio = _gPrevAVIPacket.eAviPacket.ePictureAspectRatio;
		goto func_exit;
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&glink_118_bx);
		aspectRatio = (glink_118_bx.reg_pkt_avi_dat_pip0_2 & 0x30)>>4;			//M1M0
	}

func_exit:

	ratio->eAspectRatio = aspectRatio;

	return 0;
}

/**
* HDMI_L9Bx_GetTimingInfo
*
* @parm HDMI_IOR_GET_TIMING_INFO
* @return int
*/
int HDMI_L9_GetTimingInfo(LX_HDMI_TIMING_INFO_T *info)
{
	LX_HDMI_TIMING_INFO_T 	bufTiming = {0,};
	LX_HDMI_MUTE_CTRL_T 		muteCtrl = {0, 0, 3};
	BOOLEAN mode = 0;
	UINT8 	colorDepth = 0, temp = 0;
	UINT32	tmdsClock = 0,	tmpClock = 0;
	UINT32	up_freq = 0,	down_freq = 0;

	ULONG	flags = 0;

	memset((void *)info , 0 , sizeof(LX_HDMI_TIMING_INFO_T));

	info->state = HDMI_STATE_STABLE;

	if(!HDMI_L9_GetPortConnection())
	{
		//HDMI_ERROR(" HDMI_L9Bx_GetTimingInfo  Port Dis Connection \n");
		memset(&bufTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));
		memset(&_gPrevTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));

		_gTimingChanged = gBootData->connectCn[gBootData->hdmi_switch];
		_gTimingCnt = 0;
		_gSourceMuteCnt = 0;

		goto func_exit;
	}

	if(_gIntrAVICscState == HDMI_AVI_CSC_CHANGE_STATE || _gIntrAVICscState < HDMI_AVI_CSC_TEMP_STATE)
	{
		if(_gIntrAVICscState != HDMI_AVI_CSC_CHANGE_STATE)
		{
			muteCtrl.bVideoMute = 0;			// mute Clear
			_HDMI_L9_SetInternalMute(&muteCtrl);
		}
		_gIntrAVICscState++;
#ifdef AVI_MUTE_DEBUG
		HDMI_DEBUG("* [%d] %s : AVI CSC changed   VideoState[%d] AVICscState[%d] --\n", __LINE__, __func__, _gIntrVideoState, _gIntrAVICscState);
#endif
		goto func_exit;
	}

	if(_gIntrAVICscState == HDMI_AVI_CSC_TEMP_STATE)
	{
		_gIntrAVICscState = HDMI_AVI_CSC_STABLE_STATE;
#ifdef AVI_MUTE_DEBUG
		HDMI_DEBUG("* [%d] %s : CSC Mute Cleard  VideoState[%d] AVICscState[%d] --\n", __LINE__, __func__, _gIntrVideoState, _gIntrAVICscState);
#endif
	}


	if(_gIntrSourceMute != HDMI_SOURCE_MUTE_CLEAR_STATE)
	{
		VPORT_I2C_Read((UINT32*)&glink_151_bx);

#ifdef SOURCE_MUTE_DEBUG
		HDMI_DEBUG("* [%d] Timing changed : SOURCE MUTE State[%d] Clear[%d] VideoState[%d]\n", __LINE__, _gIntrSourceMute, glink_151_bx.reg_pkt_gcp_cmute_pip0, _gIntrVideoState );
		HDMI_DEBUG("* [%d] SOURCE MUTE auto Clear on source mute flag on[%d]\n", __LINE__, _gSourceMuteCnt);
#endif
		if(glink_151_bx.reg_pkt_gcp_cmute_pip0 || _gSourceMuteCnt == 150)
		{
			spin_lock_irqsave(&_gIntrHdmiMuteLock, flags);
			_gIntrSourceMute--;
			spin_unlock_irqrestore(&_gIntrHdmiMuteLock, flags);

			if(_gIntrSourceMute == HDMI_SOURCE_MUTE_CLEAR_STATE)
			{
				muteCtrl.bVideoMute = 0;			// mute Clear
				_HDMI_L9_SetInternalMute(&muteCtrl);

				spin_lock_irqsave(&_gIntrHdmiVideoLock, flags);
				_gIntrVideoState = HDMI_VIDEO_INTERRUPT_STATE;
				spin_unlock_irqrestore(&_gIntrHdmiVideoLock, flags);

				goto func_read;
#ifdef SOURCE_MUTE_DEBUG
				HDMI_DEBUG(" ~~~~ HDMI_SURCE MUTE CLEAR[%d] VideoState[%d] **** \n", _gIntrSourceMute, _gIntrVideoState);
#endif
			}
			else
			{
				goto func_exit;
			}
		}

		_gSourceMuteCnt++;

		goto func_exit;
	}

	if((_gTimingChanged == 0) && (_gTimingCnt == gBootData->timingCn[gBootData->hdmi_switch]))
	{
		VPORT_I2C_Read((UINT32*)&glink_1_bx);
		if(	gBootData->mode != glink_1_bx.reg_hdmi_mode_pip0)
		{
			gBootData->mode = glink_1_bx.reg_hdmi_mode_pip0;
		}
		_gTimingCnt++;
	}

	if((_gIntrVideoState == HDMI_VIDEO_STABLE_STATE) && (_gTimingChanged == 0) && (_gTimingCnt >= gBootData->timingCn[gBootData->hdmi_switch]))
	{
		if(_gExtMute > 0)
		{
			if(_gExtMute == 3)
			{
				_gExtMute = 0;
				goto func_read;
			}
			_gExtMute++;
			goto func_exit;
		}

		VPORT_I2C_Read((UINT32*)&glink_339_bx);
		if( gBootData->pixelRepet != glink_339_bx.reg_pr_tx_pip0)		// when hotplug test, not update pixel repet info from Master 6000
		{
#ifdef VIDEO_DEBUG
			HDMI_DEBUG("[%d] Pixel Repetition update [%d] \n", __LINE__, glink_339_bx.reg_pr_tx_pip0);
#endif
			HDMI_L9_SetPixelRepetition(); 		// for specific 13.5MHz input(480i, 576i) L9 A0 only, L9 B0 don't use
		}

		goto func_exit2;
	}

func_read :

	OS_LockMutex(&g_HDMI_Sema);
	VPORT_I2C_Read((UINT32*)&glink_1_bx);
	gBootData->mode = mode = glink_1_bx.reg_hdmi_mode_pip0;
	OS_UnlockMutex(&g_HDMI_Sema);

#ifdef VIDEO_DEBUG
	HDMI_DEBUG("*[%d]: gBootData = %d, mode = %d, hdmi_mode_pip0 = %d\n", __LINE__, gBootData->mode, mode, glink_1_bx.reg_hdmi_mode_pip0);
#endif

	if(gBootData->mode == 1)		//If HDMI mode and AVI no packet, timing info is all '0'
	{
		_gAviNoPacketCount ++;

		if(_gIntrAVIState <= HDMI_AVI_INTERRUPT_STATE &&  _gAviNoPacketCount < 50)		// No read AVI
		{
			VPORT_I2C_Read((UINT32*)&glink_92_bx); //AVI HB 1
			if(glink_92_bx.reg_pkt_avi_hdr_pip0_0 == 0)
			{
#ifdef VIDEO_DEBUG
				HDMI_DEBUG("*[%d]: No AVI Packet - before AVI Init state\n", __LINE__);
#endif
				goto func_exit;
			}
		}
		else
		{
			if(_gAviNoPacket == 1 &&  _gAviNoPacketCount < 50)
			{
#ifdef VIDEO_DEBUG
				HDMI_DEBUG("*[%d]: No AVI Packet -\n", __LINE__);
#endif
				goto func_exit;
			}
		}
	}


	if(_gTimingChanged > 0 && _gIntrVideoState < HDMI_VIDEO_STABLE_STATE)
	{
		if(_gIntrVideoState < HDMI_VIDEO_INTERRUPT_STATE)
		{
#ifdef VIDEO_DEBUG
			HDMI_DEBUG("* [%d] : HDMI_VIDEO_INIT_STATE : HDMI Mode[%d] AviNoPacket[%d]/count[%d] -\n", __LINE__, gBootData->mode, _gAviNoPacket, _gAviNoPacketCount);
#endif
			goto func_exit;
		}

#ifdef VIDEO_DEBUG
		HDMI_DEBUG("* [%d] : Timing changed [%d]  VideoState[%d] HDMI Mode[%d] -\n", __LINE__, _gTimingChanged,_gIntrVideoState, gBootData->mode);
#endif
		_gTimingChanged --;
		goto func_exit;
	}

	if(_gTimingCnt < gBootData->timingCn[gBootData->hdmi_switch] && _gIntrVideoState != HDMI_VIDEO_STABLE_STATE  && _gTimingChanged == 0)
	{
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("* [%d] : HDMI Count(2)[%d/%d] HDMI Mode[%d] -\n", __LINE__, _gTimingCnt, gBootData->hdmiCn[gBootData->hdmi_switch], gBootData->mode);
#endif
		if(_gTimingCnt < 2)
		{
			_gTimingCnt++;
			goto func_exit;
		}
		_gTimingCnt++;
	}

	HDMI_L9_SetPixelRepetition();			// for specific 13.5MHz input(480i, 576i) L9 A0 only, L9 B0 don't use
	HDMI_L9_SetAutoSyncPolarity();			// sync inversion for UD and 3D(SS_Full) format

	VPORT_I2C_Read((UINT32*)&glink_346_bx);
	VPORT_I2C_Read((UINT32*)&glink_347_bx);
	VPORT_I2C_Read((UINT32*)&glink_348_bx);
	VPORT_I2C_Read((UINT32*)&glink_349_bx);
	VPORT_I2C_Read((UINT32*)&glink_350_bx);
	VPORT_I2C_Read((UINT32*)&glink_351_bx);
	VPORT_I2C_Read((UINT32*)&glink_352_bx);
	VPORT_I2C_Read((UINT32*)&glink_353_bx);
	VPORT_I2C_Read((UINT32*)&glink_354_bx);
	VPORT_I2C_Read((UINT32*)&glink_355_bx);
	VPORT_I2C_Read((UINT32*)&glink_356_bx);
	VPORT_I2C_Read((UINT32*)&glink_357_bx);
	VPORT_I2C_Read((UINT32*)&glink_358_bx);
	VPORT_I2C_Read((UINT32*)&glink_359_bx);

	VPORT_I2C_Read((UINT32*)&glink_363_bx);
	VPORT_I2C_Read((UINT32*)&glink_28_bx);

	bufTiming.hTotal = glink_346_bx.reg_h_tot_pip0_1;
	bufTiming.hTotal = bufTiming.hTotal << 8;
	bufTiming.hTotal = bufTiming.hTotal | glink_347_bx.reg_h_tot_pip0_0;

	bufTiming.vTotal = glink_348_bx.reg_v_tot_pip0_1;
	bufTiming.vTotal = bufTiming.vTotal << 8;
	bufTiming.vTotal = bufTiming.vTotal | glink_349_bx.reg_v_tot_pip0_0;

	bufTiming.hActive = glink_350_bx.reg_h_av_pip0_1;
	bufTiming.hActive = bufTiming.hActive << 8;
	bufTiming.hActive = bufTiming.hActive | glink_351_bx.reg_h_av_pip0_0;

	bufTiming.vActive = glink_352_bx.reg_v_av_pip0_1;
	bufTiming.vActive = bufTiming.vActive << 8;
	bufTiming.vActive = bufTiming.vActive | glink_353_bx.reg_v_av_pip0_0;
#if 0
	/* Front Porch */
	bufTiming.hStart = glink_354_bx.reg_h_fp_pip0_1;
	bufTiming.hStart = bufTiming.hStart << 8;
	bufTiming.hStart = bufTiming.hStart | glink_355_bx.reg_h_fp_pip0_0;

	bufTiming.vStart = glink_356_bx.reg_v_fp_pip0;
#else
	/* Back Porch */
	bufTiming.hStart = glink_357_bx.reg_h_bp_pip0_1;
	bufTiming.hStart = bufTiming.hStart << 8;
	bufTiming.hStart = bufTiming.hStart | glink_358_bx.reg_h_bp_pip0_0;

	bufTiming.vStart = glink_359_bx.reg_v_bp_pip0;
#endif
	///< Scan type (0 : interlace, 1 : progressive)
	bufTiming.scanType = glink_363_bx.reg_intrl_pip0;
	bufTiming.scanType 	^= 1;

	/* All vStart Value set even for Interlace Format, 1080i Issue*/
	//if( bufTiming.scanType == 0)
		//bufTiming.vStart = ((bufTiming.vStart >> 1) << 1);

	// InValid Format Check
	if(	(bufTiming.vActive < 240)  || (bufTiming.hActive < 320) ||
		(bufTiming.vActive > 2970) || (bufTiming.hActive > 4096) )
	{
		//memset(&bufTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));
		goto func_exit;
	}

	//* Support 2D 1920x1080i@50 of EIA-861D  for any PC Card  by 20111010
	//* Use HMDI Long Blank Field 2 for field change issue
	//* Not support Master #840 - because MASTER timing issue
	if(bufTiming.hTotal == 2304)// && bufTiming.hActive == 1920 && bufTiming.scanType == 1)
	{
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("Support 2D 1920x1080!@50 of EIA-861D \n");
#endif
		if(_gPrevVSIPacket.eVsiPacket.eVideoFormat == LX_FORMAT_NO_ADDITIONAL_FORMAT && bufTiming.vTotal == 1250)
		{
			VPORT_I2C_Read((UINT32*)&glink_345_bx);
			glink_345_bx.reg_lbp_f2_pip0 = 1;
			VPORT_I2C_Write((UINT32*)&glink_345_bx);
		}
		else
		{
			memset(&bufTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));
			goto func_exit;
		}
	}

	//* Support 2D 1280x1024i@86  by 20120202
	//* Not support Master #333 - because MASTER timing issue
	if(bufTiming.hActive == 1280 && bufTiming.vActive == 512 && bufTiming.scanType == 1)
	{
#ifndef VIDEO_DEBUG
		HDMI_DEBUG("Support 2D 1280x1024!@86 of Master #333 \n");
#endif
		memset(&bufTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));
			goto func_exit;

	}

	_HDMI_L9_Set3DFullTimingInfo(&bufTiming);

	if( (bufTiming.vActive == 0) && (bufTiming.hActive == 0) )		goto func_exit;

	if(bufTiming.extInfo == LX_HDMI_EXT_2D_FORMAT)		///< Master DVI to HDMI Cable #20, #21 h and v Active info +/-1 error
	{
		if(bufTiming.hActive %2 == 1)
		{
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("TimingInfo hActive = %d  modification\n", bufTiming.hActive );
#endif
			if((bufTiming.hActive > 1918) && (bufTiming.hActive < 1922)) 		bufTiming.hActive = 1920;
			else if((bufTiming.hActive > 1438) && (bufTiming.hActive < 1442))		bufTiming.hActive = 1440;
			else if((bufTiming.hActive > 1278) && (bufTiming.hActive < 1282)) 		bufTiming.hActive = 1280;
			else if((bufTiming.hActive > 718) && (bufTiming.hActive < 722)) 		bufTiming.hActive = 720;
			else if((bufTiming.hActive > 638) && (bufTiming.hActive < 642)) 		bufTiming.hActive = 640;
		}

		if(bufTiming.vActive %2 == 1)
		{
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("TimingInfo vActive= %d modification\n", bufTiming.vActive);
#endif
			if((bufTiming.vActive > 1078) && (bufTiming.vActive < 1082)) 		bufTiming.vActive = 1080;
			else if((bufTiming.vActive > 718) && (bufTiming.vActive < 722)) 		bufTiming.vActive = 720;
			else if((bufTiming.vActive > 574) && (bufTiming.vActive < 578)) 		bufTiming.vActive = 576;
			else if((bufTiming.vActive > 478) && (bufTiming.vActive < 482)) 		bufTiming.vActive = 480;
		}
	}
//////////////* Horizontal & Vertical frequency //////////////////////////
#if 1

	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_23_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_24_bx);

	up_freq = ghdmi_phy_n_23_bx.tmds_freq;
	down_freq = ghdmi_phy_n_24_bx.tmds_freq;
	tmdsClock = ((up_freq << 8) + down_freq); 	// XXX.XX KHz

	if(tmdsClock == 1350 && gBootData->pixelRepet == 0)		// L9 not support 13.5MHz W/O pixel Repet info
	{
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("TMDS Clock = 13.5MHz & Pixel Repet = %d \n", gBootData->pixelRepet);
#endif
		goto func_exit;
	}
	tmpClock = tmdsClock * 1000;

	if(tmdsClock != 0)		// XXX.XX KHz
	{
		VPORT_I2C_Read((UINT32*)&glink_344_bx);
		_gDeepColor = colorDepth = glink_344_bx.reg_cmode_stat_pip0;

		if(colorDepth)
		{
			tmdsClock= tmdsClock * 100;
			if(colorDepth == 1) tmdsClock = tmdsClock / 125;					// colorDepth = 10bit
			else				tmdsClock = tmdsClock / 150;					// colorDepth = 12bit
		}
		tmdsClock = tmdsClock * 1000;			// XX,XXX KHz
		//bufTiming.hFreq = tmdsClock / bufTiming.hTotal;		///< Horizontal frequency(100 Hz unit) = Dot Freq / hTotal

		bufTiming.vFreq = tmdsClock / bufTiming.vTotal;		//XX.X KHz
		tmpClock = bufTiming.vFreq * 100;					//X,XX0 KHz
		bufTiming.vFreq = tmpClock / bufTiming.hTotal;		//XX.X Hz	///< Veritical frequency(1/10 Hz unit) = hFreq / vTotal

#if 0	// L9 don't use, because clock and  hTotal is double
		if(gBootData->pixelRepet == 1 ) // HDMI_SetPixelRepetition
		{
			bufTiming.vFreq = bufTiming.vFreq / (gBootData->pixelRepet + gBootData->pixelRepet);
			//bufTiming.hFreq = bufTiming.hFreq / 20;
		}
		else
		{
			//bufTiming.hFreq = bufTiming.hFreq / 10;
		}
#endif
		if( bufTiming.scanType == 0)		// 0 : interlace
			bufTiming.vFreq = bufTiming.vFreq + bufTiming.vFreq;

		if((bufTiming.vFreq > 234) &&	(bufTiming.vFreq < 245))			bufTiming.vFreq = 240;
		else if((bufTiming.vFreq > 244) &&	(bufTiming.vFreq < 255))		bufTiming.vFreq = 250;
		else if((bufTiming.vFreq > 294) &&	(bufTiming.vFreq < 305))		bufTiming.vFreq = 300;
		else if((bufTiming.vFreq > 494) &&	(bufTiming.vFreq < 505))		bufTiming.vFreq = 500;
		else if((bufTiming.vFreq > 594) &&	(bufTiming.vFreq < 605))		bufTiming.vFreq = 600;
		else if((bufTiming.vFreq > 654) &&	(bufTiming.vFreq < 660))		bufTiming.vFreq = 660;
		else if((bufTiming.vFreq > 694) &&	(bufTiming.vFreq < 705))		bufTiming.vFreq = 700;
		else if((bufTiming.vFreq > 714) &&	(bufTiming.vFreq < 725))		bufTiming.vFreq = 720;
		else if((bufTiming.vFreq > 744) &&	(bufTiming.vFreq < 755))		bufTiming.vFreq = 750;
		else if((bufTiming.vFreq > 754) &&	(bufTiming.vFreq < 765))		bufTiming.vFreq = 760;
		else if((bufTiming.vFreq > 794) &&	(bufTiming.vFreq < 805))		bufTiming.vFreq = 800;
		else if((bufTiming.vFreq > 844) &&	(bufTiming.vFreq < 855))		bufTiming.vFreq = 850;
		else
		{
			temp = bufTiming.vFreq % 10;
			if( temp != 0 )
			{
				bufTiming.vFreq = bufTiming.vFreq / 10;
				if(temp < 5)
					bufTiming.vFreq = bufTiming.vFreq * 10;
				else
					bufTiming.vFreq = (bufTiming.vFreq + 1) * 10;
			}
		}

		if(bufTiming.extInfo == LX_HDMI_EXT_3D_FIELD_ALTERNATIVE)
		{
			bufTiming.vFreq = bufTiming.vFreq >> 1;
		}
		if( bufTiming.vFreq > 1000 )									bufTiming.vFreq = 1000;
	}
#else
	bufTiming.vFreq = 1;
#endif

	if(_gTimingCnt < gBootData->timingCn[gBootData->hdmi_switch])
	{
		if(_gTimingCnt > 0 && _gTimingCnt < HDMI_VIDEO_READ_STATE)
		{
#if 0
			bufTiming.hActive = bufTiming.hActive - _gTimingCnt*21;
			bufTiming.vActive = bufTiming.vActive + _gTimingCnt*22;
#else
			bufTiming.vFreq = 0;
#endif

#ifdef VIDEO_DEBUG
			HDMI_DEBUG("TimingInfo vFreq = %d \n", bufTiming.vFreq);
#endif
		}
	}
//////////////* Horizontal & Vertical frequency end //////////////////////////

func_exit:
	info->hFreq 	= _gPrevTiming.hFreq 	= bufTiming.hFreq; 			///< Horizontal frequency(100 Hz unit) = Dot Freq / hTotal
	info->vFreq 	= _gPrevTiming.vFreq 	= bufTiming.vFreq; 			///< Veritical frequency(1/10 Hz unit) = hFreq / vTotal
	info->hTotal	= _gPrevTiming.hTotal 	= bufTiming.hTotal; 		///< Horizontal total pixels
	info->vTotal 	= _gPrevTiming.vTotal	= bufTiming.vTotal; 		///< Vertical total lines
	info->hStart	= _gPrevTiming.hStart	= bufTiming.hStart; 		///< Horizontal start pixel (Back Porch)
	info->vStart 	= _gPrevTiming.vStart	= bufTiming.vStart;			///< Vertical start lines (Back Porch)
	info->hActive 	= _gPrevTiming.hActive	= bufTiming.hActive;		///< Horizontal active pixel
	info->vActive 	= _gPrevTiming.vActive	= bufTiming.vActive; 		///< Vertical active lines
	info->scanType 	= _gPrevTiming.scanType	= bufTiming.scanType; 		///< Scan type (0 : interlace, 1 : progressive) 	info->scanType ^= 1;
	info->extInfo	= _gPrevTiming.extInfo	= bufTiming.extInfo; 	///< Full 3D Timing

	if((_gTimingChanged == 0) && (_gTimingCnt >= gBootData->timingCn[gBootData->hdmi_switch]) && (_gIntrAVICscState == HDMI_AVI_CSC_STABLE_STATE))
	{
		spin_lock_irqsave(&_gIntrHdmiVideoLock, flags);
		_gIntrVideoState = HDMI_VIDEO_STABLE_STATE;
		spin_unlock_irqrestore(&_gIntrHdmiVideoLock, flags);

		HDMI_DEBUG("* [%d] TimingInfo _gIntrVideoState = %d \n", __LINE__,_gIntrVideoState);
	}
	return 0;

func_exit2:
	info->hFreq 	= _gPrevTiming.hFreq; 		///< Horizontal frequency(100 Hz unit) = Dot Freq / hTotal
	info->vFreq 	= _gPrevTiming.vFreq; 		///< Veritical frequency(1/10 Hz unit) = hFreq / vTotal
	info->hTotal	= _gPrevTiming.hTotal; 		///< Horizontal total pixels
	info->vTotal 	= _gPrevTiming.vTotal; 		///< Vertical total lines
	info->hStart	= _gPrevTiming.hStart; 		///< Horizontal start pixel (Back Porch)
	info->vStart 	= _gPrevTiming.vStart;		///< Vertical start lines (Back Porch)
	info->hActive 	= _gPrevTiming.hActive;		///< Horizontal active pixel
	info->vActive 	= _gPrevTiming.vActive; 	///< Vertical active lines
	info->scanType 	= _gPrevTiming.scanType; 	///< Scan type (0 : interlace, 1 : progressive) 	info->scanType ^= 1;
	info->extInfo	= _gPrevTiming.extInfo; 	///< Full 3D Timing
	return 0;
}

/**
* HDMI_L9Bx_GetStatus
*
* @parm LX_HDMI_STATUS_T
* @return int
*/
int HDMI_L9_GetStatus(LX_HDMI_STATUS_T *status)
{
	if(!_gSCDT)
	{
		memset((void *)status , 0 , sizeof(LX_HDMI_STATUS_T));
		return 0;
	}

	status->bHdmiMode = gBootData->mode;
	status->eColorDepth = _gDeepColor;
	status->eHotPlug = _gSCDT;
	status->pixelRepet = gBootData->pixelRepet;
	status->csc = _gCurPixelEncoding;

#ifdef VIDEO_DEBUG
	//HDMI_DEBUG(" * [%d] %s : VideoState(2)[%d] SourceMute(3)[%d] AudioState[%d] \n", __LINE__, __func__, _gIntrVideoState, _gIntrSourceMute, _gIntrAudioState);
#endif

	return 0;
}

/**
* HDMI_L9Bx_GetVsiPacket
*
* @parm LX_HDMI_VSI_PACKET_T
* @return int
*/
int HDMI_L9_GetVsiPacket(LX_HDMI_VSI_PACKET_T *packet)
{
	UINT8 tmp8 = 0;
	UINT8 count = 0;
	AI2C_DATA_T r;

	HDMI_PRINT("%s: Get ASI Packet", __func__);

	memset((void *)packet , 0 , sizeof(LX_HDMI_VSI_PACKET_T));

	if( (!_gSCDT) || (_gIntrVideoState == HDMI_VIDEO_INIT_STATE) )
	{
		memset(&_gPrevVSIPacket, 0 , sizeof(LX_HDMI_VSI_PACKET_T));
		return 0;
	}

	if(_gIntrVSIState == HDMI_VSI_STABLE_STATE  && _gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
	{
		goto func_exit;
	}

#ifdef INTERRUNT_VIDEO_DEBUG
	HDMI_DEBUG("+++ %s[%d] : VSIState = %d \n", __func__, __LINE__, _gIntrVSIState);
#endif

	VPORT_I2C_Read((UINT32*)&glink_334_bx); //VSI data 0
	VPORT_I2C_Read((UINT32*)&glink_333_bx);
	VPORT_I2C_Read((UINT32*)&glink_332_bx);
	VPORT_I2C_Read((UINT32*)&glink_331_bx);
	VPORT_I2C_Read((UINT32*)&glink_330_bx);

	memcpy(&r, &glink_334_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevVSIPacket.eVsiPacket.packet.dataBytes[0] )	count++;
	memcpy(&r, &glink_333_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevVSIPacket.eVsiPacket.packet.dataBytes[1] )	count++;
	memcpy(&r, &glink_332_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevVSIPacket.eVsiPacket.packet.dataBytes[2] )	count++;
	memcpy(&r, &glink_331_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevVSIPacket.eVsiPacket.packet.dataBytes[3] )	count++;
	memcpy(&r, &glink_330_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevVSIPacket.eVsiPacket.packet.dataBytes[4] )	count++;

	if(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
		_gIntrVSIState++;

	if(count == 5)	// same pre VSI Packet
	{
#ifdef INTERRUNT_VIDEO_DEBUG
		HDMI_DEBUG("+++ %s[%d] : Same Read  VSIState = %d \n", __func__, __LINE__, _gIntrVSIState);
#endif
		goto func_exit;
	}

	memset(&_gPrevVSIPacket, 0 , sizeof(LX_HDMI_VSI_PACKET_T));

	VPORT_I2C_Read((UINT32*)&glink_306_bx); //VSI HB 1
	VPORT_I2C_Read((UINT32*)&glink_305_bx); //VSI HB 2

	if(glink_306_bx.reg_pkt_vsi_hdr_pip0_0 == 0 && glink_305_bx.reg_pkt_vsi_hdr_pip0_1== 0)
	{
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("--- %s[%d] VSI No Packet  VSIIState = %d \n", __func__, __LINE__, _gIntrVSIState);
#endif
		goto func_exit;
	}

	VPORT_I2C_Read((UINT32*)&glink_329_bx);
	VPORT_I2C_Read((UINT32*)&glink_328_bx);
	VPORT_I2C_Read((UINT32*)&glink_327_bx);
	VPORT_I2C_Read((UINT32*)&glink_326_bx);
	VPORT_I2C_Read((UINT32*)&glink_325_bx);
	VPORT_I2C_Read((UINT32*)&glink_324_bx);
/*
	VPORT_I2C_Read((UINT32*)&glink_323_bx); //VSI data 11
	VPORT_I2C_Read((UINT32*)&glink_322_bx);
	VPORT_I2C_Read((UINT32*)&glink_321_bx);
	VPORT_I2C_Read((UINT32*)&glink_320_bx);
	VPORT_I2C_Read((UINT32*)&glink_319_bx);
	VPORT_I2C_Read((UINT32*)&glink_318_bx);
	VPORT_I2C_Read((UINT32*)&glink_317_bx);
	VPORT_I2C_Read((UINT32*)&glink_316_bx);
	VPORT_I2C_Read((UINT32*)&glink_315_bx);
	VPORT_I2C_Read((UINT32*)&glink_314_bx);
	VPORT_I2C_Read((UINT32*)&glink_313_bx);
	VPORT_I2C_Read((UINT32*)&glink_312_bx);
	VPORT_I2C_Read((UINT32*)&glink_311_bx);
	VPORT_I2C_Read((UINT32*)&glink_310_bx);
	VPORT_I2C_Read((UINT32*)&glink_309_bx);
	VPORT_I2C_Read((UINT32*)&glink_308_bx);
	VPORT_I2C_Read((UINT32*)&glink_307_bx); //VSI data 27
*/

	///< 24 bit IEEE Registration Identifier[3]
	packet->eVsiPacket.IEERegId[0] = _gPrevVSIPacket.eVsiPacket.IEERegId[0] = glink_333_bx.reg_pkt_vsi_dat_pip0_1;
	packet->eVsiPacket.IEERegId[1] = _gPrevVSIPacket.eVsiPacket.IEERegId[1] = glink_332_bx.reg_pkt_vsi_dat_pip0_2;
	packet->eVsiPacket.IEERegId[2] = _gPrevVSIPacket.eVsiPacket.IEERegId[2] = glink_331_bx.reg_pkt_vsi_dat_pip0_3;

	///< Payload  [24]
	packet->eVsiPacket.PayLoad[0] = _gPrevVSIPacket.eVsiPacket.PayLoad[0] = glink_330_bx.reg_pkt_vsi_dat_pip0_4;
	packet->eVsiPacket.PayLoad[1] = _gPrevVSIPacket.eVsiPacket.PayLoad[1] = glink_329_bx.reg_pkt_vsi_dat_pip0_5;
	packet->eVsiPacket.PayLoad[2] = _gPrevVSIPacket.eVsiPacket.PayLoad[2] = glink_328_bx.reg_pkt_vsi_dat_pip0_6;
	packet->eVsiPacket.PayLoad[3] = _gPrevVSIPacket.eVsiPacket.PayLoad[3] = glink_327_bx.reg_pkt_vsi_dat_pip0_7;
	packet->eVsiPacket.PayLoad[4] = _gPrevVSIPacket.eVsiPacket.PayLoad[4] = glink_326_bx.reg_pkt_vsi_dat_pip0_8;
	packet->eVsiPacket.PayLoad[5] = _gPrevVSIPacket.eVsiPacket.PayLoad[5] = glink_325_bx.reg_pkt_vsi_dat_pip0_9;
	packet->eVsiPacket.PayLoad[6] = _gPrevVSIPacket.eVsiPacket.PayLoad[6] = glink_324_bx.reg_pkt_vsi_dat_pip0_10;
/*
	packet->eVsiPacket.PayLoad[7] = _gPrevVSIPacket.eVsiPacket.PayLoad[7] = glink_323_bx.reg_pkt_vsi_dat_pip0_11;
	packet->eVsiPacket.PayLoad[8] = _gPrevVSIPacket.eVsiPacket.PayLoad[8] = glink_322_bx.reg_pkt_vsi_dat_pip0_12;
	packet->eVsiPacket.PayLoad[9] = _gPrevVSIPacket.eVsiPacket.PayLoad[9] = glink_321_bx.reg_pkt_vsi_dat_pip0_13;
	packet->eVsiPacket.PayLoad[10] = _gPrevVSIPacket.eVsiPacket.PayLoad[10] = glink_320_bx.reg_pkt_vsi_dat_pip0_14;
	packet->eVsiPacket.PayLoad[11] = _gPrevVSIPacket.eVsiPacket.PayLoad[11] = glink_319_bx.reg_pkt_vsi_dat_pip0_15;
	packet->eVsiPacket.PayLoad[12] = _gPrevVSIPacket.eVsiPacket.PayLoad[12] = glink_318_bx.reg_pkt_vsi_dat_pip0_16;
	packet->eVsiPacket.PayLoad[13] = _gPrevVSIPacket.eVsiPacket.PayLoad[13] = glink_317_bx.reg_pkt_vsi_dat_pip0_17;
	packet->eVsiPacket.PayLoad[14] = _gPrevVSIPacket.eVsiPacket.PayLoad[14] = glink_316_bx.reg_pkt_vsi_dat_pip0_18;
	packet->eVsiPacket.PayLoad[15] = _gPrevVSIPacket.eVsiPacket.PayLoad[15] = glink_315_bx.reg_pkt_vsi_dat_pip0_19;
	packet->eVsiPacket.PayLoad[16] = _gPrevVSIPacket.eVsiPacket.PayLoad[16] = glink_314_bx.reg_pkt_vsi_dat_pip0_20;
	packet->eVsiPacket.PayLoad[17] = _gPrevVSIPacket.eVsiPacket.PayLoad[17] = glink_313_bx.reg_pkt_vsi_dat_pip0_21;
	packet->eVsiPacket.PayLoad[18] = _gPrevVSIPacket.eVsiPacket.PayLoad[18] = glink_312_bx.reg_pkt_vsi_dat_pip0_22;
	packet->eVsiPacket.PayLoad[19] = _gPrevVSIPacket.eVsiPacket.PayLoad[19] = glink_311_bx.reg_pkt_vsi_dat_pip0_23;
	packet->eVsiPacket.PayLoad[20] = _gPrevVSIPacket.eVsiPacket.PayLoad[20] = glink_310_bx.reg_pkt_vsi_dat_pip0_24;
	packet->eVsiPacket.PayLoad[21] = _gPrevVSIPacket.eVsiPacket.PayLoad[21] = glink_309_bx.reg_pkt_vsi_dat_pip0_25;
	packet->eVsiPacket.PayLoad[22] = _gPrevVSIPacket.eVsiPacket.PayLoad[22] = glink_308_bx.reg_pkt_vsi_dat_pip0_26;
	packet->eVsiPacket.PayLoad[23] = _gPrevVSIPacket.eVsiPacket.PayLoad[23] = glink_307_bx.reg_pkt_vsi_dat_pip0_27;
*/
	/**< HDMI VSI info */
	tmp8 = glink_330_bx.reg_pkt_vsi_dat_pip0_4;
	packet->eVsiPacket.eVideoFormat = _gPrevVSIPacket.eVsiPacket.eVideoFormat = (tmp8 & 0xE0) >> 5;

	/* if videoFormat == 0, no more data */
	/* if videoFormat == 1, extended resolution present */
	packet->eVsiPacket.eVSiVIC = _gPrevVSIPacket.eVsiPacket.eVSiVIC = glink_329_bx.reg_pkt_vsi_dat_pip0_5;
	tmp8 = glink_328_bx.reg_pkt_vsi_dat_pip0_6;
	packet->eVsiPacket.e3DExtData = _gPrevVSIPacket.eVsiPacket.e3DExtData = (tmp8 & 0xF0) >> 4;
	/* if videoFormat == 2, 3D Format indication with 3d structure */
	tmp8 = glink_329_bx.reg_pkt_vsi_dat_pip0_5;
	packet->eVsiPacket.e3DStructure = _gPrevVSIPacket.eVsiPacket.e3DStructure = (tmp8 & 0xF0) >> 4;

	///< Packet raw data
	packet->eVsiPacket.packet.type = _gPrevVSIPacket.eVsiPacket.packet.type = 0x81;
	packet->eVsiPacket.packet.version = _gPrevVSIPacket.eVsiPacket.packet.version = glink_306_bx.reg_pkt_vsi_hdr_pip0_0;
	packet->eVsiPacket.packet.length = _gPrevVSIPacket.eVsiPacket.packet.length = glink_305_bx.reg_pkt_vsi_hdr_pip0_1 & 0x1F;
	packet->eVsiPacket.packet.dataBytes[0] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[0] = glink_334_bx.reg_pkt_vsi_dat_pip0_0;
	packet->eVsiPacket.packet.dataBytes[1] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[1] = glink_333_bx.reg_pkt_vsi_dat_pip0_1;
	packet->eVsiPacket.packet.dataBytes[2] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[2] = glink_332_bx.reg_pkt_vsi_dat_pip0_2;
	packet->eVsiPacket.packet.dataBytes[3] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[3] = glink_331_bx.reg_pkt_vsi_dat_pip0_3;
	packet->eVsiPacket.packet.dataBytes[4] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[4] = glink_330_bx.reg_pkt_vsi_dat_pip0_4;
	packet->eVsiPacket.packet.dataBytes[5] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[5] = glink_329_bx.reg_pkt_vsi_dat_pip0_5;
	packet->eVsiPacket.packet.dataBytes[6] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[6] = glink_328_bx.reg_pkt_vsi_dat_pip0_6;
	packet->eVsiPacket.packet.dataBytes[7] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[7] = glink_327_bx.reg_pkt_vsi_dat_pip0_7;
	packet->eVsiPacket.packet.dataBytes[8] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[8] = glink_326_bx.reg_pkt_vsi_dat_pip0_8;
	packet->eVsiPacket.packet.dataBytes[9] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[9] = glink_325_bx.reg_pkt_vsi_dat_pip0_9;
	packet->eVsiPacket.packet.dataBytes[10] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[10] = glink_324_bx.reg_pkt_vsi_dat_pip0_10;
/*
	packet->eVsiPacket.packet.dataBytes[11] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[11] = glink_323_bx.reg_pkt_vsi_dat_pip0_11;
	packet->eVsiPacket.packet.dataBytes[12] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[12] = glink_322_bx.reg_pkt_vsi_dat_pip0_12;
	packet->eVsiPacket.packet.dataBytes[13] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[13] = glink_321_bx.reg_pkt_vsi_dat_pip0_13;
	packet->eVsiPacket.packet.dataBytes[14] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[14] = glink_320_bx.reg_pkt_vsi_dat_pip0_14;
	packet->eVsiPacket.packet.dataBytes[15] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[15] = glink_319_bx.reg_pkt_vsi_dat_pip0_15;
	packet->eVsiPacket.packet.dataBytes[16] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[16] = glink_318_bx.reg_pkt_vsi_dat_pip0_16;
	packet->eVsiPacket.packet.dataBytes[17] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[17] = glink_317_bx.reg_pkt_vsi_dat_pip0_17;
	packet->eVsiPacket.packet.dataBytes[18] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[18] = glink_316_bx.reg_pkt_vsi_dat_pip0_18;
	packet->eVsiPacket.packet.dataBytes[19] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[19] = glink_315_bx.reg_pkt_vsi_dat_pip0_19;
	packet->eVsiPacket.packet.dataBytes[20] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[20] = glink_314_bx.reg_pkt_vsi_dat_pip0_20;
	packet->eVsiPacket.packet.dataBytes[21] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[21] = glink_313_bx.reg_pkt_vsi_dat_pip0_21;
	packet->eVsiPacket.packet.dataBytes[22] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[22] = glink_312_bx.reg_pkt_vsi_dat_pip0_22;
	packet->eVsiPacket.packet.dataBytes[23] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[23] = glink_311_bx.reg_pkt_vsi_dat_pip0_23;
	packet->eVsiPacket.packet.dataBytes[24] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[24] = glink_310_bx.reg_pkt_vsi_dat_pip0_24;
	packet->eVsiPacket.packet.dataBytes[25] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[25] = glink_309_bx.reg_pkt_vsi_dat_pip0_25;
	packet->eVsiPacket.packet.dataBytes[26] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[26] = glink_308_bx.reg_pkt_vsi_dat_pip0_26;
	packet->eVsiPacket.packet.dataBytes[27] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[27] = glink_307_bx.reg_pkt_vsi_dat_pip0_27;
*/
	packet->eVsiPacket.packetStatus = _gPrevVSIPacket.eVsiPacket.packetStatus = LX_HDMI_VSI_PACKET_STATUS_UPDATED;

#ifdef VIDEO_DEBUG
	HDMI_DEBUG("+++ %s[%d] VSI Info Read  \n",  __func__, __LINE__);
#endif

	return 0;

func_exit:

	packet->eVsiPacket.IEERegId[0] = _gPrevVSIPacket.eVsiPacket.IEERegId[0];
	packet->eVsiPacket.IEERegId[1] = _gPrevVSIPacket.eVsiPacket.IEERegId[1];
	packet->eVsiPacket.IEERegId[2] = _gPrevVSIPacket.eVsiPacket.IEERegId[2];

	packet->eVsiPacket.PayLoad[0] = _gPrevVSIPacket.eVsiPacket.PayLoad[0];
	packet->eVsiPacket.PayLoad[1] = _gPrevVSIPacket.eVsiPacket.PayLoad[1];
	packet->eVsiPacket.PayLoad[2] = _gPrevVSIPacket.eVsiPacket.PayLoad[2];
	packet->eVsiPacket.PayLoad[3] = _gPrevVSIPacket.eVsiPacket.PayLoad[3];
	packet->eVsiPacket.PayLoad[4] = _gPrevVSIPacket.eVsiPacket.PayLoad[4];
	packet->eVsiPacket.PayLoad[5] = _gPrevVSIPacket.eVsiPacket.PayLoad[5];
	packet->eVsiPacket.PayLoad[6] = _gPrevVSIPacket.eVsiPacket.PayLoad[6];
/*
	packet->eVsiPacket.PayLoad[7] = _gPrevVSIPacket.eVsiPacket.PayLoad[7];
	packet->eVsiPacket.PayLoad[8] = _gPrevVSIPacket.eVsiPacket.PayLoad[8];
	packet->eVsiPacket.PayLoad[9] = _gPrevVSIPacket.eVsiPacket.PayLoad[9];
	packet->eVsiPacket.PayLoad[10] = _gPrevVSIPacket.eVsiPacket.PayLoad[10];
	packet->eVsiPacket.PayLoad[11] = _gPrevVSIPacket.eVsiPacket.PayLoad[11];
	packet->eVsiPacket.PayLoad[12] = _gPrevVSIPacket.eVsiPacket.PayLoad[12];
	packet->eVsiPacket.PayLoad[13] = _gPrevVSIPacket.eVsiPacket.PayLoad[13];
	packet->eVsiPacket.PayLoad[14] = _gPrevVSIPacket.eVsiPacket.PayLoad[14];
	packet->eVsiPacket.PayLoad[15] = _gPrevVSIPacket.eVsiPacket.PayLoad[15];
	packet->eVsiPacket.PayLoad[16] = _gPrevVSIPacket.eVsiPacket.PayLoad[16];
	packet->eVsiPacket.PayLoad[17] = _gPrevVSIPacket.eVsiPacket.PayLoad[17];
	packet->eVsiPacket.PayLoad[18] = _gPrevVSIPacket.eVsiPacket.PayLoad[18];
	packet->eVsiPacket.PayLoad[19] = _gPrevVSIPacket.eVsiPacket.PayLoad[19];
	packet->eVsiPacket.PayLoad[20] = _gPrevVSIPacket.eVsiPacket.PayLoad[20];
	packet->eVsiPacket.PayLoad[21] = _gPrevVSIPacket.eVsiPacket.PayLoad[21];
	packet->eVsiPacket.PayLoad[22] = _gPrevVSIPacket.eVsiPacket.PayLoad[22];
	packet->eVsiPacket.PayLoad[23] = _gPrevVSIPacket.eVsiPacket.PayLoad[23];
*/
	packet->eVsiPacket.eVideoFormat = _gPrevVSIPacket.eVsiPacket.eVideoFormat;
	packet->eVsiPacket.eVSiVIC = _gPrevVSIPacket.eVsiPacket.eVSiVIC;
	packet->eVsiPacket.e3DExtData = _gPrevVSIPacket.eVsiPacket.e3DExtData;
	packet->eVsiPacket.e3DStructure = _gPrevVSIPacket.eVsiPacket.e3DStructure;

	packet->eVsiPacket.packet.type = _gPrevVSIPacket.eVsiPacket.packet.type;
	packet->eVsiPacket.packet.version = _gPrevVSIPacket.eVsiPacket.packet.version;
	packet->eVsiPacket.packet.length = _gPrevVSIPacket.eVsiPacket.packet.length;
	packet->eVsiPacket.packet.dataBytes[0] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[0];
	packet->eVsiPacket.packet.dataBytes[1] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[1];
	packet->eVsiPacket.packet.dataBytes[2] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[2];
	packet->eVsiPacket.packet.dataBytes[3] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[3];
	packet->eVsiPacket.packet.dataBytes[4] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[4];
	packet->eVsiPacket.packet.dataBytes[5] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[5];
	packet->eVsiPacket.packet.dataBytes[6] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[6];
	packet->eVsiPacket.packet.dataBytes[7] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[7];
	packet->eVsiPacket.packet.dataBytes[8] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[8];
	packet->eVsiPacket.packet.dataBytes[9] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[9];
	packet->eVsiPacket.packet.dataBytes[10] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[10];
/*
	packet->eVsiPacket.packet.dataBytes[11] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[11];
	packet->eVsiPacket.packet.dataBytes[12] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[12];
	packet->eVsiPacket.packet.dataBytes[13] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[13];
	packet->eVsiPacket.packet.dataBytes[14] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[14];
	packet->eVsiPacket.packet.dataBytes[15] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[15];
	packet->eVsiPacket.packet.dataBytes[16] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[16];
	packet->eVsiPacket.packet.dataBytes[17] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[17];
	packet->eVsiPacket.packet.dataBytes[18] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[18];
	packet->eVsiPacket.packet.dataBytes[19] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[19];
	packet->eVsiPacket.packet.dataBytes[20] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[20];
	packet->eVsiPacket.packet.dataBytes[21] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[21];
	packet->eVsiPacket.packet.dataBytes[22] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[22];
	packet->eVsiPacket.packet.dataBytes[23] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[23];
	packet->eVsiPacket.packet.dataBytes[24] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[24];
	packet->eVsiPacket.packet.dataBytes[25] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[25];
	packet->eVsiPacket.packet.dataBytes[26] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[26];
	packet->eVsiPacket.packet.dataBytes[27] = _gPrevVSIPacket.eVsiPacket.packet.dataBytes[27];
*/
	packet->eVsiPacket.packetStatus = _gPrevVSIPacket.eVsiPacket.packetStatus;

	return 0;
}

/**
* HDMI_L9Bx_GetAviPacket
*
* @parm LX_HDMI_AVI_PACKET_T
* @return int
*/
int HDMI_L9_GetAviPacket(LX_HDMI_AVI_PACKET_T *packet)
{
	UINT8 tmp8 = 0;
	UINT8 tmp16 = 0;
	UINT8 count = 0;
	AI2C_DATA_T r;

	HDMI_PRINT("%s: Get AVI Packet = %d\n", __func__, _gIntrAVIState);

	memset((void *)packet , 0 , sizeof(LX_HDMI_AVI_PACKET_T));

	if( (!_gSCDT) )//|| (_gIntrVideoState == HDMI_VIDEO_INIT_STATE) )
	{
		memset(&_gPrevAVIPacket, 0 , sizeof(LX_HDMI_AVI_PACKET_T));
		return 0;
	}

	if(_gIntrAVIState == HDMI_AVI_STABLE_STATE &&(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE))
	{
#ifdef INTERRUNT_VIDEO_DEBUG
		if(_gIntrVideoState != HDMI_VIDEO_STABLE_STATE)
			HDMI_DEBUG("--- %s[%d] AVIState = %d \n",  __func__, __LINE__, _gIntrAVIState);
#endif
		goto func_exit;
	}

#ifdef INTERRUNT_VIDEO_DEBUG
	//HDMI_DEBUG("--- %s[%d] AVIState = %d \n",  __func__, __LINE__, _gIntrAVIState);
#endif

	VPORT_I2C_Read((UINT32*)&glink_120_bx); //AVI data 0
	VPORT_I2C_Read((UINT32*)&glink_119_bx);
	VPORT_I2C_Read((UINT32*)&glink_118_bx);
	VPORT_I2C_Read((UINT32*)&glink_117_bx);
	VPORT_I2C_Read((UINT32*)&glink_116_bx);

	memcpy(&r, &glink_120_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevAVIPacket.eAviPacket.packet.dataBytes[0] )	count++;
	memcpy(&r, &glink_119_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevAVIPacket.eAviPacket.packet.dataBytes[1] )	count++;
	memcpy(&r, &glink_118_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevAVIPacket.eAviPacket.packet.dataBytes[2] )	count++;
	memcpy(&r, &glink_117_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevAVIPacket.eAviPacket.packet.dataBytes[3] )	count++;
	memcpy(&r, &glink_116_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevAVIPacket.eAviPacket.packet.dataBytes[4] )	count++;

	if( gBootData->mode == _gPrevAVIPacket.eAviPacket.bHdmiMode )	count++;

	if(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
		_gIntrAVIState ++;

	if(count == 6)	// same pre AVI Packet
	{
#ifdef INTERRUNT_VIDEO_DEBUG
		//HDMI_DEBUG("--- %s[%d] : Same Read  AVIState = %d \n", __func__, __LINE__, _gIntrAVIState);
#endif
		goto func_exit;
	}

	memset(&_gPrevAVIPacket, 0 , sizeof(LX_HDMI_AVI_PACKET_T));

	VPORT_I2C_Read((UINT32*)&glink_92_bx); //AVI HB 1
	VPORT_I2C_Read((UINT32*)&glink_91_bx); //AVI HB 2

	if(glink_92_bx.reg_pkt_avi_hdr_pip0_0 == 0 && glink_91_bx.reg_pkt_avi_hdr_pip0_1 == 0)
	{
		_gAviNoPacket = 1;
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("--- %s[%d] : AVI_No_Packet / AVIState[%d] \n", __func__, __LINE__, _gIntrAVIState);
#endif
		goto func_exit;
	}
	_gAviNoPacket = 0;

	VPORT_I2C_Read((UINT32*)&glink_115_bx);
	VPORT_I2C_Read((UINT32*)&glink_114_bx);
	VPORT_I2C_Read((UINT32*)&glink_113_bx);
	VPORT_I2C_Read((UINT32*)&glink_112_bx);
	VPORT_I2C_Read((UINT32*)&glink_111_bx);
	VPORT_I2C_Read((UINT32*)&glink_110_bx);
	VPORT_I2C_Read((UINT32*)&glink_109_bx);
	VPORT_I2C_Read((UINT32*)&glink_108_bx); //AVI data 11
	VPORT_I2C_Read((UINT32*)&glink_107_bx);
/*
	VPORT_I2C_Read((UINT32*)&glink_106_bx);
	VPORT_I2C_Read((UINT32*)&glink_105_bx);
	VPORT_I2C_Read((UINT32*)&glink_104_bx);
	VPORT_I2C_Read((UINT32*)&glink_103_bx);
	VPORT_I2C_Read((UINT32*)&glink_102_bx);
	VPORT_I2C_Read((UINT32*)&glink_101_bx);
	VPORT_I2C_Read((UINT32*)&glink_100_bx);
	VPORT_I2C_Read((UINT32*)&glink_99_bx);
	VPORT_I2C_Read((UINT32*)&glink_98_bx);
	VPORT_I2C_Read((UINT32*)&glink_97_bx);
	VPORT_I2C_Read((UINT32*)&glink_96_bx);
	VPORT_I2C_Read((UINT32*)&glink_95_bx);
	VPORT_I2C_Read((UINT32*)&glink_94_bx);
	VPORT_I2C_Read((UINT32*)&glink_93_bx); //AVI data 27
*/

	//Y1Y0
	tmp8 = glink_119_bx.reg_pkt_avi_dat_pip0_1;
	packet->eAviPacket.ePixelEncoding = _gCurPixelEncoding = _gPrevAVIPacket.eAviPacket.ePixelEncoding = (tmp8& 0x60)>>5;

	//A0
	tmp8 = glink_119_bx.reg_pkt_avi_dat_pip0_1;
	packet->eAviPacket.eActiveInfo = _gPrevAVIPacket.eAviPacket.eActiveInfo = (tmp8& 0x10)>>4;

	//B1B0
	tmp8 = glink_119_bx.reg_pkt_avi_dat_pip0_1;
	packet->eAviPacket.eBarInfo = _gPrevAVIPacket.eAviPacket.eBarInfo = (tmp8& 0x0C)>>2;

	//S1S0
	tmp8 = glink_119_bx.reg_pkt_avi_dat_pip0_1;
	packet->eAviPacket.eScanInfo = _gPrevAVIPacket.eAviPacket.eScanInfo = (tmp8& 0x03);

	//C1C0
	tmp8 = glink_118_bx.reg_pkt_avi_dat_pip0_2;
	packet->eAviPacket.eColorimetry = _gPrevAVIPacket.eAviPacket.eColorimetry = (tmp8& 0xC0)>>6;

	//M1M0
	tmp8 = glink_118_bx.reg_pkt_avi_dat_pip0_2;
	packet->eAviPacket.ePictureAspectRatio = _gPrevAVIPacket.eAviPacket.ePictureAspectRatio = (tmp8& 0x30)>>4;

	//R3R2R1R0
	tmp8 = glink_118_bx.reg_pkt_avi_dat_pip0_2;
	packet->eAviPacket.eActiveFormatAspectRatio = _gPrevAVIPacket.eAviPacket.eActiveFormatAspectRatio =(tmp8& 0x0F);

	//ITC
	tmp8 = glink_117_bx.reg_pkt_avi_dat_pip0_3;
	packet->eAviPacket.eITContent = _gPrevAVIPacket.eAviPacket.eITContent = (tmp8& 0x80)>>7;

	//EC2EC1EC0
	tmp8 = glink_117_bx.reg_pkt_avi_dat_pip0_3;
	packet->eAviPacket.eExtendedColorimetry = _gPrevAVIPacket.eAviPacket.eExtendedColorimetry = (tmp8& 0x70)>>4;

	//Q1Q0
	tmp8 = glink_117_bx.reg_pkt_avi_dat_pip0_3;
	packet->eAviPacket.eRGBQuantizationRange = _gPrevAVIPacket.eAviPacket.eRGBQuantizationRange = (tmp8& 0x0C)>>2;

	//SC1SC0
	tmp8 = glink_117_bx.reg_pkt_avi_dat_pip0_3;
	packet->eAviPacket.eScaling = _gPrevAVIPacket.eAviPacket.eScaling = (tmp8& 0x03);

	//VIC6~VIC0
	tmp8 = glink_116_bx.reg_pkt_avi_dat_pip0_4;
	packet->eAviPacket.VideoIdCode = _gPrevAVIPacket.eAviPacket.VideoIdCode = (tmp8& 0x7F);

	//YQ1YQ0
	tmp8 = glink_115_bx.reg_pkt_avi_dat_pip0_5;
	packet->eAviPacket.eYCCQuantizationRange = _gPrevAVIPacket.eAviPacket.eYCCQuantizationRange = (tmp8& 0xC0)>>6;

	//CN1CN0
	tmp8 = glink_115_bx.reg_pkt_avi_dat_pip0_5;
	packet->eAviPacket.eContentType = _gPrevAVIPacket.eAviPacket.eContentType = (tmp8& 0x30)>>4;

	//PR3PR2PR1PR0
	tmp8 = glink_115_bx.reg_pkt_avi_dat_pip0_5;
	packet->eAviPacket.PixelRepeat = _gPrevAVIPacket.eAviPacket.PixelRepeat = (tmp8& 0x0F);

	//Line Number of End of Top Bar
	tmp16 = glink_113_bx.reg_pkt_avi_dat_pip0_7;
	tmp16 = tmp16 << 8;
	tmp16 = tmp16 | glink_114_bx.reg_pkt_avi_dat_pip0_6;
	packet->eAviPacket.TopBarEndLineNumber = _gPrevAVIPacket.eAviPacket.TopBarEndLineNumber = tmp16;

	//Line Number of Start of Bottom Bar
	tmp16 = glink_111_bx.reg_pkt_avi_dat_pip0_9;
	tmp16 = tmp16 << 8;
	tmp16 = tmp16 | glink_112_bx.reg_pkt_avi_dat_pip0_8;
	packet->eAviPacket.BottomBarStartLineNumber = _gPrevAVIPacket.eAviPacket.BottomBarStartLineNumber = tmp16;

	//Pixel Number of End of Left Bar
	tmp16 = glink_109_bx.reg_pkt_avi_dat_pip0_11;
	tmp16 = tmp16 << 8;
	tmp16 = tmp16 | glink_110_bx.reg_pkt_avi_dat_pip0_10;
	packet->eAviPacket.LeftBarEndPixelNumber = _gPrevAVIPacket.eAviPacket.LeftBarEndPixelNumber = tmp16;

	//Pixel Number of Start of Right Bar
	tmp16 = glink_107_bx.reg_pkt_avi_dat_pip0_13;
	tmp16 = tmp16 << 8;
	tmp16 = tmp16 | glink_108_bx.reg_pkt_avi_dat_pip0_12;
	packet->eAviPacket.RightBarEndPixelNumber = _gPrevAVIPacket.eAviPacket.RightBarEndPixelNumber = tmp16;

	packet->eAviPacket.packet.type = _gPrevAVIPacket.eAviPacket.packet.type = 0x82;
	packet->eAviPacket.packet.version = _gPrevAVIPacket.eAviPacket.packet.version = glink_92_bx.reg_pkt_avi_hdr_pip0_0;
	packet->eAviPacket.packet.length = _gPrevAVIPacket.eAviPacket.packet.length = glink_91_bx.reg_pkt_avi_hdr_pip0_1 & 0x1F;

	packet->eAviPacket.packet.dataBytes[0] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[0] = glink_120_bx.reg_pkt_avi_dat_pip0_0;
	packet->eAviPacket.packet.dataBytes[1] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[1] = glink_119_bx.reg_pkt_avi_dat_pip0_1;
	packet->eAviPacket.packet.dataBytes[2] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[2] = glink_118_bx.reg_pkt_avi_dat_pip0_2;
	packet->eAviPacket.packet.dataBytes[3] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[3] = glink_117_bx.reg_pkt_avi_dat_pip0_3;
	packet->eAviPacket.packet.dataBytes[4] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[4] = glink_116_bx.reg_pkt_avi_dat_pip0_4;
	packet->eAviPacket.packet.dataBytes[5] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[5] = glink_115_bx.reg_pkt_avi_dat_pip0_5;
	packet->eAviPacket.packet.dataBytes[6] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[6] = glink_114_bx.reg_pkt_avi_dat_pip0_6;
	packet->eAviPacket.packet.dataBytes[7] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[7] = glink_113_bx.reg_pkt_avi_dat_pip0_7;
	packet->eAviPacket.packet.dataBytes[8] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[8] = glink_112_bx.reg_pkt_avi_dat_pip0_8;
	packet->eAviPacket.packet.dataBytes[9] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[9] = glink_111_bx.reg_pkt_avi_dat_pip0_9;
	packet->eAviPacket.packet.dataBytes[10] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[10] = glink_110_bx.reg_pkt_avi_dat_pip0_10;
	packet->eAviPacket.packet.dataBytes[11] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[11] = glink_109_bx.reg_pkt_avi_dat_pip0_11;
	packet->eAviPacket.packet.dataBytes[12] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[12] = glink_108_bx.reg_pkt_avi_dat_pip0_12;
	packet->eAviPacket.packet.dataBytes[13] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[13] = glink_107_bx.reg_pkt_avi_dat_pip0_13;
/*
	packet->eAviPacket.packet.dataBytes[14] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[14] = glink_106_bx.reg_pkt_avi_dat_pip0_14;
	packet->eAviPacket.packet.dataBytes[15] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[15] = glink_105_bx.reg_pkt_avi_dat_pip0_15;
	packet->eAviPacket.packet.dataBytes[16] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[16] = glink_104_bx.reg_pkt_avi_dat_pip0_16;
	packet->eAviPacket.packet.dataBytes[17] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[17] = glink_103_bx.reg_pkt_avi_dat_pip0_17;
	packet->eAviPacket.packet.dataBytes[18] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[18] = glink_102_bx.reg_pkt_avi_dat_pip0_18;
	packet->eAviPacket.packet.dataBytes[19] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[19] = glink_101_bx.reg_pkt_avi_dat_pip0_19;
	packet->eAviPacket.packet.dataBytes[20] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[20] = glink_100_bx.reg_pkt_avi_dat_pip0_20;
	packet->eAviPacket.packet.dataBytes[21] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[21] = glink_99_bx.reg_pkt_avi_dat_pip0_21;
	packet->eAviPacket.packet.dataBytes[22] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[22] = glink_98_bx.reg_pkt_avi_dat_pip0_22;
	packet->eAviPacket.packet.dataBytes[23] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[23] = glink_97_bx.reg_pkt_avi_dat_pip0_23;
	packet->eAviPacket.packet.dataBytes[24] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[24] = glink_96_bx.reg_pkt_avi_dat_pip0_24;
	packet->eAviPacket.packet.dataBytes[25] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[25] = glink_95_bx.reg_pkt_avi_dat_pip0_25;
	packet->eAviPacket.packet.dataBytes[26] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[26] = glink_94_bx.reg_pkt_avi_dat_pip0_26;
	packet->eAviPacket.packet.dataBytes[27] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[27] = glink_93_bx.reg_pkt_avi_dat_pip0_27;
*/
	OS_LockMutex(&g_HDMI_Sema);
	VPORT_I2C_Read((UINT32*)&glink_1_bx);
	gBootData->mode = glink_1_bx.reg_hdmi_mode_pip0;
	OS_UnlockMutex(&g_HDMI_Sema);

	packet->eAviPacket.bHdmiMode = _gPrevAVIPacket.eAviPacket.bHdmiMode = gBootData->mode;

	_HDMI_L9_SetRGBYCbCr(&_gCurPixelEncoding);

#ifdef VIDEO_DEBUG
	HDMI_DEBUG("--- %s[%d] AVI Info Read  CSC = %d\n",  __func__, __LINE__, _gCurPixelEncoding);
#endif

	return 0;

func_exit:
	packet->eAviPacket.ePixelEncoding = _gCurPixelEncoding = _gPrevAVIPacket.eAviPacket.ePixelEncoding;
	packet->eAviPacket.eActiveInfo = _gPrevAVIPacket.eAviPacket.eActiveInfo;
	packet->eAviPacket.eBarInfo = _gPrevAVIPacket.eAviPacket.eBarInfo;
	packet->eAviPacket.eScanInfo = _gPrevAVIPacket.eAviPacket.eScanInfo;
	packet->eAviPacket.eColorimetry = _gPrevAVIPacket.eAviPacket.eColorimetry;
	packet->eAviPacket.ePictureAspectRatio = _gPrevAVIPacket.eAviPacket.ePictureAspectRatio;
	packet->eAviPacket.eActiveFormatAspectRatio = _gPrevAVIPacket.eAviPacket.eActiveFormatAspectRatio;
	packet->eAviPacket.eITContent = _gPrevAVIPacket.eAviPacket.eITContent;
	packet->eAviPacket.eExtendedColorimetry = _gPrevAVIPacket.eAviPacket.eExtendedColorimetry;
	packet->eAviPacket.eRGBQuantizationRange = _gPrevAVIPacket.eAviPacket.eRGBQuantizationRange;
	packet->eAviPacket.eScaling = _gPrevAVIPacket.eAviPacket.eScaling;
	packet->eAviPacket.VideoIdCode = _gPrevAVIPacket.eAviPacket.VideoIdCode;
	packet->eAviPacket.eYCCQuantizationRange = _gPrevAVIPacket.eAviPacket.eYCCQuantizationRange;
	packet->eAviPacket.eContentType = _gPrevAVIPacket.eAviPacket.eContentType;
	packet->eAviPacket.PixelRepeat = _gPrevAVIPacket.eAviPacket.PixelRepeat;
	packet->eAviPacket.TopBarEndLineNumber = _gPrevAVIPacket.eAviPacket.TopBarEndLineNumber;
	packet->eAviPacket.BottomBarStartLineNumber = _gPrevAVIPacket.eAviPacket.BottomBarStartLineNumber;
	packet->eAviPacket.LeftBarEndPixelNumber = _gPrevAVIPacket.eAviPacket.LeftBarEndPixelNumber;
	packet->eAviPacket.RightBarEndPixelNumber = _gPrevAVIPacket.eAviPacket.RightBarEndPixelNumber;
	packet->eAviPacket.packet.type = _gPrevAVIPacket.eAviPacket.packet.type;
	packet->eAviPacket.packet.version = _gPrevAVIPacket.eAviPacket.packet.version;
	packet->eAviPacket.packet.length = _gPrevAVIPacket.eAviPacket.packet.length;
	packet->eAviPacket.packet.dataBytes[0] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[0];
	packet->eAviPacket.packet.dataBytes[1] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[1];
	packet->eAviPacket.packet.dataBytes[2] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[2];
	packet->eAviPacket.packet.dataBytes[3] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[3];
	packet->eAviPacket.packet.dataBytes[4] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[4];
	packet->eAviPacket.packet.dataBytes[5] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[5];
	packet->eAviPacket.packet.dataBytes[6] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[6];
	packet->eAviPacket.packet.dataBytes[7] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[7];
	packet->eAviPacket.packet.dataBytes[8] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[8];
	packet->eAviPacket.packet.dataBytes[9] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[9];
	packet->eAviPacket.packet.dataBytes[10] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[10];
	packet->eAviPacket.packet.dataBytes[11] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[11];
	packet->eAviPacket.packet.dataBytes[12] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[12];
	packet->eAviPacket.packet.dataBytes[13] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[13];
/*
	packet->eAviPacket.packet.dataBytes[14] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[14];
	packet->eAviPacket.packet.dataBytes[15] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[15];
	packet->eAviPacket.packet.dataBytes[16] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[16];
	packet->eAviPacket.packet.dataBytes[17] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[17];
	packet->eAviPacket.packet.dataBytes[18] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[18];
	packet->eAviPacket.packet.dataBytes[19] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[19];
	packet->eAviPacket.packet.dataBytes[20] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[20];
	packet->eAviPacket.packet.dataBytes[21] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[21];
	packet->eAviPacket.packet.dataBytes[22] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[22];
	packet->eAviPacket.packet.dataBytes[23] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[23];
	packet->eAviPacket.packet.dataBytes[24] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[24];
	packet->eAviPacket.packet.dataBytes[25] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[25];
	packet->eAviPacket.packet.dataBytes[26] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[26];
	packet->eAviPacket.packet.dataBytes[27] = _gPrevAVIPacket.eAviPacket.packet.dataBytes[27];
*/
	packet->eAviPacket.bHdmiMode = _gPrevAVIPacket.eAviPacket.bHdmiMode;

	return 0;
}

/**
* HDMI_L9Bx_GetSpdPacket
*
* @parm LX_HDMI_SPD_PACKET_T
* @return int
*/
int HDMI_L9_GetSpdPacket(LX_HDMI_SPD_PACKET_T *packet)
{
	UINT8 count = 0;
	AI2C_DATA_T r;

	HDMI_PRINT("%s: Get SPD Packet", __func__);

	memset((void *)packet , 0 , sizeof(LX_HDMI_SPD_PACKET_T));

	if (!_gSCDT)
	{
		memset(&_gPrevSPDPacket, 0 , sizeof(LX_HDMI_SPD_PACKET_T));
		return 0;
	}

	VPORT_I2C_Read((UINT32*)&glink_272_bx);
	VPORT_I2C_Read((UINT32*)&glink_271_bx);
	VPORT_I2C_Read((UINT32*)&glink_270_bx);
	VPORT_I2C_Read((UINT32*)&glink_269_bx);
	VPORT_I2C_Read((UINT32*)&glink_268_bx);

	memcpy(&r, &glink_272_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevSPDPacket.VendorName[0] )	count++;
	memcpy(&r, &glink_271_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevSPDPacket.VendorName[1] )	count++;
	memcpy(&r, &glink_270_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevSPDPacket.VendorName[2] )	count++;
	memcpy(&r, &glink_269_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevSPDPacket.VendorName[3] )	count++;
	memcpy(&r, &glink_268_bx, sizeof(AI2C_DATA_T));
	if( r.data == _gPrevSPDPacket.VendorName[4] )	count++;

	if(count == 5)	// same pre VSI Packet
	{
#ifdef VIDEO_DEBUG
		//HDMI_DEBUG(" HDMI_L9Bx_GetSpdPacket  Same---------- Same\n");	//ATSC 에서 호출
#endif
		goto func_exit;
	}

	VPORT_I2C_Read((UINT32*)&glink_244_bx);  /* HDR_1 - Length of Source Product Description InfoFrame */
	VPORT_I2C_Read((UINT32*)&glink_245_bx);  /* HDR_0 - InfoFrame Version */
	//VPORT_I2C_Read((UINT32*)&glink_273_bx);  /* Checksum */

	if(glink_244_bx.reg_pkt_spd_hdr_pip0_1 == 0 && glink_245_bx.reg_pkt_spd_hdr_pip0_0 == 0)
	{
		memset(&_gPrevSPDPacket, 0 , sizeof(LX_HDMI_SPD_PACKET_T));
#ifdef VIDEO_DEBUG
		HDMI_DEBUG("--- %s[%d] SPD No Packet \n", __func__, __LINE__);
#endif
		goto func_exit;
	}

	VPORT_I2C_Read((UINT32*)&glink_267_bx);
	VPORT_I2C_Read((UINT32*)&glink_266_bx);
	VPORT_I2C_Read((UINT32*)&glink_265_bx);
	VPORT_I2C_Read((UINT32*)&glink_264_bx);
	VPORT_I2C_Read((UINT32*)&glink_263_bx);
	VPORT_I2C_Read((UINT32*)&glink_262_bx);
	VPORT_I2C_Read((UINT32*)&glink_261_bx);
	VPORT_I2C_Read((UINT32*)&glink_260_bx);
	VPORT_I2C_Read((UINT32*)&glink_259_bx);
	VPORT_I2C_Read((UINT32*)&glink_258_bx);
	VPORT_I2C_Read((UINT32*)&glink_257_bx);
	VPORT_I2C_Read((UINT32*)&glink_256_bx);
	VPORT_I2C_Read((UINT32*)&glink_255_bx);
	VPORT_I2C_Read((UINT32*)&glink_254_bx);
	VPORT_I2C_Read((UINT32*)&glink_253_bx);
	VPORT_I2C_Read((UINT32*)&glink_252_bx);
	VPORT_I2C_Read((UINT32*)&glink_251_bx);
	VPORT_I2C_Read((UINT32*)&glink_250_bx);
	VPORT_I2C_Read((UINT32*)&glink_249_bx);
	VPORT_I2C_Read((UINT32*)&glink_248_bx);

	packet->VendorName[0] = _gPrevSPDPacket.VendorName[0] = glink_272_bx.reg_pkt_spd_dat_pip0_1;
	packet->VendorName[1] = _gPrevSPDPacket.VendorName[1] = glink_271_bx.reg_pkt_spd_dat_pip0_2;
	packet->VendorName[2] = _gPrevSPDPacket.VendorName[2] = glink_270_bx.reg_pkt_spd_dat_pip0_3;
	packet->VendorName[3] = _gPrevSPDPacket.VendorName[3] = glink_269_bx.reg_pkt_spd_dat_pip0_4;
	packet->VendorName[4] = _gPrevSPDPacket.VendorName[4] = glink_268_bx.reg_pkt_spd_dat_pip0_5;
	packet->VendorName[5] = _gPrevSPDPacket.VendorName[5] = glink_267_bx.reg_pkt_spd_dat_pip0_6;
	packet->VendorName[6] = _gPrevSPDPacket.VendorName[6] = glink_266_bx.reg_pkt_spd_dat_pip0_7;
	packet->VendorName[7] = _gPrevSPDPacket.VendorName[7] = glink_265_bx.reg_pkt_spd_dat_pip0_8;

	packet->ProductDescription[0] = _gPrevSPDPacket.ProductDescription[0] = glink_264_bx.reg_pkt_spd_dat_pip0_9;
	packet->ProductDescription[1] = _gPrevSPDPacket.ProductDescription[1] = glink_263_bx.reg_pkt_spd_dat_pip0_10;
	packet->ProductDescription[2] = _gPrevSPDPacket.ProductDescription[2] = glink_262_bx.reg_pkt_spd_dat_pip0_11;
	packet->ProductDescription[3] = _gPrevSPDPacket.ProductDescription[3] = glink_261_bx.reg_pkt_spd_dat_pip0_12;
	packet->ProductDescription[4] = _gPrevSPDPacket.ProductDescription[4] = glink_260_bx.reg_pkt_spd_dat_pip0_13;
	packet->ProductDescription[5] = _gPrevSPDPacket.ProductDescription[5] = glink_259_bx.reg_pkt_spd_dat_pip0_14;
	packet->ProductDescription[6] = _gPrevSPDPacket.ProductDescription[6] = glink_258_bx.reg_pkt_spd_dat_pip0_15;
	packet->ProductDescription[7] = _gPrevSPDPacket.ProductDescription[7] = glink_257_bx.reg_pkt_spd_dat_pip0_16;
	packet->ProductDescription[8] = _gPrevSPDPacket.ProductDescription[8] = glink_256_bx.reg_pkt_spd_dat_pip0_17;
	packet->ProductDescription[9] = _gPrevSPDPacket.ProductDescription[9] = glink_255_bx.reg_pkt_spd_dat_pip0_18;
	packet->ProductDescription[10] = _gPrevSPDPacket.ProductDescription[10] = glink_254_bx.reg_pkt_spd_dat_pip0_19;
	packet->ProductDescription[11] = _gPrevSPDPacket.ProductDescription[11] = glink_253_bx.reg_pkt_spd_dat_pip0_20;
	packet->ProductDescription[12] = _gPrevSPDPacket.ProductDescription[12] = glink_252_bx.reg_pkt_spd_dat_pip0_21;
	packet->ProductDescription[13] = _gPrevSPDPacket.ProductDescription[13] = glink_251_bx.reg_pkt_spd_dat_pip0_22;
	packet->ProductDescription[14] = _gPrevSPDPacket.ProductDescription[14] = glink_250_bx.reg_pkt_spd_dat_pip0_23;
	packet->ProductDescription[15] = _gPrevSPDPacket.ProductDescription[15] = glink_249_bx.reg_pkt_spd_dat_pip0_24;

	packet->SourceDeviceInfo = _gPrevSPDPacket.SourceDeviceInfo = glink_248_bx.reg_pkt_spd_dat_pip0_25;
#ifdef VIDEO_DEBUG
	HDMI_DEBUG(" HDMI_L9_GetSpdPacket  Read \n");
#endif
	return 0;

func_exit:

	packet->VendorName[0] = _gPrevSPDPacket.VendorName[0];
	packet->VendorName[1] = _gPrevSPDPacket.VendorName[1];
	packet->VendorName[2] = _gPrevSPDPacket.VendorName[2];
	packet->VendorName[3] = _gPrevSPDPacket.VendorName[3];
	packet->VendorName[4] = _gPrevSPDPacket.VendorName[4];
	packet->VendorName[5] = _gPrevSPDPacket.VendorName[5];
	packet->VendorName[6] = _gPrevSPDPacket.VendorName[6];
	packet->VendorName[7] = _gPrevSPDPacket.VendorName[7];

	packet->ProductDescription[0] = _gPrevSPDPacket.ProductDescription[0];
	packet->ProductDescription[1] = _gPrevSPDPacket.ProductDescription[1];
	packet->ProductDescription[2] = _gPrevSPDPacket.ProductDescription[2];
	packet->ProductDescription[3] = _gPrevSPDPacket.ProductDescription[3];
	packet->ProductDescription[4] = _gPrevSPDPacket.ProductDescription[4];
	packet->ProductDescription[5] = _gPrevSPDPacket.ProductDescription[5];
	packet->ProductDescription[6] = _gPrevSPDPacket.ProductDescription[6];
	packet->ProductDescription[7] = _gPrevSPDPacket.ProductDescription[7];
	packet->ProductDescription[8] = _gPrevSPDPacket.ProductDescription[8];
	packet->ProductDescription[9] = _gPrevSPDPacket.ProductDescription[9];
	packet->ProductDescription[10] = _gPrevSPDPacket.ProductDescription[10];
	packet->ProductDescription[11] = _gPrevSPDPacket.ProductDescription[11];
	packet->ProductDescription[12] = _gPrevSPDPacket.ProductDescription[12];
	packet->ProductDescription[13] = _gPrevSPDPacket.ProductDescription[13];
	packet->ProductDescription[14] = _gPrevSPDPacket.ProductDescription[14];
	packet->ProductDescription[15] = _gPrevSPDPacket.ProductDescription[15];

	packet->SourceDeviceInfo = _gPrevSPDPacket.SourceDeviceInfo;
	return 0;
}

/**
* HDMI_L9Bx_SetHPDEnDisable
*
* @parm LX_HDMI_HPD_T
* @return int
*/
int HDMI_L9_SetHPD(LX_HDMI_HPD_T *hpd)
{
// end (need check HPD_out_enable) 201108
	VPORT_I2C_Read((UINT32*)&ghpd_out_control_0_bx);

	if(hpd->bEnable == 1)
		ghpd_out_control_0_bx.hpd0_out = 0;
	else
		ghpd_out_control_0_bx.hpd0_out = 1;
	ghpd_out_control_0_bx.hpd0_oen = 1;

	VPORT_I2C_Write((UINT32*)&ghpd_out_control_0_bx);

	return 0;
}

/**
* HDMI_L9Bx_SetPort
* L9B0 has 1 port.
* @parm
* @return int
*/
int HDMI_L9_SetPort(UINT32 *hpd)
{
#ifdef	KDRV_CONFIG_PM
	memcpy( (void *)&gstPmPortSel , (void *)hpd , sizeof(LX_HDMI_HPD_T) );
#endif


	/* HDMI Link Reset - Video Format Info.*/
	_HDMI_L9_ClearResetLink(1);

	/* Port	Power down control */
	HDMI_L9_SetPowerControl(0);

	// try to do power on without status check
	HDMI_L9_SetPowerControl(1);

	//OS_MsecSleep(50);

	// All Link Reset Clear
	_HDMI_L9_ClearResetLink(0);

	return 0;
}

/**
* HDMI_L9Bx_SetPowerDown
*
* @parm HDMI_PHY_TYPE_T
* @return int
*/
int HDMI_L9_SetPowerControl(UINT32 power)
{
	BOOLEAN	pdb = 0;

	if(power == 0) // Power down
		pdb = 0;
	else	// power up
		pdb = 1;

	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_01_bx);
	ghdmi_phy_n_01_bx.resetb_all = pdb;
	ghdmi_phy_n_01_bx.pdb_all = pdb;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_01_bx);

	HDMI_PRINT("HDMI_L9_SetPowerControl [%s] \n", power?"Power Up":"Power Down");

	return 0;
}

int HDMI_L9_RunReset(void)
{
	// hdmi link Reset - All Clear
	_HDMI_L9_ClearSWResetAll();

	// DR Capacitance Selection
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_82_bx);
	ghdmi_phy_n_82_bx.dr_mode = 1;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_82_bx);

	// PLL_Mode_Sel Auto Reset
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_12_bx);
	ghdmi_phy_n_12_bx.cr_test = 1;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_12_bx);

	// HDMI Current Default value 2(60uA)- Use 60uA for L9 by sunghyun.yang 2011-04-29
	//VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_25_bx);
	//ghdmi_phy_n_25_bx.idr_adj = 2;
	//VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_25_bx);

	//HDMI_L9A0_ADAPTIVE_LOOP
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_41_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_43_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_44_bx);

	ghdmi_phy_n_41_bx.eq_cs_sel = 0;
	ghdmi_phy_n_41_bx.eq_rs_sel = 0;
	ghdmi_phy_n_43_bx.eq_rs = 3;
	ghdmi_phy_n_44_bx.eq_cs = 3;

	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_41_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_43_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_44_bx);

	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_45_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_46_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_47_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_48_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_4b_bx);
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_4c_bx);

	ghdmi_phy_n_45_bx.eq_thr_h = 6;
	ghdmi_phy_n_46_bx.eq_thr_l = 12;
	ghdmi_phy_n_47_bx.eq_tot_h = 7;
	ghdmi_phy_n_48_bx.eq_tot_l = 15;
	ghdmi_phy_n_4b_bx.eq_start_frz = 20;
	ghdmi_phy_n_4c_bx.eq_avg_width = 0;		// HDCP Problem to the Master

	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_45_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_46_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_47_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_48_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_4b_bx);
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_4c_bx);

	//2012-02-12 sh.myoung
	// 특정 ACE Chip 에서 Demod 동작 여부에 Phy TMDS Decoder와 HDMI Link 사이의 Data timing 영향 받음.
	// The margin  of No inversion : 600ps -> The margin of inversion : 2.1ns
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_a4_bx);
	ghdmi_phy_n_a4_bx.tmds_clk_inv = 1;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_a4_bx);

	// for UD and 3D_SS_Full format
	VPORT_I2C_Read((UINT32*)&glink_345_bx);
	glink_345_bx.reg_neg_pol_en_pip0 = 0;
	VPORT_I2C_Write((UINT32*)&glink_345_bx);

	// HPD PIN Control Enable
	VPORT_I2C_Read((UINT32*)&ghpd_out_control_0_bx);
	ghpd_out_control_0_bx.hpd0_oen = 0;
	VPORT_I2C_Write((UINT32*)&ghpd_out_control_0_bx);

	// Video Path Auto Configuration Enable(default = 1)
	//VPORT_I2C_Read((UINT32*)&glink_2_bx);
	//glink_2_bx_bx.reg_avc_en_pip0 = 1;
	//VPORT_I2C_Read((UINT32*)&glink_2_bx);

	// not used hdcp key ROM
	VPORT_I2C_Read((UINT32*)&glink_818_bx);
	glink_818_bx.reg_dbg_hdcp_key_bak = 0;
	VPORT_I2C_Write((UINT32*)&glink_818_bx);

	return 0;
}


int HDMI_L9_HWInitial(void)
{
	//Initialize HDMI semaphore
	OS_InitMutex(&g_HDMI_Sema, OS_SEM_ATTR_DEFAULT);

	// Enable HDMI Internal PHY and I2C for L9A

	/* PHY0_PHY_PDB=1, PHY0_PHY_RSTN=1 을 동시에 인가시 내부 Regulator가 Final Value까지 올라가기도 전에 RSTN이 풀리므로
	 * Regulator를 전원으로 사용하는 Register들이 제대로 pre-set되지 않는 현상이 생기는 것으로 판단됨. by sunghyun.yang 2011.06.14
	 */

	/* WARN!!! If hdmiphy1_sdaout_enable is set to 1
	 * with powerdown mode off, it will affect other blocks.
	 * PHY_SDA_O Enable이 B0 에서 ghpd_out_control_1로 변경 됨.
	 */
	VPORT_I2C_Read((UINT32*)&ghpd_out_control_1_bx);
	ghpd_out_control_1_bx.phy0_phy_pdb = 1;
	VPORT_I2C_Write((UINT32*)&ghpd_out_control_1_bx);
	OS_MsecSleep(5);	// ms delay

	VPORT_I2C_Read((UINT32*)&ghpd_out_control_1_bx);
	if ( lx_ace_rev() == LX_CHIP_REV(L9,B0) )
	{
		ghpd_out_control_1_bx.phy_enable = 0;		// phy_sda_o Enable
		HDMI_DEBUG(" ACE HDMI L9 B0 \n");
	}
	else
	{
		ghpd_out_control_1_bx.phy_enable = 1;		// phy_sda_o Enable
		HDMI_DEBUG(" ACE HDMI L9 B1/B2 \n");
	}
	VPORT_I2C_Write((UINT32*)&ghpd_out_control_1_bx);
	//OS_MsecSleep(5);	// ms delay

	VPORT_I2C_Read((UINT32*)&ghpd_out_control_1_bx);
	ghpd_out_control_1_bx.phy0_phy_rstn = 1;
	VPORT_I2C_Write((UINT32*)&ghpd_out_control_1_bx);

	// Internal I2C for PHY
	VPORT_I2C_Read((UINT32*)&gaudio_pll_5_bx);
	gaudio_pll_5_bx.phy_i2c_sel = 1;
	VPORT_I2C_Write((UINT32*)&gaudio_pll_5_bx);

	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_02_bx);
	ghdmi_phy_n_02_bx.pdb_sel = 1;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_02_bx);
/*
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_01_bx);
	ghdmi_phy_n_01_bx.pdb_all = 0;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_01_bx);

	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_01_bx);
	ghdmi_phy_n_01_bx.pdb_all = 1;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_01_bx);
*/
	HDMI_L9_RunReset();

	// audio setting
	HDMI_L9_SetAudio();

	HDMI_L9_EnableInterrupt();
	HDMI_DEBUG("L9 HDMI Initialize \n" );
	return 0;
}

static int _HDMI_L9_Set3DFullTimingInfo(LX_HDMI_TIMING_INFO_T *info)
{
	int ret = 0;
	UINT8 tmp8 = 0, vic = 0;

	LX_HDMI_TIMING_INFO_T 	bufTiming = {0,};
	LX_HDMI_VSI_VIDEO_FORMAT_T eVideoFormat;	/**< HDMI VSI info */
	LX_HDMI_VSI_3D_STRUCTURE_T e3DStructure;	/**< HDMI VSI info */

	info->extInfo = LX_HDMI_EXT_2D_FORMAT;

	memcpy(&bufTiming , info , sizeof(LX_HDMI_TIMING_INFO_T));

	/**< HDMI VSI info */
	VPORT_I2C_Read((UINT32*)&glink_330_bx);
	VPORT_I2C_Read((UINT32*)&glink_329_bx);

	tmp8 = glink_330_bx.reg_pkt_vsi_dat_pip0_4;
	eVideoFormat = (tmp8 & 0xE0) >> 5;

	tmp8 = glink_329_bx.reg_pkt_vsi_dat_pip0_5;
	e3DStructure = (tmp8 & 0xF0) >> 4;

	HDMI_PRINT(" Timinginfo   eVideoFormat = %d //  buf e3DStructure = %d \n\n", eVideoFormat, e3DStructure);

	if(eVideoFormat == LX_FORMAT_NO_ADDITIONAL_FORMAT)
	{
		bufTiming.extInfo = LX_HDMI_EXT_2D_FORMAT;		///< 2D format
/*
		if( (bufTiming.hActive == 1280)	&& 	(bufTiming.vActive == 1470) && (bufTiming.scanType == 1))
		{
			bufTiming.vActive = 720;
			bufTiming.full_3d_timing = LX_HDMI_EXT_3D_FRAMEPACK;
		}

		if( (bufTiming.hActive == 1920)	&& 	(bufTiming.vActive == 2228) && (bufTiming.scanType == 1))
		{
			bufTiming.vActive = 1080;
			bufTiming.scanType = 0;
			bufTiming.full_3d_timing = LX_HDMI_EXT_3D_FRAMEPACK;
		}

		if( (bufTiming.hActive == 1920)	&& 	(bufTiming.vActive == 2205) && (bufTiming.scanType == 1))
		{
			bufTiming.vActive = 1080;
			bufTiming.full_3d_timing = LX_HDMI_EXT_3D_FRAMEPACK;
		}

		if( (bufTiming.hActive == 1920)	&& 	(bufTiming.vActive == 1103) && (bufTiming.scanType == 1))
		{
			bufTiming.vActive = 1080;
			bufTiming.scanType = 0;
			bufTiming.full_3d_timing = LX_HDMI_EXT_3D_FIELD_ALTERNATIVE;
		}

		if( (bufTiming.hActive == 1920)	&& 	(bufTiming.vActive == 2160) && (bufTiming.scanType == 1))
		{
			bufTiming.vActive = 1080;
			bufTiming.full_3d_timing = LX_HDMI_EXT_3D_LINE_ALTERNATIVE;
		}

		if( (bufTiming.hActive == 2560)	&& 	(bufTiming.vActive == 720) && (bufTiming.scanType == 1))
		{
			bufTiming.hActive = 1280;
			bufTiming.full_3d_timing = LX_HDMI_EXT_3D_SBSFULL;
		}
*/
		goto func_exit;

	}
	else if(eVideoFormat == LX_FORMAT_3D_FORMAT)
	{
		if(e3DStructure < 2)
		{
			VPORT_I2C_Read((UINT32*)&glink_116_bx);
			vic = glink_116_bx.reg_pkt_avi_dat_pip0_4;		//VIC6~VIC0
			vic = (vic & 0x7F);

	 		if(vic == 5 || vic == 6 ||vic == 7 ||vic == 10 || vic == 11 || vic == 20 || vic == 21 ||
	 			vic == 22 || vic == 25 || vic == 26 || vic == 39 || vic == 40 || vic == 44 || vic == 45)		// 1080!@60Hz & 1080!@50Hz
				bufTiming.scanType = 0;

			HDMI_PRINT(" VIC  = %d \n", vic);
		}

		switch(e3DStructure)
		{
			case LX_HDMI_VSI_3D_STRUCTURE_FRAME_PACKING:
				bufTiming.extInfo = LX_HDMI_EXT_3D_FRAMEPACK;
				break;

			case LX_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE:
				bufTiming.extInfo = LX_HDMI_EXT_3D_FIELD_ALTERNATIVE;
				break;

			case LX_HDMI_VSI_3D_STRUCTURE_LINE_ALTERNATIVE:
				bufTiming.extInfo = LX_HDMI_EXT_3D_LINE_ALTERNATIVE;
				break;

			case LX_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_FULL:
				bufTiming.extInfo = LX_HDMI_EXT_3D_SBSFULL;
				break;

			default:
				 bufTiming.extInfo = e3DStructure;
				goto func_exit;
				break;
		}
	}
	else	 if(eVideoFormat == LX_FORMAT_EXTENDED_RESOLUTION_FORMAT)		// UD Format
		return ret;


	switch(bufTiming.extInfo)
	{
		case LX_HDMI_EXT_3D_FRAMEPACK:
		{

			if(vic == 0)
			{
				if( (bufTiming.vActive == 2228) ||(bufTiming.vActive == 1028) )		//1080i & 480i
				{
					bufTiming.scanType = 0;
					tmp8 = 68; //23+22+23
					bufTiming.vActive = (bufTiming.vActive - tmp8) >> 1;
				}
				else if(bufTiming.vActive == 1226)	//576i
				{
					bufTiming.scanType = 0;
					tmp8 = 74; //23+22+23
					bufTiming.vActive = (bufTiming.vActive - tmp8) >> 1;
				}
			}
			else
			{
				if(bufTiming.scanType)		//progressive
				{
					// Russia  STB Issue
					// VSI Info is 3D F/P and Source is 2D
					if( (bufTiming.hActive == 720 && bufTiming.vActive == 480) \
						|| (bufTiming.hActive == 720 && bufTiming.vActive == 576) \
						|| (bufTiming.hActive == 1280 && bufTiming.vActive == 720) \
						|| (bufTiming.hActive == 1920 && bufTiming.vActive == 1080) )
					{
						bufTiming.extInfo = LX_HDMI_EXT_2D_FORMAT;		///< 2D format
						break;
					}

					tmp8 = (bufTiming.vTotal - bufTiming.vActive);
					bufTiming.vActive = (bufTiming.vActive - tmp8) >> 1;
				}
				else					//interlace
				{
					if( (bufTiming.vActive == 2228) ||(bufTiming.vActive == 1028) )		//1080i & 480i
					{
						tmp8 = 68; //23+22+23
						bufTiming.vActive = (bufTiming.vActive - tmp8) >> 1;
					}
					else if(bufTiming.vActive == 1226)		//576i
					{
						tmp8 = 74; // 25+24+25
						bufTiming.vActive = (bufTiming.vActive - tmp8) >> 1;
					}
					else if((bufTiming.hActive == 1920) && (bufTiming.vActive == 1103))
					{
						tmp8 = 23; //23
						bufTiming.vActive = bufTiming.vActive - tmp8;
					}
					else
					{
						// Russia  STB Issue
						// VSI Info is 3D F/P and Source is 2D
						bufTiming.extInfo = LX_HDMI_EXT_2D_FORMAT;		///< 2D format
					}
				}
			}
		}	break;

		case LX_HDMI_EXT_3D_SBSFULL:
		{
			if(bufTiming.hTotal == 4608)/* Not support 1920x1080!@50 of EIA-861D */
			{
				memset(&bufTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));
			}
			else
				bufTiming.hActive = bufTiming.hActive >> 1;
		}	break;

		case LX_HDMI_EXT_3D_FIELD_ALTERNATIVE:
		{
			bufTiming.scanType = 0;

			if(bufTiming.vActive == 1103)		tmp8 = 23; //1080! - 22.5
			else if(bufTiming.vActive == 601) 	tmp8 = 25; //576! - 24.5
			else if(bufTiming.vActive == 503)	tmp8 = 23; //480! - 22.5
			else 								tmp8 = 0;

			bufTiming.vActive = bufTiming.vActive - tmp8;

			if(bufTiming.hTotal == 2304 && bufTiming.vTotal == 1250)/* Not support 1920x1080!@50 of EIA-861D */
			{
				memset(&bufTiming , 0 , sizeof(LX_HDMI_TIMING_INFO_T));
			}
		}	break;

		case LX_HDMI_EXT_3D_LINE_ALTERNATIVE:
		{
			bufTiming.vActive = bufTiming.vActive >> 1;
		}	break;

		default:
			break;
	}

func_exit:

#ifdef VIDEO_DEBUG
	if(_gTimingCnt < 6 && _gTimingCnt > 3)
	{
		HDMI_ERROR(" VIC  = %d [gpreAVI - %d] \n", vic, _gPrevAVIPacket.eAviPacket.VideoIdCode);
		HDMI_ERROR(" Timinginfo   buf hActive = %d // 	hActive = %d \n", bufTiming.hActive, info->hActive);
		HDMI_ERROR(" Timinginfo   buf vActive = %d // 	vActive = %d \n", bufTiming.vActive, info->vActive);
		HDMI_ERROR(" Timinginfo   buf scanType = %d //  scanType = %d \n", bufTiming.scanType, info->scanType);
		HDMI_ERROR(" Timinginfo   buf full_3d = %d //  full_3d = %d \n", bufTiming.extInfo, info->extInfo);
		HDMI_ERROR(" Timinginfo   full_3d([0]Normal[1]FP[2]SSF[3]FA[4]LA = %d \n", bufTiming.extInfo);
	}
#endif

	//info->hTotal			= bufTiming.hTotal; 			///< Horizontal total pixels
	//info->vTotal 			= bufTiming.vTotal; 			///< Vertical total lines
	//info->hStart			= bufTiming.hStart; 			///< Horizontal start pixel (Back Porch)
	//info->vStart 			= bufTiming.vStart;				///< Vertical start lines (Back Porch)
	info->hActive 			= bufTiming.hActive;			///< Horizontal active pixel
	info->vActive 			= bufTiming.vActive; 			///< Vertical active lines
	info->scanType 			= bufTiming.scanType; 			///< Scan type (0 : interlace, 1 : progressive) 	info->scanType ^= 1;
	info->extInfo	= bufTiming.extInfo; 	///< Full 3D Timing

	return ret;
}

/**
* HDMI_L9Bx_SetAudio
*
* @parm void
* @return int
*/
int HDMI_L9_SetAudio(void)
{
	VPORT_I2C_Read((UINT32*)&glink_0_bx);
	glink_0_bx.reg_arc_src_prt0 = 1;
	VPORT_I2C_Write((UINT32*)&glink_0_bx);

	//Channel 0
	VPORT_I2C_Read((UINT32*)&glink_1_bx);
	glink_1_bx.reg_aac_en_pip0 = 1;		//Auto Audio Path Configuration Enable(N, CTS value is auto configured.)
	VPORT_I2C_Write((UINT32*)&glink_1_bx);

	VPORT_I2C_Read((UINT32*)&glink_367_bx);
	glink_367_bx.reg_acr_en_pip0   = 1;		//ACR Enable(Audio Clock Generation Function Activation)
	glink_367_bx.reg_acr_n_fs_pip0 = 1;		//0 : 128Fs, 1 : 256 Fs, 2 : 512Fs(default : 256Fs)
	glink_367_bx.reg_acr_clk_aud_div_pip0 = 1;	//0 : 128Fs, 1 : 256 Fs, 2 : 512Fs(default : 256Fs)
	VPORT_I2C_Write((UINT32*)&glink_367_bx);

	VPORT_I2C_Read((UINT32*)&glink_368_bx);
	glink_368_bx.reg_acr_ncts_sel_pip0 = 0;		//Use N, CTS value for audio clock generation
	glink_368_bx.reg_acr_adj_thr_pip0 = 3;		//Threshold Value for Clock Frequency Auto Adjustment for proper FIFO running, not required
	glink_368_bx.reg_acr_adj_en_pip0 = 1;		//Enable Clock Frequency Auto Adjustment for proper FIFO running
	VPORT_I2C_Write((UINT32*)&glink_368_bx);

	VPORT_I2C_Read((UINT32*)&glink_383_bx);
	glink_383_bx.reg_i2s_sd_en_pip0   = 0xF;	//I2S SD Output Enable(4 Channel)
	glink_383_bx.reg_i2s_sd0_map_pip0 = 0;		//I2S SD 0 Output Channel Mappings
	VPORT_I2C_Write((UINT32*)&glink_383_bx);

	VPORT_I2C_Read((UINT32*)&glink_384_bx);
	glink_384_bx.reg_i2s_sd1_map_pip0 = 1;		//I2S SD 1 Output Channel Mappings
	glink_384_bx.reg_i2s_sd2_map_pip0 = 2;		//I2S SD 2 Output Channel Mappings
	glink_384_bx.reg_i2s_sd3_map_pip0 = 3;		//I2S SD 3 Output Channel Mappings
	VPORT_I2C_Write((UINT32*)&glink_384_bx);

	VPORT_I2C_Read((UINT32*)&glink_385_bx);
	glink_385_bx.reg_i2s_out_en_pip0 = 1;		//I2S Output Enable
	VPORT_I2C_Write((UINT32*)&glink_385_bx);

	VPORT_I2C_Read((UINT32 *)&glink_382_bx);
	glink_382_bx.reg_i2s_sck_edge_pip0 = 1;		//I2S Format for falling edge
	VPORT_I2C_Write((UINT32*)&glink_382_bx);

	return 0;
}

/**
 *  _HDMI_L9Bx_GetAudioTypeAndFreq
 *
 *  @return int
*/
static int _HDMI_L9_GetAudioTypeAndFreq(LX_HDMI_AUDIO_TYPE_T *audioType, LX_HDMI_SAMPLING_FREQ_T *samplingFreq)
{
	int ret = 0;

	//Check if audio sample word used for other purposes than liner PCM.
	VPORT_I2C_Read((UINT32*)&glink_387_bx);

	if(glink_387_bx.reg_achst_byte0_pip0 & HDMI_AUDIO_SAMPLE_NON_PCM_MASK)	//bit 1, 0 : PCM, 1 : non-PCM
	{
		//Check a vaild Pc data for payload
		VPORT_I2C_Read((UINT32*)&glink_394_bx);

		if((glink_394_bx.reg_burst_pc_pip0_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0) //bit 7, 0 : No Error, 1 : Error
		{
			//Set Audio Data-Types according to IEC61937-2 Burst Info Preamble C
			switch(glink_394_bx.reg_burst_pc_pip0_0 & BURST_INFO_AUDIO_TYPE_BIT_MASK)	//bit 4 ~ 0
			{
				case BURST_INFO_AUDIO_TYPE_AC3:
				case BURST_INFO_AUDIO_TYPE_AC3_ENHANCED:
					*audioType = LX_HDMI_AUDIO_AC3;
					break;

				case BURST_INFO_AUDIO_TYPE_DTS_I:
				case BURST_INFO_AUDIO_TYPE_DTS_II:
				case BURST_INFO_AUDIO_TYPE_DTS_III:
				case BURST_INFO_AUDIO_TYPE_DTS_IV:
					*audioType = LX_HDMI_AUDIO_DTS;
					break;

				case BURST_INFO_AUDIO_TYPE_MPEG2_AAC:
				case BURST_INFO_AUDIO_TYPE_MPEG2_AAC_LOW:
				case BURST_INFO_AUDIO_TYPE_MPEG4_AAC:
					*audioType = LX_HDMI_AUDIO_AAC;
					break;

				case BURST_INFO_AUDIO_TYPE_MPEG1_L1:
				case BURST_INFO_AUDIO_TYPE_MPEG1_L23:
				case BURST_INFO_AUDIO_TYPE_MPEG2_EXT:
				case BURST_INFO_AUDIO_TYPE_MPEG2_L1:
				case BURST_INFO_AUDIO_TYPE_MPEG2_L2:
				case BURST_INFO_AUDIO_TYPE_MPEG2_L3:
					*audioType = LX_HDMI_AUDIO_MPEG;
					break;

				default:
					*audioType = LX_HDMI_AUDIO_NO_AUDIO;
					break;
			}

			//Debug print
			if((glink_394_bx.reg_burst_pc_pip0_0 & BURST_INFO_AUDIO_TYPE_BIT_MASK) == BURST_INFO_AUDIO_TYPE_PAUSE)
			{
				HDMI_DEBUG("HDMI_GetAudioInfo : BURST_INFO_AUDIO_TYPE_PAUSE(Pc = %d)!!!\n", glink_394_bx.reg_burst_pc_pip0_0);
			}
		}	//if( (glink_394_bx.reg_burst_pc_pip0_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK) == 0 ) //bit 7
		else
		{
			*audioType = LX_HDMI_AUDIO_PCM;

			HDMI_ERROR("HDMI_GetAudioInfo : Burst Info Error = %d\n", (glink_394_bx.reg_burst_pc_pip0_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK));
		}
	}	//if( (glink_387_bx.reg_achst_byte0_pip0 >> 1) == 1)	//bit 1
	else
	{
		*audioType = LX_HDMI_AUDIO_PCM;
	}

	//Set Sampling frequency from IEC60958 Channel Status Byte 3
	VPORT_I2C_Read((UINT32*)&glink_390_bx);

	switch(glink_390_bx.reg_achst_byte3_pip0 & HDMI_AUDIO_SAMPLE_BIT_MASK) 	//bit 0 ~ 3
	{
		case HDMI_AUDIO_SAMPLE_22_05KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_22_05KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_24_KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_24_KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_32_KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_32_KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_44_1KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_44_1KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_48_KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_48_KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_88_2KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_88_2KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_96_KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_96_KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_176_4KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_176_4KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_192_KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_192_KHZ;
			break;

		case HDMI_AUDIO_SAMPLE_768_KHZ:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_768_KHZ;
			break;

		default:
			*samplingFreq = LX_HDMI_SAMPLING_FREQ_NONE;

			HDMI_ERROR("HDMI_GetAudioInfo : samplingFreq = %d\n", *samplingFreq);
			break;
	}

	return ret;
}

/**
 *  _HDMI_L9Bx_GetAudioFreqFromTmdsClock
 *
 *  @return int
*/
static int _HDMI_L9_GetAudioFreqFromTmdsClock(LX_HDMI_SAMPLING_FREQ_T *samplingFreqFromTmds)
{
	int ret = 0;

	UINT8		ui8TmdsClockHigh = 0;		//< HDMI measured clock value of TMDS clock for upper 8 bit
	UINT8		ui8TmdsClockLow = 0;		//< HDMI measured clock value of TMDS clock for low 8 bit

	UINT64		ui64TmdsClock = 0;			//< HDMI measured clock value of TMDS clock
	UINT64		ui64AcrN = 0;				//< HDMI ACR N value
	UINT64		ui64AcrCts = 0;				//< HDMI ACR CTS value
	UINT64		ui64TmdsSamplingFreq = 0;	//< HDMI sampling frequency in source device from TMDS clock

	//Get measured frequency value of TMDS clock.
	ACTRL_RdFL(ghdmi_phy_n_23_bx);
	ACTRL_Rd01(ghdmi_phy_n_23_bx, tmds_freq, ui8TmdsClockHigh);

	ACTRL_RdFL(ghdmi_phy_n_24_bx);
	ACTRL_Rd01(ghdmi_phy_n_24_bx, tmds_freq, ui8TmdsClockLow);
	ui64TmdsClock = (UINT64)((ui8TmdsClockHigh << 8) | ui8TmdsClockLow) * 10000;

	HDMI_AUDIO("Get TDMS Clock : ui64TmdsClock = %llu, ui8TmdsClockHigh = 0x%X, ui8TmdsClockLow = %d\n", ui64TmdsClock, ui8TmdsClockHigh, ui8TmdsClockLow);

	//Get ACR N H/W value.
	VPORT_I2C_Read((UINT32*)&glink_372_bx);
	VPORT_I2C_Read((UINT32*)&glink_373_bx);
	VPORT_I2C_Read((UINT32*)&glink_374_bx);
	ui64AcrN = (UINT64)((glink_372_bx.reg_acr_n_tx_pip0_2 << 16) | (glink_373_bx.reg_acr_n_tx_pip0_1 << 8) | glink_374_bx.reg_acr_n_tx_pip0_0);

	//Get ACR CTS H/W value.
	VPORT_I2C_Read((UINT32*)&glink_378_bx);
	VPORT_I2C_Read((UINT32*)&glink_379_bx);
	VPORT_I2C_Read((UINT32*)&glink_380_bx);
	ui64AcrCts = (UINT64)((glink_378_bx.reg_acr_cts_tx_pip0_2 << 16) | (glink_379_bx.reg_acr_cts_tx_pip0_1 << 8) | glink_380_bx.reg_acr_cts_tx_pip0_0);

	HDMI_AUDIO("Get TDMS ACR  : ui64AcrN = %llu, ui64AcrCts = %llu\n", ui64AcrN, ui64AcrCts);

	//Compute a sampling frequency from TMDS clock
	ui64TmdsSamplingFreq = ui64AcrN * ui64TmdsClock;

	//Check divide by zero value.
	if( (ui64TmdsSamplingFreq > 0) && (ui64AcrCts > 0) )
	{
		do_div(ui64TmdsSamplingFreq, ui64AcrCts * 128);
	}

	//Mapping a sampling frequency from measuring from TMDS clock and ACR N & CTS H/W value
	if(ui64TmdsSamplingFreq == 0)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_NONE;
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_NONE\n");
	}
	else if(ui64TmdsSamplingFreq < 22983)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_22_05KHZ;	//  22.05 kHz(not supported)
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_22_05KHZ(not supported)\n");
	}
	else if(ui64TmdsSamplingFreq < 30000)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_24_KHZ;	//  24 kHz(not supported)
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_24_KHZ(not supported)\n");
	}
	else if(ui64TmdsSamplingFreq < 33800)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_32_KHZ;	//  32 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_32KHZ\n");
	}
	else if(ui64TmdsSamplingFreq < 45965)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_44_1KHZ;	//  44.1 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_44_1KHZ\n");
	}
	else if(ui64TmdsSamplingFreq < 67000)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_48_KHZ;	//  48 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_48_KHZ\n");
	}
	else if(ui64TmdsSamplingFreq < 91935)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_88_2KHZ;	//  88.2 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_88_2KHZ\n");
	}
	else if(ui64TmdsSamplingFreq < 135000)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_96_KHZ;	//  96 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_96_KHZ\n");
	}
	else if(ui64TmdsSamplingFreq < 183870)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_176_4KHZ;	//  176.4 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_176_4KHZ\n");
	}
	else if(ui64TmdsSamplingFreq < 210000)
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_192_KHZ;	//  192 kHz
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_192_KHZ\n");
	}
	else
	{
		*samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_768_KHZ;	//  768 kHz(not supported)
		HDMI_PRINT("Get Fs from TDMS clock => LX_HDMI_SAMPLING_FREQ_768_KHZ(not supported)\n");
	}

	HDMI_AUDIO("Get Fs from TDMS clock : %llu => %d\n", ui64TmdsSamplingFreq, *samplingFreqFromTmds);
//	HDMI_ERROR("Get Fs from TDMS clock : %llu => %d\n", ui64TmdsSamplingFreq, *samplingFreqFromTmds);

	return ret;
}

/**
 *  _HDMI_L9Bx_DebugAudioInfo
 *
 *  @return int
*/
#ifdef	ENABLE_HDMI_AUDIO_DEBUG
static int _HDMI_L9_DebugAudioInfo(void)
{
	int ret = 0;

	UINT8		ui8TmdsClockHigh = 0;		//< HDMI measured clock value of TMDS clock for upper 8 bit
	UINT8		ui8TmdsClockLow = 0;		//< HDMI measured clock value of TMDS clock for low 8 bit

	UINT64		ui64TmdsClock = 0;			//< HDMI measured clock value of TMDS clock
	UINT64		ui64AcrN = 0;				//< HDMI ACR N value
	UINT64		ui64AcrCts = 0;				//< HDMI ACR CTS value
	UINT64		ui64TmdsSamplingFreq = 0;	//< HDMI sampling frequency in source device from TMDS clock

	//Get measured frequency value of TMDS clock.
	ACTRL_RdFL(ghdmi_phy_n_23_bx);
	ACTRL_Rd01(ghdmi_phy_n_23_bx, tmds_freq, ui8TmdsClockHigh);

	ACTRL_RdFL(ghdmi_phy_n_24_bx);
	ACTRL_Rd01(ghdmi_phy_n_24_bx, tmds_freq, ui8TmdsClockLow);
	ui64TmdsClock = (UINT64)((ui8TmdsClockHigh << 8) | ui8TmdsClockLow) * 10000;

	HDMI_AUDIO("Get TDMS Clock : ui64TmdsClock = %llu, ui8TmdsClockHigh = 0x%X, ui8TmdsClockLow = %d\n", ui64TmdsClock, ui8TmdsClockHigh, ui8TmdsClockLow);

	//Get ACR N H/W value.
	VPORT_I2C_Read((UINT32*)&glink_372_bx);
	VPORT_I2C_Read((UINT32*)&glink_373_bx);
	VPORT_I2C_Read((UINT32*)&glink_374_bx);
	ui64AcrN = (UINT64)((glink_372_bx.reg_acr_n_tx_pip0_2 << 16) | (glink_373_bx.reg_acr_n_tx_pip0_1 << 8) | glink_374_bx.reg_acr_n_tx_pip0_0);

	//Get ACR CTS H/W value.
	VPORT_I2C_Read((UINT32*)&glink_378_bx);
	VPORT_I2C_Read((UINT32*)&glink_379_bx);
	VPORT_I2C_Read((UINT32*)&glink_380_bx);
	ui64AcrCts = (UINT64)((glink_378_bx.reg_acr_cts_tx_pip0_2 << 16) | (glink_379_bx.reg_acr_cts_tx_pip0_1 << 8) | glink_380_bx.reg_acr_cts_tx_pip0_0);

	HDMI_AUDIO("Get TDMS ACR  : ui64AcrN = %llu, ui64AcrCts = %llu\n", ui64AcrN, ui64AcrCts);

	//Compute a sampling frequency from TMDS clock
	ui64TmdsSamplingFreq = ui64AcrN * ui64TmdsClock;

	//Check divide by zero value.
	if( (ui64TmdsSamplingFreq > 0) && (ui64AcrCts > 0) )
	{
		do_div(ui64TmdsSamplingFreq, ui64AcrCts * 128);
	}

	HDMI_DEBUG("TMDS Clock = %llu, ACR N = %llu, ACR CTS = %llu, Tmds Fs = %llu\n",	\
				ui64TmdsSamplingFreq, ui64AcrN, ui64AcrCts, ui64TmdsSamplingFreq);

	//Read glink_378_bx reg.
	VPORT_I2C_Read((UINT32*)&glink_387_bx);
	VPORT_I2C_Read((UINT32*)&glink_388_bx);
	VPORT_I2C_Read((UINT32*)&glink_389_bx);
	VPORT_I2C_Read((UINT32*)&glink_390_bx);
	VPORT_I2C_Read((UINT32*)&glink_391_bx);

	//Check IEC60958 Channel Status Byte0 ~ 3
	HDMI_DEBUG("IEC60958 Channel Status Byte0 = 0x%X, Byte1 = 0x%X, Byte2 = 0x%X, Byte3 = 0x%X\n",	\
				glink_387_bx.reg_achst_byte0_pip0, glink_388_bx.reg_achst_byte1_pip0, glink_389_bx.reg_achst_byte2_pip0, glink_390_bx.reg_achst_byte3_pip0);

	//Check IEC60958 Channel Status Byte4
	HDMI_DEBUG("IEC60958 Channel Status Byte4 = 0x%X\n", glink_391_bx.reg_achst_byte4_pip0);

	if(glink_387_bx.reg_achst_byte0_pip0 & 0x1)
		HDMI_DEBUG("Consumer use of channel status block is error!!!\n");
	else
		HDMI_DEBUG("Consumer use of channel status block.\n");


	if(glink_387_bx.reg_achst_byte0_pip0 & 0x2)
		HDMI_DEBUG("Audio sample word used for other purposes than liner PCM.\n");
	else
		HDMI_DEBUG("Audio sample word used for liner PCM.\n");


	if(glink_387_bx.reg_achst_byte0_pip0 & 0x4)
		HDMI_DEBUG("Software for which no copyright is asserted.\n");
	else
		HDMI_DEBUG("Software for which copyright is asserted.\n");


	HDMI_DEBUG("Category code = 0x%X\n", glink_388_bx.reg_achst_byte1_pip0);

	HDMI_DEBUG("Source number = %d\n", glink_389_bx.reg_achst_byte2_pip0 & 0x0F);


	HDMI_DEBUG("Channel number = %d\n", glink_389_bx.reg_achst_byte2_pip0 & 0xF0);
	if((glink_389_bx.reg_achst_byte2_pip0 & 0xF0) == 0x01)
		HDMI_DEBUG("Left channel for stereo channel format.\n");

	if((glink_389_bx.reg_achst_byte2_pip0 & 0xF0) == 0x02)
		HDMI_DEBUG("Right channel for stereo channel format.\n");


	if((glink_390_bx.reg_achst_byte3_pip0 & 0x0F) == 0x0)
		HDMI_DEBUG("Symbol frequency = 64 X 44.1KHz = 2.8224 MHz.\n");

	if((glink_390_bx.reg_achst_byte3_pip0 & 0x0F) == 0x2)
		HDMI_DEBUG("Symbol frequency = 64 X 48KHz = 3.072 MHz.\n");

	if((glink_390_bx.reg_achst_byte3_pip0 & 0x0F) == 0x3)
		HDMI_DEBUG("Symbol frequency = 64 X 32KHz = 2.048 MHz.\n");


	if((glink_390_bx.reg_achst_byte3_pip0 & 0x30) == 0x0)
		HDMI_DEBUG("Clock accuracy is Level II.\n");

	if((glink_390_bx.reg_achst_byte3_pip0 & 0x30) == 0x1)
		HDMI_DEBUG("Clock accuracy is Level I.\n");

	if((glink_390_bx.reg_achst_byte3_pip0 & 0x30) == 0x2)
		HDMI_DEBUG("Clock accuracy is Level III.\n");

	if((glink_390_bx.reg_achst_byte3_pip0 & 0x30) == 0x3)
		HDMI_DEBUG("Interface frame rate not matched to sampling frequency.\n");


	if(glink_390_bx.reg_achst_byte3_pip0 & 0x80)
		HDMI_DEBUG("Maximum audio sample word length is 24 bits.\n");
	else
		HDMI_DEBUG("Maximum audio sample word length is 20 bits.\n");

	//Check IEC61937 Burst Info
	if(glink_387_bx.reg_achst_byte0_pip0 & 0x2)
	{
		//Check a vaild Pc data for payload
		VPORT_I2C_Read((UINT32*)&glink_394_bx);
		VPORT_I2C_Read((UINT32*)&glink_395_bx);

		HDMI_DEBUG("IEC61937 Burst Info Pc = 0x%X, Pd = 0x%X\n",	\
					glink_394_bx.reg_burst_pc_pip0_0, glink_395_bx.reg_burst_pd_pip0_1);

		if(glink_394_bx.reg_burst_pc_pip0_0 & BURST_INFO_PAYLOAD_ERROR_BIT_MASK)
			HDMI_DEBUG("Error-flag indicationg that the burst-payload may contain errors.\n");
		else
			HDMI_DEBUG("Error-flag indicationg a vaild burst-payload.\n");


		//Set Audio Data-Types according to IEC61937-2 Burst Info Preamble C
		switch(glink_394_bx.reg_burst_pc_pip0_0 & 0x001F)	//bit 4 ~ 0
		{
			case BURST_INFO_AUDIO_TYPE_AC3:
			case BURST_INFO_AUDIO_TYPE_AC3_ENHANCED:
				HDMI_DEBUG("LX_HDMI_AUDIO_AC3(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_DTS_I:
			case BURST_INFO_AUDIO_TYPE_DTS_II:
			case BURST_INFO_AUDIO_TYPE_DTS_III:
				HDMI_DEBUG("LX_HDMI_AUDIO_DTS(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_MPEG1_L1:
			case BURST_INFO_AUDIO_TYPE_MPEG1_L23:
			case BURST_INFO_AUDIO_TYPE_MPEG2_EXT:
			case BURST_INFO_AUDIO_TYPE_MPEG2_L1:
			case BURST_INFO_AUDIO_TYPE_MPEG2_L2:
			case BURST_INFO_AUDIO_TYPE_MPEG2_L3:
				HDMI_DEBUG("LX_HDMI_AUDIO_MPEG(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_MPEG2_AAC:
				HDMI_DEBUG("LX_HDMI_AUDIO_AAC(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_ATRAC:
			case BURST_INFO_AUDIO_TYPE_ATRAC_23:
				HDMI_DEBUG("BURST_INFO_AUDIO_TYPE_ATRAC or ATRAC_23(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_NULL:
				HDMI_DEBUG("BURST_INFO_AUDIO_TYPE_NULL(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_SMPTE_338M:
				HDMI_DEBUG("BURST_INFO_AUDIO_TYPE_SMPTE_338M(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			case BURST_INFO_AUDIO_TYPE_PAUSE:
				HDMI_DEBUG("BURST_INFO_AUDIO_TYPE_PAUSE(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;

			default:
				HDMI_AUDIO("LX_HDMI_AUDIO_NO_AUDIO(Audio type in Pc = %d)\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x001F);
				break;
		}

		HDMI_DEBUG("Data-type-dependent info. = %d\n", glink_394_bx.reg_burst_pc_pip0_0 & 0x1F00);
		HDMI_DEBUG("Bitstream number = %d\n", glink_394_bx.reg_burst_pc_pip0_0 & 0xD000);

		HDMI_DEBUG("Length-code : Number of bits = %d\n", glink_395_bx.reg_burst_pd_pip0_1);
	}

	return ret;
}
#endif	//#ifdef	ENABLE_HDMI_AUDIO_DEBUG


/**
 *  HDMI_GetAudioInfo
 *
 *  @parm LX_HDMI_AUDIO_INFO_T *
 *  @return int
*/
int HDMI_L9_GetAudioInfo(LX_HDMI_AUDIO_INFO_T *audio_info)
{
	int 	ret = 0;

	ULONG	flags = 0;
	UINT32  					intrAudioState  = HDMI_AUDIO_INIT_STATE;

	LX_HDMI_AUDIO_TYPE_T		audioType		= LX_HDMI_AUDIO_NO_AUDIO;		///< HDMI Audio Type.
	LX_HDMI_SAMPLING_FREQ_T 	samplingFreq	= LX_HDMI_SAMPLING_FREQ_48_KHZ; ///< Sampling Frequency

	UINT16						ui16VActive;			//< HDMI Vertical Active Size
	UINT16						ui16HActive;			//< HDMI horizontal Active Size

	LX_HDMI_SAMPLING_FREQ_T		samplingFreqFromTmds = LX_HDMI_SAMPLING_FREQ_48_KHZ;	//< HDMI sampling frequency from TMDS clock

	//Increase _gHdmiAudioPrintCount;
	_gHdmiAudioPrintCount++;

	//Check HDMI port connection
	VPORT_I2C_Read((UINT32*)&glink_0_bx);

	if(glink_0_bx.reg_scdt_prt0 == 0)	//Check HDMI, DVI Sync Detect
	{
		//spin lock for protection : lock
		spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);

		//Clear _gIntrAudioState
		_gIntrAudioState = HDMI_AUDIO_INIT_STATE;

		//spin lock for protection : unlock
		spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

		if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
			HDMI_DEBUG("HDMI_GetAudioInfo : HDMI / DVI Not Connected(state = %d)!!!\n", _gIntrAudioState);

		goto func_exit;
	}

	//spin lock for protection : lock
	spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);

	//copy audio interrupt state
	intrAudioState = _gIntrAudioState;

	//spin lock for protection : unlock
	spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

	//Check _gIntrAudioState is stably changed.
	if(intrAudioState == HDMI_AUDIO_STABLE_STATE && _gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
	{
		//Check video active size from global variables.
		if( ((_gPrevTiming.vActive <  240) || (_gPrevTiming.hActive <  320)	\
		   ||(_gPrevTiming.vActive > 2970) || (_gPrevTiming.hActive > 4096)	\
		   ||(_gPrevTiming.vFreq > 800))
		   && (_gExtMute == 0) )
		{
			HDMI_DEBUG("HDMI_GetAudioInfo 1 : Video Active Size Error(v = %d, h = %d, vf = %d)!!!\n",	\
						 _gPrevTiming.vActive, _gPrevTiming.hActive, _gPrevTiming.vFreq);

			//spin lock for protection for audio
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
			_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

			goto func_exit;
		}

		//Check HDMI timing count
		if(gBootData->mode)
		{
			//Check HDMI timing count
			if( _gTimingCnt < gBootData->timingCn[gBootData->hdmi_switch] )
			{
				HDMI_DEBUG("HDMI_GetAudioInfo 1 : HDMI Timing Error(time = %d, table = %d)!!!\n",	\
							 _gTimingCnt, gBootData->timingCn[gBootData->hdmi_switch]);

				//spin lock for protection for audio
				spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
				_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
				spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

				goto func_exit;
			}
		}
		else
		{
			//Check DVI timing count
			if( _gTimingCnt < gBootData->dviCn[gBootData->hdmi_switch] )
			{
				HDMI_DEBUG("HDMI_GetAudioInfo 1 : DVI Timing Error(time = %d, table = %d)!!!\n",	\
							 _gTimingCnt, gBootData->dviCn[gBootData->hdmi_switch]);

				//spin lock for protection for audio
				spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
				_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
				spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

				goto func_exit;
			}
		}

		//Recheck for HDMI Audio Format and sampling frequency
		if((_gHdmiAudioPrintCount % HDMI_AUDIO_RECHECK_TIME) == 0)	// 1 seconds, DDI calls every 50 ms
		{
			//Get HDMI Audio Type and Sampling Frequency
			(void)_HDMI_L9_GetAudioTypeAndFreq(&audioType, &samplingFreq);

			//Get a sampling frequency from TMDS clock
			(void)_HDMI_L9_GetAudioFreqFromTmdsClock(&samplingFreqFromTmds);

			//L9 IP Bug : non-PCM interrupt is not triggerred if non-PCM(AC-3) is changed to non-PCM(DTS).
			if( (audioType 	  		  != _gHdmiAudioInfo.audioType)
			  ||(samplingFreqFromTmds != _gHdmiAudioInfo.samplingFreq) )
			{
				HDMI_DEBUG("Recheck => HDMI_GetAudioInfo : type = %d(%d), tmds freq = %d(%d), freq = %d, state = %d\n",	\
							audioType, _gHdmiAudioInfo.audioType, samplingFreqFromTmds, _gHdmiAudioInfo.samplingFreq,	\
							samplingFreq, _gIntrAudioState);

				//spin lock for protection for audio
				spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
				_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
				spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

				goto func_exit;
			}
		}

		//Return a previous value.
		audio_info->audioType	   = _gHdmiAudioInfo.audioType;
		audio_info->samplingFreq   = _gHdmiAudioInfo.samplingFreq;

		//Debug print
		if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
		{
			HDMI_PRINT("HDMI_GetAudioInfo 1 : type = %d, freq = %d, state = %d\n",	\
						audio_info->audioType, audio_info->samplingFreq, _gIntrAudioState);
		}

		return ret;
	}
	else if( (intrAudioState == HDMI_AUDIO_STABLE_STATE)	\
		  && (_gIntrVideoState != HDMI_VIDEO_STABLE_STATE)	\
		  && (_gTimingCnt >= HDMI_VIDEO_READ_STATE) )
	{
		//Debug print
		if( _gTimingCnt >= (HDMI_VIDEO_READ_STATE + 3) )
		{
			HDMI_DEBUG("HDMI_GetAudioInfo 1 : HDMI_VIDEO_INTERRUPT_STATE(state A = %d, V = %d, count = %d)!!!\n", _gIntrAudioState, _gIntrVideoState, _gTimingCnt);
		}

		//Return a previous value.
		audio_info->audioType	   = _gHdmiAudioInfo.audioType;
		audio_info->samplingFreq   = _gHdmiAudioInfo.samplingFreq;

		return ret;
	}
	else if(intrAudioState == HDMI_AUDIO_STABLE_STATE && _gIntrVideoState != HDMI_VIDEO_STABLE_STATE)
	{
		HDMI_DEBUG("HDMI_GetAudioInfo 1 : HDMI_VIDEO_INTERRUPT_STATE(state A = %d, V = %d)!!!\n", _gIntrAudioState, _gIntrVideoState);

		//spin lock for protection for audio
		spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
		_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
		spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
	}
	else if(intrAudioState == HDMI_AUDIO_GET_INFO_STATE && _gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
	{
		if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
			HDMI_DEBUG("HDMI_GetAudioInfo 1 : HDMI_AUDIO_GET_INFO_STATE(state A = %d, V = %d)!!!\n", _gIntrAudioState, _gIntrVideoState);
	}
	else if(intrAudioState < HDMI_AUDIO_GET_INFO_STATE && _gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
	{
		//spin lock for protection : lock
		spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);

		//increase _gIntrAudioState
		_gIntrAudioState++;

		//spin lock for protection : unlock
		spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);

		if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
			HDMI_DEBUG("HDMI_GetAudioInfo 1 : HDMI_AUDIO_UNSTABLE_STATE(state A = %d, V = %d)!!!\n", _gIntrAudioState, _gIntrVideoState);

		goto func_exit;
	}
	else
	{
		if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
			HDMI_DEBUG("HDMI_GetAudioInfo 1 : HDMI / DVI Not Connected(state = %d)!!!\n", _gIntrAudioState);

		goto func_exit;
	}

	//Get video vertical active size
	VPORT_I2C_Read((UINT32*)&glink_350_bx);
	ui16HActive  = glink_350_bx.reg_h_av_pip0_1 << 8;
	VPORT_I2C_Read((UINT32*)&glink_351_bx);
	ui16HActive |= glink_351_bx.reg_h_av_pip0_0;

	//Get video horizontal active size
	VPORT_I2C_Read((UINT32*)&glink_352_bx);
	ui16VActive  = glink_352_bx.reg_v_av_pip0_1 << 8;
	VPORT_I2C_Read((UINT32*)&glink_353_bx);
	ui16VActive |= glink_353_bx.reg_v_av_pip0_0;

	//Check video active size
	if( (ui16VActive <  240) || (ui16HActive <  320)	\
	  ||(ui16VActive > 2970) || (ui16HActive > 4096) )
	{
		HDMI_AUDIO("HDMI_GetAudioInfo : Video Active Size Error(v = %d, h = %d)!!!\n",	\
					 ui16VActive, ui16HActive);

		goto func_exit;
	}

	//Get a HDMI / DVI mode
	//VPORT_I2C_Read((UINT32*)&glink_1_bx);

	//Check HDMI /DVI Mode, 0 : DVI, 1 : HDMI
	//if(glink_1_bx.reg_hdmi_mode_pip0)
	if(gBootData->mode)
	{
		//Check HDMI timing count
		if( _gTimingCnt < gBootData->timingCn[gBootData->hdmi_switch] )
		{
			HDMI_AUDIO("HDMI_GetAudioInfo : HDMI Timing Error(time = %d, table = %d)!!!\n",	\
						 _gTimingCnt, gBootData->timingCn[gBootData->hdmi_switch]);

			goto func_exit;
		}

		//Get HDMI Audio Type and Sampling Frequency
		(void)_HDMI_L9_GetAudioTypeAndFreq(&audioType, &samplingFreq);

		//Get HDMI Audio Sampling Frequency from TMDS clock when audio sample is PCM
		if(audioType == LX_HDMI_AUDIO_PCM)
		{
			//Get a sampling frequency from TMDS clock
			(void)_HDMI_L9_GetAudioFreqFromTmdsClock(&samplingFreqFromTmds);

			//Check a sampling frequency from status byte to TMDS clock
			//status byte 0 value is 44.2Khz normal case or abnormal case
			if( (samplingFreq == LX_HDMI_SAMPLING_FREQ_44_1KHZ)
			  &&(samplingFreqFromTmds != LX_HDMI_SAMPLING_FREQ_44_1KHZ) )
			{
				//Set a no audio mode
				audioType = LX_HDMI_AUDIO_NO_AUDIO;

				if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
				{
					HDMI_ERROR("HDMI_GetAudioInfo : Freq Error(status = %d, tmds = %d)!!!\n",	\
								samplingFreq, samplingFreqFromTmds);
				}

				goto func_exit;
			}

			//Set a audio output mute when TMDS Fs is zero or not support.
			if( (samplingFreqFromTmds == LX_HDMI_SAMPLING_FREQ_NONE)
			  ||(samplingFreqFromTmds == LX_HDMI_SAMPLING_FREQ_22_05KHZ)
			  ||(samplingFreqFromTmds == LX_HDMI_SAMPLING_FREQ_24_KHZ)
			  ||(samplingFreqFromTmds == LX_HDMI_SAMPLING_FREQ_768_KHZ))
			{
				//Set a no audio mode
				audioType = LX_HDMI_AUDIO_NO_AUDIO;

				//Mute audio data
				VPORT_I2C_Read((UINT32*)&glink_383_bx);
				glink_383_bx.reg_i2s_sd_en_pip0 = 0x0;
				VPORT_I2C_Write((UINT32*)&glink_383_bx);

				if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
					HDMI_ERROR("HDMI_GetAudioInfo : TMDS Fs Error(%d)!!!\n", samplingFreqFromTmds);
			}
			else
			{
				//Set a sampling frequency from TMDS clock
				samplingFreq = samplingFreqFromTmds;

 				//Un-mute audio data
				VPORT_I2C_Read((UINT32*)&glink_383_bx);
				glink_383_bx.reg_i2s_sd_en_pip0 = 0xF;
				VPORT_I2C_Write((UINT32*)&glink_383_bx);

				HDMI_PRINT("HDMI_GetAudioInfo : samplingFreq = %d\n", samplingFreq);
			}
		}
		else
		{
			//Un-mute audio data
			VPORT_I2C_Read((UINT32*)&glink_383_bx);
			glink_383_bx.reg_i2s_sd_en_pip0 = 0xF;
			VPORT_I2C_Write((UINT32*)&glink_383_bx);
		}

		//Check a audio and video stable status
		if( (audioType 	  == _gHdmiAudioInfo.audioType)
		  &&(samplingFreq == _gHdmiAudioInfo.samplingFreq)
		  &&(_gHdmiAudioInfo.audioType >= LX_HDMI_AUDIO_PCM)
		  &&(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE) )
		{
			//spin lock for protection : lock
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);

			//Set a _gIntrAudioState
			_gIntrAudioState = HDMI_AUDIO_STABLE_STATE;

			//spin lock for protection : unlock
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}

		//For debug print
		if( (audioType != _gHdmiAudioInfo.audioType) || (samplingFreq != _gHdmiAudioInfo.samplingFreq))
		{
			//Check a vaild Pc data for payload
			VPORT_I2C_Read((UINT32*)&glink_394_bx);

			HDMI_DEBUG("HDMI_GetAudioInfo : type = %d(0x%X), freq = %d\n",	\
						audioType, glink_394_bx.reg_burst_pc_pip0_0 & 0x1F, samplingFreq);

#ifdef	ENABLE_HDMI_AUDIO_DEBUG
			//Print Audio Debug Info.
			(void)_HDMI_L9_DebugAudioInfo();
#endif		//#ifdef	ENABLE_HDMI_AUDIO_DEBUG
		}
	}
	else
	{
		//Check DVI timing count
		if( _gTimingCnt < gBootData->timingCn[gBootData->hdmi_switch] )
		{
			HDMI_AUDIO("HDMI_GetAudioInfo : DVI Timing Error(time = %d, table = %d)!!!\n",	\
						 _gTimingCnt, gBootData->timingCn[gBootData->hdmi_switch]);

			goto func_exit;
		}

		//Set DVI mode
		audioType	   = LX_HDMI_AUDIO_DVI;
		samplingFreq   = LX_HDMI_SAMPLING_FREQ_48_KHZ;

		//Check a audio and video stable status
		if( (audioType 	  == _gHdmiAudioInfo.audioType)
		  &&(samplingFreq == _gHdmiAudioInfo.samplingFreq)
		  &&(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE) )
		{
			//spin lock for protection : lock
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);

			//Set a _gIntrAudioState
			_gIntrAudioState = HDMI_AUDIO_STABLE_STATE;

			//spin lock for protection : unlock
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}

		//For debug print
		if(audioType != _gHdmiAudioInfo.audioType)
		{
			HDMI_DEBUG("HDMI_GetAudioInfo : type = 0x%X, freq = 0x%X,\n", audioType, samplingFreq);
		}
	}

func_exit:
	//Mute audio data
	if(audioType == LX_HDMI_AUDIO_NO_AUDIO)
	{
		VPORT_I2C_Read((UINT32*)&glink_383_bx);
		glink_383_bx.reg_i2s_sd_en_pip0 = 0x0;
		VPORT_I2C_Write((UINT32*)&glink_383_bx);

		//Clears a global value for audio info.
		memset(&_gHdmiAudioInfo, 0, sizeof(LX_HDMI_AUDIO_INFO_T));

		//Debug print
		if((_gHdmiAudioPrintCount % DEBUG_HDMI_AUDIO_MSG_PRINT_TIME) == 0)	//DDI calls every 50 ms
		{
			HDMI_DEBUG("HDMI_GetAudioInfo : HDMI Audio Mute On !!!\n");
		}
	}

	//Update HDMI Audio Info.
	audio_info->audioType	   = audioType;
	audio_info->samplingFreq   = samplingFreq;

	//Update global value for checking next call
	_gHdmiAudioInfo.audioType	   = audioType;
	_gHdmiAudioInfo.samplingFreq   = samplingFreq;

	HDMI_PRINT("HDMI_GetAudioInfo : type = %d, freq = %d, state = %d\n",	\
				audio_info->audioType, audio_info->samplingFreq, _gIntrAudioState);

	return ret;
}

int _HDMI_L9_SetInternalMute(LX_HDMI_MUTE_CTRL_T *interMute)
{
	if(interMute->bVideoMute == 1)
	{
		VPORT_I2C_Read((UINT32*)&glink_1_bx);

		if(glink_1_bx.reg_mute_vid_pip0 != 1)
		{
			glink_1_bx.reg_mute_vid_pip0 = 1;
			VPORT_I2C_Write((UINT32*)&glink_1_bx);
		}
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&glink_1_bx);

		if(glink_1_bx.reg_mute_vid_pip0 != 0)
		{
			glink_1_bx.reg_mute_vid_pip0 = 0;
			VPORT_I2C_Write((UINT32*)&glink_1_bx);
		}
	}

/*
	//Mute audio data
	if( interMute->bAudioMute == 1)
	{
		VPORT_I2C_Read((UINT32*)&glink_383_bx);
		glink_383_bx.reg_i2s_sd_en_pip0 = 0x0;
		VPORT_I2C_Write((UINT32*)&glink_383_bx);
	}
	else
	{
		VPORT_I2C_Read((UINT32*)&glink_383_bx);
		glink_383_bx.reg_i2s_sd_en_pip0 = 0xF;
		VPORT_I2C_Write((UINT32*)&glink_383_bx);
	}
*/	return 0;


}

/**
 *  HDMI_SetMute
 *
 *  @parm LX_HDMI_MUTE_CTRL_T *
 *  @return int
*/
int HDMI_L9_SetMute(LX_HDMI_MUTE_CTRL_T *mute)
{
	if (_gSCDT && _gIntrVideoState == HDMI_VIDEO_STABLE_STATE)
	{
		_gExtMute = 1;
	}

	return 0;
}

/**
 *  HDMI_SetArc
 *
 *  @parm LX_HDMI_ARC_CTRL_T *
 *  @return int
*/
int HDMI_L9_SetArc(LX_HDMI_ARC_CTRL_T *arc)
{
	int ret = 0;
#if 1
	/* ARC pdb Issue - L9A B0 fixed : sh.myoung 20110518*/
#ifdef L9A_A0_ARC_PDB
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_26_bx);
	ghdmi_phy_n_26_bx.odt_sel = arc->ARCEnable * 2; // Off : 0, On : 2(default)
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_26_bx);
#endif

	VPORT_I2C_Read((UINT32*)&glink_0_bx);

	//Enable ARC in Phy0
	glink_0_bx.reg_arc_src_prt0 = 0;

	VPORT_I2C_Read((UINT32*)&ghpd_out_control_1_bx);
	ghpd_out_control_1_bx.phy0_phy_arc_pdb = arc->bARCEnable;
	VPORT_I2C_Write((UINT32*)&ghpd_out_control_1_bx);

	VPORT_I2C_Write((UINT32*)&glink_0_bx);

	HDMI_PRINT("HDMI_L9_SetArc [%s]\n", arc->bARCEnable?"On":"Off");
#endif
	return ret;
}

/**
 * HDMI_L9Bx_SetRGBYCbCr
 *
 * @parm UINT32 *
 * @return int
*/
int _HDMI_L9_SetRGBYCbCr(LX_HDMI_AVI_COLORSPACE_T *space)
{
#if 0
	if (_gSCDT && _gTimingChanged == 0)
		_gTimingChanged = gBootData->connectCn[gBootData->hdmi_switch];
#else
	UINT8 blank_r = 0x0;
	UINT8 blank_b = 0x0;

	if(*space == _gPrevPixelEncoding)
	{
#ifdef VIDEO_DEBUG
		//HDMI_DEBUG("- [%d] %s - CSC[%d]  Same -\n", __LINE__, __func__, *space);
#endif
		goto func_exit;
	}

	switch(*space)
	{
		case LX_HDMI_AVI_COLORSPACE_YCBCR422:
		case LX_HDMI_AVI_COLORSPACE_YCBCR444:
		{
			blank_r = 0x8;
			blank_b = 0x8;
		}	break;

		case LX_HDMI_AVI_COLORSPACE_RGB:
		default:
		{
			blank_r = 0x0;
			blank_b = 0x0;
		}	break;
	}

	/* Blank Red */
	VPORT_I2C_Read((UINT32*)&glink_399_bx);
	glink_399_bx.reg_vid_blank_r_prt0_1 = blank_r;
	VPORT_I2C_Write((UINT32*)&glink_399_bx);

	/* Blank Blue */
	VPORT_I2C_Read((UINT32*)&glink_403_bx);
	glink_403_bx.reg_vid_blank_b_prt0_1 = blank_b;
	VPORT_I2C_Write((UINT32*)&glink_403_bx);

#ifdef VIDEO_DEBUG
	HDMI_DEBUG("- [%d] %s - CSC[%d] VID Blank Changed -\n", __LINE__, __func__, *space);
#endif

#endif

func_exit:
	_gPrevPixelEncoding = *space;

	return 0;
}

/**
 *  HDMI_PowerConsumxption
 *
 *  @param LX_HDMI_POWER_CTRL_T *
 *  @return int
*/
int HDMI_L9_PowerConsumption(UINT32 power)
{
	VPORT_I2C_Read((UINT32*)&ghdmi_phy_n_01_bx);
	ghdmi_phy_n_01_bx.resetb_all = power;
	ghdmi_phy_n_01_bx.pdb_all = power;
	VPORT_I2C_Write((UINT32*)&ghdmi_phy_n_01_bx);

	HDMI_ERROR(" HDMI_L9_PowerConsumption Power[%s]\n", (power ? "On" : "Off"));
	return 0;
}

int HDMI_L9_SetUDn3DControl(LX_HDMI_UD_3D_MODE_T *udn3d)
{
	VPORT_I2C_Read((UINT32*)&gdata_bridge_2_bx);

	switch(*udn3d)
	{
		case LX_HDMI_UD:
			gdata_bridge_2_bx.reg_3dfr_bridge_mode = 0;
			gdata_bridge_2_bx.reg_ud_autoset = 1;
			gdata_bridge_2_bx.reg_3dfr_autoset = 0;
			break;

		case LX_HDMI_3D_FP_60HZ:
			gdata_bridge_2_bx.reg_3dfr_bridge_mode = 1;
			gdata_bridge_2_bx.reg_ud_autoset = 0;
			gdata_bridge_2_bx.reg_3dfr_autoset = 1;
			break;

		case LX_HDMI_UD_SCALING:
			gdata_bridge_2_bx.reg_3dfr_bridge_mode = 2;
			gdata_bridge_2_bx.reg_ud_autoset = 1;
			gdata_bridge_2_bx.reg_3dfr_autoset = 0;
			break;

		case LX_HDMI_3D_SS_FULL:
		default:
			gdata_bridge_2_bx.reg_3dfr_bridge_mode = 0;
			gdata_bridge_2_bx.reg_ud_autoset = 0;
			gdata_bridge_2_bx.reg_3dfr_autoset = 0;
			break;
	}

	VPORT_I2C_Write((UINT32*)&gdata_bridge_2_bx);
	HDMI_PRINT("HDMI_L9_SetUDn3DControl[0:2D, 1:UD 2:SS 3:FP] ==>[ %d ]\n", *udn3d);

	return 0;
}

/**
 *  HDMI_GetRegister
 *
 *  @parm UINT32 *
 *  @return int
 	data:8,
	rsvd8:8,
	slaveAddr:8,
	regAddr:8;
*/
int HDMI_L9_GetRegister(UINT32 addr , UINT32 *value)
{
	VPORT_I2C_DATA_T *i2cData = (VPORT_I2C_DATA_T*)&addr;

	VPORT_I2C_Read((UINT32*)i2cData);

	//HDMI_ERROR("Read Slave 0x%x, reg 0x%x  Data = 0x%x\n", i2cData->slaveAddr, i2cData->regAddr, i2cData->data);
	*value = i2cData->data;

	return 0;
}


/**
 *  HDMI_GetAudioInfo
 *
 *  @parm LX_HDMI_AUDIO_INFO_T *
 *  @return int
*/
int HDMI_L9_SetRegister(UINT32 addr , UINT32 value)
{
	VPORT_I2C_DATA_T *i2cData = (VPORT_I2C_DATA_T*)&addr;
	i2cData->data = (UINT8)(value&0x000000ff);

	//HDMI_ERROR("Write Slave 0x%x, reg 0x%x  Data = 0x%x\n", i2cData->slaveAddr, i2cData->regAddr, i2cData->data);

	VPORT_I2C_Write((UINT32*)i2cData);

	return 0;
}


/**
 *
 * HDMI_L9Bx_irq_handler irq handler
 *
 * @param	irq , device id , regs
 * @return	0 : OK , -1 : NOK
 *
*/
irqreturn_t HDMI_L9_IRQHandler(int irq, void *dev)
{
	ULONG	flags = 0;
	LX_HDMI_MUTE_CTRL_T 		muteCtrl = {0, 0, 1};
	LX_HDMI_AVI_COLORSPACE_T	csc = LX_HDMI_AVI_COLORSPACE_RGB;


	//LX_HDMI_MUTE_CTRL_T		hdmiMute = {1, 1, 2};  // Default - A/V Mute
	VPORT_I2C_Read((UINT32*)&gl9a_hdmi0_intr_0_bx);
	VPORT_I2C_Read((UINT32*)&gl9a_hdmi0_intr_5_bx);
	VPORT_I2C_Read((UINT32*)&gl9a_hdmi0_intr_6_bx);

#if 0
	HDMI_ERROR("[intr_0_bx] = 0x%X\n", gl9a_hdmi0_intr_0_bx);
	HDMI_ERROR("[intr_5_bx] = 0x%X\n", gl9a_hdmi0_intr_5_bx);
	HDMI_ERROR("[intr_6_bx] = 0x%X\n", gl9a_hdmi0_intr_6_bx);
#endif

	if(gl9a_hdmi0_intr_6_bx.intr_vf_stable)
	{
		//spin lock for protection
		spin_lock_irqsave(&_gIntrHdmiVideoLock, flags);
		_gIntrVideoState = HDMI_VIDEO_INTERRUPT_STATE;
		spin_unlock_irqrestore(&_gIntrHdmiVideoLock, flags);

		// when change from other external input to before hdmi port(hdmi source changed), have before AVI, VSI info.
		if((_gTimingChanged == 0) && (_gTimingCnt >= gBootData->timingCn[gBootData->hdmi_switch]))
		{
			_gIntrAVIState = HDMI_AVI_INTERRUPT_STATE;
			_gIntrVSIState = HDMI_VSI_INTERRUPT_STATE;
			_gTimingCnt = HDMI_VIDEO_READ_STATE;
			HDMI_DEBUG("[HDMI_VF_STABLE]  HDMI Info changed at other external input \n");

			//spin lock for protection for audio
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
			_gIntrAudioState = HDMI_AUDIO_STABLE_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}
		else
		{
			//spin lock for protection for audio
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
			_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}

		HDMI_DEBUG("[HDMI_VF_STABLE]  = %d \n", _gIntrVideoState);
	}

	if(gl9a_hdmi0_intr_5_bx.intr_chg_avi_b12345)
	{
		_gIntrAVIState = HDMI_AVI_INTERRUPT_STATE;
		HDMI_PRINT("gl9a_hdmi0_intr_5_bx[HDMI_AVI]\n");

		if(gl9a_hdmi0_intr_6_bx.intr_chg_avi_to_ycc444)
			csc = LX_HDMI_AVI_COLORSPACE_YCBCR444;

		if(gl9a_hdmi0_intr_6_bx.intr_chg_avi_to_ycc422)
			csc = LX_HDMI_AVI_COLORSPACE_YCBCR422;

		if(gl9a_hdmi0_intr_6_bx.intr_chg_avi_to_rgb)
			csc = LX_HDMI_AVI_COLORSPACE_RGB;

#ifndef INTERRUNT_VIDEO_DEBUG
		HDMI_DEBUG("[HDMI_AVI] preCSS[%d] CSC = %d \n", _gPrevPixelEncoding, csc);
#endif
		if(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE)			// for PS3 CSC
		{
			if(_gPrevPixelEncoding != csc)
			{
				muteCtrl.bVideoMute = 1;
				_HDMI_L9_SetInternalMute(&muteCtrl);

				//spin lock for protection
				spin_lock_irqsave(&_gIntrHdmiVideoLock, flags);
				_gIntrVideoState = HDMI_VIDEO_INIT_STATE;
				spin_unlock_irqrestore(&_gIntrHdmiVideoLock, flags);

				_gIntrAVICscState = HDMI_AVI_CSC_CHANGE_STATE;
#ifdef AVI_MUTE_DEBUG
				HDMI_DEBUG("[HDMI_AVI] Video Mute /  _gIntrAVICscState = %d \n", _gIntrAVICscState);
#endif
			}
		}
	}

	if(gl9a_hdmi0_intr_0_bx.intr_clr_mute_pip0)
	{
		HDMI_DEBUG(" ~~~~~~~~~~~~~~~ [HDMI_MUTE_CLEAR]\n");

	}

	if(gl9a_hdmi0_intr_0_bx.intr_set_mute_pip0)
	{
#ifdef SOURCE_MUTE_DEBUG
		HDMI_DEBUG(" **** %d SOURCE MUTE Interrupt[%d] \n", __LINE__, _gIntrSourceMute );
#endif
		if(_gIntrVideoState > HDMI_VIDEO_INIT_STATE)
		{
			if(_gIntrSourceMute != HDMI_SOURCE_MUTE_STATE && _gIntrVideoState != HDMI_VIDEO_INIT_STATE)
			{
				muteCtrl.bVideoMute = 1;
				_HDMI_L9_SetInternalMute(&muteCtrl);

				spin_lock_irqsave(&_gIntrHdmiMuteLock, flags);
				_gIntrSourceMute = HDMI_SOURCE_MUTE_STATE;
				spin_unlock_irqrestore(&_gIntrHdmiMuteLock, flags);

				_gIntrVSIState = HDMI_VSI_INIT_STATE;
#ifdef SOURCE_MUTE_DEBUG
				HDMI_DEBUG(" **** %d HDMI_SOURCE MUTE Enable[%d] \n", __LINE__, _gIntrSourceMute );
#endif
			}
		}
	}

	if(gl9a_hdmi0_intr_0_bx.intr_hdmi_mode_prt0)
	{
		HDMI_PRINT("gl9a_hdmi0_intr_0_bx[HDMI_MODE]\n");

	}

	if(gl9a_hdmi0_intr_0_bx.intr_plug_prt0)
	{
		HDMI_PRINT("gl9a_hdmi0_intr_0_bx[HDMI_PLUG]\n");

	}

	if(gl9a_hdmi0_intr_0_bx.intr_vs_det_prt0)
	{
		HDMI_PRINT("gl9a_hdmi0_intr_0_bx[HDMI_VS_DET]\n");

	}

	if(gl9a_hdmi0_intr_0_bx.intr_scdt_prt0)
	{
		HDMI_PRINT("gl9a_hdmi0_intr_0_bx[HDMI_SCDT]\n");

	}

	if( (gl9a_hdmi0_intr_6_bx.intr_2npcm_chg_pip0 == 1)
	  ||(gl9a_hdmi0_intr_6_bx.intr_2pcm_chg_pip0 == 1)
	  ||(gl9a_hdmi0_intr_6_bx.intr_fs_chg_pip0 == 1) )
	{
		// when change from other external input to before hdmi port(hdmi source changed), have before AVI, VSI info.
		if((_gTimingChanged == 0) && (_gTimingCnt >= gBootData->timingCn[gBootData->hdmi_switch]))
		{
			//spin lock for protection for audio
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
			_gIntrAudioState = HDMI_AUDIO_STABLE_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}
		else
		{
			//spin lock for protection for audio
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
			_gIntrAudioState = HDMI_AUDIO_INTERRUPT_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}

		if(gl9a_hdmi0_intr_6_bx.intr_2npcm_chg_pip0)
		{
			HDMI_DEBUG("[HDMI_AUDIO_2NPCM]\n");
		}

		if(gl9a_hdmi0_intr_6_bx.intr_2pcm_chg_pip0)
		{
			HDMI_DEBUG("[HDMI_AUDIO_2PCM]\n");
		}

		if(gl9a_hdmi0_intr_6_bx.intr_fs_chg_pip0)
		{
			HDMI_DEBUG("[HDMI_FS]\n");
		}
	}

	if(gl9a_hdmi0_intr_6_bx.intr_chg_vsi_vformat)
	{
		_gIntrVSIState = HDMI_VSI_INTERRUPT_STATE;
#ifdef INTERRUNT_VIDEO_DEBUG
		HDMI_DEBUG("[HDMI_VSI]  = %d\n", _gIntrVSIState);
#endif

		// when  don't change Sync and change VSI on 3D for OPTIMUS Phone ( 3D / LTE /MHL )
		if(_gIntrVideoState == HDMI_VIDEO_STABLE_STATE) 		// for optimus phone
		{
			//spin lock for protection
			spin_lock_irqsave(&_gIntrHdmiVideoLock, flags);
			_gIntrVideoState = HDMI_VIDEO_INIT_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiVideoLock, flags);

			_gIntrAVICscState = HDMI_AVI_CSC_CHANGE_STATE;
			_gTimingCnt = HDMI_VIDEO_READ_STATE;

			HDMI_DEBUG("[HDMI_VSI_STABLE]  HDMI VSI Info changed on VIDEO Stable State\n");

			//spin lock for protection for audio
			spin_lock_irqsave(&_gIntrHdmiAudioLock, flags);
			_gIntrAudioState = HDMI_AUDIO_STABLE_STATE;
			spin_unlock_irqrestore(&_gIntrHdmiAudioLock, flags);
		}
	}

	VPORT_I2C_Write((UINT32*)&gl9a_hdmi0_intr_0_bx);
	VPORT_I2C_Write((UINT32*)&gl9a_hdmi0_intr_6_bx);
	VPORT_I2C_Write((UINT32*)&gl9a_hdmi0_intr_5_bx);

	return IRQ_HANDLED;
}

void HDMI_L9_EnableInterrupt(void)
{
	VPORT_I2C_Read((UINT32*)&gl9a_hdmi0_intr_en_0_bx);
	//gl9a_hdmi0_intr_en_0_bx.enable_intr_clr_mute_pip0 = 1;
	gl9a_hdmi0_intr_en_0_bx.enable_intr_set_mute_pip0 = 1;
	//gl9a_hdmi0_intr_en_0_bx.enable_intr_hdmi_mode_prt0 = 1;
	//gl9a_hdmi0_intr_en_0_bx.enable_intr_vs_det_prt0 = 1;
	//gl9a_hdmi0_intr_en_0_bx.enable_intr_scdt_prt0 = 1;
	//gl9a_hdmi0_intr_0_bx.enable_intr_plug_prt0 = 1;
	VPORT_I2C_Write((UINT32*)&gl9a_hdmi0_intr_en_0_bx);

	VPORT_I2C_Read((UINT32*)&gl9a_hdmi0_intr_en_5_bx);
	gl9a_hdmi0_intr_en_5_bx.enable_intr_chg_avi_b12345 = 1;
	VPORT_I2C_Write((UINT32*)&gl9a_hdmi0_intr_en_5_bx);

	VPORT_I2C_Read((UINT32*)&gl9a_hdmi0_intr_en_6_bx);
	//audio
	gl9a_hdmi0_intr_en_6_bx.enable_intr_2npcm_chg_pip0 = 1;
	gl9a_hdmi0_intr_en_6_bx.enable_intr_2pcm_chg_pip0 = 1;
	gl9a_hdmi0_intr_en_6_bx.enable_intr_fs_chg_pip0 = 1;
	//video
	gl9a_hdmi0_intr_en_6_bx.enable_intr_vf_stable = 1;
	gl9a_hdmi0_intr_en_6_bx.enable_intr_chg_vsi_vformat = 1;
	gl9a_hdmi0_intr_en_6_bx.enable_intr_chg_avi_to_ycc444 = 1;
	gl9a_hdmi0_intr_en_6_bx.enable_intr_chg_avi_to_ycc422 = 1;
	gl9a_hdmi0_intr_en_6_bx.enable_intr_chg_avi_to_rgb = 1;
	VPORT_I2C_Write((UINT32*)&gl9a_hdmi0_intr_en_6_bx);

	/* implement interrupt for L9A B0 */
	if (request_irq(L9_IRQ_HDMI1, HDMI_L9_IRQHandler, 0, "hdmi", NULL))
	{
		HDMI_ERROR("request_irq  is failed\n");
	}

	HDMI_ERROR("HDMI_L9_EnableInterrupt\n");

	return;
}

#ifdef	KDRV_CONFIG_PM
int HDMI_L9_RunSuspend(void)
{
	int ret = -1;

	return ret;

}

int HDMI_L9_RunResume(void)
{

	int ret = -1;

	return ret;

}
#endif
