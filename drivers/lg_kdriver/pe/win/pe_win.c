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


/** @file pe_win.c
 *
 *  driver for picture enhance window control functions. ( used only within kdriver )
 *	- control window of each pe module
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
#include "pe_win.h"
#include "pe_etc_hw.h"
#include "pe_win_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_WIN_ERROR	printk

#define PE_WIN_DBG_PRINT(fmt,args...)	\
	if(_g_win_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_WIN_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_WIN_ERROR(fmt,##args);_action;}}

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
static int PE_WIN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_WIN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_WIN_SetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams);
static int PE_WIN_GetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_win_trace=0x0;	//default should be off.

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init pe window
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_WIN_HW_H13_Init();
			PE_WIN_CHECK_CODE(ret,break,"[%s,%d] PE_WIN_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_WIN_HW_L9_Init();
			PE_WIN_CHECK_CODE(ret,break,"[%s,%d] PE_WIN_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_WIN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of win setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_WIN_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_WIN_DBG_PRINT("S %s\n",#_struct);\
			PE_WIN_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_WIN_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_WIN_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_WIN_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_WIN_SET_FUNC(LX_PE_WIN_D3D_INFO_T,		PE_WIN_SetAutoDetectInfo);
		PE_WIN_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_WIN_SetDefaultSettings);
		PE_WIN_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_WIN_SetDebugSettings);
		default:
		{
			PE_WIN_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of win getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_WIN_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_WIN_DBG_PRINT("S %s\n",#_struct);\
			PE_WIN_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_WIN_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_WIN_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_WIN_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_WIN_GET_FUNC(LX_PE_WIN_D3D_INFO_T,	PE_WIN_GetAutoDetectInfo);
		default:
		{
			PE_WIN_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

static int PE_WIN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_WIN_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
	}while(0);
	return ret;
}
static int PE_WIN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_WIN_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(WIN)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_win_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(WIN)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_WIN_HW_H13_SetDbgPrint(_g_win_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_WIN_HW_L9_SetDbgPrint(_g_win_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(WIN)))
				{
					PE_WIN_DBG_PRINT("pe1 win1,2 : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_win1_ctrl_00, win_en,	0x0);
						PE_P1L_L9B_QWr01(pe1_l_win2_ctrl_00, win_en,	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_win1_ctrl_00, win_en,	0x0);
						PE_P1R_L9B_QWr01(pe1_r_win2_ctrl_00, win_en,	0x0);
					}
				}
				else
				{
					PE_WIN_DBG_PRINT("pe1 win1,2 : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_win1_ctrl_00, win_en,	0x1);
						PE_P1L_L9B_QWr01(pe1_l_win2_ctrl_00, win_en,	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_win1_ctrl_00, win_en,	0x1);
						PE_P1R_L9B_QWr01(pe1_r_win2_ctrl_00, win_en,	0x1);
					}
				}
			}
			else if(PE_KDRV_VER_L9AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(WIN)))
				{
					PE_WIN_DBG_PRINT("pe1 win, bbd en, : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9A_QWr01(pe1_l_win_ctrl_00, win_en,		0x0);
						PE_P1L_L9A_QWr01(pe1_l_bbd2d_ctrl_0, black_boundary_detection_enable,	0x0);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9A_QWr01(pe1_r_win_ctrl_00, win_en,		0x0);
						PE_P1R_L9A_QWr01(pe1_r_bbd2d_ctrl_0, black_boundary_detection_enable,	0x0);
					}
				}
				else
				{
					PE_WIN_DBG_PRINT("pe1 win, bbd en, : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9A_QWr01(pe1_l_win_ctrl_00, win_en,		0x1);
						PE_P1L_L9A_QWr01(pe1_l_bbd2d_ctrl_0, black_boundary_detection_enable,	0x1);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9A_QWr01(pe1_r_win_ctrl_00, win_en,		0x1);
						PE_P1R_L9A_QWr01(pe1_r_bbd2d_ctrl_0, black_boundary_detection_enable,	0x1);
					}
				}
			}
			else
			#endif
			{
				PE_WIN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
static int PE_WIN_SetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_WIN_HW_L9_SetAutoDetectInfo(pstParams);
			PE_WIN_CHECK_CODE(ret,break,"[%s,%d] PE_WIN_HW_L9_SetAutoDetectInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_WIN_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
static int PE_WIN_GetAutoDetectInfo(LX_PE_WIN_D3D_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_WIN_HW_L9_GetAutoDetectInfo(pstParams);
			PE_WIN_CHECK_CODE(ret,break,"[%s,%d] PE_WIN_HW_L9_GetAutoDetectInfo() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_WIN_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}

