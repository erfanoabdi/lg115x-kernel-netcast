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

#ifndef __MODULE_CMD_LIPSYNC_H__
#define __MODULE_CMD_LIPSYNC_H__

#include "imc/adec_imc_cmd.h"


#define LIPSYNC_CMD_SET_ONOFF			ADEC_CMD(0x2000, LipsyncCmdSetOnoff)
#define LIPSYNC_CMD_SET_BOUND			ADEC_CMD(0x2001, LipsyncCmdSetBound)
#define LIPSYNC_CMD_SET_CLOCKTYPE		ADEC_CMD(0x2002, LipsyncCmdSetclocktype)
#define LIPSYNC_CMD_SET_BASE			ADEC_CMD(0x2003, LipsyncCmdSetBase)
#define LIPSYNC_CMD_SET_FS              ADEC_CMD(0x2004, LipsyncCmdSetFs)
#define LIPSYNC_CMD_SET_DEBUGPRINT      ADEC_CMD(0x2005, LipsyncCmdSetDebugprint)

#define LIPSYNC_CMD_PRINT_MODULE_STATE	ADEC_CMD_SIMP(0x2020)

typedef struct _LipsyncCmdSetOnoff{
	// 0 : off ,  1 : on
	unsigned int onoff;
}LipsyncCmdSetOnoff;

typedef struct _LipsyncCmdSetBound{
	unsigned int lbound;
	unsigned int ubound;
	unsigned int offset;
	unsigned int freerunlbound;
	unsigned int freerunubound;
}LipsyncCmdSetBound;

typedef struct _LipsyncCmdSetclocktype{
	// 0x01 : pcrM,  0x02 : pcrA, 0x11 : None pcr, 0x100 : gstc 	
	unsigned int clocktype;
}LipsyncCmdSetclocktype;

typedef struct _LipsyncCmdSetBase{
	unsigned int clockbase;
	unsigned int streambase; 
}LipsyncCmdSetBase;


typedef struct _LipsyncCmdSetFs{
	unsigned int Fs;
}LipsyncCmdSetFs;

typedef struct _LipsyncCmdSetDebugprint{
	unsigned int interval;		// ms, 0 is off,   
}LipsyncCmdSetDebugprint;


#endif
