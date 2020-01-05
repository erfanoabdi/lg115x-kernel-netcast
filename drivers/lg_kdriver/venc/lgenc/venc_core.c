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
 *  core api implementation for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.05.19
 *  note		Additional information.
 *
 *  @addtogroup lg1152_venc
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
#include "venc_reg_api.h"
#include "venc_drv.h"
#include "venc_core.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VENC_TIMEOUT			100
#define	VENC_DEFAULT_QP_LEVEL	17

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VENC_CHECK_CODE(__checker, __if_action, fmt, args...) \
			__CHECK_IF_ERROR(__checker, VENC_PRINT, __if_action, fmt, ##args)

//#define E_INTER_EN						0x0400		// IPC
#define E_INTER_EN						0x0C00		// IPC, VSYNC

#define ENABLE_IPC_INTERRUPT()			VENC_REG_SetExtInterruptEnable( E_INTER_EN );
#define DISABLE_IPC_INTERRUPT()			VENC_REG_SetExtInterruptDisable( E_INTER_EN );
#define CLEAR_IPC_INTERRUPT()			VENC_REG_ClearInterrupt( E_INTER_EN );

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
OS_EVENT_T			gstEvent;
UINT32				gui32ImageSize;
UINT32				gui32BufferIndex;
UINT32				gui32NumberOfFrames;
UINT32				gaFrameBytes[VENC_BIT_RATE_BUFFER];

// for ES Buffer
UINT32				gui32ESWptr;
UINT32				gui32ESRptr;

// for AUI Buffer
UINT32				gui32AUIWptr;
UINT32				gui32AUIRptr;

#ifdef VENC_ENABLE_TS_OUT
UINT32				gui32TSWptr;
UINT32				gui32TSRptr;
#endif /* VENC_ENABLE_TS_OUT */

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static SINT32	_VENC_LoadCodec( void );
#if 0
static UINT16	_VENC_GetStride( UINT16 i_ui16Width );
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void	VENC_DeviceInit( void )
{
	VENC_REG_Initialize();

	/* Configure SROM Start */
	VENC_REG_SetSROMStart( gpstVencMemConfig->uiSROMBase );

	/* Configure SRAM Start */
	VENC_REG_SetSRAMStart( gpstVencMemConfig->uiSRAMBase );

	/* Configure Frame buffer Start */
	VENC_REG_IPC_SetFrameBufferBase(gpstVencMemConfig->uiFrameBufBase );

	/* Configure DPB Start */
	VENC_REG_IPC_SetDPBBase(gpstVencMemConfig->uiDPBBase );

	/* Initialize the ES Base Address also */
	VENC_REG_IPC_SetVideoESBaseAddr( gpstVencMemConfig->uiESBufBase );
	VENC_REG_IPC_SetVideoESEndAddr( gpstVencMemConfig->uiESBufBase + gpstVencMemConfig->uiESBufSize );

	/* AUI Buffer base and size */
	VENC_REG_IPC_SetVideoAUIBaseAddr( gpstVencMemConfig->uiAUIBufBase );
	VENC_REG_IPC_SetVideoAUIEndAddr( gpstVencMemConfig->uiAUIBufBase + gpstVencMemConfig->uiAUIBufSize );

	/* Initialize the Scaler Base Address */
	VENC_REG_IPC_SetThumbnailBase( gpstVencMemConfig->uiScalerBase );

	/* Initialize the Audio ES Base Address also */
	VENC_REG_IPC_SetAudioESBaseAddr( gpstVencMemConfig->uiAESBufBase );
	VENC_REG_IPC_SetAudioESEndAddr( gpstVencMemConfig->uiAESBufBase + gpstVencMemConfig->uiAESBufSize );

#ifdef VENC_ENABLE_TS_OUT
	/* Video TS Buffer base and size */
	VENC_REG_IPC_SetVideoTSBaseAddr( gpstVencMemConfig->uiTSBufBase );
	VENC_REG_IPC_SetVideoTSEndAddr( gpstVencMemConfig->uiTSBufBase	+ gpstVencMemConfig->uiTSBufSize );
#endif /* VENC_ENABLE_TS_OUT */

	/* Audio AUI Buffer base and size */
	VENC_REG_IPC_SetAudioAUIBaseAddr( gpstVencMemConfig->uiAAUIBufBase );
	VENC_REG_IPC_SetAudioAUIEndAddr( gpstVencMemConfig->uiAAUIBufBase + gpstVencMemConfig->uiAAUIBufSize );

	/* Load Codec */
	_VENC_LoadCodec();

	/* Set Proc control value for starting the codec */
	VENC_REG_SetProcCtrl( 0, 0 );

	/* Event Init */
	OS_InitEvent( &gstEvent );

	/* Disable System encoding */
	// jaeseop.so 2011/10/27 - CPU system muxing 구현으로 h/w senc disable 함.
	VENC_REG_IPC_SetSENCModeEnable( FALSE );

	/* Set Default values for QP_Level and GOP)*/
	// jaeseop.so 2011/11/10
	// 	VENC_SetEncoderInput()에서 세팅하던 값을 초기화코드로 이동
	VENC_REG_IPC_SetConfig( TRUE, TRUE, FALSE, TRUE );
	VENC_REG_IPC_SetQPLevel( VENC_DEFAULT_QP_LEVEL );
	VENC_REG_IPC_SetGOP( 14, 1, 1 );	// Set default GOP value

	//VENC_PRINT("VENC Device Initialize success\n");
}

void 	VENC_DeviceFinal( void )
{
	VENC_REG_Finalize();
}

void	VENC_Initailize( void )
{
	//Reset the write index when initializing the registers, read index will be reset in mcu
	VENC_REG_IPC_SetWriteIndexOfInputBuffer( 0 );

	gui32ESRptr = gui32ESWptr = 0;
	gui32AUIRptr = gui32AUIWptr = 0;

#ifdef VENC_ENABLE_TS_OUT
	gui32TSRptr = gui32TSWptr = 0;
#endif /* VENC_ENABLE_TS_OUT */

	/* Enable the interrupt for IPC */
	ENABLE_IPC_INTERRUPT();

	VENC_PRINT("VENC Initialize success\n");
}

void	VENC_GetBufferInfo( LX_VENC_BUFFER_T *o_pstInfo )
{
	o_pstInfo->ui32PhysicalAddress = gpstVencMemConfig->uiScalerBase;
	o_pstInfo->ui32Size = gpstVencMemConfig->uiScalerSize;

	o_pstInfo->ui32ESBufPhysBase = gpstVencMemConfig->uiESBufBase;
	o_pstInfo->ui32ESBufSize = gpstVencMemConfig->uiESBufSize;
	o_pstInfo->ui32ESBufOffset = gpstVencMemConfig->uiESBufBase - gpstVencMemConfig->uiSRAMBase;

	o_pstInfo->ui32AUIBufPhysBase = gpstVencMemConfig->uiAUIBufBase;
	o_pstInfo->ui32AUIBufSize = gpstVencMemConfig->uiAUIBufSize;
	o_pstInfo->ui32AUIBufOffset = gpstVencMemConfig->uiAUIBufBase - gpstVencMemConfig->uiSRAMBase;

#ifdef VENC_ENABLE_TS_OUT
	o_pstInfo->ui32TSBufPhysBase = gpstVencMemConfig->uiTSBufBase;
	o_pstInfo->ui32TSBufSize 	= gpstVencMemConfig->uiTSBufSize;
	o_pstInfo->ui32TSBufOffset	= gpstVencMemConfig->uiTSBufBase - gpstVencMemConfig->uiSRAMBase;
#endif /* VENC_ENABLE_TS_OUT */

}

SINT32	VENC_SetEncoderInput( LX_VENC_ENC_INPUT_T *i_pstParam )
{
	SINT32 retVal = RET_OK;

	if ( ( (i_pstParam->eInputMode > LX_VENC_INPUT_MAX) )			||
		 ( (i_pstParam->eColorFormat > LX_VENC_COLOR_FORMAT_MAX) )	||
		 ( (i_pstParam->eSourceType > LX_VENC_SOURCE_TYPE_MAX) )	||
		 ( (i_pstParam->eYUYVMode > LX_VENC_YUYV_MODE_MAX) )		)
	{
		retVal = RET_INVALID_PARAMS;
		goto FUNC_EXIT;
	}

#if 0
	// 2011/08/23
	//	VENC_CONFIG0 = 0x1011000D, 2011.08.23이후 default 설정값
	// 2011/11/10
	//	VENC_CONFIG0(0x80c), VENC_MODE2_IN(0x814) 기본값 설정을 VENC_DeviceInit()으로 옮김
	// VENC_REG_IPC_SetConfig( TRUE, TRUE, FALSE, TRUE );
	// VENC_REG_IPC_SetQPLevel( VENC_DEFAULT_QP_LEVEL );
	// VENC_REG_IPC_SetGOP( 14, 1, 1 );	// Set default GOP value.
#endif

	VENC_REG_IPC_SetInputMode( i_pstParam->eInputMode );
	VENC_REG_IPC_SetMode( i_pstParam->eSourceType, i_pstParam->eColorFormat, i_pstParam->eYUYVMode );
	VENC_REG_IPC_SetPicResolution( i_pstParam->ui16Width, i_pstParam->ui16Height );
	VENC_REG_IPC_SetPictureOffset( i_pstParam->ui32PictureOffset );
	VENC_REG_IPC_SetOffset( i_pstParam->ui32HeaderSizeinPic, i_pstParam->ui16Stride );

	switch ( i_pstParam->eInputMode )
	{
		case LX_VENC_INPUT_DVI:
		{
			/* YUV input buffer base address and end address */
			VENC_REG_IPC_SetInputBufBaseAddr( gpstVencMemConfig->uiInBufBase );
			VENC_REG_IPC_SetInputBufEndAddr( gpstVencMemConfig->uiInBufBase + gpstVencMemConfig->uiInBufSize );
		}
		break;

		case LX_VENC_INPUT_CVD:
		case LX_VENC_INPUT_USB:
		case LX_VENC_INPUT_MJPEG:
		default:
		{
			VENC_REG_IPC_SetInputBufBaseAddr( (UINT32)i_pstParam->pInBuffBase );
			VENC_REG_IPC_SetInputBufEndAddr( (UINT32)i_pstParam->pInBuffBase + i_pstParam->ui32InpBuffSize );
		}
		break;
	}

FUNC_EXIT:
	return retVal;
}

SINT32	VENC_SetCommand( LX_VENC_ENC_COMMAND_T i_eCommand )
{
	SINT32 retVal = RET_OK;

	VENC_CHECK_CODE( ( (i_eCommand < LX_VENC_COMMAND_MIN) || (i_eCommand > LX_VENC_COMMAND_MAX) ),
					 { retVal = RET_INVALID_PARAMS; goto FUNC_EXIT; },
					 "Wrong command !!!\n" );

	if ( (i_eCommand == LX_VENC_COMMAND_REFRESH) || (i_eCommand == LX_VENC_COMMAND_START) )
	{
		VENC_REG_IPC_SetCommand( LX_VENC_COMMAND_PAUSE );
		DISABLE_IPC_INTERRUPT();
		CLEAR_IPC_INTERRUPT();

		gui32NumberOfFrames = 0;
		gui32BufferIndex = 0;

		// Flush buffer
		if (i_eCommand == LX_VENC_COMMAND_REFRESH)
		{
			gui32ESRptr = gui32ESWptr = gpstVencMemConfig->uiESBufBase;
			gui32AUIRptr = gui32AUIWptr = gpstVencMemConfig->uiAUIBufBase;

#ifdef VENC_ENABLE_TS_OUT
			gui32TSRptr = gui32TSWptr = gpstVencMemConfig->uiTSBufBase;
#endif /* VENC_ENABLE_TS_OUT */
		}
		else
		{
			gui32ESRptr = gui32ESWptr;
			gui32AUIRptr = gui32AUIWptr;

#ifdef VENC_ENABLE_TS_OUT
			gui32TSRptr = gui32TSWptr;
#endif /* VENC_ENABLE_TS_OUT */
		}

		ENABLE_IPC_INTERRUPT();
	}

	VENC_REG_IPC_SetCommand( i_eCommand );

FUNC_EXIT:
	return retVal;
}

SINT32	VENC_SetPictureQuality( LX_VENC_ENC_QUALITY_T i_eQuality )
{
	SINT32 retVal = RET_OK;

	UINT16 ui16TargetBitrate = 0;
	UINT16 ui16Threshold = 0;

	switch(i_eQuality)
	{
		case LX_VENC_QUALITY_LOW:
			ui16TargetBitrate = 20;
			break;
		case LX_VENC_QUALITY_MID_LOW:
			ui16TargetBitrate = 40;
			break;
		case LX_VENC_QUALITY_MIDDLE:
			ui16TargetBitrate = 60;
			break;
		case LX_VENC_QUALITY_MID_HIGH:
			ui16TargetBitrate = 80;
			break;
		case LX_VENC_QUALITY_HIGH:
		default:
			ui16TargetBitrate = 100;
			break;
	}

	ui16Threshold = ui16TargetBitrate / 10;	// 10% target bitrate

	VENC_REG_IPC_SetRateControl( TRUE, ui16Threshold, ui16TargetBitrate );

	return retVal;
}

SINT32	VENC_SetTargetBitrate( UINT32 i_ui32TargetBitrate )
{
	SINT32 retVal = RET_OK;

	UINT16	ui16TargetBitrate = 0;
	UINT16	ui16Threshold = 0;

	if ( i_ui32TargetBitrate > 0 )
	{
		ui16TargetBitrate = i_ui32TargetBitrate / 30;
		ui16Threshold = ui16TargetBitrate / 10;
	}

	VENC_REG_IPC_SetRateControl( TRUE, ui16Threshold, ui16TargetBitrate );

	return retVal;
}

SINT32	VENC_GetEncodingInfomation( LX_VENC_ENC_INFO_T *o_pstInfo )
{
	SINT32 retVal = RET_OK;
	LX_VENC_ENC_INFO_T stParam;
	UINT32 ui32FrameRate;
	UINT32 ui32NumberOfFrames, ui32NumberOfBytes;
	UINT32 ui32Index;
	UINT8 ui8QPLevel;
	UINT8 ui8GopN, ui8GopM, ui8GopIdr;
	UINT16 ui16Width, ui16Height;

	stParam.ui32FrameRate = VENC_REG_GetFrameRate();
	stParam.ui32BitRate = 0;
	
	switch ( stParam.ui32FrameRate )
	{
		case 	LX_VENC_FRAME_RATE_23HZ: { ui32FrameRate = 23; } break;
		case 	LX_VENC_FRAME_RATE_24HZ: { ui32FrameRate = 24; } break;
		case 	LX_VENC_FRAME_RATE_25HZ: { ui32FrameRate = 25; } break;
		case 	LX_VENC_FRAME_RATE_29HZ: { ui32FrameRate = 29; } break;
		case 	LX_VENC_FRAME_RATE_30HZ: { ui32FrameRate = 30; } break;
		case 	LX_VENC_FRAME_RATE_50HZ: { ui32FrameRate = 50; } break;
		case 	LX_VENC_FRAME_RATE_59HZ: { ui32FrameRate = 59; } break;
		case 	LX_VENC_FRAME_RATE_60HZ: { ui32FrameRate = 60; } break;
		case 	LX_VENC_FRAME_RATE_15HZ: { ui32FrameRate = 15; } break;
		default:
		{
#if 0
			retVal = RET_ERROR;
			VENC_PRINT("Frame rate Error !!!!\n");
			goto FUNC_EXIT;
#else
			// Encoding Infomation을 추가하면서 정상값이 아닌 경우에도 에러처리 하지 않도록 수정함.
			// QPLevel과 GOP 값은 레지스터 값을 그대로 읽어서 리턴.
			ui32FrameRate = 0;
#endif
		}
		break;
	}

	if ( gui32NumberOfFrames > 0 )
	{
		DISABLE_IPC_INTERRUPT();

		ui32NumberOfFrames = gui32NumberOfFrames;
		ui32NumberOfBytes = 0;
		for ( ui32Index = 0 ; ui32Index < VENC_BIT_RATE_BUFFER ; ++ui32Index )
		{
			ui32NumberOfBytes += gaFrameBytes[ui32Index];
		}

		ENABLE_IPC_INTERRUPT();
		VENC_CHECK_CODE( ui32NumberOfFrames == 0,
						 { retVal = RET_ERROR; goto FUNC_EXIT; },
						 "Encoding information Error !!!!\n" );

		stParam.ui32BitRate = (ui32NumberOfBytes * 8 / ui32NumberOfFrames) / ui32FrameRate;

		//VENC_PRINT("Number of Frames : %d, Number Of Bytes : %d\n", gui32NumberOfFrames, ui32NumberOfBytes );
	}

	// add qp_level
	VENC_REG_IPC_GetQPLevel( &ui8QPLevel );
	stParam.ui8QPLevel = ui8QPLevel;

	// add GOP Infomations
	VENC_REG_IPC_GetGOP( &ui8GopN, &ui8GopM, &ui8GopIdr);
	stParam.ui8GopN = ui8GopN;
	stParam.ui8GopM = ui8GopM;
	stParam.ui8GopIdr = ui8GopIdr;

#if 0
	// 2012/11/02
	// ioctl{LX_VENC_IOW_ENC_SET_INPUT}에서 설정되는 값이 초기화 되지 않은 값이고,
	// 그 값을 레지스터에서 읽어가는 구조로 되어 있기 때문에 정확한 resolution이 아님.
	// DE에서 설정해 주는 값으로 읽어야 함.

	VENC_REG_IPC_GetPicResolution( &ui16Width, &ui16Height );
	if ( ui16Width > 0 && ui16Height > 0 )
	{
		stParam.ui16Width = ui16Width;
		stParam.ui16Height = ui16Height;
	}
	else
#endif
	{
		VENC_REG_PREP_GetDESize( &ui16Width, &ui16Height );
		stParam.ui16Width = ui16Width;
		stParam.ui16Height = ui16Height;
	}

	memcpy( o_pstInfo, &stParam, sizeof(LX_VENC_ENC_INFO_T) );

FUNC_EXIT:
	return retVal;
}


LX_VENC_DE_STATUS_T gstDEStatus;
BOOLEAN	bGetInputFrame = FALSE;

SINT32	VENC_GetInputFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *o_pstFrameImage )
{
	UINT32 ui32RecvEvent;
	SINT32 retVal = RET_OK;

	bGetInputFrame = TRUE;

	retVal = OS_RecvEvent( &gstEvent, VENC_EVENT_SCALER, &ui32RecvEvent, OS_EVENT_RECEIVE_ANY, VENC_TIMEOUT*15);

	if ( retVal != RET_OK )
	{ 
		VENC_PRINT("Event timeout!!!\n");
		retVal = RET_ERROR;
		goto FUNC_EXIT;
	}

	bGetInputFrame = FALSE;

	if ( gstDEStatus.ui16Width > 0 && gstDEStatus.ui16Height > 0 && gstDEStatus.ui32YBase > 0 )
	{
		UINT32 size = gstDEStatus.ui16Height * gstDEStatus.ui16Stride;
		void *dest, *pY, *pC;

		dest = ioremap( gpstVencMemConfig->uiScalerBase, gpstVencMemConfig->uiScalerSize );

#if 0
		VENC_INFO("YBase: 0x%08x, CBase: 0x%08x, Size: %dx%d, Stride: %d\n",
			gstDEStatus.ui32YBase, gstDEStatus.ui32CBase,
			gstDEStatus.ui16Width, gstDEStatus.ui16Height, gstDEStatus.ui16Stride);
		VENC_INFO("Frame Type: %s\n", gstDEStatus.eFrameStruct == LX_VENC_ENC_FRAME_TYPE_PROGRESSIVE ? "P" : "I");
#endif

		if ( dest == (void *)-1 )
		{
			goto FUNC_EXIT;
		}

		pY = ioremap( gstDEStatus.ui32YBase, size );
		if ( pY == (void *)-1 )
		{
			iounmap( dest );
			goto FUNC_EXIT;
		}
		
		pC = ioremap( gstDEStatus.ui32CBase, size );
		if ( pC == (void *)-1 )
		{
			iounmap( dest );
			iounmap( pY );
			goto FUNC_EXIT;
		}


#if 0
		// 422 Semi-planar
		{
			int i;
			int height = gstDEStatus.ui16Height;
			int width = gstDEStatus.ui16Width;
			int stride = gstDEStatus.ui16Stride;

			UINT32 targetBase = (UINT32)dest;
			UINT32 sourceBase;

			sourceBase = (UINT32)pY;
			for ( i = 0; i < height; i++ )
			{
				memcpy( (void *)targetBase, (void *)sourceBase, width );

				targetBase += width;
				sourceBase += stride;
			}

			sourceBase = (UINT32)pC;
			for ( i = 0; i < height; i++ )
			{
				memcpy( (void *)targetBase, (void *)sourceBase, width );

				targetBase += width;
				sourceBase += stride;
			}

            o_pstFrameImage->type = LX_VENC_ENC_FRAME_IMAGE_TYPE_422_PACKED;//right???
			o_pstFrameImage->ui32Size = width * height * 2;
            o_pstFrameImage->ui32Height = height;
            o_pstFrameImage->ui32Width = width;
            o_pstFrameImage->ui32Stride = width;
		    o_pstFrameImage->ui32YPhyAdd = gpstVencMemConfig->uiScalerBase;
		}
#else
		// 422 Planar
		if ( gstDEStatus.eFrameStruct == LX_VENC_ENC_FRAME_TYPE_PROGRESSIVE )
		{
			int height = gstDEStatus.ui16Height;
			int width = gstDEStatus.ui16Width;
			int stride = gstDEStatus.ui16Stride;

			UINT32 targetBase = (UINT32)dest;
			UINT32 sourceBase;
			char *cb, *cr;
			int i, j;

			sourceBase = (UINT32)pY;
			for ( i = 0; i < height; i++ )
			{
				memcpy( (void *)targetBase, (void *)sourceBase, width );

				targetBase += width;
				sourceBase += stride;
			}

			sourceBase = (UINT32)pC;
			cb = (char *)(dest + (width * height));
			cr = (char *)((UINT32)cb + (width * height / 2));
			
			for ( i = 0; i < height; i++ )
			{
				UINT32 srcOffset = i * stride;
				UINT32 tarOffset = i * (width / 2);
				
				for ( j = 0; j < width / 2; j ++ )
				{
					cb[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
					cr[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
				}
			}

			o_pstFrameImage->type = LX_VENC_ENC_FRAME_IMAGE_TYPE_422_PLANAR;
			o_pstFrameImage->ui32Size = width * height * 2;
			o_pstFrameImage->ui32Height = height;
			o_pstFrameImage->ui32Width = width;
			o_pstFrameImage->ui32Stride = width;
			o_pstFrameImage->ui32YPhyAdd = gpstVencMemConfig->uiScalerBase;
			o_pstFrameImage->ui32UPhyAdd = o_pstFrameImage->ui32YPhyAdd + (width * height);
			o_pstFrameImage->ui32VPhyAdd = o_pstFrameImage->ui32UPhyAdd + ((width * height) >> 1);
		}
		else if (  gstDEStatus.eFrameStruct == LX_VENC_ENC_FRAME_TYPE_TOP ||
			 gstDEStatus.eFrameStruct == LX_VENC_ENC_FRAME_TYPE_BOTTOM )
		{
			int height = gstDEStatus.ui16Height;
			int width = gstDEStatus.ui16Width;
			int stride = gstDEStatus.ui16Stride;

			UINT32 targetBase = (UINT32)dest;
			UINT32 sourceBase;
			char *cb, *cr;
			int i, j;

			sourceBase = (UINT32)pY;
			for ( i = 0; i < height/2; i++ )
			{
				memcpy( (void *)targetBase, (void *)sourceBase, width );

				targetBase += width;
				//sourceBase += stride;
				
				memcpy( (void *)targetBase, (void *)sourceBase, width );

				targetBase += width;
				sourceBase += stride;
			}

			sourceBase = (UINT32)pC;
			cb = (char *)(dest + (width * height));
			cr = (char *)((UINT32)cb + (width * height / 2));
			
			for ( i = 0; i < height/2; i++ )
			{
				UINT32 srcOffset = i * stride;
				UINT32 tarOffset = (i*2+0) * (width / 2);
				
				for ( j = 0; j < width / 2; j ++ )
				{
					cb[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
					cr[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
				}

				srcOffset = i * stride;
				tarOffset = (i*2+1) * (width / 2);

				for ( j = 0; j < width / 2; j ++ )
				{
					cb[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
					cr[tarOffset + j] = *(char *)(sourceBase + srcOffset++);
				}
			}

			o_pstFrameImage->type = LX_VENC_ENC_FRAME_IMAGE_TYPE_422_PLANAR;
			o_pstFrameImage->ui32Size = width * height * 2;
			o_pstFrameImage->ui32Height = height;
			o_pstFrameImage->ui32Width = width;
			o_pstFrameImage->ui32Stride = width;
			o_pstFrameImage->ui32YPhyAdd = gpstVencMemConfig->uiScalerBase;
			o_pstFrameImage->ui32UPhyAdd = o_pstFrameImage->ui32YPhyAdd + (width * height);
			o_pstFrameImage->ui32VPhyAdd = o_pstFrameImage->ui32UPhyAdd + ((width * height) >> 1);
		}
#endif

		//o_pstInfo->ui32Size = size * 2;

		iounmap( dest );
		iounmap( pY );
		iounmap( pC );
	}

FUNC_EXIT:
	return retVal;

}

SINT32	VENC_GetOutputBufferState( LX_VENC_ENC_OUTPUT_T *o_pstOutputParam )
{
	SINT32 retVal = RET_OK;
	UINT32 ui32RecvEvent;

	retVal = OS_RecvEvent( &gstEvent, VENC_EVENT_ES_WPTR, &ui32RecvEvent, OS_EVENT_RECEIVE_ANY, VENC_TIMEOUT);
	VENC_CHECK_CODE( retVal != 0,
					 { retVal = RET_ERROR; goto FUNC_EXIT; },
					 "Event timeout!!!\n" );

	DISABLE_IPC_INTERRUPT();
	// ES Buffer WR/RD Pointer
	o_pstOutputParam->ui32OffsetStart = gui32ESRptr - gpstVencMemConfig->uiESBufBase;
	o_pstOutputParam->ui32OffsetEnd = gui32ESWptr - gpstVencMemConfig->uiESBufBase;
	gui32ESRptr = gui32ESWptr;

	// AUI Buffer WR/RD Pointer
	o_pstOutputParam->ui32AUIOffsetStart = gui32AUIRptr - gpstVencMemConfig->uiAUIBufBase;
	o_pstOutputParam->ui32AUIOffsetEnd = gui32AUIWptr - gpstVencMemConfig->uiAUIBufBase;
	gui32AUIRptr = gui32AUIWptr;
	ENABLE_IPC_INTERRUPT();

FUNC_EXIT:
	return retVal;
}


SINT32	VENC_GetOutputTSBufferState( LX_VENC_ENC_TS_OUTPUT_T *o_pstOutputParam )
{
	SINT32 retVal = RET_OK;
	UINT32 ui32RecvEvent;

	retVal = OS_RecvEvent( &gstEvent, VENC_EVENT_TS_WPTR, &ui32RecvEvent, OS_EVENT_RECEIVE_ANY, VENC_TIMEOUT);
	VENC_CHECK_CODE( retVal != 0,
					 { retVal = RET_ERROR; goto FUNC_EXIT; },
					 "Event timeout!!!\n" );

	DISABLE_IPC_INTERRUPT();

	// ES Buffer WR/RD Pointer
	o_pstOutputParam->ui32TSOffsetStart = gui32TSRptr - gpstVencMemConfig->uiTSBufBase;
	o_pstOutputParam->ui32TSOffsetEnd = gui32TSWptr - gpstVencMemConfig->uiTSBufBase;
	gui32TSRptr = gui32TSWptr;

#ifdef VENC_ENABLE_DEBUG
	o_pstOutputParam->ui32TSCount = VENC_REG_IPC_GetTSCount();
#endif

	ENABLE_IPC_INTERRUPT();

FUNC_EXIT:
	return retVal;
}

SINT32	VENC_SetSTCEnable ( BOOLEAN enableSTC )
{
	VENC_REG_SetSTCEnable( enableSTC );

	return RET_OK;
}

SINT32 	VENC_ResetSTC ( void )
{
	VENC_REG_ResetSTC( );

	return RET_OK;
}

SINT32	VENC_GetSTC( LX_VENC_ENC_STC_T *o_pstSTC )
{
	if ( o_pstSTC == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	o_pstSTC->ui32STCBase = VENC_REG_GetSTCBase();
	o_pstSTC->ui32STCExt = VENC_REG_GetSTCExt();

	return RET_OK;
}

SINT32	VENC_PREP_GetSTC( UINT32 *o_ui32STC )
{
	if ( o_ui32STC == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	*o_ui32STC = VENC_REG_PREP_GetSTC();

	return RET_OK;
}

SINT32	VENC_PREP_GetDEStatus( LX_VENC_DE_STATUS_T *o_pstDEStatus )
{
	UINT32 ret = RET_OK;
	UINT16 ui16Width = 0;
	UINT16 ui16Height = 0;
	UINT8  u8FrameStruct;
	
	if ( o_pstDEStatus == NULL )
	{
		return RET_INVALID_PARAMS;
	}

	ret = VENC_REG_PREP_GetDESize( &ui16Width, &ui16Height );

	if ( ret == RET_OK )
	{
		o_pstDEStatus->ui16Width = ui16Width;
		o_pstDEStatus->ui16Height = ui16Height;
	}

	o_pstDEStatus->ui32YBase = VENC_REG_PREP_GetDEYBase();
	o_pstDEStatus->ui32CBase = VENC_REG_PREP_GetDECBase();
	o_pstDEStatus->ui16Stride = VENC_REG_PREP_GetDEYStride();

	ret = VENC_REG_PREP_GetPictureInfo( NULL, &u8FrameStruct, NULL );
	
	if ( ret == RET_OK )
	{
		o_pstDEStatus->eFrameStruct = (LX_VENC_ENC_FRAME_TYPE_T)u8FrameStruct;
	}

#if 0
	VENC_PRINT("Y:0x%08x, C:0x%08x, %d, %d\n", 
		o_pstDEStatus->ui32YBase, o_pstDEStatus->ui32CBase, o_pstDEStatus->ui16Width, o_pstDEStatus->ui16Height);
#endif

	return ret;
}

SINT32 VENC_SetQPValue( UINT8 i_ui8QPValue )
{
	// Rate control and QP Level control are mutually exclusive.
	// So, if need to set QP Level, Rate control need to turn off.
	
	VENC_REG_IPC_SetRateControl( FALSE, 0, 0 );
	VENC_REG_IPC_SetQPLevel( i_ui8QPValue );

	return RET_OK;
}

SINT32 VENC_GetQPValue( UINT8* o_pui8QPValue )
{
	VENC_REG_IPC_GetQPLevel( o_pui8QPValue );

	return RET_OK;
}

SINT32 VENC_SetGOP( UINT8 i_ui8GopNValue )
{
	VENC_REG_IPC_SetGOP( i_ui8GopNValue, 1, 1 );	// GOP_M = 1, GOP_IDR = 1

	return RET_OK;
}

SINT32 VENC_SetForceBP( BOOLEAN enableForceBP )
{
	VENC_REG_IPC_SetForceBP( enableForceBP );

	return RET_OK;
}

void	VENC_GetTsCounts( LX_VENC_ENC_TS_COUNT_T *o_pstParam )
{
	if ( o_pstParam != NULL )
	{
	o_pstParam->ui32TSCount = VENC_REG_IPC_GetTSCount();
}
}

SINT32 	VENC_GetPerformanceGauge( LX_VENC_ENC_PERPERMANCE_T *o_pstParam )
{
	SINT32 ret;
	
	if ( o_pstParam != NULL )
	{
		UINT16 frameCount = 0;
		UINT16 encodingDuration = 0;
		UINT32 bitrate = 0;
		
		VENC_REG_IPC_GetPerformanceGauge(&frameCount, &encodingDuration, &bitrate);
			
		o_pstParam->ui16FrameCount = frameCount;
		o_pstParam->ui16Duration = encodingDuration;
		o_pstParam->ui32Bitrate = bitrate;

		ret = RET_OK;
	}
	else
	{
		ret = RET_INVALID_PARAMS;
	}

	return ret;
}

void 	VENC_RunSuspend( void )
{
	/* Store the registers */
	// VENC_StoreRegister();
}

void 	VENC_RunResume( void )
{
	/* Restore the registers */
	// VENC_RestoreRegister();

	/* halt codec for safer side */
	VENC_REG_SetProcCtrl( 1, 1 );

	/* Load codec */
	_VENC_LoadCodec();
	VENC_PRINT("[%s] Load codec success\n", VENC_MODULE);

	/* Set Proc control value for starting the codec */
	VENC_REG_SetProcCtrl( 0, 0 );
}

/*----------------------------------------------------------------------------------------
	Static Function Definition
----------------------------------------------------------------------------------------*/
static SINT32	_VENC_LoadCodec( void )
{
	void *pui8VirtAddr;
	void *pCodec;
	UINT32 ui32CodecSize;
	SINT32 retVal = RET_OK;

	ui32CodecSize = VENC_REG_GetCodecData( &pCodec );
	VENC_CHECK_CODE( ui32CodecSize == 0,
					   { retVal = RET_ERROR; goto FUNC_EXIT; },
					   "Codec data error!!!\n" );

	/* Sanity check */
	VENC_CHECK_CODE( ui32CodecSize > gpstVencMemConfig->uiSROMSize,
					   { retVal = RET_ERROR; goto FUNC_EXIT; },
					   "Codec size[%d] larger than all memory size[%d]!!!\n",
					   ui32CodecSize,
					   gpstVencMemConfig->uiSROMSize );

	/* Remap ROM base */
	pui8VirtAddr = (void *) ioremap( gpstVencMemConfig->uiSROMBase, gpstVencMemConfig->uiSROMSize );
	VENC_CHECK_CODE( pui8VirtAddr == NULL,
					   { retVal = RET_ERROR; goto FUNC_EXIT; },
					   "Codec base remap error!!!\n" );

	/* Write the codec to the predefined start address */
	memcpy( pui8VirtAddr, pCodec, ui32CodecSize );

	iounmap( pui8VirtAddr );
	
	VENC_DEBUG("Codec load success\n");

FUNC_EXIT:
	return retVal;
}

#if 0
static UINT16	_VENC_GetStride( UINT16 i_ui16Width )
{
	UINT16 ui16Stride;

	if ( i_ui16Width <= 128 )			{ ui16Stride = 128; }
	else if ( i_ui16Width <= 256 )		{ ui16Stride = 256; }
	else if ( i_ui16Width <= 512 )		{ ui16Stride = 512; }
	else if ( i_ui16Width <= 1024 )	{ ui16Stride = 1024; }
	else if ( i_ui16Width <= 2048 )	{ ui16Stride = 2048; }
	else								{ ui16Stride = 0; }

	return ui16Stride;
}
#endif

/** @} */

