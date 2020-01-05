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
 *  register api implementation for venc device of H13.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		jaeseop.so (jaeseop.so@lge.com)
 *  version		1.0
 *  date		2012.08.08
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
#include <linux/kthread.h>
#include <asm/io.h>			// for ioremap()/iounmap()
//#include <linux/wait.h> 	// for interruptible_sleep_on_timeout()
#include <linux/slab.h>
#include <linux/delay.h>	// for msleep()


#include "base_types.h"
#include "os_util.h"
#include "../venc_cfg.h"
#include "../venc_drv.h"

#include "venc_h13b0_regprep.h"
#include "venc_kapi.h"

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
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _DefaultSetOSB( H1ENCODE_API_T *pstEncoder, H1ENCODE_MEM_T memOSB);
static void _DefaultSetESB( H1ENCODE_API_T *pstEncoder, H1ENCODE_MEM_T memESB);
static void _DefaultSetAUI( H1ENCODE_API_T *pstEncoder, H1ENCODE_MEM_T memAUI);

static int _DefaultSetFrameType( H1ENCODE_API_T *pstEncoder, H1ENCODE_FRAME_TYPE_T frameType );
static int _DefaultSetFrameSize( H1ENCODE_API_T *pstEncoder, u32 width, u32 height, u32 stride);
static int _DefaultSetBitrate( H1ENCODE_API_T *pstEncoder, u32 bitrate );
static int _DefaultSetGOPLength( H1ENCODE_API_T *pstEncoder, u32 gopLength );
static int _DefaultSetFrameRate( H1ENCODE_API_T *pstEncoder, u32 frameRate );
static int _DefaultSetQPValue( H1ENCODE_API_T *pstEncoder, u32 qp );

static int _DefaultGetBitrate( H1ENCODE_API_T *pstEncoder, u32 *pBitrate );
static int _DefaultGetGOPLength( H1ENCODE_API_T *pstEncoder, u32 *pGopLength );
static int _DefaultGetFrameRate( H1ENCODE_API_T *pstEncoder, u32 *pFrameRate );
static int _DefaultGetQPValue( H1ENCODE_API_T *pstEncoder, u32 *pQP );

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#if 0
static const u32 H1ENCODE_VUI_FRAMERATE[][3] = {
	// num_units_in_tick, time_scale, framerate code
	{    0,	     0, LX_VENC_FRAME_RATE_NONE },	// NONE
	{ 1001,  48000, LX_VENC_FRAME_RATE_23HZ },	// 23.98 Hz				H1ENCODE_FRAMERATECODE_MIN
	{ 1000,  48000, LX_VENC_FRAME_RATE_24HZ },	// 24 Hz
	{ 1000,  50000, LX_VENC_FRAME_RATE_25HZ },	// 25 Hz	
	{ 1001,  60000, LX_VENC_FRAME_RATE_29HZ },	// 29.97 Hz
	{ 1000,  60000, LX_VENC_FRAME_RATE_30HZ },	// 30 Hz
	{ 1000, 100000, LX_VENC_FRAME_RATE_50HZ },	// 50 Hz	
	{ 1001, 120000, LX_VENC_FRAME_RATE_59HZ },	// 59.94 Hz
	{ 1000, 120000, LX_VENC_FRAME_RATE_60HZ },	// 60 Hz
	{ 1000,  30000, LX_VENC_FRAME_RATE_15HZ },	// 30 Hz (Only for LGE)	H1ENCODE_FRAMERATECODE_MAX
};
#else
static const u32 H1ENCODE_VUI_FRAMERATE[][3] = {
	// num_units_in_tick, time_scale, framerate code
	{	 0,	     0, LX_VENC_FRAME_RATE_NONE },	// NONE
	{ 1001,  24000, LX_VENC_FRAME_RATE_23HZ },	// 23.98 Hz				H1ENCODE_FRAMERATECODE_MIN
	{ 1000,  24000, LX_VENC_FRAME_RATE_24HZ },	// 24 Hz
	{ 1000,  25000, LX_VENC_FRAME_RATE_25HZ },	// 25 Hz	
	{ 1001,  30000, LX_VENC_FRAME_RATE_29HZ },	// 29.97 Hz
	{ 1000,  30000, LX_VENC_FRAME_RATE_30HZ },	// 30 Hz
	{ 1000,  50000, LX_VENC_FRAME_RATE_50HZ },	// 50 Hz	
	{ 1001,  60000, LX_VENC_FRAME_RATE_59HZ },	// 59.94 Hz
	{ 1000,  60000, LX_VENC_FRAME_RATE_60HZ },	// 60 Hz
	{ 1000,  15000, LX_VENC_FRAME_RATE_15HZ },	// 30 Hz (Only for LGE)	H1ENCODE_FRAMERATECODE_MAX
};
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/

H1ENCODE_API_T *H1EncodeAPISetDefault( H1ENCODE_API_T *pstEncoder )
{
	TRACE_ENTER();

	if ( pstEncoder != NULL )
	{

#if 0
		// allocate encoding functions
		pstEncoder->Open 	= _H264Open;
		pstEncoder->Close 	= _H264Close;
		pstEncoder->Encode 	= _H264Encode;
#endif

		// allocate setter fucntions
		pstEncoder->SetMemOSB = _DefaultSetOSB;
		pstEncoder->SetMemESB = _DefaultSetESB;
		pstEncoder->SetMemAUI = _DefaultSetAUI;

		pstEncoder->SetFrameSize = _DefaultSetFrameSize;
		pstEncoder->SetFrameType = _DefaultSetFrameType;
		pstEncoder->SetGOPLength = _DefaultSetGOPLength;
		pstEncoder->SetBitrate   = _DefaultSetBitrate;
		pstEncoder->SetFrameRate = _DefaultSetFrameRate;
		pstEncoder->SetQPValue   = _DefaultSetQPValue;

		// allocate getter functions
		pstEncoder->GetGOPLength = _DefaultGetGOPLength;
		pstEncoder->GetBitrate   = _DefaultGetBitrate;
		pstEncoder->GetFrameRate = _DefaultGetFrameRate;
		pstEncoder->GetQPValue   = _DefaultGetQPValue;
		
	}

	return pstEncoder;
}


////////////////////////////////////////////////////////////////////////////////
//
//	Setter functions
//
////////////////////////////////////////////////////////////////////////////////

static void _DefaultSetOSB( H1ENCODE_API_T *pstEncoder, H1ENCODE_MEM_T memOSB)
{
	if ( pstEncoder == NULL )
	{
		return;
	}

#ifdef	H1ENCODE_USE_STRUCT_ASSIGNMENT
	pstEncoder->memOSB = memOSB;
#else
	memcpy( &pstEncoder->memOSB, &memOSB, sizeof(H1ENCODE_MEM_T) );
#endif

	if (pstEncoder->eEncodeType == LX_VENC_ENCODE_TYPE_VP8)
	{
		// VP8 encoding시 내부적으로 output buffer를 2개로 나누어 사용함.
		// 그때, buffer를 연속적으로 관리할 수 없어서 전체 buffer를
		// 8개로 나누어 할당하고 그 위치는 index로 관리함.

		u32 align = 0;
		u32 frameSize = 0;
		int i;

		pstEncoder->outputFrameCount = 8;
		pstEncoder->outputFrameIndex = 0;
		align = MROUND(pstEncoder->memOSB.u32Size, 512);
		if ( align != pstEncoder->memOSB.u32Size )
		{
			align = align - 512;
		}
		frameSize = align / pstEncoder->outputFrameCount;

		for ( i = 0; i < pstEncoder->outputFrameCount; i++ )
		{
			H1ENCODE_MEM_T *mem;
			mem = &pstEncoder->memOutputFrame[i];

			mem->u32Phys = pstEncoder->memOSB.u32Phys + (frameSize * i);
			mem->u32Virt = pstEncoder->memOSB.u32Virt + (frameSize * i);
			mem->u32Size = frameSize;

			VENC_INFO("[H1ENCODE_MEM_T] 0x%08x, 0x%08x, 0x%08x\n", mem->u32Phys, mem->u32Virt, mem->u32Size);
		}
	}
}

static void _DefaultSetESB( H1ENCODE_API_T *pstEncoder, H1ENCODE_MEM_T memESB)
{
	if ( pstEncoder == NULL )
	{
		return;
	}

#ifdef	H1ENCODE_USE_STRUCT_ASSIGNMENT
	pstEncoder->memESB = memESB;
#else
	memcpy( &pstEncoder->memESB, &memESB, sizeof(H1ENCODE_MEM_T) );
#endif
}

static void _DefaultSetAUI( H1ENCODE_API_T *pstEncoder, H1ENCODE_MEM_T memAUI)
{
	if ( pstEncoder == NULL )
	{
		return;
	}

#ifdef	H1ENCODE_USE_STRUCT_ASSIGNMENT
	pstEncoder->memAUI = memAUI;
#else
	memcpy( &pstEncoder->memAUI, &memAUI, sizeof(H1ENCODE_MEM_T) );
#endif
}

static int _DefaultSetFrameType( H1ENCODE_API_T *pstEncoder, H1ENCODE_FRAME_TYPE_T frameType )
{
	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	pstEncoder->eFrameType = frameType;

	return RET_OK;
}

static int _DefaultSetFrameSize( H1ENCODE_API_T *pstEncoder, u32 width, u32 height, u32 stride)
{
	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	pstEncoder->width = width;
	pstEncoder->height = height;
	pstEncoder->stride = stride;

	return RET_OK;
}

static int _DefaultSetBitrate( H1ENCODE_API_T *pstEncoder, u32 targetBitrate )
{
	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}
	
	if ( targetBitrate < H1ENCODE_BITRATE_MIN )
	{
		targetBitrate = H1ENCODE_BITRATE_MIN;
	}
	else if ( targetBitrate > H1ENCODE_BITRATE_MAX )
	{
		targetBitrate = H1ENCODE_BITRATE_MAX;
	}

	pstEncoder->bitrate = targetBitrate;

	return RET_OK;
}

static int _DefaultSetGOPLength( H1ENCODE_API_T *pstEncoder, u32 gopLength )
{
	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	pstEncoder->gopLength = gopLength;

	return RET_OK;
}

static int _DefaultSetFrameRate( H1ENCODE_API_T *pstEncoder, u32 frameRateCode )
{
	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	if ( frameRateCode < H1ENCODE_FRAMERATECODE_MIN || frameRateCode > H1ENCODE_FRAMERATECODE_MAX )
	{
		return RET_ERROR;
}

	pstEncoder->frameRateCode 	= frameRateCode;
	pstEncoder->frameRateDenom 	= H1ENCODE_VUI_FRAMERATE[frameRateCode][0];	// num_units_in_tick
	pstEncoder->frameRateNum	= H1ENCODE_VUI_FRAMERATE[frameRateCode][1];	// time_scale	

	return RET_OK;
}

static int _DefaultSetQPValue( H1ENCODE_API_T *pstEncoder, u32 qp )
{
	if ( pstEncoder == NULL )
	{
		return RET_ERROR;
	}

	pstEncoder->qp = qp;

	return RET_OK;
}



////////////////////////////////////////////////////////////////////////////////
//
//	Getter functions
//
////////////////////////////////////////////////////////////////////////////////

static int _DefaultGetBitrate( H1ENCODE_API_T *pstEncoder, u32 *pBitrate )
{
	if ( pBitrate == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	*pBitrate = pstEncoder->bitrate;
	
	return RET_OK;
}

static int _DefaultGetGOPLength( H1ENCODE_API_T *pstEncoder, u32 *pGopLength )
{
	if ( pGopLength == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	*pGopLength = pstEncoder->gopLength;

	return RET_OK;
}

static int _DefaultGetFrameRate( H1ENCODE_API_T *pstEncoder, u32 *pFrameRate )
{
	if ( pFrameRate == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	*pFrameRate = pstEncoder->frameRateCode;

	return RET_OK;
}

static int _DefaultGetQPValue( H1ENCODE_API_T *pstEncoder, u32 *pQP )
{
	if ( pQP == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	*pQP = pstEncoder->qp;

	return RET_OK;
}

