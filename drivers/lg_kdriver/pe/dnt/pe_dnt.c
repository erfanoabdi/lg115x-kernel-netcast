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


/** @file pe_dnt.c
 *
 *  driver for picture enhance deinterlacer functions. ( used only within kdriver )
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
#include "pe_cmn.h"
#include "pe_dnt.h"
#include "pe_etc_hw.h"
#include "pe_dnt_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DNT_ERROR	printk

#define PE_DNT_DBG_PRINT(fmt,args...)	\
	if(_g_dnt_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_DNT_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_DNT_ERROR(fmt,##args);_action;}}

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
static int PE_DNT_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_DNT_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_DNT_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
static int PE_DNT_GetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
static int PE_DNT_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);
static int PE_DNT_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_DNT_SETTINGS_T _g_pe_dnt_info;
static UINT32 _g_dnt_trace=0x0;		//default should be off.

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * init dnt
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_DNT_DBG_PRINT("init global values.\n");
			memset0(_g_pe_dnt_info);
			ret = PE_DNT_HW_H13_Init();
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			PE_DNT_DBG_PRINT("init global values.\n");
			memset0(_g_pe_dnt_info);
			ret = PE_DNT_HW_L9_Init();
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DNT_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);	
	return ret;
}

/**
 * standard function of dnt setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_DNT_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_DNT_DBG_PRINT("S %s\n",#_struct);\
			PE_DNT_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_DNT_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_DNT_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_DNT_SET_FUNC(LX_PE_DNT_FILMMODE_T,		PE_DNT_SetFilmMode);
		PE_DNT_SET_FUNC(LX_PE_DNT_LD_MODE_T,		PE_DNT_SetLowDelayMode);
		PE_DNT_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_DNT_SetDefaultSettings);
		PE_DNT_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_DNT_SetDebugSettings);
		default:
		{
			PE_DNT_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of dnt getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_DNT_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_DNT_DBG_PRINT("S %s\n",#_struct);\
			PE_DNT_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_DNT_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_DNT_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_DNT_GET_FUNC(LX_PE_DNT_FILMMODE_T,	PE_DNT_GetFilmMode);
		PE_DNT_GET_FUNC(LX_PE_DNT_LD_MODE_T,	PE_DNT_GetLowDelayMode);
		default:
		{
			PE_DNT_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * default setting
 *
 * @param   *pstParams [in]LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_DNT_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DNT_HW_H13_SetDefault(pstParams);
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13_SetDefault() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DNT_HW_L9_SetDefault(pstParams);
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_L9_SetDefault() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DNT_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * debug setting
 *
 * @param   *pstParams [in]LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_DNT_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo=&_g_pe_dnt_info;	/* to avoid warning(unused variable) */
		PE_DNT_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(DNT)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_dnt_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(DNT)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_DNT_HW_H13_SetDbgPrint(_g_dnt_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_DNT_HW_L9_SetDbgPrint(_g_dnt_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DNT)))
				{
					PE_DNT_DBG_PRINT("luma,chroma_mode:%s,%s,  film_mode_enable:disable.\n",\
						pInfo->dbg_op_mode[LX_PE_WIN_0]? "temporal":"spatial",\
						pInfo->dbg_op_mode[LX_PE_WIN_1]? "temporal":"spatial");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9B0_RdFL(ipc_ctrl_00);
						PE_P0L_L9B0_RdFL(ipc_ctrl_23);
						PE_P0L_L9B0_Wr01(ipc_ctrl_00,	luma_mode,			pInfo->dbg_op_mode[LX_PE_WIN_0]);
						PE_P0L_L9B0_Wr01(ipc_ctrl_00,	chroma_mode,		pInfo->dbg_op_mode[LX_PE_WIN_0]);
						PE_P0L_L9B0_Wr01(ipc_ctrl_00,	film_mode_enable,	0x0);
						PE_P0L_L9B0_Wr01(ipc_ctrl_23,	reg_global_tbm_en,	0x0);
						PE_P0L_L9B0_WrFL(ipc_ctrl_00);
						PE_P0L_L9B0_WrFL(ipc_ctrl_23);
						if(pInfo->dbg_op_mode[LX_PE_WIN_0])	pInfo->dbg_op_mode[LX_PE_WIN_0]=0;
						else									pInfo->dbg_op_mode[LX_PE_WIN_0]=1;
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9B0_RdFL(ipc_ctrl_00);
						PE_P0R_L9B0_RdFL(ipc_ctrl_23);
						PE_P0R_L9B0_Wr01(ipc_ctrl_00,	luma_mode,			pInfo->dbg_op_mode[LX_PE_WIN_1]);
						PE_P0R_L9B0_Wr01(ipc_ctrl_00,	chroma_mode,		pInfo->dbg_op_mode[LX_PE_WIN_1]);
						PE_P0R_L9B0_Wr01(ipc_ctrl_00,	film_mode_enable,	0x0);
						PE_P0R_L9B0_Wr01(ipc_ctrl_23,	reg_global_tbm_en,	0x0);
						PE_P0R_L9B0_WrFL(ipc_ctrl_00);
						PE_P0R_L9B0_WrFL(ipc_ctrl_23);
						if(pInfo->dbg_op_mode[LX_PE_WIN_1])	pInfo->dbg_op_mode[LX_PE_WIN_1]=0;
						else									pInfo->dbg_op_mode[LX_PE_WIN_1]=1;
					}
				}
				else
				{
					PE_DNT_DBG_PRINT("luma,chroma_mode : motion adaptive.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9B0_RdFL(ipc_ctrl_00);
						PE_P0L_L9B0_Wr01(ipc_ctrl_00,	luma_mode,	0x2);
						PE_P0L_L9B0_Wr01(ipc_ctrl_00,	chroma_mode,0x2);
						PE_P0L_L9B0_WrFL(ipc_ctrl_00);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9B0_RdFL(ipc_ctrl_00);
						PE_P0R_L9B0_Wr01(ipc_ctrl_00,	luma_mode,	0x2);
						PE_P0R_L9B0_Wr01(ipc_ctrl_00,	chroma_mode,0x2);
						PE_P0R_L9B0_WrFL(ipc_ctrl_00);
					}
				}
			}
			else if(PE_KDRV_VER_L9AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DNT)))
				{
					PE_DNT_DBG_PRINT("luma,chroma_mode:%s,%s,  film_mode_enable:disable.\n",\
						pInfo->dbg_op_mode[LX_PE_WIN_0]? "temporal":"spatial",\
						pInfo->dbg_op_mode[LX_PE_WIN_1]? "temporal":"spatial");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9_RdFL(p0l_ipc_ctrl_00);
						PE_P0L_L9_Wr01(p0l_ipc_ctrl_00,	luma_mode,			pInfo->dbg_op_mode[LX_PE_WIN_0]);
						PE_P0L_L9_Wr01(p0l_ipc_ctrl_00,	chroma_mode,		pInfo->dbg_op_mode[LX_PE_WIN_0]);
						PE_P0L_L9_Wr01(p0l_ipc_ctrl_00,	film_mode_enable,	0x0);
						PE_P0L_L9_WrFL(p0l_ipc_ctrl_00);
						if(pInfo->dbg_op_mode[LX_PE_WIN_0])	pInfo->dbg_op_mode[LX_PE_WIN_0]=0;
						else								pInfo->dbg_op_mode[LX_PE_WIN_0]=1;
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9_RdFL(p0r_ipc_ctrl_00);
						PE_P0R_L9_Wr01(p0r_ipc_ctrl_00,	luma_mode,			pInfo->dbg_op_mode[LX_PE_WIN_1]);
						PE_P0R_L9_Wr01(p0r_ipc_ctrl_00,	chroma_mode,		pInfo->dbg_op_mode[LX_PE_WIN_1]);
						PE_P0R_L9_Wr01(p0r_ipc_ctrl_00,	film_mode_enable,	0x0);
						PE_P0R_L9_WrFL(p0r_ipc_ctrl_00);
						if(pInfo->dbg_op_mode[LX_PE_WIN_1])	pInfo->dbg_op_mode[LX_PE_WIN_1]=0;
						else								pInfo->dbg_op_mode[LX_PE_WIN_1]=1;
					}
				}
				else
				{
					PE_DNT_DBG_PRINT("luma,chroma_mode : motion adaptive.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9_RdFL(p0l_ipc_ctrl_00);
						PE_P0L_L9_Wr01(p0l_ipc_ctrl_00,	luma_mode,	0x2);
						PE_P0L_L9_Wr01(p0l_ipc_ctrl_00,	chroma_mode,0x2);
						PE_P0L_L9_WrFL(p0l_ipc_ctrl_00);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9_RdFL(p0r_ipc_ctrl_00);
						PE_P0R_L9_Wr01(p0r_ipc_ctrl_00,	luma_mode,	0x2);
						PE_P0R_L9_Wr01(p0r_ipc_ctrl_00,	chroma_mode,0x2);
						PE_P0R_L9_WrFL(p0r_ipc_ctrl_00);
					}
				}
			}
			else
			#endif
			{
				PE_DNT_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * set film mode
 *
 * @param   *pstParams [in]LX_PE_DNT_FILMMODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DNT_DBG_PRINT("set pstParams[%d] : en:%d\n",pstParams->win_id,pstParams->enable);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#if 1	// changed_to_fw_control
				PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
				PE_P1L_H13B0_Wr01(pe1_dse_ctrl_01, reg_fmd_en_0,	(pstParams->enable)? 0x1:0x0);
				PE_P1L_H13B0_WrFL(pe1_dse_ctrl_01);
				#else
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_ipc_ctrl_00, cr_film_mode_enable,	(pstParams->enable)? 0x1:0x0);
				PE_P0L_H13B0_WrFL(p0l_ipc_ctrl_00);
				#endif
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				#if 1	// changed_to_fw_control
				PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
				PE_P1L_H13B0_Wr01(pe1_dse_ctrl_01, reg_fmd_en_1,	(pstParams->enable)? 0x1:0x0);
				PE_P1L_H13B0_WrFL(pe1_dse_ctrl_01);
				#else
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_H13B0_Wr01(p0r_ipc_ctrl_00, cr_film_mode_enable,	(pstParams->enable)? 0x1:0x0);
				PE_P0R_H13B0_WrFL(p0r_ipc_ctrl_00);
				#endif
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P0L_H13_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_H13_Wr01(p0l_ipc_ctrl_00, film_mode_enable,	(pstParams->enable)? 0x1:0x0);
				PE_P0L_H13_WrFL(p0l_ipc_ctrl_00);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P0R_H13_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_H13_Wr01(p0r_ipc_ctrl_00, film_mode_enable,	(pstParams->enable)? 0x1:0x0);
				PE_P0R_H13_WrFL(p0r_ipc_ctrl_00);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_DNT_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				ret = PE_FWI_L9_SetFilmMode(pstParams);
				PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFilmMode() error.\n",__F__,__L__);
			}
			else
			{
				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					PE_P0L_L9B0_RdFL(ipc_ctrl_00);
					PE_P0L_L9B0_RdFL(ipc_ctrl_12);
					PE_P0L_L9B0_Wr01(ipc_ctrl_00,	film_mode_enable,	(pstParams->enable)? 0x1:0x0);
					PE_P0L_L9B0_Wr01(ipc_ctrl_12,	fmd_32_enable,		(pstParams->enable)? 0x1:0x0);
					PE_P0L_L9B0_Wr01(ipc_ctrl_12,	fmd_22_enable,		(pstParams->enable)? 0x1:0x0);
					PE_P0L_L9B0_WrFL(ipc_ctrl_00);
					PE_P0L_L9B0_WrFL(ipc_ctrl_12);
				}
				if(PE_CHECK_WIN1(pstParams->win_id))
				{
					PE_P0R_L9B0_RdFL(ipc_ctrl_00);
					PE_P0R_L9B0_RdFL(ipc_ctrl_12);
					PE_P0R_L9B0_Wr01(ipc_ctrl_00,	film_mode_enable,	(pstParams->enable)? 0x1:0x0);
					PE_P0R_L9B0_Wr01(ipc_ctrl_12,	fmd_32_enable,		(pstParams->enable)? 0x1:0x0);
					PE_P0R_L9B0_Wr01(ipc_ctrl_12,	fmd_22_enable,		(pstParams->enable)? 0x1:0x0);
					PE_P0R_L9B0_WrFL(ipc_ctrl_00);
					PE_P0R_L9B0_WrFL(ipc_ctrl_12);
				}
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P0L_L9_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_L9_RdFL(p0l_ipc_ctrl_12);
				PE_P0L_L9_Wr01(p0l_ipc_ctrl_00,	film_mode_enable,	(pstParams->enable)? 0x1:0x0);
				PE_P0L_L9_Wr01(p0l_ipc_ctrl_12,	fmd_32_enable,		(pstParams->enable)? 0x1:0x0);
				PE_P0L_L9_Wr01(p0l_ipc_ctrl_12,	fmd_22_enable,		(pstParams->enable)? 0x1:0x0);
				PE_P0L_L9_WrFL(p0l_ipc_ctrl_00);
				PE_P0L_L9_WrFL(p0l_ipc_ctrl_12);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P0R_L9_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_L9_RdFL(p0r_ipc_ctrl_12);
				PE_P0R_L9_Wr01(p0r_ipc_ctrl_00,	film_mode_enable,	(pstParams->enable)? 0x1:0x0);
				PE_P0R_L9_Wr01(p0r_ipc_ctrl_12,	fmd_32_enable,		(pstParams->enable)? 0x1:0x0);
				PE_P0R_L9_Wr01(p0r_ipc_ctrl_12,	fmd_22_enable,		(pstParams->enable)? 0x1:0x0);
				PE_P0R_L9_WrFL(p0r_ipc_ctrl_00);
				PE_P0R_L9_WrFL(p0r_ipc_ctrl_12);
			}
		}
		else
		#endif
		{
			PE_DNT_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get film mode
 *
 * @param   *pstParams [in/out]LX_PE_DNT_FILMMODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_GetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				#if 1	// changed_to_fw_control
				PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
				PE_P1L_H13B0_Rd01(pe1_dse_ctrl_01, reg_fmd_en_0,	pstParams->enable);
				#else
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_H13B0_Rd01(p0l_ipc_ctrl_00, cr_film_mode_enable,	pstParams->enable);
				#endif
			}
			if(PE_CHECK_WIN1(win_id))
			{
				#if 1	// changed_to_fw_control
				PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
				PE_P1L_H13B0_Rd01(pe1_dse_ctrl_01, reg_fmd_en_1,	pstParams->enable);
				#else
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_H13B0_Rd01(p0r_ipc_ctrl_00, cr_film_mode_enable,	pstParams->enable);
				#endif
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_H13_Rd01(p0l_ipc_ctrl_00, film_mode_enable,	pstParams->enable);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_H13_Rd01(p0r_ipc_ctrl_00, film_mode_enable,	pstParams->enable);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_DNT_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				PE_FWI_L9_SETTINGS_T param;
				ret = PE_FWI_L9_GetCurFwiSettings(&param);
				PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_GetCurFwiSettings() error.\n",__F__,__L__);
				if(PE_CHECK_WIN0(win_id))
				{
					pstParams->enable = param.fmd_ctrl[LX_PE_WIN_0].fmd_enable? 1:0;
				}
				if(PE_CHECK_WIN1(win_id))
				{
					pstParams->enable = param.fmd_ctrl[LX_PE_WIN_1].fmd_enable? 1:0;
				}
			}
			else
			{
				if(PE_CHECK_WIN0(win_id))
				{
					PE_P0L_L9B0_RdFL(ipc_ctrl_00);
					PE_P0L_L9B0_Rd01(ipc_ctrl_00,	film_mode_enable,	pstParams->enable);
				}
				if(PE_CHECK_WIN1(win_id))
				{
					PE_P0R_L9B0_RdFL(ipc_ctrl_00);
					PE_P0R_L9B0_Rd01(ipc_ctrl_00,	film_mode_enable,	pstParams->enable);
				}
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_L9_Rd01(p0l_ipc_ctrl_00,	film_mode_enable,	pstParams->enable);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_L9_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_L9_Rd01(p0r_ipc_ctrl_00,	film_mode_enable,	pstParams->enable);
			}
		}
		else
		#endif
		{
			PE_DNT_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_DNT_DBG_PRINT("get pstParams[%d] : en:%d\n",pstParams->win_id,pstParams->enable);
	} while (0);
	return ret;
}
/**
 * set low delay mode
 *
 * @param   *pstParams [in] LX_PE_DNT_LD_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_DNT_DBG_PRINT("set[%d]:en:%d\n",pstParams->win_id,pstParams->enable);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DNT_HW_H13_SetLowDelayMode(pstParams);
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13_SetLowDelayMode() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DNT_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get low delay mode
 *
 * @param   *pstParams [in/out] LX_PE_DNT_LD_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DNT_HW_H13_GetLowDelayMode(pstParams);
			PE_DNT_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13_GetLowDelayMode() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DNT_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_DNT_DBG_PRINT("get[%d]:en:%d\n",pstParams->win_id,pstParams->enable);
	}while(0);
	return ret;
}

