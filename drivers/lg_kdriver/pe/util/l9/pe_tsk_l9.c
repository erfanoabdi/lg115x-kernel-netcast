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


/** @file pe_tsk_hw_l9.c
 *
 *  task func. for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
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
#include <linux/kthread.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc_hw.h"
#include "pe_shp_hw.h"
#include "pe_nrd_hw.h"
#include "pe_ccm_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define TSK_L9_START 0
#define TSK_L9_END 1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_TSK_L9_ERROR	printk
#define PE_TSK_L9_PRINT	printk

#define PE_TSK_L9_DBG_PRINT(fmt,args...)	\
	if(_g_pe_tsk_l9_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_TSK_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_TSK_L9_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	PE_TSK_L9_DBG_OFF = 0,
	PE_TSK_L9_DBG_ON,
	PE_TSK_L9_DBG_TIME,
	PE_TSK_L9_DBG_MAX
}
PE_TSK_L9_OPR_DBG_MODE;

typedef enum
{
	PE_TSK_L9_TIME_TASK = 0,
	PE_TSK_L9_TIME_SCL,
	PE_TSK_L9_TIME_MAX
}
PE_TSK_L9_TIME;

typedef struct
{
	UINT32 tick_start_time[PE_TSK_L9_TIME_MAX];
	UINT32 tick_end_time[PE_TSK_L9_TIME_MAX];
}
PE_TSK_L9_TIME_INFO_T;

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
static int PE_TSK_L9_CheckTime(char *fn_str, PE_TSK_L9_TIME location, UINT32 pos);
static int PE_TSK_L9_PicTask(void *data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DECLARE_WAIT_QUEUE_HEAD(_wq_pe_l9);
static OS_SEM_T	_g_pe_tsk_l9_sem;
static UINT32 _g_pe_tsk_l9_trace=0x0;		//default should be off.
static struct task_struct *g_pstPeTaskL9 = NULL;
static PE_TSK_L9_CFG_T _g_pe_tsk_l9_cfg;

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
void PE_TSK_L9_SetDbgPrint(UINT32 on_off)
{
	_g_pe_tsk_l9_trace = on_off? 1:0;
	return;
}
/**
 * set task operation
 *
 * @param   *pstParams [in] LX_PE_ETC_DBG_T
 * @return  void
 * @see     PE_TSK_L9_OPR_T
 * @author
 */
int PE_TSK_L9_SetTaskOperation(LX_PE_ETC_DBG_T *pstParams)
{
    int ret = RET_OK;
	PE_TSK_L9_OPR_T *pOpr = &_g_pe_tsk_l9_cfg.opr;
	do {
		CHECK_KNULL(pstParams);
		PE_TSK_L9_CHECK_CODE((sizeof(UINT32)*pstParams->size)!=sizeof(PE_TSK_L9_OPR_T),\
			break,"[%s,%d] size mismatch.\n",__F__,__L__);
		if(pOpr->pause_task&&!pstParams->data[0])
		{
			wake_up_interruptible(&_wq_pe_l9);
			PE_TSK_L9_DBG_PRINT("re-start pic task.\n");
		}
		memcpy(pOpr,&pstParams->data[0],sizeof(PE_TSK_L9_OPR_T));
		PE_TSK_L9_DBG_PRINT("set : pause:%d, time:%d, dbg_md:%d\n",\
			pOpr->pause_task,pOpr->timeout,pOpr->dbgmode);
	} while(0);
	return ret;
}
/**
 * get task operation
 *
 * @param   *pstParams [in/out] LX_PE_ETC_DBG_T
 * @return  void
 * @see     PE_TSK_L9_OPR_T
 * @author
 */
int PE_TSK_L9_GetTaskOperation(LX_PE_ETC_DBG_T *pstParams)
{
	int ret = RET_OK;
	PE_TSK_L9_OPR_T *pOpr = &_g_pe_tsk_l9_cfg.opr;
	do{
		CHECK_KNULL(pstParams);
		PE_TSK_L9_CHECK_CODE((sizeof(UINT32)*pstParams->size)!=sizeof(PE_TSK_L9_OPR_T),\
			break,"[%s,%d] size mismatch.\n",__F__,__L__);
		memcpy(&pstParams->data[0],pOpr,sizeof(PE_TSK_L9_OPR_T));
		PE_TSK_L9_DBG_PRINT("get : pause:%d, time:%d\n",pOpr->pause_task,pOpr->timeout);
	}while(0);
	return ret;
}
/**
 * create pe l9 task
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_L9_CreatePicTask(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9)
		{
			if(g_pstPeTaskL9)
			{
				PE_TSK_L9_DBG_PRINT("pic task is already created.\n");
				ret = RET_ERROR;
				break;
			}			
			g_pstPeTaskL9 = kthread_create(PE_TSK_L9_PicTask, (void *)NULL, "pe_thread_l9");
			if(g_pstPeTaskL9)
			{
				PE_TSK_L9_DBG_PRINT("pic task is created successfully.\n");
			}
			else
			{
				PE_TSK_L9_DBG_PRINT("pic task creation fail.\n");
				ret = RET_ERROR;
				break;
			}
		}
		else
		{
			PE_TSK_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * start pe l9 task
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_L9_StartPicTask(void)
{
	int ret = RET_OK;
	PE_TSK_L9_OPR_T *pOpr = &_g_pe_tsk_l9_cfg.opr;
	do{
		OS_InitMutex(&_g_pe_tsk_l9_sem, OS_SEM_ATTR_DEFAULT);
		if(PE_KDRV_VER_L9)
		{
			if(g_pstPeTaskL9)
			{
				memset0(_g_pe_tsk_l9_cfg);
				pOpr->pause_task = 0;
				pOpr->timeout = 30;
				wake_up_process(g_pstPeTaskL9);
				PE_TSK_L9_DBG_PRINT("pic task wake up successfully.\n");
			}
			else
			{
				PE_TSK_L9_DBG_PRINT("start fail. pic task is not created.\n");
				ret = RET_ERROR;
				break;
			}
		}
		else
		{
			PE_TSK_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * stop pe l9 task
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_L9_StopPicTask(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_L9)
		{
			if(g_pstPeTaskL9)
			{
				kthread_stop(g_pstPeTaskL9);
				PE_TSK_L9_DBG_PRINT("stop pic task.\n");
			}
			else
			{
				PE_TSK_L9_DBG_PRINT("stop fail. pic task is not created.\n");
				ret = RET_ERROR;
				break;
			}
		}
		else
		{
			PE_TSK_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
static int PE_TSK_L9_CheckTime(char *fn_str, PE_TSK_L9_TIME location, UINT32 pos)
{
	int ret = RET_OK;
	static PE_TSK_L9_TIME_INFO_T time_info;
	PE_TSK_L9_OPR_T *pOpr = &_g_pe_tsk_l9_cfg.opr;
	UINT32 time_diff;
	do {
		if(pOpr->dbgmode!=PE_TSK_L9_DBG_TIME)
		{
			ret = RET_OK;
			break;
		}
		switch(pos)
		{
			case TSK_L9_START:
				time_info.tick_start_time[location] = OS_GetMsecTicks_Tag();
				break;
			case TSK_L9_END:
			default:
				time_info.tick_end_time[location] = OS_GetMsecTicks_Tag();
				if(time_info.tick_end_time[location] >= time_info.tick_start_time[location])
					time_diff = time_info.tick_end_time[location] - time_info.tick_start_time[location];
				else
					time_diff = time_info.tick_start_time[location] + (0xFFFFFFFF - time_info.tick_end_time[location]);
				PE_TSK_L9_PRINT("%s :	%d msec  elapsed\n", fn_str, (time_diff==0)?1:time_diff);
				break;
		}
	}while(0);
	return ret;
}
/**
 * pe hw l9 task
 *
 * @param   *data [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_TSK_L9_PicTask(void *data)
{
	int ret = RET_OK;
	static unsigned int count = 0;
	PE_TSK_L9_CFG_T *pCfg = &_g_pe_tsk_l9_cfg;
	PE_INF_L9_SETTINGS_T *pInfo = &_g_pe_tsk_l9_cfg.inf;
	PE_TSK_L9_OPR_T *pOpr = &_g_pe_tsk_l9_cfg.opr;
	PE_TSK_L9_DBG_PRINT("pic task start.\n");
	while(1)
	{
		/* check stop condition when device is closed */
		if(kthread_should_stop())
		{
			PE_TSK_L9_DBG_PRINT("pic task exit.\n");
			break;
		}
		PE_TSK_L9_CheckTime("picture task", PE_TSK_L9_TIME_TASK, TSK_L9_START);
		/**********************************************/
		/* add specific func.                         */
		/**********************************************/
		/* check info */
		ret = PE_INF_L9_CheckSclInfo();
		/* check info */
		ret = PE_INF_L9_GetCurInfSettings(pInfo);
		/* set ov r sync */
		ret = PE_WIN_HW_L9_SetWcpSync(pCfg);
		/* set picture window */
		ret = PE_WIN_HW_L9_SetEnhancingWindow(pCfg);
		/* set scaler filter */
		ret = PE_SHP_HW_L9_SetScalerFilterCtrl(pCfg);
		/* set resolution enable */
		ret = PE_SHP_HW_L9_SetReEnableCtrl(pCfg);
		/* set pe detour */
		ret = PE_NRD_HW_L9_SetMeasureWinCtrl(pCfg);
		/* set acr gain */
		ret = PE_CCM_HW_L9_SetAutoCrGain(pCfg);
		/**********************************************/
		PE_TSK_L9_CheckTime("picture task", PE_TSK_L9_TIME_TASK, TSK_L9_END);
		PE_TSK_L9_DBG_PRINT("count :%d\n",count);
		if(count > 10000)	count = 0;
		else				count ++;
		/**********************************************/
		OS_MsecSleep(pOpr->timeout);
		if(pOpr->pause_task)
		{
			PE_TSK_L9_DBG_PRINT("pic task is paused.\n");
			interruptible_sleep_on(&_wq_pe_l9);
		}
	}
	return 0;
}

