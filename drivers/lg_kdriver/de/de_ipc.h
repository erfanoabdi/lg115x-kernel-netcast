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

#ifndef _DE_IPC_h
#define _DE_IPC_h

#include "de_vbi_def.h"

int VIDEO_IPC_CopyStr2Queue(MCU_VIDEO_EXCHANGE_T *pIpcQue, char *pBuff);
int VIDEO_IPC_PutQue2IPC(char *pBuff, MCU_VIDEO_EXCHANGE_T *pIpcQue, VIDEO_IPC_STATUS_T *pStatus);
int VIDEO_CPU_WakeUpIPC(void);
int VIDEO_CPU_WakeUpJPG(void);
int VIDEO_IPC_CopyStr(char *pdBuff, char *psBuff);
//int MCU_VIDEO_IPC_RUN2CLI(char *cliBuff);
BOOLEAN VIDEO_IPC_GetData(char *pBuff, UINT32 *pLen, MCU_VIDEO_EXCHANGE_T *pIpcQue);
BOOLEAN VIDEO_GetPrintOfIPC(void);

int VIDEO_IPC_MakeArg2Str(int argc, char **argv, char *pStr);
int VIDEO_CPU_PutStr(char *msgBuff, VIDEO_IPC_DATA_TYPE_T ipcType);
int VIDEO_IPC_PutLine2Queue(MCU_VIDEO_EXCHANGE_T *pIpcQue, char *pStr, VIDEO_IPC_DATA_TYPE_T ipcType);
int DBI_VIDEO_FIRWARE(int argc, char **argv);
int VIDEO_IPC_PutData2Queue(MCU_VIDEO_EXCHANGE_T *pIpcQue, char *pStr, UINT32 msgCnt);
int VIDEO_CPU_PutData(char *msgBuff, UINT32 msgCnt);
int VIDEO_CPU_GetData(char *msgBuff, UINT32 msgCnt);
//int VIDEO_CPU_GetStr(char *pBuff, UINT32 *pLen, BOOLEAN *pReady);
BOOLEAN VIDEO_IPC_Gets(char *pBuff, UINT32 *pLen, MCU_VIDEO_EXCHANGE_T *pIpcQue);
int DE_IPC_Init(void);
int DE_IPC_SetData(UINT32 cmd, void *pMsg, UINT32 msgCnt);
int DE_IPC_GetData(void *pMsg, UINT32 msgCnt);
int DE_IPC_SetStr(void *pMsg, UINT32 msgCnt);

void VIDEO_CPU_ISR_FROM_MCU(unsigned long temp);
void VIDEO_CPU_DMA_FROM_MCU(unsigned long temp);
void VIDEO_CPU_WDG_FROM_MCU(unsigned long temp);
void VIDEO_CPU_JPG_FROM_MCU(unsigned long temp);
void VIDEO_CPU_USB_FROM_MCU(unsigned long temp);
void VIDEO_CPU_WEL_FROM_MCU(unsigned long temp);
void VIDEO_CPU_WER_FROM_MCU(unsigned long temp);
int VIDEO_WorkQueue_Init(void);
int VIDEO_WorkQueue_Destory(void);
int DE_IPC_Free(void);
#ifdef USE_DE_TRACE_IPC_MSG
int MCU_VIDEO_IPC_PRINT(const char *file, const int line, const char *fn, char *cliBuff, UINT32 strLen);
int MCU_VIDEO_IPC_CHECK(const char *file, const int line, const char *fn, char *cliBuff);
#endif
int DE_KIPC_SetData(UINT32 ipcCmd, void *pMsg, UINT32 msgCnt);
int DE_KIPC_GetData(void *pMsg, UINT32 msgCnt);
int VIDEO_DENC_SetTtx(VIDEO_TTX_PACK_T *pTtxPack);

int VIDEO_WEL_WaitVsync(void);
int VIDEO_WER_WaitVsync(void);
#endif
