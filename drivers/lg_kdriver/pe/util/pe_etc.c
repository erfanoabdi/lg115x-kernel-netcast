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


/** @file pe_etc.c
 *
 *  driver for picture enhance etc functions. ( used only within kdriver )
 *	- functional functions regardless of modules
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.07.16
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
#include "pe_spd.h"
#include "pe_etc.h"
#include "pe_etc_hw.h"
#include "pe_cmn_hw.h"
#include "pe_dcm_hw.h"
#include "pe_shp_hw.h"
#include "pe_dnt_hw.h"
#include "pe_nrd_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_ETC_ERROR	printk

#define PE_ETC_DBG_PRINT(fmt,args...)	\
	if(_g_etc_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_ETC_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_ETC_ERROR(fmt,##args);_action;}}

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

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_ETC_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_ETC_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_ETC_SetD3D(LX_PE_D3D_SETTINGS_T *pstParams);
static int PE_ETC_GetD3DInfo(LX_PE_D3D_INFO_T *pstParams);
static int PE_ETC_GetDSCInfo(LX_PE_D3D_DSC_INFO_T *pstParams);
static int PE_ETC_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams);
static int PE_ETC_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams);
static int PE_ETC_SetMiscDbg(LX_PE_ETC_DBG_T *pstParams);
static int PE_ETC_GetMiscDbg(LX_PE_ETC_DBG_T *pstParams);
static int PE_ETC_GetLevelInfo(LX_PE_INF_LEVEL_T *pstParams);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_etc_trace=0x0;	//default should be off.

#ifdef USE_PE_KDRV_CODES_FOR_H13
static PE_ETC_MISC_DBG_T _g_pe_h13_etc_dbg_set_fn[] = {\
	{/* 00 */ PE_TSK_H13_SetTaskOperation,		"PE_TSK_H13_SetTaskOperation"},\
	{/* 01 */ PE_REG_H13_WrReg,					"PE_REG_H13_WrReg"},\
	{/* 02 */ PE_INF_H13_SetPathMonitor,		"PE_INF_H13_SetPathMonitor"}};
static PE_ETC_MISC_DBG_T _g_pe_h13_etc_dbg_get_fn[] = {\
	{/* 00 */ PE_TSK_H13_GetTaskOperation,		"PE_TSK_H13_GetTaskOperation"},\
	{/* 01 */ PE_REG_H13_RdReg,					"PE_REG_H13_RdReg"},\
	{/* 02 */ PE_INF_H13_GetGeneralPicInfo,		"PE_INF_H13_GetGeneralPicInfo"},\
	{/* 03 */ PE_HST_HW_H13_GetGlobalHistInfo,	"PE_HST_HW_H13_GetGlobalHistInfo"},\
	{/* 04 */ PE_INF_H13_GetPathMonitor,		"PE_INF_H13_GetPathMonitor"},\
	{/* 05 */ PE_SHP_H13_RdSclFltCoeff,			"PE_SHP_H13_RdSclFltCoeff"},\
	{/* 06 */ PE_DNT_HW_H13_RdDefault,			"PE_DNT_HW_H13_RdDefault"},\
	{/* 07 */ PE_NRD_HW_H13_RdDefault,			"PE_NRD_HW_H13_RdDefault"},\
	{/* 08 */ PE_SHP_HW_H13_RdDefault,			"PE_SHP_HW_H13_RdDefault"}};
#endif
#ifdef USE_PE_KDRV_CODES_FOR_L9
static PE_ETC_MISC_DBG_T _g_pe_l9_etc_dbg_set_fn[] = {\
	{/* 00 */ PE_TSK_L9_SetTaskOperation,		"PE_TSK_L9_SetTaskOperation"},\
	{/* 01 */ PE_D3D_L9_DBG_SetThreshold,		"PE_D3D_L9_DBG_SetThreshold"}};
static PE_ETC_MISC_DBG_T _g_pe_l9_etc_dbg_get_fn[] = {\
	{/* 00 */ PE_TSK_L9_GetTaskOperation,		"PE_TSK_L9_GetTaskOperation"},\
	{/* 01 */ PE_D3D_L9_DBG_GetThreshold,		"PE_D3D_L9_DBG_GetThreshold"}};
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * misc. module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_INF_H13_Init();
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_Init() error.\n",__F__,__L__);
			/* Starting task should be the last in the pe initialization */
			ret = PE_TSK_H13_StartPicTask();
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_TSK_H13_StartPicTask() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_INF_L9_Init();
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_Init() error.\n",__F__,__L__);
			ret = PE_D3D_L9_Init();
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_L9_Init() error.\n",__F__,__L__);
			/* Starting task should be the last in the pe initialization */
			ret = PE_TSK_L9_StartPicTask();
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_TSK_L9_StartPicTask() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of etc setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_ETC_SET_FSDP(_struct,_func,_sdp)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_ETC_DBG_PRINT("S %s\n",#_struct);\
			PE_ETC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			ret = PE_COPY_FROM_USER(_sdp, (void *)&param, (void *)p_rcv, datasize);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s error.\n",__F__,__L__,#_sdp);\
			ret = _func(&param);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_ETC_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

#define PE_ETC_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_ETC_DBG_PRINT("S %s\n",#_struct);\
			PE_ETC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_ETC_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

#define PE_ETC_SET_TABL(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_ETC_DBG_PRINT("S %s\n",#_struct);\
			PE_ETC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size,0,16) * sizeof(UINT32);\
			PE_ETC_CHECK_CODE(!bufsize,break,"[%s,%d] bufsize zero.\n",__F__,__L__);\
			p_data = OS_Malloc(bufsize);\
			PE_ETC_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] copy_from_user error.\n",__F__,__L__);\
			param.func_num = p_rcv->func_num;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_ETC_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
		if(p_data){OS_Free(p_data);}\
	}\
	break

	/* data null check */
	PE_ETC_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_ETC_SET_TABL(LX_PE_ETC_DBG_T,			PE_ETC_SetMiscDbg);
		PE_ETC_SET_FUNC(LX_PE_INF_DISPLAY_T,		PE_ETC_SetDisplayInfo);
		PE_ETC_SET_FUNC(LX_PE_D3D_SETTINGS_T,		PE_ETC_SetD3D);
		PE_ETC_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_ETC_SetDebugSettings);
		PE_ETC_SET_FSDP(LX_PE_DEFAULT_SETTINGS_T,	PE_ETC_SetDefaultSettings,	PE_SUSPEND_D3D_SETDEFAULT);
		default:
		{
			PE_ETC_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of etc getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_ETC_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_ETC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
		}while(0);\
	}\
	break

#define PE_ETC_GET_TABL(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_ETC_DBG_PRINT("S %s\n",#_struct);\
			PE_ETC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size,0,16) * sizeof(UINT32);\
			PE_ETC_CHECK_CODE(!bufsize,break,"[%s,%d] bufsize zero.\n",__F__,__L__);\
			p_data = OS_Malloc(bufsize);\
			PE_ETC_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] copy_from_user error.\n",__F__,__L__);\
			param.func_num = p_rcv->func_num;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] copy_to_user error.\n",__F__,__L__);\
			PE_ETC_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
		if(p_data){OS_Free(p_data);}\
	}\
	break

	/* data null check */
	PE_ETC_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_ETC_GET_TABL(LX_PE_ETC_DBG_T,		PE_ETC_GetMiscDbg);
		PE_ETC_GET_FUNC(LX_PE_INF_DISPLAY_T,	PE_ETC_GetDisplayInfo);
		PE_ETC_GET_FUNC(LX_PE_D3D_INFO_T,		PE_ETC_GetD3DInfo);
		PE_ETC_GET_FUNC(LX_PE_D3D_DSC_INFO_T,	PE_ETC_GetDSCInfo);
		PE_ETC_GET_FUNC(LX_PE_INF_LEVEL_T,		PE_ETC_GetLevelInfo);
		default:
		{
			PE_ETC_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_ETC_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CCM)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_etc_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(ETC)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_TSK_H13_SetDbgPrint(_g_etc_trace);
			if(PE_KDRV_VER_H13)	PE_INF_H13_SetDbgPrint(_g_etc_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_TSK_L9_SetDbgPrint(_g_etc_trace);
			if(PE_KDRV_VER_L9)	PE_INF_L9_SetDbgPrint(_g_etc_trace);
			#endif
		}
	}while(0);
	return ret;
}
/**
 * default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;

	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_D3D_L9_SetDefault(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_L9_SetDefault() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set misc debug(for debug)
 *
 * @param   *pstParams [in] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_SetMiscDbg(LX_PE_ETC_DBG_T *pstParams)
{
    int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			if (pstParams->func_num>=(sizeof(_g_pe_h13_etc_dbg_set_fn)/sizeof(PE_ETC_MISC_DBG_T)))
			{
				PE_ETC_ERROR("[%s,%d] invalid func_num[%d].\n",__F__,__L__,pstParams->func_num);
				break;
			}
			CHECK_KNULL(_g_pe_h13_etc_dbg_set_fn[pstParams->func_num].func);
			ret = _g_pe_h13_etc_dbg_set_fn[pstParams->func_num].func(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n", \
				__F__,__L__,_g_pe_h13_etc_dbg_set_fn[pstParams->func_num].fn_name);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if (pstParams->func_num>=(sizeof(_g_pe_l9_etc_dbg_set_fn)/sizeof(PE_ETC_MISC_DBG_T)))
			{
				PE_ETC_ERROR("[%s,%d] invalid func_num[%d].\n",__F__,__L__,pstParams->func_num);
				break;
			}
			CHECK_KNULL(_g_pe_l9_etc_dbg_set_fn[pstParams->func_num].func);
			ret = _g_pe_l9_etc_dbg_set_fn[pstParams->func_num].func(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n", \
				__F__,__L__,_g_pe_l9_etc_dbg_set_fn[pstParams->func_num].fn_name);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get misc debug(for debug)
 *
 * @param   *pstParams [in/out] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_GetMiscDbg(LX_PE_ETC_DBG_T *pstParams)
{
    int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			if (pstParams->func_num>=(sizeof(_g_pe_h13_etc_dbg_get_fn)/sizeof(PE_ETC_MISC_DBG_T)))
			{
				PE_ETC_ERROR("[%s,%d] invalid func_num[%d].\n",__F__,__L__,pstParams->func_num);
				break;
			}
			CHECK_KNULL(_g_pe_h13_etc_dbg_get_fn[pstParams->func_num].func);
			ret = _g_pe_h13_etc_dbg_get_fn[pstParams->func_num].func(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n", \
				__F__,__L__,_g_pe_h13_etc_dbg_get_fn[pstParams->func_num].fn_name);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if (pstParams->func_num>=(sizeof(_g_pe_l9_etc_dbg_get_fn)/sizeof(PE_ETC_MISC_DBG_T)))
			{
				PE_ETC_ERROR("[%s,%d] invalid func_num[%d].\n",__F__,__L__,pstParams->func_num);
				break;
			}
			CHECK_KNULL(_g_pe_l9_etc_dbg_get_fn[pstParams->func_num].func);
			ret = _g_pe_l9_etc_dbg_get_fn[pstParams->func_num].func(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n", \
				__F__,__L__,_g_pe_l9_etc_dbg_get_fn[pstParams->func_num].fn_name);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set display info
 *
 * @param   *pstParams [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_INF_H13_SetDispInfo(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_SetDispInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_INF_L9_SetDispInfo(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_SetDispInfo() error.\n",__F__,__L__);
			PE_CMN_HW_L9_SetManualLoadMode(1);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get display info
 *
 * @param   *pstParams [in/out] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_INF_H13_SETTINGS_T inf_set;
			ret = PE_INF_H13_GetCurInfSettings(&inf_set);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(win_id))
			{
				inf_set.disp_info[LX_PE_WIN_0].win_id = pstParams->win_id;
				memcpy(pstParams,&inf_set.disp_info[LX_PE_WIN_0],sizeof(LX_PE_INF_DISPLAY_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				inf_set.disp_info[LX_PE_WIN_1].win_id = pstParams->win_id;
				memcpy(pstParams,&inf_set.disp_info[LX_PE_WIN_1],sizeof(LX_PE_INF_DISPLAY_T));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			PE_INF_L9_SETTINGS_T inf_set;
			ret = PE_INF_L9_GetCurInfSettings(&inf_set);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(win_id))
			{
				inf_set.disp_info[LX_PE_WIN_0].win_id = pstParams->win_id;
				memcpy(pstParams,&inf_set.disp_info[LX_PE_WIN_0],sizeof(LX_PE_INF_DISPLAY_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				inf_set.disp_info[LX_PE_WIN_1].win_id = pstParams->win_id;
				memcpy(pstParams,&inf_set.disp_info[LX_PE_WIN_1],sizeof(LX_PE_INF_DISPLAY_T));
			}
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set 3d detection
 *
 * @param   *pstParams [in] LX_PE_D3D_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_SetD3D(LX_PE_D3D_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_D3D_L9_SetD3D(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_L9_SetD3D() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get 3d detection
 *
 * @param   *pstParams [in/out] LX_PE_D3D_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_GetD3DInfo(LX_PE_D3D_INFO_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_D3D_L9_GetD3DInfo(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_L9_GetD3DInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get dual screen info.
 *
 * @param   *pstParams [in/out] LX_PE_D3D_DSC_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_GetDSCInfo(LX_PE_D3D_DSC_INFO_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			ret = PE_D3D_L9_GetDSCInfo(pstParams);
			PE_ETC_CHECK_CODE(ret,break,"[%s,%d] PE_D3D_L9_GetDSCInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get level info
 *
 * @param   *pstParams [in/out] LX_PE_INF_LEVEL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_ETC_GetLevelInfo(LX_PE_INF_LEVEL_T *pstParams)
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
				if(pstParams->sel&LX_PE_LEVEL_MOTION)
				{	PE_P0L_H13B0_QRd01(p0l_tnr_status_00, x_avg_t,	 	pstParams->motion_level);}
				if(pstParams->sel&LX_PE_LEVEL_NOISE)
				{	PE_P0L_H13B0_QRd01(p0l_tnr_status_00, nt_lvl, 		pstParams->noise_level);}
				if(pstParams->sel&LX_PE_LEVEL_PEAKPOS)
				{	PE_P0L_H13B0_QRd01(p0l_tnr_status_00, x_peak_t2, 	pstParams->peakpos_level);}
			}
			if(PE_CHECK_WIN1(win_id))
			{
				if(pstParams->sel&LX_PE_LEVEL_MOTION)
				{	PE_P0R_H13B0_QRd01(p0r_tnr_status_00, x_avg_t, 		pstParams->motion_level);}
				if(pstParams->sel&LX_PE_LEVEL_NOISE)
				{	PE_P0R_H13B0_QRd01(p0r_tnr_status_00, nt_lvl, 		pstParams->noise_level);}
				if(pstParams->sel&LX_PE_LEVEL_PEAKPOS)
				{	PE_P0R_H13B0_QRd01(p0r_tnr_status_00, x_peak_t2, 	pstParams->peakpos_level);}
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				if(pstParams->sel&LX_PE_LEVEL_MOTION)
				{	PE_P0L_H13_QRd01(p0l_tnr_status_00, x_avg_t, 	pstParams->motion_level);}
				if(pstParams->sel&LX_PE_LEVEL_NOISE)
				{	PE_P0L_H13_QRd01(p0l_tnr_status_00, nt_lvl, 	pstParams->noise_level);}
				if(pstParams->sel&LX_PE_LEVEL_PEAKPOS)
				{	PE_P0L_H13_QRd01(p0l_tnr_status_00, x_peak_t2, 	pstParams->peakpos_level);}
			}
			if(PE_CHECK_WIN1(win_id))
			{
				if(pstParams->sel&LX_PE_LEVEL_MOTION)
				{	PE_P0R_H13_QRd01(p0r_tnr_status_00, x_avg_t, 	pstParams->motion_level);}
				if(pstParams->sel&LX_PE_LEVEL_NOISE)
				{	PE_P0R_H13_QRd01(p0r_tnr_status_00, nt_lvl, 	pstParams->noise_level);}
				if(pstParams->sel&LX_PE_LEVEL_PEAKPOS)
				{	PE_P0R_H13_QRd01(p0r_tnr_status_00, x_peak_t2, 	pstParams->peakpos_level);}
			}
		}
		else
		#endif
		{
			PE_ETC_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
