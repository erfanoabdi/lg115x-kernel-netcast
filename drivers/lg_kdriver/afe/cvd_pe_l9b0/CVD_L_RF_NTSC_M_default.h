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

static const CVD_REG_PARAM_T cvd_rf_ntsc_m_l_default[] = 
{
	{0x4250, 0x00000000},	{0x42B4, 0x00000200},	{0x42B8, 0x00020010},	{0x42C4, 0x00017110},
	{0x42EC, 0x00016FC1},	{0x439C, 0x0011038A},	{0x43A0, 0x01031F8F},	{0x43A4, 0x1FD00010},
	{0x43A8, 0x00000003},	{0x43AC, 0x00010380},	{0x43B0, 0x00EE1FA9},	{0x43B4, 0x1FE60003},
	{0x43B8, 0x00000000},	{0x43BC, 0x00010100},	{0x43D8, 0x00030000},	{0x43DC, 0x00000004},
	{0x43E0, 0x00001000},	{0x43E4, 0x00600203},	{0x43E8, 0x00001050},	{0x4410, 0x00000000},
	{0x4414, 0x00000012},	{0x4418, 0x00001110},	{0x441C, 0x0001FFD4},	{0x4420, 0xFFED01F8},
	{0x4424, 0x07911039},	{0x4428, 0x18821BF6},	{0x4544, 0x3120030C},	{0x4548, 0x00080131},
	{0x454C, 0x00200100},	{0x4550, 0x00080010},	{0x4554, 0x00200000},	{0x4558, 0x03040508},
	{0x455C, 0x00000000},	{0x4560, 0x00000000},	{0x4568, 0x00000001},	{0x456C, 0x00100010},
	{0x4570, 0x00004C00},	{0x4574, 0x12180F00},	{0x4578, 0x00301C28},	{0x457C, 0x30200000},
	{0x4580, 0x8002A300},	{0x4584, 0x20301820},	{0x4588, 0x00000000},	{0x4590, 0x0C002480},
	{0x4594, 0x48FF99FF},	{0x4598, 0x060028FF},	{0x459C, 0x00000004},	{0x45A0, 0x00000000},
	{0x45A4, 0x00000000},	{0x45A8, 0x00000000},	{0x45AC, 0x00000000},	{0x45B0, 0x0000000F},
	{0x45B4, 0x00000000},	{0x45B8, 0x3838100B},	{0x45BC, 0x08002021},	{0x45C0, 0x00000021},
	{0x45C4, 0x08002000},	{0x45C8, 0x00001038},	{0x45D8, 0x0000FFFF},	{0x45DC, 0x80808000},
	{0x45E0, 0x0000FFFF},	{0x45E4, 0x80808000},	{0x45E8, 0x00000008},	{0x45EC, 0x08002080},
	{0x45F0, 0x40c060FF},	{0x45F4, 0x002000F3},	{0x45F8, 0xA0FF0800},	{0x45FC, 0x01000000},
	{0x4600, 0x00000000},	{0x4604, 0x00000000},	{0x4608, 0x002D002C},	{0x460C, 0x007FF00C},
	{0x4610, 0x007C0135},	{0x4614, 0x001357C0},	{0x4618, 0x0000C7FF},	{0x4620, 0x00000647},
	{0x4624, 0x00000a40},	{0x4634, 0x002C002B},	{0x4638, 0x00290027},	{0x4640, 0x9700FF00},
	{0x4650, 0x02700000},	{0x4654, 0x00000000},	{0x4678, 0x00000000},	{0x469C, 0x00000000},
	{0x46A0, 0x00000000},	{0x46A4, 0x00000000},	{0x46A8, 0x00000000},	{0x46AC, 0x00000000}
};
//120202 : by min.kim (y/c delay)
// 0x4620 : 0x687 => 0x647, 0x4624 : 0xa80 => 0xa40
