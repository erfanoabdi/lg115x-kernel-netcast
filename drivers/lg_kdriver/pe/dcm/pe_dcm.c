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


/** @file pe_dcm.c
 *
 *  driver for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	- dynamic contrast enhancement, histogram information and configuration.
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
#include "pe_win.h"
#include "pe_dcm.h"
#include "pe_etc_hw.h"
#include "pe_dcm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_ERROR	printk

#define PE_DCM_DBG_PRINT(fmt,args...)	\
	if(_g_dcm_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_DCM_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_DCM_ERROR(fmt,##args);_action;}}


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
static int PE_DCM_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_DCM_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_DCM_GetHistogramInfo(LX_PE_DCM_HISTO_INFO_T *pstParams);
static int PE_DCM_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
static int PE_DCM_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
static int PE_DCM_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
static int PE_DCM_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
static int PE_DCM_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
static int PE_DCM_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
static int PE_DCM_SetDceSmoothCtrl(LX_PE_DCM_DCE_SMOOTH_T *pstParams);
static int PE_DCM_GetDceSmoothCtrl(LX_PE_DCM_DCE_SMOOTH_T *pstParams);
static int PE_DCM_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
static int PE_DCM_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
static int PE_DCM_SetHistoConfig(LX_PE_DCM_HISTO_CFG_T *pstParams);
static int PE_DCM_GetHistoConfig(LX_PE_DCM_HISTO_CFG_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dcm_trace=0x0;	//default should be off.

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init dynamic contrast module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_Init();
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_Init() error.\n",__F__,__L__);
			ret = PE_HST_HW_H13_Init();
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_Init();
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of dcm setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_DCM_SET_TABL(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_DCM_DBG_PRINT("S %s\n",#_struct);\
			PE_DCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size,0,16) * sizeof(UINT32);\
			PE_DCM_CHECK_CODE(!bufsize,break,"[%s,%d] bufsize zero.\n",__F__,__L__);\
			p_data = OS_Malloc(bufsize);\
			PE_DCM_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] copy_from_user error.\n",__F__,__L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_DCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
		if(p_data){OS_Free(p_data);}\
	}\
	break

#define PE_DCM_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_DCM_DBG_PRINT("S %s\n",#_struct);\
			PE_DCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_DCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

/* set func without start,end print(WOPT:WithOut PRint) because of too many prints */
#define PE_DCM_SET_WOPR(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_DCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_DCM_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_DCM_SET_WOPR(LX_PE_DCM_DCE_LUT_T,		PE_DCM_SetDceLut);
		PE_DCM_SET_WOPR(LX_PE_DCM_DSE_LUT_T,		PE_DCM_SetDseLut);
		PE_DCM_SET_FUNC(LX_PE_DCM_DCE_CONF_T,		PE_DCM_SetDceConfig);
		PE_DCM_SET_FUNC(LX_PE_DCM_BLENDING_T,		PE_DCM_SetDceBlendingCtrl);
		PE_DCM_SET_FUNC(LX_PE_DCM_HISTO_CFG_T,		PE_DCM_SetHistoConfig);
		PE_DCM_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_DCM_SetDefaultSettings);
		PE_DCM_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_DCM_SetDebugSettings);
		PE_DCM_SET_FUNC(LX_PE_DCM_DCE_SMOOTH_T,		PE_DCM_SetDceSmoothCtrl);

		default:
		{
			PE_DCM_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of dcm getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DCM_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_DCM_GET_TABL(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_DCM_DBG_PRINT("S %s\n",#_struct);\
			PE_DCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size,0,16) * sizeof(UINT32);\
			PE_DCM_CHECK_CODE(!bufsize,break,"[%s,%d] bufsize zero.\n",__F__,__L__);\
			p_data = OS_Malloc(bufsize);\
			PE_DCM_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);\
			param.win_id = p_rcv->win_id;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] copy_to_user error.\n",__F__,__L__);\
			PE_DCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
		if(p_data){OS_Free(p_data);}\
	}\
	break

#define PE_DCM_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_DCM_DBG_PRINT("S %s\n",#_struct);\
			PE_DCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_DCM_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

/* get func without start,end print(WOPT:WithOut PRint) because of too many prints */
#define PE_DCM_GET_WOPR(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_DCM_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_DCM_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_DCM_GET_WOPR(LX_PE_DCM_HISTO_INFO_T,		PE_DCM_GetHistogramInfo);
		PE_DCM_GET_FUNC(LX_PE_DCM_DCE_CONF_T,		PE_DCM_GetDceConfig);
		PE_DCM_GET_FUNC(LX_PE_DCM_BLENDING_T,		PE_DCM_GetDceBlendingCtrl);
		PE_DCM_GET_FUNC(LX_PE_DCM_HISTO_CFG_T,		PE_DCM_GetHistoConfig);
		PE_DCM_GET_TABL(LX_PE_DCM_DCE_LUT_T,		PE_DCM_GetDceLut);
		PE_DCM_GET_TABL(LX_PE_DCM_DSE_LUT_T,		PE_DCM_GetDseLut);
		PE_DCM_GET_FUNC(LX_PE_DCM_DCE_SMOOTH_T,		PE_DCM_GetDceSmoothCtrl);
		default:
		{
			PE_DCM_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
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
static int PE_DCM_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
	}while(0);
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
static int PE_DCM_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DCM_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(DCM)),\
			pstParams->print_lvl,pstParams->bypass);

		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_dcm_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(DCM)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_DCM_HW_H13_SetDbgPrint(_g_dcm_trace);
			if(PE_KDRV_VER_H13)	PE_HST_HW_H13_SetDbgPrint(_g_dcm_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_DCM_HW_L9_SetDbgPrint(_g_dcm_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DCM)))
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13B0_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
				}
				else
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13B0_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
				}
			}
		
			else if(PE_KDRV_VER_H13AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DCM)))
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
				}
				else
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13_QWr01(pe1_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
				}
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DCM)))
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B0_Wr01(pe1_l_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
				}
				else
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
				}
			}
			else if(PE_KDRV_VER_L9AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(DCM)))
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9A_QWr01(pe1_l_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9A_QWr01(pe1_r_dce_ctrl_00,	dynamic_contrast_en,	0x0);
					}
				}
				else
				{
					PE_DCM_DBG_PRINT("dynamic_contrast_en : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9A_QWr01(pe1_l_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9A_QWr01(pe1_r_dce_ctrl_00,	dynamic_contrast_en,	0x1);
					}
				}
			}
			else
			#endif
			{
				PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * get dce histogram info
 *
 * @param   *pstParams [in/out] LX_PE_DCM_HISTO_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetHistogramInfo(LX_PE_DCM_HISTO_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_GetHistogramInfo(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_GetHistogramInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_GetHistogramInfo(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_GetHistogramInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * set dce config
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_CONF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_SetDceConfig(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_SetDceConfig() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_SetDceConfig(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_SetDceConfig() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get dce config
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_CONF_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_GetDceConfig(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_GetDceConfig() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_GetDceConfig(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_GetDceConfig() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set dce lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_SetDceLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_SetDceLut() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_SetDceLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_SetDceLut() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
/**
 * get dce lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DCE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_GetDceLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_GetDceLut() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_GetDceLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_GetDceLut() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
/**
 * set dse lut
 *
 * @param   *pstParams [in] LX_PE_DCM_DSE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_SetDseLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_SetDseLut() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_SetDseLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_SetDseLut() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
/**
 * get dse lut
 *
 * @param   *pstParams [in/out] LX_PE_DCM_DSE_LUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_GetDseLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_GetDseLut() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_GetDseLut(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_GetDseLut() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}
/**
 * set dce blur
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_SMOOTH_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_SetDceSmoothCtrl(LX_PE_DCM_DCE_SMOOTH_T *pstParams)
{
	int ret = RET_OK;
	do {
			CHECK_KNULL(pstParams);
			//#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13BX)
			{
				if(PE_CHECK_WIN0(pstParams->win_id))
				{
					PE_P1L_H13B0_QWr02(pe1_dce_blur_ctrl_00, avg_filter_tap,	GET_BITS(pstParams->avg_filter_tap,0,2),\
															 edge_map_tap,		GET_BITS(pstParams->edge_map_tap,0,2));
					PE_P1L_H13B0_QWr04(pe1_dce_blur_ctrl_01, e_to_w_th_x0,		GET_BITS(pstParams->e_to_w_th_x0,0,8),\
															 e_to_w_th_x1,		GET_BITS(pstParams->e_to_w_th_x1,0,8),\
															 e_to_w_th_y0,		GET_BITS(pstParams->e_to_w_th_y0,0,8),\
															 e_to_w_th_y1,		GET_BITS(pstParams->e_to_w_th_y1,0,8));
					PE_P1L_H13B0_QWr01(pe1_dce_blur_ctrl_02, chroma_blur_mode, 	GET_BITS(pstParams->chroma_blur_mode,0,2));
					PE_P1L_H13B0_QWr01(pe1_dce_ctrl_01,		 blur_v_gain, 	 	GET_BITS(pstParams->blur_v_gain,0,4));
					
				}
			}
			else
			//#endif
			{
				PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
			}
	} while (0);
	return ret;
}
/**
 * get dce blur
 *
 * @param   *pstParams [in] LX_PE_DCM_DCE_SMOOTH_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetDceSmoothCtrl(LX_PE_DCM_DCE_SMOOTH_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QRd02(pe1_dce_blur_ctrl_00, avg_filter_tap,	pstParams->avg_filter_tap,\
														 edge_map_tap,		pstParams->edge_map_tap);
				PE_P1L_H13B0_QRd04(pe1_dce_blur_ctrl_01, e_to_w_th_x0,		pstParams->e_to_w_th_x0,\
														 e_to_w_th_x1,		pstParams->e_to_w_th_x1,\
														 e_to_w_th_y0,		pstParams->e_to_w_th_y0,\
														 e_to_w_th_y1,		pstParams->e_to_w_th_y1);
				PE_P1L_H13B0_QRd01(pe1_dce_blur_ctrl_02, chroma_blur_mode, 	pstParams->chroma_blur_mode);
				PE_P1L_H13B0_QRd01(pe1_dce_ctrl_01,		 blur_v_gain, 	 	pstParams->blur_v_gain);
				
			}
			if(_g_dcm_trace)
			{
				PE_DCM_DBG_PRINT("get pstParams : filter_tap:%d, map_tap:%d\n"\
					"e_to_w_th_x0,1:%d,%d, e_to_w_th_y0,1:%d,%d\n""chroma_mode:%d, blur_v_gain:%d\n",\
					pstParams->avg_filter_tap,pstParams->edge_map_tap,\
					pstParams->e_to_w_th_x0,pstParams->e_to_w_th_x1,\
					pstParams->e_to_w_th_y0,pstParams->e_to_w_th_y1,\
					pstParams->chroma_blur_mode,pstParams->blur_v_gain);
			}
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);	
	return ret;
}

/**
 * set dce blending control
 *
 * @param   *pstParams [in] LX_PE_DCM_BLENDING_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_SetDceBlendingCtrl(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_SetDceBlendingCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_SetDceBlendingCtrl(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_SetDceBlendingCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do.\n");
		}
	} while (0);	
	return ret;
}
/**
 * get dce blending control
 *
 * @param   *pstParams [in/out] LX_PE_DCM_BLENDING_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_DCM_HW_H13_GetDceBlendingCtrl(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_H13_GetDceBlendingCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_DCM_HW_L9_GetDceBlendingCtrl(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_L9_GetDceBlendingCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do.\n");
		}
		PE_DCM_DBG_PRINT("get pstParams[%d] : color_out_gain:%d\n",pstParams->win_id,pstParams->color_out_gain);
		if(_g_dcm_trace)
		{
			UINT32 i,sel;
			for(i=0;i<16;i++)
			{
				sel = ((pstParams->region_sel>>i)&0x1);
				PE_DCM_DBG_PRINT("[%2d]%d\n",i,sel);
			}
		}
	} while (0);	
	return ret;
}
/**
 * set histogram config
 *
 * @param   *pstParams [in] LX_PE_DCM_HISTO_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_SetHistoConfig(LX_PE_DCM_HISTO_CFG_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_HST_HW_H13_SetHistoConfig(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_SetHistoConfig() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get histogram config
 *
 * @param   *pstParams [in/out] LX_PE_DCM_HISTO_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DCM_GetHistoConfig(LX_PE_DCM_HISTO_CFG_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_HST_HW_H13_GetHistoConfig(pstParams);
			PE_DCM_CHECK_CODE(ret,break,"[%s,%d] PE_HST_HW_H13_GetHistoConfig() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_DCM_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}

