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

const PE_REG_PARAM_T ipc_l_sd_480_default_h13b0[] = 
{
	/* ipc, 0x0500~0x055C, 0x05F0~0x063C, */
	{0x0500, 0xFA70ACAA},
	{0x0608, 0x0A081019},
	{0x0504, 0x00870000},
	{0x060C, 0xE818E818},
	{0x0510, 0x18002800},	// et_offset[7:0]:0x1->0x0
	{0x0514, 0x032B0B00},
	{0x0518, 0x00880777},
	{0x051C, 0x0EE002DF},
	{0x0618, 0x6180C318},
	{0x054C, 0x007C6850},
	{0x05F8, 0xFFC02018},
	{0x0548, 0xFF10FF08},
	{0x05FC, 0x8093FF29},
	{0x0604, 0x11161010},
	{0x0600, 0x507B0130},
	{0x0614, 0x80304018},
	{0x0610, 0x0900FF0D},
	{0x0534, 0x30001003},
	{0x05A4, 0x02122003},	// vflt_y
	{0x05F0, 0x41919818},
	{0x05F4, 0xCC409959},
	{0x0508, 0x18287010},
	{0x050C, 0xF5505038},
	{0x0544, 0x10505CE1},
	{0x0550, 0x0A030A8C},
	{0x0554, 0x0949041B},
	{0x0558, 0x050E0491},
	{0x055C, 0x001C0172},
	{0x0630, 0x0057006E},
	{0x062C, 0x1EAD0146},
	{0x061C, 0x00000503},
	{0x0520, 0x04400320},
	{0x0634, 0x005E0060},
	/* FMD Tuning */
	{0x0524, 0x00FF2850},
	{0x0528, 0x20280420},
	{0x052C, 0x1A0005B0},
	{0x0530, 0xFF2A2003},
	{0x0538, 0xFF506025},
	{0x053C, 0xE8580040},
	{0x0540, 0x532820A0}
};