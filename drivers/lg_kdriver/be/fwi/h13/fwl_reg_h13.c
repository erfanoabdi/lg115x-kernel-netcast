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
 *  fw loader reg driver file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.06
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/delay.h>


#include "os_util.h"
#include "be_dbg.h"

#include "be_def.h"
#include "be_cfg.h"
#include "fwl_reg_h13.h"
#include "h13/be_dppb_reg_h13.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern BE_MEM_CFG_T *gpBeMem;

extern DPPB_TOP_REG_H13_T gDPPB_TOP_H13;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief download BE firmware
 *
 * @param ucIndex [IN] index information for new firmware
 * @param pucBuff [IN] pointer information for new firmware
 * @param ulSize [IN] size information for new firmware
 * @param bIsMcuFw [IN] boolean information for MCU firmware or not
 *
 * @return FW base address if success, NULL for otherwise
 */
UINT32 FWL_REG_H13_FW_Download(UINT8 ucIndex, UINT8 *pucBuff, UINT32 ulSize, BOOLEAN bIsMcuFw)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;
	char            *lpAddr = NULL;

	do {
		CHECK_NULL(pucBuff);
		CHECK_NULL(ulSize);
		if(ucIndex >= BE_CH_MEM_DOWNLOAD_FW_MAX) 
		{
			BREAK_WRONG(ucIndex);
		}

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[ucIndex];
		CHECK_NULL(pFwMem);
		
		if(bIsMcuFw)
		{
			BOOLEAN         run_stall = 0;
			
			DPPB_TOP_H13_RdFL(top_runstall);
			DPPB_TOP_H13_Rd01(top_runstall, runstall, run_stall);
			if(!run_stall) break;
		}
		
		lpAddr = (char *)ioremap(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(lpAddr);
		memcpy(lpAddr, pucBuff, ulSize);

		if(bIsMcuFw)
		{
			DPPB_TOP_H13_RdFL(top_tr_addr_offset_0);
			DPPB_TOP_H13_Wr01(top_tr_addr_offset_0, tr_addr_offset_0, pFwMem->fw_base);
			DPPB_TOP_H13_WrFL(top_tr_addr_offset_0);
			
			msleep(10); // wait ddr to ddr transition

			DPPB_TOP_H13_Wr01(top_runstall, runstall, 0);
			DPPB_TOP_H13_WrFL(top_runstall);

			msleep(10); // wait ddr to ddr/mcu-iram transition
		}

		iounmap(lpAddr);
	} while(0);
	
	return ret == RET_OK ? pFwMem->fw_base : (UINT32)NULL;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check mcu is alive
 *
 * @param void
 *
 * @return TRUE if mcu run, FALSE for otherwise
 */
BOOLEAN FWL_REG_H13_MCUisAlive(void)
{
	BOOLEAN isFwRun = FALSE;
	DPPB_TOP_H13_FLRf(top_stat_vector_sel, stat_vector_sel, isFwRun);
	return TRUE;//isFwRun;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief return firmware memory base size
 *
 * @param ucIndex [IN] index information for the firmware
 *
 * @return firmware memory base size if success, 0 for otherwise
 */
UINT32 FWL_REG_H13_GetFwMemBaseSize(UINT8 ucIndex)
{
	int ret = RET_OK;

	do {
		if(ucIndex >= BE_CH_MEM_DOWNLOAD_FW_MAX) 
		{
			BREAK_WRONG(ucIndex);
			break;
		}
	} while(0);
	
	return ret == RET_OK ? gpBeMem->fw[ucIndex].fw_size : (UINT32)0;
}
