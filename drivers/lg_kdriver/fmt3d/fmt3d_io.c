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
#include <asm/io.h>

#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "../de/de_model.h"

#include "../de/de_def.h"
#include "../de/l8/de_ipc_def_l8.h"
#include "../de/de_ipc.h"

#include "fmt3d_kapi.h"

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
#ifdef INCLUDE_KDRV_DE
#ifdef USE_COLUMN_ALTERNATIVE_HALF_CLOCK
// this will be removed in next time
//extern int FMT3D_SetLAMode(BOOLEAN b3dLaMode);
#endif
#endif

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
/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize 3D formatter module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_Init(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	void *pstParams = NULL;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_INIT;

	ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter processing mode
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetProcessMode(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_PROCESS_MODE_T *pstParams = (LX_3D_PROCESS_MODE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_PROCESS_MODE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_PROCESS_MODE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get 3D formatter processing mode
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_GetProcessMode(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_PROCESS_MODE_T *pstParams = (LX_3D_PROCESS_MODE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_GET_PROCESS_MODE;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		//if (ret) break;
		ret = DE_IPC_GetData(pstParams, sizeof(LX_3D_PROCESS_MODE_T));
		ffprintk("src_mux(%d), run_mode(0x%08x), dis_fmt(%d), dis_freq(%d), out_lr_order(%d), cvg_mode(%d), cvg_value(%d), cvg_min(%d), cvg_max(%d)\n", pstParams->src_mux, pstParams->run_mode, pstParams->dis_fmt, pstParams->dis_freq, pstParams->out_lr_order, pstParams->cvg_mode, pstParams->cvg_value, pstParams->cvg_min, pstParams->cvg_max);
	} while (0);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image setting
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetInImgInfo(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_IN_CONFIG_T *pstParams = (LX_3D_IN_CONFIG_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_IN_IMG_INFO;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_IN_CONFIG_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get 3D formatter input image setting
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_GetInImgInfo(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_IN_CONFIG_T *pstParams = (LX_3D_IN_CONFIG_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_GET_IN_IMG_INFO;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		//if (ret) break;
		ret = DE_IPC_GetData(pstParams, sizeof(LX_3D_IN_CONFIG_T));
	} while (0);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get 3D formatter output image info.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_GetOutImgInfo(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_OUT_IMG_INFO_T *pstParams = (LX_3D_OUT_IMG_INFO_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_GET_OUT_IMG_INFO;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
		//if (ret) break;
		ret = DE_IPC_GetData(pstParams, sizeof(LX_3D_OUT_IMG_INFO_T));
	} while (0);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter running mode.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetRunmode(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_RUNMODE_T *pstParams = (LX_3D_RUNMODE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_RUNMODE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_RUNMODE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image left/right order.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_ToggleLrInOrder(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_LR_ORDER_T *pstParams = (LX_3D_LR_ORDER_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_TOGGLE_LR_IN_ORDER;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_LR_ORDER_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter output left/right first order.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_ToggleLrOutOrder(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_LR_ORDER_T *pstParams = (LX_3D_LR_ORDER_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_TOGGLE_LR_OUT_ORDER;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_LR_ORDER_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image format.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetInImgFmt(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_IMG_FMT_T *pstParams = (LX_3D_IMG_FMT_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_IN_IMG_FMT;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_IMG_FMT_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter display format(line interleaved or frame sequential).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetDisFmt(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_DIS_FMT_TYPE_T *pstParams = (LX_3D_DIS_FMT_TYPE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_DIS_FMT;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_DIS_FMT_TYPE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetInFrRate(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_IMG_FREQ_T *pstParams = (LX_3D_IMG_FREQ_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_IN_FR_RATE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_IMG_FREQ_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter output frame rate (120Hz or 240Hz)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetOutFrRate(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_DIS_FREQ_T *pstParams = (LX_3D_DIS_FREQ_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_OUT_FR_RATE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_DIS_FREQ_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D convergence
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetConvergence(signed long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_CONVERGENCE_CTRL_T *pstParams = (LX_3D_CONVERGENCE_CTRL_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_CONVERGENCE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_CONVERGENCE_CTRL_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetImgDoublePic(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_IMG_DOUBLE_PIC_T *pstParams = (LX_3D_IMG_DOUBLE_PIC_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_IMG_DOUBLE_PIC;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_IMG_DOUBLE_PIC_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image sample mode.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetSampleMode(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_SAMPLE_MODE_T *pstParams = (LX_3D_SAMPLE_MODE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_SAMPLE_MODE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_SAMPLE_MODE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select 3D formatter input source path.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetSrcMux(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_SRC_MUX_TYPE_T *pstParams = (LX_3D_SRC_MUX_TYPE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_SRC_MUX;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_SRC_MUX_TYPE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter input image scan type
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetImgScanType(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_IMG_SCAN_TYPE_T *pstParams = (LX_3D_IMG_SCAN_TYPE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_IMG_SCAN_TYPE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_IMG_SCAN_TYPE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter output type for FRC MCU operation
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetFrcOutType(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_OUT_TYPE_T *pstParams = (LX_3D_OUT_TYPE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_FRC_OUT_TYPE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_OUT_TYPE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D formatter output LR order for FRC MCU operation
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetFrcOutLrOrder(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_LR_ORDER_T *pstParams = (LX_3D_LR_ORDER_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_FRC_OUT_LR_ORDER;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_LR_ORDER_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set T3 convergence
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_T3_IO_SetConvergence(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_CONVERGENCE_CTRL_T *pstParams = (LX_3D_CONVERGENCE_CTRL_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_T3_IPC_SET_CONVERGENCE;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_CONVERGENCE_CTRL_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set T3 depth control
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_T3_IO_SetDepthCtrl(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	UINT16 *pstParams = (UINT16 *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_T3_IPC_SET_DEPTH_CTRL;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(UINT16));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set FPR FHD mode
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetFprFhd(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_FPR_FHD_MODE_T *pstParams = (LX_3D_FPR_FHD_MODE_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_FPR_FHD;

	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_FPR_FHD_MODE_T));
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set input/output control (onoff, format, lr order)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int FMT3D_IO_SetInOutCtrl(unsigned long arg)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	LX_3D_INOUT_CTRL_T *pstParams = (LX_3D_INOUT_CTRL_T *)arg;
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_INOUT_CTRL;
#ifdef USE_COLUMN_ALTERNATIVE_HALF_CLOCK
	LX_3D_INOUT_CTRL_T stParams;
	BOOLEAN b3dLaMode;
	static LX_3D_RUNMODE_T    run3dMode  = LX_3D_RUNMODE_OFF;
	static LX_3D_IMG_FMT_IN_T in3dFormat = LX_3D_IMG_IN_TOPNBOTTOM;

	do {
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_INOUT_CTRL_T));
        if (ret) break;
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
		do {
			if (0xff != stParams.run_mode)   run3dMode  = stParams.run_mode;
			if (0xff != stParams.in_img_fmt) in3dFormat = stParams.in_img_fmt;
			b3dLaMode = FALSE;
			if (!run3dMode) break;
			if (LX_3D_IMG_IN_COLUMNALTERNATIVE != in3dFormat) break;
			b3dLaMode = TRUE;
		} while (0);
//		ret = FMT3D_SetLAMode(b3dLaMode);
	} while (0);
#else
	ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_3D_INOUT_CTRL_T));
#endif
#endif

	return ret;
}

/**  @} */
