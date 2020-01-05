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


/** @file pe_io.c
 *
 *  io interface functions for pe device. ( used only within kdriver )
 *	
 *	@author		
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
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_io.h"
#include "pe_cmn.h"
#include "pe_csc.h"
#include "pe_cmg.h"
#include "pe_nrd.h"
#include "pe_dnt.h"
#include "pe_shp.h"
#include "pe_ccm.h"
#include "pe_dcm.h"
#include "pe_win.h"
#include "pe_spd.h"
#include "pe_etc.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_IO_INIT__ON	1
#define PE_IO_INIT_OFF	0

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_IO_ERROR	printk

#ifdef PE_USE_DBG_PRINT
#define PE_IO_DBG_PRINT(fmt,args...)	printk("[%s,%d] "fmt,__F__,__L__, ##args)
#else
#define PE_IO_DBG_PRINT(fmt,args...)
#endif

#define PE_IO_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_IO_ERROR(fmt,##args);_action;}}

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

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PE_IO_INF_T _g_pe_io_inf;	// pe io info

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * process packet
 *
 * @param   rcvdata [in] unsigned int
 * @param   recvpkt [in] LX_PE_PKT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */ 
int PE_IO_ProcessPkt(unsigned int *rcvdata, LX_PE_PKT_T *rcvpkt)
{
	int ret = RET_OK;
	unsigned int rw_type, module_type, func_type, data_size;

	PE_IO_CHECK_CODE(!rcvdata,return RET_ERROR,"[%s,%d]rcvdata is null. \n",__F__,__L__);
	PE_IO_CHECK_CODE(!rcvpkt,return RET_ERROR,"[%s,%d]rcvpkt is null. \n",__F__,__L__);

	rw_type = PE_GET_PKTINFO_RWTYPE(rcvpkt->info);
	module_type = PE_GET_PKTINFO_MODLTYPE(rcvpkt->info);
	func_type = PE_GET_PKTINFO_FUNCTYPE(rcvpkt->info);
	data_size = rcvpkt->size;
	PE_IO_DBG_PRINT("type:rw:%d,modl:%d,func:%d, size:%d\n",rw_type,module_type,func_type,data_size);

	switch(rw_type)
	{
		case PE_ITEM_PKTRW(SET):
		case PE_ITEM_PKTRW(GET):
		{
			switch(module_type)
			{
				case PE_ITEM_PKTMODL(CMN):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_CMN_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_CMN_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(CSC):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_CSC_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_CSC_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(CMG):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_CMG_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_CMG_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(NRD):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_NRD_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_NRD_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(DNT):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_DNT_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_DNT_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(SHP):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_SHP_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_SHP_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(CCM):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_CCM_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_CCM_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(DCM):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_DCM_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_DCM_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(WIN):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_WIN_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_WIN_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(ETC):
					if(rw_type==PE_ITEM_PKTRW(SET))	ret=PE_ETC_SetFunction(rcvdata,func_type,data_size);
					else							ret=PE_ETC_GetFunction(rcvdata,func_type,data_size);
				break;
				case PE_ITEM_PKTMODL(DEFAULT):
				case PE_ITEM_PKTMODL(DBG):
				{
					if(rw_type==PE_ITEM_PKTRW(SET))
					{
						do{
							ret=PE_CMN_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMN_SetFunction() error..\n",__F__,__L__);
							ret=PE_CSC_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CSC_SetFunction() error..\n",__F__,__L__);
							ret=PE_CMG_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMG_SetFunction() error..\n",__F__,__L__);
							ret=PE_NRD_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_NRD_SetFunction() error..\n",__F__,__L__);
							ret=PE_DNT_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_DNT_SetFunction() error..\n",__F__,__L__);
							ret=PE_SHP_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_SHP_SetFunction() error..\n",__F__,__L__);
							ret=PE_CCM_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CCM_SetFunction() error..\n",__F__,__L__);
							ret=PE_DCM_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_DCM_SetFunction() error..\n",__F__,__L__);
							ret=PE_WIN_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_WIN_SetFunction() error..\n",__F__,__L__);
							ret=PE_ETC_SetFunction(rcvdata,func_type,data_size);
							PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_D3D_SetFunction() error..\n",__F__,__L__);
						}while(0);
					}
					else
					{
						ret=PE_CMN_GetFunction(rcvdata,func_type,data_size);
					}
				}
				break;
				default:
					PE_IO_ERROR("[%s,%d]module_type default case...\n",__F__,__L__);
					ret = RET_ERROR;					
				break;
			}
		}
		break;
		case PE_ITEM_PKTRW(INIT):
		{
			ret = PE_IO_Init(rcvdata,data_size);
		}
		break;
		default:
		{
			PE_IO_ERROR("[%s,%d]rw_type default case...\n",__F__,__L__);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * init picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_IO_InitPicEnhanceModule(void)
{
	int ret = RET_OK;

	PE_IO_DBG_PRINT("S\n");
	do{
		ret = PE_CMN_InitPicEnhanceModule();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMN_InitPicEnhanceModule() error..\n",__F__,__L__);
		memset(&_g_pe_io_inf,0x0,sizeof(PE_IO_INF_T));
	}while(0);
	PE_IO_DBG_PRINT("E\n");

	return ret;
}
/**
 * clean up picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_IO_CleanupPicEnhanceModule(void)
{
	int ret = RET_OK;

	PE_IO_DBG_PRINT("S\n");
	do{
		ret = PE_CMN_CleanupPicEnhanceModule();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMN_CleanupPicEnhanceModule() error..\n",__F__,__L__);
	}while(0);
	PE_IO_DBG_PRINT("E\n");

	return ret;
}
/**
 * open picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_IO_OpenPicEnhanceModule(void)
{
	int ret = RET_OK;
	PE_IO_INF_T *io_info = &_g_pe_io_inf;

	PE_IO_DBG_PRINT("S\n");
	do{
		ret = PE_CMN_OpenPicEnhanceModule();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMN_OpenPicEnhanceModule() error..\n",__F__,__L__);
		io_info->initialized = PE_IO_INIT_OFF;	//This func. is called when my_dev->dev_open_count == 0.
	}while(0);
	PE_IO_DBG_PRINT("E\n");

	return ret;
}
/**
 * close picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_IO_ClosePicEnhanceModule(void)
{
	int ret = RET_OK;

	PE_IO_DBG_PRINT("S\n");
	do{
		ret = PE_CMN_ClosePicEnhanceModule();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMN_ClosePicEnhanceModule() error..\n",__F__,__L__);
	}while(0);
	PE_IO_DBG_PRINT("E\n");

	return ret;
}
/**
 * pe io init
 *
 * @param   data [in/out] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_IO_Init(unsigned int *data, unsigned int datasize)
{
	int ret = RET_OK;
	PE_IO_INF_T *io_info = &_g_pe_io_inf;

	PE_IO_DBG_PRINT("S\n");
	do{
		if(io_info->initialized>=PE_IO_INIT__ON)
		{
			PE_IO_DBG_PRINT("PE was already initialized(%d).\n",io_info->initialized);
			break;
		}
		ret = PE_CMN_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMN_Init() error..\n",__F__,__L__);
		ret = PE_CSC_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CSC_Init() error..\n",__F__,__L__);
		ret = PE_CMG_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CMG_Init() error..\n",__F__,__L__);
		ret = PE_NRD_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_NRD_Init() error..\n",__F__,__L__);
		ret = PE_DNT_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_DNT_Init() error..\n",__F__,__L__);
		ret = PE_SHP_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_SHP_Init() error..\n",__F__,__L__);
		ret = PE_CCM_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_CCM_Init() error..\n",__F__,__L__);
		ret = PE_DCM_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_DCM_Init() error..\n",__F__,__L__);
		ret = PE_WIN_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_WIN_Init() error..\n",__F__,__L__);
		ret = PE_ETC_Init();
		PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_ETC_Init() error..\n",__F__,__L__);
		if(PE_SPD_CheckInitResume(data,datasize))
		{
			ret = PE_SPD_resume();
			PE_IO_CHECK_CODE(ret,break,"[%s,%d]PE_SPD_resume() error..\n",__F__,__L__);
		}
		io_info->initialized=PE_IO_INIT__ON;
	}while(0);
	PE_IO_DBG_PRINT("E\n");

	return ret;
}

