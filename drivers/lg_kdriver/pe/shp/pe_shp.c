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


/** @file pe_shp.c
 *
 *  driver for picture enhance sharpness functions. ( used only within kdriver )
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
#include "pe_cmn.h"
#include "pe_shp.h"
#include "pe_etc_hw.h"
#include "pe_shp_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_SHP_ERROR	printk

#define PE_SHP_DBG_PRINT(fmt,args...)	\
	if(_g_shp_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_SHP_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_SHP_ERROR(fmt,##args);_action;}}

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
static int PE_SHP_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_SHP_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_SHP_SetScalerFilterCoeff(LX_PE_SHP_SCLFILTER_T *pstParams);
static int PE_SHP_GetScalerFilterCoeff(LX_PE_SHP_SCLFILTER_T *pstParams);
static int PE_SHP_SetReCmnCtrl(void *pstParams);
static int PE_SHP_GetReCmnCtrl(void *pstParams);
static int PE_SHP_SetReHorCtrl(void *pstParams);
static int PE_SHP_GetReHorCtrl(void *pstParams);
static int PE_SHP_SetReVerCtrl(void *pstParams);
static int PE_SHP_GetReVerCtrl(void *pstParams);
static int PE_SHP_SetReMiscCtrl(void *pstParams);
static int PE_SHP_GetReMiscCtrl(void *pstParams);
static int PE_SHP_SetEdgeEnhanceCtrl(void *pstParams);
static int PE_SHP_GetEdgeEnhanceCtrl(void *pstParams);
static int PE_SHP_SetDetailEnhanceCtrl(void *pstParams);
static int PE_SHP_GetDetailEnhanceCtrl(void *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_shp_trace=0x0;	//default should be off.

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/

/**
 * init shp
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_Init();
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_SHP_HW_L9_Init();
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of shp setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_SHP_SET_FUNC(_struct,_func,_void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_SHP_DBG_PRINT("S %s\n",#_struct);\
			PE_SHP_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_SHP_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_SHP_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_SHP_SET_FUNC(LX_PE_SHP_SCLFILTER_T,		PE_SHP_SetScalerFilterCoeff,_STRUCT_INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE0_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE0_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE0_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_EE0_T,			PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE1_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_EE1_T,			PE_SHP_SetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_DE1_T,			PE_SHP_SetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_CMN_T,		PE_SHP_SetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_HOR_T,		PE_SHP_SetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_VER_T,		PE_SHP_SetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_SHP_RE2_MISC_T,		PE_SHP_SetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_SHP_SetDefaultSettings,	_STRUCT_INPUT_);
		PE_SHP_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_SHP_SetDebugSettings,	_STRUCT_INPUT_);
		default:
		{
			PE_SHP_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of shp getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_SHP_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_SHP_GET_FUNC(_struct,_func,_void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_SHP_DBG_PRINT("S %s\n",#_struct);\
			PE_SHP_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_SHP_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_SHP_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_SHP_GET_FUNC(LX_PE_SHP_SCLFILTER_T,	PE_SHP_GetScalerFilterCoeff,_STRUCT_INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE0_CMN_T,	PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE0_HOR_T,	PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE0_VER_T,	PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_EE0_T,		PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_CMN_T,	PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_HOR_T,	PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_VER_T,	PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE1_MISC_T,	PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_EE1_T,		PE_SHP_GetEdgeEnhanceCtrl,	_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_DE1_T,		PE_SHP_GetDetailEnhanceCtrl,_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_CMN_T,	PE_SHP_GetReCmnCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_HOR_T,	PE_SHP_GetReHorCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_VER_T,	PE_SHP_GetReVerCtrl,		_VOID___INPUT_);
		PE_SHP_GET_FUNC(LX_PE_SHP_RE2_MISC_T,	PE_SHP_GetReMiscCtrl,		_VOID___INPUT_);
		default:
		{
			PE_SHP_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * set default settings
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_SHP_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetDefault(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetDefault() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_SHP_HW_L9_SetDefault(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_SetDefault() error.\n",__F__,__L__);
			if(PE_KDRV_VER_L9BX)
			{
				PE_CMN_SETTINGS_T cmn_info;
				ret = PE_CMN_GetCurCmnSettings(&cmn_info);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
				PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
				if(cmn_info.use_pe_fw)
				{
					ret = PE_FWI_L9_SetShpDefault((UINT32)pstParams->win_id);
					PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetShpDefault() error.\n",__F__,__L__);
				}
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_SHP_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(SHP)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_shp_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(SHP)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_SHP_HW_H13_SetDbgPrint(_g_shp_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_SHP_HW_L9_SetDbgPrint(_g_shp_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(SHP)))
				{
					PE_SHP_DBG_PRINT("pe0 der, pe1 der,lsr,shp,cti,ti,dj : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
				        PE_P0L_L9A_QWr01(p0l_der_ctrl_0,		der_en,					0x0);

				        PE_P1L_L9A_QWr01(pe1_l_der_ctrl_0,		der_v_en,				0x0);
				        PE_P1L_L9A_QWr02(pe1_l_lsr_ctrl_06,		edge_y_filter_en,		0x0,\
				        										edge_c_filter_en,		0x0);
				        PE_P1L_L9A_QWr01(pe1_l_shp_edge_ctrl_00,edge_enhance_enable,	0x0);
				        PE_P1L_L9A_QWr01(pe1_l_cti_ctrl_00,		cti_en,					0x0);
				        PE_P1L_L9A_QWr02(pe1_l_cti_ctrl_02,		ycm_en0,				0x0,\
				        										ycm_en1,				0x0);
				        PE_P1L_L9A_QWr01(pe1_l_ti_ctrl_1,		enable,					0x0);
				        PE_P1L_L9A_QWr01(pe1_l_ti_ctrl_2,		enable,					0x0);
				        PE_P1L_L9A_QWr01(pe1_l_ti_ctrl_3,		enable,					0x0);
				        PE_P1L_L9A_QWr01(pe1_l_dj_ctrl_00,		edf_en,					0x0);
				        PE_P1L_L9A_QWr01(pe1_l_lsr_dtl_ctrl_00,	detail_enhancer_enable,	0x0);
				        PE_P1L_L9A_QWr01(pe1_l_lsr_dtl_ee_ctrl_02,enable,				0x0);
				        PE_P1L_L9A_QWr01(pe1_l_shp_um_ctrl_0,	enable,					0x0);
				        PE_P1L_L9A_QWr01(pe1_l_shp_blur_ctrl,	enable,					0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
				        PE_P0R_L9A_QWr01(p0r_der_ctrl_0,		der_en,					0x0);

				        PE_P1R_L9A_QWr01(pe1_r_der_ctrl_0,		der_v_en,				0x0);
				        PE_P1R_L9A_QWr02(pe1_r_lsr_ctrl_06,		edge_y_filter_en,		0x0,\
				        										edge_c_filter_en,		0x0);
				        PE_P1R_L9A_QWr01(pe1_r_shp_edge_ctrl_00,edge_enhance_enable,	0x0);
				        PE_P1R_L9A_QWr01(pe1_r_cti_ctrl_00,		cti_en,					0x0);
				        PE_P1R_L9A_QWr02(pe1_r_cti_ctrl_02,		ycm_en0,				0x0,\
				        										ycm_en1,				0x0);
				        PE_P1R_L9A_QWr01(pe1_r_ti_ctrl_1,		enable,					0x0);
				        PE_P1R_L9A_QWr01(pe1_r_ti_ctrl_2,		enable,					0x0);
				        PE_P1R_L9A_QWr01(pe1_r_ti_ctrl_3,		enable,					0x0);
				        PE_P1R_L9A_QWr01(pe1_r_dj_ctrl_00,		edf_en,					0x0);
				        PE_P1R_L9A_QWr01(pe1_r_lsr_dtl_ctrl_00,	detail_enhancer_enable,	0x0);
				        PE_P1R_L9A_QWr01(pe1_r_lsr_dtl_ee_ctrl_02,enable,				0x0);
				        PE_P1R_L9A_QWr01(pe1_r_shp_um_ctrl_0,	enable,					0x0);
				        PE_P1R_L9A_QWr01(pe1_r_shp_blur_ctrl,	enable,					0x0);
					}
				}
			}
			else
			#endif
			{
				PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * set scaler filter coeff
 *
 * @param   *pstParams [in] LX_PE_SHP_SCLFILTER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_SetScalerFilterCoeff(LX_PE_SHP_SCLFILTER_T *pstParams)
{
	int ret = RET_ERROR;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_SHP_DBG_PRINT("set[%d]:idx_y:%d,%d,idx_c:%d,%d\n",pstParams->win_id,\
			pstParams->h_luma_id,pstParams->v_luma_id,pstParams->h_chrm_id,pstParams->v_chrm_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetScalerFilterCoeff(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetScalerFilterCoeff() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_SHP_HW_L9_SetScalerFilterCoeff(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_SetScalerFilterCoeff() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get scaler filter coeff
 *
 * @param   *pstParams [in/out] LX_PE_SHP_SCLFILTER_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_SHP_GetScalerFilterCoeff(LX_PE_SHP_SCLFILTER_T *pstParams)
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
			PE_SHP_HW_H13_SETTINGS_T param;
			ret = PE_SHP_HW_H13_GetCurShpSettings(&param);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetCurShpSettings() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(win_id))
			{
				param.cur_scl_idx[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&param.cur_scl_idx[LX_PE_WIN_0],sizeof(LX_PE_SHP_SCLFILTER_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				param.cur_scl_idx[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&param.cur_scl_idx[LX_PE_WIN_1],sizeof(LX_PE_SHP_SCLFILTER_T));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			PE_SHP_HW_L9_SETTINGS_T param;
			ret = PE_SHP_HW_L9_GetCurShpSettings(&param);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_L9_GetCurShpSettings() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(win_id))
			{
				param.scl_idx[LX_PE_WIN_0].win_id=pstParams->win_id;
				memcpy(pstParams,&param.scl_idx[LX_PE_WIN_0],sizeof(LX_PE_SHP_SCLFILTER_T));
			}
			if(PE_CHECK_WIN1(win_id))
			{
				param.scl_idx[LX_PE_WIN_1].win_id=pstParams->win_id;
				memcpy(pstParams,&param.scl_idx[LX_PE_WIN_1],sizeof(LX_PE_SHP_SCLFILTER_T));
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_SHP_DBG_PRINT("get[%d]:idx_y:%d,%d,idx_c:%d,%d\n",pstParams->win_id,\
			pstParams->h_luma_id,pstParams->v_luma_id,pstParams->h_chrm_id,pstParams->v_chrm_id);
	}while(0);
	return ret;
}
/**
 * set resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for H13BX
 * - use input struct LX_PE_SHP_RE1_CMN_T for L9BX,H13AX
 * - use input struct LX_PE_SHP_RE0_CMN_T for L9AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_SetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetReCmnCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetReCmnCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_CMN_T *pp=(LX_PE_SHP_RE1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d] : resolution common ctrl\n"\
				" mp w,b_gain:%d,%d,  sp w,b_gain:%d,%d\n"\
				" cti   : en:%d, size:%d, g:%d,%d,%d\n",\
				pp->win_id,pp->mp_white_gain,pp->mp_black_gain,\
				pp->sp_white_gain,pp->sp_black_gain,\
				pp->cti_en,pp->tap_size,pp->cti_gain,pp->ycm_y_gain,pp->ycm_c_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P1L_L9B_QWr02(pe1_l_mp_ctrl_01,	white_gain,	GET_BITS(pp->mp_white_gain,0,7),\
													black_gain,	GET_BITS(pp->mp_black_gain,0,7));
				PE_P1L_L9B_QWr02(pe1_l_sp_ctrl_01,	white_gain,	GET_BITS(pp->sp_white_gain,0,7),\
													black_gain,	GET_BITS(pp->sp_black_gain,0,7));
				PE_P1L_L9B_QWr03(pe1_l_cti_ctrl_00,	cti_en,		GET_BITS(pp->cti_en,0,1),\
													tap_size,	GET_BITS(pp->tap_size,0,3),\
													cti_gain,	GET_BITS(pp->cti_gain,0,8));
				PE_P1L_L9B_QWr02(pe1_l_cti_ctrl_02,	ycm_y_gain,	GET_BITS(pp->ycm_y_gain,0,4),\
													ycm_c_gain,	GET_BITS(pp->ycm_c_gain,0,4));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P1R_L9B_QWr02(pe1_r_mp_ctrl_01,	white_gain,	GET_BITS(pp->mp_white_gain,0,7),\
													black_gain,	GET_BITS(pp->mp_black_gain,0,7));
				PE_P1R_L9B_QWr02(pe1_r_sp_ctrl_01,	white_gain,	GET_BITS(pp->sp_white_gain,0,7),\
													black_gain,	GET_BITS(pp->sp_black_gain,0,7));
				PE_P1R_L9B_QWr03(pe1_r_cti_ctrl_00,	cti_en,		GET_BITS(pp->cti_en,0,1),\
													tap_size,	GET_BITS(pp->tap_size,0,3),\
													cti_gain,	GET_BITS(pp->cti_gain,0,8));
				PE_P1R_L9B_QWr02(pe1_r_cti_ctrl_02,	ycm_y_gain,	GET_BITS(pp->ycm_y_gain,0,4),\
													ycm_c_gain,	GET_BITS(pp->ycm_c_gain,0,4));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_RE0_CMN_T *pp=(LX_PE_SHP_RE0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P1L_L9A_QWr02(pe1_l_shp_edge_ctrl_01,	white_gain,			GET_BITS(pp->peaking_w_gain,0,7),\
															black_gain,			GET_BITS(pp->peaking_b_gain,0,7));
				PE_P1L_L9A_QWr02(pe1_l_lsr_dtl_ctrl_00,		gain_w,				GET_BITS(pp->detail_master_w_gain,0,8),\
															gain_b,				GET_BITS(pp->detail_master_b_gain,0,8));
				PE_P1L_L9A_QWr02(pe1_l_lsr_dtl_ee_ctrl_02,	lap_gain,			GET_BITS(pp->detail_lap_gain,0,8),\
															sobel_manual_gain,	GET_BITS(pp->detail_sobel_gain,0,8));
				PE_P1L_L9A_QWr02(pe1_l_lsr_dtl_ee_ctrl_03,	white_gain, 		GET_BITS(pp->detail_lap_w_gain,0,7),\
															black_gain, 		GET_BITS(pp->detail_lap_b_gain,0,7));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P1R_L9A_QWr02(pe1_r_shp_edge_ctrl_01,	white_gain,			GET_BITS(pp->peaking_w_gain,0,7),\
															black_gain,			GET_BITS(pp->peaking_b_gain,0,7));
				PE_P1R_L9A_QWr02(pe1_r_lsr_dtl_ctrl_00,		gain_w,				GET_BITS(pp->detail_master_w_gain,0,8),\
															gain_b,				GET_BITS(pp->detail_master_b_gain,0,8));
				PE_P1R_L9A_QWr02(pe1_r_lsr_dtl_ee_ctrl_02,	lap_gain,			GET_BITS(pp->detail_lap_gain,0,8),\
															sobel_manual_gain,	GET_BITS(pp->detail_sobel_gain,0,8));
				PE_P1R_L9A_QWr02(pe1_r_lsr_dtl_ee_ctrl_03,	white_gain, 		GET_BITS(pp->detail_lap_w_gain,0,7),\
															black_gain, 		GET_BITS(pp->detail_lap_b_gain,0,7));
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution common control
 * - use input struct LX_PE_SHP_RE2_CMN_T for H13BX
 * - use input struct LX_PE_SHP_RE1_CMN_T for L9BX,H13AX
 * - use input struct LX_PE_SHP_RE0_CMN_T for L9AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_GetReCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_GetReCmnCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetReCmnCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_CMN_T *pp=(LX_PE_SHP_RE1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd02(pe1_l_mp_ctrl_01,	white_gain,	pp->mp_white_gain,\
													black_gain,	pp->mp_black_gain);
				PE_P1L_L9B_QRd02(pe1_l_sp_ctrl_01,	white_gain,	pp->sp_white_gain,\
													black_gain,	pp->sp_black_gain);
				PE_P1L_L9B_QRd03(pe1_l_cti_ctrl_00,	cti_en,		pp->cti_en,\
													tap_size,	pp->tap_size,\
													cti_gain,	pp->cti_gain);
				PE_P1L_L9B_QRd02(pe1_l_cti_ctrl_02,	ycm_y_gain,	pp->ycm_y_gain,\
													ycm_c_gain,	pp->ycm_c_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd02(pe1_r_mp_ctrl_01,	white_gain,	pp->mp_white_gain,\
													black_gain,	pp->mp_black_gain);
				PE_P1R_L9B_QRd02(pe1_r_sp_ctrl_01,	white_gain,	pp->sp_white_gain,\
													black_gain,	pp->sp_black_gain);
				PE_P1R_L9B_QRd03(pe1_r_cti_ctrl_00,	cti_en,		pp->cti_en,\
													tap_size,	pp->tap_size,\
													cti_gain,	pp->cti_gain);
				PE_P1R_L9B_QRd02(pe1_r_cti_ctrl_02,	ycm_y_gain,	pp->ycm_y_gain,\
													ycm_c_gain,	pp->ycm_c_gain);
			}
			PE_SHP_DBG_PRINT("get[%d] : resolution common ctrl\n"\
				" mp w,b_gain:%d,%d,  sp w,b_gain:%d,%d\n"\
				" cti   : en:%d, size:%d, g:%d,%d,%d\n",\
				pp->win_id,pp->mp_white_gain,pp->mp_black_gain,\
				pp->sp_white_gain,pp->sp_black_gain,\
				pp->cti_en,pp->tap_size,pp->cti_gain,pp->ycm_y_gain,pp->ycm_c_gain);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_RE0_CMN_T *pp=(LX_PE_SHP_RE0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9A_QRd02(pe1_l_shp_edge_ctrl_01,	white_gain,			pp->peaking_w_gain,\
															black_gain,			pp->peaking_b_gain);
				PE_P1L_L9A_QRd02(pe1_l_lsr_dtl_ctrl_00,		gain_w,				pp->detail_master_w_gain,\
															gain_b,				pp->detail_master_b_gain);
				PE_P1L_L9A_QRd02(pe1_l_lsr_dtl_ee_ctrl_02,	lap_gain,			pp->detail_lap_gain,\
															sobel_manual_gain,	pp->detail_sobel_gain);
				PE_P1L_L9A_QRd02(pe1_l_lsr_dtl_ee_ctrl_03,	white_gain, 		pp->detail_lap_w_gain,\
															black_gain, 		pp->detail_lap_b_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9A_QRd02(pe1_r_shp_edge_ctrl_01,	white_gain,			pp->peaking_w_gain,\
															black_gain,			pp->peaking_b_gain);
				PE_P1R_L9A_QRd02(pe1_r_lsr_dtl_ctrl_00,		gain_w,				pp->detail_master_w_gain,\
															gain_b,				pp->detail_master_b_gain);
				PE_P1R_L9A_QRd02(pe1_r_lsr_dtl_ee_ctrl_02,	lap_gain,			pp->detail_lap_gain,\
															sobel_manual_gain,	pp->detail_sobel_gain);
				PE_P1R_L9A_QRd02(pe1_r_lsr_dtl_ee_ctrl_03,	white_gain, 		pp->detail_lap_w_gain,\
															black_gain, 		pp->detail_lap_b_gain);
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution horizontal control
 * - use input struct LX_PE_SHP_RE2_HOR_T for L9BX,H13BX
 * - use input struct LX_PE_SHP_RE1_HOR_T for L9BX,H13AX
 * - use input struct LX_PE_SHP_RE0_HOR_T for L9AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_SetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetReHorCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetReHorCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_HOR_T *pp=(LX_PE_SHP_RE1_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d] : resolution horizontal ctrl\n"\
				" en:%d, g:%d,%d,%d, a_gen_w:%d, mp,sp_gain:%d,%d\n",\
				pp->win_id,pp->edge_y_filter_en,pp->reg_csft_gain,\
				pp->edge_filter_white_gain,pp->edge_filter_black_gain,\
				pp->a_gen_width,pp->mp_horizontal_gain,pp->sp_horizontal_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P1L_L9B_QWr01(pe1_l_derh_ctrl_00,a_gen_width,			GET_BITS(pp->a_gen_width,0,4));
				PE_P1L_L9B_QWr01(pe1_l_derh_ctrl_05,reg_csft_gain, 			GET_BITS(pp->reg_csft_gain,0,6));
				PE_P1L_L9B_QWr03(pe1_l_derh_ctrl_06,edge_y_filter_en, 		GET_BITS(pp->edge_y_filter_en,0,1),\
													edge_filter_white_gain,	GET_BITS(pp->edge_filter_white_gain,0,6),\
													edge_filter_black_gain,	GET_BITS(pp->edge_filter_black_gain,0,6));
				PE_P1L_L9B_QWr01(pe1_l_mp_ctrl_01,	horizontal_gain,		GET_BITS(pp->mp_horizontal_gain,0,8));
				PE_P1L_L9B_QWr01(pe1_l_sp_ctrl_01,	horizontal_gain,		GET_BITS(pp->sp_horizontal_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_derh_ctrl_00,a_gen_width,			GET_BITS(pp->a_gen_width,0,4));
				PE_P1R_L9B_QWr01(pe1_r_derh_ctrl_05,reg_csft_gain, 			GET_BITS(pp->reg_csft_gain,0,6));
				PE_P1R_L9B_QWr03(pe1_r_derh_ctrl_06,edge_y_filter_en, 		GET_BITS(pp->edge_y_filter_en,0,1),\
													edge_filter_white_gain,	GET_BITS(pp->edge_filter_white_gain,0,6),\
													edge_filter_black_gain,	GET_BITS(pp->edge_filter_black_gain,0,6));
				PE_P1R_L9B_QWr01(pe1_r_mp_ctrl_01,	horizontal_gain,		GET_BITS(pp->mp_horizontal_gain,0,8));
				PE_P1R_L9B_QWr01(pe1_r_sp_ctrl_01,	horizontal_gain,		GET_BITS(pp->sp_horizontal_gain,0,8));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_RE0_HOR_T *pp=(LX_PE_SHP_RE0_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P1L_L9A_QWr01(pe1_l_shp_edge_ctrl_01, horizontal_gain,	GET_BITS(pp->peaking_hor_gain,0,8));
				PE_P1L_L9A_QWr01(pe1_l_lsr_ctrl_05, csft_gain,				GET_BITS(pp->dr_csft_gain,0,6));
				PE_P1L_L9A_QWr02(pe1_l_lsr_ctrl_06, edge_filter_white_gain,	GET_BITS(pp->dr_edgef_w_gain,0,6),\
													edge_filter_black_gain,	GET_BITS(pp->dr_edgef_b_gain,0,6));
				PE_P1L_L9A_QWr02(pe1_l_ti_ctrl_2,	y_gain,					GET_BITS(pp->ti_hpre_ygain,0,8),\
													c_gain,					GET_BITS(pp->ti_hpre_cgain,0,8));
				PE_P1L_L9A_QWr02(pe1_l_ti_ctrl_3,	y_gain,					GET_BITS(pp->ti_hpost_ygain,0,8),\
													c_gain,					GET_BITS(pp->ti_hpost_cgain,0,8));
				PE_P1L_L9A_QWr02(pe1_l_cti_ctrl_00, tap_size,				GET_BITS(pp->cti_tap_size,0,3),\
													cti_gain,				GET_BITS(pp->cti_gain,0,8));
				PE_P1L_L9A_QWr02(pe1_l_cti_ctrl_02, ycm_band_sel,			GET_BITS(pp->cti_ycm_band_sel,0,3),\
													ycm_diff_th,			GET_BITS(pp->cti_ycm_diff_th,0,8));
				PE_P1L_L9A_QWr02(pe1_l_cti_ctrl_02, ycm_y_gain,				GET_BITS(pp->cti_ycm_y_gain,0,4),\
													ycm_c_gain,				GET_BITS(pp->cti_ycm_c_gain,0,4));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P1R_L9A_QWr01(pe1_r_shp_edge_ctrl_01, horizontal_gain,	GET_BITS(pp->peaking_hor_gain,0,8));
				PE_P1R_L9A_QWr01(pe1_r_lsr_ctrl_05, csft_gain,				GET_BITS(pp->dr_csft_gain,0,6));
				PE_P1R_L9A_QWr02(pe1_r_lsr_ctrl_06, edge_filter_white_gain,	GET_BITS(pp->dr_edgef_w_gain,0,6),\
													edge_filter_black_gain,	GET_BITS(pp->dr_edgef_b_gain,0,6));
				PE_P1R_L9A_QWr02(pe1_r_ti_ctrl_2,	y_gain,					GET_BITS(pp->ti_hpre_ygain,0,8),\
													c_gain,					GET_BITS(pp->ti_hpre_cgain,0,8));
				PE_P1R_L9A_QWr02(pe1_r_ti_ctrl_3,	y_gain,					GET_BITS(pp->ti_hpost_ygain,0,8),\
													c_gain,					GET_BITS(pp->ti_hpost_cgain,0,8));
				PE_P1R_L9A_QWr02(pe1_r_cti_ctrl_00, tap_size,				GET_BITS(pp->cti_tap_size,0,3),\
													cti_gain,				GET_BITS(pp->cti_gain,0,8));
				PE_P1R_L9A_QWr02(pe1_r_cti_ctrl_02, ycm_band_sel,			GET_BITS(pp->cti_ycm_band_sel,0,3),\
													ycm_diff_th,			GET_BITS(pp->cti_ycm_diff_th,0,8));
				PE_P1R_L9A_QWr02(pe1_r_cti_ctrl_02, ycm_y_gain,				GET_BITS(pp->cti_ycm_y_gain,0,4),\
													ycm_c_gain,				GET_BITS(pp->cti_ycm_c_gain,0,4));
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution horizontal control
 * - use input struct LX_PE_SHP_RE1_HOR_T for L9BX,H13
 * - use input struct LX_PE_SHP_RE0_HOR_T for L9AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_GetReHorCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_GetReHorCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetReHorCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_HOR_T *pp=(LX_PE_SHP_RE1_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_derh_ctrl_00,a_gen_width,			pp->a_gen_width);
				PE_P1L_L9B_QRd01(pe1_l_derh_ctrl_05,reg_csft_gain, 			pp->reg_csft_gain);
				PE_P1L_L9B_QRd03(pe1_l_derh_ctrl_06,edge_y_filter_en, 		pp->edge_y_filter_en,\
													edge_filter_white_gain,	pp->edge_filter_white_gain,\
													edge_filter_black_gain,	pp->edge_filter_black_gain);
				PE_P1L_L9B_QRd01(pe1_l_mp_ctrl_01,	horizontal_gain,		pp->mp_horizontal_gain);
				PE_P1L_L9B_QRd01(pe1_l_sp_ctrl_01,	horizontal_gain,		pp->sp_horizontal_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_derh_ctrl_00,a_gen_width,			pp->a_gen_width);
				PE_P1R_L9B_QRd01(pe1_r_derh_ctrl_05,reg_csft_gain, 			pp->reg_csft_gain);
				PE_P1R_L9B_QRd03(pe1_r_derh_ctrl_06,edge_y_filter_en, 		pp->edge_y_filter_en,\
													edge_filter_white_gain,	pp->edge_filter_white_gain,\
													edge_filter_black_gain,	pp->edge_filter_black_gain);
				PE_P1R_L9B_QRd01(pe1_r_mp_ctrl_01,	horizontal_gain,		pp->mp_horizontal_gain);
				PE_P1R_L9B_QRd01(pe1_r_sp_ctrl_01,	horizontal_gain,		pp->sp_horizontal_gain);
			}
			PE_SHP_DBG_PRINT("get[%d] : resolution horizontal ctrl\n"\
				" en:%d, g:%d,%d,%d, a_gen_w:%d, mp,sp_gain:%d,%d\n",\
				pp->win_id,pp->edge_y_filter_en,pp->reg_csft_gain,\
				pp->edge_filter_white_gain,pp->edge_filter_black_gain,\
				pp->a_gen_width,pp->mp_horizontal_gain,pp->sp_horizontal_gain);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_RE0_HOR_T *pp=(LX_PE_SHP_RE0_HOR_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9A_QRd01(pe1_l_shp_edge_ctrl_01, horizontal_gain,	pp->peaking_hor_gain);
				PE_P1L_L9A_QRd01(pe1_l_lsr_ctrl_05, csft_gain,				pp->dr_csft_gain);
				PE_P1L_L9A_QRd02(pe1_l_lsr_ctrl_06, edge_filter_white_gain,	pp->dr_edgef_w_gain,\
													edge_filter_black_gain,	pp->dr_edgef_b_gain);
				PE_P1L_L9A_QRd02(pe1_l_ti_ctrl_2,	y_gain,					pp->ti_hpre_ygain,\
													c_gain,					pp->ti_hpre_cgain);
				PE_P1L_L9A_QRd02(pe1_l_ti_ctrl_3,	y_gain,					pp->ti_hpost_ygain,\
													c_gain,					pp->ti_hpost_cgain);
				PE_P1L_L9A_QRd02(pe1_l_cti_ctrl_00, tap_size,				pp->cti_tap_size,\
													cti_gain,				pp->cti_gain);
				PE_P1L_L9A_QRd02(pe1_l_cti_ctrl_02, ycm_band_sel,			pp->cti_ycm_band_sel,\
													ycm_diff_th,			pp->cti_ycm_diff_th);
				PE_P1L_L9A_QRd02(pe1_l_cti_ctrl_02, ycm_y_gain,				pp->cti_ycm_y_gain,\
													ycm_c_gain,				pp->cti_ycm_c_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9A_QRd01(pe1_r_shp_edge_ctrl_01, horizontal_gain,	pp->peaking_hor_gain);
				PE_P1R_L9A_QRd01(pe1_r_lsr_ctrl_05, csft_gain,				pp->dr_csft_gain);
				PE_P1R_L9A_QRd02(pe1_r_lsr_ctrl_06, edge_filter_white_gain,	pp->dr_edgef_w_gain,\
													edge_filter_black_gain,	pp->dr_edgef_b_gain);
				PE_P1R_L9A_QRd02(pe1_r_ti_ctrl_2,	y_gain,					pp->ti_hpre_ygain,\
													c_gain,					pp->ti_hpre_cgain);
				PE_P1R_L9A_QRd02(pe1_r_ti_ctrl_3,	y_gain,					pp->ti_hpost_ygain,\
													c_gain,					pp->ti_hpost_cgain);
				PE_P1R_L9A_QRd02(pe1_r_cti_ctrl_00, tap_size,				pp->cti_tap_size,\
													cti_gain,				pp->cti_gain);
				PE_P1R_L9A_QRd02(pe1_r_cti_ctrl_02, ycm_band_sel,			pp->cti_ycm_band_sel,\
													ycm_diff_th,			pp->cti_ycm_diff_th);
				PE_P1R_L9A_QRd02(pe1_r_cti_ctrl_02, ycm_y_gain,				pp->cti_ycm_y_gain,\
													ycm_c_gain,				pp->cti_ycm_c_gain);
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for H13BX
 * - use input struct LX_PE_SHP_RE1_VER_T for L9BX,H13AX
 * - use input struct LX_PE_SHP_RE0_VER_T for L9AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_SetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetReVerCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetReVerCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_VER_T *pp=(LX_PE_SHP_RE1_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d] : resolution vertical ctrl\n"\
				" en:%d, th:%d, g:%d,%d,%d, der_g:%d, mmd_sel:%d, mp,sp_g:%d,%d\n",\
				pp->win_id,pp->der_v_en,pp->bif_manual_th,pp->csft_gain,\
				pp->gain_b,pp->gain_w,pp->der_gain_mapping,pp->mmd_sel,\
				pp->mp_vertical_gain,pp->sp_vertical_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P1L_L9B_QWr03(pe1_l_derv_ctrl_0,	der_v_en,			GET_BITS(pp->der_v_en,0,1),\
													bif_manual_th,		GET_BITS(pp->bif_manual_th,0,8),\
													der_gain_mapping,	GET_BITS(pp->der_gain_mapping,0,2));
				PE_P1L_L9B_QWr01(pe1_l_derv_ctrl_1,	csft_gain,			GET_BITS(pp->csft_gain,0,6));
				PE_P1L_L9B_QWr01(pe1_l_derv_ctrl_2,	mmd_sel,			GET_BITS(pp->mmd_sel,0,3));
				PE_P1L_L9B_QWr02(pe1_l_derv_ctrl_3,	gain_b,				GET_BITS(pp->gain_b,0,7),\
													gain_w,				GET_BITS(pp->gain_w,0,7));
				PE_P1L_L9B_QWr01(pe1_l_mp_ctrl_01,	vertical_gain,		GET_BITS(pp->mp_vertical_gain,0,8));
				PE_P1L_L9B_QWr01(pe1_l_sp_ctrl_01,	vertical_gain,		GET_BITS(pp->sp_vertical_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P1R_L9B_QWr03(pe1_r_derv_ctrl_0,	der_v_en,			GET_BITS(pp->der_v_en,0,1),\
													bif_manual_th,		GET_BITS(pp->bif_manual_th,0,8),\
													der_gain_mapping,	GET_BITS(pp->der_gain_mapping,0,2));
				PE_P1R_L9B_QWr01(pe1_r_derv_ctrl_1,	csft_gain,			GET_BITS(pp->csft_gain,0,6));
				PE_P1R_L9B_QWr01(pe1_r_derv_ctrl_2,	mmd_sel,			GET_BITS(pp->mmd_sel,0,3));
				PE_P1R_L9B_QWr02(pe1_r_derv_ctrl_3,	gain_b,				GET_BITS(pp->gain_b,0,7),\
													gain_w,				GET_BITS(pp->gain_w,0,7));
				PE_P1R_L9B_QWr01(pe1_r_mp_ctrl_01,	vertical_gain,		GET_BITS(pp->mp_vertical_gain,0,8));
				PE_P1R_L9B_QWr01(pe1_r_sp_ctrl_01,	vertical_gain,		GET_BITS(pp->sp_vertical_gain,0,8));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_RE0_VER_T *pp=(LX_PE_SHP_RE0_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_L9A_QWr01(p0l_der_ctrl_0,			bif_th,			GET_BITS(pp->dr_vbif_th,0,8));
				PE_P1L_L9A_QWr01(pe1_l_shp_edge_ctrl_01,	vertical_gain,	GET_BITS(pp->peaking_ver_gain,0,8));
				PE_P1L_L9A_QWr01(pe1_l_ti_ctrl_1,			ti_gain, 		GET_BITS(pp->ti_v_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_L9A_QWr01(p0r_der_ctrl_0,			bif_th,			GET_BITS(pp->dr_vbif_th,0,8));
				PE_P1R_L9A_QWr01(pe1_r_shp_edge_ctrl_01,	vertical_gain,	GET_BITS(pp->peaking_ver_gain,0,8));
				PE_P1R_L9A_QWr01(pe1_r_ti_ctrl_1,			ti_gain, 		GET_BITS(pp->ti_v_gain,0,8));
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution vertical control
 * - use input struct LX_PE_SHP_RE2_VER_T for H13BX
 * - use input struct LX_PE_SHP_RE1_VER_T for L9BX,H13AX
 * - use input struct LX_PE_SHP_RE0_VER_T for L9AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_GetReVerCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_GetReVerCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetReVerCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_VER_T *pp=(LX_PE_SHP_RE1_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd03(pe1_l_derv_ctrl_0,	der_v_en,			pp->der_v_en,\
													bif_manual_th,		pp->bif_manual_th,\
													der_gain_mapping,	pp->der_gain_mapping);
				PE_P1L_L9B_QRd01(pe1_l_derv_ctrl_1,	csft_gain,			pp->csft_gain);
				PE_P1L_L9B_QRd01(pe1_l_derv_ctrl_2,	mmd_sel,			pp->mmd_sel);
				PE_P1L_L9B_QRd02(pe1_l_derv_ctrl_3,	gain_b,				pp->gain_b,\
													gain_w,				pp->gain_w);
				PE_P1L_L9B_QRd01(pe1_l_mp_ctrl_01,	vertical_gain,		pp->mp_vertical_gain);
				PE_P1L_L9B_QRd01(pe1_l_sp_ctrl_01,	vertical_gain,		pp->sp_vertical_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd03(pe1_r_derv_ctrl_0,	der_v_en,			pp->der_v_en,\
													bif_manual_th,		pp->bif_manual_th,\
													der_gain_mapping,	pp->der_gain_mapping);
				PE_P1R_L9B_QRd01(pe1_r_derv_ctrl_1,	csft_gain,			pp->csft_gain);
				PE_P1R_L9B_QRd01(pe1_r_derv_ctrl_2,	mmd_sel,			pp->mmd_sel);
				PE_P1R_L9B_QRd02(pe1_r_derv_ctrl_3,	gain_b,				pp->gain_b,\
													gain_w,				pp->gain_w);
				PE_P1R_L9B_QRd01(pe1_r_mp_ctrl_01,	vertical_gain,		pp->mp_vertical_gain);
				PE_P1R_L9B_QRd01(pe1_r_sp_ctrl_01,	vertical_gain,		pp->sp_vertical_gain);
			}
			PE_SHP_DBG_PRINT("get[%d] : resolution vertical ctrl\n"\
				" en:%d, th:%d, g:%d,%d,%d, der_g:%d, mmd_sel:%d, mp,sp_g:%d,%d\n",\
				pp->win_id,pp->der_v_en,pp->bif_manual_th,pp->csft_gain,\
				pp->gain_b,pp->gain_w,pp->der_gain_mapping,pp->mmd_sel,\
				pp->mp_vertical_gain,pp->sp_vertical_gain);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_RE0_VER_T *pp=(LX_PE_SHP_RE0_VER_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9A_QRd01(p0l_der_ctrl_0,		bif_th,			pp->dr_vbif_th);
				PE_P1L_L9A_QRd01(pe1_l_shp_edge_ctrl_01,vertical_gain,	pp->peaking_ver_gain);
				PE_P1L_L9A_QRd01(pe1_l_ti_ctrl_1,		ti_gain, 		pp->ti_v_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{

				PE_P0R_L9A_QRd01(p0r_der_ctrl_0,		bif_th,			pp->dr_vbif_th);
				PE_P1R_L9A_QRd01(pe1_r_shp_edge_ctrl_01,vertical_gain,	pp->peaking_ver_gain);
				PE_P1R_L9A_QRd01(pe1_r_ti_ctrl_1,		ti_gain, 		pp->ti_v_gain);
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for H13BX
 * - use input struct LX_PE_SHP_RE1_MISC_T for L9BX,H13AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_SetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetReMiscCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetReMiscCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_SHP_RE1_MISC_T *pp=(LX_PE_SHP_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d] :  resolution misc ctrl\n"\
				" e-map : sel:%d, ga:%d,%d,%d\n"\
				" t-map : sel:%d,%d, g:%d, gt:%d,%d,%d,%d,%d,%d,%d, cor1:%d,var_th:%d\n"\
				" d-jag : en:%d, th:%d,%d, g:%d\n",pp->win_id,\
				pp->amap2_sel,pp->ga_max,pp->ga_th0,pp->ga_th1,pp->amap1_sel,\
				pp->max_sel,pp->tmap_gain,pp->gt_th0,pp->gt_th0a,pp->gt_th0b,\
				pp->gt_th1,pp->gt_gain0a,pp->gt_gain0b,pp->gt_max,pp->coring_mode1,pp->var_th,\
				pp->center_blur_en,pp->level_th,pp->protect_th,pp->n_avg_gain);
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				ret = PE_FWI_L9_SetReMiscCtrl(pp);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetReMiscCtrl() error.\n",__F__,__L__);
			}
			else
			{
				if(PE_CHECK_WIN0(pp->win_id))
				{
					/* map */
					PE_P1L_L9B_QWr02(pe1_l_coring_ctrl_05,	gt_th1,		GET_BITS(pp->gt_th1,0,8),\
															gt_th0,		GET_BITS(pp->gt_th0,0,8));
					PE_P1L_L9B_QWr02(pe1_l_coring_ctrl_06,	gt_th0a,	GET_BITS(pp->gt_th0a,0,8),\
															gt_th0b,	GET_BITS(pp->gt_th0b,0,8));
				}
				if(PE_CHECK_WIN1(pp->win_id))
				{
					/* map */
					PE_P1R_L9B_QWr02(pe1_r_coring_ctrl_05,	gt_th1,		GET_BITS(pp->gt_th1,0,8),\
															gt_th0,		GET_BITS(pp->gt_th0,0,8));
					PE_P1R_L9B_QWr02(pe1_r_coring_ctrl_06,	gt_th0a,	GET_BITS(pp->gt_th0a,0,8),\
															gt_th0b,	GET_BITS(pp->gt_th0b,0,8));
				}
			}

			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* map */
				PE_P1L_L9B_QWr02(pe1_l_coring_ctrl_04,	coring_mode1,GET_BITS(pp->coring_mode1,0,2),\
														var_th,		GET_BITS(pp->var_th,0,11));
				PE_P1L_L9B_QWr01(pe1_l_coring_ctrl_05,	gt_max,		GET_BITS(pp->gt_max,0,6));
				PE_P1L_L9B_QWr02(pe1_l_coring_ctrl_06,	gt_gain0a,	GET_BITS(pp->gt_gain0a,0,6),\
														gt_gain0b,	GET_BITS(pp->gt_gain0b,0,6));
				PE_P1L_L9B_QWr05(pe1_l_coring_ctrl_00,	amap2_sel,	GET_BITS(pp->amap2_sel,0,2),\
														ga_max,		GET_BITS(pp->ga_max,0,6),\
														ga_th0,		GET_BITS(pp->ga_th0,0,8),\
														ga_th1,		GET_BITS(pp->ga_th1,0,8),\
														amap1_sel,	GET_BITS(pp->amap1_sel,0,2));
				PE_P1L_L9B_QWr01(pe1_l_coring_ctrl_01,	max_sel,	GET_BITS(pp->max_sel,0,3));
				PE_P1L_L9B_QWr01(pe1_l_coring_ctrl_07,	tmap_gain,	GET_BITS(pp->tmap_gain,0,7));
				/* d-jag */
				PE_P1L_L9B_QWr01(pe1_l_dj_ctrl_00,	center_blur_en,	GET_BITS(pp->center_blur_en,0,1));
				PE_P1L_L9B_QWr03(pe1_l_dj_ctrl_01,	level_th,		GET_BITS(pp->level_th,0,8),\
													protect_th,		GET_BITS(pp->protect_th,0,8),\
													n_avg_gain,		GET_BITS(pp->n_avg_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* map */
				PE_P1R_L9B_QWr02(pe1_r_coring_ctrl_04,	coring_mode1,GET_BITS(pp->coring_mode1,0,2),\
														var_th,		GET_BITS(pp->var_th,0,11));
				PE_P1R_L9B_QWr01(pe1_r_coring_ctrl_05,	gt_max,		GET_BITS(pp->gt_max,0,6));
				PE_P1R_L9B_QWr02(pe1_r_coring_ctrl_06,	gt_gain0a,	GET_BITS(pp->gt_gain0a,0,6),\
														gt_gain0b,	GET_BITS(pp->gt_gain0b,0,6));
				PE_P1R_L9B_QWr05(pe1_r_coring_ctrl_00,	amap2_sel,	GET_BITS(pp->amap2_sel,0,2),\
														ga_max,		GET_BITS(pp->ga_max,0,6),\
														ga_th0,		GET_BITS(pp->ga_th0,0,8),\
														ga_th1,		GET_BITS(pp->ga_th1,0,8),\
														amap1_sel,	GET_BITS(pp->amap1_sel,0,2));
				PE_P1R_L9B_QWr01(pe1_r_coring_ctrl_01,	max_sel,	GET_BITS(pp->max_sel,0,3));
				PE_P1R_L9B_QWr01(pe1_r_coring_ctrl_07,	tmap_gain,	GET_BITS(pp->tmap_gain,0,7));
				/* d-jag */
				PE_P1R_L9B_QWr01(pe1_r_dj_ctrl_00,	center_blur_en,	GET_BITS(pp->center_blur_en,0,1));
				PE_P1R_L9B_QWr03(pe1_r_dj_ctrl_01,	level_th,		GET_BITS(pp->level_th,0,8),\
													protect_th,		GET_BITS(pp->protect_th,0,8),\
													n_avg_gain,		GET_BITS(pp->n_avg_gain,0,8));
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get resolution misc control
 * - use input struct LX_PE_SHP_RE2_MISC_T for H13BX
 * - use input struct LX_PE_SHP_RE1_MISC_T for L9BX,H13AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_GetReMiscCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_GetReMiscCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetReMiscCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_SHP_RE1_MISC_T *pp=(LX_PE_SHP_RE1_MISC_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CMN_SETTINGS_T cmn_info;
				ret = PE_CMN_GetCurCmnSettings(&cmn_info);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
				PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
				if(cmn_info.use_pe_fw)
				{
					PE_FWI_L9_SETTINGS_T param;
					ret = PE_FWI_L9_GetCurFwiSettings(&param);
					PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_GetCurFwiSettings() error.\n",__F__,__L__);
					if(PE_CHECK_WIN0(win_id))
					{
						pp->gt_th0 = param.coring_05[LX_PE_WIN_0].gt_th0;
						pp->gt_th1 = param.coring_05[LX_PE_WIN_0].gt_th1;
						pp->gt_th0a = param.coring_06[LX_PE_WIN_0].gt_th0a;
						pp->gt_th0b = param.coring_06[LX_PE_WIN_0].gt_th0b;
					}
					if(PE_CHECK_WIN1(win_id))
					{
						pp->gt_th0 = param.coring_05[LX_PE_WIN_1].gt_th0;
						pp->gt_th1 = param.coring_05[LX_PE_WIN_1].gt_th1;
						pp->gt_th0a = param.coring_06[LX_PE_WIN_1].gt_th0a;
						pp->gt_th0b = param.coring_06[LX_PE_WIN_1].gt_th0b;
					}
				}
				else
				{
					if(PE_CHECK_WIN0(win_id))
					{
						/* map */
						PE_P1L_L9B_QRd02(pe1_l_coring_ctrl_05,	gt_th1,		pp->gt_th1,\
																gt_th0,		pp->gt_th0);
						PE_P1L_L9B_QRd02(pe1_l_coring_ctrl_06,	gt_th0a,	pp->gt_th0a,\
																gt_th0b,	pp->gt_th0b);
					}
					if(PE_CHECK_WIN1(win_id))
					{
						/* map */
						PE_P1R_L9B_QRd02(pe1_r_coring_ctrl_05,	gt_th1,		pp->gt_th1,\
																gt_th0,		pp->gt_th0);
						PE_P1R_L9B_QRd02(pe1_r_coring_ctrl_06,	gt_th0a,	pp->gt_th0a,\
																gt_th0b,	pp->gt_th0b);
					}
				}
				/* map */
				PE_P1L_L9B_QRd05(pe1_l_coring_ctrl_00,	amap2_sel,	pp->amap2_sel,\
														ga_max,		pp->ga_max,\
														ga_th0,		pp->ga_th0,\
														ga_th1,		pp->ga_th1,\
														amap1_sel,	pp->amap1_sel);
				PE_P1L_L9B_QRd01(pe1_l_coring_ctrl_01,	max_sel,	pp->max_sel);
				PE_P1L_L9B_QRd02(pe1_l_coring_ctrl_04,	coring_mode1,pp->coring_mode1,\
														var_th,		pp->var_th);
				PE_P1L_L9B_QRd01(pe1_l_coring_ctrl_05,	gt_max,		pp->gt_max);
				PE_P1L_L9B_QRd02(pe1_l_coring_ctrl_06,	gt_gain0a,	pp->gt_gain0a,\
														gt_gain0b,	pp->gt_gain0b);
				PE_P1L_L9B_QRd01(pe1_l_coring_ctrl_07,	tmap_gain,	pp->tmap_gain);
				/* d-jag */
				PE_P1L_L9B_QRd01(pe1_l_dj_ctrl_00,	center_blur_en,	pp->center_blur_en);
				PE_P1L_L9B_QRd03(pe1_l_dj_ctrl_01,	level_th,		pp->level_th,\
													protect_th,		pp->protect_th,\
													n_avg_gain,		pp->n_avg_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				/* map */
				PE_P1R_L9B_QRd05(pe1_r_coring_ctrl_00,	amap2_sel,	pp->amap2_sel,\
														ga_max,		pp->ga_max,\
														ga_th0,		pp->ga_th0,\
														ga_th1,		pp->ga_th1,\
														amap1_sel,	pp->amap1_sel);
				PE_P1R_L9B_QRd01(pe1_r_coring_ctrl_01,	max_sel,	pp->max_sel);
				PE_P1R_L9B_QRd02(pe1_r_coring_ctrl_04,	coring_mode1,pp->coring_mode1,\
														var_th,		pp->var_th);
				PE_P1R_L9B_QRd01(pe1_r_coring_ctrl_05,	gt_max,		pp->gt_max);
				PE_P1R_L9B_QRd02(pe1_r_coring_ctrl_06,	gt_gain0a,	pp->gt_gain0a,\
														gt_gain0b,	pp->gt_gain0b);
				PE_P1R_L9B_QRd01(pe1_r_coring_ctrl_07,	tmap_gain,	pp->tmap_gain);
				/* d-jag */
				PE_P1R_L9B_QRd01(pe1_r_dj_ctrl_00,	center_blur_en,	pp->center_blur_en);
				PE_P1R_L9B_QRd03(pe1_r_dj_ctrl_01,	level_th,		pp->level_th,\
													protect_th,		pp->protect_th,\
													n_avg_gain,		pp->n_avg_gain);
			}
			PE_SHP_DBG_PRINT("get[%d] :  resolution misc ctrl\n"\
				" e-map : sel:%d, ga:%d,%d,%d\n"\
				" t-map : sel:%d,%d, g:%d, gt:%d,%d,%d,%d,%d,%d,%d, cor1:%d,var_th:%d\n"\
				" d-jag : en:%d, th:%d,%d, g:%d\n",pp->win_id,\
				pp->amap2_sel,pp->ga_max,pp->ga_th0,pp->ga_th1,pp->amap1_sel,\
				pp->max_sel,pp->tmap_gain,pp->gt_th0,pp->gt_th0a,pp->gt_th0b,\
				pp->gt_th1,pp->gt_gain0a,pp->gt_gain0b,pp->gt_max,pp->coring_mode1,pp->var_th,\
				pp->center_blur_en,pp->level_th,pp->protect_th,pp->n_avg_gain);
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for L9BX,H13
 * - use input struct LX_PE_SHP_EE0_T for L9AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_SetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetEdgeEnhanceCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetEdgeEnhanceCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_SHP_EE1_T *pp=(LX_PE_SHP_EE1_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d]: mp g_b,w:%d,%d, sp g_b,w:%d,%d\n",pp->win_id,\
				pp->mp_edge_gain_b,pp->mp_edge_gain_w,pp->sp_edge_gain_b,pp->sp_edge_gain_w);
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				ret = PE_FWI_L9_SetReEdgeAndDetailCtrl((UINT32)pp->win_id,pp,NULL);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetReEdgeAndDetailCtrl() error.\n",__F__,__L__);
			}
			else
			{
				if(PE_CHECK_WIN0(pp->win_id))
				{
					PE_P1L_L9B_QWr02(pe1_l_coring_ctrl_09,	edge_gain_b,	GET_BITS(pp->mp_edge_gain_b,0,7),\
															edge_gain_w,	GET_BITS(pp->mp_edge_gain_w,0,7));
					PE_P1L_L9B_QWr02(pe1_l_dp_ctrl_01,		edge_gain_b,	GET_BITS(pp->sp_edge_gain_b,0,7),\
															edge_gain_w,	GET_BITS(pp->sp_edge_gain_w,0,7));
				}
				if(PE_CHECK_WIN1(pp->win_id))
				{
					PE_P1R_L9B_QWr02(pe1_r_coring_ctrl_09,	edge_gain_b,	GET_BITS(pp->mp_edge_gain_b,0,7),\
															edge_gain_w,	GET_BITS(pp->mp_edge_gain_w,0,7));
					PE_P1R_L9B_QWr02(pe1_r_dp_ctrl_01,		edge_gain_b,	GET_BITS(pp->sp_edge_gain_b,0,7),\
															edge_gain_w,	GET_BITS(pp->sp_edge_gain_w,0,7));
				}
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_EE0_T *pp=(LX_PE_SHP_EE0_T *)pstParams;
			UINT8 si_data,ei_data;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d]: si,ei:%d,%d\n",pp->win_id,pp->sharp_intensity,pp->edge_intensity);

			si_data = pp->sharp_intensity;
			ei_data = pp->edge_intensity;
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P1L_L9A_QWr01(pe1_l_shp_um_ctrl_0,		enable,		si_data? 0x1:0x0);
				PE_P1L_L9A_QWr01(pe1_l_shp_um_ctrl_0,		gain_b,		si_data? 0x38:0x18);
				PE_P1L_L9A_QWr01(pe1_l_shp_um_ctrl_0,		gain_w,		si_data? 0x30:0x10);
				PE_P1L_L9A_QWr01(pe1_l_shp_edge_ctrl_02,	laplacian_weight,	(ei_data==2)? 0x7f:(ei_data==1)? 0x60:0x40);

			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P1R_L9A_QWr01(pe1_r_shp_um_ctrl_0,		enable,		si_data? 0x1:0x0);
				PE_P1R_L9A_QWr01(pe1_r_shp_um_ctrl_0,		gain_b,		si_data? 0x38:0x18);
				PE_P1R_L9A_QWr01(pe1_r_shp_um_ctrl_0,		gain_w,		si_data? 0x30:0x10);
				PE_P1R_L9A_QWr01(pe1_r_shp_edge_ctrl_02,	laplacian_weight,	(ei_data==2)? 0x7f:(ei_data==1)? 0x60:0x40);
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get edge enhance control
 * - use input struct LX_PE_SHP_EE1_T for L9BX,H13
 * - use input struct LX_PE_SHP_EE0_T for L9AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_GetEdgeEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_GetEdgeEnhanceCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetEdgeEnhanceCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_SHP_EE1_T *pp=(LX_PE_SHP_EE1_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				PE_FWI_L9_SETTINGS_T param;
				ret = PE_FWI_L9_GetCurFwiSettings(&param);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_GetCurFwiSettings() error.\n",__F__,__L__);
				if(PE_CHECK_WIN0(win_id))
				{
					pp->mp_edge_gain_b = param.coring_09[LX_PE_WIN_0].edge_gain_b;
					pp->mp_edge_gain_w = param.coring_09[LX_PE_WIN_0].edge_gain_w;
					pp->sp_edge_gain_b = param.dp_01[LX_PE_WIN_0].edge_gain_b; 
					pp->sp_edge_gain_w = param.dp_01[LX_PE_WIN_0].edge_gain_w;
				}
				if(PE_CHECK_WIN1(win_id))
				{
					pp->mp_edge_gain_b = param.coring_09[LX_PE_WIN_1].edge_gain_b;
					pp->mp_edge_gain_w = param.coring_09[LX_PE_WIN_1].edge_gain_w;
					pp->sp_edge_gain_b = param.dp_01[LX_PE_WIN_1].edge_gain_b; 
					pp->sp_edge_gain_w = param.dp_01[LX_PE_WIN_1].edge_gain_w;
				}
			}else
			{
				if(PE_CHECK_WIN0(win_id))
				{
					PE_P1L_L9B_QRd02(pe1_l_coring_ctrl_09,	edge_gain_b,	pp->mp_edge_gain_b,\
															edge_gain_w,	pp->mp_edge_gain_w);
					PE_P1L_L9B_QRd02(pe1_l_dp_ctrl_01,		edge_gain_b,	pp->sp_edge_gain_b,\
															edge_gain_w,	pp->sp_edge_gain_w);
				}
				if(PE_CHECK_WIN1(win_id))
				{
					PE_P1R_L9B_QRd02(pe1_r_coring_ctrl_09,	edge_gain_b,	pp->mp_edge_gain_b,\
															edge_gain_w,	pp->mp_edge_gain_w);
					PE_P1R_L9B_QRd02(pe1_r_dp_ctrl_01,		edge_gain_b,	pp->sp_edge_gain_b,\
															edge_gain_w,	pp->sp_edge_gain_w);
				}
			}
			PE_SHP_DBG_PRINT("get[%d]: mp g_b,w:%d,%d, sp g_b,w:%d,%d\n",\
				pp->win_id,pp->mp_edge_gain_b,pp->mp_edge_gain_w,\
				pp->sp_edge_gain_b,pp->sp_edge_gain_w);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_SHP_EE0_T *pp=(LX_PE_SHP_EE0_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9A_QRd01(pe1_l_shp_um_ctrl_0,		enable,		pp->sharp_intensity);
				PE_P1L_L9A_QRd01(pe1_l_shp_edge_ctrl_02,	laplacian_weight,	pp->edge_intensity);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9A_QRd01(pe1_r_shp_um_ctrl_0,		enable,		pp->sharp_intensity);
				PE_P1R_L9A_QRd01(pe1_r_shp_edge_ctrl_02,	laplacian_weight,	pp->edge_intensity);
			}
			PE_SHP_DBG_PRINT("get[%d]: si,ei:%d,%d\n",pp->win_id,pp->sharp_intensity,pp->edge_intensity);
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for L9BX,H13
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_SetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_SetDetailEnhanceCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_SetDetailEnhanceCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_SHP_DE1_T *pp=(LX_PE_SHP_DE1_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_SHP_DBG_PRINT("set[%d]: mp g_b,w:%d,%d, sp g_b,w:%d,%d\n",\
				pp->win_id,pp->mp_texture_gain_b,pp->mp_texture_gain_w,\
				pp->sp_texture_gain_b,pp->sp_texture_gain_w);
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				ret = PE_FWI_L9_SetReEdgeAndDetailCtrl((UINT32)pp->win_id,NULL,pp);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetReEdgeAndDetailCtrl() error.\n",__F__,__L__);
			}
			else
			{
				if(PE_CHECK_WIN0(pp->win_id))
				{
					PE_P1L_L9B_QWr02(pe1_l_coring_ctrl_09,	texture_gain_b,	GET_BITS(pp->mp_texture_gain_b,0,7),\
															texture_gain_w,	GET_BITS(pp->mp_texture_gain_w,0,7));
					PE_P1L_L9B_QWr02(pe1_l_dp_ctrl_01,		texture_gain_b,	GET_BITS(pp->sp_texture_gain_b,0,7),\
															texture_gain_w,	GET_BITS(pp->sp_texture_gain_w,0,7));
				}
				if(PE_CHECK_WIN1(pp->win_id))
				{
					PE_P1R_L9B_QWr02(pe1_r_coring_ctrl_09,	texture_gain_b,	GET_BITS(pp->mp_texture_gain_b,0,7),\
															texture_gain_w,	GET_BITS(pp->mp_texture_gain_w,0,7));
					PE_P1R_L9B_QWr02(pe1_r_dp_ctrl_01,		texture_gain_b,	GET_BITS(pp->sp_texture_gain_b,0,7),\
															texture_gain_w,	GET_BITS(pp->sp_texture_gain_w,0,7));
				}
			}
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get detail enhance control
 * - use input struct LX_PE_SHP_DE1_T for L9BX,H13
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		function description
 * @author
 */
static int PE_SHP_GetDetailEnhanceCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_SHP_HW_H13_GetDetailEnhanceCtrl(pstParams);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_SHP_HW_H13_GetDetailEnhanceCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_SHP_DE1_T *pp=(LX_PE_SHP_DE1_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_SHP_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				PE_FWI_L9_SETTINGS_T param;
				ret = PE_FWI_L9_GetCurFwiSettings(&param);
				PE_SHP_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_GetCurFwiSettings() error.\n",__F__,__L__);
				if(PE_CHECK_WIN0(win_id))
				{
					pp->mp_texture_gain_b = param.coring_09[LX_PE_WIN_0].texture_gain_b;
					pp->mp_texture_gain_w = param.coring_09[LX_PE_WIN_0].texture_gain_w;
					pp->sp_texture_gain_b = param.dp_01[LX_PE_WIN_0].texture_gain_b; 
					pp->sp_texture_gain_w = param.dp_01[LX_PE_WIN_0].texture_gain_w;
				}
				if(PE_CHECK_WIN1(win_id))
				{
					pp->mp_texture_gain_b = param.coring_09[LX_PE_WIN_1].texture_gain_b;
					pp->mp_texture_gain_w = param.coring_09[LX_PE_WIN_1].texture_gain_w;
					pp->sp_texture_gain_b = param.dp_01[LX_PE_WIN_1].texture_gain_b; 
					pp->sp_texture_gain_w = param.dp_01[LX_PE_WIN_1].texture_gain_w;
				}
			}
			else
			{
				if(PE_CHECK_WIN0(win_id))
				{
					PE_P1L_L9B_QRd02(pe1_l_coring_ctrl_09,	texture_gain_b,	pp->mp_texture_gain_b,\
															texture_gain_w,	pp->mp_texture_gain_w);
					PE_P1L_L9B_QRd02(pe1_l_dp_ctrl_01,		texture_gain_b,	pp->sp_texture_gain_b,\
															texture_gain_w,	pp->sp_texture_gain_w);
				}
				if(PE_CHECK_WIN1(win_id))
				{
					PE_P1R_L9B_QRd02(pe1_r_coring_ctrl_09,	texture_gain_b,	pp->mp_texture_gain_b,\
															texture_gain_w,	pp->mp_texture_gain_w);
					PE_P1R_L9B_QRd02(pe1_r_dp_ctrl_01,		texture_gain_b,	pp->sp_texture_gain_b,\
															texture_gain_w,	pp->sp_texture_gain_w);
				}
			}
			PE_SHP_DBG_PRINT("get[%d]: mp g_b,w:%d,%d, sp g_b,w:%d,%d\n",\
				pp->win_id,pp->mp_texture_gain_b,pp->mp_texture_gain_w,\
				pp->sp_texture_gain_b,pp->sp_texture_gain_w);
		}
		else
		#endif
		{
			PE_SHP_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}


