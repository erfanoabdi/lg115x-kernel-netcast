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

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#ifdef USE_XTENSA
#include <string.h>
#include <stdlib.h>
#include <BSP/UART/stdio.h>

#include <XDE/CFG_VIDEO.h>
#include <Common/DDI_DTV.h>
#include <Common/MEM_DTV.h>

#include <XDE/VIDEO_TYPE.h>
#include <XDE/IPC_VIDEO.h>
#include <XDE/REG_DLR.h>
#include <XDE/MEM_VIDEO.h>
#include <XDE/MCU_VIDEO.h>
#include <XDE/de_kapi.h>
#include <XDE/IO_VIDEO.h>
#include <XDE/REG_DLR.h>
#include <XDE/DD_VIDEO_Param.h>
#include <XDE/REG_VIDEO_MCU.h>

#include "XDE/fmt3d_kapi.h"
#include "XDE/io_fmt3d.h"
#ifdef USE_XTENSA_FRC
#include "FRC/FRC_Config.h"
#endif

#else
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "os_util.h"

#include "base_types.h"

#include "../de/de_model.h"
#include "../de/de_def.h"
#include "../de/l8/de_ipc_def_l8.h"
#include "../de/de_ipc.h"

#include "fmt3d_kapi.h"
#include "mcu/io_fmt3d.h"
#include "../de/mcu/mcu_test.h"

#endif

#ifdef USE_VIDEO_TEST_MCU_IN_CPU
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#undef USE_3DF_CHECK_IN_SIZE

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
extern char gaSendBuffOfIPC[VIDEO_MSG_STR_MAX];
#ifdef USE_XTENSA_FRC
#ifdef USE_XTENSA_L8B0
extern frc_config_t frcNextConfig;
#else
extern frc_config frcCurrConfig;
#endif
#endif


/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
#ifdef USE_XTENSA
#ifdef USE_XTENSA_FRC
#ifdef USE_XTENSA_L8B0
static DTV_STATUS_T FRC_MFT3D_SetFrcOutType(panel_type_t frcType, input_mode_t frcMode, output_side_t frcSide) DE_CODEDDR;
#else
static DTV_STATUS_T FRC_MFT3D_SetFrcOutType(cfg_rgb_mode rgbMode, cfg_side_mode sideMode) DE_CODEDDR;
#endif
static LX_3D_LR_ORDER_T FMT3D_GetFrcOutOrder(void) DE_CODEDDR;
#endif
#endif

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
#ifdef USE_XTENSA
static VIDEO_3DF_TYPE_T saVideoInx3DF[VIDEO_3DF_MAX] = { VIDEO_3DF_TB, VIDEO_3DF_SS, VIDEO_3DF_CB, VIDEO_3DF_FS, VIDEO_3DF_FD, VIDEO_3DF_MAX, VIDEO_3DF_MAX, VIDEO_3DF_MAX};
static LX_3D_OUT_TYPE_T sVideoFrcOutType    = LX_3D_OUT_OFF;
#ifdef USE_XTENSA_FRC
static LX_3D_LR_ORDER_T	sVideoFrcOutLrOrder = LX_3D_LR_ORDER_L_FIRST;
#endif
#endif

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
DTV_STATUS_T MCU_FMT3D_IO_Init(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	ret = VIDEO_3DF_InitFormatAsDefault();
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetProcessMode(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_PROCESS_MODE_T stParams;
    PROC_MODE_T 			proc_mode;
	CONVERGENCE_RANGE_T     convergence_range;

	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		proc_mode.pre3d_src_mux    = stParams.src_mux;
		proc_mode.pre3d_run_mode   = stParams.run_mode;
		proc_mode.display_format   = stParams.dis_fmt;
		proc_mode.display_freq     = stParams.dis_freq;
		proc_mode.lr_out_order     = stParams.out_lr_order;
		proc_mode.convergence_mode = stParams.cvg_mode;
		proc_mode.convergence      = stParams.cvg_value;
		convergence_range.conv_min = stParams.cvg_min;
		convergence_range.conv_max = stParams.cvg_max;

		ret = VIDEO_SetProcModeOf3DF(&proc_mode, NULL, &convergence_range);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_GetProcessMode(char *strBuff)
{
	DTV_STATUS_T ret = OK;
	LX_3D_PROCESS_MODE_T stParams;
#ifdef USE_XTENSA
    PROC_MODE_T 			proc_mode;
	CONVERGENCE_RANGE_T     convergence_range;
	do {
		ret = VIDEO_GetProcModeOf3DF(&proc_mode, NULL, &convergence_range);
		if (ret) break;
		stParams.src_mux      = proc_mode.pre3d_src_mux;
		stParams.run_mode     = proc_mode.pre3d_run_mode;
		stParams.dis_fmt      = proc_mode.display_format;
		stParams.dis_freq     = proc_mode.display_freq;
		stParams.out_lr_order = proc_mode.lr_out_order;
		stParams.cvg_mode     = proc_mode.convergence_mode;
		stParams.cvg_value    = proc_mode.convergence;
		stParams.cvg_min      = convergence_range.conv_min;
		stParams.cvg_max      = convergence_range.conv_max;

		memcpy(gaSendBuffOfIPC, &stParams, sizeof(stParams));
	} while (0);
#endif
	ret = VIDEO_MCU_PutData(gaSendBuffOfIPC, sizeof(stParams));

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetInImgInfo(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_IN_CONFIG_T stParams;
    IN_IMG_FORMAT_T      in_img_format;

	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		in_img_format.in_image_format  = saVideoInx3DF[stParams.in_img_fmt];
		in_img_format.color_format     = stParams.color_fmt;
		in_img_format.lr_in_order      = stParams.in_lr_order;
		in_img_format.in_freq          = stParams.input_fr; // L8 does not have input_fr field
		in_img_format.progressive      = stParams.is_prog;
		in_img_format.double_pic       = stParams.is_dbl_pic;
		in_img_format.in_bit_res       = stParams.bit_res;
		in_img_format.sample_mode      = stParams.sample_mode;
		in_img_format.sample_comb      = stParams.sample_comb;
		in_img_format.spatial_flip     = stParams.spatial_flip;
		in_img_format.tl_frame_flip    = stParams.is_tl_flip;

		ret = VIDEO_SetProcModeOf3DF(NULL, &in_img_format, NULL);
		if (ret) break;
		ret = VIDEO_SetSizeOfImageForDlr(stParams.in_img_size.w, stParams.in_img_size.h, stParams.crop_offset);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_GetInImgInfo(char *strBuff)
{
	DTV_STATUS_T ret = OK;
	LX_3D_IN_CONFIG_T stParams;
#ifdef USE_XTENSA
	IN_IMG_FORMAT_T   in_img_format;
	int i;

	do {
		ret = VIDEO_GetProcModeOf3DF(NULL, &in_img_format, NULL);
		if (ret) break;
		for (i=0;i<VIDEO_3DF_MAX;i++) if (saVideoInx3DF[i] == in_img_format.in_image_format) break;
		stParams.in_img_fmt   = i;
		stParams.color_fmt    = in_img_format.color_format;
		stParams.in_lr_order  = in_img_format.lr_in_order;
		stParams.input_fr     = in_img_format.in_freq;	// L8 does not have input_fr field
		stParams.is_prog      = in_img_format.progressive;
		stParams.is_dbl_pic   = in_img_format.double_pic;
		stParams.bit_res      = in_img_format.in_bit_res;
		stParams.sample_mode  = in_img_format.sample_mode;
		stParams.sample_comb  = in_img_format.sample_comb;
		stParams.spatial_flip = in_img_format.spatial_flip;
		stParams.is_tl_flip   = in_img_format.tl_frame_flip;

		ret = VIDEO_GetSizeOfImageForDlrReg(&stParams.in_img_size.w, &stParams.in_img_size.h, &stParams.crop_offset);
		if (ret) break;

		memcpy(gaSendBuffOfIPC, &stParams, sizeof(stParams));
	} while (0);
#endif
	ret = VIDEO_MCU_PutData(gaSendBuffOfIPC, sizeof(stParams));

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_GetOutImgInfo(char *strBuff)
{
	DTV_STATUS_T ret = OK;
	LX_3D_OUT_IMG_INFO_T stParams;
#ifdef USE_XTENSA
	PRE3D_OUT_IMG_INFO_T pre3d_out_img_info;

	do {
		ret = VIDEO_GetPre3dOutInfoForDlrReg(&pre3d_out_img_info);
		if (ret) break;
		stParams.out_img_size.w = pre3d_out_img_info.out_img_width;
		stParams.out_img_size.h = pre3d_out_img_info.out_img_height;
		stParams.out_img_fmt    = pre3d_out_img_info.out_img_format;

		memcpy(gaSendBuffOfIPC, &stParams, sizeof(stParams));
	} while (0);
#endif
	ret = VIDEO_MCU_PutData(gaSendBuffOfIPC, sizeof(stParams));

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetRunmode(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_RUNMODE_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_RUN_MODE, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_ToggleLrInOrder(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_LR_ORDER_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_LR_IN_ORDER, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_ToggleLrOutOrder(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_LR_ORDER_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_LR_OUT_ORDER, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetInImgFmt(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_IMG_FMT_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_IN_IMAGE_FORMAT, saVideoInx3DF[stParams]);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetDisFmt(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_DIS_FMT_TYPE_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_DISPLAY_FORMAT, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetInFrRate(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_IMG_FREQ_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_IN_FREQ, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetOutFrRate(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_DIS_FREQ_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_DISPLAY_FREQ, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetConvergence(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_CONVERGENCE_CTRL_T stParams;
	VIDEO_3DF_MODE_T mode3DF;
	UINT32			 inImgFmt;
	SINT16			 s16ConvValue;
	int				 iConvValue;
	BOOLEAN 		 runAtT3;

	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		do {
			runAtT3 = FALSE;
			if (!VIDEO_GetParameter(VIDEO_CTRL_2DTO3D_FRAME_SEQUENCE)) break;
			mode3DF  = VIDEO_GetMode3DF();
			inImgFmt = VIDEO_GetFormatOf3DF(VIDEO_3DF_IN_IMAGE_FORMAT);
			if ( (VIDEO_3DF_MODE_FPR3T!=mode3DF) && !((VIDEO_3DF_MODE_NORMAL==mode3DF) && (VIDEO_3DF_FS==inImgFmt)) ) break;
			runAtT3 = TRUE;
		} while (0);

		if (runAtT3) {
			s16ConvValue = GET_SEXT(stParams.conv_val, 0, 16);
			ret = VIDEO_T3_REG_SetDepthConvergence(NULL, &s16ConvValue, &stParams.edge_val);
		} else {
			iConvValue = GET_SEXT(stParams.conv_val, 0, 16);
			ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_CONVERGENCE, iConvValue);
		}
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetImgDoublePic(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_IMG_DOUBLE_PIC_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_DOUBLE_PIC, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetSampleMode(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_SAMPLE_MODE_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_SAMPLE_MODE, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetSrcMux(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_SRC_MUX_TYPE_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_SRC_MUX, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetImgScanType(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_IMG_SCAN_TYPE_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_SetFormatOf3DF(VIDEO_3DF_PROGRESSIVE, stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetFrcOutType(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_OUT_TYPE_T stParams;

	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = FMT3D_SetFrcOutType(stParams);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetFrcOutOrder(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
#ifdef USE_XTENSA_FRC
	LX_3D_LR_ORDER_T stParams;

	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = FMT3D_SetFrcOutOrder(stParams);
	} while (0);
#endif
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_T3_IO_SetConvergence(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_CONVERGENCE_CTRL_T stParams;
	SINT16 convValue;

	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		convValue  = GET_SEXT(stParams.conv_val, 0, 16);
		ret = VIDEO_T3_REG_SetDepthConvergence(NULL, &convValue, &stParams.edge_val);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_T3_IO_SetDepthCtrl(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	UINT16 stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_T3_REG_SetDepthConvergence(&stParams, NULL, NULL);
	} while (0);
#endif

	return ret;
}

DTV_STATUS_T MCU_FMT3D_IO_SetFprFhd(char *strBuff)
{
	DTV_STATUS_T ret = OK;
#ifdef USE_XTENSA
	LX_3D_FPR_FHD_MODE_T stParams;
	do {
		memcpy(&stParams, strBuff, sizeof(stParams));
		ret = VIDEO_T3_REG_SetDepthConvergence(&stParams, NULL, NULL);
	} while (0);
#endif

	return ret;
}

LX_3D_OUT_TYPE_T FMT3D_GetFrcOutType(void)
{
	LX_3D_OUT_TYPE_T outType = sVideoFrcOutType;
	VIDEO_3DF_MODE_T mode3DF;

	do {
		mode3DF = VIDEO_GetMode3DF();
		if (VIDEO_3DF_MODE_2DTO3D == mode3DF) break;
		if (VIDEO_3DF_MODE_3DBYT3 == mode3DF) break;
		if (VIDEO_3DF_MODE_FPR3T  == mode3DF) break;
		if (LX_3D_OUT_LINEINTERLEAVED != outType) break;
		if (VIDEO_3DF_RUN_OFF != VIDEO_GetFormatOf3DF(VIDEO_3DF_RUN_MODE)) break;
		outType = LX_3D_OUT_OFF;
	} while (0);

	return outType;
}

DTV_STATUS_T FMT3D_SetFrcOutType(LX_3D_OUT_TYPE_T outType)
{
	sVideoFrcOutType = outType;

	return OK;
}

#ifdef USE_XTENSA
#ifdef USE_XTENSA_FRC
DTV_STATUS_T FMT3D_SetFrcOutOrder(LX_3D_LR_ORDER_T lrOrder)
{
	sVideoFrcOutLrOrder = lrOrder;

	return OK;
}

static LX_3D_LR_ORDER_T FMT3D_GetFrcOutOrder(void)
{
	return sVideoFrcOutLrOrder;
}

#ifdef USE_XTENSA_L8B0
DTV_STATUS_T FMT3D_SetFrcOutput(void)
{
	DTV_STATUS_T ret = OK;
	panel_type_t  		  frcType;
	LX_3D_OUT_TYPE_T	  outType;
	VIDEO_3DF_MODE_T	  mode3DF;
	VIDEO_3DF_TYPE_T      out3DF;
	UINT32                inImgFmt;
	VIDEO_3DF_RUN_T       run3DF;
	input_mode_t 		  frcMode;
	output_side_t         frcSide = OUTPUT_SIDE_ALL;
#ifdef USE_3DF_CHECK_IN_SIZE
	VIDEO_RECT_T 		  vIn;
#endif

	do {
		frcType  = PANEL_TYPE_PG;
		outType  = FMT3D_GetFrcOutType();
		mode3DF  = VIDEO_GetMode3DF();
		out3DF   = VIDEO_3DF_GetType();
		inImgFmt = VIDEO_GetFormatOf3DF(VIDEO_3DF_IN_IMAGE_FORMAT);
		run3DF   = VIDEO_GetFormatOf3DF(VIDEO_3DF_RUN_MODE);
		switch (outType) {
			case LX_3D_OUT_LINEINTERLEAVED :
				if ( (VIDEO_3DF_MODE_2DTO3D==mode3DF)||(VIDEO_3DF_MODE_3DBYT3==mode3DF)||(VIDEO_3DF_MODE_FPR3T==mode3DF) ) {
					frcMode = INPUT_MODE_3DTB;
				} else if ( VIDEO_3DF_RUN_2D == run3DF ) {
					frcSide = OUTPUT_SIDE_L_T;
					if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
						if (VIDEO_3DF_SS == out3DF) frcType = PANEL_TYPE_SG;
						frcMode = (VIDEO_3DF_SS == out3DF)?INPUT_MODE_3DSS:INPUT_MODE_3DTB;
					} else if (VIDEO_3DF_SS == inImgFmt) {
						frcType = PANEL_TYPE_SG;
						frcMode = INPUT_MODE_3DSS;
					} else if (VIDEO_3DF_TB == inImgFmt) {
						frcMode = INPUT_MODE_3DTB;
					}
				} else if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS == out3DF) {
						frcMode = INPUT_MODE_3DSS;
					} else if ( (VIDEO_3DF_TB == out3DF) || (VIDEO_3DF_FS == out3DF) ) {
						frcMode = INPUT_MODE_3DTB;
					}
				} else {
					if (VIDEO_3DF_TB != inImgFmt) break;
#ifdef USE_3DF_CHECK_IN_SIZE
					ret = VIDEO_GetInfoOfWCP(VIDEO_WIN_DSP, &vIn, NULL, NULL, NULL);
					if (ret) break;
					if (1920 != vIn.w) break;
					if (1080 != vIn.h) break;
#endif
					frcMode = INPUT_MODE_3DTB;
				}
				break;
			case LX_3D_OUT_FRAMESEQ :
				frcType = PANEL_TYPE_SG;
				if ( VIDEO_3DF_MODE_2DTO3D == mode3DF ) {
					frcMode = INPUT_MODE_3DSS;
				} else if ( VIDEO_3DF_RUN_2D == run3DF ) {
					frcSide = OUTPUT_SIDE_L_T;
					if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
						frcMode = (VIDEO_3DF_SS == out3DF)?INPUT_MODE_3DSS:INPUT_MODE_3DTB;
					} else if (VIDEO_3DF_SS == inImgFmt) {
						frcMode = INPUT_MODE_3DSS;
					} else if (VIDEO_3DF_TB == inImgFmt) {
						frcMode = INPUT_MODE_3DTB;
					}
				} else if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS != out3DF) break;
					if (VIDEO_3DF_FS != inImgFmt) break;
					frcMode = INPUT_MODE_3DSS;
				} else if (VIDEO_3DF_SS == inImgFmt) {
					frcMode = INPUT_MODE_3DSS;
				} else if (VIDEO_3DF_FS == inImgFmt) {
					frcMode = INPUT_MODE_3DSS;
				}
				break;
			case LX_3D_OUT_DUAL :
				frcType = PANEL_TYPE_SG;
				if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS != out3DF) break;
					if (VIDEO_3DF_FS != inImgFmt) break;
					frcMode = INPUT_MODE_3DSS;
				} else if (VIDEO_3DF_SS == inImgFmt) {
					frcMode = INPUT_MODE_3DSS;
				} else if (VIDEO_3DF_FS == inImgFmt) {
					frcMode = INPUT_MODE_3DSS;
				}
				break;
			case LX_3D_OUT_OFF :
				frcMode = INPUT_MODE_2D;
				break;
			default :
				break;
		}
		if (ret) break;
		ret = FRC_MFT3D_SetFrcOutType(frcType, frcMode, frcSide);
	} while (0);

	return ret;
}

static DTV_STATUS_T FRC_MFT3D_SetFrcOutType(panel_type_t frcType, input_mode_t frcMode, output_side_t frcSide)
{
	output_order_t 		  frcOrder;
	static panel_type_t   frcType_Old  = 0xff;
	static input_mode_t   frcMode_Old  = 0xff;
	static output_side_t  sideMode_Old = 0xff;
	static output_order_t frcOrder_Old = 0xff;

	do {
		frcOrder = (LX_3D_LR_ORDER_L_FIRST == FMT3D_GetFrcOutOrder())?OUTPUT_ORDER_LR:OUTPUT_ORDER_RL;
		if ( (frcType_Old==frcType) && (frcMode_Old==frcMode) && (sideMode_Old==frcSide) && (frcOrder_Old==frcOrder) ) break;
		frcType_Old  = frcType;
		frcMode_Old  = frcMode;
		sideMode_Old = frcSide;
		frcOrder_Old = frcOrder;

		frcNextConfig.panel.type   = frcType;
		frcNextConfig.input.mode   = frcMode;
		frcNextConfig.output.side  = frcSide;
		frcNextConfig.output.order = frcOrder;
	} while (0);

	return OK;
}
#elif !defined(USE_SEARCH_SKIP_DEFINITION)
DTV_STATUS_T FMT3D_SetFrcOutput(void)
{
	DTV_STATUS_T ret = OK;
	LX_3D_OUT_TYPE_T	  outType;
	VIDEO_3DF_MODE_T	  mode3DF;
	VIDEO_3DF_TYPE_T      out3DF;
	UINT32                inImgFmt;
	LX_3D_LR_ORDER_T	  lrOrder;
	cfg_rgb_mode          rgbMode = CFG_RGB_BYPASS;
	cfg_side_mode         sideMode = CFG_SIDE_ALL;
#ifdef USE_3DF_CHECK_IN_SIZE
	VIDEO_RECT_T 		  vIn;
#endif

	do {
		outType	= FMT3D_GetFrcOutType();
		lrOrder = FMT3D_GetFrcOutOrder();
		mode3DF	= VIDEO_GetMode3DF();
		out3DF   = VIDEO_3DF_GetType();
		inImgFmt = VIDEO_GetFormatOf3DF(VIDEO_3DF_IN_IMAGE_FORMAT);
		switch (outType) {
			case LX_3D_OUT_LINEINTERLEAVED :
				if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS == out3DF) {
						rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_0_0:CFG_RGB_3D_0_1;
					} else if ( (VIDEO_3DF_TB == out3DF) || (VIDEO_3DF_FS == out3DF) ) {
						rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_1_0:CFG_RGB_3D_1_1;
					}
				} else {
					if (VIDEO_3DF_TB != inImgFmt) break;
#ifdef USE_3DF_CHECK_IN_SIZE
					ret = VIDEO_GetInfoOfWCP(VIDEO_WIN_DSP, &vIn, NULL, NULL, NULL);
					if (ret) break;
					if (1920 != vIn.w) break;
					if (1080 != vIn.h) break;
#endif
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_1_0:CFG_RGB_3D_1_1;
				}
				break;
			case LX_3D_OUT_FRAMESEQ :
				if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS != out3DF) break;
					if (VIDEO_3DF_FS != inImgFmt) break;
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_2_0:CFG_RGB_3D_2_1;
				} else if (VIDEO_3DF_SS == inImgFmt) {
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_2_0:CFG_RGB_3D_2_1;
				} else if (VIDEO_3DF_FS == inImgFmt) {
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_5_0:CFG_RGB_3D_5_1;
				}
				break;
			case LX_3D_OUT_DUAL :
				if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS != out3DF) break;
					if (VIDEO_3DF_FS != inImgFmt) break;
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_3_0:CFG_RGB_3D_3_1;
				} else if (VIDEO_3DF_SS == inImgFmt) {
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_3_0:CFG_RGB_3D_3_1;
				} else if (VIDEO_3DF_FS == inImgFmt) {
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_6_0:CFG_RGB_3D_6_1;
				}
				break;
			case LX_3D_OUT_OFF :
				if (VIDEO_3DF_RUN_2D != VIDEO_GetFormatOf3DF(VIDEO_3DF_RUN_MODE)) break;
				//sideMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_SIDE_L_T:CFG_SIDE_R_B;
				sideMode = CFG_SIDE_R_B;
				if ( VIDEO_3DF_MODE_NORMAL == mode3DF ) {
					if (VIDEO_3DF_SS != out3DF) break;
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_2_0:CFG_RGB_3D_2_1;
				} else if (VIDEO_3DF_FS == inImgFmt) {
					rgbMode = (LX_3D_LR_ORDER_L_FIRST == lrOrder)?CFG_RGB_3D_5_0:CFG_RGB_3D_5_1;
				}
				break;
			default :
				break;
		}
		if (ret) break;
		ret = FRC_MFT3D_SetFrcOutType(rgbMode, sideMode);
	} while (0);

	return ret;
}

static DTV_STATUS_T FRC_MFT3D_SetFrcOutType(cfg_rgb_mode rgbMode, cfg_side_mode sideMode)
{
	cfg_color_space colorSpace;
	cfg_inp_mode    inpMode;
	static cfg_rgb_mode    rgbMode_Old    = CFG_RGB_BYPASS;
	static cfg_side_mode   sideMode_Old   = CFG_SIDE_ALL;
	static cfg_color_space colorSpace_Nor = CFG_CS_YUV;
	static cfg_inp_mode    inpMode_Nor    = CFG_INP_11;
	static BOOLEAN bInitialized = FALSE;

	do {
		if ( (rgbMode_Old == rgbMode) && (sideMode_Old == sideMode) ) break;
		rgbMode_Old  = rgbMode;
		sideMode_Old = sideMode;

		do {
			if (bInitialized) break;
			bInitialized = TRUE;
			colorSpace_Nor = frcCurrConfig.colorSpace;
			inpMode_Nor    = frcCurrConfig.inpMode;
		} while (0);

		do {
			colorSpace     = CFG_CS_RGB;
			inpMode        = CFG_INP_11;
			if (CFG_RGB_BYPASS != rgbMode)  break;
			if (CFG_SIDE_ALL   != sideMode) break;
			colorSpace     = colorSpace_Nor;
			inpMode        = inpMode_Nor;
		} while (0);

		frcCurrConfig.colorSpace = colorSpace;
		frcCurrConfig.inpMode	 = inpMode;

	frcCurrConfig.rgbMode = rgbMode;
		frcCurrConfig.sideMode	 = sideMode;
	} while (0);

	return OK;
}
#endif
#endif
#endif
#endif
