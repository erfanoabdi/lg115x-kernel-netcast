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

#include "sdec_drv.h"

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
volatile SDIO_REG_H13A0_T	*stSDEC_IO_RegH13A0;
volatile SDIO_REG_H13A0_T	stSDEC_IO_RegShadowH13A0[1];

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static volatile	SDIO_REG_A0_T 	*stSDEC_IO_RegA0;
static volatile	SDIO_REG_A0_T 	stSDEC_IO_RegShadowA0[1];

static volatile	SDIO_REG_B0_T 	*stSDEC_IO_RegB0;
static volatile	SDIO_REG_B0_T 	stSDEC_IO_RegShadowB0[1];




int SDEC_HAL_IOInit(void)
{
	int ret = RET_ERROR;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
		stSDEC_IO_RegH13A0	 	= (SDIO_REG_H13A0_T *)ioremap(H13_SDEC_IO_REG_BASE, 0x200);
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
		stSDEC_IO_RegB0	 	= (SDIO_REG_B0_T *)ioremap(L9_SDEC_IO_REG_BASE, 0x200);
	else
		stSDEC_IO_RegA0	 	= (SDIO_REG_A0_T *)ioremap(L9_SDEC_IO_REG_BASE, 0x200);
	

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_SetGPBBaseAddr(UINT8 gpb_base)
{
	int ret = RET_ERROR;

	SDIO_RdFL(gpb_base_addr);
	SDIO_Wr01(gpb_base_addr, gpb_base, gpb_base);
	SDIO_WrFL(gpb_base_addr);

	ret = RET_OK;
	return ret;
}

UINT32 SDEC_HAL_GetSTCCErrorCtrl(UINT8 idx)
{
	UINT32	val  = 0;
	
	SDIO_RdFL(stcc_err_ctrl[idx]);
	SDIO_Rd(stcc_err_ctrl[idx], val);	/* read */

	return val;
}

int SDEC_HAL_SetSTCCErrorCtrl(UINT8 idx, UINT32 err_max, UINT8 en)
{
	int ret = RET_ERROR;

	SDIO_RdFL(stcc_err_ctrl[idx]);
	SDIO_Wr01(stcc_err_ctrl[idx], err_max, err_max);
	SDIO_Wr01(stcc_err_ctrl[idx], en, en);
	SDIO_WrFL(stcc_err_ctrl[idx]);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_SDMWCLastBValidMode(UINT8 en)
{
	int ret = RET_ERROR;

	SDIO_RdFL(test);
	SDIO_Wr01(test, last_bval, en);
	SDIO_WrFL(test);

	ret = RET_OK;

	return ret;
}


int SDEC_HAL_EnableVideoReady(UINT8 idx, UINT8 en)
{
	int ret = RET_ERROR;

	SDIO_RdFL(test);
	switch(idx)
	{
		case 0 : SDIO_Wr01(test, vid0_rdy_en, en); break;
		case 1 : SDIO_Wr01(test, vid1_rdy_en, en); break;
		default : goto exit;
	}
	SDIO_WrFL(test);

	ret = RET_OK;

exit:
	return ret;
}


int SDEC_HAL_EnableAudioReady(UINT8 idx, UINT8 en)
{
	int ret = RET_ERROR;

	SDIO_RdFL(test);
	switch(idx)
	{
		case 0 : SDIO_Wr01(test, aud0_rdy_en, en); break;
		case 1 : SDIO_Wr01(test, aud1_rdy_en, en); break;
		default : goto exit;
	}
	SDIO_WrFL(test);

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_EnableAutoIncr(UINT8 en)
{
	int ret = RET_ERROR;

	SDIO_RdFL(test);
	SDIO_Wr01(test, auto_incr, en);
	SDIO_WrFL(test);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_SetTs2PesPid(UINT16 pid)
{
	int ret = RET_ERROR;

	SDIO_RdFL(cdic2_ts2pes);
	SDIO_Wr01(cdic2_ts2pes, PID, pid);
	SDIO_WrFL(cdic2_ts2pes);

	ret = RET_OK;
	return ret;
}

UINT16 SDEC_HAL_GetTs2PesPid(void)
{
	UINT16	val  = 0;

	SDIO_RdFL(cdic2_ts2pes);
	SDIO_Rd01(cdic2_ts2pes, PID, val);

	return val;
}

UINT32 SDEC_HAL_IntrStatReadAndClear(void)
{
	UINT32 val = 0;

	SDIO_RdFL(intr_stat);
	SDIO_Rd(intr_stat, val);	/* read */
	SDIO_WrFL(intr_stat);		/* clear */

	return val;
}

int SDEC_HAL_EnableIntrPcr(UINT8 en)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(intr_en);
	SDIO_Wr01(intr_en, pcr, en);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrTimeBaseDiscontinuity(UINT8 en)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(intr_en);
	SDIO_Wr01(intr_en, tb_dcont, en);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrBDRC(UINT8 idx, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT8	val = 0;

	SDIO_RdFL(intr_en);
	SDIO_Rd01(intr_en, bdrc, val);

	val |= ( 1 << idx );

	SDIO_Wr01(intr_en, bdrc, val);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrErrReport(UINT8 en)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(intr_en);
	SDIO_Wr01(intr_en, err_rpt, en);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrGPBData(UINT8 ch, UINT8 isHigh, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT8	val = 0;

	SDIO_RdFL(intr_en);
	SDIO_Rd01(intr_en, gpb_data, val);

	/* CH A + Low  = 0 + 0 = 0
	 * CH A + High = 0 + 1 = 1
	 * CH B + Low  = 2 + 0 = 2
	 * CH B + High = 2 + 1 = 3
	 */
	val |= 1 << ( ch * 2 + isHigh );

	SDIO_Wr01(intr_en, gpb_data, val);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrGPBFull(UINT8 ch, UINT8 isHigh, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT8	val = 0;

	SDIO_RdFL(intr_en);
	SDIO_Rd01(intr_en, gpb_full, val);

	/* CH A + Low  = 0 + 0 = 0
	 * CH A + High = 0 + 1 = 1
	 * CH B + Low  = 2 + 0 = 2
	 * CH B + High = 2 + 1 = 3
	 */
	val |= 1 << ( ch * 2 + isHigh );

	SDIO_Wr01(intr_en, gpb_full, val);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrTPInfo(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT8	val = 0;

	SDIO_RdFL(intr_en);
	SDIO_Rd01(intr_en, tp_info, val);

	val |= ( 1 << ch );

	SDIO_Wr01(intr_en, tp_info, val);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableIntrSectionErr(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT8	val = 0;

	SDIO_RdFL(intr_en);
	SDIO_Rd01(intr_en, sec_err, val);

	val |= ( 1 << ch );

	SDIO_Wr01(intr_en, sec_err, val);
	SDIO_WrFL(intr_en);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_EnableInterrupt(E_SDEC_INTR_T eSdecIntrSrc, UINT8 en)
{
	int 	ret = RET_ERROR;

	switch(eSdecIntrSrc)
	{
		case PCR:					SDEC_HAL_EnableIntrPcr(en);	break;

		case TB_DCOUNT:				SDEC_HAL_EnableIntrTimeBaseDiscontinuity(en);	break;

		case BDRC_0:				SDEC_HAL_EnableIntrBDRC(0, en);	break;
		case BDRC_1:				SDEC_HAL_EnableIntrBDRC(1, en);	break;
		case BDRC_2:				SDEC_HAL_EnableIntrBDRC(2, en);	break;
		case BDRC_3:				SDEC_HAL_EnableIntrBDRC(3, en);	break;

		case ERR_RPT:				SDEC_HAL_EnableIntrErrReport(en);	break;

		case GPB_DATA_CHA_GPL:		SDEC_HAL_EnableIntrGPBData(0, 0, en);	break;
		case GPB_DATA_CHA_GPH:		SDEC_HAL_EnableIntrGPBData(0, 1, en);	break;
		case GPB_DATA_CHB_GPL:		SDEC_HAL_EnableIntrGPBData(1, 0, en);	break;
		case GPB_DATA_CHB_GPH:		SDEC_HAL_EnableIntrGPBData(1, 1, en);	break;

		case GPB_FULL_CHA_GPL:		SDEC_HAL_EnableIntrGPBFull(0, 0, en);	break;
		case GPB_FULL_CHA_GPH:		SDEC_HAL_EnableIntrGPBFull(0, 1, en);	break;
		case GPB_FULL_CHB_GPL:		SDEC_HAL_EnableIntrGPBFull(1, 0, en);	break;
		case GPB_FULL_CHB_GPH:		SDEC_HAL_EnableIntrGPBFull(1, 1, en);	break;

		case TP_INFO_CHA:			SDEC_HAL_EnableIntrTPInfo(0, en);	break;
		case TP_INFO_CHB:			SDEC_HAL_EnableIntrTPInfo(1, en);	break;
		case SEC_ERR_CHA:			SDEC_HAL_EnableIntrSectionErr(0, en);	break;
		case SEC_ERR_CHB:			SDEC_HAL_EnableIntrSectionErr(1, en);	break;
		default:					goto exit;
		break;
	}

	ret = RET_OK;

exit:
	return ret;
}

UINT32 SDEC_HAL_GetErrorInterruptStat(void)
{
	UINT32 val = 0;

	SDIO_RdFL(err_intr_stat);
	SDIO_Rd(err_intr_stat, val);	/* read */

	return val;
}

int SDEC_HAL_EnableErrorInterrupt(E_SDEC_ERRINTR_T eSdecErrIntr, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(err_intr_en);
	switch(eSdecErrIntr)
	{
		case MPG_SD:		SDIO_Wr01(err_intr_en, mpg_sd, val);	break;
		case MPG_CC:		SDIO_Wr01(err_intr_en, mpg_cc, val);	break;
		case MPG_DUP:		SDIO_Wr01(err_intr_en, mpg_dup, val);	break;
		case MPG_TS:		SDIO_Wr01(err_intr_en, mpg_ts, val);	break;
		case MPG_PD:		SDIO_Wr01(err_intr_en, mpg_pd, val);	break;
		case STCC_DCONT:	SDIO_Wr01(err_intr_en, stcc_dcont, val);	break;
		case CDIF_RPAGE:	SDIO_Wr01(err_intr_en, cdif_rpage, val);	break;
		case CDIF_WPAGE:	SDIO_Wr01(err_intr_en, cdif_wpage, val);	break;
		case CDIF_OVFLOW:	SDIO_Wr01(err_intr_en, cdif_ovflow, val);	break;
		case SB_DROPPED:	SDIO_Wr01(err_intr_en, sb_dropped, val);	break;
		case SYNC_LOST:		SDIO_Wr01(err_intr_en, sync_lost, val);	break;
		case TEST_DCONT:	SDIO_Wr01(err_intr_en, test_dcont, val);	break;
		default:					goto exit;
		break;
	}
	SDIO_WrFL(err_intr_en);

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_SDMWCReset(UINT32 val)
{
	int 	ret = RET_ERROR;

	if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
	{
		SD_RdFL_H13A0(SDIO, sdmwc_sw_reset);
		SD_Wr_H13A0(SDIO, sdmwc_sw_reset, val);
		SD_WrFL_H13A0(SDIO, sdmwc_sw_reset);
	}
	else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
	{
		SD_RdFL_B0(SDIO, sdmwc_sw_reset);
		SD_Wr_B0(SDIO, sdmwc_sw_reset, val);
		SD_WrFL_B0(SDIO, sdmwc_sw_reset);
	}

	ret = RET_OK;
	
	return ret;
}

UINT32 SDEC_HAL_SDMWCGet(void)
{
	UINT32			val = 0;

	if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
	{
		SD_RdFL_H13A0(SDIO, sdmwc_sw_reset);
		SD_Rd_H13A0(SDIO, sdmwc_sw_reset, val);
	}
	else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
	{
		SD_RdFL_B0(SDIO, sdmwc_sw_reset);
		SD_Rd_B0(SDIO, sdmwc_sw_reset, val);
	}
	
	return val;
}

UINT32 SDEC_HAL_SDMWCGetStatus(void)
{
	UINT32			val = 0;

	if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
	{
		SD_RdFL_H13A0(SDIO, sdmwc_stat);
		SD_Rd_H13A0(SDIO, sdmwc_stat, val);
	}
	else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
	{
		SD_RdFL_B0(SDIO, sdmwc_stat);
		SD_Rd_B0(SDIO, sdmwc_stat, val);
	}
	return val;
}

UINT32 SDEC_HAL_STCCGetASG(void)
{
	UINT32	val = 0;

	SDIO_RdFL(stcc_asg);
	SDIO_Rd(stcc_asg, val);

	return val;
}


UINT8 SDEC_HAL_STCCGetMain(void)
{
	UINT8	val = 0;

	SDIO_RdFL(stcc_asg);
	SDIO_Rd01(stcc_asg, main, val);
	return val;
}

int SDEC_HAL_STCCSetMain(UINT8 ch)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(stcc_asg);
	SDIO_Wr01(stcc_asg, main, ch);
	SDIO_WrFL(stcc_asg);

	ret = RET_OK;
	return ret;
}

int SDEC_HAL_STCCSetVideoAssign(UINT8 idx, UINT8 ch)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(stcc_asg);
	switch(idx)
	{
		case 0: SDIO_Wr01(stcc_asg, vid0, ch);	break;
		case 1: SDIO_Wr01(stcc_asg, vid1, ch);	break;
		default : goto exit;
	}
	SDIO_WrFL(stcc_asg);

	ret = RET_OK;
exit:
	return ret;
}

int SDEC_HAL_STCCSetAudioAssign(UINT8 idx, UINT8 ch)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(stcc_asg);
	switch(idx)
	{
		case 0: SDIO_Wr01(stcc_asg, aud0, ch);	break;
		case 1: SDIO_Wr01(stcc_asg, aud1, ch);	break;
		default : goto exit;
	}
	SDIO_WrFL(stcc_asg);

	ret = RET_OK;
exit:
	return ret;
}

UINT32 SDEC_HAL_STCCGetReg(UINT8 ch)
{
	UINT32 val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);

	return val;
}

int SDEC_HAL_STCCSetReg(UINT8 ch, UINT32 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);

	ret = RET_OK;

	return ret;
}


int SDEC_HAL_STCCSetSTC(UINT8 ch, UINT32 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(stcc[ch * 4 + 1]);
	SDIO_Wr(stcc[ch * 4 + 1], val);
	SDIO_WrFL(stcc[ch * 4 + 1]);

	ret = RET_OK;

	return ret;
}


UINT32 SDEC_HAL_STCCGetSTC(UINT8 ch, UINT8 isHigh)
{
	UINT32	val = 0;

	switch(isHigh)
	{
		case 0:
			SDIO_RdFL(stcc[ch * 4 + 3]);
			SDIO_Rd(stcc[ch * 4 + 3], val);
			val = extract_bits(val, 0x3FF, 16);
			break;
		case 1:
			SDIO_RdFL(stcc[ch * 4 + 1]);
			SDIO_Rd(stcc[ch * 4 + 1], val);
			break;
		default : val = -1; break;
	}

	return val;
}

UINT32 SDEC_HAL_STCCGetPCR(UINT8 ch, UINT8 isHigh)
{
	UINT32	val = 0;

	switch(isHigh)
	{
		case 0:
			SDIO_RdFL(stcc[ch * 4 + 3]);
			SDIO_Rd(stcc[ch * 4 + 3], val);
			val = extract_bits(val, 0x3FF, 0);
			break;
		case 1:
			SDIO_RdFL(stcc[ch * 4 + 2]);
			SDIO_Rd(stcc[ch * 4 + 2], val);
			break;
		default : val = -1; break;
	}

	return val;
}

int SDEC_HAL_STCCEnable(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);
	val |= ( en << 31);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_STCCSetCh(UINT8 ch, UINT8 chan)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);
	val |= ( chan << 29);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);


	ret = RET_OK;

	return ret;
}

int SDEC_HAL_STCCEnableCopy(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);
	val |= ( en << 1);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_STCCEnableLatch(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);
	val |= ( en << 0);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_STCCReset(UINT8 ch)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);
	val |= ( 1 << 30);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_AVSTCReset(UINT8 ch)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;
	/* AV STC Reset Condition, from IPT , 2013. 02. 26 */
	UINT32	val_stc_9_0 = 0x32b;
	UINT32 	val_stc_41_10 = 0xffffffff;

	/* Set stc_41_10 */
	SDIO_RdFL(stcc[ch * 4 + 1]);
	SDIO_Rd(stcc[ch * 4 + 1], val);
	val |= ( val_stc_41_10 ); // set all 1 to stc_41_10
	SDIO_Wr(stcc[ch * 4 + 1], val);
	SDIO_WrFL(stcc[ch * 4 + 1]);
	
	/* Set stc_9_0 */
	SDIO_RdFL(stcc[ch * 4 + 3]);
	SDIO_Rd(stcc[ch * 4 + 3], val);
	val &= ( 0xfc00ffff );	// reset stc_9_0
	val |= ( val_stc_9_0 << 16);
	SDIO_Wr(stcc[ch * 4 + 3], val);
	SDIO_WrFL(stcc[ch * 4 + 3]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_STCCSetPCRPid(UINT8 ch, UINT16 pid)
{
	int 	ret = RET_ERROR;
	UINT32	val = 0;

	SDIO_RdFL(stcc[ch * 4]);
	SDIO_Rd(stcc[ch * 4], val);
	val |= ( pid << 16);
	SDIO_Wr(stcc[ch * 4], val);
	SDIO_WrFL(stcc[ch * 4]);


	ret = RET_OK;

	return ret;
}


int SDEC_HAL_STCCSetSubStccRate(UINT32 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(sub_stcc_rate);
	SDIO_Wr(sub_stcc_rate, val);
	SDIO_WrFL(sub_stcc_rate);

	ret = RET_OK;

	return ret;
}


UINT32 SDEC_HAL_STCCGetSubStccRate(void)
{
	UINT32	val = 0;

	SDIO_RdFL(sub_stcc_rate);
	SDIO_Rd(sub_stcc_rate, val);

	return val;
}

int SDEC_HAL_GSTC(UINT32 *pStcc_bs_32_1, UINT32 *pStcc_bs_0)
{
	int 	ret = RET_OK;

	if( lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		*pStcc_bs_32_1 		= stSDEC_IO_RegH13A0->gstc0.stcc_bs_32_1;
		*pStcc_bs_0 		= stSDEC_IO_RegH13A0->gstc0.stcc_bs_0;
	}
	else if( lx_chip_rev() < LX_CHIP_REV(L9, B0))
	{
		SD_RdFL_A0(SDIO, stcc_g);
		SD_Rd01_A0(SDIO, stcc_g, stcc_41_10, *pStcc_bs_32_1);
		SD_Rd01_A0(SDIO, stcc_g, stcc_9_0, *pStcc_bs_0);
		*pStcc_bs_0 = *pStcc_bs_0 >> 9;
	}
	else if( lx_chip_rev() <= LX_CHIP_REV(L9, B2))
	{
		//SD_RdFL_B0(SDIO, gstc);
		//SD_Rd01_B0(SDIO, gstc, stcc_bs_32_1, *pStcc_bs_32_1);
		//SD_Rd01_B0(SDIO, gstc, stcc_bs_0, *pStcc_bs_0);
		*pStcc_bs_32_1 	= stSDEC_IO_RegB0->gstc.stcc_bs_32_1;
		*pStcc_bs_0 		= stSDEC_IO_RegB0->gstc.stcc_bs_0;
	}
	else
	{
		ret = RET_ERROR;
	}
	
	return ret;
}


int SDEC_HAL_GSTCReset(void)
{
	int 	ret = RET_OK;

	if( lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		SD_RdFL_H13A0(SDIO, gstc0);
		SD_Wr01_H13A0(SDIO, gstc0, rst, 1);
		SD_WrFL_H13A0(SDIO, gstc0);
	}
	else if( lx_chip_rev() < LX_CHIP_REV(L9, B0))
	{
		SD_RdFL_A0(SDIO, stcc_g);
		SD_Wr01_A0(SDIO, stcc_g, rst, 1);
		SD_WrFL_A0(SDIO, stcc_g);
	}
	else if( lx_chip_rev() <= LX_CHIP_REV(L9, B2))
	{
		SD_RdFL_B0(SDIO, gstc);
		SD_Wr01_B0(SDIO, gstc, rst, 1);
		SD_WrFL_B0(SDIO, gstc);
	}
	else
	{
		ret = RET_ERROR;
	}

	return ret;
}

int SDEC_HAL_GSTC1(UINT32 *pStcc_bs_32_1, UINT32 *pStcc_bs_0)
{
	int 	ret = RET_OK;

	if( lx_chip_rev() >= LX_CHIP_REV(H13, B0))
	{
		*pStcc_bs_32_1 		= stSDEC_IO_RegH13A0->gstc1.stcc_bs_32_1;
		*pStcc_bs_0 		= stSDEC_IO_RegH13A0->gstc1.stcc_bs_0;
	}
	else
	{
		ret = RET_ERROR;
	}
	
	return ret;
}


int SDEC_HAL_GSTC1Reset(void)
{
	int 	ret = RET_OK;

	if( lx_chip_rev() >= LX_CHIP_REV(H13, B0))
	{
		SD_RdFL_H13A0(SDIO, gstc1);
		SD_Wr01_H13A0(SDIO, gstc1, rst, 1);
		SD_WrFL_H13A0(SDIO, gstc1);
	}
	else
	{
		ret = RET_ERROR;
	}

	return ret;
}


int SDEC_HAL_DSCSetCasType(UINT8 ch, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], cas_type, val);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_DSCSetBlkMode(UINT8 ch, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], blk_mode, val);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_DSCSetResMode(UINT8 ch, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], res_mode, val);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_DSCSetKeySize(UINT8 ch, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], key_size, val);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_DSCEnablePESCramblingCtrl(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], psc_en, en);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_DSCSetEvenMode(UINT8 ch, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], even_mode, val);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_DSCSetOddMode(UINT8 ch, UINT8 val)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdic_dsc[ch]);
	SDIO_Wr01(cdic_dsc[ch], odd_mode, val);
	SDIO_WrFL(cdic_dsc[ch]);

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_SetParallelInput(UINT8 isExternal)
{
	int 			ret 		= RET_ERROR;

	if (lx_chip_rev() <= LX_CHIP_REV(L9, A1))
	{
		SD_RdFL_A0(SDIO, cdin_parallel_sel);
		SD_Wr01_A0(SDIO, cdin_parallel_sel, p_sel, isExternal);
		SD_WrFL_A0(SDIO, cdin_parallel_sel);
	}

	ret = RET_OK;

	return ret;
}

int SDEC_HAL_CIDCReset(UINT8 ch)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Wr01(cdic2, rst, 1);
		SDIO_WrFL(cdic2);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Wr01_H13A0(SDIO, cdic3, rst, 1);
			SD_WrFL_H13A0(SDIO, cdic3);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Wr01_B0(SDIO, cdic3, rst, 1);
			SD_WrFL_B0(SDIO, cdic3);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Wr01(cdic[ch], rst, 1);
		SDIO_WrFL(cdic[ch]);
	}

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_CIDCMinSyncByteDetection(UINT8 ch, UINT8 val)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Wr01(cdic2, min_sb_det, val);
		SDIO_WrFL(cdic2);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Wr01_H13A0(SDIO, cdic3, min_sb_det, val);
			SD_WrFL_H13A0(SDIO, cdic3);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Wr01_B0(SDIO, cdic3, min_sb_det, val);
			SD_WrFL_B0(SDIO, cdic3);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Wr01(cdic[ch], min_sb_det, val);
		SDIO_WrFL(cdic[ch]);
	}

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_CIDCMaxSyncByteDrop(UINT8 ch, UINT8 val)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Wr01(cdic2, max_sb_drp, val);
		SDIO_WrFL(cdic2);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Wr01_H13A0(SDIO, cdic3, max_sb_drp, val);
			SD_WrFL_H13A0(SDIO, cdic3);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Wr01_B0(SDIO, cdic3, max_sb_drp, val);
			SD_WrFL_B0(SDIO, cdic3);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Wr01(cdic[ch], max_sb_drp, val);
		SDIO_WrFL(cdic[ch]);
	}

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_CIDCSetSrc(UINT8 ch, UINT8 val)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Wr01(cdic2, src, val);
		SDIO_WrFL(cdic2);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Wr01_H13A0(SDIO, cdic3, src, val);
			SD_WrFL_H13A0(SDIO, cdic3);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Wr01_B0(SDIO, cdic3, src, val);
			SD_WrFL_B0(SDIO, cdic3);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Wr01(cdic[ch], src, val);
		SDIO_WrFL(cdic[ch]);
	}

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_CIDCRead(UINT8 ch, UINT32 *pVal)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Rd(cdic2, *pVal);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Rd_H13A0(SDIO, cdic3, *pVal);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Rd_B0(SDIO, cdic3, *pVal);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Rd(cdic[ch], *pVal);
	}

	ret = RET_OK;

exit:
	return ret;
}

int SDEC_HAL_CIDCGetStatus(UINT8 ch, CDIC *pCdic)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Rd01(cdic2, 	src, 			pCdic->src);
		SDIO_Rd01(cdic2, 	no_wdata, 		pCdic->no_wdata);
		SDIO_Rd01(cdic2, 	sync_lost,		pCdic->sync_lost);
		SDIO_Rd01(cdic2, 	sb_dropped,		pCdic->sb_dropped);
		SDIO_Rd01(cdic2, 	cdif_empty,		pCdic->cdif_empty);
		SDIO_Rd01(cdic2, 	cdif_full,		pCdic->cdif_full);
		SDIO_Rd01(cdic2, 	pd_wait,		pCdic->pd_wait);
		SDIO_Rd01(cdic2, 	cdif_ovflow,	pCdic->cdif_ovflow);
		SDIO_Rd01(cdic2, 	cdif_wpage,		pCdic->cdif_wpage);
		SDIO_Rd01(cdic2, 	cdif_rpage,		pCdic->cdif_rpage);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Rd01_H13A0(SDIO, cdic3, 	src, 			pCdic->src);
			SD_Rd01_H13A0(SDIO, cdic3, 	no_wdata, 		pCdic->no_wdata);
			SD_Rd01_H13A0(SDIO, cdic3, 	sync_lost,		pCdic->sync_lost);
			SD_Rd01_H13A0(SDIO, cdic3, 	sb_dropped,		pCdic->sb_dropped);
			SD_Rd01_H13A0(SDIO, cdic3, 	cdif_empty,		pCdic->cdif_empty);
			SD_Rd01_H13A0(SDIO, cdic3, 	cdif_full,		pCdic->cdif_full);
			SD_Rd01_H13A0(SDIO, cdic3, 	pd_wait,		pCdic->pd_wait);
			SD_Rd01_H13A0(SDIO, cdic3, 	cdif_ovflow,	pCdic->cdif_ovflow);
			SD_Rd01_H13A0(SDIO, cdic3, 	cdif_wpage,		pCdic->cdif_wpage);
			SD_Rd01_H13A0(SDIO, cdic3, 	cdif_rpage,		pCdic->cdif_rpage);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Rd01_B0(SDIO, cdic3, 	src, 			pCdic->src);
			SD_Rd01_B0(SDIO, cdic3, 	no_wdata, 		pCdic->no_wdata);
			SD_Rd01_B0(SDIO, cdic3, 	sync_lost,		pCdic->sync_lost);
			SD_Rd01_B0(SDIO, cdic3, 	sb_dropped,		pCdic->sb_dropped);
			SD_Rd01_B0(SDIO, cdic3, 	cdif_empty,		pCdic->cdif_empty);
			SD_Rd01_B0(SDIO, cdic3, 	cdif_full,		pCdic->cdif_full);
			SD_Rd01_B0(SDIO, cdic3, 	pd_wait,		pCdic->pd_wait);
			SD_Rd01_B0(SDIO, cdic3, 	cdif_ovflow,	pCdic->cdif_ovflow);
			SD_Rd01_B0(SDIO, cdic3, 	cdif_wpage,		pCdic->cdif_wpage);
			SD_Rd01_B0(SDIO, cdic3, 	cdif_rpage,		pCdic->cdif_rpage);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Rd01(cdic[ch], 	src, 			pCdic->src);
		SDIO_Rd01(cdic[ch], 	no_wdata, 		pCdic->no_wdata);
		SDIO_Rd01(cdic[ch], 	sync_lost,		pCdic->sync_lost);
		SDIO_Rd01(cdic[ch], 	sb_dropped,		pCdic->sb_dropped);
		SDIO_Rd01(cdic[ch], 	cdif_empty,		pCdic->cdif_empty);
		SDIO_Rd01(cdic[ch], 	cdif_full,		pCdic->cdif_full);
		SDIO_Rd01(cdic[ch], 	pd_wait,		pCdic->pd_wait);
		SDIO_Rd01(cdic[ch], 	cdif_ovflow,	pCdic->cdif_ovflow);
		SDIO_Rd01(cdic[ch], 	cdif_wpage,		pCdic->cdif_wpage);
		SDIO_Rd01(cdic[ch], 	cdif_rpage,		pCdic->cdif_rpage);
	}

	ret = RET_OK;

exit:
	return ret;
}

UINT8 SDEC_HAL_CIDCGetCdif_OverFlow(UINT8 ch)
{
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;
	UINT8	val = 0;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Rd01(cdic2, cdif_ovflow, val);

	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Rd01_H13A0(SDIO, cdic3, cdif_ovflow, val);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Rd01_B0(SDIO, cdic3, cdif_ovflow, val);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Rd01(cdic[ch], cdif_ovflow, val);
	}

exit:
	return val;
}

UINT8 SDEC_HAL_CIDCGetCdif_Full(UINT8 ch)
{
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;
	UINT8	val = 0;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Rd01(cdic2, cdif_full, val);

	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Rd01_H13A0(SDIO, cdic3, cdif_full, val);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Rd01_B0(SDIO, cdic3, cdif_full, val);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Rd01(cdic[ch], cdif_full, val);
	}

exit:
	return val;
}

UINT32 SDEC_HAL_CIDCGet(UINT8 ch)
{
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;
	UINT32			val = 0;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	LX_SDEC_HAL_CHECK_CH(pSdecConf,ch);

	/* if channel is just simple channel */
	if( pSdecConf->chInfo[ch].capa_lev == 0 )
	{
		SDIO_RdFL(cdic2);
		SDIO_Rd(cdic2, val);
	}
	/* if channel is just for recording */
	else if( ch == 3 )
	{
		if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
		{
			SD_RdFL_H13A0(SDIO, cdic3);
			SD_Rd_H13A0(SDIO, cdic3, val);
		}
		else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
		{
			SD_RdFL_B0(SDIO, cdic3);
			SD_Rd_B0(SDIO, cdic3, val);
		}
	}
	else
	{
		SDIO_RdFL(cdic[ch]);
		SDIO_Rd(cdic[ch], val);
	}

exit:
	return val;
}

int SDEC_HAL_CIDC3DlConf(UINT8 ch, UINT8 val)
{
	int 			ret 		= RET_ERROR;
	LX_SDEC_CFG_T* 	pSdecConf 	= NULL;

	/* get chip configuation */
	pSdecConf = SDEC_CFG_GetConfig();

	/* this is only work to chip version which has 4 channel */
	LX_SDEC_HAL_CHECK_CH(pSdecConf, 3);

	/* value is 0, 1 */
	if( val > 1 )	goto exit;

	switch(ch)
	{
		case 0: /* DL0_SEL */
			if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
			{
				SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
				SD_Wr01_H13A0(SDIO, cdic3_dl_conf, dl0_sel, val);
				SD_WrFL_H13A0(SDIO, cdic3_dl_conf);
			}
			else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
			{
				SD_RdFL_B0(SDIO, cdic3_dl_conf);
				SD_Wr01_B0(SDIO, cdic3_dl_conf, dl0_sel, val);
				SD_WrFL_B0(SDIO, cdic3_dl_conf);
			}
			break;
		case 1: /* DL1_SEL */
			if( lx_chip_rev()	>= LX_CHIP_REV(H13, A0) )
			{
				SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
				SD_Wr01_H13A0(SDIO, cdic3_dl_conf, dl1_sel, val);
				SD_WrFL_H13A0(SDIO, cdic3_dl_conf);
			}
			else if( lx_chip_rev()	>= LX_CHIP_REV(L9, B0) )
			{
				SD_RdFL_B0(SDIO, cdic3_dl_conf);
				SD_Wr01_B0(SDIO, cdic3_dl_conf, dl1_sel, val);
				SD_WrFL_B0(SDIO, cdic3_dl_conf);
			}
			break;
		default :
			goto exit;
	}

	ret = RET_OK;

exit:
	return ret;
}


int SDEC_HAL_CDIC2PIDFSetPidfData(UINT8 idx, UINT32 val)
{
	int ret = RET_ERROR;

	/* read register */
	SD_RdFL_H13A0(SDIO, cdic3_dl_conf);

	/* write index , data, write enable */
	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf_addr, idx);
	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf_val, val);
	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pid_wr_en, SDEC_HAL_ENABLE);
	
	SD_WrFL_H13A0(SDIO, cdic3_dl_conf);
	
	ret = RET_OK;
	return ret;
}


UINT32 SDEC_HAL_CDIC2PIDFGetPidfData(UINT8 idx)
{
	UINT32 val = 0;

	/* set pid filter index */
	SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf_addr, idx);
	SD_WrFL_H13A0(SDIO, cdic3_dl_conf);

	/* read data */
	SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
	SD_Rd01_H13A0(SDIO, cdic3_dl_conf, pidf_val, val);
	
	return val;
}


int SDEC_HAL_CDIC2PIDFEnablePidFilter(UINT8 idx, UINT8 en)
{
	int ret = RET_ERROR;

	SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
	switch(idx){
		case 0:	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf0_en, en);	break;
		case 1:	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf1_en, en);	break;
		case 2:	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf2_en, en);	break;
		case 3:	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, pidf3_en, en);	break;
		default : break;
	}
	SD_WrFL_H13A0(SDIO, cdic3_dl_conf);

	ret = RET_OK;
	return ret;
}

UINT8 SDEC_HAL_CDIC2GetPIDFEnable(UINT8 idx)
{
	UINT8 en = SDEC_HAL_DISABLE;

	SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
	switch(idx){
		case 0:	SD_Rd01_H13A0(SDIO, cdic3_dl_conf, pidf0_en, en);	break;
		case 1:	SD_Rd01_H13A0(SDIO, cdic3_dl_conf, pidf1_en, en);	break;
		case 2:	SD_Rd01_H13A0(SDIO, cdic3_dl_conf, pidf2_en, en);	break;
		case 3:	SD_Rd01_H13A0(SDIO, cdic3_dl_conf, pidf3_en, en);	break;
		default : break;
	}
	SD_WrFL_H13A0(SDIO, cdic3_dl_conf);

	return en;
}



int SDEC_HAL_CDIC2DlExtConf(UINT8 ch, UINT8 val)
{
	int ret = RET_ERROR;

	SD_RdFL_H13A0(SDIO, cdic3_dl_conf);
	switch(ch){
		case 0:	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, dl0_ext_sel, val);	break;
		case 1:	SD_Wr01_H13A0(SDIO, cdic3_dl_conf, dl1_ext_sel, val);	break;
		default : break;
	}
	SD_WrFL_H13A0(SDIO, cdic3_dl_conf);

	ret = RET_OK;
	return ret;
}




int SDEC_HAL_CDIPEnable(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdip[ch]);
	SDIO_Wr01(cdip[ch], en, en);
	SDIO_WrFL(cdip[ch]);

	ret = RET_OK;

	return ret;
}

#if 1
/**
 * Set CDIP setting
 *
 * @param	idx				[in] CDIP index
 * @param	isParallel		[in] is this port using for parallel or serial ( 0 = serial 1 = parallel )
 * @param	isFirst			[in] is this port first in parallel? only used if isParallel is 1.
 * @return	if succeeded - RET_OK, else - RET_ERROR.
 */
int SDEC_HAL_CDIP(UINT8 idx,	LX_SDEC_CFG_INPUT_T *pCfg)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdip[idx]);

	if(pCfg != NULL)
	{
		SDIO_Wr01(cdip[idx], sync_type, 	pCfg->sync_type);
		SDIO_Wr01(cdip[idx], pconf, 		pCfg->pconf);
		SDIO_Wr01(cdip[idx], clk_div,		pCfg->clk_div);
		SDIO_Wr01(cdip[idx], val_en,		pCfg->val_en);
		SDIO_Wr01(cdip[idx], en,			1);
		SDIO_Wr01(cdip[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
		SDIO_Wr01(cdip[idx], val_en,		pCfg->val_en);
		SDIO_Wr01(cdip[idx], req_en,		pCfg->req_en);
		SDIO_Wr01(cdip[idx], err_en,		pCfg->err_en);
		SDIO_Wr01(cdip[idx], req_act_lo,	pCfg->req_act_lo);
		SDIO_Wr01(cdip[idx], val_act_lo,	pCfg->val_act_lo);
		SDIO_Wr01(cdip[idx], clk_act_lo,	pCfg->clk_act_lo);
		SDIO_Wr01(cdip[idx], err_act_hi,	pCfg->err_act_hi);
		SDIO_Wr01(cdip[idx], test_en,		0);
	}
	else
	{
		SDIO_Wr01(cdip[idx], sync_type, 	SDEC_HAL_CDIP_47DETECTION);
		SDIO_Wr01(cdip[idx], clk_div,		0x8);
		SDIO_Wr01(cdip[idx], pconf, 		SDEC_HAL_CDIP_SERIAL_0);
		SDIO_Wr01(cdip[idx], val_en,		0);
		SDIO_Wr01(cdip[idx], en,			0);
		SDIO_Wr01(cdip[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
		SDIO_Wr01(cdip[idx], val_en,		0);
		SDIO_Wr01(cdip[idx], req_en,		0);
		SDIO_Wr01(cdip[idx], err_en,		0);
		SDIO_Wr01(cdip[idx], req_act_lo,	0);
		SDIO_Wr01(cdip[idx], val_act_lo,	0);
		SDIO_Wr01(cdip[idx], clk_act_lo,	0);
		SDIO_Wr01(cdip[idx], err_act_hi,	0);
		SDIO_Wr01(cdip[idx], test_en,		0);

	}

	SDIO_WrFL(cdip[idx]);

	ret = RET_OK;

	return ret;
}
#else
/**
 * Set CDIP setting
 *
 * @param	idx				[in] CDIP index
 * @param	isParallel		[in] is this port using for parallel or serial ( 0 = serial 1 = parallel )
 * @param	isFirst			[in] is this port first in parallel? only used if isParallel is 1.
 * @return	if succeeded - RET_OK, else - RET_ERROR.
 */
int SDEC_HAL_CDIP(UINT8 idx,	UINT8 isParallel, UINT8 isFirst, UINT8 isClockActLow, UINT8 isValEnable)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdip[idx]);
#if 0
	switch(isParallel)
	{
		/* serial */
		case SDEC_HAL_CDIP_SERIAL:
			SDIO_Wr01(cdip[idx], sync_type, 	SDEC_HAL_CDIP_POS_SOP);
			SDIO_Wr01(cdip[idx], clk_div,		0x14);
			SDIO_Wr01(cdip[idx], pconf, 		SDEC_HAL_CDIP_SERIAL_0);
			SDIO_Wr01(cdip[idx], val_en, 		1);
			SDIO_Wr01(cdip[idx], en,			1);
			break;

		/* parallel */
		case SDEC_HAL_CDIP_PARALLEL:
			SDIO_Wr01(cdip[idx], sync_type, 	SDEC_HAL_CDIP_47DETECTION);

			if (isFirst == SDEC_HAL_CDIP_FIRST)
			{
				SDIO_Wr01(cdip[idx], clk_div,		0x14);
				SDIO_Wr01(cdip[idx], pconf, 		SDEC_HAL_CDIP_PARALLEL_0);
				SDIO_Wr01(cdip[idx], val_en,		1);
				SDIO_Wr01(cdip[idx], en,			1);
			}
			else
			{
				/* this is second or third port in parallel */
				SDIO_Wr01(cdip[idx], clk_div,		0x8);
				SDIO_Wr01(cdip[idx], pconf, 		SDEC_HAL_CDIP_SERIAL_0);
				SDIO_Wr01(cdip[idx], val_en,		0);
				SDIO_Wr01(cdip[idx], en,			0);
			}
			break;

	}
#else
	switch(isParallel)
	{
		/* serial */
		case SDEC_HAL_CDIP_SERIAL:
			SDIO_Wr01(cdip[idx], sync_type, 	SDEC_HAL_CDIP_POS_SOP);
			SDIO_Wr01(cdip[idx], pconf, 		SDEC_HAL_CDIP_SERIAL_0);
			break;

		/* parallel */
		case SDEC_HAL_CDIP_PARALLEL:
			SDIO_Wr01(cdip[idx], sync_type, 	SDEC_HAL_CDIP_47DETECTION);
			SDIO_Wr01(cdip[idx], pconf, 		SDEC_HAL_CDIP_PARALLEL_0);

			break;

	}

	switch(isFirst)
	{
		/* this is first port in parallel or serial port */
		case SDEC_HAL_CDIP_FIRST:
			SDIO_Wr01(cdip[idx], clk_div,		0x14);
			SDIO_Wr01(cdip[idx], val_en,		1);
			SDIO_Wr01(cdip[idx], en,			1);
			break;
		/* this is second or third port in parallel */
		case SDEC_HAL_CDIP_FOLLOWER:
			SDIO_Wr01(cdip[idx], clk_div,		0x8);
			SDIO_Wr01(cdip[idx], en,			0);
	}
#endif

	/* common setting */
	SDIO_Wr01(cdip[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
	SDIO_Wr01(cdip[idx], val_en,		isValEnable);
	SDIO_Wr01(cdip[idx], req_en,		0);
	SDIO_Wr01(cdip[idx], err_en,		0);
	SDIO_Wr01(cdip[idx], req_act_lo,	0);
	SDIO_Wr01(cdip[idx], val_act_lo,	0);
	SDIO_Wr01(cdip[idx], clk_act_lo,	isClockActLow);
	SDIO_Wr01(cdip[idx], err_act_hi,	0);
	SDIO_Wr01(cdip[idx], test_en,		0);

	SDIO_WrFL(cdip[idx]);

	ret = RET_OK;

	return ret;
}
#endif

int SDEC_HAL_CDIOPEnable(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdiop[ch]);
	SDIO_Wr01(cdiop[ch], en, en);
	SDIO_WrFL(cdiop[ch]);

	ret = RET_OK;

	return ret;
}

/**
 * Set CDIOP setting
 *
 * @param	idx				[in] CDIP index
 * @param	inout			[in] 0 : in 1: out
 * @return	if succeeded - RET_OK, else - RET_ERROR.
 */
#if 1
int SDEC_HAL_CDIOP(UINT8 idx,	LX_SDEC_CFG_INPUT_T *pCfg)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdiop[idx]);

	SDIO_Wr01(cdiop[idx], sync_type, 	pCfg->sync_type);
	SDIO_Wr01(cdiop[idx], pconf, 		pCfg->pconf);
	SDIO_Wr01(cdiop[idx], clk_div,		pCfg->clk_div);
	SDIO_Wr01(cdiop[idx], val_en,		pCfg->val_en);
	SDIO_Wr01(cdiop[idx], cdinout,		pCfg->cdin_out);
	SDIO_Wr01(cdiop[idx], val_sel,		pCfg->val_sel);
	SDIO_Wr01(cdiop[idx], en,			1);
	SDIO_Wr01(cdiop[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
	SDIO_Wr01(cdiop[idx], val_en,		pCfg->val_en);
	SDIO_Wr01(cdiop[idx], req_en,		pCfg->req_en);
	SDIO_Wr01(cdiop[idx], err_en,		pCfg->err_en);
	SDIO_Wr01(cdiop[idx], req_act_lo,	pCfg->req_act_lo);
	SDIO_Wr01(cdiop[idx], val_act_lo,	pCfg->val_act_lo);
	SDIO_Wr01(cdiop[idx], clk_act_lo,	pCfg->clk_act_lo);
	SDIO_Wr01(cdiop[idx], err_act_hi,	pCfg->err_act_hi);
	SDIO_Wr01(cdiop[idx], test_en,		0);

	SDIO_WrFL(cdiop[idx]);

	ret = RET_OK;

	return ret;
}

#else
int SDEC_HAL_CDIOP(UINT8 idx, UINT8 inout, UINT8 isClockActLow, UINT8 isValEnable)
{
	int 	ret = RET_ERROR;

	SDIO_RdFL(cdiop[idx]);

	SDIO_Wr01(cdiop[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
	SDIO_Wr01(cdiop[idx], sync_type, 	SDEC_HAL_CDIP_POS_SOP);
	SDIO_Wr01(cdiop[idx], clk_div,		0x14);
	SDIO_Wr01(cdiop[idx], pconf, 		SDEC_HAL_CDIOP_SERIAL_0);
	SDIO_Wr01(cdiop[idx], cdinout,		inout);
	SDIO_Wr01(cdiop[idx], val_sel,		2);
	SDIO_Wr01(cdiop[idx], req_en,		0);
	SDIO_Wr01(cdiop[idx], val_en,		isValEnable);
	SDIO_Wr01(cdiop[idx], err_en,		0);
	SDIO_Wr01(cdiop[idx], req_act_lo,	0);
	SDIO_Wr01(cdiop[idx], val_act_lo,	0);
	SDIO_Wr01(cdiop[idx], clk_act_lo,	isClockActLow);
	SDIO_Wr01(cdiop[idx], err_act_hi,	0);
	SDIO_Wr01(cdiop[idx], test_en,		0);
	SDIO_Wr01(cdiop[idx], en,			1);

	SDIO_WrFL(cdiop[idx]);

	ret = RET_OK;

	return ret;
}
#endif

int SDEC_HAL_CDIPAEnable(UINT8 ch, UINT8 en)
{
	int 	ret = RET_ERROR;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		SD_RdFL_H13A0(SDIO, cdipa[ch]);
		SD_Wr01_H13A0(SDIO, cdipa[ch], en, en);
		SD_WrFL_H13A0(SDIO, cdipa[ch]);

		ret = RET_OK;
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		SD_RdFL_B0(SDIO, cdipa[ch]);
		SD_Wr01_B0(SDIO, cdipa[ch], en, en);
		SD_WrFL_B0(SDIO, cdipa[ch]);

		ret = RET_OK;
	}

	return ret;
}


/**
 * Set CDIP setting
 *
 * @param	idx				[in] CDIP index
 * @param	isParallel		[in] is this port using for parallel or serial ( 0 = serial 1 = parallel )
 * @param	isFirst			[in] is this port first in parallel? only used if isParallel is 1.
 * @return	if succeeded - RET_OK, else - RET_ERROR.
 */
int SDEC_HAL_CDIPA(UINT8 idx,	LX_SDEC_CFG_INPUT_T *pCfg)
{
	int 	ret = RET_ERROR;

	if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{
		SD_RdFL_H13A0(SDIO, cdipa[idx]);

		if(pCfg != NULL)
		{
			SD_Wr01_H13A0(SDIO, cdipa[idx], sync_type, 	pCfg->sync_type);
			SD_Wr01_H13A0(SDIO, cdipa[idx], pconf, 		pCfg->pconf);
			SD_Wr01_H13A0(SDIO, cdipa[idx], clk_div,		pCfg->clk_div);
			SD_Wr01_H13A0(SDIO, cdipa[idx], val_en,		pCfg->val_en);
			SD_Wr01_H13A0(SDIO, cdipa[idx], en,			1);
			SD_Wr01_H13A0(SDIO, cdipa[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
			SD_Wr01_H13A0(SDIO, cdipa[idx], val_en,		pCfg->val_en);
			SD_Wr01_H13A0(SDIO, cdipa[idx], req_en,		pCfg->req_en);
			SD_Wr01_H13A0(SDIO, cdipa[idx], err_en,		pCfg->err_en);
			SD_Wr01_H13A0(SDIO, cdipa[idx], req_act_lo,	pCfg->req_act_lo);
			SD_Wr01_H13A0(SDIO, cdipa[idx], val_act_lo,	pCfg->val_act_lo);
			SD_Wr01_H13A0(SDIO, cdipa[idx], clk_act_lo,	pCfg->clk_act_lo);
			SD_Wr01_H13A0(SDIO, cdipa[idx], err_act_hi,	pCfg->err_act_hi);
			SD_Wr01_H13A0(SDIO, cdipa[idx], test_en,		0);
		}
		else
		{
			SD_Wr01_H13A0(SDIO, cdipa[idx], sync_type, 	SDEC_HAL_CDIP_47DETECTION);
			SD_Wr01_H13A0(SDIO, cdipa[idx], clk_div,		0x8);
			SD_Wr01_H13A0(SDIO, cdipa[idx], pconf, 		SDEC_HAL_CDIP_SERIAL_0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], val_en,		0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], en,			0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
			SD_Wr01_H13A0(SDIO, cdipa[idx], val_en,		0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], req_en,		0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], err_en,		0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], req_act_lo,	0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], val_act_lo,	0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], clk_act_lo,	0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], err_act_hi,	0);
			SD_Wr01_H13A0(SDIO, cdipa[idx], test_en,		0);
		}

		SD_WrFL_H13A0(SDIO, cdipa[idx]);

		ret = RET_OK;
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
	{
		SD_RdFL_B0(SDIO, cdipa[idx]);

		if(pCfg != NULL)
		{
			SD_Wr01_B0(SDIO, cdipa[idx], sync_type, 	pCfg->sync_type);
			SD_Wr01_B0(SDIO, cdipa[idx], pconf, 		pCfg->pconf);
			SD_Wr01_B0(SDIO, cdipa[idx], clk_div,		pCfg->clk_div);
			SD_Wr01_B0(SDIO, cdipa[idx], val_en,		pCfg->val_en);
			SD_Wr01_B0(SDIO, cdipa[idx], en,			1);
			SD_Wr01_B0(SDIO, cdipa[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
			SD_Wr01_B0(SDIO, cdipa[idx], val_en,		pCfg->val_en);
			SD_Wr01_B0(SDIO, cdipa[idx], req_en,		pCfg->req_en);
			SD_Wr01_B0(SDIO, cdipa[idx], err_en,		pCfg->err_en);
			SD_Wr01_B0(SDIO, cdipa[idx], req_act_lo,	pCfg->req_act_lo);
			SD_Wr01_B0(SDIO, cdipa[idx], val_act_lo,	pCfg->val_act_lo);
			SD_Wr01_B0(SDIO, cdipa[idx], clk_act_lo,	pCfg->clk_act_lo);
			SD_Wr01_B0(SDIO, cdipa[idx], err_act_hi,	pCfg->err_act_hi);
			SD_Wr01_B0(SDIO, cdipa[idx], test_en,		0);
		}
		else
		{
			SD_Wr01_B0(SDIO, cdipa[idx], sync_type, 	SDEC_HAL_CDIP_47DETECTION);
			SD_Wr01_B0(SDIO, cdipa[idx], clk_div,		0x8);
			SD_Wr01_B0(SDIO, cdipa[idx], pconf, 		SDEC_HAL_CDIP_SERIAL_0);
			SD_Wr01_B0(SDIO, cdipa[idx], val_en,		0);
			SD_Wr01_B0(SDIO, cdipa[idx], en,			0);
			SD_Wr01_B0(SDIO, cdipa[idx], dtype, 		SDEC_HAL_CDIP_MPEG2TS);
			SD_Wr01_B0(SDIO, cdipa[idx], val_en,		0);
			SD_Wr01_B0(SDIO, cdipa[idx], req_en,		0);
			SD_Wr01_B0(SDIO, cdipa[idx], err_en,		0);
			SD_Wr01_B0(SDIO, cdipa[idx], req_act_lo,	0);
			SD_Wr01_B0(SDIO, cdipa[idx], val_act_lo,	0);
			SD_Wr01_B0(SDIO, cdipa[idx], clk_act_lo,	0);
			SD_Wr01_B0(SDIO, cdipa[idx], err_act_hi,	0);
			SD_Wr01_B0(SDIO, cdipa[idx], test_en,		0);
		}

		SD_WrFL_B0(SDIO, cdipa[idx]);

		ret = RET_OK;
	}


	return ret;
}

