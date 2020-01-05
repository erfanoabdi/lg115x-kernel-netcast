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
#ifndef __MODULE_EVT_SPDIF_H__
#define __MODULE_EVT_SPDIF_H__

#include "common/adec_media_type.h"
#include "imc/adec_imc_evt.h"


#define SPDIF_EVT_GET_FMT_FOR_SOUNDBAR		0x0011


typedef struct _SpdifEvtGetFmtForSoundbar
{
	unsigned int		id;					//24bit		
	unsigned int		data;				//16bit
	unsigned int		reserved;			//24bit
	unsigned int		checksum;			//8bit
}SpdifEvtGetFmtForSoundbar;


#endif //__MODULE_EVT_SPDIF_H__

