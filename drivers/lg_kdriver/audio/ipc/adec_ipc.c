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


/** 
 *	@file adec_ipc.c
 *	 
 *
 *	@author		Jung, Kyung Soon (kyungsoon.jung@leg.com)
 *	@version	0.0.1
 *	@date		2012-03-15
 *	@note		
 *	@see		http://www.lge.com	
 *	@addtogroup ADEC_COMMON
 *	@{
 */

#include "common/adec_common.h"
#include "common/adec_reg_api.h"
#include "ipc/adec_ipc.h"
#include "ipc/adec_ipc_internal.h"
#include "adec_ipc_internal.h"
static void *IPC_MEM_MOD = NULL;


int IPC_GetStructSize()
{
	return sizeof(IpcInfo);
}

ADEC_RESULT IPC_Init(
	void* _ipc, 
	IpcRegister _writeAddr, 
	IpcRegister _readAddr,
	unsigned int _syncWord,
	unsigned int _memSize,
	void* _physicalAddr,
	void* _logicalAddr,
	IpcRole _ipcRole)
{
	IpcInfo* ipc;

	IPC_ASSERT_STR(
		_ipc != NULL,
		return ADEC_ERR_NULL,
		"_ipc should not be null\n");

	ipc = (IpcInfo*)_ipc;

	ipc->writeOffsetAddr 	= _writeAddr;
	ipc->readOffsetAddr 	= _readAddr;
	ipc->syncWord 			= _syncWord;
	ipc->maxSize			= _memSize;
	ipc->physicalAddr		= _physicalAddr;
	ipc->logicalAddr		= _logicalAddr;
	ipc->role				= _ipcRole;
	ipc->interruptFunc		= NULL;
	ipc->interruptParam		= NULL;

	return ADEC_ERR_NONE;
}

ADEC_RESULT IPC_ClearRegister(void* _ipc, int _force)
{
	IpcInfo* ipc;
	unsigned int readOffset;
	unsigned int writeOffset;

	IPC_ASSERT_STR(
		_ipc != NULL,
		return ADEC_ERR_NULL,
		"_ipc should not be null\n");

	ipc = (IpcInfo*)_ipc;

	writeOffset = ADEC_ReadRegister(ipc->writeOffsetAddr);
	readOffset = ADEC_ReadRegister(ipc->readOffsetAddr);

	if (writeOffset != readOffset && _force == 0)
	{
		return ADEC_ERR_GENERAL;
	}

	ADEC_WriteRegister(ipc->writeOffsetAddr, 0);
	ADEC_WriteRegister(ipc->readOffsetAddr , 0);

	return ADEC_ERR_NONE;
}

ADEC_RESULT IPC_WriteCommand(
	void* _ipc, 
	IpcHeader* _ipcHeader,
	void* _param,
	int _sendIntrrupt)
{
	IpcInfo* ipc;
	unsigned int *startAddr;
	unsigned int *ipcStartAddr;
	unsigned int writeOffset;
	unsigned int readOffset;

	int freeSize;
	int cmdLength;

	IPC_ASSERT_STR(
		_ipc != NULL && _ipcHeader != NULL,
		return ADEC_ERR_NULL,
		"_ipc & _ipcHeader should not be null\n");

	ipc = (IpcInfo*)_ipc;

	if (IPC_ROLE_WRITER != ipc->role)
	{
		return ADEC_ERR_PERMISSION;
	}

	writeOffset = ADEC_ReadRegister(ipc->writeOffsetAddr);
	readOffset 	= ADEC_ReadRegister(ipc->readOffsetAddr);

	if ( writeOffset < readOffset)
	{
		freeSize = (int)readOffset - (int)writeOffset;
	}
	else
	{
		freeSize = (int)(ipc->maxSize) - (int)writeOffset + (int)readOffset;
	}

	cmdLength = sizeof(IpcHeader) + (int)(_ipcHeader->paramLength) + 4;

	if( cmdLength >= freeSize)
	{
		return ADEC_ERR_OVERFLOW;
	}

	startAddr = (unsigned int*)ipc->logicalAddr;

	IPC_ASSERT(writeOffset < ipc->maxSize, return ADEC_ERR_DATA_CORRUPTED);
	
	if (writeOffset + (unsigned int)cmdLength >= ipc->maxSize)
	{
		if (readOffset <= (unsigned int)cmdLength)
		{
			return ADEC_ERR_OVERFLOW;
		}
		ipcStartAddr = &startAddr[writeOffset >> 2];
		ipcStartAddr[0] = IPC_END_FLAG;
		ADEC_CACHE_WRITEBACK(ipcStartAddr, 4);
		writeOffset = 0;
	}

	ipcStartAddr = &startAddr[writeOffset >> 2];
	ipcStartAddr[0] = ipc->syncWord;
	writeOffset += 4;

	ADEC_MEMCPY(IPC_MEM_MOD, &startAddr[writeOffset >> 2], _ipcHeader, sizeof(IpcHeader));
	writeOffset += sizeof(IpcHeader);
	ADEC_ASSERT((_ipcHeader->paramLength & 0x03) == 0,
		return ADEC_ERR_ALIGNMENT);
	if (_ipcHeader->paramLength > 0)
	{
		ADEC_ASSERT(_param != NULL,
		            return ADEC_ERR_NULL;);
		ADEC_MEMCPY(IPC_MEM_MOD, &startAddr[writeOffset >> 2], _param, _ipcHeader->paramLength);
		writeOffset += _ipcHeader->paramLength;
	}
	ADEC_CACHE_WRITEBACK(ipcStartAddr, cmdLength);

	ADEC_WriteRegister(ipc->writeOffsetAddr, writeOffset);

	if(_sendIntrrupt && ipc->interruptFunc)
	{
		ipc->interruptFunc(ipc->interruptParam);
	}

	return ADEC_ERR_NONE;
}


ADEC_RESULT IPC_SetInterrupt(
	void* _ipc, 
	IpcSendIntFunc _func, 
	void* _param)
{
	IpcInfo* ipc;

	IPC_ASSERT_STR(
		_ipc != NULL,
		return ADEC_ERR_NULL,
		"_ipc should not be null\n");

	ipc = (IpcInfo*)_ipc;

	ipc->interruptFunc = _func;
	ipc->interruptParam = _param;

	return ADEC_ERR_NONE;
}

ADEC_RESULT IPC_ReadCommand(
	void* _ipc,
	IpcHeader** _ipcHeader,
	unsigned int* _paramLength)
{
	IpcInfo* ipc;
	IpcHeader* param;
	unsigned int* readPosition;
	unsigned int writeOffset;
	unsigned int readOffset;
	int usedSize;
#ifdef CACHE_CONTROL_ENABLE
	unsigned int cacheStart;
	unsigned int cacheEnd;
#endif


	IPC_ASSERT_STR(
		_ipc != NULL && _ipcHeader != NULL && _paramLength != NULL,
		return ADEC_ERR_NULL,
		"_ipc & _ipcHeader should not be null\n");

	ipc = (IpcInfo*)_ipc;

	if (IPC_ROLE_READER != ipc->role)
	{
		return ADEC_ERR_PERMISSION;
	}

	writeOffset = ADEC_ReadRegister(ipc->writeOffsetAddr);
	readOffset 	= ADEC_ReadRegister(ipc->readOffsetAddr);

	if ( writeOffset < readOffset)
	{
		usedSize = (int)(ipc->maxSize) - (int)readOffset + (int)writeOffset;
	}
	else
	{
		usedSize = (int)writeOffset - (int)readOffset;
	}

	IPC_ASSERT_STR(
		usedSize >= 0,
		return ADEC_ERR_DATA_CORRUPTED,
		"usedSize cannot be smaller than 0\n");

	if (usedSize == 0)
	{
		return ADEC_ERR_UNDERFLOW;
	}

	readPosition = &(((unsigned int*)ipc->logicalAddr)[readOffset >> 2]);

	ADEC_CACHE_INVALIDATE(readPosition, ADEC_CNST_IPC_CACHE_SIZE);
#ifdef CACHE_CONTROL_ENABLE
	cacheStart = ((unsigned int)readPosition) & ADEC_CNST_IPC_CACHE_MASK;
	cacheEnd = (((unsigned int)readPosition + ADEC_CNST_IPC_CACHE_SIZE - 1) 
		        & ADEC_CNST_IPC_CACHE_MASK)
		       + ADEC_CNST_IPC_CACHE_SIZE;
#endif

	if (*readPosition != ipc->syncWord)
	{	
		// Find Sync
		while(*readPosition != ipc->syncWord && usedSize > 0)
		{
			if (*readPosition == IPC_END_FLAG)
			{
				readOffset = 0;
				if (ipc->wraparoundAction == IPC_WRAPAROUND_REGARD_AS_ERROR)
				{
					ADEC_WriteRegister(ipc->readOffsetAddr, readOffset);
					return ADEC_ERR_WRAPAROUND;
				}
				usedSize = (int)(writeOffset);
				readPosition = (unsigned int*)ipc->logicalAddr;
#ifdef CACHE_CONTROL_ENABLE
				ADEC_CACHE_INVALIDATE((void*)readPosition, ADEC_CNST_IPC_CACHE_SIZE);
				cacheStart = ((unsigned int)readPosition) & ADEC_CNST_IPC_CACHE_MASK;
				cacheEnd = (((unsigned int)readPosition + ADEC_CNST_IPC_CACHE_SIZE - 1)
					        & ADEC_CNST_IPC_CACHE_MASK)
					       + ADEC_CNST_IPC_CACHE_SIZE;
#endif
			}
			else
			{
				readPosition ++;
				usedSize -= 4;
				readOffset += 4;
#ifdef CACHE_CONTROL_ENABLE
				IPC_ASSERT_STR((unsigned int)readPosition >= cacheStart,
				               return ADEC_ERR_GENERAL;,
				               "Cache Start : %08X\tRead Position %08X\n",
				               cacheStart,
				               (unsigned int)readPosition);
				if ((unsigned int)readPosition >= cacheEnd)
				{
					ADEC_CACHE_INVALIDATE((void*)cacheEnd, ADEC_CNST_IPC_CACHE_SIZE);
					cacheEnd += ADEC_CNST_IPC_CACHE_SIZE;
					IPC_ASSERT_STR((unsigned int)readPosition < cacheEnd,
					                return ADEC_ERR_GENERAL;,
					                "In this condition readPosition(%08X) should be less than cacheEnd(%08X)\n",
					                (unsigned int)readPosition,
					                cacheStart);
				}
#endif
			}
		}
	}

	if(usedSize == 0)
	{
		ADEC_WriteRegister(ipc->readOffsetAddr, readOffset);
		IPC_DBG_ERR("Fail to find sync\n");
		return ADEC_ERR_DATA_CORRUPTED;
	}
	
	IPC_ASSERT_STR(*readPosition == ipc->syncWord,
	                return ADEC_ERR_GENERAL;,
	                "If reach to this code, Threre has to be sync word at read position\n");
	
	readPosition ++;
	readOffset += 4;
	
#ifdef CACHE_CONTROL_ENABLE
	// Validation cached area
	IPC_ASSERT_STR((unsigned int)readPosition >= cacheStart,
	               return ADEC_ERR_GENERAL;,
	               "Cache Start : %08X\tRead Position %08X\n",
	               cacheStart,
	               (unsigned int)readPosition);
	
	while((unsigned int)readPosition + sizeof(IpcHeader) >= cacheEnd)
	{
		ADEC_CACHE_INVALIDATE((void*)cacheEnd, ADEC_CNST_IPC_CACHE_SIZE);
		cacheEnd += ADEC_CNST_IPC_CACHE_SIZE;
	}
#endif
	

	param = (IpcHeader*)readPosition;

	*_ipcHeader = param;
	*_paramLength = param->paramLength;
	
#ifdef CACHE_CONTROL_ENABLE
	readPosition += sizeof(IpcHeader) >> 2;

	while((unsigned int)readPosition + param->paramLength >= cacheEnd)
	{
		ADEC_CACHE_INVALIDATE((void*)cacheEnd, ADEC_CNST_IPC_CACHE_SIZE);
		cacheEnd += ADEC_CNST_IPC_CACHE_SIZE;
	}
#endif

	readOffset += param->paramLength + sizeof(IpcHeader);

	ADEC_WriteRegister(ipc->readOffsetAddr, readOffset);

	return ADEC_ERR_NONE;
}

int IPC_CheckHasIpc(void* _ipc)
{
	if(IPC_GetUsedSize(_ipc) > 0)
	{
		return 1;
	}
	
	return 0;
}

int IPC_GetUsedSize(void* _ipc)
{
	IpcInfo* ipc;
	unsigned int writeOffset;
	unsigned int readOffset;
	int usedSize;

	ipc = (IpcInfo*)_ipc;

	IPC_ASSERT_STR(
		_ipc != NULL,
		return -ADEC_ERR_NULL,
		"_ipc should not be null\n");

	writeOffset = ADEC_ReadRegister(ipc->writeOffsetAddr);
	readOffset 	= ADEC_ReadRegister(ipc->readOffsetAddr);

	if ( writeOffset < readOffset)
	{
		usedSize = (int)(ipc->maxSize) - (int)readOffset + (int)writeOffset;
	}
	else
	{
		usedSize = (int)writeOffset - (int)readOffset;
	}

	return usedSize;
}

int IPC_GetFreeSize(void* _ipc)
{
	IpcInfo* ipc;
	unsigned int writeOffset;
	unsigned int readOffset;

	int freeSize;

	IPC_ASSERT_STR(
		_ipc != NULL,
		return -ADEC_ERR_NULL,
		"_ipc should not be null\n");

	ipc = (IpcInfo*)_ipc;

	writeOffset = ADEC_ReadRegister(ipc->writeOffsetAddr);
	readOffset 	= ADEC_ReadRegister(ipc->readOffsetAddr);

	if ( writeOffset < readOffset)
	{
		freeSize = (int)readOffset - (int)writeOffset;
	}
	else
	{
		freeSize = (int)(ipc->maxSize) - (int)writeOffset + (int)readOffset;
	}

	return freeSize;
}

ADEC_RESULT IPC_SetWraparoundAction(void* _ipc, IpcWraparoundAction _wraparoundAction)
{
	IpcInfo* ipc;

	IPC_ASSERT_STR(
		_ipc != NULL,
		return ADEC_ERR_NULL;,
		"_ipc should not be null\n");

	ipc = (IpcInfo*)_ipc;

	IPC_ASSERT(
		_wraparoundAction == IPC_WRAPAROUND_CONTINUE || _wraparoundAction == IPC_WRAPAROUND_REGARD_AS_ERROR,
		return ADEC_ERR_RANGE;);

	ipc->wraparoundAction = _wraparoundAction;

	return ADEC_ERR_NONE;
}

/** @} */


