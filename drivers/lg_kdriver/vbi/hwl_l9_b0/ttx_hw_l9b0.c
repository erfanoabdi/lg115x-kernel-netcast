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
 *	TTX module control Drivers linux module
 *
 *  author      won.hur (won.hur@lge.com)
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg1150_TTX
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <linux/timer.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include "vbi_kapi.h"

#include "vbi_module.h"
#include "vbi_data.h"
#include "vbi_hw.h"
#include "vbi_drv.h"

#include "./../../afe/l9/vport_reg_l9b0.h"
#include "./../../afe/cvd_hw.h"

#include "os_util.h"
#ifdef	_WITHOUT_AFE_
//volatile VPORT_Reg_T *gVportReg;	// <- prototype from AFE. because the
					//	registers for ADC, CVD, HDMI are in AFE modules
#else	//_WITHOUT_ADC_
//extern volatile VPORT_RegBx_T *gVportRegBx;
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	VBI_OFF	0
#define	VBI_ON	1
#define WSS_BUF_SIZE	5

#define ALLOW_54MHZ_TTX_MODE 0

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
#define	VPS_DATA_LINE	16
#define	WSS_DATA_LINE	23
#define	DATA_OFFSET		2

#define VBI_DATA_ODD_START_LINE		6
#define VBI_DATA_ODD_END_LINE		23
#define VBI_DATA_EVEN_START_LINE	318
#define VBI_DATA_EVEN_END_LINE		335
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
int gTTXCountOfLine318;
int gTTXCountOfOtherLine;

#ifdef	KDRV_CONFIG_PM
static int guiPmIntStatus = 0;
static eVBIDataType guiPmTtxModeStatus = eTTX625B;
#endif
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
extern volatile VPORT_L9B0_REG_T __iomem *gpRegVPORT_L9B0;
extern volatile VPORT_L9B0_REG_T __iomem *gpRealRegVPORT_L9B0;
static volatile unsigned long gTTX_addr;

static int ttx_54Mhz_flag = 0;

static unsigned char *ucPacket;

/*========================================================================================
	Implementation Group
========================================================================================*/

int TTX_HWInitialize_L9Bx(void)
{
	int ret = 0;

	gTTXCountOfLine318 = 0;

	// TODO:dws
	gTTX_addr = (volatile unsigned long)ioremap(	gstRegCfgVBI->vbi_register_base , 	gstRegCfgVBI->vbi_register_size);

	ucPacket = (unsigned char *)kmalloc( (TTX_MAX_DATA + 7) * MAX_PACKET_NUM , GFP_KERNEL);

	// Need to modify kdriver to use little endian.
	VPORT_L9B0_RdFL(vbi_ctrl_001);
	VPORT_L9B0_Wr01(vbi_ctrl_001, reg_vbi_little_endian, 0);
	VPORT_L9B0_WrFL(vbi_ctrl_001);

	return ret;
}

int TTX_HWUninitialize_L9Bx(void)
{
	int ret = 0;

	//iounmap((void *)gpRealRegVPORT_L9B0);
	//kfree((void*)gpRegVPORT_L9B0);
	iounmap((void *)gTTX_addr);

	kfree((void*)ucPacket);


	return ret;
}

int TTX_SetInputFormat_L9Bx(eVBIDataType type)
{
	int ret = 0;

	TTX_PRINT("%s input : %d\n" , __func__ , type);

#ifdef	KDRV_CONFIG_PM
	guiPmTtxModeStatus = type;
#endif

	switch(type)
	{
		case eDisable:
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_OFF);
			VPORT_L9B0_WrFL(vbi_004);
			break;

		case eClosedCaptionUS:
		case eClosedCaptionEURO:
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
//			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(iris_039);

			VPORT_L9B0_Wr(vbi_007, 0);
			VPORT_L9B0_Wr(vbi_008, 0);
			VPORT_L9B0_Wr(vbi_009, 0);
			VPORT_L9B0_Wr(vbi_010, 0x11);
			VPORT_L9B0_Wr(vbi_011, 0);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0xE736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54548282);
			VPORT_L9B0_Wr(vbi_014, 0x35A012DB);
			VPORT_L9B0_Wr(vbi_015, 0x2066159A);
//			VPORT_L9B0_Wr01(vbi_016, wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);

			VPORT_L9B0_WrFL(vbi_004);
			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
//			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);

			break;

		case eVPS:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
//			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);

			VPORT_L9B0_Wr(vbi_007, 0);
			VPORT_L9B0_Wr(vbi_008, 0);
			VPORT_L9B0_Wr(vbi_009, 0);
			VPORT_L9B0_Wr(vbi_010, 0);
			VPORT_L9B0_Wr(vbi_011, 0);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_Wr(vbi_014, 0x35A012DB);
			VPORT_L9B0_Wr(vbi_015, 0x2066159a);
//			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
//			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			VPORT_L9B0_WrFL(vbi_010);
			break;

		case eTTX625A:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
//			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);

			VPORT_L9B0_Wr(vbi_007, 0x55555555);
			VPORT_L9B0_Wr(vbi_008, 0x55555555);
			VPORT_L9B0_Wr(vbi_009, 0x55555555);
			VPORT_L9B0_Wr(vbi_010, 0x55555555);
			VPORT_L9B0_Wr(vbi_011, 0);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
//			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
//			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
//			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			break;

		case eTTX625B:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_RdFL(vbi_013);
			VPORT_L9B0_RdFL(vbi_012);


			VPORT_L9B0_Wr(vbi_007, 0x66666666);
			VPORT_L9B0_Wr(vbi_008, 0x66666666);
			// 110917 by dws : Enable 16, 329 line TTX Slicing
			VPORT_L9B0_Wr(vbi_009, 0x66666666);
			//VPORT_L9B0_Wr(vbi_009, 0x66663366);
			VPORT_L9B0_Wr(vbi_010, 0x66666666);
			// 110917 by dws : Disable 336 line WSS Slicing
			VPORT_L9B0_Wr(vbi_011, 0x660C0000);
			//VPORT_L9B0_Wr(vbi_011, 0x66cc0000);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54825a5a);
			VPORT_L9B0_Wr(vbi_014, 0x35A00F91);

			//VPORT_L9B0_Wr(vbi_015, 0x2066159a);
			// 110712 : WSS malfunction on green/red pattern
			//VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x205A);		//13.48MHz
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);		//13.5MHz
			VPORT_L9B0_Wr01(vbi_015, reg_vps_dto, 0x159a);

			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);

			// 110712 : WSS malfunction on green/red pattern
			VPORT_L9B0_Wr01(vbi_013, reg_vbi_wss_slicer_mode, 0x1);

			VPORT_L9B0_Wr01(vbi_004, reg_vbi_muxout, 0);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_hsyncout, 0);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);

			// 111104 allow one bit error in start code detection for L9B1 only
			if( lx_chip_rev( ) >= LX_CHIP_REV(L9,B1) )
				VPORT_L9B0_Wr01(vbi_004, reg_vbi_st_err_ignored, 1);
			else
				VPORT_L9B0_Wr01(vbi_004, reg_vbi_st_err_ignored, 0);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			VPORT_L9B0_WrFL(vbi_013);

			// 110905 for L9B0 54MHz TTX
			VPORT_L9B0_RdFL(vbi_022);
			VPORT_L9B0_Wr01(vbi_022, reg_ttx_out_sel, 0x0);	//select 54Mhz or 27Mhz TTX
			VPORT_L9B0_Wr01(vbi_022, reg_ttx_vbi_en, 0x1);
			VPORT_L9B0_Wr01(vbi_022, reg_ttx_adap_slvl_en, 0x1);
			VPORT_L9B0_Wr01(vbi_022, reg_ttx_vbi_data_hlvl, 0x36);
			VPORT_L9B0_WrFL(vbi_022);

			VPORT_L9B0_RdFL(vbi_023);
			VPORT_L9B0_Wr01(vbi_023, reg_ttx_tt_slicer_mode, 0x0);
			VPORT_L9B0_Wr01(vbi_023, reg_ttx_teletext_runin_accum_amp, 0x40);
			VPORT_L9B0_Wr01(vbi_023, reg_ttx_vbi_tele_lpfil_acq_gain, 0x8);
			VPORT_L9B0_Wr01(vbi_023, reg_ttx_vbi_tele_lpfil_track_gai, 0x4);
			VPORT_L9B0_Wr01(vbi_023, reg_ttx_vbi_tele_lpfil_fine_gain, 0x2);
			VPORT_L9B0_Wr01(vbi_023, reg_ttx_teletext_start, 0x5a);
			VPORT_L9B0_WrFL(vbi_023);

			VPORT_L9B0_RdFL(vbi_024);
			VPORT_L9B0_Wr01(vbi_024, reg_ttx_vbi_fixgate_en, 0x0);
			VPORT_L9B0_Wr01(vbi_024, reg_ttx_teletext_dto, 0x1f22);
			VPORT_L9B0_Wr01(vbi_024, reg_ttx_teletext_frame_start, 0x2);
			VPORT_L9B0_Wr01(vbi_024, reg_ttx_start_code, 0x27);
			VPORT_L9B0_WrFL(vbi_024);

			// 110121 won.hur : for 318 line TTX data
			VPORT_L9B0_Wr(vbi_012, 0x00000060);
			VPORT_L9B0_WrFL(vbi_012);

			break;

		case eTTX625C:

		break;
		case eTTX625D:

		break;
		case eTTX525B:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
//			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);

			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_Wr(vbi_007, 0x99999999);
			VPORT_L9B0_Wr(vbi_008, 0x99999999);
			VPORT_L9B0_Wr(vbi_009, 0x99999999);
			VPORT_L9B0_Wr(vbi_010, 0x99999999);
			VPORT_L9B0_Wr(vbi_011, 0);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
//			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
//			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
//			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			break;

		case eTTX525C:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
//			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);

			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_Wr(vbi_007, 0xAAAAAAAA);
			VPORT_L9B0_Wr(vbi_008, 0xAAAAAAAA);
			VPORT_L9B0_Wr(vbi_009, 0xAAAAAAAA);
			VPORT_L9B0_Wr(vbi_010, 0xAAAAAAAA);
			VPORT_L9B0_Wr(vbi_011, 0);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0xE736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54546482);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
//			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
//			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x23);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
//			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			break;

		case eTTX525D:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
//			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);

			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_Wr(vbi_007, 0xBBBBBBBB);
			VPORT_L9B0_Wr(vbi_008, 0xBBBBBBBB);
			VPORT_L9B0_Wr(vbi_009, 0xBBBBBBBB);
			VPORT_L9B0_Wr(vbi_010, 0xBBBBBBBB);
			VPORT_L9B0_Wr(vbi_011, 0);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0xA736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			//VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			//VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x23);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
//			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			break;

		case eWSS625:
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_RdFL(vbi_004);

			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_Wr(vbi_007, 0);
			VPORT_L9B0_Wr(vbi_008, 0);
			VPORT_L9B0_Wr(vbi_009, 0);
			VPORT_L9B0_Wr(vbi_010, 0);
			VPORT_L9B0_Wr(vbi_011, 0x00CC0000);
			// vbi_data_hlvl & start_code
			VPORT_L9B0_Wr(vbi_006, 0xE736);
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			VPORT_L9B0_Wr(vbi_020, 0x54828282);
//			VPORT_L9B0_Wr01(vbi_014, teletext_dto, 0x12DB);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x23);

			VPORT_L9B0_WrFL(vbi_007);
			VPORT_L9B0_WrFL(vbi_008);
			VPORT_L9B0_WrFL(vbi_009);
			VPORT_L9B0_WrFL(vbi_010);
			VPORT_L9B0_WrFL(vbi_011);
			VPORT_L9B0_WrFL(vbi_006);
			VPORT_L9B0_WrFL(vbi_020);
			VPORT_L9B0_WrFL(vbi_014);
			VPORT_L9B0_WrFL(vbi_015);
			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
			VPORT_L9B0_WrFL(vbi_004);
			break;

		case eWSSJ:
			break;
		default:
			break;
	}

	TTX_PRINT("%s done\n", __func__);

	return ret;

}


int TTX_SetInterruptClear_L9Bx(void)
{
	int ret = 0;
	UINT32 intr_vp1_en;

	VPORT_L9B0_RdFL(cvd_intr1_clear0);
	intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_clear0);
	VPORT_L9B0_Wr(cvd_intr1_clear0, (intr_vp1_en |= (1<<15)));
	VPORT_L9B0_WrFL(cvd_intr1_clear0);

	VPORT_L9B0_RdFL(cvd_intr1_clear0);
	intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_clear0);
	VPORT_L9B0_Wr(cvd_intr1_clear0, (intr_vp1_en &= ~(1<<15)));
	VPORT_L9B0_WrFL(cvd_intr1_clear0);

	return ret;
}


int TTX_SetInterrupt_L9Bx(int on_off)
{
	int ret = 0;
	UINT32 intr_vp1_en;

#ifdef	KDRV_CONFIG_PM
	guiPmIntStatus = on_off;
#endif

	if(on_off)
	{
		VPORT_L9B0_RdFL(cvd_intr1_enable1);
		intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_enable1);
		VPORT_L9B0_Wr(cvd_intr1_enable1, (intr_vp1_en |= L9_VBI_INTERRUPT_MASK));
		VPORT_L9B0_WrFL(cvd_intr1_enable1);
	}
	else
	{
		VPORT_L9B0_RdFL(cvd_intr1_enable1);
		intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_enable1);
		VPORT_L9B0_Wr(cvd_intr1_enable1, (intr_vp1_en &= ~L9_VBI_INTERRUPT_MASK));
		VPORT_L9B0_WrFL(cvd_intr1_enable1);

		TTX_SetInterruptClear_L9Bx();
	}

	return ret;
}


int TTX_ParsingVBIData_L9Bx(sHeaderData *data )
{
	int ret = 0;
	unsigned long middle_addr;
	int iHeaderPos;
	int i;

#if 0
	sHeaderPacket packet;
	sTTXPacket packet;
#endif
	int buffer_number = 0;

	VPORT_L9B0_RdFL(vbi_ctrl_002);
	VPORT_L9B0_Rd01(vbi_ctrl_002, reg_vbi_buffer_number, buffer_number);

	switch(buffer_number)
	{
		case 0:
			VPORT_L9B0_RdFL(vbi_ctrl_002);
			VPORT_L9B0_RdFL(vbi_ctrl_003);

			VPORT_L9B0_Rd01(vbi_ctrl_002, reg_vbi0_start_addr, data->start);
			VPORT_L9B0_Rd01(vbi_ctrl_003, reg_vbi0_end_addr, data->end);
			VPORT_L9B0_Rd01(vbi_ctrl_002, reg_vbi0_data_cnt, data->count);
			break;
		case 1:
			VPORT_L9B0_RdFL(vbi_ctrl_004);
			VPORT_L9B0_RdFL(vbi_ctrl_005);

			VPORT_L9B0_Rd01(vbi_ctrl_004, reg_vbi1_start_addr, data->start);
			VPORT_L9B0_Rd01(vbi_ctrl_005, reg_vbi1_end_addr, data->end);
			VPORT_L9B0_Rd01(vbi_ctrl_004, reg_vbi1_data_cnt, data->count);
			break;
		case 2:
			VPORT_L9B0_RdFL(vbi_ctrl_006);
			VPORT_L9B0_RdFL(vbi_ctrl_007);

			VPORT_L9B0_Rd01(vbi_ctrl_006, reg_vbi2_start_addr, data->start);
			VPORT_L9B0_Rd01(vbi_ctrl_007, reg_vbi2_end_addr, data->end);
			VPORT_L9B0_Rd01(vbi_ctrl_006, reg_vbi2_data_cnt, data->count);
			break;
		case 3:
			VPORT_L9B0_RdFL(vbi_ctrl_008);
			VPORT_L9B0_RdFL(vbi_ctrl_009);

			VPORT_L9B0_Rd01(vbi_ctrl_008, reg_vbi3_start_addr, data->start);
			VPORT_L9B0_Rd01(vbi_ctrl_009, reg_vbi3_end_addr, data->end);
			VPORT_L9B0_Rd01(vbi_ctrl_008, reg_vbi3_data_cnt, data->count);
		break;
	}
	//TTX_PRINT("TTX end %d start %d \n", data->end , data->start );

	if(data->count > 0x800)
	{
		TTX_PRINT("came too long packet [%d]\n", data->count);
		ret = -1;
	}
	else
	{
		unsigned int *uiData;
		data->data_num = 0;

		// all data copy to DDR. because our system can't access as BYTE
#if 0
		if( data->end > data->start )
			memcpy((void *)ucPacket , (void *)(gpRealRegVPORT_L9B0 + data->start*4) , sizeof(int)*(data->end - data->start + 1));
		else
		{
			middle_addr = 0x400 - data->start;
			memcpy((void *)ucPacket , (void *)(gpRealRegVPORT_L9B0 + data->start*4) , sizeof(int)*middle_addr );
			memcpy((void *)(ucPacket + middle_addr*4), (void *)(gpRealRegVPORT_L9B0) , sizeof(int)*(data->end + 1) );
		}
#else

//TTX_PRINT("start [%d] end [%d]\n", data->start , data->end);
		if( data->end > data->start )
		{
			for(i = 0; i < (data->end - data->start + 1) ; i++)
			{
				uiData = (unsigned int *)(gTTX_addr + (data->start + i)*4);

				*(ucPacket + i*4 + 0) = (unsigned char)( (*uiData>>24)&0xff );
				*(ucPacket + i*4 + 1) = (unsigned char)( (*uiData>>16)&0xff );
				*(ucPacket + i*4 + 2) = (unsigned char)( (*uiData>>8)&0xff );
				*(ucPacket + i*4 + 3) = (unsigned char)( (*uiData)&0xff );
			}
			//memcpy((void *)ucPacket , (void *)(gpRealRegVPORT_L9B0 + data->start*4) , sizeof(int)*(data->end - data->start + 1));

		}
		else
		{
			//110831 by dws. VBI Buffer reduced
			//middle_addr = 0x400 - data->start;
			middle_addr = 0x200 - data->start;

			for(i = 0; i < (middle_addr) ; i++)
			{
				uiData = (unsigned int *)(gTTX_addr + (data->start + i)*4);

				*(ucPacket + i*4 + 0) = (unsigned char)( (*uiData>>24)&0xff );
				*(ucPacket + i*4 + 1) = (unsigned char)( (*uiData>>16)&0xff );
				*(ucPacket + i*4 + 2) = (unsigned char)( (*uiData>>8)&0xff );
				*(ucPacket + i*4 + 3) = (unsigned char)( (*uiData)&0xff );
			}

			for(i = 0; i < (data->end + 1) ; i++)
			{
				uiData = (unsigned int *)(gTTX_addr + i*4);

				*(ucPacket + (i + middle_addr)*4 + 0) = (unsigned char)( (*uiData>>24)&0xff );
				*(ucPacket + (i + middle_addr)*4 + 1) = (unsigned char)( (*uiData>>16)&0xff );
				*(ucPacket + (i + middle_addr)*4 + 2) = (unsigned char)( (*uiData>>8)&0xff );
				*(ucPacket + (i + middle_addr)*4 + 3) = (unsigned char)( (*uiData)&0xff );
			}
		}

		iHeaderPos = 0;

		//TTX_PRINT(" parsing start %p\n" ,ucPacket);
		for(i=0;i<MAX_PACKET_NUM;i++)
		{
			//if( ( (*(ucPacket + iHeaderPos + 3)&0xf0) == 0x20 ) && ( *(ucPacket + iHeaderPos + 1) == 0xff) && (*(ucPacket+iHeaderPos+2) == 0xff))

			// seraching data position. and deliver the position to PutVBIData.
			if( ( *(ucPacket + iHeaderPos + 0) == 0x00) && ( *(ucPacket + iHeaderPos + 1) == 0xff) && (*(ucPacket+iHeaderPos+2) == 0xff))
			{
#if 0
			    printk("VBI DATA : %2x %2x %2x %2x ", *(ucPacket + iHeaderPos),*(ucPacket + iHeaderPos +1),*(ucPacket + iHeaderPos +2), *(ucPacket + iHeaderPos+3));
			    printk("%2x %2x %2x ", *(ucPacket + iHeaderPos+4),*(ucPacket + iHeaderPos +5),*(ucPacket + iHeaderPos + 6) );
				printk("Count : %2d => ", *(ucPacket + iHeaderPos + 4));
				for(y=0; y< *(ucPacket + iHeaderPos + 4); y++)
				{
					printk("[%3d]: %2x ",y, (*(ucPacket + iHeaderPos + 7 + y)));
				}
				if( *(ucPacket + iHeaderPos + 4) == 0x2a) printk(" TTX 625B\n");
				else printk(" NO TTX\n");
#endif

				if( ( *(ucPacket + iHeaderPos + 6) == 0x01) && ( *(ucPacket + iHeaderPos + 5) == 0x3e)) gTTXCountOfLine318++;
				else gTTXCountOfOtherLine++;
				ttx_54Mhz_flag = 0;
				data->data_start[data->data_num] = iHeaderPos + 7;
				data->data_end[data->data_num] = iHeaderPos + 7 + *(ucPacket + iHeaderPos + 4);
				data->data_num++;
				//TTX_PRINT("27Mhz data length %x , status %x\n", *(ucPacket + iHeaderPos + 4) , *(ucPacket + iHeaderPos + 3));
				iHeaderPos = iHeaderPos + 7 + *(ucPacket + iHeaderPos + 4);

			}
#ifdef ALLOW_54MHZ_TTX_MODE  //111025 by won.hur. Disabling code to prevent weird operation
							 //                   when preamble is miss-read on 27Mhz
			// This is for 54Mhz TTX block : preamble is changed to 0x0000FFFF
			else if( ( *(ucPacket + iHeaderPos + 0) == 0x00) && ( *(ucPacket + iHeaderPos + 1) == 0x00) && ( *(ucPacket + iHeaderPos + 2) == 0xff) && (*(ucPacket+iHeaderPos+3) == 0xff))
			{
				if( ( *(ucPacket + iHeaderPos + 6) == 0x01) && ( *(ucPacket + iHeaderPos + 5) == 0x3e)) gTTXCountOfLine318++;
				else gTTXCountOfOtherLine++;
				ttx_54Mhz_flag = 1;
				data->data_start[data->data_num] = iHeaderPos + 8;
				data->data_end[data->data_num] = iHeaderPos + 7 + *(ucPacket + iHeaderPos + 5);
				data->data_num++;
				//TTX_PRINT("54Mhz  data length %x , status %x\n", *(ucPacket + iHeaderPos + 5) , *(ucPacket + iHeaderPos + 4));
				iHeaderPos = iHeaderPos + 7 + *(ucPacket + iHeaderPos + 5);

			}
#endif
			else
			{
		//		TTX_PRINT(" 1:%x , 2:%x , 3:%x \n", (*(ucPacket + iHeaderPos + 3)&0xff), *(ucPacket + iHeaderPos + 1),*(ucPacket + iHeaderPos + 2) );
				iHeaderPos = iHeaderPos + 7 + *(ucPacket + iHeaderPos + 4);
			}
			//TTX_PRINT("data count %d , header %d\n", data->count , iHeaderPos);
			if( data->count <= iHeaderPos + 1) break;

		}

	}



#endif

	return ret;
}

int TTX_PutVBIData_L9Bx(sHeaderData *data)
{
	int ret = 0;
	int i;
	int offset = 3;
	unsigned long ptr = 0;
	unsigned int data_size = 0;
	unsigned int temp_type = 0;
	unsigned int temp_line = 0;

	static sWSSBufInform	wss_buf[WSS_BUF_SIZE] = {{0,}, };
	UINT32	curr_wss_int_time;
	int wss_num;

	if (ttx_54Mhz_flag)
		offset++;
#if 0
	unsigned long middle_addr;

	if( data->end > data->start )
		memcpy((void *)data->addr , (void *)(gpRealRegVPORT_L9B0 + data->start*4) , sizeof(int)*(data->end - data->start + 1));
	else
	{
		middle_addr = 0x400 - data->start;
		memcpy((void *)data->addr , (void *)(gpRealRegVPORT_L9B0 + data->start*4) , middle_addr*4 );
		memcpy((void *)(data->addr + middle_addr*4), (void *)(gpRealRegVPORT_L9B0) , (data->end + 1)*4 );
	}
#else
//TTX_PRINT("save start\n");
	for(i = 0 ; i < data->data_num ; i++)
	{

		// 111026 won.hur : Since VBIL26 register is initially writen to be 0x60(Related to a DQMS issue, where ttx data on line 318 couldn't be read),
		// 					We needed to add some filters as to block garbage data going up to the circular buffer on the upper stage.
		// 					So before sending the data to the circular buffer, data are filtered whether they are on the VBI range.
		temp_line = VBI_TTX_GetVBIDataLineCount((void *)(ucPacket + data->data_start[i] - DATA_OFFSET));

		if(((temp_line >= VBI_DATA_ODD_START_LINE)&&(temp_line <= VBI_DATA_ODD_END_LINE))||((temp_line >= VBI_DATA_EVEN_START_LINE)&&(temp_line <= VBI_DATA_EVEN_END_LINE)))
		{
			// by wonsik.do WSS and VPS are contained only in odd filed.
			data->type = *(ucPacket+offset) & 0x0F;
			//data->type = *(ucPacket+offset) & 0x0E;

			VBI_TTX_GetDataAddr(data); // This would increase the circular buffer pointer!!

			/*
			if(data->type != 6)	// debug mode
			{
				TTX_PRINT("type[%d] type[%d] end[%d] start[%d] \n", data->type , *(ucPacket+offset) ,data->data_end[i] , data->data_start[i] );

			}
			*/

			data_size = data->data_end[i] - data->data_start[i];
			temp_type = data->type;

			switch(temp_type)
			{
				case 0x6: // teletext
				case 0x7:
					ptr = 6;
				break;

				//case 0x8:	// WSS
				case 0x9:	// WSS
					ptr = 0;

					curr_wss_int_time = jiffies_to_msecs(jiffies);	// get current time

					//TTX_PRINT("WSS: byte[0x%x] data1[0x%x] data2[0x%x] line[%d] status[0x%x] time_diff[%d]\n" , data->data_end[i]-data->data_start[i] , *(ucPacket + data->data_start[i]) , *(ucPacket + data->data_start[i]+1), *(ucPacket + data->data_start[i]-2), *(ucPacket + data->data_start[i]-4), (curr_wss_int_time - wss_buf[0].wss_int_time));
					if(*(ucPacket +  data->data_start[i]-DATA_OFFSET) != WSS_DATA_LINE)
					{
						continue;
					}

					for(wss_num=1;wss_num<WSS_BUF_SIZE;wss_num++)
					{
						wss_buf[WSS_BUF_SIZE - wss_num].wss_data 		= wss_buf[WSS_BUF_SIZE -wss_num -1].wss_data;
						wss_buf[WSS_BUF_SIZE - wss_num].wss_int_time 	= wss_buf[WSS_BUF_SIZE -wss_num -1].wss_int_time;
					}

					//memcpy( &wss_buf[0].wss_data,  (ucPacket + data->data_start[i]), sizeof(unsigned short));	// copy data1/2 to wss_buf[0]
					wss_buf[0].wss_data =  ((*(ucPacket + data->data_start[i]+1)& 0xFF)<<8) | *(ucPacket + data->data_start[i]);
					wss_buf[0].wss_int_time = curr_wss_int_time;

					//DQMS 1109-04120 : Sometimes WSS data is missing on ATV 5CH.
					if( (wss_buf[WSS_BUF_SIZE - 1].wss_data	!= wss_buf[WSS_BUF_SIZE - 2].wss_data) || (wss_buf[WSS_BUF_SIZE - 2].wss_data	!= wss_buf[WSS_BUF_SIZE - 3].wss_data) || (wss_buf[WSS_BUF_SIZE - 3].wss_data	!= wss_buf[WSS_BUF_SIZE - 4].wss_data) || (wss_buf[WSS_BUF_SIZE - 4].wss_data	!= wss_buf[0].wss_data)  || ( (wss_buf[0].wss_int_time - wss_buf[WSS_BUF_SIZE -1].wss_int_time) > 600 ))
					{
						//TTX_PRINT("garbage wss data !!!\n");
						//do not copy wss data
						data->addr = 0;
						break;
					}
					/*
					for(wss_num=1;wss_num<WSS_BUF_SIZE;wss_num++)
					{
						if( (wss_buf[WSS_BUF_SIZE - wss_num].wss_data	!= wss_buf[WSS_BUF_SIZE -wss_num -1].wss_data) || ( (wss_buf[WSS_BUF_SIZE - wss_num -1].wss_int_time - wss_buf[WSS_BUF_SIZE -wss_num].wss_int_time) > 50 ))
						{
							//TTX_PRINT("garbage wss data !!!\n");
							//do not copy wss data
							data->addr = 0;
							break;
						}
					}
					*/

					if(data_size > 0xd) data_size = 0xd;
				break;
				//case 0xc:	// VPS
				case 0xd:	// VPS
					ptr = 2;
					//TTX_PRINT("VPS: byte[0x%x] data9[0x%x] data10[0x%x] data11[0x%x] data12[0x%x] data13[0x%x] line[%d] status[0x%x] \n" , data->data_end[i]-data->data_start[i] , *(ucPacket + data->data_start[i]+8), *(ucPacket + data->data_start[i]+9), *(ucPacket + data->data_start[i]+10), *(ucPacket + data->data_start[i]+11), *(ucPacket + data->data_start[i]+12), *(ucPacket + data->data_start[i]-2), *(ucPacket + data->data_start[i]-4));
				//TTX_PRINT("VPS: [%x] [%x]  [%d] [%d]\n" , data->addr ,  data->data_end[i]-data->data_start[i] , *(ucPacket + data->data_start[i]) , *(ucPacket + data->data_start[i]+1));

					if(*(ucPacket +  data->data_start[i]-DATA_OFFSET) != VPS_DATA_LINE)
					{
						continue;
					}
					if(data_size > 0xd) data_size = 0xd;

				break;
				default:
					ptr = 0;
				break;

			}

			if(data->addr != 0)
			{
				memcpy( (void *)(data->addr + ptr) , (void *)(ucPacket + data->data_start[i]) , data_size);
			}

		}
		//else TTX_PRINT("VBI DATA NOT IN VBI RANGE!, LINE IS : [%d]\n", temp_line);

		offset = data->data_end[i] + 3;

		if (ttx_54Mhz_flag)
			offset++;
		//TTX_PRINT("offset [%d] end [%d]\n" , offset , data->data_end[i]);

	}
#endif

	return ret;

}

int TTX_Enable_VPS_Slicer_L9Bx(BOOLEAN Enable)
{
	VPORT_L9B0_RdFL(vbi_009);

	if(Enable)
		VPORT_L9B0_Wr01(vbi_009, reg_vbil16, 0x63);	// Enable VPS Slicing on Line #16
	else
		VPORT_L9B0_Wr01(vbi_009, reg_vbil16, 0x66);	// Enable TTX Slicing on Line #16

	VPORT_L9B0_WrFL(vbi_009);

	return 0;
}

int TTX_SetVBILPF_L9Bx(int onoff)
{
	int ret = 0;

	VPORT_L9B0_RdFL(vbi_005);

	if(onoff)
	{
		VPORT_L9B0_Wr(vbi_005, 0x00000001);
	}
	else
	{
		VPORT_L9B0_Wr(vbi_005, 0x00000000);
	}

	VPORT_L9B0_WrFL(vbi_005);

	return ret;
}

int TTX_CheckOnLine318_L9Bx(int mode)
{
	int ret = 0;

	if(mode)
	{
		//TTX_PRINT("Reset checking on line 318.\n");
		gTTXCountOfLine318 = 0;
		gTTXCountOfOtherLine = 0;
		ret = 1;
	}
	else
	{
		//TTX_PRINT("Count of line 318 vs Other is [%d]/[%d]\n", gTTXCountOfLine318, gTTXCountOfOtherLine);

		if(gTTXCountOfLine318 > 10)
		{
			if(gTTXCountOfOtherLine > 10) ret = 4;   // Case when data is also in line 318.
		    else ret = 3; 							 // Case when data is only in line 318.
		}
		else ret = 2;	// Case when data on line 318 does not exist...
	}
	return ret;
}

int TTX_SetTypeLine318_L9Bx(int onoff)
{

	int ret = 0;

	VPORT_L9B0_RdFL(vbi_012);

	if(onoff)
	{
		//TTX_PRINT("Detection for line 318 is ON.\n");
		VPORT_L9B0_Wr(vbi_012, 0x00000060);
	}
	else
	{
		//TTX_PRINT("Detection for line 318 is off.\n");
		VPORT_L9B0_Wr(vbi_012, 0x00000000);
	}

	VPORT_L9B0_WrFL(vbi_012);

	return ret;
}

int TTX_Set_TT_Slicer_Mode_L9Bx(unsigned int mode)
{

	int ret = 0;

	TTX_PRINT("%s enterd [%d]\n", __func__, mode);

	VPORT_L9B0_RdFL(vbi_013);

	if(mode < 4)
	{
		VPORT_L9B0_Wr01(vbi_013, reg_vbi_tt_slicer_mode, mode);
		VPORT_L9B0_WrFL(vbi_013);
		ret = 0;
	}
	else
	{
		ret = -1;
	}

	return ret;
}


#ifdef	KDRV_CONFIG_PM

int TTX_RunSuspend_L9Bx(void)
{
	// param will be saved automatically....
	return 0;
}

int TTX_RunResume_L9Bx(void)
{
	TTX_SetInterrupt_L9Bx(guiPmIntStatus);
	TTX_SetInputFormat_L9Bx(guiPmTtxModeStatus);
	return 0;
}

#endif

/** @} */

