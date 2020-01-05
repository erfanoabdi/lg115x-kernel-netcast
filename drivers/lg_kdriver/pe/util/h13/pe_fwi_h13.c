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


/** @file pe_fwi_h13.c
 *
 *  driver for firmware interface functions. ( used only within kdriver )
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
#include "pe_etc.h"
#include "pe_etc_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_H13_ERROR	printk

#define PE_FWI_H13_DBG_PRINT(fmt,args...)	\
	if(_g_fwi_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_FWI_H13_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_FWI_H13_ERROR(fmt,##args);_action;}}

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
static int PE_FWI_H13_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_fwi_h13_trace=0x0;	//default should be off.
static PE_FWI_H13_SETTINGS_T _g_pe_fwi_h13_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set pq f/w settings
 *
 * @param   header [in] PE_FWI_PQ_TABLE_HEAD_T
 * @param   *table [in] UINT8
 * @param   tbl_size [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_FWI_H13_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize)
{
	int ret = RET_OK;
	UINT32 offset;
	UINT32 length;
	UINT32 dataSize;
	UINT8 *pData = NULL;
	DE_IPC_CMD_T ipcCmd = PQL_IPC_SET_TABLE;
	do{
		offset = header.offset;
		length = header.length;
		PE_FWI_H13_CHECK_CODE(!length,break,"[%s,%d] length is zero.\n",__F__,__L__);
		PE_FWI_H13_CHECK_CODE(!pTable,break,"[%s,%d] pTable is null.\n",__F__,__L__);
		PE_FWI_H13_CHECK_CODE(!tblSize,break,"[%s,%d] tblSize is zero.\n",__F__,__L__);
		PE_FWI_H13_CHECK_CODE(((offset+length)>tblSize),break,\
			"[%s,%d] offset(%d) and length(%d) is greater than tblSize(%d).\n",\
			__F__,__L__,offset,length,tblSize);
		PE_FWI_H13_DBG_PRINT(" wid:%d,ofs:%d,len:%d, tbl_size:%d\n",\
			header.win_id,header.offset,header.length,tblSize);
		dataSize = sizeof(header)+length;
		pData = OS_KMalloc(dataSize);
		PE_FWI_H13_CHECK_CODE(!pData,break,"[%s,%d] pData is null.\n",__F__,__L__);
		memcpy(pData,&header,sizeof(header));
		memcpy(&pData[sizeof(header)],&pTable[offset],length);
		ret = PE_FWI_SETDATA(ipcCmd, pData, dataSize);
		PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
	}while(0);
	if(pData)	OS_Free(pData);
	return ret;
}
/**
 * set debug print enable
 *
 * @param   on_off [in] UINT32
 * @return  void
 * @see
 * @author
 */
void PE_FWI_H13_SetDbgPrint(UINT32 on_off)
{
	_g_fwi_h13_trace = on_off? 1:0;
	return;
}
/**
 * get debug print enable
 *
 * @param   void
 * @return  on,off
 * @see
 * @author
 */
UINT32 PE_FWI_H13_GetDbgPrint(void)
{
	return _g_fwi_h13_trace;
}

/**
 * init fwi module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_H13)
		{
			PE_FWI_H13_DBG_PRINT("init global values.\n");
			memset(&_g_pe_fwi_h13_info,0xff,sizeof(PE_FWI_H13_SETTINGS_T));
			_g_pe_fwi_h13_info.fw_ctrl.enable=0x0;
			memset(&(_g_pe_fwi_h13_info.cen_ctrl[0]),0x0,sizeof(PE_FWI_H13_CEN_CTRL)*LX_PE_CMG_REGION_NUM);
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * set f/w control
 *	- it's for shp fw only
 *
 * @param   *pstParams [in] PE_FWI_H13_FW_CTRL
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetFwCtrl(PE_FWI_H13_FW_CTRL *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(pInfo->fw_ctrl.enable!=pstParams->enable)
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_FW_CTRL);
				header.length = sizeof(PE_FWI_H13_FW_CTRL);
				table.fw_ctrl.enable = (pstParams->enable)? 1:0;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, fw_ctrl.enable:%d->%d\n",header.win_id,\
					header.offset,header.length,tbl_size,pInfo->fw_ctrl.enable,table.fw_ctrl.enable);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->fw_ctrl.enable = (pstParams->enable)? 1:0;
			}
			else
			{
				/*too many print*/
				/*PE_FWI_H13_DBG_PRINT("fw_ctrl.enable:%d->%d,same..\n",pInfo->fw_ctrl.enable,pstParams->enable);*/	
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set fw ctrl enable(periodic)
 *
 * @param   *pCfg [in] PE_TSK_H13_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetFwCtrlEnable(PE_TSK_H13_CFG_T *pCfg)
{
	int ret = RET_OK;
	PE_FWI_H13_FW_CTRL pre_fw_ctrl,cur_fw_ctrl;
	LX_PE_INF_DISPLAY_T *disp0_info = &pCfg->inf.disp_info[LX_PE_WIN_0];
	PE_INF_H13_CTRL_T *ctrl0_info = &pCfg->inf.ctrl_info[LX_PE_WIN_0];
	PE_INF_H13_CTRL_T *ctrl1_info = &pCfg->inf.ctrl_info[LX_PE_WIN_1];
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pCfg);
		if(PE_KDRV_VER_H13BX)
		{
			pre_fw_ctrl.enable = pInfo->fw_ctrl.enable;
			/* check pip same h,v case(=split window), because of avoiding peaking transition artifact */
			if(disp0_info->out_type==LX_PE_OUT_PIP && (ctrl0_info->hv_same || ctrl1_info->hv_same))
			{
				cur_fw_ctrl.enable = 0;
			}
			else
			{
				cur_fw_ctrl.enable = 1;
			}
			ret = PE_FWI_H13_SetFwCtrl(&cur_fw_ctrl);
			PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwCtrl() error.\n",__F__,__L__);
			/* set shp again when fw.en on <-> off */
			if(pre_fw_ctrl.enable!=cur_fw_ctrl.enable && !cur_fw_ctrl.enable)
			{
				PE_FWI_H13_HOR_CTRL shp_h_ctrl;
				PE_FWI_H13_MISC_CTRL shp_m_ctrl;
				PE_FWI_H13_EDGE_GAIN shp_e_ctrl;
				PE_FWI_H13_TEXTURE_GAIN shp_t_ctrl;
				shp_h_ctrl.e_gain_th1 = pInfo->shp_h_ctrl.e_gain_th1;
				shp_h_ctrl.e_gain_th2 = pInfo->shp_h_ctrl.e_gain_th2;
				shp_m_ctrl.gt_th0 = pInfo->shp_m_ctrl.gt_th0;
				shp_m_ctrl.gt_th1 = pInfo->shp_m_ctrl.gt_th1;
				shp_m_ctrl.gt_th0a = pInfo->shp_m_ctrl.gt_th0a;
				shp_m_ctrl.gt_th0b = pInfo->shp_m_ctrl.gt_th0b;
				shp_e_ctrl.co09_gain_b = pInfo->shp_e_ctrl.co09_gain_b;
				shp_e_ctrl.co09_gain_w = pInfo->shp_e_ctrl.co09_gain_w;
				shp_e_ctrl.dp01_gain_b = pInfo->shp_e_ctrl.dp01_gain_b;
				shp_e_ctrl.dp01_gain_w = pInfo->shp_e_ctrl.dp01_gain_w;
				shp_t_ctrl.co09_gain_b = pInfo->shp_t_ctrl.co09_gain_b;
				shp_t_ctrl.co09_gain_w = pInfo->shp_t_ctrl.co09_gain_w;
				shp_t_ctrl.dp01_gain_b = pInfo->shp_t_ctrl.dp01_gain_b;
				shp_t_ctrl.dp01_gain_w = pInfo->shp_t_ctrl.dp01_gain_w;
				PE_FWI_H13_DBG_PRINT("fw_en:%d->%d, set prev shp settings again.\n",\
					pre_fw_ctrl.enable,cur_fw_ctrl.enable);
				ret = PE_FWI_H13_SetShpHorCtrl(&shp_h_ctrl);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetShpHorCtrl() error.\n",__F__,__L__);
				ret = PE_FWI_H13_SetShpMiscCtrl(&shp_m_ctrl);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetShpMiscCtrl() error.\n",__F__,__L__);
				ret = PE_FWI_H13_SetEdgeGainCtrl(&shp_e_ctrl);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetEdgeGainCtrl() error.\n",__F__,__L__);
				ret = PE_FWI_H13_SetTextureGainCtrl(&shp_t_ctrl);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetTextureGainCtrl() error.\n",__F__,__L__);
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sharpness horizontal control to f/w
 *
 * @param   *pstParams [in] PE_FWI_H13_HOR_CTRL
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetShpHorCtrl(PE_FWI_H13_HOR_CTRL *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(!pInfo->fw_ctrl.enable)
			{
				#ifdef PE_FWI_H13_USE_SHP_CTRL_WHEN_PQFW_OFF
				PE_FWI_H13_DBG_PRINT("fw_en:off, e_g12:%d,%d\n",pstParams->e_gain_th1,pstParams->e_gain_th2);
				PE_P1L_H13B0_RdFL(pe1_derh_ctrl_0b);
				PE_P1L_H13B0_Wr01(pe1_derh_ctrl_0b, e_gain_th1,	pstParams->e_gain_th1);
				PE_P1L_H13B0_Wr01(pe1_derh_ctrl_0b, e_gain_th2,	pstParams->e_gain_th2);
				PE_P1L_H13B0_WrFL(pe1_derh_ctrl_0b);
				#else
				PE_FWI_H13_DBG_PRINT("fw_ctrl.enable:%d, just return\n",pInfo->fw_ctrl.enable);
				ret = RET_OK;
				break;
				#endif
			}
			if((pInfo->shp_h_ctrl.e_gain_th1!=pstParams->e_gain_th1) || \
				(pInfo->shp_h_ctrl.e_gain_th2!=pstParams->e_gain_th2))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_HOR_CTRL);
				header.length = sizeof(PE_FWI_H13_HOR_CTRL);
				table.shp_h_ctrl.e_gain_th1 = pstParams->e_gain_th1;
				table.shp_h_ctrl.e_gain_th2 = pstParams->e_gain_th2;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, e_g12:%d,%d\n",\
					header.win_id,header.offset,header.length,tbl_size,\
					table.shp_h_ctrl.e_gain_th1,table.shp_h_ctrl.e_gain_th2);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->shp_h_ctrl.e_gain_th1 = table.shp_h_ctrl.e_gain_th1;
				pInfo->shp_h_ctrl.e_gain_th2 = table.shp_h_ctrl.e_gain_th2;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("e_g12:pre[%d,%d]->cur[%d,%d],same..\n",\
					pInfo->shp_h_ctrl.e_gain_th1,pInfo->shp_h_ctrl.e_gain_th2,\
					pstParams->e_gain_th1,pstParams->e_gain_th2);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sharpness misc control to f/w
 *
 * @param   *pstParams [in] PE_FWI_H13_MISC_CTRL
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetShpMiscCtrl(PE_FWI_H13_MISC_CTRL *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(!pInfo->fw_ctrl.enable)
			{
				#ifdef PE_FWI_H13_USE_SHP_CTRL_WHEN_PQFW_OFF
				PE_FWI_H13_DBG_PRINT("fw_en:off, gt01ab:%d,%d,%d,%d\n",pstParams->gt_th0,\
					pstParams->gt_th1,pstParams->gt_th0a,pstParams->gt_th0b);
				PE_P1L_H13B0_RdFL(pe1_coring_ctrl_05);
				PE_P1L_H13B0_RdFL(pe1_coring_ctrl_06);
				PE_P1L_H13B0_Wr01(pe1_coring_ctrl_05,	gt_th1,		pstParams->gt_th1);
				PE_P1L_H13B0_Wr01(pe1_coring_ctrl_05,	gt_th0,		pstParams->gt_th0);
				PE_P1L_H13B0_Wr01(pe1_coring_ctrl_06,	gt_th0a,	pstParams->gt_th0a);
				PE_P1L_H13B0_Wr01(pe1_coring_ctrl_06,	gt_th0b,	pstParams->gt_th0b);
				PE_P1L_H13B0_WrFL(pe1_coring_ctrl_05);
				PE_P1L_H13B0_WrFL(pe1_coring_ctrl_06);
				#else
				PE_FWI_H13_DBG_PRINT("fw_ctrl.enable:%d, just return\n",pInfo->fw_ctrl.enable);
				ret = RET_OK;
				break;
				#endif
			}
			if((pInfo->shp_m_ctrl.gt_th0!=pstParams->gt_th0) || \
				(pInfo->shp_m_ctrl.gt_th1!=pstParams->gt_th1) || \
				(pInfo->shp_m_ctrl.gt_th0a!=pstParams->gt_th0a) || \
				(pInfo->shp_m_ctrl.gt_th0b!=pstParams->gt_th0b))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_MISC_CTRL);
				header.length = sizeof(PE_FWI_H13_MISC_CTRL);
				table.shp_m_ctrl.gt_th0 = pstParams->gt_th0;
				table.shp_m_ctrl.gt_th1 = pstParams->gt_th1;
				table.shp_m_ctrl.gt_th0a = pstParams->gt_th0a;
				table.shp_m_ctrl.gt_th0b = pstParams->gt_th0b;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, gt01ab:%d,%d,%d,%d\n",\
					header.win_id,header.offset,header.length,tbl_size,\
					table.shp_m_ctrl.gt_th0,table.shp_m_ctrl.gt_th1,\
					table.shp_m_ctrl.gt_th0a,table.shp_m_ctrl.gt_th0b);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->shp_m_ctrl.gt_th0 = table.shp_m_ctrl.gt_th0;
				pInfo->shp_m_ctrl.gt_th1 = table.shp_m_ctrl.gt_th1;
				pInfo->shp_m_ctrl.gt_th0a = table.shp_m_ctrl.gt_th0a;
				pInfo->shp_m_ctrl.gt_th0b = table.shp_m_ctrl.gt_th0b;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("gt01ab:pre[%d,%d,%d,%d]->cur[%d,%d,%d,%d],same..\n",\
					pInfo->shp_m_ctrl.gt_th0,pInfo->shp_m_ctrl.gt_th0,\
					pInfo->shp_m_ctrl.gt_th0a,pInfo->shp_m_ctrl.gt_th0b,\
					pstParams->gt_th0,pstParams->gt_th1,pstParams->gt_th0a,pstParams->gt_th0b);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set edge gain control to f/w
 *
 * @param   *pstParams [in] PE_FWI_H13_EDGE_GAIN
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetEdgeGainCtrl(PE_FWI_H13_EDGE_GAIN *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	#ifdef PE_FWI_H13_USE_SHP_CTRL_WHEN_PQFW_OFF
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	#endif
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(!pInfo->fw_ctrl.enable)
			{
				#ifdef PE_FWI_H13_USE_SHP_CTRL_WHEN_PQFW_OFF
				UINT8 cur_gain[4];
				PE_INF_H13_SETTINGS_T inf_set;
				ret = PE_INF_H13_GetCurInfSettings(&inf_set);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
				cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
				CHECK_KNULL(cur0_inf);
				PE_FWI_H13_DBG_PRINT("fw_en:off,src:%d,eg_b,w:%d,%d,%d,%d\n",cur0_inf->src_type,\
					pstParams->co09_gain_b,pstParams->co09_gain_w,pstParams->dp01_gain_b,pstParams->dp01_gain_w);
				/* set 50% edge,texture gain to avoid strong peaking in sub dtv with main atv on split window mode  */
				if(cur0_inf->src_type==LX_PE_SRC_ATV)
				{
					cur_gain[0] = pstParams->co09_gain_b>>1;
					cur_gain[1] = pstParams->co09_gain_w>>1;
					cur_gain[2] = pstParams->dp01_gain_b>>1;
					cur_gain[3] = pstParams->dp01_gain_w>>1;
				}
				else
				{
					cur_gain[0] = pstParams->co09_gain_b;
					cur_gain[1] = pstParams->co09_gain_w;
					cur_gain[2] = pstParams->dp01_gain_b;
					cur_gain[3] = pstParams->dp01_gain_w;
				}
				PE_FWI_H13_DBG_PRINT("cur eg_b,w:%d,%d,%d,%d\n",cur_gain[0],cur_gain[1],cur_gain[2],cur_gain[3]);
				PE_P1L_H13_RdFL(pe1_coring_ctrl_09);
				PE_P1L_H13_RdFL(pe1_dp_ctrl_01);
				PE_P1L_H13_Wr01(pe1_coring_ctrl_09,	edge_gain_b,	cur_gain[0]);
				PE_P1L_H13_Wr01(pe1_coring_ctrl_09,	edge_gain_w,	cur_gain[1]);
				PE_P1L_H13_Wr01(pe1_dp_ctrl_01,		edge_gain_b,	cur_gain[2]);
				PE_P1L_H13_Wr01(pe1_dp_ctrl_01,		edge_gain_w,	cur_gain[3]);
				PE_P1L_H13_WrFL(pe1_coring_ctrl_09);
				PE_P1L_H13_WrFL(pe1_dp_ctrl_01);
				#else
				PE_FWI_H13_DBG_PRINT("fw_ctrl.enable:%d, just return\n",pInfo->fw_ctrl.enable);
				ret = RET_OK;
				break;
				#endif
			}
			if((pInfo->shp_e_ctrl.co09_gain_b!=pstParams->co09_gain_b) || \
				(pInfo->shp_e_ctrl.co09_gain_w!=pstParams->co09_gain_w) || \
				(pInfo->shp_e_ctrl.dp01_gain_b!=pstParams->dp01_gain_b) || \
				(pInfo->shp_e_ctrl.dp01_gain_w!=pstParams->dp01_gain_w))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_EDGE_GAIN);
				header.length = sizeof(PE_FWI_H13_EDGE_GAIN);
				table.shp_e_ctrl.co09_gain_b = pstParams->co09_gain_b;
				table.shp_e_ctrl.co09_gain_w = pstParams->co09_gain_w;
				table.shp_e_ctrl.dp01_gain_b = pstParams->dp01_gain_b;
				table.shp_e_ctrl.dp01_gain_w = pstParams->dp01_gain_w;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, eg_b,w:%d,%d,%d,%d\n",\
					header.win_id,header.offset,header.length,tbl_size,\
					table.shp_e_ctrl.co09_gain_b,table.shp_e_ctrl.co09_gain_w,\
					table.shp_e_ctrl.dp01_gain_b,table.shp_e_ctrl.dp01_gain_w);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->shp_e_ctrl.co09_gain_b = table.shp_e_ctrl.co09_gain_b;
				pInfo->shp_e_ctrl.co09_gain_w = table.shp_e_ctrl.co09_gain_w;
				pInfo->shp_e_ctrl.dp01_gain_b = table.shp_e_ctrl.dp01_gain_b;
				pInfo->shp_e_ctrl.dp01_gain_w = table.shp_e_ctrl.dp01_gain_w;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("eg_b,w:pre[%d,%d,%d,%d]->cur[%d,%d,%d,%d],same..\n",\
					pInfo->shp_e_ctrl.co09_gain_b,pInfo->shp_e_ctrl.co09_gain_w,\
					pInfo->shp_e_ctrl.dp01_gain_b,pInfo->shp_e_ctrl.dp01_gain_w,\
					pstParams->co09_gain_b,pstParams->co09_gain_w,pstParams->dp01_gain_b,pstParams->dp01_gain_w);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set texture gain control to f/w
 *
 * @param   *pstParams [in] PE_FWI_H13_TEXTURE_GAIN
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetTextureGainCtrl(PE_FWI_H13_TEXTURE_GAIN *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	#ifdef PE_FWI_H13_USE_SHP_CTRL_WHEN_PQFW_OFF
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	#endif
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(!pInfo->fw_ctrl.enable)
			{
				#ifdef PE_FWI_H13_USE_SHP_CTRL_WHEN_PQFW_OFF
				UINT8 cur_gain[4];
				PE_INF_H13_SETTINGS_T inf_set;
				ret = PE_INF_H13_GetCurInfSettings(&inf_set);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_INF_H13_GetCurInfSettings() error.\n",__F__,__L__);
				cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
				CHECK_KNULL(cur0_inf);
				PE_FWI_H13_DBG_PRINT("fw_en:off,src:%d,tg_b,w:%d,%d,%d,%d\n",cur0_inf->src_type,\
					pstParams->co09_gain_b,pstParams->co09_gain_w,pstParams->dp01_gain_b,pstParams->dp01_gain_w);
				/* set 50% edge,texture gain to avoid strong peaking in sub dtv with main atv on split window mode  */
				if(cur0_inf->src_type==LX_PE_SRC_ATV)
				{
					cur_gain[0] = pstParams->co09_gain_b>>1;
					cur_gain[1] = pstParams->co09_gain_w>>1;
					cur_gain[2] = pstParams->dp01_gain_b>>1;
					cur_gain[3] = pstParams->dp01_gain_w>>1;
				}
				else
				{
					cur_gain[0] = pstParams->co09_gain_b;
					cur_gain[1] = pstParams->co09_gain_w;
					cur_gain[2] = pstParams->dp01_gain_b;
					cur_gain[3] = pstParams->dp01_gain_w;
				}
				PE_FWI_H13_DBG_PRINT("cur tg_b,w:%d,%d,%d,%d\n",cur_gain[0],cur_gain[1],cur_gain[2],cur_gain[3]);
				PE_P1L_H13_RdFL(pe1_coring_ctrl_09);
				PE_P1L_H13_RdFL(pe1_dp_ctrl_01);
				PE_P1L_H13_Wr01(pe1_coring_ctrl_09,	texture_gain_b,	cur_gain[0]);
				PE_P1L_H13_Wr01(pe1_coring_ctrl_09,	texture_gain_w,	cur_gain[1]);
				PE_P1L_H13_Wr01(pe1_dp_ctrl_01,		texture_gain_b,	cur_gain[2]);
				PE_P1L_H13_Wr01(pe1_dp_ctrl_01,		texture_gain_w,	cur_gain[3]);
				PE_P1L_H13_WrFL(pe1_coring_ctrl_09);
				PE_P1L_H13_WrFL(pe1_dp_ctrl_01);
				#else
				PE_FWI_H13_DBG_PRINT("fw_ctrl.enable:%d, just return\n",pInfo->fw_ctrl.enable);
				ret = RET_OK;
				break;
				#endif
			}
			if((pInfo->shp_t_ctrl.co09_gain_b!=pstParams->co09_gain_b) || \
				(pInfo->shp_t_ctrl.co09_gain_w!=pstParams->co09_gain_w) || \
				(pInfo->shp_t_ctrl.dp01_gain_b!=pstParams->dp01_gain_b) || \
				(pInfo->shp_t_ctrl.dp01_gain_w!=pstParams->dp01_gain_w))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_TEXTURE_GAIN);
				header.length = sizeof(PE_FWI_H13_TEXTURE_GAIN);
				table.shp_t_ctrl.co09_gain_b = pstParams->co09_gain_b;
				table.shp_t_ctrl.co09_gain_w = pstParams->co09_gain_w;
				table.shp_t_ctrl.dp01_gain_b = pstParams->dp01_gain_b;
				table.shp_t_ctrl.dp01_gain_w = pstParams->dp01_gain_w;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, tg_b,w:%d,%d,%d,%d\n",\
					header.win_id,header.offset,header.length,tbl_size,\
					table.shp_t_ctrl.co09_gain_b,table.shp_t_ctrl.co09_gain_w,\
					table.shp_t_ctrl.dp01_gain_b,table.shp_t_ctrl.dp01_gain_w);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->shp_t_ctrl.co09_gain_b = table.shp_t_ctrl.co09_gain_b;
				pInfo->shp_t_ctrl.co09_gain_w = table.shp_t_ctrl.co09_gain_w;
				pInfo->shp_t_ctrl.dp01_gain_b = table.shp_t_ctrl.dp01_gain_b;
				pInfo->shp_t_ctrl.dp01_gain_w = table.shp_t_ctrl.dp01_gain_w;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("tg_b,w:pre[%d,%d,%d,%d]->cur[%d,%d,%d,%d],same..\n",\
					pInfo->shp_t_ctrl.co09_gain_b,pInfo->shp_t_ctrl.co09_gain_w,\
					pInfo->shp_t_ctrl.dp01_gain_b,pInfo->shp_t_ctrl.dp01_gain_w,\
					pstParams->co09_gain_b,pstParams->co09_gain_w,pstParams->dp01_gain_b,pstParams->dp01_gain_w);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set tnr ctrl to f/w
 *
 * @param   win_id [in] UINT32
 * @param   *pstParams [in] PE_FWI_H13_TNR_CTRL
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetTnrCtrl(UINT32 win_id, PE_FWI_H13_TNR_CTRL *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID cur_win_id;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			/* don't care ctrl enable on/off */
			if(win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_H13_DBG_PRINT("win_id:%d, just return\n",win_id);
				ret = RET_OK;
				break;
			}
			cur_win_id = PE_GET_CHECKED_WINID(win_id);
			if(((win_id==LX_PE_WIN_ALL)&& \
				((pInfo->tnr_ctrl[LX_PE_WIN_0].tnr_en!=pstParams->tnr_en) || \
				(pInfo->tnr_ctrl[LX_PE_WIN_0].m_fir_en!=pstParams->m_fir_en) || \
				(pInfo->tnr_ctrl[LX_PE_WIN_1].tnr_en!=pstParams->tnr_en) || \
				(pInfo->tnr_ctrl[LX_PE_WIN_1].m_fir_en!=pstParams->m_fir_en))) || \
				((pInfo->tnr_ctrl[cur_win_id].tnr_en!=pstParams->tnr_en) || \
				(pInfo->tnr_ctrl[cur_win_id].m_fir_en!=pstParams->m_fir_en)))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = win_id;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_TNR_CTRL);
				header.length = sizeof(PE_FWI_H13_TNR_CTRL);
				table.tnr_ctrl.tnr_en = (pstParams->tnr_en)? 1:0;
				table.tnr_ctrl.m_fir_en = (pstParams->m_fir_en)? 1:0;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, core,m_en[%d]:%d,%d->%d,%d\n",\
					header.win_id,header.offset,header.length,tbl_size,cur_win_id,\
					pInfo->tnr_ctrl[cur_win_id].tnr_en,pInfo->tnr_ctrl[cur_win_id].m_fir_en,\
					table.tnr_ctrl.tnr_en,table.tnr_ctrl.m_fir_en);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				if(PE_CHECK_WIN0(win_id))
				{
					pInfo->tnr_ctrl[LX_PE_WIN_0].tnr_en = table.tnr_ctrl.tnr_en;
					pInfo->tnr_ctrl[LX_PE_WIN_0].m_fir_en = table.tnr_ctrl.m_fir_en;
				}
				if(PE_CHECK_WIN1(win_id))
				{
					pInfo->tnr_ctrl[LX_PE_WIN_1].tnr_en = table.tnr_ctrl.tnr_en;
					pInfo->tnr_ctrl[LX_PE_WIN_1].m_fir_en = table.tnr_ctrl.m_fir_en;
				}
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("wid:%d,core,m_en[%d]:pre[%d,%d][%d,%d]->cur[%d,%d],same..\n",\
					win_id,cur_win_id,\
					pInfo->tnr_ctrl[LX_PE_WIN_0].tnr_en,pInfo->tnr_ctrl[LX_PE_WIN_0].m_fir_en,\
					pInfo->tnr_ctrl[LX_PE_WIN_1].tnr_en,pInfo->tnr_ctrl[LX_PE_WIN_1].m_fir_en,\
					pstParams->tnr_en,pstParams->m_fir_en);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set src info to f/w
 *
 * @param   *pstParams [in] PE_FWI_H13_SRC_INFO
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetSrcInfo(PE_FWI_H13_SRC_INFO *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			#if 0	// independ on fw enable
			if(!pInfo->fw_ctrl.enable)
			{
				PE_FWI_H13_DBG_PRINT("fw_ctrl.enable:%d, just return\n",pInfo->fw_ctrl.enable);
				ret = RET_OK;
				break;
			}
			#endif
			if((pInfo->src_info.dtv_mode!=pstParams->dtv_mode) || \
				(pInfo->src_info.hdd_mode!=pstParams->hdd_mode))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_SRC_INFO);
				header.length = sizeof(PE_FWI_H13_SRC_INFO);
				table.src_info.dtv_mode = pstParams->dtv_mode;
				table.src_info.hdd_mode = pstParams->hdd_mode;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, src_info.dtv:%d->%d,hdd:%d->%d\n",\
					header.win_id,header.offset,header.length,tbl_size,pInfo->src_info.dtv_mode,\
					table.src_info.dtv_mode,pInfo->src_info.hdd_mode,table.src_info.hdd_mode);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->src_info.dtv_mode=pstParams->dtv_mode;
				pInfo->src_info.hdd_mode=pstParams->hdd_mode;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("src_info.dtv:%d->%d,hdd:%d->%d,same..\n",pInfo->src_info.dtv_mode,\
					pstParams->dtv_mode,pInfo->src_info.hdd_mode,pstParams->hdd_mode);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set cen region ctrl
 *
 * @param   *pstParams [in] PE_FWI_H13_CEN_CTRL
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_SetCenCtrl(PE_FWI_H13_CEN_CTRL *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_FWI_H13_USE_CEN_RGN_CTRL
	#ifdef PE_FWI_H13_USE_CEN_RGN_CTRL_BY_BE_FW
	UINT32 tblsize0,tblsize1;
	PE_FWI_H13_CEN_CTRL0_T fw_ctrl0;
	PE_FWI_H13_CEN_CTRL1_T fw_ctrl1;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(pstParams->rgn_num>LX_PE_CMG_REGION_MAX)
			{
				PE_FWI_H13_DBG_PRINT("rgn_num(%d) is over, just return\n",pstParams->rgn_num);
				ret = RET_OK;
				break;
			}
			if((pInfo->cen_ctrl[pstParams->rgn_num].rgn_num!=pstParams->rgn_num) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_h!=pstParams->delta_h) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_s!=pstParams->delta_s) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_v!=pstParams->delta_v) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_g!=pstParams->delta_g) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_b!=pstParams->delta_b) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_r!=pstParams->delta_r) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].ma_gain!=pstParams->ma_gain))
			{
				fw_ctrl0.u8regnNum = pstParams->rgn_num;
				fw_ctrl0.u8deltHue = pstParams->delta_h;
				fw_ctrl0.u8deltSat = pstParams->delta_s;
				fw_ctrl0.u8deltVal = pstParams->delta_v;
				fw_ctrl1.u8deltGrn = pstParams->delta_g;
				fw_ctrl1.u8deltBlu = pstParams->delta_b;
				fw_ctrl1.u8deltRed = pstParams->delta_r;
				fw_ctrl1.u8gainMst = pstParams->ma_gain;
				tblsize0 = sizeof(PE_FWI_H13_CEN_CTRL0_T);
				tblsize1 = sizeof(PE_FWI_H13_CEN_CTRL1_T);
				PE_FWI_H13_DBG_PRINT("\n tbl_size0,1:%d,%d, num:%d->%d\n"\
					"del:%d,%d,%d,%d,%d,%d->%d,%d,%d,%d,%d,%d, m:%d->%d\n",tblsize0,tblsize1,\
					pInfo->cen_ctrl[pstParams->rgn_num].rgn_num,fw_ctrl0.u8regnNum,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_h,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_s,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_v,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_g,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_b,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_r,\
					(SINT8)fw_ctrl0.u8deltHue,(SINT8)fw_ctrl0.u8deltSat,(SINT8)fw_ctrl0.u8deltVal,\
					(SINT8)fw_ctrl1.u8deltGrn,(SINT8)fw_ctrl1.u8deltBlu,(SINT8)fw_ctrl1.u8deltRed,\
					pInfo->cen_ctrl[pstParams->rgn_num].ma_gain,fw_ctrl1.u8gainMst);
				ret = PE_FWI_BE_SETDATA(BE_PE_SET_CEN_GAIN0, (&fw_ctrl0), tblsize0);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d][GAIN0] PE_FWI_BE_SETDATA() error.\n",__F__,__L__);
				ret = PE_FWI_BE_SETDATA(BE_PE_SET_CEN_GAIN1, (&fw_ctrl1), tblsize1);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d][GAIN1] PE_FWI_BE_SETDATA() error.\n",__F__,__L__);
				pInfo->cen_ctrl[pstParams->rgn_num].rgn_num=pstParams->rgn_num;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_h=pstParams->delta_h;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_s=pstParams->delta_s;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_v=pstParams->delta_v;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_g=pstParams->delta_g;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_b=pstParams->delta_b;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_r=pstParams->delta_r;
				pInfo->cen_ctrl[pstParams->rgn_num].ma_gain=pstParams->ma_gain;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("cen num:%d->%d\n"\
					"del:%d,%d,%d,%d,%d,%d->%d,%d,%d,%d,%d,%d, m:%d->%d,same..\n",\
					pInfo->cen_ctrl[pstParams->rgn_num].rgn_num,pstParams->rgn_num,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_h,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_s,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_v,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_g,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_b,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_r,\
					(SINT8)pstParams->delta_h,(SINT8)pstParams->delta_s,\
					(SINT8)pstParams->delta_v,(SINT8)pstParams->delta_g,\
					(SINT8)pstParams->delta_b,(SINT8)pstParams->delta_r,\
					pInfo->cen_ctrl[pstParams->rgn_num].ma_gain,pstParams->ma_gain);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#else
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_H13_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_H13)
		{
			if(pstParams->rgn_num>LX_PE_CMG_REGION_MAX)
			{
				PE_FWI_H13_DBG_PRINT("rgn_num(%d) is over, just return\n",pstParams->rgn_num);
				ret = RET_OK;
				break;
			}
			if((pInfo->cen_ctrl[pstParams->rgn_num].rgn_num!=pstParams->rgn_num) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_h!=pstParams->delta_h) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_s!=pstParams->delta_s) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_v!=pstParams->delta_v) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_g!=pstParams->delta_g) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_b!=pstParams->delta_b) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].delta_r!=pstParams->delta_r) || \
				(pInfo->cen_ctrl[pstParams->rgn_num].ma_gain!=pstParams->ma_gain))
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_H13_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_H13_CEN_CTRL);
				header.length = sizeof(PE_FWI_H13_CEN_CTRL);
				table.cen_ctrl.rgn_num = pstParams->rgn_num;
				table.cen_ctrl.delta_h = pstParams->delta_h;
				table.cen_ctrl.delta_s = pstParams->delta_s;
				table.cen_ctrl.delta_v = pstParams->delta_v;
				table.cen_ctrl.delta_g = pstParams->delta_g;
				table.cen_ctrl.delta_b = pstParams->delta_b;
				table.cen_ctrl.delta_r = pstParams->delta_r;
				table.cen_ctrl.ma_gain = pstParams->ma_gain;
				PE_FWI_H13_DBG_PRINT("\n wid:%d,ofs:%d,len:%d,tbl_size:%d, num:%d->%d\n"\
					"del:%d,%d,%d,%d,%d,%d->%d,%d,%d,%d,%d,%d, m:%d->%d\n",\
					header.win_id,header.offset,header.length,tbl_size,\
					pInfo->cen_ctrl[pstParams->rgn_num].rgn_num,table.cen_ctrl.rgn_num,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_h,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_s,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_v,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_g,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_b,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_r,\
					(SINT8)table.cen_ctrl.delta_h,(SINT8)table.cen_ctrl.delta_s,\
					(SINT8)table.cen_ctrl.delta_v,(SINT8)table.cen_ctrl.delta_g,\
					(SINT8)table.cen_ctrl.delta_b,(SINT8)table.cen_ctrl.delta_r,\
					pInfo->cen_ctrl[pstParams->rgn_num].ma_gain,table.cen_ctrl.ma_gain);
				ret = PE_FWI_H13_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetFwSettings() error.\n",__F__,__L__);
				pInfo->cen_ctrl[pstParams->rgn_num].rgn_num=pstParams->rgn_num;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_h=pstParams->delta_h;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_s=pstParams->delta_s;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_v=pstParams->delta_v;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_g=pstParams->delta_g;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_b=pstParams->delta_b;
				pInfo->cen_ctrl[pstParams->rgn_num].delta_r=pstParams->delta_r;
				pInfo->cen_ctrl[pstParams->rgn_num].ma_gain=pstParams->ma_gain;
			}
			else
			{
				PE_FWI_H13_DBG_PRINT("cen num:%d->%d\n"\
					"del:%d,%d,%d,%d,%d,%d->%d,%d,%d,%d,%d,%d, m:%d->%d,same..\n",\
					pInfo->cen_ctrl[pstParams->rgn_num].rgn_num,pstParams->rgn_num,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_h,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_s,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_v,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_g,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_b,\
					(SINT8)pInfo->cen_ctrl[pstParams->rgn_num].delta_r,\
					(SINT8)pstParams->delta_h,(SINT8)pstParams->delta_s,\
					(SINT8)pstParams->delta_v,(SINT8)pstParams->delta_g,\
					(SINT8)pstParams->delta_b,(SINT8)pstParams->delta_r,\
					pInfo->cen_ctrl[pstParams->rgn_num].ma_gain,pstParams->ma_gain);
				ret = RET_OK;
				break;
			}
		}
		else
		{
			PE_FWI_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif
	#endif
	return ret;
}
/**
 * get f/w settings
 *
 * @param   *pstParams [in] PE_FWI_H13_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_H13_GetCurFwiSettings(PE_FWI_H13_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_H13_SETTINGS_T *pInfo=&_g_pe_fwi_h13_info;
	do{
		CHECK_KNULL(pstParams);
		memcpy(pstParams,pInfo,sizeof(PE_FWI_H13_SETTINGS_T));
	}while(0);
	return ret;
}

