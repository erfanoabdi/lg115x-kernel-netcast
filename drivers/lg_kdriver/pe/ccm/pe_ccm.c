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


/** @file pe_ccm.c
 *
 *  driver for picture enhance color correction module functions. ( used only within kdriver )
 *	- white balance, gamma control.
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
#include "pe_ccm.h"
#include "pe_etc_hw.h"
#include "pe_ccm_hw.h"
#include "pe_cmn_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CCM_LUT_A	0
#define PE_CCM_LUT_B	1
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CCM_ERROR	printk

#define PE_CCM_DBG_PRINT(fmt,args...)	\
	if(_g_ccm_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CCM_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_CCM_ERROR(fmt,##args);_action;}}

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
static int PE_CCM_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_CCM_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_CCM_SetGammaLut(LX_PE_CCM_GAMMALUT_T *pstParams);
static int PE_CCM_GetGammaLut(LX_PE_CCM_GAMMALUT_T *pstParams);
static int PE_CCM_SetWhiteBalance(LX_PE_CCM_WB_T *pstParams);
static int PE_CCM_GetWhiteBalance(LX_PE_CCM_WB_T *pstParams);
static int PE_CCM_SetAutoCorrection(LX_PE_CCM_AUTO_CR_T *pstParams);
static int PE_CCM_GetAutoCorrection(LX_PE_CCM_AUTO_CR_T *pstParams);
static int PE_CCM_SetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams);
static int PE_CCM_GetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams);
static int PE_CCM_SetGammaLutByReg(LX_PE_CCM_GAMMALUT_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_ccm_trace=0x0;			//default should be off.
static PE_CCM_SETTINGS_T _g_pe_ccm_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init color correctin module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			memset0(_g_pe_ccm_info);
			_g_pe_ccm_info.use_ddr = 0x0;	// set gamma lut by REG
			if(PE_KDRV_VER_H13AX) _g_pe_ccm_info.lut_type = PE_CCM_LUT_B;
			else					_g_pe_ccm_info.lut_type = PE_CCM_LUT_A;
			ret = PE_CCM_HW_H13_Init();
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			memset0(_g_pe_ccm_info);
			_g_pe_ccm_info.use_ddr = 0x1;	// set gamma lut by DDR
			ret = PE_CCM_HW_L9_Init();
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of ccm setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CCM_SET_TABL(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_CCM_DBG_PRINT("S %s\n",#_struct);\
			PE_CCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size,0,16) * sizeof(UINT32);\
			PE_CCM_CHECK_CODE(!bufsize,break,"[%s,%d] bufsize zero.\n",__F__,__L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CCM_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] copy_from_user error.\n",__F__,__L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_CCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
		if(p_data){OS_Free(p_data);}\
	}\
	break

#define PE_CCM_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CCM_DBG_PRINT("S %s\n",#_struct);\
			PE_CCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_CCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CCM_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CCM_SET_FUNC(LX_PE_CCM_PIXEL_REPLACE_T,	PE_CCM_SetPixelReplacement);
		PE_CCM_SET_FUNC(LX_PE_CCM_WB_T,				PE_CCM_SetWhiteBalance);
		PE_CCM_SET_FUNC(LX_PE_CCM_AUTO_CR_T,		PE_CCM_SetAutoCorrection);
		PE_CCM_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CCM_SetDefaultSettings);
		PE_CCM_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CCM_SetDebugSettings);
		PE_CCM_SET_TABL(LX_PE_CCM_GAMMALUT_T,		PE_CCM_SetGammaLut);
		default:
		{
			PE_CCM_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}

	return ret;
}

/**
 * standard function of ccm getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CCM_GET_TABL(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_CCM_DBG_PRINT("S %s\n",#_struct);\
			PE_CCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size,0,16) * sizeof(UINT32);\
			PE_CCM_CHECK_CODE(!bufsize,break,"[%s,%d] bufsize zero.\n",__F__,__L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CCM_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] copy_to_user error.\n",__F__,__L__);\
			PE_CCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
		if(p_data){OS_Free(p_data);}\
	}\
	break

#define PE_CCM_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CCM_DBG_PRINT("S %s\n",#_struct);\
			PE_CCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_CCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CCM_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CCM_GET_FUNC(LX_PE_CCM_PIXEL_REPLACE_T,	PE_CCM_GetPixelReplacement);
		PE_CCM_GET_FUNC(LX_PE_CCM_WB_T,				PE_CCM_GetWhiteBalance);
		PE_CCM_GET_FUNC(LX_PE_CCM_AUTO_CR_T,		PE_CCM_GetAutoCorrection);
		PE_CCM_GET_TABL(LX_PE_CCM_GAMMALUT_T,		PE_CCM_GetGammaLut);
		default:
		{
			PE_CCM_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}

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
static int PE_CCM_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
	}while(0);
	return ret;
}
/**
 * ccm Debug setting
 *
 * @param   *pstParams [in/out] LX_PE_DBG_SETTINGS_T int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CCM)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_ccm_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CCM)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_CCM_HW_H13_SetDbgPrint(_g_ccm_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_CCM_HW_L9_SetDbgPrint(_g_ccm_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)
			{
				ret = PE_CCM_HW_H13_SetDebugBypassSettings(pstParams);
				PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_H13_SetDebugBypassSettings() error.\n",__F__,__L__);
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)
			{
				ret = PE_CCM_HW_L9_SetDebugBypassSettings(pstParams);
				PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_SetDebugBypassSettings() error.\n",__F__,__L__);
			}
			else
			#endif
			{
				PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * set gamma correction lut
 *
 * @param   *pstParams [in] LX_PE_CCM_GAMMALUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_SetGammaLut(LX_PE_CCM_GAMMALUT_T *pstParams)
{
	int ret = RET_OK;
	PE_CCM_SETTINGS_T *pInfo=&_g_pe_ccm_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_CHECK_CODE(!(pstParams->size),return RET_ERROR,"[%s,%d] size is zero.\n",__F__,__L__);
		PE_CCM_CHECK_CODE(!(pstParams->data),return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			LX_PE_WIN_ID win_id=pstParams->win_id;
			if(PE_CHECK_WIN0(win_id))
			{
				pstParams->win_id=LX_PE_WIN_0;
				ret = PE_CCM_SetGammaLutByReg(pstParams);
				PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_H13_SetGammaLutByReg() error.\n",__F__,__L__);
				if(pInfo->lut_type == PE_CCM_LUT_A)	pInfo->lut_type= PE_CCM_LUT_B;
				else								pInfo->lut_type= PE_CCM_LUT_A;
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			PE_CCM_DBG_PRINT("_g_pe_ccm_info.use_ddr : %s.\n",_g_pe_ccm_info.use_ddr? "yes":"no");
			if( pInfo->use_ddr)
			{
				PE_INF_L9_SETTINGS_T inf_set;
				LX_PE_WIN_ID win_id=pstParams->win_id;
				ret = PE_INF_L9_GetCurInfSettings(&inf_set);
				PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
				if(inf_set.disp_info[LX_PE_WIN_0].out_type==LX_PE_OUT_UD)
				{
					pstParams->win_id=LX_PE_WIN_ALL;
					ret = PE_CCM_HW_L9_SetAllGammaLutByDdr(pstParams);
					PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_SetAllGammaLutByDdr() error.\n",__F__,__L__);
				}
				else
				{
					if(PE_CHECK_WIN0(win_id))
					{
						pstParams->win_id=LX_PE_WIN_0;
						ret = PE_CCM_HW_L9_SetGammaLutByDdr(pstParams);
						PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_SetGammaLutByDdr() error.\n",__F__,__L__);
					}
					if(PE_CHECK_WIN1(win_id))
					{
						if(win_id==LX_PE_WIN_ALL)
						{
							OS_MsecSleep(30);	// 20111125, sj.youm, 30m : experimental value for 1080p 24hz SBS
						}
						pstParams->win_id=LX_PE_WIN_1;
						ret = PE_CCM_HW_L9_SetGammaLutByDdr(pstParams);
						PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_SetGammaLutByDdr() error.\n",__F__,__L__);
					}
				}
			}
			else
			{
				ret = PE_CCM_SetGammaLutByReg(pstParams);
				PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_SetGammaLutByReg() error.\n",__F__,__L__);
			}
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * get gamma correction lut
 *
 * @param   *pstParams [in/out] LX_PE_CCM_GAMMALUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_GetGammaLut(LX_PE_CCM_GAMMALUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count = 0;
	LX_PE_WIN_ID win_id;
	PE_CCM_SETTINGS_T *pInfo=NULL;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_CHECK_CODE(!(pstParams->size),return RET_ERROR,"[%s,%d] size is zero.\n",__F__,__L__);
		PE_CCM_CHECK_CODE(!(pstParams->data),return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
		pInfo=&_g_pe_ccm_info;	/* to avoid warning(unused variable) */
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_gmc_ctrl_02,	gmc_mode,		0x2);//read mode
				PE_P1L_H13B0_QWr01(pe1_gmc_ctrl_01,	gmc_lut_rd_sel,(pInfo->lut_type)? 0x1:0x0);
				PE_P1L_H13B0_QWr02(pe1_gmc_ia_ctrl,	capture_ai,		0x1, //ai mode on
													capture_addr,	0x0);
				//OS_MsecSleep(20);	// 20110530, sj.youm, 20m : experimental value //  ??
				PE_P1L_H13B0_QWr01(pe1_top_ctrl_00,	load_time,		0x1);
				for(count=0;count<pstParams->size;count++)
				{
					PE_P1L_H13B0_RdFL(pe1_gmc_ia_data);
					pstParams->data[count] = PE_P1L_H13B0_Rd(pe1_gmc_ia_data);
				}
				PE_P1L_H13B0_QWr01(pe1_gmc_ctrl_02,	gmc_mode,		0x1);
				PE_P1L_H13B0_QWr01(pe1_top_ctrl_00,	load_time,		0x0);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QWr01(pe1_gmc_ctrl_02,	gmc_mode,		0x0);//read mode
				PE_P1L_H13_QWr01(pe1_gmc_ctrl_01,	gmc_lut_rd_sel,(pInfo->lut_type)? 0x1:0x0);
				PE_P1L_H13_QWr02(pe1_gmc_ia_ctrl,	capture_ai,		0x1, //ai mode on
													capture_addr,	0x0);
				//OS_MsecSleep(20);	// 20110530, sj.youm, 20m : experimental value //  ??
				PE_P1L_H13_QWr01(pe1_top_ctrl_00,	load_time,		0x1);
				for(count=0;count<pstParams->size;count++)
				{
					PE_P1L_H13_RdFL(pe1_gmc_ia_data);
					pstParams->data[count] = PE_P1L_H13_Rd(pe1_gmc_ia_data);
				}
				PE_P1L_H13_QWr01(pe1_gmc_ctrl_02,	gmc_mode,		0x1);
				PE_P1L_H13_QWr01(pe1_top_ctrl_00,	load_time,		0x0);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_HW_L9_SetManualLoadMode(0);
			OS_MsecSleep(30);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x0);//read mode
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_ctrl);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode off
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ia_ctrl);

				OS_MsecSleep(20);	// 20110530, sj.youm, 20m : experimental value
				for(count=0;count<pstParams->size;count++)
				{
					PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_data);
					pstParams->data[count] = PE_P1L_L9B0_Rd(pe1_l_gmc_ia_data);
				}
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x2);
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x0);//read mode
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_ctrl);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode off
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ia_ctrl);

				OS_MsecSleep(20);	// 20110530, sj.youm, 20m : experimental value
				for(count=0;count<pstParams->size;count++)
				{
					PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_data);
					pstParams->data[count] = PE_P1R_L9B0_Rd(pe1_r_gmc_ia_data);
				}
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x2);
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
			}
			PE_CMN_HW_L9_SetManualLoadMode(1);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x0);//read mode
				PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9_RdFL(pe1_l_gmc_ia_ctrl);
				PE_P1L_L9_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode off
				PE_P1L_L9_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1L_L9_WrFL(pe1_l_gmc_ia_ctrl);

				OS_MsecSleep(20);	// 20110530, sj.youm, 20m : experimental value
				for(count=0;count<pstParams->size;count++)
				{
					PE_P1L_L9_RdFL(pe1_l_gmc_ia_data);
					pstParams->data[count] = PE_P1L_L9_Rd(pe1_l_gmc_ia_data);
				}
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x2);
				PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x0);//read mode
				PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9_RdFL(pe1_r_gmc_ia_ctrl);
				PE_P1R_L9_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode off
				PE_P1R_L9_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1R_L9_WrFL(pe1_r_gmc_ia_ctrl);

				OS_MsecSleep(20);	// 20110530, sj.youm, 20m : experimental value
				for(count=0;count<pstParams->size;count++)
				{
					PE_P1R_L9_RdFL(pe1_r_gmc_ia_data);
					pstParams->data[count] = PE_P1R_L9_Rd(pe1_r_gmc_ia_data);
				}
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x2);
				PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
			}
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set pixel replacement
 *
 * @param   *pstParams [in/out] LX_PE_CCM_PIXEL_REPLACE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_SetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_CCM_HW_H13_SetPixelReplacement(pstParams);
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_H13_SetPixelReplacement() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CCM_HW_L9_SetPixelReplacement(pstParams);
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_SetPixelReplacement() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);

	return ret;
}
/**
 * get pixel replacement
 *
 * @param   *pstParams [in/out] LX_PE_CCM_PIXEL_REPLACE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_GetPixelReplacement(LX_PE_CCM_PIXEL_REPLACE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_CCM_HW_H13_GetPixelReplacement(pstParams);
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_H13_GetPixelReplacement() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CCM_HW_L9_GetPixelReplacement(pstParams);
			PE_CCM_CHECK_CODE(ret,break,"[%s,%d] PE_CCM_HW_L9_GetPixelReplacement() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set white Balance
 *
 * @param   *pstParams [in/out] LX_PE_CCM_WB_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_SetWhiteBalance(LX_PE_CCM_WB_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CCM_DBG_PRINT("set[%d] : gain:%d,%d,%d, offset:%d,%d,%d\n",\
			pstParams->win_id,pstParams->r_gain,pstParams->g_gain,pstParams->b_gain,\
			pstParams->r_offset,pstParams->g_offset,pstParams->b_offset);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr03(pe1_wb_ctrl_01,  user_ctrl_g_gain,	GET_BITS(pstParams->g_gain,0,8),\
													user_ctrl_b_gain,	GET_BITS(pstParams->b_gain,0,8),\
													user_ctrl_r_gain,	GET_BITS(pstParams->r_gain,0,8));

				PE_P1L_H13B0_QWr03(pe1_wb_ctrl_02,  user_ctrl_g_offset,	GET_BITS(pstParams->g_offset,0,8),\
													user_ctrl_b_offset,	GET_BITS(pstParams->b_offset,0,8),\
													user_ctrl_r_offset,	GET_BITS(pstParams->r_offset,0,8));

			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_QWr03(pe1_wb_ctrl_01, 	user_ctrl_g_gain,	GET_BITS(pstParams->g_gain,0,8),\
													user_ctrl_b_gain,	GET_BITS(pstParams->b_gain,0,8),\
													user_ctrl_r_gain,	GET_BITS(pstParams->r_gain,0,8));

				PE_P1L_H13_QWr03(pe1_wb_ctrl_02, 	user_ctrl_g_offset,	GET_BITS(pstParams->g_offset,0,8),\
													user_ctrl_b_offset,	GET_BITS(pstParams->b_offset,0,8),\
													user_ctrl_r_offset,	GET_BITS(pstParams->r_offset,0,8));

			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_wb_ctrl_01);
				PE_P1L_L9B0_RdFL(pe1_l_wb_ctrl_02);
				PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_01, user_ctrl_g_gain,	GET_BITS(pstParams->g_gain,0,8));
				PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_01, user_ctrl_b_gain,	GET_BITS(pstParams->b_gain,0,8));
				PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_01, user_ctrl_r_gain,	GET_BITS(pstParams->r_gain,0,8));
				PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_02, user_ctrl_g_offset,	GET_BITS(pstParams->g_offset,0,8));
				PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_02, user_ctrl_b_offset,	GET_BITS(pstParams->b_offset,0,8));
				PE_P1L_L9B0_Wr01(pe1_l_wb_ctrl_02, user_ctrl_r_offset,	GET_BITS(pstParams->r_offset,0,8));
				PE_P1L_L9B0_WrFL(pe1_l_wb_ctrl_01);
				PE_P1L_L9B0_WrFL(pe1_l_wb_ctrl_02);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_wb_ctrl_01);
				PE_P1R_L9B0_RdFL(pe1_r_wb_ctrl_02);
				PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_01, user_ctrl_g_gain,	GET_BITS(pstParams->g_gain,0,8));
				PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_01, user_ctrl_b_gain,	GET_BITS(pstParams->b_gain,0,8));
				PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_01, user_ctrl_r_gain,	GET_BITS(pstParams->r_gain,0,8));
				PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_02, user_ctrl_g_offset,	GET_BITS(pstParams->g_offset,0,8));
				PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_02, user_ctrl_b_offset,	GET_BITS(pstParams->b_offset,0,8));
				PE_P1R_L9B0_Wr01(pe1_r_wb_ctrl_02, user_ctrl_r_offset,	GET_BITS(pstParams->r_offset,0,8));
				PE_P1R_L9B0_WrFL(pe1_r_wb_ctrl_01);
				PE_P1R_L9B0_WrFL(pe1_r_wb_ctrl_02);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_wb_ctrl_02);
				PE_P1L_L9_RdFL(pe1_l_wb_ctrl_03);
				PE_P1L_L9_Wr01(pe1_l_wb_ctrl_02, user_ctrl_g_gain,		GET_BITS(pstParams->g_gain,0,8));
				PE_P1L_L9_Wr01(pe1_l_wb_ctrl_02, user_ctrl_b_gain,		GET_BITS(pstParams->b_gain,0,8));
				PE_P1L_L9_Wr01(pe1_l_wb_ctrl_02, user_ctrl_r_gain,		GET_BITS(pstParams->r_gain,0,8));
				PE_P1L_L9_Wr01(pe1_l_wb_ctrl_03, user_ctrl_g_offset,	GET_BITS(pstParams->g_offset,0,8));
				PE_P1L_L9_Wr01(pe1_l_wb_ctrl_03, user_ctrl_b_offset,	GET_BITS(pstParams->b_offset,0,8));
				PE_P1L_L9_Wr01(pe1_l_wb_ctrl_03, user_ctrl_r_offset,	GET_BITS(pstParams->r_offset,0,8));
				PE_P1L_L9_WrFL(pe1_l_wb_ctrl_02);
				PE_P1L_L9_WrFL(pe1_l_wb_ctrl_03);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_wb_ctrl_02);
				PE_P1R_L9_RdFL(pe1_r_wb_ctrl_03);
				PE_P1R_L9_Wr01(pe1_r_wb_ctrl_02, user_ctrl_g_gain,		GET_BITS(pstParams->g_gain,0,8));
				PE_P1R_L9_Wr01(pe1_r_wb_ctrl_02, user_ctrl_b_gain,		GET_BITS(pstParams->b_gain,0,8));
				PE_P1R_L9_Wr01(pe1_r_wb_ctrl_02, user_ctrl_r_gain,		GET_BITS(pstParams->r_gain,0,8));
				PE_P1R_L9_Wr01(pe1_r_wb_ctrl_03, user_ctrl_g_offset,	GET_BITS(pstParams->g_offset,0,8));
				PE_P1R_L9_Wr01(pe1_r_wb_ctrl_03, user_ctrl_b_offset,	GET_BITS(pstParams->b_offset,0,8));
				PE_P1R_L9_Wr01(pe1_r_wb_ctrl_03, user_ctrl_r_offset,	GET_BITS(pstParams->r_offset,0,8));
				PE_P1R_L9_WrFL(pe1_r_wb_ctrl_02);
				PE_P1R_L9_WrFL(pe1_r_wb_ctrl_03);
			}
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get white Balance
 *
 * @param   *pstParams [in/out] LX_PE_CCM_WB_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_GetWhiteBalance(LX_PE_CCM_WB_T *pstParams)
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

				PE_P1L_H13B0_QRd03(pe1_wb_ctrl_01, 	user_ctrl_g_gain,	pstParams->g_gain,\
													user_ctrl_b_gain,	pstParams->b_gain,\
													user_ctrl_r_gain,	pstParams->r_gain);
				PE_P1L_H13B0_QRd03(pe1_wb_ctrl_02, 	user_ctrl_g_offset,	pstParams->g_offset,\
													user_ctrl_b_offset,	pstParams->b_offset,\
													user_ctrl_r_offset,	pstParams->r_offset);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{

				PE_P1L_H13_QRd03(pe1_wb_ctrl_01, 	user_ctrl_g_gain,	pstParams->g_gain,\
													user_ctrl_b_gain,	pstParams->b_gain,\
													user_ctrl_r_gain,	pstParams->r_gain);
				PE_P1L_H13_QRd03(pe1_wb_ctrl_02, 	user_ctrl_g_offset,	pstParams->g_offset,\
													user_ctrl_b_offset,	pstParams->b_offset,\
													user_ctrl_r_offset,	pstParams->r_offset);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_wb_ctrl_01);
				PE_P1L_L9B0_RdFL(pe1_l_wb_ctrl_02);
				PE_P1L_L9B0_Rd01(pe1_l_wb_ctrl_01, user_ctrl_g_gain,	pstParams->g_gain);
				PE_P1L_L9B0_Rd01(pe1_l_wb_ctrl_01, user_ctrl_b_gain,	pstParams->b_gain);
				PE_P1L_L9B0_Rd01(pe1_l_wb_ctrl_01, user_ctrl_r_gain,	pstParams->r_gain);
				PE_P1L_L9B0_Rd01(pe1_l_wb_ctrl_02, user_ctrl_g_offset,	pstParams->g_offset);
				PE_P1L_L9B0_Rd01(pe1_l_wb_ctrl_02, user_ctrl_b_offset,	pstParams->b_offset);
				PE_P1L_L9B0_Rd01(pe1_l_wb_ctrl_02, user_ctrl_r_offset,	pstParams->r_offset);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_wb_ctrl_01);
				PE_P1R_L9B0_RdFL(pe1_r_wb_ctrl_02);
				PE_P1R_L9B0_Rd01(pe1_r_wb_ctrl_01, user_ctrl_g_gain,	pstParams->g_gain);
				PE_P1R_L9B0_Rd01(pe1_r_wb_ctrl_01, user_ctrl_b_gain,	pstParams->b_gain);
				PE_P1R_L9B0_Rd01(pe1_r_wb_ctrl_01, user_ctrl_r_gain,	pstParams->r_gain);
				PE_P1R_L9B0_Rd01(pe1_r_wb_ctrl_02, user_ctrl_g_offset,	pstParams->g_offset);
				PE_P1R_L9B0_Rd01(pe1_r_wb_ctrl_02, user_ctrl_b_offset,	pstParams->b_offset);
				PE_P1R_L9B0_Rd01(pe1_r_wb_ctrl_02, user_ctrl_r_offset,	pstParams->r_offset);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_wb_ctrl_02);
				PE_P1L_L9_RdFL(pe1_l_wb_ctrl_03);
				PE_P1L_L9_Rd01(pe1_l_wb_ctrl_02, user_ctrl_g_gain,		pstParams->g_gain);
				PE_P1L_L9_Rd01(pe1_l_wb_ctrl_02, user_ctrl_b_gain,		pstParams->b_gain);
				PE_P1L_L9_Rd01(pe1_l_wb_ctrl_02, user_ctrl_r_gain,		pstParams->r_gain);
				PE_P1L_L9_Rd01(pe1_l_wb_ctrl_03, user_ctrl_g_offset,	pstParams->g_offset);
				PE_P1L_L9_Rd01(pe1_l_wb_ctrl_03, user_ctrl_b_offset,	pstParams->b_offset);
				PE_P1L_L9_Rd01(pe1_l_wb_ctrl_03, user_ctrl_r_offset,	pstParams->r_offset);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_wb_ctrl_02);
				PE_P1R_L9_RdFL(pe1_r_wb_ctrl_03);
				PE_P1R_L9_Rd01(pe1_r_wb_ctrl_02, user_ctrl_g_gain,		pstParams->g_gain);
				PE_P1R_L9_Rd01(pe1_r_wb_ctrl_02, user_ctrl_b_gain,		pstParams->b_gain);
				PE_P1R_L9_Rd01(pe1_r_wb_ctrl_02, user_ctrl_r_gain,		pstParams->r_gain);
				PE_P1R_L9_Rd01(pe1_r_wb_ctrl_03, user_ctrl_g_offset,	pstParams->g_offset);
				PE_P1R_L9_Rd01(pe1_r_wb_ctrl_03, user_ctrl_b_offset,	pstParams->b_offset);
				PE_P1R_L9_Rd01(pe1_r_wb_ctrl_03, user_ctrl_r_offset,	pstParams->r_offset);
			}
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CCM_DBG_PRINT("get[%d] : gain:%d,%d,%d, offset:%d,%d,%d\n",\
			pstParams->win_id,pstParams->r_gain,pstParams->g_gain,pstParams->b_gain,\
			pstParams->r_offset,pstParams->g_offset,pstParams->b_offset);
	}while(0);
	return ret;
}
/**
 * set auto correction
 *
 * @param   *pstParams [in/out] LX_PE_CCM_AUTO_CR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_SetAutoCorrection(LX_PE_CCM_AUTO_CR_T *pstParams)
{
	int ret = RET_OK;
	PE_CCM_SETTINGS_T *pInfo=&_g_pe_ccm_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CCM_DBG_PRINT("set pstParams : en:%d, max_hist:%d,val_bins:%d, th0,1:%d,%d\n",\
			pstParams->enable,pstParams->th_max_hist,pstParams->th_valid_bins,\
			pstParams->adj_th0,pstParams->adj_th1);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			PE_P1L_H13B0_QWr04(pe1_lrcr_ctrl_01,	th_max_hist,	GET_BITS(pstParams->th_max_hist,0,8),\
													th_valid_bins,	GET_BITS(pstParams->th_valid_bins,0,8),\
													th1,			GET_BITS(pstParams->adj_th1,0,8),\
													th0,			GET_BITS(pstParams->adj_th0,0,8));
			PE_P1L_H13B0_QWr01(pe1_lrcr_ctrl_00,	enable,			pstParams->enable? 0x1:0x0);
			pInfo->auto_cr.enable = pstParams->enable? 0x1:0x0;
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_DPP_H13_QWr04(debd_pp_lrcr_ctrl_01,	th_max_hist,	GET_BITS(pstParams->th_max_hist,0,8),\
													th_valid_bins,	GET_BITS(pstParams->th_valid_bins,0,8),\
													th1,			GET_BITS(pstParams->adj_th1,0,8),\
													th0,			GET_BITS(pstParams->adj_th0,0,8));
			PE_DPP_H13_QWr01(debd_pp_lrcr_ctrl_00,	enable,			pstParams->enable? 0x1:0x0);
			pInfo->auto_cr.enable = pstParams->enable? 0x1:0x0;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_P1L_L9B_QWr04(pe1_l_lrcr_ctrl_01,	th_max_hist,	GET_BITS(pstParams->th_max_hist,0,8),\
													th_valid_bins,	GET_BITS(pstParams->th_valid_bins,0,8),\
													th1,			GET_BITS(pstParams->adj_th1,0,8),\
													th0,			GET_BITS(pstParams->adj_th0,0,8));
			PE_P1L_L9B_QWr01(pe1_l_lrcr_ctrl_00,	enable,			pstParams->enable? 0x1:0x0);
			pInfo->auto_cr.enable = pstParams->enable? 0x1:0x0;
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);

	return ret;
}
/**
 * get auto correction
 *
 * @param   *pstParams [in/out] LX_PE_CCM_AUTO_CR_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_GetAutoCorrection(LX_PE_CCM_AUTO_CR_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			PE_P1L_H13B0_QRd04(pe1_lrcr_ctrl_01,	th_max_hist,	pstParams->th_max_hist,\
													th_valid_bins,	pstParams->th_valid_bins,\
													th1,			pstParams->adj_th1,\
													th0,			pstParams->adj_th0);
			PE_P1L_H13B0_QRd01(pe1_lrcr_ctrl_00,	enable,			pstParams->enable);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_DPP_H13_QRd04(debd_pp_lrcr_ctrl_01,	th_max_hist,	pstParams->th_max_hist,\
													th_valid_bins,	pstParams->th_valid_bins,\
													th1,			pstParams->adj_th1,\
													th0,			pstParams->adj_th0);
			PE_DPP_H13_QRd01(debd_pp_lrcr_ctrl_00,	enable,			pstParams->enable);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_P1L_L9B_QRd04(pe1_l_lrcr_ctrl_01,	th_max_hist,	pstParams->th_max_hist,\
													th_valid_bins,	pstParams->th_valid_bins,\
													th1,			pstParams->adj_th1,\
													th0,			pstParams->adj_th0);
			PE_P1L_L9B_QRd01(pe1_l_lrcr_ctrl_00,	enable,			pstParams->enable);
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CCM_DBG_PRINT("get pstParams : en:%d, max_hist:%d,val_bins:%d, th0,1:%d,%d\n",\
			pstParams->enable,pstParams->th_max_hist,pstParams->th_valid_bins,\
			pstParams->adj_th0,pstParams->adj_th1);
	}while(0);

	return ret;
}
/**
 * set gamma correction lut by register
 *
 * @param   *pstParams [in] LX_PE_CCM_GAMMALUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CCM_SetGammaLutByReg(LX_PE_CCM_GAMMALUT_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count = 0;
	UINT32 lutdata;
	PE_CCM_DBG_PRINT("set[%d] : lut_size:%d\n",pstParams->win_id, pstParams->size);
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_RdFL(pe1_gmc_ia_data);
				PE_P1L_H13B0_QWr01(pe1_gmc_ctrl_02,	gmc_mode,		0x1);//write mode
				PE_P1L_H13B0_QWr02(pe1_gmc_ia_ctrl,	capture_ai,		0x1, //ai mode enble
													capture_addr,	0x0);
				PE_P1L_H13B0_QWr01(pe1_top_ctrl_00,	load_time,		0x1);
				for(count=0;count<pstParams->size;count++)
				{
					lutdata = pstParams->data[count];
					PE_P1L_H13B0_Wr01(pe1_gmc_ia_data,	lut_data_g, GET_BITS(lutdata,  0, 10));
					PE_P1L_H13B0_Wr01(pe1_gmc_ia_data,	lut_data_b, GET_BITS(lutdata, 10, 10));
					PE_P1L_H13B0_Wr01(pe1_gmc_ia_data,	lut_data_r, GET_BITS(lutdata, 20, 10));
					PE_P1L_H13B0_WrFL(pe1_gmc_ia_data);
				}
				PE_P1L_H13B0_QWr01(pe1_gmc_ctrl_01,	gmc_lut_wr_done,		0x1); //set done
				PE_P1L_H13B0_QWr01(pe1_gmc_ctrl_01,	gmc_lut_wr_done,		0x0); //reset done
				PE_P1L_H13B0_QWr01(pe1_top_ctrl_00,	load_time,		0x0);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_RdFL(pe1_gmc_ia_data);
				PE_P1L_H13_QWr01(pe1_gmc_ctrl_02,	gmc_mode,		0x1);//write mode
				PE_P1L_H13_QWr02(pe1_gmc_ia_ctrl,	capture_ai,		0x1, //ai mode enble
													capture_addr,	0x0);
				PE_P1L_H13_QWr01(pe1_top_ctrl_00,	load_time,		0x1);
				for(count=0;count<pstParams->size;count++)
				{
					lutdata = pstParams->data[count];
					PE_P1L_H13_Wr01(pe1_gmc_ia_data,	lut_data_g, GET_BITS(lutdata,  0, 10));
					PE_P1L_H13_Wr01(pe1_gmc_ia_data,	lut_data_b, GET_BITS(lutdata, 10, 10));
					PE_P1L_H13_Wr01(pe1_gmc_ia_data,	lut_data_r, GET_BITS(lutdata, 20, 10));
					PE_P1L_H13_WrFL(pe1_gmc_ia_data);
				}
				PE_P1L_H13_QWr01(pe1_gmc_ctrl_01,	gmc_lut_wr_done,		0x1); //set done
				PE_P1L_H13_QWr01(pe1_gmc_ctrl_01,	gmc_lut_wr_done,		0x0); //reset done
				PE_P1L_H13_QWr01(pe1_top_ctrl_00,	load_time,		0x0);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_HW_L9_SetManualLoadMode(0);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x1);//write mode
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_data);
				PE_P1L_L9B0_RdFL(pe1_l_gmc_ia_ctrl);
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ia_ctrl);
				PE_P1L_L9B0_RdFL(pe1_l_top_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_top_ctrl_00,	load_time,		0x1);
				PE_P1L_L9B0_WrFL(pe1_l_top_ctrl_00);
				for(count=0;count<pstParams->size;count++)
				{
					lutdata = pstParams->data[count];
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_data,	lut_data_g, GET_BITS(lutdata,  0, 10));
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_data,	lut_data_b, GET_BITS(lutdata, 10, 10));
					PE_P1L_L9B0_Wr01(pe1_l_gmc_ia_data,	lut_data_r, GET_BITS(lutdata, 20, 10));
					PE_P1L_L9B0_WrFL(pe1_l_gmc_ia_data);
				}
				PE_P1L_L9B0_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x2);//enable mode
				PE_P1L_L9B0_WrFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9B0_RdFL(pe1_l_top_ctrl_00);
				PE_P1L_L9B0_Wr01(pe1_l_top_ctrl_00,	load_time,		0x0);
				PE_P1L_L9B0_WrFL(pe1_l_top_ctrl_00);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x1);//write mode
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_data);
				PE_P1R_L9B0_RdFL(pe1_r_gmc_ia_ctrl);
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ia_ctrl);
				//msleep(20);
				PE_P1R_L9B0_RdFL(pe1_r_top_ctrl_00);
				PE_P1R_L9B0_Wr01(pe1_r_top_ctrl_00,	load_time,		0x1);
				PE_P1R_L9B0_WrFL(pe1_r_top_ctrl_00);
				for(count=0;count<pstParams->size;count++)
				{
					lutdata = pstParams->data[count];
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_data,	lut_data_g, GET_BITS(lutdata,  0, 10));
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_data,	lut_data_b, GET_BITS(lutdata, 10, 10));
					PE_P1R_L9B0_Wr01(pe1_r_gmc_ia_data,	lut_data_r, GET_BITS(lutdata, 20, 10));
					PE_P1R_L9B0_WrFL(pe1_r_gmc_ia_data);
				}
				PE_P1R_L9B0_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x2);//enable mode
				PE_P1R_L9B0_WrFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9B0_RdFL(pe1_r_top_ctrl_00);
				PE_P1R_L9B0_Wr01(pe1_r_top_ctrl_00,	load_time,		0x0);
				PE_P1R_L9B0_WrFL(pe1_r_top_ctrl_00);
			}
			PE_CMN_HW_L9_SetManualLoadMode(1);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x1);//write mode
				PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9_RdFL(pe1_l_gmc_ia_data);
				PE_P1L_L9_RdFL(pe1_l_gmc_ia_ctrl);
				PE_P1L_L9_Wr01(pe1_l_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode
				PE_P1L_L9_Wr01(pe1_l_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1L_L9_WrFL(pe1_l_gmc_ia_ctrl);
				//msleep(20);
				PE_P1L_L9_RdFL(pe1_l_top_ctrl_00);
				PE_P1L_L9_Wr01(pe1_l_top_ctrl_00,	load_time,		0x1);
				PE_P1L_L9_WrFL(pe1_l_top_ctrl_00);
				for(count=0;count<pstParams->size;count++)
				{
					lutdata = pstParams->data[count];
					PE_P1L_L9_Wr01(pe1_l_gmc_ia_data,	lut_data_g, GET_BITS(lutdata,  0, 10));
					PE_P1L_L9_Wr01(pe1_l_gmc_ia_data,	lut_data_b, GET_BITS(lutdata, 10, 10));
					PE_P1L_L9_Wr01(pe1_l_gmc_ia_data,	lut_data_r, GET_BITS(lutdata, 20, 10));
					PE_P1L_L9_WrFL(pe1_l_gmc_ia_data);
				}
				PE_P1L_L9_Wr01(pe1_l_gmc_ctrl_02,	gmc_mode,		0x2);//enable mode
				PE_P1L_L9_WrFL(pe1_l_gmc_ctrl_02);
				PE_P1L_L9_RdFL(pe1_l_top_ctrl_00);
				PE_P1L_L9_Wr01(pe1_l_top_ctrl_00,	load_time,		0x0);
				PE_P1L_L9_WrFL(pe1_l_top_ctrl_00);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x1);//write mode
				PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9_RdFL(pe1_r_gmc_ia_data);
				PE_P1R_L9_RdFL(pe1_r_gmc_ia_ctrl);
				PE_P1R_L9_Wr01(pe1_r_gmc_ia_ctrl,	capture_ai,		0x1);//ai mode
				PE_P1R_L9_Wr01(pe1_r_gmc_ia_ctrl,	capture_addr,	0x0);
				PE_P1R_L9_WrFL(pe1_r_gmc_ia_ctrl);
				//msleep(20);
				PE_P1R_L9_RdFL(pe1_r_top_ctrl_00);
				PE_P1R_L9_Wr01(pe1_r_top_ctrl_00,	load_time,		0x1);
				PE_P1R_L9_WrFL(pe1_r_top_ctrl_00);
				for(count=0;count<pstParams->size;count++)
				{
					lutdata = pstParams->data[count];
					PE_P1R_L9_Wr01(pe1_r_gmc_ia_data,	lut_data_g, GET_BITS(lutdata,  0, 10));
					PE_P1R_L9_Wr01(pe1_r_gmc_ia_data,	lut_data_b, GET_BITS(lutdata, 10, 10));
					PE_P1R_L9_Wr01(pe1_r_gmc_ia_data,	lut_data_r, GET_BITS(lutdata, 20, 10));
					PE_P1R_L9_WrFL(pe1_r_gmc_ia_data);
				}
				PE_P1R_L9_Wr01(pe1_r_gmc_ctrl_02,	gmc_mode,		0x2);//enable mode
				PE_P1R_L9_WrFL(pe1_r_gmc_ctrl_02);
				PE_P1R_L9_RdFL(pe1_r_top_ctrl_00);
				PE_P1R_L9_Wr01(pe1_r_top_ctrl_00,	load_time,		0x0);
				PE_P1R_L9_WrFL(pe1_r_top_ctrl_00);
			}
		}
		else
		#endif
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get CurCcmSettings
 *
 * @param   *pstParams [in] PE_CCM_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CCM_GetCurCcmSettings(PE_CCM_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	PE_CCM_SETTINGS_T *pInfo=&_g_pe_ccm_info;
	do {
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13 ||PE_KDRV_VER_L9BX)
		{
			memcpy(pstParams,pInfo,sizeof(PE_CCM_SETTINGS_T));
			if(_g_ccm_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_CCM_DBG_PRINT("get pstParams : en:%d, max_hist:%d,val_bins:%d, th0,1:%d,%d\n",\
						pstParams->auto_cr.enable,pstParams->auto_cr.th_max_hist,\
						pstParams->auto_cr.th_valid_bins,\
						pstParams->auto_cr.adj_th0,pstParams->auto_cr.adj_th1);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_CCM_DBG_PRINT("nothing to do.\n");
		}
	} while (0);
	return ret;
}

