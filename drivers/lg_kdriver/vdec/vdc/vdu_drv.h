/* ****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * *****************************************************************************************/

/** @file
 *
 * video decoding unit driver header for vdec device.
 * VDEC device will teach you how to make device driver with lg1154 platform.
 *
 * author     Youngwoo Jin(youngwoo.jin@lge.com)
 * version    1.0
 * date       2013.01.06
 * note       Additional information.
 *
 */

#ifndef _VDU_DRV_H_
#define _VDU_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VDU_INVALID_HANDLE			(0xFFFFFFFF)
#define VDU_INVALID_ADDRESS			(0x00000000)
#define VDU_INVALID_FRAME_INDEX		(-1)
#define VDU_FRAME_INDEX_SKIPPED		(-10)
#define VDU_OPTION_INIT_VALUE		{	.ePicScanMode	= VDU_PIC_SCAN_INVALID,	\
										.eUserData		= VDU_USERDATA_INVALID }

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef UINT32	VDU_HANDLE_T;

typedef enum
{
	VDU_RET_OK					= 0,
	VDU_RET_INVALID_CH			= 1,
	VDU_RET_INVALID_PARAM		= 2,
	VDU_RET_DPB_FULL			= 3,
	VDU_RET_SEQ_INIT_FAIL		= 4,
	VDU_RET_ERROR				= 5,

	VDU_RET_MIN					= VDU_RET_OK,
	VDU_RET_MAX					= VDU_RET_ERROR,
	VDU_RET_INVALID
} VDU_RET_T;

typedef enum
{
	VDU_NOTI_SUCCESS			=  0,
	VDU_NOTI_DISPLAY			=  1,
	VDU_NOTI_DECODING_ERROR		=  2,
	VDU_NOTI_CPB_EMPTY			=  3,
	VDU_NOTI_HEADER_NOT_FOUND	=  4,
	VDU_NOTI_SEQ_INIT_FAIL		=  5,
	VDU_NOTI_DPB_FULL			=  6,
	VDU_NOTI_SUSPEND			=  7,
	VDU_NOTI_FRAME_SKIP			=  8,
	VDU_NOTI_SKIP_EMPTY			=  9,
	VDU_NOTI_REQUEST_AU			= 10,

	VDU_NOTI_MIN				= VDU_NOTI_SUCCESS,
	VDU_NOTI_MAX				= VDU_NOTI_REQUEST_AU,
	VDU_NOTI_INVALID
} VDU_NOTI_T;

typedef enum
{
	VDU_FRM_SCAN_INVALID		= 0,
	VDU_FRM_SCAN_TOP_FIRST		= 1,
	VDU_FRM_SCAN_BOTTOM_FIRST	= 2,
	VDU_FRM_SCAN_PROGRESSIVE	= 3,

	VDU_FRM_SCAN_MIN			= VDU_FRM_SCAN_TOP_FIRST,
	VDU_FRM_SCAN_MAX			= VDU_FRM_SCAN_PROGRESSIVE,
} VDU_FRM_SCAN_T;

typedef enum
{
	VDU_FRM_3D_LEFT				= 0,
	VDU_FRM_3D_RIGHT			= 1,
	VDU_FRM_3D_NONE				= 2,

	VDU_FRM_3D_MIN				= VDU_FRM_3D_LEFT,
	VDU_FRM_3D_MAX				= VDU_FRM_3D_NONE,
	VDU_FRM_3D_INVALID
} VDU_FRM_3D_T;

typedef enum
{
	VDU_FRM_MAP_LINEAR			= 0,
	VDU_FRM_MAP_TILED			= 1,
	VDU_FRM_MAP_TILED_MIXED_V	= 1,
	VDU_FRM_MAP_TILED_FRAME_V	= 2,

	VDU_FRM_MAP_MIN				= VDU_FRM_MAP_LINEAR,
	VDU_FRM_MAX					= VDU_FRM_MAP_TILED_FRAME_V,
	VDU_FRM_INVALID
} VDU_FRM_MAP_T;

typedef enum
{
	VDU_CODEC_MPEG2				=  0,
	VDU_CODEC_MPEG4				=  1,
	VDU_CODEC_H263				=  2,
	VDU_CODEC_H263_SORENSON		=  3,
	VDU_CODEC_XVID				=  4,
	VDU_CODEC_DIVX3				=  5,
	VDU_CODEC_DIVX4				=  6,
	VDU_CODEC_DIVX5				=  7,
	VDU_CODEC_H264_AVC			=  8,
	VDU_CODEC_H264_MVC			=  9,
	VDU_CODEC_VC1_RCV_V1		= 10,
	VDU_CODEC_VC1_RCV_V2		= 11,
	VDU_CODEC_VC1_ES			= 12,
	VDU_CODEC_RVX				= 13,
	VDU_CODEC_AVS				= 14,
	VDU_CODEC_THEORA			= 15,
	VDU_CODEC_VP3				= 16,
	VDU_CODEC_VP8				= 17,

	VDU_CODEC_MIN				= VDU_CODEC_MPEG2,
	VDU_CODEC_MAX				= VDU_CODEC_VP8,
	VDU_CODEC_INVALID
} VDU_CODEC_T;

typedef enum
{
	VDU_PIC_SCAN_ALL			= 0,
	VDU_PIC_SCAN_I				= 1,
	VDU_PIC_SCAN_IP				= 2,

	VDU_PIC_SCAN_MIN			= VDU_PIC_SCAN_ALL,
	VDU_PIC_SCAN_MAX			= VDU_PIC_SCAN_IP,
	VDU_PIC_SCAN_INVALID
} VDU_PIC_SCAN_T;

typedef enum
{
	VDU_USERDATA_DISABLE		= 0,
	VDU_USERDATA_ENABLE			= 1,

	VDU_USERDATA_MIN			= VDU_USERDATA_DISABLE,
	VDU_USERDATA_MAX			= VDU_USERDATA_ENABLE,
	VDU_USERDATA_INVALID
} VDU_USERDATA_T;

typedef struct
{
	VDU_CODEC_T		eCodecType;
	VDU_FRM_MAP_T	eFrameMapType;
	UINT32			ui32CPBAddr;
	UINT32			ui32CPBSize;
	UINT32			ui32DataSize;
} VDU_OPEN_PARAM_T;

typedef struct
{
	UINT32			ui32StartAddr;
	UINT32			ui32Size;
} VDU_AU_T;

typedef struct
{
	VDU_PIC_SCAN_T	ePicScanMode;
	VDU_USERDATA_T	eUserData;
} VDU_OPTION_T;

typedef struct
{
	VDU_NOTI_T		eNotiType;
	SINT8			si8FrmIndex;
	BOOLEAN			bDecSuccess;
	BOOLEAN			bFieldSuccess;
} VDU_DEC_RESULT_T;

typedef struct
{
	struct {
		UINT32			ui32Stride;
		UINT32			ui32PicWidth;
		UINT32			ui32PicHeight;
		UINT16			ui16CropLeft;
		UINT16			ui16CropRight;
		UINT16			ui16CropTop;
		UINT16			ui16CropBottom;
	}				stRect;

	struct {
		UINT16			ui16ParW;
		UINT16			ui16ParH;
		UINT8			ui8Mpeg2Dar;
	}				stAspectRatio;

	struct {
		UINT32			ui32TiledBase;
		UINT32			ui32Y;
		UINT32			ui32Cb;
		UINT32			ui32Cr;
	}				stAddress;

	struct {
		UINT32			ui32Residual;
		UINT32			ui32Divider;
		BOOLEAN			bVariable;
	}				stFrameRate;

	struct {
		VDU_FRM_MAP_T	eFrameMapType;
		VDU_FRM_SCAN_T	eFrameScanType;
		UINT8			ui8DisplayPeriod;
		BOOLEAN			bLowDelay;
		SINT8			si8FramePackArrange;		// 3D SEI
		VDU_FRM_3D_T	eOrderOf3D;
		UINT8			ui8ErrorRate;

		UINT8			ui8PictureType;
		BOOLEAN			bTopFieldFirst;
		BOOLEAN			bRepeatFirstField;
		BOOLEAN			bFieldPicture;
	}				stDispInfo;

	struct {
		UINT8			ui8ActiveFmtDesc;
		UINT32			ui32Address;
		UINT32			ui32Size;
	} 				stUserData;

	UINT32			ui32CurRdPtr;
	UINT32			ui32ConsumeBytes;
	UINT8			ui8NumOfFrames;

	void*			pAddtionalData;
} VDU_FRM_INFO_T;

typedef void (*VDU_CALLBACK_FN_T)(VDU_HANDLE_T hInstance, VDU_DEC_RESULT_T* pstDecResult);

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/
VDU_RET_T		VDU_Init(VDU_CALLBACK_FN_T pfnCallback);
VDU_HANDLE_T	VDU_Open(VDU_OPEN_PARAM_T *pstOpenParam);
VDU_RET_T		VDU_Close(VDU_HANDLE_T hInstance);
VDU_RET_T		VDU_Flush(VDU_HANDLE_T hInstance);
VDU_RET_T		VDU_Reset(VDU_HANDLE_T hInstance);
VDU_RET_T		VDU_StartDecoding(VDU_HANDLE_T hInstance);
VDU_RET_T		VDU_GetFrameInfo(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, VDU_FRM_INFO_T *pstFrameInfo);
VDU_RET_T		VDU_GetLinearFrame(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, void* pFrameBuf);
VDU_RET_T		VDU_FeedAu(VDU_HANDLE_T hInstance, VDU_AU_T* pstAu, void* pData);
VDU_RET_T		VDU_SetOption(VDU_HANDLE_T hInstance, VDU_OPTION_T* pstOption);
VDU_RET_T		VDU_ClearFrame(VDU_HANDLE_T hInstance, SINT8 si8FrameIdx);
void			VDU_Isr(UINT8 ui8CoreNum);

/*----------------------------------------------------------------------------------------
	For independent module
----------------------------------------------------------------------------------------*/
typedef VDU_RET_T	(*VDU_INIT_FN_T)(VDU_CALLBACK_FN_T pfnNotiCallback, const UINT16* pui16Data, UINT32 ui32Size);
typedef VDU_HANDLE_T(*VDU_OPEN_FN_T)(VDU_OPEN_PARAM_T *pstOpenParam);
typedef VDU_RET_T	(*VDU_CLOSE_FN_T)(VDU_HANDLE_T hInstance);
typedef VDU_RET_T	(*VDU_FLUSH_FN_T)(VDU_HANDLE_T hInstance);
typedef VDU_RET_T	(*VDU_RESET_FN_T)(VDU_HANDLE_T hInstance);
typedef VDU_RET_T	(*VDU_START_DECODING_FN_T)(VDU_HANDLE_T hInstance);
typedef VDU_RET_T	(*VDU_GET_FRAME_INFO_FN_T)(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, VDU_FRM_INFO_T *pstFrameInfo);
typedef VDU_RET_T	(*VDU_GET_LINEAR_FRAME_FN_T)(VDU_HANDLE_T hInstance, SINT8 si8FrameNum, void* pFrameBuf);
typedef VDU_RET_T	(*VDU_FEED_AU_FN_T)(VDU_HANDLE_T hInstance, VDU_AU_T* pstAu, void* pData);
typedef VDU_RET_T	(*VDU_SET_OPTION_FN_T)(VDU_HANDLE_T hInstance, VDU_OPTION_T* pstOption);
typedef VDU_RET_T	(*VDU_CLEAR_FRAME_FN_T)(VDU_HANDLE_T hInstance, SINT8 si8FrameIdx);
typedef void		(*VDU_ISR_FN_T)(UINT8 ui8CoreNum);

typedef struct
{
	VDU_INIT_FN_T				pfnInit;
	VDU_OPEN_FN_T				pfnOpen;
	VDU_CLOSE_FN_T				pfnClose;
	VDU_FLUSH_FN_T				pfnFlush;
	VDU_RESET_FN_T				pfnReset;
	VDU_START_DECODING_FN_T		pfnStartDecoding;
	VDU_GET_FRAME_INFO_FN_T		pfnGetFrameInfo;
	VDU_GET_LINEAR_FRAME_FN_T	pfnGetLinearFrame;
	VDU_FEED_AU_FN_T			pfnFeedAu;
	VDU_SET_OPTION_FN_T			pfnSetOption;
	VDU_CLEAR_FRAME_FN_T		pfnClearFrame;
	VDU_ISR_FN_T				pfnIsr;
} VDU_OPERATIONS_T;

VDU_RET_T		VDU_RegisterOperations(VDU_OPERATIONS_T* pstOperations);

#ifdef __cplusplus
}
#endif

#endif /* _VDU_DRV_H_ */

