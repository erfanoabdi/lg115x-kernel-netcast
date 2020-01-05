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


/** @file pe_cmg.c
 *
 *  driver for picture enhance color management functions. ( used only within kdriver )
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
#include "pe_cmg.h"
#include "pe_cmg_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMG_ERROR	printk

#define PE_CMG_DBG_PRINT(fmt,args...)	\
	if(_g_cmg_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMG_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_CMG_ERROR(fmt,##args);_action;}}

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
static int PE_CMG_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_CMG_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_CMG_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
static int PE_CMG_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
static int PE_CMG_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
static int PE_CMG_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
static int PE_CMG_SetCenRegion(LX_PE_CMG_REGION_T *pstParams);
static int PE_CMG_GetCenRegion(LX_PE_CMG_REGION_T *pstParams);
static int PE_CMG_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
static int PE_CMG_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
static int PE_CMG_SetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
static int PE_CMG_GetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
static int PE_CMG_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
static int PE_CMG_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
static int PE_CMG_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
static int PE_CMG_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
static int PE_CMG_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
static int PE_CMG_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmg_trace=0x0;	//default should be off.

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * init color management
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_CMG_HW_H13_Init();
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_Init();
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_Init() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of cmg setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMG_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CMG_DBG_PRINT("S %s\n",#_struct);\
			PE_CMG_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_CMG_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CMG_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CMG_SET_FUNC(LX_PE_CMG_COLOR_CTRL_T,		PE_CMG_SetCenColorCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_ENABLE_T,			PE_CMG_SetCenEnable);
		PE_CMG_SET_FUNC(LX_PE_CMG_REGION_ENABLE_T,	PE_CMG_SetCenRegionEnable);
		PE_CMG_SET_FUNC(LX_PE_CMG_REGION_T,			PE_CMG_SetCenRegion);
		PE_CMG_SET_FUNC(LX_PE_CMG_REGION_CTRL_T,	PE_CMG_SetCenRegionCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_GLOBAL_CTRL_T,	PE_CMG_SetCenGlobalCtrl);
		PE_CMG_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CMG_SetDefaultSettings);
		PE_CMG_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CMG_SetDebugSettings);
		PE_CMG_SET_FUNC(LX_PE_CMG_CW_CTRL_T,		PE_CMG_SetClearWhiteCtrl);
		PE_CMG_SET_FUNC(LX_PE_CMG_CW_GAIN_CTRL_T,	PE_CMG_SetClearWhiteGainCtrl);
		default:
		{
			PE_CMG_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of cmg getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMG_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CMG_DBG_PRINT("S %s\n",#_struct);\
			PE_CMG_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_CMG_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CMG_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CMG_GET_FUNC(LX_PE_CMG_COLOR_CTRL_T,		PE_CMG_GetCenColorCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_ENABLE_T,			PE_CMG_GetCenEnable);
		PE_CMG_GET_FUNC(LX_PE_CMG_REGION_ENABLE_T,	PE_CMG_GetCenRegionEnable);
		PE_CMG_GET_FUNC(LX_PE_CMG_REGION_T,			PE_CMG_GetCenRegion);
		PE_CMG_GET_FUNC(LX_PE_CMG_REGION_CTRL_T,	PE_CMG_GetCenRegionCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_GLOBAL_CTRL_T,	PE_CMG_GetCenGlobalCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_CW_CTRL_T,		PE_CMG_GetClearWhiteCtrl);
		PE_CMG_GET_FUNC(LX_PE_CMG_CW_GAIN_CTRL_T,	PE_CMG_GetClearWhiteGainCtrl);
		default:
		{
			PE_CMG_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
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
static int PE_CMG_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
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
static int PE_CMG_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CMG)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmg_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMG)))? 0x1:0x0;
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13)	PE_CMG_HW_H13_SetDbgPrint(_g_cmg_trace);
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9)	PE_CMG_HW_L9_SetDbgPrint(_g_cmg_trace);
			#endif
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMG)))
				{
					PE_CMG_DBG_PRINT("cen bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13B0_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	0x0);	//CEN block OFF
					}
				}
				else
				{
					PE_CMG_DBG_PRINT("cen on.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13B0_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	0x1);	//CEN block ON
					}
				}
			}
			else if(PE_KDRV_VER_H13AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMG)))
				{
					PE_CMG_DBG_PRINT("cen bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	0x0);	//CEN block OFF
					}
				}
				else
				{
					PE_CMG_DBG_PRINT("cen on.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13_QWr01(pe1_cen_ctrl_00,	reg_cen_bypass,	0x1);	//CEN block ON
					}
				}
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMG)))
				{
					PE_CMG_DBG_PRINT("cen bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_cen_ctrl_00,	reg_cen_bypass,	0x0);	//CEN block OFF
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B_QWr01(pe1_r_cen_ctrl_00,	reg_cen_bypass,	0x0);	//CEN block OFF
					}
				}
				else
				{
					PE_CMG_DBG_PRINT("cen on.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B_QWr01(pe1_l_cen_ctrl_00,	reg_cen_bypass,	0x1);	//CEN block ON
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
                     	PE_P1R_L9B_QWr01(pe1_r_cen_ctrl_00,	reg_cen_bypass,	0x1);	//CEN block ON
					}
				}
			}
			else if(PE_KDRV_VER_L9AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMG)))
				{
					PE_CMG_DBG_PRINT("pe1_l_cen_ctrl_01 : 0x0.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9_RdFL(pe1_l_cen_ctrl_01);
						PE_P1L_L9_Wr(pe1_l_cen_ctrl_01,0x0);
						PE_P1L_L9_WrFL(pe1_l_cen_ctrl_01);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9_RdFL(pe1_r_cen_ctrl_01);
						PE_P1R_L9_Wr(pe1_r_cen_ctrl_01,0x0);
						PE_P1R_L9_WrFL(pe1_r_cen_ctrl_01);
					}
				}
			}
			else
			#endif
			{
				PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * set cen enable
 *
 * @param   *pstParams [in] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_DBG_PRINT(" set[%d]: cen enable:%d\n",pstParams->win_id,pstParams->enable);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_RdFL(pe1_cen_ctrl_00);
				PE_P1L_H13B0_Wr01(pe1_cen_ctrl_00,	reg_cen_bypass,	GET_BITS(pstParams->enable,0,1));
				PE_P1L_H13B0_WrFL(pe1_cen_ctrl_00);
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get cen enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams)
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
				PE_P1L_H13B0_RdFL(pe1_cen_ctrl_00);
				PE_P1L_H13B0_Rd01(pe1_cen_ctrl_00,	reg_cen_bypass,	pstParams->enable);
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMG_DBG_PRINT(" get[%d]: cen enable:%d\n",pstParams->win_id,pstParams->enable);
	} while(0);
	return ret;
}
/**
 * set cen region enable
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	UINT32 wdata=0;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);

		for(count=0;count<LX_PE_CMG_REGION_NUM;count++)
		{
			if(pstParams->enable[count])
				wdata |= (0x1<<(count+LX_PE_CMG_REGION_NUM));
			else
				wdata &= ~(0x1<<(count+LX_PE_CMG_REGION_NUM));

			if(pstParams->show_region[count])
				wdata |= (0x1<<(count));
			else
				wdata &= ~(0x1<<(count));
		}
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_RdFL(pe1_cen_ctrl_01);
				PE_P1L_H13B0_Wr(pe1_cen_ctrl_01,wdata);
				PE_P1L_H13B0_WrFL(pe1_cen_ctrl_01);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_RdFL(pe1_cen_ctrl_01);
				PE_P1L_H13_Wr(pe1_cen_ctrl_01,wdata);
				PE_P1L_H13_WrFL(pe1_cen_ctrl_01);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_cen_ctrl_01);
				PE_P1L_L9B0_Wr(pe1_l_cen_ctrl_01,wdata);
				PE_P1L_L9B0_WrFL(pe1_l_cen_ctrl_01);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_cen_ctrl_01);
				PE_P1R_L9B0_Wr(pe1_r_cen_ctrl_01,wdata);
				PE_P1R_L9B0_WrFL(pe1_r_cen_ctrl_01);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_cen_ctrl_01);
				PE_P1L_L9_Wr(pe1_l_cen_ctrl_01,wdata);
				PE_P1L_L9_WrFL(pe1_l_cen_ctrl_01);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_cen_ctrl_01);
				PE_P1R_L9_Wr(pe1_r_cen_ctrl_01,wdata);
				PE_P1R_L9_WrFL(pe1_r_cen_ctrl_01);
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get cen region enable
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_ENABLE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 rdata=0;
	UINT32 count=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_RdFL(pe1_cen_ctrl_01);
				rdata = PE_P1L_H13B0_Rd(pe1_cen_ctrl_01);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_RdFL(pe1_cen_ctrl_01);
				rdata = PE_P1L_H13_Rd(pe1_cen_ctrl_01);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_cen_ctrl_01);
				rdata = PE_P1L_L9B0_Rd(pe1_l_cen_ctrl_01);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_cen_ctrl_01);
				rdata = PE_P1R_L9B0_Rd(pe1_r_cen_ctrl_01);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_cen_ctrl_01);
				rdata = PE_P1L_L9_Rd(pe1_l_cen_ctrl_01);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_cen_ctrl_01);
				rdata = PE_P1R_L9_Rd(pe1_r_cen_ctrl_01);
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}

		for(count=0;count<LX_PE_CMG_REGION_NUM;count++)
		{
			if(rdata & (0x1<<(count+LX_PE_CMG_REGION_NUM)))
				pstParams->enable[count] = 1;
			else
				pstParams->enable[count] = 0;

			if(rdata & (0x1<<(count)))
				pstParams->show_region[count] = 1;
			else
				pstParams->show_region[count] = 0;
		}
	} while(0);
	return ret;
}
/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_CMG_HW_H13_SetCenRegion(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_SetCenRegion() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_SetCenRegion(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_SetCenRegion() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get cen region
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_CMG_HW_H13_GetCenRegion(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_GetCenRegion() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_GetCenRegion(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_GetCenRegion() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set cen region ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			ret = PE_CMG_HW_H13_SetCenRegionCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_SetCenRegionCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_SetCenRegionCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_SetCenRegionCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get cen region ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_CMG_HW_H13_GetCenRegionCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_GetCenRegionCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_GetCenRegionCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_GetCenRegionCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set cen global ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_GLOBAL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_CMG_HW_H13_SetCenGlobalCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_SetCenGlobalCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_SetCenGlobalCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_SetCenGlobalCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get cen global ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_GLOBAL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13)
		{
			PE_CMG_HW_H13_GetCenGlobalCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13_GetCenGlobalCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9)
		{
			ret = PE_CMG_HW_L9_GetCenGlobalCtrl(pstParams);
			PE_CMG_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_L9_GetCenGlobalCtrl() error.\n",__F__,__L__);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set cen color ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_DBG_PRINT("set pstParams[%d] : sat:%d\n",pstParams->win_id,pstParams->saturation);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));//[7:0] reg_ihsv_sgain
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_QWr01(pe1_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));//[7:0] reg_ihsv_sgain
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr01(pe1_l_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));	//[7:0] reg_ihsv_sgain
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr01(pe1_r_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));	//[7:0] reg_ihsv_sgain
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_cen_ctrl_02);
				PE_P1L_L9_Wr01(pe1_l_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));	//[7:0] reg_ihsv_sgain
				PE_P1L_L9_WrFL(pe1_l_cen_ctrl_02);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_cen_ctrl_02);
				PE_P1R_L9_Wr01(pe1_r_cen_ctrl_02, ihsv_sgain,	GET_BITS(pstParams->saturation,0,8));	//[7:0] reg_ihsv_sgain
				PE_P1R_L9_WrFL(pe1_r_cen_ctrl_02);
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get cen color ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_COLOR_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 rdata=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
			}
			pstParams->saturation=(UINT16)rdata;
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QRd01(pe1_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
			}
			pstParams->saturation=(UINT16)rdata;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd01(pe1_l_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain

			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd01(pe1_r_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
			}
			pstParams->saturation=(UINT16)rdata;
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_cen_ctrl_02);
				PE_P1L_L9_Rd01(pe1_l_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_cen_ctrl_02);
				PE_P1R_L9_Rd01(pe1_r_cen_ctrl_02, ihsv_sgain,	rdata);	//[7:0] reg_ihsv_sgain
			}
			pstParams->saturation=(UINT16)rdata;
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMG_DBG_PRINT("get pstParams[%d] : sat:%d\n",pstParams->win_id,pstParams->saturation);
	} while (0);
	return ret;
}
/**
 * set clear white
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_BIT_H13BX)
		{
			PE_CMG_DBG_PRINT("set[%d]:en:%d, yc_sel:%d, x:%d,%d,%d,%d,%d, y:%d,%d,%d,%d,%d\n"\
				"sel[0~3]%d,%d,%d,%d,[4~7]%d,%d,%d,%d,[8~11]%d,%d,%d,%d,[12~15]%d,%d,%d,%d, rgn_g:%d\n",\
				pstParams->win_id,pstParams->cw_en,pstParams->gain_sel,pstParams->gain_x[0],pstParams->gain_x[1],\
				pstParams->gain_x[2],pstParams->gain_x[3],pstParams->gain_x[4],pstParams->gain_y[0],\
				pstParams->gain_y[1],pstParams->gain_y[2],pstParams->gain_y[3],pstParams->gain_y[4],\
				GET_BITS(pstParams->region_sel,0,1),GET_BITS(pstParams->region_sel,1,1),\
				GET_BITS(pstParams->region_sel,2,1),GET_BITS(pstParams->region_sel,3,1),\
				GET_BITS(pstParams->region_sel,4,1),GET_BITS(pstParams->region_sel,5,1),\
				GET_BITS(pstParams->region_sel,6,1),GET_BITS(pstParams->region_sel,7,1),\
				GET_BITS(pstParams->region_sel,8,1),GET_BITS(pstParams->region_sel,9,1),\
				GET_BITS(pstParams->region_sel,10,1),GET_BITS(pstParams->region_sel,11,1),\
				GET_BITS(pstParams->region_sel,12,1),GET_BITS(pstParams->region_sel,13,1),\
				GET_BITS(pstParams->region_sel,14,1),GET_BITS(pstParams->region_sel,15,1),\
				pstParams->region_gain);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr04(pe1_cw_ctrl_00, 	cw_en,				GET_BITS(pstParams->cw_en,0,1),\
													cw_gain_selection,	GET_BITS(pstParams->gain_sel,0,1),\
													reg_cw_y4,			GET_BITS(pstParams->gain_y[4],0,8),\
													reg_cw_x4,			GET_BITS(pstParams->gain_x[4],0,8));
				PE_P1L_H13B0_QWr04(pe1_cw_ctrl_03,	reg_cw_y0,			GET_BITS(pstParams->gain_y[0],0,8),\
													reg_cw_x0,			GET_BITS(pstParams->gain_x[0],0,8),\
													reg_cw_y1,			GET_BITS(pstParams->gain_y[1],0,8),\
													reg_cw_x1,			GET_BITS(pstParams->gain_x[1],0,8));
				PE_P1L_H13B0_QWr04(pe1_cw_ctrl_02,	reg_cw_y2,			GET_BITS(pstParams->gain_y[2],0,8),\
													reg_cw_x2,			GET_BITS(pstParams->gain_x[2],0,8),\
													reg_cw_y3,			GET_BITS(pstParams->gain_y[3],0,8),\
													reg_cw_x3,			GET_BITS(pstParams->gain_x[3],0,8));
				PE_P1L_H13B0_RdFL(pe1_cw_ctrl_04);
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region0_sel,	GET_BITS(pstParams->region_sel,0,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region1_sel,	GET_BITS(pstParams->region_sel,1,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region2_sel,	GET_BITS(pstParams->region_sel,2,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region3_sel,	GET_BITS(pstParams->region_sel,3,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region4_sel,	GET_BITS(pstParams->region_sel,4,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region5_sel,	GET_BITS(pstParams->region_sel,5,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region6_sel,	GET_BITS(pstParams->region_sel,6,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region7_sel,	GET_BITS(pstParams->region_sel,7,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region8_sel,	GET_BITS(pstParams->region_sel,8,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region9_sel,	GET_BITS(pstParams->region_sel,9,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region10_sel,	GET_BITS(pstParams->region_sel,10,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region11_sel,	GET_BITS(pstParams->region_sel,11,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region12_sel,	GET_BITS(pstParams->region_sel,12,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region13_sel,	GET_BITS(pstParams->region_sel,13,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region14_sel,	GET_BITS(pstParams->region_sel,14,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region15_sel,	GET_BITS(pstParams->region_sel,15,1));
				PE_P1L_H13B0_Wr01(pe1_cw_ctrl_04,	color_region_gain,	GET_BITS(pstParams->region_gain,0,8));
				PE_P1L_H13B0_WrFL(pe1_cw_ctrl_04);
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get clear white
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_BIT_H13BX)
		{
			UINT32 sel_data;
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				if(pstParams->region_gain==0)	pstParams->region_gain=1;
				PE_P1L_H13B0_QRd04(pe1_cw_ctrl_00, 	cw_en,				(pstParams->cw_en),\
													cw_gain_selection,	(pstParams->gain_sel),\
													reg_cw_y4,			(pstParams->gain_y[4]),\
													reg_cw_x4,			(pstParams->gain_x[4]));
				PE_P1L_H13B0_QRd04(pe1_cw_ctrl_03,	reg_cw_y0,			(pstParams->gain_y[0]),\
													reg_cw_x0,			(pstParams->gain_x[0]),\
													reg_cw_y1,			(pstParams->gain_y[1]),\
													reg_cw_x1,			(pstParams->gain_x[1]));
				PE_P1L_H13B0_QRd04(pe1_cw_ctrl_02,	reg_cw_y2,			(pstParams->gain_y[2]),\
													reg_cw_x2,			(pstParams->gain_x[2]),\
													reg_cw_y3,			(pstParams->gain_y[3]),\
													reg_cw_x3,			(pstParams->gain_x[3]));
				PE_P1L_H13B0_RdFL(pe1_cw_ctrl_04);
				sel_data = PE_P1L_H13B0_Rd(pe1_cw_ctrl_04);
				pstParams->region_sel = GET_BITS(sel_data,0,16);	//[15:0]
				PE_P1L_H13B0_Rd01(pe1_cw_ctrl_04,	color_region_gain,	(pstParams->region_gain));
			}
			PE_CMG_DBG_PRINT("get[%d]:en:%d, yc_sel:%d, x:%d,%d,%d,%d,%d, y:%d,%d,%d,%d,%d\n"\
				"sel[0~3]%d,%d,%d,%d,[4~7]%d,%d,%d,%d,[8~11]%d,%d,%d,%d,[12~15]%d,%d,%d,%d, rgn_g:%d\n",\
				pstParams->win_id,pstParams->cw_en,pstParams->gain_sel,pstParams->gain_x[0],pstParams->gain_x[1],\
				pstParams->gain_x[2],pstParams->gain_x[3],pstParams->gain_x[4],pstParams->gain_y[0],\
				pstParams->gain_y[1],pstParams->gain_y[2],pstParams->gain_y[3],pstParams->gain_y[4],\
				GET_BITS(pstParams->region_sel,0,1),GET_BITS(pstParams->region_sel,1,1),\
				GET_BITS(pstParams->region_sel,2,1),GET_BITS(pstParams->region_sel,3,1),\
				GET_BITS(pstParams->region_sel,4,1),GET_BITS(pstParams->region_sel,5,1),\
				GET_BITS(pstParams->region_sel,6,1),GET_BITS(pstParams->region_sel,7,1),\
				GET_BITS(pstParams->region_sel,8,1),GET_BITS(pstParams->region_sel,9,1),\
				GET_BITS(pstParams->region_sel,10,1),GET_BITS(pstParams->region_sel,11,1),\
				GET_BITS(pstParams->region_sel,12,1),GET_BITS(pstParams->region_sel,13,1),\
				GET_BITS(pstParams->region_sel,14,1),GET_BITS(pstParams->region_sel,15,1),\
				pstParams->region_gain);
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set clear white gain
 *
 * @param   *pstParams [in] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_BIT_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr03(pe1_cw_ctrl_01,	user_ctrl_g_gain,	GET_BITS(pstParams->g_gain,0,8),\
													user_ctrl_b_gain,	GET_BITS(pstParams->b_gain,0,8),\
													user_ctrl_r_gain,	GET_BITS(pstParams->r_gain,0,8));
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get clear white gain
 *
 * @param   *pstParams [in/out] LX_PE_CMG_CW_GAIN_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_BIT_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QRd03(pe1_cw_ctrl_01,	user_ctrl_g_gain,	(pstParams->g_gain),\
													user_ctrl_b_gain,	(pstParams->b_gain),\
													user_ctrl_r_gain,	(pstParams->r_gain));
			}
		}
		else
		#endif
		{
			PE_CMG_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

