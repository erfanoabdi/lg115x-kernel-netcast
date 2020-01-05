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

const PE_REG_PARAM_T tnr_l_sd_mc_off_default_h13b0[] = 
{
	/* tnr 0x0440~0x04FC, 0x06D0~0x06F8*/
	{0x0468, 0x4080A000},
	{0x0440, 0x69FD4003},
	{0x0474, 0x80018000},
	{0x0488, 0x20204133},
	{0x0448, 0x05904010},
	{0x0444, 0x020DF410},	//tnr_filter_lsb_ctrl[21:20]:0x3->0x0
	{0x04F8, 0x850443FA},	//mv_pfilter_en[25]:0x0
	{0x06D8, 0x18101003},
	{0x06F8, 0x10200880},
	{0x06DC, 0xFE302820},
	{0x06EC, 0x00440101},
	{0x06E0, 0x20C00C00},
	{0x06E8, 0xF000D0FF},
	{0x06D0, 0x8418480D},
	{0x06F4, 0x18390984},
	{0x0464, 0x0250308B},
	{0x04CC, 0x0F020633},
	{0x04C8, 0x4B6201C4},
	{0x04DC, 0x00140021},
	{0x0494, 0x40FF2080},
	{0x0498, 0x400C100C},
	{0x04E8, 0x73E820E8},
	{0x06F0, 0x10E008A0},
	{0x04FC, 0x28602860},	//[16],[0]mc_flt_en_y,c off
	{0x0484, 0x18FF0840},
	{0x04EC, 0xA0FF90FF},
	{0x049C, 0x40403020},
	{0x04A0, 0x80806060},
	{0x04A4, 0x40403020},
	{0x04A8, 0x80806060},
	{0x06D4, 0x00900000},
	{0x048C, 0xC0804020},
	{0x0490, 0x20202020},
	{0x04AC, 0x20203040},
	{0x0454, 0x035A0201},
	{0x0460, 0x3F3F281E},
	{0x044C, 0x20182020},
	{0x04B4, 0xFFF00C20},
	{0x04E0, 0x00101010},
	{0x04E4, 0x00E87AE8},
	{0x046C, 0x30F02080},
	{0x0458, 0xF4181030},
	{0x0450, 0x148008C0},
	{0x0470, 0x80403860},
	{0x04B0, 0x608018E0},
	{0x04B8, 0x90206860},
	{0x045C, 0x140E0800},
	//{0x0478, 0x00000168},		//tnr measure win, set in drv
	//{0x047C, 0x01E002D0},		//tnr measure win, set in drv
	{0x04C4, 0x00001869},
	{0x04C0, 0x36070302},
	{0x0480, 0x32100000}
};
