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


/** @file pe_dnt_hw_h13.c
 *
 *  driver for picture enhance deinterlacer functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.12
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
#include "pe_etc_hw.h"
#include "pe_dnt_hw.h"
#include "pe_dnt_hw_h13a0.h"
#include "pe_dnt_hw_h13b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DNT_HW_H13_ERROR	printk

#define PE_DNT_HW_H13_DBG_PRINT(fmt,args...)	\
	if(_g_dnt_hw_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_DNT_HW_H13_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_DNT_HW_H13_ERROR(fmt,##args);_action;}}
#define PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(_pre,_cur)	\
	PE_DNT_HW_H13_DBG_PRINT("%s(%d),%s(%d) : %s.\n",\
	#_pre,(_pre),#_cur,(_cur),((_pre)!=(_cur))? "different":"same")

#ifdef PE_DNT_HW_H13_SET_IPC_CLC_ON_TASK
#define PE_DNT_HW_H13B_SET_CLC_REG_TABLE(_mdl_,_tbl,_ofs)	\
	do{\
		PE_DNT_HW_H13_DBG_PRINT("write %s.\n",#_tbl);\
		ret = PE_DNT_HW_H13B_SetClcDfltTbl((_tbl),(_ofs),sizeof(_tbl));\
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13B_SetClcDfltTbl() error.\n",__F__,__L__);\
	}while(0)
#else
#define PE_DNT_HW_H13B_SET_CLC_REG_TABLE(_mdl_,_tbl,_ofs)	\
	do{\
		PE_SET_REG_TABLE(_mdl_,_tbl,_ofs);\
		PE_DNT_HW_H13B_GetDfltClcInfo(_tbl,_ofs,sizeof(_tbl));\
	}while(0)
#endif

#define PE_DNT_HW_H13B_SET_IPC_REG_TABLE(_tbl,_ofs)	\
	do{\
		PE_DNT_HW_H13_DBG_PRINT("write %s.\n",#_tbl);\
		ret = PE_DNT_HW_H13B_SetIpcDfltTbl((_tbl),(_ofs),sizeof(_tbl));\
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13B_SetIpcDfltTbl() error.\n",__F__,__L__);\
	}while(0)

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
static int PE_DNT_HW_H13B_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_DNT_HW_H13A_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static PE_DNT_HW_H13B_IPC_FMT PE_DNT_HW_H13B_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_DNT_HW_H13B_CLC_FMT PE_DNT_HW_H13B_ConvDispInfoToClcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_DNT_HW_H13B_VFY_FMT PE_DNT_HW_H13B_ConvDispInfoToVfyFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_DNT_HW_H13A_IPC_FMT PE_DNT_HW_H13A_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static PE_DNT_HW_H13A_FMD_FMT PE_DNT_HW_H13A_ConvDispInfoToFmdFmt(LX_PE_INF_DISPLAY_T *disp_inf);
static int PE_DNT_HW_H13B_SetIpcDfltTbl(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size);
#ifdef PE_DNT_HW_H13_SET_IPC_CLC_ON_TASK
static int PE_DNT_HW_H13B_SetClcDfltTbl(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size);
#else
static void PE_DNT_HW_H13B_GetDfltClcInfo(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_dnt_hw_h13_trace=0x0;		//default should be off.
static PE_DNT_HW_H13_SETTINGS_T _g_pe_dnt_hw_h13_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set debug print on off
 *
 * @param   on_off [in] UINT8
 * @return  void
 * @see
 * @author
 */
void PE_DNT_HW_H13_SetDbgPrint(UINT32 on_off)
{
	_g_dnt_hw_h13_trace = on_off? 1:0;
	return;
}

/**
 * init dnt
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_H13_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_H13BX)
		{
			memset(&_g_pe_dnt_hw_h13_info,0xffff,sizeof(PE_DNT_HW_H13_SETTINGS_T));
			PE_DNT_HW_H13_DBG_PRINT("init ipc, tpd.\n");
			/* init ipc */
			PE_SET_REG_TABLE(DNT_HW_H13,ipc_l_init_h13b0,PE_REG_H13_WRITE_BASE);
			PE_SET_REG_TABLE(DNT_HW_H13,ipc_l_init_h13b0,PE_PE0_REG_H13_LRDIFF);
			/* init clc */
			PE_SET_REG_TABLE(DNT_HW_H13,clc_l_init_h13b0,PE_REG_H13_WRITE_BASE);
			/* init vflt y */
			PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_init_h13b0,PE_REG_H13_WRITE_BASE);
			PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_init_h13b0,PE_PE0_REG_H13_LRDIFF);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_DNT_HW_H13_DBG_PRINT("init ipc, tpd.\n");
			/* init ipc */
			PE_SET_REG_TABLE(DNT_HW_H13,ipc_l_init_h13a0,0);
			PE_SET_REG_TABLE(DNT_HW_H13,ipc_r_init_h13a0,0);
			/* init tpd */
			PE_SET_REG_TABLE(DNT_HW_H13,fim_l_init_h13a0,0);
			PE_DNT_HW_H13_DBG_PRINT("init vmc : off.\n");
			/* vmc off(because of some artifact for h13a0) */
			PE_P0L_H13_RdFL(p0l_ipc_ctrl_30);
			PE_P0L_H13_Wr01(p0l_ipc_ctrl_30, reg_vmc_en,	0x0);
			PE_P0L_H13_WrFL(p0l_ipc_ctrl_30);
			PE_P0R_H13_RdFL(p0r_ipc_ctrl_30);
			PE_P0R_H13_Wr01(p0r_ipc_ctrl_30, reg_vmc_en,	0x0);
			PE_P0R_H13_WrFL(p0r_ipc_ctrl_30);
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);	
	return ret;
}

/**
 * set dnt default
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_H13_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13BX)
		{
			ret = PE_DNT_HW_H13B_SetDefault(pstParams);
			PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13B_SetDefault() error.\n",__F__,__L__);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			ret = PE_DNT_HW_H13A_SetDefault(pstParams);
			PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_DNT_HW_H13A_SetDefault() error.\n",__F__,__L__);
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);	
	return ret;
}
/**
 * set dnt default(for H13BX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_HW_H13B_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_INF_H13_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_DNT_HW_H13B_IPC_FMT cur0_ipc_fmt,cur1_ipc_fmt;
	PE_DNT_HW_H13B_CLC_FMT cur0_clc_fmt;
	PE_DNT_HW_H13B_VFY_FMT cur0_vfy_fmt,cur1_vfy_fmt;
	static PE_DNT_HW_H13B_IPC_FMT pre0_ipc_fmt = PE_DNT_H13B_IPC_NUM;
	static PE_DNT_HW_H13B_IPC_FMT pre1_ipc_fmt = PE_DNT_H13B_IPC_NUM;
	static PE_DNT_HW_H13B_CLC_FMT pre0_clc_fmt = PE_DNT_H13B_CLC_NUM;
	static PE_DNT_HW_H13B_VFY_FMT pre0_vfy_fmt = PE_DNT_H13B_VFY_NUM;
	static PE_DNT_HW_H13B_VFY_FMT pre1_vfy_fmt = PE_DNT_H13B_VFY_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_H13_GetCurInfSettings(&inf_set);
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		/* L : ipc */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_ipc_fmt = PE_DNT_HW_H13B_ConvDispInfoToIpcFmt(cur0_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre0_ipc_fmt,cur0_ipc_fmt);
			if(pre0_ipc_fmt!=cur0_ipc_fmt)
			{
				switch(cur0_ipc_fmt)
				{
					case PE_DNT_H13B_IPC_ATV_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_atv_480_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_ATV_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_atv_576_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_DTV_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_dtv_480_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_DTV_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_dtv_576_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_DTV_HD:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_dtv_hd_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_AV_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_av_480_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_AV_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_av_576_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_SCARTRGB:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_scartrgb_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_SD_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_sd_480_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_SD_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_sd_576_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_HD:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_hd_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_IPC_PC:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_pc_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					default:
						break;
				}
				#if 0	// changed_to_fw_control
				PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
				PE_P1L_H13B0_Wr01(pe1_dse_ctrl_01, reg_fmd_en_0,	0x1);
				PE_P1L_H13B0_WrFL(pe1_dse_ctrl_01);
				#endif
				pre0_ipc_fmt=cur0_ipc_fmt;
			}
		}
		/* R : ipc */
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			cur1_ipc_fmt = PE_DNT_HW_H13B_ConvDispInfoToIpcFmt(cur1_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre1_ipc_fmt,cur1_ipc_fmt);
			if(pre1_ipc_fmt!=cur1_ipc_fmt)
			{
				switch(cur1_ipc_fmt)
				{
					case PE_DNT_H13B_IPC_ATV_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_atv_480_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_ATV_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_atv_576_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_DTV_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_dtv_480_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_DTV_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_dtv_576_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_DTV_HD:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_dtv_hd_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_AV_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_av_480_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_AV_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_av_576_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_SCARTRGB:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_scartrgb_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_SD_480:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_sd_480_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_SD_576:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_sd_576_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_HD:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_hd_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_IPC_PC:
						PE_DNT_HW_H13B_SET_IPC_REG_TABLE(ipc_l_pc_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					default:
						break;
				}
				#if 0	// changed_to_fw_control
				PE_P1L_H13B0_RdFL(pe1_dse_ctrl_01);
				PE_P1L_H13B0_Wr01(pe1_dse_ctrl_01, reg_fmd_en_1,	0x1);
				PE_P1L_H13B0_WrFL(pe1_dse_ctrl_01);
				#endif
				pre1_ipc_fmt=cur1_ipc_fmt;
			}
		}
		/* L : clc */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_clc_fmt = PE_DNT_HW_H13B_ConvDispInfoToClcFmt(cur0_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre0_clc_fmt,cur0_clc_fmt);
			if(pre0_clc_fmt!=cur0_clc_fmt)
			{
				switch(cur0_clc_fmt)
				{
					case PE_DNT_H13B_CLC_AV:
						PE_DNT_HW_H13B_SET_CLC_REG_TABLE(DNT_HW_H13,clc_l_av_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_CLC_SD:
						PE_DNT_HW_H13B_SET_CLC_REG_TABLE(DNT_HW_H13,clc_l_sd_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_CLC_HD:
						PE_DNT_HW_H13B_SET_CLC_REG_TABLE(DNT_HW_H13,clc_l_hd_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_CLC_PC:
						PE_DNT_HW_H13B_SET_CLC_REG_TABLE(DNT_HW_H13,clc_l_pc_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					default:
						break;
				}
				pre0_clc_fmt=cur0_clc_fmt;
			}
		}
		/* L : vflt y */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_vfy_fmt = PE_DNT_HW_H13B_ConvDispInfoToVfyFmt(cur0_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre0_vfy_fmt,cur0_vfy_fmt);
			if(pre0_vfy_fmt!=cur0_vfy_fmt)
			{
				switch(cur0_vfy_fmt)
				{
					case PE_DNT_H13B_VFY_SD:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_sd_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_VFY_HD_I:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_hd_i_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_VFY_HD_P:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_hd_p_default_h13b0,	PE_REG_H13_WRITE_BASE);
						break;
					case PE_DNT_H13B_VFY_PC:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_pc_default_h13b0,		PE_REG_H13_WRITE_BASE);
						break;
					default:
						break;
				}
				pre0_vfy_fmt=cur0_vfy_fmt;
			}
		}
		/* R : vflt y */
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			cur1_vfy_fmt = PE_DNT_HW_H13B_ConvDispInfoToVfyFmt(cur1_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre1_vfy_fmt,cur1_vfy_fmt);
			if(pre1_vfy_fmt!=cur1_vfy_fmt)
			{
				switch(cur1_vfy_fmt)
				{
					case PE_DNT_H13B_VFY_SD:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_sd_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_VFY_HD_I:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_hd_i_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_VFY_HD_P:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_hd_p_default_h13b0,	PE_PE0_REG_H13_LRDIFF);
						break;
					case PE_DNT_H13B_VFY_PC:
						PE_SET_REG_TABLE(DNT_HW_H13,vflt_y_l_pc_default_h13b0,		PE_PE0_REG_H13_LRDIFF);
						break;
					default:
						break;
				}
				pre1_vfy_fmt=cur1_vfy_fmt;
			}
		}
	}while(0);	
	return ret;
}
/**
 * set dnt default(for H13AX)
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_DNT_HW_H13A_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_INF_H13_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	LX_PE_INF_DISPLAY_T *cur1_inf = NULL;
	PE_DNT_HW_H13A_IPC_FMT cur0_ipc_fmt,cur1_ipc_fmt;
	PE_DNT_HW_H13A_FMD_FMT cur0_fmd_fmt,cur1_fmd_fmt;
	static PE_DNT_HW_H13A_IPC_FMT pre0_ipc_fmt = PE_DNT_H13A_IPC_NUM;
	static PE_DNT_HW_H13A_IPC_FMT pre1_ipc_fmt = PE_DNT_H13A_IPC_NUM;
	static PE_DNT_HW_H13A_FMD_FMT pre0_fmd_fmt = PE_DNT_H13A_FMD_NUM;
	static PE_DNT_HW_H13A_FMD_FMT pre1_fmd_fmt = PE_DNT_H13A_FMD_NUM;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		ret = PE_INF_H13_GetCurInfSettings(&inf_set);
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
		cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
		cur1_inf=&inf_set.disp_info[LX_PE_WIN_1];
		CHECK_KNULL(cur0_inf);
		CHECK_KNULL(cur1_inf);
		/* L : ipc */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_ipc_fmt = PE_DNT_HW_H13A_ConvDispInfoToIpcFmt(cur0_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre0_ipc_fmt,cur0_ipc_fmt);
			if(pre0_ipc_fmt!=cur0_ipc_fmt)
			{
				switch(cur0_ipc_fmt)
				{
					case PE_DNT_H13A_IPC_SD:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_IPC_HD:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_hd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_IPC_AV:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_av_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_IPC_DTV_SD:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_dtv_sd_l_default_h13a0,0);
						break;
					default:
						break;
				}
				pre0_ipc_fmt=cur0_ipc_fmt;
			}
		}
		/* R : ipc */
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			cur1_ipc_fmt = PE_DNT_HW_H13A_ConvDispInfoToIpcFmt(cur1_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre1_ipc_fmt,cur1_ipc_fmt);
			if(pre1_ipc_fmt!=cur1_ipc_fmt)
			{
				switch(cur1_ipc_fmt)
				{
					case PE_DNT_H13A_IPC_SD:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_IPC_HD:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_hd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_IPC_AV:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_av_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_IPC_DTV_SD:
						PE_SET_REG_TABLE(DNT_HW_H13,ipc_dtv_sd_r_default_h13a0,0);
						break;
					default:
						break;
				}
				pre1_ipc_fmt=cur1_ipc_fmt;
			}
		}
		/* L : film mode */
		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			cur0_fmd_fmt = PE_DNT_HW_H13A_ConvDispInfoToFmdFmt(cur0_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre0_fmd_fmt,cur0_fmd_fmt);
			if(pre0_fmd_fmt!=cur0_fmd_fmt)
			{
				switch(cur0_fmd_fmt)
				{
					case PE_DNT_H13A_FMD_ATV_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_atv_60hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_ATV_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_atv_50hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_AV_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_av_60hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_AV_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_av_50hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_DTV_SD_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_dtv_60hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_DTV_SD_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_dtv_50hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_DTV_HD:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_dtv_hd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_HDMI_SD_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_hdmi_60hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_HDMI_SD_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_hdmi_50hz_sd_l_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_HD:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_all_hd_l_default_h13a0,0);
						break;
					default:
						break;
				}
				pre0_fmd_fmt=cur0_fmd_fmt;
			}
		}
		/* R : film mode */
		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			cur1_fmd_fmt = PE_DNT_HW_H13A_ConvDispInfoToFmdFmt(cur1_inf);
			PE_DNT_HW_H13_DBG_PRINT_FMT_STATE(pre1_fmd_fmt,cur1_fmd_fmt);
			if(pre1_fmd_fmt!=cur1_fmd_fmt)
			{
				switch(cur1_fmd_fmt)
				{
					case PE_DNT_H13A_FMD_ATV_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_atv_60hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_ATV_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_atv_50hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_AV_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_av_60hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_AV_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_av_50hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_DTV_SD_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_dtv_60hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_DTV_SD_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_dtv_50hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_DTV_HD:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_dtv_hd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_HDMI_SD_60:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_hdmi_60hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_HDMI_SD_50:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_hdmi_50hz_sd_r_default_h13a0,0);
						break;
					case PE_DNT_H13A_FMD_HD:
						PE_SET_REG_TABLE(DNT_HW_H13,fmd_all_hd_r_default_h13a0,0);
						break;
					default:
						break;
				}
				pre1_fmd_fmt=cur1_fmd_fmt;
			}
		}
	}while(0);	
	return ret;
}
/**
 * get ipc fmt using display info(for H13BX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static PE_DNT_HW_H13B_IPC_FMT PE_DNT_HW_H13B_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_H13B_IPC_FMT ipc_fmt = PE_DNT_H13B_IPC_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				ipc_fmt = PE_DNT_H13B_IPC_ATV_480;
			}
			else
			{
				ipc_fmt = PE_DNT_H13B_IPC_ATV_576;
			}
			break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_SCARTRGB)
			{
				ipc_fmt = PE_DNT_H13B_IPC_SCARTRGB;
			}
			else if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				ipc_fmt = PE_DNT_H13B_IPC_AV_480;
			}
			else
			{
				ipc_fmt = PE_DNT_H13B_IPC_AV_576;
			}
			break;
		case LX_PE_SRC_PC:
			{
				ipc_fmt = PE_DNT_H13B_IPC_PC;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->fr_type==LX_PE_FR_60HZ)
					{
						ipc_fmt = PE_DNT_H13B_IPC_DTV_480;
					}
					else
					{
						ipc_fmt = PE_DNT_H13B_IPC_DTV_576;
					}
				}
				else
				{
					ipc_fmt = PE_DNT_H13B_IPC_DTV_HD;
				}
			}
			else
			{
				ipc_fmt = PE_DNT_H13B_IPC_PC;
			}
			break;
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
			{
				if(disp_inf->fmt_type==LX_PE_FMT_SD)
				{
					if(disp_inf->fr_type==LX_PE_FR_60HZ)
					{
						ipc_fmt = PE_DNT_H13B_IPC_SD_480;
					}
					else
					{
						ipc_fmt = PE_DNT_H13B_IPC_SD_576;
					}
				}
				else
				{
					ipc_fmt = PE_DNT_H13B_IPC_HD;
				}
			}
			else
			{
				ipc_fmt = PE_DNT_H13B_IPC_PC;
			}
			break;
	}
	return ipc_fmt;
}
/**
 * get clc fmt using display info(for H13BX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_DNT_HW_H13B_CLC_FMT
 * @see
 * @author
 */
static PE_DNT_HW_H13B_CLC_FMT PE_DNT_HW_H13B_ConvDispInfoToClcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_H13B_CLC_FMT clc_fmt = PE_DNT_H13B_CLC_NUM;
	if((disp_inf->out_type>=LX_PE_OUT_UD && disp_inf->out_type<=LX_PE_OUT_DUAL_FULL) || \
		(disp_inf->out_type==LX_PE_OUT_3D_2D))
	{
		clc_fmt = PE_DNT_H13B_CLC_PC;
	}
	else	//2d,2d_3d,pip
	{
		switch(disp_inf->src_type)
		{
			case LX_PE_SRC_ATV:
			case LX_PE_SRC_CVBS:
				{
					clc_fmt = PE_DNT_H13B_CLC_AV;
				}
				break;
			case LX_PE_SRC_PC:
				{
					clc_fmt = PE_DNT_H13B_CLC_PC;
				}
				break;
			case LX_PE_SRC_DTV:
			case LX_PE_SRC_COMP:
			case LX_PE_SRC_HDMI:
			default:
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					if(disp_inf->fmt_type==LX_PE_FMT_SD)
					{
						clc_fmt = PE_DNT_H13B_CLC_SD;
					}
					else
					{
						clc_fmt = PE_DNT_H13B_CLC_HD;
					}
				}
				else
				{
					clc_fmt = PE_DNT_H13B_CLC_PC;
				}
				break;
		}
	}
	return clc_fmt;
}
/**
 * get vflt y fmt using display info(for H13BX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  PE_DNT_HW_H13B_VFY_FMT
 * @see
 * @author
 */
static PE_DNT_HW_H13B_VFY_FMT PE_DNT_HW_H13B_ConvDispInfoToVfyFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_H13B_VFY_FMT vfy_fmt = PE_DNT_H13B_VFY_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
		case LX_PE_SRC_CVBS:
			{
				vfy_fmt = PE_DNT_H13B_VFY_SD;
			}
			break;
		case LX_PE_SRC_PC:
			{
				vfy_fmt = PE_DNT_H13B_VFY_PC;
			}
			break;
		case LX_PE_SRC_DTV:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				vfy_fmt = PE_DNT_H13B_VFY_SD;
			}
			else
			{
				if(disp_inf->scan_type==LX_PE_SCAN_INTERLACE)
				{
					vfy_fmt = PE_DNT_H13B_VFY_HD_I;
				}
				else
				{
					vfy_fmt = PE_DNT_H13B_VFY_HD_P;
				}
			}
			break;
	}
	return vfy_fmt;
}

#ifdef PE_DNT_HW_H13_SET_IPC_CLC_ON_TASK
/**
 * set ipc default settings(for H13BX)
 *	- keep 0x0500,0x2500[1:0]cr_luma_mode,[5:4]cr_chroma_mode,[31]cr_film_mode_enable
 *
 * @param   *table [in] PE_REG_PARAM_T
 * @param   offset [in] UINT32
 * @param   size [in] UINT32
 * @return  void
 * @see
 * @author
 */
static int PE_DNT_HW_H13B_SetIpcDfltTbl(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size)
{
	int ret = RET_OK;
	UINT32 table_size,i,r_data;
	PE_REG_PARAM_T *p_data = NULL;
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do {
		PE_DNT_HW_H13_CHECK_CODE(!table,break,"[%s,%d] table is null.\n",__F__,__L__);
		PE_DNT_HW_H13_CHECK_CODE(!size,break,"[%s,%d] size is zero.\n",__F__,__L__);
		p_data = (PE_REG_PARAM_T *)OS_Malloc(size);
		PE_DNT_HW_H13_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);
		table_size = size/sizeof(PE_REG_PARAM_T);
		for(i=0;i<table_size;i++)
		{
			p_data[i].addr = table[i].addr;
			if((table[i].addr+offset)==0x0500)
			{
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_00);
				r_data = PE_P0L_H13B0_Rd(p0l_ipc_ctrl_00);
				p_data[i].data = (table[i].data&0x7fffffcc)|(r_data&0x80000033);
				pInfo->cur_p0l_ipc_ctrl_00 = table[i].data;
			}
			else if((table[i].addr+offset)==0x2500)
			{
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_00);
				r_data = PE_P0R_H13B0_Rd(p0r_ipc_ctrl_00);
				p_data[i].data = (table[i].data&0x7fffffcc)|(r_data&0x80000033);
				pInfo->cur_p0r_ipc_ctrl_00 = table[i].data;
			}
			else
			{
				p_data[i].data = table[i].data;
			}
		}
		ret = PE_REG_SetTable(p_data,offset,size);
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
	}while(0);
	if(p_data){OS_Free(p_data);}
	return ret;
}

/**
 * set clc default settings(for H13BX)
 *	- keep 0x0560 [1]cl_filter_enable
 *
 * @param   *table [in] PE_REG_PARAM_T
 * @param   offset [in] UINT32
 * @param   size [in] UINT32
 * @return  void
 * @see
 * @author
 */
static int PE_DNT_HW_H13B_SetClcDfltTbl(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size)
{
	int ret = RET_OK;
	UINT32 table_size,i,r_data;
	PE_REG_PARAM_T *p_data = NULL;
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do {
		PE_DNT_HW_H13_CHECK_CODE(!table,break,"[%s,%d] table is null.\n",__F__,__L__);
		PE_DNT_HW_H13_CHECK_CODE(!size,break,"[%s,%d] size is zero.\n",__F__,__L__);
		p_data = (PE_REG_PARAM_T *)OS_Malloc(size);
		PE_DNT_HW_H13_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);
		table_size = size/sizeof(PE_REG_PARAM_T);
		for(i=0;i<table_size;i++)
		{
			p_data[i].addr = table[i].addr;
			if((table[i].addr+offset)==0x0560)
			{
				PE_P0L_H13B0_RdFL(p0l_clc_ctrl_00);
				r_data = PE_P0L_H13B0_Rd(p0l_clc_ctrl_00);
				p_data[i].data = (table[i].data&0xfffffff9)|(r_data&0x00000006);
				pInfo->cur_p0l_clc_ctrl_00 = table[i].data;
			}
			else
			{
				p_data[i].data = table[i].data;
			}
		}
		ret = PE_REG_SetTable(p_data,offset,size);
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
	}while(0);
	if(p_data){OS_Free(p_data);}
	return ret;
}
#else
/**
 * set ipc default settings(for H13BX)
 *	- avoid film mode setting
 *
 * @param   *table [in] PE_REG_PARAM_T
 * @param   offset [in] UINT32
 * @param   size [in] UINT32
 * @return  void
 * @see
 * @author
 */
static int PE_DNT_HW_H13B_SetIpcDfltTbl(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size)
{
	int ret = RET_OK;
	UINT32 table_size,i,r_data;
	PE_REG_PARAM_T *p_data = NULL;
	do {
		PE_DNT_HW_H13_CHECK_CODE(!table,break,"[%s,%d] table is null.\n",__F__,__L__);
		PE_DNT_HW_H13_CHECK_CODE(!size,break,"[%s,%d] size is zero.\n",__F__,__L__);
		p_data = (PE_REG_PARAM_T *)OS_Malloc(size);
		PE_DNT_HW_H13_CHECK_CODE(!p_data,break,"[%s,%d] p_data is null.\n",__F__,__L__);
		table_size = size/sizeof(PE_REG_PARAM_T);
		for(i=0;i<table_size;i++)
		{
			p_data[i].addr = table[i].addr;
			if((table[i].addr+offset)==0x0500)
			{
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_00);
				r_data = PE_P0L_H13B0_Rd(p0l_ipc_ctrl_00);
				p_data[i].data = (table[i].data&0x7fffffff)|(r_data&0x80000000);
			}
			else if((table[i].addr+offset)==0x2500)
			{
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_00);
				r_data = PE_P0R_H13B0_Rd(p0r_ipc_ctrl_00);
				p_data[i].data = (table[i].data&0x7fffffff)|(r_data&0x80000000);
			}
			else
			{
				p_data[i].data = table[i].data;
			}
		}
		ret = PE_REG_SetTable(p_data,offset,size);
		PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
	}while(0);
	if(p_data){OS_Free(p_data);}
	return ret;
}

/**
 * get clc info from clc default settings(for H13BX)
 *
 * @param   *table [in] PE_REG_PARAM_T
 * @param   offset [in] UINT32
 * @param   size [in] UINT32
 * @return  void
 * @see
 * @author
 */
static void PE_DNT_HW_H13B_GetDfltClcInfo(const PE_REG_PARAM_T *table, UINT32 offset, UINT32 size)
{
	UINT32 table_size,i;
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do {
		PE_DNT_HW_H13_CHECK_CODE(!table,break,"[%s,%d] table is null.\n",__F__,__L__);
		PE_DNT_HW_H13_CHECK_CODE(!size,break,"[%s,%d] size is zero.\n",__F__,__L__);
		table_size = size/sizeof(PE_REG_PARAM_T);
		for(i=0;i<table_size;i++)
		{
			if((table[i].addr+offset)==0x0560)
			{
				pInfo->cur_p0l_clc_ctrl_00 = table[i].data;
				PE_DNT_HW_H13_DBG_PRINT("set:clc_ctrl_00:0x%08x\n",pInfo->cur_p0l_clc_ctrl_00);
				break;
			}
		}
	}while(0);
	return;
}
#endif

/**
 * get ipc fmt using display info(for H13AX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static PE_DNT_HW_H13A_IPC_FMT PE_DNT_HW_H13A_ConvDispInfoToIpcFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_H13A_IPC_FMT ipc_fmt = PE_DNT_H13A_IPC_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			{
				ipc_fmt = PE_DNT_H13A_IPC_SD;
			}
			break;
		case LX_PE_SRC_CVBS:
			{
				ipc_fmt = PE_DNT_H13A_IPC_AV;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				ipc_fmt = PE_DNT_H13A_IPC_DTV_SD;
			}
			else
			{
				ipc_fmt = PE_DNT_H13A_IPC_HD;
			}
			break;
		case LX_PE_SRC_PC:
		case LX_PE_SRC_COMP:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				ipc_fmt = PE_DNT_H13A_IPC_SD;
			}
			else
			{
				ipc_fmt = PE_DNT_H13A_IPC_HD;
			}
			break;
	}
	return ipc_fmt;
}
/**
 * get fmd fmt using display info(for H13AX)
 *
 * @param   *disp_inf [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static PE_DNT_HW_H13A_FMD_FMT PE_DNT_HW_H13A_ConvDispInfoToFmdFmt(LX_PE_INF_DISPLAY_T *disp_inf)
{
	PE_DNT_HW_H13A_FMD_FMT fmd_fmt = PE_DNT_H13A_FMD_NUM;
	switch(disp_inf->src_type)
	{
		case LX_PE_SRC_ATV:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				fmd_fmt = PE_DNT_H13A_FMD_ATV_60;
			}
			else
			{
				fmd_fmt = PE_DNT_H13A_FMD_ATV_50;
			}
			break;
		case LX_PE_SRC_CVBS:
			if(disp_inf->fmt_type==LX_PE_FMT_NTSC)
			{
				fmd_fmt = PE_DNT_H13A_FMD_AV_60;
			}
			else
			{
				fmd_fmt = PE_DNT_H13A_FMD_AV_50;
			}
			break;
		case LX_PE_SRC_COMP:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					fmd_fmt = PE_DNT_H13A_FMD_AV_60;
				}
				else
				{
					fmd_fmt = PE_DNT_H13A_FMD_AV_50;
				}
			}
			else	//hd
			{
				fmd_fmt = PE_DNT_H13A_FMD_HD;
			}
			break;
		case LX_PE_SRC_DTV:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					fmd_fmt = PE_DNT_H13A_FMD_DTV_SD_60;
				}
				else
				{
					fmd_fmt = PE_DNT_H13A_FMD_DTV_SD_50;
				}
			}
			else	//hd
			{
				fmd_fmt = PE_DNT_H13A_FMD_DTV_HD;
			}
			break;
		case LX_PE_SRC_PC:
		case LX_PE_SRC_HDMI:
		default:
			if(disp_inf->fmt_type==LX_PE_FMT_SD)
			{
				if(disp_inf->fr_type==LX_PE_FR_60HZ)
				{
					fmd_fmt = PE_DNT_H13A_FMD_HDMI_SD_60;
				}
				else
				{
					fmd_fmt = PE_DNT_H13A_FMD_HDMI_SD_50;
				}
			}
			else	//hd
			{
				fmd_fmt = PE_DNT_H13A_FMD_HD;
			}
			break;
	}
	return fmd_fmt;
}

/**
 * set low delay mode : control game_en,clc_en
 *
 * @param   *pstParams [in] LX_PE_DNT_LD_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_H13_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams)
{
	int ret = RET_OK;
	UINT32 cr_game_en,blk_lin_en,dbg_map_en;
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DNT_HW_H13_DBG_PRINT("set[%d]:en:%d\n",pstParams->win_id,pstParams->enable);
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_DNT_HW_H13_SET_IPC_CLC_ON_TASK
				cr_game_en = (pstParams->enable)? 0x1:0x0;
				blk_lin_en = 0x0;
				dbg_map_en = (pstParams->enable)? 0x1:0x0;
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_01);
				PE_P0L_H13B0_Wr01(p0l_ipc_ctrl_01, cr_game_mode,			cr_game_en);
				PE_P0L_H13B0_WrFL(p0l_ipc_ctrl_01);
				PE_P0L_H13B0_RdFL(p0l_tnr_ctrl_10);
				PE_P0L_H13B0_Wr01(p0l_tnr_ctrl_10, tnr_black_line_en_for_i,	blk_lin_en);
				PE_P0L_H13B0_Wr01(p0l_tnr_ctrl_10, tnr_debug_map_en_for_i,	dbg_map_en);
				PE_P0L_H13B0_WrFL(p0l_tnr_ctrl_10);
				pInfo->cur_game_mode = cr_game_en;
				PE_DNT_HW_H13_DBG_PRINT("set0:game:0x%x,tnr_line(dbg):0x%x(0x%x)\n",\
					cr_game_en,blk_lin_en,dbg_map_en);
				#else
				UINT32 clc_flt_en,clc_det_en;
				cr_game_en = (pstParams->enable)? 0x1:0x0;
				clc_flt_en = (pstParams->enable)? 0x0:GET_BITS(pInfo->cur_p0l_clc_ctrl_00,1,1);	//[1]
				clc_det_en = (pstParams->enable)? 0x0:GET_BITS(pInfo->cur_p0l_clc_ctrl_00,2,1);	//[2]
				blk_lin_en = 0x0;
				dbg_map_en = (pstParams->enable)? 0x1:0x0;
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_01);
				PE_P0L_H13B0_Wr01(p0l_ipc_ctrl_01, cr_game_mode,			cr_game_en);
				PE_P0L_H13B0_WrFL(p0l_ipc_ctrl_01);
				PE_P0L_H13B0_RdFL(p0l_clc_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_clc_ctrl_00, cl_filter_enable,		clc_flt_en);
				PE_P0L_H13B0_Wr01(p0l_clc_ctrl_00, clc_detection_enable,	clc_det_en);
				PE_P0L_H13B0_WrFL(p0l_clc_ctrl_00);
				PE_P0L_H13B0_RdFL(p0l_tnr_ctrl_10);
				PE_P0L_H13B0_Wr01(p0l_tnr_ctrl_10, tnr_black_line_en_for_i,	blk_lin_en);
				PE_P0L_H13B0_Wr01(p0l_tnr_ctrl_10, tnr_debug_map_en_for_i,	dbg_map_en);
				PE_P0L_H13B0_WrFL(p0l_tnr_ctrl_10);
				PE_DNT_HW_H13_DBG_PRINT("inf0:clc_ctrl_00:0x%08x)\n",pInfo->cur_p0l_clc_ctrl_00);
				PE_DNT_HW_H13_DBG_PRINT("set0:game:0x%x,clc(det):0x%x(0x%x),tnr_line(dbg):0x%x(0x%x)\n",\
					cr_game_en,clc_flt_en,clc_det_en,blk_lin_en,dbg_map_en);
				#endif
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				cr_game_en = (pstParams->enable)? 0x1:0x0;
				blk_lin_en = 0x0;
				dbg_map_en = (pstParams->enable)? 0x1:0x0;
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_01);
				PE_P0R_H13B0_Wr01(p0r_ipc_ctrl_01, cr_game_mode,			cr_game_en);
				PE_P0R_H13B0_WrFL(p0r_ipc_ctrl_01);
				PE_P0R_H13B0_RdFL(p0r_tnr_ctrl_10);
				PE_P0R_H13B0_Wr01(p0r_tnr_ctrl_10, tnr_black_line_en_for_i,	blk_lin_en);
				PE_P0R_H13B0_Wr01(p0r_tnr_ctrl_10, tnr_debug_map_en_for_i,	dbg_map_en);
				PE_P0R_H13B0_WrFL(p0r_tnr_ctrl_10);
				PE_DNT_HW_H13_DBG_PRINT("set1:game:0x%x,tnr_line(dbg):0x%x(0x%x)\n",\
					cr_game_en,blk_lin_en,dbg_map_en);
			}
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get low delay mode : game_en
 *
 * @param   *pstParams [in] LX_PE_DNT_LD_MODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_H13_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_01);
				PE_P0L_H13B0_Rd01(p0l_ipc_ctrl_01, cr_game_mode,	pstParams->enable);
				PE_DNT_HW_H13_DBG_PRINT("inf0:clc_ctrl_00:0x%08x\n",pInfo->cur_p0l_clc_ctrl_00);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_01);
				PE_P0R_H13B0_Rd01(p0r_ipc_ctrl_01, cr_game_mode,	pstParams->enable);
			}
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_DNT_HW_H13_DBG_PRINT("get[%d]:en:%d\n",pstParams->win_id,pstParams->enable);
	}while(0);
	return ret;
}

/**
 * set ipc and clc mode
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_H13_SetIpcClcMode(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	static UINT32 count = 0;
	UINT32 cur_ipc_y_md[LX_PE_WIN_NUM],cur_ipc_c_md[LX_PE_WIN_NUM];	//[0]:L,[1]:R
	UINT32 cur_clc_flt_en,cur_clc_det_en;
	PE_INF_H13_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13)
		{
			/* check ipc,clc off case */
			if(ctrl0_info->is_src_frz && !ctrl0_info->mute_on && \
				disp0_info->src_type==LX_PE_SRC_DTV && disp0_info->dtv_type==LX_PE_DTV_FILEPLAY && \
				disp0_info->fmt_type==LX_PE_FMT_HD && disp0_info->scan_type==LX_PE_SCAN_INTERLACE)
			{
				#ifdef PE_DNT_HW_H13_SET_ONLY_CLC_ON_TASK
				cur_ipc_y_md[LX_PE_WIN_0] = GET_BITS(pInfo->cur_p0l_ipc_ctrl_00,0,2);		//[1:0]
				cur_ipc_c_md[LX_PE_WIN_0] = GET_BITS(pInfo->cur_p0l_ipc_ctrl_00,4,2);		//[5:4]
				cur_ipc_y_md[LX_PE_WIN_1] = GET_BITS(pInfo->cur_p0r_ipc_ctrl_00,0,2);		//[1:0]
				cur_ipc_c_md[LX_PE_WIN_1] = GET_BITS(pInfo->cur_p0r_ipc_ctrl_00,4,2);		//[5:4]
				#else
				cur_ipc_y_md[LX_PE_WIN_0] = PE_DNT_HW_H13_IPC_2D;		//[1:0]
				cur_ipc_c_md[LX_PE_WIN_0] = PE_DNT_HW_H13_IPC_2D;		//[5:4]
				if(disp0_info->out_type>=LX_PE_OUT_UD && disp0_info->out_type<=LX_PE_OUT_DUAL_FULL)
				{
					cur_ipc_y_md[LX_PE_WIN_1] = PE_DNT_HW_H13_IPC_2D;		//[1:0]
					cur_ipc_c_md[LX_PE_WIN_1] = PE_DNT_HW_H13_IPC_2D;		//[5:4]
				}
				else
				{
					cur_ipc_y_md[LX_PE_WIN_1] = GET_BITS(pInfo->cur_p0r_ipc_ctrl_00,0,2);		//[1:0]
					cur_ipc_c_md[LX_PE_WIN_1] = GET_BITS(pInfo->cur_p0r_ipc_ctrl_00,4,2);		//[5:4]
				}
				#endif
				cur_clc_flt_en = PE_DNT_HW_H13_CLC_OFF;		//[1]
				cur_clc_det_en = PE_DNT_HW_H13_CLC_OFF;		//[2]
			}
			else
			{
				cur_ipc_y_md[LX_PE_WIN_0] = GET_BITS(pInfo->cur_p0l_ipc_ctrl_00,0,2);		//[1:0]
				cur_ipc_c_md[LX_PE_WIN_0] = GET_BITS(pInfo->cur_p0l_ipc_ctrl_00,4,2);		//[5:4]
				cur_ipc_y_md[LX_PE_WIN_1] = GET_BITS(pInfo->cur_p0r_ipc_ctrl_00,0,2);		//[1:0]
				cur_ipc_c_md[LX_PE_WIN_1] = GET_BITS(pInfo->cur_p0r_ipc_ctrl_00,4,2);		//[5:4]
				/* clc off when game mode on */
				if(pInfo->cur_game_mode)
				{
					cur_clc_flt_en = PE_DNT_HW_H13_CLC_OFF;		//[1]
					cur_clc_det_en = PE_DNT_HW_H13_CLC_OFF;		//[2]
				}
				else
				{
					cur_clc_flt_en = GET_BITS(pInfo->cur_p0l_clc_ctrl_00,1,1);		//[1]
					cur_clc_det_en = GET_BITS(pInfo->cur_p0l_clc_ctrl_00,2,1);		//[2]
				}
			}
			if(pInfo->pre_ipc_y_md[LX_PE_WIN_0]!=cur_ipc_y_md[LX_PE_WIN_0] || \
				pInfo->pre_ipc_c_md[LX_PE_WIN_0]!=cur_ipc_c_md[LX_PE_WIN_0])
			{
				PE_DNT_HW_H13_DBG_PRINT("[inf][ipc0]frz:%d,mute:%d,src:%d,dtv:%d\n",\
					ctrl0_info->is_src_frz,ctrl0_info->mute_on,disp0_info->src_type,disp0_info->dtv_type);
				PE_DNT_HW_H13_DBG_PRINT("[inf][ipc0]fmt:%d,scan:%d,out:%d,game:%d\n",\
					disp0_info->fmt_type,disp0_info->scan_type,disp0_info->out_type,pInfo->cur_game_mode);
				PE_DNT_HW_H13_DBG_PRINT("[set][ipc0] y:%d->%d, c:%d->%d\n",\
					pInfo->pre_ipc_y_md[LX_PE_WIN_0],cur_ipc_y_md[LX_PE_WIN_0],\
					pInfo->pre_ipc_c_md[LX_PE_WIN_0],cur_ipc_c_md[LX_PE_WIN_0]);
				PE_P0L_H13B0_RdFL(p0l_ipc_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_ipc_ctrl_00, cr_luma_mode,	cur_ipc_y_md[LX_PE_WIN_0]);
				PE_P0L_H13B0_Wr01(p0l_ipc_ctrl_00, cr_chroma_mode,	cur_ipc_c_md[LX_PE_WIN_0]);
				PE_P0L_H13B0_WrFL(p0l_ipc_ctrl_00);
				pInfo->pre_ipc_y_md[LX_PE_WIN_0]=cur_ipc_y_md[LX_PE_WIN_0];
				pInfo->pre_ipc_c_md[LX_PE_WIN_0]=cur_ipc_c_md[LX_PE_WIN_0];
			}
			if(pInfo->pre_ipc_y_md[LX_PE_WIN_1]!=cur_ipc_y_md[LX_PE_WIN_1] || \
				pInfo->pre_ipc_c_md[LX_PE_WIN_1]!=cur_ipc_c_md[LX_PE_WIN_1])
			{
				PE_DNT_HW_H13_DBG_PRINT("[inf][ipc1]frz:%d,mute:%d,src:%d,dtv:%d\n",\
					ctrl0_info->is_src_frz,ctrl0_info->mute_on,disp0_info->src_type,disp0_info->dtv_type);
				PE_DNT_HW_H13_DBG_PRINT("[inf][ipc1]fmt:%d,scan:%d,out:%d,game:%d\n",\
					disp0_info->fmt_type,disp0_info->scan_type,disp0_info->out_type,pInfo->cur_game_mode);
				PE_DNT_HW_H13_DBG_PRINT("[set][ipc1] y:%d->%d, c:%d->%d\n",\
					pInfo->pre_ipc_y_md[LX_PE_WIN_1],cur_ipc_y_md[LX_PE_WIN_1],\
					pInfo->pre_ipc_c_md[LX_PE_WIN_1],cur_ipc_c_md[LX_PE_WIN_1]);
				PE_P0R_H13B0_RdFL(p0r_ipc_ctrl_00);
				PE_P0R_H13B0_Wr01(p0r_ipc_ctrl_00, cr_luma_mode,	cur_ipc_y_md[LX_PE_WIN_1]);
				PE_P0R_H13B0_Wr01(p0r_ipc_ctrl_00, cr_chroma_mode,	cur_ipc_c_md[LX_PE_WIN_1]);
				PE_P0R_H13B0_WrFL(p0r_ipc_ctrl_00);
				pInfo->pre_ipc_y_md[LX_PE_WIN_1]=cur_ipc_y_md[LX_PE_WIN_1];
				pInfo->pre_ipc_c_md[LX_PE_WIN_1]=cur_ipc_c_md[LX_PE_WIN_1];
			}
			if(pInfo->pre_clc_flt_en!=cur_clc_flt_en || pInfo->pre_clc_det_en!=cur_clc_det_en)
			{
				PE_DNT_HW_H13_DBG_PRINT("[inf][clc]frz:%d,mute:%d,src:%d,dtv:%d\n",\
					ctrl0_info->is_src_frz,ctrl0_info->mute_on,disp0_info->src_type,disp0_info->dtv_type);
				PE_DNT_HW_H13_DBG_PRINT("[inf][clc]fmt:%d,scan:%d,out:%d,game:%d\n",\
					disp0_info->fmt_type,disp0_info->scan_type,disp0_info->out_type,pInfo->cur_game_mode);
				PE_DNT_HW_H13_DBG_PRINT("[set][clc] flt:%d->%d, det:%d->%d\n",\
					pInfo->pre_clc_flt_en,cur_clc_flt_en,pInfo->pre_clc_det_en,cur_clc_det_en);
				PE_P0L_H13B0_RdFL(p0l_clc_ctrl_00);
				PE_P0L_H13B0_Wr01(p0l_clc_ctrl_00, cl_filter_enable,		cur_clc_flt_en);
				PE_P0L_H13B0_Wr01(p0l_clc_ctrl_00, clc_detection_enable,	cur_clc_det_en);
				PE_P0L_H13B0_WrFL(p0l_clc_ctrl_00);
				pInfo->pre_clc_flt_en=cur_clc_flt_en;
				pInfo->pre_clc_det_en=cur_clc_det_en;
			}
			if(_g_dnt_hw_h13_trace)
			{
				if(count>PE_PRINT_COUNT_NUM)
				{
					PE_DNT_HW_H13_DBG_PRINT("[state][inf]frz:%d,mute:%d,src:%d,dtv:%d\n",\
						ctrl0_info->is_src_frz,ctrl0_info->mute_on,disp0_info->src_type,disp0_info->dtv_type);
					PE_DNT_HW_H13_DBG_PRINT("[state][inf]fmt:%d,scan:%d,out:%d,game:%d\n",\
						disp0_info->fmt_type,disp0_info->scan_type,disp0_info->out_type,pInfo->cur_game_mode);
					PE_DNT_HW_H13_DBG_PRINT("[state][ipc_yc][0]%d,%d,[1]%d,%d,[clc]flt:%d,det:%d\n",\
						cur_ipc_y_md[LX_PE_WIN_0],cur_ipc_c_md[LX_PE_WIN_0],cur_ipc_y_md[LX_PE_WIN_1],\
						cur_ipc_c_md[LX_PE_WIN_1],cur_clc_flt_en,cur_clc_det_en);
					count=0;
				}
				count++;
			}
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * get current dnt settings
 *
 * @param   *pstParams [in/out] PE_DNT_HW_H13_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_DNT_HW_H13_GetCurDntSettings(PE_DNT_HW_H13_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_DNT_HW_H13_SETTINGS_T *pInfo = &_g_pe_dnt_hw_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13BX)
		{
			memcpy(pstParams,pInfo,sizeof(PE_DNT_HW_H13_SETTINGS_T));
			PE_DNT_HW_H13_DBG_PRINT("get game:%d, cur ipc(l,r),clc:0x%08x,0x%08x,0x%08x\n"\
				"pre ipc_y,c:[%d,%d][%d,%d], clc_flt,det:%d,%d\n",pInfo->cur_game_mode,\
				pInfo->cur_p0l_ipc_ctrl_00,pInfo->cur_p0r_ipc_ctrl_00,pInfo->cur_p0l_clc_ctrl_00,\
				pInfo->pre_ipc_y_md[LX_PE_WIN_0],pInfo->pre_ipc_y_md[LX_PE_WIN_1],\
				pInfo->pre_ipc_c_md[LX_PE_WIN_0],pInfo->pre_ipc_c_md[LX_PE_WIN_1],\
				pInfo->pre_clc_flt_en,pInfo->pre_clc_det_en);
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	return ret;
}

/**
 * read dnt default setting
 *
 * @param   *pstParams [in/out] LX_PE_ETC_DBG_T
 * @return  OK if success, ERROR otherwise.
 * @see     
 * @author
 */
int PE_DNT_HW_H13_RdDefault(LX_PE_ETC_DBG_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i,param_size,table_size,ofst;
	UINT32 *pData=NULL;
	PE_REG_PARAM_T *table=NULL;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		PE_DNT_HW_H13_CHECK_CODE(pstParams->size!=300,break,"[%s,%d] size mismatch.\n",__F__,__L__);
		pData = pstParams->data;
		if(PE_KDRV_VER_H13BX)
		{
			ofst=0;
			if(pData[ofst]==0||pData[ofst]==1)	//0,1 : ipc
			{
				table_size = sizeof(ipc_l_pc_default_h13b0);
				table = (PE_REG_PARAM_T *)OS_Malloc(table_size);
				param_size = table_size/sizeof(PE_REG_PARAM_T);
				for(i=0;i<param_size;i++)
				{
					table[i].addr = ipc_l_pc_default_h13b0[i].addr;
					if(pData[ofst]==1)	table[i].addr += PE_PE0_REG_H13_LRDIFF;
				}
			}
			else if(pData[ofst]==2)	//2 : clc
			{
				table_size = sizeof(clc_l_pc_default_h13b0);
				table = (PE_REG_PARAM_T *)OS_Malloc(table_size);
				param_size = table_size/sizeof(PE_REG_PARAM_T);
				for(i=0;i<param_size;i++)
				{
					table[i].addr = clc_l_pc_default_h13b0[i].addr;
				}
			}
			else	//3,4 : vflt y
			{
				table_size = sizeof(vflt_y_l_pc_default_h13b0);
				table = (PE_REG_PARAM_T *)OS_Malloc(table_size);
				param_size = table_size/sizeof(PE_REG_PARAM_T);
				for(i=0;i<param_size;i++)
				{
					table[i].addr = vflt_y_l_pc_default_h13b0[i].addr;
					if(pData[ofst]==4)	table[i].addr += PE_PE0_REG_H13_LRDIFF;
				}
			}
			ret = PE_REG_GetTable(table,0,table_size);
			PE_DNT_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
			ofst += 1;
			pData[ofst] = param_size;
			ofst += 1;
			for(i=0;i<param_size;i++)
			{
				pData[ofst+i*2]=table[i].addr;
				pData[ofst+i*2+1]=table[i].data;
			}
			ofst += 1;
		}
		else
		{
			PE_DNT_HW_H13_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	if(table){OS_Free(table);}\
	return ret;
}

