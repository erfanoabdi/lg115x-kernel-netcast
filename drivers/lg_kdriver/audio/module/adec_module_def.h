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
 *	@file adec_module_def.h
 *
 *
 *	@author		Jung, Kyung Soon (kyungsoon.jung@leg.com)
 *	@version	0.0.1
 *	@date		2012-03-19
 *	@note
 *	@see		http://www.lge.com
 *	@addtogroup ADEC_COMMON
 *	@{
 */


/******************************************************************************
  Header File Guarder
 ******************************************************************************/
// This file should not use header guard
//#ifndef __ADEC_MODULE_DEF_H__
//#define __ADEC_MODULE_DEF_H__


/*-----------------------------------------------------------------------------
 * Should Define ADEC_MODULE_DEF(__MODULE_ID, \
 * 								 __MODULE_NAME, \
 * 								 __MODULE_TYPE,\
 * 								 __LOCATION, \
 * 								 __NUM_IN, \
 * 								 __NUM_OUT,\
 * 								 ...)
 *
 * Should Define __BUF_END
 -----------------------------------------------------------------------------*/
#ifndef ADEC_MODULE_DEF
#define ADEC_MODULE_DEF(...)
#endif
#ifndef __BUF_END
#define __BUF_END(...) ADEC_BUF_NOT_DEF
#endif
//             +--------------------------------------------------------------------------------------------------------
//             | Manager Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_MAN_ARM,	"ARM MAN",	ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_ARM,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_MAN_DSP0,	"DSP0_MAN",	ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_DSP0,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_MAN_DSP1,	"DSP1_MAN",	ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_DSP1,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_DBG_DSP0,	"DSP0_DBG", ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_DSP0,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_DBG_DSP1,	"DSP1_DBG", ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_DSP1,	0, 0, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | Source Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_TP_IN_0,	"TP_IN_0",	ADEC_MOD_TYPE_SOURCE,	ADEC_CORE_DSP0,	0, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_TP_IN_1,	"TP_IN_1",	ADEC_MOD_TYPE_SOURCE,	ADEC_CORE_DSP0,	0, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SIF_IN,		"SIF_IN",	ADEC_MOD_TYPE_SOURCE,	ADEC_CORE_DSP0,	0, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_HDMI_IN,	"HDMI_IN",	ADEC_MOD_TYPE_SOURCE,	ADEC_CORE_DSP0,	0, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_ADC_IN,		"ADC_IN",	ADEC_MOD_TYPE_SOURCE,	ADEC_CORE_DSP0,	0, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | Codec Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_DEC_0,		"DEC_0",	ADEC_MOD_TYPE_DECODER,	ADEC_CORE_DSP0,	1, 2, ADEC_BUF_MULTI_SINK, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_DEC_1,		"DEC_1",	ADEC_MOD_TYPE_DECODER,	ADEC_CORE_DSP0,	1, 2, ADEC_BUF_MULTI_SINK, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_ENC_0,		"ENC_0",	ADEC_MOD_TYPE_ENCODOER,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_ENC_1,		"ENC_1",	ADEC_MOD_TYPE_ENCODOER,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_INTRA, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | SRC(Sample Rate conversion) Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//for dsp0
ADEC_MODULE_DEF(ADEC_MODULE_SRC_D0,		"SRC_D0",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_D1,		"SRC_D1",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_D2,		"SRC_D2",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_D3,		"SRC_D3",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_DEC,	"SRC_DEC",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

//for dsp1
ADEC_MODULE_DEF(ADEC_MODULE_SRC_0,		"SRC_0",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_1,		"SRC_1",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_2,		"SRC_2",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_3,		"SRC_3",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_4,		"SRC_4",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_5,		"SRC_5",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_6,		"SRC_6",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_7,		"SRC_7",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_8,		"SRC_8",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SRC_9,		"SRC_9",	ADEC_MOD_TYPE_SRC,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())


//             +--------------------------------------------------------------------------------------------------------
//             | Lip Sync Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_LIP_0,		"LIP_0",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_1,		"LIP_1",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_2,		"LIP_2",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_3,		"LIP_3",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_4,		"LIP_4",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_5,		"LIP_5",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_6,		"LIP_6",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_7,		"LIP_7",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_8,		"LIP_8",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_9,		"LIP_9",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_ES0,	"LIP_ES0",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_LIP_ES1,	"LIP_ES1",	ADEC_MOD_TYPE_LIPSYNC,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | Mixer Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_MIX_0,		"MIX_0",	ADEC_MOD_TYPE_MIXER,	ADEC_CORE_DSP1,	10, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_MIX_1,		"MIX_1",	ADEC_MOD_TYPE_MIXER,	ADEC_CORE_DSP1,	10, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_MIX_2,		"MIX_2",	ADEC_MOD_TYPE_MIXER,	ADEC_CORE_DSP1,	10, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_MIX_3,		"MIX_3",	ADEC_MOD_TYPE_MIXER,	ADEC_CORE_DSP1,	10, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_MIX_4,		"MIX_4",	ADEC_MOD_TYPE_MIXER,	ADEC_CORE_DSP1,	10, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | SE(Sound Engine) Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_SE,			"SE",		ADEC_MOD_TYPE_SE,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | Output Ctrl Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_OUT_CTRL_0,	"OUT_SPK",	ADEC_MOD_TYPE_OUTCTRL,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_OUT_CTRL_1,	"OUT_HP",	ADEC_MOD_TYPE_OUTCTRL,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_OUT_CTRL_2,	"OUT_SCART",ADEC_MOD_TYPE_OUTCTRL,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_OUT_CTRL_3,	"OUT_SPDIF",ADEC_MOD_TYPE_OUTCTRL,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_INTRA, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_ESOUT_CTRL, "OUT_ES",   ADEC_MOD_TYPE_ESOUTCTRL,ADEC_CORE_DSP1,	1, 1, ADEC_BUF_INTRA, __BUF_END())

//             +--------------------------------------------------------------------------------------------------------
//             | Sink Module Definition
//             +------------------------+-----------+-----------------------+---------------+---------------------------
//             | ID						| NAME		| TYPE					| LOCATION		| BUFFERS
//             +------------------------+-----------+-----------------------+---------------+---------------------------
ADEC_MODULE_DEF(ADEC_MODULE_OUT_PCM,	"PCM",		ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP1,	3, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_OUT_SPDIF,	"SPDIF",	ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP1,	1, 0, __BUF_END())
// For test. DSP0 PCM out.
ADEC_MODULE_DEF(ADEC_MODULE_OUT_PCM_0,	"PCM_0",	ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP0,	3, 0, __BUF_END())
// For test. DSP0 SPDIF out.
ADEC_MODULE_DEF(ADEC_MODULE_OUT_SPDIF_0,"SPDIF_0",	ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP0,	1, 0, __BUF_END())

// For dump. buffer in DSP
ADEC_MODULE_DEF(ADEC_MODULE_DUMP_DSP0,"DUMP_DSP0",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_DUMP_DSP1,"DUMP_DSP1",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_BYPASS_00,"BYPASS_00",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_BYPASS_01,"BYPASS_01",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_BYPASS_02,"BYPASS_02",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_BYPASS_ES,"BYPASS_ES",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP0,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_BYPASS_10,"BYPASS_10",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_BYPASS_11,"BYPASS_11",	ADEC_MOD_TYPE_BYPASS,	ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_IMC_DSP0,	"IMC_DSP0",	ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_DSP0,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_IMC_DSP1,	"IMC_DSP1",	ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_DSP1,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_IMC_ARM,	"IMC_ARM",	ADEC_MOD_TYPE_MANAGER,	ADEC_CORE_ARM,	0, 0, __BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_OUT_PCMSUB,	"PCMSUB",	ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP1,	1, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_DTO_A,      "DTO_A",	ADEC_MOD_TYPE_SINK,     ADEC_CORE_DSP1,	0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_DTO_D,      "DTO_D",    ADEC_MOD_TYPE_SINK,     ADEC_CORE_DSP1,	0, 0, __BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_RTS,        "RTS",      ADEC_MOD_TYPE_MANAGER,  ADEC_CORE_DSP1, 0, 0, __BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_HWSRC_DSP0,"HWSRC_DSP0",ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP0,	1, 1, ADEC_BUF_INTRA,__BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_HWSRC_DSP1,"HWSRC_DSP1",ADEC_MOD_TYPE_SINK,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_INTRA,__BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_SOLA_0,		"SOLA_0",	ADEC_MOD_TYPE_SOLA,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_SOLA_1,		"SOLA_1",	ADEC_MOD_TYPE_SOLA,		ADEC_CORE_DSP1,	1, 1, ADEC_BUF_MULTI_SINK, __BUF_END())

ADEC_MODULE_DEF(ADEC_MODULE_CTRLSRC_0,  "CTRLSRC_0",ADEC_MOD_TYPE_CTRLSRC,  ADEC_CORE_DSP1, 0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_CTRLSRC_1,  "CTRLSRC_1",ADEC_MOD_TYPE_CTRLSRC,  ADEC_CORE_DSP1, 0, 0, __BUF_END())
ADEC_MODULE_DEF(ADEC_MODULE_CTRLSRC_2,  "CTRLSRC_2",ADEC_MOD_TYPE_CTRLSRC,  ADEC_CORE_DSP1, 0, 0, __BUF_END())

//#endif //__ADEC_MODULE_DEF_H__
/** @} */

