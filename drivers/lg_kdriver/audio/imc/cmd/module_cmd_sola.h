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

#ifndef __MODULE_CMD_SOLA_H__
#define __MODULE_CMD_SOLA_H__

#include "imc/adec_imc_cmd.h"

#define SOLA_CMD_SET_RATE			ADEC_CMD(0x2000, SolaCmdSetRate)

#define SOLA_CMD_PRINT_MODULE_STATE	ADEC_CMD_SIMP(0x2020)



typedef struct _SolaCmdSetRate
{
	unsigned int InSample; 
	unsigned int OutSample;	 
}SolaCmdSetRate;


#endif