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

#ifndef _IO_FRC_h
#define _IO_FRC_h

DTV_STATUS_T MCU_FRC_IPC_IOCTL(char *cliBuff, UINT32 strLen);

DTV_STATUS_T MCU_FRC_IO_Init(char *strBuff);

#endif
