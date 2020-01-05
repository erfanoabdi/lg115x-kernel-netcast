
/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *  
 *  This program is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU General Public License 
 *  version 2 as published by the Free Software Foundation.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *   GNU General Public License for more details.
*/ 

/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     sooya.joo@lge.com
 * version    0.1
 * date       2010.03.11
 * note       Additional information.
 *
 * @addtogroup h13_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "../../../mcu/vdec_type_defs.h"
#include "../lg1154_vdec_base.h"
#include "../../../mcu/os_adap.h"
#include "rc0_reg.h"
#include "rc1_reg.h"
#include "../top_hal_api.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define VDEC_RC0_BASE					(H13_VDEC_BASE + 0x0400)
#define VDEC_RC1_BASE					(H13_VDEC_BASE + 0x0600)

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

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static volatile RC0_REG_T			*stpRC0_Reg = NULL;
static volatile RC1_REG_T			*stpRC1_Reg = NULL;
static volatile RC0_REG_T			stpRC0_RegShadow[1];
static volatile RC1_REG_T			stpRC1_RegShadow[1];

/**
********************************************************************************
* @brief
*   register setting
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*   stpSdecParam :SDEC parameter
* @return
*  DTV_STATUS_T
********************************************************************************
*/
void TOP_HAL_Init(void)
{
	stpRC0_Reg		= (volatile RC0_REG_T *)VDEC_TranselateVirualAddr(VDEC_RC0_BASE, 0x100);
	stpRC1_Reg		= (volatile RC1_REG_T *)VDEC_TranselateVirualAddr(VDEC_RC1_BASE, 0x100);

/* Removed by Jin */
	// VDEC0 addr_switch
//	stpRC1_Reg->vdec0_axi_addr_sw_conf0= 0x340301D0;
//	stpRC1_Reg->vdec0_axi_addr_sw_conf1 = 0x000200D0;
//	stpRC1_Reg->vdec0_axi_addr_sw_conf2 = 0x0C0101C0;

	// VDEC1 addr_switch
//	stpRC1_Reg->vdec1_axi_addr_sw_conf0 = 0x340301D0;
//	stpRC1_Reg->vdec1_axi_addr_sw_conf1 = 0x000200D0;
//	stpRC1_Reg->vdec1_axi_addr_sw_conf2 = 0x0C0101C0;
}

UINT32 TOP_HAL_GetVersion(void)
{
	RC0_RdFL(version);

	return RC0_RdFL(version);
}

void TOP_HAL_ResetMach(UINT8 vcore_num)
{
	if(vcore_num>=MSVC_NUM_OF_CORE)
		return;

	RC0_RdFL(sw_reset);
	switch(vcore_num)
	{
	case 0:
		RC0_Wr01(sw_reset, sw_reset_mach0, 1);
		break;
	case 1:
		RC0_Wr01(sw_reset, sw_reset_mach1, 1);
		break;
	default:
		return;
	}
	RC0_WrFL(sw_reset);
}

void TOP_HAL_ResetPDECAll(void)
{
	RC0_RdFL(sw_reset);
	RC0_Wr01(sw_reset, sw_reset_pdec_all, 1);
	RC0_WrFL(sw_reset);
}

void TOP_HAL_SetPdecInputSelection(UINT8 ui8PdecCh, UINT8 ui8TECh)
{
	if(ui8PdecCh>=PDEC_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(pdec_in_conf);

	switch(ui8PdecCh)
	{
	case 0:
		RC0_Wr01(pdec_in_conf, reg_pdec0_in_sel, ui8TECh&0x3);
		RC0_Wr01(pdec_in_conf, reg_vid0_rdy_dis, 0);
		break;
	case 1:
		RC0_Wr01(pdec_in_conf, reg_pdec1_in_sel, ui8TECh&0x3);
		RC0_Wr01(pdec_in_conf, reg_vid1_rdy_dis, 0);
		break;
	case 2:
		RC0_Wr01(pdec_in_conf, reg_pdec2_in_sel, ui8TECh&0x3);
		RC0_Wr01(pdec_in_conf, reg_vid2_rdy_dis, 0);
		break;
	default:
		return;
	}
	RC0_WrFL(pdec_in_conf);
}

UINT8 TOP_HAL_GetPdecInputSelection(UINT8 ui8PdecCh)
{
	UINT8 ui8TECh;
	if(ui8PdecCh>=PDEC_NUM_OF_CHANNEL)
		return 0xFF;

	RC0_RdFL(pdec_in_conf);

	switch(ui8PdecCh)
	{
	case 0:
		RC0_Rd01(pdec_in_conf, reg_pdec0_in_sel, ui8TECh);
		break;
	case 1:
		RC0_Rd01(pdec_in_conf, reg_pdec1_in_sel, ui8TECh);
		break;
	case 2:
		RC0_Rd01(pdec_in_conf, reg_pdec2_in_sel, ui8TECh);
		break;
	}

	return ui8TECh;
}

void TOP_HAL_EnablePdecInput(UINT8 ui8PdecCh)
{
	if(ui8PdecCh>=PDEC_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(pdec_in_conf);

	switch(ui8PdecCh)
	{
	case 0:
		RC0_Wr01(pdec_in_conf, reg_pdec0_in_dis, 0);
		break;
	case 1:
		RC0_Wr01(pdec_in_conf, reg_pdec1_in_dis, 0);
		break;
	case 2:
		RC0_Wr01(pdec_in_conf, reg_pdec2_in_dis, 0);
		break;
	}
	RC0_WrFL(pdec_in_conf);
}

void TOP_HAL_DisablePdecInput(UINT8 ui8PdecCh)
{
	if(ui8PdecCh>=PDEC_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(pdec_in_conf);

	switch(ui8PdecCh)
	{
	case 0:
		RC0_Wr01(pdec_in_conf, reg_pdec0_in_dis, 1);
		break;
	case 1:
		RC0_Wr01(pdec_in_conf, reg_pdec1_in_dis, 1);
		break;
	case 2:
		RC0_Wr01(pdec_in_conf, reg_pdec2_in_dis, 1);
		break;
	}
	RC0_WrFL(pdec_in_conf);
}

UINT8 TOP_HAL_IsEnablePdecInput(UINT8 ui8PdecCh)
{
	UINT8 bDisable;

	if(ui8PdecCh>=PDEC_NUM_OF_CHANNEL)
		return -1;

	RC0_RdFL(pdec_in_conf);

	switch(ui8PdecCh)
	{
	case 0:
		RC0_Rd01(pdec_in_conf, reg_pdec0_in_dis, bDisable);
		break;
	case 1:
		RC0_Rd01(pdec_in_conf, reg_pdec1_in_dis, bDisable);
		break;
	case 2:
		RC0_Rd01(pdec_in_conf, reg_pdec2_in_dis, bDisable);
		break;
	}

	return (~bDisable)&0x1;
}

void TOP_HAL_SetLQSyncMode(UINT8 ui8LQCh, UINT8 ui8sync)
{
	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return;
	if(ui8sync>=DE_IF_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Wr01(lq_in_conf, reg_lqc0_sync_mode, ui8sync&0x1);
		break;
	case 1:
		RC0_Wr01(lq_in_conf, reg_lqc1_sync_mode, ui8sync&0x1);
		break;
	case 2:
		RC0_Wr01(lq_in_conf, reg_lqc2_sync_mode, ui8sync&0x1);
		break;
	case 3:
		RC0_Wr01(lq_in_conf, reg_lqc3_sync_mode, ui8sync&0x1);
		break;
	}
	RC0_WrFL(lq_in_conf);
}

UINT8 TOP_HAL_GetLQSyncMode(UINT8 ui8LQCh)
{
	UINT8 ui8syncMode;
	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return -1;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Rd01(lq_in_conf, reg_lqc0_sync_mode, ui8syncMode);
		break;
	case 1:
		RC0_Rd01(lq_in_conf, reg_lqc1_sync_mode, ui8syncMode);
		break;
	case 2:
		RC0_Rd01(lq_in_conf, reg_lqc2_sync_mode, ui8syncMode);
		break;
	case 3:
		RC0_Rd01(lq_in_conf, reg_lqc3_sync_mode, ui8syncMode);
		break;
	}

	return ui8syncMode;
}

void TOP_HAL_SetLQInputSelection(UINT8 ui8LQCh, UINT8 ui8PdecCh)
{
	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return;

	if(ui8PdecCh>=PDEC_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Wr01(lq_in_conf, reg_lq0_in_sel, ui8PdecCh&0x3);
		break;
	case 1:
		RC0_Wr01(lq_in_conf, reg_lq1_in_sel, ui8PdecCh&0x3);
		break;
	case 2:
		RC0_Wr01(lq_in_conf, reg_lq2_in_sel, ui8PdecCh&0x3);
		break;
	case 3:
		RC0_Wr01(lq_in_conf, reg_lq3_in_sel, ui8PdecCh&0x3);
		break;
	}
	RC0_WrFL(lq_in_conf);
}

UINT8 TOP_HAL_GetLQInputSelection(UINT8 ui8LQCh)
{
	UINT8 ui8PdecCh;
	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return -1;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Rd01(lq_in_conf, reg_lq0_in_sel, ui8PdecCh);
		break;
	case 1:
		RC0_Rd01(lq_in_conf, reg_lq1_in_sel, ui8PdecCh);
		break;
	case 2:
		RC0_Rd01(lq_in_conf, reg_lq2_in_sel, ui8PdecCh);
		break;
	case 3:
		RC0_Rd01(lq_in_conf, reg_lq3_in_sel, ui8PdecCh);
		break;
	}

	return ui8PdecCh;
}

void TOP_HAL_EnableLQInput(UINT8 ui8LQCh)
{
	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Wr01(lq_in_conf, reg_lq0_in_dis, 0);
		break;
	case 1:
		RC0_Wr01(lq_in_conf, reg_lq1_in_dis, 0);
		break;
	case 2:
		RC0_Wr01(lq_in_conf, reg_lq2_in_dis, 0);
		break;
	case 3:
		RC0_Wr01(lq_in_conf, reg_lq3_in_dis, 0);
		break;
	}
	RC0_WrFL(lq_in_conf);
}

void TOP_HAL_DisableLQInput(UINT8 ui8LQCh)
{
	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Wr01(lq_in_conf, reg_lq0_in_dis, 1);
		break;
	case 1:
		RC0_Wr01(lq_in_conf, reg_lq1_in_dis, 1);
		break;
	case 2:
		RC0_Wr01(lq_in_conf, reg_lq2_in_dis, 1);
		break;
	case 3:
		RC0_Wr01(lq_in_conf, reg_lq3_in_dis, 1);
		break;
	}
	RC0_WrFL(lq_in_conf);
}

UINT8 TOP_HAL_IsEnableLQInput(UINT8 ui8LQCh)
{
	UINT8 bDisable;

	if(ui8LQCh>=LQC_NUM_OF_CHANNEL)
		return -1;

	RC0_RdFL(lq_in_conf);

	switch(ui8LQCh)
	{
	case 0:
		RC0_Rd01(lq_in_conf, reg_lq0_in_dis, bDisable);
		break;
	case 1:
		RC0_Rd01(lq_in_conf, reg_lq1_in_dis, bDisable);
		break;
	case 2:
		RC0_Rd01(lq_in_conf, reg_lq2_in_dis, bDisable);
		break;
	case 3:
		RC0_Rd01(lq_in_conf, reg_lq3_in_dis, bDisable);
		break;
	}

	return (~bDisable)&0x1;
}

void TOP_HAL_SetMachIntrMode(UINT8 vcore_num, UINT8 IntrMode)
{
	if(vcore_num>=MSVC_NUM_OF_CORE)
		return;

	RC0_RdFL(mach_conf);
	switch(vcore_num)
	{
	case 0:
		RC0_Wr01(mach_conf, reg_mach0_intr_mode, (IntrMode&0x1));
		break;
	case 1:
		RC0_Wr01(mach_conf, reg_mach1_intr_mode, (IntrMode&0x1));
		break;
	default:
		return;
	}
	RC0_WrFL(mach_conf);

}

UINT8 TOP_HAL_GetMachIntrMode(UINT8 vcore_num)
{
	UINT8 IntrMode = -1;

	if(vcore_num>=MSVC_NUM_OF_CORE)
		return IntrMode;

	RC0_RdFL(mach_conf);
	switch(vcore_num)
	{
	case 0:
		RC0_Rd01(mach_conf, reg_mach0_intr_mode, IntrMode);
		break;
	case 1:
		RC0_Wr01(mach_conf, reg_mach1_intr_mode, IntrMode);
		break;
	default:
		break;
	}

	return IntrMode;
}

UINT8 TOP_HAL_GetMachIdleStatus(UINT8 vcore_num)
{
	UINT8 idleStatus = -1;

	if(vcore_num>=MSVC_NUM_OF_CORE)
		return idleStatus;

	RC0_RdFL(mach_conf);
	switch(vcore_num)
	{
	case 0:
		RC0_Rd01(mach_conf, reg_mach0_vpu_idle, idleStatus);
		break;
	case 1:
		RC0_Wr01(mach_conf, reg_mach1_vpu_idle, idleStatus);
		break;
	default:
		break;
	}

	return idleStatus;
}

UINT8 TOP_HAL_GetMachUnderRunStatus(UINT8 vcore_num)
{
	UINT8 underRun =-1;

	if(vcore_num>=MSVC_NUM_OF_CORE)
		return underRun;

	RC0_RdFL(mach_conf);
	switch(vcore_num)
	{
	case 0:
		RC0_Rd01(mach_conf, reg_mach0_vpu_underrun, underRun);
		break;
	case 1:
		RC0_Wr01(mach_conf, reg_mach1_vpu_underrun, underRun);
		break;
	default:
		break;
	}

	return underRun;
}

/*
	VDISP_CONF                       	sync_conf                       ;	// 0x001c : ''
	PDEC0_MAU_CONF                  	pdec0_mau_conf                  ;	// 0x0020 : ''
	PDEC1_MAU_CONF                  	pdec1_mau_conf                  ;	// 0x0024 : ''
	PDEC2_MAU_CONF                  	pdec2_mau_conf                  ;	// 0x0028 : ''
	PDEC3_MAU_CONF                  	pdec3_mau_conf                  ;	// 0x002c : ''
*/

void TOP_HAL_EnableExtIntr(VDEC_INTR_T ui32IntrSrc)
{
	RC0_RdFL(intr_e_en);
	RC0_Wr(intr_e_en, RC0_Rd(intr_e_en) |(1 << ui32IntrSrc));
	RC0_WrFL(intr_e_en);
}

int TOP_HAL_DisableExtIntr(VDEC_INTR_T ui32IntrSrc)
{
	int ret;

	RC0_RdFL(intr_e_en);

	ret = !! (RC0_Rd(intr_e_en) & (1 << ui32IntrSrc));
	RC0_Wr(intr_e_en, RC0_Rd(intr_e_en) & ~(1 << ui32IntrSrc));

	RC0_WrFL(intr_e_en);

	return ret;
}

void TOP_HAL_ClearExtIntr(VDEC_INTR_T ui32IntrSrc)
{
	RC0_RdFL(intr_e_cl);
	RC0_Wr(intr_e_cl, RC0_Rd(intr_e_cl) |(1 << ui32IntrSrc));
	RC0_WrFL(intr_e_cl);
}

void TOP_HAL_ClearExtIntrMsk(UINT32 ui32IntrMsk)
{
	RC0_RdFL(intr_e_cl);
	RC0_Wr(intr_e_cl, ui32IntrMsk);
	RC0_WrFL(intr_e_cl);
}

void TOP_HAL_DisableExtIntrAll(void)
{
	RC0_RdFL(intr_e_en);
	RC0_Wr(intr_e_en, 0x0);
	RC0_WrFL(intr_e_en);

	RC0_RdFL(intr_e_cl);
	RC0_Wr(intr_e_cl, 0xFFFFFFFF);
	RC0_WrFL(intr_e_cl);
}

UINT8 TOP_HAL_IsExtIntrEnable(VDEC_INTR_T eVdecIntrSrc)
{
	UINT32 ui32Intr;
	RC0_RdFL(intr_e_en);
	ui32Intr = RC0_Rd(intr_e_en);
	if(RC0_Rd(intr_e_en) & (1 << eVdecIntrSrc))
	{
		return TRUE;
	}

	return FALSE;
}

UINT32 TOP_HAL_GetExtIntrStatus(void)
{
	RC0_RdFL(intr_e_st);
	return RC0_Rd(intr_e_st);
}

void TOP_HAL_EnableInterIntr(VDEC_INTR_T ui32IntrSrc)
{
	RC0_RdFL(intr_i_en);
	RC0_Wr(intr_i_en, RC0_Rd(intr_i_en) |(1 << ui32IntrSrc));
	RC0_WrFL(intr_i_en);
}

void TOP_HAL_DisableInterIntr(VDEC_INTR_T ui32IntrSrc)
{
	RC0_RdFL(intr_i_en);
	RC0_Wr(intr_i_en, RC0_Rd(intr_i_en) & ~(1 << ui32IntrSrc));
	RC0_WrFL(intr_i_en);
}

void TOP_HAL_ClearInterIntr(VDEC_INTR_T ui32IntrSrc)
{
	RC0_RdFL(intr_i_cl);
	RC0_Wr(intr_i_cl, RC0_Rd(intr_i_cl) |(1 << ui32IntrSrc));
	RC0_WrFL(intr_i_cl);
}

void TOP_HAL_ClearInterIntrMsk(UINT32 ui32IntrMsk)
{
	RC0_RdFL(intr_i_cl);
	RC0_Wr(intr_i_cl, ui32IntrMsk);
	RC0_WrFL(intr_i_cl);
}

void TOP_HAL_DisableInterIntrAll(void)
{
	RC0_RdFL(intr_i_en);
	RC0_Wr(intr_i_en, 0x0);
	RC0_WrFL(intr_i_en);

	RC0_RdFL(intr_i_cl);
	RC0_Wr(intr_i_cl, 0xFFFFFFFF);
	RC0_WrFL(intr_i_cl);
}

UINT8 TOP_HAL_IsInterIntrEnable(VDEC_INTR_T ui32IntrSrc)
{
	UINT32 ui32Intr;
	RC0_RdFL(intr_i_en);
	ui32Intr = RC0_Rd(intr_i_en);
	if(RC0_Rd(intr_i_en) & (1 << ui32IntrSrc))
	{
		return TRUE;
	}

	return FALSE;
}

UINT32 TOP_HAL_GetInterIntrStatus(void)
{
	RC0_RdFL(intr_i_st);
	return RC0_Rd(intr_i_st);
}

void TOP_HAL_EnableBufIntr(BUFFER_INTR_T ui32IntrSrc)
{
	RC0_RdFL(bst_intr_en);
	RC0_Wr(bst_intr_en, RC0_Rd(bst_intr_en) |(1 << ui32IntrSrc));
	RC0_WrFL(bst_intr_en);
}

void TOP_HAL_DisableBufIntr(BUFFER_INTR_T ui32IntrSrc)
{
	RC0_RdFL(bst_intr_en);
	RC0_Wr(bst_intr_en, RC0_Rd(bst_intr_en) & ~(1 << ui32IntrSrc));
	RC0_WrFL(bst_intr_en);
}

void TOP_HAL_ClearBufIntr(BUFFER_INTR_T ui32IntrSrc)
{
	RC0_RdFL(bst_intr_cl);
	RC0_Wr(bst_intr_cl, RC0_Rd(bst_intr_cl) |(1 << ui32IntrSrc));
	RC0_WrFL(bst_intr_cl);
}

void TOP_HAL_ClearBufIntrMsk(UINT32 ui32IntrMsk)
{
	RC0_RdFL(bst_intr_cl);
	RC0_Wr(bst_intr_cl, ui32IntrMsk);
	RC0_WrFL(bst_intr_cl);
}


void TOP_HAL_DisableBufIntrAll(void)
{
	RC0_RdFL(bst_intr_en);
	RC0_Wr(bst_intr_en, 0x0);
	RC0_WrFL(bst_intr_en);

	RC0_RdFL(bst_intr_cl);
	RC0_Wr(bst_intr_cl, 0xFFFFFFFF);
	RC0_WrFL(bst_intr_cl);
}

UINT8 TOP_HAL_IsBufIntrEnable(BUFFER_INTR_T ui32IntrSrc)
{
	UINT32 ui32Intr;
	RC0_RdFL(bst_intr_en);
	ui32Intr = RC0_Rd(bst_intr_en);
	if(RC0_Rd(bst_intr_en) & (1 << ui32IntrSrc))
	{
		return TRUE;
	}

	return FALSE;
}

UINT32 TOP_HAL_GetBufIntrStatus(void)
{
	RC0_RdFL(bst_intr_st);
	return RC0_Rd(bst_intr_st);
}

UINT32 TOP_HAL_GetGSTCC(void)
{
	UINT32 ui32Gstcc;
	RC0_RdFL(gstc);
	RC0_Rd01(gstc, reg_gstcc, ui32Gstcc);
	return ui32Gstcc;
}

UINT32 TOP_HAL_SetApbMachOffset(UINT8 ui8CoreNume, UINT8 ui8Offset)
{
	UINT32 u32RetVal;

	RC0_RdFL(apb_conf);
	u32RetVal = RC0_Rd(apb_conf);

	switch( ui8CoreNume )
	{
	case 0:
		RC0_Wr01(apb_conf, reg_apb_mach0_offset, ui8Offset);
		break;

	case 1:
		RC0_Wr01(apb_conf, reg_apb_mach1_offset, ui8Offset);
		break;

	default:
		break;
	}

	RC0_WrFL(apb_conf);

	return u32RetVal;
}

UINT32 TOP_HAL_SetApbVDO(UINT8 ui8GdiSelection, UINT8 ui8Offset)
{
	UINT32 u32RetVal;

	RC0_RdFL(apb_conf);
	u32RetVal = RC0_Rd(apb_conf);

	RC0_Wr01(apb_conf, reg_apb_vdo_gdi_sel, ui8GdiSelection);
	RC0_Wr01(apb_conf, reg_app_vdo_offset, ui8Offset);
	RC0_WrFL(apb_conf);

	return u32RetVal;
}

UINT32 TOP_HAL_SetApbConfig(UINT32 ui32Value)
{
	UINT32 u32RetVal;

	RC0_RdFL(apb_conf);
	u32RetVal = RC0_Rd(apb_conf);

	RC0_Wr(apb_conf, ui32Value);
	RC0_WrFL(apb_conf);

	return u32RetVal;
}
void TOP_HAL_EnableFeedTimer(void)
{	
}

void TOP_HAL_DisableFeedTimer(void)
{
}

void TOP_HAL_SetFeedTimerValue(UINT32 ui32Value)
{
}

UINT32 TOP_HAL_GetFeedTimerValue(void)
{
	return 0;
}

/** @} */

