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
 *  hxenc api header file for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2013.01.18
 *  note		Additional information.
 *
 *  @addtogroup lg1154_venc
 *	@{
 */

#ifndef _HXENC_API_H_
#define _HXENC_API_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef HXENC_PRINT
#define HXENC_PRINT( format, args... ) printk( "[HXENC_PRINT] " format, ##args )
#endif

#ifndef HXENC_ERROR
#define HXENC_ERROR( format, args... ) printk( "[HXENC_ERROR] " format, ##args )
#endif

#ifndef HXENC_TRACE
#define HXENC_TRACE( format, args... ) printk( "[HXENC_TRACE] " format, ##args )
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HXENC_OK = 0,
	HXENC_FRAME_READY = 1,

	HXENC_ERROR = -1,
	HXENC_NULL_ARGUMENT = -2,
	HXENC_INVALID_ARGUMENT = -3,
	HXENC_MEMORY_ERROR = -4,
	HXENC_EWL_ERROR = -5,
	HXENC_EWL_MEMORY_ERROR = -6,
	HXENC_INVALID_STATUS = -7,
	HXENC_OUTPUT_BUFFER_OVERFLOW = -8,
	HXENC_HW_BUS_ERROR = -9,
	HXENC_HW_DATA_ERROR = -10,
	HXENC_HW_TIMEOUT = -11,
	HXENC_HW_RESERVED = -12,
	HXENC_SYSTEM_ERROR = -13,
	HXENC_INSTANCE_ERROR = -14,
	HXENC_HRD_ERROR = -15,
	HXENC_HW_RESET = -16
} HXENC_RET_T;

typedef enum
{
	HXENC_INTRA_FRAME = 0,			/* IDR-frame or field */
	HXENC_PREDICTED_FRAME = 1,		/* P-frame or field */
	HXENC_NONIDR_INTRA_FRAME = 2,	/* Non-IDR I-frame or field */
	HXENC_NOTCODED_FRAME
} HXENC_PICTURE_CODING_TYPE_T;

typedef const void *HXENC_H264INST_T;
typedef const void *HXENC_VP8INST_T;

typedef struct
{
	UINT32 width;
	UINT32 height;
	UINT32 stride;
	UINT32 frameRateDenom;
	UINT32 frameRateNum;
	UINT32 eFrameType;
} HXENC_CONFIG_T;

typedef struct
{
	BOOLEAN bEnableTargetBitrate;
	UINT32 bitPerSecond;
	UINT32 hrdCpbSize;
	
	BOOLEAN bEnableFixedQP;
	UINT32 qp;
	UINT32 qpMin;

	BOOLEAN bEnableGOPLength;
	UINT32 gopLength;

} HXENC_RATECTRL_T;

typedef struct
{
	UINT32 fieldOrder;
	UINT32 sarWidth;		// sampleAspectRatioWidth
	UINT32 sarHeight;		// sampleAspectRatioHeight
} HXENC_CODINGCTRL_T;

typedef struct
{
	UINT32 inputWidth;
	UINT32 inputHeight;
	
	UINT32 videoStabilization;
} HXENC_PREPROCESSING_CFG_T;

typedef struct
{
	UINT32 busLuma;
	UINT32 busChromaU;
	UINT32 busChromaV;
	UINT32 timeIncrement;

	UINT32 *pOutBuf;
	UINT32 busOutBuf;
	UINT32 outBufSize;

	HXENC_PICTURE_CODING_TYPE_T codingType;

	UINT32 busLumaStab;
} HXENC_INPUT_T;

typedef struct
{
	HXENC_PICTURE_CODING_TYPE_T codingType;

	UINT32 streamSize;
} HXENC_H264_OUTPUT_T;

typedef struct
{
	HXENC_PICTURE_CODING_TYPE_T codingType;

	UINT32 *pOutBuf[9];
	UINT32 streamSize[9];
	UINT32 frameSize;
} HXENC_VP8_OUTPUT_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef VENC_HXENC_BUILTIN
int HXENC_BuiltIn_Init(void);
#endif

// For Encoder HW
int HXENC_Init( UINT32 regBase, UINT32 regSize );

void HXENC_Cleanup( void );


// For EWL
UINT32 HXENC_ReadIRQ( void );

void HXENC_WriteIRQ( UINT32 value );

int HXENC_WakeupIRQ( void );


// For Memalloc
int HXENC_MemallocInit( UINT32 start, UINT32 end );


// for H264
HXENC_RET_T	HXENC_H264Init( const HXENC_CONFIG_T *pstConfig, HXENC_H264INST_T * pInst );

HXENC_RET_T HXENC_H264Release( HXENC_H264INST_T inst );

HXENC_RET_T	HXENC_H264SetRateCtrl( HXENC_H264INST_T inst, const HXENC_RATECTRL_T *pstRateCtrl );

HXENC_RET_T HXENC_H264GetRateCtrl( HXENC_H264INST_T inst, HXENC_RATECTRL_T *pstRateCtrl );

HXENC_RET_T HXENC_H264SetCodingCtrl( HXENC_H264INST_T inst, const HXENC_CODINGCTRL_T *pstCodingCtrl );

HXENC_RET_T HXENC_H264SetPreProcessing( HXENC_H264INST_T inst, const HXENC_PREPROCESSING_CFG_T *pstPreProcCfg );

HXENC_RET_T HXENC_H264StrmStart( HXENC_H264INST_T isnt, const HXENC_INPUT_T *pstInput, HXENC_H264_OUTPUT_T *pstOutput );

HXENC_RET_T HXENC_H264StrmEncode( HXENC_H264INST_T inst, const HXENC_INPUT_T *pstInput, HXENC_H264_OUTPUT_T *pstOutput );


// for VP8
HXENC_RET_T HXENC_VP8Init( const HXENC_CONFIG_T *pstConfig, HXENC_VP8INST_T *pInst );

HXENC_RET_T HXENC_VP8Release( HXENC_VP8INST_T inst );

HXENC_RET_T HXENC_VP8SetRateCtrl( HXENC_VP8INST_T inst, const HXENC_RATECTRL_T *pstRateCtrl );

HXENC_RET_T HXENC_VP8SetCodingCtrl( HXENC_VP8INST_T inst, const HXENC_CODINGCTRL_T *pstCodingCtrl );

HXENC_RET_T HXENC_VP8SetPreProcessing( HXENC_VP8INST_T inst, const HXENC_PREPROCESSING_CFG_T *pstPreProcCfg );

HXENC_RET_T HXENC_VP8StrmEncode( HXENC_VP8INST_T inst, const HXENC_INPUT_T *pstInput, HXENC_VP8_OUTPUT_T *pstOutput );


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
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

/*----------------------------------------------------------------------------------------
	Static Function Definition
----------------------------------------------------------------------------------------*/

#endif	// _HXENC_API_H_

/** @} */

