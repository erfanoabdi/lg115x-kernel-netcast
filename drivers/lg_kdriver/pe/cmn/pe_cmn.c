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


/** @file pe_cmn.c
 *
 *  driver for picture enhance common functions. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_spd.h"
#include "pe_cmn.h"
#include "pe_etc_hw.h"
#include "pe_cmn_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMN_ERROR	printk

#define PE_CMN_DBG_PRINT(fmt,args...)	\
	if(_g_cmn_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMN_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_CMN_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 g_pe_kdrv_ver_mask = 0x0;	//default 0x0

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_CMN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_CMN_GetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_CMN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_CMN_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_CMN_SetContrast(LX_PE_CMN_CONTRAST_T *pstParams);
static int PE_CMN_GetContrast(LX_PE_CMN_CONTRAST_T *pstParams);
static int PE_CMN_SetBrightness(LX_PE_CMN_BRIGHTNESS_T *pstParams);
static int PE_CMN_GetBrightness(LX_PE_CMN_BRIGHTNESS_T *pstParams);
static int PE_CMN_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams);
static int PE_CMN_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams);
static int PE_CMN_SetHue(LX_PE_CMN_HUE_T *pstParams);
static int PE_CMN_GetHue(LX_PE_CMN_HUE_T *pstParams);
static int PE_CMN_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
static int PE_CMN_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
static int PE_CMN_SetSubContrast(LX_PE_CMN_SUB_CONTRAST_T *pstParams);
static int PE_CMN_GetSubContrast(LX_PE_CMN_SUB_CONTRAST_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmn_trace=0x0;	//default should be off.
static PE_CMN_SETTINGS_T _g_pe_cmn_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_InitPicEnhanceModule(void)
{
	int ret = RET_OK;
	do{
		/************** cfg kdrv ver **************/
		g_pe_kdrv_ver_mask = \
			((lx_chip_rev()>=LX_CHIP_REV(L9,A0) && lx_chip_rev()<LX_CHIP_REV(L9,B0))? \
			PE_KDRV_VER_BIT_L9AX:0x0)|\
			((lx_chip_rev()>=LX_CHIP_REV(L9,B0) && lx_chip_rev()<LX_CHIP_REV(L9,C0))? \
			PE_KDRV_VER_BIT_L9BX:0x0)|\
			((lx_chip_rev()>=LX_CHIP_REV(H13,A0) && lx_chip_rev()<LX_CHIP_REV(H13,B0))? \
			PE_KDRV_VER_BIT_H13AX:0x0)|\
			((lx_chip_rev()>=LX_CHIP_REV(H13,B0) && lx_chip_rev()<LX_CHIP_REV(H13,C0))? \
			PE_KDRV_VER_BIT_H13BX:0x0);
		/******************************************/
		ret = PE_REG_InitPhyToVirt();
		PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_REG_InitPhyToVirt() error.\n",__F__,__L__);
	}while(0);
	return ret;
}
/**
 * cleanup picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_CleanupPicEnhanceModule(void)
{
	int ret = RET_OK;
	do{
		ret = PE_REG_FreePhyToVirt();
		PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_REG_FreePhyToVirt() error.\n",__F__,__L__);			
	}while(0);
	return ret;
}
/**
 * open picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_OpenPicEnhanceModule(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_TSK_H13_CreatePicTask();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_TSK_H13_CreatePicTask() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_TSK_L9_CreatePicTask();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_TSK_L9_CreatePicTask() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * close picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_ClosePicEnhanceModule(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_TSK_H13_StopPicTask();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_TSK_H13_StopPicTask() error.\n",__F__,__L__);			
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_TSK_L9_StopPicTask();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_HW_L9_StopPicTask() error.\n",__F__,__L__);			
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * init common module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_FWI_H13_FW_CTRL fw_ctrl;
			PE_CMN_DBG_PRINT("init global values.\n");
			memset0(_g_pe_cmn_info);
			ret = PE_FWI_H13_Init();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_Init() error.\n",__F__,__L__);
			if(PE_KDRV_VER_H13BX)
				fw_ctrl.enable = 0x1;	//0:by register, 1:by fw, not use _g_pe_cmn_info.use_pe_fw from h13
			else
				fw_ctrl.enable = 0x0;	//0:by register, 1:by fw, not use _g_pe_cmn_info.use_pe_fw from h13
			ret = PE_FWI_H13_SetFwCtrl(&fw_ctrl);
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwCtrl() error.\n",__F__,__L__);
			ret = PE_CMN_HW_H13_Init();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			PE_CMN_DBG_PRINT("init global values.\n");
			memset0(_g_pe_cmn_info);
			_g_pe_cmn_info.use_pe_fw = 0x1;	// 0:by register, 1:by fw
			if(_g_pe_cmn_info.use_pe_fw)
			{
				ret = PE_FWI_L9_Init();
				PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_Init() error.\n",__F__,__L__);
			}
			ret = PE_CMN_HW_L9_Init();
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of cmn setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMN_SET_FSDP(_struct,_func,_sdp)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CMN_DBG_PRINT("S %s\n",#_struct);\
			PE_CMN_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			ret = PE_COPY_FROM_USER(_sdp, (void *)&param, (void *)p_rcv, datasize);\
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] %s error.\n",__F__,__L__,#_sdp);\
			ret = _func(&param);\
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_CMN_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

#define PE_CMN_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CMN_DBG_PRINT("S %s\n",#_struct);\
			PE_CMN_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_CMN_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CMN_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CMN_SET_FSDP(LX_PE_CMN_CONTRAST_T,		PE_CMN_SetContrast,			PE_SUSPEND_CMN_SETCONTRAST);
		PE_CMN_SET_FSDP(LX_PE_CMN_BRIGHTNESS_T,		PE_CMN_SetBrightness,		PE_SUSPEND_CMN_SETBRIGHTNESS);
		PE_CMN_SET_FSDP(LX_PE_CMN_SATURATION_T,		PE_CMN_SetSaturation,		PE_SUSPEND_CMN_SETSATURATION);
		PE_CMN_SET_FSDP(LX_PE_CMN_HUE_T,			PE_CMN_SetHue,				PE_SUSPEND_CMN_SETHUE);
		PE_CMN_SET_FSDP(LX_PE_DEFAULT_SETTINGS_T,	PE_CMN_SetDefaultSettings,	PE_SUSPEND_CMN_SETDEFAULT);
		PE_CMN_SET_FUNC(LX_PE_CMN_LEVEL_CTRL_T,		PE_CMN_SetLevelCtrl);
		PE_CMN_SET_FUNC(LX_PE_CMN_SUB_CONTRAST_T,	PE_CMN_SetSubContrast);
		PE_CMN_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CMN_SetDebugSettings);
		default:
		{
			PE_CMN_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of cmn getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMN_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CMN_DBG_PRINT("S %s\n",#_struct);\
			PE_CMN_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_CMN_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CMN_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CMN_GET_FUNC(LX_PE_CMN_CONTRAST_T,		PE_CMN_GetContrast);
		PE_CMN_GET_FUNC(LX_PE_CMN_BRIGHTNESS_T,		PE_CMN_GetBrightness);
		PE_CMN_GET_FUNC(LX_PE_CMN_SATURATION_T,		PE_CMN_GetSaturation);
		PE_CMN_GET_FUNC(LX_PE_CMN_HUE_T,			PE_CMN_GetHue);
		PE_CMN_GET_FUNC(LX_PE_CMN_LEVEL_CTRL_T,		PE_CMN_GetLevelCtrl);
		PE_CMN_GET_FUNC(LX_PE_CMN_SUB_CONTRAST_T,	PE_CMN_GetSubContrast);
		PE_CMN_GET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CMN_GetDefaultSettings);
		PE_CMN_GET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CMN_GetDebugSettings);
		default:
		{
			PE_CMN_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}
/**
 * set cmn fmt default settings
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo=&_g_pe_cmn_info;	/* to avoid warning(unused variable) */
		PE_CMN_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->use_pe_fw)
			{
				/* inform src info to fw */
				ret = PE_FWI_L9_SetSrcInfo(pstParams);
				PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetSrcInfo() error.\n",__F__,__L__);
			}
		}
		#endif
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			memcpy(&(pInfo->dflt[LX_PE_WIN_0]),pstParams,sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			memcpy(&(pInfo->dflt[LX_PE_WIN_1]),pstParams,sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
	}while(0);
	return ret;
}
/**
 * get cmn fmt default settings
 *
 * @param   *pstParams [in/out] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo=&_g_pe_cmn_info;	/* to avoid warning(unused variable) */
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_CHECK_WIN0(win_id))
		{
			memcpy(pstParams,&(pInfo->dflt[LX_PE_WIN_0]),sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
		if(PE_CHECK_WIN1(win_id))
		{
			memcpy(pstParams,&(pInfo->dflt[LX_PE_WIN_1]),sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
		PE_CMN_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
	}while(0);
	return ret;
}
/**
 * set cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo=&_g_pe_cmn_info;	/* to avoid warning(unused variable) */
		PE_CMN_DBG_PRINT("set[%d] type:0x%x, print:0x%x, bypass:0x%x, fwc_use,win,dbg:%d,%d,%d\n",\
			pstParams->win_id,pstParams->type,pstParams->print_lvl,pstParams->bypass,\
			pstParams->fwc.use_fw,pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmn_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMN)))? 0x1:0x0;
			pInfo->dbg_print_lvl = pstParams->print_lvl;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_CMN_HW_H13_SetDbgPrint(_g_cmn_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_CMN_HW_L9_SetDbgPrint(_g_cmn_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMN)))
				{
					PE_CMN_DBG_PRINT("cont,bri,sat disable, hue bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_H13B0_QWr01(p0l_lvcrtl_ctrl_00,	enable,		0x0);
						PE_P1L_H13B0_QWr01(pe1_vspyc_ctrl_00, enable,		0x0);
						PE_P1L_H13B0_QWr01(pe1_cen_ctrl_03, ihsv_hoffset,	0x80);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_H13B0_QWr01(p0r_lvcrtl_ctrl_00, enable,		0x0);
					}
					
				}
				else
				{
					PE_CMN_DBG_PRINT("cont,bri,sat enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_H13B0_QWr01(p0l_lvcrtl_ctrl_00, enable,		0x1);
						PE_P1L_H13B0_QWr01(pe1_vspyc_ctrl_00, enable,		0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_H13B0_QWr01(p0r_lvcrtl_ctrl_00, enable,		0x1);
					}
				}

				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					pInfo->dbg_bypass[LX_PE_WIN_0] = pstParams->bypass;
				}
			}
			else if(PE_KDRV_VER_H13AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMN)))
				{
					PE_CMN_DBG_PRINT("cont,bri,sat disable, hue bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_DPP_H13_QWr01(debd_pp_l_level_ctrl_00, enable,	0x0);
						PE_DPP_H13_QWr01(debd_pp_l_vspyc_ctrl_00, enable,	0x0);
						PE_P1L_H13_QWr01(pe1_cen_ctrl_03, ihsv_hoffset,		0x80);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_DPP_H13_QWr01(debd_pp_r_level_ctrl_00, enable,	0x0);
						PE_DPP_H13_QWr01(debd_pp_r_vspyc_ctrl_00, enable,	0x0);
					}
					
				}
				else
				{
					PE_CMN_DBG_PRINT("cont,bri,sat enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_DPP_H13_QWr01(debd_pp_l_level_ctrl_00, enable,	0x1);
						PE_DPP_H13_QWr01(debd_pp_l_vspyc_ctrl_00, enable,	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_DPP_H13_QWr01(debd_pp_r_level_ctrl_00, enable,	0x1);
						PE_DPP_H13_QWr01(debd_pp_r_vspyc_ctrl_00, enable,	0x1);
					}
				}

				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					pInfo->dbg_bypass[LX_PE_WIN_0] = pstParams->bypass;
				}
				
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMN)))
				{
					PE_CMN_DBG_PRINT("cont,bri,sat disable, hue bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_level_ctrl_00,	enable,			0x0);
						PE_P1L_L9B_QWr01(pe1_l_vspyc_ctrl_00,	enable,			0x0);
						PE_P1L_L9B_QWr01(pe1_l_vsprgb_ctrl_00,	enable,			0x0);
						PE_P1L_L9B_QWr01(pe1_l_cen_ctrl_03,		ihsv_hoffset,	0x80);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_level_ctrl_00,	enable,			0x0);
						PE_P1R_L9B_QWr01(pe1_r_vspyc_ctrl_00,	enable,			0x0);
						PE_P1R_L9B_QWr01(pe1_r_vsprgb_ctrl_00,	enable,			0x0);
						PE_P1R_L9B_QWr01(pe1_r_cen_ctrl_03,		ihsv_hoffset,	0x80);
					}
				}
				else
				{
					PE_CMN_DBG_PRINT("cont,bri,sat enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_level_ctrl_00,	enable,			0x1);
						PE_P1L_L9B_QWr01(pe1_l_vspyc_ctrl_00,	enable,			0x1);
						PE_P1L_L9B_QWr01(pe1_l_vsprgb_ctrl_00,	enable,			0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_level_ctrl_00,	enable,			0x1);
						PE_P1R_L9B_QWr01(pe1_r_vspyc_ctrl_00,	enable,			0x1);
						PE_P1R_L9B_QWr01(pe1_r_vsprgb_ctrl_00,	enable,			0x1);
					}
				}
			}
			else
			#endif
			{
				PE_CMN_DBG_PRINT("do nothing.\n");	ret = RET_OK;
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				pInfo->dbg_bypass[LX_PE_WIN_0] = pstParams->bypass;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				pInfo->dbg_bypass[LX_PE_WIN_1] = pstParams->bypass;
			}
		}
		/* set fwc */
		if(pstParams->type&LX_PE_DBG_FW)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)
			{
				PE_FWI_H13_FW_CTRL fw_ctrl;
				PE_FWI_H13_SetDbgPrint(pstParams->fwc.dbg_en);
				fw_ctrl.enable = (pstParams->fwc.ctrl_en)? 0x1:0x0;
				ret = PE_FWI_H13_SetFwCtrl(&fw_ctrl);
				PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwCtrl() error.\n",__F__,__L__);
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				pInfo->use_pe_fw = (pstParams->fwc.use_fw)? 1:0;
				PE_FWI_L9_SetDbgPrint(pstParams->fwc.dbg_en);
				ret = PE_FWI_L9_SetCtrlWin(pstParams->fwc.ctrl_en);
				PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetCtrlWin() error.\n",__F__,__L__);
			}
			else
			#endif
			{
				PE_CMN_DBG_PRINT("do nothing.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}

/**
 * get cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo=&_g_pe_cmn_info;	/* to avoid warning(unused variable) */
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_CHECK_WIN0(win_id))
		{
			pstParams->bypass = pInfo->dbg_bypass[LX_PE_WIN_0];
		}
		if(PE_CHECK_WIN1(win_id))
		{
			pstParams->bypass = pInfo->dbg_bypass[LX_PE_WIN_1];
		}
		pstParams->print_lvl = pInfo->dbg_print_lvl;
		pstParams->fwc.use_fw = pInfo->use_pe_fw;
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_FWI_H13_SETTINGS_T param;
			pstParams->fwc.dbg_en = PE_FWI_H13_GetDbgPrint();
			ret = PE_FWI_H13_GetCurFwiSettings(&param);
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_GetCurFwiSettings() error.\n",__F__,__L__);
			pstParams->fwc.ctrl_en = param.fw_ctrl.enable;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_FWI_L9_SETTINGS_T param;
			pstParams->fwc.dbg_en = PE_FWI_L9_GetDbgPrint();
			ret = PE_FWI_L9_GetCurFwiSettings(&param);
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_GetCurFwiSettings() error.\n",__F__,__L__);
			pstParams->fwc.ctrl_en = param.fw_ctrl.win_id;
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("not use fwc.\n");
			pstParams->fwc.dbg_en = 0;
			pstParams->fwc.ctrl_en = 0;
		}
		PE_CMN_DBG_PRINT("get[%d] type:0x%x, print:0x%x, bypass:0x%x, fwc_use,win,dbg:%d,%d,%d\n",\
			pstParams->win_id,pstParams->type,pstParams->print_lvl,pstParams->bypass,\
			pstParams->fwc.use_fw,pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
	}while(0);
	return ret;
}
/**
 * set contrast
 *
 * @param   *pstParams [in] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetContrast(LX_PE_CMN_CONTRAST_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		PE_CMN_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->contrast);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_vspyc_ctrl_00, contrast,		GET_BITS(pstParams->contrast,0,10));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_DPP_H13_QWr01(debd_pp_l_vspyc_ctrl_00, contrast,	GET_BITS(pstParams->contrast,0,10));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_DPP_H13_QWr01(debd_pp_r_vspyc_ctrl_00, contrast,	GET_BITS(pstParams->contrast,0,10));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr01(pe1_l_vspyc_ctrl_00, contrast,		GET_BITS(pstParams->contrast,0,10));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_vspyc_ctrl_00, contrast,		GET_BITS(pstParams->contrast,0,10));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			ret = PE_FWI_SETDATA(PQL_IPC_SET_CONTRAST, pstParams, sizeof(LX_PE_CMN_CONTRAST_T));
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PQL_IPC_SET_CONTRAST error.\n",__F__,__L__);
			PE_CMN_DBG_PRINT("win[%d] set f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(&(pInfo->con[LX_PE_WIN_0]),pstParams,sizeof(LX_PE_CMN_CONTRAST_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(&(pInfo->con[LX_PE_WIN_1]),pstParams,sizeof(LX_PE_CMN_CONTRAST_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * get contrast
 *
 * @param   *pstParams [in/out] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetContrast(LX_PE_CMN_CONTRAST_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_vspyc_ctrl_00, contrast,		pstParams->contrast);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_DPP_H13_QRd01(debd_pp_l_vspyc_ctrl_00, contrast,	pstParams->contrast);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_DPP_H13_QRd01(debd_pp_r_vspyc_ctrl_00, contrast,	pstParams->contrast);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_vspyc_ctrl_00, contrast,		pstParams->contrast);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_vspyc_ctrl_00, contrast,		pstParams->contrast);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_CMN_DBG_PRINT("win[%d] set f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				pInfo->con[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->con[LX_PE_WIN_0]),sizeof(LX_PE_CMN_CONTRAST_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pInfo->con[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->con[LX_PE_WIN_1]),sizeof(LX_PE_CMN_CONTRAST_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->contrast);
	}while(0);
	return ret;
}
/**
 * set brightness
 *
 * @param   *pstParams [in] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetBrightness(LX_PE_CMN_BRIGHTNESS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		PE_CMN_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->brightness);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_vspyc_ctrl_01, brightness,		GET_BITS(pstParams->brightness,0,10));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_DPP_H13_QWr01(debd_pp_l_vspyc_ctrl_01, brightness,	GET_BITS(pstParams->brightness,0,10));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_DPP_H13_QWr01(debd_pp_r_vspyc_ctrl_01, brightness,	GET_BITS(pstParams->brightness,0,10));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{ 
				PE_P1L_L9B_QWr01(pe1_l_vspyc_ctrl_01, brightness,		GET_BITS(pstParams->brightness,0,10));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_vspyc_ctrl_01, brightness,		GET_BITS(pstParams->brightness,0,10));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			ret = PE_FWI_SETDATA(PQL_IPC_SET_BRIGHTNESS, pstParams, sizeof(LX_PE_CMN_BRIGHTNESS_T));
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PQL_IPC_SET_BRIGHTNESS error.\n",__F__,__L__);
			PE_CMN_DBG_PRINT("win[%d] set f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(&(pInfo->bri[LX_PE_WIN_0]),pstParams,sizeof(LX_PE_CMN_BRIGHTNESS_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(&(pInfo->bri[LX_PE_WIN_1]),pstParams,sizeof(LX_PE_CMN_BRIGHTNESS_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get brightness
 *
 * @param   *pstParams [in/out] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetBrightness(LX_PE_CMN_BRIGHTNESS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_vspyc_ctrl_01, brightness,		pstParams->brightness);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_DPP_H13_QRd01(debd_pp_l_vspyc_ctrl_01, brightness,	pstParams->brightness);	
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_DPP_H13_QRd01(debd_pp_r_vspyc_ctrl_01, brightness,	pstParams->brightness);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_vspyc_ctrl_01, brightness,		pstParams->brightness);			
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_vspyc_ctrl_01, brightness,		pstParams->brightness);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_CMN_DBG_PRINT("win[%d] get f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				pInfo->bri[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->bri[LX_PE_WIN_0]),sizeof(LX_PE_CMN_BRIGHTNESS_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pInfo->bri[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->bri[LX_PE_WIN_1]),sizeof(LX_PE_CMN_BRIGHTNESS_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}

		PE_CMN_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->brightness);
	}while(0);
	return ret;
}
/**
 * set saturation
 *
 * @param   *pstParams [in] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		PE_CMN_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_vspyc_ctrl_01, saturation,		GET_BITS(pstParams->saturation,0,8));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_DPP_H13_QWr01(debd_pp_l_vspyc_ctrl_01, saturation,	GET_BITS(pstParams->saturation,0,8));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_DPP_H13_QWr01(debd_pp_r_vspyc_ctrl_01, saturation,	GET_BITS(pstParams->saturation,0,8));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr01(pe1_l_vspyc_ctrl_01, saturation,		GET_BITS(pstParams->saturation,0,8));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_vspyc_ctrl_01, saturation,		GET_BITS(pstParams->saturation,0,8));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			ret = PE_FWI_SETDATA(PQL_IPC_SET_SATURATION, pstParams, sizeof(LX_PE_CMN_SATURATION_T));
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PQL_IPC_SET_SATURATION error.\n",__F__,__L__);
			PE_CMN_DBG_PRINT("win[%d] set f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(&(pInfo->sat[LX_PE_WIN_0]),pstParams,sizeof(LX_PE_CMN_SATURATION_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(&(pInfo->sat[LX_PE_WIN_1]),pstParams,sizeof(LX_PE_CMN_SATURATION_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get saturation
 *
 * @param   *pstParams [in/out] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_vspyc_ctrl_01, saturation,		pstParams->saturation);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_DPP_H13_QRd01(debd_pp_l_vspyc_ctrl_01, saturation,	pstParams->saturation);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_DPP_H13_QRd01(debd_pp_r_vspyc_ctrl_01, saturation,	pstParams->saturation);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_vspyc_ctrl_01, saturation,		pstParams->saturation);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_vspyc_ctrl_01, saturation,		pstParams->saturation);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_CMN_DBG_PRINT("win[%d] get f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				pInfo->sat[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->sat[LX_PE_WIN_0]),sizeof(LX_PE_CMN_SATURATION_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pInfo->sat[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->sat[LX_PE_WIN_1]),sizeof(LX_PE_CMN_SATURATION_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
	}while(0);
	return ret;
}
/**
 * set hue
 *
 * @param   *pstParams [in] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		PE_CMN_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_cen_ctrl_03, ihsv_hoffset,	GET_BITS(pstParams->hue,0,8));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_QWr01(pe1_cen_ctrl_03, ihsv_hoffset,		GET_BITS(pstParams->hue,0,8));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr01(pe1_l_cen_ctrl_03, ihsv_hoffset,	GET_BITS(pstParams->hue,0,8));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_cen_ctrl_03, ihsv_hoffset,	GET_BITS(pstParams->hue,0,8));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			ret = PE_FWI_SETDATA(PQL_IPC_SET_HUE, pstParams, sizeof(LX_PE_CMN_HUE_T));
			PE_CMN_CHECK_CODE(ret,break,"[%s,%d] PQL_IPC_SET_HUE error.\n",__F__,__L__);
			PE_CMN_DBG_PRINT("win[%d] set f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				memcpy(&(pInfo->hue[LX_PE_WIN_0]),pstParams,sizeof(LX_PE_CMN_HUE_T));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				memcpy(&(pInfo->hue[LX_PE_WIN_1]),pstParams,sizeof(LX_PE_CMN_HUE_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get hue
 *
 * @param   *pstParams [in/out] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo = &_g_pe_cmn_info;
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_cen_ctrl_03, ihsv_hoffset,	pstParams->hue);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QRd01(pe1_cen_ctrl_03, ihsv_hoffset,		pstParams->hue);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_cen_ctrl_03, ihsv_hoffset,	pstParams->hue);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_cen_ctrl_03, ihsv_hoffset,	pstParams->hue);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_CMN_DBG_PRINT("win[%d] get f/w, do nothing here.\n",pstParams->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				pInfo->hue[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->hue[LX_PE_WIN_0]),sizeof(LX_PE_CMN_HUE_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pInfo->hue[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&(pInfo->hue[LX_PE_WIN_1]),sizeof(LX_PE_CMN_HUE_T));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
	}while(0);
	return ret;
}
/**
 * set level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_DBG_PRINT("set pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P0L_H13B0_QWr03(p0l_lvcrtl_ctrl_00,	y_offset,			GET_BITS(pstParams->offset,0,10),\
														center_position,	GET_BITS(pstParams->center,0,8),\
														y_gain,				GET_BITS(pstParams->gain,0,8));
				PE_P1L_H13B0_QWr01(pe1_vspyc_ctrl_00, graycolor_enable,		(pstParams->tp_on)? 0x1:0x0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P0R_H13B0_QWr03(p0r_lvcrtl_ctrl_00,	y_offset,			GET_BITS(pstParams->offset,0,10),\
														center_position,	GET_BITS(pstParams->center,0,8),\
														y_gain,				GET_BITS(pstParams->gain,0,8));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_DPP_H13_QWr03(debd_pp_l_level_ctrl_00,	y_offset,			GET_BITS(pstParams->offset,0,10),\
															center_position,	GET_BITS(pstParams->center,0,8),\
															y_gain,				GET_BITS(pstParams->gain,0,8));
				PE_DPP_H13_QWr01(debd_pp_l_vspyc_ctrl_00,	graycolor_enable,	(pstParams->tp_on)? 0x1:0x0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_DPP_H13_QWr03(debd_pp_r_level_ctrl_00,	y_offset,			GET_BITS(pstParams->offset,0,10),\
															center_position,	GET_BITS(pstParams->center,0,8),\
															y_gain,				GET_BITS(pstParams->gain,0,8));
				PE_DPP_H13_QWr01(debd_pp_r_vspyc_ctrl_00,	graycolor_enable,	(pstParams->tp_on)? 0x1:0x0);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr03(pe1_l_level_ctrl_00,	y_offset,			GET_BITS(pstParams->offset,0,10),\
														center_position,	GET_BITS(pstParams->center,0,8),\
														y_gain,				GET_BITS(pstParams->gain,0,8));
				PE_P1L_L9B_QWr01(pe1_l_vspyc_ctrl_00,	graycolor_enable,	(pstParams->tp_on)? 0x1:0x0);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr03(pe1_r_level_ctrl_00,	y_offset,			GET_BITS(pstParams->offset,0,10),\
														center_position,	GET_BITS(pstParams->center,0,8),\
														y_gain,				GET_BITS(pstParams->gain,0,8));
				PE_P1R_L9B_QWr01(pe1_r_vspyc_ctrl_00,	graycolor_enable,	(pstParams->tp_on)? 0x1:0x0);
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13B0_QRd03(p0l_lvcrtl_ctrl_00,	y_offset,			pstParams->offset,\
														center_position,	pstParams->center,\
														y_gain,				pstParams->gain);
				PE_P1L_H13B0_QRd01(pe1_vspyc_ctrl_00,	graycolor_enable,	pstParams->tp_on);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13B0_QRd03(p0r_lvcrtl_ctrl_00,	y_offset,			pstParams->offset,\
														center_position,	pstParams->center,\
														y_gain,				pstParams->gain);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_DPP_H13_QRd03(debd_pp_l_level_ctrl_00,	y_offset,			pstParams->offset,\
															center_position,	pstParams->center,\
															y_gain,				pstParams->gain);
				PE_DPP_H13_QRd01(debd_pp_l_vspyc_ctrl_00,	graycolor_enable,	pstParams->tp_on);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_DPP_H13_QRd03(debd_pp_r_level_ctrl_00,	y_offset,			pstParams->offset,\
															center_position,	pstParams->center,\
															y_gain,				pstParams->gain);
				PE_DPP_H13_QRd01(debd_pp_r_vspyc_ctrl_00,	graycolor_enable,	pstParams->tp_on);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd03(pe1_l_level_ctrl_00,	y_offset,			pstParams->offset,\
														center_position,	pstParams->center,\
														y_gain,				pstParams->gain);
				PE_P1L_L9B_QRd01(pe1_l_vspyc_ctrl_00,	graycolor_enable,	pstParams->tp_on);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd03(pe1_r_level_ctrl_00,	y_offset,			pstParams->offset,\
														center_position,	pstParams->center,\
														y_gain,				pstParams->gain);
				PE_P1R_L9B_QRd01(pe1_r_vspyc_ctrl_00,	graycolor_enable,	pstParams->tp_on);
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CMN_DBG_PRINT("get pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);
	}while(0);
	return ret;
}
/**
 * set auxiliary contrast
 *
 * @param   *pstParams [in] LX_PE_CMN_SUB_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_SetSubContrast(LX_PE_CMN_SUB_CONTRAST_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_DBG_PRINT("set pstParams[%d] : cont:%d\n",pstParams->win_id,pstParams->contrast);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr01(pe1_l_vsprgb_ctrl_00,	contrast,	GET_BITS(pstParams->contrast,0,10));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_vsprgb_ctrl_00,	contrast,	GET_BITS(pstParams->contrast,0,10));
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get auxiliary contrast
 *
 * @param   *pstParams [in/out] LX_PE_CMN_SUB_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_GetSubContrast(LX_PE_CMN_SUB_CONTRAST_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_vsprgb_ctrl_00,	contrast,	pstParams->contrast);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_vsprgb_ctrl_00,	contrast,	pstParams->contrast);
			}
		}
		else
		#endif
		{
			PE_CMN_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CMN_DBG_PRINT("get pstParams[%d] : cont:%d\n",pstParams->win_id,pstParams->contrast);
	}while(0);
	return ret;
}
/**
 * get current common settings
 *
 * @param   *pstParams [in/out] PE_CMN_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetCurCmnSettings(PE_CMN_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		pInfo = &_g_pe_cmn_info;
		if(PE_KDRV_VER_H13||PE_KDRV_VER_L9BX)
		{
			memcpy(pstParams,pInfo,sizeof(PE_CMN_SETTINGS_T));
		}
		else
		{
			PE_CMN_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}


