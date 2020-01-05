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
 * date       2010.02.19
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#define USE_GRAB_PIXEL_BY_CAPTURING_FRAME
#undef  USE_CVI_COPY_TO_NFS
#undef  USE_DSP_COPY_TO_NFS
#define USE_DE_WIN_BLANK_AT_MCU_PART
#define USE_DE_CVI_FIR_AT_MCU_PART
#define USE_DE_CVI_TPG_AT_MCU_PART
#define USE_DE_CVI_CSAMPLE_AT_MCU_PART
#define USE_DE_CVI_RESHAPE_AT_MCU_PART
#define USE_DE_CVI_GET_INFO_AT_MCU_PART

#if defined(USE_CVI_COPY_TO_NFS) || defined(USE_DSP_COPY_TO_NFS)
#  define USE_FRAME_COPY_TO_NFS
#endif
/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_qkb.h"
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "de_kapi.h"
#include "fmt3d_kapi.h"

#include "de_def.h"
#include "de_ipc_def.h"
#ifdef USE_KDRV_CODES_FOR_L9
#include "l9/de_cfg_l9.h"
#endif
#ifdef USE_KDRV_CODES_FOR_H13
#include "h13/de_cfg_h13.h"
#endif
#include "de_ipc.h"
#include "de_hal.h"
#include "de_io.h"
#ifdef INCLUDE_KDRV_VENC
#include "venc_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_SUSPEND
#define DE_COPY_FROM_USER(indx, to, from, n)    de_copy_from_user(g_de_suspended, indx, to, from, n)
#define DE_IPC_SETDATA(cmd, msg, n)             DE_KIPC_SetData(cmd, &msg, n);
#define DE_BACK_FROM_USER(indx, to, from, n)    de_copy_from_user(1, indx, to, from, n)
#else
#define DE_COPY_FROM_USER(indx, to, from, n)    copy_from_user(to, from, n)
#define DE_IPC_SETDATA(cmd, msg, n)             DE_IPC_SetData(cmd, p##msg, n);
#define DE_BACK_FROM_USER(indx, to, from, n)    (RET_OK)
#endif

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_SUSPEND
typedef enum {
    DE_SUSPEND_INIT                 ,  // 0
    DE_SUSPEND_SETBGCOLOR           ,  // 1
    DE_SUSPEND_SETWINBLANK          ,  // 2
    DE_SUSPEND_SETINPUTWIN          ,  // 3
    DE_SUSPEND_SETOUTWIN            ,  // 4
    DE_SUSPEND_SETINPUTSRC          ,  // 5
    DE_SUSPEND_SETDISOUT            ,  // 6
    DE_SUSPEND_SETCVISRCTYPE        ,  // 7
    DE_SUSPEND_SETCVICSC            ,  // 8
    DE_SUSPEND_SETPOSTCSC           ,  // 9
    DE_SUSPEND_SETDISFMT            ,  // 10
    DE_SUSPEND_SETFRRATE            ,  // 11
    DE_SUSPEND_SETCAPTUREWIN        ,  // 12
    DE_SUSPEND_SETSPREAD            ,  // 13
    DE_SUSPEND_SETCVIFIR            ,  // 14
    DE_SUSPEND_SETCVITPG            ,  // 15
    DE_SUSPEND_SETCVICSAMPLEMODE    ,  // 16
    DE_SUSPEND_SETCVISYNCRESHAPE    ,  // 17
    DE_SUSPEND_SETPETESTPATTERNGEN  ,  // 18
    DE_SUSPEND_SETPEBBDCTRL         ,  // 19
    DE_SUSPEND_OIF_INIT             ,  // 20
    DE_SUSPEND_OIF_SETLVDSOUTPUT    ,  // 21
    DE_SUSPEND_OIF_SETLVDSPOWER     ,  // 22
    DE_SUSPEND_OIF_SETDARKSCREEN    ,  // 23
    DE_SUSPEND_OIF_SETVESAJEIDA     ,  // 24
    DE_SUSPEND_OIF_SETPANELIF       ,  // 25
    DE_SUSPEND_OIF_SETPIXEL         ,  // 26
    DE_SUSPEND_OIF_SETBITDEPTH      ,  // 27
    DE_SUSPEND_OIF_SELECTOUTPATH    ,  // 28
    DE_SUSPEND_OIF_SELECTLVDSPATH   ,  // 29
    DE_SUSPEND_OIF_SELECTOUTCH      ,  // 30
    DE_SUSPEND_OIF_SELECTLEDPATH    ,  // 31
    DE_SUSPEND_OIF_SELECTPWMPATH    ,  // 32
    DE_SUSPEND_OIF_SELECTLRPATH     ,  // 33
    DE_SUSPEND_SETTABLE             ,  // 34
    DE_SUSPEND_SETDVRFMTCTRL        ,  // 35
    DE_SUSPEND_SETLVDSOUTCTRL       ,  // 36
    DE_SUSPEND_FCSETWININFO         ,  // 37
    DE_SUSPEND_SETSUBSCFREEZE       ,  // 38
    DE_SUSPEND_SET3DFULLMODE        ,  // 39
    DE_SUSPEND_SELECTWULTIWINSRC    ,  // 40
    DE_SUSPEND_CVIFREEZE            ,  // 41
    DE_SUSPEND_SETZLIST             ,  // 42
    DE_SUSPEND_SETUDMODE	    ,  // 43
	//DE_SUSPEND_CVI_DELAY	    ,  // 44
    DE_SUSPEND_SETPWMCONTROL        ,  // 45
    DE_SUSPEND_SETPWMDUTYCYCLE      ,  // 46
    DE_SUSPEND_SETPWMFREQUENCY      ,  // 47
    DE_SUSPEND_SETPWMPULSEWIDTH     ,  // 48
    DE_SUSPEND_SETLOWDELAY          ,  // 49
    DE_SUSPEND_SETLVDSPORTSWAP      ,  // 50
    DE_SUSPEND_SETMULTIVISION       ,  // 51
    DE_SUSPEND_SETFRAMETOOSD        ,  // 52
    DE_SUSPEND_SET_IF_CONFIG           // 53
} DE_SUSPEND_INDX_T;

DE_SUSPEND_STORE_T de_suspend_store[] = {
    {TRUE  ,DE_SUSPEND_INIT                 ,sizeof(LX_DE_PANEL_TYPE_T)         ,DE_IO_Init                 ,NULL},
    {TRUE  ,DE_SUSPEND_SETBGCOLOR           ,sizeof(LX_DE_COLOR_T)              ,DE_IO_SetBgColor           ,NULL},
    {TRUE  ,DE_SUSPEND_SETWINBLANK          ,sizeof(LX_DE_SET_WIN_BLANK_T)      ,DE_IO_SetWinBlank          ,NULL},
    {TRUE  ,DE_SUSPEND_SETINPUTWIN          ,sizeof(LX_DE_WIN_DIMENSION_T)      ,DE_IO_SetInputWin          ,NULL},
    {TRUE  ,DE_SUSPEND_SETOUTWIN            ,sizeof(LX_DE_WIN_DIMENSION_T)      ,DE_IO_SetOutWin            ,NULL},
    {TRUE  ,DE_SUSPEND_SETINPUTSRC          ,sizeof(LX_DE_SET_INPUT_T)          ,DE_IO_SetInputSrc          ,NULL},
    {TRUE  ,DE_SUSPEND_SETDISOUT            ,sizeof(BOOLEAN)                    ,DE_IO_SetDisOut            ,NULL},
    {TRUE  ,DE_SUSPEND_SETCVISRCTYPE        ,sizeof(LX_DE_CVI_SRC_TYPE_T)       ,DE_IO_SetCviSrcType        ,NULL},
    {TRUE  ,DE_SUSPEND_SETCVICSC            ,sizeof(LX_DE_CVI_CSC_T)            ,DE_IO_SetCviCsc            ,NULL},
    {TRUE  ,DE_SUSPEND_SETPOSTCSC           ,sizeof(LX_DE_POST_CSC_T)           ,DE_IO_SetPostCsc           ,NULL},
    {TRUE  ,DE_SUSPEND_SETDISFMT            ,sizeof(LX_DE_DIS_FMT_T)            ,DE_IO_SetDisFmt            ,NULL},
    {TRUE  ,DE_SUSPEND_SETFRRATE            ,sizeof(LX_DE_FR_RATE_T)            ,DE_IO_SetFrRate            ,NULL},
    {TRUE  ,DE_SUSPEND_SETCAPTUREWIN        ,sizeof(LX_DE_CVI_CAPTURE_WIN_T)    ,DE_IO_SetCaptureWin        ,NULL},
    {TRUE  ,DE_SUSPEND_SETSPREAD            ,sizeof(LX_DE_SET_SPREAD_T)         ,DE_IO_SetSpread            ,NULL},
    {TRUE  ,DE_SUSPEND_SETCVIFIR            ,sizeof(LX_DE_CVI_FIR_T)            ,DE_IO_SetCviFir            ,NULL},
    {TRUE  ,DE_SUSPEND_SETCVITPG            ,sizeof(LX_DE_CVI_TPG_T)            ,DE_IO_SetCviTpg            ,NULL},
    {TRUE  ,DE_SUSPEND_SETCVICSAMPLEMODE    ,sizeof(LX_DE_CSAMPLE_MODE_T)       ,DE_IO_SetCviCsampleMode    ,NULL},
    {TRUE  ,DE_SUSPEND_SETCVISYNCRESHAPE    ,sizeof(LX_DE_CVI_SYNC_RESHAPE_T)   ,DE_IO_SetCviSyncReshape    ,NULL},
    {TRUE  ,DE_SUSPEND_SETPETESTPATTERNGEN  ,sizeof(LX_DE_PE_TPG_T)             ,DE_IO_SetPeTestPatternGen  ,NULL},
    {TRUE  ,DE_SUSPEND_SETPEBBDCTRL         ,sizeof(LX_DE_PE_BBD_CTRL_T)        ,DE_IO_SetPeBbdCtrl         ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_INIT             ,sizeof(LX_DE_OIF_INFO_T)           ,DE_IO_OIF_Init             ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETLVDSOUTPUT    ,sizeof(BOOLEAN)                    ,DE_IO_OIF_SetLvdsOutput    ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETLVDSPOWER     ,sizeof(BOOLEAN)                    ,DE_IO_OIF_SetLvdsPower     ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETDARKSCREEN    ,sizeof(BOOLEAN)                    ,DE_IO_OIF_SetDarkScreen    ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETVESAJEIDA     ,sizeof(LX_DE_OIF_STD_T)            ,DE_IO_OIF_SetVesaJeida     ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETPANELIF       ,sizeof(LX_DE_OIF_PANEL_IF_T)       ,DE_IO_OIF_SetPanelIf       ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETPIXEL         ,sizeof(LX_DE_OIF_PIXEL_T)          ,DE_IO_OIF_SetPixel         ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SETBITDEPTH      ,sizeof(LX_DE_OIF_BIT_DEPTH_T)      ,DE_IO_OIF_SetBitDepth      ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SELECTOUTPATH    ,sizeof(LX_DE_OIF_OUTPUT_PATH_T)    ,DE_IO_OIF_SelectOutPath    ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SELECTLVDSPATH   ,sizeof(LX_DE_OIF_LVDS_PATH_T)      ,DE_IO_OIF_SelectLvdsPath   ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SELECTOUTCH      ,sizeof(LX_DE_OIF_OUTPUT_CH_T)      ,DE_IO_OIF_SelectOutCh      ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SELECTLEDPATH    ,sizeof(LX_DE_OIF_LED_IN_PATH_T)    ,DE_IO_OIF_SelectLedPath    ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SELECTPWMPATH    ,sizeof(LX_DE_OIF_PWM_PATH_T)       ,DE_IO_OIF_SelectPwmPath    ,NULL},
    {TRUE  ,DE_SUSPEND_OIF_SELECTLRPATH     ,sizeof(LX_DE_OIF_LR_PATH_T)        ,DE_IO_OIF_SelectLrPath     ,NULL},
    {TRUE  ,DE_SUSPEND_SETTABLE             ,sizeof(LX_DE_SET_TABLE_T)          ,DE_IO_SetTable             ,NULL},
    {TRUE  ,DE_SUSPEND_SETDVRFMTCTRL        ,sizeof(LX_DE_DVR_DISFMT_T)         ,DE_IO_SetDvrFmtCtrl        ,NULL},
    {TRUE  ,DE_SUSPEND_SETLVDSOUTCTRL       ,sizeof(LX_DE_OIF_LVDS_OUT_CTRL_T)  ,DE_IO_OIF_SetLvdsOutCtrl   ,NULL},
    {TRUE  ,DE_SUSPEND_FCSETWININFO         ,sizeof(LX_DE_RECT_T)               ,DE_IO_FC_SetWinInfo        ,NULL},
    {TRUE  ,DE_SUSPEND_SETSUBSCFREEZE       ,sizeof(BOOLEAN)                    ,DE_IO_SetSubScFreeze       ,NULL},
    {TRUE  ,DE_SUSPEND_SET3DFULLMODE        ,sizeof(LX_DE_3D_FULL_MODE_T)       ,DE_IO_SetFull3DMode        ,NULL},
    {TRUE  ,DE_SUSPEND_SELECTWULTIWINSRC    ,sizeof(LX_DE_MULTI_WIN_SRC_T)      ,DE_IO_SelectMultiWinSrc    ,NULL},
    {TRUE  ,DE_SUSPEND_CVIFREEZE            ,sizeof(LX_DE_CVI_CAPTURE_FREEZE_T) ,DE_IO_SetCviFreeze         ,NULL},
    {TRUE  ,DE_SUSPEND_SETZLIST             ,sizeof(LX_DE_ZLIST_T)				,DE_IO_SetZList		        ,NULL},
    {TRUE  ,DE_SUSPEND_SETUDMODE            ,sizeof(BOOLEAN)					,DE_IO_SetUDMode	        ,NULL},
	//{TRUE  ,DE_SUSPEND_CVI_DELAY            ,sizeof(LX_DE_SET_DBG_T)			,DE_IO_SetDebug		        ,NULL},
    {TRUE  ,DE_SUSPEND_SETPWMCONTROL        ,sizeof(LX_DE_PWM_CTRL_T)			,DE_IO_SetPwmControl        ,NULL},
    {TRUE  ,DE_SUSPEND_SETPWMDUTYCYCLE      ,sizeof(LX_DE_PWM_PARAM_T)			,DE_IO_SetPwmDutyCycle      ,NULL},
    {TRUE  ,DE_SUSPEND_SETPWMFREQUENCY      ,sizeof(LX_DE_PWM_FREQ_T)			,DE_IO_SetPwmFrequency      ,NULL},
    {TRUE  ,DE_SUSPEND_SETPWMPULSEWIDTH     ,sizeof(LX_DE_PWM_PULSE_T)			,DE_IO_SetPwmPulseWidth     ,NULL},
    {TRUE  ,DE_SUSPEND_SETLOWDELAY          ,sizeof(UINT32)			            ,DE_IO_SetLowDelay          ,NULL},
    {TRUE  ,DE_SUSPEND_SETLVDSPORTSWAP		,sizeof(BOOLEAN) 					,DE_IO_OIF_SetLvdsPortSwap	,NULL},
    {TRUE  ,DE_SUSPEND_SETMULTIVISION		,sizeof(LX_DE_RECT_T) 				,DE_IO_SetMultiVision		,NULL},
    {TRUE  ,DE_SUSPEND_SETFRAMETOOSD		,sizeof(LX_DE_OSD_FRAME_CTRL_T) 	,DE_IO_SetFrameToOsd		,NULL},
    {TRUE  ,DE_SUSPEND_SET_IF_CONFIG		,sizeof(LX_DE_IF_CONFIG_T)			,DE_IO_SetInterfaceConfig	,NULL}
};
#endif

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
extern  int     DE_FW_Download(int fromFile);
#endif

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern int  g_de_suspended;
#ifdef INCLUDE_KDRV_VENC
extern LX_VENC_MEM_CFG_S_T *gpstVencMemConfig;
#endif

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/
LX_DE_3D_FULL_MODE_T g_de_3dFullMode;
BOOLEAN 			 g_de_UdMode;
LX_DE_CVI_SRC_TYPE_T g_de_CviSrcType;
LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T g_de_CpuMviPort = {LX_DE_WIN_MAIN, LX_DE_CPU_MVI_A};
LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T g_de_3d_info = {FALSE, LX_DE_MVI_2D, LX_DE_MVI_3D_L_FIRST};
LX_DE_DVR_DISFMT_T g_de_DvrDisFmt;

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_SUSPEND
static int g_de_resumed   = FALSE;
static int de_copy_from_user(unsigned short bSuspended, unsigned short indx, void * to, const void __user * from, unsigned int n);
#endif
#ifdef USE_GRAB_PIXEL_BY_CAPTURING_FRAME
static int DE_IPC_SetCviFreeze(BOOLEAN bFreeze);
#endif
static int DE_IO_SetPlatformVersion(void);

//LX_DE_CVI_CSC_T      g_de_CviCsc;

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_OIF_INFO_FROM_VAR
static LX_DE_OIF_INFO_T gsDeOifInfo;
#endif
//OS_SEM_T  _g_de_io_sem;

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize de moudle
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_Init(unsigned long arg)
{
    int ret;
    LX_DE_PANEL_TYPE_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_PANEL_TYPE_T *pstParams = (LX_DE_PANEL_TYPE_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_DE_INIT;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_INIT, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_Init(&stParams);
		if (ret) break;
        ret = DE_IO_SetPlatformVersion();
    } while (0);

    return ret;
}

static int DE_IO_SetPlatformVersion(void)
{
    UINT32 platformVersion;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_PLATFORM_VERSION;

	platformVersion = lx_chip_rev();

	return DE_KIPC_SetData(ipcCmd, &platformVersion, sizeof(platformVersion));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of firmware
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetFirmwareInfo(unsigned long arg)
{
    int ret;
    LX_DE_FIRMWARE_INFO_T *pstParams = (LX_DE_FIRMWARE_INFO_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_FIRMWARE_INFO;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, 0);
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_FIRMWARE_INFO_T));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set background color (non-active region color).
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetBgColor(unsigned long arg)
{
    int ret;
    LX_DE_COLOR_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_COLOR_T *pstParams = (LX_DE_COLOR_T*)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_BG_COLOR;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETBGCOLOR, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
		ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
		if (ret) break;
        ret = DE_HAL_SetBgColor(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set blank of selected window and blank color
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetWinBlank(unsigned long arg)
{
    int ret;
#ifdef USE_DE_WIN_BLANK_AT_MCU_PART
    LX_DE_SET_WIN_BLANK_T *pstParams = (LX_DE_SET_WIN_BLANK_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_WIN_BLANK;

    ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_SET_WIN_BLANK_T));
#else
    LX_DE_SET_WIN_BLANK_T stParams;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETWINBLANK, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetWinBlank(&stParams);
    } while (0);
#endif

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of selected window about size and offset of input window
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetInputWin(unsigned long arg)
{
    int ret;
    LX_DE_WIN_DIMENSION_T *pstParams = (LX_DE_WIN_DIMENSION_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_INPUT_WIN;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_WIN_DIMENSION_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_WIN_DIMENSION_T));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Information of selected window about size and offset of output window
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetOutWin(unsigned long arg)
{
    int ret;
    LX_DE_WIN_DIMENSION_T *pstParams = (LX_DE_WIN_DIMENSION_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_OUT_WIN;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_WIN_DIMENSION_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_WIN_DIMENSION_T));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information of selected window about size and offset of input window
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetInputWin(unsigned long arg)
{
    int ret;
    LX_DE_WIN_DIMENSION_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_WIN_DIMENSION_T *pstParams = (LX_DE_WIN_DIMENSION_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_INPUT_WIN;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETINPUTWIN, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information of selected window about size and offset of output window
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetOutWin(unsigned long arg)
{
    int ret;
    LX_DE_WIN_DIMENSION_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_WIN_DIMENSION_T *pstParams = (LX_DE_WIN_DIMENSION_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_OUT_WIN;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETOUTWIN, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Determine to make selected window Freeze or Not
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetFreeze(unsigned long arg)
{
    LX_DE_SET_FREEZE_T *pstParams = (LX_DE_SET_FREEZE_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_FREEZE;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_SET_FREEZE_T));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
#ifdef INCLUDE_KDRV_APR
// 20130222 maybe, this is unnecessary because of mute-control
#include "../apr/apr_core.h"
#endif

int DE_IO_SetInputSrc(unsigned long arg)
{
    int ret;
    LX_DE_SET_INPUT_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_SET_INPUT_T *pstParams = (LX_DE_SET_INPUT_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_INPUT_SRC;
#ifdef INCLUDE_KDRV_APR
	LX_APR_CONTROL_T aprParams;
#endif
    do {
       ret = DE_COPY_FROM_USER(DE_SUSPEND_SETINPUTSRC, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetInputSrc(&stParams);
#ifdef INCLUDE_KDRV_APR
		aprParams.cmd     = 1;
		aprParams.sel_alg = 1;
		aprParams.cap_enb = 0;
		aprParams.fd3_enb = 1;
		aprParams.fmt     = 0;
		APR_Core_SetControl(&aprParams);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Determine to make Display turn On or Off
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDisOut(unsigned long arg)
{
    int ret;
    BOOLEAN stParams;
#ifndef USE_DE_SUSPEND
    BOOLEAN *pstParams = (BOOLEAN*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DIS_OUT;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETDISOUT, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Select tye type to demonstrate
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetMultiWin(unsigned long arg)
{
    LX_DE_MULTI_WIN_TYPE_T *pstParams = (LX_DE_MULTI_WIN_TYPE_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_MULTI_WIN;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_MULTI_WIN_TYPE_T));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Determine selected multi window to turn On or Off
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_MultiWinEnable(unsigned long arg)
{
    BOOLEAN *pstParams = (BOOLEAN*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_MULTI_WIN_ENALBE;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(BOOLEAN));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get timing information which is comming from MVI port
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetMviTimingInfo(unsigned long arg)
{
    int ret;
    LX_DE_MVI_TIMING_INFO_T *pstParams = (LX_DE_MVI_TIMING_INFO_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_MVI_TIMING_INFO;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_MVI_TIMING_INFO_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_MVI_TIMING_INFO_T));

        if(g_de_3d_info.IsOverWriting == TRUE)
        {
        	pstParams->mpeg_time.mvi_3dfmt_info = g_de_3d_info.mvi_3dfmt_info;
            pstParams->mpeg_time.mvi_3dlr_order = g_de_3d_info.mvi_3dlr_order;
        }

    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set information which is comming from CVI port
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviSrcType(unsigned long arg)
{
    int ret;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_SRC_TYPE;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVISRCTYPE, &g_de_CviSrcType, (void __user *)arg, sizeof(g_de_CviSrcType));
        if (ret) break;
        ret = DE_KIPC_SetData(ipcCmd, &g_de_CviSrcType, sizeof(g_de_CviSrcType));
        if (ret) break;
        ret = DE_HAL_SetCviSrcType(&g_de_CviSrcType);
		if (!(g_de_3dFullMode || g_de_UdMode)) break;
		g_de_CviSrcType.cvi_channel = LX_DE_CVI_CH_B;
        ret = DE_HAL_SetCviSrcType(&g_de_CviSrcType);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get color space conversion matrix and offset for each external source information.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetCviCsc(unsigned long arg)
{
    int ret;
    LX_DE_CVI_CSC_T stParams;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_GetCviCsc(&stParams);
        if (ret) break;
        ret = copy_to_user((void __user *)arg, &stParams, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviCsc(unsigned long arg)
{
    int ret;
	LX_DE_CVI_CSC_T stParams;
#ifndef USE_DE_SUSPEND
	LX_DE_CVI_CSC_T *pstParams = (LX_DE_CVI_CSC_T*)arg;
#endif
	DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_CSC;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVICSC, &stParams, (void __user *)arg, sizeof(stParams));
#endif
        if (ret) break;
		ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
		//ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVICSC, &g_de_CviCsc, (void __user *)arg, sizeof(g_de_CviCsc));
		//if (ret) break;
		//ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(g_de_CviCsc));
		//if (ret) break;
		//ret = DE_HAL_SetCviCsc(&g_de_CviCsc);
		//if (!(g_de_3dFullMode || g_de_UdMode)) break;
		//g_de_CviCsc.cvi_channel = LX_DE_CVI_CH_B;
		//ret = DE_HAL_SetCviCsc(&g_de_CviCsc);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get color space conversion matrix for post processing block
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetPostCsc(unsigned long arg)
{
    int ret;
    LX_DE_POST_CSC_T stParams;

    do {
        //ret = DE_HAL_GetPostCsc(&stParams);
        //if (ret) break;
#ifdef USE_DE_SUSPEND
        ret = DE_BACK_FROM_USER(DE_SUSPEND_SETPOSTCSC, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = copy_to_user((void __user *)arg, &stParams, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix for post processing block
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPostCsc(unsigned long arg)
{
    int ret;
    LX_DE_POST_CSC_T stParams;
#ifdef USE_KDRV_CODES_FOR_CSC_n
#ifndef USE_DE_SUSPEND
    LX_DE_POST_CSC_T *pstParams = (LX_DE_POST_CSC_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_POST_CSC;
#endif

    do {
#if defined(USE_DE_SUSPEND) || !defined(USE_KDRV_CODES_FOR_CSC_n)
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPOSTCSC, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
#ifdef USE_KDRV_CODES_FOR_CSC_n
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
#else
        ret = DE_HAL_SetPostCsc(&stParams);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get MVI source colorimetry information.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetMviColorimetry(unsigned long arg)
{
    int ret;
    LX_DE_MVI_COLORIMETRY_T stParams;
    LX_DE_MVI_COLORIMETRY_T *pstParams = (LX_DE_MVI_COLORIMETRY_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_MVI_COLORIMETRY;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_MVI_COLORIMETRY_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_MVI_COLORIMETRY_T));
        if (ret) break;
        ret = DE_HAL_GetMviColorimetry(&stParams);  // NULL
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief determine to make selected surface to turn On or Off
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetZList(unsigned long arg)
{
    int ret;
    LX_DE_ZLIST_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_ZLIST_T *pstParams = (LX_DE_ZLIST_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_ZLIST;

	do {
#ifdef USE_DE_SUSPEND
		ret = DE_COPY_FROM_USER(DE_SUSPEND_SETZLIST, &stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
#endif
		ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(LX_DE_ZLIST_T));
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set display pannel formats which are pannel type and frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDisFmt(unsigned long arg)
{
    int ret;
    LX_DE_DIS_FMT_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_DIS_FMT_T *pstParams = (LX_DE_DIS_FMT_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DIS_FMT;
    LX_DE_FR_RATE_T frRate;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETDISFMT, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_SUSPEND
        ret = DE_HAL_Init(&stParams.panel_type);
#else
        ret = DE_HAL_Init(&pstParams->panel_type);
#endif
        if (ret) break;
        ret = DE_HAL_GetFrRate(&frRate);
        if (ret) break;
        frRate.fr_rate = stParams.fr_rate;
        ret = DE_HAL_SetFrRate(&frRate);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set display frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetOutFrRate(unsigned long arg)
{
    int ret;
    LX_DE_FR_RATE_T stParams;
    LX_DE_FR_RATE_T *pstParams = (LX_DE_FR_RATE_T *)arg;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_GetFrRate(&stParams);
        if (ret) break;
        ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set display pannel formats which are pannel type and frame rate.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetFrRate(unsigned long arg)
{
    int ret;
    LX_DE_FR_RATE_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_FR_RATE_T *pstParams = (LX_DE_FR_RATE_T*)arg;
#endif
#ifdef USE_SUPPORT_EUROPE
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_FR_RATE;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETFRRATE, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_SUPPORT_EUROPE
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_HAL_SetFrRate(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief grab video pixels of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GrabPixel(unsigned long arg)
{
    int ret;
    LX_DE_GRAB_PIXEL_T stParams;
    LX_DE_GRAB_PIXEL_T *pstParams = (LX_DE_GRAB_PIXEL_T*)arg;
    DE_IPC_CMD_T ipcCmd;
#ifdef USE_GRAB_PIXEL_BY_CAPTURING_FRAME
    LX_DE_CVI_RW_VIDEO_FRAME_T frameInfo;

    do {
		ipcCmd = DE_IPC_SET_CVI_VIDEO_FRAME_BUFFER;
		ret = DE_IPC_SetCviFreeze(TRUE);
        if (ret) break;
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        frameInfo.region = stParams.region;
        frameInfo.bReadOnOff = 7;
        ret = DE_KIPC_SetData(ipcCmd, &frameInfo, sizeof(frameInfo));
        ret = DE_KIPC_GetData(&frameInfo, sizeof(frameInfo));
        if (ret) break;
        stParams.region = frameInfo.region;
        ret = DE_HAL_GrabPixel(&stParams);
		stParams.region.realPixelGrabW = GET_BITS(stParams.region.pixelGrabW,16,16);
		stParams.region.realPixelGrabH = GET_BITS(stParams.region.pixelGrabW,0 ,16);
        if (ret) break;
		ret = DE_IPC_SetCviFreeze(FALSE);
        if (ret) break;
        ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
        if (ret)  BREAK_WRONG(ret);
    } while (0);
#else
    do {
		ipcCmd = DE_IPC_GRAB_PIXEL;
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
        ret = DE_IPC_GetData(pstParams, sizeof(stParams));
    } while (0);
#endif

    return ret;
}

#ifdef USE_GRAB_PIXEL_BY_CAPTURING_FRAME
static int DE_IPC_SetCviFreeze(BOOLEAN bFreeze)
{
    LX_DE_CVI_CAPTURE_FREEZE_T cviCaptureFreeze;

	cviCaptureFreeze.bCaptureOnOff   = bFreeze;
	cviCaptureFreeze.bCviFreezeOnOff = bFreeze;

	return DE_KIPC_SetData(DE_IPC_SET_CVI_FREEZE, &cviCaptureFreeze, sizeof(cviCaptureFreeze));
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief de cvi video frame buffer freeze to read/write video frame before cvi csc parameter for self-diagnosis.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviFreeze(unsigned long arg)
{
    int ret;
    LX_DE_CVI_CAPTURE_FREEZE_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_CVI_CAPTURE_FREEZE_T *pstParams = (LX_DE_CVI_CAPTURE_FREEZE_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_FREEZE;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_CVIFREEZE, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviVideoFrameBuffer(unsigned long arg)
{
    int ret;
    LX_DE_CVI_RW_VIDEO_FRAME_T stParams;
    LX_DE_CVI_RW_VIDEO_FRAME_T frameInfo;
    LX_DE_GRAB_COLOR_T         *pFrameColor = NULL;
    UINT32                     phyFrameRows;
    UINT32                     phyFrameAddr = 0;
    UINT32                     frameSize;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_VIDEO_FRAME_BUFFER;
#ifdef USE_FRAME_COPY_TO_NFS
    OS_FILE_T   fw_file;
    char filePath[200];
    char fileName[100];
#else
    LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams = (LX_DE_CVI_RW_VIDEO_FRAME_T*)arg;
#endif

	memset(&frameInfo, 0, sizeof(LX_DE_CVI_RW_VIDEO_FRAME_T));
	memset(&stParams, 0, sizeof(LX_DE_CVI_RW_VIDEO_FRAME_T));

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_DE_CVI_RW_VIDEO_FRAME_T));
        if (ret) BREAK_WRONG(ipcCmd);
#ifdef USE_FRAME_COPY_TO_NFS
        stParams.region.pixelGrabW = 1920;
        stParams.region.pixelGrabH = 1080;
        stParams.region.pixelGrabX = 0;
        stParams.region.pixelGrabY = 0;
        stParams.bReadOnOff = 1;
#ifdef USE_DSP_COPY_TO_NFS
        stParams.region.win_id = LX_DE_WIN_MAX;
        stParams.region.colorDepth = 0;
#endif
#endif
        ret = DE_KIPC_SetData(ipcCmd, &stParams, sizeof(stParams));
        ret = DE_KIPC_GetData(&frameInfo, sizeof(frameInfo));
        if (ret) break;
        frameSize    = stParams.region.pixelGrabW * stParams.region.pixelGrabH * sizeof(LX_DE_GRAB_COLOR_T);
        phyFrameRows = GET_BITS(frameInfo.region.pixelGrabY ,16,16);
#ifdef USE_KDRV_CODES_FOR_H13
		if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
#ifdef USE_FRAME_COPY_TO_NFS
			strcpy(filePath, "/home/jaemo.kim/res/lglib/kdrv/");
#endif
			phyFrameAddr = CONV_MEM_ROW2BYTE(phyFrameRows) | GET_SVAL(frameInfo.region.colorDepth,4,4,28);
		} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
		if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
#ifdef USE_FRAME_COPY_TO_NFS
			strcpy(filePath, "/mnt/lg/res/lglib/kdrv/");
#endif
			phyFrameAddr = VIDEO_L9_ROW2PHY(phyFrameRows);
		} else
#endif
		{
		}
		if(!phyFrameAddr) break;
		pFrameColor = (LX_DE_GRAB_COLOR_T *)ioremap(phyFrameAddr, frameSize);
        CHECK_KNULL(pFrameColor);
        frameInfo.color = pFrameColor;
        frameInfo.bReadOnOff |= GET_BITS(stParams.bReadOnOff,0,1);
        if (GET_BITS(stParams.bReadOnOff,0,1)) {
            ret = DE_HAL_SetCviVideoFrameBuffer(&frameInfo);
            if (ret) break;
#ifdef USE_FRAME_COPY_TO_NFS
            sprintf(fileName, "Captured_Video__%dx%d.444_60p.img", stParams.region.pixelGrabW, stParams.region.pixelGrabH);
            strcat(filePath, fileName);
            if ( RET_OK != OS_OpenFile( &fw_file, filePath, O_CREAT|O_RDWR|O_LARGEFILE, 0666 ) )
            {
                printk("<error> can't open fw_file (%s)\n", filePath);
				BREAK_WRONG(ret);
            }
            ret = OS_WriteFile(&fw_file, (char *)pFrameColor, frameSize);
			if (ret != frameSize) BREAK_WRONG(ret);
            ret = OS_CloseFile( &fw_file );
			if (ret) BREAK_WRONG(ret);
#else
            ret = copy_to_user((void __user *)stParams.color, pFrameColor, frameSize);
			if (ret) BREAK_WRONG(ret);
#endif
        } else {
            ret = copy_from_user(pFrameColor, (void __user *)stParams.color, frameSize);
            if (ret)  BREAK_WRONG(ret);
            ret = DE_HAL_SetCviVideoFrameBuffer(&frameInfo);
        }
        stParams.region.realPixelGrabW = frameInfo.region.realPixelGrabW;
        stParams.region.realPixelGrabH = frameInfo.region.realPixelGrabH;
        stParams.region.colorSpace     = frameInfo.region.colorSpace;
#ifndef USE_FRAME_COPY_TO_NFS
        ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
        if (ret)  BREAK_WRONG(ret);
#endif
    } while (0);
    if(pFrameColor) iounmap(pFrameColor);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_RegWr(unsigned long arg)
{
    int ret;
    LX_DE_REG_WR_T *pstParams = (LX_DE_REG_WR_T*)arg;
    LX_DE_REG_WR_T lReg;
    UINT32 msgCnt = sizeof(LX_DE_REG_WR_T);
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_REG_WD;
#endif

    do {
        ret= copy_from_user(&lReg, (void __user *)pstParams, msgCnt);
        if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_WriteReg(lReg.wr_addr, lReg.wr_data);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Read Register
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_RegRd(unsigned long arg)
{
    int ret;
    UINT32 *pstParams = (UINT32*)arg;
    LX_DE_REG_WR_T lReg;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_REG_RD;
#endif

    do {
        ret = copy_from_user(&lReg.wr_addr, (void __user *)pstParams, sizeof(UINT32));
        if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_ReadReg(lReg.wr_addr, &lReg.wr_data);
        if (ret) BREAK_WRONG(ret);
        ret = copy_to_user((void __user *)pstParams, &lReg.wr_data, sizeof(UINT32));
        if (ret) BREAK_WRONG(ret);
    } while (0);
    //ffprintk("Reg[0x%08x] = 0x%08x\n", lReg.wr_addr, lReg.wr_data);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get de captured video size and offset
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetCaptureWin(unsigned long arg)
{
    int ret;
    LX_DE_CVI_CAPTURE_WIN_T stParams;
    LX_DE_CVI_CAPTURE_WIN_T *pstParams = (LX_DE_CVI_CAPTURE_WIN_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_CAPTURE_WIN;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
        ret = DE_IPC_GetData(pstParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de captured video size and offset
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCaptureWin(unsigned long arg)
{
    int ret;
    LX_DE_CVI_CAPTURE_WIN_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_CVI_CAPTURE_WIN_T *pstParams = (LX_DE_CVI_CAPTURE_WIN_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CAPTURE_WIN;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCAPTUREWIN, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set color and IRE levels of full pattern.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetIrePattern(unsigned long arg) //TODO
{
    int ret;
    LX_DE_SET_IRE_PATTERN_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_IRE_PATTERN;
#endif

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS spread spectrum for 60Hz mode (PDP).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSpread(unsigned long arg) //TODO
{
    int ret;
    LX_DE_SET_SPREAD_T stParams;
#ifdef USE_IPC_CHECK_TEMPERALY_DEFINITIOUSE_IPC_CHECK_TEMPERALY_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SPREAD;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETSPREAD, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetSpread(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set deinterlace on/off control
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDeinterlace(unsigned long arg)
{
    int ret;
    BOOLEAN  stParams;
    BOOLEAN *pstParams = (BOOLEAN*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DEINTERLACE;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetDeinterlace(stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set uart for MCU or CPU
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetUart4MCU(unsigned long arg)
{
    int ret;
    BOOLEAN  stParams;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_SetUart4MCU(stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select pre-3D input mode  (0: normal mode, 1:frame by frame mode)
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPre3DInMode(unsigned long arg)
{
    LX_DE_PRE3D_IN_MODE_T *pstParams = (LX_DE_PRE3D_IN_MODE_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_PRE3D_IN_MODE;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_PRE3D_IN_MODE_T));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control pre-3D block on/off (0: disable, 1: enable)
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPre3DOprMode(unsigned long arg)
{
    LX_DE_3D_OPR_MODE_T *pstParams = (LX_DE_3D_OPR_MODE_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_3D_OPR_MODE;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_3D_OPR_MODE_T));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control de UD and specific 3D(SS Full & Frame Packing) operating mode
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetFull3DMode(unsigned long arg)
{
    int ret;
	//LX_DE_3D_FULL_MODE_T stParams;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_3D_FULL_MODE;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SET3DFULLMODE, &g_de_3dFullMode, (void __user *)arg, sizeof(g_de_3dFullMode));
		if (ret) break;
        ret = DE_KIPC_SetData(ipcCmd, &g_de_3dFullMode, sizeof(g_de_3dFullMode));
		if (ret) break;
        ret = DE_HAL_Set3DFullMode(&g_de_3dFullMode);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control de UD mode (on/off)
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetUDMode(unsigned long arg)
{
    int ret;
	//BOOLEAN stParams;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_UD_MODE;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETUDMODE, &g_de_UdMode, (void __user *)arg, sizeof(g_de_UdMode));
		if (ret) break;
        ret = DE_KIPC_SetData(ipcCmd, &g_de_UdMode, sizeof(g_de_UdMode));
		if (ret) break;
        ret = DE_HAL_SetUdMode(&g_de_UdMode);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de PWN enable/disable.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPwmControl(unsigned long arg)
{
    int ret;
    LX_DE_PWM_CTRL_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_PWM_CTRL_T *pstParams = (LX_DE_PWM_CTRL_T*)arg;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPWMCONTROL, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetPwmControl(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de PWN duty cycle.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPwmDutyCycle(unsigned long arg)
{
    int ret;
    LX_DE_PWM_PARAM_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_PWM_PARAM_T *pstParams = (LX_DE_PWM_PARAM_T*)arg;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPWMDUTYCYCLE, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetPwmDutyCycle(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de PWN frequency.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPwmFrequency(unsigned long arg)
{
    int ret;
    LX_DE_PWM_FREQ_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_PWM_FREQ_T *pstParams = (LX_DE_PWM_FREQ_T*)arg;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPWMFREQUENCY, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetPwmFrequency(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de PWN pulse width.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPwmPulseWidth(unsigned long arg)
{
    int ret;
    LX_DE_PWM_PULSE_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_PWM_PULSE_T *pstParams = (LX_DE_PWM_PULSE_T*)arg;
#endif

    do {
		ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPWMPULSEWIDTH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetPwmPulseWidth(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de CVE parameter.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCve(unsigned long arg)
{
    LX_DE_CVE_PARAM_T *pstParams = (LX_DE_CVE_PARAM_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVE;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_CVE_PARAM_T));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set de VCS parameter.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetVcs(unsigned long arg)
{
    int ret;
    LX_DE_VCS_IPC_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_VCS;
#endif

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_SetVcs(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize OIF module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_Init(unsigned long arg)
{
    int ret;
    LX_DE_OIF_INFO_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_INIT;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_INIT, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo = stParams;
#endif
        ret = DE_HAL_OIF_Init(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set LVDS OUTPUT Enable.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetLvdsOutput(unsigned long arg)
{
    int ret;
    BOOLEAN stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_LVDS_OUTPUT;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETLVDSOUTPUT, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_OIF_SetLvdsOutput(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set LVDS Power Enable.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetLvdsPower(unsigned long arg)
{
    int ret;
    BOOLEAN stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_LVDS_POWER;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETLVDSPOWER, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_OIF_SetLvdsPower(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set LVDS to black.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetDarkScreen(unsigned long arg)
{
    int ret;
    BOOLEAN stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_DARK_SCREEN;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETDARKSCREEN, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_OIF_SetDarkScreen(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Select LVDS type(VESA/JEIDA).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetVesaJeida(unsigned long arg)
{
    int ret;
    LX_DE_OIF_STD_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_VESA_JEIDA;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETVESAJEIDA, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eVesaJeida = stParams;
#endif
        ret = DE_HAL_OIF_SetVesaJeida(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select LVDS inteface type(LVDS/mini-LVDS).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetPanelIf(unsigned long arg)
{
    int ret;
    LX_DE_OIF_PANEL_IF_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_PANEL_IF;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETPANELIF, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eLvdsMini = stParams;
#endif
        ret = DE_HAL_OIF_SetPanelIf(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS pixel type( single/dual/quad).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetPixel(unsigned long arg)
{
    int ret;
    LX_DE_OIF_PIXEL_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_PIXEL;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETPIXEL, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.ePixel = stParams;
#endif
        ret = DE_HAL_OIF_SetPixel(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS bit resolution(10bit/8bit).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetBitDepth(unsigned long arg)
{
    int ret;
    LX_DE_OIF_BIT_DEPTH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SET_BIT_DEPTH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SETBITDEPTH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eBitMode = stParams;
#endif
        ret = DE_HAL_OIF_SetBitDepth(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS signal path from DE/FRC/LED/(ODC removed)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SelectOutPath(unsigned long arg)
{
    int ret;
    LX_DE_OIF_OUTPUT_PATH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SELECT_OUT_PATH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SELECTOUTPATH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eOutVideo = stParams;
#endif
        ret = DE_HAL_OIF_SelectOutPath(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS signal path from DE/FRC/LED/ODC
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SelectLvdsPath(unsigned long arg)
{
    int ret;
    LX_DE_OIF_LVDS_PATH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SELECT_LVDS_PATH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SELECTLVDSPATH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eOutLVDS = stParams;
#endif
        ret = DE_HAL_OIF_SelectLvdsPath(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select output chanel number 1CH, 2CH, 4CH according to resolution and frame rate
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SelectOutCh(unsigned long arg)
{
    int ret;
    LX_DE_OIF_OUTPUT_CH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SELECT_OUT_CH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SELECTOUTCH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eOutCH = stParams;
#endif
        ret = DE_HAL_OIF_SelectOutCh(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select LED input path from DE/FRC.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SelectLedPath(unsigned long arg)
{
    int ret;
    LX_DE_OIF_LED_IN_PATH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SELECT_LED_PATH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SELECTLEDPATH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eLedIn = stParams;
#endif
        ret = DE_HAL_OIF_SelectLedPath(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select PWM signal path from DE/FRC.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SelectPwmPath(unsigned long arg)
{
    int ret;
    LX_DE_OIF_PWM_PATH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SELECT_PWM_PATH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SELECTPWMPATH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.ePWM = stParams;
#endif
        ret = DE_HAL_OIF_SelectPwmPath(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select LR signal path from DE/FRC.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SelectLrPath(unsigned long arg)
{
    int ret;
    LX_DE_OIF_LR_PATH_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_SELECT_LR_PATH;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_OIF_SELECTLRPATH, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_OIF_INFO_FROM_VAR
        gsDeOifInfo.eLR = stParams;
#endif
        ret = DE_HAL_OIF_SelectLrPath(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get OIF setting information.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_GetInfo(unsigned long arg)
{
    int ret;
    LX_DE_OIF_INFO_T stParams;
    LX_DE_OIF_INFO_T *pstParams = (LX_DE_OIF_INFO_T *)arg;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_OIF_GET_INFO;
#endif

    do {
#ifdef USE_DE_OIF_INFO_FROM_VAR
        memcpy(&stParams, &gsDeOifInfo, sizeof(stParams));
#else
        ret = DE_HAL_OIF_GetInfo(&stParams);
        if (ret) break;
#endif
        ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control LVDS output channel.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetLvdsOutCtrl(unsigned long arg)
{
    int ret;
    LX_DE_OIF_LVDS_OUT_CTRL_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_OIF_LVDS_OUT_CTRL_T *pstParams = (LX_DE_OIF_LVDS_OUT_CTRL_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_LVDS_PATH_INFO;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETLVDSOUTCTRL, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
		ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(LX_DE_OIF_LVDS_OUT_CTRL_T));
		if (ret) break;
        ret = DE_HAL_OIF_SetLvdsOutCtrl(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief control LVDS port swap.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_OIF_SetLvdsPortSwap(unsigned long arg)
{
    int ret;
    BOOLEAN stParams;
#ifndef USE_DE_SUSPEND
    BOOLEAN *pstParams = (BOOLEAN*)arg;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETLVDSPORTSWAP, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_OIF_SetLvdsPortSwap(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Table
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetTable(unsigned long arg)
{
    int ret = RET_ERROR;
    LX_DE_SET_TABLE_T stParams;
    LX_DE_REG_WR_T *pTable = NULL;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_DE_SET_TABLE_T));
        if (ret) BREAK_WRONG(ret);
        if (!stParams.size) break;
	if (stParams.size > 1024*1024) break;
        CHECK_KNULL(stParams.pTable);
        pTable = OS_KMalloc(stParams.size);
        CHECK_KNULL(pTable);
        ret = copy_from_user(pTable, (void __user *)stParams.pTable, stParams.size);
        if (ret) BREAK_WRONG(ret);
        stParams.pTable = pTable;
        ret = DE_HAL_SetTable(&stParams);
    } while (0);
    OS_Free(pTable);

    return ret;
}


#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_IO_FW_Download(unsigned long arg)
{
    int ret;
    LX_DE_FW_DWLD_T stParams;
    char *lpData = NULL;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(LX_DE_FW_DWLD_T));
        if (ret) BREAK_WRONG(ret);
        if (!stParams.inx)  {
            ret = DE_FW_Download(FALSE);
            break;
        }
        if (!stParams.size) break;
	if (stParams.size > 16*1024*1024) break;
        if (!stParams.pData) break;
        lpData = OS_KMalloc(stParams.size);
        CHECK_KNULL(lpData);
        ret = copy_from_user(lpData, (void __user *)stParams.pData, stParams.size);
        if (ret) BREAK_WRONG(ret);
        stParams.pData = lpData;
        ret = DE_HAL_FW_Download(&stParams);
    } while (0);
    OS_Free(lpData);

    return ret;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief send captured video fir coef for double/quad sampling case.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviFir(unsigned long arg)
{
    int ret;
    LX_DE_CVI_FIR_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_CVI_FIR_T *pstParams = (LX_DE_CVI_FIR_T*)arg;
#endif
#ifdef USE_DE_CVI_FIR_AT_MCU_PART
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_FIR;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVIFIR, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_CVI_FIR_AT_MCU_PART
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
#else
        ret = DE_HAL_SetCviFir(&stParams);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video test pattern generator to black.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviTpg(unsigned long arg)
{
    int ret;
    LX_DE_CVI_TPG_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_CVI_TPG_T *pstParams = (LX_DE_CVI_TPG_T*)arg;
#endif
#ifdef USE_DE_CVI_TPG_AT_MCU_PART
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_TPG;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVITPG, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_CVI_TPG_AT_MCU_PART
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
#else
        ret = DE_HAL_SetCviTpg(&stParams);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video color sampling mode(sub sampling or 3 tap filtering).
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviCsampleMode(unsigned long arg)
{
    int ret;
    LX_DE_CSAMPLE_MODE_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_CSAMPLE_MODE_T *pstParams = (LX_DE_CSAMPLE_MODE_T*)arg;
#endif
#ifdef USE_DE_CVI_CSAMPLE_AT_MCU_PART
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_CSAMPLE_MODE;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVICSAMPLEMODE, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_CVI_CSAMPLE_AT_MCU_PART
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
#else
        ret = DE_HAL_SetCviCsampleMode(&stParams);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief reshape sync of captured video for PC input.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCviSyncReshape(unsigned long arg)
{
    int ret;
    LX_DE_CVI_SYNC_RESHAPE_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_CVI_SYNC_RESHAPE_T *pstParams = (LX_DE_CVI_SYNC_RESHAPE_T*)arg;
#endif
#ifdef USE_DE_CVI_RESHAPE_AT_MCU_PART
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_SYNC_RESHAPE;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETCVISYNCRESHAPE, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#ifdef USE_DE_CVI_RESHAPE_AT_MCU_PART
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
#else
        ret = DE_HAL_SetCviSyncReshape(&stParams);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief generate Test Pattern in PE region.
 *
 * @param [IN] structure pointer to carry information about PE gamma LUT region.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPeTestPatternGen(unsigned long arg)
{
    int ret;
    LX_DE_PE_TPG_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_PE_TPG_T *pstParams = (LX_DE_PE_TPG_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_PE_TEST_PATTERN_GEN;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPETESTPATTERNGEN, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetPeTestPatternGen(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set PE0 black boundary detection control.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetPeBbdCtrl(unsigned long arg)
{
    int ret;
    LX_DE_PE_BBD_CTRL_T stParams;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_PE_BBD_CTRL;
#endif

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETPEBBDCTRL, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_HAL_SetPeBbdCtrl(&stParams);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get PE0 black boundary detection status.
 *
 * @param arg [OUT] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetPeBbdStatus(unsigned long arg)
{
    int ret;
    LX_DE_PE_COORDINATE_T stParams;
    LX_DE_PE_COORDINATE_T *pstParams = (LX_DE_PE_COORDINATE_T *)arg;
#ifdef USE_IPC_CHECK_TEMPORAL_DEFINITION
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_PE_BBD_STATUS;
#endif

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_GetPeBbdStatus(&stParams);
        if (ret) break;
        ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
        if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set PE0 black boundary detection status.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetEdgeCrop(unsigned long arg)
{
    BOOLEAN *pstParams = (BOOLEAN*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_EDGE_CROP;

    return DE_IPC_SetData(ipcCmd, pstParams, sizeof(BOOLEAN));
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set dvr control.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDvrFmtCtrl(unsigned long arg)
{
    int ret;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_DVR_FMT_CTRL;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETDVRFMTCTRL, &g_de_DvrDisFmt, (void __user *)arg, sizeof(g_de_DvrDisFmt));
        if (ret) break;
#ifdef INCLUDE_KDRV_VENC
		g_de_DvrDisFmt.baseAddr = (gpstVencMemConfig)?gpstVencMemConfig->uiInBufBase:0x0;
#endif
        ret = DE_KIPC_SetData(ipcCmd, &g_de_DvrDisFmt, sizeof(g_de_DvrDisFmt));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set geomitery information of picture to be caputured.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_FC_SetWinInfo(unsigned long arg)
{
    int ret;
    LX_DE_RECT_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_RECT_T *pstParams = (LX_DE_RECT_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_FC_SET_WIN_INFO;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_FCSETWININFO, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get address of picture to be caputured.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_FC_GetFrameInfo(unsigned long arg)
{
    int ret;
    LX_DE_FC_PARAM_T *pstParams = (LX_DE_FC_PARAM_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_FC_GET_FRAME_INFO;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_FC_PARAM_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_FC_PARAM_T));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set frame caputuring mode On or Off.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSubScFreeze(unsigned long arg)
{
    int ret;
    BOOLEAN stParams;
#ifndef USE_DE_SUSPEND
    BOOLEAN *pstParams = (BOOLEAN*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_SUB_SC_FREEZE;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETSUBSCFREEZE, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select source for multi window.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SelectMultiWinSrc(unsigned long arg)
{
    int ret;
    LX_DE_MULTI_WIN_SRC_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_MULTI_WIN_SRC_T *pstParams = (LX_DE_MULTI_WIN_SRC_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SELECT_MULTI_WIN_SRC;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SELECTWULTIWINSRC, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
        if (ret) break;
		ret = DE_HAL_SelectMultiWinSrc(&stParams);
        if (ret) break;
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief select between SCART RGB bypass mode and CVD overlay mode
 *
 * @param arg [IN] bypass enable/disable
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetScartRGBBypassMode(unsigned long arg)
{
    int ret;
    int Enable;

    do {
        ret = copy_from_user(&Enable, (void __user *)arg, sizeof(int));
        if (ret) break;
		//ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
		//if (ret) break;
        ret = DE_HAL_SetSCARTRGBBypassMode(&Enable);
        if (ret) break;
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get information for cvi input.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetCviInfo(unsigned long arg)
{
    int ret = RET_OK;

#ifdef USE_DE_CVI_GET_INFO_AT_MCU_PART
    LX_DE_CVI_INFO_T *pstParams = (LX_DE_CVI_INFO_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_CVI_INFO;
#else
    LX_DE_CVI_INFO_T stParams;
#endif

    do {
#ifdef USE_DE_CVI_GET_INFO_AT_MCU_PART
		ret = DE_IPC_SetData(ipcCmd, &pstParams->win_id, sizeof(LX_DE_WIN_ID_T));
		ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_CVI_INFO_T));
#else
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		ret = DE_HAL_GetCviInfo(&stParams);
		if (ret) break;
        ret = copy_to_user((void __user *)arg, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
#endif
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get debug data.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetDebug(unsigned long arg)
{
    int ret;
    LX_DE_SET_DBG_T stParams;

    do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		ret = DE_HAL_GetDebug(&stParams);
		if (ret) break;
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set debug data.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetDebug(unsigned long arg)
{
    int ret = RET_OK;
    LX_DE_SET_DBG_T *pstParams = (LX_DE_SET_DBG_T*)arg;
#ifdef USE_DE_CVI_DELAY_ON_MCU_PART
    LX_DE_SET_DBG_T stParams;
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_CVI_DELAY;
#endif

	do {
		//ret = DE_COPY_FROM_USER(DE_SUSPEND_CVI_DELAY, &stParams, (void __user *)arg, sizeof(stParams));
		//if (ret) break;
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
#ifdef USE_DE_CVI_DELAY_ON_MCU_PART
		//ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
		ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(stParams));
        if (ret) break;
#endif
		ret = DE_HAL_SetDebug(pstParams);
    } while (0);

    return ret;
}

int DE_IO_SetTableOfPql(PQL_TABLE_HEAD_T tblHead, UINT8 *pPqlTable)
{
    int ret = RET_OK;
#ifdef INCLUDE_KDRV_PE
	UINT32 tblStart;
	UINT32 tblCount;
	UINT32 trnCount;
    UINT8 *pData = NULL;
    DE_IPC_CMD_T ipcCmd = PQL_IPC_SET_TABLE;

    do {
		tblStart = tblHead.start;
		tblCount = tblHead.count;
		if (!tblCount) BREAK_WRONG(tblCount);
		trnCount = tblCount + sizeof(tblHead);
        pData = OS_KMalloc(trnCount);
		CHECK_KNULL(pData);
		CHECK_KNULL(pPqlTable);
		memcpy(pData, &tblHead, sizeof(tblHead));
		memcpy(&pData[sizeof(tblHead)], &pPqlTable[tblStart], tblCount);
        ret = DE_KIPC_SetData(ipcCmd, pData, trnCount);
    } while (0);
    OS_Free(pData);
#endif

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get duty from external pwm input .
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetPwmDutyExternal(unsigned long arg)
{
    int ret = RET_OK;
    LX_DE_EXTERNAL_PWM_T stParams;

    do {
        ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
        ret = DE_HAL_GetPwmDutyExternal(&stParams);
		if (ret) break;
        ret = copy_to_user((void __user *)arg, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set win_id, port of cpu mvi .
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCpuMviPort(unsigned long arg)
{
    int ret = RET_OK;
    LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T *pstParams = (LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T*)arg;

    do {
        g_de_CpuMviPort = *pstParams;
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get win_id, port of cpu mvi .
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetCpuMviPort(unsigned long arg)
{
    int ret = RET_OK;
    LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T *pstParams = (LX_DE_CPU_MVI_PORT_MULTI_WIN_SRC_T*)arg;

    do {
        *pstParams = g_de_CpuMviPort;
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3d info through middleware (G-streamer) .
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_Set3DInfoThroughMiddleware(unsigned long arg)
{
	int ret = RET_OK;

	LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T *pstParams = (LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T*)arg;

	do {
		g_de_3d_info = *pstParams;
	} while (0);

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief get 3d info through middleware (G-streamer) .
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_Get3DInfoThroughMiddleware(unsigned long arg)
{
	int ret = RET_OK;

	LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T *pstParams = (LX_DE_3D_INFO_THROUGH_MIDDLEWARE_T*)arg;

	do {
		*pstParams = g_de_3d_info;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set low delay mode for frame delay
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetLowDelay(unsigned long arg)
{
    int ret = RET_OK;
    UINT32 stParams;
#ifndef USE_DE_SUSPEND
    UINT32 *pstParams = (UINT32*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_LOW_DELAY;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETLOWDELAY, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get low delay mode for frame delay
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetLowDelay(unsigned long arg)
{
    int ret = RET_OK;
    LX_DE_LOW_DELAY_T *pstParams = (LX_DE_LOW_DELAY_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_LOW_DELAY;

	do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_LOW_DELAY_T));
		ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_LOW_DELAY_T));
	} while (0);

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief get information for pixel aspect ratio
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetParInfo(unsigned long arg)
{
    int ret = RET_OK;

    LX_DE_PAR_WIN_RECT_T *pstParams = (LX_DE_PAR_WIN_RECT_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_PAR_INFO;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_PAR_WIN_RECT_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_PAR_WIN_RECT_T));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set inforamtion for Multi vision
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetMultiVision(unsigned long arg)
{
    int ret;
    LX_DE_RECT_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_RECT_T *pstParams = (LX_DE_RECT_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_MULTI_VISION;

    do {
#ifdef USE_DE_SUSPEND
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETMULTIVISION, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
#endif
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set information for Web OS
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetFrameToOsd(unsigned long arg)
{
    int ret = RET_OK;
    LX_DE_OSD_FRAME_CTRL_T stParams;
    LX_DE_OSD_FRAME_CTRL_T *pstParams = (LX_DE_OSD_FRAME_CTRL_T*)arg;
    DE_IPC_CMD_T ipcCmd = DE_IPC_GET_FRAME_FOR_WEBOS;

    do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SETFRAMETOOSD, &stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		ret = DE_HAL_SetFrameToOsd(&stParams);
		if (ret) BREAK_WRONG(ret);
        ret = DE_KIPC_SetData(ipcCmd, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get information for Web OS
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetFrameForOsd(unsigned long arg)
{
    int ret = RET_OK;
#if 0
    LX_DE_OSD_FRAME_CTRL_T stParams;

    do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);

		if(stParams.win_id  ==  0)
			ret = VIDEO_WEL_WaitVsync();
		else if(stParams.win_id  ==  1)
			ret = VIDEO_WER_WaitVsync();
		else
			ret = RET_INVALID_PARAMS;
    } while (0);
#endif
    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set 3D input/output control (onoff, format, lr order)
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 **/
int DE_IO_Set3DInOutCtrl(unsigned long arg)
{
	int ret = RET_OK;
	LX_3D_INOUT_CTRL_T stParams; // DE structure
	LX_DE_3D_INOUT_CTRL_T stParams1;   // FMT3D structure
	DE_IPC_CMD_T ipcCmd = FMT3D_IPC_SET_INOUT_CTRL;

	BOOLEAN b3dLaMode;
	static LX_3D_RUNMODE_T    run3dMode  = LX_3D_RUNMODE_OFF;
	static LX_3D_IMG_FMT_IN_T in3dFormat = LX_3D_IMG_IN_TOPNBOTTOM;

	do {
		ret = copy_from_user(&stParams1, (void __user *)arg, sizeof(stParams1));
		if (ret) break;

		stParams.run_mode       = stParams1.run_mode;
		stParams.in_img_fmt     = stParams1.in_img_fmt;
		stParams.in_lr_order    = stParams1.in_lr_order;
		stParams.out_img_fmt    = stParams1.out_img_fmt;
		stParams.out_lr_order   = stParams1.out_lr_order;

		ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
		do {
			if (0xff != stParams.run_mode)   run3dMode  = stParams.run_mode;
			if (0xff != stParams.in_img_fmt) in3dFormat = stParams.in_img_fmt;
			b3dLaMode = FALSE;
			if (!run3dMode) break;
			if (LX_3D_IMG_IN_COLUMNALTERNATIVE != in3dFormat) break;
			b3dLaMode = TRUE;
		} while (0);
		ret = DE_HAL_SetLAMode(&b3dLaMode);
	} while (0);

	return ret;
}

#ifdef USE_DE_SUSPEND
static int de_copy_from_user(unsigned short bSuspended, unsigned short indx, void * to, const void __user * from, unsigned int n)
{
    int ret = RET_OK;
    DE_SUSPEND_STORE_T *pStore = NULL;

    do {
        if (!bSuspended) {
            if (copy_from_user(to, from, n)) BREAK_WRONG(n);
            if (g_de_resumed) break;
        }
        if (!n) break;
        if ( !(indx < ARRAY_SIZE(de_suspend_store)) ) BREAK_WRONG(indx);
        pStore = &de_suspend_store[indx];
        CHECK_KNULL(pStore);
        CHECK_KNULL(pStore->pData);
        if (pStore->indx != indx) BREAK_WRONG(indx);
        if (!bSuspended) {
            if (!memcpy(pStore->pData, to, n)) BREAK_WRONG(n);
            pStore->size = n;
        } else {
            if (!pStore->size) BREAK_SETV(ret, 1);
            if (pStore->size != n) BREAK_WRONG(n);
            if (!memcpy(to, pStore->pData, n)) BREAK_WRONG(n);
        }
    } while (0);

    return ret;
}

int DE_IO_probe(void)
{
    int ret = RET_OK;
    DE_SUSPEND_STORE_T *pStore = NULL;
    int indx;

    for (indx=0;indx<ARRAY_SIZE(de_suspend_store);indx++) {
        pStore = &de_suspend_store[indx];
        CHECK_KNULL(pStore);
        pStore->pData = (char *)OS_Malloc(pStore->size);
        CHECK_KNULL(pStore->pData);
        pStore->size = 0;
    }

    return ret;
}

int DE_IO_remove(void)
{
    int ret = RET_OK;
    DE_SUSPEND_STORE_T *pStore = NULL;
    int indx;

    for (indx=0;indx < ARRAY_SIZE(de_suspend_store);indx++) {
        pStore = &de_suspend_store[indx];
        CHECK_KNULL(pStore);
        OS_Free(pStore->pData);
    }
    return ret;
}

int DE_IO_resume(void)
{
    int ret = RET_OK;
    DE_SUSPEND_STORE_T *pStore = NULL;
    int indx;

    for (indx=0;indx<ARRAY_SIZE(de_suspend_store);indx++) {
        pStore = &de_suspend_store[indx];
        CHECK_KNULL(pStore);
        if (!pStore->bOn) continue;
        ret = pStore->susF(0);
        if (ret > 0) continue;
        if (ret) break;
    }
    //g_de_resumed = TRUE;

    return ret;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetInSrc(unsigned long arg)
{
    int ret;
    LX_DE_SET_INPUT_T stParams;   // old structure
    LX_DE_INPUT_CFG_T stParams1; // new structure
    LX_DE_MULTI_WIN_SRC_T stParams2;    // old structure (for ATV mute)

    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_INPUT_SRC;

    do {
	ret = copy_from_user(&stParams1, (void __user *)arg, sizeof(stParams1));
       if (ret) break;

	stParams.win_id   = stParams1.win_id;
	//stParams.port_id  = stParams1.inputSrcPort;
	stParams.port_id  = stParams1.win_id;

	if(stParams1.inputSrc == LX_DE_IN_SRC_NONE)
		stParams.inputSrc = LX_DE_SRC_NONE;
	else if(stParams1.inputSrc == LX_DE_IN_SRC_MVI)
		stParams.inputSrc = LX_DE_SRC_MVI;
	else if(stParams1.inputSrc == LX_DE_IN_SRC_CPU)
		stParams.inputSrc = LX_DE_SRC_CPU;
	else if(stParams1.inputSrc <= LX_DE_IN_SRC_HDMI)
		stParams.inputSrc = LX_DE_SRC_CVI;
	else		ret = RET_ERROR;
	if (ret) BREAK_WRONG(ret);

        ret = DE_HAL_SetInSrc(&stParams1);
	if (ret) break;

	ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
       if (ret) break;

		ipcCmd = DE_IPC_SELECT_MULTI_WIN_SRC;
		stParams2.win_id  = stParams1.win_id;
		switch (stParams1.inputSrc)
		{
			case LX_DE_IN_SRC_MVI :
				stParams2.in_port = LX_DE_PORT_MVI;
				break;
			case LX_DE_IN_SRC_ATV :
			case LX_DE_IN_SRC_CVBS :
			case LX_DE_IN_SRC_SCART :
				stParams2.in_port = LX_DE_PORT_CVD;
				break;
			case LX_DE_IN_SRC_VGA :
			case LX_DE_IN_SRC_YPBPR :
				stParams2.in_port = LX_DE_PORT_ADC;
				break;
			case LX_DE_IN_SRC_HDMI :
				stParams2.in_port = LX_DE_PORT_HDMI;
				break;
			default :
				stParams2.in_port = LX_DE_PORT_MVI;
				break;
		}
		ret = DE_IPC_SETDATA(ipcCmd, stParams2, sizeof(stParams2));
    } while (0);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information of vdec mem sharing
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetVdecMemShare(unsigned long arg)
{
	int ret = RET_OK;
	BOOLEAN stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetVdecMemShare(&stParams);
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set interface configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetInterfaceConfig(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_IF_CONFIG_T stParams;
#ifndef USE_DE_SUSPEND
    LX_DE_IF_CONFIG_T *pstParams = (LX_DE_IF_CONFIG_T*)arg;
#endif
    DE_IPC_CMD_T ipcCmd = DE_IPC_SET_IF_CONFIG;

	do {
        ret = DE_COPY_FROM_USER(DE_SUSPEND_SET_IF_CONFIG, &stParams, (void __user *)arg, sizeof(stParams));
        if (ret) break;
        ret = DE_IPC_SETDATA(ipcCmd, stParams, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetInterfaceConfig(&stParams);
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set interface configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetSystemStatus(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_SYS_STATUS_T stParams;
	LX_DE_SYS_STATUS_T *pstParams = (LX_DE_SYS_STATUS_T *)arg;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_GetSystemStatus(&stParams);
		if (ret) break;
		ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set interface configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetSourceStatus(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_SRC_STATUS_T stParams;
	LX_DE_SRC_STATUS_T *pstParams = (LX_DE_SRC_STATUS_T *)arg;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_GetSourceStatus(&stParams);
		if (ret) break;
		ret = copy_to_user((void __user *)pstParams, &stParams, sizeof(stParams));
		if (ret) BREAK_WRONG(ret);
	} while (0);

	return ret;
}



/**
 * @callgraph
 * @callergraph
 *
 * @brief Set operation infomation
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetOperation(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_OPERATION_CTRL_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetOperation(&stParams);
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set window configuration
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetSubOperation(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_SUB_OPERATION_CTRL_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetSubOperation(&stParams);
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set capture control
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_SetCaptureControl(unsigned long arg)
{
	int ret = RET_OK;
	LX_DE_CAPTURE_CTRL_T stParams;

	do {
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(stParams));
		if (ret) break;
		ret = DE_HAL_SetCaptureControl(&stParams);
		if (ret) break;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get scaler info
 *
 * @param arg [IN] win idx
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IO_GetScalerInfo(unsigned long arg)
{
	int ret = RET_OK;
    LX_DE_SCALER_INFO_T *pstParams = (LX_DE_SCALER_INFO_T*)arg;
	DE_IPC_CMD_T ipcCmd = DE_IPC_GET_SCALER_INFO;

    do {
        ret = DE_IPC_SetData(ipcCmd, pstParams, sizeof(LX_DE_SCALER_INFO_T));
        ret = DE_IPC_GetData(pstParams, sizeof(LX_DE_SCALER_INFO_T));
    } while (0);

	return ret;
}

/**  @} */
