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

#ifndef __MODULE_CMD_SRC_H__
#define __MODULE_CMD_SRC_H__

#include "imc/adec_imc_cmd.h"

#define SRC_CMD_SET_FMT			ADEC_CMD(0x2000, SrcCmdSetFmt)
#define SRC_CMD_SET_OVERPROTECT	ADEC_CMD(0x2001, SrcCmdSetOverProtect)
#define SRC_CMD_SET_ALLFMT		ADEC_CMD(0x2002, SrcCmdSetAllfmt)
#define SRC_CMD_CHANGE_FS		ADEC_CMD(0x2003, SrcCmdChangeFs)
#define SRC_CMD_SET_GAIN		ADEC_CMD(0x2004, SrcCmdSetGain)
#define SRC_CMD_SET_OUT_FS      ADEC_CMD(0x2005, SrcCmdSetOutFs)

#define SRC_CMD_PRINT_MODULE_STATE	ADEC_CMD_SIMP(0x2020)



typedef struct _SrcCmdSetFmt
{
	unsigned int InFs;		// kHz : 8000 16000 24000 32000 44100 48000 96000 etc ... 
	unsigned int OutFs;		// kHz 
	unsigned int InCh;		// channel :
	unsigned int OutCh;		// channel :
	unsigned int InFormat; // pcm format : 8 16 24 32 
	unsigned int OutFormat; // pcm format : 8 16 24 32 
}SrcCmdSetFmt;



typedef struct _SrcCmdSetAllfmt
{
	unsigned int InFs;		// kHz : 8000 16000 24000 32000 44100 48000 96000 etc ... 
	unsigned int InCh;		// channel : mono stereo & multi (Max 8ch)
	unsigned int InFormat; // pcm format : 8 16 24 32
	unsigned int InEndian;  // 0 is little , 1 is big
    unsigned int InSigned ; // 0 is signed , 1 is unsigned 

	unsigned int OutFs;		// kHz 
	unsigned int OutCh;		// channel : mono stereo 
	unsigned int OutFormat; // pcm format : 8 16 24 32 
}SrcCmdSetAllfmt;


typedef struct _SrcCmdSetOverProtect
{
	// 0 - No Overflow Protection     (default)
	// 1 - Enable Overflow Protection (to capture)
	unsigned int over_protect;
}SrcCmdSetOverProtect;



typedef struct _SrcCmdSetOutSample
{
	unsigned int Samples;		// per 1ch 
}SrcCmdSetOutSample;




typedef struct _SrcCmdChangeFs
{
	unsigned int InFs;
	unsigned int OutFs;
}SrcCmdChangeFs;

typedef struct _SrcCmdSetOutFs
{
    unsigned int OutFs;
}SrcCmdSetOutFs;


typedef struct _SrcCmdSetGain
{
	int Gain;              
    int GainEnable; 
}SrcCmdSetGain;



typedef struct _SrcCmdSetOutFreq
{
    unsigned int out_freq;
}SrcCmdSetOutFreq;

#endif
