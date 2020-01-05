/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/


/** @file
 *
 *  sdec driver
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */


/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <asm/io.h>


#include "os_util.h"

#include "sdec_hal.h"
#include "sdec_reg.h"
#include "l9/sdec_reg_l9a0.h"
#include "l9/sdec_reg_l9b0.h"
#include "h13/sdec_reg_h13a0.h"


#include "l9/base_addr_sw_l9.h"
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/
volatile SDTOP_REG_H13A0_T *stSDEC_TOP_RegH13A0;
volatile SDTOP_REG_H13A0_T stSDEC_TOP_RegShadowH13A0[1];	

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static volatile	SDTOP_REG_A0_T *stSDEC_TOP_RegA0;
static volatile	SDTOP_REG_A0_T stSDEC_TOP_RegShadowA0[1];

static volatile	SDTOP_REG_B0_T *stSDEC_TOP_RegB0;
static volatile	SDTOP_REG_B0_T stSDEC_TOP_RegShadowB0[1];


int SDEC_HAL_TOPInit(void)
{
	int ret = RET_ERROR;
	LX_ADDR_SW_CFG_T addr_sw_cfg_sdec;

	
	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		stSDEC_TOP_RegH13A0	= (SDTOP_REG_H13A0_T *)ioremap(H13_SDEC_TOP_REG_BASE, 0x20);
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
		stSDEC_TOP_RegB0	= (SDTOP_REG_B0_T *)ioremap(L9_SDEC_TOP_REG_BASE, 0x20);
	else
		stSDEC_TOP_RegA0	= (SDTOP_REG_A0_T *)ioremap(L9_SDEC_TOP_REG_BASE, 0x20);
	
	//add address sw setting for L9 logical memory map
	// jinhwan.bae TBD for H13 , same as L9? maybe.
	BASE_L9_GetAddrSwCfg( ADDR_SW_CFG_TE_SDEC , &addr_sw_cfg_sdec );

	SDTOP_RdFL(addr_sw0);
	SDTOP_RdFL(addr_sw1);
	SDTOP_RdFL(addr_sw2);
	SDTOP_Wr(addr_sw0, addr_sw_cfg_sdec.de_sav);
	SDTOP_Wr(addr_sw1, addr_sw_cfg_sdec.cpu_gpu);
	SDTOP_Wr(addr_sw2, addr_sw_cfg_sdec.cpu_shadow);
	SDTOP_WrFL(addr_sw0);
	SDTOP_WrFL(addr_sw1);
	SDTOP_WrFL(addr_sw2);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_SetVideoOut(UINT8 idx, UINT8 sel)
{
	int ret = RET_ERROR;

	SDTOP_RdFL(vid_out_sel);

	switch(idx)
	{
		/* vid 0 & vid1 is obsolete */
//		case 0 : SDTOP_Wr01(vid_out_sel, vid0_sel, sel); break;
//		case 1 : SDTOP_Wr01(vid_out_sel, vid1_sel, sel); break;
		case 2 : SDTOP_Wr01(vid_out_sel, vid2_sel, sel); break;
		default : goto exit;
	}

	SDTOP_WrFL(vid_out_sel);
	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_SetPVRSrc(UINT8 idx, UINT8 sel)
{
	int ret = RET_ERROR;

	SDTOP_RdFL(dl_sel);

	switch(idx)
	{
		case 0 : SDTOP_Wr01(dl_sel, dl0_sel, sel); break;
		case 1 : SDTOP_Wr01(dl_sel, dl1_sel, sel); break;
		default : goto exit;
	}

	SDTOP_WrFL(dl_sel);
	ret = RET_OK;

exit:
	return ret;
}

