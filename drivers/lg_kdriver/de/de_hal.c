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
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2010.03.08
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
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

#include "de_model.h"
#include "de_kapi.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "de_int_def.h"
#include "de_hal_def.h"
#include "de_ipc_def.h"
#include "de_hal.h"
#ifdef USE_KDRV_CODES_FOR_L9
#include "l9/de_fw_l9.h"
#include "l9/de_reg_l9.h"
#include "l9/de_ipc_l9.h"
#include "l9/vp_reg_l9.h"
#endif
#ifdef USE_KDRV_CODES_FOR_H13
#include "h13/de_fw_h13.h"
#include "h13/de_reg_h13.h"
#include "h13/de_ipc_h13.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static DE_DPLL_CLK_T sDeDpllClk_1920[] = {
	DCLK_148_5	  ,
	DCLK_148_3516 ,
};

static DE_DPLL_CLK_T sDeDpllClk_1366[] = {
	DCLK_81 ,
	DCLK_81 ,
};

static DE_DPLL_CLK_T sDeDpllClk_1024[] = {
	DCLK_65 ,
	DCLK_65 ,
};

static DE_DPLL_CLK_T sDeDpllClk_3840[] = {
	DCLK_148_5	  ,
	DCLK_148_3516 ,
};

static DE_PANEL_SET_T sDePanelSet[] = {
	{ LX_PANEL_TYPE_1920 , sDeDpllClk_1920 },
	{ LX_PANEL_TYPE_1366 , sDeDpllClk_1366 },
	{ LX_PANEL_TYPE_1024 , sDeDpllClk_1024 },
	{ LX_PANEL_TYPE_1365 , sDeDpllClk_1366 },
	{ LX_PANEL_TYPE_3840 , sDeDpllClk_3840 }
};

static LX_DE_FR_RATE_T sDeFrRate = { FALSE, 60 };
static LX_DE_PANEL_TYPE_T sDePanelType = LX_PANEL_TYPE_1920;

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	int ret = RET_OK;

	sDePanelType = *pstParams;
#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_Init(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_Init(pstParams);
	} else
#endif
	{
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set Frame rate of Display
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetFrRate(LX_DE_FR_RATE_T *pstParams)
{
	int ret = RET_OK;
	DE_DPLL_CLK_T dclk;
	DE_DPLL_CLK_T *pDisplayPll = NULL;
	int pllIndex;
	int i;

	do {
		CHECK_KNULL(pstParams);
		sDeFrRate = *pstParams;
		pllIndex = 0;

		for (i=0;i<ARRAY_SIZE(sDePanelSet);i++) {
			if (sDePanelSet[i].panelType != sDePanelType) continue;
			pDisplayPll = sDePanelSet[i].pDpllClk;
			break;
		}
		CHECK_KNULL(pDisplayPll);
		dclk = pDisplayPll[pllIndex];

#ifdef USE_KDRV_CODES_FOR_H13
		if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
			ret = DE_REG_H13_SetFrRate(dclk);
		} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
		if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
			ret = DE_REG_L9_SetFrRate(dclk);
		} else
#endif
		{
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get Frame rate of Display
 *
 * @param pFrRate [OUT] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetFrRate(LX_DE_FR_RATE_T *pstParams)
{
	*pstParams = sDeFrRate;
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetBgColor(pBackColor);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetBgColor(pBackColor);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set blank color of selected window
 *
 * @param pWinBlank [IN] structure pointer to carry information about window Id, whether Turn On or Off and blank color
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetWinBlank(pWinBlank);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetWinBlank(pWinBlank);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief grab video pixels of certain block size and position.
 *
 * @param stParams
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GrabPixel(LX_DE_GRAB_PIXEL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GrabPixel(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GrabPixel(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviVideoFrameBuffer(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
        ret = DE_REG_L9_SetCviVideoFrameBuffer(pstParams);
	} else
#endif
	{
	}

    return ret;
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
int DE_HAL_SetInputSrc(LX_DE_SET_INPUT_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetInputSrc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetInputSrc(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviSrcType(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetCviSrcType(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get color space conversion matrix and offset for each external source information.
 *
 * @param
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetCviCsc(LX_DE_CVI_CSC_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetCviCsc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GetCviCsc(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix and offset for each external source information.
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviCsc(LX_DE_CVI_CSC_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviCsc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetCviCsc(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get color space conversion matrix for post processing block
 *
 * @param
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetPostCsc(LX_DE_POST_CSC_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetPostCsc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GetPostCsc(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send color space conversion matrix for post processing block
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetPostCsc(LX_DE_POST_CSC_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetPostCsc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPostCsc(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get MVI source colorimetry information.
 *
 * @param pstParams [OUT] value of MVI colorimetry
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetMviColorimetry(LX_DE_MVI_COLORIMETRY_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetMviColorimetry(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GetMviColorimetry(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set LVDS spread spectrum for 60Hz mode (PDP).
 *
 * @param pstParams [OUT] value of spread spectrum period, duty, enable.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetSpread(LX_DE_SET_SPREAD_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetSpread(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetSpread(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetDeinterlace(BOOLEAN bEnable)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetDeinterlace(bEnable);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetDeinterlace(bEnable);
	} else
#endif
	{
	}
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
int DE_HAL_SetUart4MCU(BOOLEAN bUart4MCU)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_Uart0_Switch(bUart4MCU);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_Uart0_Switch(bUart4MCU);
	} else
#endif
	{
	}
	return ret;
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
int DE_HAL_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetVcs(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetVcs(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_Init(LX_DE_OIF_INFO_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_Init(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_Init(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get Informatation of OIF module.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_OIF_GetInfo(LX_DE_OIF_INFO_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_GetInfo(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_GetInfo(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetLvdsOutput(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetLvdsOutput(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetLvdsOutput(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetLvdsPower(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetLvdsPower(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetLvdsPower(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetDarkScreen(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetDarkScreen(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetDarkScreen(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetVesaJeida(LX_DE_OIF_STD_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetVesaJeida(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetVesaJeida(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetPanelIf(LX_DE_OIF_PANEL_IF_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetPanelIf(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetPanelIf(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetPixel(LX_DE_OIF_PIXEL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetPixel(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetPixel(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetBitDepth(LX_DE_OIF_BIT_DEPTH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetBitDepth(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetBitDepth(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SelectLedPath(LX_DE_OIF_LED_IN_PATH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SelectLedPath(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SelectLedPath(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SelectOutPath(LX_DE_OIF_OUTPUT_PATH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SelectOutPath(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SelectOutPath(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SelectLvdsPath(LX_DE_OIF_LVDS_PATH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SelectLvdsPath(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SelectLvdsPath(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SelectOutCh(LX_DE_OIF_OUTPUT_CH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SelectOutCh(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SelectOutCh(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SelectPwmPath(LX_DE_OIF_PWM_PATH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SelectPwmPath(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SelectPwmPath(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SelectLrPath(LX_DE_OIF_LR_PATH_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SelectLrPath(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SelectLrPath(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetLvdsOutCtrl(LX_DE_OIF_LVDS_OUT_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetLvdsOutCtrl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetLvdsOutCtrl(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_OIF_SetLvdsPortSwap(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OIF_SetLvdsPortSwap(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OIF_SetLvdsPortSwap(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Table
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetTable(LX_DE_SET_TABLE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetTable(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetTable(pstParams);
	} else
#endif
	{
	}
	return ret;
}


#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
int DE_HAL_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_FW_Download(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_FW_Download(pstParams);
	} else
#endif
	{
	}
	return ret;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief send captured video fir coef for double/quad sampling case.
 *
 * @param cvi_channel, fir coef, and enable [IN] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviFir(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetCviFir(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief send set captured video test pattern generator to black.
 *
 * @param cvi_channel, pattern enable, freeze enable, pattern color space [IN]] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviTpg(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetCviTpg(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set captured video color sampling mode(sub sampling or 3 tap filtering).
 *
 * @param cvi_channel, color sampling mode(sub_sample, 3-tap-filter) [IN] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviCsampleMode(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetCviCsampleMode(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief reshape sync of captured video for PC input.
 *
 * @param cvi_channel, horizonatal/vertical sync/fp delay, and enable [IN] value of capture video
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetCviSyncReshape(LX_DE_CVI_SYNC_RESHAPE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetCviSyncReshape(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetCviSyncReshape(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetPeTestPatternGen(LX_DE_PE_TPG_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetPeTestPatternGen(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPeTestPatternGen(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set PE0 black boundary detection control.
 *
 * @param thresholds, and enable [IN] value of BBD ctrl.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetPeBbdCtrl(LX_DE_PE_BBD_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetPeBbdCtrl(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPeBbdCtrl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get PE0 black boundary detection status.
 *
 * @param x0, y0, x1, y1 [OUT] value of BBD coordinate.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetPeBbdStatus(LX_DE_PE_COORDINATE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetPeBbdStatus(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GetPeBbdStatus(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set edge crop.
 *
 * @param pstParams [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetEdgeCrop(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetEdgeCrop(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetEdgeCrop(pstParams);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief reset Register of DE HW Block
 *
 * @param bReset [IN] BOOLEAN
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_ResetDE(bReset);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_ResetDE(bReset);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_InitPHY2VIRT(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_InitPHY2VIRT();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_InitPHY2VIRT();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_FreePHY2VIRT(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_FreePHY2VIRT();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_FreePHY2VIRT();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_GPIO_Init(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GPIO_Init();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GPIO_Init();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_HDMI_Init(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_HDMI_Init();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_HDMI_Init();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_LVDS_Init(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_LVDS_Init();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_LVDS_Init();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_MISC_Init(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_MISC_Init();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_MISC_Init();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_OSD_Init(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_OSD_Init();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_OSD_Init();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_FW_DownloadFromBin(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_FW_H13_DownloadFromBin();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_FW_L9_DownloadFromBin();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_FW_DownloadFromHead(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_FW_H13_DownloadFromHead();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_FW_L9_DownloadFromHead();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_IPCisAlive(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_IPCisAlive();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_IPCisAlive();
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_WriteReg(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_WD(addr, value);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_WD(addr, value);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_ReadReg(UINT32 addr, UINT32 *value)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		*value = DE_REG_H13_RD(addr);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		*value = DE_REG_L9_RD(addr);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetPwmControl(LX_DE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPwmControl(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetPwmDutyCycle(LX_DE_PWM_PARAM_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPwmDutyCycle(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetPwmFrequency(LX_DE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPwmFrequency(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetPwmPulseWidth(LX_DE_PWM_PULSE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetPwmPulseWidth(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_Set3DFullMode(LX_DE_3D_FULL_MODE_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_Set3DFullMode(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_Set3DFullMode(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetUdMode(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetUdMode(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetFrameToOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetFrameToOsd(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetFrameToOsd(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_GetFrameForOsd(LX_DE_OSD_FRAME_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetFrameForOsd(pstParams);
	} else
#endif
#if 0 //def USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetFrameToOsd(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetLAMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetLAMode(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetLAMode(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SelectMultiWinSrc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SelectMultiWinSrc(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetSCARTRGBBypassMode(int *pEnable)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {

	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) ) {
		ret =  DE_REG_L9_Set_SCART_RGB_Bypass_Mode(*pEnable);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_GetCviInfo(LX_DE_CVI_INFO_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetCviInfo(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GetCviInfo(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_GetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetDebug(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_GetDebug(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_SetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetDebug(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetDebug(pstParams);
	} else
#endif
	{
	}
	return ret;
}

int DE_HAL_GetPwmDutyExternal(LX_DE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,B0) ) {
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) ) {
		ret = DE_REG_L9_GetPwmDutyCycle(pstParams);
	} else
#endif
	{
	}
	return ret;
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
int DE_HAL_SetInSrc(LX_DE_INPUT_CFG_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetInSrc(pstParams);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetInSrc(pstParams);
	} else
#endif
	{
	}

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
int DE_HAL_SetVdecMemShare(BOOLEAN *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {

		return ret;
	} else
#endif
	{
	}
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
int DE_HAL_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetInterfaceConfig(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetSystemStatus(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_GetSourceStatus(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetOperation(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_REG_H13_SetSubOperation(pstParams);
	} else
#endif
	{
	}
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
int DE_HAL_SetCaptureControl(LX_DE_CAPTURE_CTRL_T *pstParams)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {

	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get interrupt status for IPC
 *
 * @param ipcType [IN] interrupt type for IPC which is happend from either MCU or CPU
 * @param pStatus [OUT] interrupt status for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_GetIPCIntrStatus(VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_IPC_H13_GetStatusReg(ipcType, pStatus);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_IPC_L9_GetStatusReg(ipcType, pStatus);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearIPCStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		ret = DE_IPC_H13_WakeUpReg(VIDEO_IPC_CPU, FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		ret = DE_IPC_L9_WakeUpReg(VIDEO_IPC_CPU, FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of JPG for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearJPGStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		ret = DE_IPC_H13_WakeUpReg(VIDEO_JPG_CPU, FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		ret = DE_IPC_L9_WakeUpReg(VIDEO_JPG_CPU, FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of USB for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearUSBStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		ret = DE_IPC_H13_WakeUpReg(VIDEO_USB_CPU, FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		ret = DE_IPC_L9_WakeUpReg(VIDEO_USB_CPU, FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of WEL for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearWELStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		ret = DE_IPC_H13_WakeUpReg(VIDEO_WEL_CPU, FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		ret = DE_IPC_L9_WakeUpReg(VIDEO_WEL_CPU, FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of WER for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearWERStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		ret = DE_IPC_H13_WakeUpReg(VIDEO_WER_CPU, FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		ret = DE_IPC_L9_WakeUpReg(VIDEO_WER_CPU, FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for watch dog
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearWDGStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_WDG_H13_WakeUpReg(FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_WDG_L9_WakeUpReg(FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for DMA
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_ClearDMAStatus(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_IPC_H13_WakeUpReg(VIDEO_DMA_CPU, FALSE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_IPC_L9_WakeUpReg(VIDEO_DMA_CPU, FALSE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for DMA
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
BOOLEAN DE_HAL_CheckIrq4Vsync(void)
{
	BOOLEAN vsyncIrq = 0;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		vsyncIrq = DE_REG_H13_CheckIrq4Vsync();
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		vsyncIrq = DE_REG_L9_CheckIrq4Vsync();
	} else
#endif
	{
	}
	return vsyncIrq;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialze IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_IPCInit(UINT32 *pBuffToMCU, UINT32 *pBuffFrMCU)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_IPC_H13_Init(pBuffToMCU, pBuffFrMCU);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev() >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_IPC_L9_Init(pBuffToMCU, pBuffFrMCU);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief uninitialze IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
BOOLEAN DE_HAL_IPCFree(UINT32 *pBuffToMCU, UINT32 *pBuffFrMCU)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev() >= LX_CHIP_REV(H13,A0) ) {
		ret = DE_IPC_H13_Free(pBuffToMCU, pBuffFrMCU);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev() >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_IPC_L9_Free(pBuffToMCU, pBuffFrMCU);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make IPC interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_WakeUpIPC(void)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
	{
		ret = DE_IPC_H13_WakeUpReg(VIDEO_IPC_MCU, TRUE);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		ret = DE_IPC_L9_WakeUpReg(VIDEO_IPC_MCU, TRUE);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make IPC interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SwitchUART0(int whichUart)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_H13
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) ) {
		DE_REG_H13_Uart0_Switch(whichUart);
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		DE_REG_L9_Uart0_Switch(whichUart);
	} else
#endif
	{
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set ttx data
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_HAL_SetTtx(VIDEO_TTX_PACK_T *pTtxPack)
{
	int ret = RET_OK;

#ifdef USE_KDRV_CODES_FOR_L9
	if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) ) {
		ret = DE_REG_L9_SetTtx(pTtxPack);
	} else
#endif
	{
	}
	return ret;
}
/**  @} */
