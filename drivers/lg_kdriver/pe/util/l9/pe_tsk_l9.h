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


/** @file pe_tsk_l9.h
 *
 *  task func. for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.09
 *	@see		
 */

#ifndef	_PE_TSK_L9_H_
#define	_PE_TSK_L9_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe task l9 operation type
 */
typedef struct
{
	UINT32 pause_task;		///< 1:pause, 0:task run
	UINT32 timeout;			///< task timeout, msec
	UINT32 dbgmode;			///< debug mode
}
PE_TSK_L9_OPR_T;

/**
 *	pe task l9 data type
 */
typedef struct
{
	UINT32 ov_r_out_sync;	///< use ovr display sync
}
PE_TSK_L9_DTA_T;

/**
 *	pe task l9 cfg type
 */
typedef struct {
	PE_INF_L9_SETTINGS_T inf;
	PE_TSK_L9_OPR_T opr;
	PE_TSK_L9_DTA_T dta;
}
PE_TSK_L9_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_TSK_L9_SetDbgPrint(UINT32 on_off);
int PE_TSK_L9_SetTaskOperation(LX_PE_ETC_DBG_T *pstParams);
int PE_TSK_L9_GetTaskOperation(LX_PE_ETC_DBG_T *pstParams);
int PE_TSK_L9_CreatePicTask(void);
int PE_TSK_L9_StartPicTask(void);
int PE_TSK_L9_StopPicTask(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_TSK_L9_H_ */
