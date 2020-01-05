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
 *	CC module control Drivers linux module
 *
 *  author      won.hur (won.hur@lge.com)
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg1150_CC
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
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include "vbi_kapi.h"

#include "vbi_module.h"
#include "vbi_hw.h"
#include "vbi_drv.h"
#include "os_util.h"

#include "./../../afe/l9/vport_reg_l9b0.h"
#include "./../../afe/cvd_hw.h"

#ifdef	_WITHOUT_AFE_
//volatile VPORT_L9B0_Reg_T *gVportReg;	// <- prototype from AFE. because the
					//	registers for ADC, CVD, HDMI are in AFE modules
#else	//_WITHOUT_ADC_
//extern volatile VPORT_L9B0_RegBx_T *gVportRegBx;
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define DEBUG_PRINT_INCOMING_CC_PACKET 0

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	VBI_OFF	0
#define	VBI_ON	1

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/// shadow register
extern volatile VPORT_L9B0_REG_T __iomem *gpRegVPORT_L9B0;
// real
extern volatile VPORT_L9B0_REG_T __iomem *gpRealRegVPORT_L9B0;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static volatile unsigned long gCC_addr;
/*========================================================================================
	Implementation Group
========================================================================================*/
//cvd register
int CC_L9B0_HWInitialize(void)
{
	int ret = 0;

	// TODO:dws
	//gCC_addr  should be defined HERE !
	gCC_addr = (volatile unsigned long)ioremap(gstRegCfgVBI->vbi_register_base , gstRegCfgVBI->vbi_register_size);
	//gpRealRegVPORT_L9B0 = (volatile VPORT_L9B0_REG_T __iomem *)ioremap(CC_L9A0_REG_MEMORY_START , CC_L9A0_REG_MEMORY_SIZE);
	//gpRegVPORT_L9B0 = (volatile VPORT_L9B0_REG_T __iomem *)kmalloc(sizeof(VPORT_L9B0_REG_T), GFP_ATOMIC);

#ifdef	KDRV_CONFIG_PM
	gCcPmData = (S_CC_PM_DATA	*)kmalloc(sizeof(S_CC_PM_DATA) , GFP_KERNEL);
    if(gCcPmData == NULL) CC_PRINT("%s gCcPmData is NULL!", __func__);
	gCcPmData->uiPmCcIntStatus = 0;
	gCcPmData->ePmCcModeStatus = 0;
#endif

	// Set to Big Endian Mode (From B0 Revision, default endian is little endian)
	// Need to modify kdriver to use little endian.
#if 0
	gVportRegBx->vbi_ctrl_001.reg_vbi_little_endian = 0;
#else
	// memory allocation for local shadow register
	// gpRegVPORT = (VPORT_L9A0_RegBx_T *)kmalloc(sizeof(VPORT_RegBx_T), GFP_KERNEL);
	VPORT_L9B0_RdFL(vbi_ctrl_001);
	VPORT_L9B0_Wr01(vbi_ctrl_001, reg_vbi_little_endian, 1);
	VPORT_L9B0_WrFL(vbi_ctrl_001);
#endif


	//111128 wonsik.do : enabled one bit error ignore from L9B0 revision.

	if( lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) )
	{
		VPORT_L9B0_RdFL(vbi_004);
		VPORT_L9B0_Wr01(vbi_004, reg_vbi_st_err_ignored, 1);
		VPORT_L9B0_WrFL(vbi_004);
	}

	CC_PRINT("%s done\n", __func__);

	return ret;
}

int CC_L9B0_HWUninitialize(void)
{
	int ret = 0;

//	iounmap((void *)gpRealRegVPORT_L9A0);
	iounmap((void *)gCC_addr);

	return ret;
}

int CC_L9B0_SetInputFormat(eVBIDataType type)
{
	int ret = 0;

	CC_PRINT("%s input : %d\n" , __func__ , type);
#ifdef	kdrv_config_pm
	gccpmdata->epmccmodestatus = type;
#endif
	switch(type)
	{
		case eDisable:
#if 0
			gVportRegBx->vbi_004.reg_vbi_en = VBI_OFF;
#else
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_OFF);
			VPORT_L9B0_WrFL(vbi_004);
#endif

		break;
		case eClosedCaptionUS:
		case eClosedCaptionEURO:
#if 0
			value = 0;
			memcpy((void *)&gvportregbx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gvportregbx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gvportregbx->vbi_009 , (void *)&value , sizeof(int) );
			value = 0x11;
			memcpy((void *)&gvportregbx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0xE736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & reg_caption_start
			value = 0x54548282;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			value = 0x35A012DB;
			memcpy((void *)&gVportRegBx->vbi_014 , (void *)&value , sizeof(int) );
			value = 0x2066159a;
			memcpy((void *)&gVportRegBx->vbi_015 , (void *)&value , sizeof(int) );
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x25;
			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
#else
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_RdFL(iris_039);

			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);

			//111130 wonsik.do : disable vbi muxout to prevent vbi data violate video data.
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_muxout, 0);
			VPORT_L9B0_Wr(vbi_006, 0xE736);
			VPORT_L9B0_Wr(vbi_007, 0);
			VPORT_L9B0_Wr(vbi_008, 0);
			VPORT_L9B0_Wr(vbi_009, 0);
			//110929 : dws add Line 18, 22 for CC Slicing
			//111014 : dws add Line 24, 25 for CC Slicing(PAL line 21,22 can be inserted on line 24, 25 on NTSC system)
			//111014 : dws removed Line 24, 25 (this is no use)
			VPORT_L9B0_Wr(vbi_010, 0x11000011);
			//VPORT_L9B0_Wr(vbi_011, 0x11001111);
			VPORT_L9B0_Wr(vbi_011, 0x11000000);
			//VPORT_L9B0_Wr(vbi_010, 0x11);
			//VPORT_L9B0_Wr(vbi_011, 0);
			VPORT_L9B0_Wr(vbi_014, 0x35A012DB);
			VPORT_L9B0_Wr(vbi_015, 0x2066159A);
			//VPORT_L9B0_Wr(vbi_020, 0x54548282);
			VPORT_L9B0_Wr(vbi_020, 0x58548282);    // 2011.12.10 won.hur : Changed CC find start h-sync value
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);

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
			VPORT_L9B0_WrFL(vbi_016);
			VPORT_L9B0_WrFL(iris_039);
#endif

		break;
		case eVPS:
#if 0
			//gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_009 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0x2736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			value = 0x54545A82;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			gVportRegBx->vbi_014.reg_teletext_dto = 0x12DB;
			gVportRegBx->vbi_015.reg_wss625_dto = 0x2066;
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x25;
			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
#else
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_Wr(vbi_007, 0);
			VPORT_L9B0_WrFL(vbi_007);

			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_Wr(vbi_008, 0);
			VPORT_L9B0_WrFL(vbi_008);

			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_Wr(vbi_009, 0);
			VPORT_L9B0_WrFL(vbi_009);

			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_Wr(vbi_010, 0);
			VPORT_L9B0_WrFL(vbi_010);

			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_Wr(vbi_011, 0);
			VPORT_L9B0_WrFL(vbi_011);

			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			VPORT_L9B0_WrFL(vbi_006);

			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_WrFL(vbi_020);

			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			VPORT_L9B0_WrFL(vbi_014);

			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			VPORT_L9B0_WrFL(vbi_015);

			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_WrFL(vbi_016);

			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);
			VPORT_L9B0_WrFL(iris_039);

			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_WrFL(vbi_004);
#endif
		break;

		case eTTX625A:
#if 0
			//gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
			value = 0x55555555;
			memcpy((void *)&gVportRegBx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_009 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0x2736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			value = 0x54545A82;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			gVportRegBx->vbi_014.reg_teletext_dto = 0x12DB;
			gVportRegBx->vbi_015.reg_wss625_dto = 0x2066;
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x25;
			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
#else
			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_Wr(vbi_007, 0x55555555);
			VPORT_L9B0_WrFL(vbi_007);

			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_Wr(vbi_008, 0x55555555);
			VPORT_L9B0_WrFL(vbi_008);

			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_Wr(vbi_009, 0x55555555);
			VPORT_L9B0_WrFL(vbi_009);

			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_Wr(vbi_010, 0x55555555);
			VPORT_L9B0_WrFL(vbi_010);

			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_Wr(vbi_011, 0);
			VPORT_L9B0_WrFL(vbi_011);

			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			VPORT_L9B0_WrFL(vbi_006);

			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_WrFL(vbi_020);

			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			VPORT_L9B0_WrFL(vbi_014);

			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			VPORT_L9B0_WrFL(vbi_015);

			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_WrFL(vbi_016);

			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);
			VPORT_L9B0_WrFL(iris_039);

			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_WrFL(vbi_004);
#endif
		break;
		case eTTX625B:


		break;

		case eTTX625C:

		break;
		case eTTX625D:

		break;
		case eTTX525B:
#if 0
			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
			value = 0x99999999;
			memcpy((void *)&gVportRegBx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_009 , (void *)&value , sizeof(int) );
			value = 0x99999999;
			memcpy((void *)&gVportRegBx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0x2736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			value = 0x54545A82;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			gVportRegBx->vbi_014.reg_teletext_dto = 0x12DB;
			gVportRegBx->vbi_015.reg_wss625_dto = 0x2066;
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x25;
#else
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_WrFL(vbi_004);

			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_Wr(vbi_007, 0x99999999);
			VPORT_L9B0_WrFL(vbi_007);

			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_Wr(vbi_008, 0x99999999);
			VPORT_L9B0_WrFL(vbi_008);

			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_Wr(vbi_009, 0x99999999);
			VPORT_L9B0_WrFL(vbi_009);

			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_Wr(vbi_010, 0x99999999);
			VPORT_L9B0_WrFL(vbi_010);

			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_Wr(vbi_011, 0);
			VPORT_L9B0_WrFL(vbi_011);

			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_Wr(vbi_006, 0x2736);
			VPORT_L9B0_WrFL(vbi_006);

			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_WrFL(vbi_020);

			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			VPORT_L9B0_WrFL(vbi_014);

			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			VPORT_L9B0_WrFL(vbi_015);

			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_WrFL(vbi_016);

			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x25);
			VPORT_L9B0_WrFL(iris_039);

#endif
		break;

		case eTTX525C:
#if 0

			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
			value = 0xAAAAAAAA;
			memcpy((void *)&gVportRegBx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_009 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0xE736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			value = 0x54546482;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			gVportRegBx->vbi_014.reg_teletext_dto = 0x12DB;
			gVportRegBx->vbi_015.reg_wss625_dto = 0x2066;
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x23;
#else
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_WrFL(vbi_004);

			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_Wr(vbi_007, 0xAAAAAAAA);
			VPORT_L9B0_WrFL(vbi_007);

			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_Wr(vbi_008, 0xAAAAAAAA);
			VPORT_L9B0_WrFL(vbi_008);

			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_Wr(vbi_009, 0xAAAAAAAA);
			VPORT_L9B0_WrFL(vbi_009);

			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_Wr(vbi_010, 0xAAAAAAAA);
			VPORT_L9B0_WrFL(vbi_010);

			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_Wr(vbi_011, 0);
			VPORT_L9B0_WrFL(vbi_011);

			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_Wr(vbi_006, 0xE736);
			VPORT_L9B0_WrFL(vbi_006);

			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_Wr(vbi_020, 0x54546482);
			VPORT_L9B0_WrFL(vbi_020);

			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			VPORT_L9B0_WrFL(vbi_014);

			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			VPORT_L9B0_WrFL(vbi_015);

			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_WrFL(vbi_016);

			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x23);
			VPORT_L9B0_WrFL(iris_039);
#endif
		break;
		case eTTX525D:
#if 0
			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
			value = 0xBBBBBBBB;
			memcpy((void *)&gVportRegBx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_009 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0xA736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			value = 0x54545A82;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			gVportRegBx->vbi_014.reg_teletext_dto = 0x12DB;
			gVportRegBx->vbi_015.reg_wss625_dto = 0x2066;
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x23;
#else
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_WrFL(vbi_004);

			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_Wr(vbi_007, 0xBBBBBBBB);
			VPORT_L9B0_WrFL(vbi_007);

			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_Wr(vbi_008, 0xBBBBBBBB);
			VPORT_L9B0_WrFL(vbi_008);

			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_Wr(vbi_009, 0xBBBBBBBB);
			VPORT_L9B0_WrFL(vbi_009);

			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_Wr(vbi_010, 0xBBBBBBBB);
			VPORT_L9B0_WrFL(vbi_010);

			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_Wr(vbi_011, 0);
			VPORT_L9B0_WrFL(vbi_011);

			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_Wr(vbi_006, 0xA736);
			VPORT_L9B0_WrFL(vbi_006);

			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_Wr(vbi_020, 0x54545A82);
			VPORT_L9B0_WrFL(vbi_020);

			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			VPORT_L9B0_WrFL(vbi_014);

			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x2066);
			VPORT_L9B0_WrFL(vbi_015);

			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_WrFL(vbi_016);

			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x23);
			VPORT_L9B0_WrFL(iris_039);

#endif
		break;

		case eWSS625	:
#if 0
			gVportRegBx->vbi_004.reg_vbi_en = VBI_ON;
			value = 0x0;
			memcpy((void *)&gVportRegBx->vbi_007 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_008 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_009 , (void *)&value , sizeof(int) );
			memcpy((void *)&gVportRegBx->vbi_010 , (void *)&value , sizeof(int) );
			value = 0x00CC0000;;
			memcpy((void *)&gVportRegBx->vbi_011 , (void *)&value , sizeof(int) );

			// vbi_data_hlvl & start_code
			value = 0xE736;
			memcpy((void *)&gVportRegBx->vbi_006 , (void *)&value , sizeof(int) );
			// reg_vps_start & reg_teletext_start & reg_wss625_start & vbi_020
			value = 0x54828282;
			memcpy((void *)&gVportRegBx->vbi_020 , (void *)&value , sizeof(int) );

			gVportRegBx->vbi_014.reg_teletext_dto = 0x12DB;
			gVportRegBx->vbi_015.reg_wss625_dto = 0x1599;
			gVportRegBx->vbi_016.reg_wss625_frame_start = 0x2;
			gVportRegBx->iris_039.reg_vsync_vbi_max = 0x23;
#else
			VPORT_L9B0_RdFL(vbi_004);
			VPORT_L9B0_Wr01(vbi_004, reg_vbi_en, VBI_ON);
			VPORT_L9B0_WrFL(vbi_004);

			VPORT_L9B0_RdFL(vbi_007);
			VPORT_L9B0_Wr(vbi_007, 0);
			VPORT_L9B0_WrFL(vbi_007);

			VPORT_L9B0_RdFL(vbi_008);
			VPORT_L9B0_Wr(vbi_008, 0);
			VPORT_L9B0_WrFL(vbi_008);

			VPORT_L9B0_RdFL(vbi_009);
			VPORT_L9B0_Wr(vbi_009, 0);
			VPORT_L9B0_WrFL(vbi_009);

			VPORT_L9B0_RdFL(vbi_010);
			VPORT_L9B0_Wr(vbi_010, 0);
			VPORT_L9B0_WrFL(vbi_010);

			VPORT_L9B0_RdFL(vbi_011);
			VPORT_L9B0_Wr(vbi_011, 0x00CC0000);
			VPORT_L9B0_WrFL(vbi_011);

			VPORT_L9B0_RdFL(vbi_006);
			VPORT_L9B0_Wr(vbi_006, 0xE736);
			VPORT_L9B0_WrFL(vbi_006);

			VPORT_L9B0_RdFL(vbi_020);
			VPORT_L9B0_Wr(vbi_020, 0x54828282);
			VPORT_L9B0_WrFL(vbi_020);

			VPORT_L9B0_RdFL(vbi_014);
			VPORT_L9B0_Wr01(vbi_014, reg_teletext_dto, 0x12DB);
			VPORT_L9B0_WrFL(vbi_014);

			VPORT_L9B0_RdFL(vbi_015);
			VPORT_L9B0_Wr01(vbi_015, reg_wss625_dto, 0x1599);
			VPORT_L9B0_WrFL(vbi_015);

			VPORT_L9B0_RdFL(vbi_016);
			VPORT_L9B0_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			VPORT_L9B0_WrFL(vbi_016);

			VPORT_L9B0_RdFL(iris_039);
			VPORT_L9B0_Wr01(iris_039, reg_vsync_vbi_max, 0x23);
			VPORT_L9B0_WrFL(iris_039);
#endif
		break;
		case eWSSJ	:

		break;
		default:

		break;
	}

	CC_PRINT("%s done\n", __func__);
	return ret;
}


int CC_L9B0_SetInterruptClear(void)
{
	int ret = 0;
	UINT32 intr_vp1_en;

#if 0
	gVportRegBx->cvd_intr1_clear0.cvd_intr1_clear0 |= (1<<15);	// interrupt clear
	gVportRegBx->cvd_intr1_clear0.cvd_intr1_clear0 &= ~(1<<15);
#else
	VPORT_L9B0_RdFL(cvd_intr1_clear0);
	intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_clear0);
	VPORT_L9B0_Wr(cvd_intr1_clear0, (intr_vp1_en |= (1<<15)));
	VPORT_L9B0_WrFL(cvd_intr1_clear0);

	VPORT_L9B0_RdFL(cvd_intr1_clear0);
	intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_clear0);
	VPORT_L9B0_Wr(cvd_intr1_clear0, (intr_vp1_en &= ~(1<<15)));
	VPORT_L9B0_WrFL(cvd_intr1_clear0);
#endif

	return ret;
}


int CC_L9B0_SetInterrupt(int on_off)
{
	int ret = 0;
	UINT32 intr_vp1_en;

#ifdef	KDRV_CONFIG_PM
	gCcPmData->uiPmCcIntStatus = on_off;
#endif
	if(on_off)
	{

		VPORT_L9B0_RdFL(cvd_intr1_enable1);
		intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_enable1);
		VPORT_L9B0_Wr(cvd_intr1_enable1, (intr_vp1_en |= L9_VBI_INTERRUPT_MASK));
		VPORT_L9B0_WrFL(cvd_intr1_enable1);

	}
	else{

		VPORT_L9B0_RdFL(cvd_intr1_enable1);
		intr_vp1_en = VPORT_L9B0_Rd(cvd_intr1_enable1);
		VPORT_L9B0_Wr(cvd_intr1_enable1, (intr_vp1_en &= ~L9_VBI_INTERRUPT_MASK));
		VPORT_L9B0_WrFL(cvd_intr1_enable1);

		VBI_CC_SetInterruptClear();
	}

	return ret;

}


int CC_L9B0_ParsingVBIData(unsigned int *packet_array)
{
	int ret = 0;
	unsigned int start, end, count;
	sCloseCaption data[6];	// 5->6 Added to prevent segmentation fault
	sCloseCaption temp_data;
	unsigned long addr;
	int buffer_number = 0;
	unsigned int packet_count;
	unsigned int valid_packet_count;
	unsigned int start_inc, first_bytes, second_bytes;
	int loop_count;
	int valid_data_flag;
	int i;

	int found_preamble;
	int found_preamble_pointer;
	int sent_data_count;


	start = 0;
	end = 0;
	count = 0;

	VPORT_L9B0_RdFL(vbi_ctrl_002);
	VPORT_L9B0_Rd01(vbi_ctrl_002, reg_vbi_buffer_number, buffer_number);

	switch(buffer_number)
	{
		case 0:
			VPORT_L9B0_RdFL(vbi_ctrl_002);
			VPORT_L9B0_RdFL(vbi_ctrl_003);

			VPORT_L9B0_Rd01(vbi_ctrl_002, reg_vbi0_start_addr, start);
			VPORT_L9B0_Rd01(vbi_ctrl_003, reg_vbi0_end_addr, end);
			VPORT_L9B0_Rd01(vbi_ctrl_002, reg_vbi0_data_cnt, count);

			break;
		case 1:
			VPORT_L9B0_RdFL(vbi_ctrl_004);
			VPORT_L9B0_RdFL(vbi_ctrl_005);

			VPORT_L9B0_Rd01(vbi_ctrl_004, reg_vbi1_start_addr, start);
			VPORT_L9B0_Rd01(vbi_ctrl_005, reg_vbi1_end_addr, end);
			VPORT_L9B0_Rd01(vbi_ctrl_004, reg_vbi1_data_cnt, count);

			break;
		case 2:
			VPORT_L9B0_RdFL(vbi_ctrl_006);
			VPORT_L9B0_RdFL(vbi_ctrl_007);

			VPORT_L9B0_Rd01(vbi_ctrl_006, reg_vbi2_start_addr, start);
			VPORT_L9B0_Rd01(vbi_ctrl_007, reg_vbi2_end_addr, end);
			VPORT_L9B0_Rd01(vbi_ctrl_006, reg_vbi2_data_cnt, count);

			break;
		case 3:
			VPORT_L9B0_RdFL(vbi_ctrl_008);
			VPORT_L9B0_RdFL(vbi_ctrl_009);

			VPORT_L9B0_Rd01(vbi_ctrl_008, reg_vbi3_start_addr, start);
			VPORT_L9B0_Rd01(vbi_ctrl_009, reg_vbi3_end_addr, end);
			VPORT_L9B0_Rd01(vbi_ctrl_008, reg_vbi3_data_cnt, count);

			break;
		default:
			ret = -1;
			return ret;
			break;
	}


	packet_count = count /9;
	valid_packet_count = 0;
	valid_data_flag = 0;

	found_preamble = 0;
	found_preamble_pointer =0;
	sent_data_count = -1;

	if(count%9)
		packet_count++;

	if(packet_count <= 5)
	{
		start_inc = start * 4;

		for(loop_count = 0;loop_count < packet_count;loop_count ++)
		{
			if( (start < gstRegCfgVBI->vbi_register_size) && (end < gstRegCfgVBI->vbi_register_size) /*&& (count <= 4*5)*/ )
			{
				valid_data_flag = 1;
				if( ((gstRegCfgVBI->vbi_register_size>>2)*4 - start_inc) < 9)
				{

					first_bytes = ((gstRegCfgVBI->vbi_register_size>>2)*4 - start_inc);
					second_bytes = 9 - first_bytes;

					addr = (unsigned long)&data[valid_packet_count];

					memcpy((void *)addr , (void *)(gCC_addr + start_inc ) , first_bytes );
					memcpy((void *)(addr + first_bytes), (void *)(gCC_addr) ,second_bytes );
#if DEBUG_PRINT_INCOMING_CC_PACKET
					printk(" %4d %4d %4d", start, end, count);
					for(i=0; i<first_bytes; i++)printk(" %2x", (unsigned char )(*(unsigned int *)(gCC_addr + start_inc + i)));
					for(i=0; i<second_bytes; i++) printk(" %2x", (unsigned char )(*(unsigned int *)(gCC_addr + i)));
					printk("\n");
#endif
					valid_packet_count++;
					start_inc = second_bytes;
				}
				else
				{
					memcpy((void *)&data[valid_packet_count], (void *)(gCC_addr + start_inc ) , 9);
#if DEBUG_PRINT_INCOMING_CC_PACKET
					printk("CC_MESSAGE= %4d %4d %4d", start, end, count);
					for(i=0; i<9; i++) printk(" %2x",(unsigned char )(*(unsigned int *)(gCC_addr + start_inc + i)));
					printk("\n");
#endif
					valid_packet_count++;
					start_inc += 9;
				}
			}
			else
			{
				CC_PRINT("ERROR!!! start[%x], end[%x], \n" ,start, end);
				valid_data_flag = 0;
			}
		}

		for(loop_count = 0;loop_count < valid_packet_count; loop_count++)
		{
			if((count%9)&&(count >9))
			{
				memcpy((void *)&temp_data, (void *)&data[loop_count], 9);
				if(found_preamble == 0)
				{
					for(i=0; i<9; i++)
					{
						if(found_preamble == 0)
						{
				 			if((*((unsigned char *)&temp_data+i)== CC_VBI_PREAMBLE_0)&&\
				 			(*((unsigned char *)&temp_data+i+1)== CC_VBI_PREAMBLE_1)&&\
			       			(*((unsigned char *)&temp_data+i+2)== CC_VBI_PREAMBLE_2)) found_preamble++;
						}
						else if(found_preamble == 1)
						{
				 			if((*((unsigned char *)&temp_data+i)== CC_VBI_PREAMBLE_0)&&\
				 			(*((unsigned char *)&temp_data+i+1)== CC_VBI_PREAMBLE_1)&&\
			       			(*((unsigned char *)&temp_data+i+2)== CC_VBI_PREAMBLE_2))
							{
								found_preamble++;
								found_preamble_pointer = i;
							}
							else if(i == 7)
							{
								if((*((unsigned char *)&temp_data+i)== CC_VBI_PREAMBLE_0)&&\
				 				(*((unsigned char *)&temp_data+i+1)== CC_VBI_PREAMBLE_1)) found_preamble = 3;

							}
							else if(i == 8)
							{
								if(*((unsigned char *)&temp_data+i)== CC_VBI_PREAMBLE_0) found_preamble = 4;
							}
						}
					}

					if(found_preamble == 2)
					{
						memcpy((unsigned char *)&data[loop_count], ((unsigned char *)&temp_data + found_preamble_pointer), (9-found_preamble_pointer));
						memcpy(((unsigned char *)&data[loop_count]+9-found_preamble_pointer), (unsigned char *)(&data[loop_count+1]), found_preamble_pointer);

						if( ((*((unsigned char *)&data[loop_count])== CC_VBI_PREAMBLE_0)&&\
		    		 	(*((unsigned char *)&data[loop_count]+1)== CC_VBI_PREAMBLE_1)&&\
		      	     	(*((unsigned char *)&data[loop_count]+2)== CC_VBI_PREAMBLE_2))&&(valid_data_flag >0))
						{
							sent_data_count++;
							packet_array[sent_data_count] = ((data[loop_count].LineCount & 0x3FF)<<22)|((data[loop_count].Status & 0x0F)<<16)|(data[loop_count].data1 << 8)|data[loop_count].data0;
						}
					}
				}
				else if(found_preamble == 2)
				{
					memcpy((unsigned char *)&data[loop_count], ((unsigned char *)&temp_data + found_preamble_pointer), (9-found_preamble_pointer));
					memcpy(((unsigned char *)&data[loop_count]+9-found_preamble_pointer), (unsigned char *)(&data[loop_count+1]), found_preamble_pointer);
					if( ((*((unsigned char *)&data[loop_count])== CC_VBI_PREAMBLE_0)&&\
		    	 	(*((unsigned char *)&data[loop_count]+1)== CC_VBI_PREAMBLE_1)&&\
		          	(*((unsigned char *)&data[loop_count]+2)== CC_VBI_PREAMBLE_2))&&(valid_data_flag >0))
					{
						sent_data_count++;
						packet_array[sent_data_count] = ((data[loop_count].LineCount & 0x3FF)<<22)|((data[loop_count].Status & 0x0F)<<16)|(data[loop_count].data1 << 8)|data[loop_count].data0;
					}
				}
				else if((found_preamble == 3)||(found_preamble == 4))
				{
					if(found_preamble == 3)
					{
						if(*((unsigned char *)&temp_data)== CC_VBI_PREAMBLE_2)
						{
							found_preamble_pointer = 2;
							found_preamble = 2;

							*((unsigned char *)&data[loop_count]) = CC_VBI_PREAMBLE_0;
							*((unsigned char *)&data[loop_count]+1) = CC_VBI_PREAMBLE_1;

							memcpy((unsigned char *)&data[loop_count]+found_preamble_pointer, ((unsigned char *)&temp_data), (9-found_preamble_pointer));

							if( ((*((unsigned char *)&data[loop_count])== CC_VBI_PREAMBLE_0)&&\
		    	 			(*((unsigned char *)&data[loop_count]+1)== CC_VBI_PREAMBLE_1)&&\
		         	 		(*((unsigned char *)&data[loop_count]+2)== CC_VBI_PREAMBLE_2))&&(valid_data_flag >0))
							{
								sent_data_count++;
								packet_array[sent_data_count] = ((data[loop_count].LineCount & 0x3FF)<<22)|((data[loop_count].Status & 0x0F)<<16)|(data[loop_count].data1 << 8)|data[loop_count].data0;
							}
						}
					}
					else
					{
						if((*((unsigned char *)&temp_data)== CC_VBI_PREAMBLE_1)&&\
						   (*((unsigned char *)&temp_data+1) == CC_VBI_PREAMBLE_2))
						{
							found_preamble_pointer = 1;
							found_preamble = 2;

							*((unsigned char *)&data[loop_count]) = CC_VBI_PREAMBLE_0;

							memcpy((unsigned char *)&data[loop_count]+found_preamble_pointer, ((unsigned char *)&temp_data), (9-found_preamble_pointer));

							if( ((*((unsigned char *)&data[loop_count])== CC_VBI_PREAMBLE_0)&&\
		    	 			(*((unsigned char *)&data[loop_count]+1)== CC_VBI_PREAMBLE_1)&&\
		         	 		(*((unsigned char *)&data[loop_count]+2)== CC_VBI_PREAMBLE_2))&&(valid_data_flag >0))
							{
								sent_data_count++;
								packet_array[sent_data_count] = ((data[loop_count].LineCount & 0x3FF)<<22)|((data[loop_count].Status & 0x0F)<<16)|(data[loop_count].data1 << 8)|data[loop_count].data0;
							}
						}
					}
					if(found_preamble != 2) found_preamble=1;
				}
			}
			else
			{
				if( ((*((unsigned char *)&data[loop_count])== CC_VBI_PREAMBLE_0)&&\
		    		 (*((unsigned char *)&data[loop_count]+1)== CC_VBI_PREAMBLE_1)&&\
		      	     (*((unsigned char *)&data[loop_count]+2)== CC_VBI_PREAMBLE_2))&&(valid_data_flag >0))
				{
					if(valid_packet_count <= 0)
					{
						CC_PRINT("FATAL ERROR!!! Data captured but valid data flag did not raise up!!\n");
						break;
					}
					else
					{
						sent_data_count++;
						packet_array[sent_data_count] = ((data[loop_count].LineCount & 0x3FF)<<22)|((data[loop_count].Status & 0x0F)<<16)|(data[loop_count].data1 << 8)|data[loop_count].data0;
					}
				}
				else
					CC_PRINT("Data came, but preamble was wrong! \n");
			}
		}
		ret = sent_data_count + 1;
	}
	else
	{
		CC_PRINT("Data came. But count value has exceeded max value. Count[%x], Start[%x], End[%x], \n" ,count, start, end);
		ret = -1;
	}

	return ret;
}

#ifdef	KDRV_CONFIG_PM

int CC_L9B0_RunSuspend(void)
{
	// param will be saved automatically....
	return 0;
}

int CC_L9B0_RunResume(void)
{
	return 0;
}

#endif

/** @} */
