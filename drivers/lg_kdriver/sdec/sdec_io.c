/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/


/** @file
 *
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/
#define PCR_RECOVERY_DEBUG	0

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include <mach/platform.h>

#include "os_util.h"


#include "sdec_kapi.h"
//#include "sdec_reg.h"
#include "sdec_drv.h"
#include "sdec_io.h"
#include "sdec_pes.h"
#include "sdec_hal.h"

#include "../sys/sys_regs.h"	//for CTOP CTRL Reg. map
#include "h13/sdec_reg_h13a0.h"

#include "sdec_swparser.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */

#define 	MAX_DELTA_ERROR_FOR_FREE_RUN 	5
#define 	_GO_FREE_RUN					1
#define 	_STOP_FREE_RUN					0

UINT8	delta_error = 0;

#endif


#ifdef __NEW_PWM_RESET_COND__ /* jinhwan.bae for new PWM reset condition */

#define 	MAX_ERROR_FOR_PWM_RESET		 	10

UINT8	pcr_error_for_reset = 0;

#endif


/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern volatile SDTOP_REG_H13A0_T 	*stSDEC_TOP_RegH13A0;
extern volatile SDIO_REG_H13A0_T	*stSDEC_IO_RegH13A0;
extern volatile MPG_REG_H13A0_T 	*stSDEC_MPG_RegH13A0[2];
extern CTOP_CTRL_REG_H13_T 			gCTOP_CTRL_H13;

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
static	void pwm_context_reset(S_SDEC_PARAM_T	*stpSdecParam, UINT8 cur_ch);

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

#if 0
void  SDEC_DTV_SOC_Message
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Level,
	const UINT8 *fmt, ...)
{

	va_list args;
	char buf[200];
//	int buf_count = 0;
	//UINT64 time = 0;
	//struct timespec curtime;
	struct timeval curtime;

	//gettimeofday(&rv, NULL);
//       if(Module_mask & module)
//       {
		if(stpSdecParam->ui32MsgMask & ui32Level)//masking
		{
			va_start(args, fmt);
			vsprintf(buf, fmt, args);

			//curtime = current_kernel_time();
			do_gettimeofday(&curtime);
			//printk("%lu:[%ld]",uiMsgLine, curtime.tv_nsec);
			//printk("%lu:[%ld]",uiMsgLine, curtime.tv_nsec);
			//printk("%lu:[%ld]",uiMsgLine, curtime.tv_usec);
			printk("[%ld]",curtime.tv_usec);

#if 0
			for(buf_count = 5; buf_count<strlen(buf); buf_count++)
			{
				gbuf[count][buf_count] = buf[buf_count];
			}
#endif /* #if 0 */

//			uiMsgLine++;
//			count++;
#if 0
			if(!(count%3))
				count=0;

#endif /* #if 0 */
			vprintk(buf, args);
			printk("\r\n");

			va_end(args);
		}
//       }
//	else
//		return;

}
#endif /* #if 0 */

/**
********************************************************************************
* @brief
*   initialize Mutex.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_MutexInitialize
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_MutexInitialize");

	//mutex_init(&stpSdecParam->stSdecMutex);
	OS_InitMutex(&stpSdecParam->stSdecMutex, OS_SEM_ATTR_DEFAULT);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_MutexInitialize");

	eRet = OK;

	return (eRet);
}

/**
********************************************************************************
* @brief
*   Deastory Mutex.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_MutexDestroy
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_MutexInitialize");

	//mutex_init(&stpSdecParam->stSdecMutex);
	OS_InitMutex(&stpSdecParam->stSdecMutex, OS_SEM_ATTR_DEFAULT);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_MutexInitialize");

	eRet = OK;

	return (eRet);
}


/**
********************************************************************************
* @brief
*   initialize spinlock.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_SpinLockInitialize
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;
	int ch_idx = 0, flt_idx = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_SpinLockInitialize");

	spin_lock_init(&stpSdecParam->stSdecNotiSpinlock);
	spin_lock_init(&stpSdecParam->stSdecPesSpinlock);
	spin_lock_init(&stpSdecParam->stSdecSecSpinlock);
	spin_lock_init(&stpSdecParam->stSdecResetSpinlock);
	spin_lock_init(&stpSdecParam->stSdecPidfSpinlock);

	for ( ch_idx = 0; ch_idx < SDEC_IO_CH_NUM ; ch_idx++ )
	{
		for ( flt_idx = 0; flt_idx < SDEC_IO_FLT_NUM ; flt_idx++ )
		{
			spin_lock_init(&stpSdecParam->stSdecGpbSpinlock[ch_idx][flt_idx]);
		}
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_SpinLockInitialize");

	eRet = OK;

	return (eRet);
}

#if 0
/**
********************************************************************************
* @brief
*   initialize spinlock destory.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_SpinLockDestroy
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_SpinLockDestroy");

	SDEC_DTV_SOC_Message( SDEC_TRACE, " -->SDEC_SpinLockDestroy");

	eRet = OK;

	return (eRet);
}
#endif

/**
********************************************************************************
* @brief
*   initialize Workqueue.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_WorkQueueInitialize
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_WorkQueueInitialize");

	//Sdec work queue init and fnc reg
	stpSdecParam->workqueue = create_workqueue("SDEC");

	if(!stpSdecParam->workqueue){
		SDEC_DEBUG_Print("create work queue failed");
		goto exit;
	}

	INIT_WORK(&stpSdecParam->Notify,		SDEC_Notify);
	INIT_WORK(&stpSdecParam->PcrRecovery,	SDEC_PCRRecovery);
	INIT_WORK(&stpSdecParam->PesProc,		SDEC_PES_Proc);

	eRet = OK;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_WorkQueueInitialize");

exit:
	return (eRet);
}

/**
********************************************************************************
* @brief
*   initialize Workqueue destory.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_WorkQueueDestroy
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_WorkQueueDestroy");

	flush_workqueue(stpSdecParam->workqueue);

	destroy_workqueue(stpSdecParam->workqueue);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_WorkQueueDestroy");

	eRet = OK;

	return (eRet);
}

/**
********************************************************************************
* @brief
*   initialize Watequeue destory.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_WaitQueueInitialize
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_WaitQueueInitialize");

	init_waitqueue_head(&stpSdecParam->wq);
	stpSdecParam->wq_condition = 0;

	/* SW Parser Event Init */
	OS_InitEvent( &stpSdecParam->stSdecSWPEvent);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_WaitQueueInitialize");

	eRet = OK;

	return (eRet);
}

/**
********************************************************************************
* @brief
*   initialize sdec module.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_InitialaizeModule
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T 	eRet = NOT_OK;
	DTV_STATUS_T 	eResult = NOT_OK;
	UINT8 			ui8ch;
	LX_SDEC_CAP_T*	stpLXSdecCap;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_InitialaizeModule");

	stpLXSdecCap = (LX_SDEC_CAP_T *)ui32Arg;

	ui8ch = stpLXSdecCap->eCh;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	if( ui8ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8ch);
		goto exit;
	}

	/* pidf init */
	eResult = SDEC_Pidf_Clear(stpSdecParam, ui8ch, CLEAR_ALL_MODE);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_Pidf_Clear failed:[%d]", eResult);
		goto exit;
	}
	/* secf init */
	eResult = SDEC_Secf_Clear(stpSdecParam, ui8ch, CLEAR_ALL_MODE);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_Secf_Clear failed:[%d]", eResult);
		goto exit;
	}

	/* get filter number & depth from channel info structure */
	stpLXSdecCap->ucPidFltNr = pSdecConf->chInfo[ui8ch].num_secf;
	stpLXSdecCap->ucSecFltNr = pSdecConf->chInfo[ui8ch].num_pidf;
	stpLXSdecCap->ucFltDepth = pSdecConf->chInfo[ui8ch].flt_dept;

#if 0
		/* copy parameters from user space */
		eRet = copy_to_user((void *)ui32Arg, &stpLXSdecCap, sizeof(LX_SDEC_CAP_T));

		if (eRet)
		{
			SDEC_DEBUG_Print("SDEC_IO_InitialaizeModule Copy to user failed");
			goto exit;
		}
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_InitialaizeModule");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   pid filter clear.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*    ui8PidfIdx :pid idx
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_Pidf_Clear
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8ch,
	UINT32 ui8PidfIdx)
{
	DTV_STATUS_T eRet = NOT_OK;

	UINT8 			ui8Pidf_idx 	= 0x0;
	UINT8 			ui8PidfNum 	= 0x0;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_Pidf_Clear");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	/* get pid filter number from channel info structure */
	ui8PidfNum	= pSdecConf->chInfo[ui8ch].num_pidf;

	/* if channel doesn't have pid filter, return error */
	if( ui8PidfNum == 0 )
	{
		SDEC_DEBUG_Print("this channel doesn't have pid filter !!!!");
		goto exit;
	}

	/* from H13 A0, CDIC2 has 4 pid filters */
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if( pSdecConf->chInfo[ui8ch].capa_lev == 0 )
		{
			if(ui8PidfIdx == CLEAR_ALL_MODE)
			{
				//clear all pid filter
		      	for (ui8Pidf_idx = 0x0; ui8Pidf_idx < ui8PidfNum; ui8Pidf_idx++)
		      	{
		        	SDEC_HAL_CDIC2PIDFSetPidfData(ui8Pidf_idx, 0x1FFF);
				}
			}
		   	else if (ui8PidfIdx < ui8PidfNum )
		   	{
				SDEC_HAL_CDIC2PIDFSetPidfData(ui8PidfIdx, 0x1FFF);
		   	}

			eRet = OK;
			goto exit;
		}
	}
	else
	{
		/* if pid filter is just simple filter, set ts2pes filter only */
		if( pSdecConf->chInfo[ui8ch].capa_lev == 0 )
		{
			/* pidf init */
			SDEC_HAL_SetTs2PesPid(0x1FFF);
			eRet = OK;
			goto exit;
		}
	}

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	if(ui8PidfIdx == CLEAR_ALL_MODE)
	{
		//clear all pid filter
      	for (ui8Pidf_idx = 0x0; ui8Pidf_idx < ui8PidfNum; ui8Pidf_idx++)
      	{
      		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->pidf_addr.pidf_idx = ui8Pidf_idx;
        	//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->pidf_data.pidf_data = 0x1fff0000;
#ifdef NOT_USE_PIDF_SPINLOCK
        	SDEC_HAL_PIDFSetPidfData(ui8ch, ui8Pidf_idx, 0x1FFF0000);
#else
			SDEC_SetPidfData(stpSdecParam, ui8ch, ui8Pidf_idx, 0x1FFF0000);
#endif

			// set secf_map 0x0
			//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_map[ui8Pidf_idx * 2].secf_map= 0x0;
			//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_map[ui8Pidf_idx * 2 + 1].secf_map= 0x0;
			SDEC_HAL_SECFSetMap(ui8ch, ui8Pidf_idx * 2, 0);
			SDEC_HAL_SECFSetMap(ui8ch, ui8Pidf_idx * 2 + 1, 0);
		}
	}
   	else if (ui8PidfIdx < ui8PidfNum )
   	{
	   	//clear only one pid filter
      	//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->pidf_addr.pidf_idx = ui8PidfIdx;
      	//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->pidf_data.pidf_data = 0x1fff0000;
#ifdef NOT_USE_PIDF_SPINLOCK
		SDEC_HAL_PIDFSetPidfData(ui8ch, ui8PidfIdx, 0x1FFF0000);
#else
		SDEC_SetPidfData(stpSdecParam, ui8ch, ui8PidfIdx, 0x1FFF0000);
#endif


		// set secf_map 0x0
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_map[ui8PidfIdx * 2].secf_map = 0x0;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_map[ui8PidfIdx * 2 + 1].secf_map = 0x0;
		SDEC_HAL_SECFSetMap(ui8ch, ui8PidfIdx * 2, 0);
		SDEC_HAL_SECFSetMap(ui8ch, ui8PidfIdx * 2 + 1, 0);
   	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_Pidf_Clear");

	eRet = OK;

exit:

	return (eRet);
}

/**
********************************************************************************
* @brief
*   section filter clear.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8PidfIdx :pid idx
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_Secf_Clear
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8ch,
	UINT32 ui8SecfIdx)
{
	DTV_STATUS_T 	eRet = NOT_OK;
	UINT8			ui8Secf_idx = 0x0, ui8Word_idx = 0x0;
	UINT8 			ui8SecfNum 	= 0x0;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_Secf_Clear");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	/* get section filter number from channel info structure */
	ui8SecfNum	= pSdecConf->chInfo[ui8ch].num_secf;

	/* if channel doesn't have secction filter, return error */
	if( ui8SecfNum == 0 )
	{
		SDEC_DEBUG_Print("this channel doesn't have section filter !!!!");
		eRet = OK;
		goto exit;
	}

	/* if pid filter is just simple filter, set ts2pes filter only */
	if( pSdecConf->chInfo[ui8ch].capa_lev == 0 )
	{
		eRet = OK;
		goto exit;
	}

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	if(ui8SecfIdx == CLEAR_ALL_MODE)
	{
		//clear all section filter
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_en[0].secf_en = 0x0;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_en[1].secf_en = 0x0;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secfb_valid[0].secfb_valid = 0x0;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secfb_valid[1].secfb_valid = 0x0;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_mtype[0].secf_mtype = 0x0;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_mtype[1].secf_mtype = 0x0;
		SDEC_HAL_SECFSetEnable(ui8ch, 0, 0);
		SDEC_HAL_SECFSetEnable(ui8ch, 1, 0);
		SDEC_HAL_SECFSetBufValid(ui8ch, 0, 0);
		SDEC_HAL_SECFSetBufValid(ui8ch, 1, 0);
		SDEC_HAL_SECFSetMapType(ui8ch, 0, 0);
		SDEC_HAL_SECFSetMapType(ui8ch, 1, 0);

		for (ui8Secf_idx = 0x0; ui8Secf_idx < ui8SecfNum; ui8Secf_idx++)
		{

			for (ui8Word_idx = 0x0; ui8Word_idx < 7; ui8Word_idx++)
			{
				//secf_addr.secf_idx = ui8Secf_idx;
				//secf_addr.word_idx = ui8Word_idx;
				//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_addr = secf_addr;
  				//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_data.secf_data = 0xAA000000;
  				SDEC_HAL_SECFSetSecfData(ui8ch, ui8Secf_idx, ui8Word_idx, 0xAA000000);
	  		}
		}

	/* For PES H/W bug workaound. See @LX_SDEC_USE_KTHREAD_PES */
	#if ( LX_SDEC_USE_KTHREAD_PES == 1)
		if(pSdecConf->noPesBug == 0)
		{
			/* if there is pes h/w buf, do it */
			SDEC_PES_AllClearPESFlt(ui8ch);
		}
	#endif

   	}
   	else if ( ui8SecfIdx < ui8SecfNum )
   	{
	   	//clear only one section filter

		//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_en[ui8IsHigh].secf_en, (ui8SecfIdx%32));
		//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secfb_valid[ui8IsHigh].secfb_valid, (ui8SecfIdx % 32));
		SDEC_HAL_SECFClearEnableBit(ui8ch, ui8SecfIdx);
		SDEC_HAL_SECFClearBufValidBit(ui8ch, ui8SecfIdx);
		for (ui8Word_idx = 0x0; ui8Word_idx < 7; ui8Word_idx++)
		{
			//secf_addr.secf_idx = ui8SecfIdx;
			//secf_addr.word_idx = ui8Word_idx;
			//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_addr = secf_addr;
			//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->secf_data.secf_data = 0xAA000000;
			SDEC_HAL_SECFSetSecfData(ui8ch, ui8SecfIdx, ui8Word_idx, 0xAA000000);
		}
	/* For PES H/W bug workaound. See @LX_SDEC_USE_KTHREAD_PES */
#if ( LX_SDEC_USE_KTHREAD_PES == 1)
		if(pSdecConf->noPesBug == 0)
		{
			/* if there is pes h/w buf, do it */
			SDEC_PES_ClearPESFlt(ui8ch, ui8SecfIdx);
		}
#endif
   	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_Secf_Clear");

	eRet = OK;

exit:
	return (eRet);
}

/**
********************************************************************************
* @brief
*   GPB init.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8GpbSize :gpb size
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_Gpb_Init
	(void)
{
	DTV_STATUS_T eRet = NOT_OK;
	UINT8 ui8Ch = 0, ui8Idx = 0;
	UINT32 gpbBaseAddr = 0, gpbBaseAddr_H = 0, gpbBaseAddr_L = 0;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_Gpb_Init");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_CHECK_CODE( pSdecConf == NULL, goto exit, "pSdecConf is NULL" );

	gpbBaseAddr = gMemCfgSDECGPB[pSdecConf->memCfg].gpb_memory_base;
	gpbBaseAddr &= ~GPB_BASE_ADDR_MASK;
	gpbBaseAddr_H = ( gpbBaseAddr >> 16 ) & 0xFFFF;
	gpbBaseAddr_L = ( gpbBaseAddr >> 0  ) & 0xFFFF;

	/* initialize BND & Write & Read pointer Register as base address */
	for ( ui8Ch = 0 ; ui8Ch < 2 ; ui8Ch++ )
	{
		for ( ui8Idx = 0 ; ui8Idx < 64 ; ui8Idx++ )
		{
			SDEC_HAL_GPBSetBnd(ui8Ch, ui8Idx, gpbBaseAddr_H, gpbBaseAddr_L);
			SDEC_HAL_GPBSetReadPtr(ui8Ch, ui8Idx, gpbBaseAddr);
			SDEC_HAL_GPBSetWritePtr(ui8Ch, ui8Idx, gpbBaseAddr);
		}
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_Gpb_Init");

	eRet = OK;

exit:
	return (eRet);
}

DTV_STATUS_T SDEC_GpbSet
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8ch,
	LX_SDEC_GPB_SIZE_T eGpbSize,
	UINT32 ui32GpbBaseAddr,
	UINT32 ui32GpbIdx)
{
	DTV_STATUS_T eRet = NOT_OK;

	GPB_BND stGpbBnd;
	UINT32 ui32Lower_Bound = 0x0, ui32Upper_Bound = 0x0, ui32GpbSize = 0x0;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_GpbSet");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	if( ui8ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8ch);
		goto exit;
	}

	if( ui32GpbIdx >= pSdecConf->chInfo[ui8ch].num_secf )
	{
		SDEC_DEBUG_Print("over GPB range %d", ui32GpbIdx);
		goto exit;
	}

	ui32GpbSize = eGpbSize * 0x1000;

	ui32Lower_Bound = ui32GpbBaseAddr & 0x0FFFF000;
	ui32Upper_Bound = ui32Lower_Bound + ui32GpbSize;

	/* set GPB boudary register */
	stGpbBnd.l_bnd = (ui32Lower_Bound >> 12) & 0x0000FFFF;
	stGpbBnd.u_bnd = (ui32Upper_Bound >> 12) & 0x0000FFFF;

	if(ui8ch < LX_SDEC_CH_C)
	{
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->gpb_bnd[ui32GpbIdx]= stGpbBnd;
		SDEC_HAL_GPBSetBnd(ui8ch, ui32GpbIdx, stGpbBnd.l_bnd, stGpbBnd.u_bnd);

		/* set GPB read & write pointer register */
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->gpb_w_ptr[ui32GpbIdx].gpb_w_ptr =	ui32Lower_Bound;
		//stpSdecParam->stSDEC_MPG_Reg[ui8ch]->gpb_r_ptr[ui32GpbIdx].gpb_r_ptr =	ui32Lower_Bound;
		SDEC_HAL_GPBSetReadPtr(ui8ch, 	ui32GpbIdx, ui32Lower_Bound);
		SDEC_HAL_GPBSetWritePtr(ui8ch, 	ui32GpbIdx, ui32Lower_Bound);

		/* enable full intr */
		SDEC_HAL_GPBSetFullIntr(ui8ch, 	ui32GpbIdx);
	}

	/* initialize base & end pointer */
	stpSdecParam->stSdecMeminfo[ui8ch][ui32GpbIdx].ui32Baseptr 		= ui32GpbBaseAddr;
	stpSdecParam->stSdecMeminfo[ui8ch][ui32GpbIdx].ui32Endptr 		= ui32GpbBaseAddr + ui32GpbSize;
	stpSdecParam->stSdecMeminfo[ui8ch][ui32GpbIdx].ui32Readptr 		= ui32GpbBaseAddr;
	stpSdecParam->stSdecMeminfo[ui8ch][ui32GpbIdx].ui32UsrReadptr	= ui32GpbBaseAddr;
	stpSdecParam->stSdecMeminfo[ui8ch][ui32GpbIdx].stGpbBnd 			= stGpbBnd;

	/* set to channel C section buffer */
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if(ui8ch == LX_SDEC_CH_C)
		{
			SDEC_SWP_SetSectionBuffer(stpSdecParam);
		}
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "l_bnd:[0x%08x]", ui32Lower_Bound);
	SDEC_DTV_SOC_Message( SDEC_NORMAL, "u_bnd:[0x%08x]", ui32Upper_Bound);
	SDEC_DTV_SOC_Message( SDEC_NORMAL, "gpb_w_ptr:[0x%08x]", ui32Lower_Bound);
	SDEC_DTV_SOC_Message( SDEC_NORMAL, "gpb_r_ptr:[0x%08x]", ui32Lower_Bound);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_GpbSet");

	eRet = OK;

exit:
	return (eRet);
}

/**
********************************************************************************
* @brief
*   parameter init.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_Intialize
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;
	DTV_STATUS_T eResult = NOT_OK;

	LX_SDEC_CFG_T* pSdecConf = NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_Intialize");

	//	Reg init
//  2011.11.04 gaius.lee - Moved to HAL
//	eResult = SDEC_RegInit(stpSdecParam);
//	if(LX_IS_ERR(eResult))
//	{
//		SDEC_DEBUG_Print("SDEC_RegInit failed:[%d]", eResult);
//		goto exit;
//	}

	/* initialize HAL api */
	SDEC_HAL_TOPInit();
	SDEC_HAL_IOInit();
	SDEC_HAL_MPGInit();
	SDEC_Gpb_Init();

	//mutex init
	eResult = SDEC_MutexInitialize(stpSdecParam);
	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_MutexInitialize failed:[%d]", eResult);
		goto exit;
	}

#if 1
	//work queue init
	eResult = SDEC_WorkQueueInitialize(stpSdecParam);
	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_WorkQueueInitialize failed:[%d]", eResult);
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "SDEC_WorkQueueInitialize success");
#endif /* #if 0 */


	//spin lock init
	eResult = SDEC_SpinLockInitialize(stpSdecParam);
	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_SpinLockInitialize failed:[%d]", eResult);
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "SDEC_SpinLockInitialize success");

	//wait queue init
	eResult = SDEC_WaitQueueInitialize(stpSdecParam);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_WaitQueueInitialize failed:[%d]", eResult);
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "SDEC_WaitQueueInitialize success");

	/* 20110331 kibeom.kim : add the mask and shift to set the gpb_base_addr (logical address in L9) value */
	/* 20110412 gaius.lee  : modify scheme used with config file. if memory address will be changed someday, we can modified memCfg value */
	pSdecConf = SDEC_CFG_GetConfig();

	SDEC_HAL_SetGPBBaseAddr((gMemCfgSDECGPB[pSdecConf->memCfg].gpb_memory_base & GPB_BASE_ADDR_MASK) >> 28);

	/* pwm reset */
	SDEC_PWM_Init(stpSdecParam);

	//intr src set
	SDEC_HAL_EnableInterrupt( PCR, 				SDEC_HAL_ENABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHA_GPL, 	SDEC_HAL_ENABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHA_GPH, 	SDEC_HAL_ENABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHB_GPL, 	SDEC_HAL_ENABLE );
	SDEC_HAL_EnableInterrupt( GPB_DATA_CHB_GPH, 	SDEC_HAL_ENABLE );

// LJH_GPB
	/* 2012.02.06 gaius.lee
	 * Bug exist in L9 HW.
	 * While CPU access Read/Write/Bound Register, SDEC HW accesses write register, write pointer goes to read/write/bound regitser which CPU access.
	 * So, remove access to read register. That's why we disable full interrupt */
	if(pSdecConf->staticGPB == 0)
	{
		SDEC_HAL_EnableInterrupt( GPB_FULL_CHA_GPL, 	SDEC_HAL_ENABLE );
		SDEC_HAL_EnableInterrupt( GPB_FULL_CHA_GPH, 	SDEC_HAL_ENABLE );
		SDEC_HAL_EnableInterrupt( GPB_FULL_CHB_GPL, 	SDEC_HAL_ENABLE );
		SDEC_HAL_EnableInterrupt( GPB_FULL_CHB_GPH, 	SDEC_HAL_ENABLE );
	}
	SDEC_HAL_EnableInterrupt( TP_INFO_CHA, 		SDEC_HAL_ENABLE );
	SDEC_HAL_EnableInterrupt( TP_INFO_CHB, 		SDEC_HAL_ENABLE );
	SDEC_HAL_EnableInterrupt( ERR_RPT, 			SDEC_HAL_DISABLE );
	SDEC_HAL_EnableInterrupt( TB_DCOUNT, 		SDEC_HAL_ENABLE );

	SDEC_HAL_SDMWCLastBValidMode(0);

	//SDEC_HAL_SetSTCCErrorCtrl(0, 0x1ff, 1);
	//SDEC_HAL_SetSTCCErrorCtrl(1, 0x1ff, 1);
	SDEC_HAL_EnableVideoReady(0, SDEC_HAL_DISABLE);
	SDEC_HAL_EnableVideoReady(1, SDEC_HAL_DISABLE);
	SDEC_HAL_EnableAudioReady(0, SDEC_HAL_DISABLE);
	SDEC_HAL_EnableAudioReady(1, SDEC_HAL_DISABLE);

	/* disable gpb overwrite
	 * do not overwrite even if buffer is overflow */
#if ( LX_SDEC_USE_GPB_OW == 0 )
	SDEC_HAL_ExtConfGPBOverWrite(0, SDEC_HAL_DISABLE);
	SDEC_HAL_ExtConfGPBOverWrite(1, SDEC_HAL_DISABLE);
#endif

	/* Set gpb full level as 256 byte */
	SDEC_HAL_ExtConfGPBFullLevel(0, 1);
	SDEC_HAL_ExtConfGPBFullLevel(1, 1);

	//SDEC_HAL_ConfSetPESReadyCheck(0, 0, SDEC_HAL_ENABLE);
	//SDEC_HAL_ConfSetPESReadyCheck(0, 1, SDEC_HAL_ENABLE);
	SDEC_HAL_ConfSetPESReadyCheck(1, 0, SDEC_HAL_ENABLE);
	SDEC_HAL_ConfSetPESReadyCheck(1, 1, SDEC_HAL_ENABLE);
#if 0
	//valuable init
//	stpSdecParam->ui32MsgMask = 0x01100011;
	stpSdecParam->ui8CurrentCh = 0x0;
	stpSdecParam->ui8CurrentMode = 0x0;
	stpSdecParam->bPcrRecoveryFlag[0] = 0x0;
	stpSdecParam->bPcrRecoveryFlag[1] = 0x0;
#endif /* #if 0 */

	if (lx_chip_rev() < LX_CHIP_REV(H13, A0))
	{
		/* For Teset, DDRC Value change - DDR Access Priority */
		REG_WRITE32(0xc00013cc, 0xf3cf0003);

		/* Memory Gating Disable - N/A in H13 */
		REG_WRITE32(0xc000b020, 0x0000000f);
	}

	/* SDEC SW Parser Init */
	SDEC_SWP_Init(stpSdecParam);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_Intialize");

	eRet = OK;

exit:
	return (eRet);
}

/**
********************************************************************************
* @brief
*   sdec param init.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_ParamInit
	(S_SDEC_PARAM_T *stpSdecParam)
{
	DTV_STATUS_T eRet = NOT_OK;

	UINT8 ui8Count = 0x0;
	UINT8 ui8Countch = 0x0;

	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;
	UINT8			ui8ChNum		= 0;
	UINT8			ui8PidfNum		= 0;
	UINT8			ui8SecfNum		= 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_ParamInit");

#if 0
	//work queue init
	eResult = SDEC_WorkQueueInitialize(stpSdecParam);
	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_WorkQueueInitialize failed:[%d]", eResult);
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "SDEC_WorkQueueInitialize success");
#endif

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	/* get informations from channel info structure */
	ui8ChNum	= pSdecConf->nChannel;

	for(ui8Countch = 0; ui8Countch < ui8ChNum; ui8Countch++)
	{
		/* get pid filter number from channel info structure */
		ui8PidfNum	= pSdecConf->chInfo[ui8Countch].num_pidf;

		/* pid filter map init */
		for(ui8Count = 0; ui8Count < ui8PidfNum; ui8Count++)
		{
			stpSdecParam->stPIDMap[ui8Countch][ui8Count].used = 0x0;
			stpSdecParam->stPIDMap[ui8Countch][ui8Count].flag = FALSE;
			stpSdecParam->stPIDMap[ui8Countch][ui8Count].mode = 0x0;
			stpSdecParam->stPIDMap[ui8Countch][ui8Count].stStatusInfo.w = 0x0;
		}

		/* get pid filter number from channel info structure */
		ui8SecfNum	= pSdecConf->chInfo[ui8Countch].num_secf;
		/* section filter map init */
		for(ui8Count = 0; ui8Count < ui8SecfNum; ui8Count++)
		{
			stpSdecParam->stSecMap[ui8Countch][ui8Count].used = 0x0;
			stpSdecParam->stSecMap[ui8Countch][ui8Count].flag = FALSE;
			stpSdecParam->stSecMap[ui8Countch][ui8Count].mode = 0x0;
			stpSdecParam->stSecMap[ui8Countch][ui8Count].stStatusInfo.w = 0x0;

			stpSdecParam->stSdecMeminfo[ui8Countch][ui8Count].ui32Baseptr = 0x0;
			stpSdecParam->stSdecMeminfo[ui8Countch][ui8Count].ui32Endptr = 0x0;
			stpSdecParam->stSdecMeminfo[ui8Countch][ui8Count].ui32Readptr = 0x0;
			stpSdecParam->stSdecMeminfo[ui8Countch][ui8Count].ui32UsrReadptr = 0x0;
			stpSdecParam->stSdecMeminfo[ui8Countch][ui8Count].ui8PidFltIdx = 0x0;
		}
	}

	//gpbdata structure init
	memset(stpSdecParam->stGPBInfo, 0x0, sizeof(LX_SDEC_NOTIFY_PARAM_T) * LX_SDEC_MAX_GPB_DATA);

	//valuable init
	stpSdecParam->ui8CurrentCh = 0x0;
	stpSdecParam->ui8CurrentMode = 0x0;
	stpSdecParam->bPcrRecoveryFlag[0] = 0x0;
	stpSdecParam->bPcrRecoveryFlag[1] = 0x0;

	stpSdecParam->ui8GpbInfoWIdx = 0x0;
	stpSdecParam->ui8GpbInfoRIdx = 0x0;

	/* set reset mode */
	stpSdecParam->ui8CDICResetMode		= E_SDEC_RESET_MODE_ENABLE;
	stpSdecParam->ui8SDMWCResetMode	= E_SDEC_RESET_MODE_ONETIME;

	/* set reset number as 0 */
	stpSdecParam->ui8CDICResetNum		= 0;
	stpSdecParam->ui8SDMWCResetNum		= 0;

#if 0
	stext_conf = stpSdecParam->stSDEC_MPG_Reg[0]->ext_conf;
	stext_conf.dpkt_vid = 0x0;
	stext_conf.dpkt_dcont = 0x1;
	stext_conf.seci_cce = 0x0;
	stext_conf.seci_dcont = 0x0;
	stpSdecParam->stSDEC_MPG_Reg[0]->ext_conf = stext_conf;
#endif
	SDEC_HAL_ExtConfSECIDcont(0, SDEC_HAL_DISABLE);
	SDEC_HAL_ExtConfSECIDcont(1, SDEC_HAL_DISABLE);

	SDEC_HAL_ExtConfSECICCError(0, SDEC_HAL_DISABLE);
	SDEC_HAL_ExtConfSECICCError(1, SDEC_HAL_DISABLE);

	SDEC_HAL_ExtConfVideoDupPacket(0, SDEC_HAL_DISABLE);
	SDEC_HAL_ExtConfVideoDupPacket(1, SDEC_HAL_DISABLE);

#if 0 
	/* 2013.02.07 Set from enable to disable. All Decoders should process Discontinuity Counter by theirselves
       SarnOff ATSC_02.ts have discontinuity indicator in the first TS packet including PES header of I frame,
       1st part of GOP is decoded unexpectedly (color tone is yellow , expected blue)
       it's requested by VDEC */
	SDEC_HAL_ExtConfDcontDupPacket(0, SDEC_HAL_ENABLE);
	SDEC_HAL_ExtConfDcontDupPacket(1, SDEC_HAL_ENABLE);
#else
	SDEC_HAL_ExtConfDcontDupPacket(0, SDEC_HAL_DISABLE);
	SDEC_HAL_ExtConfDcontDupPacket(1, SDEC_HAL_DISABLE);
#endif

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_ParamInit");

	eRet = OK;

	return (eRet);
}


/**
********************************************************************************
* @brief
*   sdec notify
* @remarks
*  wake up interrupt for signaling to user
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void SDEC_Notify
	(struct work_struct *work)
{
	S_SDEC_PARAM_T *stpSdecParam;

	LX_SDEC_CHECK_CODE( work == NULL, return, "Invalid parameters" );

	stpSdecParam =  container_of (work, S_SDEC_PARAM_T, Notify);

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_Notify");

	stpSdecParam->wq_condition = 1;
	wake_up_interruptible(&stpSdecParam->wq);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_Notify");
}

/**
********************************************************************************
* @brief
*   sdec notify
* @remarks
*  wake up interrupt for signaling to user
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/
BOOLEAN SDEC_SetNotifyParam(S_SDEC_PARAM_T *stpSdecParam, LX_SDEC_NOTIFY_PARAM_T notiParam)
{
	BOOLEAN isFound = FALSE;
	unsigned long flags = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return isFound, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_SetNotifyParam");

	spin_lock_irqsave(&stpSdecParam->stSdecNotiSpinlock, flags);

	/*
	 * overflow check
	 *
	 * case 1 : one more packet, then overflow will happen.
	 *	  ui8GpbInfoWIdx
	 *			V
	 * |---------------------------------------------------------|
	 *			 ^
	 *	  ui8GpbInfoRIdx
	 *
	 * case 2 : read pointer is 0, write pointer is ( LX_SDEC_MAX_GPB_DATA - 1 ).
	 *		  if there is one more packet, write pointer is wrapped around and same with read pointer.
	 *												   ui8GpbInfoWIdx
	 *															 V
	 * |---------------------------------------------------------|
	 * ^
	 * ui8GpbInfoRIdx
	 */

	/* stored buf info	*/
	stpSdecParam->stGPBInfo[stpSdecParam->ui8GpbInfoWIdx] = notiParam;

	/* increase write pointer */
	stpSdecParam->ui8GpbInfoWIdx = (stpSdecParam->ui8GpbInfoWIdx + 1) % LX_SDEC_MAX_GPB_DATA;

	if( ( stpSdecParam->ui8GpbInfoRIdx - stpSdecParam->ui8GpbInfoWIdx) != 1 &&							// case 1.
		( stpSdecParam->ui8GpbInfoWIdx - stpSdecParam->ui8GpbInfoRIdx) != ( LX_SDEC_MAX_GPB_DATA - 1 )	// case 2.
		)
	{
		/* buffer is not full */

		/* set found flag */
		isFound = TRUE;
	}
	else
	{
		/* buffer is full, reset to 0 */
		stpSdecParam->ui8GpbInfoRIdx = 0;
		stpSdecParam->ui8GpbInfoWIdx = 0;
		SDEC_DEBUG_Print( "Krdv->User Msg Queue is full");
	}

	spin_unlock_irqrestore(&stpSdecParam->stSdecNotiSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_SetNotifyParam");

	return isFound;
}

/**
********************************************************************************
* @brief
*   Check overflowed msg in msg queue from kdrv -> user level
* @remarks
*  check if this section or pes data is overflowed by overflow, and if, remove.
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/
#if ( LX_SDEC_USE_GPB_OW == 1 )
void SDEC_CheckNotifyOvf(S_SDEC_PARAM_T *stpSdecParam, LX_SDEC_NOTIFY_PARAM_T *pNotiParam)
{
	unsigned long 	flags = 0;
	UINT8			ui8GpbInfoRIdx = 0, ui8GpbInfoWIdx = 0, ui8Ch = 0, ui8Idx = 0;
	UINT8			ui8DeleteMargin = 0xff;
	UINT32			rdPtr = 0, wrPtr = 0, bfStr = 0, bfEnd = 0;
	UINT32			urPtr = 0;				/* user read pointer */
	UINT32			cwPtr = 0;				/* current write pointer */
	SINT32			si32DataSize = 0;		/* size to delete */
	SINT32			si32SectionSize = 0;	/* size of a section */

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return , "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_CheckNotifyOvf");

	spin_lock_irqsave(&stpSdecParam->stSdecNotiSpinlock, flags);

	ui8Ch			= pNotiParam->channel;
	ui8Idx			= pNotiParam->index;

	ui8GpbInfoRIdx 	= stpSdecParam->ui8GpbInfoRIdx;
	ui8GpbInfoWIdx 	= stpSdecParam->ui8GpbInfoWIdx;

	bfStr			= stpSdecParam->stSdecMeminfo[ui8Ch][ui8Idx].ui32Baseptr;
	bfEnd			= stpSdecParam->stSdecMeminfo[ui8Ch][ui8Idx].ui32Endptr;

	SDEC_DTV_SOC_Message(SDEC_PIDSEC, "SDEC_CheckNotifyOvf : CH%d[%d] e[%08x]\n",
				pNotiParam->channel,
				ui8Idx,
				pNotiParam->writePtr);

	/* while loop */
	while( ui8GpbInfoRIdx != ui8GpbInfoWIdx )
	{
		if( stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].channel == ui8Ch &&
			stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].index == ui8Idx &&
			stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].status & LX_SDEC_FLTSTATE_DATAREADY)
		{
			if(ui8Ch == LX_SDEC_CH_C)
			{
				stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].status = LX_SDEC_FLTSTATE_DELETED;

				/* increase user read pointer to section write pointer */
				stpSdecParam->stSdecMeminfo[ui8Ch][ui8Idx].ui32UsrReadptr = wrPtr;

				/* increase read pointer */
				ui8GpbInfoRIdx = (ui8GpbInfoRIdx + 1) % LX_SDEC_MAX_GPB_DATA;
				continue;
			}

			/* get section read pointer */
			rdPtr = stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].readPtr;
			/* get section write pointer */
			wrPtr = stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].writePtr;
			/* get user read pointer. this means real read pointer of user */
			//urPtr = SDEC_HAL_GPBGetReadPtr(ui8Ch, ui8Idx) 	| (bfStr & GPB_BASE_ADDR_MASK);
			urPtr = stpSdecParam->stSdecMeminfo[ui8Ch][ui8Idx].ui32UsrReadptr | (bfStr & GPB_BASE_ADDR_MASK);
			/* get current real-time write pointer */
			cwPtr = SDEC_HAL_GPBGetWritePtr(ui8Ch, ui8Idx) 	| (bfStr & GPB_BASE_ADDR_MASK);

			/* 1. calculate size to delete */
			if( ui8DeleteMargin == 0xff )
			{
				stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].status = LX_SDEC_FLTSTATE_DELETED;

				if( rdPtr <= cwPtr && cwPtr < wrPtr )
				{

					/* case 1. normal 1 ( probably in SDEC_Section_Proc(). But occasually in SDEC_Full_Proc() )
					 *
					 *             rdPtr      wrPtr
					 *              V          V
					 * |---------------------------------------------------------|
					 *                  ^
					 *	              cwPtr
					 */
					/* 정상적으로 current write pointer가 중간에 있다. */
					LX_MEMSIZE(si32DataSize, 		rdPtr, cwPtr, bfStr, bfEnd);
					LX_MEMSIZE(si32SectionSize, 	cwPtr, wrPtr, bfStr, bfEnd);
					ui8DeleteMargin = 2;
				}
				else if( rdPtr < cwPtr && wrPtr < cwPtr )
				{

					/* case 2. normal 2 ( probably in SDEC_Full_Proc() )
					 *
					 *             rdPtr      wrPtr
					 *              V          V
					 * |---------------------------------------------------------|
					 *                           ^
					 *	                       cwPtr
					 */
					/* current write pointer가 이 Table을 지나 있다. ( 많이 빠르므로 3개 정도 앞서서 삭제 )*/
					LX_MEMSIZE(si32DataSize, 		rdPtr, cwPtr, bfStr, bfEnd);
					LX_MEMSIZE(si32SectionSize, 	rdPtr, wrPtr, bfStr, bfEnd);
					ui8DeleteMargin = 3;
				}
				else
				{
					/* case 3. sometimes ( probably in SDEC_Full_Proc() )
					 *
					 *             rdPtr      wrPtr
					 *              V          V
					 * |---------------------------------------------------------|
					 *             ^
					 *	         cwPtr
					 */
					/* GPB_F_INTR 에서 가끔 이렇게 먼저 뜰 때가 있다. 이럴경우 그냥 앞에 있는 애들만 지워도 됨. */
					LX_MEMSIZE(si32DataSize, 		rdPtr, wrPtr, bfStr, bfEnd);
					LX_MEMSIZE(si32SectionSize, 	rdPtr, wrPtr, bfStr, bfEnd);
					ui8DeleteMargin = 1;
				}

				SDEC_DTV_SOC_Message(SDEC_PIDSEC, "DS[%d] SS[%d] rp[%08x] wp[%08x] cw[%08x] ur[%08x] m[%d]\n",
					si32DataSize,
					si32SectionSize,
					rdPtr,
					wrPtr,
					pNotiParam->writePtr,
					urPtr,
					ui8DeleteMargin
					);

				/* decrease data size as section size */
				si32DataSize -= si32SectionSize;
				/* increase user read pointer to section write pointer */
				//SDEC_HAL_GPBSetReadPtr(ui8Ch, ui8Idx, wrPtr);
				stpSdecParam->stSdecMeminfo[ui8Ch][ui8Idx].ui32UsrReadptr = wrPtr;
			}
			/* 2. Delete while size is not under zero, or margin is not zero. */
			else if(si32DataSize > 0 || ui8DeleteMargin)
			{
				SDEC_DTV_SOC_Message(SDEC_PIDSEC,"[%d] [%d]\n", si32DataSize, ui8DeleteMargin);

				stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].status = LX_SDEC_FLTSTATE_DELETED;

				/* increase user read pointer to section write pointer */
				//SDEC_HAL_GPBSetReadPtr(ui8Ch, ui8Idx, wrPtr);
				stpSdecParam->stSdecMeminfo[ui8Ch][ui8Idx].ui32UsrReadptr = wrPtr;

				/* calculate section size */
				LX_MEMSIZE(si32SectionSize, rdPtr, wrPtr, bfStr, bfEnd);

				/* decrease data size as section size */
				si32DataSize -= si32SectionSize;

				/* if data size is under zero, delete more packet as margin. Sometimes data speed is too fast. */
				if(si32DataSize < 0) ui8DeleteMargin--;
			}
			else
			{
				break;
			}
		}

		/* increase read pointer */
		ui8GpbInfoRIdx = (ui8GpbInfoRIdx + 1) % LX_SDEC_MAX_GPB_DATA;
	}

	spin_unlock_irqrestore(&stpSdecParam->stSdecNotiSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_CheckNotifyOvf");
}
#endif

/**
********************************************************************************
* @brief
*   sdec notify
* @remarks
*  wake up interrupt for signaling to user
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void SDEC_DeleteInNotify(S_SDEC_PARAM_T *stpSdecParam, UINT8 ui8Ch, UINT8 ui32SecFltId)
{
	UINT8	ui8GpbInfoRIdx = 0, ui8GpbInfoWIdx;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return , "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_CheckNotify");

	spin_lock(&stpSdecParam->stSdecNotiSpinlock);

	ui8GpbInfoRIdx 	= stpSdecParam->ui8GpbInfoRIdx;
	ui8GpbInfoWIdx 	= stpSdecParam->ui8GpbInfoWIdx;

	//printk("%s : CH%d[%d]\n", __FUNCTION__, ui8Ch, ui32SecFltId );

	/* while loop */
	while( ui8GpbInfoRIdx != ui8GpbInfoWIdx )
	{
		if( stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].channel == ui8Ch &&
			stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].index == ui32SecFltId &&
			stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].status & LX_SDEC_FLTSTATE_DATAREADY)
		{
			stpSdecParam->stGPBInfo[ui8GpbInfoRIdx].status = LX_SDEC_FLTSTATE_DELETED;

			printk("CH%d[%d] DELETE R[%d] W[%d]\n", ui8Ch, ui32SecFltId, ui8GpbInfoRIdx, ui8GpbInfoWIdx );
		}

		/* increase read pointer */
		ui8GpbInfoRIdx = (ui8GpbInfoRIdx + 1) % LX_SDEC_MAX_GPB_DATA;
	}

	//printk("%s : END\n", __FUNCTION__ );

	spin_unlock(&stpSdecParam->stSdecNotiSpinlock);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_CheckNotify");
}

/**
********************************************************************************
* @brief
*   sdec TPI register set
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8Ch :channel
*   stpSdecParam :SDEC parameter
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

DTV_STATUS_T SDEC_TPI_Set
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_TPI_Set");

#if 0
	//TP scramble check enable
	//mp = (UINT32)&stpSdecParam->stSDEC_MPG_Reg[0]->tpi_iconf;
	astTPIIConf = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->tpi_iconf;

	//TPI_ICONF Reg set
	// gaius.lee 2010.10.26
	// Setting interrupt as payload unit start indicator bit is 1.
	// This means we want to check every PES packet for scramble status checking. This is for speed.
//	astTPIIConf.tei 			= 0x1;
//	astTPIIConf.afef 			= 0x1;
//	astTPIIConf.tpdf 			= 0x1;
//	astTPIIConf.spf 			= 0x1;
//	astTPIIConf.espi			= 0x1;
//	astTPIIConf.rai 			= 0x1;
//	astTPIIConf.di 				= 0x1;
//	astTPIIConf.tsc 			= 0x0;
//	astTPIIConf.tpri 			= 0x1;
	astTPIIConf.pusi 			= 0x1;
//	astTPIIConf.tei 			= 0x1;
//	astTPIIConf.not_tsc         = 0x1;
	astTPIIConf.auto_sc_chk 	= 0x0;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->tpi_iconf = astTPIIConf;
#endif
	//TPI_ICONF Reg set
	// gaius.lee 2010.10.26
	// Setting interrupt as payload unit start indicator bit is 1.
	// This means we want to check every PES packet for scramble status checking. This is for speed.
	SDEC_HAL_TPISetIntrPayloadUnitStartIndicator(ui8Ch, SDEC_HAL_ENABLE);
	SDEC_HAL_TPISetIntrAutoScCheck(ui8Ch, SDEC_HAL_DISABLE);


	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_TPI_Set");

	eRet = OK;

	return (eRet);
}


/**
********************************************************************************
* @brief
*   sdec TPI_IEN in PIDF_DATA register set
* @remarks
*   DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   ui8Ch :channel
*   ui8PIDIdx : PID filter index
*   val : PIDF_DATA value
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

int SDEC_SetPidfData
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch,
	UINT8 ui8PIDIdx,
	UINT32 val
	)
{
	int ret = RET_ERROR;
	unsigned long 		flags = 0;

	spin_lock_irqsave(&stpSdecParam->stSdecPidfSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_NORMAL,"Set PIDF_DATA ch[%d]idx[%d][0x%x]", ui8Ch, ui8PIDIdx, val);
	ret = SDEC_HAL_PIDFSetPidfData(ui8Ch, ui8PIDIdx, val);

	spin_unlock_irqrestore(&stpSdecParam->stSdecPidfSpinlock, flags);

	return ret;

}


/**
********************************************************************************
* @brief
*   sdec TPI_IEN in PIDF_DATA register get
* @remarks
*   DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   ui8Ch :channel
*   ui8PIDIdx : PID filter index
*   work_struct
* @return
*  PIDF_DATA value
********************************************************************************
*/

UINT32 SDEC_GetPidfData
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch,
	UINT8 ui8PIDIdx
	)
{
	UINT32 ret_value = 0;
	unsigned long 		flags = 0;

	spin_lock_irqsave(&stpSdecParam->stSdecPidfSpinlock, flags);

	ret_value = SDEC_HAL_PIDFGetPidfData(ui8Ch, ui8PIDIdx);
	SDEC_DTV_SOC_Message( SDEC_NORMAL,"Get PIDF_DATA ch[%d]idx[%d][0x%x]", ui8Ch, ui8PIDIdx, ret_value);

	spin_unlock_irqrestore(&stpSdecParam->stSdecPidfSpinlock, flags);

	return ret_value;
}


/**
********************************************************************************
* @brief
*   sdec PIDF enable
* @remarks
*   DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   ui8Ch :channel
*   ui8PIDIdx : PID filter index
*   en : enable/disable
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

int SDEC_SetPidf_Enable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch,
	UINT8 ui8PIDIdx,
	UINT8 en
	)
{
	int ret = RET_ERROR;
	unsigned long 		flags = 0;

	spin_lock_irqsave(&stpSdecParam->stSdecPidfSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_NORMAL,"PIDF_EN ch[%d]idx[%d][%d]", ui8Ch, ui8PIDIdx, en);
	ret = SDEC_HAL_PIDFEnable(ui8Ch, ui8PIDIdx, en);

	spin_unlock_irqrestore(&stpSdecParam->stSdecPidfSpinlock, flags);

	return ret;
}


/**
********************************************************************************
* @brief
*   sdec TPI_IEN in PIDF_DATA register set
* @remarks
*   DETAIL INFORMATION
*   Added by jinhwan.bae, 2012.04.26, No Audio at long time aging test with US/Cable
*   US/Cable Check Scramble Status periodically, Scramble Check is used pusi interrupt -> check tsc
*   Process Context : start scramble check -> write TPI_IEN in Audio PIDF_DATA
*   Interrupt Context : Video pusi interrupt -> check tsc -> disable scramble check (since H/W Bug) -> write TPI_IEN in Video PIDF_DATA
*   If interrupt context write TPI_IEN during process context stopped just after writing PIDF_INDEX,
*   PIDF_DATA in process context after interrupt context operation is changed to Video PIDF_DATA,
*   so Video PIDF_DATA | TPI_IEN will be writen to Audio PIDF_DATA
*   all added pidf spin lock codes are related to this
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   ui8Ch :channel
*   ui8PIDIdx : PID filter index
*   en : Enable or Disable
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

int SDEC_SetPidf_TPI_IEN_Enable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch,
	UINT8 ui8PIDIdx,
	UINT8 en
	)
{
	int ret = RET_ERROR;
	unsigned long 		flags = 0;

	spin_lock_irqsave(&stpSdecParam->stSdecPidfSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_NORMAL,"TPI_IEN idx[%d][%d][%d]", ui8Ch, ui8PIDIdx, en);
	ret = SDEC_HAL_PIDFScrambleCheck(ui8Ch, ui8PIDIdx, en);

	spin_unlock_irqrestore(&stpSdecParam->stSdecPidfSpinlock, flags);

	return ret;
}


/**
********************************************************************************
* @brief
*   sdec PIDF Descrambler enable
* @remarks
*   DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   ui8Ch :channel
*   ui8PIDIdx : PID filter index
*   en : enable/disable
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

int SDEC_SetPidf_Disc_Enable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch,
	UINT8 ui8PIDIdx,
	UINT8 en
	)
{
	int ret = RET_ERROR;
	unsigned long 		flags = 0;

	spin_lock_irqsave(&stpSdecParam->stSdecPidfSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_NORMAL,"PIDF_DESC_EN ch[%d]idx[%d][%d]", ui8Ch, ui8PIDIdx, en);
	ret = SDEC_HAL_PIDFDescEnable(ui8Ch, ui8PIDIdx, en);

	spin_unlock_irqrestore(&stpSdecParam->stSdecPidfSpinlock, flags);

	return ret;
}


/**
********************************************************************************
* @brief
*   sdec PIDF Download enable
* @remarks
*   DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
*   ui8Ch :channel
*   ui8PIDIdx : PID filter index
*   en : enable/disable
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

int SDEC_SetPidf_DN_Enable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch,
	UINT8 ui8PIDIdx,
	UINT8 en
	)
{
	int ret = RET_ERROR;
	unsigned long 		flags = 0;

	spin_lock_irqsave(&stpSdecParam->stSdecPidfSpinlock, flags);

	SDEC_DTV_SOC_Message( SDEC_NORMAL,"PIDF_DN_EN ch[%d]idx[%d][%d]", ui8Ch, ui8PIDIdx, en);
	ret = SDEC_HAL_PIDFDownloadEnable(ui8Ch, ui8PIDIdx, en);

	spin_unlock_irqrestore(&stpSdecParam->stSdecPidfSpinlock, flags);

	return ret;
}



/**
********************************************************************************
* @brief
*   sdec Err interrrupt register set
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8Ch :channel
*   stpSdecParam :SDEC parameter
*   work_struct
* @return
*  DTV_STATUS_T
********************************************************************************
*/

DTV_STATUS_T SDEC_ERR_Intr_Set
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8Ch)
{
	DTV_STATUS_T eRet = NOT_OK;

	//ERR_INTR_EN stErrIntrEn;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_ERR_Intr_Set");

#if 0
	stErrIntrEn = stpSdecParam->stSDEC_IO_Reg->err_intr_en;

	stErrIntrEn.test_dcont 	= 0x1;
	stErrIntrEn.sync_lost 	= 0x3;
	stErrIntrEn.sb_dropped  = 0x3;
	stErrIntrEn.cdif_ovflow = 0x3;
	stErrIntrEn.cdif_wpage  = 0x3;
	stErrIntrEn.cdif_rpage 	= 0x3;
	stErrIntrEn.stcc_dcont 	= 0x3;
	stErrIntrEn.mpg_pd  	= 0x3;
	stErrIntrEn.mpg_ts 		= 0x3;
	stErrIntrEn.mpg_dup 	= 0x3;
	stErrIntrEn.mpg_cc  	= 0x3;
	stErrIntrEn.mpg_sd  	= 0x3;

	stpSdecParam->stSDEC_IO_Reg->err_intr_en = stErrIntrEn;
#endif

	SDEC_HAL_EnableErrorInterrupt(MPG_SD, 		0x3);
	SDEC_HAL_EnableErrorInterrupt(MPG_CC, 		0x3);
	SDEC_HAL_EnableErrorInterrupt(MPG_DUP, 		0x3);
	SDEC_HAL_EnableErrorInterrupt(MPG_TS, 		0x3);
	SDEC_HAL_EnableErrorInterrupt(MPG_PD, 		0x3);
	SDEC_HAL_EnableErrorInterrupt(STCC_DCONT, 	0x3);
	SDEC_HAL_EnableErrorInterrupt(CDIF_RPAGE, 	0x3);
	SDEC_HAL_EnableErrorInterrupt(CDIF_WPAGE, 	0x3);
	SDEC_HAL_EnableErrorInterrupt(CDIF_OVFLOW, 	0x3);
	SDEC_HAL_EnableErrorInterrupt(SB_DROPPED, 	0x3);
	SDEC_HAL_EnableErrorInterrupt(SYNC_LOST, 	0x3);
	SDEC_HAL_EnableErrorInterrupt(TEST_DCONT, 	0x1);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_ERR_Intr_Set");

	eRet = OK;

	return (eRet);
}

/**
********************************************************************************
* @brief
*   get Chip Configuration
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetChipCfg
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_CHIP_CFG_T *stpLXSdecGetChipCfg;
	LX_SDEC_CFG_T* pSdecConf = NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetChipCfg");

	/* get config */
	pSdecConf = SDEC_CFG_GetConfig();

	stpLXSdecGetChipCfg = (LX_SDEC_CHIP_CFG_T *)ui32Arg;

	stpLXSdecGetChipCfg->chip_rev 		= pSdecConf->chip_rev;
	stpLXSdecGetChipCfg->nChannel 		= pSdecConf->nChannel;
	stpLXSdecGetChipCfg->nVdecOutPort 	= pSdecConf->nVdecOutPort;
	stpLXSdecGetChipCfg->noPesBug 		= pSdecConf->noPesBug;
	stpLXSdecGetChipCfg->staticGPB 		= pSdecConf->staticGPB;

#if 0
	/* copy parameters to user space */
	eResult = copy_to_user((void *)ui32Arg,&stpLXSdecGetSTCPCR,sizeof(LX_SDEC_GET_STC_PCR_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("SDEC_IO_GetCurrentSTC Copy touser failed");
		goto exit;
	}
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetChipCfg");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   get the current STC ASG value.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetSTCCStatus
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_GET_STCC_STATUS_T *stpLXSdecGetSTCCStatus;
	LX_SDEC_STCC_STATUS_T *p;

	UINT8 	ui8Ch = 0x0;
	UINT32 	uiSTCCRegValue_32b = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetSTCCStatus");

	stpLXSdecGetSTCCStatus = (LX_SDEC_GET_STCC_STATUS_T *)ui32Arg;
	ui8Ch = stpLXSdecGetSTCCStatus->eCh;

	uiSTCCRegValue_32b = SDEC_HAL_STCCGetReg(ui8Ch);

	p = &(stpLXSdecGetSTCCStatus->stcc_status);
	p->bEn 			= ( (uiSTCCRegValue_32b & 0x80000000) >> 31 );
	p->ui8Chan 		= ( (uiSTCCRegValue_32b & 0x20000000) >> 29 );
	p->ui16Pcr_Pid 	= ( (uiSTCCRegValue_32b & 0x1fff0000) >> 16 );
	p->bRd_Mode		= ( (uiSTCCRegValue_32b & 0x00000100) >> 8 );
	p->bRate_Ctrl 	= ( (uiSTCCRegValue_32b & 0x00000010) >> 4 );
	p->bCopy_En 	= ( (uiSTCCRegValue_32b & 0x00000002) >> 1 );
	p->bLatch_En 	= ( (uiSTCCRegValue_32b & 0x00000001) );

#if 0
	printk("\n\n\n\n\n STCC STATUS [%x] [%d][%d][%x][%d][%d][%d][%d] \n\n\n\n\n",
		uiSTCCRegValue_32b,p->bEn, p->ui8Chan, p->ui16Pcr_Pid, p->bRd_Mode, p->bRate_Ctrl, p->bCopy_En, p->bLatch_En); 
#endif

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetSTCCStatus");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}



/**
********************************************************************************
* @brief
*   get the current STC ASG value.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetSTCCASGStatus
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_GET_STCCASG_T *stpLXSdecGetSTCCASG;

	UINT32 ui32ASGRegValue = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetSTCCASGStatus");

	stpLXSdecGetSTCCASG = (LX_SDEC_GET_STCCASG_T *)ui32Arg;

	// stpLXSdecGetSTCCASG->ui8Main = SDEC_HAL_STCCGetMain();
	ui32ASGRegValue = SDEC_HAL_STCCGetASG();

	stpLXSdecGetSTCCASG->ui8Main = (ui32ASGRegValue & 0x01);
	stpLXSdecGetSTCCASG->ui8Aud1 = ((ui32ASGRegValue & 0x80000) >> 19);
	stpLXSdecGetSTCCASG->ui8Aud0 = ((ui32ASGRegValue & 0x40000) >> 18);
	stpLXSdecGetSTCCASG->ui8Vid1 = ((ui32ASGRegValue & 0x20000) >> 17);
	stpLXSdecGetSTCCASG->ui8Vid0 = ((ui32ASGRegValue & 0x10000) >> 16);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetSTCCASGStatus");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   set the current STC ASG value.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetSTCCASGStatus
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_GET_STCCASG_T *stpLXSdecSetSTCCASG;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetSTCCASGStatus");

	stpLXSdecSetSTCCASG = (LX_SDEC_GET_STCCASG_T *)ui32Arg;

	/* At this time, only implemented to assign main PCR Channel , Later all fields will be added */
	SDEC_HAL_STCCSetMain(stpLXSdecSetSTCCASG->ui8Main);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetSTCCASGStatus");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}



/**
********************************************************************************
* @brief
*   get the current STC value.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetCurrentSTCPCR
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_GET_STC_PCR_T *stpLXSdecGetSTCPCR;

	UINT8 ui8Ch = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetCurrentSTC");

	stpLXSdecGetSTCPCR = (LX_SDEC_GET_STC_PCR_T *)ui32Arg;

	//ui8Ch = SDEC_HAL_STCCGetMain();
	ui8Ch = stpLXSdecGetSTCPCR->eCh;

	//stpLXSdecGetSTCPCR->uiStc_hi = stpSdecParam->stSDEC_IO_Reg->stcc[ui8Ch*4 +1];
	//stpLXSdecGetSTCPCR->uiStc_lo = extract_bits(stpSdecParam->stSDEC_IO_Reg->stcc[ui8Ch*4 +3], 0x3FF, 16);

	//stpLXSdecGetSTCPCR->uiPcr_hi = stpSdecParam->stSDEC_IO_Reg->stcc[ui8Ch*4 +2];
	//stpLXSdecGetSTCPCR->uiPcr_lo = extract_bits(stpSdecParam->stSDEC_IO_Reg->stcc[ui8Ch*4 +3], 0x3FF, 0);

	stpLXSdecGetSTCPCR->uiStc_hi = SDEC_HAL_STCCGetSTC(ui8Ch, 1);
	stpLXSdecGetSTCPCR->uiStc_lo = SDEC_HAL_STCCGetSTC(ui8Ch, 0);

	stpLXSdecGetSTCPCR->uiPcr_hi = SDEC_HAL_STCCGetPCR(ui8Ch, 1);
	stpLXSdecGetSTCPCR->uiPcr_lo = SDEC_HAL_STCCGetPCR(ui8Ch, 0);

//	SDEC_DTV_SOC_Message( SDEC_NORMAL, "Ch[%d] STC_hi value:[0x%08x]", ui8Ch, stpLXSdecGetSTCPCR->uiStc_hi);
//	SDEC_DTV_SOC_Message( SDEC_NORMAL, "Ch[%d] STC_lo value:[0x%08x]", ui8Ch, stpLXSdecGetSTCPCR->uiStc_lo);
//	SDEC_DTV_SOC_Message( SDEC_NORMAL, "Ch[%d] PCR_hi value:[0x%08x]", ui8Ch, stpLXSdecGetSTCPCR->uiStc_hi);
//	SDEC_DTV_SOC_Message( SDEC_NORMAL, "Ch[%d] PCR_lo value:[0x%08x]", ui8Ch, stpLXSdecGetSTCPCR->uiStc_lo);

	//stpLXSdecGetSTC->eCh

#if 0
	/* copy parameters to user space */
	eResult = copy_to_user((void *)ui32Arg,&stpLXSdecGetSTCPCR,sizeof(LX_SDEC_GET_STC_PCR_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("SDEC_IO_GetCurrentSTC Copy touser failed");
		goto exit;
	}
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetCurrentSTC");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   get the current PCR, STC value. Only For Debugging
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   	unsigned long *pcr
*	unsigned long *stc
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_GetCurrentSTCPCR
	(unsigned long *pcr,
	unsigned long *stc)
{
	DTV_STATUS_T eRet = NOT_OK;
	UINT8 ui8Ch = 0x0;
	UINT32 uiStc_hi = 0, uiStc_lo = 0;
	UINT32 uiPcr_hi = 0, uiPcr_lo = 0;

	LX_SDEC_CHECK_CODE( pcr == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( pcr == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_GetCurrentSTCPCR");

	uiStc_hi = SDEC_HAL_STCCGetSTC(ui8Ch, 1);
	uiStc_lo = SDEC_HAL_STCCGetSTC(ui8Ch, 0);
	uiStc_hi = ((uiStc_hi << 1 ) & 0xFFFFFFFF);
	uiStc_lo = ((uiStc_lo >> 9 ) & 0x1);
	(*stc) = (uiStc_hi | uiStc_lo);

	uiPcr_hi = SDEC_HAL_STCCGetPCR(ui8Ch, 1);
	uiPcr_lo = SDEC_HAL_STCCGetPCR(ui8Ch, 0);
	uiPcr_hi = ((uiPcr_hi << 1 ) & 0xFFFFFFFF);
	uiPcr_lo = ((uiPcr_lo >> 9 ) & 0x1);
	(*pcr) = (uiPcr_hi | uiPcr_lo);
	
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_GetCurrentSTCPCR");

	eRet = OK;

	return (eRet);
}
EXPORT_SYMBOL(SDEC_GetCurrentSTCPCR);



/**
********************************************************************************
* @brief
*   get the current GSTC value.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   	unsigned long *pcr
*	unsigned long *stc
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetCurrentGSTC
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	UINT32			gstc_sdec[2] = { 0, 0 };
	LX_SDEC_GET_GSTC_T *stpLXSdecGetGSTC;

	OS_LockMutex(&stpSdecParam->stSdecMutex);
	
	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetCurrentGSTC");

	stpLXSdecGetGSTC = (LX_SDEC_GET_GSTC_T *)ui32Arg;

	SDEC_HAL_GSTC(&gstc_sdec[0], &gstc_sdec[1]);

	stpLXSdecGetGSTC->gstc_32_1 	= gstc_sdec[0];
	stpLXSdecGetGSTC->gstc_0 		= gstc_sdec[1];
	
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetCurrentGSTC");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   select input port.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SelInputPort
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	UINT8 ui8Ch = 0x0;

	LX_SDEC_SEL_INPUT_T *stpLXSdecSelPort;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SelInputPort");

	stpLXSdecSelPort = (LX_SDEC_SEL_INPUT_T *)ui32Arg;

	ui8Ch = stpLXSdecSelPort->eCh;

	eResult = SDEC_InputSet(stpSdecParam, stpLXSdecSelPort);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_InputSet failed:[%d]", eResult);
	}

	//error intr register setting
	eResult = SDEC_ERR_Intr_Set(stpSdecParam, ui8Ch);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_InputSet failed:[%d]", eResult);
	}

	/* There is no tpi_conf in Channel C */
	if(ui8Ch >= LX_SDEC_CH_C)	goto exit_without_error;

	//TPI setting
	/*caution
	should set after input port set. Because if u set this register before input port set, and that register all bit clear
	*/
	eResult = SDEC_TPI_Set(stpSdecParam, ui8Ch);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_InputSet failed:[%d]", eResult);
	}

exit_without_error:
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SelInputPort");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   select input port.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_CfgInputPort
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CFG_INPUT_T *stpLXSdecCfgPort;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_CfgInputPort");

	stpLXSdecCfgPort = (LX_SDEC_CFG_INPUT_T *)ui32Arg;

	switch (stpLXSdecCfgPort->eInputPort)
	{
		case LX_SDEC_INPUT_PARALLEL0:
			SDEC_DTV_SOC_Message( SDEC_IO, "PARALLEL0");

			SDEC_HAL_CDIP(0, stpLXSdecCfgPort);
			SDEC_HAL_CDIP(1, NULL);
			SDEC_HAL_CDIP(2, NULL);
			break;

		case LX_SDEC_INPUT_PARALLEL1:
			SDEC_DTV_SOC_Message( SDEC_IO, "PARALLEL1");

			/* L9A0 / L9A1 */
			if (lx_chip_rev() < LX_CHIP_REV(L9, B0))
			{
				SDEC_HAL_CDIP(0, stpLXSdecCfgPort);
				SDEC_HAL_CDIP(1, NULL);
				SDEC_HAL_CDIP(2, NULL);
			}
			/* L9B0 */
			else
			{
				SDEC_HAL_CDIPA(0, stpLXSdecCfgPort);
				SDEC_HAL_CDIPA(1, NULL);
				SDEC_HAL_CDIPA(2, NULL);
			}
			break;

		case LX_SDEC_INPUT_SERIAL0:
			SDEC_DTV_SOC_Message( SDEC_IO, "SERIAL0");

#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CDIP(0, stpLXSdecCfgPort);
			SDEC_HAL_CDIP(1, NULL);
			SDEC_HAL_CDIP(2, NULL);
#else
			SDEC_HAL_CDIP(3, stpLXSdecCfgPort);
#endif
			break;
		case LX_SDEC_INPUT_SERIAL1:
			SDEC_DTV_SOC_Message( SDEC_IO, "SERIAL1");

#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CDIPA(0, stpLXSdecCfgPort);
			SDEC_HAL_CDIPA(1, NULL);
			SDEC_HAL_CDIPA(2, NULL);
#else
			SDEC_HAL_CDIOP(0, stpLXSdecCfgPort);
#endif
			break;
		case LX_SDEC_INPUT_SERIAL2:

#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			/* CDIN3 characteristic is set to CDIP[3] */
			SDEC_HAL_CDIP(3, stpLXSdecCfgPort);
#else
			/* temp source for supporting KR Sub Tuner in CDINA , should fix again ! - jinhwan.bae 0809 */
			SDEC_DTV_SOC_Message( SDEC_IO, "SERIAL2");

			SDEC_HAL_CDIPA(0, stpLXSdecCfgPort);
			SDEC_HAL_CDIPA(1, NULL);
			SDEC_HAL_CDIPA(2, NULL);
#endif
			break;
		case LX_SDEC_INPUT_SERIAL3:

#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			/* CDIN4 characteristic is set to CDIOP[0] */
			SDEC_HAL_CDIOP(0, stpLXSdecCfgPort);
#endif
			break;
		default:
			SDEC_DEBUG_Print("Invalid channel:[%d]", stpLXSdecCfgPort->eInputPort);
			goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_CfgInputPort");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   select input port.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SelParInput
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T 	eRet 		= NOT_OK;

	LX_SDEC_SEL_PAR_INPUT_T 	*stpLXSdecParInput;
	LX_SDEC_INPUT_T		 		eInputPort;

	UINT8			ui4ts_sel	= 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SelParInput");

	stpLXSdecParInput = (LX_SDEC_SEL_PAR_INPUT_T *)ui32Arg;
	eInputPort = stpLXSdecParInput->eInputPort;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		/*--------------------------------------------------------
			--> ORIGINAL Design Concept but not real
				(Please Check After H13A0!!, they might be changed to original)
			LX_SDEC_INPUT_PARALLEL0 (CDIN0 Selection) (Ctr58 [5:4])
			00b : Internal Demod 	01b : External Demod
			10b : tpo,bidir,CI In	11b : tpi, CI Out
			LX_SDEC_INPUT_PARALLEL1 (CDINA Selection) (Ctr58 [7:6])
			00b : Internal Demod	01b : External Demod
			10b : tpi, CI Out		11b : tpo,bidir,CI In

			--> H13 A0 Ctr58 Bits are Crossed Abnormally as follows
			LX_SDEC_INPUT_PARALLEL0 (CDIN0 Selection) (Ctr58 [7:6])
			00b : Internal Demod 	01b : External Demod
			10b : tpo,bidir,CI In	11b : tpi, CI Out
			LX_SDEC_INPUT_PARALLEL1 (CDINA Selection) (Ctr58 [5:4])
			00b : Internal Demod	01b : External Demod
			10b : tpi, CI Out		11b : tpo,bidir,CI In
		   --------------------------------------------------------*/
		switch (stpLXSdecParInput->eParInput)
		{
			case LX_SDEC_INTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_INTERNAL_DEMOD [P%d]", eInputPort - 2);

				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
#if 0 // jinhwan.bae H13A0 Ctr58 Register is Crossed [5:4] for PARALLEL 1, [7:6] for PARALLEL 0
				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0xC; /* XX00 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0x3; /*00XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#else
				if( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0xC; /* XX00 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0x3; /*00XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#endif
				CTOP_CTRL_H13A0_WrFL(ctr58);
				break;
			case LX_SDEC_EXTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_EXTERNAL_DEMOD [P%d]", eInputPort - 2);

				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
#if 0 // jinhwan.bae H13A0 Ctr58 Register is Crossed [5:4] for PARALLEL 1, [7:6] for PARALLEL 0
				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0xC;
					ui4ts_sel |= 0x1;	/* XX01 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0x3;
					ui4ts_sel |= 0x4;	/* 01XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#else
				if( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0xC;
					ui4ts_sel |= 0x1;	/* XX01 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0x3;
					ui4ts_sel |= 0x4;	/* 01XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#endif

				CTOP_CTRL_H13A0_WrFL(ctr58);
				break;
			case LX_SDEC_CI_INPUT:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_CI_INPUT [P%d]", eInputPort - 2);

				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Wr01(ctr58, tpio_sel_ctrl, 1);	/* Set Parallel IO as Input ?? jinhwan.bae -> yes, so if you need ci input signal, select external one instead of CI_INPUT */
				// CTOP_CTRL_H13A0_Wr01(ctr58, tpio_sel_ctrl, 0); /* Always Output !We want to get output data ??  */
				CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
#if 0 // jinhwan.bae H13A0 Ctr58 Register is Crossed [5:4] for PARALLEL 1, [7:6] for PARALLEL 0
				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0xC;
					ui4ts_sel |= 0x2;	/* XX10 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0x3;
					ui4ts_sel |= 0xC;	/* 11XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#else
				if( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0xC;
					ui4ts_sel |= 0x3;	/* XX11 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0x3;
					ui4ts_sel |= 0x8;	/* 10XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#endif

				CTOP_CTRL_H13A0_WrFL(ctr58);
				break;
			case LX_SDEC_CI_OUTPUT:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_CI_OUTPUT [P%d]", eInputPort - 2);

				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Wr01(ctr58, tpio_sel_ctrl, 0); /* CI_INPUT port changed to Always Output !We want to get output data ??  */
				CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
#if 0 // jinhwan.bae H13A0 Ctr58 Register is Crossed [5:4] for PARALLEL 1, [7:6] for PARALLEL 0
				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0xC;
					ui4ts_sel |= 0x3;	/* XX11 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0x3;
					ui4ts_sel |= 0x8;	/* 10XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#else
				if( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
				{
					ui4ts_sel &= 0xC;
					ui4ts_sel |= 0x2;	/* XX10 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
				{
					ui4ts_sel &= 0x3;
					ui4ts_sel |= 0xC;	/* 11XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				}
#endif

				CTOP_CTRL_H13A0_WrFL(ctr58);
				break;

			default:
				SDEC_DEBUG_Print("Invalid Port:[%d]", stpLXSdecParInput->eParInput);
				goto exit;
			break;
		}
	}
#ifdef INCLUDE_L9_CHIP_KDRV
	/* L9A0 / L9A1 */
	else if (lx_chip_rev() < LX_CHIP_REV(L9, B0))
	{
		if( stpLXSdecParInput->eParInput == LX_SDEC_INTERNAL_DEMOD)
		{
			SDEC_DTV_SOC_Message( SDEC_IO, "L9 A1 LX_SDEC_INTERNAL_DEMOD [P%d]", eInputPort - 2);
			//stpSdecParam->stSDEC_IO_Reg->cdin_parallel_sel.p_sel = 0x0;
			/* select internal parallel input */
			SDEC_HAL_SetParallelInput(0);
		}
		else
		{
			SDEC_DTV_SOC_Message( SDEC_IO, "L9 A1 LX_SDEC_EXTERNAL_DEMOD [P%d]", eInputPort - 2);
			//stpSdecParam->stSDEC_IO_Reg->cdin_parallel_sel.p_sel = 0x1;
			/* select external parallel input */
			SDEC_HAL_SetParallelInput(1);
		}
	}
	/* L9B0 */
	else
	{
		switch (stpLXSdecParInput->eParInput)
		{
			case LX_SDEC_INTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_INTERNAL_DEMOD [P%d]", eInputPort - 2);

				CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);

				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp0_in_sel, 0);
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp1_in_sel, 0);

				CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);
				break;
			case LX_SDEC_EXTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_EXTERNAL_DEMOD [P%d]", eInputPort - 2);

				CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);

				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp0_in_sel, 3);
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp1_in_sel, 1);

				CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);
				break;
			case LX_SDEC_CI_INPUT:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_CI_INPUT [P%d]", eInputPort - 2);

				CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);
				CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tpio_sel_ctrl, 1);

				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp0_in_sel, 2);
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp1_in_sel, 2);

				CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);
				break;
			case LX_SDEC_CI_OUTPUT:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_CI_OUTPUT [P%d]", eInputPort - 2);

				CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);
				CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tpio_sel_ctrl, 0);

				if( eInputPort == LX_SDEC_INPUT_PARALLEL0 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp0_in_sel, 1);
				else if ( eInputPort == LX_SDEC_INPUT_PARALLEL1 )
					CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp1_in_sel, 3);

				CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);
				break;

			default:
				SDEC_DEBUG_Print("Invalid Port:[%d]", stpLXSdecParInput->eParInput);
				goto exit;
			break;
		}
	}
#endif

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SelParInput");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   select input port.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SelCiInput
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T 	eRet 		= NOT_OK;

	LX_SDEC_SEL_CI_INPUT_T 		*stpLXSdecParInput;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SelCiInput");

	stpLXSdecParInput = (LX_SDEC_SEL_CI_INPUT_T *)ui32Arg;

	SDEC_DTV_SOC_Message( SDEC_IO, "%s : stpLXSdecParInput->eParInput = %d", __FUNCTION__, stpLXSdecParInput->eParInput);

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		switch (stpLXSdecParInput->eParInput)
		{
			case LX_SDEC_INTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_INTERNAL_DEMOD");

				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Wr01(ctr58, tpo_sel_ctrl, 0);
				CTOP_CTRL_H13A0_WrFL(ctr58);

				break;
			case LX_SDEC_EXTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_EXTERNAL_DEMOD");

				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Wr01(ctr58, tpo_sel_ctrl, 1);
				CTOP_CTRL_H13A0_WrFL(ctr58);

				break;

			default:
				SDEC_DEBUG_Print("Invalid Port:[%d]", stpLXSdecParInput->eParInput);
				goto exit;
			break;
		}
	}
#ifdef INCLUDE_L9_CHIP_KDRV
	/* L9A0 / L9A1 */
	else if (lx_chip_rev() < LX_CHIP_REV(L9, B0))
	{
		/* Nothing to do */
		;
	}
	/* L9B0 */
	else
	{
		switch (stpLXSdecParInput->eParInput)
		{
			case LX_SDEC_INTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_INTERNAL_DEMOD");

				CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);
				CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tpo_sel_ctrl, 0);
				CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);

				break;
			case LX_SDEC_EXTERNAL_DEMOD:
				SDEC_DTV_SOC_Message( SDEC_IO, "LX_SDEC_EXTERNAL_DEMOD");

				CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);
				CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tpo_sel_ctrl, 1);
				CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);

				break;

			default:
				SDEC_DEBUG_Print("Invalid Port:[%d]", stpLXSdecParInput->eParInput);
				goto exit;
			break;
		}
	}
#endif

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SelCiInput");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   set esa mode.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetCipherEnable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;

	LX_SDEC_CIPHER_ENABLE_T *stLXSdecCipherEnalbe;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	BOOLEAN bEnable = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetCipherEnable");

	stLXSdecCipherEnalbe = (LX_SDEC_CIPHER_ENABLE_T *)ui32Arg;

	ui8Ch = stLXSdecCipherEnalbe->eCh;
	ui32PidFltId  = stLXSdecCipherEnalbe->uiPidFltId;
	bEnable	= stLXSdecCipherEnalbe->bEnable;

#if 0
	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx = ui32PidFltId;

	if(bEnable)
	{
		clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data, 14);//14th bit disable
	}
	else
	{
		set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data, 14); //14th bit enable
	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);
#endif

#ifdef NOT_USE_PIDF_SPINLOCK
	SDEC_HAL_PIDFDescEnable(ui8Ch, ui32PidFltId, bEnable);
#else
	SDEC_SetPidf_Disc_Enable(stpSdecParam, ui8Ch, ui32PidFltId, bEnable);
#endif

	SDEC_DTV_SOC_Message( SDEC_DESC, "SDEC_IO_SetCipherEnable : Ch[%d] FilterId[%d] bEnable[%d]", ui8Ch, ui32PidFltId, bEnable);
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetCipherEnable");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   set esa mode.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetCipherMode
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	UINT8	ui8Ch = 0x0;
	LX_SDEC_CIPHER_MODE_T *stpLXSdecCipherMode;
	//CDIC_DSC stCdicDsc;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetCipherMode");

	stpLXSdecCipherMode = (LX_SDEC_CIPHER_MODE_T *)ui32Arg;

	ui8Ch = stpLXSdecCipherMode->eCh;

#if 0
	stCdicDsc = stpSdecParam->stSDEC_IO_Reg->cdic_dsc[stpLXSdecCipherMode->eCh];

	stCdicDsc.cas_type = stpLXSdecCipherMode->eCasType;
	stCdicDsc.blk_mode = stpLXSdecCipherMode->eBlkMode;
	stCdicDsc.res_mode = stpLXSdecCipherMode->eResMode;
	stCdicDsc.key_size = stpLXSdecCipherMode->eKeySize;
	stCdicDsc.psc_en = stpLXSdecCipherMode->ePSCEn;//default enable

	stCdicDsc.even_mode = 0x2;
	stCdicDsc.odd_mode	= 0x3;

	stpSdecParam->stSDEC_IO_Reg->cdic_dsc[stpLXSdecCipherMode->eCh] = stCdicDsc;
#else
	SDEC_HAL_DSCSetCasType(ui8Ch, stpLXSdecCipherMode->eCasType);
	SDEC_HAL_DSCSetBlkMode(ui8Ch, stpLXSdecCipherMode->eBlkMode);
	SDEC_HAL_DSCSetResMode(ui8Ch, stpLXSdecCipherMode->eResMode);
	SDEC_HAL_DSCSetKeySize(ui8Ch, stpLXSdecCipherMode->eKeySize);
	SDEC_HAL_DSCEnablePESCramblingCtrl(ui8Ch, stpLXSdecCipherMode->ePSCEn);
	SDEC_HAL_DSCSetEvenMode(ui8Ch, 0x2);
	SDEC_HAL_DSCSetOddMode(ui8Ch, 0x3);
#endif

	SDEC_DTV_SOC_Message( SDEC_DESC, "SDEC_IO_SetCipherMode : Ch[%d] Type(3:AES)[%d]", ui8Ch, stpLXSdecCipherMode->eCasType);
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetCipherMode");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   set Cipher key.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetCipherKey
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	UINT8 ui8count = 0x0;

	LX_SDEC_CIPHERKEY_T *stpLXSdecCipherKey;
	UINT8 	key_type = 0, pid_idx = 0, odd_key = 0;
	UINT32	*ui32pAddr;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetCipherKey");

	stpLXSdecCipherKey = (LX_SDEC_CIPHERKEY_T *)ui32Arg;

	if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN || stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD)//Key type :even or ODD
	{
		key_type = 0x0;
		pid_idx =  stpLXSdecCipherKey->uiPidFltId;
		if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN)
		{
			odd_key = 0x0;
		}
		else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD)
		{
			odd_key = 0x1;
		}

		ui8count = 0x0;	//by skpark
	}
	else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD_IV || stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN_IV)//Key type :IV
	{
		if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			key_type = 0x1;
			pid_idx =  stpLXSdecCipherKey->uiPidFltId;
			if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN_IV)
			{
				odd_key = 0x0;
			}
			else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD_IV)
			{
				odd_key = 0x1;
			}

			ui8count = 0x0;	//by skpark
		}
		else
		{
			/* L9 Configuration */
			if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD_IV)
			{
				key_type = 0x1;				// LX_SDEC_CIPHER_KEY_IV;			// modified by skpark
				ui8count = 0x4;				//by skpark
				stpLXSdecCipherKey->uiKeySize += 4;		// by skpark
			}
			else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN_IV)
			{
				key_type = 0x01;
				ui8count = 0x0;				//by skpark
			}
		}
	}
	else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_MULTI2)
	{
		key_type = 0x02;
		ui8count = 0x0;				//by skpark
	}

	ui32pAddr = (UINT32 *)stpLXSdecCipherKey->puiCipherKey;

	if( ( key_type != 0x1 ) || ( pid_idx != 0xFF ) )	/* For BCAS IV, Only key_type == 0x1 && pid_idx == 0xFF should be set to all, others are set by original way */
	{
		/* Followings are Original Source Code before BCAS */
		//by skpark
		for( ; ui8count < stpLXSdecCipherKey->uiKeySize; ui8count++)
		{
			SDEC_HAL_KMEMSet( stpLXSdecCipherKey->eCh, key_type, pid_idx, odd_key, ui8count, *ui32pAddr);
			ui32pAddr++;
		}
	}
	else
	{
		UINT8 	ui8pidfilter 	= 0x0;
		UINT8	ui8PidfNum 		= 0x0;
		LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

		/* get chip configuation */
		pSdecConf = SDEC_CFG_GetConfig();

		/* get pid filter number from channel info structure */
		ui8PidfNum	= pSdecConf->chInfo[stpLXSdecCipherKey->eCh].num_pidf;

		// IV vector set to all PID filter jinhwan.bae
		for(ui8pidfilter = 0x0; ui8pidfilter < ui8PidfNum; ui8pidfilter++)
		{
			ui32pAddr = (UINT32 *)stpLXSdecCipherKey->puiCipherKey;

			for(ui8count = 0x0 ; ui8count < stpLXSdecCipherKey->uiKeySize; ui8count++)
			{
				SDEC_HAL_KMEMSet( stpLXSdecCipherKey->eCh, key_type, ui8pidfilter, odd_key, ui8count, *ui32pAddr);
				ui32pAddr++;
			}
		}
	}

	SDEC_DTV_SOC_Message( SDEC_DESC, "SDEC_IO_SetCipherKey : Ch[%d] idx[%d] eKeyMode[%d]", stpLXSdecCipherKey->eCh, stpLXSdecCipherKey->uiPidFltId, stpLXSdecCipherKey->eKeyMode);
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetCipherKey");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   set Cipher key.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetCipherKey
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	UINT8 ui8count = 0x0;

	LX_SDEC_GET_CIPHERKEY_T stLXSdecCipherKey, *stpLXSdecCipherKey;
	UINT8 	key_type = 0, pid_idx = 0, odd_key = 0;
	UINT32		*ui32pAddr;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetCipherKey");

	eResult = copy_from_user(&stLXSdecCipherKey, (void __user *)ui32Arg, sizeof(LX_SDEC_GET_CIPHERKEY_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	stpLXSdecCipherKey = &stLXSdecCipherKey;

	if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN || stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD)//Key type :even or ODD
	{
		key_type = 0x0;
		pid_idx =  stpLXSdecCipherKey->uiPidFltId;
		if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN)
		{
			odd_key = 0x0;
		}
		else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD)
		{
			odd_key = 0x1;
		}

		ui8count = 0x0;	//by skpark
	}
	else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD_IV || stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN_IV)//Key type :IV
	{
		if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		{
			key_type = 0x1;
			pid_idx =  stpLXSdecCipherKey->uiPidFltId;
			if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN_IV)
			{
				odd_key = 0x0;
			}
			else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD_IV)
			{
				odd_key = 0x1;
			}

			ui8count = 0x0;	//by skpark
		}
		else
		{
			/* L9 Configuration */
			if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_ODD_IV)
			{
				key_type = 0x1;	// LX_SDEC_CIPHER_KEY_IV;			// modified by skpark
				ui8count = 0x4;				//by skpark
				stpLXSdecCipherKey->uiKeySize += 4;		// by skpark
			}
			else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_EVEN_IV)
			{
				key_type = 0x01;
				ui8count = 0x0;				//by skpark
			}
		}
	}
	else if(stpLXSdecCipherKey->eKeyMode == LX_SDEC_CIPHER_KEY_MULTI2)
	{
		key_type = 0x02;
		ui8count = 0x0;				//by skpark
	}

	ui32pAddr = (UINT32 *)(&stpLXSdecCipherKey->uiCipherKey[0]);

    //by skpark
	for( ; ui8count < stpLXSdecCipherKey->uiKeySize; ui8count++)
	{
		*ui32pAddr = swab32(SDEC_HAL_KMEMGet( stpLXSdecCipherKey->eCh, key_type, pid_idx, odd_key, ui8count));
		ui32pAddr++;
	}

	/* copy parameters to user space */
	eResult = copy_to_user((void *)ui32Arg, stpLXSdecCipherKey, sizeof(LX_SDEC_GET_CIPHERKEY_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_DESC, "SDEC_IO_GetCipherKey : idx[%d] eKeyMode[%d]", stpLXSdecCipherKey->uiPidFltId, stpLXSdecCipherKey->eKeyMode);
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetCipherKey");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   SDEC PID filter set.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetPCRPID
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_SET_PCRPID_T *stpLXSdecPIDFltSetPID;
	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidValue = 0x0;
	BOOLEAN bMain = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetPCRPID");

	stpLXSdecPIDFltSetPID = (LX_SDEC_PIDFLT_SET_PCRPID_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltSetPID->eCh;
	ui32PidValue = stpLXSdecPIDFltSetPID->uiPidValue;
	bMain = stpLXSdecPIDFltSetPID->bMain;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] PCR  PidValue[0x%08x]", ui8Ch,	ui32PidValue);

	if(ui32PidValue == 0x1fff)
	{
		// chan | pcr_pid
#if 0
		stpSdecParam->stSDEC_IO_Reg->stcc[4*ui8Ch] = 0x00000000 | (ui8Ch << 29) | (ui32PidValue << 16);
#elif 1
		SDEC_HAL_STCCSetReg(ui8Ch, 0x00000000 | (ui8Ch << 29) | (ui32PidValue << 16));
#else
		SDEC_HAL_STCCSetCh(ui8Ch, ui8Ch);
		SDEC_HAL_STCCSetPCRPid(ui8Ch, ui32PidValue);
#endif
		if(bMain) pwm_context_reset(stpSdecParam, ui8Ch);
	}
	else
	{
		// en | chan | pcr_pid | copy_en | latch_en
#if 0
		stpSdecParam->stSDEC_IO_Reg->stcc[4*ui8Ch] = 0x80000003 | (ui8Ch << 29) | (ui32PidValue << 16);
#elif 1
		SDEC_HAL_STCCSetReg(ui8Ch, 0x80000000 | (ui8Ch << 29) );
		SDEC_HAL_STCCSetSTC(ui8Ch, 0);
		SDEC_HAL_STCCSetReg(ui8Ch, 0x80000003 | (ui8Ch << 29) | (ui32PidValue << 16));
#else
		SDEC_HAL_STCCEnable(ui8Ch, SDEC_HAL_ENABLE);
		SDEC_HAL_STCCSetCh(ui8Ch, ui8Ch);
		SDEC_HAL_STCCSetPCRPid(ui8Ch, ui32PidValue);
		SDEC_HAL_STCCEnableCopy(ui8Ch, SDEC_HAL_ENABLE);
		SDEC_HAL_STCCEnableLatch(ui8Ch, SDEC_HAL_ENABLE);
#endif
	}

	/* if current channel is main channel, set main
	 * warning *
	 * viewing channel is not main channel, main channel is pcr recovery channel */
	//if(bMain)	stpSdecParam->stSDEC_IO_Reg->stcc_asg.main = ui8Ch;
	if(bMain)
	{
		SDEC_HAL_STCCSetMain(ui8Ch);
		pwm_context_reset(stpSdecParam, ui8Ch);	// added by jinhwan.bae for support pip operation 
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetPCRPID");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}


/**
********************************************************************************
* @brief
*   set pcr recovery.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetPcrRecovery
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SET_PCR_RECOVERY_T *stpLXSdecSetPCRRecovery;

	UINT8 ui8Ch = 0x0;
	UINT8 ui8PcrCmd = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetPcrRecovery");

	stpLXSdecSetPCRRecovery = (LX_SDEC_SET_PCR_RECOVERY_T *)ui32Arg;

	ui8Ch = stpLXSdecSetPCRRecovery->eCh;

	ui8PcrCmd = stpLXSdecSetPCRRecovery->eCmd;

	switch (ui8PcrCmd)
	{
		case LX_SDEC_PCR_CMD_DISABLE:
			stpSdecParam->bPcrRecoveryFlag[ui8Ch] = FALSE;
//			SDEC_HAL_STCCReset(ui8Ch);
			break;
		case LX_SDEC_PCR_CMD_ENABLE:
			stpSdecParam->bPcrRecoveryFlag[ui8Ch] = TRUE;
#if 0	/* jinhwan.bae to add for stc counter reset to 0 , which is A/V decoder STC counter value reset , pause -> play sequence */
			SDEC_HAL_AVSTCReset(ui8Ch);
			usleep(50);	/* actually 12us needed to send the reset value to A/V Decoder */
#endif
			SDEC_HAL_STCCReset(ui8Ch);
#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
			/* For Enable Case, Initialize Free Run Status of Each Channel - temp, PCR refactoring needed with ch structure */
			SDEC_IO_SendFreeRunCmd(0, _STOP_FREE_RUN);
			SDEC_IO_SendFreeRunCmd(1, _STOP_FREE_RUN);
#endif

#ifdef __NEW_PWM_RESET_COND__
			pcr_error_for_reset = 0;
#endif
			break;
		case LX_SDEC_PCR_CMD_RESET:
			//set__bit(stpSdecParam->stSDEC_IO_Reg->stcc[4*ui8Ch], 30); 	//reset
			//set__bit(stpSdecParam->stSDEC_IO_Reg->stcc[4*ui8Ch], 1);	//copy_en
			SDEC_HAL_STCCReset(ui8Ch);
			SDEC_HAL_STCCEnableCopy(ui8Ch, SDEC_HAL_ENABLE);
		break;
		default:
			SDEC_DEBUG_Print("Invalid PCR cmd:[%d]", ui8PcrCmd);
			goto exit;
		break;
	}

//The original scheme use pwm
#if 0
	stpSdecParam->bPcrRecoveryFlag[ui8Ch] = (stpLXSdecSetPCRRecovery->bEnable == 0x1) ? TRUE : FALSE;

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "SDEC ch:[%d] pcr recover flag:[%d]", ui8Ch, stpLXSdecSetPCRRecovery->bEnable);
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetPcrRecovery");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   get information of input port setting
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetInputPort
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	LX_SDEC_GET_INPUT_T stLXSdecGetInputPort, *stpLXSdecGetInputPort;

	UINT8 ui8Ch = 0x0;
	//CDIC *Cdic;
	//UINT32 val = 0;
	CDIC cdic;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetPcrRecovery");

	eResult = copy_from_user(&stLXSdecGetInputPort, (void __user *)ui32Arg, sizeof(LX_SDEC_GET_INPUT_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	stpLXSdecGetInputPort = &stLXSdecGetInputPort;

	ui8Ch = stpLXSdecGetInputPort->eCh;

//	if(ui8Ch < LX_SDEC_CH_C )	Cdic = stpSdecParam->stSDEC_IO_Reg->cdic[ui8Ch];
//	else						Cdic = stpSdecParam->stSDEC_IO_Reg->cdic2;
	//SDEC_HAL_CIDCRead(ui8Ch, &val);
	//Cdic = (CDIC*)&val;
	SDEC_HAL_CIDCGetStatus(ui8Ch, &cdic);


#if 0
	stpLXSdecGetInputPort->uiSrc 		= ( ui32Cdic >> LX_CDIC_SRC ) 			& 0xF );
	stpLXSdecGetInputPort->uiNo_wdata	= ( ui32Cdic >> LX_CDIC_NO_WDATA ) 		& 0x1 );
	stpLXSdecGetInputPort->uiSync_lost	= ( ui32Cdic >> LX_CDIC_NO_SYNCLOST ) 	& 0x1 );
	stpLXSdecGetInputPort->uiSb_dropped	= ( ui32Cdic >> LX_CDIC_SB_DROPPED ) 	& 0x1 );
	stpLXSdecGetInputPort->uiCdif_empty	= ( ui32Cdic >> LX_CDIC_CDIF_EMPTY ) 	& 0x1 );
	stpLXSdecGetInputPort->uiCdif_full	= ( ui32Cdic >> LX_CDIC_CDIF_FULL ) 	& 0x1 );
	stpLXSdecGetInputPort->uiPd_wait	= ( ui32Cdic >> LX_CDIC_PD_WAIT ) 		& 0x1 );
	stpLXSdecGetInputPort->uiCdif_ovflow= ( ui32Cdic >> LX_CDIC_CDIF_OVFLOW ) 	& 0x1 );
	stpLXSdecGetInputPort->uiCdif_wpage	= ( ui32Cdic >> LX_CDIC_CDIF_WPAGE ) 	& 0x1 );
	stpLXSdecGetInputPort->uiCdif_rpage	= ( ui32Cdic >> LX_CDIC_CDIF_RPAGE ) 	& 0x1 );
#else
	stpLXSdecGetInputPort->uiSrc			= cdic.src;
	stpLXSdecGetInputPort->uiNo_wdata		= cdic.no_wdata;
	stpLXSdecGetInputPort->uiSync_lost		= cdic.sync_lost;
	stpLXSdecGetInputPort->uiSb_dropped 	= cdic.sb_dropped;
	stpLXSdecGetInputPort->uiCdif_empty 	= cdic.cdif_empty;
	stpLXSdecGetInputPort->uiCdif_full		= cdic.cdif_full;
	stpLXSdecGetInputPort->uiPd_wait		= cdic.pd_wait;
	stpLXSdecGetInputPort->uiCdif_ovflow	= cdic.cdif_ovflow;
	stpLXSdecGetInputPort->uiCdif_wpage 	= cdic.cdif_wpage;
	stpLXSdecGetInputPort->uiCdif_rpage 	= cdic.cdif_rpage;
#endif


	/* copy parameters to user space */
	eResult = copy_to_user((void *)ui32Arg,stpLXSdecGetInputPort,sizeof(LX_SDEC_GET_INPUT_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetPcrRecovery");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   set video output port
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetVidOutport
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	LX_SDEC_SET_VDEC_PORT_T stLXSdecSetVidOutort, *stpLXSdecSetVidOutort;
	LX_SDEC_CFG_T* pSdecConf = NULL;

	UINT8 ui8Ch = 0x0;
	UINT8 ui8sel = 0x0;
	int ret = RET_ERROR;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetVidOutport");

	eResult = copy_from_user(&stLXSdecSetVidOutort, (void __user *)ui32Arg, sizeof(LX_SDEC_SET_VDEC_PORT_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	stpLXSdecSetVidOutort = &stLXSdecSetVidOutort;

	ui8Ch 	= (UINT8)stpLXSdecSetVidOutort->ucPort;
	ui8sel	= (UINT8)stpLXSdecSetVidOutort->eFrom;

	/* get config */
	pSdecConf = SDEC_CFG_GetConfig();

	/* if port number is out of range, return errror */
	if(ui8Ch > pSdecConf->nVdecOutPort) goto exit;

	ret =SDEC_HAL_SetVideoOut(ui8Ch, ui8sel);
	if(ret != RET_OK) { SDEC_DEBUG_Print("error in HAL"); goto exit; }

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetVidOutport");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   set  SDEC input port enable and disable select
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_InputPortEnable(LX_SDEC_INPUT_T eInputPath, UINT8 en)
{
	int ret = RET_ERROR;

	switch (eInputPath)
	{
		case LX_SDEC_INPUT_PARALLEL0:
			SDEC_HAL_CDIPEnable(0, en);
			break;
		case LX_SDEC_INPUT_PARALLEL1:
			if (lx_chip_rev() < LX_CHIP_REV(L9, B0))
			{
				SDEC_HAL_CDIPEnable(0, en);
			}
			else
			{
				SDEC_HAL_CDIPAEnable(0, en);
			}
			break;

		case LX_SDEC_INPUT_SERIAL0:
#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			if( en == SDEC_HAL_ENABLE)
			{
				if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
				{
					UINT8			ui4ts_sel	= 0x0;
					
					CTOP_CTRL_H13A0_RdFL(ctr58);
					CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
					ui4ts_sel &= 0x3; 
					ui4ts_sel |= 0x4;	/* 01XX */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
					CTOP_CTRL_H13A0_WrFL(ctr58);
				}
			}
	
			SDEC_HAL_CDIPEnable(0, en);
#else
			SDEC_HAL_CDIPEnable(3, en);
#endif
			break;

		case LX_SDEC_INPUT_SERIAL1:
#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			if( en == SDEC_HAL_ENABLE)
			{
				if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
				{
					UINT8			ui4ts_sel	= 0x0;
					
					CTOP_CTRL_H13A0_RdFL(ctr58);
					CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
					ui4ts_sel &= 0xC; 
					ui4ts_sel |= 0x1;	/* XX01 */
					CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
					CTOP_CTRL_H13A0_WrFL(ctr58);
				}
			}
			
			SDEC_HAL_CDIPAEnable(0, en);
#else
			SDEC_HAL_CDIOPEnable(0, en);
#endif
			break;

		case LX_SDEC_INPUT_SERIAL2:
#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CDIPEnable(3, en);
#else
			/* temp source for supporting KR Sub Tuner in CDINA , should fix again ! - jinhwan.bae 0809 */
			if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
			{
				UINT8			ui4ts_sel	= 0x0;
				
				CTOP_CTRL_H13A0_RdFL(ctr58);
				CTOP_CTRL_H13A0_Rd01(ctr58, ts_sel, ui4ts_sel);
				ui4ts_sel &= 0xC; 
				ui4ts_sel |= 0x1;	/* XX01 */
				CTOP_CTRL_H13A0_Wr01(ctr58, ts_sel, ui4ts_sel);
				CTOP_CTRL_H13A0_WrFL(ctr58);
			}
			
			SDEC_HAL_CDIPAEnable(0, en);
#endif
			break;

		case LX_SDEC_INPUT_SERIAL3:
#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CDIOPEnable(0, en);
#endif
			break;

		default:
			goto exit;
	}

	ret = RET_OK;

exit:
	return ret;
}


/**
********************************************************************************
* @brief
*   set  SDEC input port enable and disable select
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_InputPortEnable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;

	LX_SDEC_CH_T eCh;
	LX_SDEC_INPUT_T 		eInputPath;
	LX_SDEC_ENABLE_INPUT_T	stLXSdecEnableInput;
	UINT8					ui8En = 0;
	UINT8 					ui8cdif_full = 0, ui8cdif_ovflow = 0;
	CDIC 					cdic;

	unsigned long 			flags = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_InputPortEnable");

	eResult = copy_from_user(&stLXSdecEnableInput, (void __user *)ui32Arg, sizeof(LX_SDEC_ENABLE_INPUT_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	eCh 		= stLXSdecEnableInput.eCh;
	eInputPath 	= stLXSdecEnableInput.eInputPath;
	ui8En		= stLXSdecEnableInput.bEnable ? 0x1 : 0x0;

	//if(eCh == LX_SDEC_CH_C) 	ui8cdif_full = stpSdecParam->stSDEC_IO_Reg->cdic2.cdif_full;
	//else						ui8cdif_full = stpSdecParam->stSDEC_IO_Reg->cdic[eCh].cdif_full;
	SDEC_HAL_CIDCGetStatus(eCh, &cdic);

	ui8cdif_full	= cdic.cdif_full;
	ui8cdif_ovflow	= cdic.cdif_ovflow;

	/* reset CDIC before enable CDIP */
	if( stLXSdecEnableInput.bEnable)
	{
		if( ui8cdif_full || ui8cdif_ovflow )
		{
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			SDEC_DTV_SOC_Message(SDEC_RESET, RED_COLOR "SDIO RESET in CH Change" NORMAL_COLOR );

			/* 0xC000B220(SDIO-CDIC)*/
			SDEC_DTV_SOC_Message(SDEC_RESET, "CDIC       [0x%08x]", SDEC_HAL_CIDCGet(eCh));

			/* 0xC000B260(SDIO-SDMWC)*/
			SDEC_DTV_SOC_Message(SDEC_RESET, "SDMWC      [0x%08x]", SDEC_HAL_SDMWCGet());

			/* 0xC000B264(SDIO-SDMWC_STAT)*/
			SDEC_DTV_SOC_Message(SDEC_RESET, "SDMWC_STAT [0x%08x]", SDEC_HAL_SDMWCGetStatus());

			/* 0xC000B418(SDCORE-CHAN_STAT)*/
			SDEC_DTV_SOC_Message(SDEC_RESET, "CHAN_STAT  [0x%08x]", SDEC_HAL_GetChannelStatus2(eCh));

			/* 0xC000B420(SDCORE-CC_CHK_EN)*/
			SDEC_DTV_SOC_Message(SDEC_RESET, "CC_CHK_EN  [0x%08x%08x]", SDEC_HAL_CCCheckEnableGet(eCh, 0), SDEC_HAL_CCCheckEnableGet(eCh, 1));

			/* disable channel input and wait 0.01 ms */
			SDEC_InputPortEnable(stpSdecParam->eInputPath[eCh], SDEC_HAL_DISABLE);
			
			OS_UsecDelay(10);
			
			SDEC_InputPortReset(eCh);

			OS_UsecDelay(10);

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
		}

		/* CLEAR CC_CHK_EN Register */
		SDEC_HAL_CCCheckEnableSet(eCh, 0, 0);
		SDEC_HAL_CCCheckEnableSet(eCh, 1, 0);
	}

	SDEC_InputPortEnable(eInputPath,	ui8En);

	/* save input mode for polling check SDEC stuck */
	if( eCh < LX_SDEC_CH_C )	stpSdecParam->eInputPath[eCh] = eInputPath;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_InputPortEnable");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   set  SDEC input port enable and disable select
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SelectPVRSource
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;

	UINT8 ui8Ch = 0x0;
	LX_SDEC_DL_SEL_T  stLXSdecDlSel;
	int ret = RET_ERROR;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SelectPVRSource");

	eResult = copy_from_user(&stLXSdecDlSel, (void __user *)ui32Arg, sizeof(LX_SDEC_DL_SEL_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	ui8Ch = stLXSdecDlSel.eCh;

	/* For CDIC2 Download for SDT set */
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if( stLXSdecDlSel.eSrc == LX_SDEC_FROM_CDIC2 )
		{
			/* set PVR source as SDEC (SDEC / SENC) */
			ret = SDEC_HAL_SetPVRSrc(ui8Ch, LX_SDEC_FROM_SDEC);
			/* set PVR SDEC source as CDIC3 (SDEC(A,B) / CDIC3) */
			ret = SDEC_HAL_CIDC3DlConf(ui8Ch, 1);
			/* set PVR SDEC CDIC source as CDIC2 (CDIC3 / CDIC2) */
			ret = SDEC_HAL_CDIC2DlExtConf(ui8Ch, 1);
		}
		else if( stLXSdecDlSel.eSrc == LX_SDEC_FROM_CDIC )
		{
			/* set PVR source as SDEC (SDEC / SENC) */
			ret = SDEC_HAL_SetPVRSrc(ui8Ch, LX_SDEC_FROM_SDEC);
			/* set PVR source as CDIC3 (SDEC(A,B) / CDIC3) */
			ret = SDEC_HAL_CIDC3DlConf(ui8Ch, 1);
			/* set PVR SDEC CDIC source as CDIC3 (CDIC3 / CDIC2) */
			ret = SDEC_HAL_CDIC2DlExtConf(ui8Ch, 0);
		}
		else
		{
			/* set PVR source as SDEC Core */
			ret = SDEC_HAL_CIDC3DlConf(ui8Ch, 0);
			ret = SDEC_HAL_SetPVRSrc(ui8Ch, stLXSdecDlSel.eSrc);
		}
	}
	else
	{
		if( stLXSdecDlSel.eSrc == LX_SDEC_FROM_CDIC )
		{
			/* set PVR source as CDIC3 */
			ret = SDEC_HAL_CIDC3DlConf(ui8Ch, 1);
			ret = SDEC_HAL_SetPVRSrc(ui8Ch, LX_SDEC_FROM_SDEC);
		}
		else
		{
			/* set PVR source as SDEC Core */
			ret = SDEC_HAL_CIDC3DlConf(ui8Ch, 0);
			ret = SDEC_HAL_SetPVRSrc(ui8Ch, stLXSdecDlSel.eSrc);
		}
	}

	if(ret != RET_OK) { SDEC_DEBUG_Print("error in HAL"); goto exit; }

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SelectPVRSource");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   set input port.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_InputSet
	(S_SDEC_PARAM_T *stpSdecParam,
	LX_SDEC_SEL_INPUT_T *stpLXSdecSelPort)
{
	DTV_STATUS_T eRet = NOT_OK;
	UINT8 ui8Ch = 0x0;
	CDIC cdic;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_InputSet");

	ui8Ch = stpLXSdecSelPort->eCh;

	/* checking channel sanity */
	if( ui8Ch >= LX_SDEC_CH_NUM)
	{
		SDEC_DEBUG_Print("Invalid channel:[%d]", stpLXSdecSelPort->eCh);
		goto exit;
	}

	/* set variable 0 */
	memset( &cdic, 0, sizeof(cdic));

	//cdic.rst		= 1;
	//cdic.min_sb_det = 3;
	//cdic.max_sb_drp = 3;
	SDEC_HAL_CIDCMinSyncByteDetection(ui8Ch, 3);
	SDEC_HAL_CIDCMaxSyncByteDrop(ui8Ch, 3);

	switch (stpLXSdecSelPort->eInputPath)
	{
		case LX_SDEC_INPUT_SERIAL0:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] SERIAL0", stpLXSdecSelPort->eCh);

			//SDEC_CdipConfSet(stpSdecParam, 3, stpLXSdecSelPort->eStreamMode);
			//SDEC_HAL_CDIP(3, SDEC_HAL_CDIP_SERIAL, SDEC_HAL_CDIP_FIRST, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);

			//cdic.src		= E_SDEC_CDIC_SRC_CDIN3;
			//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F300000;
#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN0);
#else
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN3);
#endif
			break;
		case LX_SDEC_INPUT_SERIAL1:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] SERIAL1", stpLXSdecSelPort->eCh);

			//SDEC_CdiopConfInSet(stpSdecParam, 0, stpLXSdecSelPort->eStreamMode);
			//SDEC_HAL_CDIOP(0, SDEC_HAL_CDIOP_IN, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);

			//cdic.src		= E_SDEC_CDIC_SRC_CDIN4;
//					*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F400000;
#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDINA);
#else
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN4);
#endif
			break;
		case LX_SDEC_INPUT_SERIAL2:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] SERIAL2", stpLXSdecSelPort->eCh);

#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN3);
#else
			/* temp source for supporting KR Sub Tuner in CDINA , should fix again ! - jinhwan.bae 0809 */
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDINA);
#endif
			break;
		case LX_SDEC_INPUT_SERIAL3:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] SERIAL3", stpLXSdecSelPort->eCh);

#ifdef LX_SDEC_USE_NEW_INPUTCONFIG
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN4);
#endif
			break;
		case LX_SDEC_INPUT_PARALLEL0:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] PARALLEL0", stpLXSdecSelPort->eCh);

			//SDEC_CdipConfSet(stpSdecParam, 0, stpLXSdecSelPort->eStreamMode);
			//SDEC_CdipConfSet(stpSdecParam, 1, stpLXSdecSelPort->eStreamMode);
			//SDEC_CdipConfSet(stpSdecParam, 2, stpLXSdecSelPort->eStreamMode);
			//SDEC_HAL_CDIP(0, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FIRST, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);
			//SDEC_HAL_CDIP(1, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FOLLOWER, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);
			//SDEC_HAL_CDIP(2, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FOLLOWER, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);

			if (lx_chip_rev() < LX_CHIP_REV(L9, B0))
			{
				/* select internal parallel input */
			//	SDEC_HAL_SetParallelInput(0);
			}
			else
			{
				// L9B0
				//CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);
				//CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp0_in_sel, 0);
				//CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);
			}


			//cdic.src		= E_SDEC_CDIC_SRC_CDIN0;
			//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F000000;
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN0);
		break;

		case LX_SDEC_INPUT_PARALLEL1:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] PARALLEL1", stpLXSdecSelPort->eCh);

			if (lx_chip_rev() < LX_CHIP_REV(L9, B0))
			{
				//SDEC_CdipConfSet(stpSdecParam, 0, stpLXSdecSelPort->eStreamMode);
				//SDEC_CdipConfSet(stpSdecParam, 1, stpLXSdecSelPort->eStreamMode);
				//SDEC_CdipConfSet(stpSdecParam, 2, stpLXSdecSelPort->eStreamMode);
				////SDEC_HAL_CDIP(0, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FIRST, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);
				//SDEC_HAL_CDIP(1, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FOLLOWER, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);
				//SDEC_HAL_CDIP(2, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FOLLOWER, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);

				//stpSdecParam->stSDEC_IO_Reg->cdin_parallel_sel.p_sel = 0x1;
				/* select external parallel input */
				//SDEC_HAL_SetParallelInput(1);

				//cdic.src		= E_SDEC_CDIC_SRC_CDIN0;
				//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F000000;
				SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN0);
			}
			else
			{
				//SDEC_CdipConfSet(stpSdecParam, 0, stpLXSdecSelPort->eStreamMode);
				//SDEC_CdipConfSet(stpSdecParam, 1, stpLXSdecSelPort->eStreamMode);
				//SDEC_CdipConfSet(stpSdecParam, 2, stpLXSdecSelPort->eStreamMode);
				//SDEC_HAL_CDIPA(0, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FIRST, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);
				//SDEC_HAL_CDIPA(1, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FOLLOWER, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);
				//SDEC_HAL_CDIPA(2, SDEC_HAL_CDIP_PARALLEL, SDEC_HAL_CDIP_FOLLOWER, SDEC_HAL_CDIP_CLK_ACT_HIGH, SDEC_HAL_CDIP_VAL_ENABLE);

				// L9B0
				//CTOP_CTRL_L9B_RdFL(ctr50_reg_tpio_sel);
				//CTOP_CTRL_L9B_Wr01(ctr50_reg_tpio_sel, tp1_in_sel, 1);
				//CTOP_CTRL_L9B_WrFL(ctr50_reg_tpio_sel);


			//	CTOP_CTRL_L9B_RdFL(ctr53_reg_gpio_mux_enable);
				//CTOP_CTRL_L9B_Wr01(ctr53_reg_gpio_mux_enable, gp5_4_mux_en, 0);
				//CTOP_CTRL_L9B_Wr01(ctr53_reg_gpio_mux_enable, gp5_5_mux_en, 0);
				//CTOP_CTRL_L9B_Wr01(ctr53_reg_gpio_mux_enable, gp5_6_mux_en, 0);
				//CTOP_CTRL_L9B_Wr01(ctr53_reg_gpio_mux_enable, gp5_7_mux_en, 0);
				//CTOP_CTRL_L9B_WrFL(ctr53_reg_gpio_mux_enable);

				//cdic.src		= E_SDEC_CDIC_SRC_CDIN0;
				//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F000000;
				SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDINA);
			}
		break;
#if 0
		case LX_SDEC_INPUTMODE_SERIAL2:
			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] SERIAL2", stpLXSdecSelPort->eCh);

			//SDEC_CdipConfSet(stpSdecParam, 4, stpLXSdecSelPort->eStreamMode);
			//SDEC_HAL_CDIP(3, SDEC_HAL_CDIP_SERIAL, SDEC_HAL_CDIP_FIRST, SDEC_HAL_CDIP_CLK_ACT_LOW, SDEC_HAL_CDIP_VAL_DISABLE);

			//cdic.src		= E_SDEC_CDIC_SRC_CDIN3;
			//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F300000;
			SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN3);
		break;

		case LX_SDEC_INPUTMODE_SERIAL3:
		SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] SERIAL3", stpLXSdecSelPort->eCh);

		/* gaius.lee 2011.07.04 - set stpio as input dedicated mode */
		if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
		{
			// L9B0
			//CTOP_CTRL_L9B_RdFL(ctr32_reg_gpio_mux_enable);
			//CTOP_CTRL_L9B_Wr01(ctr32_reg_gpio_mux_enable, stpio_en_ctrl, 1);
			//CTOP_CTRL_L9B_WrFL(ctr32_reg_gpio_mux_enable);
		}
		else
		{
			/* gaius.lee 2011.07.04 - set stpio as input dedicated mode */
			CTOP_CTRL_L9_RdFL(ctr32);
			CTOP_CTRL_L9_Wr01(ctr32, stpio_en_ctrl, 1);
			CTOP_CTRL_L9_WrFL(ctr32);
		}

		//SDEC_CdiopConfInSet(stpSdecParam, 0, stpLXSdecSelPort->eStreamMode);
		//SDEC_HAL_CDIOP(0, SDEC_HAL_CDIOP_IN, SDEC_HAL_CDIP_CLK_ACT_LOW, SDEC_HAL_CDIP_VAL_DISABLE);

		//cdic.src		= E_SDEC_CDIC_SRC_CDIN4;
		//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F400000;
		SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_CDIN4);
		break;
#endif
		case LX_SDEC_INPUT_DVR:

			SDEC_DTV_SOC_Message( SDEC_IO, "Ch[%d] DVR", stpLXSdecSelPort->eCh);

			if(ui8Ch == LX_SDEC_CH_B)
				//cdic.src		= E_SDEC_CDIC_SRC_UPLOAD1;
				//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_B] = 0x1F700000;
				SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_UPLOAD1);
			else
				//cdic.src		= E_SDEC_CDIC_SRC_UPLOAD0;
				//*(volatile UINT32 *)ui32Cdic[LX_SDEC_CH_A] = 0x1F600000;
				SDEC_HAL_CIDCSetSrc(ui8Ch, E_SDEC_CDIC_SRC_UPLOAD0);
			break;

		default:
				SDEC_DEBUG_Print("Invalid input path:[%d]", stpLXSdecSelPort->eInputPath);
				goto exit;
		break;
	}

	/* gaius.lee 2011.01.18
	 * channel C 추가로 A/B/C 를 미리 나누지 않고 나중에 한방에 쓰도록 수정
 	 */
	//if(ui8Ch == LX_SDEC_CH_C)	stpSdecParam->stSDEC_IO_Reg->cdic2			= cdic;
	//else						stpSdecParam->stSDEC_IO_Reg->cdic[ui8Ch]	= cdic;

	SDEC_DTV_SOC_Message( SDEC_IO, "Reset");

	if(stpLXSdecSelPort->bPortReset == TRUE)
	{
		/* disable sdec input port */
		SDEC_InputPortEnable(stpLXSdecSelPort->eInputPath,	SDEC_HAL_DISABLE);

		OS_UsecDelay(10);

#if 0
		/* reset sdec input port */
		SDEC_HAL_CIDCReset(ui8Ch);
		/* wait 10 us */
		OS_UsecDelay(10);
#endif
		SDEC_InputPortReset(ui8Ch);

		OS_UsecDelay(10);

		/* enable sdec input port */
		SDEC_InputPortEnable(stpLXSdecSelPort->eInputPath,	SDEC_HAL_ENABLE);
	}

	/* jinhwan.bae added 2013. 02. 19 work around for CDIF_FULL, MWF_OVF, in US mode reset was done with SERIAL (default value)
	    if SetInputConfig(ENABLE) is not called, no input is defined stpSdecParam->eInputPath[ch], default serial is set  */
	/* save input mode for polling check SDEC stuck */
	if( stpLXSdecSelPort->eCh < LX_SDEC_CH_C )	stpSdecParam->eInputPath[stpLXSdecSelPort->eCh] = stpLXSdecSelPort->eInputPath;

	SDEC_DTV_SOC_Message( SDEC_IO, "Done");

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_InputSet");

	eRet = OK;

exit:
	return (eRet);
}

#if 0
/**
********************************************************************************
* @brief
*   cdip conf set.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8CdipIdx
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_CdipConfSet
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8SettingIdx,
	LX_SDEC_STREAMMODE_T eSdecStreamMode)
{
	DTV_STATUS_T eRet = NOT_OK;
	CDIP stCdip;
	UINT8 ui8CdipIdx = 0;

	static  S_SDEC_CDIP_CONF_SET_T staSdecCdipConfSet[] = {
#if 0
	       //serial 0
		{E_SDEC_CDIP_3, E_SDEC_CDIP_ENABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_ENABLE, E_SDEC_CDIP_VAL_ENABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIP_SERIAL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x14, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_POS_SOP, E_SDEC_CDIP_ATSC}, //CDIP3
#endif /* #if 0 */
		//serial 1

#if 0
		{E_SDEC_CDIOP_0, E_SDEC_CDIP_ENABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_ENABLE, E_SDEC_CDIP_VAL_ENABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIOP_VAL_SEL_2, E_SDEC_CDIOP_SERIAL_0, 0x0, 0x14, 0x0, 0x0, E_SDEC_CDIP_POS_SOP, E_SDEC_CDIP_ATSC},//CDIOP0
#endif /* #if 0 */

		//parallel 0
		{E_SDEC_CDIP_0, E_SDEC_CDIP_ENABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_DISABLE, E_SDEC_CDIP_VAL_ENABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIP_PARALLEL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x14, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_47DETECTION, E_SDEC_CDIP_ATSC},//CDIP0
		{E_SDEC_CDIP_1, E_SDEC_CDIP_DISABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_DISABLE, E_SDEC_CDIP_VAL_DISABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIP_SERIAL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x8, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_47DETECTION, E_SDEC_CDIP_ATSC},//CDIP1
		{E_SDEC_CDIP_2, E_SDEC_CDIP_DISABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_DISABLE, E_SDEC_CDIP_VAL_DISABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIP_SERIAL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x8, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_47DETECTION, E_SDEC_CDIP_ATSC},//CDIP2
		 //serial 0
		{E_SDEC_CDIP_3, E_SDEC_CDIP_ENABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_DISABLE, E_SDEC_CDIP_VAL_ENABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIP_SERIAL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x14, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_POS_SOP, E_SDEC_CDIP_ATSC}, //CDIP3
		 //serial 2
		{E_SDEC_CDIP_3, E_SDEC_CDIP_ENABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_LOW,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_DISABLE, E_SDEC_CDIP_VAL_DISABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIP_SERIAL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x14, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_POS_SOP, E_SDEC_CDIP_ATSC}, //CDIP3
	};


	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	if( ui8SettingIdx > 3 ) 	ui8CdipIdx = 3;
	else						ui8CdipIdx = ui8SettingIdx;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_CdipConfSet");

	stCdip = stpSdecParam->stSDEC_IO_Reg->cdip[ui8SettingIdx];

	stCdip.dtype      		= eSdecStreamMode;//staSdecCdipConfSet[ui8SettingIdx].eSdecCdipDtype;
	stCdip.sync_type  	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipSyncType;
	//reg_sdec_io->cdip[SdecCdipIdx].f.ba_val_dis 		= staSdecCdipConfSet[stpSdecParam->ui8InputSetIdx].eSdecCdipBaSop;
	//reg_sdec_io->cdip[eSdecCdipIdx].f.ba_val_dis 		= staSdecCdipConfSet[stpSdecParam->ui8InputSetIdx].eSdecCdipBaVal;
	stCdip.clk_div    		= staSdecCdipConfSet[ui8SettingIdx].ui32ClkDiv;
	//reg_sdec_io->cdip[eSdecCdipIdx].f.ba_clk_dis	 	= eSdecCdipBaClk;
	stCdip.pconf      		= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipPconf;
	stCdip.req_en    	 	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipReqEn;
	stCdip.val_en     	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipValEn;
	stCdip.err_en     	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipErrEn;
	stCdip.req_act_lo 	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipReqPol;
	stCdip.val_act_lo 	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipValPol;
	stCdip.clk_act_lo 	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipClkPol;
	stCdip.err_act_hi 	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipErrPol;
	stCdip.test_en    	= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipTestEn;
	stCdip.en         		= staSdecCdipConfSet[ui8SettingIdx].eSdecCdipEn;

	stpSdecParam->stSDEC_IO_Reg->cdip[ui8CdipIdx] = stCdip;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_CdipConfSet");

	eRet = OK;

exit:
	return (eRet);
}

DTV_STATUS_T SDEC_CdiopConfInSet
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8CdipIdx,
	LX_SDEC_STREAMMODE_T eSdecStreamMode)
{
	DTV_STATUS_T eRet = NOT_OK;
	CDIOP stCdiop[2];

	static  S_SDEC_CDIP_CONF_IN_SET_T staSdecCdipConfInSet[] = {
	{E_SDEC_CDIOP_0, E_SDEC_CDIP_ENABLE, E_SDEC_CDIP_TEST_DISABLE, E_SDEC_CDIP_ERR_ACT_LOW, E_SDEC_CDIP_CLK_ACT_HIGH,
		  E_SDEC_CDIP_VAL_ACT_HIGH, E_SDEC_CDIP_REQ_ACT_HIGH, E_SDEC_CDIP_ERR_DISABLE, E_SDEC_CDIP_VAL_ENABLE, E_SDEC_CDIP_REQ_DISABLE,
		  E_SDEC_CDIOP_VAL_SEL_2, E_SDEC_CDIOP_SERIAL_0, E_SDEC_CDIP_BA_CLK_ENABLE, 0x14, E_SDEC_CDIP_BA_VAL_ENABLE, E_SDEC_CDIP_BA_SOP_ENABLE, E_SDEC_CDIP_POS_SOP, E_SDEC_CDIP_ATSC}//CDIOP0
	};

	if (stpSdecParam == NULL)
	{
		SDEC_DEBUG_Print("Invalid parameters");
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_CdipConfInSet");

	stCdiop[ui8CdipIdx] = stpSdecParam->stSDEC_IO_Reg->cdiop[ui8CdipIdx];

	stCdiop[ui8CdipIdx].dtype      	= eSdecStreamMode;//staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipDtype;
	stCdiop[ui8CdipIdx].sync_type  	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipSyncType;
	//reg_sdec_io->cdip[SdecCdipIdx].f.ba_val_dis 		= staSdecCdipConfSet[stpSdecParam->ui8InputSetIdx].eSdecCdipBaSop;
	//reg_sdec_io->cdip[eSdecCdipIdx].f.ba_val_dis 		= staSdecCdipConfSet[stpSdecParam->ui8InputSetIdx].eSdecCdipBaVal;
	stCdiop[ui8CdipIdx].clk_div    		= staSdecCdipConfInSet[ui8CdipIdx].ui32ClkDiv;
	//reg_sdec_io->cdip[eSdecCdipIdx].f.ba_clk_dis	 	= eSdecCdipBaClk;
	stCdiop[ui8CdipIdx].pconf      		= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipPconf;
	stCdiop[ui8CdipIdx].req_en    	 	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipReqEn;
	stCdiop[ui8CdipIdx].val_en     	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipValEn;
	stCdiop[ui8CdipIdx].err_en     	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipErrEn;
	stCdiop[ui8CdipIdx].req_act_lo 	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipReqPol;
	stCdiop[ui8CdipIdx].val_act_lo 	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipValPol;
	stCdiop[ui8CdipIdx].clk_act_lo 	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipClkPol;
	stCdiop[ui8CdipIdx].err_act_hi 	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipErrPol;
	stCdiop[ui8CdipIdx].test_en    	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipTestEn;
	stCdiop[ui8CdipIdx].en         	= staSdecCdipConfInSet[ui8CdipIdx].eSdecCdipEn;


	stpSdecParam->stSDEC_IO_Reg->cdiop[ui8CdipIdx] = stCdiop[ui8CdipIdx];

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_CdipConfInSet");

	eRet = OK;

exit:
	return (eRet);
}
#endif

/**
********************************************************************************
* @brief
*   SDEC core input port setting.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterAlloc
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	LX_SDEC_PIDFLT_ALLOC_T *stpLXSdecPIDFltAlloc;

	UINT8 ui8Ch = 0x0;
	UINT8 ui8PidIdx = 0x0;
	UINT16 ui16Pid = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterAlloc");

	stpLXSdecPIDFltAlloc = (LX_SDEC_PIDFLT_ALLOC_T *)ui32Arg;

	ui8Ch 	= stpLXSdecPIDFltAlloc->eCh;
	ui16Pid	= stpLXSdecPIDFltAlloc->uiPidValue;

	eResult = SDEC_PIDIdxCheck(stpSdecParam, ui8Ch, &ui8PidIdx, stpLXSdecPIDFltAlloc->ePidFltMode, ui16Pid);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] returned PID Idx:[%d]", ui8Ch, ui8PidIdx);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_SelPidFilterIdx failed:[%d]", eResult);
	}

	stpLXSdecPIDFltAlloc->uiPidFltId = ui8PidIdx;

	/* copy parameters to user space */
#if 0
	eResult = copy_to_user((void *)ui32Arg,&stpLXSdecPIDFltAlloc,sizeof(LX_SDEC_PIDFLT_ALLOC_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterAlloc");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);

	return (eRet);
}


/**
********************************************************************************
* @brief
*   SDEC PID idx check.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8pPidIdx :return pid idx
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_PIDIdxCheck
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8ch,
	UINT8 *ui8pPidIdx,
	LX_SDEC_PIDFLT_MODE_T ePidFltMode,
	UINT16 ui16PidValue )
{
	DTV_STATUS_T 	eRet 			= OK;
	UINT8 			ui8Count 		= 0x0;
	UINT8 			ui8PidfNum		= 0x0;
	UINT8 			ui8FltMode 	= 0x0;
	BOOLEAN 		bFind		 	= FALSE;
	UINT32			ui32PidfData	= 0x0;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_PIDIdxCheck");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	ui8FltMode = ePidFltMode;

	if( ui8ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8ch);
		goto exit;
	}

	/* get pid filter number from channel info structure */
	ui8PidfNum = pSdecConf->chInfo[ui8ch].num_pidf;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		/* Check CH_C */
		if( pSdecConf->chInfo[ui8ch].capa_lev == 0)
		{
			for(ui8Count = 0; ui8Count < ui8PidfNum; ui8Count++)
			{

				/* Check if there is same pid filter */
				ui32PidfData = SDEC_HAL_CDIC2PIDFGetPidfData(ui8Count);
				if( ui16PidValue == ( ui32PidfData & 0x1FFF ) )
				{
					SDEC_DEBUG_Print( "Same PID is exist!!!! pidval[%04x] idx[%2d]", ui16PidValue, ui8Count );

					/* if there is same pid filter, clear!! */
					SDEC_Pidf_Clear(stpSdecParam, ui8ch, ui8Count);
					stpSdecParam->stPIDMap[ui8ch][ui8Count].used = 0x0;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].flag = FALSE;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].mode = 0x0;
					//stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.w = 0x0;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_FREE = 0x0;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x0;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_OVERFLOW = 0x0;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x0;
				}

				if( (stpSdecParam->stPIDMap[ui8ch][ui8Count].used) == 0x0)
				{
					stpSdecParam->stPIDMap[ui8ch][ui8Count].used = 0x1;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].mode = ui8FltMode;
					//empty GPB idx set
					//stpSdecParam->stPIDMap[ui8ch][ui8Count].flag = TRUE;
					stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x1;
					*ui8pPidIdx = ui8Count;
					bFind = TRUE;

					/* 테스트 결과, 앞에 있는 pid filter 만 Check해도 될 듯. */
					break;
				}
			}

			goto check_find;
		}
	}

	for(ui8Count = 0; ui8Count < ui8PidfNum; ui8Count++)
	{

		/* Check if there is same pid filter */
#ifdef NOT_USE_PIDF_SPINLOCK
		ui32PidfData = SDEC_HAL_PIDFGetPidfData(ui8ch, ui8Count);
#else
		ui32PidfData = SDEC_GetPidfData(stpSdecParam, ui8ch, ui8Count);
#endif
		if( ui16PidValue == ( ( ui32PidfData >> 16 ) & 0x1FFF) )
		{
			SDEC_DEBUG_Print( "Same PID is exist!!!! pidval[%04x] idx[%2d]", ui16PidValue, ui8Count );

			/* if there is same pid filter, clear!! */
			SDEC_Pidf_Clear(stpSdecParam, ui8ch, ui8Count);
			stpSdecParam->stPIDMap[ui8ch][ui8Count].used = 0x0;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].flag = FALSE;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].mode = 0x0;
			//stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.w = 0x0;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_FREE = 0x0;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x0;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_OVERFLOW = 0x0;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x0;
		}

		if( (stpSdecParam->stPIDMap[ui8ch][ui8Count].used) == 0x0)
		{
			stpSdecParam->stPIDMap[ui8ch][ui8Count].used = 0x1;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].mode = ui8FltMode;
			//empty GPB idx set
			//stpSdecParam->stPIDMap[ui8ch][ui8Count].flag = TRUE;
			stpSdecParam->stPIDMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x1;
			*ui8pPidIdx = ui8Count;
			bFind = TRUE;

			/* 테스트 결과, 앞에 있는 pid filter 만 Check해도 될 듯. */
			break;
		}
	}

check_find:
	if(bFind == FALSE )
	{
		SDEC_DEBUG_Print( RED_COLOR"Ch[%d] PID filter alloc failed"NORMAL_COLOR, ui8ch);
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_PIDIdxCheck");

	eRet = OK;

exit:
	return (eRet);
}

/**
********************************************************************************
* @brief
*   SDEC Sec idx check.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8pPidIdx :return Sec idx
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_SecIdxCheck
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT8 ui8ch,
	UINT8 *ui8pSecIdx)
{
	DTV_STATUS_T 	eRet = OK;

	UINT8 			ui8SecfNum		= 0x0;
	UINT8 			ui8Count 		= 0x0;
	BOOLEAN 		bBufFullFlag 	= FALSE;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_SecIdxCheck");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	if( ui8ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8ch);
		goto exit;
	}

	/* get section filter number from channel info structure */
	ui8SecfNum = pSdecConf->chInfo[ui8ch].num_secf;

	if( ui8ch < LX_SDEC_CH_C )
	{
		/* gaius.lee 2011.06.08
		 * set this because of problem in L8 & L9 A0
		 * there is h/w issue in GPB0, so we shall not use GPB0
		 */
		//if (lx_chip_rev() <= LX_CHIP_REV(L9, A1)) 	ui8Count = 1;
		//else											ui8Count = 0;
		/* gaius.lee 2012.01.05
		 * upper issue is still in L9 B0
		 */
		ui8Count = 1;

		//sec filter map check
		for(; ui8Count < ui8SecfNum; ui8Count++)
		{
			if((stpSdecParam->stSecMap[ui8ch][ui8Count].used) == 0x0)
			{
				stpSdecParam->stSecMap[ui8ch][ui8Count].used = 0x1;
				//empty GPB idx set
				//stpSdecParam->stSecMap[ui8ch][ui8Count].flag = TRUE;
				stpSdecParam->stSecMap[ui8ch][ui8Count].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x1;

				*ui8pSecIdx = ui8Count;

				bBufFullFlag = TRUE;

				break;
			}
		}
	}
	else
	{
		stpSdecParam->stSecMap[ui8ch][0].used = 0x1;
		stpSdecParam->stSecMap[ui8ch][0].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x1;
		*ui8pSecIdx = 0;
		bBufFullFlag = TRUE;
	}

	//allock fail, buffer full
	if(bBufFullFlag  != TRUE)
	{
		SDEC_DEBUG_Print( RED_COLOR"Ch[%d] Section  filter allock failed"NORMAL_COLOR, ui8ch);
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_SecIdxCheck");

	eRet = OK;

exit:
	return (eRet);
}


/**
********************************************************************************
* @brief
*   SDEC Check Available Section Filter Number
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui8pPidIdx :return Sec idx
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterGetAvailableNumber
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_GET_AVAIL_NUMBER_T *stpLXSdecSecFltAvailNum;
	UINT8 			ui8SecfNum		= 0x0;
	UINT8 			ui8Count 		= 0x0;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;


	UINT8 	ui8Ch = 0x0;
	UINT32 	uiAvailFilter = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterGetAvailableNumber");

	stpLXSdecSecFltAvailNum =(LX_SDEC_SECFLT_GET_AVAIL_NUMBER_T *)ui32Arg;

	ui8Ch = (UINT8)stpLXSdecSecFltAvailNum->eCh;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	if( ui8Ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8Ch);
		goto exit;
	}

	/* get section filter number from channel info structure */
	ui8SecfNum = pSdecConf->chInfo[ui8Ch].num_secf;

	if( ui8Ch < LX_SDEC_CH_C )
	{
		/* gaius.lee 2011.06.08
		 * set this because of problem in L8 & L9 A0
		 * there is h/w issue in GPB0, so we shall not use GPB0
		 */
		//if (lx_chip_rev() <= LX_CHIP_REV(L9, A1)) 	ui8Count = 1;
		//else											ui8Count = 0;
		/* gaius.lee 2012.01.05
		 * upper issue is still in L9 B0
		 */
		ui8Count = 1;

		//sec filter map check
		for(; ui8Count < ui8SecfNum; ui8Count++)
		{
			if((stpSdecParam->stSecMap[ui8Ch][ui8Count].used) == 0x0)
			{
				uiAvailFilter++;
			}
		}
	}
	else
	{
		uiAvailFilter = 1;
	}

	/* set return value */
	stpLXSdecSecFltAvailNum->uiAvailFilter = uiAvailFilter;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterGetAvailableNumber");

	eRet = OK;

exit:
	return (eRet);
}


/**
********************************************************************************
* @brief
*   SDEC PID filter free.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterFree
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_FREE_T *stpLXSdecPIDFltFree;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterFree");

	stpLXSdecPIDFltFree =(LX_SDEC_PIDFLT_FREE_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltFree->eCh;
	ui32PidFltId = stpLXSdecPIDFltFree->uiPidFltId;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] PidFltId[%d] Free", ui8Ch, ui32PidFltId);

	SDEC_Pidf_Clear(stpSdecParam, ui8Ch, ui32PidFltId);

	//PID Map init
	stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].used = 0x0;
	stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].flag = FALSE;
	stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].mode = 0x0;
	stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].stStatusInfo.w = 0x0;
	stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x0;

#if 0
	/* copy parameters from user space */
	eResult = copy_from_user(&ui32Arg,
		(void *)ui32Arg,
		sizeof(ui32Arg));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterFree");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   SDEC PID filter set.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterSetPID
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_SET_PID_T *stpLXSdecPIDFltSetPID;
	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	UINT32 ui32PidValue = 0x0;
	UINT32 ui32PidfData = 0x0;
	UINT32 ui32PidfDest = (DEST_RESERVED);
	UINT32 ui32dest= 0x0;
	LX_SDEC_CFG_T* pSdecConf = NULL;
	BOOLEAN	bSection = FALSE;
	BOOLEAN bEnable = TRUE;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterSetPID");

	stpLXSdecPIDFltSetPID = (LX_SDEC_PIDFLT_SET_PID_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltSetPID->eCh;
	ui32PidFltId = stpLXSdecPIDFltSetPID->uiPidFltId;
	ui32PidValue = stpLXSdecPIDFltSetPID->uiPidValue;
	ui32dest = stpLXSdecPIDFltSetPID->uiDest;
	bSection = stpLXSdecPIDFltSetPID->bSection;
	bEnable = stpLXSdecPIDFltSetPID->bEnable;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "filter type:[%08x]", ui32dest);

	/* get config */
	pSdecConf = SDEC_CFG_GetConfig();

	if( ui8Ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8Ch);
		goto exit;
	}

	/* from H13 A0, CDIC2 has 4 pid filters */
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if( pSdecConf->chInfo[ui8Ch].capa_lev == 0 )
		{
			SDEC_HAL_CDIC2PIDFSetPidfData(ui32PidFltId, ui32PidValue);
			SDEC_HAL_CDIC2PIDFEnablePidFilter(ui32PidFltId, SDEC_HAL_ENABLE);	/* seperate enable as L9 correction */
			SDEC_SWP_SetPID(ui32PidFltId, ui32PidValue);
			goto exit_without_error;
		}
	}
	else
	{
		/* if this channel is simple channel, just set ts2pes parser and exit */
		if( pSdecConf->chInfo[ui8Ch].capa_lev == 0)
		{
			//stpSdecParam->stSDEC_IO_Reg->cdic2_ts2pes.PID = ui32PidValue;
			SDEC_HAL_SetTs2PesPid(ui32PidValue);
			goto exit_without_error;
		}
	}

	/* saving stcc_asg value for later */
	//stcc_asg =stpSdecParam->stSDEC_IO_Reg->stcc_asg;

	/* setting PID */
	ui32PidfData = PID(ui32PidValue);

	if(ui32dest & LX_SDEC_PIDFLT_DEST_VDEC0)
	{
		ui32PidfData |= PAYLOAD_PES;
		ui32PidfDest = VID_DEV0;

		/* setting stc reference of vid0 to current channel */
		//stcc_asg.vid0 = ui8Ch;
		SDEC_HAL_STCCSetVideoAssign(0, ui8Ch);

		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] VID0 PidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}
	else if(ui32dest & LX_SDEC_PIDFLT_DEST_VDEC1)
	{
		ui32PidfData |= PAYLOAD_PES;
		ui32PidfDest = VID_DEV1;

		/* setting stc reference of vid1 to current channel */
		//stcc_asg.vid1 = ui8Ch;
		SDEC_HAL_STCCSetVideoAssign(1, ui8Ch);

		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] VID1 PidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}
	else if(ui32dest & LX_SDEC_PIDFLT_DEST_ADEC0)
	{
		ui32PidfData |= PAYLOAD_PES;
		ui32PidfDest = AUD_DEV0;

		/* setting stc reference of vid1 to current channel */
		//stcc_asg.aud0 = ui8Ch;
		SDEC_HAL_STCCSetAudioAssign(0, ui8Ch);

		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] AUD0 PidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}
	else if(ui32dest & LX_SDEC_PIDFLT_DEST_ADEC1)
	{
		ui32PidfData |= PAYLOAD_PES;
		ui32PidfDest = AUD_DEV1;

		/* setting stc reference of vid1 to current channel */
		//stcc_asg.aud1 = ui8Ch;
		SDEC_HAL_STCCSetAudioAssign(1, ui8Ch);

		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] AUD1 PidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}
	else if(ui32dest & LX_SDEC_PIDFLT_DEST_GPB)
	{
		//for section filter map enable
		// SF_MAN_EN은 map select에서 한다.
		ui32PidfDest = DEST_RESERVED;
		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] GPBPidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}
	else if(ui32dest & LX_SDEC_PIDFLT_DEST_RAWTS)
	{
		//for saving raw ts
		ui32PidfData |= TS_DN;
		ui32PidfDest = DEST_RESERVED;
		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] GPBPidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}
	else if(ui32dest & LX_SDEC_PIDFLT_DEST_OTHER)
	{
		ui32PidfDest = DEST_RESERVED;
		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] GPBPidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}

	/* setting stcc_asg value */
	//stpSdecParam->stSDEC_IO_Reg->stcc_asg = stcc_asg;

	if( ui32dest & LX_SDEC_PIDFLT_DEST_DVR )
	{
		/* To delete PAYLOAD_PES for Section Download - for JP 2013.02.04 jinhwan.bae */
		//ui32PidfData |= PAYLOAD_PES;
		/* jinhwan.bae 2013. 02.17
		    Purpose : Support Section Download and Parsing at the same time, for netcast4.0 JP
		    Reason  : To support this, remove PLOAD_PES at download set pid.
		                  But Video Data is inserted to Section GPB
		    WorkAround : To divide set value as Section/PES type.
		                       If PES, set PLOAD_PES at download set pid. so need flag bSection */
		if(bSection == TRUE)
		{
			/* Not Insert PLOAD_PES at Download */
		}
		else
		{
			/* Insert PLOAD_PES at Download */
			ui32PidfData |= PAYLOAD_PES;
		}
		
		ui32PidfData |= DL_EN;

		SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] DVR PidFltId[%d] PidValue[0x%08x]", ui8Ch, ui32PidFltId, ui32PidValue);
	}

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] ui32PidfData[0x%08x] PidValue[0x%08x]", ui8Ch, ui32PidfData, ui32PidfDest);

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx 	= ui32PidFltId;
	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data 	= ( DEC_EN | ui32PidfData | ui32PidfDest );

	if(bEnable == TRUE)
	{
#ifdef NOT_USE_PIDF_SPINLOCK
		SDEC_HAL_PIDFSetPidfData(ui8Ch, ui32PidFltId, DEC_EN | ui32PidfData | ui32PidfDest );
#else
		SDEC_SetPidfData(stpSdecParam, ui8Ch, ui32PidFltId, DEC_EN | ui32PidfData | ui32PidfDest );
#endif
	}
	else
	{
#ifdef NOT_USE_PIDF_SPINLOCK
		SDEC_HAL_PIDFSetPidfData(ui8Ch, ui32PidFltId, ui32PidfData | ui32PidfDest );
#else
		SDEC_SetPidfData(stpSdecParam, ui8Ch, ui32PidFltId, ui32PidfData | ui32PidfDest );
#endif
	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

#if 0
	/* copy parameters from user space */
	eResult = copy_from_user(&ui32Arg,
		(void *)ui32Arg,
		sizeof(ui32Arg));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */

exit_without_error:
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterSetPID");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}


/**
********************************************************************************
* @brief
*   SDEC PID filter map select.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterMapSelect
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_SELSECFLT_T *stpLXSdecPIDFltSelect;
	LX_SDEC_CFG_T* 	pSdecConf 		= NULL;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	UINT32 ui32SecFltId = 0x0;
	UINT32 pidf_data = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterMapSelect");

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	stpLXSdecPIDFltSelect = (LX_SDEC_PIDFLT_SELSECFLT_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltSelect->eCh;
	ui32PidFltId = stpLXSdecPIDFltSelect->uiPidFltId;
	ui32SecFltId = stpLXSdecPIDFltSelect->uiSecFltId;

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx = ui32PidFltId;
	//pidf_data = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data;

#ifdef NOT_USE_PIDF_SPINLOCK
	pidf_data = SDEC_HAL_PIDFGetPidfData(ui8Ch, ui32PidFltId);
#else
	pidf_data = SDEC_GetPidfData(stpSdecParam, ui8Ch, ui32PidFltId);
#endif

	/* If PES mode, section filter is not used, But for simple structure, use section filter */
	if(	stpLXSdecPIDFltSelect->eGpbMode == LX_SDEC_PIDFLT_GPB_MODE_PES )
	{
		/* Disconnect section filter connection and remove destination */
		pidf_data &= ~ ( SF_MAN_EN | DEST );

		/* Enable PES_Paylod and link gpd index */
		pidf_data |=  PAYLOAD_PES | ui32SecFltId;

		/* For PES H/W bug workaound. See @LX_SDEC_USE_KTHREAD_PES */
	#if	( LX_SDEC_USE_KTHREAD_PES == 1)
		if(pSdecConf->noPesBug == 0 )
		{
			/* if there is pes h/w buf, do it */
			/* added TS_DN. Gather TS packet and parse manually */
			pidf_data |=  PAYLOAD_PES | TS_DN | ui32SecFltId;

			SDEC_PES_SetPESFlt(ui8Ch, ui32SecFltId);
			SDEC_PES_SetDstBuf(stpSdecParam, ui8Ch, ui32SecFltId);
		}
	#endif
	}
	else if ( stpLXSdecPIDFltSelect->eGpbMode == LX_SDEC_PIDFLT_GPB_MODE_RAWTS )
	{
		/* Disconnect section filter connection and remove destination */
		pidf_data &= ~ ( SF_MAN_EN | DEST );

		/* Enable PES_Paylod and link gpd index */
		pidf_data |=  PAYLOAD_PES | GPB_IRQ_CONF | TS_DN | ui32SecFltId;
	}
	else
	{
		/* connect section filter connection */
		pidf_data |= SF_MAN_EN;

		#if 0
		/* map the section filter to pid filter.
		 n /2 th pid filter is mapped to mth bit section filter. */
		if(ui32SecFltId < 32)
			//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui32PidFltId*2].secf_map |= (0x1 << ui32SecFltId);
		/* (n /2 + 1) th pid filter is mapped to (m + 32) th bit section filter.  because one register can handle only 32-bits*/
		else
			//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui32PidFltId*2 + 1].secf_map |= (0x1 << (ui32SecFltId%32));
		#endif
	
		SDEC_HAL_SECFSetMapBit(ui8Ch, ui32PidFltId, ui32SecFltId);
	}

	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx = ui32PidFltId;
	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data = pidf_data;
#ifdef NOT_USE_PIDF_SPINLOCK
	SDEC_HAL_PIDFSetPidfData(ui8Ch, ui32PidFltId, pidf_data);
#else
	SDEC_SetPidfData(stpSdecParam, ui8Ch, ui32PidFltId, pidf_data);
#endif

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui8PidFltIdx = ui32PidFltId;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].flag = true;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x1;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] SecMap true flag idx[%d]", ui8Ch, ui32SecFltId);




#if 0
	/* copy parameters from user space */
	eResult = copy_from_user(&ui32Arg,
		(void *)ui32Arg,
		sizeof(ui32Arg));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterMapSelect");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
		
	return (eRet);
}

/**
********************************************************************************
* @brief
*   SDEC PID filter enable or disable.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterEnable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_ENABLE_T *stpLXSdecPIDFltEnable;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	BOOLEAN bPidFltEnable = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterEnable");

	stpLXSdecPIDFltEnable = (LX_SDEC_PIDFLT_ENABLE_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltEnable->eCh;
	ui32PidFltId = stpLXSdecPIDFltEnable->uiPidFltId;
	bPidFltEnable = stpLXSdecPIDFltEnable->bPidFltEnable;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] FltId[%d] flag[0x%08x]", ui8Ch, ui32PidFltId, bPidFltEnable);

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx = ui32PidFltId;

	switch (bPidFltEnable)
	{
		case TRUE:
			//set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data, 31);
			if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
			{
				if(ui8Ch == LX_SDEC_CH_C) 	SDEC_HAL_CDIC2PIDFEnablePidFilter(ui32PidFltId, SDEC_HAL_ENABLE);	/* seperate enable as L9 correction */
				else
                {
#ifdef NOT_USE_PIDF_SPINLOCK
					SDEC_HAL_PIDFEnable(ui8Ch, ui32PidFltId, SDEC_HAL_ENABLE);
#else
					SDEC_SetPidf_Enable(stpSdecParam, ui8Ch, ui32PidFltId, SDEC_HAL_ENABLE);
#endif
                }
			}
			else
			{
#ifdef NOT_USE_PIDF_SPINLOCK
				SDEC_HAL_PIDFEnable(ui8Ch, ui32PidFltId, SDEC_HAL_ENABLE);
#else
				SDEC_SetPidf_Enable(stpSdecParam, ui8Ch, ui32PidFltId, SDEC_HAL_ENABLE);
#endif
			}
			stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x1;
			stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].flag = TRUE;

		break;
		case FALSE:
			//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data, 31);
			if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
			{
				if(ui8Ch == LX_SDEC_CH_C) 	SDEC_HAL_CDIC2PIDFEnablePidFilter(ui32PidFltId, SDEC_HAL_DISABLE);	/* seperate enable as L9 correction */
				else
				{
#ifdef NOT_USE_PIDF_SPINLOCK
					SDEC_HAL_PIDFEnable(ui8Ch, ui32PidFltId, SDEC_HAL_DISABLE);
#else
					SDEC_SetPidf_Enable(stpSdecParam, ui8Ch, ui32PidFltId, SDEC_HAL_DISABLE);
#endif
				}
			}
			else
			{
#ifdef NOT_USE_PIDF_SPINLOCK
				SDEC_HAL_PIDFEnable(ui8Ch, ui32PidFltId, SDEC_HAL_DISABLE);
#else
				SDEC_SetPidf_Enable(stpSdecParam, ui8Ch, ui32PidFltId, SDEC_HAL_DISABLE);
#endif
			}
			stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x0;
			stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].flag = FALSE;
		break;
		default:
			SDEC_DEBUG_Print("Invalid parameter:[%d]", bPidFltEnable);
			goto exit;
		break;
	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterEnable");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   CRC check scheme of SDEC PID filter enable or disable.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterCRCEnable
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_ENABLE_T *stpLXSdecPIDFltEnable;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	BOOLEAN bPidFltEnable = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterCRCEnable");

	stpLXSdecPIDFltEnable = (LX_SDEC_PIDFLT_ENABLE_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltEnable->eCh;
	ui32PidFltId = stpLXSdecPIDFltEnable->uiPidFltId;
	bPidFltEnable = stpLXSdecPIDFltEnable->bPidFltEnable;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] FltId[%d] flag[0x%08x]", ui8Ch, ui32PidFltId, bPidFltEnable);

	if( bPidFltEnable)
	{
		//CRC set & mtype & valid check
		//set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pes_crc_en[ui8IsHigh].crc16_en, ui32PidFltId);
		SDEC_HAL_PIDFSetCRCBit(ui8Ch, ui32PidFltId);
	}
	else
	{
		//CRC set & mtype & valid check
		//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pes_crc_en[ui8IsHigh].crc16_en, ui32PidFltId);
		SDEC_HAL_PIDFClearCRCBit(ui8Ch, ui32PidFltId);
	}

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterCRCEnable");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   SDEC PID filter get state.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterGetState
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_STATE_T *stpLXSdecPIDFltState;
	//PIDF_DATA stPIDfData;
	UINT32	pidfData = 0x0;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	LX_SDEC_CFG_T* pSdecConf = NULL;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterGetState");

	stpLXSdecPIDFltState = (LX_SDEC_PIDFLT_STATE_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltState->eCh;
	ui32PidFltId = stpLXSdecPIDFltState->uiPidFltId;

	/* get config */
	pSdecConf = SDEC_CFG_GetConfig();

	if( ui8Ch >= pSdecConf->nChannel )
	{
		SDEC_DEBUG_Print("over channel range %d", ui8Ch);
		goto exit;
	}

	/* from H13 A0, CDIC2 has 4 pid filters */
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if( pSdecConf->chInfo[ui8Ch].capa_lev == 0 )
		{
			stpLXSdecPIDFltState->uiPidValue = SDEC_HAL_CDIC2PIDFGetPidfData(stpLXSdecPIDFltState->uiPidFltId);
			stpLXSdecPIDFltState->bDec_en	= SDEC_HAL_CDIC2GetPIDFEnable(stpLXSdecPIDFltState->uiPidFltId);

			/* jinhwan.bae more information need? */

			goto exit_without_error;
		}
	}
	else
	{
		/* if this channel is simple channel, just get PID and exit */
		if( pSdecConf->chInfo[ui8Ch].capa_lev == 0)
		{
			//stpLXSdecPIDFltState->uiPidValue  = stpSdecParam->stSDEC_IO_Reg->cdic2_ts2pes.PID;
			stpLXSdecPIDFltState->uiPidValue  = SDEC_HAL_GetTs2PesPid();
			goto exit_without_error;
		}
	}

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx = stpLXSdecPIDFltState->uiPidFltId;
	//stPIDfData = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data;
#ifdef NOT_USE_PIDF_SPINLOCK
	pidfData = SDEC_HAL_PIDFGetPidfData(ui8Ch, stpLXSdecPIDFltState->uiPidFltId);
#else
	pidfData = SDEC_GetPidfData(stpSdecParam, ui8Ch, stpLXSdecPIDFltState->uiPidFltId);
#endif

	//auto increment enalbe
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	//SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	stpLXSdecPIDFltState->uiPidValue = extract_bits(pidfData, 0x1FFF, 16);/**< out - setted PID Value of PID Filter */

	stpLXSdecPIDFltState->bDec_en	= extract_bits(pidfData, 0x1, 31);
	stpLXSdecPIDFltState->bDl_en	= extract_bits(pidfData, 0x1, 30);
	stpLXSdecPIDFltState->bPload_pes= extract_bits(pidfData, 0x1, 12);
	stpLXSdecPIDFltState->bSf_map_en= extract_bits(pidfData, 0x1, 11);
	stpLXSdecPIDFltState->uiDest	= extract_bits(pidfData, 0x7f, 0);

	//stpLXSdecPIDFltState->uiSecf_map[0] = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui32PidFltId*2].secf_map;
	//stpLXSdecPIDFltState->uiSecf_map[1] = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui32PidFltId*2 + 1].secf_map;
	stpLXSdecPIDFltState->uiSecf_map[0] = SDEC_HAL_SECFGetMap(ui8Ch, ui32PidFltId*2);
	stpLXSdecPIDFltState->uiSecf_map[1] = SDEC_HAL_SECFGetMap(ui8Ch, ui32PidFltId*2 + 1);

//if(stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].flag != TRUE)
//	{
	stpLXSdecPIDFltState->uiFltState = stpSdecParam->stPIDMap[ui8Ch][ui32PidFltId].stStatusInfo.w;/**< out - Status of PID filter.  @see LX_SDEC_FLTSTATE_T */
//	}

	stpLXSdecPIDFltState->uiRegValue = pidfData;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] pididx[%d] value[0x%08x]", ui8Ch, ui32PidFltId, stpLXSdecPIDFltState->uiPidValue);

	/*should check*/
//	stpLXSdecPIDFltState->uiFltState =

	/* copy parameters to user space */
#if 0
	eResult = copy_to_user((void *)ui32Arg,&stpLXSdecPIDFltState,sizeof(LX_SDEC_PIDFLT_STATE_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */

exit_without_error:
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterGetState");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}

/**
********************************************************************************
* @brief
*   SDEC PID filter enable or disable.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterEnableSCMBCHK
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_ENABLE_T *stpLXSdecPIDFltEnable;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	BOOLEAN bPidFltEnable = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterEnable");

	stpLXSdecPIDFltEnable = (LX_SDEC_PIDFLT_ENABLE_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltEnable->eCh;
	ui32PidFltId = stpLXSdecPIDFltEnable->uiPidFltId;
	bPidFltEnable = stpLXSdecPIDFltEnable->bPidFltEnable;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] FltId[%d] flag[0x%08x]", ui8Ch, ui32PidFltId, bPidFltEnable);

#if 0
	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx = ui32PidFltId;

	switch (bPidFltEnable)
	{
		case TRUE:
			set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data, 15);

		break;
		case FALSE:
			clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data, 15);
		break;
		default:
			SDEC_DEBUG_Print("Invalid parameter:[%d]", bPidFltEnable);
			goto exit;
		break;
	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);
#endif
	// jinhwan.bae for No Audio Issue, 2012.04.26 SSDEC_HAL_PIDFScrambleCheck(ui8Ch, ui32PidFltId, bPidFltEnable);
	// replaced following spin lock I/F
	SDEC_SetPidf_TPI_IEN_Enable(stpSdecParam, ui8Ch, ui32PidFltId, bPidFltEnable);

	/* enable tp interrupt */
	if(bPidFltEnable)
		SDEC_HAL_TPISetIntrPayloadUnitStartIndicator(ui8Ch, SDEC_HAL_ENABLE);
	else
		SDEC_HAL_TPISetIntrPayloadUnitStartIndicator(ui8Ch, SDEC_HAL_DISABLE);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterEnable");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   Enable download as SDEC PID filter
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PIDFilterEnableDownload
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_PIDFLT_ENABLE_T *stpLXSdecPIDFltEnable;
	UINT8 ui8Ch = 0x0;
	UINT32 ui32PidFltId = 0x0;
	UINT8  bEnable = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PIDFilterEnableDownload");

	stpLXSdecPIDFltEnable = (LX_SDEC_PIDFLT_ENABLE_T *)ui32Arg;

	ui8Ch = stpLXSdecPIDFltEnable->eCh;
	ui32PidFltId = stpLXSdecPIDFltEnable->uiPidFltId;
	bEnable = stpLXSdecPIDFltEnable->bPidFltEnable;

#if 0
	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	/* Get current setting data from register */
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx 	= ui32PidFltId;

	ui32PidfData = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data;

	/* Enable download */
	if( bEnable )		ui32PidfData |=  DL_EN;
	else 				ui32PidfData &= ~DL_EN;

	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_addr.pidf_idx 	= ui32PidFltId;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->pidf_data.pidf_data 	= ui32PidfData;
#endif

#ifdef NOT_USE_PIDF_SPINLOCK
	SDEC_HAL_PIDFDownloadEnable(ui8Ch, ui32PidFltId, bEnable);
#else
	SDEC_SetPidf_DN_Enable(stpSdecParam, ui8Ch, ui32PidFltId, bEnable);
#endif

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PIDFilterEnableDownload");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);

	return (eRet);

}


//from here for section filter

/**
********************************************************************************
* @brief
*   SDEC Section filter alloc.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterAlloc
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	LX_SDEC_SECFLT_ALLOC_T *stpLXSdecSecFltAlloc;

	UINT8 ui8Ch = 0x0;
	UINT8 ui8SecIdx = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterAlloc");

	stpLXSdecSecFltAlloc = (LX_SDEC_SECFLT_ALLOC_T *)ui32Arg;

	ui8Ch = stpLXSdecSecFltAlloc->eCh;

	eResult = SDEC_SecIdxCheck(stpSdecParam, ui8Ch, &ui8SecIdx);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] returned Section PID Idx:[%d]", ui8Ch, ui8SecIdx);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_SelSecFilterIdx failed:[%d]", eResult);
		goto exit;
	}

	stpLXSdecSecFltAlloc->uiSecFltId = ui8SecIdx;

#if 0
	/* copy parameters to user space */
	eResult = copy_to_user((void *)ui32Arg,&stpLXSdecSecFltAlloc,sizeof(LX_SDEC_SECFLT_ALLOC_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterAlloc");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/* Work Around for si11~ stream, PMT updated stream but all client request/cancel independantly
    so, MHEG DSMCC and Subtitle with same PID are enabled, and Subtitle Canceled
    But PES_PLOAD is not removed in PID filter, so, abnormal situation happened. */
/**
********************************************************************************
* @brief
*   SDEC PES filter free.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_PESFilterFree
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_FREE_T *stpLXSecPIDFltFree;
	LX_SDEC_CFG_T* pSdecConf = NULL;

	UINT8 ui8Ch = 0x0;//, ui8IsHigh = 0x0;
	UINT32 ui32SecFltId = 0x0;
	UINT32 ui8PidFltIdx = 0x0;

	unsigned long flags = 0;

	UINT32 pidf_data = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_PESFilterFree");

	stpLXSecPIDFltFree =(LX_SDEC_SECFLT_FREE_T *)ui32Arg;

	ui8Ch = stpLXSecPIDFltFree->eCh;
	ui32SecFltId = stpLXSecPIDFltFree->uiSecFltId;

	ui8PidFltIdx = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui8PidFltIdx;

	/* work around */
#ifdef NOT_USE_PIDF_SPINLOCK
	pidf_data = SDEC_HAL_PIDFGetPidfData(ui8Ch, ui8PidFltIdx);
#else
	pidf_data = SDEC_GetPidfData(stpSdecParam, ui8Ch, ui8PidFltIdx);
#endif

	/* Clear PAYLOAD_PES Fields */
	pidf_data &= ~ ( PAYLOAD_PES | DEST );
	pidf_data |= DEST_RESERVED; /* 4F */

#ifdef NOT_USE_PIDF_SPINLOCK
	SDEC_HAL_PIDFSetPidfData(ui8Ch, ui8PidFltIdx, pidf_data);
#else
	SDEC_SetPidfData(stpSdecParam, ui8Ch, ui8PidFltIdx, pidf_data);
#endif

	/* set high bit */
	//if(ui32SecFltId < 32)	ui8IsHigh = 0x0;
	//else					ui8IsHigh = 0x1;

	/* Clear secion filter map register */
	//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui8PidFltIdx * 2 + ui8IsHigh].secf_map, (ui32SecFltId%32));
	if(ui8Ch < LX_SDEC_CH_C)
	{
		SDEC_HAL_SECFClearMapBit(ui8Ch, ui8PidFltIdx, ui32SecFltId);
	}

#if 0
	if(ui32SecFltId < 32)
		stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui8PidFltIdx * 2].secf_map &= ~( 0x1 << ui32SecFltId);
	else
		stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui8PidFltIdx * 2 + 1].secf_map &= ~( 0x1 << (ui32SecFltId%32));
#endif

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] PesFltId[%d] Free", ui8Ch, ui32SecFltId);

	SDEC_GPB_LOCK(stpSdecParam, ui8Ch, ui32SecFltId);

	/* delete msge in notify queue */
	SDEC_DeleteInNotify(stpSdecParam, ui8Ch, ui32SecFltId);

	//Section Filter  Map init
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].used = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].flag = FALSE;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].mode = 0x0;

	SDEC_Secf_Clear(stpSdecParam, ui8Ch, ui32SecFltId);

	// LJH_GPB
	pSdecConf = SDEC_CFG_GetConfig();
	/* 2012.02.06 gaius.lee
	 * Bug exist in L9 HW.
	 * While CPU access Read/Write/Bound Register, SDEC HW accesses write register, write pointer goes to read/write/bound regitser which CPU access.
	 * So, we make GPB map as static. That's why we disable this section. */
	if((pSdecConf->staticGPB == 0) || (ui8Ch == LX_SDEC_CH_C))
	{
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Baseptr 	= 0x00000000;
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Endptr	= 0x00000000;
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Readptr 	= 0x00000000;
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32UsrReadptr 	= 0x00000000;
	}
	stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui8PidFltIdx	= 0x0;

	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.w = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_OVERFLOW = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_DATAREADY = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_SCRAMBLED = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x0;

	/* clear full buffer interrupt */
	if(ui8Ch < LX_SDEC_CH_C)
	{
		SDEC_HAL_GPBClearFullIntr(ui8Ch,	ui32SecFltId);
	}

	SDEC_GPB_UNLOCK(stpSdecParam, ui8Ch, ui32SecFltId);

#if 0
	/* copy parameters from user space */
	eResult = copy_from_user(&ui32Arg,
		(void *)ui32Arg,
		sizeof(ui32Arg));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_PESFilterFree");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   SDEC Section filter free.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterFree
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_FREE_T *stpLXSecPIDFltFree;
	LX_SDEC_CFG_T* pSdecConf = NULL;

	UINT8 ui8Ch = 0x0;//, ui8IsHigh = 0x0;
	UINT32 ui32SecFltId = 0x0;
	UINT32 ui8PidFltIdx = 0x0;

	unsigned long flags = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterFree");

	stpLXSecPIDFltFree =(LX_SDEC_SECFLT_FREE_T *)ui32Arg;

	ui8Ch = stpLXSecPIDFltFree->eCh;
	ui32SecFltId = stpLXSecPIDFltFree->uiSecFltId;

	ui8PidFltIdx = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui8PidFltIdx;

	/* set high bit */
	//if(ui32SecFltId < 32)	ui8IsHigh = 0x0;
	//else					ui8IsHigh = 0x1;

	/* Clear secion filter map register */
	//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui8PidFltIdx * 2 + ui8IsHigh].secf_map, (ui32SecFltId%32));
	if(ui8Ch < LX_SDEC_CH_C)
	{
		SDEC_HAL_SECFClearMapBit(ui8Ch, ui8PidFltIdx, ui32SecFltId);
	}

#if 0
	if(ui32SecFltId < 32)
		stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui8PidFltIdx * 2].secf_map &= ~( 0x1 << ui32SecFltId);
	else
		stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_map[ui8PidFltIdx * 2 + 1].secf_map &= ~( 0x1 << (ui32SecFltId%32));
#endif

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] SecFltId[%d] Free", ui8Ch, ui32SecFltId);

	SDEC_GPB_LOCK(stpSdecParam, ui8Ch, ui32SecFltId);

	/* delete msge in notify queue */
	SDEC_DeleteInNotify(stpSdecParam, ui8Ch, ui32SecFltId);

	//Section Filter  Map init
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].used = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].flag = FALSE;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].mode = 0x0;

	SDEC_Secf_Clear(stpSdecParam, ui8Ch, ui32SecFltId);

	// LJH_GPB
	pSdecConf = SDEC_CFG_GetConfig();
	/* 2012.02.06 gaius.lee
	 * Bug exist in L9 HW.
	 * While CPU access Read/Write/Bound Register, SDEC HW accesses write register, write pointer goes to read/write/bound regitser which CPU access.
	 * So, we make GPB map as static. That's why we disable this section. */
	if((pSdecConf->staticGPB == 0) || (ui8Ch == LX_SDEC_CH_C))
	{
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Baseptr 	= 0x00000000;
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Endptr	= 0x00000000;
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Readptr 	= 0x00000000;
		stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32UsrReadptr 	= 0x00000000;
	}
	stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui8PidFltIdx	= 0x0;

	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.w = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_OVERFLOW = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_DATAREADY = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_SCRAMBLED = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_ENABLE = 0x0;
	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.f.SDEC_FLTSTATE_ALLOC = 0x0;

	/* clear full buffer interrupt */
	if(ui8Ch < LX_SDEC_CH_C)
	{
		SDEC_HAL_GPBClearFullIntr(ui8Ch,	ui32SecFltId);
	}

	SDEC_GPB_UNLOCK(stpSdecParam, ui8Ch, ui32SecFltId);

#if 0
	/* copy parameters from user space */
	eResult = copy_from_user(&ui32Arg,
		(void *)ui32Arg,
		sizeof(ui32Arg));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterFree");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   SDEC Section filter pattern.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterPattern
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_PATTERN_T *stpLXSecFltPattern;

	UINT8 ui8Ch = 0x0;
	UINT8 bHigh = 0x0;
	UINT8 ui8Mode = 0x0;
	UINT32 ui32SecFltId = 0x0;
	UINT32 *ui32pPattern;
	UINT32 *ui32pMask;
	UINT32 *ui32pNeq;
	UINT32 ui32Pattern_L = 0x0;
	UINT32 ui32Pattern_H = 0x0;
	UINT32 ui32Mask_L = 0x0;
	UINT32 ui32Mask_H = 0x0;
	UINT32 ui32Neq_L = 0x0;
	UINT32 ui32Neq_H = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterPattern");

	stpLXSecFltPattern =(LX_SDEC_SECFLT_PATTERN_T *)ui32Arg;

	ui8Ch = stpLXSecFltPattern->eCh;
	ui32SecFltId = stpLXSecFltPattern->uiSecFltId;

	/* if section filter index is higher than 32, sometimes use other register */
	if(ui32SecFltId > 32)	bHigh = 0x1;
	else					bHigh = 0x0;

 	ui8Mode = (UINT8)stpLXSecFltPattern->uiSecFltMode;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		if(ui8Ch == LX_SDEC_CH_C)
		{
			SDEC_SWP_SetSectionFilterPattern(stpLXSecFltPattern);
			stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].mode = ui8Mode;

			SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterPattern");
			OS_UnlockMutex(&stpSdecParam->stSdecMutex);
			return OK;
		}
	}

	ui32pPattern = (UINT32 *)stpLXSecFltPattern->pucPattern;
	ui32pMask = (UINT32 *)stpLXSecFltPattern->pucMask;
	ui32pNeq = (UINT32 *)stpLXSecFltPattern->pucNotEqual;
#if 1
	ui32Pattern_H	= swab32(*ui32pPattern); 	ui32pPattern++;
	ui32Pattern_L	= swab32(*ui32pPattern);
	ui32Mask_H		= swab32(*ui32pMask);		ui32pMask++;
	ui32Mask_L 		= swab32(*ui32pMask);
	ui32Neq_H 		= swab32(*ui32pNeq);		ui32pNeq++;
	ui32Neq_L 		= swab32(*ui32pNeq);
#else
	ui32Pattern_H = *ui32pPattern;
	ui32pPattern++;
	ui32Pattern_L = *ui32pPattern;
	ui32Mask_H = *ui32pMask;
	ui32pMask++;
	ui32Mask_L = *ui32pMask;

	ui32Neq_H = *ui32pNeq;
	ui32pNeq++;
	ui32Neq_L = *ui32pNeq;
#endif

	stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].mode = ui8Mode;

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section Filter Mode:[%d]", ui8Ch, stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].mode);


	//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_mtype[bHigh].secf_mtype, (ui32SecFltId % 32));

	//set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secfb_valid[bHigh].secfb_valid, (ui32SecFltId % 32));
	SDEC_HAL_SECFSetBufValidBit(ui8Ch, ui32SecFltId);

	if( ui8Mode & LX_SDEC_FLTMODE_NOCRCCHK )
	{
		//CRC check disable
		//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->sec_crc_en[bHigh].crc_en, (ui32SecFltId % 32));
		SDEC_HAL_SECFClearCRCBit(ui8Ch, ui32SecFltId);
	}
	else
	{
		//CRC check enable
		//clear__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->sec_crc_en[bHigh].crc_en, (ui32SecFltId % 32));
		SDEC_HAL_SECFSetCRCBit(ui8Ch, ui32SecFltId);
	}

#if 0
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_mtype[0x0].secf_mtype = 0xFFFFFFFF;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_mtype[0x1].secf_mtype = 0xFFFFFFFF;
	//the use of sec filter gpb enable
	set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secfb_valid[0x0].secfb_valid,ui32SecFltId);
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secfb_valid[0x0].secfb_valid =  //0x00000000;//low
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secfb_valid[0x1].secfb_valid = 0x00000000;//high
#endif /* #if 0 */

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

#if 0
	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;

	stSecfAddr.word_idx = 0x0;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Pattern_H;

	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stSecfAddr.word_idx = 0x1;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Pattern_L;

	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stSecfAddr.word_idx = 0x2;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Mask_H;

	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stSecfAddr.word_idx = 0x3;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Mask_L;

	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stSecfAddr.word_idx = 0x4;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Neq_H;

	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stSecfAddr.word_idx = 0x5;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Neq_L;

	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stSecfAddr.word_idx = 0x6;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32SecFltId;
#endif
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 0, ui32Pattern_H);
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 1, ui32Pattern_L);
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 2, ui32Mask_H);
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 3, ui32Mask_L);
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 4, ui32Neq_H);
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 5, ui32Neq_L);
	SDEC_HAL_SECFSetSecfData(ui8Ch, ui32SecFltId, 6, ui32SecFltId);
	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

#ifdef __AUTO_INCREMENT
	stSecfAddr = stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr;
	stSecfAddr.secf_idx = ui32SecFltId;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_addr = stSecfAddr;

	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Pattern_H;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Pattern_L;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Mask_H;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Mask_L;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Neq_H;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32Neq_L;
	stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_data.secf_data = ui32SecFltId;


	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32Pattern_H:[0x%08x]", ui8Ch, ui32Pattern_H);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32Pattern_L:[0x%08x]", ui8Ch, ui32Pattern_L);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32Mask_H:[0x%08x]", ui8Ch, ui32Mask_H);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32Mask_L:[0x%08x]", ui8Ch, ui32Mask_L);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32Neq_H:[0x%08x]", ui8Ch, ui32Neq_H);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32Neq_L:[0x%08x]", ui8Ch, ui32Neq_L);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] Section pattern ui32SecFltId:[0x%08x]", ui8Ch, ui32SecFltId);
#endif

#if 0

	if(ui32SecFltId < 32 )
	{
		set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_en[0].secf_en, ui32SecFltId);
	}else
	{
		set__bit(stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->secf_en[1].secf_en, (ui32SecFltId % 32) );
	}
#endif
	SDEC_HAL_SECFSetEnableBit(ui8Ch, ui32SecFltId);
#if 0
	/* copy parameters from user space */
	eResult = copy_from_user(&ui32Arg,
		(void *)ui32Arg,
		sizeof(ui32Arg));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}
#endif /* #if 0 */
	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterPattern");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   SDEC Section filter buffer reset.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterBufferReset
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_BUFFER_RESET *stpLXSdecSecfltBufferReset;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32GpbIdx = 0x0, ui32GpbBaseAddr = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterBufferReset");

	stpLXSdecSecfltBufferReset =(LX_SDEC_SECFLT_BUFFER_RESET *)ui32Arg;

	ui8Ch 		= stpLXSdecSecfltBufferReset->eCh;
	ui32GpbIdx 	= stpLXSdecSecfltBufferReset->uiSecFltId;

	ui32GpbBaseAddr = stpSdecParam->stSdecMeminfo[ui8Ch][ui32GpbIdx].ui32Baseptr;

	SDEC_DTV_SOC_Message( SDEC_ERROR, "SDEC_IO_SectionFilterBufferReset CH%c gpb[%d]",
						(ui8Ch)?'B':'A',
						ui32GpbIdx);

	/* set GPB read & write pointer register */
	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->gpb_w_ptr[ui32GpbIdx].gpb_w_ptr =	ui32Lower_Bound;
	//stpSdecParam->stSDEC_MPG_Reg[ui8Ch]->gpb_r_ptr[ui32GpbIdx].gpb_r_ptr =	ui32Lower_Bound;
	SDEC_HAL_GPBSetReadPtr(ui8Ch, 	ui32GpbIdx, ui32GpbBaseAddr);
	SDEC_HAL_GPBSetWritePtr(ui8Ch, 	ui32GpbIdx, ui32GpbBaseAddr);


	/* initialize base & end pointer */
	stpSdecParam->stSdecMeminfo[ui8Ch][ui32GpbIdx].ui32Baseptr 	= ui32GpbBaseAddr;
	stpSdecParam->stSdecMeminfo[ui8Ch][ui32GpbIdx].ui32Readptr 	= ui32GpbBaseAddr;
	stpSdecParam->stSdecMeminfo[ui8Ch][ui32GpbIdx].ui32UsrReadptr 	= ui32GpbBaseAddr;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterBufferReset");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}

/**
********************************************************************************
* @brief
*   SDEC Section filter  buffer set.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterBufferSet
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult = NOT_OK;
	LX_SDEC_SECFLT_BUFFER_SET_T *stpLXSdecSecfltBufferSet;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32SecFltId = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterBufferSet");

	stpLXSdecSecfltBufferSet =(LX_SDEC_SECFLT_BUFFER_SET_T *)ui32Arg;

	ui8Ch = stpLXSdecSecfltBufferSet->eCh;
	ui32SecFltId = stpLXSdecSecfltBufferSet->uiSecFltId;

	if(ui8Ch >= LX_SDEC_CH_NUM)
	{
		SDEC_DEBUG_Print("Invalid channel:[%d]", ui8Ch);
		goto exit;
	}

	//GPB Set
	eResult = SDEC_GpbSet(stpSdecParam,
					ui8Ch,
					stpLXSdecSecfltBufferSet->eBufferSize,
					stpLXSdecSecfltBufferSet->uiBufAddress,
					stpLXSdecSecfltBufferSet->uiSecFltId);

	if(LX_IS_ERR(eResult))
	{
		SDEC_DEBUG_Print("SDEC_GpbSet failed");
		goto exit;
	}

	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] GPB Base address:[0x%08x]", ui8Ch, stpLXSdecSecfltBufferSet->uiBufAddress);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] GPB size:[%d]", ui8Ch, stpLXSdecSecfltBufferSet->eBufferSize);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "Ch[%d] ui32PidFltId:[%d]", ui8Ch, ui32SecFltId);


	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterBufferSet");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}

/**
********************************************************************************
* @brief
*   SDEC Section filter  get infot.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterGetInfo
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK, eResult= NOT_OK;
	LX_SDEC_SECFLT_BUFFER_GET_INFO_T *stpLXSdecSecfltBufferGetInfo;
	LX_SDEC_SECFLT_BUFFER_GET_INFO_T stLXSdecSecfltBufferGetInfo;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32SecFltId  = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );
	LX_SDEC_CHECK_CODE( ui8Ch > LX_SDEC_CH_B, 	goto exit, "Invalid parameters" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterGetInfo");

	eResult = copy_from_user(&stLXSdecSecfltBufferGetInfo, (void __user *)ui32Arg, sizeof(LX_SDEC_SECFLT_BUFFER_GET_INFO_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	stpLXSdecSecfltBufferGetInfo = &stLXSdecSecfltBufferGetInfo;

	ui8Ch = stpLXSdecSecfltBufferGetInfo->eCh;

	ui32SecFltId = stpLXSdecSecfltBufferGetInfo->uiSecFltId;

	stpLXSdecSecfltBufferGetInfo->uiReadPtr 	= SDEC_HAL_GPBGetReadPtr(ui8Ch, ui32SecFltId);
	stpLXSdecSecfltBufferGetInfo->uiWritePtr 	= SDEC_HAL_GPBGetWritePtr(ui8Ch, ui32SecFltId);

#if 0
	if(stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32NumofSection > SDEC_MAX_PACKETNUM)
	{
		stpLXSdecSecfltBufferGetInfo->uiSectionNr = SDEC_MAX_PACKETNUM;
	}
	else
	{
		stpLXSdecSecfltBufferGetInfo->uiSectionNr = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32NumofSection;
	}

	//stpLXSdecSecfltBufferGetInfo->uiSectionNr = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32NumofSection;
	//stpLXSdecSecfltBufferGetInfo->uiReadAddr = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Rdptr;
	//stpLXSdecSecfltBufferGetInfo->uiWriteAddr = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32Wrptr;
	memcpy(&stpLXSdecSecfltBufferGetInfo->uiReadPtr[0],  &stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32ReadPtr[0],  sizeof(UINT32)*stpLXSdecSecfltBufferGetInfo->uiSectionNr);
	memcpy(&stpLXSdecSecfltBufferGetInfo->uiWritePtr[0], &stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32WritePtr[0], sizeof(UINT32)*stpLXSdecSecfltBufferGetInfo->uiSectionNr);
#if 0
	// 20101020 seokjoo.lee : to support gpb base is configured over 256MB range.
	// stSdecMeminfo[ch][fltid].ui32ReadPtr[0] is restricted to 28 bit due to gpb_w_ptr & gpb_r_ptr.
	if( gMemCfgSDECGPB.gpb_memory_base >= 0x10000000 )
	{
		int i ;
		for ( i = 0 ; i < stpLXSdecSecfltBufferGetInfo->uiSectionNr ; i ++)
		{
			stpLXSdecSecfltBufferGetInfo->uiReadPtr[i]  |= 0x10000000;
			stpLXSdecSecfltBufferGetInfo->uiWritePtr[i] |= 0x10000000;
		}
	}
#endif
//	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "[Ch%d] ui32Rdptr:[0x%08x]",ui8Ch, stpLXSdecSecfltBufferGetInfo->uiReadAddr);
//	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "[Ch%d] ui32Wrptr:[0x%08x]",ui8Ch, stpLXSdecSecfltBufferGetInfo->uiWriteAddr);
	SDEC_DTV_SOC_Message( SDEC_PIDSEC, "[Ch%d] ui32NumofSection:[0x%08x]",ui8Ch, stpLXSdecSecfltBufferGetInfo->uiSectionNr);

	stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32NumofSection = 0x0;
#endif

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterGetInfo");

	eResult = copy_to_user((void *)ui32Arg,stpLXSdecSecfltBufferGetInfo, sizeof(LX_SDEC_SECFLT_BUFFER_GET_INFO_T));

	if (eResult)
	{
		SDEC_DEBUG_Print("Copy from user failed");
		goto exit;
	}

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}

/**
********************************************************************************
* @brief
*   SDEC Section filter  set read pointer.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterSetReadPtr
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_READPTR_SET_T *stpLXSdecSecfltReadPtrSet;
	LX_SDEC_CFG_T* pSdecConf = NULL;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32SecFltId = 0x0;
	UINT32 ui32ReadPtr = 0x0;


	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterSetReadPtr");

	stpLXSdecSecfltReadPtrSet =(LX_SDEC_SECFLT_READPTR_SET_T *)ui32Arg;

	ui8Ch 			= stpLXSdecSecfltReadPtrSet->eCh;
	ui32SecFltId 	= stpLXSdecSecfltReadPtrSet->uiSecFltId;
	ui32ReadPtr 	= stpLXSdecSecfltReadPtrSet->uiReadPtr;

	// LJH_GPB
	pSdecConf = SDEC_CFG_GetConfig();

	/* 2012.02.06 gaius.lee
	 * Bug exist in L9 HW.
	 * While CPU access Read/Write/Bound Register, SDEC HW accesses write register, write pointer goes to read/write/bound regitser which CPU access.
	 * So, remove access to read register. That's why we disable this line. */
	if(pSdecConf->staticGPB == 0)
	{
		SDEC_HAL_GPBSetReadPtr(ui8Ch, ui32SecFltId, ui32ReadPtr);
	}
	/* save user read pointer */
	stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui32UsrReadptr = ui32ReadPtr;

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterSetReadPtr");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}

/**
********************************************************************************
* @brief
*   SDEC Section filter  buffer get state.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SectionFilterGetState
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_SECFLT_STATE_T *stpLXSdecSecfltState;

	UINT8 ui8Ch = 0x0;
	UINT32 ui32SecFltId = 0x0;
	UINT8 ui8wordIdx = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SectionFilterGetState");

	stpLXSdecSecfltState =(LX_SDEC_SECFLT_STATE_T *)ui32Arg;

	ui8Ch = stpLXSdecSecfltState->eCh;
	ui32SecFltId = stpLXSdecSecfltState->uiSecFltId;

	/* Get Status of Section Filter @see LX_SDEC_FLTSTATE_T */
	stpLXSdecSecfltState->uiFltState = stpSdecParam->stSecMap[ui8Ch][ui32SecFltId].stStatusInfo.w;

	/* Get Map Type */
	stpLXSdecSecfltState->ucSecf_mtype = SDEC_HAL_SECFGetMapTypeBit(ui8Ch, ui32SecFltId);

	/* Get Linked PID Filter */
	stpLXSdecSecfltState->uiPidFltId = stpSdecParam->stSdecMeminfo[ui8Ch][ui32SecFltId].ui8PidFltIdx;

	//auto increment disable
	//SDEC_Enable_AutoIncr(stpSdecParam, 0);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_DISABLE);

	for( ui8wordIdx = 0 ; ui8wordIdx < 7 ; ui8wordIdx++ )
	{
		/* jinhwan.bae , static analysis, protect overrun */
		if( ui8wordIdx < 2 ) stpLXSdecSecfltState->uiPattern[ui8wordIdx] = SDEC_HAL_SECFGetSecfData(ui8Ch, ui32SecFltId, ui8wordIdx);
		else if( ui8wordIdx < 4 ) stpLXSdecSecfltState->uiMask[ui8wordIdx - 2] = SDEC_HAL_SECFGetSecfData(ui8Ch, ui32SecFltId, ui8wordIdx);
		else if( ui8wordIdx < 6 ) stpLXSdecSecfltState->uiNotEqual[ui8wordIdx - 4] = SDEC_HAL_SECFGetSecfData(ui8Ch, ui32SecFltId, ui8wordIdx);
		else if( ui8wordIdx == 6 ) stpLXSdecSecfltState->uiGpbIdx = SDEC_HAL_SECFGetSecfData(ui8Ch, ui32SecFltId, ui8wordIdx);
	}

	//auto increment enable
	//SDEC_Enable_AutoIncr(stpSdecParam, 1);
	SDEC_HAL_EnableAutoIncr(SDEC_HAL_ENABLE);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SectionFilterGetState");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);

}

/**
********************************************************************************
* @brief
*   enable log.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpVdecParam :VDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_EnableLog(S_SDEC_PARAM_T *stpSdecParam, UINT32 ulArg)
{
	DTV_STATUS_T eRet = NOT_OK;
	int idx;
	UINT32 *pulArg = (UINT32*)ulArg;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ulArg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_EnableLog");

	stpSdecParam->ui32MsgMask = *pulArg;

	for ( idx = 0; idx < LX_MAX_MODULE_DEBUG_NUM; idx++)
	{
		if ( *pulArg & (1<<idx) ) OS_DEBUG_EnableModuleByIndex ( g_sdec_debug_fd, idx, DBG_COLOR_NONE );
		else					OS_DEBUG_DisableModuleByIndex( g_sdec_debug_fd, idx);
	};

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_EnableLog");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   Read Register value
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpVdecParam :VDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_GetRegister(S_SDEC_PARAM_T *stpSdecParam, UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_GET_REG_T *stpLXSdecReadRegisters;
	LX_SDEC_BLOCK_T eSdecBlock;
	UINT32 ui32BaseAddr = 0x0, ui32Offset = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetRegister");

	stpLXSdecReadRegisters =(LX_SDEC_GET_REG_T *)ui32Arg;
	eSdecBlock	= stpLXSdecReadRegisters->eSdecBlock;
	ui32Offset 	= stpLXSdecReadRegisters->uiOffset;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
#if 0
		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				ui32BaseAddr = (UINT32 )H13_SDEC_TOP_REG_BASE;
				break;

			case LX_SDEC_BLOCK_IO:
				ui32BaseAddr = (UINT32 )H13_SDEC_IO_REG_BASE;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				ui32BaseAddr = (UINT32 )H13_SDEC_MPG_REG_BASE0;
				break;

			case LX_SDEC_BLOCK_CORE_B:
				ui32BaseAddr = (UINT32 )H13_SDEC_MPG_REG_BASE1;
				break;

			case LX_SDEC_BLOCK_CTOP:
				ui32BaseAddr = (UINT32 )H13_CTOP_REG_BASE;
				break;

			default :
				ui32BaseAddr = 0;
				eRet = NOT_OK;
				goto exit;
		}
#else
		UINT32* reg_ptr = NULL;

		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				reg_ptr = (UINT32*)stSDEC_TOP_RegH13A0;
				break;

			case LX_SDEC_BLOCK_IO:
				reg_ptr = (UINT32*)stSDEC_IO_RegH13A0;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				reg_ptr = (UINT32*)stSDEC_MPG_RegH13A0[0];
				break;

			case LX_SDEC_BLOCK_CORE_B:
				reg_ptr = (UINT32*)stSDEC_MPG_RegH13A0[1];
				break;
				
			case LX_SDEC_BLOCK_CTOP:
				reg_ptr = (UINT32*)gCTOP_CTRL_H13.phys.addr;
				break;
				
			default :
				eRet = NOT_OK;
				goto exit;
		}

		eRet = OK;

		stpLXSdecReadRegisters->uiValue = *(reg_ptr + (ui32Offset/4));
			
		goto exit;
#endif
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
	{
		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				ui32BaseAddr = (UINT32 )L9_SDEC_TOP_REG_BASE;
				break;

			case LX_SDEC_BLOCK_IO:
				ui32BaseAddr = (UINT32 )L9_SDEC_IO_REG_BASE;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				ui32BaseAddr = (UINT32 )L9_SDEC_MPG_REG_BASE0;
				break;

			case LX_SDEC_BLOCK_CORE_B:
				ui32BaseAddr = (UINT32 )L9_SDEC_MPG_REG_BASE1;
				break;

			case LX_SDEC_BLOCK_CTOP:
				ui32BaseAddr = (UINT32 )L9_TOPCTRL_BASE;
				break;

			default :
				ui32BaseAddr = 0;
				goto exit;
		}
	}
	else
	{
		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				ui32BaseAddr = (UINT32 )L8_SDEC_TOP_REG_BASE;
				break;

			case LX_SDEC_BLOCK_IO:
				ui32BaseAddr = (UINT32 )L8_SDEC_IO_REG_BASE;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				ui32BaseAddr = (UINT32 )L8_SDEC_MPG_REG_BASE0;
				break;

			case LX_SDEC_BLOCK_CORE_B:
				ui32BaseAddr = (UINT32 )L8_SDEC_MPG_REG_BASE1;
				break;

			default :
				ui32BaseAddr = 0;
				goto exit;
		}
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "ui32BaseAddr = %08x , %08x", ui32BaseAddr, ui32BaseAddr + ui32Offset);

	stpLXSdecReadRegisters->uiValue = REG_READ32(ui32BaseAddr+ui32Offset);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetRegister");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}

/**
********************************************************************************
* @brief
*   Write Register value
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpVdecParam :VDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_SetRegister(S_SDEC_PARAM_T *stpSdecParam, UINT32 ui32Arg)
{
	DTV_STATUS_T eRet = NOT_OK;
	LX_SDEC_GET_REG_T *stpLXSdecReadRegisters;
	LX_SDEC_BLOCK_T eSdecBlock;
	UINT32 ui32BaseAddr = 0x0, ui32Offset = 0x0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_SetRegister");

	stpLXSdecReadRegisters =(LX_SDEC_GET_REG_T *)ui32Arg;
	eSdecBlock	= stpLXSdecReadRegisters->eSdecBlock;
	ui32Offset 	= stpLXSdecReadRegisters->uiOffset;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
#if 0 // jinhwan.bae for kernel 3.x, ioremap should be used
		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				ui32BaseAddr = (UINT32 )H13_SDEC_TOP_REG_BASE;
				break;

			case LX_SDEC_BLOCK_IO:
				ui32BaseAddr = (UINT32 )H13_SDEC_IO_REG_BASE;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				ui32BaseAddr = (UINT32 )H13_SDEC_MPG_REG_BASE0;
				break;

			case LX_SDEC_BLOCK_CORE_B:
				ui32BaseAddr = (UINT32 )H13_SDEC_MPG_REG_BASE1;
				break;

			case LX_SDEC_BLOCK_CTOP:
				ui32BaseAddr = (UINT32 )H13_CTOP_REG_BASE;
				break;

			default :
				ui32BaseAddr = 0;
				eRet = NOT_OK;
				goto exit;
		}
#else
		UINT32* reg_ptr = NULL;

		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				reg_ptr = (UINT32*)stSDEC_TOP_RegH13A0;
				break;

			case LX_SDEC_BLOCK_IO:
				reg_ptr = (UINT32*)stSDEC_IO_RegH13A0;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				reg_ptr = (UINT32*)stSDEC_MPG_RegH13A0[0];
				break;

			case LX_SDEC_BLOCK_CORE_B:
				reg_ptr = (UINT32*)stSDEC_MPG_RegH13A0[1];
				break;
				
			case LX_SDEC_BLOCK_CTOP:
				reg_ptr = (UINT32*)gCTOP_CTRL_H13.phys.addr;
				break;
				
			default :
				eRet = NOT_OK;
				goto exit;
		}

		eRet = OK;

		*(reg_ptr + (ui32Offset/4)) = stpLXSdecReadRegisters->uiValue;
			
		goto exit;
#endif
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, A0))
	{
		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				ui32BaseAddr = (UINT32 )L9_SDEC_TOP_REG_BASE;
				break;

			case LX_SDEC_BLOCK_IO:
				ui32BaseAddr = (UINT32 )L9_SDEC_IO_REG_BASE;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				ui32BaseAddr = (UINT32 )L9_SDEC_MPG_REG_BASE0;
				break;

			case LX_SDEC_BLOCK_CORE_B:
				ui32BaseAddr = (UINT32 )L9_SDEC_MPG_REG_BASE1;
				break;

			case LX_SDEC_BLOCK_CTOP:
				ui32BaseAddr = (UINT32 )L9_TOPCTRL_BASE;
				break;

			default :
				ui32BaseAddr = 0;
				goto exit;
		}
	}
	else
	{
		switch(eSdecBlock)
		{
			case LX_SDEC_BLOCK_TOP:
				ui32BaseAddr = (UINT32 )L8_SDEC_TOP_REG_BASE;
				break;

			case LX_SDEC_BLOCK_IO:
				ui32BaseAddr = (UINT32 )L8_SDEC_IO_REG_BASE;
				break;

			case LX_SDEC_BLOCK_CORE_A:
				ui32BaseAddr = (UINT32 )L8_SDEC_MPG_REG_BASE0;
				break;

			case LX_SDEC_BLOCK_CORE_B:
				ui32BaseAddr = (UINT32 )L8_SDEC_MPG_REG_BASE1;
				break;

			default :
				ui32BaseAddr = 0;
				goto exit;
		}
	}

	SDEC_DTV_SOC_Message( SDEC_NORMAL, "ui32BaseAddr = %08x , %08x", ui32BaseAddr, ui32BaseAddr + ui32Offset);

	REG_WRITE32(ui32BaseAddr+ui32Offset, stpLXSdecReadRegisters->uiValue);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_SetRegister");

	eRet = OK;

exit:
	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
********************************************************************************
* @brief
*   Reset  SDEC input port
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_InputPortReset(UINT8 ui8Ch)
{
	int 			ret = RET_ERROR;
	UINT32			sdmwc_stat = 0;
	UINT8			chk_cnt = 0;

	/* wait until SDMWC is idle */
	sdmwc_stat = ( SDEC_HAL_SDMWCGetStatus() & 0x00000333 );

	while(sdmwc_stat != 0 && chk_cnt++ < 3)
	{
		sdmwc_stat = ( SDEC_HAL_SDMWCGetStatus() & 0x00000333 );
		OS_UsecDelay(1000);
	}

	SDEC_DTV_SOC_Message(SDEC_RESET, "chk_cnt[%d] ", chk_cnt );

	/* if not idle, reset SDMWC */
	if(chk_cnt >= 3)
	{
		SDEC_DTV_SOC_Message(SDEC_RESET, "NOT IDLE!");

		/* 0xC000B264(SDIO-SDMWC_STAT)*/
		SDEC_DTV_SOC_Message(SDEC_RESET, "SDMWC_STAT [0x%08x]", SDEC_HAL_SDMWCGetStatus());

		/* This block is added from L9 B0 */
		/* Reset */
		SDEC_HAL_SDMWCReset(0x30000000);
		/* wait 10 us */
		OS_UsecDelay(10);
		/* Clear */
		SDEC_HAL_SDMWCReset(0x00000000);
		/* wait 10 us */
		OS_UsecDelay(10);
	}


	/* reset channel */
	//stpSdecParam->stSDEC_IO_Reg->cdic[ui8Ch].rst = 1;
	SDEC_HAL_CIDCReset(ui8Ch);

	/* wait 10 us */
	OS_UsecDelay(10);

	ret = RET_OK;

	return ret;
}


/**
********************************************************************************
* @brief
*   Reset  SDEC Memory write Controller
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_SDMWCReset(UINT8 ui8Ch)
{
	int 			ret = RET_ERROR;

	/* This block is added from L9 B0 */
	/* Reset */
	SDEC_HAL_SDMWCReset(0x30000000);

	/* wait 10 us */
	OS_UsecDelay(10);

	/* Clear */
	SDEC_HAL_SDMWCReset(0x00000000);

	/* wait 1 ms */
	OS_UsecDelay(1000);

	ret = RET_OK;

	return ret;
}

/**
********************************************************************************
* @brief
*   Reset  SDEC H/W block. Using Chip TOP.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_Register_Backup(UINT32 *pRegStore, S_REG_BACKUP_LIST_T *pBackList)
{
	int 			ret = RET_ERROR;
	UINT8			i = 0, offset = 0;

	if(pBackList->bInit == FALSE )
	{
		/* Make a list about register backup offset list */
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIP0]			= 0x00;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIP1]			= 0x04;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIP2]			= 0x08;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIP3]			= 0x0C;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIOP0]			= 0x10;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIOP1]			= 0x14;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIC_DSC0]		= 0x28;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIC_DSC1]		= 0x2C;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_INTR_EN]			= 0x100;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_ERR_INTR_EN]		= 0x110;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_GPB_BASE]			= 0x120;
		pBackList->regIO[E_SDEC_REGBACKUP_IO_CDIC2]			= 0x12C;

		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_EXT_CONF]		= 0x10;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_TPI_ICONF]	= 0x40;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_KMEM_ADDR]	= 0x98;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_KMEM_DATA]	= 0x9C;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_SECF_EN_L] 	= 0xB0;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_SECF_EN_H] 	= 0xB4;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_SECF_MTYPE_L]	= 0xB8;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_SECF_MTYPE_H]	= 0xBC;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_SECFB_VALID_L]= 0xC0;
		pBackList->regCORE[E_SDEC_REGBACKUP_CORE_SECFB_VALID_H]= 0xC4;

		pBackList->bInit = TRUE;
	}

	/* SD IO Bakcup */
	for ( i = 0 ; i < E_SDEC_REGBACKUP_IO_NUM ; i++, offset++ )
	{
		pRegStore[i] = REG_READ32(L9_SDEC_IO_REG_BASE + pBackList->regIO[i]);

		SDEC_DTV_SOC_Message(SDEC_RESET, "BACKUP  IO    OFFSET[0x%03x] VAL[0x%08x]", pBackList->regIO[i], pRegStore[offset]);
	}


	/* SD CORE0 Bakcup */
	for ( i = 0 ; i < E_SDEC_REGBACKUP_CORE_NUM ; i++, offset++ )
	{
		pRegStore[offset] = REG_READ32(L9_SDEC_MPG_REG_BASE0 + pBackList->regCORE[i]);

		SDEC_DTV_SOC_Message(SDEC_RESET, "BACKUP  CORE0 OFFSET[0x%03x] VAL[0x%08x]", pBackList->regIO[i], pRegStore[offset]);
	}

	/* SD CORE0 Bakcup */
	for ( i = 0 ; i < E_SDEC_REGBACKUP_CORE_NUM ; i++, offset++)
	{
		pRegStore[offset] = REG_READ32(L9_SDEC_MPG_REG_BASE0 + pBackList->regCORE[i]);

		SDEC_DTV_SOC_Message(SDEC_RESET, "BACKUP  CORE1 OFFSET[0x%03x] VAL[0x%08x]", pBackList->regIO[i], pRegStore[offset]);
	}

	ret = RET_OK;

	return ret;
}

/**
********************************************************************************
* @brief
*   Reset  SDEC H/W block. Using Chip TOP.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_Register_Restore(UINT32 *pRegStore, S_REG_BACKUP_LIST_T *pBackList)
{
	int 			ret = RET_ERROR;
	UINT8			i = 0, offset = 0;

	if(pBackList->bInit == FALSE )
	{
		SDEC_DTV_SOC_Message(SDEC_RESET, "SDEC_Register_Restore list is not initialized. ");
		goto exit;
	}

	/* SD IO Restore */
	for ( i = 0 ; i < E_SDEC_REGBACKUP_IO_NUM ; i++, offset++ )
	{
		SDEC_DTV_SOC_Message(SDEC_RESET, "RESTORE IO    OFFSET[0x%03x] VAL[0x%08x]", pBackList->regIO[i], pRegStore[offset]);
		REG_WRITE32(L9_SDEC_IO_REG_BASE + pBackList->regIO[i], pRegStore[i]);
	}

	/* SD CORE0 Restore */
	for ( i = 0 ; i < E_SDEC_REGBACKUP_CORE_NUM ; i++, offset++ )
	{
		SDEC_DTV_SOC_Message(SDEC_RESET, "RESTORE CORE0 OFFSET[0x%03x] VAL[0x%08x]", pBackList->regIO[i], pRegStore[offset]);
		REG_WRITE32(L9_SDEC_MPG_REG_BASE0 + pBackList->regCORE[i], pRegStore[offset]);
	}

	/* SD CORE1 Restore */
	for ( i = 0 ; i < E_SDEC_REGBACKUP_CORE_NUM ; i++, offset++ )
	{
		SDEC_DTV_SOC_Message(SDEC_RESET, "RESTORE CORE1 OFFSET[0x%03x] VAL[0x%08x]", pBackList->regIO[i], pRegStore[offset]);
		REG_WRITE32(L9_SDEC_MPG_REG_BASE0 + pBackList->regCORE[i], pRegStore[offset]);
	}

	ret = RET_OK;

exit:
	return ret;
}

static UINT32 				_gsRegStore[E_SDEC_REGBACKUP_IO_NUM + E_SDEC_REGBACKUP_CORE_NUM  + E_SDEC_REGBACKUP_CORE_NUM];	/* IO + CORE0 + CORE1 */
static S_REG_BACKUP_LIST_T 	_gsBackupList = { .bInit = FALSE };


/**
********************************************************************************
* @brief
*   Reset  SDEC H/W block. Using Chip TOP.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_TE_Reset(void)
{
	int 			ret = RET_ERROR;
	//UINT8			chk_cnt = 0;

	if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		/* Register Backup */
		SDEC_Register_Backup( &_gsRegStore[0], &_gsBackupList);

		/* Port Disable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_DISABLE);

#ifdef INCLUDE_L9_CHIP_KDRV
		/* SDEC Channel Mode Backup */
		if (lx_chip_rev() < LX_CHIP_REV(H13, A0))
		{
		#if 0
			/* Flush */
			CTOP_CTRL_L9B_WRITE(0x15C, 0x20);
			while(chk_cnt++ < 10)
			{
				if(CTOP_CTRL_L9B_READ(0x158) == 0x20)
					break;

				/* wait 1 us */
				OS_UsecDelay(1);
			}
			CTOP_CTRL_L9B_WRITE(0x15C, 0x0);


			if(chk_cnt < 10)
		#endif
			{
				CTOP_CTRL_L9B_WRITE(0x28, 0x20000);
				OS_UsecDelay(10);
				CTOP_CTRL_L9B_WRITE(0x28, 0x00000);
				OS_UsecDelay(10);
			}
		}
		/* SDEC Channel Mode Restore */
#endif

		/* Port Enable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_ENABLE);

		/* Register Restore */
		SDEC_Register_Restore(&_gsRegStore[0], &_gsBackupList);

	}


	ret = RET_OK;

	return ret;
}

/**
********************************************************************************
* @brief
*   Reset  SDEC H/W block. Using Chip TOP.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_TEA_Reset(void)
{
	int 			ret = RET_ERROR;
	UINT8			chk_cnt = 0;

	if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		/* Register Backup */
		SDEC_Register_Backup(_gsRegStore, &_gsBackupList);

		/* Port Disable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_DISABLE);

#ifdef INCLUDE_L9_CHIP_KDRV
		if (lx_chip_rev() < LX_CHIP_REV(H13, A0))
		{
			/* SDEC Channel Mode Backup */
			/* TEA 만 Flush 한다고 한다. */
		#if 1
			/* Flush */
			CTOP_CTRL_L9B_WRITE(0x15C, 0x20);
			while(chk_cnt++ < 10)
			{
				if(CTOP_CTRL_L9B_READ(0x158) == 0x20)
					break;

				/* wait 1 us */
				OS_UsecDelay(1);
			}
			CTOP_CTRL_L9B_WRITE(0x15C, 0x0);


			if(chk_cnt < 10)
		#endif
			{
				CTOP_CTRL_L9B_WRITE(0x28, 0x38000);	/* SDEC TEA ( 0x08000 )+ TEAH ( 0x10000 )+ TE ( 0x20000 ) Reset */
				OS_UsecDelay(10);
				CTOP_CTRL_L9B_WRITE(0x28, 0x00000);
				OS_UsecDelay(10);
			}
		}
#endif

		/* SDEC Channel Mode Restore */

		/* Port Enable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_ENABLE);

		/* Register Restore */
		SDEC_Register_Restore(_gsRegStore, &_gsBackupList);
	}


	ret = RET_OK;

	return ret;
}


/**
********************************************************************************
* @brief
*   Reset  SDEC H/W block. Using Chip TOP.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_TEAH_Reset(void)
{
	int 			ret = RET_ERROR;
	//UINT8			chk_cnt = 0;

	if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		/* Register Backup */
		SDEC_Register_Backup(_gsRegStore, &_gsBackupList);

		/* Port Disable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_DISABLE);

#ifdef INCLUDE_L9_CHIP_KDRV
		if (lx_chip_rev() < LX_CHIP_REV(H13, A0))
		{
			/* wait 1 ms */
			OS_UsecDelay(1000);
		#if 0
			/* Flush */
			CTOP_CTRL_L9B_WRITE(0x15C, 0x20);
			while(chk_cnt++ < 10)
			{
				if(CTOP_CTRL_L9B_READ(0x158) == 0x20)
					break;

				/* wait 1 us */
				OS_UsecDelay(1);
			}
			CTOP_CTRL_L9B_WRITE(0x15C, 0x0);


			if(chk_cnt < 10)
		#endif
			{
				CTOP_CTRL_L9B_WRITE(0x28, 0x30000);	/* SDEC TEAH ( 0x10000 )+ TE ( 0x20000 ) Reset */
				OS_UsecDelay(10);
				CTOP_CTRL_L9B_WRITE(0x28, 0x00000);
			}
		}
#endif

		/* wait 1 ms */
		OS_UsecDelay(1000);

		/* SDEC Channel Mode Restore */

		/* Port Enable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_ENABLE);

		/* Register Restore */
		SDEC_Register_Restore(_gsRegStore, &_gsBackupList);
	}


	ret = RET_OK;

	return ret;
}

/**
********************************************************************************
* @brief
*   Reset  SDEC H/W block. Using Chip TOP.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_TEAHFlush_Reset(void)
{
	int 			ret = RET_ERROR;
	UINT8			chk_cnt = 0;

	if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		/* Register Backup */
		SDEC_Register_Backup(_gsRegStore, &_gsBackupList);

		/* Port Disable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_DISABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_DISABLE);

#ifdef INCLUDE_L9_CHIP_KDRV
		if (lx_chip_rev() < LX_CHIP_REV(H13, A0))
		{
			/* wait 1 ms */
			OS_UsecDelay(1000);

			/* Flush */
			CTOP_CTRL_L9B_WRITE(0x15C, 0x20);
			while(chk_cnt++ < 10)
			{
				if(CTOP_CTRL_L9B_READ(0x158) == 0x20)
					break;

				/* wait 1 us */
				OS_UsecDelay(1);
			}
			CTOP_CTRL_L9B_WRITE(0x15C, 0x0);

			if(chk_cnt < 10)
			{
				CTOP_CTRL_L9B_WRITE(0x28, 0x30000);	/* SDEC TEAH ( 0x10000 )+ TE ( 0x20000 ) Reset */
				OS_UsecDelay(10);
				CTOP_CTRL_L9B_WRITE(0x28, 0x00000);
			}
		}
#endif

		/* wait 1 ms */
		OS_UsecDelay(1000);

		/* SDEC Channel Mode Restore */

		/* Port Enable */
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL0, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_SERIAL1, 		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL0,		SDEC_HAL_ENABLE);
		SDEC_InputPortEnable(LX_SDEC_INPUT_PARALLEL1,		SDEC_HAL_ENABLE);

		/* Register Restore */
		SDEC_Register_Restore(_gsRegStore, &_gsBackupList);
	}


	ret = RET_OK;

	return ret;
}


/**
********************************************************************************
* @brief
*   Send Debug Command to Kdrv.
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   ui32Arg :arguments from userspace
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
DTV_STATUS_T SDEC_IO_DebugCommand
	(S_SDEC_PARAM_T *stpSdecParam,
	UINT32 ui32Arg)
{
	DTV_STATUS_T 		eRet = NOT_OK;
	LX_SDEC_DBG_CMD_T 	*stpLXSdecDbgCmd;
	UINT8				ui8Ch = 0;

	unsigned long 		flags = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	OS_LockMutex(&stpSdecParam->stSdecMutex);

	SDEC_DTV_SOC_Message( SDEC_TRACE, "<--SDEC_IO_GetChipCfg");

	stpLXSdecDbgCmd = (LX_SDEC_DBG_CMD_T *)ui32Arg;

	switch(stpLXSdecDbgCmd->eCmd)
	{
		case LX_SDEC_CMD_RESET_CDIC:
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			/* get channel */
			ui8Ch = (UINT8)stpLXSdecDbgCmd->inParam;

			/* disable channel input and wait 0.01 ms */
			SDEC_InputPortEnable(stpSdecParam->eInputPath[ui8Ch], 		SDEC_HAL_DISABLE);

			OS_UsecDelay(10);

			SDEC_InputPortReset(ui8Ch);

			OS_UsecDelay(10);

			/* enable channel input */
			SDEC_InputPortEnable(stpSdecParam->eInputPath[ui8Ch], 		SDEC_HAL_ENABLE);

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
			break;

		case LX_SDEC_CMD_RESET_SDMWC:
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			/* get channel */
			ui8Ch = (UINT8)stpLXSdecDbgCmd->inParam;

			/* disable channel input and wait 0.01 ms */
			SDEC_InputPortEnable(stpSdecParam->eInputPath[ui8Ch], SDEC_HAL_DISABLE);

			OS_UsecDelay(10);

			SDEC_SDMWCReset(ui8Ch);

			OS_UsecDelay(10);

			/* enable channel input */
			SDEC_InputPortEnable(stpSdecParam->eInputPath[ui8Ch], SDEC_HAL_ENABLE);

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
			break;

		case LX_SDEC_CMD_RESET_TE:
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			SDEC_TE_Reset();

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
			break;

		case LX_SDEC_CMD_RESET_TEA:
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			SDEC_TEA_Reset();

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
			break;

		case LX_SDEC_CMD_RESET_TEAH:
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			SDEC_TEAH_Reset();

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
			break;

		case LX_SDEC_CMD_RESET_TEAH_FLUSH:
			spin_lock_irqsave(&stpSdecParam->stSdecResetSpinlock, flags);

			SDEC_TEAHFlush_Reset();

			spin_unlock_irqrestore(&stpSdecParam->stSdecResetSpinlock, flags);
			break;

		case LX_SDEC_CMD_EN_CIDC :
			if(stpLXSdecDbgCmd->inParam == E_SDEC_RESET_MODE_ONETIME)	stpSdecParam->ui8CDICResetNum = 0;
			stpSdecParam->ui8CDICResetMode = (UINT8)stpLXSdecDbgCmd->inParam;
			break;

		case LX_SDEC_CMD_EN_SDMWC:
			if(stpLXSdecDbgCmd->inParam == E_SDEC_RESET_MODE_ONETIME)	stpSdecParam->ui8SDMWCResetNum = 0;
			stpSdecParam->ui8SDMWCResetMode = (UINT8)stpLXSdecDbgCmd->inParam;
			break;

		case LX_SDEC_CMD_SET_FCW:
			SDEC_IO_SettingFCW(stpSdecParam , stpLXSdecDbgCmd->inParam);
			break;
			
		default :
			break;
	}

#if 0
	/* copy parameters to user space */
	eResult = copy_to_user((void *)ui32Arg,&stpLXSdecGetSTCPCR,sizeof(LX_SDEC_GET_STC_PCR_T));
	if (eResult)
	{
		SDEC_DEBUG_Print("SDEC_IO_GetCurrentSTC Copy touser failed");
		goto exit;
	}
#endif /* #if 0 */

	SDEC_DTV_SOC_Message( SDEC_TRACE, "-->SDEC_IO_GetChipCfg");

	eRet = OK;

	OS_UnlockMutex(&stpSdecParam->stSdecMutex);
	return (eRet);
}


/**
 * Below code is from LG D2A STB
 *
 * Modified and adjusted by Jihoon Lee ( gaius.lee@lge.com )
 *
 * 2010.06.14 @ DTV Lab.
 */


/**
 *
 * Filter context - initialised by calling pwm_init
 * @ingroup sdec_struct_type
 */
typedef struct
{
  unsigned long service				: 1, 	///< 0x00(bit 1) : pcr service doing
                recovery_Enable     : 1, 	///< 0x00(bit 1) : enable pcr recovery
                first_pcr_arrived	: 1,	///< 0x00(bit 1) : first_pcr_arrived
                reserved 			: 29;	///< 0x00(bit 28): reserved
  unsigned long fcw_base;					///< 0x04        : fcw base for selected Memory Clock
  signed   long fcw_offset;					///< 0x08        : fcw offset for first reset after each ch. change.
  unsigned long fcw_value;					///< 0x0c        : temperary fcw value
  unsigned long lastUpdateTime;				///< 0x10        : last updated Time Tick
  unsigned long new_reset_discard;			///< 0x14        : after reset recovery discarding count
  unsigned long new_adjust_skip;			///< 0x18        : skip adjusting right after adjust
  unsigned long skip_chk_overshoot;		 	///< 0x1c        : check divergence
  unsigned long fcw_trickSpeed;				///< 0x20        : multiply value for trick mode
  unsigned int	max_ignore_count;			///			 : max ignore count for protecting first jitter
} pwm_context_t;

UINT32	max_fcw_value;
UINT32	min_fcw_value;

UINT32	pwm_fcw_default		= 0;
UINT32	pwm_fcw_threshold		= 0;
UINT32	pwm_fcw_threshold_with_max_ignore = 0;
UINT32	pwm_fcw_window_sz		= 0;
SINT32	pwm_fcw_sz_step		= 0;


/*---------------------------------------------------------
 * Constant definition
---------------------------------------------------------*/
#define DCO_INPUT_CLOCK 	198
#define DCO_COEF			8388608		/* 2^23 */

//#define FCW_DEFAULT_VALUE 0x0011742f	/* 27 Mhz */
#define FCW_DEFAULT_VALUE 0x0011745D	/* 27 Mhz */
//#define FCW_DEFAULT_VALUE (UINT32)(KHZ_TO_FCW(24000))
#define FCW_PREFIX			0

#define FREQ_THRESHOLD_KHZ 						100
#define FREQ_THRESHOLD_KHZ_WITH_MAX_IGNORE	    5

#define PWM_DEBUG_LEVEL		2

#define FCW_WINDOW_SZ		8000

#define FCW_SZ_STEP 		0x9			/* 정확하게 계산하면 8.67 정도 됨 */

#define	PWM_MAX_DIFF_IGNORE		 36		/* 36 unit in 45 Khz PCR Frequency	  */
#define	PWM_MIN_DIFF_IGNORE		  4		/*  4 unit in 45 Khz PCR Frequency	  */
#define	PWM_DELTA_WINDOW		 24		/* Window size of direction filtering */
#define PWM_SUM_WINDOW			  4		/* Number of sum windows              */

#define MTS_HUGE_PCR_DIFFERENCE  (45*5000) /* <-- For stream wrap arround , 45*5000ms 5 sec --- 45MHz 020524 */

//#define MAX_DELTA_CLK 				(2 * 45)
#define MAX_DELTA_CLK 				(2* 45 * 10)

/*---------------------------------------------------------
 * Macro definition
---------------------------------------------------------*/
#define FCW_TO_KHZ(fcw)	( ((fcw) & 0x1FFFFF) * DCO_INPUT_CLOCK  / ( DCO_COEF / 1000 ))
#define KHZ_TO_FCW(khz)	( (khz)  * (DCO_COEF / DCO_INPUT_CLOCK) / 1000)

/* SINT64 divide macro with do_div */
#define DO_DIV_SINT64(n, div) { \
	if(n < 0 ) \
	{ \
		UINT64	u = (UINT64) (-n); \
		do_div(u, div); \
		n = (SINT64) (-u); \
	} \
	else \
		do_div(n, div); \
};
/*---------------------------------------------------------
    External 변수와 함수 prototype 선언
    (External Variables & Function Prototypes Declarations)
---------------------------------------------------------*/

/*---------------------------------------------------------
    Static 변수와 함수 prototype 선언
    (Static Variables & Function Prototypes Declarations)
---------------------------------------------------------*/
/*prototypes*/
static UINT32		nDeltaChkCount	= 0;	/* No. of data in nPwmWindow  */

static UINT32		_TimeStamps[PWM_SUM_WINDOW+1];		/* 시간  */
static SINT64		_MeanOfDelta[PWM_SUM_WINDOW*2];	/* pcr - stc의 차이를 저장한 nSumOfDelta를 시간으로 나눈 값 */
static UINT32		_AbsOfDelta[PWM_SUM_WINDOW*2];		/* pcr - stc의 차이를 저장한 nSumOfDelta를 시간으로 나눈 값의 절대값 */

static UINT32		*nTimeStamps = &_TimeStamps[1];	/* [1]을 가리키는 이유는 nTimeStamps[-1]로 이전 시간을 얻기 위해서다 */
static UINT32		*nAbsOfDelta = &_AbsOfDelta[PWM_SUM_WINDOW];
static SINT64		*nMeanOfDelta = &_MeanOfDelta[PWM_SUM_WINDOW];

static SINT32		nSumOfDelta[PWM_SUM_WINDOW];		/* pcr - stc의 차이를 저장한 값 */
static SINT32		nMstElapsed[PWM_SUM_WINDOW];		/* _timeStamp 값들의 차이값.. 즉, nSumOfDelta를 모을 때 걸린  시간. 이 값으로 _MeanofDelta나누어서 freq를 측정한다. */


static pwm_context_t pwm_context = {
	FALSE,				  // service
	FALSE,				  // recovery_Enable
	FALSE,				  // first_pcr_arrived
	    0,				  // reserved
		0,				  // fcw_base
	    0,				  // fcw_offset
	    0,				  // fcw_value
	    0,				  // lastUpdateTime
	    5,                // new_reset_discard
	    3,				  // new_adjust_skip
	    0,				  // skip_chk_overshoot
	    0,				  // fcw_trickSpeed
	    0				  // max_ignore_count
	};



UINT32 SDEC_IO_SettingFCW(S_SDEC_PARAM_T *stpSdecParam, UINT32 new_fcw_value)
{
#if 0
	/* Registers */
	volatile UINT32* reg_StcRef;	/* STC Referrence - will be set time which will apply DCO to system */
	volatile UINT32* reg_StcReal; 	/* STC Real - Real STC */
	volatile UINT32* reg_FCW;		/* FCW Register */
#endif
	UINT32	ui32stcReal_32 = 0, ui32stcReal_31_0 = 0;

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );

#if 1
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		CTOP_CTRL_H13_WRITE(0x154, new_fcw_value);

		////////////////////////////////////////////////////////////////////////////
		/* Setting DCO Value */
		/* STC Referrence - will be set time which will apply DCO to system */
		/* Actually, During Read/Write, All DCO Related Function Control Needed.ex. Stop, Set and Restart */
		/* But even if not, Read/Write Action is needed to adapt to the DCO Value really */
		/* Before Read/Write, DCO Value is not adapted really */
		/* read real STC value */
		ui32stcReal_32		= CPU_TOP_H13_READ(0x150);
		ui32stcReal_31_0	= CPU_TOP_H13_READ(0x154);

		/* setting referrence STC value with real stc + 0x10. */
		CPU_TOP_H13_WRITE(0x148, ui32stcReal_32);
		CPU_TOP_H13_WRITE(0x14C, ui32stcReal_31_0 + 0x10);
	}
#ifdef INCLUDE_L9_CHIP_KDRV
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		CTOP_CTRL_L9B_WRITE(0x0ec, new_fcw_value);

		////////////////////////////////////////////////////////////////////////////
		/* Setting DCO Value */
		/* STC Referrence - will be set time which will apply DCO to system */
		/* read real STC value */
		ui32stcReal_32		= CTOP_CTRL_L9B_READ(0x150);
		ui32stcReal_31_0	= CTOP_CTRL_L9B_READ(0x154);

		/* setting referrence STC value with real stc + 0x10. */
		CTOP_CTRL_L9B_WRITE(0x148, ui32stcReal_32);
		CTOP_CTRL_L9B_WRITE(0x14C, ui32stcReal_31_0 + 0x10);
	}
	else
	{
		CTOP_CTRL_L9_WRITE(0x0ec, new_fcw_value);

		////////////////////////////////////////////////////////////////////////////
		/* Setting DCO Value */
		/* STC Referrence - will be set time which will apply DCO to system */
		/* read real STC value */
		ui32stcReal_32		= CTOP_CTRL_L9_READ(0x150);
		ui32stcReal_31_0	= CTOP_CTRL_L9_READ(0x154);

		/* setting referrence STC value with real stc + 0x10. */
		CTOP_CTRL_L9_WRITE(0x148, ui32stcReal_32);
		CTOP_CTRL_L9_WRITE(0x14C, ui32stcReal_31_0 + 0x10);
	}
#endif
#else
	reg_FCW 	= (UINT32*) stpSdecParam->ui32DCORegVirAddr;
	reg_StcRef	= (UINT32*) stpSdecParam->ui32TOPRegStcRef;
	reg_StcReal	= (UINT32*) stpSdecParam->ui32TOPRegStcReal;

#if 0
	if(pwm_context.fcw_multiply != 10)
		ui32FCW_Val = pwm_context.fcw_trickSpeed;
	else
		ui32FCW_Val = new_fcw_value;
#else
	ui32FCW_Val = new_fcw_value;
#endif

	/* FCW 구하는 수식 */
	*reg_FCW = (ui32FCW_Val);

	/* STC Ref Register에 쓴 시간과 real 시간이 일치하면 그 때 새로운 FCW 값을 적용한다. */
	ui32StcVal[0] = *reg_StcReal;
	ui32StcVal[1] = *(reg_StcReal + 1);

	*reg_StcRef = ui32StcVal[0];
	*(reg_StcRef+1) = ui32StcVal[1] + 0x10;
#endif

	return RET_OK;
}


#define NORMAL_STC 0x0011743D

DTV_STATUS_T SDEC_IO_SetSTCMultiply(S_SDEC_PARAM_T *stpSdecParam, UINT32 ui32Arg)
{
	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return INVALID_PARAMS, "Invalid parameters" );
	LX_SDEC_CHECK_CODE( ui32Arg == 0, return INVALID_ARGS, "Invalid argument" );

	pwm_context.fcw_trickSpeed = (ui32Arg * NORMAL_STC) / 10;
	pwm_context.fcw_trickSpeed |= FCW_PREFIX;

	if(ui32Arg != 10)
		SDEC_IO_SettingFCW(stpSdecParam, pwm_context.fcw_trickSpeed);
	else
		SDEC_IO_SettingFCW(stpSdecParam, pwm_context.fcw_value);

	return OK;
}


/**
 * pwm status clear and data structure init.
 *
 * @param 		fResetCount   pwm reset value
 * @return		void
 * @ingroup sdec_pwm_func
 */
static void pwm_context_reset(S_SDEC_PARAM_T	*stpSdecParam, UINT8 cur_ch)
{
	int		i;

	SDEC_DTV_SOC_Message( SDEC_PCR, "pwm_context_reset[Ch:%d]",cur_ch);

	for (i = 0; i < PWM_SUM_WINDOW; i++)
		nSumOfDelta[i] = 0;

	pwm_context.new_reset_discard = 5;
	pwm_context.new_adjust_skip   = PWM_SUM_WINDOW-1;
	pwm_context.fcw_value = pwm_context.fcw_base = pwm_fcw_default;

	max_fcw_value = pwm_context.fcw_base + (pwm_fcw_window_sz * pwm_fcw_sz_step);
	min_fcw_value = pwm_context.fcw_base - (pwm_fcw_window_sz * pwm_fcw_sz_step);

	SDEC_IO_SettingFCW(stpSdecParam, pwm_context.fcw_value);

	nDeltaChkCount		= 0;

	//set__bit(stpSdecParam->stSDEC_IO_Reg->stcc[cur_ch*4], 1);//copy
	SDEC_HAL_STCCEnableCopy(cur_ch, SDEC_HAL_ENABLE);

#ifdef __NEW_PWM_RESET_COND__
	pcr_error_for_reset = 0;
#endif
}

/**
 *
 *  Initialisation function, resets hardware on first call
 *
 *  @return			void
 *
 * 	@ingroup sdec_pwm_func
 */
void SDEC_PWM_Init(S_SDEC_PARAM_T	*stpSdecParam )
{
	SDEC_DTV_SOC_Message( SDEC_PCR, "SDEC_PWM_Init\n");

	pwm_fcw_default		= ( FCW_DEFAULT_VALUE | FCW_PREFIX );
	pwm_fcw_threshold		= KHZ_TO_FCW(FREQ_THRESHOLD_KHZ);
	pwm_fcw_threshold_with_max_ignore = KHZ_TO_FCW(FREQ_THRESHOLD_KHZ_WITH_MAX_IGNORE);
	pwm_fcw_sz_step		= FCW_SZ_STEP;
	pwm_fcw_window_sz		= FCW_WINDOW_SZ;

	pwm_context_reset(stpSdecParam, 0);
	pwm_context.first_pcr_arrived = FALSE;
}


#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */

/**
********************************************************************************
* @brief
*   Set STC MAX Value for discontinuity check
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void SDEC_IO_SendFreeRunCmd(UINT8 ch, UINT8 free_run)
{
	/* Called with free_run = 1 : FREE RUN, free_run = 0 : STOP FREE RUN */
	if( free_run == _GO_FREE_RUN )
	{
		SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[37m\x1b[44m" "[PCR] SEND FREERUN CMD to AVDECODER !!!!!" "\x1b[0m" );
		SDEC_HAL_SetSTCCErrorCtrl(ch, 0x1, free_run); /* Set STC Discontinuity to 1 */
	}
	else
	{
		SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[37m\x1b[44m" "[PCR] STOP FREERUN CMD to AVDECODER !!!!!" "\x1b[0m" );
		SDEC_HAL_SetSTCCErrorCtrl(ch, 0xFFFFFFF /* F 7EA */, free_run); /* Set Discontinuiy to 0xFFFFFFF and disable */ 
		delta_error = 0;
	}
}


/**
********************************************************************************
* @brief
*   Check Free Run Status
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
* @return
*  DTV_STATUS_T
********************************************************************************
*/
UINT8 SDEC_IO_GetFreeRunCmdStatus(UINT8 ch)
{
	UINT32 val;
	
	val = SDEC_HAL_GetSTCCErrorCtrl(ch);
		
	if( ( val & 0x0FFFFFFF ) == 0x1 ) /* Check Discontinuity Only */
	{
		return _GO_FREE_RUN;
	}
	else
	{
		return _STOP_FREE_RUN;
	}
}


/**
********************************************************************************
* @brief
*   Check Free Run Condition and Send Free Run Command to AVDecoder
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void SDEC_IO_CheckFreeRun(UINT8 ch, UINT8 free_run)
{
	if( free_run  == _GO_FREE_RUN )
	{
#if 0
		if( _GO_FREE_RUN == SDEC_IO_GetFreeRunCmdStatus(ch) )
		{
			return;
		}
#else
		if( delta_error > MAX_DELTA_ERROR_FOR_FREE_RUN )
		{
			return;
		}
#endif
		delta_error++;

		SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[32m" "CHECK ENABLE FREERUN Ch[%d] Delta_Error[%d]" "\x1b[0m", ch, delta_error );

		if( delta_error > MAX_DELTA_ERROR_FOR_FREE_RUN )
		{
			SDEC_IO_SendFreeRunCmd(ch, _GO_FREE_RUN);
		}
	}
	else
	{
#if 0
		if( _STOP_FREE_RUN == SDEC_IO_GetFreeRunCmdStatus(ch) )
		{
			return;
		}
#else
		if( delta_error == 0 )
		{
			return;
		}
#endif

		delta_error--;

		SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[32m" "CHECK DISABLE FREERUN Ch[%d] Delta_Error[%d]" "\x1b[0m", ch, delta_error );

		if( delta_error == 0 )
		{
			SDEC_IO_SendFreeRunCmd(ch, _STOP_FREE_RUN);
		}
	}
}

#endif


#ifdef __NEW_PWM_RESET_COND__ /* jinhwan.bae for NEW PWM Reset Condition */

/**
********************************************************************************
* @brief
*   Set PWM Reset Condition
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void SDEC_IO_SetPWMResetCondition(S_SDEC_PARAM_T *stpSdecParam, UINT8 ch, BOOLEAN reset)
{
	SDEC_DTV_SOC_Message( SDEC_PCR, "PWM Reset Cond Ch[%d] Reset[%d] TotalCount[%d] ", ch, reset, pcr_error_for_reset );
	
	/* Reset Condition */
	if(reset)
	{
		if(pcr_error_for_reset < MAX_ERROR_FOR_PWM_RESET * 2)
		{
			pcr_error_for_reset++;
		}

		if( pcr_error_for_reset > MAX_ERROR_FOR_PWM_RESET )
		{
			pwm_context_reset(stpSdecParam, ch);
			SDEC_DTV_SOC_Message( SDEC_PCR, "PWM Reset Done Cond Ch[%d] TotalCount[%d] ", ch, pcr_error_for_reset );
		}
	}
	else /* Normal Case */
	{
		if( pcr_error_for_reset > 0 )
		{
			pcr_error_for_reset--;
		}
	}
}


#endif


/**
********************************************************************************
* @brief
*   Get Download Status in SDEC Driver
* @remarks
*   It's a temporal function for H13, Netcast 4.0 .
*   It's only for detecting Delayed Play mode in Time Shift
*   Return Value is used for work around of our stupid upload speed 
* @par requirements:
*
* @param
* @return
*  DTV_STATUS_T
********************************************************************************
*/
static BOOLEAN SDEC_IsDownloading(S_SDEC_PARAM_T	*stpSdecParam)
{
	int i;
	BOOLEAN retval = FALSE;

	for(i=0;i<4;i++)
	{
		if(stpSdecParam->stPIDMap[1][i].used == 0x1)
		{
			retval = TRUE;
			break;
		}
	}

	return retval;
}


/**
********************************************************************************
* @brief
*   PCR Recovery Algorithm Routine
* @remarks
*   HISTORY
*	jinhwan.bae
*	This Routine had been composed at the time of beginning of DTV development in LGE.
*	Now, nobody remember exactly about history of algorithm.
*	It's one of the reason why we can't modify with instantaneous temptation.
*	It's LG's own algorithm accumulated many years.
*	- 2012. 11. 16
*	Inserted one thing to send the command for freerunning with invalid PCR stream
*	Main Target Stream is 330MHz_SR6956_256QAM_STV_Estonia.ts
*	Recovery Characteristics
*		- Almost time : after 500ms from previous PCR interrupt, PCR-STC > 20ms
*		- Sometimes  : corrected pwm value is more than 100 KHz
*	Condition for Free Run
*		- insert delta_error : raising at > 20ms, falling at first pwm correction
*
* @par requirements:
* @param
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void action_pcr(S_SDEC_PARAM_T	*stpSdecParam, UINT8 cur_ch, UINT32 cur_pcr, UINT32 cur_stc)
{
	static SINT32	prev_pcr, prev_stc, prev_jit;
	UINT32 		cur_fcw_value = pwm_context.fcw_value;
	UINT32 		new_fcw_value = pwm_context.fcw_value;
	UINT32		capture_ms = OS_GetMsecTicks();
	SINT32		sDelta_clk;
	UINT32		uDelta_clk;
	SINT32		pcr_diff = 0;
	SINT32		stc_diff = 0;
	SINT32		pcr_jitt = 0;
	UINT32		cur_ch_src = 0;
	BOOLEAN		is_delayedplay = FALSE;

	if ( stpSdecParam->bPcrRecoveryFlag[cur_ch] == FALSE )
	{
		/* No need to check video pts diffrence
		 * because VDEC is not started!
		 */
  		return;
	}

	/* read uploading status */
	SDEC_HAL_CIDCRead(cur_ch, &cur_ch_src);
	cur_ch_src = ((cur_ch_src >> 20) & 0xF);
	if((cur_ch_src == 0x6) || (cur_ch_src == 0x7))
	{
		if( TRUE == SDEC_IsDownloading(stpSdecParam) )
		{
			SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[32m" "uploading mode" "\x1b[0m");
			is_delayedplay = TRUE;
		}
	}
	
	sDelta_clk = (SINT32)cur_pcr - (SINT32)cur_stc;
	uDelta_clk = abs(sDelta_clk);

	//SDEC_DTV_SOC_Message( SDEC_PCR, "action_pcr\n");
	/* --- If new_reset_discard is not zero pcr recovery will be skpped */
	if(pwm_context.new_reset_discard != 0)
	{
		pwm_context.new_reset_discard--;
		if(pwm_context.new_reset_discard == 0)
		{
			prev_pcr = cur_pcr;
			prev_stc = cur_stc;
			pwm_context.lastUpdateTime = capture_ms;
			pwm_context.max_ignore_count = 0;
			SDEC_DTV_SOC_Message( SDEC_PCR, "pwm_context.lastUpdateTime\n");
		}
		/* LIPSYNC
		 * video pts should be check before
		 * recovery the pcr normal track action!(after channel change status)
		 */
		 //VDEC_CheckPtsDiff();
		return;
	}

	/* --- Calulate PCR/STC difference, 45Khz --- */
    pcr_diff = cur_pcr - prev_pcr;
	stc_diff = cur_stc - prev_stc;
	pcr_jitt = cur_pcr - cur_stc;

	/*	Reduce the frequency of PCR arrival. 2000 was	*/
	/* from SAA7219 Reference driver					*/
	if (abs(pcr_diff) < 2250)	/* 50 ms */
	{
		/* LIPSYNC
		 * video pts should be check
		 * independently pcr duration
		 */
		 //VDEC_CheckPtsDiff();
		return;
	}

	#if ( PWM_DEBUG_LEVEL > 1 )
	if(pwm_context.new_reset_discard ==0)
	{
		SDEC_DTV_SOC_Message( SDEC_PCR, "[ch%d],(%5d Khz), (fcw:0x%08x),(ofs:%6ld), %08x, %08x, pcr_log, %5d",
				cur_ch,
				FCW_TO_KHZ(cur_fcw_value),
				cur_fcw_value,
				cur_fcw_value-pwm_context.fcw_base,
				cur_pcr, cur_stc , pcr_jitt
			);
	}
	#endif

	/* No Recovery Test */
	if (is_delayedplay == TRUE)
	{
		prev_pcr = cur_pcr;
		prev_stc = cur_stc;
		prev_jit = pcr_jitt;
		
		if( abs(pcr_diff) >= MTS_HUGE_PCR_DIFFERENCE)
		{
			SDEC_DTV_SOC_Message( SDEC_PCR, "pcr_diff so Huge->pcr_reset:%ld, %d, %d", abs(pcr_diff), prev_pcr, cur_pcr);
	
			pwm_context_reset(stpSdecParam, cur_ch);
		}

		return;
	}
	
	/* --- Calculate the error, and a correction value, the correction value
		   is based on the VCXO specs, and should cause the error value to
		   fall to zero in approximately 1 second ie an adjustment of 1 digit
		   should result in a modification to the clock of approximately 64
		   cycles per second. NOTE if we are closely synchronised then the
		   correction value may be zero.                         --- */

	if( abs(pcr_diff) >= MTS_HUGE_PCR_DIFFERENCE)
	{
		SDEC_DTV_SOC_Message( SDEC_PCR, "pcr_diff so Huge->pcr_reset:%ld, %d, %d", abs(pcr_diff), prev_pcr, cur_pcr);

		pwm_context_reset(stpSdecParam, cur_ch);

#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
		SDEC_IO_CheckFreeRun(cur_ch, _GO_FREE_RUN);
#endif

#ifdef __NEW_PWM_RESET_COND__
		/* jinhwan.bae, HUGE Diff Need Reset Now */
#endif

		/* LIPSYNC */
		//VDEC_SetPTSCheckClear(0);
		return;
	}
	else if(uDelta_clk >= MTS_HUGE_PCR_DIFFERENCE)
	{
		/*
		 *	Stream 의 Error에 의해, PCR에 glitch 가 발생한 경우,
		 *	pcr - stc 의 차이에 의해 복구하는 코드가 필요함.
		 *
		 *	----- Raleigh121_TW_Cable121_1 : Vch 2 관련 수정.
		 */
		SDEC_DTV_SOC_Message( SDEC_PCR, "uDelta_clk is Huge :%d", uDelta_clk);

		pwm_context_reset(stpSdecParam, cur_ch);

#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
		SDEC_IO_CheckFreeRun(cur_ch, _GO_FREE_RUN);
#endif

#ifdef __NEW_PWM_RESET_COND__
		/* jinhwan.bae, HUGE Diff Need Reset Now */
#endif

		/* LIPSYNC */
		//VDEC_SetPTSCheckClear(0);
		return;
	}

	if (pwm_context.lastUpdateTime && (uDelta_clk < PWM_MAX_DIFF_IGNORE/*MAX IGNORE Value*/))
	{
		SDEC_DTV_SOC_Message( SDEC_PCR, "MAX IGNORE Value Count [%d]", pwm_context.max_ignore_count);
#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
		SDEC_IO_CheckFreeRun(cur_ch, _STOP_FREE_RUN);
#endif

#ifdef __NEW_PWM_RESET_COND__
		/* jinhwan.bae, Normal and Recovery Sequence, set --  */
		SDEC_IO_SetPWMResetCondition( stpSdecParam, cur_ch, FALSE);
#endif

#if 1
		if(pwm_context.max_ignore_count < 100) /* jinhwan.bae temporally limit to 100, FIXME in M14~) */
		{
			pwm_context.max_ignore_count++;
		}
#endif
	}
	else if (pwm_context.lastUpdateTime && ((capture_ms - pwm_context.lastUpdateTime) <= 500))
	{
		/*
		 * Sampling time이 너무 작아 오차가 커질 수 있으므로 무시한다.
		 * 또한, Divide by zero도 방지한다.
		 */
		SDEC_DTV_SOC_Message( SDEC_PCR, "<= 500");
	}
	else if(uDelta_clk >= MAX_DELTA_CLK)
	{
		SDEC_DTV_SOC_Message( SDEC_PCR, "DELTA Check Point");

#ifdef __NEW_PWM_RESET_COND__
		/* jinhwan.bae, Error Case but need to waiting */
		SDEC_IO_SetPWMResetCondition( stpSdecParam, cur_ch, TRUE);
#else
		/* Original jinhwan.bae */
		pwm_context_reset(stpSdecParam, cur_ch);
#endif
		
#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
		SDEC_IO_CheckFreeRun(cur_ch, _GO_FREE_RUN);
#endif
	}
	else if (pwm_context.lastUpdateTime)
	{
		UINT32 elapsed_ms;
		SINT32 adjust;
		SINT32 coef = (27000000/45000);

		/* uDelta_clk is based on 45Khz clock	*/
		if(capture_ms > pwm_context.lastUpdateTime)
			elapsed_ms = capture_ms - pwm_context.lastUpdateTime;
		else
			elapsed_ms = capture_ms + (0xffffffff - pwm_context.lastUpdateTime);

		SDEC_DTV_SOC_Message( SDEC_PCR, "First Recovery after lastUpdateTime, elapsed ms(%5d) ",elapsed_ms);

		adjust = ( ((coef * uDelta_clk * 1000 ) / elapsed_ms) * pwm_fcw_sz_step ) / 250;

		if (sDelta_clk < 0)
			adjust = -adjust;

		/* for easy debug */
		SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[31m" "estimated instantaneous frequency = %lu.%03lu Mhz" "\x1b[0m",
			FCW_TO_KHZ(pwm_context.fcw_value + adjust) / 1000,
			FCW_TO_KHZ(pwm_context.fcw_value + adjust) % 1000);

		/* frequency를 계산해서 threshold 안의 값이 아니면 freerun으로 간다. */
		/* jinhwan.bae 안정적인 PCR 이면 크게 튄 첫 jitter 를 거른다. 2013. 3. 3 for protecting timeshift clock fluctuation */
		if(pwm_context.max_ignore_count > 10 )
		{
			if( abs(adjust) > pwm_fcw_threshold_with_max_ignore )
			{
				SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[31m" "adjust = %d threshold = %d It May Jitter! first PCR after max ignore !!!!!" "\x1b[0m",
					adjust,
					pwm_fcw_threshold_with_max_ignore);

				prev_pcr = cur_pcr;
				prev_stc = cur_stc;
				prev_jit = pcr_jitt;

				return;
			}
		}
		else
		{
			if( abs(adjust) > pwm_fcw_threshold)
			{
				SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[31m" "adjust = %d threshold = %d GOTO FREERUN!!!!!" "\x1b[0m",
					adjust,
					pwm_fcw_threshold);

				pwm_context_reset(stpSdecParam, cur_ch);

#ifdef __NEW_PWM_RESET_COND__
			/* jinhwan.bae, Remain to Original, Actually, another factor needed to set the adjust frequency as Stream - FIXME later */
#endif

#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
				SDEC_IO_CheckFreeRun(cur_ch, _GO_FREE_RUN);
#endif
				return;
			}
		}

		/*
		 * Jitter 가 급격하게 변하지 않은 경우,
		 * 계산된 Center frequency를 사용한다.
		 */
		pwm_context.fcw_value			+= (adjust * 103 ) / 100;
		pwm_context.lastUpdateTime		 = 0;
		pwm_context.new_adjust_skip		 = PWM_SUM_WINDOW-1;
		pwm_context.skip_chk_overshoot	 = PWM_SUM_WINDOW;
		nTimeStamps[-1] = capture_ms;

		new_fcw_value = pwm_context.fcw_value;

		if      (new_fcw_value < min_fcw_value) new_fcw_value = min_fcw_value;
		else if (new_fcw_value > max_fcw_value) new_fcw_value = max_fcw_value;

#if ( PWM_DEBUG_LEVEL > 0 )
		SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[33m" "[ch%d] adjust(%6d,%6ld), 0x%08x, elapsed_ms: %5d  %08x, %08x, %4d, %08x" "\x1b[0m",
					cur_ch,
					adjust,
					new_fcw_value-pwm_context.fcw_base,
					new_fcw_value,
					elapsed_ms,
					cur_pcr,
					cur_stc , pcr_jitt, cur_fcw_value
				);
#endif
		SDEC_IO_SettingFCW(stpSdecParam, new_fcw_value);

		pwm_context.fcw_value = new_fcw_value;

#ifdef __SEND_FREE_RUN_CMD_WITH_INVALID_PCR__	/* jinhwan.bae for free run command */
		SDEC_IO_CheckFreeRun(cur_ch, _STOP_FREE_RUN);
#endif

#ifdef __NEW_PWM_RESET_COND__
		/* jinhwan.bae, Normal and Recovery Sequence, set --  */
		SDEC_IO_SetPWMResetCondition( stpSdecParam, cur_ch, FALSE);
#endif

	}
	else
	{
		UINT32	changeMask;
		SINT32	adjust = 0;
		SINT32	nSignOfDelta;
		SINT32	nSignOfSlope, nDiffSlope;
		UINT32	index, o_idx;
		int		i, nOvershoot = 0;

		o_idx	= nDeltaChkCount / PWM_DELTA_WINDOW;
		index	= (o_idx % PWM_SUM_WINDOW);

		nSumOfDelta[index] += sDelta_clk;
		nDeltaChkCount++;

#ifdef __NEW_PWM_RESET_COND__
		/* jinhwan.bae, Normal and Recovery Sequence, set --  */
		SDEC_IO_SetPWMResetCondition( stpSdecParam, cur_ch, FALSE);
#endif
		if ((nDeltaChkCount % PWM_DELTA_WINDOW) == 0)
		{
			nTimeStamps[index]		= capture_ms;
			nMstElapsed[index]		= nTimeStamps[index] - nTimeStamps[index-1];
			//nSumOfDelta[index]	= (600 * 1000 * nSumOfDelta[index]) / PWM_DELTA_WINDOW;
			nMeanOfDelta[index] 	= 600 * 1000 * (SINT64) nSumOfDelta[index];
			DO_DIV_SINT64(nMeanOfDelta[index],PWM_DELTA_WINDOW);
			//nMeanOfDelta[index]	= nSumOfDelta[index] / nMstElapsed[index];	/* 1초당 변폭 */
			DO_DIV_SINT64(nMeanOfDelta[index], nMstElapsed[index]);
			nAbsOfDelta[index]		= abs(nMeanOfDelta[index]);

			if (pwm_context.new_adjust_skip > 0)
				pwm_context.new_adjust_skip--;

			if (o_idx >= PWM_SUM_WINDOW)
			{
				nSignOfDelta  = ((nMeanOfDelta[index] >= 0) ? 1 : -1);
				nSignOfSlope  = ((nAbsOfDelta[index-3] > nAbsOfDelta[index-4]) ? 0x1000 : 0);
				nSignOfSlope += ((nAbsOfDelta[index-2] > nAbsOfDelta[index-3]) ? 0x0100 : 0);
				nSignOfSlope += ((nAbsOfDelta[index-1] > nAbsOfDelta[index-2]) ? 0x0010 : 0);
				nSignOfSlope += ((nAbsOfDelta[index-0] > nAbsOfDelta[index-1]) ? 0x0001 : 0);

				changeMask	  = ((nMeanOfDelta[index-3] > 0) ? 0x1000 : 0);
				changeMask	 |= ((nMeanOfDelta[index-2] > 0) ? 0x0100 : 0);
				changeMask	 |= ((nMeanOfDelta[index-1] > 0) ? 0x0010 : 0);
				changeMask	 |= ((nMeanOfDelta[index-0] > 0) ? 0x0001 : 0);

				nDiffSlope = ((int)nAbsOfDelta[index] - (int)nAbsOfDelta[index-4])/PWM_SUM_WINDOW;

#if 0
				SDEC_DTV_SOC_Message( SDEC_PCR, "nMeanOfDelta[%lld, %lld, %lld, %lld]",
					nMeanOfDelta[index-3],
					nMeanOfDelta[index-2],
					nMeanOfDelta[index-1],
					nMeanOfDelta[index-0]
						);

				SDEC_DTV_SOC_Message( SDEC_PCR, "new_adjust_skip[%lu] changeMask[0x%04x] nAbsOfDelta[%d], nSignOfSlope[0x%04x] nOvershoot[%d]",
						pwm_context.new_adjust_skip,
						changeMask,
						nAbsOfDelta[index],
						nSignOfSlope,
						nOvershoot
						);
#endif
				if (pwm_context.skip_chk_overshoot == 0)
				{
					for (i = 0; i < PWM_SUM_WINDOW; i++)
					{
					  if (nAbsOfDelta[index-i] > 2700) nOvershoot++;
					}
				}

				if (pwm_context.new_adjust_skip > 0)
				{
					/*
					 *	Skip 3 times just after last adjustment
					 */
				}
				else if ((changeMask == 0x1110) || (changeMask == 0x1))
				{
					/*
					 *	Difference의 부호가 바뀌었으므로
					 *	Center frequency를 조정한다.
					 */
					int diff = (nMeanOfDelta[index] - nMeanOfDelta[index-4])/PWM_SUM_WINDOW;

					pwm_context.new_adjust_skip = PWM_SUM_WINDOW-1;
					pwm_context.skip_chk_overshoot = 0;
					adjust = (diff * 103 * pwm_fcw_sz_step) / (250 * 100);
#if ( PWM_DEBUG_LEVEL > 1 )
					SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[32m" "[ch%d] (changeMask) adjust(%3d)  diff[%4d]" "\x1b[0m",
									cur_ch,  adjust, diff);
					SDEC_DTV_SOC_Message( SDEC_PCR, "[ch%d] nMeanOfDelta[%d]%lld] nMeanOfDelta[%d][%lld]",
									cur_ch,  index, nMeanOfDelta[index], index-4, nMeanOfDelta[index-4]);
#endif
				}
				else if (nAbsOfDelta[index] < 250)
				{
					/*
					 *	System Clock has been almost converged,
					 *	Nothing to do.
					 */
					pwm_context.skip_chk_overshoot = 0;
				}
				else if (nSignOfSlope == 0x1111)
				{
					/*
					 *	System Clock is going to diverge.
					 *	MUST adjust FCW value to slope
					 */
					pwm_context.new_adjust_skip = PWM_SUM_WINDOW-1;
					adjust = nSignOfDelta * (nDiffSlope * 120)  * pwm_fcw_sz_step / (250 * 100);
#if ( PWM_DEBUG_LEVEL > 1 )
					SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[32m" "[ch%d] (nSignOfSlope == 0x1111) adjust(%3d)  nSignOfDelta[0x%04x] nDiffSlope[%4d]" "\x1b[0m",
									cur_ch,  adjust, nSignOfDelta, nDiffSlope);
					SDEC_DTV_SOC_Message( SDEC_PCR, "[ch%d] nMeanOfDelta[%d]%lld] nMeanOfDelta[%d][%lld]",
									cur_ch,  index, nMeanOfDelta[index], index-4, nMeanOfDelta[index-4]);
#endif
				}
				else if (nOvershoot >= 2)
				{
					/*
					 *	Jitter is too big, speed up more
					 *	MUST adjust FCW value to slope
					 */
					int diff1 = (nMeanOfDelta[index] - nMeanOfDelta[index-4])/PWM_SUM_WINDOW;
					int diff2 = (nMeanOfDelta[index] / 8);

					if      ((diff1 ^ diff2) &    0x8000000) diff1 = 0;
					else if ((diff1 < 0) && (diff2 < diff1)) diff1 = diff2;
					else if ((diff1 > 0) && (diff2 > diff1)) diff1 = diff2;

					pwm_context.new_adjust_skip = PWM_SUM_WINDOW-1;
					pwm_context.skip_chk_overshoot = PWM_SUM_WINDOW;
					adjust = (diff1 * 120  * pwm_fcw_sz_step) / (250*100);
#if ( PWM_DEBUG_LEVEL > 1 )
					SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[32m" "[ch%d] (nOvershoot >= 2) adjust(%3d)  diff1[%4d] diff2[%4d]" "\x1b[0m",
									cur_ch,  adjust, diff1, diff2);
					SDEC_DTV_SOC_Message( SDEC_PCR, "[ch%d] nMeanOfDelta[%d]%lld] nMeanOfDelta[%d][%lld]",
									cur_ch,  index, nMeanOfDelta[index], index-4, nMeanOfDelta[index-4]);
#endif
				}
				else if ((changeMask != 0x1111) && (changeMask != 0x0000))
				{
					if (pwm_context.skip_chk_overshoot > 0)
						pwm_context.skip_chk_overshoot--;
				}

				#if	0
				{
				int	idx_3 = ((index + PWM_SUM_WINDOW - 3) % PWM_SUM_WINDOW);
				int	idx_2 = ((index + PWM_SUM_WINDOW - 2) % PWM_SUM_WINDOW);
				int	idx_1 = ((index + PWM_SUM_WINDOW - 1) % PWM_SUM_WINDOW);

				dbgprint(", %4d, %4d, %4d, %4d,  %5d, %5d, %5d,  %5d,  %2d, ss, %04x, cm, %04x, %d(%d), %d",
							nMstElapsed [idx_3], nMstElapsed [idx_2], nMstElapsed [idx_1], nMstElapsed [index],
							nMeanOfDelta[idx_3], nMeanOfDelta[idx_2], nMeanOfDelta[idx_1], nMeanOfDelta[index],
							nSignOfDelta, nSignOfSlope, changeMask, nDiffSlope,
							adjust, pwm_context.skip_chk_overshoot);
				}
				#endif

				if (adjust == 0)
				{
					/* adjust 가 0이면 아무런 action 필요 없음. */
				}
				else
				{
					new_fcw_value += adjust;

					/* 보정한 Pwm Control 값을 Register에 반영	*/
					SDEC_IO_SettingFCW(stpSdecParam, new_fcw_value);
					pwm_context.fcw_value = new_fcw_value;
#if ( PWM_DEBUG_LEVEL > 0 )
				SDEC_DTV_SOC_Message( SDEC_PCR, "\x1b[34m" "[ch%d]NEW fcw, 0x%06x==>0x%06x, adjust(%3d)   %08x, %08x, %4d, %08x" "\x1b[0m",
								cur_ch,
								cur_fcw_value, new_fcw_value, adjust,
								cur_pcr,cur_stc , pcr_jitt, cur_fcw_value );
#endif
				}


			}

			if (index == (PWM_SUM_WINDOW-1))
			{
				nTimeStamps[-1] = nTimeStamps[index];
			}

			nAbsOfDelta[index-4]  = nAbsOfDelta[index];
			nMeanOfDelta[index-4] = nMeanOfDelta[index];
			nSumOfDelta[(index+1)%PWM_SUM_WINDOW] = 0;
		}
	}

	prev_pcr = cur_pcr;
	prev_stc = cur_stc;
	prev_jit = pcr_jitt;

	/* LIPSYNC
	 * video pts should be check before
	 * at normal return status of action_pcr function
	 */
	//VDEC_CheckPtsDiff();
}



void SDEC_PCRRecovery(struct work_struct *work)
{
	S_SDEC_PARAM_T 	*stpSdecParam;
	UINT32 			ui32Curr_stc 				= 0x0;
	UINT32 			ui32Curr_pcr 				= 0x0;
	UINT8 			cur_ch 						= 0x0;

	stpSdecParam =	container_of (work, S_SDEC_PARAM_T, PcrRecovery);

	LX_SDEC_CHECK_CODE( stpSdecParam == NULL, return, "Invalid parameters" );

	cur_ch			= stpSdecParam->stPCR_STC.ui8Channel;
	ui32Curr_stc 	= stpSdecParam->stPCR_STC.STC_hi_value;
	ui32Curr_pcr 	= stpSdecParam->stPCR_STC.PCR_hi_value;

#if PCR_RECOVERY_DEBUG
	SDEC_DTV_SOC_Message( SDEC_PCR,",%u, %u, %d", ui32Curr_stc, ui32Curr_pcr, ui32Curr_stc - ui32Curr_pcr);
#endif

	action_pcr(stpSdecParam, cur_ch, ui32Curr_pcr,ui32Curr_stc);
}

