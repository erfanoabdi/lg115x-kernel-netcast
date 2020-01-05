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


/** @file apr_reg_l9.c
 *
 *  driver for 3d format auto detection. ( used only within kdriver )
 *	- functional functions regardless of modules
 *
 *	@author		justine.jeong
 *	@version	0.1
 *	@note
 *	@date		2012.07.10
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <mach/platform.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "l9/linux_platform.h"

#include "apr_core.h"
#include "apr_reg_l9.h"

/* external de module */
#include "l9/de_cfg_l9.h"
#include "l9/de_ctr_reg_l9.h"
#include "l9/de_mif_reg_l9.h"
#include "l9/de_wcp_reg_l9.h"
#include "l9/de_msc_reg_l9.h"
#include "l9/de_ssc_reg_l9.h"

/* external pe module */
#include "pe_cfg.h"
#include "reg/pe_reg.h"
#include "util/pe_etc_hw.h"
#include "dcm/pe_dcm_hw.h"

/* external venc module */
#include "venc_cfg.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define ROW2PHY(a) (a << 14)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern DE_DEB_REG_L9_T gDE_DEB_L9;
extern DE_DEC_REG_L9_T gDE_DEC_L9;
extern DE_MIB_REG_L9_T gDE_MIB_L9;
extern DE_MID_REG_L9_T gDE_MID_L9;
extern DE_MIF_REG_L9_T gDE_MIF_L9;
extern DE_OVL_REG_L9_T gDE_OVL_L9;
extern DE_OVR_REG_L9_T gDE_OVR_L9;
extern DE_MSL_REG_L9_T gDE_MSL_L9;
extern DE_MSR_REG_L9_T gDE_MSR_L9;
extern DE_SSC_REG_L9_T gDE_SSC_L9;
extern LX_VENC_MEM_CFG_S_T	*gpstVencMemConfig;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile UINT8 *gpMBase_ssc_l9  = NULL;
volatile UINT8 *gpMBase_venc_l9 = NULL;
volatile UINT32 *gpTimerBase_l9 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

int APR_L9_Init(void)
{
	int ret = RET_OK;

	if(gpMBase_ssc_l9 == NULL)
	{
		gpMBase_ssc_l9 = (volatile UINT8 *)ioremap(VIDEO_L9_FRAME_DDR_BASE, VIDEO_L9_MEM_SIZE_OF_FRAME_MEMORY);
	}

	if(gpMBase_venc_l9 == NULL)
	{
		if(gpstVencMemConfig->uiInBufBase != 0)
		{
			gpMBase_venc_l9 = (volatile UINT8 *)ioremap(gpstVencMemConfig->uiInBufBase, gpstVencMemConfig->uiInBufSize);
		}
	}

	if(gpTimerBase_l9 == NULL)
	{
		gpTimerBase_l9 = (volatile UINT32 *)ioremap(L9_TIMER_BASE + 0x24, 4);
	}

	return ret;
}

int APR_L9_Uninit(void)
{
	int ret = RET_OK;
	
	if (gpMBase_ssc_l9) iounmap((void *)gpMBase_ssc_l9);
	if (gpMBase_venc_l9) iounmap((void *)gpMBase_venc_l9);
	if (gpTimerBase_l9) iounmap((void *)gpTimerBase_l9);

	return ret;
}

int APR_L9_InitInterrupt(BOOLEAN intr_en)
{
	DE_DEB_L9B_RdFL(deb_intr_mask);
	DE_DEB_L9B_Wr01(deb_intr_mask, mask_disp_for_cpu, intr_en?0:1);  // unmasking interrupt from de
	DE_DEB_L9B_WrFL(deb_intr_mask);
	return RET_OK;
}

int APR_L9_InitHardware(void)
{
	int ret = RET_OK;

	do {
		PE_P0L_L9B0_RdFL(tridfd_ctrl_00);
		PE_P0L_L9B0_RdFL(tridfd_ctrl_01);
		PE_P0L_L9B0_RdFL(tridfd_ctrl_02);
		PE_P0L_L9B0_RdFL(tridfd_ctrl_03);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_00, aw_offset_x, 0);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_00, aw_offset_y, 0);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_00, cb_th1, 0x3C);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_00, cb_th2, 0x14);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_01, cc_th1, 0x3C);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_01, cc_th2, 0x14);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_01, ll_th1, 0x3C);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_01, ll_th2, 0x14);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_02, pt_th, 0x80);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_02, sstb_th, 0x07);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_02, div_mode, 0);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_03, small_delta_en, 0);
		PE_P0L_L9B0_Wr01(tridfd_ctrl_03, small_delta_th, 0xFF);
		PE_P0L_L9B0_WrFL(tridfd_ctrl_00);
		PE_P0L_L9B0_WrFL(tridfd_ctrl_01);
		PE_P0L_L9B0_WrFL(tridfd_ctrl_02);
		PE_P0L_L9B0_WrFL(tridfd_ctrl_03);
	} while(0);

	return ret;
}

int APR_L9_GetMaxFromBuffer(UINT32 *pBuf, UINT32 count, UINT32 *pElect)
{
    int ret = RET_OK;
	UINT32 i=0, j=0;
	UINT32 temp=0;

	do {
		for(i=0;i<count;i++)
		{
			for(j=0;j<count;j++)
			{
				if(pBuf[j] >= temp)
				{
					temp = pBuf[j];
				}
			}
		}
		*pElect = temp;
	} while(0);
	return ret;
}

int APR_L9_CollectBasicData(APR_CFG_T *apr_cfg, APR_DTA_T *apr_data)
{
    int ret = RET_OK;
	APR_CFG_T *pCfg  = apr_cfg;
	APR_DTA_T *pData = apr_data;
	static UINT32 motion_l[4] = { 0 };
	static UINT32 motion_r[4] = { 0 };

	do {
		PE_P0L_L9B0_RdFL(tpd_stat_00);
		PE_P0L_L9B0_Rd01(tpd_stat_00, reg_s_status, pData->tpd);
		PE_P0L_L9B0_RdFL(tridfd_stat_00);
		PE_P0L_L9B0_Rd01(tridfd_stat_00, cb_count, pData->cb);
		PE_P0L_L9B0_RdFL(tridfd_stat_00);
		PE_P0L_L9B0_Rd01(tridfd_stat_00, cc_count, pData->cc);
		PE_P0L_L9B0_RdFL(tridfd_stat_01);
		PE_P0L_L9B0_Rd01(tridfd_stat_01, ll_count, pData->ll);
		PE_P0L_L9B0_Rd01(tridfd_stat_01, tridfd_format, pData->hw_fmt);

		PE_P0L_L9B0_RdFL(tridfd_stat_02);
		PE_P0L_L9B0_Rd01(tridfd_stat_02, delta_ss_h, pData->ssh);
		PE_P0L_L9B0_RdFL(tridfd_stat_03);
		PE_P0L_L9B0_Rd01(tridfd_stat_03, delta_ss_v, pData->ssv);
		PE_P0L_L9B0_RdFL(tridfd_stat_04);
		PE_P0L_L9B0_Rd01(tridfd_stat_04, delta_tb_v, pData->tbv);
		PE_P0L_L9B0_RdFL(tridfd_stat_05);
		PE_P0L_L9B0_Rd01(tridfd_stat_05, delta_tb_h, pData->tbh);

		PE_P0L_L9B0_RdFL(tridfd_stat_06);
		PE_P0L_L9B0_Rd01(tridfd_stat_06, ss_ratio, pData->ssr);
		PE_P0L_L9B0_RdFL(tridfd_stat_07);
		PE_P0L_L9B0_Rd01(tridfd_stat_07, tb_ratio, pData->tbr);

		PE_P0L_L9B0_RdFL(tnr_status_00);
		PE_P0L_L9B0_RdFL(tnr_status_01);
		PE_P0L_L9B0_RdFL(apl_stat_00);
		motion_l[3] = motion_l[2];
		motion_l[2] = motion_l[1];
		motion_l[1] = motion_l[0];
		PE_P0L_L9B0_Rd01(tnr_status_00, x_avg_t, motion_l[0]);
		ret = APR_L9_GetMaxFromBuffer(motion_l, 4, &pData->motion_l);
		PE_P0L_L9B0_Rd01(tnr_status_00, nt_lvl, pData->nt_l);
		PE_P0L_L9B0_Rd01(tnr_status_01, x_avg_s, pData->spatial_l);
		PE_P0L_L9B0_Rd01(apl_stat_00, apl_stat_00, pData->apl_l);

		PE_P0R_L9B0_RdFL(tnr_status_00);
		PE_P0R_L9B0_RdFL(tnr_status_01);
		PE_P0R_L9B0_RdFL(apl_stat_00);
		motion_r[3] = motion_r[2];
		motion_r[2] = motion_r[1];
		motion_r[1] = motion_r[0];
		PE_P0R_L9B0_Rd01(tnr_status_00, x_avg_t, motion_r[0]);
		ret = APR_L9_GetMaxFromBuffer(motion_r, 4, &pData->motion_r);
		PE_P0R_L9B0_Rd01(tnr_status_00, nt_lvl, pData->nt_r);
		PE_P0R_L9B0_Rd01(tnr_status_01, x_avg_s, pData->spatial_r);
		PE_P0R_L9B0_Rd01(apl_stat_00, apl_stat_00, pData->apl_r);

		DE_OVL_L9_RdFL(ovl_ov_msize);
		DE_OVL_L9_Rd01(ovl_ov_msize, m_hsize, pCfg->out_win_x);
		DE_OVL_L9_Rd01(ovl_ov_msize, m_vsize, pCfg->out_win_y);
	}while(0);

	return ret;
}

int APR_L9_GetOVInfo(APR_CFG_T *apr_cfg, APR_CAP_SRC_T ov_src, APR_OV_INFO_T *ov_info)
{
	int ret = RET_OK;
	APR_CFG_T *pCfg = apr_cfg;
	UINT32 stride=0;
	UINT32 intr_mask;
	BOOLEAN sel_scaler_l = FALSE;
	BOOLEAN sel_scaler_r = FALSE;
	BOOLEAN sel_scaler_s = FALSE;

	do {
		switch (ov_src)
		{
			case APR_CAP_SRC_L_OVR :
			{
				DE_DEC_L9B_RdFL(dec_intr_mask);
				DE_DEC_L9B_Rd01(dec_intr_mask, dec_intr_mask, intr_mask);
				ov_info->src_valid = ((intr_mask & (1<<23)) == 0)?TRUE:FALSE;

				DE_MIB_L9_RdFL(mifb_saddr_rd_ext0);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ext0, req_rd_saddr_8_ovm_y_msb4b, ov_info->y_msb);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ext0, req_rd_saddr_8_ovm_c_msb4b, ov_info->c_msb);

				DE_MIB_L9_RdFL(mifb_saddr_rd_ovm_y);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ovm_y, req_rd_saddr_8_ovm_y, ov_info->y_base);
				DE_MIB_L9_RdFL(mifb_saddr_rd_ovm_c);
				DE_MIB_L9_Rd01(mifb_saddr_rd_ovm_c, req_rd_saddr_8_ovm_c, ov_info->c_base);

				DE_MIB_L9_RdFL(mifb_rd_set_10b);
				DE_MIB_L9_Rd01(mifb_rd_set_10b, set_10b_req_rd_ovm_y, ov_info->bpp);

				ov_info->stride = 2048;

				DE_OVL_L9_RdFL(ovl_ov_msize);
				DE_OVL_L9_Rd01(ovl_ov_msize, m_hsize, ov_info->h);
				DE_OVL_L9_Rd01(ovl_ov_msize, m_vsize, ov_info->v);

				DE_MSL_L9_RdFL(msc_c_format_l);
				DE_MSL_L9_Rd01(msc_c_format_l, out_c_format, ov_info->sub_sample);
				
				ov_info->frame_base_phys[0] = ROW2PHY(ov_info->y_base);
				sel_scaler_l = TRUE;
			}
			break;
			case APR_CAP_SRC_R_OVR :
			{
				DE_DEC_L9B_RdFL(dec_intr_mask);
				DE_DEC_L9B_Rd01(dec_intr_mask, dec_intr_mask, intr_mask);
				ov_info->src_valid = ((intr_mask & (1<<23)) == 0)?TRUE:FALSE;

				DE_MID_L9_RdFL(mifd_saddr_rd_ext0);
				DE_MID_L9_Rd01(mifd_saddr_rd_ext0, req_rd_saddr_ov_y_msb4b, ov_info->y_msb);
				DE_MID_L9_Rd01(mifd_saddr_rd_ext0, req_rd_saddr_ov_c_msb4b, ov_info->c_msb);

				DE_MID_L9_RdFL(mifd_saddr_rd_ov_y_ov_c);
				DE_MID_L9_Rd01(mifd_saddr_rd_ov_y_ov_c, req_rd_saddr_ov_y, ov_info->y_base);
				DE_MID_L9_Rd01(mifd_saddr_rd_ov_y_ov_c, req_rd_saddr_ov_c, ov_info->c_base);

				//DE_MID_L9_RdFL(mifd_rd_set_10b);
				//DE_MID_L9_Rd01(mifd_rd_set_10b, set_10b_req_rd_ovm_y, ov_info->bpp);

				ov_info->stride = 2048;

				DE_OVR_L9_RdFL(ovr_ov_msize);
				DE_OVR_L9_Rd01(ovr_ov_msize, m_hsize, ov_info->h);
				DE_OVR_L9_Rd01(ovr_ov_msize, m_vsize, ov_info->v);

				DE_MSR_L9_RdFL(msc_c_format_r);
				DE_MSR_L9_Rd01(msc_c_format_r, out_c_format, ov_info->sub_sample);
				
				ov_info->frame_base_phys[1] = ROW2PHY(ov_info->y_base);
				sel_scaler_r = TRUE;
			}
			break;
			case APR_CAP_SRC_S_CVR :
			{
				DE_DEC_L9B_RdFL(dec_intr_mask);
				DE_DEC_L9B_Rd01(dec_intr_mask, dec_intr_mask, intr_mask);
				ov_info->src_valid = ((intr_mask & (1<<16)) == 0)?TRUE:FALSE;

				DE_MIF_L9_RdFL(miff_saddr_rd_ext0);
				DE_MIF_L9_Rd01(miff_saddr_rd_ext0, req_rd_saddr_cve_y_msb4b, ov_info->y_msb);
				DE_MIF_L9_Rd01(miff_saddr_rd_ext0, req_rd_saddr_cve_c_msb4b, ov_info->c_msb);

				DE_MIF_L9_RdFL(miff_saddr_rd_cve_yc);
				DE_MIF_L9_Rd01(miff_saddr_rd_cve_yc, req_rd_saddr_cve_y, ov_info->y_base);
				DE_MIF_L9_Rd01(miff_saddr_rd_cve_yc, req_rd_saddr_cve_c, ov_info->c_base);

				DE_SSC_L9_RdFL(ssc_win_out_size);
				DE_SSC_L9_Rd01(ssc_win_out_size, out_win_h_size, ov_info->h);
				DE_SSC_L9_Rd01(ssc_win_out_size, out_win_v_size, ov_info->v);

				DE_SSC_L9_RdFL(ssc_ctrl);
				DE_SSC_L9_Rd01(ssc_ctrl, dvr_write_mode, stride);
				if(stride)
					ov_info->stride = ((ov_info->h + 15) / 16) * 16;
				else
					ov_info->stride = 1024;

				DE_SSC_L9_RdFL(ssc_c_format);
				DE_SSC_L9_Rd01(ssc_c_format, out_c_format, ov_info->sub_sample);
				
				ov_info->frame_base_phys[0] = ROW2PHY(ov_info->y_base);
				sel_scaler_s = TRUE;
			}
			break;
			case APR_CAP_SRC_L_PRW :
			case APR_CAP_SRC_L_TNR :
			case APR_CAP_SRC_R_PRW :
			case APR_CAP_SRC_R_TNR :
			default :
				ov_info->src_valid = FALSE;
				break;
		}

		ov_info->pFrameBase = NULL;
		
		if(	(ov_info->y_base == 0)                || \
			(ov_info->h == 0)                     || \
			(ov_info->v == 0)                     || \
			(ov_info->stride == 0)                || \
			(ov_info->h > APR_MAX_HSIZE)          || \
			(ov_info->v > APR_MAX_VSIZE)          || \
			(ov_info->stride > 2048) )              
		{
			if(pCfg->cap.enb >= LX_APR_CAP_FMT) printk("h_size[%d]/v_size[%d]/y_base[%d]\n", \
					ov_info->h, ov_info->v, ov_info->y_base);
			ov_info->src_valid = FALSE;
			break;
		}

		if(ROW2PHY(ov_info->y_base) > 0x10000000)
		{
			if(pCfg->cap.enb >= LX_APR_CAP_FMT) printk("y_base  0x%08x\n", ROW2PHY(ov_info->y_base));
			ov_info->src_valid = FALSE;
			break;
		}

		if(ov_info->y_msb == 0x7)
		{
			if((gpMBase_venc_l9 == NULL) || (gpstVencMemConfig->uiInBufBase == 0))
			{
				ov_info->src_valid = FALSE;
			}
			ov_info->pFrameBase = (volatile UINT8*)((UINT32)gpMBase_venc_l9 + (ROW2PHY(ov_info->y_base) - (gpstVencMemConfig->uiInBufBase - 0x70000000)));
			if(sel_scaler_l || sel_scaler_s)
				ov_info->frame_base_phys[0] += 0x70000000;
			if(sel_scaler_r)
				ov_info->frame_base_phys[1] += 0x70000000;
		}
		else if(ov_info->y_msb == 0x8)
		{
			ov_info->pFrameBase = (volatile UINT8*)((UINT32)gpMBase_ssc_l9 + ROW2PHY(ov_info->y_base));
			if(sel_scaler_l || sel_scaler_s)
				ov_info->frame_base_phys[0] += 0x80000000;
			if(sel_scaler_r)
				ov_info->frame_base_phys[1] += 0x80000000;
		}
		else
		{
			if(pCfg->cap.enb >= LX_APR_CAP_FMT) printk("%s : un-defined msb [ 0x%X000 0000 ]\n", \
					__F__, ov_info->y_msb & 0xF);
			if(sel_scaler_l || sel_scaler_s)
				ov_info->frame_base_phys[0] = 0;
			if(sel_scaler_r)
				ov_info->frame_base_phys[1] = 0;
			ov_info->src_valid = FALSE;
		}

		if(ov_info->src_valid)
		{
			if(pCfg->cap.enb >= LX_APR_CAP_FMT) printk("%s : ov src[%d] frame_base_phys[0/1] 0x%08X 0x%08X\n",\
					__F__, ov_src, ov_info->frame_base_phys[0],ov_info->frame_base_phys[1]);
		}
	} while(0);

	return ret;
}

int APR_L9_GetUSecTimerVal(UINT32 *tv)
{
	int ret = RET_OK;
	*tv = (UINT32)((0xFFFFFFFF - *gpTimerBase_l9)/198);
	return ret;
}
