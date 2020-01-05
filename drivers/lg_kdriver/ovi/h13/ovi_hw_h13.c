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
 *	OVI module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
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
#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hw_h13.h"
#include "ovi_reg_def_h13.h"
#include "ovi_reg_h13.h"

// For CTOP register access
#include "../../sys/sys_regs.h"
#include "ovi_output_format_h13b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_H13_LVDS_MAX_PORT_NUM 4
#define OVI_HW_H13_VX1_CASE_A_LANE_NUM 4
#define OVI_HW_H13_VX1_CASE_B_LANE_NUM 6
#define OVI_HW_H13_VX1_RTOP_MAX_LANE_NUM 8 // RTOP에서는 Vx1이 8lane까지 지원하는 것으로 되어 있으나 CTOP에서 6lane으로 제한하여 최종 6lane 사용 가능
#define OVI_HW_H13_VX1_LANE0_PDB_EN_BIT 11
#define OVI_HW_H13_VX1_LINK11_EN_BIT 23
#define OVI_HW_H13_RGB_D0_VAL 0
#define OVI_HW_H13_OSD_D0_VAL 4

#define OVI_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define OVI_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	volatile UINT32 *dppbVinCfgAddr;

	volatile UINT32 *dppaRegBaseAddr;
	volatile UINT32 *tconRegBaseAddr;
	volatile UINT32 *oifRegBaseAddr;
	volatile UINT32 *ctopRegBaseAddr;
} OVI_HW_H13_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_H13_OUTPUT_MODES_T;
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_H13_T gOVI_TCON_H13;
OVI_OIF_REG_H13_T gOVI_OIF_H13;

unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_H13Bx[] =
{
	{"H13_OVI_HSLVDS_2PORT_60HZ_480P\n",  ovi_output_format_hslvds_2port_60hz_480p, sizeof(ovi_output_format_hslvds_2port_60hz_480p)/sizeof(LX_OVI_REG_T)},
	{"H13_OVI_HSLVDS_2PORT_60HZ_720P\n",  ovi_output_format_hslvds_2port_60hz_720p, sizeof(ovi_output_format_hslvds_2port_60hz_720p)/sizeof(LX_OVI_REG_T)},
	{"H13_OVI_HSLVDS_2PORT_60HZ_1080P\n", ovi_output_format_hslvds_2port_60hz_1080p, sizeof(ovi_output_format_hslvds_2port_60hz_1080p)/sizeof(LX_OVI_REG_T)},

	{"H13_OVI_HSLVDS_2PORT_60HZ_2X_MODE_1080P\n", ovi_output_format_hslvds_2port_2x_60hz_1080p, sizeof(ovi_output_format_hslvds_2port_2x_60hz_1080p)/sizeof(LX_OVI_REG_T)},
	{"H13_OVI_HSLVDS_4PORT_120HZ_1080P\n", ovi_output_format_hslvds_4port_120hz_1080p, sizeof(ovi_output_format_hslvds_4port_120hz_1080p)/sizeof(LX_OVI_REG_T)},
	{"H13_OVI_EPI_6LANE_120HZ_1080P\n", ovi_output_format_epi_6lane_120hz_1080p, sizeof(ovi_output_format_epi_6lane_120hz_1080p)/sizeof(LX_OVI_REG_T)},
};

OVI_HW_H13_OUTPUT_MODES_T _gOVIOutputModes_H13 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OVI_HW_H13_INFO_T oviHwH13Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
int OVI_HW_H13_Initialize(void)
{
	int ret = RET_OK;

	do {
		if(lx_chip_rev() >= LX_CHIP_REV( H13, B0))
		{
			UINT32 tconCtrlReg;

			/* Set configuration of Output mode presets, for mode change on run time */
			_gOVIOutputModes_H13.pOVIOutputModes = _gOVIOutputModes_H13Bx;
			_gOVIOutputModes_H13.number_of_modes	 = sizeof(_gOVIOutputModes_H13Bx)/sizeof(LX_OVI_OUTPUT_MODE_T);

			gOVI_TCON_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_H13B0_T));
			gOVI_OIF_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_H13B0_T));

			gOVI_TCON_H13.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_H13_BASE, sizeof(OVI_TCON_REG_H13B0_T));
			gOVI_OIF_H13.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_H13_BASE, sizeof(OVI_OIF_REG_H13B0_T));

			oviHwH13Info.dppbVinCfgAddr = (volatile UINT32 *)ioremap(0xC0030010, sizeof(UINT32)); // 0xC0030010 -> AD_VIN_CONFIG of DPPB LED

			oviHwH13Info.dppaRegBaseAddr = (volatile UINT32 *)ioremap(0xC0030010, sizeof(UINT32));
			oviHwH13Info.tconRegBaseAddr = gOVI_TCON_H13.phys.addr;
			oviHwH13Info.oifRegBaseAddr = gOVI_OIF_H13.phys.addr;
			oviHwH13Info.ctopRegBaseAddr = gCTOP_CTRL_H13.phys.addr;

		}
	} while(0);

	return ret;
}

int OVI_HW_H13_Close(void)
{
	int ret = RET_OK;

	if(lx_chip_rev() >= LX_CHIP_REV( H13, B0))
	{
		if(gOVI_TCON_H13.shdw.addr)
		{
			OS_Free((void *)gOVI_TCON_H13.shdw.addr);
			gOVI_TCON_H13.shdw.addr = NULL;
		}
		if(gOVI_OIF_H13.shdw.addr)
		{
			OS_Free((void *)gOVI_OIF_H13.shdw.addr);
			gOVI_OIF_H13.shdw.addr = NULL;
		}

		if (gOVI_TCON_H13.phys.addr)
		{
			iounmap((void *)gOVI_TCON_H13.phys.addr);
			gOVI_TCON_H13.phys.addr = NULL;
		}
		if (gOVI_OIF_H13.phys.addr)
		{
			iounmap((void *)gOVI_OIF_H13.phys.addr);
			gOVI_OIF_H13.phys.addr = NULL;
		}

		if (oviHwH13Info.dppbVinCfgAddr)
		{
			iounmap((void *)oviHwH13Info.dppbVinCfgAddr);
			oviHwH13Info.dppbVinCfgAddr = NULL;
		}

		if (oviHwH13Info.dppaRegBaseAddr)
		{
			iounmap((void *)oviHwH13Info.dppaRegBaseAddr);
			oviHwH13Info.dppaRegBaseAddr = NULL;
		}
		oviHwH13Info.tconRegBaseAddr = NULL;
		oviHwH13Info.oifRegBaseAddr = NULL;
		oviHwH13Info.ctopRegBaseAddr = NULL;
	}

	return ret;
}

int OVI_HW_H13_SetLvds(LX_OVI_LVDS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 lvdsSel = 0;
	UINT32 vx1Sel = 0;
	UINT32 ctrReg_val = 0;
	UINT32 vidPortNum = 0, osdPortNum = 0;
	UINT32 port;
	UINT32 bitShiftNum;

	do {
		if((pstParams->eVideoBandwidth+pstParams->eOsdBandwidth > OVI_HW_H13_LVDS_MAX_PORT_NUM)
			&& (pstParams->eMode == LX_OVI_LVDS_MODE_NORMAL))
		{
			OVI_ERROR("OVI ERROR! These settings are not supported!\n");
			OVI_BREAK_WRONG(pstParams->eVideoBandwidth+pstParams->eOsdBandwidth);
		}

		// Preferentially, all channel power down -> power on for only selected channel
		CTOP_CTRL_H13B0_RdFL(ctr111);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
		CTOP_CTRL_H13B0_WrFL(ctr111);

		// reset
		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_pdb11, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr23);
		CTOP_CTRL_H13B0_Wr01(ctr23, reg_dppb, 0x1);
		CTOP_CTRL_H13B0_WrFL(ctr23);

		if(pstParams->eMode == LX_OVI_LVDS_MODE_HS)
		{
			CTOP_CTRL_H13B0_RdFL(ctr24);
			CTOP_CTRL_H13B0_Wr01(ctr24, tx_combo_sel, 0x3);
			CTOP_CTRL_H13B0_WrFL(ctr24);
		}
		else
		{
			CTOP_CTRL_H13B0_RdFL(ctr24);
			CTOP_CTRL_H13B0_Wr01(ctr24, tx_combo_sel, 0x4);
			CTOP_CTRL_H13B0_WrFL(ctr24);
		}

		if(pstParams->bEnable) // Vx1 disable
		{
			OVI_OIF_H13_RdFL(oif_vx1_config0);
			OVI_OIF_H13_Rd01(oif_vx1_config0, vx1_sel, vx1Sel);
			vx1Sel = (vx1Sel & ~(1<<24)) | (!pstParams->bEnable << 24);
			OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_sel, vx1Sel);
			OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_en, !pstParams->bEnable);
			OVI_OIF_H13_WrFL(oif_vx1_config0);
		}

		OVI_OIF_H13_RdFL(oif_lvds_config0);

		OVI_OIF_H13_Rd01(oif_lvds_config0, lvds_sel, lvdsSel);
		lvdsSel = (lvdsSel & ~(1<<12)) | (pstParams->bEnable << 12);
		OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_sel, lvdsSel);
		OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_swap, pstParams->bSwapEn);

		switch(pstParams->eOutputStd)
		{
			case LX_OVI_LVDS_OUT_JEIDA :
				OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_lsb_first, 0);
				break;

			case LX_OVI_LVDS_OUT_VESA :
				OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_lsb_first, 1);
				break;

			default :
				break;
		}

		switch(pstParams->eBitDepth)
		{
			case LX_OVI_8BIT :
				OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_8bit_mode, 1);
				break;

			case LX_OVI_10BIT :
				OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_8bit_mode, 0);
				break;

			default :
				break;
		}

		OVI_OIF_H13_WrFL(oif_lvds_config0);

		switch(pstParams->eVideoBandwidth)
		{
			case LX_OVI_BANDWIDTH_0CH :

				break;

			case LX_OVI_BANDWIDTH_1CH :
				*oviHwH13Info.dppbVinCfgAddr = 0x1;

				OVI_OIF_H13_RdFL(oif_vch_config);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_in_port, 0x1);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
				vidPortNum = 1;
				OVI_OIF_H13_WrFL(oif_vch_config);

				CTOP_CTRL_H13B0_RdFL(ctr24);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x1);	// 37.125MHz
				CTOP_CTRL_H13B0_WrFL(ctr24);
				break;

			case LX_OVI_BANDWIDTH_2CH :
				*oviHwH13Info.dppbVinCfgAddr = 0x1;

				OVI_OIF_H13_RdFL(oif_vch_config);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_in_port, 0x1);
				if(pstParams->eMode == LX_OVI_LVDS_MODE_HS)
				{
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
					vidPortNum = 1;
				}
				else
				{
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0x1);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth/2);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
					vidPortNum = 2;
				}
				OVI_OIF_H13_WrFL(oif_vch_config);

				CTOP_CTRL_H13B0_RdFL(ctr24);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz
				CTOP_CTRL_H13B0_WrFL(ctr24);
				break;

			case LX_OVI_BANDWIDTH_4CH :
				*oviHwH13Info.dppbVinCfgAddr = 0x0;

				OVI_OIF_H13_RdFL(oif_vch_config);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_in_port, 0x3);
				if(pstParams->eMode == LX_OVI_LVDS_MODE_HS)
				{
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0x1);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth/2);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
					vidPortNum = 2;
				}
				else
				{
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0x3);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth/4);
					OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
					vidPortNum = 4;
				}
				OVI_OIF_H13_WrFL(oif_vch_config);

				CTOP_CTRL_H13B0_RdFL(ctr24);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz
				CTOP_CTRL_H13B0_WrFL(ctr24);
				break;

			default :
				break;
		}

		switch(pstParams->eOsdBandwidth)
		{
			case LX_OVI_BANDWIDTH_0CH :

				break;

			case LX_OVI_BANDWIDTH_1CH :
				OVI_OIF_H13_RdFL(oif_och_config);
				OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x0);
				OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth);
				OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
				osdPortNum = 1;
				OVI_OIF_H13_WrFL(oif_och_config);
				break;

			case LX_OVI_BANDWIDTH_2CH :
				OVI_OIF_H13_RdFL(oif_och_config);
				if(pstParams->eMode == LX_OVI_LVDS_MODE_HS)
				{
					OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x0);
					OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth);
					OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
					osdPortNum = 1;
				}
				else
				{
					OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x1);
					OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth/2);
					OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
					osdPortNum = 2;
				}
				OVI_OIF_H13_WrFL(oif_och_config);
				break;

			case LX_OVI_BANDWIDTH_4CH :
				OVI_OIF_H13_RdFL(oif_och_config);
				if(pstParams->eMode == LX_OVI_LVDS_MODE_HS)
				{
					OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x1);
					OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth/2);
					OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
					osdPortNum = 2;
				}
				else
				{
					OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x3);
					OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth/4);
					OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
					osdPortNum = 4;
				}
				OVI_OIF_H13_WrFL(oif_och_config);
				break;

			default :
				break;
		}

		OVI_OIF_H13_RdFL(oif_lvds_config0);
		CTOP_CTRL_H13B0_RdFL(ctr111);
		for(port=0; port<(vidPortNum+osdPortNum); port++)
		{
			OVI_OIF_H13_Rd01(oif_lvds_config0, lvds_sel, lvdsSel);
			bitShiftNum = (OVI_HW_H13_LVDS_MAX_PORT_NUM-1-port)*3;
			if(port < vidPortNum)
			{
				lvdsSel = (lvdsSel & ~(0x7<<bitShiftNum)) | ((OVI_HW_H13_RGB_D0_VAL+port) << bitShiftNum);
			}
			else
			{
				lvdsSel = (lvdsSel & ~(0x7<<bitShiftNum)) | ((OVI_HW_H13_OSD_D0_VAL+port-vidPortNum) << bitShiftNum);
			}
			OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_sel, lvdsSel);

			if(!pstParams->bPowDn) // port와 power mapping 확인!!!!!
			{
				ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
				bitShiftNum = port*6;
				ctrReg_val = (ctrReg_val & ~(0x3F<<bitShiftNum)) | (0x3F<<bitShiftNum);
				CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
			}
		}
		OVI_OIF_H13_WrFL(oif_lvds_config0);
		CTOP_CTRL_H13B0_WrFL(ctr111);

		// LVDS default
		CTOP_CTRL_H13B0_RdFL(ctr100);
		CTOP_CTRL_H13B0_Wr(ctr100, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr100);

		CTOP_CTRL_H13B0_RdFL(ctr101);
		CTOP_CTRL_H13B0_Wr(ctr101, 0x03FD0000);
		CTOP_CTRL_H13B0_WrFL(ctr101);

		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_test_di1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_test_di2, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_read_address_offset1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_read_address_offset2, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_clk_pix1x_rf1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_clk_pix1x_rf2, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr103);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sw_pud, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_mode, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_adj_term, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_term_en, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_rf, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_lock, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_lock_ctl, 0x2);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_lpf, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_prediv, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_cih, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_ib_oft, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_fin, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_pll_ic, 0x3);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sw_rext, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr103);

		CTOP_CTRL_H13B0_RdFL(ctr104);
		CTOP_CTRL_H13B0_RdFL(ctr105);
		CTOP_CTRL_H13B0_RdFL(ctr106);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune0, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune1, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune2, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune3, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune4, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune5, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune6, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune7, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune8, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune9, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune10, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune11, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune12, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune13, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune14, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune15, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune16, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune17, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune18, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune19, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune20, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune21, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune22, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune23, 0x5);
		CTOP_CTRL_H13B0_WrFL(ctr104);
		CTOP_CTRL_H13B0_WrFL(ctr105);
		CTOP_CTRL_H13B0_WrFL(ctr106);

		CTOP_CTRL_H13B0_RdFL(ctr107);
		CTOP_CTRL_H13B0_RdFL(ctr108);
		CTOP_CTRL_H13B0_RdFL(ctr109);
		CTOP_CTRL_H13B0_RdFL(ctr110);
		CTOP_CTRL_H13B0_Wr(ctr107, 0x0);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr108);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr108, ctrReg_val);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr109);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr109, ctrReg_val);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr110);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr110, ctrReg_val);
		CTOP_CTRL_H13B0_WrFL(ctr107);
		CTOP_CTRL_H13B0_WrFL(ctr108);
		CTOP_CTRL_H13B0_WrFL(ctr109);
		CTOP_CTRL_H13B0_WrFL(ctr110);

		OS_MsecSleep(1);

		// reset done
		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_pdb11, 0x1);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr23);
		CTOP_CTRL_H13B0_Wr01(ctr23, reg_dppb, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr23);
	} while(0);

	return ret;
}

int OVI_HW_H13_SetVx1(LX_OVI_VX1_T *pstParams)
{
	int ret = RET_OK;
	UINT32 lvdsSel = 0;
	UINT32 vx1Sel = 0;
	UINT32 ctrReg_val = 0;
	UINT32 lane;
	UINT32 bitShiftNum;

	do {
		if((pstParams->eVideoBandwidth+pstParams->eOsdBandwidth != OVI_HW_H13_VX1_CASE_A_LANE_NUM)
			&& (pstParams->eVideoBandwidth+pstParams->eOsdBandwidth != OVI_HW_H13_VX1_CASE_B_LANE_NUM))
		{
			OVI_ERROR("OVI ERROR! These settings are not supported!\n");
			OVI_BREAK_WRONG(pstParams->eVideoBandwidth+pstParams->eOsdBandwidth);
		}
		if(pstParams->eBitDepth != LX_OVI_10BIT)
		{
			OVI_ERROR("OVI ERROR! This setting is not supported!\n");
			OVI_BREAK_WRONG(pstParams->eBitDepth);
		}

		// Preferentially, all channel power down -> power on for only selected channel
		CTOP_CTRL_H13B0_RdFL(ctr111);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
		CTOP_CTRL_H13B0_WrFL(ctr111);

		// reset
		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_pdb11, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr23);
		CTOP_CTRL_H13B0_Wr01(ctr23, reg_dppb, 0x1);
		CTOP_CTRL_H13B0_WrFL(ctr23);

		CTOP_CTRL_H13B0_RdFL(ctr24);
		CTOP_CTRL_H13B0_Wr01(ctr24, tx_combo_sel, 0x4);
		CTOP_CTRL_H13B0_WrFL(ctr24);

		////////////////////////////////////vx1_out_mode의 사용법??
		if(pstParams->bEnable) // -> LVDS disable
		{
			OVI_OIF_H13_RdFL(oif_lvds_config0);
			OVI_OIF_H13_Rd01(oif_lvds_config0, lvds_sel, lvdsSel);
			lvdsSel = (lvdsSel & ~(1<<12)) | (!pstParams->bEnable << 12);
			OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_sel, lvdsSel);
			OVI_OIF_H13_WrFL(oif_lvds_config0);
		}

		OVI_OIF_H13_RdFL(oif_vx1_config0);
		OVI_OIF_H13_Rd01(oif_vx1_config0, vx1_sel, vx1Sel);
		vx1Sel = (vx1Sel & ~(1<<24)) | (pstParams->bEnable << 24);
		OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_sel, vx1Sel);
		OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_en, pstParams->bEnable);
		OVI_OIF_H13_WrFL(oif_vx1_config0);
		///////////////////////////////////////////

		switch(pstParams->eVideoBandwidth)
		{
			case LX_OVI_BANDWIDTH_0CH :

				break;

			case LX_OVI_BANDWIDTH_2CH :
				*oviHwH13Info.dppbVinCfgAddr = 0x1;

				OVI_OIF_H13_RdFL(oif_vch_config);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_in_port, 0x1);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0x1);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth/2);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
				OVI_OIF_H13_WrFL(oif_vch_config);

				CTOP_CTRL_H13B0_RdFL(ctr24);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz
				CTOP_CTRL_H13B0_WrFL(ctr24);
				break;

			case LX_OVI_BANDWIDTH_4CH :
				*oviHwH13Info.dppbVinCfgAddr = 0x0;

				OVI_OIF_H13_RdFL(oif_vch_config);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_in_port, 0x3);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_out_port, 0x3);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_out_h_width, pstParams->eVideoHWidth/4);
				OVI_OIF_H13_Wr01(oif_vch_config, vch_hb_width, 0x4);
				OVI_OIF_H13_WrFL(oif_vch_config);

				CTOP_CTRL_H13B0_RdFL(ctr24);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz
				CTOP_CTRL_H13B0_WrFL(ctr24);
				break;

			default :
				break;
		}

		switch(pstParams->eOsdBandwidth)
		{
			case LX_OVI_BANDWIDTH_0CH :

				break;

			case LX_OVI_BANDWIDTH_2CH :
				OVI_OIF_H13_RdFL(oif_och_config);
				OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x1);
				OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth/2);
				OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
				OVI_OIF_H13_WrFL(oif_och_config);
				break;

			case LX_OVI_BANDWIDTH_4CH :
				OVI_OIF_H13_RdFL(oif_och_config);
				OVI_OIF_H13_Wr01(oif_och_config, och_out_port, 0x3);
				OVI_OIF_H13_Wr01(oif_och_config, och_out_h_width, pstParams->eOsdHWidth/4);
				OVI_OIF_H13_Wr01(oif_och_config, och_hb_width, 0x4);
				OVI_OIF_H13_WrFL(oif_och_config);
				break;

			default :
				break;
		}

		OVI_OIF_H13_RdFL(oif_vx1_config0);
		CTOP_CTRL_H13B0_RdFL(ctr101);
		CTOP_CTRL_H13B0_RdFL(ctr108);
		CTOP_CTRL_H13B0_RdFL(ctr111);
		for(lane=0; lane<(pstParams->eVideoBandwidth+pstParams->eOsdBandwidth); lane++)
		{
			OVI_OIF_H13_Rd01(oif_vx1_config0, vx1_sel, vx1Sel);
			bitShiftNum = (OVI_HW_H13_VX1_RTOP_MAX_LANE_NUM-1-lane)*3;
			if(lane < pstParams->eVideoBandwidth)
			{
				vx1Sel = (vx1Sel & ~(0x7<<bitShiftNum)) | ((OVI_HW_H13_RGB_D0_VAL+lane) << bitShiftNum);
			}
			else
			{
				vx1Sel = (vx1Sel & ~(0x7<<bitShiftNum)) | ((OVI_HW_H13_OSD_D0_VAL+lane-(pstParams->eVideoBandwidth)) << bitShiftNum);
			}
			OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_sel, vx1Sel);

			ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr108);
			bitShiftNum = OVI_HW_H13_VX1_LINK11_EN_BIT-lane;
			ctrReg_val = (ctrReg_val & ~(0x1<<bitShiftNum)) | (0x1<<bitShiftNum);
			ctrReg_val &= 0xFFFF0000;
			CTOP_CTRL_H13B0_Wr(ctr108, ctrReg_val);

			if(!pstParams->bPowDn)
			{
				ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
				bitShiftNum = OVI_HW_H13_VX1_LANE0_PDB_EN_BIT-lane;
				ctrReg_val = (ctrReg_val & ~(0x1<<bitShiftNum)) | (0x1<<bitShiftNum);
				CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
			}
		}
		if(pstParams->eVideoBandwidth+pstParams->eOsdBandwidth == OVI_HW_H13_VX1_CASE_A_LANE_NUM)
		{
			CTOP_CTRL_H13B0_Wr(ctr101, 0x09550800); // C4_LANEMODE : 0x0
		}
		else //if(pstParams->eVideoBandwidth+pstParams->eOsdBandwidth == OVI_HW_H13_VX1_CASE_B_LANE_NUM)
		{
			CTOP_CTRL_H13B0_Wr(ctr101, 0x09554800); // C4_LANEMODE : 0x1
		}

		OVI_OIF_H13_WrFL(oif_vx1_config0);
		CTOP_CTRL_H13B0_WrFL(ctr101);
		CTOP_CTRL_H13B0_WrFL(ctr108);
		CTOP_CTRL_H13B0_WrFL(ctr111);

		// Vx1 default
		CTOP_CTRL_H13B0_RdFL(ctr100);
		CTOP_CTRL_H13B0_Wr(ctr100, 0x22000000);
		CTOP_CTRL_H13B0_WrFL(ctr100);

		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_test_di1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_test_di2, 0x2aa);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_read_address_offset1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_read_address_offset2, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_clk_pix1x_rf1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_clk_pix1x_rf2, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr103);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sw_pud, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_mode, 0x3);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_adj_term, 0x8);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_term_en, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_rf, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_lock, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_lock_ctl, 0x2);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_lpf, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_prediv, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_cih, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_ib_oft, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_fin, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_pll_ic, 0x3);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sw_rext, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr103);

		CTOP_CTRL_H13B0_RdFL(ctr104);
		CTOP_CTRL_H13B0_RdFL(ctr105);
		CTOP_CTRL_H13B0_RdFL(ctr106);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune0, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune1, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune2, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune3, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune4, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune5, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune6, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune7, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune8, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune9, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune10, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune11, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune12, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune13, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune14, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune15, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune16, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune17, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune18, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune19, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune20, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune21, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune22, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune23, 0x5);
		CTOP_CTRL_H13B0_WrFL(ctr104);
		CTOP_CTRL_H13B0_WrFL(ctr105);
		CTOP_CTRL_H13B0_WrFL(ctr106);

		CTOP_CTRL_H13B0_RdFL(ctr107);
		CTOP_CTRL_H13B0_RdFL(ctr109);
		CTOP_CTRL_H13B0_RdFL(ctr110);
		CTOP_CTRL_H13B0_Wr(ctr107, 0x0);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr109);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr109, ctrReg_val);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr110);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr110, ctrReg_val);
		CTOP_CTRL_H13B0_WrFL(ctr107);
		CTOP_CTRL_H13B0_WrFL(ctr109);
		CTOP_CTRL_H13B0_WrFL(ctr110);

		OS_MsecSleep(1);

		// reset done
		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_pdb11, 0x1);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr23);
		CTOP_CTRL_H13B0_Wr01(ctr23, reg_dppb, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr23);
	} while(0);

	return ret;
}

int OVI_HW_H13_SetEpi(LX_OVI_EPI_T *pstParams)
{
	int ret = RET_OK;
	UINT32 lvdsSel = 0;
	UINT32 vx1Sel = 0;
	UINT32 ctrReg_val = 0;

	do {
		if(pstParams->eBitDepth != LX_OVI_8BIT)
		{
			OVI_ERROR("OVI ERROR! This setting is not supported!\n");
			OVI_BREAK_WRONG(pstParams->eBitDepth);
		}

		// Preferentially, all channel power down -> power on for only selected channel
		CTOP_CTRL_H13B0_RdFL(ctr111);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
		CTOP_CTRL_H13B0_WrFL(ctr111);

		// reset
		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_pdb11, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr23);
		CTOP_CTRL_H13B0_Wr01(ctr23, reg_dppb, 0x1);
		CTOP_CTRL_H13B0_WrFL(ctr23);

		// EPI enable -> LVDS/Vx1 disable, EPI disable -> LVDS or Vx1 enable
		OVI_OIF_H13_RdFL(oif_lvds_config0);
		OVI_OIF_H13_RdFL(oif_vx1_config0);
		OVI_OIF_H13_Rd01(oif_lvds_config0, lvds_sel, lvdsSel);
		lvdsSel = (lvdsSel & ~(1<<12)) | (!pstParams->bEnable << 12);
		OVI_OIF_H13_Wr01(oif_lvds_config0, lvds_sel, lvdsSel);
		OVI_OIF_H13_Rd01(oif_vx1_config0, vx1_sel, vx1Sel);
		vx1Sel = (vx1Sel & ~(1<<24)) | (!pstParams->bEnable << 24);
		OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_sel, vx1Sel);
		OVI_OIF_H13_Wr01(oif_vx1_config0, vx1_en, !pstParams->bEnable);
		OVI_OIF_H13_WrFL(oif_lvds_config0);
		OVI_OIF_H13_WrFL(oif_vx1_config0);

		*oviHwH13Info.dppbVinCfgAddr = 0x0;

		CTOP_CTRL_H13B0_RdFL(ctr24);
		CTOP_CTRL_H13B0_RdFL(ctr101);
		CTOP_CTRL_H13B0_WrFL(ctr111);
		switch(pstParams->eOutput)
		{
			case LX_OVI_EPI_6LANE :
				CTOP_CTRL_H13B0_Wr01(ctr24, tx_combo_sel, 0x0);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz

				CTOP_CTRL_H13B0_Wr(ctr101, 0x03FD0000); // C4_LANEMODE : 0x0

				ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
				ctrReg_val = (ctrReg_val & 0xFF000000) | 0x3F000;
				CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
				break;

			case LX_OVI_EPI_12LANE :
				CTOP_CTRL_H13B0_Wr01(ctr24, tx_combo_sel, 0x1);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz

				CTOP_CTRL_H13B0_Wr(ctr101, 0x03FD4000); // C4_LANEMODE : 0x1

				ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
				ctrReg_val = (ctrReg_val & 0xFF000000) | 0x3FFC0;
				CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
				break;

			case LX_OVI_EPI_16LANE :
				CTOP_CTRL_H13B0_Wr01(ctr24, tx_combo_sel, 0x2);
				CTOP_CTRL_H13B0_Wr01(ctr24, dppb_clk_sel, 0x0);	// 74.25MHz

				CTOP_CTRL_H13B0_Wr(ctr101, 0x03FD8000); // C4_LANEMODE : 0x2

				ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr111);
				ctrReg_val = (ctrReg_val & 0xFF000000) | 0x3FFFC;
				CTOP_CTRL_H13B0_Wr(ctr111, ctrReg_val);
				break;

			default :
				break;
		}
		CTOP_CTRL_H13B0_WrFL(ctr24);
		CTOP_CTRL_H13B0_WrFL(ctr101);
		CTOP_CTRL_H13B0_WrFL(ctr111);

		// EPI default
		CTOP_CTRL_H13B0_RdFL(ctr100);
		CTOP_CTRL_H13B0_Wr(ctr100, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr100);

		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_test_di1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_test_di2, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_read_address_offset1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_read_address_offset2, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_clk_pix1x_rf1, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_clk_pix1x_rf2, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr103);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sw_pud, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_mode, 0x2);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_adj_term, 0x8);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_term_en, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_rf, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_lock, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_lock_ctl, 0x2);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_lpf, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_prediv, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_cih, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_ib_oft, 0x1);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sel_fin, 0x0);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_pll_ic, 0x3);
		CTOP_CTRL_H13B0_Wr01(ctr103, c4_sw_rext, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr103);

		CTOP_CTRL_H13B0_RdFL(ctr104);
		CTOP_CTRL_H13B0_RdFL(ctr105);
		CTOP_CTRL_H13B0_RdFL(ctr106);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune0, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune1, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune2, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune3, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune4, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune5, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune6, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune7, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune8, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr104, c4_itune9, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune10, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune11, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune12, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune13, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune14, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune15, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune16, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune17, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune18, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr105, c4_itune19, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune20, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune21, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune22, 0x5);
		CTOP_CTRL_H13B0_Wr01(ctr106, c4_itune23, 0x5);
		CTOP_CTRL_H13B0_WrFL(ctr104);
		CTOP_CTRL_H13B0_WrFL(ctr105);
		CTOP_CTRL_H13B0_WrFL(ctr106);

		CTOP_CTRL_H13B0_RdFL(ctr107);
		CTOP_CTRL_H13B0_RdFL(ctr108);
		CTOP_CTRL_H13B0_RdFL(ctr109);
		CTOP_CTRL_H13B0_RdFL(ctr110);
		CTOP_CTRL_H13B0_Wr(ctr107, 0x0);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr108);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr108, ctrReg_val);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr109);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr109, ctrReg_val);
		ctrReg_val = CTOP_CTRL_H13B0_Rd(ctr110);
		ctrReg_val = ctrReg_val & 0xFF000000;
		CTOP_CTRL_H13B0_Wr(ctr110, ctrReg_val);
		CTOP_CTRL_H13B0_WrFL(ctr107);
		CTOP_CTRL_H13B0_WrFL(ctr108);
		CTOP_CTRL_H13B0_WrFL(ctr109);
		CTOP_CTRL_H13B0_WrFL(ctr110);

		OS_MsecSleep(1);

		// reset done
		CTOP_CTRL_H13B0_RdFL(ctr102);
		CTOP_CTRL_H13B0_Wr01(ctr102, c4_pdb11, 0x1);
		CTOP_CTRL_H13B0_WrFL(ctr102);

		CTOP_CTRL_H13B0_RdFL(ctr23);
		CTOP_CTRL_H13B0_Wr01(ctr23, reg_dppb, 0x0);
		CTOP_CTRL_H13B0_WrFL(ctr23);
	} while(0);

	return ret;
}

int OVI_HW_H13_SetDarkScreen(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {

	} while(0);

	return ret;
}

int OVI_HW_H13_SetReverse(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		// horizontal reverse만 존재???
	} while(0);

	return ret;
}

int OVI_HW_H13_GetTconBaseAddr(UINT32 *pstParams)
{
	int ret = RET_OK;

	do {
		if(gpOviTconMem && gpOviTconMem->base)
		{
			*pstParams = gpOviTconMem->base;
		}
		else
		{
			*pstParams = (UINT32)NULL;
			OVI_ERROR("OVI ERROR! TCON memory is not configured!\n");
			OVI_BREAK_WRONG((UINT32)gpOviTconMem);
		}
	} while(0);

	return ret;
}

int OVI_HW_H13_GetInfo(LX_OVI_INFO_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int OVI_HW_H13_GetConfigVer(LX_OVI_CONFIG_VER_T *pstParams)
{
	int ret = RET_OK;

	do {
			ret = RET_OK;
	} while(0);

	return ret;
}


int OVI_HW_H13_SetCombination(UINT32 eParam)
{
	int ret = RET_ERROR;
	int i,count;
	volatile LX_OVI_REG_T	*regs;
	char	*index;
	unsigned int read_data, same;

	do {
		/* Step 1. Check whether paramater is valid */
		if(eParam == 119) {	// Magic keyword to print available output modes...
			printk("\n[OVI] Display possible OVI mode index...\n");
			for(i=0; i<_gOVIOutputModes_H13.number_of_modes;i++)
			{
				printk("[OVI] Index[%d] : %s", i,_gOVIOutputModes_H13.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(eParam >= 10000)
		{
			eParam = eParam - 10000;
			printk("\n[OVI] Display current register value for items related to index [%d]\n", eParam);

			if(eParam > _gOVIOutputModes_H13.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]\n", eParam);
				break;
			}

			regs  = _gOVIOutputModes_H13.pOVIOutputModes[eParam].regs;
			count = _gOVIOutputModes_H13.pOVIOutputModes[eParam].count;
			index = _gOVIOutputModes_H13.pOVIOutputModes[eParam].index;

			printk("\n[OVI] Reading registers values related to  index => %s", (char *)index);
			for(i=0; i<count; i++){
				OVI_REG_RD(regs[i].addr, read_data);
				if(read_data == regs[i].value) same = 1;
				else same = 0;

				printk("\n[%03d] Current value of [0x%08x] => [0x%8x] / index value [0x%8x] (%s)", i, regs[i].addr, read_data, regs[i].value, same ? "SAME":"DIFFER");
			}
			printk("\n[OVI] Register read complete!\n");

			ret = RET_OK;
			break;
		}
		else if(eParam > _gOVIOutputModes_H13.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", eParam);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_H13.pOVIOutputModes[eParam].regs;
		count = _gOVIOutputModes_H13.pOVIOutputModes[eParam].count;
		index = _gOVIOutputModes_H13.pOVIOutputModes[eParam].index;

		printk("\n[OVI] Setting to preset index => %s", (char *)index);
		for(i=0; i<count; i++){
			printk("\n[%03d] Writing... [0x%08x] <= [0x%8x]", i, regs[i].addr, regs[i].value);
			OVI_REG_WR(regs[i].addr, regs[i].value);
		}
		printk("\n[OVI] Setting preset complete!\n");

		ret = RET_OK;
	} while(0);

	return ret;
}

int OVI_HW_H13_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T stParam)
{
	int ret = RET_OK;

	do {
			CTOP_CTRL_H13B0_RdFL(ctr79);

			if(stParam.bEnable)
			{
				if(/*stParam.u16Period == LX_OVI_SPREAD_SPECTRUM_DEFAULT_PERIOD*/1)	// ignore stParam.u16Period
				{
					switch(stParam.eSpreadRatio)
					{
						case LX_OVI_SPREAD_RATIO_1 :
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_udex_ctrl, 0x3);
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_msex_ctrl, 0x17);
						break;
						case LX_OVI_SPREAD_RATIO_2 :
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_udex_ctrl, 0x4);
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_msex_ctrl, 0x12);
						break;
						case LX_OVI_SPREAD_RATIO_4 :
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_udex_ctrl, 0x7);
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_msex_ctrl, 0xa);
						break;
						case LX_OVI_SPREAD_RATIO_3 :
						default :
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_udex_ctrl, 0x6);
							CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_msex_ctrl, 0xc);
						break;
					}
				}
				else
				{
					CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_udex_ctrl, 0x6);
					CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_msex_ctrl, 0xc);
				}
			}
			else
			{
				CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_udex_ctrl, 0x0);
				CTOP_CTRL_H13B0_Wr01(ctr79, m2_dr3p_msex_ctrl, 0x0);
			}

			CTOP_CTRL_H13B0_WrFL(ctr79);
		} while(0);

	return ret;
}

/** @} */
