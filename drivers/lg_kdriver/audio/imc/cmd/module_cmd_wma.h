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


#ifndef __MODULE_CMD_WMA_H__
#define __MODULE_CMD_WMA_H__

#include "imc/adec_imc_cmd.h"

#define WMA_CMD_SET_PARAM		ADEC_CMD(0x2000, WmaCmdSetParam)

#define WMA_CMD_DEBUG_STATUS	ADEC_CMD_SIMP(0x2020)


typedef struct _WmaCmdSetParam
{
    unsigned int val_samp_freq;
    unsigned int val_num_chan;
    unsigned int val_pcm_wd_sz;
    unsigned int val_w_fmt_tag;
    unsigned int val_blk_align;
    unsigned int val_encode_opt;
    unsigned int val_avg_bitrate;
    unsigned int val_ch_mask;
    unsigned int val_adv_encode_opt;
    unsigned int adv_encode_opt2;
} WmaCmdSetParam;

#endif // #ifndef __MODULE_CMD_WMA_H__

