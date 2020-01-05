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


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.02.16
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
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
#include <asm-generic/errno-base.h>
#include <linux/string.h>
#include <linux/workqueue.h>
#include <linux/version.h>

#include <mach/platform.h>
#include <asm/io.h>

#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"

#include "de_kapi.h"
#include "de_def.h"
#include "de_int_def.h"
#include "de_hal_def.h"
#include "de_cfg.h"
#include "de_ipc_def.h"
#include "de_hal.h"
#include "de_ipc.h"
#ifdef USE_VIDEO_TEST_MCU_IN_CPU
#include "mcu/mcu_test.h"
#include "mcu/io_video.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#undef  USE_DE_CPU_IPC_WKQ_SND
#define USE_DE_CPU_IPC_WKQ_RCV
#define DE_IPC_TRY_CNT 3000
#define DE_IPC_WAIT_TIME_MSEC  10
#define DE_IPC_TRY_CNT_FOR_JPG 10
#define DE_IPC_TRY_CNT_FOR_USB 10
#define DE_IPC_TRY_CNT_FOR_WEL 10
#define DE_IPC_TRY_CNT_FOR_WER 10

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef USE_LINUX_KERNEL
#define	DE_IPC_LOCK()			do { spin_lock_irqsave(&_g_de_ipc_lock, flags);	  } while(0)
#define DE_IPC_UNLOCK()			do { spin_unlock_irqrestore(&_g_de_ipc_lock, flags); } while(0)
#else
#define	DE_IPC_LOCK()
#define DE_IPC_UNLOCK()
#endif

#ifdef USE_DE_TRACE_IPC_MSG
#define	DE_IPC_DBG_PRT(pMsg, nCnt)	MCU_VIDEO_IPC_PRINT(__FILE__, __LINE__, __FUNCTION__, pMsg, nCnt);
#else
#define	DE_IPC_DBG_PRT(pMsg, nCnt)
#endif
#ifdef USE_DE_TRACE_IPC_CHK
#define	DE_IPC_DBG_CHK(msg)			MCU_VIDEO_IPC_CHECK(__FILE__, __LINE__, __FUNCTION__, msg);
#else
#define	DE_IPC_DBG_CHK(msg)
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#if defined(USE_DE_CPU_IPC_WKQ_SND) || defined(USE_DE_CPU_IPC_WKQ_RCV)
typedef struct {
	struct workqueue_struct *wrq;
#ifdef USE_DE_CPU_IPC_WKQ_SND
	struct work_struct wrkSnd;
#endif
#ifdef USE_DE_CPU_IPC_WKQ_RCV
	struct work_struct wrkRcv;
#endif
	OS_SEM_T mtxSnd;
} DE_WORKQUEUE_T;
#endif

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
#ifdef USE_DE_CPU_IPC_WKQ_SND
static void VIDEO_CPU_SendMsg(struct work_struct *work);
#else
static int VIDEO_CPU_Send2MCU(void);
#endif
#ifdef USE_DE_CPU_IPC_WKQ_RCV
static void DE_IPC_RcvMsg(struct work_struct *work);
#endif
UINT32 DE_REG_WB(UINT32 addr, char *pData, char *pField);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static	spinlock_t		_g_de_ipc_lock = SPIN_LOCK_UNLOCKED;
#else
static	DEFINE_SPINLOCK(_g_de_ipc_lock);
#endif

#if defined(USE_DE_CPU_IPC_WKQ_SND) || defined(USE_DE_CPU_IPC_WKQ_RCV)
static DE_WORKQUEUE_T gwrqDe;
#endif

static char *gpVideoBuffToMCU;
static char *gpVideoBuffFrMCU;

static DECLARE_WAIT_QUEUE_HEAD(wqAckFrMCU);
static DECLARE_WAIT_QUEUE_HEAD(wqIpcFrMCU);
static DECLARE_WAIT_QUEUE_HEAD(wqIpcForJPG);
static DECLARE_WAIT_QUEUE_HEAD(wqIpcForUSB);
static DECLARE_WAIT_QUEUE_HEAD(wqIpcForWEL);
static DECLARE_WAIT_QUEUE_HEAD(wqIpcForWER);
static DEFINE_SPINLOCK(spinWDog);

static MCU_VIDEO_EXCHANGE_T saIpcQueToMCU;
static MCU_VIDEO_EXCHANGE_T saIpcQueFrMCU;

//static char saSendBuff[VIDEO_MSG_STR_MAX];
static char saRecvBuff[VIDEO_MSG_STR_MAX];

static SINT32 sWDogCount = -1;
static int de_wakeup_send2mcu_timeout;
static int de_wakeup_recv4mcu_timeout;
static int de_wakeup_recv4jpg_timeout;
static int de_wakeup_recv4usb_timeout;
static int de_wakeup_recv4wel_timeout;
static int de_wakeup_recv4wer_timeout;

OS_SEM_T	_g_de_ipc_snd_sem;
OS_SEM_T	_g_de_ipc_rcv_sem;

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_Init(void)
{
	int ret = RET_OK;
	UINT32 addrVideoBuffToMCU;
	UINT32 addrVideoBuffFrMCU;

	do {
		OS_InitMutex(&_g_de_ipc_snd_sem, OS_SEM_ATTR_DEFAULT);
		OS_InitMutex(&_g_de_ipc_rcv_sem, OS_SEM_ATTR_DEFAULT);
		ret = DE_HAL_IPCInit(&addrVideoBuffToMCU, &addrVideoBuffFrMCU);
		if (ret) break;
		gpVideoBuffToMCU = (char *)addrVideoBuffToMCU;
		gpVideoBuffFrMCU = (char *)addrVideoBuffFrMCU;
#ifdef USE_QEMU_SYSTEM
#ifdef USE_VIDEO_TEST_MCU_IN_CPU
		if (ret) break;
		ret = VIDEO_MCU_IPC_Init((UINT32)gpVideoBuffToMCU, (UINT32)gpVideoBuffFrMCU);
#endif
#endif
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_Free(void)
{
	int ret = RET_OK;
	UINT32 addrVideoBuffToMCU;
	UINT32 addrVideoBuffFrMCU;

	do {
		addrVideoBuffToMCU = (UINT32)gpVideoBuffToMCU;
		addrVideoBuffFrMCU = (UINT32)gpVideoBuffFrMCU;
		ret = DE_HAL_IPCFree(&addrVideoBuffToMCU, &addrVideoBuffFrMCU);
		if (ret) break;
		gpVideoBuffToMCU = (char *)addrVideoBuffToMCU;
		gpVideoBuffFrMCU = (char *)addrVideoBuffFrMCU;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Send command to MCU via IPC
 *
 * @param ipcCmd [IN] command for IPC
 * @param pMsg [IN] pointer to delever Message to MCU
 * @param msgCnt [IN] Bytes to transfer to MCU
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_SetData(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	char *plBuff;
	int cmdSize = sizeof(ipcCmd);
	int ipcSize = cmdSize + msgCnt;

	DE_IPC_DBG_CHK("Begin");
	DE_IPC_DBG_PRT(pMsg, msgCnt);
	do {
		plBuff = OS_Malloc(ipcSize);
        CHECK_KNULL(plBuff);
		if ( !memcpy(plBuff, &ipcCmd, cmdSize) ) BREAK_WRONG(ipcCmd);
		if (msgCnt > 0) if ( copy_from_user(&plBuff[cmdSize], (void __user *)pMsg, msgCnt) ) BREAK_WRONG(msgCnt);
		DE_IPC_DBG_CHK("Enter");
		ret = VIDEO_CPU_PutData(plBuff, ipcSize);
		DE_IPC_DBG_CHK("Exit");
	} while (0);
	if (plBuff) OS_Free(plBuff);
	DE_IPC_DBG_CHK("End");

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Receive Message from MCU via IPC
 *
 * @param pMsg [OUT] pointer to delever Message to MCU
 * @param msgCnt [IN] Bytes to get from MCU
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_GetData(void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	char *plBuff = NULL;

	do {
		plBuff = OS_Malloc(msgCnt);
        CHECK_KNULL(plBuff);
		ret = OS_LockMutex(&_g_de_ipc_rcv_sem);
		if (ret) BREAK_WRONG(ret);
		if ( msgCnt != VIDEO_CPU_GetData(plBuff, msgCnt) ) BREAK_WRONG(msgCnt);
		DE_IPC_DBG_PRT(plBuff, msgCnt);
		ret = copy_to_user((void __user *)pMsg, plBuff, msgCnt);
        if (ret) BREAK_WRONG(msgCnt);
	} while (0);
	OS_UnlockMutex(&_g_de_ipc_rcv_sem);
	if (plBuff) OS_Free(plBuff);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Send CLI from CPU to MCU via IPC
 *
 * @param pMsg [IN] pointer to delever Message to MCU
 * @param msgCnt [IN] Bytes to transfer to MCU
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_SetStr(void *pMsg, UINT32 msgCnt)
{
	int ret = RET_ERROR;
	char *plBuff;

	do {
		plBuff = OS_Malloc(msgCnt+1);
        CHECK_KNULL(plBuff);
		memset(plBuff, 0, msgCnt+1);
		if ( copy_from_user(plBuff, (void __user *)pMsg, msgCnt) ) break;
		DE_IPC_DBG_PRT(plBuff, msgCnt);
		ret = VIDEO_CPU_PutStr(plBuff, VIDEO_IPC_CMD_CLI);
	} while (0);
	if (plBuff) OS_Free(plBuff);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Put string of cli to queue of IPC
 *
 * @param msgBuff [IN] message buffer pointer
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_CPU_PutStr(char *msgBuff, VIDEO_IPC_DATA_TYPE_T ipcType)
{
    int ret = RET_ERROR;

	ret = OS_LockMutex(&_g_de_ipc_snd_sem);
    do {
        CHECK_KNULL(msgBuff);
		DE_IPC_DBG_PRT(msgBuff, strlen(msgBuff));
		ret = VIDEO_IPC_PutLine2Queue(&saIpcQueToMCU, msgBuff, ipcType);
		if (ret) break;
#ifdef USE_DE_CPU_IPC_WKQ_SND
		OS_LockMutex(&gwrqDe.mtxSnd);
		queue_work(gwrqDe.wrq, &gwrqDe.wrkSnd);
#else
		ret = VIDEO_CPU_Send2MCU();
#endif
    } while (0);
	OS_UnlockMutex(&_g_de_ipc_snd_sem);

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Put String to IPC queue after slicing string as unit size
 *
 * @param pIpcQue [OUT] pointer of IPC queue
 * @param pStr [IN] pointer of CLI
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_IPC_PutLine2Queue(MCU_VIDEO_EXCHANGE_T *pIpcQue, char *pStr, VIDEO_IPC_DATA_TYPE_T ipcType)
{
	int ret = RET_ERROR;

	int totalLen;
	int totalCnt;
	int readLen;
	char msgBuffIPC[VIDEO_IPC_STR_MAX];

	do {
		totalLen = strlen(pStr)+1;
		DE_IPC_DBG_PRT(pStr, totalLen);
		totalCnt = totalLen/(VIDEO_IPC_STR_MAX - VIDEO_IPC_DATA);
		while (totalLen>0) {
			readLen = (totalLen < (VIDEO_IPC_STR_MAX - VIDEO_IPC_DATA)) ? totalLen : (VIDEO_IPC_STR_MAX - VIDEO_IPC_DATA);
			memcpy(&msgBuffIPC[VIDEO_IPC_DATA], pStr, readLen);
			msgBuffIPC[VIDEO_IPC_SIZE] = readLen;
			msgBuffIPC[VIDEO_IPC_CONT] = totalCnt;
			msgBuffIPC[VIDEO_IPC_FROM] = VIDEO_IPC_FROM_HOST;
			msgBuffIPC[VIDEO_IPC_TYPE] = ipcType;
			pStr	 += readLen;
			totalLen -= readLen;
			totalCnt--;
			ret = VIDEO_IPC_CopyStr2Queue(pIpcQue, msgBuffIPC);
			if (ret) break;
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Put data to queue of IPC
 *
 * @param msgBuff [IN] data buffer pointer
 * @param msgCnt [IN] bytes to copy to msgBuff
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_CPU_PutData(char *msgBuff, UINT32 msgCnt)
{
    int ret = RET_ERROR;

	DE_IPC_DBG_CHK("lock _g_de_ipc_snd_sem");
	ret = OS_LockMutex(&_g_de_ipc_snd_sem);
    do {
        CHECK_KNULL(msgBuff);
		DE_IPC_DBG_PRT(msgBuff, msgCnt);
		DE_IPC_DBG_CHK("Enter");
		ret = VIDEO_IPC_PutData2Queue(&saIpcQueToMCU, msgBuff, msgCnt);
		DE_IPC_DBG_CHK("Exit");
		if (ret) break;
#ifdef USE_DE_CPU_IPC_WKQ_SND
		OS_LockMutex(&gwrqDe.mtxSnd);
		queue_work(gwrqDe.wrq, &gwrqDe.wrkSnd);
#else
		DE_IPC_DBG_CHK("Enter");
		ret = VIDEO_CPU_Send2MCU();
		DE_IPC_DBG_CHK("Exit");
#endif
    } while (0);
	OS_UnlockMutex(&_g_de_ipc_snd_sem);
	DE_IPC_DBG_CHK("unlock _g_de_ipc_snd_sem");

    return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Put data to IPC queue after slicing data as unit size
 *
 * @param pIpcQue [OUT] pointer of IPC queue
 * @param pStr [IN] pointer of data
 * @param msgCnt [IN] Bytes to copy from string buffer to queue buffer
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_IPC_PutData2Queue(MCU_VIDEO_EXCHANGE_T *pIpcQue, char *pStr, UINT32 msgCnt)
{
	int ret = RET_ERROR;

	int totalLen;
	int totalCnt;
	int readLen;
	char msgBuffIPC[VIDEO_IPC_STR_MAX];

	DE_IPC_DBG_CHK("Begin");
	do {
		totalLen = msgCnt;
		totalCnt = totalLen/(VIDEO_IPC_STR_MAX - VIDEO_IPC_DATA);
		while (totalLen>0) {
			readLen = (totalLen < (VIDEO_IPC_STR_MAX - VIDEO_IPC_DATA)) ? totalLen : (VIDEO_IPC_STR_MAX - VIDEO_IPC_DATA);
			memcpy(&msgBuffIPC[VIDEO_IPC_DATA], pStr, readLen);
			msgBuffIPC[VIDEO_IPC_SIZE] = readLen;
			msgBuffIPC[VIDEO_IPC_CONT] = totalCnt;
			msgBuffIPC[VIDEO_IPC_FROM] = VIDEO_IPC_FROM_HOST;
			msgBuffIPC[VIDEO_IPC_TYPE] = VIDEO_IPC_CMD_VAL;
			pStr	 += readLen;
			totalLen -= readLen;
			totalCnt--;
			DE_IPC_DBG_CHK("Enter");
			ret = VIDEO_IPC_CopyStr2Queue(pIpcQue, msgBuffIPC);
			DE_IPC_DBG_CHK("Exit");
			DE_IPC_DBG_PRT(msgBuffIPC, readLen+4);
			if (ret) break;
		}
	} while (0);
	DE_IPC_DBG_CHK("End");

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief  Copy data to IPC queue
 *
 * @param pIpcQue [OUT] pointer of IPC Queue
 * @param pBuff [IN] pointer of data
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_IPC_CopyStr2Queue(MCU_VIDEO_EXCHANGE_T *pIpcQue, char *pBuff)
{
	int ret = RET_OK;
	UINT8 *pStr;
	int num;
	unsigned long flags;

	DE_IPC_DBG_CHK("Begin");
	do {
        CHECK_KNULL(pBuff);
		if (!pBuff[VIDEO_IPC_SIZE]) break;

        DE_IPC_LOCK();
		num = pIpcQue->wInx - pIpcQue->rInx;
        DE_IPC_UNLOCK();
		if (num<0) num += VIDEO_IPC_BUFF_NUM;
		if (num>(VIDEO_IPC_BUFF_NUM-2)) {
			pIpcQue->queOverflow++;
			ffprintk("pIpcQue Buffer Overflow\n");
			ret = RET_ERROR;
			break;
		}
		if (pIpcQue->queMax < (num+1)) pIpcQue->queMax = (num+1);

		pStr = pIpcQue->str[pIpcQue->wInx];
		DE_IPC_DBG_CHK("Enter");
		ret = VIDEO_IPC_CopyStr(pStr, pBuff);
		DE_IPC_DBG_CHK("Exit");
		DE_IPC_DBG_PRT(pStr, pStr[0]+4);
		if (ret) break;
        DE_IPC_LOCK();
        pIpcQue->wInx++;
		if (pIpcQue->wInx >= VIDEO_IPC_BUFF_NUM) pIpcQue->wInx = 0;
        DE_IPC_UNLOCK();
	} while (0);
	DE_IPC_DBG_CHK("End");

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Copy between buffers
 *
 * @param pdBuff [OUT] destination buffer pointer
 * @param psBuff [IN] source buffer pointer
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_IPC_CopyStr(char *pdBuff, char *psBuff)
{
	int ret = RET_OK;
	UINT32 *ptrDst = (UINT32 *)pdBuff;
	UINT32 *ptrSrc = (UINT32 *)psBuff;
	UINT32 ipcSize = psBuff[VIDEO_IPC_SIZE]+(VIDEO_IPC_DATA+3); // 4(Head) + 3 (4-byte allign)
	int i;

	do {
		ipcSize>>=2;
		if (ipcSize > (VIDEO_IPC_STR_MAX>>2)) {
			ffprintk("psBuff(%d) is over than %d\n", ipcSize, VIDEO_IPC_STR_MAX);
			ret = RET_ERROR;
			break;
		}
		for (i=0;i<ipcSize;i++) *ptrDst++ = *ptrSrc++;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Send Messag from IPC Queue to MCU memory for IPC which is located DDR memory
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
#ifdef USE_DE_CPU_IPC_WKQ_SND
void VIDEO_CPU_SendMsg(struct work_struct *work)
{
	int ret;
	VIDEO_IPC_STATUS_T ipcStatus;
	UINT32 tryCount;
	BOOLEAN sendingMesg2MCU = TRUE;
	DE_WORKQUEUE_T *lwrqDe = container_of(work, DE_WORKQUEUE_T, wrkSnd);

#ifdef USE_VIDEO_TEST_MCU_IN_CPU
	TEST_CPU_WakeUp();
#endif
	tryCount = 0;
	do {
		ret = VIDEO_IPC_PutQue2IPC(gpVideoBuffToMCU, &saIpcQueToMCU, &ipcStatus);
		if (ret) break;
		switch (ipcStatus) {
			case VIDEO_IPC_LAST :
			case VIDEO_IPC_OK :
				DE_HAL_WakeUpIPC();
				tryCount = 0;
			case VIDEO_IPC_BUSY :
				de_wakeup_send2mcu_timeout = 1;
				wait_event_interruptible_timeout(wqAckFrMCU, !de_wakeup_send2mcu_timeout, 1);
				if (de_wakeup_send2mcu_timeout) { tryCount++; break; }
				if (VIDEO_IPC_LAST != ipcStatus) break;
			default :
				sendingMesg2MCU = FALSE;
				break;
		}
		if (tryCount > DE_IPC_TRY_CNT) BREAK_WRONG(tryCount);
	} while (sendingMesg2MCU);
	if (sendingMesg2MCU) gpVideoBuffToMCU[VIDEO_IPC_SIZE] = 0;
	OS_UnlockMutex(&lwrqDe->mtxSnd);
}
#else
static int VIDEO_CPU_Send2MCU(void)
{
	int ret;
	VIDEO_IPC_STATUS_T ipcStatus;
	UINT32 tryCount;
	BOOLEAN sendingMesg2MCU = TRUE;

	DE_IPC_DBG_CHK("Begin");
	tryCount = 0;
	do {
		DE_IPC_DBG_CHK("Enter");
		ret = VIDEO_IPC_PutQue2IPC(gpVideoBuffToMCU, &saIpcQueToMCU, &ipcStatus);
		DE_IPC_DBG_CHK("Exit");
		if (ret) break;
		switch (ipcStatus) {
			case VIDEO_IPC_LAST :
			case VIDEO_IPC_OK :
				DE_HAL_WakeUpIPC();
				tryCount = 0;
				// don't insert break;
			case VIDEO_IPC_BUSY :
				de_wakeup_send2mcu_timeout = 1;
				wait_event_interruptible_timeout(wqAckFrMCU, !de_wakeup_send2mcu_timeout, 1);
				if (de_wakeup_send2mcu_timeout) { tryCount++; break; }
				if (VIDEO_IPC_LAST != ipcStatus) break;
				// don't insert break;
			default :
				sendingMesg2MCU = FALSE;
				break;
		}
		if (tryCount > DE_IPC_TRY_CNT) BREAK_WRONG(tryCount);
	} while (sendingMesg2MCU);
	if (sendingMesg2MCU) gpVideoBuffToMCU[VIDEO_IPC_SIZE] = 0;
	DE_IPC_DBG_CHK("End");

	return ret;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief Copy data form IPC queue to memory for IPC
 *
 * @param pBuff [OUT] buffer pointer for IPC which is located in DDR memory
 * @param pIpcQue [IN] buffer pointer for IPC Queue
 * @param pStatus [OUT] status to indicate transmition from IPC Queue to IPC memory
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_IPC_PutQue2IPC(char *pBuff, MCU_VIDEO_EXCHANGE_T *pIpcQue, VIDEO_IPC_STATUS_T *pStatus)
{
	int ret = RET_OK;
	UINT8 *pStr;
	unsigned long flags;

	DE_IPC_DBG_CHK("Begin");
	*pStatus = VIDEO_IPC_OK;
	do {
        CHECK_KNULL(pBuff);
        CHECK_KNULL(pIpcQue);
        DE_IPC_LOCK();
		if (pIpcQue->wInx == pIpcQue->rInx) {
			*pStatus = VIDEO_IPC_EMPTY;
            DE_IPC_UNLOCK();
			break;
		}
        DE_IPC_UNLOCK();
		if(pBuff[VIDEO_IPC_SIZE]) {
			*pStatus = VIDEO_IPC_BUSY;
			break;
		}
		pStr = pIpcQue->str[pIpcQue->rInx];
        DE_IPC_LOCK();
		pIpcQue->rInx++;
		if (pIpcQue->rInx >= VIDEO_IPC_BUFF_NUM) pIpcQue->rInx = 0;
        DE_IPC_UNLOCK();
		if (!pStr[VIDEO_IPC_SIZE]) {
			*pStatus = VIDEO_IPC_EMPTY;
			break;
		}
		if (!pStr[VIDEO_IPC_CONT]) *pStatus = VIDEO_IPC_LAST;
		DE_IPC_DBG_PRT(pStr, pStr[0]+4);
		DE_IPC_DBG_CHK("Enter");
		ret = VIDEO_IPC_CopyStr(pBuff, pStr);
		DE_IPC_DBG_CHK("Exit");
	} while (0);
	DE_IPC_DBG_CHK("End");

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief make DAM interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_CPU_WakeUpDMA(void)
{
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make JPG interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int VIDEO_CPU_WakeUpJPG(void)
{
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get data from queue of IPC
 *
 * @param msgBuff [OUT] data buffer pointer
 *
 * @return length of transfered data
 */
int VIDEO_CPU_GetData(char *msgBuff, UINT32 msgCnt)
{
	UINT32  readLen;
	UINT32  totalLen;
	UINT32  tryCount;
	UINT32  checkLen;
    BOOLEAN isCompleted;
	UINT32  receivedMsg;
	char    readBuf[VIDEO_IPC_STR_MAX];

	readLen  = 0;
	totalLen = 0;
	tryCount = 0;
	checkLen = 0;
	receivedMsg = 0;
    do {
		de_wakeup_recv4mcu_timeout = 1;
		wait_event_interruptible_timeout(wqIpcFrMCU, !de_wakeup_recv4mcu_timeout, 1);
		do {
			isCompleted = VIDEO_IPC_Gets(readBuf, &readLen, &saIpcQueFrMCU);
			if (!readLen) break;
			checkLen = totalLen + readLen;
			if (checkLen != msgCnt) {
				ffprintk("Received(%d) is different from Request(%d)\n", checkLen, msgCnt);
				totalLen = 0;
				isCompleted = FALSE;
				receivedMsg++;
				break;
			}
			memcpy(&msgBuff[totalLen], readBuf, readLen);
			totalLen = checkLen;
		} while (!isCompleted);
		if (tryCount++ > DE_IPC_TRY_CNT) { ffprintk("Wrong tryCount/GetCnt/GetMsg/ReqMsg(0x%x/0x%x/0x%x/0x%x)\n", tryCount, receivedMsg, checkLen, msgCnt); break; }
    } while (!isCompleted);

	return totalLen;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get data from IPC queue
 *
 * @param pBuff [OUT] buffer pointer to get data from IPC queue
 * @param pLen [OUT] Bytes to be copied
 * @param pIpcQue [IN] buffer pointer of IPC Queue
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
BOOLEAN VIDEO_IPC_Gets(char *pBuff, UINT32 *pLen, MCU_VIDEO_EXCHANGE_T *pIpcQue)
{
	BOOLEAN isCompleted = FALSE;
	UINT32  rdSize;
	UINT8 *pStr;

	*pLen = 0;
	do {
		if (pIpcQue->wInx == pIpcQue->rInx) break;
		pStr = pIpcQue->str[pIpcQue->rInx];
		rdSize = pStr[VIDEO_IPC_SIZE];
		if (!rdSize) break;
		if (rdSize > (VIDEO_IPC_STR_MAX-VIDEO_IPC_DATA)) break;
		memcpy(pBuff, &pStr[VIDEO_IPC_DATA], rdSize);
		*pLen += rdSize;
		pIpcQue->rInx++;
		if (pIpcQue->rInx >= VIDEO_IPC_BUFF_NUM) pIpcQue->rInx = 0;
		if(pStr[VIDEO_IPC_CONT]) break;
		isCompleted = TRUE;
	} while (0);

	return isCompleted;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt IPC handler to get data from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_ISR_FROM_MCU(unsigned long temp)
{
	VIDEO_IPC_CopyStr2Queue(&saIpcQueFrMCU, gpVideoBuffFrMCU);
	gpVideoBuffFrMCU[VIDEO_IPC_SIZE] = 0;

	switch (gpVideoBuffFrMCU[VIDEO_IPC_TYPE]) {
		case VIDEO_IPC_CMD_VAL :
			de_wakeup_recv4mcu_timeout = 0;
			wake_up_interruptible(&wqIpcFrMCU);
			break;
		case VIDEO_IPC_CMD_CLI :
		default :
			queue_work(gwrqDe.wrq, &gwrqDe.wrkRcv);
			break;
	}
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt JPG handler to get data from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_JPG_FROM_MCU(unsigned long temp)
{
	de_wakeup_recv4jpg_timeout = 0;
	wake_up_interruptible(&wqIpcForJPG);
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt USB handler to get data from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_USB_FROM_MCU(unsigned long temp)
{
	de_wakeup_recv4usb_timeout = 0;
	wake_up_interruptible(&wqIpcForUSB);
}

/**
 * @callgraph
 * @callergraph

 * @brief interrupt WEL handler to get data from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_WEL_FROM_MCU(unsigned long temp)
{
	de_wakeup_recv4wel_timeout = 0;
	wake_up_interruptible(&wqIpcForWEL);
}

/**
 * @callgraph
 * @callergraph

 * @brief interrupt WER handler to get data from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_WER_FROM_MCU(unsigned long temp)
{
	de_wakeup_recv4wer_timeout = 0;
	wake_up_interruptible(&wqIpcForWER);
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt DMA handler to get data from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_DMA_FROM_MCU(unsigned long temp)
{
	de_wakeup_send2mcu_timeout = 0;
	wake_up_interruptible(&wqAckFrMCU);
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief interrupt handler to get event about watch dog from MCU
 *
 * @param temp [IN] dummy argument
 */
void VIDEO_CPU_WDG_FROM_MCU(unsigned long temp)
{
	unsigned long flags;

	spin_lock_irqsave(&spinWDog, flags);
	sWDogCount = 0;
	spin_unlock_irqrestore(&spinWDog, flags);
	ffprintk("CPU received Wachdog Interrupt from DE MCU\n");
}

int VIDEO_WorkQueue_Init(void)
{
#if defined(USE_DE_CPU_IPC_WKQ_SND) || defined(USE_DE_CPU_IPC_WKQ_RCV)
	gwrqDe.wrq = create_workqueue("DE_IPC_SEND");

	if(!gwrqDe.wrq) {
		ffprintk("create work queue failed");
		return RET_ERROR;
	}

#ifdef USE_DE_CPU_IPC_WKQ_SND
	OS_InitMutex(&gwrqDe.mtxSnd, OS_SEM_ATTR_DEFAULT);
	INIT_WORK(&gwrqDe.wrkSnd, VIDEO_CPU_SendMsg);
#endif
#ifdef USE_DE_CPU_IPC_WKQ_RCV
	INIT_WORK(&gwrqDe.wrkRcv, DE_IPC_RcvMsg);
#endif
#endif

#ifdef USE_VIDEO_TEST_MCU_IN_CPU
	MCU_TEST_Init();
#endif

	return RET_OK;
}

int VIDEO_WorkQueue_Destory(void)
{
#if defined(USE_DE_CPU_IPC_WKQ_SND) || defined(USE_DE_CPU_IPC_WKQ_RCV)
	destroy_workqueue(gwrqDe.wrq);
#endif
#ifdef USE_VIDEO_TEST_MCU_IN_CPU
	MCU_TEST_Destory();
#endif

	return RET_OK;
}

#ifdef USE_DE_TRACE_IPC_MSG
int MCU_VIDEO_IPC_PRINT(const char *file, const int line, const char *fn, char *cliBuff, UINT32 strLen)
{
	int ret = RET_OK;
	int i;

	do {
		printk("%s:%d:%s, aaaaa length(%d)", file,line,fn,strLen);
		if (!strLen) break;
		printk(" data = [%02x", cliBuff[0]&0xff);
		for (i=1;i<strLen;i++) {
			printk(" %02x", cliBuff[i]&0xff);
			if ((i%4) == 3) printk(",");
		}
		printk("]");
	} while (0);
	printk("\n");

	return ret;
}

int MCU_VIDEO_IPC_CHECK(const char *file, const int line, const char *fn, char *cliBuff)
{
	printk("%s:%d:%s, %s\n", file,line,fn,cliBuff);

	return RET_OK;
}
#endif

#ifdef USE_DE_CPU_IPC_WKQ_RCV
/**
 * @callgraph
 * @callergraph
 *
 * @brief Receive Messag from IPC Queue for IPC memory which is located DDR memory
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
void DE_IPC_RcvMsg(struct work_struct *work)
{
	static UINT32 totalLen = 0;
	UINT32 checkLen;
    BOOLEAN isCompleted;
	UINT32 readLen;
	char readBuf[VIDEO_IPC_STR_MAX];
	int whichUart = 0;
	char *tok;
	int  argc;
	char **argv  = NULL;
	int  rdNum;
	int  i;
	LX_DE_REG_WR_T lReg;

	do {
		isCompleted = VIDEO_IPC_Gets(readBuf, &readLen, &saIpcQueFrMCU);
		if (!readLen) break;
		checkLen = totalLen + readLen;
		if (VIDEO_MSG_STR_MAX <= checkLen) {
			ffprintk("Received(%d) is over than Max(%d)\n", checkLen, VIDEO_MSG_STR_MAX);
			totalLen = 0;
			break;
		}
		memcpy(&saRecvBuff[totalLen], readBuf, readLen);
		totalLen = checkLen;
		if (!isCompleted) break;
		totalLen = 0;
#ifdef USE_DE_SWITCH_UART
		if ((tok = strstr(saRecvBuff, "\n" )) != NULL) *tok = 0;
		if (!strcmp(saRecvBuff, "UART_SWITCH_TO_CPU")) {
			ffprintk("%s\n", saRecvBuff);
			DE_HAL_SwitchUART0(whichUart);
		} else {
			argv = argv_split(GFP_KERNEL, saRecvBuff, &argc);
			if (!argv) break;
			if (!strcmp(argv[0], "CVRD")) {
				if      (argc == 2) rdNum = 1;
				else if (argc == 3) rdNum = simple_strtoul(argv[2], NULL, 0);
				else                break;
				lReg.wr_addr = simple_strtoul(argv[1], NULL, 0);
				for (i=0;i<rdNum;i++) {
					DE_HAL_ReadReg(lReg.wr_addr, &lReg.wr_data);
					sprintf(readBuf, "Address[ 0x%x ], Vaule[ 0x%08x ]", lReg.wr_addr, lReg.wr_data);
					VIDEO_CPU_PutStr(readBuf, VIDEO_IPC_CMD_PRT);
					lReg.wr_addr += 4;
				}
			} else if ( (!strcmp(argv[0], "CVWD")) || (!strcmp(argv[0], "CVWR")) ) {
				do {
					if (argc != 3) break;
					lReg.wr_addr = simple_strtoul(argv[1], NULL, 0);
					lReg.wr_data = simple_strtoul(argv[2], NULL, 0);
					sprintf(readBuf, "Address[ 0x%x ], Vaule[ 0x%08x ]", lReg.wr_addr, lReg.wr_data);
					VIDEO_CPU_PutStr(readBuf, VIDEO_IPC_CMD_PRT);
					DE_HAL_WriteReg(lReg.wr_addr, lReg.wr_data);
				} while (0);
			} else if ( !strcmp(argv[0], "CVBW") ) {
				if (argc != 4) break;
				lReg.wr_addr = simple_strtoul(argv[1], NULL, 16);
				lReg.wr_data = DE_REG_WB(lReg.wr_addr, argv[3], argv[2]);
				sprintf(readBuf, "Address[ 0x%x ], Vaule[ 0x%08x ]", lReg.wr_addr, lReg.wr_data);
				VIDEO_CPU_PutStr(readBuf, VIDEO_IPC_CMD_PRT);
			}
		}
#endif
	} while (0);
	if (argv) argv_free(argv);
}
#endif

UINT32 DE_REG_WB(UINT32 addr, char *pData, char *pField)
{
    UINT32 val = 0xdeadcafe;
    UINT32 rValue;
    UINT32 mValue;
    UINT32 nd, nw;
    UINT32 nDn, nUp;
    char *tok, *pUp, *pDn;

    do {
        if ((tok = strstr(pField, "]" )) == NULL) break;
        *tok = 0;
        if ((tok = strstr(pField, "[" )) == NULL) break;
        pUp = tok+1;
        if ((tok = strstr(pField, ":" )) != NULL) {
            pDn = tok+1;
            *tok = 0;
            if (strlen(pUp) == 0) break;
            if (strlen(pDn) == 0) break;
#ifdef USE_LINUX_KERNEL
            nUp = simple_strtoul(pUp, NULL, 10);
            nDn = simple_strtoul(pDn, NULL, 10);
#else
            nUp = strtoul(pUp, NULL, 10);
            nDn = strtoul(pDn, NULL, 10);
#endif
        } else {
            if (strlen(pUp) == 0) break;
#ifdef USE_LINUX_KERNEL
            nUp = simple_strtoul(pUp, NULL, 10);
#else
            nUp = strtoul(pUp, NULL, 10);
#endif
            nDn = nUp;
        }

        nw = 1;
        if (nUp > nDn) {
            nd = nDn;
            nw += (nUp - nDn);
        } else if (nUp < nDn) {
            nd = nUp;
            nw += (nDn - nUp);
        } else {
            nd = nUp;
        }
        if (nd + nw > 32) break;

        mValue   = GET_PVAL(0xFFFFFFFF, nd, nw);
		DE_HAL_ReadReg(addr, &rValue);
		rValue &= ~mValue;
		val = simple_strtoul(pData, NULL, 16);
        val    <<= nd;
        val     += rValue;

		DE_HAL_WriteReg(addr, val);
    } while(0);

    return val;
}

int DE_KIPC_SetData(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	char *plBuff;
	int cmdSize = sizeof(ipcCmd);
	int ipcSize = cmdSize + msgCnt;

	do {
		plBuff = OS_Malloc(ipcSize);
        CHECK_KNULL(plBuff);
		if ( !memcpy(plBuff, &ipcCmd, cmdSize) ) BREAK_WRONG(ipcCmd);
		if (msgCnt > 0) if ( !memcpy(&plBuff[cmdSize], pMsg, msgCnt) ) BREAK_WRONG(msgCnt);
		ret = VIDEO_CPU_PutData(plBuff, ipcSize);
	} while (0);
	if (plBuff) OS_Free(plBuff);

	return ret;
}

int DE_KIPC_GetData(void *pMsg, UINT32 msgCnt)
{
	int ret = RET_OK;
	char *plBuff = NULL;

	do {
		plBuff = OS_Malloc(msgCnt);
        CHECK_KNULL(plBuff);
		ret = OS_LockMutex(&_g_de_ipc_rcv_sem);
        if (ret) BREAK_WRONG(ret);
		if ( msgCnt != VIDEO_CPU_GetData(plBuff, msgCnt) ) BREAK_WRONG(msgCnt);
		DE_IPC_DBG_PRT(plBuff, msgCnt);
		if ( !memcpy(pMsg, plBuff, msgCnt) ) BREAK_WRONG(msgCnt);
	} while (0);
	OS_UnlockMutex(&_g_de_ipc_rcv_sem);
	if (plBuff) OS_Free(plBuff);

	return ret;
}

int VIDEO_DENC_SetTtx(VIDEO_TTX_PACK_T *pTtxPack)
{
    int ret = RET_OK;

	ret = DE_HAL_SetTtx(pTtxPack);

	return ret;
}

int VIDEO_JPG_WaitVsync(void)
{
	UINT32 tryCount;

	tryCount = 0;
	do {
		de_wakeup_recv4jpg_timeout = 1;
		wait_event_interruptible_timeout(wqIpcForJPG, !de_wakeup_recv4jpg_timeout, msecs_to_jiffies(DE_IPC_WAIT_TIME_MSEC));
		if (!de_wakeup_recv4jpg_timeout) break;
		tryCount++;
	} while (tryCount < DE_IPC_TRY_CNT_FOR_JPG);

	return (tryCount < DE_IPC_TRY_CNT_FOR_JPG)?RET_OK:RET_TIMEOUT;
}

int VIDEO_USB_WaitVsync(void)
{
	UINT32 tryCount;

	tryCount = 0;
	do {
		de_wakeup_recv4usb_timeout = 1;
		wait_event_interruptible_timeout(wqIpcForUSB, !de_wakeup_recv4usb_timeout, msecs_to_jiffies(DE_IPC_WAIT_TIME_MSEC));
		if (!de_wakeup_recv4usb_timeout) break;
		tryCount++;
	} while (tryCount < DE_IPC_TRY_CNT_FOR_USB);

	return (tryCount < DE_IPC_TRY_CNT_FOR_USB)?RET_OK:RET_TIMEOUT;
}

int VIDEO_WEL_WaitVsync(void)
{
	UINT32 tryCount;

	tryCount = 0;
	do {
		de_wakeup_recv4wel_timeout = 1;
		wait_event_interruptible_timeout(wqIpcForWEL, !de_wakeup_recv4wel_timeout, msecs_to_jiffies(DE_IPC_WAIT_TIME_MSEC));
		if (!de_wakeup_recv4wel_timeout) break;
		tryCount++;
	} while (tryCount < DE_IPC_TRY_CNT_FOR_WEL);

	return (tryCount < DE_IPC_TRY_CNT_FOR_WEL)?RET_OK:RET_TIMEOUT;
}

int VIDEO_WER_WaitVsync(void)
{
	UINT32 tryCount;

	tryCount = 0;
	do {
		de_wakeup_recv4wer_timeout = 1;
		wait_event_interruptible_timeout(wqIpcForWER, !de_wakeup_recv4wer_timeout, msecs_to_jiffies(DE_IPC_WAIT_TIME_MSEC));
		if (!de_wakeup_recv4wer_timeout) break;
		tryCount++;
	} while (tryCount < DE_IPC_TRY_CNT_FOR_WER);

	return (tryCount < DE_IPC_TRY_CNT_FOR_WER)?RET_OK:RET_TIMEOUT;
}

/** @} */
