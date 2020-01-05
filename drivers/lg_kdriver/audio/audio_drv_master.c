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


/** @file	audio_kdrv_master.c
 *
 *  main driver implementation for  audio master device.
 *  audio master device will teach you how to make device driver with new platform.
 *
 *  author	wonchang.shin (wonchang.shin@lge.com)
 *  version	0.1
 *  date		2012.04.25
 *  note		Additional information.
 *
 *  @addtogroup lg1150_audio
 *	@{
 */


#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>    /**< For isr */
#include <linux/irq.h>			/**< For isr */
#include <linux/ioport.h>		/**< For request_region, check_region etc */
#include <linux/rmap.h>
#include <linux/kthread.h>
#include <asm/io.h>				/**< For ioremap_nocache */
#include <asm/memory.h>
#include <asm/uaccess.h>
#include <linux/poll.h>
#include <linux/version.h>

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"

#include "debug_util.h"
#include "audio_cfg.h"
#include "audio_drv.h"
#include "audio_reg.h"
#include "sys_regs.h"	//for CTOP CTRL Reg. map

#include "audio_imc_func.h"
#include "audio_buffer.h"

#include "audio_drv_master.h"
#include "audio_drv_debug.h"
#include "audio_drv_manager.h"
#include "audio_drv_decoder.h"
#include "audio_drv_renderer.h"

#define NUM_OF_AUD_PRINT_TYPE		12
#define NUM_OF_AUD_PRINT_COLOR	8

#undef ENABLE_SE_PARAM_DEBUG

#define NUM_OF_LGSEFN004MODE1_BASIC_PARAM	2
#define NUM_OF_LGSEFN004MODE1_PARAM			5

// for multichannel speakers
#define	DEFAULT_I2S_CH		2
#define DEFAULT_NUM_OF_I2S	1

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
/* define AUDIO register */
extern volatile LX_AUD_REG_T		*g_pRealRegAud;
extern LX_AUD_REG_T					*g_pTempRegAud;

extern LX_AUD_KDRV_T				g_AudKdrv;

//define register address
extern LX_AUD_REG_CFG_T 			g_stAudRegCfg[];
extern LX_AUD_REG_CFG_T 			*pstAudRegCfg;
extern LX_AUD_MEM_CFG_S_T 			*pstMemCfgAud;
extern UINT32						*g_pui32SEParamVirAddr;

extern UINT32						g_audModIpcPrint;
extern SINT32						g_AudDebugFd;
extern UINT32						g_audIpcPrintCheckErrorFlag;

extern UINT8	*allocMod_Str[ADEC_MODULE_MOD_MAX+1];
extern UINT8	*modTypeStr[LX_AUD_MOD_TYPE_MAX+1];
extern UINT8	*allocDev_Str[AUD_DEV_MAX+1];
extern UINT8	*devTypeStr[LX_AUD_DEV_TYPE_MAX+1];

extern AUD_RENDER_INFO_T	_gRenderInfo[DEV_REN_NUM];

extern BOOLEAN	g_bEnableDspMonitor;

// DTO Rate
extern LX_AUD_CLOCK_SRC_T	g_setClockSrc;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
AUD_MASTER_INFO_T	_gMasterInfo;

//This value is set by ADEC_DRV_InitModule function
LX_AUD_MASTER_SPDIF_OUTPUT_T	g_AudSpdifOutputType   = LX_AUD_MASTER_SPDIF_PCM;
static struct task_struct 		*_gpstAudioMonitorTask = NULL;		//Audio Monitor task

/* AUDIO Debug Print Type */
UINT8 *ui8AudPrintType[NUM_OF_AUD_PRINT_TYPE]  =
						{ "AUD_PRINT", 	   "AUD_TRACE", 	"AUD_ISR_DEBUG",	\
						  "AUD_MIP_DEBUG", "AUD_ERROR", 	"AUD_DEBUG",	\
						  "AUD_DEBUG_TMP", "AUD_IPC_DEBUG", "AUD_IPC_MSG",	\
						  "AUD_MIP_I2C", };

/* AUDIO Debug Print Color */
UINT8 *ui8AudPrintColor[NUM_OF_AUD_PRINT_COLOR] = {
			"COLOR_BLACK",
			"COLOR_RED",
			"COLOR_GREEN",
			"COLOR_YELLOW",
			"COLOR_BLUE",
			"COLOR_PURPLE",
			"COLOR_CYAN",
			"COLOR_GRAY",
};

// For SPDIF Output PCM Connection
static UINT32 _gSpdifOutPcmCnt = 0;

// ResetConnect
static UINT32	_gPreConnectDev[LX_AUD_MASTER_OUTPUT_MAX] = {AUD_DEV_MAS0, AUD_DEV_MAS0, AUD_DEV_MAS0, 0};

static SINT32 AUDIO_SetVolume ( LX_AUD_MASTER_CONFIG_VOLUME_T *pVolumeConfig );
static SINT32 AUDIO_SetMute ( LX_AUD_MASTER_CONFIG_MUTE_T *pMuteConfig );
static SINT32 AUDIO_SetDelay ( LX_AUD_MASTER_CONFIG_DELAY_T *pDelayConfig );
static SINT32 AUDIO_SetOutMode ( LX_AUD_MASTER_CONFIG_OUT_MODE_T *pOutModeConfig );
static SINT32 AUDIO_SetSpdifOutput ( LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T *pSpdifOutputConfig );
static SINT32 AUDIO_GetSpdifOutput ( LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T *pSpdifOutputConfig );
static SINT32 AUDIO_SetSpdifScms( LX_AUD_MASTER_CONFIG_SPDIF_SCMS_T *pSpdifScmsConfig );
static SINT32 AUDIO_SetBalance ( LX_AUD_MASTER_CONFIG_BALANCE_T *pBalanceConfig );
static SINT32 AUDIO_SetBass ( LX_AUD_MASTER_CONFIG_BASS_T *pBassConfig );
static SINT32 AUDIO_SetTreble ( LX_AUD_MASTER_CONFIG_TREBLE_T *pTrebleConfig );
static SINT32 AUDIO_SetADCInputPort ( UINT32 adcInputPort );
static SINT32 AUDIO_SetPowerCtrl ( LX_AUD_MASTER_CONFIG_POWER_CTRL_T *pPowerCtrlConfig );
static SINT32 AUDIO_SetSpeakerOutput ( LX_AUD_MASTER_CONFIG_SPK_OUTPUT_T *pSpkOutputConfig );
static SINT32 AUDIO_SetSEFunction ( LX_AUD_MASTER_PARAM_SE_FN_T *pSeFnParam );
static SINT32 AUDIO_GetSEFunction ( LX_AUD_MASTER_PARAM_SE_FN_T *pSeFnParam );
static SINT32 AUDIO_SetMixerDelay ( LX_AUD_MASTER_CONFIG_MIXER_DELAY_T *pMixerDelayConfig );
static SINT32 AUDIO_SetMixerVolume ( LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T *pMixerVolumeConfig );
static SINT32 AUDIO_SetDacVolume(LX_AUD_MASTER_CONFIG_DAC_VOLUME_T  *pDacVolumeConfig);
static SINT32 AUDIO_SetDacMute(LX_AUD_MASTER_CONFIG_DAC_MUTE_T  *pDacMuteConfig);
static SINT32 AUDIO_SetEvent(LX_AUD_EVENT_TYPE_T *pEvent);
static SINT32 AUDIO_GetEvent(LX_AUD_EVENT_TYPE_T *pEvent);
static SINT32 AUDIO_ConnectOutput (UINT32 connectDev, LX_AUD_MASTER_OUTPUT_T output, UINT32 bUseSE);
static SINT32 AUDIO_DisconnectOutput (UINT32 connectDev, LX_AUD_MASTER_OUTPUT_T output);
static AUD_SE_FN_MODE_T AUDIO_GetSeFnMode(LX_AUD_MASTER_SE_FN_T seFnMode);
static SINT32 AUDIO_EnableSoundBar (LX_AUD_MASTER_SOUNDBAR_T bOnOff);
static SINT32 AUDIO_SetSoundBarParam (LX_AUD_MASTER_SOUNDBAR_PARAM_T *pSoundbarParam);
static SINT32 AUDIO_GetSoundBarStatus (LX_AUD_MASTER_SOUNDBAR_STATUS_T *pSoundbarStatus );
static SINT32 AUDIO_SetSoundBarPower (UINT32 bOnOff);
static SINT32 AUDIO_SetSpdifOnOff(UINT32 bOnOff);
static SINT32 AUDIO_SetI2SNum(UINT32 num);

/**
 * Register Notification.
 * @param 	pMasterInfo		[in] Master information.
 * @param 	pFuncImcNoti	[in] pointer to callback function.
 * @param 	allocMod		[in] allocated module.
 * @param 	event			[in] event.
 * @return 	void.
 * @see		().
 */
static void _AUDIO_RegisterMasterNoti(
	AUD_MASTER_INFO_T* pMasterInfo,
	PFN_ImcNoti	pFuncImcNoti,
	UINT32 allocMod,
	UINT32 event,
	IMC_ACTION_REPEAT_TYPE repeatType,
	SINT32 notiLevel)
{
	UINT32							actionID;
	AUD_EVENT_T						*pMasterEvent = NULL;
	ImcActionParameter 				actionParam;

	if(pMasterInfo->ui32EventNum >= AUD_EVENT_NUM)
	{
		AUD_KDRV_ERROR("MasterEventNum(%d) is over AUD_EVENT_NUM. \n", pMasterInfo->ui32EventNum);
		return;
	}

	actionParam.actionType = IMC_ACTION_GET_CALLBACK;
	actionParam.repeatType = repeatType;
	actionParam.target = ADEC_MODULE_MAN_ARM;
	actionParam.actionParam.notiParam.noti = (PFN_ImcNoti)pFuncImcNoti;
	actionParam.actionParam.notiParam.param = pMasterInfo;
	actionParam.actionParam.notiParam.level = notiLevel;
	IMC_RegisterEvent(IMC_GetLocalImc(0), event, allocMod, &actionID, &actionParam);

	if(repeatType != IMC_ACTION_ONCE)
	{
		pMasterEvent = &pMasterInfo->mstEvent[pMasterInfo->ui32EventNum];
		pMasterEvent->event = event;
		pMasterEvent->actionID = actionID;
		pMasterEvent->moduleID = allocMod;
		pMasterInfo->ui32EventNum++;
	}

	AUD_KDRV_PRINT("%s [0x%x 0x%x, 0x%x] \n", __F__, event, actionID, allocMod);
	return;
}

/**
 * Initialize master Information.
 * @param 	void
 * @return 	void
 * @see		KDRV_AUDIO_OpenMaster
 */
static void _AUDIO_InitMasterInfo(void)
{
	AUD_OUT_CTRL_MODULE_T audOutCtrlMod[LX_AUD_MASTER_OUTPUT_MAX] =
	{
		// ADEC_MODULE_ID, 			ui32Volume,	ui32Mute,	ui32Delay,	ui32Balance, 	outMode,				ui32ConnectDev,		ui32UseSE
		{ ADEC_MODULE_OUT_CTRL_0, 	0x800000, 	0, 			0, 			50,				LX_AUD_MASTER_OUT_LR,	AUD_DEV_MAS0,		TRUE},
		{ ADEC_MODULE_OUT_CTRL_1,	0x800000,	0,			0,			50,				LX_AUD_MASTER_OUT_LR,	AUD_DEV_MAS0,		FALSE},
		{ ADEC_MODULE_OUT_CTRL_2,	0x800000,	0,			0,			50,				LX_AUD_MASTER_OUT_LR,	AUD_DEV_MAS0,		FALSE},
		{ ADEC_MODULE_OUT_CTRL_3,	0x800000,	0,			0,			50,				LX_AUD_MASTER_OUT_LR,	AUD_NO_DEV,			FALSE},
	};

	memset(&_gMasterInfo, 0, sizeof(AUD_MASTER_INFO_T));

	_gMasterInfo.ui32AllocDev 	   = AUD_NO_DEV;
	_gMasterInfo.spdifSamplingFreq = LX_AUD_SAMPLING_FREQ_48_KHZ;

	memcpy(&(_gMasterInfo.outCtrlMod[LX_AUD_MASTER_OUTPUT_SPEAKER]),
		   &audOutCtrlMod[LX_AUD_MASTER_OUTPUT_SPEAKER],
		   sizeof(AUD_OUT_CTRL_MODULE_T)*LX_AUD_MASTER_OUTPUT_MAX);

	_gMasterInfo.soundBarStatus.ui32SoundBarOnOff = FALSE;
	_gMasterInfo.soundBarStatus.ui32WirelessOnOff = FALSE;

	_gMasterInfo.ui32I2SNum = DEFAULT_NUM_OF_I2S;

	//Initialize AUDIO SPDIF semaphore
	OS_InitMutex(&_gMasterInfo.spdifSemaphore, OS_SEM_ATTR_DEFAULT);

	return;
}

/**
 * Sound Bar Status Callback function.
 * @param 	_param			[out] parameters.
 * @param 	_paramLen		[out] length of parameters.
 * @param 	_cbParam		[in] callback parameters.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		AUDIO_SetSoundBarParam
 */
static SINT32 _AUDIO_MstSoundBarStatusCb(void* _param, int _paramLen, void* _cbParam)
{
	SpdifEvtGetFmtForSoundbar *pSoundBarStatus = NULL;

	pSoundBarStatus = (SpdifEvtGetFmtForSoundbar*)_param;

	_gMasterInfo.soundBarStatus.ui32SubFrameID = pSoundBarStatus->id;
	_gMasterInfo.soundBarStatus.ui32SubFrameData = pSoundBarStatus->data;
	_gMasterInfo.soundBarStatus.ui32SubFrameCheckSum = pSoundBarStatus->checksum;

	// Print For Debug
	if(_paramLen != sizeof(SpdifEvtGetFmtForSoundbar))
	{
		AUD_KDRV_ERROR("SoundBar Status : Param Length Error[Expected:%d][Input:%d]\n", sizeof(SpdifEvtGetFmtForSoundbar), _paramLen);
		return RET_ERROR;
	}

	AUD_KDRV_DEBUG("SoundBar Status : id(0x%x), data(0x%x), res(0x%x), CS(0x%x)\n", \
					pSoundBarStatus->id, pSoundBarStatus->data, pSoundBarStatus->reserved, pSoundBarStatus->checksum);
	return RET_OK;
}

/**
 * DTO_A Rate Callback function.
 * @param 	_param			[out] parameters.
 * @param 	_paramLen		[out] length of parameters.
 * @param 	_cbParam		[in] callback parameters.
 * @return 	if succeeded - RET_OK, else - RET_ERROR.
 * @see		KDRV_AUDIO_OpenMaster
 */
static SINT32 _AUDIO_MstDtoARateCb(void* _param, int _paramLen, void* _cbParam)
{
	DtoEvtChangeDtoRate	*pDtoRate = NULL;

	pDtoRate = (DtoEvtChangeDtoRate*)_param;

	if(_paramLen != sizeof(DtoEvtChangeDtoRate))
	{
		AUD_KDRV_ERROR("Param Length Error : [Expected:%d][Input:%d]\n", sizeof(DtoEvtChangeDtoRate), _paramLen);
		return RET_ERROR;
	}

	//Lock a AUDIO SPDIF Semaphore, Do not use spin lock
	OS_LockMutex(&_gMasterInfo.spdifSemaphore);

	//Set a decoder sampling frequency and DTO rate
	#ifdef USE_DTO_AAD
	(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(_gMasterInfo.spdifSamplingFreq, pDtoRate->dto_rate, AUD_DTO_AAD);
	#else
	(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(_gMasterInfo.spdifSamplingFreq, pDtoRate->dto_rate, AUD_DTO_A);
	#endif
	//Unlock a AUDIO SPDIF Semaphore
	OS_UnlockMutex(&_gMasterInfo.spdifSemaphore);

	AUD_KDRV_DEBUG("DTO_A Rate(%d)\n", pDtoRate->dto_rate);
	return RET_OK;
}


/**
 * Alloc Master's Modules.
 * @param 	void
 * @return 	void
 * @see		KDRV_AUDIO_OpenMaster
 */
static SINT32 _AUDIO_AllocMaster(LX_AUD_ALLOC_DEV_T allocDev)
{
	UINT32					modTypeToAlloc;
	UINT32					allocMod_MIX = ADEC_MODULE_NO_MOD;
	UINT32					allocMod_SE = ADEC_MODULE_NO_MOD;
	UINT32					allocMod_OUT_CTRL_0 = ADEC_MODULE_NO_MOD;
	ADEC_MODULE_ID			managerModule;
	CmCmdDisconnect			disconnectParam;
	ImcCmdFlushParam		flushParam;
	AUD_MASTER_INFO_T		*pMstInfo = NULL;

	pMstInfo = &_gMasterInfo;

	modTypeToAlloc = LX_AUD_MIX;
	allocMod_MIX = AUDIO_AllocModule(allocDev, modTypeToAlloc, 0);
	if(allocMod_MIX != ADEC_MODULE_NO_MOD )
	{
		AUD_KDRV_RM("Module[%s] is alloc [Alloc:%s] \n", modTypeStr[modTypeToAlloc], (char *)allocMod_Str[allocMod_MIX]);
	}
	else
	{
		AUD_KDRV_ERROR(" Module[%s] is not available ret[%d] \n", modTypeStr[modTypeToAlloc], allocMod_MIX);
		return RET_ERROR;
	}

	modTypeToAlloc	= LX_AUD_SE;
	allocMod_SE = AUDIO_AllocModule(allocDev, modTypeToAlloc, 0);
	if(allocMod_SE != ADEC_MODULE_NO_MOD )
	{
		AUD_KDRV_RM("Module[%s] is alloc [Alloc:%s] \n",modTypeStr[modTypeToAlloc], (char *)allocMod_Str[allocMod_SE]);
	}
	else
	{
		AUDIO_FreeModule(allocMod_MIX,allocDev);
		AUD_KDRV_ERROR(" Module[%s] is not available ret[%d] \n",modTypeStr[modTypeToAlloc], allocMod_SE);
		return RET_ERROR;
	}

	modTypeToAlloc	= LX_AUD_OUT_CTRL;
	allocMod_OUT_CTRL_0 = AUDIO_AllocModule(allocDev, modTypeToAlloc, 0);
	if(allocMod_OUT_CTRL_0 != ADEC_MODULE_NO_MOD )
	{
		AUD_KDRV_RM("Module[%s] is alloc [Alloc:%s] \n",modTypeStr[modTypeToAlloc], (char *)allocMod_Str[allocMod_OUT_CTRL_0]);
	}
	else
	{
		AUDIO_FreeModule(allocMod_OUT_CTRL_0,allocDev);
		AUDIO_FreeModule(allocMod_MIX,allocDev);
		AUD_KDRV_ERROR(" Module[%s] is not available ret[%d] \n",modTypeStr[modTypeToAlloc], allocMod_OUT_CTRL_0);
		return RET_ERROR;
	}

	#if 0	// Stop/Flushing Mixer module causes DSP latched up. Kyungsoon.Jung
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, allocMod_MIX);
	#endif
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, allocMod_SE);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, allocMod_OUT_CTRL_0);

	#if 0	// Stop/Flushing Mixer module causes DSP latched up. Kyungsoon.Jung
	memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, allocMod_MIX, sizeof(ImcCmdFlushParam), &flushParam);
	#endif

	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, allocMod_SE, sizeof(ImcCmdFlushParam), &flushParam);

	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, allocMod_OUT_CTRL_0, sizeof(ImcCmdFlushParam), &flushParam);

	managerModule = _AUDIO_GetManagerModule(allocMod_SE);
	disconnectParam.module = allocMod_SE;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);
	AUD_KDRV_RM("[%11s]       ----  X  ----      [%11s] disconnection OKl\n", allocMod_Str[allocMod_MIX],allocMod_Str[allocMod_SE]);

	managerModule = _AUDIO_GetManagerModule(allocMod_OUT_CTRL_0);
	disconnectParam.module = allocMod_OUT_CTRL_0;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, allocMod_OUT_CTRL_0, sizeof(CmCmdDisconnect), &disconnectParam);
	AUD_KDRV_RM("[%11s]       ----  X  ----      [%11s] disconnection OKl\n", allocMod_Str[allocMod_SE],allocMod_Str[allocMod_OUT_CTRL_0]);

	if(AUDIO_IsNotConnectedYet(allocMod_MIX, allocMod_SE))
	{
		AUDIO_ConnectTo(allocMod_MIX, allocMod_SE, NO_FORCE, NO_FORCE);
	}

	if(AUDIO_IsNotConnectedYet(allocMod_SE, allocMod_OUT_CTRL_0))
	{
		AUDIO_ConnectTo(allocMod_SE, allocMod_OUT_CTRL_0, NO_FORCE, NO_FORCE);
	}

	// Disconnect default connection of SPDIF on DSP
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_SPDIF);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_CTRL_3);

	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, ADEC_MODULE_OUT_SPDIF, sizeof(ImcCmdFlushParam), &flushParam);

	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, ADEC_MODULE_OUT_CTRL_3, sizeof(ImcCmdFlushParam), &flushParam);

	managerModule = _AUDIO_GetManagerModule(ADEC_MODULE_OUT_SPDIF);
	disconnectParam.module = ADEC_MODULE_OUT_SPDIF;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);

	managerModule = _AUDIO_GetManagerModule(ADEC_MODULE_OUT_CTRL_3);
	disconnectParam.module = ADEC_MODULE_OUT_CTRL_3;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);

	#if 0	// Stop/Flushing Mixer module causes DSP latched up. Kyungsoon.Jung
	AUDIO_IMC_SendCmd(ADEC_CMD_START,allocMod_MIX);
	#endif

	AUDIO_IMC_SendCmd(ADEC_CMD_START,allocMod_SE);
	AUDIO_IMC_SendCmd(ADEC_CMD_START,allocMod_OUT_CTRL_0);

	// Register DTO Rate Callback function
	_AUDIO_RegisterMasterNoti(pMstInfo, (PFN_ImcNoti)_AUDIO_MstDtoARateCb, ADEC_MODULE_DTO_A, DTO_EVT_CHANGE_DTO_RATE, IMC_ACTION_REPEAT, 1);

	return RET_OK;
}

/**
 * Dealloc Master's Modules.
 * @param 	void
 * @return 	void
 * @see		KDRV_AUDIO_OpenMaster
 */
static SINT32 _AUDIO_DeallocMaster(LX_AUD_ALLOC_DEV_T allocDev)
{
	UINT32					allocModNum = 0;
	UINT32					i = 0;
	AUD_EVENT_T				*pMstEvent = NULL;
	LX_AUD_MOD_T			*pOwnMods;
	LX_AUD_ALLOC_FREE_INFO_T * freeDEV;

	if( allocDev != AUD_DEV_MAS0)
	{
		AUD_KDRV_ERROR("%s: allocDev [%d]\n",__FUNCTION__,allocDev);
		return RET_ERROR;
	}

	AUDIO_GetAllocInfo(allocDev, &allocModNum , &pOwnMods);




	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_PCM);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_MIX_0);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_CTRL_0);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_CTRL_1);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_CTRL_2);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_OUT_CTRL_3);
	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_ESOUT_CTRL);

	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, ADEC_MODULE_SE);

	// Disconnect modules in Master
	AUDIO_DisconnectAllInDev(allocDev);

	// Free modules in Master
	for(i = 0; i < allocModNum; i++)
	{
		AUDIO_FreeModule(pOwnMods[i].mod, allocDev);
	}

	freeDEV = &DevInfo.list[allocDev];
	freeDEV->headOfDev			= NULL;
	freeDEV->tailOfDev		= NULL;

	// Initialize Event
	for(i = 0; i < _gMasterInfo.ui32EventNum; i++)
	{
		pMstEvent = &(_gMasterInfo.mstEvent[i]);
		IMC_CancelEvent(IMC_GetLocalImc(0), pMstEvent->event , pMstEvent->moduleID, pMstEvent->actionID);
	}

	_gMasterInfo.ui32EventNum = 0;

	return RET_OK;
}

/**
 * open handler for audio master device
 *
 */
SINT32	KDRV_AUDIO_OpenMaster(struct inode *inode, struct file *filp)
{
	UINT32		nMajor;
	UINT32		nMinor;
	UINT32		devType;

	AUD_DEVICE_T	*my_dev;

	struct cdev					*pCdev;

	LX_AUD_ALLOC_FREE_INFO_T	OpenInfo;
	LX_AUD_ALLOC_DEV_T			allocDevice = AUD_NO_DEV;

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	pCdev	= inode->i_cdev;
	my_dev	= container_of(pCdev, AUD_DEVICE_T, cdev);
	filp->private_data = my_dev;

	devType = DEV_TYPE_BASE + nMinor;
	my_dev->devType = devType;

	my_dev->openCount++;
	if(my_dev->isInit == TRUE)
	{
		my_dev->allocDev = AUD_DEV_MAS0;

		AUD_KDRV_PRINT("%s.%d: openCount is %u\n", __FUNCTION__, __LINE__, my_dev->openCount);
		return RET_OK;
	}

	AUDIO_DevInfoInit();
	_AUDIO_InitMasterInfo();

	OpenInfo.devType = devType;

	allocDevice = AUDIO_AllocDev(&OpenInfo);
	if(allocDevice != AUD_NO_DEV)
	{
		AUD_KDRV_RM("%s is opened[major:%d minor:%d][Alloc:%s] \n",	\
					 devTypeStr[devType], nMajor, nMinor, allocDev_Str[(UINT32)allocDevice]);

		if(my_dev->isInit != TRUE)
		{
			//Initializes the audio module.
			AUDIO_InitModule();

			my_dev->isInit = TRUE;
		}

		my_dev->allocDev =  allocDevice ;
	}
	else
	{
		AUD_KDRV_RM("%s is not available ret[%d] \n", devTypeStr[devType], (UINT32)allocDevice);
		return RET_ERROR;
	}

	_AUDIO_AllocMaster(my_dev->allocDev);

	// create audio master monitor task
	if(_gpstAudioMonitorTask == NULL)
	{
		_gpstAudioMonitorTask = kthread_run(AUDIO_MonitorTask, NULL, "AUD-KDRV-TASK");

		if (_gpstAudioMonitorTask != NULL)
			AUD_KDRV_PRINT("%s.%d: Monitor task is created\n", __FUNCTION__, __LINE__);
		else
			AUD_KDRV_ERROR("%s.%d: Monitor task creation ERR!!!\n", __FUNCTION__, __LINE__);
	}

	AUD_KDRV_PRINT("Open Master device file (%d:%d)\n", nMajor, nMinor);
	return RET_OK;
}

/**
 * close handler for audio master device
 *
 */
SINT32 KDRV_AUDIO_CloseMaster(struct inode *inode, struct file *filp)
{
	UINT32		nMajor;
	UINT32		nMinor;
	SINT32		freeDevice = 0;

	AUD_DEVICE_T	*audDev = NULL;

	LX_AUD_ALLOC_FREE_INFO_T	closeInfo;
	LX_AUD_ALLOC_DEV_T			allocDevice;

	audDev = (AUD_DEVICE_T*)filp->private_data;

	if(audDev == NULL)
	{
		AUD_KDRV_ERROR("%s.%d: private_data is NULL\n", __FUNCTION__, __LINE__);
		return RET_ERROR;
	}

	nMajor = imajor(inode);
	nMinor = iminor(inode);

	if(audDev->openCount > 0)
		audDev->openCount--;

	if(audDev->openCount > 0)
	{
		AUD_KDRV_PRINT("%s.%d: openCount is %u\n", __FUNCTION__, __LINE__, audDev->openCount);
		return RET_OK;
	}

	AUD_KDRV_PRINT("%s.%d: openCount is %u\n", __FUNCTION__, __LINE__, audDev->openCount);

	/* Set a audio master device */
	allocDevice = audDev->devType;

	closeInfo.devType 	 = audDev->devType;
	closeInfo.allocDev = allocDevice;

	freeDevice = AUDIO_FreeDev(&closeInfo);

	if(freeDevice != AUD_NO_DEV)
	{
		AUD_KDRV_RMD("%d(%s) is closed[Freed:%s]\n", freeDevice, devTypeStr[audDev->devType], (char *)allocDev_Str[allocDevice] );
	}
	else
	{
		AUD_KDRV_RMD(" All %d(%s) is already freed \n", freeDevice, devTypeStr[audDev->devType]);
	}

	kfree(audDev);

	// release monitor task
	if(_gpstAudioMonitorTask != NULL)
	{
		kthread_stop(_gpstAudioMonitorTask);
		_gpstAudioMonitorTask = NULL;

		AUD_KDRV_PRINT("Stop monitor task\n");
	}

	AUD_KDRV_RMD("Close Master device file(%d:%d)\n", nMajor, nMinor);
	return RET_OK;
}

/**
 * ioctl handler for audio master device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int KDRV_AUDIO_IoctlMaster(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
#else
long KDRV_AUDIO_IoctlMaster(struct file *filp, unsigned int cmd, unsigned long arg)
#endif
{
	int					retVal = 0;
	int					err = 0;
	AUD_DEVICE_T*	my_dev;

	my_dev = (AUD_DEVICE_T*)filp->private_data;

	/*
	* check if IOCTL command is valid or not.
	* - if magic value doesn't match, return error (-ENOTTY)
	* - if command is out of range, return error (-ENOTTY)
	*
	* note) -ENOTTY means "Inappropriate ioctl for device.
	*/
	if (_IOC_TYPE(cmd) != AUD_MASTER_IOC_MAGIC)
	{
		DBG_PRINT_WARNING("invalid magic. magic=0x%02X\n", _IOC_TYPE(cmd) );
		return -ENOTTY;
	}
	if (_IOC_NR(cmd) > AUD_MASTER_IOC_MAXNR)
	{
		DBG_PRINT_WARNING("out of ioctl command. cmd_idx=%d\n", _IOC_NR(cmd) );
		return -ENOTTY;
	}

	/*
	* check if user memory is valid or not.
	* if memory can't be accessed from kernel, return error (-EFAULT)
	*/
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err =  !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err)
	{
		DBG_PRINT_WARNING("memory access error. cmd_idx=%d, rw=%c%c, memptr=%p\n",
							_IOC_NR(cmd),
							(_IOC_DIR(cmd) & _IOC_READ)? 'r':'-',
							(_IOC_DIR(cmd) & _IOC_WRITE)? 'w':'-',
							(void*)arg );
		return -EFAULT;
	}

	AUD_KDRV_TRACE("cmd = %08X (cmd_idx=%d)\n", cmd, _IOC_NR(cmd) );

	switch(cmd)
	{
		case AUD_MASTER_IOW_SET_VOLUME:
		{
			LX_AUD_MASTER_CONFIG_VOLUME_T		volumeConfig;

			AUD_KDRV_TRACE("IOCTL Set Volume!!!\n");

			if ( copy_from_user(&volumeConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_VOLUME_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetVolume(&volumeConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_DAC_VOLUME:
		{
			LX_AUD_MASTER_CONFIG_DAC_VOLUME_T		dacVolumeConfig;

			AUD_KDRV_TRACE("IOCTL Set DAC Volume!!!\n");

			if ( copy_from_user(&dacVolumeConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_DAC_VOLUME_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetDacVolume(&dacVolumeConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_MUTE:
		{
			LX_AUD_MASTER_CONFIG_MUTE_T		muteConfig;

			AUD_KDRV_TRACE("IOCTL Set Mute!!!\n");

			if ( copy_from_user(&muteConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_MUTE_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetMute(&muteConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_DAC_MUTE:
		{
			LX_AUD_MASTER_CONFIG_DAC_MUTE_T		dacMuteConfig;

			AUD_KDRV_TRACE("IOCTL Set DAC Mute!!!\n");

			if ( copy_from_user(&dacMuteConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_DAC_MUTE_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetDacMute(&dacMuteConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_DELAY:
		{
			LX_AUD_MASTER_CONFIG_DELAY_T		delayConfig;

			AUD_KDRV_TRACE("IOCTL Set Delay!!!\n");

			if ( copy_from_user(&delayConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_DELAY_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetDelay(&delayConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_OUT_MODE:
		{
			LX_AUD_MASTER_CONFIG_OUT_MODE_T		outModeConfig;

			AUD_KDRV_TRACE("IOCTL Set Out Mode!!!\n");

			if ( copy_from_user(&outModeConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_OUT_MODE_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetOutMode(&outModeConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_SPK_OUTPUT:
		{
			LX_AUD_MASTER_CONFIG_SPK_OUTPUT_T		spkOutputConfig;

			AUD_KDRV_TRACE("IOCTL Set SPEAKER Output!!!\n");

			if ( copy_from_user(&spkOutputConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_SPK_OUTPUT_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetSpeakerOutput(&spkOutputConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_SPDIF_OUTPUT:
		{
			LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T		spdifOutputConfig;

			AUD_KDRV_TRACE("IOCTL Set SPDIF Output!!!\n");

			if ( copy_from_user(&spdifOutputConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetSpdifOutput(&spdifOutputConfig);
		}
		break;

		case AUD_MASTER_IOR_GET_SPDIF_OUTPUT:
		{
			LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T		spdifOutputConfig;

			AUD_KDRV_TRACE("IOCTL Get SPDIF Output!!!\n");

			retVal = AUDIO_GetSpdifOutput(&spdifOutputConfig);

			if (copy_to_user((void *)arg, (void *)&spdifOutputConfig, sizeof(LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T)))
				return RET_ERROR;
		}
		break;

		case AUD_MASTER_IOW_SET_SPDIF_SCMS:
		{
			LX_AUD_MASTER_CONFIG_SPDIF_SCMS_T		spdifScmsConfig;

			AUD_KDRV_TRACE("IOCTL Set SPDIF SCMS!!!\n");

			if ( copy_from_user(&spdifScmsConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_SPDIF_SCMS_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetSpdifScms(&spdifScmsConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_SPDIF_ONOFF:
		{
			UINT32		setSpdifOnOff;

			AUD_KDRV_TRACE("IOCTL Set SPDIF On/OFF!!!\n");

			if ( copy_from_user(&setSpdifOnOff, (void __user *)arg, sizeof(UINT32)) )
				return RET_ERROR;

			retVal = AUDIO_SetSpdifOnOff(setSpdifOnOff);
		}
		break;

		case AUD_MASTER_IOW_SET_BALANCE:
		{
			LX_AUD_MASTER_CONFIG_BALANCE_T		balancesConfig;

			AUD_KDRV_TRACE("IOCTL Set Balance!!!\n");

			if ( copy_from_user(&balancesConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_BALANCE_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetBalance(&balancesConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_BASS:
		{
			LX_AUD_MASTER_CONFIG_BASS_T		bassConfig;

			AUD_KDRV_TRACE("IOCTL Set Bass!!!\n");

			if ( copy_from_user(&bassConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_BASS_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetBass(&bassConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_TREBLE:
		{
			LX_AUD_MASTER_CONFIG_TREBLE_T		trebleConfig;

			AUD_KDRV_TRACE("IOCTL Set TREBLE!!!\n");

			if ( copy_from_user(&trebleConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_TREBLE_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetTreble(&trebleConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_ADC_INPUT_PORT:
		{
			UINT32		adcInputPort;

			AUD_KDRV_TRACE("IOCTL Set ADC Input Port!!!\n");

			if ( copy_from_user(&adcInputPort, (void __user *)arg, sizeof(UINT32)) )
				return RET_ERROR;

			retVal = AUDIO_SetADCInputPort(adcInputPort);
		}
		break;

		case AUD_MASTER_IOW_SET_POWER_CTRL:
		{
			LX_AUD_MASTER_CONFIG_POWER_CTRL_T		powerCtrlConfig;

			AUD_KDRV_TRACE("IOCTL Set Power Ctrl!!!\n");

			if ( copy_from_user(&powerCtrlConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_POWER_CTRL_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetPowerCtrl(&powerCtrlConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_MIXER_DELAY:
		{
			LX_AUD_MASTER_CONFIG_MIXER_DELAY_T		mixerDelayConfig;

			AUD_KDRV_TRACE("IOW_SET_MIXER_DELAY!!!\n");

			if ( copy_from_user(&mixerDelayConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_MIXER_DELAY_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetMixerDelay(&mixerDelayConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_MIXER_VOLUME:
		{
			LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T		mixerVolumeConfig;

			AUD_KDRV_TRACE("IOW_SET_MIXER_DELAY!!!\n");

			if ( copy_from_user(&mixerVolumeConfig, (void __user *)arg, sizeof(LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetMixerVolume(&mixerVolumeConfig);
		}
		break;

		case AUD_MASTER_IOW_SET_SE_FN:
		{
			LX_AUD_MASTER_PARAM_SE_FN_T		seFnParam;

			AUD_KDRV_TRACE("IOCTL Set SE FN!!!\n");

			if ( copy_from_user(&seFnParam, (void __user *)arg, sizeof(LX_AUD_MASTER_PARAM_SE_FN_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetSEFunction(&seFnParam);
		}
		break;

		case AUD_MASTER_IOWR_GET_SE_FN:
		{
			LX_AUD_MASTER_PARAM_SE_FN_T		seFnParam;

			AUD_KDRV_TRACE("IOCTL Set SE FN!!!\n");

			if ( copy_from_user(&seFnParam, (void __user *)arg, sizeof(LX_AUD_MASTER_PARAM_SE_FN_T)) )
				return RET_ERROR;

			retVal = AUDIO_GetSEFunction(&seFnParam);

			if (copy_to_user((void *)arg, (void *)&seFnParam, sizeof(LX_AUD_MASTER_PARAM_SE_FN_T)))
				return RET_ERROR;
		}
		break;

		case AUD_MASTER_IOW_ENABLE_SOUNDBAR:
		{
			LX_AUD_MASTER_SOUNDBAR_T		enableSoundBar;

			AUD_KDRV_TRACE("IOCTL Enable Sound Bar!!!\n");

			if ( copy_from_user(&enableSoundBar, (void __user *)arg, sizeof(LX_AUD_MASTER_SOUNDBAR_T)) )
				return RET_ERROR;

			retVal = AUDIO_EnableSoundBar(enableSoundBar);
		}
		break;

		case AUD_MASTER_IOW_SET_SOUNDBAR_PARAM:
		{
			LX_AUD_MASTER_SOUNDBAR_PARAM_T		soundBarParam;

			AUD_KDRV_TRACE("IOCTL Set SOUNDBAR PARAM!!!\n");

			if ( copy_from_user(&soundBarParam, (void __user *)arg, sizeof(LX_AUD_MASTER_SOUNDBAR_PARAM_T)) )
				return RET_ERROR;

			retVal = AUDIO_SetSoundBarParam(&soundBarParam);
		}
		break;

		case AUD_MASTER_IOR_GET_SOUNDBAR_STATUS:
		{
			LX_AUD_MASTER_SOUNDBAR_STATUS_T		soundBarStatus;

			AUD_KDRV_TRACE("IOCTL Get SOUNDBAR STATUS!!!\n");

			retVal = AUDIO_GetSoundBarStatus(&soundBarStatus);

			if ( copy_to_user((void *)arg, (void *)&soundBarStatus, sizeof(LX_AUD_MASTER_SOUNDBAR_STATUS_T)) )
				return RET_ERROR;
		}
		break;

		case AUD_MASTER_IOW_SET_SOUNDBAR_POWER:
		{
			UINT32		setSoundBarPower;

			AUD_KDRV_TRACE("IOCTL Set Sound Bar Power!!!\n");

			if ( copy_from_user(&setSoundBarPower, (void __user *)arg, sizeof(UINT32)) )
				return RET_ERROR;

			retVal = AUDIO_SetSoundBarPower(setSoundBarPower);
		}
		break;

		case AUD_MASTER_IO_RESET_AAD_MODULE:
		{
			AUD_KDRV_TRACE("IOCTL RESET AAD MODULE!!!\n");

			retVal = AUDIO_ResetAADModule();
		}
		break;

		case AUD_MASTER_IOW_SET_EVENT:
		{
			LX_AUD_EVENT_TYPE_T	event;

			AUD_KDRV_TRACE("IOCTL Set Event\n");

			if (copy_from_user(&event, (void __user *)arg, sizeof(LX_AUD_EVENT_TYPE_T)))
				return RET_ERROR;

			retVal = AUDIO_SetEvent(&event);
		}
		break;

		case AUD_MASTER_IORW_GET_EVENT:
		{
			LX_AUD_EVENT_TYPE_T	event;

			AUD_KDRV_TRACE("IOCTL Get Event\n");

			if (copy_from_user(&event, (void __user *)arg, sizeof(LX_AUD_EVENT_TYPE_T)))
				return RET_ERROR;

			retVal = AUDIO_GetEvent(&event);

			if (copy_to_user((void *)arg, (void *)&event, sizeof(LX_AUD_EVENT_TYPE_T)))
				return RET_ERROR;
		}
		break;

		case AUD_MASTER_IOW_SET_I2S_NUM:
		{
			UINT32		i2sNum;

			AUD_KDRV_TRACE("IOCTL Set I2S Number!!!\n");

			if ( copy_from_user(&i2sNum, (void __user *)arg, sizeof(UINT32)) )
				return RET_ERROR;

			retVal = AUDIO_SetI2SNum(i2sNum);
		}
		break;

		case AUD_MASTER_IOR_GET_GSTC:
		{
			UINT32	gstc;

			AUD_KDRV_TRACE("IOCTL Get GSTC\n");

			if (copy_from_user(&gstc, (void __user *)arg, sizeof(UINT64)))
				return RET_ERROR;

			AUD_RdFL(aud_gstcc0lreg);
			gstc = AUD_Rd(aud_gstcc0lreg);

			if (copy_to_user((void *)arg, (void *)&gstc, sizeof(UINT64)))
				return RET_ERROR;
		}
		break;


		case AUD_IOW_CUSTOM_IMC:
		{
			LX_AUD_CUSTOM_IMC_T			customImc;

			AUD_KDRV_TRACE("AUD_IOW_CUSTOM_IMC\n");

			if ( copy_from_user(&customImc, (void __user *)arg, sizeof(LX_AUD_CUSTOM_IMC_T)) )
				return RET_ERROR;

			(void)KDRV_AUDIO_CustomImc(&customImc);

		}
		break;

		case AUD_IOWR_READ_AND_WRITE_REG:
		{
			LX_AUD_REG_INFO_T		regInfo;

			memset(&regInfo, 0x0, sizeof(LX_AUD_REG_INFO_T));

			AUD_KDRV_TRACE("AUD_IORW_READ_AND_WRITE_REG\n");

			if(copy_from_user(&regInfo, (void __user *)arg, sizeof(LX_AUD_REG_INFO_T)))
				return RET_ERROR;

			(void)KDRV_AUDIO_ReadAndWriteReg(&regInfo);

			if(copy_to_user((void *)arg, (void *)&regInfo, sizeof(LX_AUD_REG_INFO_T)))
				return RET_ERROR;
		}
		break;

		case AUD_IOW_DEBUG_PRINT_CTRL:
		{
			LX_AUD_DEBUG_CTRL_T	debugCtrl;

			memset(&debugCtrl, 0x0, sizeof(LX_AUD_DEBUG_CTRL_T));

			AUD_KDRV_TRACE("AUD_IOW_DEBUG_PRINT_CTRL\n");

			if(copy_from_user( &debugCtrl, (void __user *)arg, sizeof(LX_AUD_DEBUG_CTRL_T)))
				return RET_ERROR;


			if((debugCtrl.printType >= NUM_OF_AUD_PRINT_TYPE) || (debugCtrl.printColor >= NUM_OF_AUD_PRINT_COLOR) )
			{
				AUD_KDRV_ERROR("Check Argument\n" );
				return RET_ERROR;
			}

			if(debugCtrl.printColor == DBG_COLOR_NONE)
			{
				OS_DEBUG_DisableModuleByIndex(g_AudDebugFd, debugCtrl.printType);
				AUD_KDRV_ERROR("AUD_PRINT_TYPE[%s] is disabled.\n", ui8AudPrintType[debugCtrl.printType]);
			}
			else
			{
				OS_DEBUG_EnableModuleByIndex(g_AudDebugFd, debugCtrl.printType, debugCtrl.printColor);
				AUD_KDRV_ERROR("AUD_PRINT_TYPE[%s] is enabled Color is [%s].\n", ui8AudPrintType[debugCtrl.printType], ui8AudPrintColor[debugCtrl.printColor - 1]);
			}

			return RET_OK;
 		}
		break;

		/* Download DSP0 Image for test */
		case AUD_MASTER_DOWNALOD_DSP0:
		{
			LX_AUD_CODEC_T		codecType;

			AUD_KDRV_TRACE("IOCTL Download DSP0 Image!!!\n");

			if(copy_from_user(&codecType, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			retVal = AUDIO_LoadDSP0Codec();
		}
		break;

		/* Download DSP1 Image for test */
		case AUD_MASTER_DOWNALOD_DSP1:
		{
			LX_AUD_CODEC_T		codecType;

			AUD_KDRV_TRACE("IOCTL Download DSP1 Image!!!\n");

			if(copy_from_user(&codecType, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			retVal = AUDIO_LoadDSP1Codec();
		}
		break;

		case AUD_IOW_DEBUG_MEM_DUMP:
		{
			LX_AUD_DEBUG_MEM_DUMP_T		memDump;

			AUD_KDRV_TRACE("IOCTL Download DSP1 Image!!!\n");

			if(copy_from_user(&memDump, (void __user *)arg, sizeof(LX_AUD_DEBUG_MEM_DUMP_T)))
				return RET_ERROR;

			AUDIO_ShowMemoryDump(&memDump);
 		}
		break;

		case AUD_IO_DEBUG_ALLOC_INFO:
		{
			AUDIO_UpdateConnectionInfo();
 		}
		break;

		case AUD_IOWR_DEBUG_GET_MOD_INFO:
		{
			LX_AUD_DEBUG_MOD_INFO_T		modInfo;

			memset(&modInfo, 0x0, sizeof(LX_AUD_DEBUG_MOD_INFO_T));

			AUD_KDRV_TRACE("AUD_IOW_DEBUG_GET_MOD_INFO\n");

			if(copy_from_user( &modInfo, (void __user *)arg, sizeof(LX_AUD_DEBUG_MOD_INFO_T)))
				return RET_ERROR;

			(void)KDRV_AUDIO_GetModIdFromStr(&modInfo);

			if(copy_to_user((void *)arg, (void *)&modInfo, sizeof(LX_AUD_DEBUG_MOD_INFO_T)))
				return RET_ERROR;
 		}
		break;

		case AUD_MASTER_IOR_GET_KDRV_HANDLE:
		{
			AUD_KDRV_RMD("%s.%d: [AUD_REN_IOW_GET_KDRV_HANDLE] Called\n", __F__, __L__);

			if(copy_to_user((void *)arg, (void *)&(my_dev->allocDev), sizeof(UINT32)))
				return RET_ERROR;
		}
		break;

		case AUD_MASTER_IOW_CONNECT_OUTPUT:
		{
			LX_AUD_MASTER_CONNECT_OUTPUT_T connect;

			AUD_KDRV_RMD("%s.%d: [AUD_MASTER_IOW_CONNECT] Called\n", __F__, __L__);

			if(copy_from_user( &connect, (void __user *)arg, sizeof(LX_AUD_MASTER_CONNECT_OUTPUT_T)))
				return RET_ERROR;

			retVal = AUDIO_ConnectOutput(connect.ui32KdrHandler, connect.output, connect.ui32UseSE);
		}
		break;

		case AUD_MASTER_IOW_DISCONNECT_OUTPUT:
		{
			LX_AUD_MASTER_DISCONNECT_OUTPUT_T disconnect;

			AUD_KDRV_RMD("%s.%d: [LX_AUD_MASTER_DISCONNECT_T] Called\n", __F__, __L__);

			if(copy_from_user( &disconnect, (void __user *)arg, sizeof(LX_AUD_MASTER_DISCONNECT_OUTPUT_T)))
				return RET_ERROR;

			retVal = AUDIO_DisconnectOutput(disconnect.ui32KdrHandler, disconnect.output);
		}
		break;

		case AUD_IOR_GET_FW_DEBUG_PRINT_INFO:
		{
			LX_AUD_FW_DEBUG_INFO_T debug_info;

			AUD_KDRV_RMD("%s.%d: [AUD_IOR_GET_FW_DEBUG_PRINT_INFO] Called\n", __F__, __L__);
			if(KDRV_AUDIO_GetFwDebugInfo(&debug_info) < 0)
				return RET_ERROR;
			if(copy_to_user((void *)arg, (void *)&debug_info, sizeof(LX_AUD_FW_DEBUG_INFO_T)))
				return RET_ERROR;
		}
		break;

		case AUD_IOW_SET_FW_DEBUG_MASK:
		{
			UINT32 debug_mask;

			if(copy_from_user(&debug_mask, (void __user *)arg, sizeof(UINT32)))
				return RET_ERROR;

			KDRV_AUDIO_SetFwDebugMask(debug_mask);
		}
		break;

		case AUD_IOWR_DEBUG_GET_DECODED_INFO:
		{
			LX_AUD_DEBUG_DECODED_INFO_T		decInfo;

			AUD_KDRV_TRACE("AUD_IOWR_DEBUG_GET_DECODED_INFO\n");

			if(copy_from_user( &decInfo, (void __user *)arg, sizeof(LX_AUD_DEBUG_DECODED_INFO_T)))
				return RET_ERROR;

			(void)KDRV_AUDIO_GetDecodedInfoForDebug(&decInfo);

			if(copy_to_user((void *)arg, (void *)&decInfo, sizeof(LX_AUD_DEBUG_DECODED_INFO_T)))
				return RET_ERROR;
 		}
		break;

		default:
		{
			/* redundant check but it seems more readable */
			AUD_KDRV_ERROR("Invalid IOCTL Call!!!\n");
			retVal = RET_INVALID_IOCTL;
		}
		break;
	}

	return retVal;
}

/**
 * Set Volume for output ports.
 * @see
*/
static SINT32 AUDIO_SetOutCtrlAll ( AUD_OUT_CTRL_MODULE_T *pOutCtrlConfig )
{
	ADEC_MODULE_ID		audioModule;
	OutctrlCmdSetAll		setOutCtrlAll;

	if(pOutCtrlConfig == NULL)
	{
		AUD_KDRV_ERROR("output is out of range!!!\n");
		return RET_ERROR;
	}

	audioModule = pOutCtrlConfig->module;
	setOutCtrlAll.Delay = pOutCtrlConfig->ui32Delay;
	setOutCtrlAll.Gain = pOutCtrlConfig->ui32Volume;
	setOutCtrlAll.GainEnable = 1;
	setOutCtrlAll.Mute = pOutCtrlConfig->ui32Mute;
	setOutCtrlAll.Balanced = pOutCtrlConfig->ui32Balance - 50;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_ALL, audioModule, sizeof(OutctrlCmdSetAll), &setOutCtrlAll);

	AUD_KDRV_PRINT("%s(Module:%d)\n", __F__, pOutCtrlConfig->module);

	return RET_OK;
}


/**
 * Set Volume for output ports.
 * @see
*/
static SINT32 AUDIO_SetVolume ( LX_AUD_MASTER_CONFIG_VOLUME_T *pVolumeConfig )
{
	ADEC_MODULE_ID		audioModule;
	OutctrlCmdSetGain	setOutCtrlGain;

	if(pVolumeConfig->output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_ERROR("output is out of range!!!\n");
		return RET_ERROR;
	}

	audioModule = _gMasterInfo.outCtrlMod[pVolumeConfig->output].module;
	setOutCtrlGain.GainEnable = 1;
	setOutCtrlGain.Gain = pVolumeConfig->ui32Volume;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_GAIN, audioModule, sizeof(OutctrlCmdSetGain), &setOutCtrlGain);

	_gMasterInfo.outCtrlMod[pVolumeConfig->output].ui32Volume = pVolumeConfig->ui32Volume;

	AUD_KDRV_PRINT("AUDIO_SetVolume(Output:%d, Volume:0x%x)\n", pVolumeConfig->output, pVolumeConfig->ui32Volume);

	return RET_OK;
}

/**
 * Set Mute for output ports.
 * @see
*/
static SINT32 AUDIO_SetMute ( LX_AUD_MASTER_CONFIG_MUTE_T *pMuteConfig )
{
	ADEC_MODULE_ID		audioModule;
	OutctrlCmdSetMute		setOutCtrlMute;
	ADEC_MODULE_ID		spdifModule = ADEC_MODULE_ESOUT_CTRL;
	EsoutctrlCmdSetMute	setSpdifEsMute;

	if(pMuteConfig->output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_ERROR("output is out of range!!!\n");
		return RET_ERROR;
	}

	audioModule = _gMasterInfo.outCtrlMod[pMuteConfig->output].module;
	setOutCtrlMute.Mute = pMuteConfig->ui32Mute;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_MUTE, audioModule, sizeof(OutctrlCmdSetMute), &setOutCtrlMute);

	if(pMuteConfig->output == LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		setSpdifEsMute.Mute = pMuteConfig->ui32Mute;
		AUDIO_IMC_SendCmdParam(ESOUTCTRL_CMD_SET_MUTE, spdifModule, sizeof(EsoutctrlCmdSetMute), &setSpdifEsMute);
	}

	_gMasterInfo.outCtrlMod[pMuteConfig->output].ui32Mute = pMuteConfig->ui32Mute;

	AUD_KDRV_PRINT("AUDIO_SetMute(Output:%d, Mute:%d)\n", pMuteConfig->output, pMuteConfig->ui32Mute);

	return RET_OK;
}

/**
 * Set Delay for output ports.
 * @see
*/
static SINT32 AUDIO_SetDelay ( LX_AUD_MASTER_CONFIG_DELAY_T *pDelayConfig )
{
	ADEC_MODULE_ID		audioModule;
	OutctrlCmdSetDelay	setOutCtrlDelay;
	ADEC_MODULE_ID		spdifModule = ADEC_MODULE_ESOUT_CTRL;
	EsoutctrlCmdSetDelay	setSpdifDelay;

	if(pDelayConfig->output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_ERROR("output is out of range!!!\n");
		return RET_ERROR;
	}

	audioModule = _gMasterInfo.outCtrlMod[pDelayConfig->output].module;
	setOutCtrlDelay.Delay= pDelayConfig->ui32Delay;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_DELAY, audioModule, sizeof(OutctrlCmdSetDelay), &setOutCtrlDelay);

	if(pDelayConfig->output == LX_AUD_MASTER_OUTPUT_SPDIF && _gMasterInfo.spdifOutputFormat == LX_AUD_MASTER_SPDIF_ES)
	{
		setSpdifDelay.Delay = pDelayConfig->ui32Delay;
		setSpdifDelay.Fs    = _gMasterInfo.spdifSamplingFreq;
		AUDIO_IMC_SendCmdParam(ESOUTCTRL_CMD_SET_DELAY, spdifModule, sizeof(EsoutctrlCmdSetDelay), &setSpdifDelay);
	}

	_gMasterInfo.outCtrlMod[pDelayConfig->output].ui32Delay = pDelayConfig->ui32Delay;

	AUD_KDRV_PRINT("AUDIO_SetDelay(Output:%d, Delay:%d)\n", pDelayConfig->output, pDelayConfig->ui32Delay);

	return RET_OK;
}

/**
 * Set balance for output ports.
 * @see
*/
static SINT32 AUDIO_SetBalance ( LX_AUD_MASTER_CONFIG_BALANCE_T *pBalanceConfig )
{
	ADEC_MODULE_ID			audioModule;
	OutctrlCmdSetBalanced	setOutCtrlBalanced;

	if(pBalanceConfig->output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_ERROR("output is out of range!!!\n");
		return RET_ERROR;
	}

	audioModule = _gMasterInfo.outCtrlMod[pBalanceConfig->output].module;
	setOutCtrlBalanced.Balanced = pBalanceConfig->ui32Balance - 50;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_BALANCED, audioModule, sizeof(OutctrlCmdSetBalanced), &setOutCtrlBalanced);

	_gMasterInfo.outCtrlMod[pBalanceConfig->output].ui32Balance = pBalanceConfig->ui32Balance;

	AUD_KDRV_PRINT("AUDIO_SetBalance(Output:%d, Balance:%d)\n", pBalanceConfig->output, pBalanceConfig->ui32Balance);
	return RET_OK;
}

/**
 * Set Volume for output ports.
 * @see
*/
static SINT32 AUDIO_SetOutMode ( LX_AUD_MASTER_CONFIG_OUT_MODE_T *pOutModeConfig )
{
	ADEC_MODULE_ID		audioModule;
	OutctrlCmdSetPcmoutmode	setPcmOutMode;

	if(pOutModeConfig->output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_ERROR("output is out of range!!!\n");
		return RET_ERROR;
	}

	audioModule = _gMasterInfo.outCtrlMod[pOutModeConfig->output].module;
	setPcmOutMode.OutMode = pOutModeConfig->outMode;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_PCMOUTMODE, audioModule, sizeof(OutctrlCmdSetPcmoutmode), &setPcmOutMode);

	_gMasterInfo.outCtrlMod[pOutModeConfig->output].outMode = pOutModeConfig->outMode;

	AUD_KDRV_PRINT("AUDIO_SetOutMode(Output:%d, OutMode:%d)\n", pOutModeConfig->output, pOutModeConfig->outMode);
	return RET_OK;
}

/**
 * Set SPDIF Output for output ports.
 * @see
*/
static SINT32 AUDIO_SetSpdifOutput ( LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T *pSpdifOutputConfig )
{
	g_AudSpdifOutputType = pSpdifOutputConfig->spdifOutput;

	AUD_KDRV_PRINT("AUDIO_SetSpdifOutput(%d)\n", pSpdifOutputConfig->spdifOutput);
	return RET_OK;
}

/**
 * Set SPDIF Output for output ports.
 * @see
*/
static SINT32 AUDIO_GetSpdifOutput ( LX_AUD_MASTER_CONFIG_SPDIF_OUTPUT_T *pSpdifOutputConfig )
{
	pSpdifOutputConfig->spdifOutput = g_AudSpdifOutputType;

	AUD_KDRV_PRINT("AUDIO_GetSpdifOutput(%d)\n", pSpdifOutputConfig->spdifOutput);
	return RET_OK;
}

/**
 * Set SPDIF SCMS for output ports.
 * @see
*/
static SINT32 AUDIO_SetSpdifScms( LX_AUD_MASTER_CONFIG_SPDIF_SCMS_T *pSpdifScmsConfig )
{
	SpdifCmdSetScms	setSpdifScms;

	setSpdifScms.scms_type = pSpdifScmsConfig->spdifScms;
	AUDIO_IMC_SendCmdParam(SPDIF_CMD_SET_SCMS, ADEC_MODULE_OUT_SPDIF, sizeof(SpdifCmdSetScms), &setSpdifScms);

	AUD_KDRV_PRINT("AUDIO_SetSpdifScms(%d)\n", pSpdifScmsConfig->spdifScms);

	return RET_OK;
}

/**
 * Set On or Off for SPDIF Output Light.
 * @see
*/
static SINT32 AUDIO_SetSpdifOnOff( UINT32 bOnOff )
{
	SpdifCmdSetLight	setSpdifLight;

	setSpdifLight.onoff = bOnOff;
	AUDIO_IMC_SendCmdParam(SPDIF_CMD_SET_LIGHT, ADEC_MODULE_OUT_SPDIF, sizeof(SpdifCmdSetLight), &setSpdifLight);

	_gMasterInfo.spdifOnOff = bOnOff;

	AUD_KDRV_PRINT("AUDIO_SetSpdifOnOff(%d)\n", bOnOff);
	return RET_OK;
}

/**
 * Set bass for output ports.
 * @see
*/
static SINT32 AUDIO_SetBass ( LX_AUD_MASTER_CONFIG_BASS_T *pBassConfig )
{
	AUD_KDRV_PRINT("AUDIO_SetBass(%d) : Not Supported!!!\n", pBassConfig->ui32Bass);
	return RET_OK;
}

/**
 * Set treble for output ports.
 * @see
*/
static SINT32 AUDIO_SetTreble ( LX_AUD_MASTER_CONFIG_TREBLE_T *pTrebleConfig )
{
	AUD_KDRV_PRINT("AUDIO_SetTreble(%d) : Not Supported!!!\n", pTrebleConfig->ui32Treble);
	return RET_OK;
}

/**
 * Set input port.
 * @see
*/
static SINT32 AUDIO_SetADCInputPort ( UINT32 adcInputPort )
{
	//Set ADC Input port for Mixed IP Module
	(void)MIXED_IP_AUDIO_SetADCPortNumber(adcInputPort);

	AUD_KDRV_PRINT("AUDIO_SetADCInputPort(%d)\n", adcInputPort);
	return RET_OK;
}

/**
 * Set Power Block Mode.
 * @see
*/
static SINT32  AUDIO_SetPowerCtrl ( LX_AUD_MASTER_CONFIG_POWER_CTRL_T *pPowerCtrlConfig )
{
	//Set ADC Input port for Mixed IP Module
	(void)MIXED_IP_AUDIO_PowerControl(pPowerCtrlConfig->powerBlock, pPowerCtrlConfig->powerMode);

	AUD_KDRV_PRINT("AUDIO_SetPowerCtrl(%d %d)\n", pPowerCtrlConfig->powerBlock, pPowerCtrlConfig->powerMode);
	return RET_OK;
}

/**
 * Set Speaker Output for output ports.
 * @see
*/
static SINT32 AUDIO_SetSpeakerOutput ( LX_AUD_MASTER_CONFIG_SPK_OUTPUT_T *pSpkOutputConfig )
{
	SINT32				retVal = RET_OK;
	ADEC_MODULE_ID		audioModule;

	if(pSpkOutputConfig->spkOutput == LX_AUD_MASTER_SPK_PCM)
	{
		audioModule = ADEC_MODULE_OUT_PCM;
		retVal |= AUDIO_IMC_SendCmd(ADEC_CMD_START, audioModule);
	}
	else if(pSpkOutputConfig->spkOutput == LX_AUD_MASTER_SPK_PCM_0)
	{
		audioModule = ADEC_MODULE_OUT_PCM;
		retVal |= AUDIO_IMC_SendCmd(ADEC_CMD_STOP, audioModule);

#if 0	// disable ADEC_MOUDLE_OUT_PCM_0 setting
		audioModule = ADEC_MODULE_OUT_PCM_0;
		retVal |= AUDIO_IMC_SendCmd(ADEC_CMD_START, audioModule);
#endif
	}
	else
	{
		audioModule = ADEC_MODULE_OUT_PCM;
		retVal |= AUDIO_IMC_SendCmd(ADEC_CMD_STOP, audioModule);
	}

	AUD_KDRV_PRINT("AUDIO_SetSpeakerOutput(%d)\n", pSpkOutputConfig->spkOutput);
	return retVal;
}

/**
 * Sets a Sound Engine(SE) Function mode and paramters.
 * The Function mode and each paramter size is defined.
 * @see
*/
static SINT32  AUDIO_SetSEFunction ( LX_AUD_MASTER_PARAM_SE_FN_T *pSeFnParam )
{
	UINT32		seParamAddr = 0;
	UINT16		seParamSize	= 0;

	SeCmdSetMode	setSeMode;
	SeCmdSetParam	setSeParam;

	ADEC_MODULE_ID		audioModule = ADEC_MODULE_SE;

#ifdef ENABLE_SE_PARAM_DEBUG
	UINT16		ui16Count = 0;
#endif

	//Sanity check
	if((pSeFnParam->ui32Param == NULL)	\
	  ||(pSeFnParam->ui32NoParam == 0) || (pSeFnParam->ui32NoParam >= 1024))
	{
		AUD_KDRV_ERROR("%s : error!!!(pParams = %p, noParam = %d)\n", __F__, pSeFnParam->ui32Param, pSeFnParam->ui32NoParam);
		return RET_ERROR;
	}

	/* Set a SE function mode */
	if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_SET)
	{
		setSeMode.Mode = pSeFnParam->ui32Param[0];
		setSeMode.DeqMode = pSeFnParam->ui32Param[1];
		setSeMode.PeqMode = pSeFnParam->ui32Param[2];
		AUDIO_IMC_SendCmdParam(SE_CMD_SET_MODE, audioModule, sizeof(SeCmdSetMode), &setSeMode);
		memcpy(&(_gMasterInfo.seModeParam[0]),  &setSeMode, sizeof(SeCmdSetMode));
		AUD_KDRV_PRINT("SE mode : %x, Deq : %x, Peq : %x.\n", setSeMode.Mode, setSeMode.DeqMode, setSeMode.PeqMode);

		return RET_OK;
	}

	if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_000)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN000;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN000+NUM_OF_LGSEFN000_INIT_PARAM;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN000 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN000_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN000 INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
		else if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN000_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN000 VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN000;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_001)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN001;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN001 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN001_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN001 VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN001;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_003)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN003;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN003 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN003_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN003 INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN003;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_004_MODE1)
	{
		/* Set a SE parameter address and size */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(pSeFnParam->varOption == LX_AUD_MASTER_SE_VAR_ALL) )
		{
			seParamAddr = ADDR_OF_LGSEFN004MODE1;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(pSeFnParam->varOption < LX_AUD_MASTER_SE_VAR_ALL) )
		{
			seParamAddr = ADDR_OF_LGSEFN004MODE1 + NUM_OF_LGSEFN004MODE1_BASIC_PARAM +
				(pSeFnParam->varOption * NUM_OF_LGSEFN004MODE1_PARAM);
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN004_MODE1 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(pSeFnParam->varOption == LX_AUD_MASTER_SE_VAR_ALL) &&
			(seParamSize != NUM_OF_LGSEFN004MODE1_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN004_MODE1 VARI ALL size = %d.\n", seParamSize);
			return RET_ERROR;
		}
		else if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(pSeFnParam->varOption < LX_AUD_MASTER_SE_VAR_ALL) &&
			(seParamSize != NUM_OF_LGSEFN004MODE1_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN004_MODE1 VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN004_MODE1;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_004_MODE2)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES )
		{
			seParamAddr = ADDR_OF_LGSEFN004MODE2;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN004_MODE2 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN004MODE2_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN004_MODE2 VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN004_MODE2;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_004_MODE3)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES )
		{
			seParamAddr = ADDR_OF_LGSEFN004MODE3;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN004_MODE3 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN004MODE3_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN004_MODE3 VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN004_MODE3;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_006)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN006;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN006 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN006_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN006 VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN006;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_008)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN008;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN008 + NUM_OF_LGSEFN008_INIT_PARAM;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN008 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN008_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN008  INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
		else if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN008_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN008  VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN008;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_009)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN009;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN009 + NUM_OF_LGSEFN009_INIT_PARAM;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN009 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN009_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN009  INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
		else if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN009_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN009  VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN009;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_010)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN010;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN010 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN010_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN010  INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN010;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_011)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN011;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN011 + NUM_OF_LGSEFN011_INIT_PARAM;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN011 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN011_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN011  INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
		else	 if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN011_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN011  VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN011;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_012)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN012;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES)
		{
			seParamAddr = ADDR_OF_LGSEFN012 + NUM_OF_LGSEFN012_INIT_PARAM;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN012 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN012_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN012  INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
		else if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_VARIABLES) &&
			(seParamSize != NUM_OF_LGSEFN012_VAR_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN012  VARI size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN012;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_013)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY)
		{
			seParamAddr = ADDR_OF_LGSEFN013;
			seParamSize = pSeFnParam->ui32NoParam;
		}
		else
		{
			AUD_KDRV_ERROR("%s : FN_MODE_FN013 option = %d.\n", __F__, pSeFnParam->dataOption);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		/* Sanity Check */
		if((pSeFnParam->dataOption == LX_AUD_MASTER_SE_DATA_INIT_ONLY) &&
			(seParamSize != NUM_OF_LGSEFN013_INIT_PARAM))
		{
			AUD_KDRV_ERROR("AUDIO_SetSEFunction : FN_MODE_FN013  INIT size = %d.\n", seParamSize);
			return RET_ERROR;
		}
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
		/* Update a Sound Engine Mask */
		g_AudKdrv.soundEngineMask |= MASK_SE_FN_MODE_FN013;
	}
	else if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_UPDATE_PARAM)
	{
		seParamSize = 0;
	}
	else
	{
		AUD_KDRV_ERROR("%s : Function Mode Error!!!(%d)\n", __F__, pSeFnParam->fnMode);
		return RET_ERROR;
	}

	AUD_KDRV_PRINT("%s : addr = 0x%04X, size = %d(%d)\n", __F__, (UINT32)seParamAddr, seParamSize, sizeof(UINT32)*seParamSize);

	//Copy Sound Engine(SE)  parameters
	if(seParamSize != 0)
	{
		if(g_pui32SEParamVirAddr != NULL)
		{
			memcpy(g_pui32SEParamVirAddr + seParamAddr, pSeFnParam->ui32Param, sizeof(UINT32) * seParamSize);
		}
		else
		{
			AUD_KDRV_ERROR("%s : g_pui32SEParamVirAddr is NULL!!!\n", __F__);
			return RET_ERROR;
		}

#ifdef ENABLE_SE_PARAM_DEBUG
		//Read parameter value for debug
		AUD_KDRV_ERROR("SE Param Start...[0x%8X]\n", g_pui32SEParamVirAddr[seParamAddr]);
		for(ui16Count = 0; ui16Count < seParamSize; ui16Count++)
		//for(ui16Count = 0; ui16Count < 3; ui16Count++)
		{
			AUD_KDRV_ERROR("Param[%3d] = 0x%8X\n", ui16Count + 1, g_pui32SEParamVirAddr[seParamAddr + ui16Count]);
		}
		AUD_KDRV_ERROR("SE Param End...[0x%8X]\n", g_pui32SEParamVirAddr[seParamAddr + seParamSize - 1]);
#endif		//#ifdef ENABLE_SE_PARAM_DEBUG
	}

	setSeParam.FnMode = AUDIO_GetSeFnMode(pSeFnParam->fnMode);
	setSeParam.DataOption = pSeFnParam->dataOption;
	AUDIO_IMC_SendCmdParam(SE_CMD_SET_PARAM, audioModule, sizeof(SeCmdSetParam), &setSeParam);

	AUD_KDRV_PRINT("SE FnMode : %x, dataOption : %x.\n", setSeParam.FnMode, setSeParam.DataOption);
	return RET_OK;
}

/**
 * Gets a Sound Engine(SE) Function mode and paramters.
 * The Function mode and each paramter size is defined.
 * @see
*/
static SINT32  AUDIO_GetSEFunction ( LX_AUD_MASTER_PARAM_SE_FN_T *pSeFnParam )
{
	if(pSeFnParam->fnMode == LX_AUD_MASTER_SE_FN_010)
	{
		/* Set a SE parameter address and size */
		if(pSeFnParam->accessMode == LX_AUD_MASTER_SE_ACCESS_READ)
		{
			//Read the sound level for left and righr channel
			AUD_RdFL(aud_levelmo_l);
			AUD_RdFL(aud_levelmo_r);

			pSeFnParam->ui32Param[0] = AUD_Rd(aud_levelmo_l);	//left volume
			pSeFnParam->ui32Param[1] = AUD_Rd(aud_levelmo_r);	//right volume
		}
		else
		{
			pSeFnParam->ui32Param[0] = 0;	//left volume
			pSeFnParam->ui32Param[1] = 0;	//right volume

			AUD_KDRV_ERROR("AUDIO_GetSEFunction : FN_FN010 access = %d.\n", pSeFnParam->accessMode);
			return RET_ERROR;
		}
	}

	AUD_KDRV_PRINT("AUDIO_GetSEFunction : L(0x%x), R(0x%x)\n", pSeFnParam->ui32Param[0], pSeFnParam->ui32Param[1]);
	return RET_OK;
}

/**
 * Set Delay for Mixer Port.
 * @see
*/
static SINT32 AUDIO_SetMixerDelay ( LX_AUD_MASTER_CONFIG_MIXER_DELAY_T *pMixerDelayConfig )
{
	ADEC_MODULE_ID		audioModule;
	ADEC_MODULE_ID		srcModule = ADEC_MODULE_SRC_0;
	MixCmdSetInitDelay	setMixInitDelay;
	MixCmdEnablePort		enabeMixPort;
	ImcCmdFlushParam	flushParam;

	audioModule = pMixerDelayConfig->mixer + ADEC_MODULE_MIX_0;

	enabeMixPort.port = pMixerDelayConfig->ui32Port;
	enabeMixPort.enable = 0;
	AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT, audioModule, sizeof(MixCmdEnablePort), &enabeMixPort);

	msleep_interruptible(10);

	memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
	flushParam.num_of_port = 1;
	flushParam.port_list[0] = MOD_IN_PORT(pMixerDelayConfig->ui32Port);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, audioModule, sizeof(ImcCmdFlushParam), &flushParam);

	//memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, srcModule, sizeof(ImcCmdFlushParam), &flushParam);

	setMixInitDelay.port = pMixerDelayConfig->ui32Port;
	setMixInitDelay.init_delay_length = pMixerDelayConfig->ui32Delay * 48;
	AUDIO_IMC_SendCmdParam(MIX_CMD_SET_INIT_DELAY, audioModule, sizeof(MixCmdSetInitDelay), &setMixInitDelay);

	enabeMixPort.port = pMixerDelayConfig->ui32Port;
	enabeMixPort.enable = 1;
	AUDIO_IMC_SendCmdParam(MIX_CMD_ENABLE_PORT, audioModule, sizeof(MixCmdEnablePort), &enabeMixPort);

	AUD_KDRV_PRINT("AUDIO_SetDelay(port :%d, delay:%d)\n", setMixInitDelay.port, setMixInitDelay.init_delay_length);
	return RET_OK;
}

/**
 * Set Delay for Mixer Port.
 * @see
*/
static SINT32 AUDIO_SetMixerVolume ( LX_AUD_MASTER_CONFIG_MIXER_VOLUME_T *pMixerVolumeConfig )
{
	ADEC_MODULE_ID		audioModule;
	MixCmdSetGain		setMixGain;

	audioModule = pMixerVolumeConfig->mixer + ADEC_MODULE_MIX_0;

	setMixGain.port = pMixerVolumeConfig->ui32Port;
	setMixGain.gain = pMixerVolumeConfig->ui32Volume;
	AUDIO_IMC_SendCmdParam(MIX_CMD_SET_GAIN, audioModule, sizeof(MixCmdSetGain), &setMixGain);

	AUD_KDRV_PRINT("AUDIO_SetMixerVolume(port:%d, gain:%d)\n", setMixGain.port, setMixGain.gain);

	return RET_OK;
}

/**
 * Set Volume for DAC Port.
 * @see
*/
static SINT32 AUDIO_SetDacVolume(LX_AUD_MASTER_CONFIG_DAC_VOLUME_T  *pDacVolumeConfig)
{
	LX_AUD_DAC_VOL_T dacVol;

	dacVol.portNum 	= LX_AUD_OUTPUT_DAC0;
	dacVol.hwVolume = (UINT16)pDacVolumeConfig->ui32Volume;
	dacVol.mode 	= LX_AUD_DAC_MIXEDIP;
	dacVol.swVolume	= 0;	//not used now
	dacVol.scartGain= 0;	//not used now

	MIXED_IP_AUDIO_SetDACOutVolume(dacVol);

	AUD_KDRV_PRINT("AUDIO_SetDacVolume(port:%d, volume:%d)\n", dacVol.portNum, dacVol.hwVolume);

	return RET_OK;
}


/**
 * Set Volume for DAC Port.
 * @see
*/
static SINT32 AUDIO_SetDacMute(LX_AUD_MASTER_CONFIG_DAC_MUTE_T  *pDacMuteConfig)
{
	LX_AUD_OUTPUT_PORT_MUTE_T dacMute;

	dacMute.portNum  = LX_AUD_OUTPUT_DAC0;
	dacMute.bHwOnOff = (BOOLEAN)pDacMuteConfig->ui32Mute;
	dacMute.mode 	 = pDacMuteConfig->mode;
	dacMute.bSwOnOff = 0;	//not used now

	MIXED_IP_AUDIO_SetDACOutMute(dacMute);

	AUD_KDRV_PRINT("AUDIO_SetDacVolume(port:%d, mute:%d, mode:%d)\n", dacMute.portNum, dacMute.bHwOnOff, dacMute.mode);

	return RET_OK;
}

/**
 * Connect other device to Master Outputs.
 * @see
*/
static SINT32 AUDIO_ConnectOutput (UINT32 connectDev, LX_AUD_MASTER_OUTPUT_T output, UINT32 bUseSE)
{
	LX_AUD_ALLOC_FREE_INFO_T * connectDevInfo;
	ADEC_MODULE_ID			connectModule =ADEC_MOD_TYPE_NOT_DEF;
	ADEC_MODULE_ID			managerModule;
	ADEC_MODULE_ID			outCtrlModule;
	ADEC_MODULE_ID			outModule;
	SpdifCmdSetOutmode 		setSpdifOutpMode;
	CmCmdConnect			connectParam;

	AUD_KDRV_RM("AUDIO_ConnectMaster  %s \n",allocDev_Str[ connectDev]);

	if(output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_RM("Invalid Connection Trial\n");
		return RET_ERROR;
	}

	if(_gMasterInfo.outCtrlMod[output].ui32ConnectDev != AUD_NO_DEV &&
		_gMasterInfo.outCtrlMod[output].ui32ConnectDev != connectDev)
	{
		AUD_KDRV_RM("Other device is already connected.\n");
		return RET_OK;
	}

	connectDevInfo = AUDIO_GetAllocDevInfo(connectDev);

	if(connectDevInfo == NULL)
	{
		AUD_KDRV_DEBUG(" Check connectDevInfo[%p] \n",connectDevInfo);
		return RET_ERROR;
	}


	if(connectDevInfo->headOfDev == NULL ||  connectDevInfo->tailOfDev == NULL)
	{
		AUD_KDRV_DEBUG("========== CAUTION ============ \n");
		AUD_KDRV_DEBUG("connect head[%p] tail[%p]\n",connectDevInfo->headOfDev, connectDevInfo->tailOfDev);
		return RET_ERROR;
	}

	if((bUseSE == TRUE) && (connectDev == AUD_DEV_MAS0))
	{
		connectModule = ADEC_MODULE_SE;
		_gMasterInfo.outCtrlMod[output].ui32UseSE = bUseSE;
	}
	else if(connectDevInfo->devType==LX_AUD_DEV_MAS)
	{
		//mix
		connectModule = ((LX_AUD_ALLOC_FREE_INFO_T *) (connectDevInfo->headOfDev))->allocMod;
	}
	else if(connectDevInfo->devType==LX_AUD_DEV_REN)
	{
		//lipes
		connectModule = ((LX_AUD_ALLOC_FREE_INFO_T *) (connectDevInfo->tailOfDev))->allocMod;
	}

	if(output == LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		if(connectModule == ADEC_MODULE_LIP_ES0 || connectModule == ADEC_MODULE_LIP_ES1)
		{
			outCtrlModule = ADEC_MODULE_ESOUT_CTRL;
			connectParam.output_port = MOD_OUT_PORT(0);
		}
		else
		{
			_gSpdifOutPcmCnt++;
			if(_gSpdifOutPcmCnt > 1)
			{
				AUD_KDRV_DEBUG("[%s] _gSpdifOutPcmCnt(%d) \n", __F__, _gSpdifOutPcmCnt);
				return RET_OK;
			}

			outCtrlModule = _gMasterInfo.outCtrlMod[output].module;
			if(connectDev == AUD_DEV_MAS0)
				connectParam.output_port = MOD_OUT_PORT(0)+output;
			else
				connectParam.output_port = MOD_OUT_PORT(0)+1;
		}
		managerModule = _AUDIO_GetManagerModule(outCtrlModule);
		connectParam.input_module	= outCtrlModule;
		connectParam.input_port = MOD_IN_PORT(0);
		connectParam.output_module = connectModule;

		//mix/se(connectdev)     -c-    esout_ctrl/out_ctrl3
		AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, managerModule, sizeof(CmCmdConnect), &connectParam);
		AUD_KDRV_RM("[%11s]       ----  1C  ----      [%11s] connection OKl\n", allocMod_Str[connectModule],allocMod_Str[outCtrlModule]);
	}
	else
	{
		outCtrlModule	 = _gMasterInfo.outCtrlMod[output].module;
		managerModule = _AUDIO_GetManagerModule(outCtrlModule);
		connectParam.input_module	= outCtrlModule;
		connectParam.input_port = MOD_IN_PORT(0);
		connectParam.output_module = connectModule;
		if(connectDev == AUD_DEV_MAS0)
			connectParam.output_port = MOD_OUT_PORT(0)+output;
		else
			connectParam.output_port = MOD_OUT_PORT(0)+1;
		AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, managerModule, sizeof(CmCmdConnect), &connectParam);

		//mix/se(connectdev)    -c-  out_ctrl3
		AUD_KDRV_RM("[%11s]       ----  2C  ----      [%11s] connection OKl\n", allocMod_Str[connectModule],allocMod_Str[outCtrlModule]);
	}

	if(output ==LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		if(connectModule == ADEC_MODULE_LIP_ES0 || connectModule == ADEC_MODULE_LIP_ES1)
		{
			EsoutctrlCmdSetAll	setSpdifAll;

			setSpdifAll.Delay = _gMasterInfo.outCtrlMod[output].ui32Delay;
			setSpdifAll.Fs    = _gMasterInfo.spdifSamplingFreq;
			setSpdifAll.Mute  = _gMasterInfo.outCtrlMod[output].ui32Mute;
			AUDIO_IMC_SendCmdParam(ESOUTCTRL_CMD_SET_ALL, outCtrlModule, sizeof(EsoutctrlCmdSetAll), &setSpdifAll);
		}
	}

	if(output ==LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		outModule = ADEC_MODULE_OUT_SPDIF;
		managerModule = _AUDIO_GetManagerModule(outModule);
		connectParam.input_module	= outModule;
		connectParam.input_port = MOD_IN_PORT(0);
		connectParam.output_module = outCtrlModule;
		connectParam.output_port = MOD_OUT_PORT(0);
		AUDIO_IMC_SendCmdParam(CM_CMD_CONNECT, managerModule, sizeof(CmCmdConnect), &connectParam);

						//esout_ctrl/outctrl3    - c -    ADEC_MODULE_OUT_SPDIF
		AUD_KDRV_RM("[%11s]       ----  3C  ----      [%11s] connection OKl\n", allocMod_Str[outCtrlModule],allocMod_Str[outModule]);

		if(connectModule == ADEC_MODULE_LIP_ES0 || connectModule == ADEC_MODULE_LIP_ES1)
		{
			setSpdifOutpMode.out_format = LX_AUD_MASTER_SPDIF_ES;
			setSpdifOutpMode.Fs = _gMasterInfo.spdifSamplingFreq;

			_gMasterInfo.spdifOutputFormat = LX_AUD_MASTER_SPDIF_ES;
		}
		else
		{
			setSpdifOutpMode.out_format = LX_AUD_MASTER_SPDIF_PCM;
			setSpdifOutpMode.Fs = LX_AUD_SAMPLING_FREQ_48_KHZ;

			_gMasterInfo.spdifOutputFormat = LX_AUD_MASTER_SPDIF_PCM;
			_gMasterInfo.spdifSamplingFreq = LX_AUD_SAMPLING_FREQ_48_KHZ;
		}
		AUDIO_IMC_SendCmdParam(SPDIF_CMD_SET_OUTFORMAT, outModule, sizeof(SpdifCmdSetOutmode), &setSpdifOutpMode);

		//Update a SPDIF Clock Frequency.
		(void)KDRV_AUDIO_UpdateSamplingFreq(_gMasterInfo.spdifSamplingFreq);
	}

	AUDIO_IMC_SendCmd(ADEC_CMD_START, outCtrlModule);
	if(output == LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		AUDIO_IMC_SendCmd(ADEC_CMD_START, outModule);
		MIXED_IP_AUDIO_StartDTO(g_setClockSrc, _gMasterInfo.spdifOutputFormat);
	}

	_gMasterInfo.outCtrlMod[output].ui32ConnectDev = connectDev;

	return RET_OK;
}

/**
 * Disconnect other device to Master Outputs.
 * @see
*/
static SINT32 AUDIO_DisconnectOutput (UINT32 connectDev, LX_AUD_MASTER_OUTPUT_T output)
{
	LX_AUD_ALLOC_FREE_INFO_T * connectDevInfo;
	ADEC_MODULE_ID			connectModule =ADEC_MOD_TYPE_NOT_DEF;
	ADEC_MODULE_ID			managerModule;
	ADEC_MODULE_ID			outCtrlModule;
	ADEC_MODULE_ID			outModule ;
	CmCmdDisconnect			disconnectParam;
	ImcCmdFlushParam		flushParam;

	AUD_KDRV_RM("AUDIO_DisconnectMaster  %s  \n",allocDev_Str[ connectDev]);

	if(output >= LX_AUD_MASTER_OUTPUT_MAX)
	{
		AUD_KDRV_RM("Invalid Disconnection Trial \n");
		AUDIO_UpdateConnectionInfo();
		return RET_ERROR;
	}

	if(_gMasterInfo.outCtrlMod[output].ui32ConnectDev != connectDev)
	{
		AUD_KDRV_DEBUG("Other device is already connected.\n");
		return RET_OK;
	}

	connectDevInfo = AUDIO_GetAllocDevInfo(connectDev);

	if(connectDevInfo == NULL)
	{
		AUD_KDRV_DEBUG(" Check connectDevInfo[%p] \n",connectDevInfo);
		return RET_ERROR;
	}

	if(connectDevInfo->headOfDev == NULL || connectDevInfo->tailOfDev == NULL)
	{
		AUD_KDRV_DEBUG("========== CAUTION ============ \n");
		AUD_KDRV_DEBUG("connect head[%p] tail[%p]\n",connectDevInfo->headOfDev, connectDevInfo->tailOfDev);
		return RET_ERROR;
	}

	if(connectDevInfo->devType == LX_AUD_DEV_MAS)
	{
		//mix
		connectModule = ((LX_AUD_ALLOC_FREE_INFO_T *) (connectDevInfo->headOfDev))->allocMod;
	}
	else if(connectDevInfo->devType == LX_AUD_DEV_REN)
	{
		//lipes
		connectModule = ((LX_AUD_ALLOC_FREE_INFO_T *) (connectDevInfo->tailOfDev))->allocMod;
	}

	// Stop Modules
	if(output == LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		if(connectModule != ADEC_MODULE_LIP_ES0 && connectModule != ADEC_MODULE_LIP_ES1)
		{
			if(_gSpdifOutPcmCnt > 0)
			{
				_gSpdifOutPcmCnt--;
			}

			if(_gSpdifOutPcmCnt > 0)
			{
				AUD_KDRV_DEBUG("[%s] _gSpdifOutPcmCnt(%d) \n", __F__, _gSpdifOutPcmCnt);
				return RET_OK;
			}
		}
		outModule = ADEC_MODULE_OUT_SPDIF;

		AUDIO_IMC_SendCmd(ADEC_CMD_STOP, outModule);
	}

	if(output == LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		if(connectModule == ADEC_MODULE_LIP_ES0 || connectModule == ADEC_MODULE_LIP_ES1)
		{
			outCtrlModule = ADEC_MODULE_ESOUT_CTRL;
		}
		else
		{
			outCtrlModule = _gMasterInfo.outCtrlMod[output].module;
		}
	}
	else
	{
		outCtrlModule		= _gMasterInfo.outCtrlMod[output].module;
	}

	AUDIO_IMC_SendCmd(ADEC_CMD_STOP, outCtrlModule);

	// Flush & Disconnect Modules
	if(output == LX_AUD_MASTER_OUTPUT_SPDIF)
	{
		memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
		flushParam.num_of_port	= 1;
		flushParam.port_list[0]	= MOD_IN_PORT(0);
		AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, outModule, sizeof(ImcCmdFlushParam), &flushParam);

		managerModule = _AUDIO_GetManagerModule(outModule);
		disconnectParam.module = outModule;
		disconnectParam.port = MOD_IN_PORT(0);
		AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);
		AUD_KDRV_RM("[%11s]       ----  1X  ----      [%11s] disconnection OKl\n", allocMod_Str[connectModule],allocMod_Str[outModule]);
	}

	memset(&flushParam, 0, sizeof(ImcCmdFlushParam));
	flushParam.num_of_port	= 1;
	flushParam.port_list[0]	= MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(ADEC_CMD_FLUSH, outCtrlModule, sizeof(ImcCmdFlushParam), &flushParam);

	managerModule = _AUDIO_GetManagerModule(outCtrlModule);
	disconnectParam.module = outCtrlModule;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);
	AUD_KDRV_RM("[%11s]       ----  2X  ----      [%11s] disconnection OKl\n", allocMod_Str[connectModule],allocMod_Str[outCtrlModule]);

	// for ResetConnectMaster
	_gPreConnectDev[output] = _gMasterInfo.outCtrlMod[output].ui32ConnectDev;

	_gMasterInfo.outCtrlMod[output].ui32ConnectDev = AUD_NO_DEV;

	return RET_OK;
}

/**
 * Enable SoundBar or Wireless SoundBar.
 * @see
*/
static SINT32 AUDIO_EnableSoundBar (LX_AUD_MASTER_SOUNDBAR_T bOnOff)
{
	UINT32	allocDev = AUD_DEV_REN0;
	SINT32	renIndex = AUD_DEV_REN0;
	ULONG	flags;

	/* If sound bar is off, SPDIF ID Data is cleared. DDI does not call AUDIO_SetSoundBarParam function. */
	if(bOnOff.ui32SoundBarOnOff == FALSE && _gMasterInfo.soundBarStatus.ui32SoundBarOnOff == TRUE)
	{
		AUDIO_IMC_SendCmd(SPDIF_CMD_CLEAR_FMT_FOR_SOUNDBAR, ADEC_MODULE_OUT_SPDIF);
	}

	/* If sound bar is off, SPDIF ID Data is cleared. DDI does not call AUDIO_SetSoundBarParam function. */
	if(bOnOff.ui32WirelessOnOff != _gMasterInfo.soundBarStatus.ui32WirelessOnOff)
	{

	/* Check a render open status for AUD_DEV_REN11. */
		for(allocDev = AUD_DEV_REN0; allocDev < AUD_DEV_REN11; allocDev++)
		{
			renIndex = GET_REN_INDEX(allocDev);

			if(_gRenderInfo[renIndex].ui32AllocDev != 0)
			{
				//spin lock for protection
				spin_lock_irqsave(&gAudEventSpinLock, flags);

				//Set a audio GET event type for next event.
				gAudGetEvent[allocDev].allocDev  = allocDev;
				gAudGetEvent[allocDev].eventMsg |= LX_AUD_EVENT_SB_CHANGED;

				//spin unlock for protection
				spin_unlock_irqrestore(&gAudEventSpinLock, flags);

				//Wake up poll event if allocated device and event message is set.
				if( (gAudSetEvent[allocDev].allocDev != AUD_NO_DEV)		\
				  &&(gAudSetEvent[allocDev].eventMsg & LX_AUD_EVENT_SB_CHANGED) )
				{
					wake_up_interruptible_all(&gAudPollWaitQueue);
				}
			}
		}
	}

	_gMasterInfo.soundBarStatus.ui32SoundBarOnOff = bOnOff.ui32SoundBarOnOff;
	_gMasterInfo.soundBarStatus.ui32WirelessOnOff = bOnOff.ui32WirelessOnOff;

	AUD_KDRV_DEBUG("AUDIO_EnableSoundBar(soundbar : %d, wireless : %d)\n", bOnOff.ui32SoundBarOnOff, bOnOff.ui32WirelessOnOff);
	return RET_OK;
}

/**
 * Set SoundBar ID and Data.
 * @see
*/
static SINT32 AUDIO_SetSoundBarParam (LX_AUD_MASTER_SOUNDBAR_PARAM_T *pSoundbarParam)
{
	AUD_MASTER_INFO_T				*pMstInfo = NULL;
	SpdifCmdSetFmtForSoundbar		setSoundbarFormat;

	pMstInfo = &_gMasterInfo;

	_AUDIO_RegisterMasterNoti(pMstInfo, (PFN_ImcNoti)_AUDIO_MstSoundBarStatusCb, ADEC_MODULE_OUT_SPDIF, SPDIF_EVT_GET_FMT_FOR_SOUNDBAR, IMC_ACTION_ONCE, 1);

	setSoundbarFormat.id = pSoundbarParam->ui32ID;
	setSoundbarFormat.mute = (pSoundbarParam->ui32Data >> 7) & 0x1;
	setSoundbarFormat.volume = pSoundbarParam->ui32Data & 0x7F;
	AUDIO_IMC_SendCmdParam(SPDIF_CMD_SET_FMT_FOR_SOUNDBAR, ADEC_MODULE_OUT_SPDIF, sizeof(SpdifCmdSetFmtForSoundbar), &setSoundbarFormat);

	AUD_KDRV_PRINT("AUDIO_SetSoundBarParam(mute:%d vol:%d)\n", setSoundbarFormat.mute, setSoundbarFormat.volume);
	return RET_OK;
}

/**
 * Get SoundBar Status.
 * @see
*/
static SINT32 AUDIO_GetSoundBarStatus (LX_AUD_MASTER_SOUNDBAR_STATUS_T *pSoundbarStatus )
{
	memcpy(pSoundbarStatus, &(_gMasterInfo.soundBarStatus), sizeof(LX_AUD_MASTER_SOUNDBAR_STATUS_T));

	AUD_KDRV_PRINT("AUDIO_GetSoundBarStatus(%x %x %x)\n", pSoundbarStatus->ui32SubFrameID, pSoundbarStatus->ui32SubFrameData, pSoundbarStatus->ui32SubFrameCheckSum);
	return RET_OK;
}

/**
 * Set SoundBar Power On/Off.
 * @see
*/
static SINT32 AUDIO_SetSoundBarPower (UINT32 bOnOff)
{
	AUD_MASTER_INFO_T		*pMstInfo = NULL;
	SpdifCmdOnoffSoundbar	setSoundBarPower;

	pMstInfo = &_gMasterInfo;

	_AUDIO_RegisterMasterNoti(pMstInfo, (PFN_ImcNoti)_AUDIO_MstSoundBarStatusCb, ADEC_MODULE_OUT_SPDIF, SPDIF_EVT_GET_FMT_FOR_SOUNDBAR, IMC_ACTION_ONCE, 1);

	setSoundBarPower.onoff = bOnOff;

	AUDIO_IMC_SendCmdParam(SPDIF_CMD_ONOFF_SOUNDBAR, ADEC_MODULE_OUT_SPDIF, sizeof(SpdifCmdOnoffSoundbar), &setSoundBarPower);

	AUD_KDRV_PRINT("AUDIO_SetSoundBarPower(onOff : %d)\n", bOnOff);
	return RET_OK;
}

/**
 * Set a audio event type.
 * @see KDRV_AUDIO_PollMaster
 */
static SINT32 AUDIO_SetEvent(LX_AUD_EVENT_TYPE_T *pEvent)
{
	ULONG	flags;
	LX_AUD_ALLOC_DEV_T	allocDev;

	/* Set a audio device. */
	allocDev = pEvent->allocDev;

	/* Check a audio device for callback function. */
	if(allocDev >= AUD_DEV_MAX)
	{
		AUD_KDRV_ERROR("AUDIO_SetEvent : allocDev is AUD_DEV_MAX.(%d))\n", allocDev);
		return RET_ERROR;
	}

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Set a audio SET event type for next event.
	gAudSetEvent[allocDev].allocDev = pEvent->allocDev;
	gAudSetEvent[allocDev].eventMsg = pEvent->eventMsg;

	//Reset a audio GET event type for next event.
	gAudGetEvent[allocDev].allocDev = AUD_NO_DEV;
	gAudGetEvent[allocDev].eventMsg = LX_AUD_EVENT_MASK_NONE;

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	AUD_KDRV_DEBUG("AUDIO_SetEvent(allocDev = %d, event = 0x%X)\n", pEvent->allocDev, pEvent->eventMsg);
	return RET_OK;
}

/**
 * Get a audio event type.
 * @see KDRV_AUDIO_PollMaster
 */
static SINT32 AUDIO_GetEvent(LX_AUD_EVENT_TYPE_T *pEvent)
{
	ULONG	flags;

	LX_AUD_ALLOC_DEV_T	allocDev;
	LX_AUD_EVENT_MSG_T	eventMsg;

	/* Set a audio device. */
	allocDev = pEvent->allocDev;
	eventMsg = pEvent->eventMsg;

	/* Check a audio device for callback function. */
	if(allocDev >= AUD_DEV_MAX)
	{
		AUD_KDRV_ERROR("AUDIO_GetEvent : allocDev is AUD_DEV_MAX.(%d))\n", allocDev);
		return RET_ERROR;
	}

	//spin lock for protection
	spin_lock_irqsave(&gAudEventSpinLock, flags);

	//Check if a allocated device and event message is set.
	if( (gAudGetEvent[allocDev].allocDev != AUD_NO_DEV)		\
	  &&(gAudGetEvent[allocDev].eventMsg != LX_AUD_EVENT_MASK_NONE) )
	{
		//Set a event for notificaton.
		pEvent->allocDev = gAudGetEvent[allocDev].allocDev;
		pEvent->eventMsg = gAudGetEvent[allocDev].eventMsg;

		//Reset a audio GET event type for next event.
		gAudGetEvent[allocDev].allocDev  = pEvent->allocDev;
		gAudGetEvent[allocDev].eventMsg &= (~eventMsg);
	}
	else
	{
		//Set a event for notificaton.
		pEvent->allocDev = AUD_NO_DEV;
		pEvent->eventMsg = LX_AUD_EVENT_MASK_NONE;
	}

	//spin unlock for protection
	spin_unlock_irqrestore(&gAudEventSpinLock, flags);

	if(pEvent->eventMsg)
		AUD_KDRV_DEBUG("AUDIO_GetEvent(allocDev = %d, event(%d) = 0x%X)\n", allocDev, pEvent->allocDev, pEvent->eventMsg);
	else
		AUD_KDRV_ISR_DEBUG("AUDIO_GetEvent(allocDev = %d, event(%d) = 0x%X)\n", allocDev, pEvent->allocDev, pEvent->eventMsg);
	return RET_OK;
}

/**
 * Set the number of I2S for multichannel speakers.
 * @see KDRV_AUDIO_IoctlMaster
 */
static SINT32 AUDIO_SetI2SNum(UINT32 num)
{
	SeCmdSetOutCh			setSeOutCh;
	OutctrlCmdSetChannel	setOutctrlCh;
	PcmoutCmdSetSpkch		setPcmoutSpkCh;

	// Set Sound Engine
	setSeOutCh.ch = DEFAULT_I2S_CH * num;
	AUDIO_IMC_SendCmdParam(SE_CMD_SET_OUTCH, ADEC_MODULE_SE, sizeof(SeCmdSetOutCh), &setSeOutCh);

	// Set Output Control for Speaker
	setOutctrlCh.Ch = DEFAULT_I2S_CH * num;
	AUDIO_IMC_SendCmdParam(OUTCTRL_CMD_SET_CHANNEL, ADEC_MODULE_OUT_CTRL_0, sizeof(OutctrlCmdSetChannel), &setOutctrlCh);

	// Set Output for Speaker
	setPcmoutSpkCh.channel = DEFAULT_I2S_CH * num;
	AUDIO_IMC_SendCmdParam(PCMOUT_CMD_SET_SPKCH, ADEC_MODULE_OUT_PCM, sizeof(PcmoutCmdSetSpkch), &setPcmoutSpkCh);

	_gMasterInfo.ui32I2SNum = num;

	AUD_KDRV_DEBUG("%s(number = %d)\n", __F__, num);

	return RET_OK;
}


/**
 * Find Max Delay in Output Control Modules.
 * @see AUDIO_SetDelay
 */
UINT32 AUDIO_FindMaxDelay(void)
{
	UINT32 i;
	UINT32 ui32MaxDelay = 0;

	for(i = 0; i < LX_AUD_MASTER_OUTPUT_MAX; i++)
	{
		if(_gMasterInfo.outCtrlMod[i].ui32Delay > ui32MaxDelay)
		{
			ui32MaxDelay = _gMasterInfo.outCtrlMod[i].ui32Delay;
		}
	}

	return ui32MaxDelay;
}

static AUD_SE_FN_MODE_T AUDIO_GetSeFnMode(LX_AUD_MASTER_SE_FN_T seFnMode)
{
	AUD_SE_FN_MODE_T adecSeFnMode;

	switch(seFnMode)
	{
		case LX_AUD_MASTER_SE_FN_000:
			adecSeFnMode = AUD_SE_FN000;
			break;

		case LX_AUD_MASTER_SE_FN_001:
			adecSeFnMode = AUD_SE_FN001;
			break;

		case LX_AUD_MASTER_SE_FN_002:
			adecSeFnMode = AUD_SE_FN002;
			break;

		case LX_AUD_MASTER_SE_FN_003:
			adecSeFnMode = AUD_SE_FN003;
			break;

		case LX_AUD_MASTER_SE_FN_004_MODE1:
			adecSeFnMode = AUD_SE_FN004_MODE1;
			break;

		case LX_AUD_MASTER_SE_FN_004_MODE2:
			adecSeFnMode = AUD_SE_FN004_MODE2;
			break;

		case LX_AUD_MASTER_SE_FN_004_MODE3:
			adecSeFnMode = AUD_SE_FN004_MODE3;
			break;

		case LX_AUD_MASTER_SE_FN_005:
			adecSeFnMode = AUD_SE_FN005;
			break;

		case LX_AUD_MASTER_SE_FN_006:
			adecSeFnMode = AUD_SE_FN006;
			break;

		case LX_AUD_MASTER_SE_FN_007:
			adecSeFnMode = AUD_SE_FN007;
			break;

		case LX_AUD_MASTER_SE_FN_008:
			adecSeFnMode = AUD_SE_FN008;
			break;

		case LX_AUD_MASTER_SE_FN_009:
			adecSeFnMode = AUD_SE_FN009;
			break;

		case LX_AUD_MASTER_SE_FN_010:
			adecSeFnMode = AUD_SE_FN010;
			break;

		case LX_AUD_MASTER_SE_FN_011:
			adecSeFnMode = AUD_SE_FN011;
			break;

		case LX_AUD_MASTER_SE_FN_012:
			adecSeFnMode = AUD_SE_FN012;
			break;

		case LX_AUD_MASTER_SE_FN_013:
			adecSeFnMode = AUD_SE_FN013;
			break;

		case LX_AUD_MASTER_SE_FN_UPDATE_PARAM:
			adecSeFnMode = AUD_SE_FN_UPDATE_PARAM;
			break;

		default:
			return AUD_SE_FN_MAX;
	}
	return adecSeFnMode;
}

/**
 * Update a input sampling frequency.
 * @see
*/
SINT32 KDRV_AUDIO_UpdateSamplingFreq(LX_AUD_SAMPLING_FREQ_T samplingFreq)
{
	LX_AUD_SPDIF_DTO_RATE_T	spdifDTORate;

	EsoutctrlCmdSetDelay	setSpdifDelay;
	SpdifCmdSetOutmode 		setSpdifOutpMode;

	if(_gMasterInfo.spdifOutputFormat == LX_AUD_MASTER_SPDIF_ES)
	{
		setSpdifDelay.Delay = _gMasterInfo.outCtrlMod[LX_AUD_MASTER_OUTPUT_SPDIF].ui32Delay;
		setSpdifDelay.Fs 	= samplingFreq;
		AUDIO_IMC_SendCmdParam(ESOUTCTRL_CMD_SET_DELAY, ADEC_MODULE_ESOUT_CTRL, sizeof(EsoutctrlCmdSetDelay), &setSpdifDelay);

		setSpdifOutpMode.out_format = LX_AUD_MASTER_SPDIF_ES;
		setSpdifOutpMode.Fs 		= samplingFreq;
		AUDIO_IMC_SendCmdParam(SPDIF_CMD_SET_OUTFORMAT, ADEC_MODULE_OUT_SPDIF, sizeof(SpdifCmdSetOutmode), &setSpdifOutpMode);

		/* Update a global SPDIF sampling frequency */
		_gMasterInfo.spdifSamplingFreq = samplingFreq;
	}
	else
	{
		/* Update a global SPDIF sampling frequency */
		_gMasterInfo.spdifSamplingFreq = LX_AUD_SAMPLING_FREQ_48_KHZ;
	}

	// Set DTO Int Sampling Frequency
	MIXED_IP_AUDIO_SetDTOIntSamplingFreq(g_setClockSrc, _gMasterInfo.spdifOutputFormat, _gMasterInfo.spdifSamplingFreq);

	//Lock a AUDIO SPDIF Semaphore, Do not use spin lock
	OS_LockMutex(&_gMasterInfo.spdifSemaphore);

	//Set a decoder sampling frequency and normal DTO rate
	#ifdef USE_DTO_AAD
	spdifDTORate = MIXED_IP_AUDIO_GetDTORate(g_setClockSrc, _gMasterInfo.spdifSamplingFreq, AUD_DTO_AAD);
 	(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(_gMasterInfo.spdifSamplingFreq, spdifDTORate, AUD_DTO_AAD);
	#else
	spdifDTORate = MIXED_IP_AUDIO_GetDTORate(g_setClockSrc, _gMasterInfo.spdifSamplingFreq, AUD_DTO_A);
 	(void)MIXED_IP_AUDIO_SetSPDIFSamplingFreq(_gMasterInfo.spdifSamplingFreq, spdifDTORate, AUD_DTO_A);
	#endif
	//Unlock a AUDIO SPDIF Semaphore
	OS_UnlockMutex(&_gMasterInfo.spdifSemaphore);

	AUD_KDRV_PRINT("%s(Fs %d)\n", __F__, samplingFreq);
	return RET_OK;
}

void	KDRV_AUDIO_ResetDisconnectMaster(void)
{
	UINT32				i = 0;
	ADEC_MODULE_ID		managerModule;
	ADEC_MODULE_ID		outctrlModule = ADEC_MODULE_OUT_CTRL_3;
	ADEC_MODULE_ID		outModule = ADEC_MODULE_OUT_SPDIF;
	CmCmdDisconnect		disconnectParam;

	managerModule = _AUDIO_GetManagerModule(outctrlModule);
	disconnectParam.module = outctrlModule;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);

	managerModule = _AUDIO_GetManagerModule(outModule);
	disconnectParam.module = outModule;
	disconnectParam.port = MOD_IN_PORT(0);
	AUDIO_IMC_SendCmdParam(CM_CMD_DISCONNECT, managerModule, sizeof(CmCmdDisconnect), &disconnectParam);

	for(i = 0; i < LX_AUD_MASTER_OUTPUT_MAX; i++)
	{
		AUDIO_DisconnectOutput(_gMasterInfo.outCtrlMod[i].ui32ConnectDev, i);
	}
}

void	KDRV_AUDIO_ResetMaster(void)
{
	_AUDIO_DeallocMaster(AUD_DEV_MAS0);

	_AUDIO_AllocMaster(AUD_DEV_MAS0);

}

void	KDRV_AUDIO_ResetMasterParam(void)
{
	LX_AUD_MASTER_PARAM_SE_FN_T 	seFnParam;

	seFnParam.fnMode = LX_AUD_MASTER_SE_FN_UPDATE_PARAM;
	seFnParam.dataOption = LX_AUD_MASTER_SE_DATA_ALL;
	seFnParam.ui32Param = &(_gMasterInfo.seModeParam[0]);
	seFnParam.ui32NoParam = 3;
	AUDIO_SetSEFunction(&seFnParam);

	seFnParam.fnMode = LX_AUD_MASTER_SE_FN_SET;
	seFnParam.ui32Param = &(_gMasterInfo.seModeParam[0]);
	seFnParam.ui32NoParam = 3;
	AUDIO_SetSEFunction(&seFnParam);

	AUDIO_SetSpdifOnOff(_gMasterInfo.spdifOnOff);
	AUDIO_SetI2SNum(_gMasterInfo.ui32I2SNum);
}

void	KDRV_AUDIO_ResetConnectMaster(void)
{
	AUD_OUT_CTRL_MODULE_T			*pOutCtrlMod = NULL;
	UINT32							i = 0;

	for(i = 0; i < LX_AUD_MASTER_OUTPUT_MAX; i++)
	{
		pOutCtrlMod = &(_gMasterInfo.outCtrlMod[i]);
		AUDIO_SetOutCtrlAll(pOutCtrlMod);
		AUDIO_ConnectOutput(_gPreConnectDev[i], i, _gMasterInfo.outCtrlMod[i].ui32UseSE);
	}
}

void	KDRV_AUDIO_RestartMaster(void)
{
	LX_AUD_SPDIF_DTO_RATE_T		spdifDTORate;
	DtoCtrlCmdSetDtorate		setDtoRate;

	//Send a IMC command for DTO setting
	if(g_AudKdrv.bInitDone == TRUE)
	{
		MIXED_IP_AUDIO_SetDTOIntSrc(g_setClockSrc, _gMasterInfo.spdifOutputFormat);

		// Set DTO Rate
	#ifdef USE_DTO_AAD
		spdifDTORate = MIXED_IP_AUDIO_GetDTORate(g_setClockSrc, _gMasterInfo.spdifSamplingFreq, AUD_DTO_AAD);
	#else
		spdifDTORate = MIXED_IP_AUDIO_GetDTORate(g_setClockSrc, _gMasterInfo.spdifSamplingFreq, AUD_DTO_A);
	#endif
		setDtoRate.dtorate			= (UINT32)spdifDTORate;
		setDtoRate.force_cnt_clear	= (UINT32)1;
		AUDIO_IMC_SendCmdParam(DTOCTRL_CMD_SET_DTORATE, ADEC_MODULE_DTO_A, sizeof(DtoCtrlCmdSetDtorate), &setDtoRate);

		MIXED_IP_AUDIO_StartDTO(g_setClockSrc, _gMasterInfo.spdifOutputFormat);
	}

	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_OUT_PCM);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_MIX_0);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_OUT_CTRL_0);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_OUT_CTRL_1);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_OUT_CTRL_2);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_OUT_CTRL_3);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_ESOUT_CTRL);
	AUDIO_IMC_SendCmd(ADEC_CMD_START, ADEC_MODULE_SE);

}

