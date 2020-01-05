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

const PE_REG_PARAM_T shp_l_rf_pal_default_h13b0[] =
{
	/* scaler : min-max clipping(V)*/
	{0x1180, 0x00000281},
	/* cva cti */
	{0x0184, 0x30000030},
	/* p0l cti */
	{0x0584, 0x00451810},
	{0x05E4, 0x00282005},
	/* pe1 shp, 0x53D0~0x54CC,0x54F0~0x5550,0x5560~0x559C */
	{0x53D0, 0x07030109},
	{0x53D4, 0x00004100},
	{0x53D8, 0x0801F808},
	{0x53DC, 0xC80C0000},
	{0x53E0, 0x0000FF01},
	{0x53E4, 0x1E100401},
	{0x53E8, 0x85060600},
	{0x53EC, 0x3F000000},
	{0x53F0, 0x30FF1010},
	{0x53F4, 0x00004020},
	{0x53F8, 0x17114428},
	{0x53FC, 0x17114428},
	{0x5400, 0x0006300A},
	{0x5404, 0x00000018},
	{0x5408, 0x44280000},
	{0x540C, 0x00002020},
	{0x5410, 0x00000000},
	{0x5414, 0x2A2A2323},
	{0x5418, 0x00000000},
	{0x541C, 0x00000000},
	{0x5420, 0x10DE14CA},
	{0x5424, 0x00002195},
	{0x5428, 0x00000000},
	{0x542C, 0x00000000},
	{0x5430, 0x00013EE2},
	{0x5434, 0x00013FC5},
	{0x5438, 0x000141A1},
	{0x543C, 0x00014251},
	{0x5440, 0x00014149},
	{0x5444, 0x17114428},
	{0x5448, 0x1DC745BF},
	{0x544C, 0x17114428},
	{0x5450, 0x17114428},
	{0x5454, 0x17114428},
	{0x5458, 0x00013FE4},
	{0x545C, 0x17114428},
	{0x5460, 0x00013FCB},
	{0x5464, 0x00013F1B},
	{0x5468, 0x00013F24},
	{0x546C, 0x00014070},
	{0x5470, 0x06101000},
	{0x5474, 0x17114428},
	{0x5478, 0x00003F20},
	{0x547C, 0x00000000},
	{0x5480, 0x17114428},
	{0x5484, 0x17114428},
	{0x5488, 0x00013E55},
	{0x548C, 0x00013F77},
	{0x5490, 0x00000001},
	{0x5494, 0x08332A2A},
	{0x5498, 0x20012024},
	{0x549C, 0x00000000},
	{0x54A0, 0x01401000},
	{0x54A4, 0x17114428},
	{0x54A8, 0x00000000},
	{0x54AC, 0x00001010},
	{0x54B0, 0x000C0C01},
	{0x54B4, 0x00C81919},
	{0x54B8, 0xD8D06040},
	{0x54BC, 0x3800FFFF},
	{0x54C0, 0xFFD8D048},
	{0x54C4, 0x000000FF},
	{0x54C8, 0x17114428},
	{0x54CC, 0x17114428},
	{0x54D0, 0x00000000},
	{0x54D4, 0x00000000},
	{0x54D8, 0x00000000},
	{0x54DC, 0x00000000},
	{0x54E0, 0x00000000},
	{0x54E4, 0x00000000},
	{0x54E8, 0x00000000},
	{0x54EC, 0x00000000},
	{0x54F0, 0x00000001},
	{0x54F4, 0x08332323},
	{0x54F8, 0x20016024},
	{0x54FC, 0x00000000},
	{0x5500, 0x01401000},
	{0x5504, 0x17114428},
	{0x5508, 0x00000000},
	{0x550C, 0x00001042},
	{0x5510, 0x000C0C01},
	{0x5514, 0x00B01919},
	{0x5518, 0xD8D06040},
	{0x551C, 0x3800FFFF},
	{0x5520, 0xFFD8D049},
	{0x5524, 0x000000FF},
	{0x5528, 0x17114428},
	{0x552C, 0x17114428},
	{0x5530, 0x8020D001},
	{0x5534, 0x00000007},
	{0x5538, 0x00FF0852},
	{0x553C, 0x00014196},
	{0x5540, 0x00013ED9},
	{0x5544, 0x00013FD5},
	{0x5548, 0x17114428},
	{0x554C, 0x17114428},
	{0x5550, 0x00000001},
	{0x5560, 0x04301030},
	{0x5564, 0x78380A05},
	{0x5568, 0x00040C01},
	{0x556C, 0x00040C01},
	{0x5570, 0x00210703},
	{0x5574, 0x01280820},
	{0x5578, 0x10081810},
	{0x557C, 0x40403B2A},
	{0x5580, 0x0000003F},
	{0x5584, 0x4545233E},
	{0x5588, 0x17114428},
	{0x558C, 0x17114428},
	{0x5590, 0xB0000165},
	{0x5594, 0x00801000},
	{0x5598, 0x0000100B},
	{0x559C, 0x100B100B}
};

