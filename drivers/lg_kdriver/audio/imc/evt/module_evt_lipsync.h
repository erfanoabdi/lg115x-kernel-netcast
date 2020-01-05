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




/******************************************************************************
  Header File Guarder 
 ******************************************************************************/
#ifndef __MODULE_EVT_LIPSYNC_H__
#define __MODULE_EVT_LIPSYNC_H__

#include "common/adec_media_type.h"
#include "imc/adec_imc_evt.h"


#define LIPSYNC_EVT_NOPCR_BASELINE			0x0B01
#define LIPSYNC_EVT_PRESENT_END             0x0B02
#define LIPSYNC_EVT_UNDERFLOW				0x0B03


typedef struct _LipsyncEvtNopcrBaseline
{
	unsigned int		baseST;			// steam time			
	unsigned int		baseCT;			// clock time
}LipsyncEvtNopcrBaseline;



typedef struct _LipsyncEvtPresentEnd
{
	unsigned int		remain_ms;						
}LipsyncEvtPresentEnd;

typedef struct _LipsyncEvtUnderflow
{
	unsigned int		tmp;						
}LipsyncEvtUnderflow;


#endif //__MODULE_EVT_SPDIF_H__

