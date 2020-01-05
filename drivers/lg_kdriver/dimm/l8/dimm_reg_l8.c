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
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2010.03.22
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/
#define USE_DIMM_NEW_LUT

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>

#include "base_types.h"
#include "os_util.h"

#include "../de/de_ver_def.h"
#include "../de/de_def.h"
#include "../de/l8/de_ipc_def_l8.h"
#include "../de/l8/de_reg_def_l8.h"

#include "dimm_kapi.h"
#include "l8/dimm_reg_l8.h"
#include "l8/dimm_reg_l8b0.h"
//#include "dimm_firmware.h"
#include "l8/dimm_regp_l8.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define DIMM_LUT_HEADER4PC_NOT_INTIALIZED (0xFFFFFFFF)

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define LED_L8AX_WfCM(_r,_f,_c,_m)	    (gpRegLED_L8Ax->_r._f) = (_c)?((_m)|gpRegLED_L8Ax->_r._f):(~(_m)&gpRegLED_L8Ax->_r._f)
#define LED_L8AX_Rdfd(_r,_f)			(gpRegLED_L8Ax->_r._f)
#define LED_L8B0_WfCM(_r,_f,_c,_m)	    (gpRegLED_L8B0->_r._f) = (_c)?((_m)|gpRegLED_L8B0->_r._f):(~(_m)&gpRegLED_L8B0->_r._f)
#define LED_L8B0_Rdfd(_r,_f)			(gpRegLED_L8B0->_r._f)

#define LED_RdFL(_r)			do { if (gDimmVersionIsL8B0) LED_L8B0_RdFL(_r);			  else LED_L8AX_RdFL(_r);			 } while (0)
#define LED_WrFL(_r)			do { if (gDimmVersionIsL8B0) LED_L8B0_WrFL(_r);			  else LED_L8AX_WrFL(_r);			 } while (0)
#define LED_Wr01(_r,_f01,_v01)	do { if (gDimmVersionIsL8B0) LED_L8B0_Wr01(_r,_f01,_v01); else LED_L8AX_Wr01(_r,_f01,_v01);  } while (0)
#define LED_WfCM(_r,_f,_c,_m)	do { if (gDimmVersionIsL8B0) LED_L8B0_WfCM(_r,_f,_c,_m);  else LED_L8AX_WfCM(_r,_f,_c,_m);   } while (0)
#define LED_Rdfd(_r,_f)			(gDimmVersionIsL8B0)?LED_L8B0_Rdfd(_r,_f):LED_L8AX_Rdfd(_r,_f)

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct {
	UINT32 addr;
	UINT32 num;
} DIMM_LUT_HEADER_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static BOOLEAN gDimmVersionIsL8B0 = TRUE;
#if defined(USE_VIDEO_IOREMAP)
static			LED_L8AX_REG_T *gpRealRegLED_L8Ax = NULL;
static			LED_L8B0_REG_T *gpRealRegLED_L8B0 = NULL;
#else
static volatile LED_L8AX_REG_T *gpRealRegLED_L8Ax = NULL;
static volatile LED_L8B0_REG_T *gpRealRegLED_L8B0 = NULL;
#endif
static LED_L8AX_REG_T *gpRegLED_L8Ax = NULL;
static LED_L8B0_REG_T *gpRegLED_L8B0 = NULL;

#ifndef USE_DIMM_NEW_LUT
DIMM_LUT_HEADER_T sDimmLutHeader[] = {
	{ 0x104, 2	  },
	{ 0x100, 2	  },
	{ 0x220, 400  },
	{ 0x224, 600  },
	{ 0x228, 81   },
	{ 0x22c, 72   },
	{ 0x230, 72   },
	{ 0x234, 64   },
	{ 0x238, 1024 },
	{ 0x23C, 1024 },
	{ 0x218, 80   },
	{ 0x21c, 120  },
	{ 0x0e0, 25   },
/*	{ 0x10c, 1	  },
	{ 0x110, 1	  },
	{ 0x114, 1	  },
	{ 0x118, 1	  },
	{ 0x138, 1	  },
	{ 0x144, 1	  },
	{ 0x148, 1	  },
	{ 0x14c, 1	  },
	{ 0x150, 1	  },
	{ 0x154, 1	  },
	{ 0x158, 1	  },
	{ 0x15c, 1	  },
	{ 0x160, 1	  },
	{ 0x164, 1	  },
	{ 0x168, 1	  },
	{ 0x16c, 1	  },
	{ 0x170, 1	  },
	{ 0x1B0, 1	  },
	{ 0x024, 1	  },
	{ 0x084, 1	  },
	{ 0x088, 1	  },
	{ 0x08c, 1	  },
	{ 0x090, 1	  },
	{ 0x028, 1	  },
	{ 0x02c, 1	  },
	{ 0x030, 1	  },
	{ 0x020, 1	  },
	{ 0x0D0, 1	  },
	{ 0x0E4, 1	  },
	{ 0x040, 1	  },
	{ 0x09c, 1	  },
	{ 0x058, 1	  },
	{ 0x174, 1	  },
	{ 0x210, 1	  }
*/
};

DIMM_LUT_HEADER_T sDimmLutHeader4PC[] = {
	{ 0x228, 81   },
	{ 0x22c, 72   },
	{ 0x230, 72   },
	{ 0x234, 64   },
	{ 0x238, 1024 },
	{ 0x23C, 1024 },
	{ 0x088, 1    },
	{ 0x09C, 1    },
};
#endif

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief Create DIMM Register.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_Create(void)
{
	int ret = RET_OK;

	gDimmVersionIsL8B0 = (lx_chip_rev() >= LX_CHIP_REV(L8,B0));
#ifdef USE_QEMU_SYSTEM
	if (gDimmVersionIsL8B0) {
		gpRealRegLED_L8B0 = (		 LED_L8B0_REG_T *)OS_KMalloc(sizeof(LED_L8B0_REG_T));
	} else {
		gpRealRegLED_L8Ax = (		 LED_L8AX_REG_T *)OS_KMalloc(sizeof(LED_L8AX_REG_T));
	}
#elif defined(USE_VIDEO_IOREMAP)
	if (gDimmVersionIsL8B0) {
		gpRealRegLED_L8B0 = (volatile LED_L8B0_REG_T *)ioremap(DTVSOC_LED_BASE, sizeof(LED_L8B0_REG_T));
	} else {
		gpRealRegLED_L8Ax = (volatile LED_L8AX_REG_T *)ioremap(DTVSOC_LED_BASE, sizeof(LED_L8AX_REG_T));
	}
#else
	if (gDimmVersionIsL8B0) {
		gpRealRegLED_L8B0 = (volatile LED_L8B0_REG_T *)(DTVSOC_LED_BASE);
	} else {
		gpRealRegLED_L8Ax = (volatile LED_L8AX_REG_T *)(DTVSOC_LED_BASE);
	}
#endif
	if (gDimmVersionIsL8B0) {
		gpRegLED_L8B0	  = (		 LED_L8B0_REG_T *)OS_KMalloc(sizeof(LED_L8B0_REG_T));
	} else {
		gpRegLED_L8Ax	  = (		 LED_L8AX_REG_T *)OS_KMalloc(sizeof(LED_L8AX_REG_T));
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Destroy DIMM module.
 *
 * @return RET_OK(0)
 */
int DIMM_REG_Destroy(void)
{
	int ret = RET_OK;

#ifdef USE_QEMU_SYSTEM
	if (gDimmVersionIsL8B0) {
		OS_Free((void*)gpRealRegLED_L8B0);
	} else {
		OS_Free((void*)gpRealRegLED_L8Ax);
	}
#elif defined(USE_VIDEO_IOREMAP)
	if (gDimmVersionIsL8B0) {
		iounmap((void*)gpRealRegLED_L8B0);
	} else {
		iounmap((void*)gpRealRegLED_L8Ax);
	}
#endif
	if (gDimmVersionIsL8B0) {
		OS_Free((void*)gpRegLED_L8B0);
	} else {
		OS_Free((void*)gpRegLED_L8Ax);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize DIMM module.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_Init(LX_DIMM_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_DIMM_LUT_CTRL_T dimmLut;

	LED_RdFL(cmem_addr_clr);
	LED_Wr01(cmem_addr_clr, mem_addr_clr, 1);
	LED_WrFL(cmem_addr_clr);

	LED_RdFL(blu_type);
	switch (pstParams->blType) {
		case LX_BL_NOR_LED	:
		case LX_BL_IOP_LED	:
		case LX_BL_ALEF_LED :
		case LX_BL_IOL_LED	:
			LED_Wr01(blu_type, edge_lit, 0);
			break;
		case LX_BL_EDGE_LED :
			LED_Wr01(blu_type, edge_lit, 1);
			LED_Wr01(blu_type, edge_type, 1);
			break;
		case LX_BL_CCFL		:
		default :
			break;
	}
	LED_WrFL(blu_type);

	do {
		if (!pstParams->u32length) break;
		if (!pstParams->InitData) break;
		dimmLut.pLut   = pstParams->InitData;
		dimmLut.u32Num = pstParams->u32length;

		ret = DIMM_REG_LutControl(&dimmLut);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control local-dimming-on.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_LocaldimmingControl(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	if (gDimmVersionIsL8B0) {
		LED_L8B0_RdFL(spi_cmd_num);
		switch (LED_L8B0_Rdfd(spi_cmd_num, spi_cmd_mode)) {
			case 0 :
				LED_L8B0_RdFL(spi_cmd01);
				LED_L8B0_WfCM(spi_cmd01, spi_cmd0, *pstParams, 0x1);
				LED_L8B0_WrFL(spi_cmd01);
				break;
			case 1 :
				LED_L8B0_RdFL(spi_cmd01);
				LED_L8B0_WfCM(spi_cmd01, spi_cmd1, *pstParams, 0x1);
				LED_L8B0_WrFL(spi_cmd01);
				break;
			case 2 :
				LED_L8B0_RdFL(spi_cmd23);
				LED_L8B0_WfCM(spi_cmd23, spi_cmd2, *pstParams, 0x1);
				LED_L8B0_WrFL(spi_cmd23);
				break;
			case 3 :
				LED_L8B0_RdFL(spi_cmd23);
				LED_L8B0_WfCM(spi_cmd23, spi_cmd3, *pstParams, 0x1);
				LED_L8B0_WrFL(spi_cmd23);
				break;
			default :
				break;
		}
	} else {
		LED_L8AX_RdFL(spi_cmd);
		LED_L8AX_WfCM(spi_cmd, spi_cmd, *pstParams, 0x1);
		LED_L8AX_WrFL(spi_cmd);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Dimming Store Demo Mode.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_StoreDemo(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	LED_RdFL(dbg_ctrl);
	LED_WfCM(dbg_ctrl, demo_en, *pstParams, 1);
	LED_WrFL(dbg_ctrl);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Dimming Line Demo Mode.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_LineDemo(LX_DIMM_LINE_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		LED_RdFL(dbg_ctrl);
		LED_WfCM(dbg_ctrl, pb_en, pstParams->bEnable, 0x1);
		LED_WrFL(dbg_ctrl);

		LED_RdFL(pat_en);
		switch (pstParams->ePatEn) {
			case LX_DIMM_DEMO_PATTERN_NORMAL :
			case LX_DIMM_DEMO_PATTERN_SQUARE :
			case LX_DIMM_DEMO_PATTERN_GRID :
			case LX_DIMM_DEMO_PATTERN_GRADATION_R :
			case LX_DIMM_DEMO_PATTERN_GRADATION_G :
			case LX_DIMM_DEMO_PATTERN_GRADATION_B :
			case LX_DIMM_DEMO_PATTERN_COLOR_BAR :
				LED_Wr01(pat_en, pat_en, pstParams->ePatEn);
				LED_WrFL(pat_en);
				break;
			default :
				BREAK_WRONG(pstParams->ePatEn);
		}
		if (ret) break;

		LED_RdFL(pat_hv_ppf);
		LED_Wr01(pat_hv_ppf, pat_v_ppf, (pstParams->u8Vppf & 0xff));
		LED_Wr01(pat_hv_ppf, pat_h_ppf, (pstParams->u8Hppf & 0xff));
		LED_WrFL(pat_hv_ppf);
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Control Pixel Compensation.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_ControlCompensation(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	LED_RdFL(pc_en);
	LED_WfCM(pc_en, comp_en, *pstParams, 0x1);
	LED_WrFL(pc_en);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Look up Table.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_LutControl(LX_DIMM_LUT_CTRL_T *pstParams)
#ifdef USE_DIMM_NEW_LUT
{
	int ret = RET_OK;
	UINT32 tableLenth;
	UINT32 sizeAddr;
	UINT32 lutData;
	UINT32 lutAddr;
	UINT32 baseAddr;
	int i, idx, lutSize;

	do {
		tableLenth = pstParams->u32Num;
		if (!tableLenth) break;
		CHECK_KNULL(pstParams->pLut);

		//printk("TableLenth[%d] \n", tableLenth);
		baseAddr = (gDimmVersionIsL8B0)?(UINT32)gpRealRegLED_L8B0:(UINT32)gpRealRegLED_L8Ax;
		for (idx=0;idx<tableLenth;)
		{
			sizeAddr = pstParams->pLut[idx++];
			lutSize  = GET_BITS(sizeAddr, 16, 16);
			lutAddr  = GET_BITS(sizeAddr,  0, 16);
			//printk("TableLenth[%d] pAddr [0x%08x] = lutSize [%d]\n", (idx-1),(UINT32)lutAddr, (UINT32)lutSize);

			if (!lutSize) BREAK_WRONG(lutSize);
			if (lutAddr > 0x3fc) BREAK_WRONG(lutAddr);
			if (GET_BITS(lutAddr, 0, 2)) BREAK_WRONG(lutAddr);

			lutAddr += baseAddr;
			for(i=0;i<lutSize;i++)
			{
				if (!(idx<tableLenth)) BREAK_WRONG(tableLenth);
				lutData = pstParams->pLut[idx++];
				REG_WD(lutAddr, lutData);
				//printk("TableLenth[%d]  pAddr [0x%08x] lutSize[%d] = 0x%08x\n", (idx-1), (UINT32)lutAddr, i, (UINT32)lutData);
			}
		}
	} while (0);

	return ret;
}
#else
{
	int ret = RET_OK;
	int i;
	int j;
	int t;
	int lnDimmLut;
	DIMM_LUT_HEADER_T *lpDimmLut;
	UINT32 baseAddr;
	UINT32 regValue;
	volatile UINT32 *pAddr;
	UINT32 isLutTable;
	static UINT32 sDimmLutNum = DIMM_LUT_HEADER4PC_NOT_INTIALIZED;

	if (DIMM_LUT_HEADER4PC_NOT_INTIALIZED == sDimmLutNum) {
		sDimmLutNum = sDimmLutHeader4PC[0].num;
		for (i=1;i<ARRAY_SIZE(sDimmLutHeader4PC);i++) sDimmLutNum += sDimmLutHeader4PC[i].num;
	}

	isLutTable = (pstParams->u32Num == sDimmLutNum)?TRUE:FALSE;
	if ( isLutTable ) {
		lpDimmLut = sDimmLutHeader4PC;
		lnDimmLut = ARRAY_SIZE(sDimmLutHeader4PC);
	} else if (pstParams->u32Num > 2000) {
		lpDimmLut = sDimmLutHeader;
		lnDimmLut = ARRAY_SIZE(sDimmLutHeader);
	} else {
		lpDimmLut = NULL;
		lnDimmLut = 0;
	}

	baseAddr = (gDimmVersionIsL8B0)?(UINT32)gpRealRegLED_L8B0:(UINT32)gpRealRegLED_L8Ax;
	do {
		if (!lpDimmLut) break;
		t = 0;
		for (i=0;i<lnDimmLut;i++) {
			pAddr = (UINT32 *)(baseAddr + lpDimmLut[i].addr);
			//ffprintk("pAddr [0x%08x, 0x%08x] = 0x%08x\n", (UINT32)baseAddr, (UINT32)lpDimmLut[i].addr, (UINT32)pAddr);

			if ( !isLutTable ) {
				if ( 0 == i ) {
					regValue  = pstParams->pLut[t++] << 8;
					regValue |= pstParams->pLut[t++];
					*(volatile UINT32 *)pAddr	 = regValue;
					//printk("pAddr [0x%08x] = 0x%08x\n", (UINT32)pAddr, (UINT32)regValue);
					continue;
				} else if ( 1 == i) {
					regValue  = pstParams->pLut[t++] << 16;
					regValue |= pstParams->pLut[t++];
					*(volatile UINT32 *)pAddr	 = regValue;
					//printk("pAddr [0x%08x] = 0x%08x\n", (UINT32)pAddr, (UINT32)regValue);
					LED_RdFL(blu_type);
					switch (LED_Rdfd(blu_type, edge_lit)) {
						case 0 :
							lpDimmLut[2].num  = pstParams->pLut[3] * 5;
							lpDimmLut[3].num  = pstParams->pLut[2] * 5;
							lpDimmLut[10].num = pstParams->pLut[3];
							lpDimmLut[11].num = pstParams->pLut[2];
							break;
						case 1 :
							lpDimmLut[3].num  = lpDimmLut[2].num  = (LED_Rdfd(blu_type, edge_type))?1920:1080;
							lpDimmLut[10].num = pstParams->pLut[3];
							lpDimmLut[11].num = pstParams->pLut[2];
							break;
						default :
							lpDimmLut[3].num  = lpDimmLut[2].num  = (LED_Rdfd(blu_type, edge_type))?1920:1080;
							lpDimmLut[10].num = pstParams->pLut[3];
							lpDimmLut[11].num = pstParams->pLut[2];
							break;
					}
					continue;
				}
			}

			//printk("lpDimmLut [%d] = 0x%08x\n", i, (UINT32)lpDimmLut[i].num);
			for (j=0;j<lpDimmLut[i].num;j++) {
				//printk("pAddr [%d][%d][0x%08x] = %d\n", i,j,(UINT32)pAddr, (UINT32)pstParams->pLut[t]);
				*(volatile UINT32 *)pAddr = pstParams->pLut[t++];
			}
		}
	} while (0);

	do {
		if (lpDimmLut) break;
		for (i=0;i<pstParams->u32Num;i+=2) {
			pAddr	 = (UINT32 *)(baseAddr + pstParams->pLut[i]);
			regValue = (UINT32	)(pstParams->pLut[i+1]);
			*(volatile UINT32 *)pAddr = regValue;
			//ffprintk("pAddr [%d][0x%08x] = 0x%08x\n", i,(UINT32)pAddr, (UINT32)regValue);
		}
	} while (0);

	return ret;
}
#endif

/**
 * @callgraph
 * @callergraph
 *
 * @brief Local Dimming Control for Store Mode.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_StoreControl(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	LED_RdFL(dbg_ctrl);
	LED_WfCM(dbg_ctrl, apf_en, *pstParams, 1);
	LED_WrFL(dbg_ctrl);

	return ret;
}
/**
 * @callgraph
 * @callergraph
 *
 * @brief Local Dimming Control White Balance Color.
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_WbColorControl(LX_DIMM_WBCOLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;

	if (gDimmVersionIsL8B0) {
		//printk("\n[%s,%d]0x%x,0x%x,0x%x\n\n",__func__,__LINE__,pstParams->rOffsetGain,pstParams->gOffsetGain,pstParams->bOffsetGain);
		LED_L8B0_RdFL(wb_r_gain_offset);
		LED_L8B0_RdFL(wb_g_gain_offset);
		LED_L8B0_RdFL(wb_b_gain_offset);
		LED_L8B0_Wr(wb_r_gain_offset, pstParams->rOffsetGain);
		LED_L8B0_Wr(wb_g_gain_offset, pstParams->gOffsetGain);
		LED_L8B0_Wr(wb_b_gain_offset, pstParams->bOffsetGain);
		LED_L8B0_WrFL(wb_r_gain_offset);
		LED_L8B0_WrFL(wb_g_gain_offset);
		LED_L8B0_WrFL(wb_b_gain_offset);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief read Register
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
UINT32 DIMM_REG_RegRd(UINT32 addr)
{
	UINT32 value;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;

	do {
		recvAddr = addr;
		if		(recvAddr <= 0x2000) recvAddr += DTVSOC_LED_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;

		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;
		value = REG_RD(currAddr);
		if (currAddr == recvAddr) break;

		nextValue = REG_RD(currAddr+4);
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	} while (0);

	return value;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Write Register
 *
 * @param pstParams [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DIMM_REG_RegWr(LX_DIMM_REG_WRITE_T *pstParams)
{
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 value;

	do {
		recvAddr = pstParams->wr_addr;
		value	 = pstParams->wr_data;
		if		(recvAddr <= 0x2000) recvAddr += DTVSOC_LED_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;

		if (currAddr == recvAddr) {
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(currAddr);
		nextValue = REG_RD((currAddr+4));

		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);

		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);

		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(currAddr		,currValue);
		REG_WD((currAddr+4) ,nextValue);
	} while (0);

	return RET_OK;
}

/**  @} */
