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
#ifndef __MODULE_EVT_DTO_H__
#define __MODULE_EVT_DTO_H__

#include "common/adec_media_type.h"
#include "imc/adec_imc_evt.h"


#define DTO_EVT_CHANGE_DTO_RATE           0x0C00


typedef struct _DtoEvtChangeDtoRate
{
   unsigned int         dto_rate;
}DtoEvtChangeDtoRate;

#endif //__MODULE_EVT_DTO_H__

