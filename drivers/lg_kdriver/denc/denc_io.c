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
 * date       2010.03.17
 * note       Additional information.
 *
 * @addtogroup lg1150_denc
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#define USE_DENC_TURN_ON_ONTY_MCU_PART
#define USE_DENC_TTXDATA_LOADED_AT_MCU
#define USE_DENC_TTXDATA_ONLY_CPU_PART
#define USE_DENC_VPSDATA_ONLY_CPU_PART
#undef  USE_DENC_WSSDATA_ONLY_CPU_PART
#undef  USE_DENC_TTXDATA_BY_DDR

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "../de/de_model.h"

#include "../de/de_def.h"
#include "../de/de_ipc_def.h"
#include "../de/de_ipc.h"

#include "denc_kapi.h"
#include "denc_io.h"
#include "denc_hal.h"

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
BOOLEAN gVideoVcrEnable = FALSE;
BOOLEAN gVideoDacEnable = FALSE;
BOOLEAN gVideoTtxEnable = TRUE;
BOOLEAN gVideoVpsEnable = TRUE;
BOOLEAN gVideoWssEnable = TRUE;

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
/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize DENC module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_Init(unsigned long arg)
{
	int ret = RET_OK;
#ifndef USE_DENC_TTXDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	void *pstParams = NULL;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_INIT;
#endif
#endif

	do {
#ifndef USE_DENC_TTXDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		if (ret) break;
#endif
#endif
		ret = DENC_HAL_Init();
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief NTSC/PAL/SECAM encoder enable(TRUE : enable, FALSE : disable)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_OnOff(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_ONOFF;
	BOOLEAN dacEnable;
#endif

	do {
        ret = copy_from_user(&gVideoVcrEnable, (void __user *)arg, sizeof(gVideoVcrEnable));
		if (ret) BREAK_WRONG(ret);
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(gVideoVcrEnable));
#endif
#ifndef USE_DENC_TURN_ON_ONTY_MCU_PART
		if (ret) break;
		ret = DENC_HAL_OnOff(&gVideoVcrEnable);
#endif
		if (ret) break;
		dacEnable = (gVideoDacEnable || gVideoVcrEnable)?TRUE:FALSE;
		ret = DENC_HAL_VdacPowerControl(&dacEnable);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Select the color standard of CVE.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_SetOutPutVideoStd(unsigned long arg)
{
	int ret = RET_OK;
	LX_DENC_VIDEO_SYSTEM_T stParams;
#ifdef INCLUDE_KDRV_DE
	LX_DENC_VIDEO_SYSTEM_T *pstParams = (LX_DENC_VIDEO_SYSTEM_T *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_SET_OUTPUT_VIDEO_STD;
#endif

	do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
		if (ret) break;
#endif
		ret = DENC_HAL_SetOutPutVideoStd(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Select the input source of CVE.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_SetSource(unsigned long arg)
{
	int ret = RET_OK;
	LX_DENC_VIDEO_SOURCE_T stParams;
#ifdef INCLUDE_KDRV_DE
	LX_DENC_VIDEO_SOURCE_T *pstParams = (LX_DENC_VIDEO_SOURCE_T *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_SET_SOURCE;
#endif

	do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
		if (ret) break;
#endif
		ret = DENC_HAL_SetSource(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Teletext insertion enable (TRUE : enable, FALSE : disable)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_TtxEnable(unsigned long arg)
{
	int ret = RET_OK;
#ifndef USE_DENC_TTXDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_TTX_ENABLE;
#endif
#endif

	do {
        ret = copy_from_user(&gVideoTtxEnable, (void __user *)arg, sizeof(gVideoTtxEnable));
		if (ret) BREAK_WRONG(ret);
#ifndef USE_DENC_TTXDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(gVideoTtxEnable));
		if (ret) break;
#endif
#endif
		ret = DENC_HAL_TtxEnable(&gVideoTtxEnable);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief wss insertion enable (TRUE : enable, FALSE : disable)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_WssEnable(unsigned long arg)
{
	int ret = RET_OK;
#ifndef USE_DENC_WSSDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_WSS_ENABLE;
#endif
#endif

	do {
#ifdef USE_DENC_WSSDATA_ONLY_CPU_PART
        ret = copy_from_user(&gVideoWssEnable, (void __user *)arg, sizeof(gVideoWssEnable));
		if (ret) BREAK_WRONG(ret);
		ret = DENC_HAL_WssEnable(&gVideoWssEnable);
#else
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(gVideoWssEnable));
#endif
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief VPS insertion enable (TRUE : enable, FALSE : disable)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_VpsEnable(unsigned long arg)
{
	int ret = RET_OK;
#ifndef USE_DENC_VPSDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_VPS_ENABLE;
#endif
#endif

	do {
        ret = copy_from_user(&gVideoVpsEnable, (void __user *)arg, sizeof(gVideoVpsEnable));
		if (ret) BREAK_WRONG(ret);
#ifndef USE_DENC_VPSDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(gVideoVpsEnable));
		if (ret) break;
#endif
#endif
		ret = DENC_HAL_VpsEnable(&gVideoVpsEnable);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Inserts Teletext data to VBI lines.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_SetTtxData(unsigned long arg)
{
	int ret = RET_OK;
	LX_DENC_TTX_DATA_T stParams;
	VIDEO_TTX_PACK_T   ttxPack;
#ifdef USE_DENC_TTXDATA_LOADED_AT_MCU
#ifdef INCLUDE_KDRV_DE
#ifndef USE_DENC_TTXDATA_BY_DDR
	DE_IPC_CMD_T ipcCmd = DENC_IPC_SET_TTX_DATA;
#endif
#endif
#endif

	do {
		if (!gVideoVcrEnable) break;
		if (!gVideoTtxEnable) break;
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		if (48 != stParams.Size) BREAK_WRONG(stParams.Size);
		ttxPack.ttxLine = stParams.Line_Number;
		ret = copy_from_user(ttxPack.ttxData, (void __user *)stParams.pPacket_Addr, stParams.Size);
		if (ret) BREAK_WRONG(ret);
#ifdef USE_DENC_TTXDATA_LOADED_AT_MCU
#ifdef INCLUDE_KDRV_DE
#ifdef USE_DENC_TTXDATA_BY_DDR
		ret = VIDEO_DENC_SetTtx(&ttxPack);
#else
		ret = DE_KIPC_SetData(ipcCmd, &ttxPack, sizeof(ttxPack));
#endif
#endif
#else
		stParams.pPacket_Addr = ttxPack.ttxData;
		ret = DENC_HAL_SetTtxData(&stParams);
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Inserts WSS data to VBI line.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_SetWssData(unsigned long arg)
{
	int ret = RET_OK;
	LX_DENC_WSS_DATA_T stParams;
#ifndef USE_DENC_WSSDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	LX_DENC_WSS_DATA_T *pstParams = (LX_DENC_WSS_DATA_T *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_SET_WSS_DATA;
#endif
#endif

	do {
		if (!gVideoVcrEnable) break;
#ifdef USE_DENC_WSSDATA_ONLY_CPU_PART
		if (!gVideoWssEnable) break;
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		ret = DENC_HAL_SetWssData(&stParams);
#else
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
#endif
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Inserts VPS data to VBI lines.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_SetVpsData(unsigned long arg)
{
	int ret = RET_OK;
	LX_DENC_VPS_DATA_T stParams;
	UINT8 vpsData[16];
#ifndef USE_DENC_VPSDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	DE_IPC_CMD_T ipcCmd = DENC_IPC_SET_VPS_DATA;
#endif
#endif

	do {
		if (!gVideoVcrEnable) break;
		if (!gVideoVpsEnable) break;
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
        ret = copy_from_user(&vpsData, (void __user *)stParams.pVPS_DATA, 15);
		if (ret) BREAK_WRONG(ret);
#ifndef USE_DENC_VPSDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
		vpsData[15] = stParams.Enable;
		ret = DE_KIPC_SetData(ipcCmd, vpsData, 16);
#endif
#else
		stParams.pVPS_DATA = vpsData;
		ret = DENC_HAL_SetVpsData(&stParams);
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Enable/disable internal colorbar pattern (TRUE : enable, FALSE : disable)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_ColorBarEnable(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN stParams;
#ifndef USE_DENC_TTXDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_COLORBAR_ENABLE;
#endif
#endif

	do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
#ifndef USE_DENC_TTXDATA_ONLY_CPU_PART
#ifdef INCLUDE_KDRV_DE
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		if (ret) break;
#endif
#endif
		ret = DENC_HAL_ColorBarEnable(&stParams);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Power On/Off VDAC & Buffer of DENC Block (0:off, 1:on)
 *
 * @param arg [IN] UINT32 data(not address)
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_VdacPowerControl(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN dacEnable;

	do {
        ret = copy_from_user(&gVideoDacEnable, (void __user *)arg, sizeof(gVideoDacEnable));
		if (ret) BREAK_WRONG(ret);

		dacEnable = (gVideoDacEnable || gVideoVcrEnable)?TRUE:FALSE;
		ret = DENC_HAL_VdacPowerControl(&dacEnable);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set dark of DENC Block (0:off, 1:on)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_MuteControl(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_MUTE_CONTROL;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(BOOLEAN));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief turn on/off sub-scaler for 3D auto detectiong by capturing video.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DENC_IO_StripCaptureControl(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	BOOLEAN *pstParams = (BOOLEAN *)arg;
	DE_IPC_CMD_T ipcCmd = DENC_IPC_STRIP_CAPTURE_CONTROL;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(BOOLEAN));
#endif

	return ret;
}

/**  @} */
