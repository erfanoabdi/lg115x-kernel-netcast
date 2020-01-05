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

#ifndef __MODULE_CMD_SE_H__
#define __MODULE_CMD_SE_H__

#include "imc/adec_imc_cmd.h"

#define SE_CMD_SET_MODE		ADEC_CMD(0x2000, SeCmdSetMode)
#define SE_CMD_SET_PARAM	ADEC_CMD(0x2001, SeCmdSetParam)
#define SE_CMD_SET_BYPASS	ADEC_CMD(0x2002, SeCmdSetBypass)
#define SE_CMD_SET_OUTCH	ADEC_CMD(0x2003, SeCmdSetOutCh)

#define SE_CMD_PRINT_MODULE_STATE	ADEC_CMD_SIMP(0x2020)
#define SE_CMD_PRINT_PARAM	ADEC_CMD(0x2021,SeCmdSetParam)


typedef struct _SeCmdSetMode{
	unsigned int Mode;
	unsigned int DeqMode;
	unsigned int PeqMode;
}SeCmdSetMode;


typedef struct _SeCmdSetParam{
	unsigned int FnMode;			// fn number
	unsigned int DataOption;		// 0 : init_only, 1 : variables, 2 : all
//	unsigned int VarOption;		//not used	
//	unsigned int AccessMode;	//not used
//	unsigned int NoParam;		//not used
}SeCmdSetParam;


typedef struct _SeCmdSetBypass{
	unsigned int bypass;			// 1 is Bypass
}SeCmdSetBypass;

typedef struct _SeCmdSetOutCh{
	unsigned int ch;			// 2 or 4 channel 
}SeCmdSetOutCh;


#endif
