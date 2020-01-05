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


/** @file pe_nrd.c
 *
 *  driver for picture enhance noise reduction functions. ( used only within kdriver )
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
#include "pe_spd.h"
#include "pe_etc.h"
#include "pe_cmn.h"
#include "pe_nrd.h"
#include "pe_etc_hw.h"
#include "pe_nrd_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_ERROR	printk

#define PE_NRD_DBG_PRINT(fmt,args...)	\
	if(_g_nrd_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_NRD_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_NRD_ERROR(fmt,##args);_action;}}

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
static int PE_NRD_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_NRD_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_NRD_SetDnrCmnCtrl(void *pstParams);
static int PE_NRD_GetDnrCmnCtrl(void *pstParams);
static int PE_NRD_SetDnrDetailCtrl(void *pstParams);
static int PE_NRD_GetDnrDetailCtrl(void *pstParams);
static int PE_NRD_SetTnrCmnCtrl(void *pstParams);
static int PE_NRD_GetTnrCmnCtrl(void *pstParams);
static int PE_NRD_SetTnrDetailCtrl(void *pstParams);
static int PE_NRD_GetTnrDetailCtrl(void *pstParams);
static int PE_NRD_SetTnrColorRgnCtrl(LX_PE_NRD_TNR_CRGN_T *pstParams);
static int PE_NRD_GetTnrColorRgnCtrl(LX_PE_NRD_TNR_CRGN_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_nrd_trace=0x0;	//default should be off.

/*----------------------------------------------------------------------------------------
	Implementation Group
----------------------------------------------------------------------------------------*/

/**
 * init nrd init
 * 	- h13,l9 tnr alpha lut loading sequence
 *		: load time on -> tnr off -> loading alpha lut -> tnr on -> load time off
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_NRD_HW_H13_Init();
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_NRD_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_NRD_HW_L9_Init();
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_NRD_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of nrd setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_NRD_SET_FUNC(_struct,_func,_void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_NRD_DBG_PRINT("S %s\n",#_struct);\
			PE_NRD_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_NRD_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_NRD_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR0_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR0_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR1_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR1_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR1_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR1_DETAIL_T,	PE_NRD_SetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR2_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR2_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR2_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR2_DETAIL_T,	PE_NRD_SetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR_CRGN_T,		PE_NRD_SetTnrColorRgnCtrl,	_STRUCT_INPUT_);
		PE_NRD_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_NRD_SetDefaultSettings,	_STRUCT_INPUT_);
		PE_NRD_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_NRD_SetDebugSettings,	_STRUCT_INPUT_);
		default:
		{
			PE_NRD_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of nrd getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_NRD_GET_FUNC(_struct,_func,_void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_NRD_DBG_PRINT("S %s\n",#_struct);\
			PE_NRD_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_NRD_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_NRD_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR0_CMN_T,	PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR0_CMN_T,	PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR1_CMN_T,	PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR1_DETAIL_T,PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR1_CMN_T,	PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR1_DETAIL_T,PE_NRD_GetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR2_CMN_T,	PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR2_DETAIL_T,PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR2_CMN_T,	PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR2_DETAIL_T,PE_NRD_GetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR_CRGN_T,	PE_NRD_GetTnrColorRgnCtrl,	_STRUCT_INPUT_);
		default:
		{
			PE_NRD_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
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
static int PE_NRD_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_NRD_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_NRD_HW_H13_SetDefault(pstParams);
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_NRD_HW_H13_SetDefault() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_NRD_HW_L9_SetDefault(pstParams);
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_NRD_HW_L9_SetDefault() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
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
static int PE_NRD_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_NRD_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(NRD)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_nrd_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(NRD)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_NRD_HW_H13_SetDbgPrint(_g_nrd_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_NRD_HW_L9_SetDbgPrint(_g_nrd_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(NRD)))
				{
					PE_NRD_DBG_PRINT("tnr,dnr : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_H13B0_QWr01(p0l_tnr_ctrl_00,	tnr_enable, 	0x0);
						PE_P0L_H13B0_QWr03(p0l_dnr_max_ctrl,enable_mnr, 	0x0,\
															enable_dc_bnr, 	0x0,\
															enable_ac_bnr, 	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_H13B0_QWr01(p0r_tnr_ctrl_00,	tnr_enable, 	0x0);
						PE_P0R_H13B0_QWr03(p0r_dnr_max_ctrl,enable_mnr, 	0x0,\
															enable_dc_bnr, 	0x0,\
															enable_ac_bnr, 	0x0);
					}
				}
				else
				{
					PE_NRD_DBG_PRINT("tnr,dnr : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_H13B0_QWr01(p0l_tnr_ctrl_00,	tnr_enable, 	0x1);
						PE_P0L_H13B0_QWr03(p0l_dnr_max_ctrl,enable_mnr, 	0x1,\
															enable_dc_bnr, 	0x1,\
															enable_ac_bnr, 	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_H13B0_QWr01(p0r_tnr_ctrl_00,	tnr_enable, 	0x1);
						PE_P0R_H13B0_QWr03(p0r_dnr_max_ctrl,enable_mnr, 	0x1,\
															enable_dc_bnr, 	0x1,\
															enable_ac_bnr, 	0x1);
					}
				}
			}
			else if(PE_KDRV_VER_H13AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(NRD)))
				{
					PE_NRD_DBG_PRINT("tnr,dnr : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_H13_QWr01(p0l_tnr_ctrl_00,	tnr_enable, 	0x0);
						PE_P0L_H13_QWr04(p0l_dnr_max_ctrl,	enable_snr, 	0x0,\
															enable_mnr, 	0x0,\
															enable_dc_bnr, 	0x0,\
															enable_ac_bnr, 	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_H13_QWr01(p0r_tnr_ctrl_00,	tnr_enable, 	0x0);
						PE_P0R_H13_QWr04(p0r_dnr_max_ctrl,	enable_snr, 	0x0,\
															enable_mnr, 	0x0,\
															enable_dc_bnr, 	0x0,\
															enable_ac_bnr, 	0x0);
					}
				}
				else
				{
					PE_NRD_DBG_PRINT("tnr,dnr : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_H13_QWr01(p0l_tnr_ctrl_00,	tnr_enable, 	0x1);
						PE_P0L_H13_QWr04(p0l_dnr_max_ctrl,	enable_snr, 	0x1,\
															enable_mnr, 	0x1,\
															enable_dc_bnr, 	0x1,\
															enable_ac_bnr, 	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_H13_QWr01(p0r_tnr_ctrl_00,	tnr_enable, 	0x1);
						PE_P0R_H13_QWr04(p0r_dnr_max_ctrl,	enable_snr, 	0x1,\
															enable_mnr, 	0x1,\
															enable_dc_bnr, 	0x1,\
															enable_ac_bnr, 	0x1);
					}
				}
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(NRD)))
				{
					PE_NRD_DBG_PRINT("tnr,dnr : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9B_QWr01(tnr_ctrl_00,	tnr_enable, 	0x0);
						PE_P0L_L9B_QWr04(dnr_max_ctrl,	enable_snr, 	0x0,\
														enable_mnr, 	0x0,\
														enable_dc_bnr, 	0x0,\
														enable_ac_bnr, 	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9B_QWr01(tnr_ctrl_00,	tnr_enable, 	0x0);
						PE_P0R_L9B_QWr04(dnr_max_ctrl,	enable_snr, 	0x0,\
														enable_mnr, 	0x0,\
														enable_dc_bnr, 	0x0,\
														enable_ac_bnr, 	0x0);
					}
				}
				else
				{
					PE_NRD_DBG_PRINT("tnr,dnr : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9B_QWr01(tnr_ctrl_00,	tnr_enable, 	0x1);
						PE_P0L_L9B_QWr04(dnr_max_ctrl,	enable_snr, 	0x1,\
														enable_mnr, 	0x1,\
														enable_dc_bnr, 	0x1,\
														enable_ac_bnr, 	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9B_QWr01(tnr_ctrl_00,	tnr_enable, 	0x1);
						PE_P0R_L9B_QWr04(dnr_max_ctrl,	enable_snr, 	0x1,\
														enable_mnr, 	0x1,\
														enable_dc_bnr, 	0x1,\
														enable_ac_bnr, 	0x1);
					}
				}
			}
			else if(PE_KDRV_VER_L9AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(NRD)))
				{
					PE_NRD_DBG_PRINT("tnr,bnr(h,v),mnr,dc bnr,snr : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9A_QWr01(p0l_tnr_ctrl_00,		tnr_enable, 	0x0);
						PE_P0L_L9A_QWr02(p0l_bnr_ac_ctrl_00,	bnr_h_en, 		0x0,\
																bnr_v_en, 		0x0);
						PE_P0L_L9A_QWr01(p0l_mnr_ctrl_00,		mnr_enable, 	0x0);
						PE_P0L_L9A_QWr01(p0l_bnr_dc_ctrl_00,	dc_bnr_enable, 	0x0);
						PE_P0L_L9A_QWr01(p0l_snr_ctrl_00,		snr_enable, 	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9A_QWr01(p0r_tnr_ctrl_00,		tnr_enable, 	0x0);
						PE_P0R_L9A_QWr02(p0r_bnr_ac_ctrl_00,	bnr_h_en, 		0x0,\
																bnr_v_en, 		0x0);
						PE_P0R_L9A_QWr01(p0r_mnr_ctrl_00,		mnr_enable, 	0x0);
						PE_P0R_L9A_QWr01(p0r_bnr_dc_ctrl_00,	dc_bnr_enable, 	0x0);
						PE_P0R_L9A_QWr01(p0r_snr_ctrl_00,		snr_enable, 	0x0);
					}
				}
				else
				{
					PE_NRD_DBG_PRINT("tnr,bnr(h,v),mnr : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P0L_L9A_QWr01(p0l_tnr_ctrl_00,		tnr_enable, 	0x1);
						PE_P0L_L9A_QWr02(p0l_bnr_ac_ctrl_00,	bnr_h_en, 		0x1,\
																bnr_v_en, 		0x1);
						PE_P0L_L9A_QWr01(p0l_mnr_ctrl_00,		mnr_enable, 	0x1);
						PE_P0L_L9A_QWr01(p0l_bnr_dc_ctrl_00,	dc_bnr_enable, 	0x0);
						PE_P0L_L9A_QWr01(p0l_snr_ctrl_00,		snr_enable, 	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P0R_L9A_QWr01(p0r_tnr_ctrl_00,		tnr_enable, 	0x1);
						PE_P0R_L9A_QWr02(p0r_bnr_ac_ctrl_00,	bnr_h_en, 		0x1,\
																bnr_v_en, 		0x1);
						PE_P0R_L9A_QWr01(p0r_mnr_ctrl_00,		mnr_enable, 	0x1);
						PE_P0R_L9A_QWr01(p0r_bnr_dc_ctrl_00,	dc_bnr_enable, 	0x0);
						PE_P0R_L9A_QWr01(p0r_snr_ctrl_00,		snr_enable, 	0x0);
					}
				}
			}
			else
			#endif
			{
				PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * set dnr common ctrl
 * - use input struct LX_PE_NRD_DNR2_CMN_T for H13BX
 * - use input struct LX_PE_NRD_DNR1_CMN_T for L9BX
 * - use input struct LX_PE_NRD_DNR0_CMN_T for L9AX,H13AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_SetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_DNR2_CMN_T *pp=(LX_PE_NRD_DNR2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : dnr main : en: ac:%d, mnr:%d, dc:%d\n"\
				"mnr : en:%d, master_gain%d, chroma_gain:%d,h_gain:%d, v_gain:%d\n"\
				"ac_bnr: h,v_en:%d,%d,  mo_max,min:%d,%d,  h,v_bmax:%d,%d,  str_h,v_max:%d,%d\n"\
				"dc_bnr: en:%d,master_gain%d, chroma_gain:%d\n",pp->win_id,\
				/* dnr main */
				pp->enable_mnr,pp->enable_ac_bnr,pp->enable_dc_bnr,\
				/* mnr */
				pp->reg_mnr_enable,pp->reg_mnr_master_gain,pp->reg_chroma_master_gain,pp->reg_mnr_h_gain,pp->reg_mnr_v_gain,\
				/* ac */
				pp->bnr_h_en,pp->bnr_v_en,pp->ac_bnr_protect_motion_max,pp->ac_bnr_protect_motion_min,\
				pp->hbmax_gain,pp->vbmax_gain,pp->strength_h_max,pp->strength_v_max,\
				/* dc */
				pp->reg_dc_bnr_enable,pp->reg_dc_bnr_mastergain,pp->reg_dc_bnr_chromagain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_H13B0_QWr03(p0l_dnr_max_ctrl,	enable_ac_bnr,			GET_BITS(pp->enable_ac_bnr,0,1),\
														enable_mnr,				GET_BITS(pp->enable_mnr,0,1),\
														enable_dc_bnr,			GET_BITS(pp->enable_dc_bnr,0,1));
				PE_P0L_H13B0_QWr03(p0l_mnr_ctrl_00,		reg_mnr_enable,			GET_BITS(pp->reg_mnr_enable,0,1),\
														reg_mnr_master_gain,	GET_BITS(pp->reg_mnr_master_gain,0,8),\
														reg_chroma_master_gain,	GET_BITS(pp->reg_chroma_master_gain,0,8));
				PE_P0L_H13B0_QWr02(p0l_mnr_ctrl_02,		reg_mnr_h_gain,			GET_BITS(pp->reg_mnr_h_gain,0,8),\
														reg_mnr_v_gain,			GET_BITS(pp->reg_mnr_v_gain,0,8));				
				PE_P0L_H13B0_QWr04(p0l_bnr_ac_ctrl_00,	reg_bnr_ac_h_en,		GET_BITS(pp->bnr_h_en,0,1),\
														reg_bnr_ac_v_en,		GET_BITS(pp->bnr_v_en,0,1),\
														reg_bnr_ac_gain_h_max,	GET_BITS(pp->hbmax_gain,0,4),\
														reg_bnr_ac_gain_v_max,	GET_BITS(pp->vbmax_gain,0,4));
				PE_P0L_H13B0_QWr02(p0l_bnr_ac_ctrl_06,	ac_bnr_protect_motion_max,	GET_BITS(pp->ac_bnr_protect_motion_max,0,8),\
														ac_bnr_protect_motion_min,	GET_BITS(pp->ac_bnr_protect_motion_min,0,8));
				PE_P0L_H13B0_QWr01(p0l_bnr_ac_ctrl_01,	strength_h_max,			GET_BITS(pp->strength_h_max,0,8));
				PE_P0L_H13B0_QWr01(p0l_bnr_ac_ctrl_02,	strength_v_max,			GET_BITS(pp->strength_v_max,0,8));				
				PE_P0L_H13B0_QWr03(p0l_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		GET_BITS(pp->reg_dc_bnr_enable,0,1),\
														reg_dc_bnr_mastergain,	GET_BITS(pp->reg_dc_bnr_mastergain,0,8),\
														reg_dc_bnr_chromagain,	GET_BITS(pp->reg_dc_bnr_chromagain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_H13B0_QWr03(p0r_dnr_max_ctrl,	enable_ac_bnr,			GET_BITS(pp->enable_ac_bnr,0,1),\
														enable_mnr,				GET_BITS(pp->enable_mnr,0,1),\
														enable_dc_bnr,			GET_BITS(pp->enable_dc_bnr,0,1));
				PE_P0R_H13B0_QWr03(p0r_mnr_ctrl_00,		reg_mnr_enable,			GET_BITS(pp->reg_mnr_enable,0,1),\
														reg_mnr_master_gain,	GET_BITS(pp->reg_mnr_master_gain,0,8),\
														reg_chroma_master_gain,	GET_BITS(pp->reg_chroma_master_gain,0,8));
				PE_P0R_H13B0_QWr02(p0r_mnr_ctrl_02,		reg_mnr_h_gain,			GET_BITS(pp->reg_mnr_h_gain,0,8),\
														reg_mnr_v_gain,			GET_BITS(pp->reg_mnr_v_gain,0,8));				
				PE_P0R_H13B0_QWr04(p0r_bnr_ac_ctrl_00,	reg_bnr_ac_h_en,		GET_BITS(pp->bnr_h_en,0,1),\
														reg_bnr_ac_v_en,		GET_BITS(pp->bnr_v_en,0,1),\
														reg_bnr_ac_gain_h_max,	GET_BITS(pp->hbmax_gain,0,4),\
														reg_bnr_ac_gain_v_max,	GET_BITS(pp->vbmax_gain,0,4));
				PE_P0R_H13B0_QWr02(p0r_bnr_ac_ctrl_06,	ac_bnr_protect_motion_max,	GET_BITS(pp->ac_bnr_protect_motion_max,0,8),\
														ac_bnr_protect_motion_min,	GET_BITS(pp->ac_bnr_protect_motion_min,0,8));
				PE_P0R_H13B0_QWr01(p0r_bnr_ac_ctrl_01,	strength_h_max,			GET_BITS(pp->strength_h_max,0,8));
				PE_P0R_H13B0_QWr01(p0r_bnr_ac_ctrl_02,	strength_v_max,			GET_BITS(pp->strength_v_max,0,8));				
				PE_P0R_H13B0_QWr03(p0r_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		GET_BITS(pp->reg_dc_bnr_enable,0,1),\
														reg_dc_bnr_mastergain,	GET_BITS(pp->reg_dc_bnr_mastergain,0,8),\
														reg_dc_bnr_chromagain,	GET_BITS(pp->reg_dc_bnr_chromagain,0,8));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			UINT32 ac_bnr_h_gain,ac_bnr_v_gain;
			LX_PE_NRD_DNR0_CMN_T *pp=(LX_PE_NRD_DNR0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : en:m:%d,a:%d,%d,d:%d, gain:m:%d,a:%d,%d,d:%d\n",pp->win_id,\
				pp->mnr_enable,pp->ac_bnr_h_en,pp->ac_bnr_v_en,pp->dc_bnr_en,\
				pp->mnr_gain,pp->ac_bnr_h_gain,pp->ac_bnr_h_gain,pp->dc_bnr_gain);
			ac_bnr_h_gain = (GET_BITS(pp->ac_bnr_h_gain,0,8)>0x80)? 0x80:GET_BITS(pp->ac_bnr_h_gain,0,8);
			ac_bnr_v_gain = (GET_BITS(pp->ac_bnr_v_gain,0,8)>0x80)? 0x80:GET_BITS(pp->ac_bnr_v_gain,0,8);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_H13_QWr02(p0l_mnr_ctrl_00,		reg_mnr_enable, 		(pp->mnr_enable)? 0x1:0x0,\
														reg_mnr_master_gain,	GET_BITS(pp->mnr_gain,0,8));
				PE_P0L_H13_QWr02(p0l_bnr_ac_ctrl_00,	bnr_h_en,	 			(pp->ac_bnr_h_en)? 0x1:0x0,\
														bnr_v_en,				(pp->ac_bnr_v_en)? 0x1:0x0);
				PE_P0L_H13_QWr01(p0l_bnr_ac_ctrl_01,	strength_h_max,			ac_bnr_h_gain);
				PE_P0L_H13_QWr01(p0l_bnr_ac_ctrl_02,	strength_v_max,			ac_bnr_v_gain);
				PE_P0L_H13_QWr02(p0l_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		(pp->dc_bnr_en)? 0x1:0x0,\
														reg_dc_bnr_mastergain,	GET_BITS(pp->dc_bnr_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_H13_QWr02(p0r_mnr_ctrl_00,		reg_mnr_enable, 		(pp->mnr_enable)? 0x1:0x0,\
														reg_mnr_master_gain,	GET_BITS(pp->mnr_gain,0,8));
				PE_P0R_H13_QWr02(p0r_bnr_ac_ctrl_00,	bnr_h_en,	 			(pp->ac_bnr_h_en)? 0x1:0x0,\
														bnr_v_en,				(pp->ac_bnr_v_en)? 0x1:0x0);
				PE_P0R_H13_QWr01(p0r_bnr_ac_ctrl_01,	strength_h_max,			ac_bnr_h_gain);
				PE_P0R_H13_QWr01(p0r_bnr_ac_ctrl_02,	strength_v_max,			ac_bnr_v_gain);
				PE_P0R_H13_QWr02(p0r_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		(pp->dc_bnr_en)? 0x1:0x0,\
														reg_dc_bnr_mastergain,	GET_BITS(pp->dc_bnr_gain,0,8));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_NRD_DNR1_CMN_T *pp=(LX_PE_NRD_DNR1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : mnr : en:%d, flt_th:%d\n"\
				"ac_bnr: h,v_en:%d,%d,  mo_max,min:%d,%d,  h,v_bmax:%d,%d,  str_h,v_max:%d,%d\n"\
				"dc_bnr: en:%d,  mo_min,max:%d,%d, ac_blki_multi:%d\n",\
				pp->win_id,pp->mnr_enable,pp->filter_threshold,\
				pp->bnr_h_en,pp->bnr_v_en,pp->ac_bnr_protect_motion_max,\
				pp->ac_bnr_protect_motion_min,pp->hbmax_gain,pp->vbmax_gain,\
				pp->strength_h_max,pp->strength_v_max,\
				pp->dc_bnr_enable,pp->motion_min,pp->motion_max,\
				pp->ac_blockiness_multifly);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_L9B_QWr01(mnr_ctrl_00,	mnr_enable,			GET_BITS(pp->mnr_enable,0,1));
				PE_P0L_L9B_QWr01(mnr_ctrl_05,	filter_threshold,	GET_BITS(pp->filter_threshold,0,8));
				PE_P0L_L9B_QWr04(bnr_ac_ctrl_00,bnr_h_en,			GET_BITS(pp->bnr_h_en,0,1),\
												bnr_v_en,			GET_BITS(pp->bnr_v_en,0,1),\
												hbmax_gain,			GET_BITS(pp->hbmax_gain,0,4),\
												vbmax_gain,			GET_BITS(pp->vbmax_gain,0,4));
				PE_P0L_L9B_QWr01(bnr_ac_ctrl_01,strength_h_max,		GET_BITS(pp->strength_h_max,0,8));
				PE_P0L_L9B_QWr01(bnr_ac_ctrl_02,strength_v_max,		GET_BITS(pp->strength_v_max,0,8));
				PE_P0L_L9B_QWr02(bnr_ac_ctrl_06,ac_bnr_protect_motion_max,	GET_BITS(pp->ac_bnr_protect_motion_max,0,8),\
												ac_bnr_protect_motion_min,	GET_BITS(pp->ac_bnr_protect_motion_min,0,8));
				PE_P0L_L9B_QWr03(bnr_dc_ctrl_00,dc_bnr_enable,		GET_BITS(pp->dc_bnr_enable,0,1),\
												motion_min,			GET_BITS(pp->motion_min,0,4),\
												motion_max,			GET_BITS(pp->motion_max,0,4));
				PE_P0L_L9B_QWr01(bnr_dc_ctrl_01,ac_blockiness_multifly_x_n,GET_BITS(pp->ac_blockiness_multifly,0,4));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_L9B_QWr01(mnr_ctrl_00,	mnr_enable,			GET_BITS(pp->mnr_enable,0,1));
				PE_P0R_L9B_QWr01(mnr_ctrl_05,	filter_threshold,	GET_BITS(pp->filter_threshold,0,8));
				PE_P0R_L9B_QWr04(bnr_ac_ctrl_00,bnr_h_en,			GET_BITS(pp->bnr_h_en,0,1),\
												bnr_v_en,			GET_BITS(pp->bnr_v_en,0,1),\
												hbmax_gain,			GET_BITS(pp->hbmax_gain,0,4),\
												vbmax_gain,			GET_BITS(pp->vbmax_gain,0,4));
				PE_P0R_L9B_QWr01(bnr_ac_ctrl_01,strength_h_max,		GET_BITS(pp->strength_h_max,0,8));
				PE_P0R_L9B_QWr01(bnr_ac_ctrl_02,strength_v_max,		GET_BITS(pp->strength_v_max,0,8));
				PE_P0R_L9B_QWr02(bnr_ac_ctrl_06,ac_bnr_protect_motion_max,	GET_BITS(pp->ac_bnr_protect_motion_max,0,8),\
												ac_bnr_protect_motion_min,	GET_BITS(pp->ac_bnr_protect_motion_min,0,8));
				PE_P0R_L9B_QWr03(bnr_dc_ctrl_00,dc_bnr_enable,		GET_BITS(pp->dc_bnr_enable,0,1),\
												motion_min,			GET_BITS(pp->motion_min,0,4),\
												motion_max,			GET_BITS(pp->motion_max,0,4));
				PE_P0R_L9B_QWr01(bnr_dc_ctrl_01,ac_blockiness_multifly_x_n,GET_BITS(pp->ac_blockiness_multifly,0,4));
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_NRD_DNR0_CMN_T *pp=(LX_PE_NRD_DNR0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : %d,%d,%d,%d,%d,%d\n",pp->win_id,\
				pp->mnr_enable,pp->ac_bnr_h_en,pp->ac_bnr_v_en,\
				pp->ac_bnr_h_gain,pp->dc_bnr_gain,pp->mnr_gain);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_L9A_QWr01(p0l_mnr_ctrl_00,		mnr_enable, 		(pp->mnr_enable)? 0x1:0x0);
				PE_P0L_L9A_QWr02(p0l_bnr_ac_ctrl_00,	bnr_h_en, 			(pp->ac_bnr_h_en)? 0x1:0x0,\
														bnr_v_en, 			(pp->ac_bnr_v_en)? 0x1:0x0);
				PE_P0L_L9A_QWr01(p0l_bnr_ac_ctrl_01, 	strength_h_max, 	GET_BITS(pp->ac_bnr_h_gain,0,8));
				PE_P0L_L9A_QWr01(p0l_bnr_dc_ctrl_00, 	gain, 				GET_BITS(pp->dc_bnr_gain,0,8));
				PE_P0L_L9A_QWr01(p0l_mnr_ctrl_05, 		filter_threshold,	GET_BITS(pp->mnr_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_L9A_QWr01(p0r_mnr_ctrl_00,		mnr_enable, 		(pp->mnr_enable)? 0x1:0x0);
				PE_P0R_L9A_QWr02(p0r_bnr_ac_ctrl_00,	bnr_h_en, 			(pp->ac_bnr_h_en)? 0x1:0x0,\
														bnr_v_en, 			(pp->ac_bnr_v_en)? 0x1:0x0);
				PE_P0R_L9A_QWr01(p0r_bnr_ac_ctrl_01, 	strength_h_max, 	GET_BITS(pp->ac_bnr_h_gain,0,8));
				PE_P0R_L9A_QWr01(p0r_bnr_dc_ctrl_00, 	gain, 				GET_BITS(pp->dc_bnr_gain,0,8));
				PE_P0R_L9A_QWr01(p0r_mnr_ctrl_05, 		filter_threshold,	GET_BITS(pp->mnr_gain,0,8));
			}
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get dnr common ctrl
 * - use input struct LX_PE_NRD_DNR2_CMN_T for H13BX
 * - use input struct LX_PE_NRD_DNR1_CMN_T for L9BX
 * - use input struct LX_PE_NRD_DNR0_CMN_T for L9AX,H13AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_GetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_DNR2_CMN_T *pp = (LX_PE_NRD_DNR2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13B0_QRd03(p0l_dnr_max_ctrl,	enable_ac_bnr,			pp->enable_ac_bnr,\
														enable_mnr,				pp->enable_mnr,\
														enable_dc_bnr,			pp->enable_dc_bnr);
				PE_P0L_H13B0_QRd03(p0l_mnr_ctrl_00,		reg_mnr_enable,			pp->reg_mnr_enable,\
														reg_mnr_master_gain,	pp->reg_mnr_master_gain,\
														reg_chroma_master_gain,	pp->reg_chroma_master_gain);
				PE_P0L_H13B0_QRd02(p0l_mnr_ctrl_02,		reg_mnr_h_gain,			pp->reg_mnr_h_gain,\
														reg_mnr_v_gain,			pp->reg_mnr_v_gain);				
				PE_P0L_H13B0_QRd04(p0l_bnr_ac_ctrl_00,	reg_bnr_ac_h_en,		pp->bnr_h_en,\
														reg_bnr_ac_v_en,		pp->bnr_v_en,\
														reg_bnr_ac_gain_h_max,	pp->hbmax_gain,\
														reg_bnr_ac_gain_v_max,	pp->vbmax_gain);
				PE_P0L_H13B0_QRd02(p0l_bnr_ac_ctrl_06,	ac_bnr_protect_motion_max,	pp->ac_bnr_protect_motion_max,\
														ac_bnr_protect_motion_min,	pp->ac_bnr_protect_motion_min);
				PE_P0L_H13B0_QRd01(p0l_bnr_ac_ctrl_01,	strength_h_max,			pp->strength_h_max);
				PE_P0L_H13B0_QRd01(p0l_bnr_ac_ctrl_02,	strength_v_max,			pp->strength_v_max);				
				PE_P0L_H13B0_QRd03(p0l_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		pp->reg_dc_bnr_enable,\
														reg_dc_bnr_mastergain,	pp->reg_dc_bnr_mastergain,\
														reg_dc_bnr_chromagain,	pp->reg_dc_bnr_chromagain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13B0_QRd03(p0r_dnr_max_ctrl,	enable_ac_bnr,			pp->enable_ac_bnr,\
														enable_mnr,				pp->enable_mnr,\
														enable_dc_bnr,			pp->enable_dc_bnr);
				PE_P0R_H13B0_QRd03(p0r_mnr_ctrl_00,		reg_mnr_enable,			pp->reg_mnr_enable,\
														reg_mnr_master_gain,	pp->reg_mnr_master_gain,\
														reg_chroma_master_gain,	pp->reg_chroma_master_gain);
				PE_P0R_H13B0_QRd02(p0r_mnr_ctrl_02,		reg_mnr_h_gain,			pp->reg_mnr_h_gain,\
														reg_mnr_v_gain,			pp->reg_mnr_v_gain);				
				PE_P0R_H13B0_QRd04(p0r_bnr_ac_ctrl_00,	reg_bnr_ac_h_en,		pp->bnr_h_en,\
														reg_bnr_ac_v_en,		pp->bnr_v_en,\
														reg_bnr_ac_gain_h_max,	pp->hbmax_gain,\
														reg_bnr_ac_gain_v_max,	pp->vbmax_gain);
				PE_P0R_H13B0_QRd02(p0r_bnr_ac_ctrl_06,	ac_bnr_protect_motion_max,	pp->ac_bnr_protect_motion_max,\
														ac_bnr_protect_motion_min,	pp->ac_bnr_protect_motion_min);
				PE_P0R_H13B0_QRd01(p0r_bnr_ac_ctrl_01,	strength_h_max,			pp->strength_h_max);
				PE_P0R_H13B0_QRd01(p0r_bnr_ac_ctrl_02,	strength_v_max,			pp->strength_v_max);				
				PE_P0R_H13B0_QRd03(p0r_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		pp->reg_dc_bnr_enable,\
														reg_dc_bnr_mastergain,	pp->reg_dc_bnr_mastergain,\
														reg_dc_bnr_chromagain,	pp->reg_dc_bnr_chromagain);
			}
			PE_NRD_DBG_PRINT("get[%d] : dnr main : en: ac:%d, mnr:%d, dc:%d\n"\
						  	 "          mnr      : en:%d, master_gain%d, chroma_gain:%d,h_gain:%d, v_gain:%d\n"\
						 	 "          ac_bnr   : h,v_en:%d,%d,  mo_max,min:%d,%d,  h,v_bmax:%d,%d,  str_h,v_max:%d,%d\n"\
						  	 "          dc_bnr   : en:%d,master_gain%d, chroma_gain:%d\n",pp->win_id,\
				/* dnr main */
				pp->enable_mnr,pp->enable_ac_bnr,pp->enable_dc_bnr,\
				/* mnr */
				pp->reg_mnr_enable,pp->reg_mnr_master_gain,pp->reg_chroma_master_gain,pp->reg_mnr_h_gain,pp->reg_mnr_v_gain,\
				/* ac */
				pp->bnr_h_en,pp->bnr_v_en,pp->ac_bnr_protect_motion_max,pp->ac_bnr_protect_motion_min,\
				pp->hbmax_gain,pp->vbmax_gain,pp->strength_h_max,pp->strength_v_max,\
				/* dc */
				pp->reg_dc_bnr_enable,pp->reg_dc_bnr_mastergain,pp->reg_dc_bnr_chromagain);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			LX_PE_NRD_DNR0_CMN_T *pp = (LX_PE_NRD_DNR0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13_QRd02(p0l_mnr_ctrl_00,		reg_mnr_enable, 		pp->mnr_enable,\
														reg_mnr_master_gain,	pp->mnr_gain);
				PE_P0L_H13_QRd02(p0l_bnr_ac_ctrl_00,	bnr_h_en,	 			pp->ac_bnr_h_en,\
														bnr_v_en,				pp->ac_bnr_v_en);
				PE_P0L_H13_QRd01(p0l_bnr_ac_ctrl_01,	strength_h_max,			pp->ac_bnr_h_gain);
				PE_P0L_H13_QRd01(p0l_bnr_ac_ctrl_02,	strength_v_max,			pp->ac_bnr_v_gain);
				PE_P0L_H13_QRd02(p0l_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		pp->dc_bnr_en,\
														reg_dc_bnr_mastergain,	pp->dc_bnr_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13_QRd02(p0r_mnr_ctrl_00,		reg_mnr_enable, 		pp->mnr_enable,\
														reg_mnr_master_gain,	pp->mnr_gain);
				PE_P0R_H13_QRd02(p0r_bnr_ac_ctrl_00,	bnr_h_en,	 			pp->ac_bnr_h_en,\
														bnr_v_en,				pp->ac_bnr_v_en);
				PE_P0R_H13_QRd01(p0r_bnr_ac_ctrl_01,	strength_h_max,			pp->ac_bnr_h_gain);
				PE_P0R_H13_QRd01(p0r_bnr_ac_ctrl_02,	strength_v_max,			pp->ac_bnr_v_gain);
				PE_P0R_H13_QRd02(p0r_bnr_dc_ctrl_00,	reg_dc_bnr_enable,		pp->dc_bnr_en,\
														reg_dc_bnr_mastergain,	pp->dc_bnr_gain);
			}
			PE_NRD_DBG_PRINT("get[%d] : en:m:%d,a:%d,%d,d:%d, gain:m:%d,a:%d,%d,d:%d\n",pp->win_id,\
				pp->mnr_enable,pp->ac_bnr_h_en,pp->ac_bnr_v_en,pp->dc_bnr_en,\
				pp->mnr_gain,pp->ac_bnr_h_gain,pp->ac_bnr_h_gain,pp->dc_bnr_gain);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_NRD_DNR1_CMN_T *pp = (LX_PE_NRD_DNR1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9B_QRd01(mnr_ctrl_00,	mnr_enable,			pp->mnr_enable);
				PE_P0L_L9B_QRd01(mnr_ctrl_05,	filter_threshold,	pp->filter_threshold);
				PE_P0L_L9B_QRd04(bnr_ac_ctrl_00,bnr_h_en,			pp->bnr_h_en,\
												bnr_v_en,			pp->bnr_v_en,\
												hbmax_gain,			pp->hbmax_gain,\
												vbmax_gain,			pp->vbmax_gain);
				PE_P0L_L9B_QRd01(bnr_ac_ctrl_01,strength_h_max,		pp->strength_h_max);
				PE_P0L_L9B_QRd01(bnr_ac_ctrl_02,strength_v_max,		pp->strength_v_max);
				PE_P0L_L9B_QRd02(bnr_ac_ctrl_06,ac_bnr_protect_motion_max,	pp->ac_bnr_protect_motion_max,\
												ac_bnr_protect_motion_min,	pp->ac_bnr_protect_motion_min);
				PE_P0L_L9B_QRd03(bnr_dc_ctrl_00,dc_bnr_enable,		pp->dc_bnr_enable,\
												motion_min,			pp->motion_min,\
												motion_max,			pp->motion_max);
				PE_P0L_L9B_QRd01(bnr_dc_ctrl_01,ac_blockiness_multifly_x_n,pp->ac_blockiness_multifly);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_L9B_QRd01(mnr_ctrl_00,	mnr_enable,			pp->mnr_enable);
				PE_P0R_L9B_QRd01(mnr_ctrl_05,	filter_threshold,	pp->filter_threshold);
				PE_P0R_L9B_QRd04(bnr_ac_ctrl_00,bnr_h_en,			pp->bnr_h_en,\
												bnr_v_en,			pp->bnr_v_en,\
												hbmax_gain,			pp->hbmax_gain,\
												vbmax_gain,			pp->vbmax_gain);
				PE_P0R_L9B_QRd01(bnr_ac_ctrl_01,strength_h_max,		pp->strength_h_max);
				PE_P0R_L9B_QRd01(bnr_ac_ctrl_02,strength_v_max,		pp->strength_v_max);
				PE_P0R_L9B_QRd02(bnr_ac_ctrl_06,ac_bnr_protect_motion_max,	pp->ac_bnr_protect_motion_max,\
												ac_bnr_protect_motion_min,	pp->ac_bnr_protect_motion_min);
				PE_P0R_L9B_QRd03(bnr_dc_ctrl_00,dc_bnr_enable,		pp->dc_bnr_enable,\
												motion_min,			pp->motion_min,\
												motion_max,			pp->motion_max);
				PE_P0R_L9B_QRd01(bnr_dc_ctrl_01,ac_blockiness_multifly_x_n,pp->ac_blockiness_multifly);
			}
			PE_NRD_DBG_PRINT("get[%d] : mnr : en:%d, flt_th:%d\n"\
				"ac_bnr: h,v_en:%d,%d,  mo_max,min:%d,%d,  h,v_bmax:%d,%d,  str_h,v_max:%d,%d\n"\
				"dc_bnr: en:%d,  mo_min,max:%d,%d, ac_blki_multi:%d\n",\
				pp->win_id,pp->mnr_enable,pp->filter_threshold,\
				pp->bnr_h_en,pp->bnr_v_en,pp->ac_bnr_protect_motion_max,\
				pp->ac_bnr_protect_motion_min,pp->hbmax_gain,pp->vbmax_gain,\
				pp->strength_h_max,pp->strength_v_max,\
				pp->dc_bnr_enable,pp->motion_min,pp->motion_max,\
				pp->ac_blockiness_multifly);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_NRD_DNR0_CMN_T *pp = (LX_PE_NRD_DNR0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9A_QRd01(p0l_mnr_ctrl_00,		mnr_enable, 		pp->mnr_enable);
				PE_P0L_L9A_QRd02(p0l_bnr_ac_ctrl_00,	bnr_h_en, 			pp->ac_bnr_h_en,\
														bnr_v_en, 			pp->ac_bnr_v_en);
				PE_P0L_L9A_QRd01(p0l_bnr_ac_ctrl_01, 	strength_h_max, 	pp->ac_bnr_h_gain);
				PE_P0L_L9A_QRd01(p0l_bnr_dc_ctrl_00, 	gain, 				pp->dc_bnr_gain);
				PE_P0L_L9A_QRd01(p0l_mnr_ctrl_05, 		filter_threshold,	pp->mnr_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_L9A_QRd01(p0r_mnr_ctrl_00,		mnr_enable, 		pp->mnr_enable);
				PE_P0R_L9A_QRd02(p0r_bnr_ac_ctrl_00,	bnr_h_en, 			pp->ac_bnr_h_en,\
														bnr_v_en, 			pp->ac_bnr_v_en);
				PE_P0R_L9A_QRd01(p0r_bnr_ac_ctrl_01, 	strength_h_max, 	pp->ac_bnr_h_gain);
				PE_P0R_L9A_QRd01(p0r_bnr_dc_ctrl_00, 	gain, 				pp->dc_bnr_gain);
				PE_P0R_L9A_QRd01(p0r_mnr_ctrl_05, 		filter_threshold,	pp->mnr_gain);
			}
			PE_NRD_DBG_PRINT("get[%d] : %d,%d,%d,%d,%d,%d\n",pp->win_id,\
				pp->mnr_enable,pp->ac_bnr_h_en,pp->ac_bnr_v_en,\
				pp->ac_bnr_h_gain,pp->dc_bnr_gain,pp->mnr_gain);
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for H13BX
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for L9BX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_SetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_DNR2_DETAIL_T *pp=(LX_PE_NRD_DNR2_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] \n"\
				"mnr   : h_expend:%d,  gain_flt_size:%d,  mmd_min s1,s2:%d,%d ratio_min,max: %d,%d \n"\
				"mnr   : filter x0,x1,y0,y1:%d,%d,%d,%d\n"\
				"mnr   : motion_en:%d, filter:%d, min:%d, max:%d\n"\
				"mnr   : motion x0,x1,y0,y1:%d,%d,%d,%d\n"\
				"ac_bnr: protect_en:%d, sdhd_sel(source type):%d, flt_thpe:%d,\n"\
				"ac_bnr: strength h_x0,h_x1,v_x0,v_x1:%d,%d,%d,%d, detect_min_th:%d\n"\
				"dc_bnr: var_en:%d,  motion_en:%d,  acadaptive:%d, sdhd_sel:%d\n"\
				"dc_bnr: blur_sel:%d, protection_en:%d \n"\
				"dc_bnr: var_th0,th1,th2,th3%d,%d,%d,%d, motion_th0,th1,th2,th3%d,%d,%d,%d\n"\
				"dc_bnr: chroma_var:%d, var_h_gain:%d, protection_th:%d\n",pp->win_id,\
				/* mnr */
				pp->reg_h_expend,pp->reg_gain_flt_size,\
				pp->reg_mnr_s1_mmd_min,pp->reg_mnr_s2_ratio_min,pp->reg_mnr_s2_ratio_max,pp->reg_mnr_s2_mmd_min,\
				pp->reg_filter_x0,pp->reg_filter_x1,pp->reg_filter_y0,pp->reg_filter_y1,\
				pp->reg_motion_mnr_en,pp->reg_motion_mnr_filter,pp->reg_mnr_motion_min,pp->reg_mnr_motion_max,\
				pp->reg_motion_mnr_x0,pp->reg_motion_mnr_x1,pp->reg_motion_mnr_y0,pp->reg_motion_mnr_y1,\
				/* ac_bnr */
				pp->motion_protect_enable,pp->source_type,pp->fiter_type,\
				pp->strength_h_x0,pp->strength_h_x1,pp->strength_v_x0,pp->strength_v_x1,\
				pp->detect_min_th,\
				/* dc_bnr */
				pp->reg_dc_bnr_var_en,pp->reg_dc_bnr_motion_en,pp->reg_dc_bnr_acadaptive,pp->reg_dc_bnr_sdhd_sel,\
				pp->reg_dc_blur_sel,pp->reg_dc_protection_en,\
				pp->reg_dc_bnr_var_th0,pp->reg_dc_bnr_var_th1,\
				pp->reg_dc_bnr_var_th2,pp->reg_dc_bnr_var_th3,\
				pp->reg_dc_bnr_motion_th0,pp->reg_dc_bnr_motion_th1,\
				pp->reg_dc_bnr_motion_th2,pp->reg_dc_bnr_motion_th3,\
				pp->reg_dc_chroma_variance,pp->reg_dc_var_h_gain,pp->reg_dc_protection_th);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* mnr */
				PE_P0L_H13B0_QWr02(p0l_mnr_ctrl_00,	reg_h_expend,		GET_BITS(pp->reg_h_expend,0,1),\
													reg_gain_flt_size,	GET_BITS(pp->reg_gain_flt_size,0,1));
				
				PE_P0L_H13B0_QWr04(p0l_mnr_ctrl_01,	reg_mnr_s1_mmd_min,		GET_BITS(pp->reg_mnr_s1_mmd_min,0,8),\
													reg_mnr_s2_ratio_min,	GET_BITS(pp->reg_mnr_s2_ratio_min,0,8),\
													reg_mnr_s2_ratio_max,	GET_BITS(pp->reg_mnr_s2_ratio_max,0,8),\
													reg_mnr_s2_mmd_min,		GET_BITS(pp->reg_mnr_s2_mmd_min,0,8));
				PE_P0L_H13B0_QWr04(p0l_mnr_ctrl_03,	reg_filter_x0,	GET_BITS(pp->reg_filter_x0,0,8),\
													reg_filter_x1,	GET_BITS(pp->reg_filter_x1,0,8),\
													reg_filter_y0,	GET_BITS(pp->reg_filter_y0,0,8),\
													reg_filter_y1,	GET_BITS(pp->reg_filter_y1,0,8));
				PE_P0L_H13B0_QWr04(p0l_mnr_ctrl_04,	reg_motion_mnr_en,		GET_BITS(pp->reg_motion_mnr_en,0,1),\
													reg_motion_mnr_filter,	GET_BITS(pp->reg_motion_mnr_filter,0,1),\
													reg_mnr_motion_min,		GET_BITS(pp->reg_mnr_motion_min,0,8),\
													reg_mnr_motion_max,		GET_BITS(pp->reg_mnr_motion_max,0,8));
				PE_P0L_H13B0_QWr04(p0l_mnr_ctrl_05,	reg_motion_mnr_x0,		GET_BITS(pp->reg_motion_mnr_x0,0,8),\
													reg_motion_mnr_x1,		GET_BITS(pp->reg_motion_mnr_x1,0,8),\
													reg_motion_mnr_y0,		GET_BITS(pp->reg_motion_mnr_y0,0,8),\
													reg_motion_mnr_y1,		GET_BITS(pp->reg_motion_mnr_y1,0,8));
				/* ac_bnr */
				PE_P0L_H13B0_QWr03(p0l_bnr_ac_ctrl_00,	reg_bnr_ac_protect_en,	GET_BITS(pp->motion_protect_enable,0,1),\
														reg_bnr_ac_sdhd_sel,	GET_BITS(pp->source_type,0,1),\
														reg_bnr_ac_flt_type,	GET_BITS(pp->fiter_type,0,1));
				PE_P0L_H13B0_QWr03(p0l_bnr_ac_ctrl_01,	strength_h_x0,	GET_BITS(pp->strength_h_x0,0,8),\
														strength_h_x1,	GET_BITS(pp->strength_h_x1,0,8),\
														detect_min_th,	GET_BITS(pp->detect_min_th,0,8));
				PE_P0L_H13B0_QWr02(p0l_bnr_ac_ctrl_02,	strength_v_x0,	GET_BITS(pp->strength_v_x0,0,8),\
														strength_v_x1,	GET_BITS(pp->strength_v_x1,0,8));
				/* dc_bnr */
				PE_P0L_H13B0_QWr04(p0l_bnr_dc_ctrl_00,	reg_dc_bnr_var_en,		GET_BITS(pp->reg_dc_bnr_var_en,0,1),\
														reg_dc_bnr_motion_en,	GET_BITS(pp->reg_dc_bnr_motion_en,0,1),\
														reg_dc_bnr_acadaptive,	GET_BITS(pp->reg_dc_bnr_acadaptive,0,1),
														reg_dc_bnr_sdhd_sel,	GET_BITS(pp->reg_dc_bnr_sdhd_sel,0,1));
				PE_P0L_H13B0_QWr02(p0l_bnr_dc_ctrl_00,	reg_dc_blur_sel,		GET_BITS(pp->reg_dc_blur_sel,0,2),\
														reg_dc_protection_en,	GET_BITS(pp->reg_dc_protection_en,0,1));
				PE_P0L_H13B0_QWr04(p0l_bnr_dc_ctrl_01,	reg_dc_bnr_var_th0,		GET_BITS(pp->reg_dc_bnr_var_th0,0,8),\
														reg_dc_bnr_var_th1,		GET_BITS(pp->reg_dc_bnr_var_th1,0,8),\
														reg_dc_bnr_var_th2,		GET_BITS(pp->reg_dc_bnr_var_th2,0,8),\
														reg_dc_bnr_var_th3,		GET_BITS(pp->reg_dc_bnr_var_th3,0,8));
				PE_P0L_H13B0_QWr04(p0l_bnr_dc_ctrl_02,	reg_dc_bnr_motion_th0,	GET_BITS(pp->reg_dc_bnr_motion_th0,0,8),\
														reg_dc_bnr_motion_th1,	GET_BITS(pp->reg_dc_bnr_motion_th1,0,8),\
														reg_dc_bnr_motion_th2,	GET_BITS(pp->reg_dc_bnr_motion_th2,0,8),\
														reg_dc_bnr_motion_th3,	GET_BITS(pp->reg_dc_bnr_motion_th3,0,8));
				PE_P0L_H13B0_QWr03(p0l_bnr_dc_ctrl_03,	reg_dc_chroma_variance,	GET_BITS(pp->reg_dc_chroma_variance,0,8),\
														reg_dc_var_h_gain,		GET_BITS(pp->reg_dc_var_h_gain,0,8),\
														reg_dc_protection_th,	GET_BITS(pp->reg_dc_protection_th,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* mnr */
				PE_P0R_H13B0_QWr02(p0r_mnr_ctrl_00,	reg_h_expend,		GET_BITS(pp->reg_h_expend,0,1),\
													reg_gain_flt_size,	GET_BITS(pp->reg_gain_flt_size,0,1));
				
				PE_P0R_H13B0_QWr04(p0r_mnr_ctrl_01,	reg_mnr_s1_mmd_min,		GET_BITS(pp->reg_mnr_s1_mmd_min,0,8),\
													reg_mnr_s2_ratio_min,	GET_BITS(pp->reg_mnr_s2_ratio_min,0,8),\
													reg_mnr_s2_ratio_max,	GET_BITS(pp->reg_mnr_s2_ratio_max,0,8),\
													reg_mnr_s2_mmd_min,		GET_BITS(pp->reg_mnr_s2_mmd_min,0,8));
				PE_P0R_H13B0_QWr04(p0r_mnr_ctrl_03,	reg_filter_x0,	GET_BITS(pp->reg_filter_x0,0,8),\
													reg_filter_x1,	GET_BITS(pp->reg_filter_x1,0,8),\
													reg_filter_y0,	GET_BITS(pp->reg_filter_y0,0,8),\
													reg_filter_y1,	GET_BITS(pp->reg_filter_y1,0,8));
				PE_P0R_H13B0_QWr04(p0r_mnr_ctrl_04,	reg_motion_mnr_en,		GET_BITS(pp->reg_motion_mnr_en,0,1),\
													reg_motion_mnr_filter,	GET_BITS(pp->reg_motion_mnr_filter,0,1),\
													reg_mnr_motion_min,		GET_BITS(pp->reg_mnr_motion_min,0,8),\
													reg_mnr_motion_max,		GET_BITS(pp->reg_mnr_motion_max,0,8));
				PE_P0R_H13B0_QWr04(p0r_mnr_ctrl_05,	reg_motion_mnr_x0,		GET_BITS(pp->reg_motion_mnr_x0,0,8),\
													reg_motion_mnr_x1,		GET_BITS(pp->reg_motion_mnr_x1,0,8),\
													reg_motion_mnr_y0,		GET_BITS(pp->reg_motion_mnr_y0,0,8),\
													reg_motion_mnr_y1,		GET_BITS(pp->reg_motion_mnr_y1,0,8));
				/* ac_bnr */
				PE_P0R_H13B0_QWr03(p0r_bnr_ac_ctrl_00,	reg_bnr_ac_protect_en,	GET_BITS(pp->motion_protect_enable,0,1),\
														reg_bnr_ac_sdhd_sel,	GET_BITS(pp->source_type,0,1),\
														reg_bnr_ac_flt_type,	GET_BITS(pp->fiter_type,0,1));
				PE_P0R_H13B0_QWr03(p0r_bnr_ac_ctrl_01,	strength_h_x0,	GET_BITS(pp->strength_h_x0,0,8),\
														strength_h_x1,	GET_BITS(pp->strength_h_x1,0,8),\
														detect_min_th,	GET_BITS(pp->detect_min_th,0,8));
				PE_P0R_H13B0_QWr02(p0r_bnr_ac_ctrl_02,	strength_v_x0,	GET_BITS(pp->strength_v_x0,0,8),\
														strength_v_x1,	GET_BITS(pp->strength_v_x1,0,8));
				/* dc_bnr */
				PE_P0R_H13B0_QWr04(p0r_bnr_dc_ctrl_00,	reg_dc_bnr_var_en,		GET_BITS(pp->reg_dc_bnr_var_en,0,1),\
														reg_dc_bnr_motion_en,	GET_BITS(pp->reg_dc_bnr_motion_en,0,1),\
														reg_dc_bnr_acadaptive,	GET_BITS(pp->reg_dc_bnr_acadaptive,0,1),
														reg_dc_bnr_sdhd_sel,	GET_BITS(pp->reg_dc_bnr_sdhd_sel,0,1));
				PE_P0R_H13B0_QWr02(p0r_bnr_dc_ctrl_00,	reg_dc_blur_sel,		GET_BITS(pp->reg_dc_blur_sel,0,2),\
														reg_dc_protection_en,	GET_BITS(pp->reg_dc_protection_en,0,1));
				PE_P0R_H13B0_QWr04(p0r_bnr_dc_ctrl_01,	reg_dc_bnr_var_th0,		GET_BITS(pp->reg_dc_bnr_var_th0,0,8),\
														reg_dc_bnr_var_th1,		GET_BITS(pp->reg_dc_bnr_var_th1,0,8),\
														reg_dc_bnr_var_th2,		GET_BITS(pp->reg_dc_bnr_var_th2,0,8),\
														reg_dc_bnr_var_th3,		GET_BITS(pp->reg_dc_bnr_var_th3,0,8));
				PE_P0R_H13B0_QWr04(p0r_bnr_dc_ctrl_02,	reg_dc_bnr_motion_th0,	GET_BITS(pp->reg_dc_bnr_motion_th0,0,8),\
														reg_dc_bnr_motion_th1,	GET_BITS(pp->reg_dc_bnr_motion_th1,0,8),\
														reg_dc_bnr_motion_th2,	GET_BITS(pp->reg_dc_bnr_motion_th2,0,8),\
														reg_dc_bnr_motion_th3,	GET_BITS(pp->reg_dc_bnr_motion_th3,0,8));
				PE_P0R_H13B0_QWr03(p0r_bnr_dc_ctrl_03,	reg_dc_chroma_variance,	GET_BITS(pp->reg_dc_chroma_variance,0,8),\
														reg_dc_var_h_gain,		GET_BITS(pp->reg_dc_var_h_gain,0,8),\
														reg_dc_protection_th,	GET_BITS(pp->reg_dc_protection_th,0,8));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_NRD_DNR1_DETAIL_T *pp=(LX_PE_NRD_DNR1_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] \n"\
				"mnr   : g_map_en:%d,  sd_hd:%d,  [x]:%d,%d,%d,%d,  [y]:%d,%d,%d,%d\n"\
				"ac_bnr: mo_p_en:%d,  src_type:%d,  flt_type:%d\n"\
				"ac_bnr: [str_h_x]:%d,%d,  det_min_th:%d,  [str_v_x]:%d,%d\n"\
				"dc_bnr: blki_adp:%d,  mo_g_en:%d,  sd_hd:%d\n"\
				"dc_bnr: [x,y]:%d,%d, %d,%d, %d,%d, %d,%d\n",\
				pp->win_id,\
				/* mnr */
				pp->edge_gain_mapping_enable,pp->sel_sd_hd,\
				pp->x1_position,pp->x2_position,pp->x3_position,pp->x4_position,\
				pp->y1_position,pp->y2_position,pp->y3_position,pp->y4_position,\
				/* ac_bnr */
				pp->motion_protect_enable,pp->source_type,pp->fiter_type,\
				pp->strength_h_x0,pp->strength_h_x1,pp->detect_min_th,\
				pp->strength_v_x0,pp->strength_v_x1,\
				/* dc_bnr */
				pp->ac_blockiness_adaptive_mode,pp->motion_gain_enable,pp->sd_hd_sel,\
				pp->dc_bnr_gain_ctrl_x0,pp->dc_bnr_gain_ctrl_y0,\
				pp->dc_bnr_gain_ctrl_x1,pp->dc_bnr_gain_ctrl_y1,\
				pp->dc_bnr_gain_ctrl_x2,pp->dc_bnr_gain_ctrl_y2,\
				pp->dc_bnr_gain_ctrl_x3,pp->dc_bnr_gain_ctrl_y3);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* mnr */
				PE_P0L_L9B_QWr02(mnr_ctrl_00,	edge_gain_mapping_enable,	GET_BITS(pp->edge_gain_mapping_enable,0,1),\
												sel_sd_hd,					GET_BITS(pp->sel_sd_hd,0,1));
				PE_P0L_L9B_QWr01(mnr_ctrl_03,	x1_position,	GET_BITS(pp->x1_position,0,8));
				PE_P0L_L9B_QWr04(mnr_ctrl_04,	x2_position,	GET_BITS(pp->x2_position,0,8),\
												x3_position,	GET_BITS(pp->x3_position,0,8),\
												x4_position,	GET_BITS(pp->x4_position,0,8),\
												y1_position,	GET_BITS(pp->y1_position,0,8));
				PE_P0L_L9B_QWr03(mnr_ctrl_05,	y2_position,	GET_BITS(pp->y2_position,0,8),\
												y3_position,	GET_BITS(pp->y3_position,0,8),\
												y4_position,	GET_BITS(pp->y4_position,0,8));
				/* ac_bnr */
				PE_P0L_L9B_QWr03(bnr_ac_ctrl_00,motion_protect_enable,		GET_BITS(pp->motion_protect_enable,0,1),\
												source_type,	GET_BITS(pp->source_type,0,1),\
												fiter_type,		GET_BITS(pp->fiter_type,0,1));
				PE_P0L_L9B_QWr03(bnr_ac_ctrl_01,strength_h_x0,	GET_BITS(pp->strength_h_x0,0,8),\
												strength_h_x1,	GET_BITS(pp->strength_h_x1,0,8),\
												detect_min_th,	GET_BITS(pp->detect_min_th,0,8));
				PE_P0L_L9B_QWr02(bnr_ac_ctrl_02,strength_v_x0,	GET_BITS(pp->strength_v_x0,0,8),\
												strength_v_x1,	GET_BITS(pp->strength_v_x1,0,8));
				/* dc_bnr */
				PE_P0L_L9B_QWr03(bnr_dc_ctrl_00,ac_blockiness_adaptive_mode,GET_BITS(pp->ac_blockiness_adaptive_mode,0,1),\
												motion_gain_enable,			GET_BITS(pp->motion_gain_enable,0,1),\
												sd_hd_sel,					GET_BITS(pp->sd_hd_sel,0,1));
				PE_P0L_L9B_QWr04(bnr_dc_ctrl_02,dc_bnr_gain_ctrl_y2,	GET_BITS(pp->dc_bnr_gain_ctrl_y2,0,8),\
												dc_bnr_gain_ctrl_x2,	GET_BITS(pp->dc_bnr_gain_ctrl_x2,0,8),\
												dc_bnr_gain_ctrl_y3,	GET_BITS(pp->dc_bnr_gain_ctrl_y3,0,8),\
												dc_bnr_gain_ctrl_x3,	GET_BITS(pp->dc_bnr_gain_ctrl_x3,0,8));
				PE_P0L_L9B_QWr04(bnr_dc_ctrl_03,dc_bnr_gain_ctrl_y0,	GET_BITS(pp->dc_bnr_gain_ctrl_y0,0,8),\
												dc_bnr_gain_ctrl_x0,	GET_BITS(pp->dc_bnr_gain_ctrl_x0,0,8),\
												dc_bnr_gain_ctrl_y1,	GET_BITS(pp->dc_bnr_gain_ctrl_y1,0,8),\
												dc_bnr_gain_ctrl_x1,	GET_BITS(pp->dc_bnr_gain_ctrl_x1,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* mnr */
				PE_P0R_L9B_QWr02(mnr_ctrl_00,	edge_gain_mapping_enable,	GET_BITS(pp->edge_gain_mapping_enable,0,1),\
												sel_sd_hd,					GET_BITS(pp->sel_sd_hd,0,1));
				PE_P0R_L9B_QWr01(mnr_ctrl_03,	x1_position,	GET_BITS(pp->x1_position,0,8));
				PE_P0R_L9B_QWr04(mnr_ctrl_04,	x2_position,	GET_BITS(pp->x2_position,0,8),\
												x3_position,	GET_BITS(pp->x3_position,0,8),\
												x4_position,	GET_BITS(pp->x4_position,0,8),\
												y1_position,	GET_BITS(pp->y1_position,0,8));
				PE_P0R_L9B_QWr03(mnr_ctrl_05,	y2_position,	GET_BITS(pp->y2_position,0,8),\
												y3_position,	GET_BITS(pp->y3_position,0,8),\
												y4_position,	GET_BITS(pp->y4_position,0,8));
				/* ac_bnr */
				PE_P0R_L9B_QWr03(bnr_ac_ctrl_00,motion_protect_enable,		GET_BITS(pp->motion_protect_enable,0,1),\
												source_type,	GET_BITS(pp->source_type,0,1),\
												fiter_type,		GET_BITS(pp->fiter_type,0,1));
				PE_P0R_L9B_QWr03(bnr_ac_ctrl_01,strength_h_x0,	GET_BITS(pp->strength_h_x0,0,8),\
												strength_h_x1,	GET_BITS(pp->strength_h_x1,0,8),\
												detect_min_th,	GET_BITS(pp->detect_min_th,0,8));
				PE_P0R_L9B_QWr02(bnr_ac_ctrl_02,strength_v_x0,	GET_BITS(pp->strength_v_x0,0,8),\
												strength_v_x1,	GET_BITS(pp->strength_v_x1,0,8));
				/* dc_bnr */
				PE_P0R_L9B_QWr03(bnr_dc_ctrl_00,ac_blockiness_adaptive_mode,GET_BITS(pp->ac_blockiness_adaptive_mode,0,1),\
												motion_gain_enable,			GET_BITS(pp->motion_gain_enable,0,1),\
												sd_hd_sel,					GET_BITS(pp->sd_hd_sel,0,1));
				PE_P0R_L9B_QWr04(bnr_dc_ctrl_02,dc_bnr_gain_ctrl_y2,	GET_BITS(pp->dc_bnr_gain_ctrl_y2,0,8),\
												dc_bnr_gain_ctrl_x2,	GET_BITS(pp->dc_bnr_gain_ctrl_x2,0,8),\
												dc_bnr_gain_ctrl_y3,	GET_BITS(pp->dc_bnr_gain_ctrl_y3,0,8),\
												dc_bnr_gain_ctrl_x3,	GET_BITS(pp->dc_bnr_gain_ctrl_x3,0,8));
				PE_P0R_L9B_QWr04(bnr_dc_ctrl_03,dc_bnr_gain_ctrl_y0,	GET_BITS(pp->dc_bnr_gain_ctrl_y0,0,8),\
												dc_bnr_gain_ctrl_x0,	GET_BITS(pp->dc_bnr_gain_ctrl_x0,0,8),\
												dc_bnr_gain_ctrl_y1,	GET_BITS(pp->dc_bnr_gain_ctrl_y1,0,8),\
												dc_bnr_gain_ctrl_x1,	GET_BITS(pp->dc_bnr_gain_ctrl_x1,0,8));
			}
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for H13BX
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for L9BX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_GetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		win_id = LX_PE_WIN_0;	/* to avoid warning(unused variable) */
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_DNR2_DETAIL_T *pp=(LX_PE_NRD_DNR2_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* mnr */
				PE_P0L_H13B0_QRd02(p0l_mnr_ctrl_00,	reg_h_expend,			pp->reg_h_expend,\
													reg_gain_flt_size,		pp->reg_gain_flt_size);				
				PE_P0L_H13B0_QRd04(p0l_mnr_ctrl_01,	reg_mnr_s1_mmd_min,		pp->reg_mnr_s1_mmd_min,\
													reg_mnr_s2_ratio_min,	pp->reg_mnr_s2_ratio_min,\
													reg_mnr_s2_ratio_max,	pp->reg_mnr_s2_ratio_max,\
													reg_mnr_s2_mmd_min,		pp->reg_mnr_s2_mmd_min);
				PE_P0L_H13B0_QRd04(p0l_mnr_ctrl_03,	reg_filter_x0,			pp->reg_filter_x0,\
													reg_filter_x1,			pp->reg_filter_x1,\
													reg_filter_y0,			pp->reg_filter_y0,\
													reg_filter_y1,			pp->reg_filter_y1);
				PE_P0L_H13B0_QRd04(p0l_mnr_ctrl_04,	reg_motion_mnr_en,		pp->reg_motion_mnr_en,\
													reg_motion_mnr_filter,	pp->reg_motion_mnr_filter,\
													reg_mnr_motion_min,		pp->reg_mnr_motion_min,\
													reg_mnr_motion_max,		pp->reg_mnr_motion_max);
				PE_P0L_H13B0_QRd04(p0l_mnr_ctrl_05,	reg_motion_mnr_x0,		pp->reg_motion_mnr_x0,\
													reg_motion_mnr_x1,		pp->reg_motion_mnr_x1,\
													reg_motion_mnr_y0,		pp->reg_motion_mnr_y0,\
													reg_motion_mnr_y1,		pp->reg_motion_mnr_y1);
				/* ac_bnr */
				PE_P0L_H13B0_QRd03(p0l_bnr_ac_ctrl_00,	reg_bnr_ac_protect_en,	pp->motion_protect_enable,\
														reg_bnr_ac_sdhd_sel,	pp->source_type,\
														reg_bnr_ac_flt_type,	pp->fiter_type);
				PE_P0L_H13B0_QRd03(p0l_bnr_ac_ctrl_01,	strength_h_x0,		pp->strength_h_x0,\
														strength_h_x1,		pp->strength_h_x1,\
														detect_min_th,		pp->detect_min_th);
				PE_P0L_H13B0_QRd02(p0l_bnr_ac_ctrl_02,	strength_v_x0,		pp->strength_v_x0,\
														strength_v_x1,		pp->strength_v_x1);
				/* dc_bnr */
				PE_P0L_H13B0_QRd04(p0l_bnr_dc_ctrl_00,	reg_dc_bnr_var_en,		pp->reg_dc_bnr_var_en,\
														reg_dc_bnr_motion_en,	pp->reg_dc_bnr_motion_en,\
														reg_dc_bnr_acadaptive,	pp->reg_dc_bnr_acadaptive,\
														reg_dc_bnr_sdhd_sel,	pp->reg_dc_bnr_sdhd_sel);
				PE_P0L_H13B0_QRd02(p0l_bnr_dc_ctrl_00,	reg_dc_blur_sel,		pp->reg_dc_blur_sel,\
														reg_dc_protection_en,	pp->reg_dc_protection_en);
				PE_P0L_H13B0_QRd04(p0l_bnr_dc_ctrl_01,	reg_dc_bnr_var_th0,		pp->reg_dc_bnr_var_th0,\
														reg_dc_bnr_var_th1,		pp->reg_dc_bnr_var_th1,\
														reg_dc_bnr_var_th2,		pp->reg_dc_bnr_var_th2,\
														reg_dc_bnr_var_th3,		pp->reg_dc_bnr_var_th3);
				PE_P0L_H13B0_QRd04(p0l_bnr_dc_ctrl_02,	reg_dc_bnr_motion_th0,	pp->reg_dc_bnr_motion_th0,\
														reg_dc_bnr_motion_th1,	pp->reg_dc_bnr_motion_th1,\
														reg_dc_bnr_motion_th2,	pp->reg_dc_bnr_motion_th2,\
														reg_dc_bnr_motion_th3,	pp->reg_dc_bnr_motion_th3);
				PE_P0L_H13B0_QRd03(p0l_bnr_dc_ctrl_03,	reg_dc_chroma_variance,	pp->reg_dc_chroma_variance,\
														reg_dc_var_h_gain,		pp->reg_dc_var_h_gain,\
														reg_dc_protection_th,	pp->reg_dc_protection_th);
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* mnr */
				PE_P0R_H13B0_QRd02(p0r_mnr_ctrl_00,	reg_h_expend,			pp->reg_h_expend,\
													reg_gain_flt_size,		pp->reg_gain_flt_size);
				
				PE_P0R_H13B0_QRd04(p0r_mnr_ctrl_01,	reg_mnr_s1_mmd_min,		pp->reg_mnr_s1_mmd_min,\
													reg_mnr_s2_ratio_min,	pp->reg_mnr_s2_ratio_min,\
													reg_mnr_s2_ratio_max,	pp->reg_mnr_s2_ratio_max,\
													reg_mnr_s2_mmd_min,		pp->reg_mnr_s2_mmd_min);
				PE_P0R_H13B0_QRd04(p0r_mnr_ctrl_03,	reg_filter_x0,			pp->reg_filter_x0,\
													reg_filter_x1,			pp->reg_filter_x1,\
													reg_filter_y0,			pp->reg_filter_y0,\
													reg_filter_y1,			pp->reg_filter_y1);
				PE_P0R_H13B0_QRd04(p0r_mnr_ctrl_04,	reg_motion_mnr_en,		pp->reg_motion_mnr_en,\
													reg_motion_mnr_filter,	pp->reg_motion_mnr_filter,\
													reg_mnr_motion_min,		pp->reg_mnr_motion_min,\
													reg_mnr_motion_max,		pp->reg_mnr_motion_max);
				PE_P0R_H13B0_QRd04(p0r_mnr_ctrl_05,	reg_motion_mnr_x0,		pp->reg_motion_mnr_x0,\
													reg_motion_mnr_x1,		pp->reg_motion_mnr_x1,\
													reg_motion_mnr_y0,		pp->reg_motion_mnr_y0,\
													reg_motion_mnr_y1,		pp->reg_motion_mnr_y1);
				/* ac_bnr */
				PE_P0R_H13B0_QRd03(p0r_bnr_ac_ctrl_00,	reg_bnr_ac_protect_en,	pp->motion_protect_enable,\
														reg_bnr_ac_sdhd_sel,	pp->source_type,\
														reg_bnr_ac_flt_type,	pp->fiter_type);
				PE_P0R_H13B0_QRd03(p0r_bnr_ac_ctrl_01,	strength_h_x0,		pp->strength_h_x0,\
														strength_h_x1,		pp->strength_h_x1,\
														detect_min_th,		pp->detect_min_th);
				PE_P0R_H13B0_QRd02(p0r_bnr_ac_ctrl_02,	strength_v_x0,		pp->strength_v_x0,\
														strength_v_x1,		pp->strength_v_x1);
				/* dc_bnr */
				PE_P0R_H13B0_QRd04(p0r_bnr_dc_ctrl_00,	reg_dc_bnr_var_en,		pp->reg_dc_bnr_var_en,\
														reg_dc_bnr_motion_en,	pp->reg_dc_bnr_motion_en,\
														reg_dc_bnr_acadaptive,	pp->reg_dc_bnr_acadaptive,\
														reg_dc_bnr_sdhd_sel,	pp->reg_dc_bnr_sdhd_sel);
				PE_P0R_H13B0_QRd02(p0r_bnr_dc_ctrl_00,	reg_dc_blur_sel,		pp->reg_dc_blur_sel,\
														reg_dc_protection_en,	pp->reg_dc_protection_en);
				PE_P0R_H13B0_QRd04(p0r_bnr_dc_ctrl_01,	reg_dc_bnr_var_th0,		pp->reg_dc_bnr_var_th0,\
														reg_dc_bnr_var_th1,		pp->reg_dc_bnr_var_th1,\
														reg_dc_bnr_var_th2,		pp->reg_dc_bnr_var_th2,\
														reg_dc_bnr_var_th3,		pp->reg_dc_bnr_var_th3);
				PE_P0R_H13B0_QRd04(p0r_bnr_dc_ctrl_02,	reg_dc_bnr_motion_th0,	pp->reg_dc_bnr_motion_th0,\
														reg_dc_bnr_motion_th1,	pp->reg_dc_bnr_motion_th1,\
														reg_dc_bnr_motion_th2,	pp->reg_dc_bnr_motion_th2,\
														reg_dc_bnr_motion_th3,	pp->reg_dc_bnr_motion_th3);
				PE_P0R_H13B0_QRd03(p0r_bnr_dc_ctrl_03,	reg_dc_chroma_variance,	pp->reg_dc_chroma_variance,\
														reg_dc_var_h_gain,		pp->reg_dc_var_h_gain,\
														reg_dc_protection_th,	pp->reg_dc_protection_th);
			}
			PE_NRD_DBG_PRINT("get[%d] \n"\
				"mnr   : h_expend:%d,  gain_flt_size:%d,  mmd_min s1,s2:%d,%d ratio_min,max: %d,%d \n"\
				"mnr   : filter x0,x1,y0,y1:%d,%d,%d,%d\n"\
				"mnr   : motion_en:%d, filter:%d, min:%d, max:%d\n"\
				"mnr   : motion x0,x1,y0,y1:%d,%d,%d,%d\n"\
				"ac_bnr: protect_en:%d, sdhd_sel(source type):%d, flt_thpe:%d,\n"\
				"ac_bnr: strength h_x0,h_x1,v_x0,v_x1:%d,%d,%d,%d, detect_min_th:%d\n"\
				"dc_bnr: var_en:%d,  motion_en:%d,  acadaptive:%d, sdhd_sel:%d\n"\
				"dc_bnr: blur_sel:%d, protection_en:%d \n"\
				"dc_bnr: var_th0,th1,th2,th3%d,%d,%d,%d, motion_th0,th1,th2,th3%d,%d,%d,%d\n"\
				"dc_bnr: chroma_var:%d, var_h_gain:%d, protection_th:%d\n",pp->win_id,\
				/* mnr */
				pp->reg_h_expend,pp->reg_gain_flt_size,\
				pp->reg_mnr_s1_mmd_min,pp->reg_mnr_s2_ratio_min,pp->reg_mnr_s2_ratio_max,pp->reg_mnr_s2_mmd_min,\
				pp->reg_filter_x0,pp->reg_filter_x1,pp->reg_filter_y0,pp->reg_filter_y1,\
				pp->reg_motion_mnr_en,pp->reg_motion_mnr_filter,pp->reg_mnr_motion_min,pp->reg_mnr_motion_max,\
				pp->reg_motion_mnr_x0,pp->reg_motion_mnr_x1,pp->reg_motion_mnr_y0,pp->reg_motion_mnr_y1,\
				/* ac_bnr */
				pp->motion_protect_enable,pp->source_type,pp->fiter_type,\
				pp->strength_h_x0,pp->strength_h_x1,pp->strength_v_x0,pp->strength_v_x1,\
				pp->detect_min_th,\
				/* dc_bnr */
				pp->reg_dc_bnr_var_en,pp->reg_dc_bnr_motion_en,pp->reg_dc_bnr_acadaptive,pp->reg_dc_bnr_sdhd_sel,\
				pp->reg_dc_blur_sel,pp->reg_dc_protection_en,\
				pp->reg_dc_bnr_var_th0,pp->reg_dc_bnr_var_th1,\
				pp->reg_dc_bnr_var_th2,pp->reg_dc_bnr_var_th3,\
				pp->reg_dc_bnr_motion_th0,pp->reg_dc_bnr_motion_th1,\
				pp->reg_dc_bnr_motion_th2,pp->reg_dc_bnr_motion_th3,\
				pp->reg_dc_chroma_variance,pp->reg_dc_var_h_gain,pp->reg_dc_protection_th);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_NRD_DNR1_DETAIL_T *pp=(LX_PE_NRD_DNR1_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				/* mnr */
				PE_P0L_L9B_QRd02(mnr_ctrl_00,	edge_gain_mapping_enable,	pp->edge_gain_mapping_enable,\
												sel_sd_hd,					pp->sel_sd_hd);
				PE_P0L_L9B_QRd01(mnr_ctrl_03,	x1_position,				pp->x1_position);
				PE_P0L_L9B_QRd04(mnr_ctrl_04,	x2_position,				pp->x2_position,\
												x3_position,				pp->x3_position,\
												x4_position,				pp->x4_position,\
												y1_position,				pp->y1_position);
				PE_P0L_L9B_QRd03(mnr_ctrl_05,	y2_position,				pp->y2_position,\
												y3_position,				pp->y3_position,\
												y4_position,				pp->y4_position);
				/* ac_bnr */
				PE_P0L_L9B_QRd03(bnr_ac_ctrl_00,motion_protect_enable,		pp->motion_protect_enable,\
												source_type,				pp->source_type,\
												fiter_type,					pp->fiter_type);
				PE_P0L_L9B_QRd03(bnr_ac_ctrl_01,strength_h_x0,				pp->strength_h_x0,\
												strength_h_x1,				pp->strength_h_x1,\
												detect_min_th,				pp->detect_min_th);
				PE_P0L_L9B_QRd02(bnr_ac_ctrl_02,strength_v_x0,				pp->strength_v_x0,\
												strength_v_x1,				pp->strength_v_x1);
				/* dc_bnr */
				PE_P0L_L9B_QRd03(bnr_dc_ctrl_00,ac_blockiness_adaptive_mode,pp->ac_blockiness_adaptive_mode,\
												motion_gain_enable,			pp->motion_gain_enable,\
												sd_hd_sel,					pp->sd_hd_sel);
				PE_P0L_L9B_QRd04(bnr_dc_ctrl_02,dc_bnr_gain_ctrl_y2,		pp->dc_bnr_gain_ctrl_y2,\
												dc_bnr_gain_ctrl_x2,		pp->dc_bnr_gain_ctrl_x2,\
												dc_bnr_gain_ctrl_y3,		pp->dc_bnr_gain_ctrl_y3,\
												dc_bnr_gain_ctrl_x3,		pp->dc_bnr_gain_ctrl_x3);
				PE_P0L_L9B_QRd04(bnr_dc_ctrl_03,dc_bnr_gain_ctrl_y0,		pp->dc_bnr_gain_ctrl_y0,\
												dc_bnr_gain_ctrl_x0,		pp->dc_bnr_gain_ctrl_x0,\
												dc_bnr_gain_ctrl_y1,		pp->dc_bnr_gain_ctrl_y1,\
												dc_bnr_gain_ctrl_x1,		pp->dc_bnr_gain_ctrl_x1);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				/* mnr */
				PE_P0R_L9B_QRd02(mnr_ctrl_00,	edge_gain_mapping_enable,	pp->edge_gain_mapping_enable,\
												sel_sd_hd,					pp->sel_sd_hd);
				PE_P0R_L9B_QRd01(mnr_ctrl_03,	x1_position,				pp->x1_position);
				PE_P0R_L9B_QRd04(mnr_ctrl_04,	x2_position,				pp->x2_position,\
												x3_position,				pp->x3_position,\
												x4_position,				pp->x4_position,\
												y1_position,				pp->y1_position);
				PE_P0R_L9B_QRd03(mnr_ctrl_05,	y2_position,				pp->y2_position,\
												y3_position,				pp->y3_position,\
												y4_position,				pp->y4_position);
				/* ac_bnr */
				PE_P0R_L9B_QRd03(bnr_ac_ctrl_00,motion_protect_enable,		pp->motion_protect_enable,\
												source_type,				pp->source_type,\
												fiter_type,					pp->fiter_type);
				PE_P0R_L9B_QRd03(bnr_ac_ctrl_01,strength_h_x0,				pp->strength_h_x0,\
												strength_h_x1,				pp->strength_h_x1,\
												detect_min_th,				pp->detect_min_th);
				PE_P0R_L9B_QRd02(bnr_ac_ctrl_02,strength_v_x0,				pp->strength_v_x0,\
												strength_v_x1,				pp->strength_v_x1);
				/* dc_bnr */
				PE_P0R_L9B_QRd03(bnr_dc_ctrl_00,ac_blockiness_adaptive_mode,pp->ac_blockiness_adaptive_mode,\
												motion_gain_enable,			pp->motion_gain_enable,\
												sd_hd_sel,					pp->sd_hd_sel);
				PE_P0R_L9B_QRd04(bnr_dc_ctrl_02,dc_bnr_gain_ctrl_y2,		pp->dc_bnr_gain_ctrl_y2,\
												dc_bnr_gain_ctrl_x2,		pp->dc_bnr_gain_ctrl_x2,\
												dc_bnr_gain_ctrl_y3,		pp->dc_bnr_gain_ctrl_y3,\
												dc_bnr_gain_ctrl_x3,		pp->dc_bnr_gain_ctrl_x3);
				PE_P0R_L9B_QRd04(bnr_dc_ctrl_03,dc_bnr_gain_ctrl_y0,		pp->dc_bnr_gain_ctrl_y0,\
												dc_bnr_gain_ctrl_x0,		pp->dc_bnr_gain_ctrl_x0,\
												dc_bnr_gain_ctrl_y1,		pp->dc_bnr_gain_ctrl_y1,\
												dc_bnr_gain_ctrl_x1,		pp->dc_bnr_gain_ctrl_x1);
			}
			PE_NRD_DBG_PRINT("get[%d] \n"\
				"mnr   : g_map_en:%d,  sd_hd:%d,  [x]:%d,%d,%d,%d,  [y]:%d,%d,%d,%d\n"\
				"ac_bnr: mo_p_en:%d,  src_type:%d,  flt_type:%d\n"\
				"ac_bnr: [str_h_x]:%d,%d,  det_min_th:%d,  [str_v_x]:%d,%d\n"\
				"dc_bnr: blki_adp:%d,  mo_g_en:%d,  sd_hd:%d\n"\
				"dc_bnr: [x,y]:%d,%d, %d,%d, %d,%d, %d,%d\n",\
				pp->win_id,\
				/* mnr */
				pp->edge_gain_mapping_enable,pp->sel_sd_hd,\
				pp->x1_position,pp->x2_position,pp->x3_position,pp->x4_position,\
				pp->y1_position,pp->y2_position,pp->y3_position,pp->y4_position,\
				/* ac_bnr */
				pp->motion_protect_enable,pp->source_type,pp->fiter_type,\
				pp->strength_h_x0,pp->strength_h_x1,pp->detect_min_th,\
				pp->strength_v_x0,pp->strength_v_x1,\
				/* dc_bnr */
				pp->ac_blockiness_adaptive_mode,pp->motion_gain_enable,pp->sd_hd_sel,\
				pp->dc_bnr_gain_ctrl_x0,pp->dc_bnr_gain_ctrl_y0,\
				pp->dc_bnr_gain_ctrl_x1,pp->dc_bnr_gain_ctrl_y1,\
				pp->dc_bnr_gain_ctrl_x2,pp->dc_bnr_gain_ctrl_y2,\
				pp->dc_bnr_gain_ctrl_x3,pp->dc_bnr_gain_ctrl_y3);
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set tnr common ctrl
 * - use input struct LX_PE_NRD_TNR2_CMN_T for H13BX
 * - use input struct LX_PE_NRD_TNR1_CMN_T for L9BX,H13AX
 * - use input struct LX_PE_NRD_TNR0_CMN_T for L9AX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_SetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_TNR2_CMN_T *pp=(LX_PE_NRD_TNR2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : auto_en:%d, y,c_g:%d,%d, adj_nt_en,val:%d,%d\n",pp->win_id,\
				pp->auto_mode_en,pp->y_gain,pp->c_gain,pp->adjust_nt_lvl,pp->adjust_nt_lvl_val);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_H13B0_QWr02(p0l_tnr_ctrl_13,	adjust_nt_lvl,		GET_BITS(pp->adjust_nt_lvl,0,1),\
													adjust_nt_lvl_val,	GET_BITS(pp->adjust_nt_lvl_val,0,8));
				PE_P0L_H13B0_QWr02(p0l_tnr_ctrl_18,	y_gain,				GET_BITS(pp->y_gain,0,8),\
													c_gain,				GET_BITS(pp->c_gain,0,8));
				PE_P1L_H13B0_QWr01(pe1_dse_ctrl_01,	reg_tnr_auto_en,	(pp->auto_mode_en)? 0x1:0x0);
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_H13B0_QWr02(p0r_tnr_ctrl_13,	adjust_nt_lvl,		GET_BITS(pp->adjust_nt_lvl,0,1),\
													adjust_nt_lvl_val,	GET_BITS(pp->adjust_nt_lvl_val,0,8));
				PE_P0R_H13B0_QWr02(p0r_tnr_ctrl_18,	y_gain,				GET_BITS(pp->y_gain,0,8),\
													c_gain,				GET_BITS(pp->c_gain,0,8));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			LX_PE_NRD_TNR1_CMN_T *pp=(LX_PE_NRD_TNR1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : y,c_g:%d,%d, adj_nt_en,val:%d,%d\n",pp->win_id,\
				pp->y_gain,pp->c_gain,pp->adjust_nt_lvl,pp->adjust_nt_lvl_val);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_H13_QWr02(p0l_tnr_ctrl_13,	adjust_nt_lvl,		GET_BITS(pp->adjust_nt_lvl,0,1),\
													adjust_nt_lvl_val,	GET_BITS(pp->adjust_nt_lvl_val,0,8));
				PE_P0L_H13_QWr02(p0l_tnr_ctrl_18,	y_gain,				GET_BITS(pp->y_gain,0,8),\
													c_gain,				GET_BITS(pp->c_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_H13_QWr02(p0r_tnr_ctrl_13,	adjust_nt_lvl,		GET_BITS(pp->adjust_nt_lvl,0,1),\
													adjust_nt_lvl_val,	GET_BITS(pp->adjust_nt_lvl_val,0,8));
				PE_P0R_H13_QWr02(p0r_tnr_ctrl_18,	y_gain,				GET_BITS(pp->y_gain,0,8),\
													c_gain,				GET_BITS(pp->c_gain,0,8));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_NRD_TNR1_CMN_T *pp=(LX_PE_NRD_TNR1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : auto:%d, y,c_g:%d,%d, adj_nt_en,val:%d,%d\n",\
				pp->win_id,pp->auto_mode,pp->y_gain,pp->c_gain,\
				pp->adjust_nt_lvl,pp->adjust_nt_lvl_val);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_L9B_QWr02(tnr_ctrl_13,	adjust_nt_lvl,		GET_BITS(pp->adjust_nt_lvl,0,1),\
												adjust_nt_lvl_val,	GET_BITS(pp->adjust_nt_lvl_val,0,8));
				PE_P0L_L9B_QWr02(tnr_ctrl_18,	y_gain,				GET_BITS(pp->y_gain,0,8),\
												c_gain,				GET_BITS(pp->c_gain,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_L9B_QWr02(tnr_ctrl_13,	adjust_nt_lvl,		GET_BITS(pp->adjust_nt_lvl,0,1),\
												adjust_nt_lvl_val,	GET_BITS(pp->adjust_nt_lvl_val,0,8));
				PE_P0R_L9B_QWr02(tnr_ctrl_18,	y_gain,				GET_BITS(pp->y_gain,0,8),\
												c_gain,				GET_BITS(pp->c_gain,0,8));
			}
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_NRD_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				ret = PE_FWI_L9_SetTnrAutoMode(pp);
				PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetTnrAutoMode() error.\n",__F__,__L__);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_NRD_TNR0_CMN_T *pp=(LX_PE_NRD_TNR0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] : en:%d,nt_lvl:%d\n",\
				pp->win_id,pp->tnr_enable,pp->adj_nt_lvl_val);
			ret = PE_FWI_SETDATA(PQL_IPC_SET_TNR, pp, sizeof(LX_PE_NRD_TNR0_CMN_T));
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_P0L_L9A_QWr02(p0l_tnr_ctrl_13,	adjust_nt_lvl,		(pp->tnr_enable)? 0x1:0x0,\
													adjust_nt_lvl_val,	GET_BITS(pp->adj_nt_lvl_val,0,8));
				PE_P0L_L9A_QWr02(p0l_tnr_ctrl_18,	y_gain,				(pp->tnr_enable)? 0x20:0xff,\
													c_gain,				(pp->tnr_enable)? 0x20:0xff);
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				PE_P0R_L9A_QWr02(p0r_tnr_ctrl_13,	adjust_nt_lvl,		(pp->tnr_enable)? 0x1:0x0,\
													adjust_nt_lvl_val,	GET_BITS(pp->adj_nt_lvl_val,0,8));
				PE_P0R_L9A_QWr02(p0r_tnr_ctrl_18,	y_gain,				(pp->tnr_enable)? 0x20:0xff,\
													c_gain,				(pp->tnr_enable)? 0x20:0xff);
			}
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get tnr common ctrl
 * - use input struct LX_PE_NRD_TNR2_CMN_T for H13BX
 * - use input struct LX_PE_NRD_TNR1_CMN_T for L9BX,H13AX
 * - use input struct LX_PE_NRD_TNR0_CMN_T for L9AX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_GetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_TNR2_CMN_T *pp=(LX_PE_NRD_TNR2_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13B0_QRd02(p0l_tnr_ctrl_13,	adjust_nt_lvl,		pp->adjust_nt_lvl,\
													adjust_nt_lvl_val,	pp->adjust_nt_lvl_val);
				PE_P0L_H13B0_QRd02(p0l_tnr_ctrl_18,	y_gain,				pp->y_gain,\
													c_gain,				pp->c_gain);
				PE_P1L_H13B0_QRd01(pe1_dse_ctrl_01,	reg_tnr_auto_en,	pp->auto_mode_en);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13B0_QRd02(p0r_tnr_ctrl_13,	adjust_nt_lvl,		pp->adjust_nt_lvl,\
													adjust_nt_lvl_val,	pp->adjust_nt_lvl_val);
				PE_P0R_H13B0_QRd02(p0r_tnr_ctrl_18,	y_gain,				pp->y_gain,\
													c_gain,				pp->c_gain);
				pp->auto_mode_en = 0xff;
			}
			PE_NRD_DBG_PRINT("get[%d] : auto_en:%d, y,c_g:%d,%d, adj_nt_en,val:%d,%d\n",pp->win_id,\
				pp->auto_mode_en,pp->y_gain,pp->c_gain,pp->adjust_nt_lvl,pp->adjust_nt_lvl_val);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			LX_PE_NRD_TNR1_CMN_T *pp=(LX_PE_NRD_TNR1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13_QRd02(p0l_tnr_ctrl_13,	adjust_nt_lvl,		pp->adjust_nt_lvl,\
													adjust_nt_lvl_val,	pp->adjust_nt_lvl_val);
				PE_P0L_H13_QRd02(p0l_tnr_ctrl_18,	y_gain,				pp->y_gain,\
													c_gain,				pp->c_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13_QRd02(p0r_tnr_ctrl_13,	adjust_nt_lvl,		pp->adjust_nt_lvl,\
													adjust_nt_lvl_val,	pp->adjust_nt_lvl_val);
				PE_P0R_H13_QRd02(p0r_tnr_ctrl_18,	y_gain,				pp->y_gain,\
													c_gain,				pp->c_gain);
			}
			PE_NRD_DBG_PRINT("get[%d] : y,c_g:%d,%d, adj_nt_en,val:%d,%d\n",pp->win_id,\
				pp->y_gain,pp->c_gain,pp->adjust_nt_lvl,pp->adjust_nt_lvl_val);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CMN_SETTINGS_T cmn_info;
			LX_PE_NRD_TNR1_CMN_T *pp=(LX_PE_NRD_TNR1_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9B_QRd02(tnr_ctrl_13,	adjust_nt_lvl,		pp->adjust_nt_lvl,\
												adjust_nt_lvl_val,	pp->adjust_nt_lvl_val);
				PE_P0L_L9B_QRd02(tnr_ctrl_18,	y_gain,				pp->y_gain,\
												c_gain,				pp->c_gain);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_L9B_QRd02(tnr_ctrl_13,	adjust_nt_lvl,		pp->adjust_nt_lvl,\
												adjust_nt_lvl_val,	pp->adjust_nt_lvl_val);
				PE_P0R_L9B_QRd02(tnr_ctrl_18,	y_gain,				pp->y_gain,\
												c_gain,				pp->c_gain);
			}
			ret = PE_CMN_GetCurCmnSettings(&cmn_info);
			PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_GetCurCmnSettings() error.\n",__F__,__L__);
			PE_NRD_DBG_PRINT("use_pe_fw : %s.\n",cmn_info.use_pe_fw? "yes":"no");
			if(cmn_info.use_pe_fw)
			{
				PE_FWI_L9_SETTINGS_T param;
				ret = PE_FWI_L9_GetCurFwiSettings(&param);
				PE_NRD_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_GetCurFwiSettings() error.\n",__F__,__L__);
				pp->auto_mode = param.tnr_ctrl.auto_enable? 1:0;
			}
			else
			{
				pp->auto_mode = 0;
			}
			PE_NRD_DBG_PRINT("get[%d] : auto:%d, y,c_g:%d,%d, adj_nt_en,val:%d,%d\n",\
				pp->win_id,pp->auto_mode,pp->y_gain,pp->c_gain,\
				pp->adjust_nt_lvl,pp->adjust_nt_lvl_val);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			LX_PE_NRD_TNR0_CMN_T *pp=(LX_PE_NRD_TNR0_CMN_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9A_QRd02(p0l_tnr_ctrl_13,	adjust_nt_lvl,		pp->tnr_enable,\
													adjust_nt_lvl_val,	pp->adj_nt_lvl_val);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_L9A_QRd02(p0r_tnr_ctrl_13,	adjust_nt_lvl,		pp->tnr_enable,\
													adjust_nt_lvl_val,	pp->adj_nt_lvl_val);
			}
			PE_NRD_DBG_PRINT("get[%d] : en:%d,nt_lvl:%d\n",\
				pp->win_id,pp->tnr_enable,pp->adj_nt_lvl_val);
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR2_DETAIL_T for H13BX
 * - use input struct LX_PE_NRD_TNR1_DETAIL_T for L9BX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_SetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_TNR2_DETAIL_T *pp=(LX_PE_NRD_TNR2_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] \n"\
				"ma:\nmotion: 	 coring_en (y,c): %d,%d, gain (y,c): %d,%d,\n"\
					 "         	 coring_th: %d, offset_en: %d, gain_en_var (m,a): %d,%d\n"\
					 "         	 wa_y(0,1,2,3):%d,%d,%d,%d, wa_x(0,1,2,3):%d,%d,%d,%d\n"\
					 "alph_gain: gain_x(p0,p1,p2,p3):%d,%d,%d,%d, gain_y(p0,p1,p2,p3):%d,%d,%d,%d\n"\
					 "alph_remap:ave_en:%d, mapping_y_en:%d, mapping_c_en:%d\n"\
					 "           map_y(x0,x1,x2,x3):%d,%d,%d,%d, map_y(y0,y1,y2,y3):%d,%d,%d,%d\n"\
					 "           map_c(x0,x1,x2,x3):%d,%d,%d,%d, map_c(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "adj_gain:  gm_en:%d, lpct:%d, avg_ts_en:%d, lpct_sel:%d\n"\
				     "           gm(x0,x1,x2,x3):%d,%d,%d,%d, gm(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           st(x0,x1,x2,x3):%d,%d,%d,%d, st(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           lpct(x0,x1,x2,x3):%d,%d,%d,%d, lpct(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           m_gain_en_var2:%d,\n"\
				     "           ctrl(x0,x1,y0,y1):%d,%d,%d,%d\n"\
				     "           sf_map_flt_en:%d, map_tap:%d, map_gain:%d\n"\
				     "           sf_th(0,1,2,3,4):%d,%d,%d,%d,%d\n"\
				     "           sf_mb(x0,x1,x2,x3):%d,%d,%d,%d, sf_mb(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           sf_gain_md:%d, sf_gain:%d, sf_en(y,c):%d,%d, sf_mo_exp_md:%d\n"\
				"mc:\n           sel_pels:%d, mamc_blend:%d, blend_sel:%d\n"\
				     "           blend(x0,x1,y0,y1):%d,%d,%d,%d\n"\
				"me:\n           hlf_pel_en:%d, smth(gain,en):%d,%d, gmv_smth(gain,en):%d,%d\n"\
				     "           mv0_th:%d, mv0_en:%d, sad_en:%d, sad_gm_en:%d\n"\
				     "           ctrl(x0,x1,y0,y1):%d,%d,%d,%d\n",\
				pp->win_id,\
				// ma: motion 
				pp->m_coring_en_y,pp->m_coring_en_c,pp->m_gain_y,pp->m_gain_c,\
				pp->m_coring_th,pp->m_offset_mode_en,pp->m_gain_en_var,pp->a_gain_en_var,\
				pp->wa_y0,pp->wa_y1,pp->wa_y2,pp->wa_y3,pp->wa_x0,pp->wa_x1,pp->wa_x2,pp->wa_x3,\
				// ma: alpha gain
				pp->luma_gain_p0_x,pp->luma_gain_p1_x,pp->luma_gain_p2_x,pp->luma_gain_p3_x,\
				pp->luma_gain_p0_y,pp->luma_gain_p1_y,pp->luma_gain_p2_y,pp->luma_gain_p3_y,\
				// alpha remapping
				pp->alpha_avg_en,pp->alpha_mapping_y_en,pp->alpha_mapping_c_en,\
				pp->alpha_mapping_y_x0,pp->alpha_mapping_y_x1,pp->alpha_mapping_y_x2,pp->alpha_mapping_y_x3,\
				pp->alpha_mapping_y_y0,pp->alpha_mapping_y_y1,pp->alpha_mapping_y_y2,pp->alpha_mapping_y_y3,\
				pp->alpha_mapping_c_x0,pp->alpha_mapping_c_x1,pp->alpha_mapping_c_x2,pp->alpha_mapping_c_x3,\
				pp->alpha_mapping_c_y0,pp->alpha_mapping_c_y1,pp->alpha_mapping_c_y2,pp->alpha_mapping_c_y3,\
				// adjust gain
				pp->nt_lvl_adjust_gm_enable,pp->nt_lvl_adjust_lpct_enable,\
				pp->nt_lvl_adjust_avg_ts_enable,pp->nt_lvl_adjust_lpct_sel,\
				pp->nt_lvl_gain_gm_x0,pp->nt_lvl_gain_gm_x1,pp->nt_lvl_gain_gm_x2,pp->nt_lvl_gain_gm_x3,\
				pp->nt_lvl_gain_gm_y0,pp->nt_lvl_gain_gm_y1,pp->nt_lvl_gain_gm_y2,pp->nt_lvl_gain_gm_y3,\
				pp->nt_lvl_gain_st_x0,pp->nt_lvl_gain_st_x1,pp->nt_lvl_gain_st_x2,pp->nt_lvl_gain_st_x3,\
				pp->nt_lvl_gain_st_y0,pp->nt_lvl_gain_st_y1,pp->nt_lvl_gain_st_y2,pp->nt_lvl_gain_st_y3,\
				pp->nt_lvl_gain_lpct_x0,pp->nt_lvl_gain_lpct_x1,pp->nt_lvl_gain_lpct_x2,pp->nt_lvl_gain_lpct_x3,\
				pp->nt_lvl_gain_lpct_y0,pp->nt_lvl_gain_lpct_y1,pp->nt_lvl_gain_lpct_y2,pp->nt_lvl_gain_lpct_y3,\
				pp->m_gain_en_var2,\
				pp->m_gain_ctrl2_x0,pp->m_gain_ctrl2_x1,pp->m_gain_ctrl2_y0,pp->m_gain_ctrl2_y1,\
				pp->sf_map_flt_en,pp->sf_map_tap,pp->sf_map_gain,\
				pp->sf_th0,pp->sf_th1,pp->sf_th2,pp->sf_th3,pp->sf_th4,\
				pp->sf_mb_x0,pp->sf_mb_x1,pp->sf_mb_x2,pp->sf_mb_x3,\
				pp->sf_mb_y0,pp->sf_mb_y1,pp->sf_mb_y2,pp->sf_mb_y3,\
				pp->sf_gain_mode,pp->sf_gain,pp->sf_blend_en_y,pp->sf_blend_en_c,pp->sf_blend_motion_exp_mode,\
				// mc: 
				pp->sad_sel_pels,pp->sad_mamc_blend,pp->mamc_blend_sel,\
				pp->mamc_blend_x0,pp->mamc_blend_x1,pp->mamc_blend_y0,pp->mamc_blend_y1,\
				// me: 
				pp->hme_half_pel_en,pp->mv_cost_smooth_gain,pp->mv_cost_smooth_en,\
				pp->mv_cost_gmv_smooth_gain,pp->mv_cost_gmv_smooth_en,\
				pp->mv0_protect_th,pp->mv0_protect_en,pp->sad_protect_en,pp->sad_protect_gm_en,\
				pp->mv_protect_control_x0,pp->mv_protect_control_x1,\
				pp->mv_protect_control_y0,pp->mv_protect_control_y1);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* ma: motion */
				PE_P0L_H13B0_QWr02(p0l_tnr_ctrl_38,	m_coring_en_c,		GET_BITS(pp->m_coring_en_c,0,1),\
													m_coring_en_y,		GET_BITS(pp->m_coring_en_y,0,1));
				PE_P0L_H13B0_QWr03(p0l_tnr_ctrl_38,	m_gain_c,			GET_BITS(pp->m_gain_c,0,4),\
													m_gain_y,			GET_BITS(pp->m_gain_y,0,4),\
													m_coring_th,		GET_BITS(pp->m_coring_th,0,6));
				PE_P0L_H13B0_QWr03(p0l_tnr_ctrl_02,	m_offset_mode_en,	GET_BITS(pp->m_offset_mode_en,0,1),\
													m_gain_en_var,		GET_BITS(pp->m_gain_en_var,0,1),\
													a_gain_en_var,		GET_BITS(pp->a_gain_en_var,0,1));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_03,	wa_y0,				GET_BITS(pp->wa_y0,0,8),\
													wa_y1,				GET_BITS(pp->wa_y1,0,8),\
													wa_x0,				GET_BITS(pp->wa_x0,0,8),\
													wa_x1,				GET_BITS(pp->wa_x1,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_29,	wa_y2,				GET_BITS(pp->wa_y2,0,8),\
													wa_y3,				GET_BITS(pp->wa_y3,0,8),\
													wa_x2,				GET_BITS(pp->wa_x2,0,8),\
													wa_x3,				GET_BITS(pp->wa_x3,0,8));
				/* ma: alpha gain */
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_19,	luma_gain_p0_x,			GET_BITS(pp->luma_gain_p0_x,0,8),\
													luma_gain_p1_x,			GET_BITS(pp->luma_gain_p1_x,0,8),\
													luma_gain_p2_x,			GET_BITS(pp->luma_gain_p2_x,0,8),\
													luma_gain_p3_x,			GET_BITS(pp->luma_gain_p3_x,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_20,	luma_gain_p0_y,			GET_BITS(pp->luma_gain_p0_y,0,8),\
													luma_gain_p1_y,			GET_BITS(pp->luma_gain_p1_y,0,8),\
													luma_gain_p2_y,			GET_BITS(pp->luma_gain_p2_y,0,8),\
													luma_gain_p3_y,			GET_BITS(pp->luma_gain_p3_y,0,8));
				/* ma: alhpa remapping*/
				PE_P0L_H13B0_QWr03(p0l_tnr_ctrl_00,	alpha_avg_en,		GET_BITS(pp->alpha_avg_en,0,1),\
													alpha_mapping_y_en,	GET_BITS(pp->alpha_mapping_y_en,0,8),\
													alpha_mapping_c_en,	GET_BITS(pp->alpha_mapping_c_en,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_23,	alpha_mapping_y_y0,	GET_BITS(pp->alpha_mapping_y_y0,0,8),\
													alpha_mapping_y_x0,	GET_BITS(pp->alpha_mapping_y_x0,0,8),\
													alpha_mapping_y_y1,	GET_BITS(pp->alpha_mapping_y_y1,0,8),\
													alpha_mapping_y_x1,	GET_BITS(pp->alpha_mapping_y_x1,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_24,	alpha_mapping_y_y2,	GET_BITS(pp->alpha_mapping_y_y2,0,8),\
													alpha_mapping_y_x2,	GET_BITS(pp->alpha_mapping_y_x2,0,8),\
													alpha_mapping_y_y3,	GET_BITS(pp->alpha_mapping_y_y3,0,8),\
													alpha_mapping_y_x3,	GET_BITS(pp->alpha_mapping_y_x3,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_25,	alpha_mapping_c_y0,	GET_BITS(pp->alpha_mapping_c_y0,0,8),\
													alpha_mapping_c_x0,	GET_BITS(pp->alpha_mapping_c_x0,0,8),\
													alpha_mapping_c_y1,	GET_BITS(pp->alpha_mapping_c_y1,0,8),\
													alpha_mapping_c_x1,	GET_BITS(pp->alpha_mapping_c_x1,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_26,	alpha_mapping_c_y2,	GET_BITS(pp->alpha_mapping_c_y2,0,8),\
													alpha_mapping_c_x2,	GET_BITS(pp->alpha_mapping_c_x2,0,8),\
													alpha_mapping_c_y3,	GET_BITS(pp->alpha_mapping_c_y3,0,8),\
													alpha_mapping_c_x3,	GET_BITS(pp->alpha_mapping_c_x3,0,8));
				/*ma: noise level adjust gain*/
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_00,	nt_lvl_adjust_gm_enable,		GET_BITS(pp->nt_lvl_adjust_gm_enable,0,1),\
													nt_lvl_adjust_lpct_enable,		GET_BITS(pp->nt_lvl_adjust_lpct_enable,0,1),\
													nt_lvl_adjust_avg_ts_enable,	GET_BITS(pp->nt_lvl_adjust_avg_ts_enable,0,1),\
													nt_lvl_adjust_lpct_sel,			GET_BITS(pp->nt_lvl_adjust_lpct_sel,0,1));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_04,	nt_lvl_gain_gm_y0,		GET_BITS(pp->nt_lvl_gain_gm_y0,0,8),\
													nt_lvl_gain_gm_x0,		GET_BITS(pp->nt_lvl_gain_gm_x0,0,8),\
													nt_lvl_gain_gm_y1,		GET_BITS(pp->nt_lvl_gain_gm_y1,0,8),\
													nt_lvl_gain_gm_x1,		GET_BITS(pp->nt_lvl_gain_gm_x1,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_12,	nt_lvl_gain_gm_y2,		GET_BITS(pp->nt_lvl_gain_gm_y2,0,8),\
													nt_lvl_gain_gm_x2,		GET_BITS(pp->nt_lvl_gain_gm_x2,0,8),\
													nt_lvl_gain_gm_y3,		GET_BITS(pp->nt_lvl_gain_gm_y3,0,8),\
													nt_lvl_gain_gm_x3,		GET_BITS(pp->nt_lvl_gain_gm_x3,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_28,	nt_lvl_gain_st_y0,		GET_BITS(pp->nt_lvl_gain_st_y0,0,8),\
													nt_lvl_gain_st_x0,		GET_BITS(pp->nt_lvl_gain_st_x0,0,8),\
													nt_lvl_gain_st_y1,		GET_BITS(pp->nt_lvl_gain_st_y1,0,8),\
													nt_lvl_gain_st_x1,		GET_BITS(pp->nt_lvl_gain_st_x1,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_30,	nt_lvl_gain_st_y2,		GET_BITS(pp->nt_lvl_gain_st_y2,0,8),\
													nt_lvl_gain_st_x2,		GET_BITS(pp->nt_lvl_gain_st_x2,0,8),\
													nt_lvl_gain_st_y3,		GET_BITS(pp->nt_lvl_gain_st_y3,0,8),\
													nt_lvl_gain_st_x3,		GET_BITS(pp->nt_lvl_gain_st_x3,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_32,	nt_lvl_gain_lpct_y0,	GET_BITS(pp->nt_lvl_gain_lpct_y0,0,8),\
													nt_lvl_gain_lpct_x0,	GET_BITS(pp->nt_lvl_gain_lpct_x0,0,8),\
													nt_lvl_gain_lpct_y1,	GET_BITS(pp->nt_lvl_gain_lpct_y1,0,8),\
													nt_lvl_gain_lpct_x1,	GET_BITS(pp->nt_lvl_gain_lpct_x1,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_33,	nt_lvl_gain_lpct_y2,	GET_BITS(pp->nt_lvl_gain_lpct_y2,0,8),\
													nt_lvl_gain_lpct_x2,	GET_BITS(pp->nt_lvl_gain_lpct_x2,0,8),\
													nt_lvl_gain_lpct_y3,	GET_BITS(pp->nt_lvl_gain_lpct_y3,0,8),\
													nt_lvl_gain_lpct_x3,	GET_BITS(pp->nt_lvl_gain_lpct_x3,0,8));
				PE_P0L_H13B0_QWr01(p0l_tnr_ctrl_02,	m_gain_en_var2,			GET_BITS(pp->m_gain_en_var2,0,1));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_48,	m_gain_ctrl2_y0,		GET_BITS(pp->m_gain_ctrl2_y0,0,8),\
													m_gain_ctrl2_x0,		GET_BITS(pp->m_gain_ctrl2_x0,0,8),\
													m_gain_ctrl2_y1,		GET_BITS(pp->m_gain_ctrl2_y1,0,8),\
													m_gain_ctrl2_x1,		GET_BITS(pp->m_gain_ctrl2_x1,0,8));
				PE_P0L_H13B0_QWr03(p0l_tnr_ctrl_40,	sf_map_flt_en,			GET_BITS(pp->sf_map_flt_en,0,1),\
													sf_map_tap,				GET_BITS(pp->sf_map_tap,0,2),\
													sf_map_gain,			GET_BITS(pp->sf_map_gain,0,6));
				PE_P0L_H13B0_QWr02(p0l_tnr_ctrl_40,	sf_th0,					GET_BITS(pp->sf_th0,0,8),\
													sf_th1,					GET_BITS(pp->sf_th1,0,8));
				PE_P0L_H13B0_QWr03(p0l_tnr_ctrl_41,	sf_th2,					GET_BITS(pp->sf_th2,0,8),\
													sf_th3,					GET_BITS(pp->sf_th3,0,8),\
													sf_th4,					GET_BITS(pp->sf_th4,0,8));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_42,	sf_mb_x0,				GET_BITS(pp->sf_mb_x0,0,8),\
													sf_mb_x1,				GET_BITS(pp->sf_mb_x1,0,8),\
													sf_mb_y0,				GET_BITS(pp->sf_mb_y0,0,8),\
													sf_mb_y1,				GET_BITS(pp->sf_mb_y1,0,8));													
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_44,	sf_mb_x2,				GET_BITS(pp->sf_mb_x2,0,8),\
													sf_mb_x3,				GET_BITS(pp->sf_mb_x3,0,8),\
													sf_mb_y2,				GET_BITS(pp->sf_mb_y2,0,8),\
													sf_mb_y3,				GET_BITS(pp->sf_mb_y3,0,8));
				PE_P0L_H13B0_QWr02(p0l_tnr_ctrl_45,	sf_gain_mode,			GET_BITS(pp->sf_gain_mode,0,1),\
													sf_gain,				GET_BITS(pp->sf_gain,0,4));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_36,	sf_blend_en_y,			GET_BITS(pp->sf_blend_en_y,0,1),\
													sf_blend_en_c,			GET_BITS(pp->sf_blend_en_c,0,1),\
													sf_blend_motion_exp_mode,	GET_BITS(pp->sf_blend_motion_exp_mode,0,2),\
													sad_sel_pels,			GET_BITS(pp->sad_sel_pels,0,1));
				/* mc */
				PE_P0L_H13B0_QWr01(p0l_tnr_ctrl_21,	sad_mamc_blend,		GET_BITS(pp->sad_mamc_blend,0,8));
				PE_P0L_H13B0_QWr01(p0l_tnr_ctrl_00,	mamc_blend_sel,		GET_BITS(pp->mamc_blend_sel,0,1));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_46,	mamc_blend_x0,		GET_BITS(pp->mamc_blend_x0,0,8),\
													mamc_blend_x1,		GET_BITS(pp->mamc_blend_x1,0,8),\
													mamc_blend_y0,		GET_BITS(pp->mamc_blend_y0,0,8),\
													mamc_blend_y1,		GET_BITS(pp->mamc_blend_y1,0,8));
				/* me */
				PE_P0L_H13B0_QWr03(p0l_tnr_ctrl_36,	hme_half_pel_en,		GET_BITS(pp->hme_half_pel_en,0,1),\
													mv_cost_smooth_gain,	GET_BITS(pp->mv_cost_smooth_gain,0,5),\
													mv_cost_smooth_en,		GET_BITS(pp->mv_cost_smooth_en,0,1));
				PE_P0L_H13B0_QWr02(p0l_tnr_ctrl_36,	mv0_protect_th,			GET_BITS(pp->mv0_protect_th,0,7),\
													mv0_protect_en,			GET_BITS(pp->mv0_protect_en,0,1));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_38,	mv_cost_gmv_smooth_gain,	GET_BITS(pp->mv_cost_gmv_smooth_gain,0,5),\
													mv_cost_gmv_smooth_en,		GET_BITS(pp->mv_cost_gmv_smooth_en,0,1),\
													sad_protect_en,				GET_BITS(pp->sad_protect_en,0,1),\
													sad_protect_gm_en,			GET_BITS(pp->sad_protect_gm_en,0,1));
				PE_P0L_H13B0_QWr04(p0l_tnr_ctrl_22,	mv_protect_control_x0,		GET_BITS(pp->mv_protect_control_x0,0,8),\
													mv_protect_control_x1,		GET_BITS(pp->mv_protect_control_x1,0,8),\
													mv_protect_control_y0,		GET_BITS(pp->mv_protect_control_y0,0,8),\
													mv_protect_control_y1,		GET_BITS(pp->mv_protect_control_y1,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* ma: motion */
				PE_P0R_H13B0_QWr02(p0r_tnr_ctrl_38,	m_coring_en_c,		GET_BITS(pp->m_coring_en_c,0,1),\
													m_coring_en_y,		GET_BITS(pp->m_coring_en_y,0,1));
				PE_P0R_H13B0_QWr03(p0r_tnr_ctrl_38,	m_gain_c,			GET_BITS(pp->m_gain_c,0,4),\
													m_gain_y,			GET_BITS(pp->m_gain_y,0,4),\
													m_coring_th,		GET_BITS(pp->m_coring_th,0,6));
				PE_P0R_H13B0_QWr03(p0r_tnr_ctrl_02,	m_offset_mode_en,	GET_BITS(pp->m_offset_mode_en,0,1),\
													m_gain_en_var,		GET_BITS(pp->m_gain_en_var,0,1),\
													a_gain_en_var,		GET_BITS(pp->a_gain_en_var,0,1));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_03,	wa_y0,				GET_BITS(pp->wa_y0,0,8),\
													wa_y1,				GET_BITS(pp->wa_y1,0,8),\
													wa_x0,				GET_BITS(pp->wa_x0,0,8),\
													wa_x1,				GET_BITS(pp->wa_x1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_29,	wa_y2,				GET_BITS(pp->wa_y2,0,8),\
													wa_y3,				GET_BITS(pp->wa_y3,0,8),\
													wa_x2,				GET_BITS(pp->wa_x2,0,8),\
													wa_x3,				GET_BITS(pp->wa_x3,0,8));
				/* ma: alpha gain */
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_19,	luma_gain_p0_x,			GET_BITS(pp->luma_gain_p0_x,0,8),\
													luma_gain_p1_x,			GET_BITS(pp->luma_gain_p1_x,0,8),\
													luma_gain_p2_x,			GET_BITS(pp->luma_gain_p2_x,0,8),\
													luma_gain_p3_x,			GET_BITS(pp->luma_gain_p3_x,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_20,	luma_gain_p0_y,			GET_BITS(pp->luma_gain_p0_y,0,8),\
													luma_gain_p1_y,			GET_BITS(pp->luma_gain_p1_y,0,8),\
													luma_gain_p2_y,			GET_BITS(pp->luma_gain_p2_y,0,8),\
													luma_gain_p3_y,			GET_BITS(pp->luma_gain_p3_y,0,8));
				/* ma: alhpa remapping*/
				PE_P0R_H13B0_QWr03(p0r_tnr_ctrl_00,	alpha_avg_en,		GET_BITS(pp->alpha_avg_en,0,1),\
													alpha_mapping_y_en,	GET_BITS(pp->alpha_mapping_y_en,0,8),\
													alpha_mapping_c_en,	GET_BITS(pp->alpha_mapping_c_en,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_23,	alpha_mapping_y_y0,	GET_BITS(pp->alpha_mapping_y_y0,0,8),\
													alpha_mapping_y_x0,	GET_BITS(pp->alpha_mapping_y_x0,0,8),\
													alpha_mapping_y_y1,	GET_BITS(pp->alpha_mapping_y_y1,0,8),\
													alpha_mapping_y_x1,	GET_BITS(pp->alpha_mapping_y_x1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_24,	alpha_mapping_y_y2,	GET_BITS(pp->alpha_mapping_y_y2,0,8),\
													alpha_mapping_y_x2,	GET_BITS(pp->alpha_mapping_y_x2,0,8),\
													alpha_mapping_y_y3,	GET_BITS(pp->alpha_mapping_y_y3,0,8),\
													alpha_mapping_y_x3,	GET_BITS(pp->alpha_mapping_y_x3,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_25,	alpha_mapping_c_y0,	GET_BITS(pp->alpha_mapping_c_y0,0,8),\
													alpha_mapping_c_x0,	GET_BITS(pp->alpha_mapping_c_x0,0,8),\
													alpha_mapping_c_y1,	GET_BITS(pp->alpha_mapping_c_y1,0,8),\
													alpha_mapping_c_x1,	GET_BITS(pp->alpha_mapping_c_x1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_26,	alpha_mapping_c_y2,	GET_BITS(pp->alpha_mapping_c_y2,0,8),\
													alpha_mapping_c_x2,	GET_BITS(pp->alpha_mapping_c_x2,0,8),\
													alpha_mapping_c_y3,	GET_BITS(pp->alpha_mapping_c_y3,0,8),\
													alpha_mapping_c_x3,	GET_BITS(pp->alpha_mapping_c_x3,0,8));
				/*ma: noise level adjust gain*/
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_00,	nt_lvl_adjust_gm_enable,		GET_BITS(pp->nt_lvl_adjust_gm_enable,0,1),\
													nt_lvl_adjust_lpct_enable,		GET_BITS(pp->nt_lvl_adjust_lpct_enable,0,1),\
													nt_lvl_adjust_avg_ts_enable,	GET_BITS(pp->nt_lvl_adjust_avg_ts_enable,0,1),\
													nt_lvl_adjust_lpct_sel,			GET_BITS(pp->nt_lvl_adjust_lpct_sel,0,1));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_04,	nt_lvl_gain_gm_y0,		GET_BITS(pp->nt_lvl_gain_gm_y0,0,8),\
													nt_lvl_gain_gm_x0,		GET_BITS(pp->nt_lvl_gain_gm_x0,0,8),\
													nt_lvl_gain_gm_y1,		GET_BITS(pp->nt_lvl_gain_gm_y1,0,8),\
													nt_lvl_gain_gm_x1,		GET_BITS(pp->nt_lvl_gain_gm_x1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_12,	nt_lvl_gain_gm_y2,		GET_BITS(pp->nt_lvl_gain_gm_y2,0,8),\
													nt_lvl_gain_gm_x2,		GET_BITS(pp->nt_lvl_gain_gm_x2,0,8),\
													nt_lvl_gain_gm_y3,		GET_BITS(pp->nt_lvl_gain_gm_y3,0,8),\
													nt_lvl_gain_gm_x3,		GET_BITS(pp->nt_lvl_gain_gm_x3,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_28,	nt_lvl_gain_st_y0,		GET_BITS(pp->nt_lvl_gain_st_y0,0,8),\
													nt_lvl_gain_st_x0,		GET_BITS(pp->nt_lvl_gain_st_x0,0,8),\
													nt_lvl_gain_st_y1,		GET_BITS(pp->nt_lvl_gain_st_y1,0,8),\
													nt_lvl_gain_st_x1,		GET_BITS(pp->nt_lvl_gain_st_x1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_30,	nt_lvl_gain_st_y2,		GET_BITS(pp->nt_lvl_gain_st_y2,0,8),\
													nt_lvl_gain_st_x2,		GET_BITS(pp->nt_lvl_gain_st_x2,0,8),\
													nt_lvl_gain_st_y3,		GET_BITS(pp->nt_lvl_gain_st_y3,0,8),\
													nt_lvl_gain_st_x3,		GET_BITS(pp->nt_lvl_gain_st_x3,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_32,	nt_lvl_gain_lpct_y0,	GET_BITS(pp->nt_lvl_gain_lpct_y0,0,8),\
													nt_lvl_gain_lpct_x0,	GET_BITS(pp->nt_lvl_gain_lpct_x0,0,8),\
													nt_lvl_gain_lpct_y1,	GET_BITS(pp->nt_lvl_gain_lpct_y1,0,8),\
													nt_lvl_gain_lpct_x1,	GET_BITS(pp->nt_lvl_gain_lpct_x1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_33,	nt_lvl_gain_lpct_y2,	GET_BITS(pp->nt_lvl_gain_lpct_y2,0,8),\
													nt_lvl_gain_lpct_x2,	GET_BITS(pp->nt_lvl_gain_lpct_x2,0,8),\
													nt_lvl_gain_lpct_y3,	GET_BITS(pp->nt_lvl_gain_lpct_y3,0,8),\
													nt_lvl_gain_lpct_x3,	GET_BITS(pp->nt_lvl_gain_lpct_x3,0,8));
				PE_P0R_H13B0_QWr01(p0r_tnr_ctrl_02,	m_gain_en_var2,			GET_BITS(pp->m_gain_en_var2,0,1));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_48,	m_gain_ctrl2_y0,		GET_BITS(pp->m_gain_ctrl2_y0,0,8),\
													m_gain_ctrl2_x0,		GET_BITS(pp->m_gain_ctrl2_x0,0,8),\
													m_gain_ctrl2_y1,		GET_BITS(pp->m_gain_ctrl2_y1,0,8),\
													m_gain_ctrl2_x1,		GET_BITS(pp->m_gain_ctrl2_x1,0,8));
				PE_P0R_H13B0_QWr03(p0r_tnr_ctrl_40,	sf_map_flt_en,			GET_BITS(pp->sf_map_flt_en,0,1),\
													sf_map_tap,				GET_BITS(pp->sf_map_tap,0,2),\
													sf_map_gain,			GET_BITS(pp->sf_map_gain,0,6));
				PE_P0R_H13B0_QWr02(p0r_tnr_ctrl_40,	sf_th0,					GET_BITS(pp->sf_th0,0,8),\
													sf_th1,					GET_BITS(pp->sf_th1,0,8));
				PE_P0R_H13B0_QWr03(p0r_tnr_ctrl_41,	sf_th2,					GET_BITS(pp->sf_th2,0,8),\
													sf_th3,					GET_BITS(pp->sf_th3,0,8),\
													sf_th4,					GET_BITS(pp->sf_th4,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_42,	sf_mb_x0,				GET_BITS(pp->sf_mb_x0,0,8),\
													sf_mb_x1,				GET_BITS(pp->sf_mb_x1,0,8),\
													sf_mb_y0,				GET_BITS(pp->sf_mb_y0,0,8),\
													sf_mb_y1,				GET_BITS(pp->sf_mb_y1,0,8));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_44,	sf_mb_x2,				GET_BITS(pp->sf_mb_x2,0,8),\
													sf_mb_x3,				GET_BITS(pp->sf_mb_x3,0,8),\
													sf_mb_y2,				GET_BITS(pp->sf_mb_y2,0,8),\
													sf_mb_y3,				GET_BITS(pp->sf_mb_y3,0,8));
				PE_P0R_H13B0_QWr02(p0r_tnr_ctrl_45,	sf_gain_mode,			GET_BITS(pp->sf_gain_mode,0,1),\
													sf_gain,				GET_BITS(pp->sf_gain,0,4));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_36,	sf_blend_en_y,			GET_BITS(pp->sf_blend_en_y,0,1),\
													sf_blend_en_c,			GET_BITS(pp->sf_blend_en_c,0,1),\
													sf_blend_motion_exp_mode,	GET_BITS(pp->sf_blend_motion_exp_mode,0,2),\
													sad_sel_pels,			GET_BITS(pp->sad_sel_pels,0,1));
				/* mc */
				PE_P0R_H13B0_QWr01(p0r_tnr_ctrl_21,	sad_mamc_blend,		GET_BITS(pp->sad_mamc_blend,0,8));
				PE_P0R_H13B0_QWr01(p0r_tnr_ctrl_00,	mamc_blend_sel,		GET_BITS(pp->mamc_blend_sel,0,1));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_46,	mamc_blend_x0,		GET_BITS(pp->mamc_blend_x0,0,8),\
													mamc_blend_x1,		GET_BITS(pp->mamc_blend_x1,0,8),\
													mamc_blend_y0,		GET_BITS(pp->mamc_blend_y0,0,8),\
													mamc_blend_y1,		GET_BITS(pp->mamc_blend_y1,0,8));
				/* me */
				PE_P0R_H13B0_QWr03(p0r_tnr_ctrl_36,	hme_half_pel_en,		GET_BITS(pp->hme_half_pel_en,0,1),\
													mv_cost_smooth_gain,	GET_BITS(pp->mv_cost_smooth_gain,0,5),\
													mv_cost_smooth_en,		GET_BITS(pp->mv_cost_smooth_en,0,1));
				PE_P0R_H13B0_QWr02(p0r_tnr_ctrl_36,	mv0_protect_th,			GET_BITS(pp->mv0_protect_th,0,7),\
													mv0_protect_en,			GET_BITS(pp->mv0_protect_en,0,1));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_38,	mv_cost_gmv_smooth_gain,	GET_BITS(pp->mv_cost_gmv_smooth_gain,0,5),\
													mv_cost_gmv_smooth_en,		GET_BITS(pp->mv_cost_gmv_smooth_en,0,1),\
													sad_protect_en,				GET_BITS(pp->sad_protect_en,0,1),\
													sad_protect_gm_en,			GET_BITS(pp->sad_protect_gm_en,0,1));
				PE_P0R_H13B0_QWr04(p0r_tnr_ctrl_22,	mv_protect_control_x0,		GET_BITS(pp->mv_protect_control_x0,0,8),\
													mv_protect_control_x1,		GET_BITS(pp->mv_protect_control_x1,0,8),\
													mv_protect_control_y0,		GET_BITS(pp->mv_protect_control_y0,0,8),\
													mv_protect_control_y1,		GET_BITS(pp->mv_protect_control_y1,0,8));
				}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_NRD_TNR1_DETAIL_T *pp=(LX_PE_NRD_TNR1_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			PE_NRD_DBG_PRINT("set[%d] \n"\
				"motion histo                : %d, %d, %d, %d\n"\
				"alpha gain - gm gain        : %d,  [y,x]:%d,%d, %d,%d, %d,%d, %d,%d\n"\
				"alpha gain - avg st gain    : %d,  [y,x]:%d,%d, %d,%d, %d,%d, %d,%d\n"\
				"alpha lut                   : %d, %d, %d, %d, %d, %d, %d, %d\n"\
				"adjust alpha                : %d, %d, %d, %d\n"\
				"adjust alpha - s. var to wa : %d,  [x]:%d,%d,%d,%d,  [y]:%d,%d,%d,%d\n",\
				pp->win_id,\
				/* motion histo(n-lvl estimate) */
				pp->calc_motion_flt_enable,pp->calc_motion_flt_type,\
				pp->y_th_lo,pp->y_th_hi,\
				/* alpha gain(n-lvl gaining), gm gain */
				pp->nt_lvl_adjust_gm_enable,pp->nt_lvl_gain_gm_y0,pp->nt_lvl_gain_gm_x0,\
				pp->nt_lvl_gain_gm_y1,pp->nt_lvl_gain_gm_x1,pp->nt_lvl_gain_gm_y2,\
				pp->nt_lvl_gain_gm_x2,pp->nt_lvl_gain_gm_y3,pp->nt_lvl_gain_gm_x3,\
				/* alpha gain(n-lvl gaining), avg st gain */
				pp->nt_lvl_adjust_avg_ts_enable,pp->nt_lvl_gain_st_y0,\
				pp->nt_lvl_gain_st_x0,pp->nt_lvl_gain_st_y1,pp->nt_lvl_gain_st_x1,\
				pp->nt_lvl_gain_st_y2,pp->nt_lvl_gain_st_x2,pp->nt_lvl_gain_st_y3,\
				pp->nt_lvl_gain_st_x3,\
				/* alpha lut(n-lvl apply) */
				pp->alpha_lut_ind0,pp->alpha_lut_ind1,pp->alpha_lut_ind2,\
				pp->alpha_lut_ind3,pp->alpha_lut_ind4,pp->alpha_lut_ind5,\
				pp->alpha_lut_ind6,pp->alpha_lut_ind7,\
				/* adjust alpha(alpha gaining), adjust alpha */
				pp->adj_alpha_nt_lvl_th0,pp->adj_alpha_nt_lvl_th1,\
				pp->adj_alpha_k0,pp->adj_alpha_k1,\
				/* adjust alpha(alpha gaining), s. var --> WA */
				pp->wa_enable,pp->wa_x0,pp->wa_x1,pp->wa_x2,pp->wa_x3,\
				pp->wa_y0,pp->wa_y1,pp->wa_y2,pp->wa_y3);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				/* top */
				PE_P0L_L9B_QWr05(tnr_ctrl_00,	wa_enable,					GET_BITS(pp->wa_enable,0,1),\
												calc_motion_flt_enable,		GET_BITS(pp->calc_motion_flt_enable,0,1),\
												calc_motion_flt_type,		GET_BITS(pp->calc_motion_flt_type,0,1),\
												nt_lvl_adjust_gm_enable,	GET_BITS(pp->nt_lvl_adjust_gm_enable,0,1),\
												nt_lvl_adjust_avg_ts_enable,GET_BITS(pp->nt_lvl_adjust_avg_ts_enable,0,1));
				/* motion histo(n-lvl estimate) */
				PE_P0L_L9B_QWr02(tnr_ctrl_01,	y_th_lo,			GET_BITS(pp->y_th_lo,0,10),\
												y_th_hi,			GET_BITS(pp->y_th_hi,0,10));
				/* alpha gain(n-lvl gaining), gm gain */
				PE_P0L_L9B_QWr04(tnr_ctrl_04,	nt_lvl_gain_gm_y0,	GET_BITS(pp->nt_lvl_gain_gm_y0,0,8),\
												nt_lvl_gain_gm_x0,	GET_BITS(pp->nt_lvl_gain_gm_x0,0,8),\
												nt_lvl_gain_gm_y1,	GET_BITS(pp->nt_lvl_gain_gm_y1,0,8),\
												nt_lvl_gain_gm_x1,	GET_BITS(pp->nt_lvl_gain_gm_x1,0,8));
				PE_P0L_L9B_QWr04(tnr_ctrl_12,	nt_lvl_gain_gm_y2,	GET_BITS(pp->nt_lvl_gain_gm_y2,0,8),\
												nt_lvl_gain_gm_x2,	GET_BITS(pp->nt_lvl_gain_gm_x2,0,8),\
												nt_lvl_gain_gm_y3,	GET_BITS(pp->nt_lvl_gain_gm_y3,0,8),\
												nt_lvl_gain_gm_x3,	GET_BITS(pp->nt_lvl_gain_gm_x3,0,8));
				/* alpha gain(n-lvl gaining), avg st gain */
				PE_P0L_L9B_QWr04(tnr_ctrl_28,	nt_lvl_gain_st_y0,	GET_BITS(pp->nt_lvl_gain_st_y0,0,8),\
												nt_lvl_gain_st_x0,	GET_BITS(pp->nt_lvl_gain_st_x0,0,8),\
												nt_lvl_gain_st_y1,	GET_BITS(pp->nt_lvl_gain_st_y1,0,8),\
												nt_lvl_gain_st_x1,	GET_BITS(pp->nt_lvl_gain_st_x1,0,8));
				PE_P0L_L9B_QWr04(tnr_ctrl_30,	nt_lvl_gain_st_y2,	GET_BITS(pp->nt_lvl_gain_st_y2,0,8),\
												nt_lvl_gain_st_x2,	GET_BITS(pp->nt_lvl_gain_st_x2,0,8),\
												nt_lvl_gain_st_y3,	GET_BITS(pp->nt_lvl_gain_st_y3,0,8),\
												nt_lvl_gain_st_x3,	GET_BITS(pp->nt_lvl_gain_st_x3,0,8));
				/* alpha lut(n-lvl apply) */
				PE_P0L_L9B_QWr04(tnr_ctrl_07,	alpha_lut_ind0,		GET_BITS(pp->alpha_lut_ind0,0,8),\
												alpha_lut_ind1,		GET_BITS(pp->alpha_lut_ind1,0,8),\
												alpha_lut_ind2,		GET_BITS(pp->alpha_lut_ind2,0,8),\
												alpha_lut_ind3,		GET_BITS(pp->alpha_lut_ind3,0,8));
				PE_P0L_L9B_QWr03(tnr_ctrl_08,	alpha_lut_ind4,		GET_BITS(pp->alpha_lut_ind4,0,8),\
												alpha_lut_ind5,		GET_BITS(pp->alpha_lut_ind5,0,8),\
												alpha_lut_ind6,		GET_BITS(pp->alpha_lut_ind6,0,8));
				PE_P0L_L9B_QWr01(tnr_ctrl_02,	alpha_lut_ind7,		GET_BITS(pp->alpha_lut_ind7,0,8));
				/* adjust alpha(alpha gaining), adjust alpha */
				PE_P0L_L9B_QWr01(tnr_ctrl_05,	adj_alpha_nt_lvl_th0,	GET_BITS(pp->adj_alpha_nt_lvl_th0,0,8));
				PE_P0L_L9B_QWr01(tnr_ctrl_08,	adj_alpha_nt_lvl_th1,	GET_BITS(pp->adj_alpha_nt_lvl_th1,0,8));
				PE_P0L_L9B_QWr02(tnr_ctrl_06,	adj_alpha_k0,			GET_BITS(pp->adj_alpha_k0,0,8),\
												adj_alpha_k1,			GET_BITS(pp->adj_alpha_k1,0,8));
				/* adjust alpha(alpha gaining), s. var --> WA */
				PE_P0L_L9B_QWr04(tnr_ctrl_03,	wa_y0,					GET_BITS(pp->wa_y0,0,8),\
												wa_y1,					GET_BITS(pp->wa_y1,0,8),\
												wa_x0,					GET_BITS(pp->wa_x0,0,8),\
												wa_x1,					GET_BITS(pp->wa_x1,0,8));
				PE_P0L_L9B_QWr04(tnr_ctrl_29,	wa_y2,					GET_BITS(pp->wa_y2,0,8),\
												wa_y3,					GET_BITS(pp->wa_y3,0,8),\
												wa_x2,					GET_BITS(pp->wa_x2,0,8),\
												wa_x3,					GET_BITS(pp->wa_x3,0,8));
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* top */
				PE_P0R_L9B_QWr05(tnr_ctrl_00,	wa_enable,					GET_BITS(pp->wa_enable,0,1),\
												calc_motion_flt_enable,		GET_BITS(pp->calc_motion_flt_enable,0,1),\
												calc_motion_flt_type,		GET_BITS(pp->calc_motion_flt_type,0,1),\
												nt_lvl_adjust_gm_enable,	GET_BITS(pp->nt_lvl_adjust_gm_enable,0,1),\
												nt_lvl_adjust_avg_ts_enable,GET_BITS(pp->nt_lvl_adjust_avg_ts_enable,0,1));
				/* motion histo(n-lvl estimate) */
				PE_P0R_L9B_QWr02(tnr_ctrl_01,	y_th_lo,			GET_BITS(pp->y_th_lo,0,10),\
												y_th_hi,			GET_BITS(pp->y_th_hi,0,10));
				/* alpha gain(n-lvl gaining), gm gain */
				PE_P0R_L9B_QWr04(tnr_ctrl_04,	nt_lvl_gain_gm_y0,	GET_BITS(pp->nt_lvl_gain_gm_y0,0,8),\
												nt_lvl_gain_gm_x0,	GET_BITS(pp->nt_lvl_gain_gm_x0,0,8),\
												nt_lvl_gain_gm_y1,	GET_BITS(pp->nt_lvl_gain_gm_y1,0,8),\
												nt_lvl_gain_gm_x1,	GET_BITS(pp->nt_lvl_gain_gm_x1,0,8));
				PE_P0R_L9B_QWr04(tnr_ctrl_12,	nt_lvl_gain_gm_y2,	GET_BITS(pp->nt_lvl_gain_gm_y2,0,8),\
												nt_lvl_gain_gm_x2,	GET_BITS(pp->nt_lvl_gain_gm_x2,0,8),\
												nt_lvl_gain_gm_y3,	GET_BITS(pp->nt_lvl_gain_gm_y3,0,8),\
												nt_lvl_gain_gm_x3,	GET_BITS(pp->nt_lvl_gain_gm_x3,0,8));
				/* alpha gain(n-lvl gaining), avg st gain */
				PE_P0R_L9B_QWr04(tnr_ctrl_28,	nt_lvl_gain_st_y0,	GET_BITS(pp->nt_lvl_gain_st_y0,0,8),\
												nt_lvl_gain_st_x0,	GET_BITS(pp->nt_lvl_gain_st_x0,0,8),\
												nt_lvl_gain_st_y1,	GET_BITS(pp->nt_lvl_gain_st_y1,0,8),\
												nt_lvl_gain_st_x1,	GET_BITS(pp->nt_lvl_gain_st_x1,0,8));
				PE_P0R_L9B_QWr04(tnr_ctrl_30,	nt_lvl_gain_st_y2,	GET_BITS(pp->nt_lvl_gain_st_y2,0,8),\
												nt_lvl_gain_st_x2,	GET_BITS(pp->nt_lvl_gain_st_x2,0,8),\
												nt_lvl_gain_st_y3,	GET_BITS(pp->nt_lvl_gain_st_y3,0,8),\
												nt_lvl_gain_st_x3,	GET_BITS(pp->nt_lvl_gain_st_x3,0,8));
				/* alpha lut(n-lvl apply) */
				PE_P0R_L9B_QWr04(tnr_ctrl_07,	alpha_lut_ind0,		GET_BITS(pp->alpha_lut_ind0,0,8),\
												alpha_lut_ind1,		GET_BITS(pp->alpha_lut_ind1,0,8),\
												alpha_lut_ind2,		GET_BITS(pp->alpha_lut_ind2,0,8),\
												alpha_lut_ind3,		GET_BITS(pp->alpha_lut_ind3,0,8));
				PE_P0R_L9B_QWr03(tnr_ctrl_08,	alpha_lut_ind4,		GET_BITS(pp->alpha_lut_ind4,0,8),\
												alpha_lut_ind5,		GET_BITS(pp->alpha_lut_ind5,0,8),\
												alpha_lut_ind6,		GET_BITS(pp->alpha_lut_ind6,0,8));
				PE_P0R_L9B_QWr01(tnr_ctrl_02,	alpha_lut_ind7,		GET_BITS(pp->alpha_lut_ind7,0,8));
				/* adjust alpha(alpha gaining), adjust alpha */
				PE_P0R_L9B_QWr01(tnr_ctrl_05,	adj_alpha_nt_lvl_th0,	GET_BITS(pp->adj_alpha_nt_lvl_th0,0,8));
				PE_P0R_L9B_QWr01(tnr_ctrl_08,	adj_alpha_nt_lvl_th1,	GET_BITS(pp->adj_alpha_nt_lvl_th1,0,8));
				PE_P0R_L9B_QWr02(tnr_ctrl_06,	adj_alpha_k0,			GET_BITS(pp->adj_alpha_k0,0,8),\
												adj_alpha_k1,			GET_BITS(pp->adj_alpha_k1,0,8));
				/* adjust alpha(alpha gaining), s. var --> WA */
				PE_P0R_L9B_QWr04(tnr_ctrl_03,	wa_y0,					GET_BITS(pp->wa_y0,0,8),\
												wa_y1,					GET_BITS(pp->wa_y1,0,8),\
												wa_x0,					GET_BITS(pp->wa_x0,0,8),\
												wa_x1,					GET_BITS(pp->wa_x1,0,8));
				PE_P0R_L9B_QWr04(tnr_ctrl_29,	wa_y2,					GET_BITS(pp->wa_y2,0,8),\
												wa_y3,					GET_BITS(pp->wa_y3,0,8),\
												wa_x2,					GET_BITS(pp->wa_x2,0,8),\
												wa_x3,					GET_BITS(pp->wa_x3,0,8));
			}
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR2_DETAIL_T for H13BX
 * - use input struct LX_PE_NRD_TNR1_DETAIL_T for L9BX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
static int PE_NRD_GetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		win_id = LX_PE_WIN_0;	/* to avoid warning(unused variable) */
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			LX_PE_NRD_TNR2_DETAIL_T *pp=(LX_PE_NRD_TNR2_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(pp->win_id))
			{
				// ma: motion 
				PE_P0L_H13B0_QRd02(p0l_tnr_ctrl_38,	m_coring_en_c,		pp->m_coring_en_c,\
													m_coring_en_y,		pp->m_coring_en_y);
				PE_P0L_H13B0_QRd03(p0l_tnr_ctrl_38,	m_gain_c,			pp->m_gain_c,\
													m_gain_y,			pp->m_gain_y,\
													m_coring_th,		pp->m_coring_th);
				PE_P0L_H13B0_QRd03(p0l_tnr_ctrl_02,	m_offset_mode_en,	pp->m_offset_mode_en,\
													m_gain_en_var,		pp->m_gain_en_var,\
													a_gain_en_var,		pp->a_gain_en_var);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_03,	wa_y0,				pp->wa_y0,\
													wa_y1,				pp->wa_y1,\
													wa_x0,				pp->wa_x0,\
													wa_x1,				pp->wa_x1);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_29,	wa_y2,				pp->wa_y2,\
													wa_y3,				pp->wa_y3,\
													wa_x2,				pp->wa_x2,\
													wa_x3,				pp->wa_x3);
				// ma: alpha gain 
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_19,	luma_gain_p0_x,			pp->luma_gain_p0_x,\
													luma_gain_p1_x,			pp->luma_gain_p1_x,\
													luma_gain_p2_x,			pp->luma_gain_p2_x,\
													luma_gain_p3_x,			pp->luma_gain_p3_x);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_20,	luma_gain_p0_y,			pp->luma_gain_p0_y,\
													luma_gain_p1_y,			pp->luma_gain_p1_y,\
													luma_gain_p2_y,			pp->luma_gain_p2_y,\
													luma_gain_p3_y,			pp->luma_gain_p3_y);
				// ma: alhpa remapping
				PE_P0L_H13B0_QRd03(p0l_tnr_ctrl_00,	alpha_avg_en,		pp->alpha_avg_en,\
													alpha_mapping_y_en,	pp->alpha_mapping_y_en,\
													alpha_mapping_c_en,	pp->alpha_mapping_c_en);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_23,	alpha_mapping_y_y0,	pp->alpha_mapping_y_y0,\
													alpha_mapping_y_x0,	pp->alpha_mapping_y_x0,\
													alpha_mapping_y_y1,	pp->alpha_mapping_y_y1,\
													alpha_mapping_y_x1,	pp->alpha_mapping_y_x1);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_24,	alpha_mapping_y_y2,	pp->alpha_mapping_y_y2,\
													alpha_mapping_y_x2,	pp->alpha_mapping_y_x2,\
													alpha_mapping_y_y3,	pp->alpha_mapping_y_y3,\
													alpha_mapping_y_x3,	pp->alpha_mapping_y_x3);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_25,	alpha_mapping_c_y0,	pp->alpha_mapping_c_y0,\
													alpha_mapping_c_x0,	pp->alpha_mapping_c_x0,\
													alpha_mapping_c_y1,	pp->alpha_mapping_c_y1,\
													alpha_mapping_c_x1,	pp->alpha_mapping_c_x1);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_26,	alpha_mapping_c_y2,	pp->alpha_mapping_c_y2,\
													alpha_mapping_c_x2,	pp->alpha_mapping_c_x2,\
													alpha_mapping_c_y3,	pp->alpha_mapping_c_y3,\
													alpha_mapping_c_x3,	pp->alpha_mapping_c_x3);
				//ma: noise level adjust gain
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_00,	nt_lvl_adjust_gm_enable,		pp->nt_lvl_adjust_gm_enable,\
													nt_lvl_adjust_lpct_enable,		pp->nt_lvl_adjust_lpct_enable,\
													nt_lvl_adjust_avg_ts_enable,	pp->nt_lvl_adjust_avg_ts_enable,\
													nt_lvl_adjust_lpct_sel,			pp->nt_lvl_adjust_lpct_sel);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_04,	nt_lvl_gain_gm_y0,		pp->nt_lvl_gain_gm_y0,\
													nt_lvl_gain_gm_x0,		pp->nt_lvl_gain_gm_x0,\
													nt_lvl_gain_gm_y1,		pp->nt_lvl_gain_gm_y1,\
													nt_lvl_gain_gm_x1,		pp->nt_lvl_gain_gm_x1);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_12,	nt_lvl_gain_gm_y2,		pp->nt_lvl_gain_gm_y2,\
													nt_lvl_gain_gm_x2,		pp->nt_lvl_gain_gm_x2,\
													nt_lvl_gain_gm_y3,		pp->nt_lvl_gain_gm_y3,\
													nt_lvl_gain_gm_x3,		pp->nt_lvl_gain_gm_x3);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_28,	nt_lvl_gain_st_y0,		pp->nt_lvl_gain_st_y0,\
													nt_lvl_gain_st_x0,		pp->nt_lvl_gain_st_x0,\
													nt_lvl_gain_st_y1,		pp->nt_lvl_gain_st_y1,\
													nt_lvl_gain_st_x1,		pp->nt_lvl_gain_st_x1);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_30,	nt_lvl_gain_st_y2,		pp->nt_lvl_gain_st_y2,\
													nt_lvl_gain_st_x2,		pp->nt_lvl_gain_st_x2,\
													nt_lvl_gain_st_y3,		pp->nt_lvl_gain_st_y3,\
													nt_lvl_gain_st_x3,		pp->nt_lvl_gain_st_x3);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_32,	nt_lvl_gain_lpct_y0,	pp->nt_lvl_gain_lpct_y0,\
													nt_lvl_gain_lpct_x0,	pp->nt_lvl_gain_lpct_x0,\
													nt_lvl_gain_lpct_y1,	pp->nt_lvl_gain_lpct_y1,\
													nt_lvl_gain_lpct_x1,	pp->nt_lvl_gain_lpct_x1);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_33,	nt_lvl_gain_lpct_y2,	pp->nt_lvl_gain_lpct_y2,\
													nt_lvl_gain_lpct_x2,	pp->nt_lvl_gain_lpct_x2,\
													nt_lvl_gain_lpct_y3,	pp->nt_lvl_gain_lpct_y3,\
													nt_lvl_gain_lpct_x3,	pp->nt_lvl_gain_lpct_x3);
				PE_P0L_H13B0_QRd01(p0l_tnr_ctrl_02,	m_gain_en_var2,		pp->m_gain_en_var2);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_48,	m_gain_ctrl2_y0,	pp->m_gain_ctrl2_y0,\
													m_gain_ctrl2_x0,	pp->m_gain_ctrl2_x0,\
													m_gain_ctrl2_y1,	pp->m_gain_ctrl2_y1,\
													m_gain_ctrl2_x1,	pp->m_gain_ctrl2_x1);
				PE_P0L_H13B0_QRd03(p0l_tnr_ctrl_40,	sf_map_flt_en,		pp->sf_map_flt_en,\
													sf_map_tap,			pp->sf_map_tap,\
													sf_map_gain,		pp->sf_map_gain);
				PE_P0L_H13B0_QRd02(p0l_tnr_ctrl_40,	sf_th0,				pp->sf_th0,\
													sf_th1,				pp->sf_th1);
				PE_P0L_H13B0_QRd03(p0l_tnr_ctrl_41,	sf_th2,				pp->sf_th2,\
													sf_th3,				pp->sf_th3,\
													sf_th4,				pp->sf_th4);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_42,	sf_mb_x0,			pp->sf_mb_x0,\
													sf_mb_x1,			pp->sf_mb_x1,\
													sf_mb_y0,			pp->sf_mb_y0,\
													sf_mb_y1,			pp->sf_mb_y1);													
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_44,	sf_mb_x2,			pp->sf_mb_x2,\
													sf_mb_x3,			pp->sf_mb_x3,\
													sf_mb_y2,			pp->sf_mb_y2,\
													sf_mb_y3,			pp->sf_mb_y3);
				PE_P0L_H13B0_QRd02(p0l_tnr_ctrl_45,	sf_gain_mode,		pp->sf_gain_mode,\
													sf_gain,			pp->sf_gain);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_36,	sf_blend_en_y,		pp->sf_blend_en_y,\
													sf_blend_en_c,		pp->sf_blend_en_c,\
													sf_blend_motion_exp_mode,	pp->sf_blend_motion_exp_mode,\
													sad_sel_pels,				pp->sad_sel_pels);
				//mc 
				PE_P0L_H13B0_QRd01(p0l_tnr_ctrl_21,	sad_mamc_blend,		pp->sad_mamc_blend);
				PE_P0L_H13B0_QRd01(p0l_tnr_ctrl_00,	mamc_blend_sel,		pp->mamc_blend_sel);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_46,	mamc_blend_x0,		pp->mamc_blend_x0,\
													mamc_blend_x1,		pp->mamc_blend_x1,\
													mamc_blend_y0,		pp->mamc_blend_y0,\
													mamc_blend_y1,		pp->mamc_blend_y1);
				// me 
				PE_P0L_H13B0_QRd03(p0l_tnr_ctrl_36,	hme_half_pel_en,		pp->hme_half_pel_en,\
													mv_cost_smooth_gain,	pp->mv_cost_smooth_gain,\
													mv_cost_smooth_en,		pp->mv_cost_smooth_en);
				PE_P0L_H13B0_QRd02(p0l_tnr_ctrl_36,	mv0_protect_th,			pp->mv0_protect_th,\
													mv0_protect_en,			pp->mv0_protect_en);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_38,	mv_cost_gmv_smooth_gain,	pp->mv_cost_gmv_smooth_gain,\
													mv_cost_gmv_smooth_en,		pp->mv_cost_gmv_smooth_en,\
													sad_protect_en,				pp->sad_protect_en,\
													sad_protect_gm_en,			pp->sad_protect_gm_en);
				PE_P0L_H13B0_QRd04(p0l_tnr_ctrl_22,	mv_protect_control_x0,		pp->mv_protect_control_x0,\
													mv_protect_control_x1,		pp->mv_protect_control_x1,\
													mv_protect_control_y0,		pp->mv_protect_control_y0,\
													mv_protect_control_y1,		pp->mv_protect_control_y1);
				
			}
			if(PE_CHECK_WIN1(pp->win_id))
			{
				/* ma: motion */
				PE_P0R_H13B0_QRd02(p0r_tnr_ctrl_38,	m_coring_en_c,		pp->m_coring_en_c,\
													m_coring_en_y,		pp->m_coring_en_y);
				PE_P0R_H13B0_QRd03(p0r_tnr_ctrl_38,	m_gain_c,			pp->m_gain_c,\
													m_gain_y,			pp->m_gain_y,\
													m_coring_th,		pp->m_coring_th);
				PE_P0R_H13B0_QRd03(p0r_tnr_ctrl_02,	m_offset_mode_en,	pp->m_offset_mode_en,\
													m_gain_en_var,		pp->m_gain_en_var,\
													a_gain_en_var,		pp->a_gain_en_var);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_03,	wa_y0,				pp->wa_y0,\
													wa_y1,				pp->wa_y1,\
													wa_x0,				pp->wa_x0,\
													wa_x1,				pp->wa_x1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_29,	wa_y2,				pp->wa_y2,\
													wa_y3,				pp->wa_y3,\
													wa_x2,				pp->wa_x2,\
													wa_x3,				pp->wa_x3);
				/* ma: alpha gain */
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_19,	luma_gain_p0_x,			pp->luma_gain_p0_x,\
													luma_gain_p1_x,			pp->luma_gain_p1_x,\
													luma_gain_p2_x,			pp->luma_gain_p2_x,\
													luma_gain_p3_x,			pp->luma_gain_p3_x);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_20,	luma_gain_p0_y,			pp->luma_gain_p0_y,\
													luma_gain_p1_y,			pp->luma_gain_p1_y,\
													luma_gain_p2_y,			pp->luma_gain_p2_y,\
													luma_gain_p3_y,			pp->luma_gain_p3_y);
				/* ma: alhpa remapping*/
				PE_P0R_H13B0_QRd03(p0r_tnr_ctrl_00,	alpha_avg_en,		pp->alpha_avg_en,\
													alpha_mapping_y_en,	pp->alpha_mapping_y_en,\
													alpha_mapping_c_en,	pp->alpha_mapping_c_en);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_23,	alpha_mapping_y_y0,	pp->alpha_mapping_y_y0,\
													alpha_mapping_y_x0,	pp->alpha_mapping_y_x0,\
													alpha_mapping_y_y1,	pp->alpha_mapping_y_y1,\
													alpha_mapping_y_x1,	pp->alpha_mapping_y_x1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_24,	alpha_mapping_y_y2,	pp->alpha_mapping_y_y2,\
													alpha_mapping_y_x2,	pp->alpha_mapping_y_x2,\
													alpha_mapping_y_y3,	pp->alpha_mapping_y_y3,\
													alpha_mapping_y_x3,	pp->alpha_mapping_y_x3);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_25,	alpha_mapping_c_y0,	pp->alpha_mapping_c_y0,\
													alpha_mapping_c_x0,	pp->alpha_mapping_c_x0,\
													alpha_mapping_c_y1,	pp->alpha_mapping_c_y1,\
													alpha_mapping_c_x1,	pp->alpha_mapping_c_x1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_26,	alpha_mapping_c_y2,	pp->alpha_mapping_c_y2,\
													alpha_mapping_c_x2,	pp->alpha_mapping_c_x2,\
													alpha_mapping_c_y3,	pp->alpha_mapping_c_y3,\
													alpha_mapping_c_x3,	pp->alpha_mapping_c_x3);
				/*ma: noise level adjust gain*/
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_00,	nt_lvl_adjust_gm_enable,		pp->nt_lvl_adjust_gm_enable,\
													nt_lvl_adjust_lpct_enable,		pp->nt_lvl_adjust_lpct_enable,\
													nt_lvl_adjust_avg_ts_enable,	pp->nt_lvl_adjust_avg_ts_enable,\
													nt_lvl_adjust_lpct_sel,			pp->nt_lvl_adjust_lpct_sel);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_04,	nt_lvl_gain_gm_y0,		pp->nt_lvl_gain_gm_y0,\
													nt_lvl_gain_gm_x0,		pp->nt_lvl_gain_gm_x0,\
													nt_lvl_gain_gm_y1,		pp->nt_lvl_gain_gm_y1,\
													nt_lvl_gain_gm_x1,		pp->nt_lvl_gain_gm_x1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_12,	nt_lvl_gain_gm_y2,		pp->nt_lvl_gain_gm_y2,\
													nt_lvl_gain_gm_x2,		pp->nt_lvl_gain_gm_x2,\
													nt_lvl_gain_gm_y3,		pp->nt_lvl_gain_gm_y3,\
													nt_lvl_gain_gm_x3,		pp->nt_lvl_gain_gm_x3);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_28,	nt_lvl_gain_st_y0,		pp->nt_lvl_gain_st_y0,\
													nt_lvl_gain_st_x0,		pp->nt_lvl_gain_st_x0,\
													nt_lvl_gain_st_y1,		pp->nt_lvl_gain_st_y1,\
													nt_lvl_gain_st_x1,		pp->nt_lvl_gain_st_x1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_30,	nt_lvl_gain_st_y2,		pp->nt_lvl_gain_st_y2,\
													nt_lvl_gain_st_x2,		pp->nt_lvl_gain_st_x2,\
													nt_lvl_gain_st_y3,		pp->nt_lvl_gain_st_y3,\
													nt_lvl_gain_st_x3,		pp->nt_lvl_gain_st_x3);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_32,	nt_lvl_gain_lpct_y0,	pp->nt_lvl_gain_lpct_y0,\
													nt_lvl_gain_lpct_x0,	pp->nt_lvl_gain_lpct_x0,\
													nt_lvl_gain_lpct_y1,	pp->nt_lvl_gain_lpct_y1,\
													nt_lvl_gain_lpct_x1,	pp->nt_lvl_gain_lpct_x1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_33,	nt_lvl_gain_lpct_y2,	pp->nt_lvl_gain_lpct_y2,\
													nt_lvl_gain_lpct_x2,	pp->nt_lvl_gain_lpct_x2,\
													nt_lvl_gain_lpct_y3,	pp->nt_lvl_gain_lpct_y3,\
													nt_lvl_gain_lpct_x3,	pp->nt_lvl_gain_lpct_x3);
				PE_P0R_H13B0_QRd01(p0r_tnr_ctrl_02,	m_gain_en_var2,			pp->m_gain_en_var2);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_48,	m_gain_ctrl2_y0,		pp->m_gain_ctrl2_y0,\
													m_gain_ctrl2_x0,		pp->m_gain_ctrl2_x0,\
													m_gain_ctrl2_y1,		pp->m_gain_ctrl2_y1,\
													m_gain_ctrl2_x1,		pp->m_gain_ctrl2_x1);
				PE_P0R_H13B0_QRd03(p0r_tnr_ctrl_40,	sf_map_flt_en,			pp->sf_map_flt_en,\
													sf_map_tap,				pp->sf_map_tap,\
													sf_map_gain,			pp->sf_map_gain);
				PE_P0R_H13B0_QRd02(p0r_tnr_ctrl_40,	sf_th0,					pp->sf_th0,\
													sf_th1,					pp->sf_th1);
				PE_P0R_H13B0_QRd03(p0r_tnr_ctrl_41,	sf_th2,					pp->sf_th2,\
													sf_th3,					pp->sf_th3,\
													sf_th4,					pp->sf_th4);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_42,	sf_mb_x0,				pp->sf_mb_x0,\
													sf_mb_x1,				pp->sf_mb_x1,\
													sf_mb_y0,				pp->sf_mb_y0,\
													sf_mb_y1,				pp->sf_mb_y1);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_44,	sf_mb_x2,				pp->sf_mb_x2,\
													sf_mb_x3,				pp->sf_mb_x3,\
													sf_mb_y2,				pp->sf_mb_y2,\
													sf_mb_y3,				pp->sf_mb_y3);
				PE_P0R_H13B0_QRd02(p0r_tnr_ctrl_45,	sf_gain_mode,			pp->sf_gain_mode,\
													sf_gain,				pp->sf_gain);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_36,	sf_blend_en_y,			pp->sf_blend_en_y,\
													sf_blend_en_c,			pp->sf_blend_en_c,\
													sf_blend_motion_exp_mode,	pp->sf_blend_motion_exp_mode,\
													sad_sel_pels,			pp->sad_sel_pels);
				/* mc */
				PE_P0R_H13B0_QRd01(p0r_tnr_ctrl_21,	sad_mamc_blend,		pp->sad_mamc_blend);
				PE_P0R_H13B0_QRd01(p0r_tnr_ctrl_00,	mamc_blend_sel,		pp->mamc_blend_sel);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_46,	mamc_blend_x0,		pp->mamc_blend_x0,\
													mamc_blend_x1,		pp->mamc_blend_x1,\
													mamc_blend_y0,		pp->mamc_blend_y0,\
													mamc_blend_y1,		pp->mamc_blend_y1);
				/* me */
				PE_P0R_H13B0_QRd03(p0r_tnr_ctrl_36,	hme_half_pel_en,		pp->hme_half_pel_en,\
													mv_cost_smooth_gain,	pp->mv_cost_smooth_gain,\
													mv_cost_smooth_en,		pp->mv_cost_smooth_en);
				PE_P0R_H13B0_QRd02(p0r_tnr_ctrl_36,	mv0_protect_th,			pp->mv0_protect_th,\
													mv0_protect_en,			pp->mv0_protect_en);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_38,	mv_cost_gmv_smooth_gain,	pp->mv_cost_gmv_smooth_gain,\
													mv_cost_gmv_smooth_en,		pp->mv_cost_gmv_smooth_en,\
													sad_protect_en,				pp->sad_protect_en,\
													sad_protect_gm_en,			pp->sad_protect_gm_en);
				PE_P0R_H13B0_QRd04(p0r_tnr_ctrl_22,	mv_protect_control_x0,		pp->mv_protect_control_x0,\
													mv_protect_control_x1,		pp->mv_protect_control_x1,\
													mv_protect_control_y0,		pp->mv_protect_control_y0,\
													mv_protect_control_y1,		pp->mv_protect_control_y1);
			}
			
			PE_NRD_DBG_PRINT("get[%d] \n"\
				"ma:\nmotion: 	 coring_en (y,c): %d,%d, gain (y,c): %d,%d,\n"\
					 "         	 coring_th: %d, offset_en: %d, gain_en_var (m,a): %d,%d\n"\
					 "         	 wa_y(0,1,2,3):%d,%d,%d,%d, wa_x(0,1,2,3):%d,%d,%d,%d\n"\
					 "alph_gain: gain_x(p0,p1,p2,p3):%d,%d,%d,%d, gain_y(p0,p1,p2,p3):%d,%d,%d,%d\n"\
					 "alph_remap:ave_en:%d, mapping_y_en:%d, mapping_c_en:%d\n"\
					 "           map_y(x0,x1,x2,x3):%d,%d,%d,%d, map_y(y0,y1,y2,y3):%d,%d,%d,%d\n"\
					 "           map_c(x0,x1,x2,x3):%d,%d,%d,%d, map_c(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "adj_gain:  gm_en:%d, lpct:%d, avg_ts_en:%d, lpct_sel:%d\n"\
				     "           gm(x0,x1,x2,x3):%d,%d,%d,%d, gm(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           st(x0,x1,x2,x3):%d,%d,%d,%d, st(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           lpct(x0,x1,x2,x3):%d,%d,%d,%d, lpct(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           m_gain_en_var2:%d,\n"\
				     "           ctrl(x0,x1,y0,y1):%d,%d,%d,%d\n"\
				     "           sf_map_flt_en:%d, map_tap:%d, map_gain:%d\n"\
				     "           sf_th(0,1,2,3,4):%d,%d,%d,%d,%d\n"\
				     "           sf_mb(x0,x1,x2,x3):%d,%d,%d,%d, sf_mb(y0,y1,y2,y3):%d,%d,%d,%d\n"\
				     "           sf_gain_md:%d, sf_gain:%d, sf_en(y,c):%d,%d, sf_mo_exp_md:%d\n"\
				"mc:\n           sel_pels:%d, mamc_blend:%d, blend_sel:%d\n"\
				     "           blend(x0,x1,y0,y1):%d,%d,%d,%d\n"\
				"me:\n           hlf_pel_en:%d, smth(gain,en):%d,%d, gmv_smth(gain,en):%d,%d\n"\
				     "           mv0_th:%d, mv0_en:%d, sad_en:%d, sad_gm_en:%d\n"\
				     "           ctrl(x0,x1,y0,y1):%d,%d,%d,%d\n",\
				pp->win_id,\
				// ma: motion 
				pp->m_coring_en_y,pp->m_coring_en_c,pp->m_gain_y,pp->m_gain_c,\
				pp->m_coring_th,pp->m_offset_mode_en,pp->m_gain_en_var,pp->a_gain_en_var,\
				pp->wa_y0,pp->wa_y1,pp->wa_y2,pp->wa_y3,pp->wa_x0,pp->wa_x1,pp->wa_x2,pp->wa_x3,\
				// ma: alpha gain
				pp->luma_gain_p0_x,pp->luma_gain_p1_x,pp->luma_gain_p2_x,pp->luma_gain_p3_x,\
				pp->luma_gain_p0_y,pp->luma_gain_p1_y,pp->luma_gain_p2_y,pp->luma_gain_p3_y,\
				// alpha remapping
				pp->alpha_avg_en,pp->alpha_mapping_y_en,pp->alpha_mapping_c_en,\
				pp->alpha_mapping_y_x0,pp->alpha_mapping_y_x1,pp->alpha_mapping_y_x2,pp->alpha_mapping_y_x3,\
				pp->alpha_mapping_y_y0,pp->alpha_mapping_y_y1,pp->alpha_mapping_y_y2,pp->alpha_mapping_y_y3,\
				pp->alpha_mapping_c_x0,pp->alpha_mapping_c_x1,pp->alpha_mapping_c_x2,pp->alpha_mapping_c_x3,\
				pp->alpha_mapping_c_y0,pp->alpha_mapping_c_y1,pp->alpha_mapping_c_y2,pp->alpha_mapping_c_y3,\
				// adjust gain
				pp->nt_lvl_adjust_gm_enable,pp->nt_lvl_adjust_lpct_enable,\
				pp->nt_lvl_adjust_avg_ts_enable,pp->nt_lvl_adjust_lpct_sel,\
				pp->nt_lvl_gain_gm_x0,pp->nt_lvl_gain_gm_x1,pp->nt_lvl_gain_gm_x2,pp->nt_lvl_gain_gm_x3,\
				pp->nt_lvl_gain_gm_y0,pp->nt_lvl_gain_gm_y1,pp->nt_lvl_gain_gm_y2,pp->nt_lvl_gain_gm_y3,\
				pp->nt_lvl_gain_st_x0,pp->nt_lvl_gain_st_x1,pp->nt_lvl_gain_st_x2,pp->nt_lvl_gain_st_x3,\
				pp->nt_lvl_gain_st_y0,pp->nt_lvl_gain_st_y1,pp->nt_lvl_gain_st_y2,pp->nt_lvl_gain_st_y3,\
				pp->nt_lvl_gain_lpct_x0,pp->nt_lvl_gain_lpct_x1,pp->nt_lvl_gain_lpct_x2,pp->nt_lvl_gain_lpct_x3,\
				pp->nt_lvl_gain_lpct_y0,pp->nt_lvl_gain_lpct_y1,pp->nt_lvl_gain_lpct_y2,pp->nt_lvl_gain_lpct_y3,\
				pp->m_gain_en_var2,\
				pp->m_gain_ctrl2_x0,pp->m_gain_ctrl2_x1,pp->m_gain_ctrl2_y0,pp->m_gain_ctrl2_y1,\
				pp->sf_map_flt_en,pp->sf_map_tap,pp->sf_map_gain,\
				pp->sf_th0,pp->sf_th1,pp->sf_th2,pp->sf_th3,pp->sf_th4,\
				pp->sf_mb_x0,pp->sf_mb_x1,pp->sf_mb_x2,pp->sf_mb_x3,\
				pp->sf_mb_y0,pp->sf_mb_y1,pp->sf_mb_y2,pp->sf_mb_y3,\
				pp->sf_gain_mode,pp->sf_gain,pp->sf_blend_en_y,pp->sf_blend_en_c,pp->sf_blend_motion_exp_mode,\
				// mc: 
				pp->sad_sel_pels,pp->sad_mamc_blend,pp->mamc_blend_sel,\
				pp->mamc_blend_x0,pp->mamc_blend_x1,pp->mamc_blend_y0,pp->mamc_blend_y1,\
				// me: 
				pp->hme_half_pel_en,pp->mv_cost_smooth_gain,pp->mv_cost_smooth_en,\
				pp->mv_cost_gmv_smooth_gain,pp->mv_cost_gmv_smooth_en,\
				pp->mv0_protect_th,pp->mv0_protect_en,pp->sad_protect_en,pp->sad_protect_gm_en,\
				pp->mv_protect_control_x0,pp->mv_protect_control_x1,\
				pp->mv_protect_control_y0,pp->mv_protect_control_y1);
				
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_NRD_TNR1_DETAIL_T *pp=(LX_PE_NRD_TNR1_DETAIL_T *)pstParams;
			PE_CHECK_WINID(pp->win_id);
			win_id = PE_GET_CHECKED_WINID(pp->win_id);
			if(PE_CHECK_WIN0(win_id))
			{
				/* top */
				PE_P0L_L9B_QRd05(tnr_ctrl_00,	wa_enable,					pp->wa_enable,\
												calc_motion_flt_enable,		pp->calc_motion_flt_enable,\
												calc_motion_flt_type,		pp->calc_motion_flt_type,\
												nt_lvl_adjust_gm_enable,	pp->nt_lvl_adjust_gm_enable,\
												nt_lvl_adjust_avg_ts_enable,pp->nt_lvl_adjust_avg_ts_enable);
				/* motion histo(n-lvl estimate) */
				PE_P0L_L9B_QRd02(tnr_ctrl_01,	y_th_lo,			pp->y_th_lo,\
												y_th_hi,			pp->y_th_hi);
				/* alpha gain(n-lvl gaining), gm gain */
				PE_P0L_L9B_QRd04(tnr_ctrl_04,	nt_lvl_gain_gm_y0,	pp->nt_lvl_gain_gm_y0,\
												nt_lvl_gain_gm_x0,	pp->nt_lvl_gain_gm_x0,\
												nt_lvl_gain_gm_y1,	pp->nt_lvl_gain_gm_y1,\
												nt_lvl_gain_gm_x1,	pp->nt_lvl_gain_gm_x1);
				PE_P0L_L9B_QRd04(tnr_ctrl_12,	nt_lvl_gain_gm_y2,	pp->nt_lvl_gain_gm_y2,\
												nt_lvl_gain_gm_x2,	pp->nt_lvl_gain_gm_x2,\
												nt_lvl_gain_gm_y3,	pp->nt_lvl_gain_gm_y3,\
												nt_lvl_gain_gm_x3,	pp->nt_lvl_gain_gm_x3);
				/* alpha gain(n-lvl gaining), avg st gain */
				PE_P0L_L9B_QRd04(tnr_ctrl_28,	nt_lvl_gain_st_y0,	pp->nt_lvl_gain_st_y0,\
												nt_lvl_gain_st_x0,	pp->nt_lvl_gain_st_x0,\
												nt_lvl_gain_st_y1,	pp->nt_lvl_gain_st_y1,\
												nt_lvl_gain_st_x1,	pp->nt_lvl_gain_st_x1);
				PE_P0L_L9B_QRd04(tnr_ctrl_30,	nt_lvl_gain_st_y2,	pp->nt_lvl_gain_st_y2,\
												nt_lvl_gain_st_x2,	pp->nt_lvl_gain_st_x2,\
												nt_lvl_gain_st_y3,	pp->nt_lvl_gain_st_y3,\
												nt_lvl_gain_st_x3,	pp->nt_lvl_gain_st_x3);
				/* alpha lut(n-lvl apply) */
				PE_P0L_L9B_QRd04(tnr_ctrl_07,	alpha_lut_ind0,		pp->alpha_lut_ind0,\
												alpha_lut_ind1,		pp->alpha_lut_ind1,\
												alpha_lut_ind2,		pp->alpha_lut_ind2,\
												alpha_lut_ind3,		pp->alpha_lut_ind3);
				PE_P0L_L9B_QRd03(tnr_ctrl_08,	alpha_lut_ind4,		pp->alpha_lut_ind4,\
												alpha_lut_ind5,		pp->alpha_lut_ind5,\
												alpha_lut_ind6,		pp->alpha_lut_ind6);
				PE_P0L_L9B_QRd01(tnr_ctrl_02,	alpha_lut_ind7,		pp->alpha_lut_ind7);
				/* adjust alpha(alpha gaining), adjust alpha */
				PE_P0L_L9B_QRd01(tnr_ctrl_05,	adj_alpha_nt_lvl_th0,	pp->adj_alpha_nt_lvl_th0);
				PE_P0L_L9B_QRd01(tnr_ctrl_08,	adj_alpha_nt_lvl_th1,	pp->adj_alpha_nt_lvl_th1);
				PE_P0L_L9B_QRd02(tnr_ctrl_06,	adj_alpha_k0,			pp->adj_alpha_k0,\
												adj_alpha_k1,			pp->adj_alpha_k1);
				/* adjust alpha(alpha gaining), s. var --> WA */
				PE_P0L_L9B_QRd04(tnr_ctrl_03,	wa_y0,					pp->wa_y0,\
												wa_y1,					pp->wa_y1,\
												wa_x0,					pp->wa_x0,\
												wa_x1,					pp->wa_x1);
				PE_P0L_L9B_QRd04(tnr_ctrl_29,	wa_y2,					pp->wa_y2,\
												wa_y3,					pp->wa_y3,\
												wa_x2,					pp->wa_x2,\
												wa_x3,					pp->wa_x3);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				/* top */
				PE_P0R_L9B_QRd05(tnr_ctrl_00,	wa_enable,					pp->wa_enable,\
												calc_motion_flt_enable,		pp->calc_motion_flt_enable,\
												calc_motion_flt_type,		pp->calc_motion_flt_type,\
												nt_lvl_adjust_gm_enable,	pp->nt_lvl_adjust_gm_enable,\
												nt_lvl_adjust_avg_ts_enable,pp->nt_lvl_adjust_avg_ts_enable);
				/* motion histo(n-lvl estimate) */
				PE_P0R_L9B_QRd02(tnr_ctrl_01,	y_th_lo,			pp->y_th_lo,\
												y_th_hi,			pp->y_th_hi);
				/* alpha gain(n-lvl gaining), gm gain */
				PE_P0R_L9B_QRd04(tnr_ctrl_04,	nt_lvl_gain_gm_y0,	pp->nt_lvl_gain_gm_y0,\
												nt_lvl_gain_gm_x0,	pp->nt_lvl_gain_gm_x0,\
												nt_lvl_gain_gm_y1,	pp->nt_lvl_gain_gm_y1,\
												nt_lvl_gain_gm_x1,	pp->nt_lvl_gain_gm_x1);
				PE_P0R_L9B_QRd04(tnr_ctrl_12,	nt_lvl_gain_gm_y2,	pp->nt_lvl_gain_gm_y2,\
												nt_lvl_gain_gm_x2,	pp->nt_lvl_gain_gm_x2,\
												nt_lvl_gain_gm_y3,	pp->nt_lvl_gain_gm_y3,\
												nt_lvl_gain_gm_x3,	pp->nt_lvl_gain_gm_x3);
				/* alpha gain(n-lvl gaining), avg st gain */
				PE_P0R_L9B_QRd04(tnr_ctrl_28,	nt_lvl_gain_st_y0,	pp->nt_lvl_gain_st_y0,\
												nt_lvl_gain_st_x0,	pp->nt_lvl_gain_st_x0,\
												nt_lvl_gain_st_y1,	pp->nt_lvl_gain_st_y1,\
												nt_lvl_gain_st_x1,	pp->nt_lvl_gain_st_x1);
				PE_P0R_L9B_QRd04(tnr_ctrl_30,	nt_lvl_gain_st_y2,	pp->nt_lvl_gain_st_y2,\
												nt_lvl_gain_st_x2,	pp->nt_lvl_gain_st_x2,\
												nt_lvl_gain_st_y3,	pp->nt_lvl_gain_st_y3,\
												nt_lvl_gain_st_x3,	pp->nt_lvl_gain_st_x3);
				/* alpha lut(n-lvl apply) */
				PE_P0R_L9B_QRd04(tnr_ctrl_07,	alpha_lut_ind0,		pp->alpha_lut_ind0,\
												alpha_lut_ind1,		pp->alpha_lut_ind1,\
												alpha_lut_ind2,		pp->alpha_lut_ind2,\
												alpha_lut_ind3,		pp->alpha_lut_ind3);
				PE_P0R_L9B_QRd03(tnr_ctrl_08,	alpha_lut_ind4,		pp->alpha_lut_ind4,\
												alpha_lut_ind5,		pp->alpha_lut_ind5,\
												alpha_lut_ind6,		pp->alpha_lut_ind6);
				PE_P0R_L9B_QRd01(tnr_ctrl_02,	alpha_lut_ind7,		pp->alpha_lut_ind7);
				/* adjust alpha(alpha gaining), adjust alpha */
				PE_P0R_L9B_QRd01(tnr_ctrl_05,	adj_alpha_nt_lvl_th0,	pp->adj_alpha_nt_lvl_th0);
				PE_P0R_L9B_QRd01(tnr_ctrl_08,	adj_alpha_nt_lvl_th1,	pp->adj_alpha_nt_lvl_th1);
				PE_P0R_L9B_QRd02(tnr_ctrl_06,	adj_alpha_k0,			pp->adj_alpha_k0,\
												adj_alpha_k1,			pp->adj_alpha_k1);
				/* adjust alpha(alpha gaining), s. var --> WA */
				PE_P0R_L9B_QRd04(tnr_ctrl_03,	wa_y0,					pp->wa_y0,\
												wa_y1,					pp->wa_y1,\
												wa_x0,					pp->wa_x0,\
												wa_x1,					pp->wa_x1);
				PE_P0R_L9B_QRd04(tnr_ctrl_29,	wa_y2,					pp->wa_y2,\
												wa_y3,					pp->wa_y3,\
												wa_x2,					pp->wa_x2,\
												wa_x3,					pp->wa_x3);
			}
			PE_NRD_DBG_PRINT("get[%d] \n"\
				"motion histo                : %d, %d, %d, %d\n"\
				"alpha gain - gm gain        : %d,  [y,x]:%d,%d, %d,%d, %d,%d, %d,%d\n"\
				"alpha gain - avg st gain    : %d,  [y,x]:%d,%d, %d,%d, %d,%d, %d,%d\n"\
				"alpha lut                   : %d, %d, %d, %d, %d, %d, %d, %d\n"\
				"adjust alpha                : %d, %d, %d, %d\n"\
				"adjust alpha - s. var to wa : %d,  [x]:%d,%d,%d,%d,  [y]:%d,%d,%d,%d\n",\
				pp->win_id,\
				/* motion histo(n-lvl estimate) */
				pp->calc_motion_flt_enable,pp->calc_motion_flt_type,\
				pp->y_th_lo,pp->y_th_hi,\
				/* alpha gain(n-lvl gaining), gm gain */
				pp->nt_lvl_adjust_gm_enable,pp->nt_lvl_gain_gm_y0,pp->nt_lvl_gain_gm_x0,\
				pp->nt_lvl_gain_gm_y1,pp->nt_lvl_gain_gm_x1,pp->nt_lvl_gain_gm_y2,\
				pp->nt_lvl_gain_gm_x2,pp->nt_lvl_gain_gm_y3,pp->nt_lvl_gain_gm_x3,\
				/* alpha gain(n-lvl gaining), avg st gain */
				pp->nt_lvl_adjust_avg_ts_enable,pp->nt_lvl_gain_st_y0,\
				pp->nt_lvl_gain_st_x0,pp->nt_lvl_gain_st_y1,pp->nt_lvl_gain_st_x1,\
				pp->nt_lvl_gain_st_y2,pp->nt_lvl_gain_st_x2,pp->nt_lvl_gain_st_y3,\
				pp->nt_lvl_gain_st_x3,\
				/* alpha lut(n-lvl apply) */
				pp->alpha_lut_ind0,pp->alpha_lut_ind1,pp->alpha_lut_ind2,\
				pp->alpha_lut_ind3,pp->alpha_lut_ind4,pp->alpha_lut_ind5,\
				pp->alpha_lut_ind6,pp->alpha_lut_ind7,\
				/* adjust alpha(alpha gaining), adjust alpha */
				pp->adj_alpha_nt_lvl_th0,pp->adj_alpha_nt_lvl_th1,\
				pp->adj_alpha_k0,pp->adj_alpha_k1,\
				/* adjust alpha(alpha gaining), s. var --> WA */
				pp->wa_enable,pp->wa_x0,pp->wa_x1,pp->wa_x2,pp->wa_x3,\
				pp->wa_y0,pp->wa_y1,pp->wa_y2,pp->wa_y3);
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set tnr color region ctrl
 *
 * @param   *pstParams [in] LX_PE_NRD_TNR_CRGN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_SetTnrColorRgnCtrl(LX_PE_NRD_TNR_CRGN_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_NRD_CHECK_CODE(pstParams->gain_rgn[0]>255,break,\
			"[%s,%d] gain_rgn[0]:%d is over.\n",__F__,__L__,pstParams->gain_rgn[0]);
		PE_NRD_CHECK_CODE(pstParams->gain_rgn[1]>255,break,\
			"[%s,%d] gain_rgn[1]:%d is over.\n",__F__,__L__,pstParams->gain_rgn[1]);
		PE_NRD_CHECK_CODE(pstParams->gain_rgn[2]>255,break,\
			"[%s,%d] gain_rgn[2]:%d is over.\n",__F__,__L__,pstParams->gain_rgn[2]);
		PE_NRD_CHECK_CODE(pstParams->gain_rgn[3]>255,break,\
			"[%s,%d] gain_rgn[3]:%d is over.\n",__F__,__L__,pstParams->gain_rgn[3]);
		PE_NRD_DBG_PRINT("set pstParams[%d] : gain:%d,%d,%d,%d\n",pstParams->win_id,\
			pstParams->gain_rgn[0],pstParams->gain_rgn[1],pstParams->gain_rgn[2],pstParams->gain_rgn[3]);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P0L_L9B_QWr04(tnr_ctrl_27,	crgn_gain_rgn0,	GET_BITS(pstParams->gain_rgn[0],0,8),\
												crgn_gain_rgn1,	GET_BITS(pstParams->gain_rgn[1],0,8),\
												crgn_gain_rgn2,	GET_BITS(pstParams->gain_rgn[2],0,8),\
												crgn_gain_rgn3,	GET_BITS(pstParams->gain_rgn[3],0,8));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P0R_L9B_QWr04(tnr_ctrl_27,	crgn_gain_rgn0,	GET_BITS(pstParams->gain_rgn[0],0,8),\
												crgn_gain_rgn1,	GET_BITS(pstParams->gain_rgn[1],0,8),\
												crgn_gain_rgn2,	GET_BITS(pstParams->gain_rgn[2],0,8),\
												crgn_gain_rgn3,	GET_BITS(pstParams->gain_rgn[3],0,8));
			}
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get tnr color region ctrl
 *
 * @param   *pstParams [in/out] LX_PE_NRD_TNR_CRGN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_NRD_GetTnrColorRgnCtrl(LX_PE_NRD_TNR_CRGN_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_L9B_QRd04(tnr_ctrl_27,	crgn_gain_rgn0,	pstParams->gain_rgn[0],\
												crgn_gain_rgn1,	pstParams->gain_rgn[1],\
												crgn_gain_rgn2,	pstParams->gain_rgn[2],\
												crgn_gain_rgn3,	pstParams->gain_rgn[3]);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_L9B_QRd04(tnr_ctrl_27,	crgn_gain_rgn0,	pstParams->gain_rgn[0],\
												crgn_gain_rgn1,	pstParams->gain_rgn[1],\
												crgn_gain_rgn2,	pstParams->gain_rgn[2],\
												crgn_gain_rgn3,	pstParams->gain_rgn[3]);
			}
		}
		else
		#endif
		{
			PE_NRD_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_NRD_DBG_PRINT("get pstParams[%d] : gain:%d,%d,%d,%d\n",pstParams->win_id,\
			pstParams->gain_rgn[0],pstParams->gain_rgn[1],pstParams->gain_rgn[2],pstParams->gain_rgn[3]);
	} while (0);
	return ret;
}

