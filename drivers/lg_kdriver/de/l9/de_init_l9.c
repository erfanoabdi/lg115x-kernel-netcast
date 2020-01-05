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


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2011.06.01
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"

#include "de_kapi.h"
#include "de_hal.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define VIDEO_REG_Write DE_HAL_WriteReg
#define VIDEO_REG_WB    DE_REG_WB

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
UINT32 DE_REG_WB(UINT32 addr, char *pData, char *pField);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
int VIDEO_InitRegister(void)
{
	//Script pql_run.scr Begin
	//Script pql_run.scr => pql/L9A0_StaticUI_Set_csc_110520.txt Begin
	//- Input CSC
	//- icsc_709_limited
	VIDEO_REG_Write(0xc0020124, 0x09d300fe);
	VIDEO_REG_Write(0xc0020128, 0x02ee7a98);
	VIDEO_REG_Write(0xc002012c, 0x07067e62);
	VIDEO_REG_Write(0xc0020130, 0x799e7f5c);
	VIDEO_REG_Write(0xc0020134, 0x07060000);
	VIDEO_REG_Write(0xc0020138, 0x00000000);
	VIDEO_REG_Write(0xc002013c, 0x00400200);
	VIDEO_REG_Write(0xc0020140, 0x02000002);
	VIDEO_REG_Write(0xc0020140, 0x02000003); //-Coefficient Load

	//- PCC
	//- Bypass
	VIDEO_REG_Write(0xc00215e4, 0x00000000);
	VIDEO_REG_Write(0xc00215e8, 0x00001000);
	VIDEO_REG_Write(0xc00215ec, 0x00000000);
	VIDEO_REG_Write(0xc00215f0, 0x00001000);

	//- Output CSC
	//- Output csc, Brightness, Saturation
	//- ocsc_709_extend
	//- Brightness : 50
	//- Saturation : 70
	VIDEO_REG_Write(0xc00215c4, 0x12a07b3c);
	VIDEO_REG_Write(0xc00215c8, 0x740b12a0);
	VIDEO_REG_Write(0xc00215cc, 0x2f600000);
	VIDEO_REG_Write(0xc00215d0, 0x12a00000);
	VIDEO_REG_Write(0xc00215d4, 0x282a07bc);
	VIDEO_REG_Write(0xc00215d8, 0x06000600);
	VIDEO_REG_Write(0xc00215dc, 0x00000000);
	VIDEO_REG_Write(0xc00215e0, 0x00001000);
	VIDEO_REG_Write(0xc00215c0, 0x00000005);
	//- 5:pcc,oCSC enable, 4:pcc enable, 1:oCSC enable, 0:pcc,oCSC disable

	//- Contrast, Hue
	//- Contrast : 100
	//- Hue : 50
	#if 0	// 20110625 justine.jeong    control by DE_REG_L9_VSPMute
	VIDEO_REG_Write(0xc00215b0, 0x80800001);
	#endif
	VIDEO_REG_Write(0xc002160c, 0x0080807f);

	//- WB
	//- WB Gain
	//- R:118  G:120  B:192
	//- WB Offset
	//- R:128  G:128  B:128
	VIDEO_REG_Write(0xc00216c8, 0x0076c078);
	VIDEO_REG_Write(0xc00216cc, 0x00808080);
	VIDEO_REG_Write(0xc00216c0, 0x00000000);
	//END
	//Script pql_run.scr => pql/L9A0_StaticUI_Set_csc_110520.txt End

	//Script pql_run.scr => pql/IPC_TuningL101015.txt Begin
	// RomFile Extracted from D
	VIDEO_REG_Write(0x051c, 0x1601ff81);
	VIDEO_REG_Write(0x0500, 0xf1046faa);
	VIDEO_REG_Write(0x0504, 0x80002404);
	VIDEO_REG_Write(0x0544, 0xa03080e0);
	VIDEO_REG_Write(0x0520, 0x24080000);
	VIDEO_REG_Write(0x0508, 0x18287008);
	VIDEO_REG_Write(0x050c, 0xf5505038);
	VIDEO_REG_Write(0x05f0, 0x400080f5);
	VIDEO_REG_Write(0x05f4, 0x18398000);
	VIDEO_REG_Write(0x05f8, 0x13300173);
	VIDEO_REG_Write(0x05fc, 0x1009a0bf);
	VIDEO_REG_Write(0x060c, 0x30301011);
	VIDEO_REG_Write(0x0608, 0x08081010);
	VIDEO_REG_Write(0x0604, 0x10400000);
	VIDEO_REG_Write(0x0600, 0x10000801);
	VIDEO_REG_Write(0x0610, 0x04186003);
	VIDEO_REG_Write(0x0524, 0x14142a06);
	VIDEO_REG_Write(0x0518, 0x351e0f2d);
	VIDEO_REG_Write(0x0514, 0x01013005);
	VIDEO_REG_Write(0x0510, 0x54400000);
	VIDEO_REG_Write(0x0548, 0x84400000);
	VIDEO_REG_Write(0x0580, 0x3eff3000);
	// End
	//Script pql_run.scr => pql/IPC_TuningL101015.txt End

	//Script pql_run.scr => pql/IPC_TuningL101015_R.txt Begin
	// RomFile Extracted from D
	VIDEO_REG_Write(0x251c, 0x1601ff81);
	VIDEO_REG_Write(0x2500, 0xf1046faa);
	VIDEO_REG_Write(0x2504, 0x80002404);
	VIDEO_REG_Write(0x2544, 0xa03080e0);
	VIDEO_REG_Write(0x2520, 0x24080000);
	VIDEO_REG_Write(0x2508, 0x18287008);
	VIDEO_REG_Write(0x250c, 0xf5505038);
	VIDEO_REG_Write(0x25f0, 0x400080f5);
	VIDEO_REG_Write(0x25f4, 0x18398000);
	VIDEO_REG_Write(0x25f8, 0x13300173);
	VIDEO_REG_Write(0x25fc, 0x1009a0bf);
	VIDEO_REG_Write(0x260c, 0x30301011);
	VIDEO_REG_Write(0x2608, 0x08081010);
	VIDEO_REG_Write(0x2604, 0x10400000);
	VIDEO_REG_Write(0x2600, 0x10000801);
	VIDEO_REG_Write(0x2610, 0x04186003);
	VIDEO_REG_Write(0x2524, 0x14142a06);
	VIDEO_REG_Write(0x2518, 0x351e0f2d);
	VIDEO_REG_Write(0x2514, 0x01013005);
	VIDEO_REG_Write(0x2510, 0x54400000);
	VIDEO_REG_Write(0x2548, 0x84400000);
	VIDEO_REG_Write(0x2580, 0x3eff3000);
	// End
	//Script pql_run.scr => pql/IPC_TuningL101015_R.txt End

	//Script pql_run.scr => pql/tnr_default_HD.txt Begin
	// ---------------------------------
	// tnr core
	// ---------------------------------
	// Off First then On at Last
	VIDEO_REG_Write(0x0440, 0x4d37e203); // [31:24]scene_change_th(30d=>0x1E), [0]:tnr_enable
	// disable to upload tables
	VIDEO_REG_WB(0x0440, "z0", "[0]"); // [0]:tnr_disable
	// ---
	VIDEO_REG_Write(0x0444, 0x083d0060);
	VIDEO_REG_Write(0x0448, 0x400a4025);
	VIDEO_REG_Write(0x044c, 0xff388038);
	VIDEO_REG_Write(0x0450, 0x3824140a);
	VIDEO_REG_Write(0x0454, 0x38280201);
	VIDEO_REG_Write(0x0458, 0x50204014);
	VIDEO_REG_Write(0x045c, 0x1e181109);
	VIDEO_REG_Write(0x0460, 0x80342e28);
	VIDEO_REG_Write(0x0464, 0x00602303);
	VIDEO_REG_Write(0x0468, 0x4000a000); // Show nothing, Ignore Active Window
	VIDEO_REG_Write(0x046c, 0x00404080);
	VIDEO_REG_Write(0x0470, 0x80008000);
	// nt level adjust : 0x80 -> 0x80
	VIDEO_REG_Write(0x0474, 0x80008000);
	VIDEO_REG_Write(0x0478, 0x00000000);
	VIDEO_REG_Write(0x047c, 0x00000000);
	VIDEO_REG_Write(0x0480, 0x60100000); // GM, NT Lvl, PeakT
	VIDEO_REG_Write(0x0484, 0x00000020); // avg_t
	VIDEO_REG_Write(0x0488, 0x20200130);
	VIDEO_REG_Write(0x048c, 0x00000000);
	VIDEO_REG_Write(0x0490, 0x00000000);
	VIDEO_REG_Write(0x0494, 0x20202020);
	VIDEO_REG_Write(0x0498, 0x20202020);
	VIDEO_REG_Write(0x049c, 0x00000000);
	VIDEO_REG_Write(0x04a0, 0x00000000);
	VIDEO_REG_Write(0x04a4, 0x20202020);
	VIDEO_REG_Write(0x04a8, 0x20202020);
	VIDEO_REG_Write(0x04ac, 0x20202020); // [31:24]CRegion_Gain_Out_Rgn1,[23:16]CRegion_Gain_In_Rgn1,[15:8]CRegion_Gain_Out_Rgn0,[7:0]CRegion_Gain_In_Rgn0
	VIDEO_REG_Write(0x04b0, 0x20202020); // [31:24]CRegion_Gain_Out_Rgn3,[23:16]CRegion_Gain_In_Rgn3,[15:8]CRegion_Gain_Out_Rgn2,[7:0]CRegion_Gain_In_Rgn2
	// Wa2
	VIDEO_REG_Write(0x04b4, 0x00702818);
	VIDEO_REG_Write(0x04b8, 0x00008068);
	// -- TNR Alpha-LUT
	VIDEO_REG_Write(0x04d0, 0x00001000); // [12]AI enable [2:0]Indirect Address
	VIDEO_REG_Write(0x04d4, 0xff583220); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x1a090501); // Data LSB (Trigger) Addr=0
	VIDEO_REG_Write(0x04d4, 0xff65412e); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x24110602); // Data LSB (Trigger) Addr=1
	VIDEO_REG_Write(0x04d4, 0xffa15f41); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x31180902); // Data LSB (Trigger) Addr=2
	VIDEO_REG_Write(0x04d4, 0xfffb8658); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x411e0804); // Data LSB (Trigger) Addr=3
	VIDEO_REG_Write(0x04d4, 0xfffb9664); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x4d280c04); // Data LSB (Trigger) Addr=4
	VIDEO_REG_Write(0x04d4, 0xfffcae77); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x59320e05); // Data LSB (Trigger) Addr=5
	VIDEO_REG_Write(0x04d4, 0xfffdc799); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x6f3b1306); // Data LSB (Trigger) Addr=6
	VIDEO_REG_Write(0x04d4, 0x00000000); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x00000000); // Data LSB (Trigger) Addr=7
	VIDEO_REG_Write(0x04d4, 0x807f7c76); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x6f4f4c80); // Data LSB (Trigger) Addr=8
	VIDEO_REG_Write(0x04d4, 0x807d786f); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x61373180); // Data LSB (Trigger) Addr=9
	VIDEO_REG_Write(0x04d4, 0x807d786f); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x5d2e2880); // Data LSB (Trigger) Addr=A
	VIDEO_REG_Write(0x04d4, 0x807d7a6f); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x60292380); // Data LSB (Trigger) Addr=B
	VIDEO_REG_Write(0x04d4, 0x807d776d); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x5c282180); // Data LSB (Trigger) Addr=C
	VIDEO_REG_Write(0x04d4, 0x807d776d); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x5a281f80); // Data LSB (Trigger) Addr=D
	VIDEO_REG_Write(0x04d4, 0x807a776f); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x61281c80); // Data LSB (Trigger) Addr=E
	VIDEO_REG_Write(0x04d4, 0x00000000); // Data MSB
	VIDEO_REG_Write(0x04d8, 0x00000000); // Data LSB (Trigger) Addr=F
	// -- TNR 3D-LUT
	VIDEO_REG_Write(0x04e0, 0x00101010); // [12]AI enable [2:0]Indirect Address
	// small motion (x1.0)
	VIDEO_REG_Write(0x04e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x20000600); // Data LSB (Trigger) Addr=0
	VIDEO_REG_Write(0x04e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x20000600); // Data LSB (Trigger) Addr=1
	VIDEO_REG_Write(0x04e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x20000600); // Data LSB (Trigger) Addr=2
	VIDEO_REG_Write(0x04e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x20000600); // Data LSB (Trigger) Addr=3
	// large motion (x0.675)
	VIDEO_REG_Write(0x04e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x13e806e8); // Data LSB (Trigger) Addr=4
	VIDEO_REG_Write(0x04e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x13e806e8); // Data LSB (Trigger) Addr=5
	VIDEO_REG_Write(0x04e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x13e806e8); // Data LSB (Trigger) Addr=6
	VIDEO_REG_Write(0x04e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x04e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x04ec, 0x13e806e8); // Data LSB (Trigger) Addr=7
	// large motion (x1.0)
	// WR 000004E4 00007A00 # Data MSB
	// WR 000004E8 73002000 # Data Middle
	// WR 000004EC 13000600 # Data LSB (Trigger) Addr=4
	// WR 000004E4 00007A00 # Data MSB
	// WR 000004E8 73002000 # Data Middle
	// WR 000004EC 13000600 # Data LSB (Trigger) Addr=5
	// WR 000004E4 00007A00 # Data MSB
	// WR 000004E8 73002000 # Data Middle
	// WR 000004EC 13000600 # Data LSB (Trigger) Addr=6
	// WR 000004E4 00007A00 # Data MSB
	// WR 000004E8 73002000 # Data Middle
	// WR 000004EC 13000600 # Data LSB (Trigger) Addr=7
	//-- ---------------------------------
	//-- color region
	//-- ---------------------------------
	VIDEO_REG_Write(0x04f0, 0x00001000); //- CR AI Write
	VIDEO_REG_Write(0x04f4, 0x0d50641e); //- CR[0][0] H(149),S(19),Y(30)
	VIDEO_REG_Write(0x04f4, 0x0dc0cc28); //- CR[0][1] H(154),S(39),Y(40)
	VIDEO_REG_Write(0x04f4, 0x0e310046); //- CR[0][2] H(159),S(49),Y(70)
	VIDEO_REG_Write(0x04f4, 0x13819896); //- CR[0][3] H(219),S(79),Y(150)
	VIDEO_REG_Write(0x04f4, 0x0520b019); //- CR[1][0] H(57),S(34),Y(25)
	VIDEO_REG_Write(0x04f4, 0x0550cc28); //- CR[1][1] H(59),S(39),Y(40)
	VIDEO_REG_Write(0x04f4, 0x05c10046); //- CR[1][2] H(64),S(49),Y(70)
	VIDEO_REG_Write(0x04f4, 0x0c01988c); //- CR[1][3] H(134),S(79),Y(140)
	VIDEO_REG_Write(0x04f4, 0x1dc06446); //- CR[2][0] H(334),S(19),Y(70)
	VIDEO_REG_Write(0x04f4, 0x1f10b05a); //- CR[2][1] H(349),S(34),Y(90)
	VIDEO_REG_Write(0x04f4, 0x255198be); //- CR[2][2] H(419),S(79),Y(190)
	VIDEO_REG_Write(0x04f4, 0x2711fcd2); //- CR[2][3] H(439),S(99),Y(210)
	VIDEO_REG_Write(0x04f4, 0x00000000); //- CR[3][0] H(0),S(0),Y(0)
	VIDEO_REG_Write(0x04f4, 0x00100401); //- CR[3][1] H(0),S(0),Y(1)
	VIDEO_REG_Write(0x04f4, 0x1fd0cc19); //- CR[3][2] H(357),S(39),Y(25)
	VIDEO_REG_Write(0x04f4, 0x1fe13028); //- CR[3][3] H(358),S(59),Y(40)
	// CLC
	// WR 0000046C 00000000	# [5:4]CLC CC LineMem Ctrl ("00":No Or-ing, "01","10":OrWithUpperLines)
	// WR 00000460 00000000	# [31]CLC Detector Fake Mode('1':Random-like, '0':Grid Type), [1:0]CLC Detection Enable
	//
	VIDEO_REG_WB(0x0440, "z1", "[0]"); // [0]:tnr_enable
	//
	//END
	//Script pql_run.scr => pql/tnr_default_HD.txt End

	//Script pql_run.scr => pql/tnr_default_HD.R.txt Begin
	// ---------------------------------
	// tnr core
	// ---------------------------------
	// Off First then On at Last
	VIDEO_REG_Write(0x2440, 0x4d37e203); // [31:24]scene_change_th(30d=>0x1E), [0]:tnr_enable
	// disable to upload tables
	VIDEO_REG_WB(0x2440, "z0", "[0]"); // [0]:tnr_disable
	// ---
	VIDEO_REG_Write(0x2444, 0x083d0060);
	VIDEO_REG_Write(0x2448, 0x400a4025);
	VIDEO_REG_Write(0x244c, 0xff388038);
	VIDEO_REG_Write(0x2450, 0x3824140a);
	VIDEO_REG_Write(0x2454, 0x38280201);
	VIDEO_REG_Write(0x2458, 0x50204014);
	VIDEO_REG_Write(0x245c, 0x1e181109);
	VIDEO_REG_Write(0x2460, 0x80342e28);
	VIDEO_REG_Write(0x2464, 0x00602303);
	VIDEO_REG_Write(0x2468, 0x4000a000); // Show nothing, Ignore Active Window
	VIDEO_REG_Write(0x246c, 0x00404080);
	VIDEO_REG_Write(0x2470, 0x80008000);
	// nt level adjust : 0x80 -> 0x80
	VIDEO_REG_Write(0x2474, 0x80008000);
	VIDEO_REG_Write(0x2478, 0x00000000);
	VIDEO_REG_Write(0x247c, 0x00000000);
	VIDEO_REG_Write(0x2480, 0x60100000); // GM, NT Lvl, PeakT
	VIDEO_REG_Write(0x2484, 0x00000020); // avg_t
	VIDEO_REG_Write(0x2488, 0x20200130);
	VIDEO_REG_Write(0x248c, 0x00000000);
	VIDEO_REG_Write(0x2490, 0x00000000);
	VIDEO_REG_Write(0x2494, 0x20202020);
	VIDEO_REG_Write(0x2498, 0x20202020);
	VIDEO_REG_Write(0x249c, 0x00000000);
	VIDEO_REG_Write(0x24a0, 0x00000000);
	VIDEO_REG_Write(0x24a4, 0x20202020);
	VIDEO_REG_Write(0x24a8, 0x20202020);
	VIDEO_REG_Write(0x24ac, 0x20202020); // [31:24]CRegion_Gain_Out_Rgn1,[23:16]CRegion_Gain_In_Rgn1,[15:8]CRegion_Gain_Out_Rgn0,[7:0]CRegion_Gain_In_Rgn0
	VIDEO_REG_Write(0x24b0, 0x20202020); // [31:24]CRegion_Gain_Out_Rgn3,[23:16]CRegion_Gain_In_Rgn3,[15:8]CRegion_Gain_Out_Rgn2,[7:0]CRegion_Gain_In_Rgn2
	// Wa2
	VIDEO_REG_Write(0x24b4, 0x00702818);
	VIDEO_REG_Write(0x24b8, 0x00008068);
	// -- TNR Alpha-LUT
	VIDEO_REG_Write(0x24d0, 0x00001000); // [12]AI enable [2:0]Indirect Address
	VIDEO_REG_Write(0x24d4, 0xff583220); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x1a090501); // Data LSB (Trigger) Addr=0
	VIDEO_REG_Write(0x24d4, 0xff65412e); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x24110602); // Data LSB (Trigger) Addr=1
	VIDEO_REG_Write(0x24d4, 0xffa15f41); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x31180902); // Data LSB (Trigger) Addr=2
	VIDEO_REG_Write(0x24d4, 0xfffb8658); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x411e0804); // Data LSB (Trigger) Addr=3
	VIDEO_REG_Write(0x24d4, 0xfffb9664); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x4d280c04); // Data LSB (Trigger) Addr=4
	VIDEO_REG_Write(0x24d4, 0xfffcae77); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x59320e05); // Data LSB (Trigger) Addr=5
	VIDEO_REG_Write(0x24d4, 0xfffdc799); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x6f3b1306); // Data LSB (Trigger) Addr=6
	VIDEO_REG_Write(0x24d4, 0x00000000); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x00000000); // Data LSB (Trigger) Addr=7
	VIDEO_REG_Write(0x24d4, 0x807f7c76); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x6f4f4c80); // Data LSB (Trigger) Addr=8
	VIDEO_REG_Write(0x24d4, 0x807d786f); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x61373180); // Data LSB (Trigger) Addr=9
	VIDEO_REG_Write(0x24d4, 0x807d786f); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x5d2e2880); // Data LSB (Trigger) Addr=A
	VIDEO_REG_Write(0x24d4, 0x807d7a6f); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x60292380); // Data LSB (Trigger) Addr=B
	VIDEO_REG_Write(0x24d4, 0x807d776d); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x5c282180); // Data LSB (Trigger) Addr=C
	VIDEO_REG_Write(0x24d4, 0x807d776d); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x5a281f80); // Data LSB (Trigger) Addr=D
	VIDEO_REG_Write(0x24d4, 0x807a776f); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x61281c80); // Data LSB (Trigger) Addr=E
	VIDEO_REG_Write(0x24d4, 0x00000000); // Data MSB
	VIDEO_REG_Write(0x24d8, 0x00000000); // Data LSB (Trigger) Addr=F
	// -- TNR 3D-LUT
	VIDEO_REG_Write(0x24e0, 0x00101010); // [12]AI enable [2:0]Indirect Address
	// small motion (x1.0)
	VIDEO_REG_Write(0x24e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x20000600); // Data LSB (Trigger) Addr=0
	VIDEO_REG_Write(0x24e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x20000600); // Data LSB (Trigger) Addr=1
	VIDEO_REG_Write(0x24e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x20000600); // Data LSB (Trigger) Addr=2
	VIDEO_REG_Write(0x24e4, 0x00007a00); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73004000); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x20000600); // Data LSB (Trigger) Addr=3
	// large motion (x0.675)
	VIDEO_REG_Write(0x24e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x13e806e8); // Data LSB (Trigger) Addr=4
	VIDEO_REG_Write(0x24e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x13e806e8); // Data LSB (Trigger) Addr=5
	VIDEO_REG_Write(0x24e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x13e806e8); // Data LSB (Trigger) Addr=6
	VIDEO_REG_Write(0x24e4, 0x00e87ae8); // Data MSB
	VIDEO_REG_Write(0x24e8, 0x73e820e8); // Data Middle
	VIDEO_REG_Write(0x24ec, 0x13e806e8); // Data LSB (Trigger) Addr=7
	// large motion (x1.0)
	// WR 000024E4 00007A00 # Data MSB
	// WR 000024E8 73002000 # Data Middle
	// WR 000024EC 13000600 # Data LSB (Trigger) Addr=4
	// WR 000024E4 00007A00 # Data MSB
	// WR 000024E8 73002000 # Data Middle
	// WR 000024EC 13000600 # Data LSB (Trigger) Addr=5
	// WR 000024E4 00007A00 # Data MSB
	// WR 000024E8 73002000 # Data Middle
	// WR 000024EC 13000600 # Data LSB (Trigger) Addr=6
	// WR 000024E4 00007A00 # Data MSB
	// WR 000024E8 73002000 # Data Middle
	// WR 000024EC 13000600 # Data LSB (Trigger) Addr=7
	//-- ---------------------------------
	//-- color region
	//-- ---------------------------------
	VIDEO_REG_Write(0x24f0, 0x00001000); //- CR AI Write
	VIDEO_REG_Write(0x24f4, 0x0d50641e); //- CR[0][0] H(149),S(19),Y(30)
	VIDEO_REG_Write(0x24f4, 0x0dc0cc28); //- CR[0][1] H(154),S(39),Y(40)
	VIDEO_REG_Write(0x24f4, 0x0e310046); //- CR[0][2] H(159),S(49),Y(70)
	VIDEO_REG_Write(0x24f4, 0x13819896); //- CR[0][3] H(219),S(79),Y(150)
	VIDEO_REG_Write(0x24f4, 0x0520b019); //- CR[1][0] H(57),S(34),Y(25)
	VIDEO_REG_Write(0x24f4, 0x0550cc28); //- CR[1][1] H(59),S(39),Y(40)
	VIDEO_REG_Write(0x24f4, 0x05c10046); //- CR[1][2] H(64),S(49),Y(70)
	VIDEO_REG_Write(0x24f4, 0x0c01988c); //- CR[1][3] H(134),S(79),Y(140)
	VIDEO_REG_Write(0x24f4, 0x1dc06446); //- CR[2][0] H(334),S(19),Y(70)
	VIDEO_REG_Write(0x24f4, 0x1f10b05a); //- CR[2][1] H(349),S(34),Y(90)
	VIDEO_REG_Write(0x24f4, 0x255198be); //- CR[2][2] H(419),S(79),Y(190)
	VIDEO_REG_Write(0x24f4, 0x2711fcd2); //- CR[2][3] H(439),S(99),Y(210)
	VIDEO_REG_Write(0x24f4, 0x00000000); //- CR[3][0] H(0),S(0),Y(0)
	VIDEO_REG_Write(0x24f4, 0x00100401); //- CR[3][1] H(0),S(0),Y(1)
	VIDEO_REG_Write(0x24f4, 0x1fd0cc19); //- CR[3][2] H(357),S(39),Y(25)
	VIDEO_REG_Write(0x24f4, 0x1fe13028); //- CR[3][3] H(358),S(59),Y(40)
	// CLC
	// WR 0000246C 00000000	# [5:4]CLC CC LineMem Ctrl ("00":No Or-ing, "01","10":OrWithUpperLines)
	// WR 00002460 00000000	# [31]CLC Detector Fake Mode('1':Random-like, '0':Grid Type), [1:0]CLC Detection Enable
	//
	VIDEO_REG_WB(0x2440, "z1", "[0]"); // [0]:tnr_enable
	//
	//END
	//Script pql_run.scr => pql/tnr_default_HD.R.txt End

	//Script pql_run.scr => pql/rom_Q1_tuning_101022_L.txt Begin
	//-- ---------------------------------
	//-- LSR A Map: Color Boundary
	//-- ---------------------------------
	VIDEO_REG_WB(0x13f4, "x0C", "[23:19]"); //-- weight
	VIDEO_REG_WB(0x13f4, "x2", "[18:16]"); //-- mode(Ay+w*(Acb+Acr))


	//-- ---------------------------------
	//--DeRinging1(V)
	//-- ---------------------------------
	VIDEO_REG_WB(0x1400, "z1", "[0]"); // der1-v on

	//-- ---------------------------------
	//--LSR (Edge)
	//-- ---------------------------------
	VIDEO_REG_WB(0x13e8, "x3", "[31:30]"); //-- enable
//BW 000013E8 [13: 8]  xA #--x3 #-x3  #-- x5 edge:white gain
	VIDEO_REG_WB(0x13e8, "xA", "[21:16]"); //--x3 #-x3  #-- x2 edge:black gain
	VIDEO_REG_WB(0x13e4, "x6", "[13:8]"); //--x4 #-x4  #-- csft_gain(0x10)
	VIDEO_REG_WB(0x13d0, "x7", "[27:24]"); // A-width

	//-- ---------------------------------
	//--SHP (Edge) : Gain
	//-- ---------------------------------
	VIDEO_REG_WB(0x14f0, "z1", "[0]"); //-- enable
	VIDEO_REG_WB(0x14f4, "x18", "[6:0]"); //-- edge white gain
	VIDEO_REG_WB(0x14f4, "x28", "[14:8]"); //-- edge black gain
	VIDEO_REG_WB(0x14f4, "x20", "[23:16]"); //-- edge H gain
	VIDEO_REG_WB(0x14f4, "x18", "[31:24]"); //-- edge V gain
	VIDEO_REG_WB(0x14f8, "x10", "[31:24]"); //-- Sobel gain
	VIDEO_REG_WB(0x14f8, "xA0", "[15:8]"); //-- Lap gain

	//-- SHP: edge: coring
	VIDEO_REG_WB(0x1508, "z1", "[0]"); //--enable
	VIDEO_REG_WB(0x1508, "x0", "[7:6]"); //--mmd_sel(V) : '00': 7tap, "01": 5tap, "1x": 3tap
	VIDEO_REG_WB(0x1508, "x1", "[5:4]"); //--mmd_sel(H) : '00': 7tap, "01": 5tap, "1x": 3tap
	VIDEO_REG_WB(0x1508, "z0", "[8]"); //--th1 resolution
	VIDEO_REG_WB(0x1508, "x8", "[23:16]"); //--th1 (0x30 --> 0x8)
	VIDEO_REG_WB(0x1508, "x80", "[31:24]"); //--th2

	//-- SHP: edge: artifact reduction
	VIDEO_REG_WB(0x150c, "z0", "[0]"); //-- on/off
	VIDEO_REG_WB(0x150c, "z0", "[7]"); //-- debug on/off
	VIDEO_REG_WB(0x150c, "z0", "[6:4]"); //-- debug image selection
	VIDEO_REG_WB(0x150c, "x8", "[19:16]"); //-- gain(0.0(0x0) ~ 1.0(0x8))
	VIDEO_REG_WB(0x1510, "xA", "[7:0]"); //-- p0_th1
	VIDEO_REG_WB(0x1510, "x14", "[15:8]"); //-- p0_th2
	VIDEO_REG_WB(0x1510, "x08", "[23:16]"); //-- p1_th1
	VIDEO_REG_WB(0x1510, "x08", "[31:24]"); //-- p1_th2
	VIDEO_REG_WB(0x1514, "x20", "[7:0]"); //-- p1_th3
	VIDEO_REG_WB(0x1514, "x40", "[15:8]"); //-- p2_th1
	VIDEO_REG_WB(0x1514, "x48", "[23:16]"); //-- p2_th2
	VIDEO_REG_WB(0x1514, "x48", "[31:24]"); //-- p2_th3

	//-- stable H-peaking
	VIDEO_REG_WB(0x1500, "x1", "[12]"); //--	Gx manual mode
	VIDEO_REG_WB(0x1500, "x40", "[23:16]"); //--	Gx manual gain
	VIDEO_REG_WB(0x1500, "x0", "[26:24]"); //-- w.a(lap5, lap7)

	//-- stable V-peaking
	VIDEO_REG_WB(0x14f0, "z1", "[16]"); //-- Stable V-peaking enable

	//-- ---------------------------------
	//-- TI(H) #1:
	//-- ---------------------------------
	VIDEO_REG_WB(0x1578, "z0", "[0]"); //--   Off
	VIDEO_REG_WB(0x1578, "z0", "[1]"); //--  median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x1578, "x20", "[23:16]"); //-- <- 0x60 gain
	VIDEO_REG_WB(0x1578, "x40", "[15:8]"); //-- <- coring Th
	VIDEO_REG_WB(0x1578, "x5", "[6:4]"); //-- <- coring Step

	//-- ---------------------------------
	//-- TI(H) #2:
	//-- ---------------------------------
	VIDEO_REG_WB(0x157c, "z1", "[0]"); //--   On
	VIDEO_REG_WB(0x157c, "z0", "[1]"); //--  median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x157c, "x60", "[23:16]"); //-- <- 0x60 gain
	VIDEO_REG_WB(0x157c, "x40", "[15:8]"); //-- <- coring Th
	VIDEO_REG_WB(0x157c, "x5", "[6:4]"); //-- <- coring Step

	//-- ---------------------------------
	//-- TI(V) #1 : (After De-Ringing) --> Removed
	//-- ---------------------------------
	VIDEO_REG_WB(0x1570, "z0", "[0]"); //-- on
	VIDEO_REG_WB(0x1570, "z0", "[1]"); //-- median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x1570, "x30", "[23:16]"); //-- gain
	VIDEO_REG_WB(0x1570, "x40", "[15:8]"); //-- coring Th
	VIDEO_REG_WB(0x1570, "x5", "[6:4]"); //-- coring Step

	//-- ---------------------------------
	//-- TI(V) #2 : (In Peaking)
	//-- ---------------------------------
	VIDEO_REG_WB(0x1574, "z1", "[0]"); //-- off
	VIDEO_REG_WB(0x1574, "z0", "[1]"); //-- median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x1574, "x40", "[23:16]"); //-- gain
	VIDEO_REG_WB(0x1574, "x40", "[15:8]"); //-- coring Th
	VIDEO_REG_WB(0x1574, "x5", "[6:4]"); //-- coring Step

	//-- ---------------------------------
	//-- Adaptive TI-H control
	//-- ---------------------------------

	VIDEO_REG_WB(0x1580, "z1", "[0]"); //-- G0 :on/off
	VIDEO_REG_WB(0x1580, "z1", "[1]"); //-- G1 : on/off
	VIDEO_REG_WB(0x1580, "x50", "[23:16]"); //-- G0 : th0
	VIDEO_REG_WB(0x1580, "x5A", "[31:24]"); //-- G0 : th1
	VIDEO_REG_WB(0x1584, "x0", "[1:0]"); //-- G1 : div mode

	//-- ---------------------------------
	//-- CTI #1
	//-- ---------------------------------
	VIDEO_REG_WB(0x1520, "z1", "[0]"); //--on/off
	VIDEO_REG_WB(0x1520, "z1", "[1]"); //--filter type('0': bif, '1': um)
	VIDEO_REG_WB(0x1520, "z0", "[2]"); //--yc align enable
	VIDEO_REG_WB(0x1520, "x0", "[6:4]"); //--tap size
	VIDEO_REG_WB(0x1520, "x20", "[15:8]"); //--gain(3.5u)
	VIDEO_REG_WB(0x1520, "x60", "[23:16]"); //--a-mean th
	VIDEO_REG_WB(0x1520, "x23", "[31:24]"); //--C-csft gain
	VIDEO_REG_WB(0x1524, "x8", "[7:0]"); //--Y-csft gain
	VIDEO_REG_WB(0x1524, "x0", "[10:8]"); //--Y-csft tap

	//-- ---------------------------------
	//-- YCM #1
	//-- ---------------------------------
	VIDEO_REG_WB(0x1528, "z0", "[0]"); //-- pre ycm en
	VIDEO_REG_WB(0x1528, "z1", "[1]"); //-- post ycm en
	VIDEO_REG_WB(0x1528, "x2", "[6:4]"); //-- band sel
	VIDEO_REG_WB(0x1528, "x18", "[15:8]"); //-- diff th
	VIDEO_REG_WB(0x1528, "xF", "[19:16]"); //-- y gain
	VIDEO_REG_WB(0x1528, "xF", "[23:20]"); //-- c gain

	//-- ---------------------------------
	//-- EDF/DeJagging
	//-- ---------------------------------
	VIDEO_REG_WB(0x1590, "z1", "[0]"); // - EDF_enable
	VIDEO_REG_WB(0x1590, "z0", "[1]"); // - DJ_enable
	VIDEO_REG_WB(0x1590, "z0", "[5]"); // - L-protect enable
	VIDEO_REG_WB(0x1590, "z0", "[6]"); // - Center-pixel mode
	VIDEO_REG_WB(0x1590, "z1", "[6]"); // - center-blur	on/off
	VIDEO_REG_WB(0x1590, "x0", "[18:16]"); // - output mux(normal display)
	VIDEO_REG_WB(0x1590, "x2", "[21:20]"); // - center-blur mode(0" avg3x3, 1: avg3x1, 2: median3x3)
	VIDEO_REG_WB(0x1590, "z0", "[22]"); // - n-avg : mode
	VIDEO_REG_WB(0x1594, "x80", "[23:16]"); // - n-avg : gain
	VIDEO_REG_WB(0x1590, "z0", "[7]"); // - direcion number
	VIDEO_REG_WB(0x1590, "z1", "[2]"); // - g0: feature norm en
	VIDEO_REG_WB(0x1590, "z0", "[3]"); // - g0: feature-to-gain mapping en
	VIDEO_REG_WB(0x1594, "x10", "[7:0]"); // - g0: level threshold
	VIDEO_REG_WB(0x1598, "xB", "[4:0]"); // - edf_cnt_min
	VIDEO_REG_WB(0x1598, "x10", "[12:8]"); // - edf_cnt_max
	VIDEO_REG_WB(0x159c, "xB", "[4:0]"); // - dj_h_cnt_min
	VIDEO_REG_WB(0x159c, "x10", "[12:8]"); // - dj_h_cnt_max
	VIDEO_REG_WB(0x159c, "xB", "[20:16]"); // - dj_v_cnt_min
	VIDEO_REG_WB(0x159c, "x10", "[28:24]"); // - dj_v_cnt_max
	VIDEO_REG_WB(0x1590, "z0", "[4]"); // - Line Var mode
	VIDEO_REG_WB(0x1590, "x1", "[12:8]"); // - cnt diff th
	VIDEO_REG_WB(0x1590, "xB0", "[31:24]"); // - line-var diff th
	VIDEO_REG_WB(0x1594, "x10", "[15:8]"); // - g1 protect th


	//-- ---------------------------------
	//-- Detail
	//-- ---------------------------------

	//--common control
	VIDEO_REG_WB(0x1410, "z1", "[0]"); //-- detail on/off
	VIDEO_REG_WB(0x1410, "x48", "[23:16]"); //-- detail:black gain
//BW 00001410 [15: 8]  x40  #-- detail:white gain

	//-- filter #1
//BW 00001414 [ 7: 0]  x1   #-- f2 gain
//BW 00001414 [15: 8]  x2   #-- f3 gain
	VIDEO_REG_WB(0x1414, "x4", "[23:16]"); //-- f4 gain
	VIDEO_REG_WB(0x1414, "x8", "[31:24]"); //-- f5 gain
//BW 00001418 [ 7: 0]  xA   #-- t5 gain
	VIDEO_REG_WB(0x1410, "x3", "[25:24]"); //-- filter normalizatoin : 0(1/128),1(1/256),2(1/512),3(1/1024)
	VIDEO_REG_WB(0x1410, "z0", "[26]"); //-- SD/HD filter selection(SD)
	VIDEO_REG_WB(0x1424, "x0", "[14:12]"); //-- display gain for debug image

	//-- filter #2 (MSUM)
	VIDEO_REG_WB(0x1454, "z0", "[8]"); //-- enh2 enable
	VIDEO_REG_WB(0x1454, "z1", "[12]"); //-- enh2 norm. en
	VIDEO_REG_WB(0x1450, "x38", "[5:0]"); //--w3
	VIDEO_REG_WB(0x1450, "x38", "[13:8]"); //--w5
	VIDEO_REG_WB(0x1450, "x30", "[21:16]"); //--w7
	VIDEO_REG_WB(0x1450, "x30", "[29:24]"); //--w9
	VIDEO_REG_WB(0x1454, "x28", "[5:0]"); //-- w11


	//-- filter #3 (Laplacian)
	VIDEO_REG_WB(0x1458, "z1", "[0]"); //-- enable
	VIDEO_REG_WB(0x1458, "x0", "[6:4]"); //-- filter sel
	VIDEO_REG_WB(0x1458, "x50", "[15:8]"); //-- lap_gain
	VIDEO_REG_WB(0x1458, "x40", "[23:16]"); //-- sobel_gx_gain
	VIDEO_REG_WB(0x1458, "x10", "[31:24]"); //-- sobel_manual_gain
	VIDEO_REG_WB(0x145c, "x28", "[6:0]"); //-- white_gain
	VIDEO_REG_WB(0x145c, "x38", "[14:8]"); //-- black_gain
	VIDEO_REG_WB(0x145c, "x20", "[23:16]"); //-- h_gain
	VIDEO_REG_WB(0x145c, "x10", "[31:24]"); //-- v_gain


	//-- coring
	VIDEO_REG_WB(0x1424, "z1", "[0]"); //-- coring on
	VIDEO_REG_WB(0x1424, "x1", "[5:4]"); //-- mmd kernel size(3x3,5x3, 7x3, 9x3)
	VIDEO_REG_WB(0x142c, "x10", "[7:0]"); //-- L1
	VIDEO_REG_WB(0x142c, "x18", "[15:8]"); //-- L2
	VIDEO_REG_WB(0x142c, "x40", "[23:16]"); //-- H1
	VIDEO_REG_WB(0x142c, "x60", "[31:24]"); //-- H2

	//-- Lgain(Freq-band filter)
	VIDEO_REG_WB(0x1434, "z1", "[0]"); //-- lgain on
	VIDEO_REG_WB(0x1434, "x0", "[2:1]"); //-- "10": white gain에 적용
	VIDEO_REG_WB(0x1434, "x1E", "[15:8]"); //-- low th0
	VIDEO_REG_WB(0x1434, "x50", "[23:16]"); //-- low th1
	VIDEO_REG_WB(0x1438, "x78", "[7:0]"); //-- high th0
	VIDEO_REG_WB(0x1438, "x98", "[15:8]"); //-- high th1

	//--LSR (Pre-Gain Balancing, 10bit mode)
	VIDEO_REG_WB(0x143c, "z0", "[0]"); //-- disable
	VIDEO_REG_WB(0x143c, "z1", "[4]"); //-- x-resolution:'0':8bit, '1': 12bit
//BW 0000143C [15: 8] x1 	 #-- x5  #-- x6   #-- x1
	VIDEO_REG_WB(0x143c, "x2", "[23:16]"); //-- xa  #-- x20  #-- x2
//BW 00001440 [ 7: 0] x4 	 #-- xa  #-- xA   #-- y1
//BW 00001440 [15: 8] x8	 #-- x10 #-- x25  #-- y2
	VIDEO_REG_WB(0x1440, "x80", "[23:16]"); //-- x12 #-- xD0  #-- y3
	//--

	//--LSR: Post-Gain balancing
	VIDEO_REG_WB(0x1460, "z0", "[0]"); //-- on/off
	VIDEO_REG_WB(0x1460, "z1", "[4]"); //-- x-resolution: '0': 8bit, '1': 12bit
	VIDEO_REG_WB(0x1460, "x1", "[15:8]"); //-- x1
	VIDEO_REG_WB(0x1460, "x2", "[23:16]"); //-- x2
	VIDEO_REG_WB(0x1464, "x3", "[7:0]"); //-- y1
	VIDEO_REG_WB(0x1464, "x6", "[15:8]"); //-- y2
	VIDEO_REG_WB(0x1464, "x20", "[23:16]"); //-- y3



	//-- ---------------------------------
	//-- Blur
	//-- ---------------------------------
	VIDEO_REG_WB(0x1550, "z0", "[0]"); //-- Blur Disable
	VIDEO_REG_WB(0x1550, "z1", "[1]"); //-- Coring Enable
	VIDEO_REG_WB(0x1550, "x00", "[15:8]"); //-- Blur Gain
	VIDEO_REG_WB(0x1550, "x02", "[23:16]"); //-- Coring Min
	VIDEO_REG_WB(0x1550, "x08", "[31:24]"); //-- Coring Max

	//-- ---------------------------------
	//-- Single-scale UM
	//-- ---------------------------------
	VIDEO_REG_WB(0x1530, "z1", "[0]"); //-- LCon on
	VIDEO_REG_WB(0x1530, "x0", "[3]"); //-- filter tap('0': 3x3,'1': 5x3)
	VIDEO_REG_WB(0x1530, "x18", "[23:16]"); //-- black gain
	VIDEO_REG_WB(0x1530, "x10", "[15:8]"); //-- white gain
	VIDEO_REG_WB(0x1530, "z1", "[1]"); //-- Coring En
	VIDEO_REG_WB(0x1530, "x1", "[6:5]"); //-- coring mmd kernel(5x3)
	VIDEO_REG_WB(0x1530, "z0", "[2]"); //-- coring feature: mmd(0), x-avg(1)
//BW 00001534 [ 7: 0] x20 #-- coring th(L1)
//BW 00001534 [15: 8] x40 #-- coring th(L2)
	VIDEO_REG_WB(0x1534, "x80", "[23:16]"); //-- coring th(H1)
	VIDEO_REG_WB(0x1534, "xa0", "[31:24]"); //-- coring th(H2)

	//-- Lgain(SSUM)
	VIDEO_REG_WB(0x1538, "z1", "[0]"); //-- lgain on
	VIDEO_REG_WB(0x1538, "x0", "[2:1]"); //-- "10": white gain에 적용
	VIDEO_REG_WB(0x1538, "x1E", "[15:8]"); //-- low th0
	VIDEO_REG_WB(0x1538, "x50", "[23:16]"); //-- low th1
	VIDEO_REG_WB(0x153c, "x78", "[7:0]"); //-- high th0
	VIDEO_REG_WB(0x153c, "x98", "[15:8]"); //-- high th1


	//-- Load Setting --
	VIDEO_REG_Write(0x1300, 0x00000004); //-- manual load
	VIDEO_REG_Write(0x1300, 0x00000020); //-- load enable
	//Script pql_run.scr => pql/rom_Q1_tuning_101022_L.txt End

	//Script pql_run.scr => pql/rom_Q1_tuning_101022_R.txt Begin
	//-- ---------------------------------
	//-- LSR A Map: Color Boundary
	//-- ---------------------------------
	VIDEO_REG_WB(0x33f4, "x0C", "[23:19]"); //-- weight
	VIDEO_REG_WB(0x33f4, "x2", "[18:16]"); //-- mode(Ay+w*(Acb+Acr))


	//-- ---------------------------------
	//--DeRinging1(V)
	//-- ---------------------------------
	VIDEO_REG_WB(0x3400, "z1", "[0]"); // der1-v on

	//-- ---------------------------------
	//--LSR (Edge)
	//-- ---------------------------------
	VIDEO_REG_WB(0x33e8, "x3", "[31:30]"); //-- enable
//BW 000033E8 [13: 8]  xA #--x3 #-x3  #-- x5 edge:white gain
	VIDEO_REG_WB(0x33e8, "xA", "[21:16]"); //--x3 #-x3  #-- x2 edge:black gain
	VIDEO_REG_WB(0x33e4, "x6", "[13:8]"); //--x4 #-x4  #-- csft_gain(0x10)
	VIDEO_REG_WB(0x33d0, "x7", "[27:24]"); // A-width

	//-- ---------------------------------
	//--SHP (Edge) : Gain
	//-- ---------------------------------
	VIDEO_REG_WB(0x34f0, "z1", "[0]"); //-- enable
	VIDEO_REG_WB(0x34f4, "x18", "[6:0]"); //-- edge white gain
	VIDEO_REG_WB(0x34f4, "x28", "[14:8]"); //-- edge black gain
	VIDEO_REG_WB(0x34f4, "x20", "[23:16]"); //-- edge H gain
	VIDEO_REG_WB(0x34f4, "x18", "[31:24]"); //-- edge V gain
	VIDEO_REG_WB(0x34f8, "x10", "[31:24]"); //-- Sobel gain
	VIDEO_REG_WB(0x34f8, "xA0", "[15:8]"); //-- Lap gain

	//-- SHP: edge: coring
	VIDEO_REG_WB(0x3508, "z1", "[0]"); //--enable
	VIDEO_REG_WB(0x3508, "x0", "[7:6]"); //--mmd_sel(V) : '00': 7tap, "01": 5tap, "1x": 3tap
	VIDEO_REG_WB(0x3508, "x1", "[5:4]"); //--mmd_sel(H) : '00': 7tap, "01": 5tap, "1x": 3tap
	VIDEO_REG_WB(0x3508, "z0", "[8]"); //--th1 resolution
	VIDEO_REG_WB(0x3508, "x8", "[23:16]"); //--th1 (0x30 --> 0x8)
	VIDEO_REG_WB(0x3508, "x80", "[31:24]"); //--th2

	//-- SHP: edge: artifact reduction
	VIDEO_REG_WB(0x350c, "z0", "[0]"); //-- on/off
	VIDEO_REG_WB(0x350c, "z0", "[7]"); //-- debug on/off
	VIDEO_REG_WB(0x350c, "z0", "[6:4]"); //-- debug image selection
	VIDEO_REG_WB(0x350c, "x8", "[19:16]"); //-- gain(0.0(0x0) ~ 1.0(0x8))
	VIDEO_REG_WB(0x3510, "xA", "[7:0]"); //-- p0_th1
	VIDEO_REG_WB(0x3510, "x14", "[15:8]"); //-- p0_th2
	VIDEO_REG_WB(0x3510, "x08", "[23:16]"); //-- p1_th1
	VIDEO_REG_WB(0x3510, "x08", "[31:24]"); //-- p1_th2
	VIDEO_REG_WB(0x3514, "x20", "[7:0]"); //-- p1_th3
	VIDEO_REG_WB(0x3514, "x40", "[15:8]"); //-- p2_th1
	VIDEO_REG_WB(0x3514, "x48", "[23:16]"); //-- p2_th2
	VIDEO_REG_WB(0x3514, "x48", "[31:24]"); //-- p2_th3

	//-- stable H-peaking
	VIDEO_REG_WB(0x3500, "x1", "[12]"); //--	Gx manual mode
	VIDEO_REG_WB(0x3500, "x40", "[23:16]"); //--	Gx manual gain
	VIDEO_REG_WB(0x3500, "x0", "[26:24]"); //-- w.a(lap5, lap7)

	//-- stable V-peaking
	VIDEO_REG_WB(0x34f0, "z1", "[16]"); //-- Stable V-peaking enable

	//-- ---------------------------------
	//-- TI(H) #1:
	//-- ---------------------------------
	VIDEO_REG_WB(0x3578, "z0", "[0]"); //--   Off
	VIDEO_REG_WB(0x3578, "z0", "[1]"); //--  median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x3578, "x20", "[23:16]"); //-- <- 0x60 gain
	VIDEO_REG_WB(0x3578, "x40", "[15:8]"); //-- <- coring Th
	VIDEO_REG_WB(0x3578, "x5", "[6:4]"); //-- <- coring Step

	//-- ---------------------------------
	//-- TI(H) #2:
	//-- ---------------------------------
	VIDEO_REG_WB(0x357c, "z1", "[0]"); //--   On
	VIDEO_REG_WB(0x357c, "z0", "[1]"); //--  median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x357c, "x60", "[23:16]"); //-- <- 0x60 gain
	VIDEO_REG_WB(0x357c, "x40", "[15:8]"); //-- <- coring Th
	VIDEO_REG_WB(0x357c, "x5", "[6:4]"); //-- <- coring Step

	//-- ---------------------------------
	//-- TI(V) #1 : (After De-Ringing) --> Removed
	//-- ---------------------------------
	VIDEO_REG_WB(0x3570, "z0", "[0]"); //-- on
	VIDEO_REG_WB(0x3570, "z0", "[1]"); //-- median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x3570, "x30", "[23:16]"); //-- gain
	VIDEO_REG_WB(0x3570, "x40", "[15:8]"); //-- coring Th
	VIDEO_REG_WB(0x3570, "x5", "[6:4]"); //-- coring Step

	//-- ---------------------------------
	//-- TI(V) #2 : (In Peaking)
	//-- ---------------------------------
	VIDEO_REG_WB(0x3574, "z1", "[0]"); //-- off
	VIDEO_REG_WB(0x3574, "z0", "[1]"); //-- median filtering off(include center pixel in min/max clipping.)
	VIDEO_REG_WB(0x3574, "x40", "[23:16]"); //-- gain
	VIDEO_REG_WB(0x3574, "x40", "[15:8]"); //-- coring Th
	VIDEO_REG_WB(0x3574, "x5", "[6:4]"); //-- coring Step

	//-- ---------------------------------
	//-- Adaptive TI-H control
	//-- ---------------------------------

	VIDEO_REG_WB(0x3580, "z1", "[0]"); //-- G0 :on/off
	VIDEO_REG_WB(0x3580, "z1", "[1]"); //-- G1 : on/off
	VIDEO_REG_WB(0x3580, "x50", "[23:16]"); //-- G0 : th0
	VIDEO_REG_WB(0x3580, "x5A", "[31:24]"); //-- G0 : th1
	VIDEO_REG_WB(0x3584, "x0", "[1:0]"); //-- G1 : div mode

	//-- ---------------------------------
	//-- CTI #1
	//-- ---------------------------------
	VIDEO_REG_WB(0x3520, "z1", "[0]"); //--on/off
	VIDEO_REG_WB(0x3520, "z1", "[1]"); //--filter type('0': bif, '1': um)
	VIDEO_REG_WB(0x3520, "z0", "[2]"); //--yc align enable
	VIDEO_REG_WB(0x3520, "x0", "[6:4]"); //--tap size
	VIDEO_REG_WB(0x3520, "x20", "[15:8]"); //--gain(3.5u)
	VIDEO_REG_WB(0x3520, "x60", "[23:16]"); //--a-mean th
	VIDEO_REG_WB(0x3520, "x23", "[31:24]"); //--C-csft gain
	VIDEO_REG_WB(0x3524, "x8", "[7:0]"); //--Y-csft gain
	VIDEO_REG_WB(0x3524, "x0", "[10:8]"); //--Y-csft tap

	//-- ---------------------------------
	//-- YCM #1
	//-- ---------------------------------
	VIDEO_REG_WB(0x3528, "z0", "[0]"); //-- pre ycm en
	VIDEO_REG_WB(0x3528, "z1", "[1]"); //-- post ycm en
	VIDEO_REG_WB(0x3528, "x2", "[6:4]"); //-- band sel
	VIDEO_REG_WB(0x3528, "x18", "[15:8]"); //-- diff th
	VIDEO_REG_WB(0x3528, "xF", "[19:16]"); //-- y gain
	VIDEO_REG_WB(0x3528, "xF", "[23:20]"); //-- c gain

	//-- ---------------------------------
	//-- EDF/DeJagging
	//-- ---------------------------------
	VIDEO_REG_WB(0x3590, "z1", "[0]"); // - EDF_enable
	VIDEO_REG_WB(0x3590, "z0", "[1]"); // - DJ_enable
	VIDEO_REG_WB(0x3590, "z0", "[5]"); // - L-protect enable
	VIDEO_REG_WB(0x3590, "z0", "[6]"); // - Center-pixel mode
	VIDEO_REG_WB(0x3590, "z1", "[6]"); // - center-blur	on/off
	VIDEO_REG_WB(0x3590, "x0", "[18:16]"); // - output mux(normal display)
	VIDEO_REG_WB(0x3590, "x2", "[21:20]"); // - center-blur mode(0" avg3x3, 1: avg3x1, 2: median3x3)
	VIDEO_REG_WB(0x3590, "z0", "[22]"); // - n-avg : mode
	VIDEO_REG_WB(0x3594, "x80", "[23:16]"); // - n-avg : gain
	VIDEO_REG_WB(0x3590, "z0", "[7]"); // - direcion number
	VIDEO_REG_WB(0x3590, "z1", "[2]"); // - g0: feature norm en
	VIDEO_REG_WB(0x3590, "z0", "[3]"); // - g0: feature-to-gain mapping en
	VIDEO_REG_WB(0x3594, "x10", "[7:0]"); // - g0: level threshold
	VIDEO_REG_WB(0x3598, "xB", "[4:0]"); // - edf_cnt_min
	VIDEO_REG_WB(0x3598, "x10", "[12:8]"); // - edf_cnt_max
	VIDEO_REG_WB(0x359c, "xB", "[4:0]"); // - dj_h_cnt_min
	VIDEO_REG_WB(0x359c, "x10", "[12:8]"); // - dj_h_cnt_max
	VIDEO_REG_WB(0x359c, "xB", "[20:16]"); // - dj_v_cnt_min
	VIDEO_REG_WB(0x359c, "x10", "[28:24]"); // - dj_v_cnt_max
	VIDEO_REG_WB(0x3590, "z0", "[4]"); // - Line Var mode
	VIDEO_REG_WB(0x3590, "x1", "[12:8]"); // - cnt diff th
	VIDEO_REG_WB(0x3590, "xB0", "[31:24]"); // - line-var diff th
	VIDEO_REG_WB(0x3594, "x10", "[15:8]"); // - g1 protect th


	//-- ---------------------------------
	//-- Detail
	//-- ---------------------------------

	//--common control
	VIDEO_REG_WB(0x3410, "z1", "[0]"); //-- detail on/off
	VIDEO_REG_WB(0x3410, "x48", "[23:16]"); //-- detail:black gain
//BW 00003410 [15: 8]  x40  #-- detail:white gain

	//-- filter #1
//BW 00003414 [ 7: 0]  x1   #-- f2 gain
//BW 00003414 [15: 8]  x2   #-- f3 gain
	VIDEO_REG_WB(0x3414, "x4", "[23:16]"); //-- f4 gain
	VIDEO_REG_WB(0x3414, "x8", "[31:24]"); //-- f5 gain
//BW 00003418 [ 7: 0]  xA   #-- t5 gain
	VIDEO_REG_WB(0x3410, "x3", "[25:24]"); //-- filter normalizatoin : 0(1/128),1(1/256),2(1/512),3(1/1024)
	VIDEO_REG_WB(0x3410, "z0", "[26]"); //-- SD/HD filter selection(SD)
	VIDEO_REG_WB(0x3424, "x0", "[14:12]"); //-- display gain for debug image

	//-- filter #2 (MSUM)
	VIDEO_REG_WB(0x3454, "z0", "[8]"); //-- enh2 enable
	VIDEO_REG_WB(0x3454, "z1", "[12]"); //-- enh2 norm. en
	VIDEO_REG_WB(0x3450, "x38", "[5:0]"); //--w3
	VIDEO_REG_WB(0x3450, "x38", "[13:8]"); //--w5
	VIDEO_REG_WB(0x3450, "x30", "[21:16]"); //--w7
	VIDEO_REG_WB(0x3450, "x30", "[29:24]"); //--w9
	VIDEO_REG_WB(0x3454, "x28", "[5:0]"); //-- w11


	//-- filter #3 (Laplacian)
	VIDEO_REG_WB(0x3458, "z1", "[0]"); //-- enable
	VIDEO_REG_WB(0x3458, "x0", "[6:4]"); //-- filter sel
	VIDEO_REG_WB(0x3458, "x50", "[15:8]"); //-- lap_gain
	VIDEO_REG_WB(0x3458, "x40", "[23:16]"); //-- sobel_gx_gain
	VIDEO_REG_WB(0x3458, "x10", "[31:24]"); //-- sobel_manual_gain
	VIDEO_REG_WB(0x345c, "x28", "[6:0]"); //-- white_gain
	VIDEO_REG_WB(0x345c, "x38", "[14:8]"); //-- black_gain
	VIDEO_REG_WB(0x345c, "x20", "[23:16]"); //-- h_gain
	VIDEO_REG_WB(0x345c, "x10", "[31:24]"); //-- v_gain


	//-- coring
	VIDEO_REG_WB(0x3424, "z1", "[0]"); //-- coring on
	VIDEO_REG_WB(0x3424, "x1", "[5:4]"); //-- mmd kernel size(3x3,5x3, 7x3, 9x3)
	VIDEO_REG_WB(0x342c, "x10", "[7:0]"); //-- L1
	VIDEO_REG_WB(0x342c, "x18", "[15:8]"); //-- L2
	VIDEO_REG_WB(0x342c, "x40", "[23:16]"); //-- H1
	VIDEO_REG_WB(0x342c, "x60", "[31:24]"); //-- H2

	//-- Lgain(Freq-band filter)
	VIDEO_REG_WB(0x3434, "z1", "[0]"); //-- lgain on
	VIDEO_REG_WB(0x3434, "x0", "[2:1]"); //-- "10": white gain에 적용
	VIDEO_REG_WB(0x3434, "x1E", "[15:8]"); //-- low th0
	VIDEO_REG_WB(0x3434, "x50", "[23:16]"); //-- low th1
	VIDEO_REG_WB(0x3438, "x78", "[7:0]"); //-- high th0
	VIDEO_REG_WB(0x3438, "x98", "[15:8]"); //-- high th1

	//--LSR (Pre-Gain Balancing, 10bit mode)
	VIDEO_REG_WB(0x343c, "z0", "[0]"); //-- disable
	VIDEO_REG_WB(0x343c, "z1", "[4]"); //-- x-resolution:'0':8bit, '1': 12bit
//BW 0000343C [15: 8] x1 	 #-- x5  #-- x6   #-- x1
	VIDEO_REG_WB(0x343c, "x2", "[23:16]"); //-- xa  #-- x20  #-- x2
//BW 00003440 [ 7: 0] x4 	 #-- xa  #-- xA   #-- y1
//BW 00003440 [15: 8] x8	 #-- x10 #-- x25  #-- y2
	VIDEO_REG_WB(0x3440, "x80", "[23:16]"); //-- x12 #-- xD0  #-- y3
	//--

	//--LSR: Post-Gain balancing
	VIDEO_REG_WB(0x3460, "z0", "[0]"); //-- on/off
	VIDEO_REG_WB(0x3460, "z1", "[4]"); //-- x-resolution: '0': 8bit, '1': 12bit
	VIDEO_REG_WB(0x3460, "x1", "[15:8]"); //-- x1
	VIDEO_REG_WB(0x3460, "x2", "[23:16]"); //-- x2
	VIDEO_REG_WB(0x3464, "x3", "[7:0]"); //-- y1
	VIDEO_REG_WB(0x3464, "x6", "[15:8]"); //-- y2
	VIDEO_REG_WB(0x3464, "x20", "[23:16]"); //-- y3



	//-- ---------------------------------
	//-- Blur
	//-- ---------------------------------
	VIDEO_REG_WB(0x3550, "z0", "[0]"); //-- Blur Disable
	VIDEO_REG_WB(0x3550, "z1", "[1]"); //-- Coring Enable
	VIDEO_REG_WB(0x3550, "x00", "[15:8]"); //-- Blur Gain
	VIDEO_REG_WB(0x3550, "x02", "[23:16]"); //-- Coring Min
	VIDEO_REG_WB(0x3550, "x08", "[31:24]"); //-- Coring Max

	//-- ---------------------------------
	//-- Single-scale UM
	//-- ---------------------------------
	VIDEO_REG_WB(0x3530, "z1", "[0]"); //-- LCon on
	VIDEO_REG_WB(0x3530, "x0", "[3]"); //-- filter tap('0': 3x3,'1': 5x3)
	VIDEO_REG_WB(0x3530, "x18", "[23:16]"); //-- black gain
	VIDEO_REG_WB(0x3530, "x10", "[15:8]"); //-- white gain
	VIDEO_REG_WB(0x3530, "z1", "[1]"); //-- Coring En
	VIDEO_REG_WB(0x3530, "x1", "[6:5]"); //-- coring mmd kernel(5x3)
	VIDEO_REG_WB(0x3530, "z0", "[2]"); //-- coring feature: mmd(0), x-avg(1)
//BW 00003534 [ 7: 0] x20 #-- coring th(L1)
//BW 00003534 [15: 8] x40 #-- coring th(L2)
	VIDEO_REG_WB(0x3534, "x80", "[23:16]"); //-- coring th(H1)
	VIDEO_REG_WB(0x3534, "xa0", "[31:24]"); //-- coring th(H2)

	//-- Lgain(SSUM)
	VIDEO_REG_WB(0x3538, "z1", "[0]"); //-- lgain on
	VIDEO_REG_WB(0x3538, "x0", "[2:1]"); //-- "10": white gain에 적용
	VIDEO_REG_WB(0x3538, "x1E", "[15:8]"); //-- low th0
	VIDEO_REG_WB(0x3538, "x50", "[23:16]"); //-- low th1
	VIDEO_REG_WB(0x353c, "x78", "[7:0]"); //-- high th0
	VIDEO_REG_WB(0x353c, "x98", "[15:8]"); //-- high th1


	//-- Load Setting --
	VIDEO_REG_Write(0x3300, 0x00000004); //-- manual load
	VIDEO_REG_Write(0x3300, 0x00000020); //-- load enable
	//Script pql_run.scr => pql/rom_Q1_tuning_101022_R.txt End
	//Script pql_run.scr End

	return RET_OK;
}

/**  @} */
