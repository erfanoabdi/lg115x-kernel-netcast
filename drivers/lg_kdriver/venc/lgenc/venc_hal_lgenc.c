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
 *  hal api implementation for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2012.07.23
 *  note		Additional information.
 *
 *  @addtogroup lg1154_venc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <asm/io.h>
#include "os_util.h"
#include "venc_hal.h"

#include "venc_core.h"
#include "venc_isr.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define LGENC_QP_DEFAULT	10

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

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
static VENC_HAL_API_T _VencHalApiLGEnc;

/*========================================================================================
	Implementation Group
========================================================================================*/

VENC_HAL_API_T *VENC_HAL_InitializeLGEnc( void )
{
	return &_VencHalApiLGEnc;
}

static int _VENC_DeviceInitialize ( void )
{
	VENC_DeviceInit();

	return RET_OK;
}

static int _VENC_DeviceFinalize ( void )
{
	VENC_DeviceFinal();

	return RET_OK;
}

static int _VENC_Initialize( void )
{
	VENC_Initailize();

	return RET_OK;
}

static int _VENC_SetInputConfig ( LX_VENC_ENC_INPUT_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	VENC_SetEncoderInput( pstParams );

	return RET_OK;
}

static int _VENC_SetCommand ( LX_VENC_ENC_COMMAND_T eParam )
{
	return VENC_SetCommand( eParam );
}

static int _VENC_SetQuality ( LX_VENC_ENC_QUALITY_T eParam )
{
	return VENC_SetPictureQuality( eParam );
}

static int _VENC_SetQPLevel ( UINT32 ui32Param )
{
	// 2012/11/1: Firmware에서는 qp_level이라는 값으로 설정하고 있음.
	// 새로운 인코더와 값을 맞추기 위해서 기존의 기본값을 빼기로함.
	
	return VENC_SetQPValue( ui32Param - LGENC_QP_DEFAULT );
}

static int _VENC_SetGOP ( UINT32 u32Param )
{
	return VENC_SetGOP( u32Param );
}

static int _VENC_SetTargetBitrate ( UINT32 u32Param )
{
	return VENC_SetTargetBitrate( u32Param );
}

static int _VENC_SetEncodeType( LX_VENC_ENCODE_TYPE_T eParam )
{
	if ( eParam > LX_VENC_ENCODE_TYPE_MAX )
	{
		return RET_INVALID_PARAMS;
	}

	return RET_OK;
}

#if 0
static int _VENC_GetBufferInfo ( LX_VENC_BUFFER_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return RET_OK;
}
#endif

static int _VENC_GetEncodeInfo( LX_VENC_ENC_INFO_T *pstParams )
{
	int ret;
	
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	ret = VENC_GetEncodingInfomation( pstParams );

	// firmware에서 설정하는 값이 QP = qp_level + 10임.
	// 2011/11/01 H13B0와 동일한 값으로 설정하기 위해서 kadp에서는 qp값만 알고
	// 드라이버에서 firmware로 해당 값을 변환하도록 수정함.
	pstParams->ui8QPLevel += LGENC_QP_DEFAULT;

	return ret;
}

static int _VENC_GetFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return VENC_GetInputFrameImage( pstParams );
}

static int _VENC_GetOutputBuffer( LX_VENC_ENC_OUTPUT_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return VENC_GetOutputBufferState( pstParams );
}

static int _VENC_GetPerformance( LX_VENC_ENC_PERPERMANCE_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return VENC_GetPerformanceGauge( pstParams );
}

static irqreturn_t _VENC_ISRHandler( void )
{

	VENC_ISR();

	return IRQ_HANDLED;
}

/*----------------------------------------------------------------------------------------
	Static Function Definition
----------------------------------------------------------------------------------------*/
static VENC_HAL_API_T _VencHalApiLGEnc =
{
	.version			= LX_CHIP_REV(L9,A0),

	// Initialize/Finalize functions
	.DeviceInitialize 	= _VENC_DeviceInitialize,
	.DeviceFinalize 	= _VENC_DeviceFinalize,
	.Initialize			= _VENC_Initialize,

	// Getter functions
	.GetOutputBuffer	= _VENC_GetOutputBuffer,
	.GetPerformance		= _VENC_GetPerformance,
	.GetEncodeInfo		= _VENC_GetEncodeInfo,
	.GetFrameImage		= _VENC_GetFrameImage,

	// Setter functions
	.SetEncodeType 		= _VENC_SetEncodeType,
	.SetInputConfig 	= _VENC_SetInputConfig,
	.SetCommand 		= _VENC_SetCommand,
	.SetQuality			= _VENC_SetQuality,
	.SetQPLevel			= _VENC_SetQPLevel,
	.SetGOP				= _VENC_SetGOP,
	.SetTargetBitrate	= _VENC_SetTargetBitrate,

	// ISR Handler
	.ISRHandler			= _VENC_ISRHandler,
};

/** @} */

