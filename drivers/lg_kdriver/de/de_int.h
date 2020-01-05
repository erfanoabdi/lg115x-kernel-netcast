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

#ifndef _DE_INT_h
#define _DE_INT_h

irqreturn_t DE_IPC_interrupt(int irq, void *dev_id, struct pt_regs *regs);
irqreturn_t DE_VSYNC_interrupt(int irq, void *dev_id, struct pt_regs *regs);

void DE_IPC_Handler(void);
void DE_VSYNC_Handler(void);

void VIDEO_CPU_VSYNC_Tasklet(unsigned long temp);

int VIDEO_IPC_GetStatus(VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus);
int VIDEO_CPU_ClearWDG(void);
int VIDEO_CPU_ClearIPC(void);
int VIDEO_CPU_ClearDMA(void);
int VIDEO_CPU_ClearJPG(void);
int VIDEO_CPU_ClearUSB(void);
int DE_VSYNC_WaitTimeOut(int timeout);
void DE_VSYNC_WakeUp(void);

#endif
