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
 * Video decoding driver header for vdec device.
 * VDEC device will teach you how to make device driver with lg115x platform.
 *
 * author     Junghyun son(junghyun.son@lge.com)
 * version    1.0
 * date       2012.05.10
 * note       Additional information.
 *
 */
 
#ifndef _VDC_DRV_H_
#define _VDC_DRV_H_


/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/wait.h>
#include "../vds/disp_clear_q.h"
#include "../decoded_q.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
	VDC Codec Type.
		decoding formats supported by the VDC.
*/
typedef enum
{
	VDC_CODEC_H264_HP		=  0,
	VDC_CODEC_VC1_RCV_V1	=  1,
	VDC_CODEC_VC1_RCV_V2	=  2,
	VDC_CODEC_VC1_ES		=  3,
	VDC_CODEC_MPEG2_HP		=  4,
	VDC_CODEC_MPEG4_ASP		=  5,
	VDC_CODEC_XVID			=  6,
	VDC_CODEC_DIVX3			=  7,
	VDC_CODEC_DIVX4			=  8,
	VDC_CODEC_DIVX5			=  9,
	VDC_CODEC_RVX			= 10,
	VDC_CODEC_AVS			= 11,
	VDC_CODEC_VP8			= 12,
	VDC_CODEC_H264_MVC		= 13,
	VDC_CODEC_THEORA		= 14,
	VDC_CODEC_SW			= 15,

	VDC_CODEC_MIN			= VDC_CODEC_H264_HP,
	VDC_CODEC_MAX			= VDC_CODEC_SW,
	VDC_CODEC_INVALID
} VDC_CODEC_T;

typedef enum
{
	VDC_CODEC_STATE_NULL = 0,
	VDC_CODEC_STATE_READY,	
	VDC_CODEC_STATE_FEEDING,
	VDC_CODEC_STATE_RUNNING
} VDC_CODEC_STATE_T;

/**
	VDC Skip Mode & Type.
		picture skip mode and type supported by the VDC.
*/
typedef enum
{
	VDC_SKIP_NONE			= 0,			///< decode IPB frame.
	VDC_SKIP_PB				= 1,			///< I picture only (PB skip)
	VDC_SKIP_B				= 2,			///< IP picture only (B skip only)
	VDC_SKIP_MIN			= VDC_SKIP_NONE,
	VDC_SKIP_MAX			= VDC_SKIP_B,
	VDC_SKIP_INVALID
} VDC_SKIP_T;

/* Will be removed */
typedef enum
{
	VDC_SRC_SDEC0	= 0,
	VDC_SRC_SDEC1	= 1,
	VDC_SRC_SDEC2	= 2,
	VDC_SRC_BUFF0	= 3,
	VDC_SRC_BUFF1	= 4,
	VDC_SRC_BUFFTVP	= 5,
	VDC_SRC_FRMBUF0	= 6,
	VDC_SRC_FRMBUF1	= 7
} VDC_SRC_T;

typedef enum
{
	VDC_CORE_BODA950 = 0,	
	VDC_CORE_NOT_SUPPORTED,
	VDC_CORE_MAX,
	VDC_CORE_END = 0xFF
} VDC_CORE_T;

typedef enum
{
	VDC_MEMORY_FORMAT_TILED = 0,
	VDC_MEMORY_FORMAT_RASTER	
} VDC_MEMORY_FORMAT_T;

/**
	VDC Open Parameter Structure.
*/
typedef struct
{
	UINT8			ui8VesCh;
	void			*priv;
	VDC_SRC_T		ui8Src;
	VDC_CODEC_T		ui8Vcodec;
	UINT32			ui32CpbBufAddr;
	UINT32			ui32CpbBufSize;
	clear_q_t		*clear_q;
	decoded_q_t		*decoded_q;
	VDC_MEMORY_FORMAT_T	output_memory_format;
} VDC_OPEN_PARAM_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/
void		VDC_Init(void);
UINT8		VDC_Open(VDC_OPEN_PARAM_T* pstOpenParam);
void		VDC_Close(UINT8 ui8VdcCh);
void		VDC_Reset(UINT8 ui8VdcCh);
void		VDC_Start(UINT8 ui8VdcCh);
void		VDC_Update(UINT8 ui8VdcCh);
void		VDC_Flush(UINT8 ui8VdcCh);
void		VDC_Stop(UINT8 ui8VdcCh);		
VDC_CODEC_STATE_T VDC_GetCoreState(UINT8 ui8VdcCh, wait_queue_head_t **wait);
void		VDC_SetSkipMode(UINT8 ui8VdcCh, VDC_SKIP_T eSkipMode);
void		VDC_SetUserDataOutput(UINT8 ui8VdcCh, BOOLEAN bEnable);
void		VDC_GetFrame(UINT8 ui8VdcCh, UINT8 ui8FrameNum, void* vpFrameBuf);

#ifdef __cplusplus
}
#endif
#endif /* _VDC_DRV_H_ */

