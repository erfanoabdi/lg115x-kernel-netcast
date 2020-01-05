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
#include "venc_drv.h"
//#include "venc_kapi.h"
#include "h1encode.h"

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
static VENC_HAL_API_T _VencHalApiH13Bx;

/*========================================================================================
	Implementation Group
========================================================================================*/
VENC_HAL_API_T *VENC_HAL_InitializeH13Bx( void )
{
	return &_VencHalApiH13Bx;
}

static int _VENC_DeviceInitialize ( void )
{
	
	H1EncodeInitialize();

	return RET_OK;
}

static int _VENC_DeviceFinalize ( void )
{
	
	H1EncodeFinalize();

	return RET_OK;
}

static int _VENC_Initialize( void )
{

	return RET_OK;
}

static int _VENC_SetInputConfig ( LX_VENC_ENC_INPUT_T *pstParams )
{
	int ret;
	
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	ret = H1EncodeSetFramerate( pstParams->ui32FrameRate );

	if ( ret != RET_OK )
	{
		return ret;
	}

	ret = H1EncodeSetInputSource( pstParams->eInputSource );

	return ret;
}

static int _VENC_SetCommand ( LX_VENC_ENC_COMMAND_T eParam )
{
	int ret;

	ret = H1EncodeCommand( eParam );

	return ret;
}

static int _VENC_SetQuality ( LX_VENC_ENC_QUALITY_T eParam )
{
	u32 bitrate;	// bit/s

	switch( eParam )
	{
		case LX_VENC_QUALITY_LOW:
			bitrate = 600 * 1000;	// 600kbps
			break;
		case LX_VENC_QUALITY_MID_LOW:
			bitrate = 1200 * 1000;	// 1200kbps
			break;
		case LX_VENC_QUALITY_MIDDLE:
			bitrate = 1800 * 1000; 	// 1800kbps
			break;
		case LX_VENC_QUALITY_MID_HIGH:
			bitrate = 2400 * 1000;	// 2400kbps
			break;
		case LX_VENC_QUALITY_HIGH:
		default:
			bitrate = 3000 * 1000;	// 3000kbps
			break;
	}
	
	return H1EncodeSetBitrate( bitrate );
}

static int _VENC_SetGOP ( UINT32 u32Param )
{
	H1EncodeSetGOP( u32Param );

	return RET_OK;
}

static int _VENC_SetTargetBitrate( UINT32 targetBitrate )
{
	// In: targetBitrate kbits/s
	targetBitrate = targetBitrate * 1000;
	
	return H1EncodeSetBitrate( targetBitrate );
}

static int _VENC_SetQPLevel( UINT32 u32Param )
{
	H1EncodeSetQPValue( u32Param );

	return RET_OK;
}

static int _VENC_SetEncodeType( LX_VENC_ENCODE_TYPE_T eParam )
{
	if ( eParam > LX_VENC_ENCODE_TYPE_MAX )
	{
		return RET_INVALID_PARAMS;
	}

	H1EncodeSetEncodeType( eParam );
	
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
	u16 width, height;
	
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}	
	
	pstParams->ui32FrameRate = H1EncodeGetFramerate();

	// Kadp에 반환할 때는 kbits/s 단위
	pstParams->ui32BitRate		= H1EncodeGetBitrate() / 1000;
	
	pstParams->ui8QPLevel		= H1EncodeGetQPValue();
	pstParams->ui8GopN			= H1EncodeGetGOP();
	pstParams->ui8GopM			= 0;
	pstParams->ui8GopIdr		= 0;

	if ( H1EncodeGetResolution( &width, &height ) == RET_OK )
	{
		pstParams->ui16Width = width;
		pstParams->ui16Height = height;
	}
	
	return RET_OK;
}

static int _VENC_GetFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	H1EncodeGetFrameImage( pstParams );

	return RET_OK;
}

static int _VENC_GetOutputBuffer( LX_VENC_ENC_OUTPUT_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	return H1EncodeGetOutputBuffer( pstParams );
}

static int _VENC_GetPerformance( LX_VENC_ENC_PERPERMANCE_T *pstParams )
{
	if ( pstParams == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	pstParams->ui16FrameCount 	= (UINT16) H1EncodeGetEncodedFrameCount();
	pstParams->ui16Duration 	= (UINT16) H1EncodeGetEncodeMsec();
	pstParams->ui32Bitrate		= H1EncodeGetBitrate();

	return RET_OK;
}

static int _VENC_PROC_ReadStatus( char * buffer )
{
	if ( buffer == NULL )
	{
		return 0;
	}

	return H1EncodeReadStatus( buffer );
}

static irqreturn_t _VENC_ISRHandler( void )
{
	H1EncodeISRHandler();

	return IRQ_HANDLED;
}

/*----------------------------------------------------------------------------------------
	Static Function Definition
----------------------------------------------------------------------------------------*/
static VENC_HAL_API_T _VencHalApiH13Bx = 
{
	.version			= LX_CHIP_REV(H13,B0),

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
	.SetGOP				= _VENC_SetGOP,
	.SetTargetBitrate	= _VENC_SetTargetBitrate,
	.SetQPLevel			= _VENC_SetQPLevel,

	.PROC_ReadStatus 	= _VENC_PROC_ReadStatus,

	// ISR Handler
	.ISRHandler			= _VENC_ISRHandler,
};

/** @} */

