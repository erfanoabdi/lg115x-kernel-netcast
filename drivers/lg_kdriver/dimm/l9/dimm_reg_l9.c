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
 * date		  2011.02.25
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "de_ver_def.h"
#ifdef USE_KDRV_CODES_FOR_L9
#include "de_def.h"
#include "l9/de_reg_def_l9.h"

#include "dimm_kapi.h"
#include "l9/dimm_reg_l9.h"
#include "l9/dimm_regp_l9.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

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
static volatile DIMM_REG_L9_T gDIMM_L9;

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
int DIMM_REG_L9_Create(void)
{
	int ret = RET_OK;

	gDIMM_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DIMM_REG_L9_T));
	gDIMM_L9.phys.addr = (volatile UINT32 *)ioremap(DTVSOC_DIMM_L9_BASE, sizeof(DIMM_REG_L9_T));

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
int DIMM_REG_L9_Destroy(void)
{
	int ret = RET_OK;

	OS_Free((void *)gDIMM_L9.shdw.addr);
	if (gDIMM_L9.phys.addr) iounmap((void *)gDIMM_L9.phys.addr);

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
int DIMM_REG_L9_Init(LX_DIMM_INFO_T *pstParams)
{
	int ret = RET_OK;
	LX_DIMM_LUT_CTRL_T dimmLut;

	DIMM_L9_FLWf(cmem_addr_clr, mem_addr_clr, 1);

	DIMM_L9_RdFL(blu_type);
	switch (pstParams->blType) {
		case LX_BL_NOR_LED	:
		case LX_BL_IOP_LED	:
		case LX_BL_ALEF_LED :
		case LX_BL_IOL_LED	:
			DIMM_L9_Wr01(blu_type, edge_lit, 0);
			break;
		case LX_BL_EDGE_LED :
			DIMM_L9_Wr01(blu_type, edge_lit, 1);
			DIMM_L9_Wr01(blu_type, edge_type, 1);
			break;
		case LX_BL_CCFL		:
		default :
			break;
	}
	DIMM_L9_WrFL(blu_type);

	do {
		if (!pstParams->u32length) break;
		if (!pstParams->InitData) break;
		dimmLut.pLut   = pstParams->InitData;
		dimmLut.u32Num = pstParams->u32length;

		ret = DIMM_REG_L9_LutControl(&dimmLut);
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
int DIMM_REG_L9_LocaldimmingControl(BOOLEAN *pstParams)
{
	int ret = RET_OK;
	UINT32 spiCmdMode = 0;

	DIMM_L9_FLRf(spi_cmd_num, spi_cmd_mode, spiCmdMode);
	switch (spiCmdMode) {
		case 0 :
			DIMM_L9_RdFL(spi_cmd01);
			DIMM_L9_WfCM(spi_cmd01, spi_cmd0, *pstParams, 0x1);
			DIMM_L9_WrFL(spi_cmd01);
			break;
		case 1 :
			DIMM_L9_RdFL(spi_cmd01);
			DIMM_L9_WfCM(spi_cmd01, spi_cmd1, *pstParams, 0x1);
			DIMM_L9_WrFL(spi_cmd01);
			break;
		case 2 :
			DIMM_L9_RdFL(spi_cmd23);
			DIMM_L9_WfCM(spi_cmd23, spi_cmd2, *pstParams, 0x1);
			DIMM_L9_WrFL(spi_cmd23);
			break;
		case 3 :
			DIMM_L9_RdFL(spi_cmd23);
			DIMM_L9_WfCM(spi_cmd23, spi_cmd3, *pstParams, 0x1);
			DIMM_L9_WrFL(spi_cmd23);
			break;
		default :
			break;
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
int DIMM_REG_L9_StoreDemo(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	DIMM_L9_FLCM(dbg_ctrl, demo_en, *pstParams, 1);

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
int DIMM_REG_L9_LineDemo(LX_DIMM_LINE_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		DIMM_L9_FLCM(dbg_ctrl, pb_en, pstParams->bEnable, 0x1);

		switch (pstParams->ePatEn) {
			case LX_DIMM_DEMO_PATTERN_NORMAL :
			case LX_DIMM_DEMO_PATTERN_SQUARE :
			case LX_DIMM_DEMO_PATTERN_GRID :
			case LX_DIMM_DEMO_PATTERN_GRADATION_R :
			case LX_DIMM_DEMO_PATTERN_GRADATION_G :
			case LX_DIMM_DEMO_PATTERN_GRADATION_B :
			case LX_DIMM_DEMO_PATTERN_COLOR_BAR :
				DIMM_L9_FLWf(pat_en, pat_en, pstParams->ePatEn);
				break;
			default :
				BREAK_WRONG(pstParams->ePatEn);
		}
		if (ret) break;

		DIMM_L9_RdFL(pat_hv_ppf);
		DIMM_L9_Wr01(pat_hv_ppf, pat_v_ppf, (pstParams->u8Vppf & 0xff));
		DIMM_L9_Wr01(pat_hv_ppf, pat_h_ppf, (pstParams->u8Hppf & 0xff));
		DIMM_L9_WrFL(pat_hv_ppf);
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
int DIMM_REG_L9_ControlCompensation(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	DIMM_L9_FLCM(pc_en, comp_en, *pstParams, 0x1);

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
int DIMM_REG_L9_LutControl(LX_DIMM_LUT_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 tableLenth;
	UINT32 sizeAddr;
	UINT32 lutData;
	UINT32 lutAddr;
	int i, idx, lutSize;

	do {
		tableLenth = pstParams->u32Num;
		if (!tableLenth) break;
		CHECK_KNULL(pstParams->pLut);

		for (idx=0;idx<tableLenth;)
		{
			sizeAddr = pstParams->pLut[idx++];
			lutSize  = GET_BITS(sizeAddr, 16, 16);
			lutAddr  = GET_BITS(sizeAddr,  0, 16);
			if (!lutSize) BREAK_WRONG(lutSize);
			if (GET_BITS(lutAddr, 0, 2)) BREAK_WRONG(lutAddr);

			lutAddr += (UINT32)gDIMM_L9.phys.addr;
			for(i=0;i<lutSize;i++)
			{
				if (!(idx<tableLenth)) BREAK_WRONG(tableLenth);
				lutData = pstParams->pLut[idx++];
				REG_WD(lutAddr, lutData);
			}
		}
	} while (0);

	return ret;
}

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
int DIMM_REG_L9_StoreControl(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	DIMM_L9_FLCM(dbg_ctrl, apf_en, *pstParams, 1);

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
int DIMM_REG_L9_WbColorControl(LX_DIMM_WBCOLOR_CTRL_T *pstParams)
{
	int ret = RET_OK;

	//printk("\n[%s,%d]0x%x,0x%x,0x%x\n\n",__func__,__LINE__,pstParams->rOffsetGain,pstParams->gOffsetGain,pstParams->bOffsetGain);
	DIMM_L9_FLWr(wb_r_gain_offset, pstParams->rOffsetGain);
	DIMM_L9_FLWr(wb_g_gain_offset, pstParams->gOffsetGain);
	DIMM_L9_FLWr(wb_b_gain_offset, pstParams->bOffsetGain);

	return ret;
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
int DIMM_REG_L9_RegWr(LX_DIMM_REG_WRITE_T *pstParams)
{
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 value;
	UINT32 virtAddr = 0;

	do {
		recvAddr = pstParams->wr_addr;
		value	 = pstParams->wr_data;
		if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DIMM_L9_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_DIMM_L9_BASE;
		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;

		virtAddr = (UINT32)ioremap(currAddr, 0x8);
		if (currAddr == recvAddr) {
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(virtAddr);
		nextValue = REG_RD((virtAddr+4));

		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);

		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);

		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(virtAddr		,currValue);
		REG_WD((virtAddr+4) ,nextValue);
	} while (0);
	if (virtAddr) iounmap((void *)virtAddr);

	return RET_OK;
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
UINT32 DIMM_REG_L9_RegRd(UINT32 addr)
{
	UINT32 value;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 virtAddr = 0;

	do {
		recvAddr = addr;
		if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DIMM_L9_BASE;
		else if (recvAddr <= 0xffff) recvAddr += DTVSOC_DIMM_L9_BASE;

		currAddr = recvAddr;
		currAddr >>= 2;
		currAddr <<= 2;
		virtAddr = (UINT32)ioremap(currAddr, 0x8);

		value = REG_RD(virtAddr);
		if (currAddr == recvAddr) break;

		nextValue = REG_RD(virtAddr+4);
		dBit = (recvAddr - virtAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	} while (0);
	if (virtAddr) iounmap((void *)virtAddr);

	return value;
}

#endif
/**  @} */
