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


/** @file pe_fwi_l9.c
 *
 *  driver for firmware interface functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.26
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
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_etc_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_FWI_L9_ERROR	printk

#define PE_FWI_L9_DBG_PRINT(fmt,args...)	\
	if(_g_fwi_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_FWI_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_FWI_L9_ERROR(fmt,##args);_action;}}

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
static int PE_FWI_L9_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_fwi_l9_trace=0x0;	//default should be off.
static PE_FWI_L9_SETTINGS_T _g_pe_fwi_l9_info;

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
static int PE_FWI_L9_SetFwSettings(PE_FWI_PQ_TABLE_HEAD_T header, UINT8 *pTable, UINT32 tblSize)
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
		PE_FWI_L9_CHECK_CODE(!length,break,"[%s,%d] length is zero.\n",__F__,__L__);
		PE_FWI_L9_CHECK_CODE(!pTable,break,"[%s,%d] pTable is null.\n",__F__,__L__);
		PE_FWI_L9_CHECK_CODE(!tblSize,break,"[%s,%d] tblSize is zero.\n",__F__,__L__);
		PE_FWI_L9_CHECK_CODE(((offset+length)>tblSize),break,\
			"[%s,%d] offset(%d) and length(%d) is greater than tblSize(%d).\n",\
			__F__,__L__,offset,length,tblSize);

		PE_FWI_L9_DBG_PRINT(" wId:%d,ofs:%d,len:%d, tbl_size:%d\n",\
			header.win_id,header.offset,header.length,tblSize);

		dataSize = sizeof(header)+length;
		pData = OS_KMalloc(dataSize);
		PE_FWI_L9_CHECK_CODE(!pData,break,"[%s,%d] pData is null.\n",__F__,__L__);
		memcpy(pData,&header,sizeof(header));
		memcpy(&pData[sizeof(header)],&pTable[offset],length);
		ret = PE_FWI_SETDATA(ipcCmd, pData, dataSize);
		PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
	}while(0);
	if(pData)	OS_Free(pData);
	return ret;
}

/**
 * init fwi module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9)
		{
			PE_FWI_L9_DBG_PRINT("init global values.\n");
			memset(&_g_pe_fwi_l9_info,0xff,sizeof(PE_FWI_L9_SETTINGS_T));
			ret = PE_FWI_L9_SetCtrlWin(LX_PE_WIN_0);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
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
void PE_FWI_L9_SetDbgPrint(UINT32 on_off)
{
	_g_fwi_l9_trace = on_off? 1:0;
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
UINT32 PE_FWI_L9_GetDbgPrint(void)
{
	return _g_fwi_l9_trace;
}
/**
 * set pq f/w control enable & window
 *
 * @param   win_id [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetCtrlWin(UINT32 win_id)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id!=win_id)
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_L9_FW_CTRL);
				header.length = sizeof(PE_FWI_L9_FW_CTRL);
				table.fw_ctrl.win_id = win_id;	//0,1,2:on(0:L, 1:R, 2:All), 0xff:off
				PE_FWI_L9_DBG_PRINT(" wId:%d,ofs:%d,len:%d, tbl_size:%d, fw_ctrl.win_id:%d->%d\n",header.win_id,\
					header.offset,header.length,tbl_size,pInfo->fw_ctrl.win_id,table.fw_ctrl.win_id);
				pInfo->fw_ctrl.win_id = win_id;
				ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
			}
			else
			{
				PE_FWI_L9_DBG_PRINT(" win_id:%d -> %d, just return\n",\
					pInfo->fw_ctrl.win_id,win_id);
			}
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set mute state to f/w
 *
 * @param   *pstParams [in] PE_FWI_L9_MUTE_CTRL
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetMuteState(PE_FWI_L9_MUTE_CTRL *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, en:%d, just return\n",\
					pInfo->fw_ctrl.win_id, pstParams->mute_enable);
				ret = RET_OK;
				break;
			}
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
			header.win_id = LX_PE_WIN_0;
			header.offset = PE_FWI_OFFSET(PE_FWI_L9_MUTE_CTRL);
			header.length = sizeof(PE_FWI_L9_MUTE_CTRL);
			table.mute_ctrl.mute_enable = (pstParams->mute_enable)? 1:0;	// on, off
			PE_FWI_L9_DBG_PRINT(" wId:%d,ofs:%d,len:%d, tbl_size:%d, mute_en:%d\n",\
				header.win_id,header.offset,header.length,tbl_size,table.mute_ctrl.mute_enable);
			ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set tnr auto mode to f/w
 *
 * @param   *pstParams [in] LX_PE_NRD_TNR1_CMN_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetTnrAutoMode(LX_PE_NRD_TNR1_CMN_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9BX)
		{
			if(!PE_CHECK_WIN0(pstParams->win_id) || (pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL))
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, wId:%d, tnr auto en:%d, just return\n",\
					pInfo->fw_ctrl.win_id,pstParams->win_id, pstParams->auto_mode);
				ret = RET_OK;
				break;
			}
			if(pInfo->tnr_ctrl.auto_enable!=pstParams->auto_mode)
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_L9_TNR_CTRL);
				header.length = sizeof(PE_FWI_L9_TNR_CTRL);
				table.tnr_ctrl.auto_enable = (pstParams->auto_mode)? 1:0;	// on, off

				PE_FWI_L9_DBG_PRINT(" wId:%d,ofs:%d,len:%d, tbl_size:%d, tnr_auto:%d -> %d\n",header.win_id,\
					header.offset,header.length,tbl_size,pInfo->tnr_ctrl.auto_enable,table.tnr_ctrl.auto_enable);

				pInfo->tnr_ctrl.auto_enable = table.tnr_ctrl.auto_enable;
				ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
			}
			else
			{
				PE_FWI_L9_DBG_PRINT(" tnr_auto_md:%d -> %d, just return\n",\
					pInfo->tnr_ctrl.auto_enable,pstParams->auto_mode);
			}
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set scaler setting count to f/w
 *
 * @param   cnt [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetSclSettingCnt(UINT32 cnt)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, cnt:%d, just return\n",pInfo->fw_ctrl.win_id,cnt);
				ret = RET_OK;
				break;
			}
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
			header.win_id = LX_PE_WIN_0;
			header.offset = PE_FWI_OFFSET(PE_FWI_L9_SCL_CTRL);
			header.length = sizeof(PE_FWI_L9_SCL_CTRL);
			table.scl_ctrl.set_cnt = (cnt>0xff)? 0xff:cnt;

			PE_FWI_L9_DBG_PRINT(" wId:%d,ofs:%d,len:%d, tbl_size:%d, set_cnt:%d\n",\
				header.win_id,header.offset,header.length,tbl_size,table.scl_ctrl.set_cnt);
			ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set src info to f/w
 *	- dtv play type : normal, file, hdd
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetSrcInfo(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	PE_INF_L9_SETTINGS_T inf_set;
	LX_PE_INF_DISPLAY_T *cur0_inf = NULL;
	do{
		CHECK_KNULL(pstParams);
		ret = PE_INF_L9_GetCurInfSettings(&inf_set);
		PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_INF_L9_GetCurInfSettings() error.\n",__F__,__L__);
		if(PE_KDRV_VER_L9BX)
		{
			cur0_inf=&inf_set.disp_info[LX_PE_WIN_0];
			CHECK_KNULL(cur0_inf);
			if(pstParams->win_id!=LX_PE_WIN_0 || pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, wId:%d, dtv_type:%d, just return\n",\
					pInfo->fw_ctrl.win_id,pstParams->win_id,cur0_inf->dtv_type);
				ret = RET_OK;
				break;
			}
			if(pInfo->src_info.dtv_play_type!=cur0_inf->dtv_type)
			{
				pTable = (UINT8 *)&table;
				tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
				header.win_id = LX_PE_WIN_0;
				header.offset = PE_FWI_OFFSET(PE_FWI_L9_SRC_INFO);
				header.length = sizeof(PE_FWI_L9_SRC_INFO);
				table.src_info.dtv_play_type = (UINT8)(cur0_inf->dtv_type);

				PE_FWI_L9_DBG_PRINT(" wId:%d,ofs:%d,len:%d, tbl_size:%d, dtv_type:%d -> %d\n",header.win_id,\
					header.offset,header.length,tbl_size,pInfo->src_info.dtv_play_type,table.src_info.dtv_play_type);

				pInfo->src_info.dtv_play_type=table.src_info.dtv_play_type;
				ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
				PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
			}
			else
			{
				PE_FWI_L9_DBG_PRINT(" dtv_type:%d -> %d, just return\n",\
					pInfo->src_info.dtv_play_type,cur0_inf->dtv_type);
			}
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set film mode to f/w
 *
 * @param   *pstParams [in] LX_PE_DNT_FILMMODE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, wId:%d, en:%d, just return\n",\
					pInfo->fw_ctrl.win_id,pstParams->win_id,pstParams->enable);
				ret = RET_OK;
				break;
			}
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
			header.win_id = LX_PE_WIN_0;
			header.offset = PE_FWI_OFFSET(PE_FWI_L9_DNT_FMD_CTRL);
			header.length = sizeof(PE_FWI_L9_DNT_FMD_CTRL);
			table.fmd_ctrl.fmd_enable = (pstParams->enable)? 1:0;

			PE_FWI_L9_DBG_PRINT("[%s,%d]wId:%d,ofs:%d,len:%d, tbl_size:%d, fmd_en:%d\n",\
				__F__,__L__,header.win_id,header.offset,\
				header.length,tbl_size,table.fmd_ctrl.fmd_enable);
			ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				pInfo->fmd_ctrl[LX_PE_WIN_0].fmd_enable	= table.fmd_ctrl.fmd_enable;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				pInfo->fmd_ctrl[LX_PE_WIN_0].fmd_enable = table.fmd_ctrl.fmd_enable;
			}
			ret = PE_FWI_L9_SetCtrlWin((UINT32)pstParams->win_id);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetCtrlWin() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set sharpness default to f/w
 *
 * @param   win_id [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetShpDefault(UINT32 win_id)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL || win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, wId:%d, just return\n",\
					pInfo->fw_ctrl.win_id,win_id);
				ret = RET_OK;
				break;
			}
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
			header.win_id = win_id;
			header.offset = PE_FWI_OFFSET(PE_FWI_L9_SHP_DERH_CTRL_0B);
			header.length = sizeof(PE_FWI_L9_SHP_DERH_CTRL_0B);
			table.shp_derh_ctrl_0B.e_gain_th1 = 0x28;
			table.shp_derh_ctrl_0B.e_gain_th2 = 0x44;

			PE_FWI_L9_DBG_PRINT("[%s,%d]wId:%d,ofs:%d,len:%d, tbl_size:%d, e_g_th1,2:%d,%d\n",\
				__F__,__L__,header.win_id,header.offset,header.length,tbl_size,\
				table.shp_derh_ctrl_0B.e_gain_th1,table.shp_derh_ctrl_0B.e_gain_th2);
			ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);
			ret = PE_FWI_L9_SetCtrlWin(win_id);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetCtrlWin() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set resolution enhance misc control
 *
 * @param   *pstParams [in] LX_PE_SHP_RE1_MISC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetReMiscCtrl(LX_PE_SHP_RE1_MISC_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		CHECK_KNULL(pstParams);
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, just return\n",pInfo->fw_ctrl.win_id);
				ret = RET_OK;
				break;
			}
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
			header.win_id = pstParams->win_id;
			header.offset = PE_FWI_OFFSET(PE_FWI_L9_SHP_CORING_CTRL_05);
			header.length = sizeof(PE_FWI_L9_SHP_CORING_CTRL_05)+sizeof(PE_FWI_L9_SHP_CORING_CTRL_06);
			table.shp_coring_ctrl_05.gt_th0 = GET_BITS(pstParams->gt_th0,0,8);
			table.shp_coring_ctrl_05.gt_th1 = GET_BITS(pstParams->gt_th1,0,8);
			table.shp_coring_ctrl_06.gt_th0a = GET_BITS(pstParams->gt_th0a,0,8);
			table.shp_coring_ctrl_06.gt_th0b = GET_BITS(pstParams->gt_th0b,0,8);

			PE_FWI_L9_DBG_PRINT("[%s,%d]wId:%d,ofs:%d,len:%d, tbl_size:%d\n"\
				"gt_th0,1:%d,%d, gt_th0a,b:%d,%d\n",__F__,__L__,\
				header.win_id,header.offset,header.length,tbl_size,\
				table.shp_coring_ctrl_05.gt_th0,table.shp_coring_ctrl_05.gt_th1,\
				table.shp_coring_ctrl_06.gt_th0a,table.shp_coring_ctrl_06.gt_th0b);
			ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);

			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				pInfo->coring_05[LX_PE_WIN_0].gt_th0 = table.shp_coring_ctrl_05.gt_th0;
				pInfo->coring_05[LX_PE_WIN_0].gt_th1 = table.shp_coring_ctrl_05.gt_th1;
				pInfo->coring_06[LX_PE_WIN_0].gt_th0a = table.shp_coring_ctrl_06.gt_th0a;
				pInfo->coring_06[LX_PE_WIN_0].gt_th0b = table.shp_coring_ctrl_06.gt_th0b;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				pInfo->coring_05[LX_PE_WIN_1].gt_th0 = table.shp_coring_ctrl_05.gt_th0;
				pInfo->coring_05[LX_PE_WIN_1].gt_th1 = table.shp_coring_ctrl_05.gt_th1;
				pInfo->coring_06[LX_PE_WIN_1].gt_th0a = table.shp_coring_ctrl_06.gt_th0a;
				pInfo->coring_06[LX_PE_WIN_1].gt_th0b = table.shp_coring_ctrl_06.gt_th0b;
			}
			ret = PE_FWI_L9_SetCtrlWin((UINT32)pstParams->win_id);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetCtrlWin() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set edge and detail enhance ctrl
 *
 * @param   win_id [in] UINT32
 * @param   *pstEe [in] LX_PE_SHP_EE1_T
 * @param   *pstDe [in] LX_PE_SHP_DE1_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_SetReEdgeAndDetailCtrl(UINT32 win_id,LX_PE_SHP_EE1_T *pstEe,LX_PE_SHP_DE1_T *pstDe)
{
	int ret = RET_OK;
	PE_FWI_PQ_TABLE_HEAD_T header;
	PE_FWI_L9_PQ_IPC_CTRL table;
	LX_PE_WIN_ID wId;
	UINT32 tbl_size;
	UINT8 *pTable = NULL;
	LX_PE_SHP_EE1_T e_param;
	LX_PE_SHP_DE1_T d_param;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		if(PE_KDRV_VER_L9BX)
		{
			if(pInfo->fw_ctrl.win_id>LX_PE_WIN_ALL || win_id>LX_PE_WIN_ALL)
			{
				PE_FWI_L9_DBG_PRINT("fw_ctrl.win_id:%d, wId:%d, just return\n",\
					pInfo->fw_ctrl.win_id,win_id);
				break;
			}
			wId = PE_GET_CHECKED_WINID(win_id);
			if(!pstEe)
			{
				e_param.win_id = (LX_PE_WIN_ID)win_id;
				e_param.mp_edge_gain_b = pInfo->coring_09[wId].edge_gain_b;
				e_param.mp_edge_gain_w = pInfo->coring_09[wId].edge_gain_w;
				e_param.sp_edge_gain_b = pInfo->dp_01[wId].edge_gain_b;
				e_param.sp_edge_gain_w = pInfo->dp_01[wId].edge_gain_w;
			}
			else
			{
				memcpy(&e_param,pstEe,sizeof(LX_PE_SHP_EE1_T));
			}
			if(!pstDe)
			{
				d_param.win_id = (LX_PE_WIN_ID)win_id;
				d_param.mp_texture_gain_b = pInfo->coring_09[wId].texture_gain_b;
				d_param.mp_texture_gain_w = pInfo->coring_09[wId].texture_gain_w;
				d_param.sp_texture_gain_b = pInfo->dp_01[wId].texture_gain_b;
				d_param.sp_texture_gain_w = pInfo->dp_01[wId].texture_gain_w;
			}
			else
			{
				memcpy(&d_param,pstDe,sizeof(LX_PE_SHP_DE1_T));
			}
			pTable = (UINT8 *)&table;
			tbl_size = sizeof(PE_FWI_L9_PQ_IPC_CTRL);
			header.win_id = wId;
			header.offset = PE_FWI_OFFSET(PE_FWI_L9_SHP_CORING_CTRL_09);
			header.length = sizeof(PE_FWI_L9_SHP_CORING_CTRL_09)+sizeof(PE_FWI_L9_SHP_DP_CTRL_01);

			table.shp_coring_ctrl_09.edge_gain_b = GET_BITS(e_param.mp_edge_gain_b,0,7);
			table.shp_coring_ctrl_09.edge_gain_w = GET_BITS(e_param.mp_edge_gain_w,0,7);
			table.shp_coring_ctrl_09.texture_gain_b = GET_BITS(d_param.mp_texture_gain_b,0,7);
			table.shp_coring_ctrl_09.texture_gain_w = GET_BITS(d_param.mp_texture_gain_w,0,7);
			table.shp_dp_ctrl_01.edge_gain_b = GET_BITS(e_param.sp_edge_gain_b,0,7);
			table.shp_dp_ctrl_01.edge_gain_w = GET_BITS(e_param.sp_edge_gain_w,0,7);
			table.shp_dp_ctrl_01.texture_gain_b = GET_BITS(d_param.sp_texture_gain_b,0,7);
			table.shp_dp_ctrl_01.texture_gain_w = GET_BITS(d_param.sp_texture_gain_w,0,7);

			PE_FWI_L9_DBG_PRINT("[%s,%d]wId:%d,ofs:%d,len:%d, tbl_size:%d\n"\
				"coring  edge_gain_b,w:%d,%d, texture_gain_b,w:%d,%d\n"\
				"dp      edge_gain_b,w:%d,%d, texture_gain_b,w:%d,%d\n",__F__,__L__,\
				header.win_id,header.offset,header.length,tbl_size,\
				table.shp_coring_ctrl_09.edge_gain_b,table.shp_coring_ctrl_09.edge_gain_w,\
				table.shp_coring_ctrl_09.texture_gain_b,table.shp_coring_ctrl_09.texture_gain_w,\
				table.shp_dp_ctrl_01.edge_gain_b,table.shp_dp_ctrl_01.edge_gain_w,\
				table.shp_dp_ctrl_01.texture_gain_b,table.shp_dp_ctrl_01.texture_gain_w);
			ret = PE_FWI_L9_SetFwSettings(header, pTable, tbl_size);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetFwSettings() error.\n",__F__,__L__);

			if(PE_CHECK_WIN0(win_id))
			{
				pInfo->coring_09[LX_PE_WIN_0].edge_gain_b = table.shp_coring_ctrl_09.edge_gain_b;
				pInfo->coring_09[LX_PE_WIN_0].edge_gain_w = table.shp_coring_ctrl_09.edge_gain_w;
				pInfo->coring_09[LX_PE_WIN_0].texture_gain_b = table.shp_coring_ctrl_09.texture_gain_b;
				pInfo->coring_09[LX_PE_WIN_0].texture_gain_w = table.shp_coring_ctrl_09.texture_gain_w;
				pInfo->dp_01[LX_PE_WIN_0].edge_gain_b = table.shp_dp_ctrl_01.edge_gain_b;
				pInfo->dp_01[LX_PE_WIN_0].edge_gain_w = table.shp_dp_ctrl_01.edge_gain_w;
				pInfo->dp_01[LX_PE_WIN_0].texture_gain_b = table.shp_dp_ctrl_01.texture_gain_b;
				pInfo->dp_01[LX_PE_WIN_0].texture_gain_w = table.shp_dp_ctrl_01.texture_gain_w;
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pInfo->coring_09[LX_PE_WIN_1].edge_gain_b = table.shp_coring_ctrl_09.edge_gain_b;
				pInfo->coring_09[LX_PE_WIN_1].edge_gain_w = table.shp_coring_ctrl_09.edge_gain_w;
				pInfo->coring_09[LX_PE_WIN_1].texture_gain_b = table.shp_coring_ctrl_09.texture_gain_b;
				pInfo->coring_09[LX_PE_WIN_1].texture_gain_w = table.shp_coring_ctrl_09.texture_gain_w;
				pInfo->dp_01[LX_PE_WIN_1].edge_gain_b = table.shp_dp_ctrl_01.edge_gain_b;
				pInfo->dp_01[LX_PE_WIN_1].edge_gain_w = table.shp_dp_ctrl_01.edge_gain_w;
				pInfo->dp_01[LX_PE_WIN_1].texture_gain_b = table.shp_dp_ctrl_01.texture_gain_b;
				pInfo->dp_01[LX_PE_WIN_1].texture_gain_w = table.shp_dp_ctrl_01.texture_gain_w;
			}
			ret = PE_FWI_L9_SetCtrlWin((UINT32)win_id);
			PE_FWI_L9_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_L9_SetCtrlWin() error.\n",__F__,__L__);
		}
		else
		{
			PE_FWI_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get l9 f/w settings
 *
 * @param   *pstParams [in] PE_FWI_L9_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_FWI_L9_GetCurFwiSettings(PE_FWI_L9_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_FWI_L9_SETTINGS_T *pInfo=&_g_pe_fwi_l9_info;
	do{
		CHECK_KNULL(pstParams);
		memcpy(pstParams,pInfo,sizeof(PE_FWI_L9_SETTINGS_T));
	}while(0);
	return ret;
}

