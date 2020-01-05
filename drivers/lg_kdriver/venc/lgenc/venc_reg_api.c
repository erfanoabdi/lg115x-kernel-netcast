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
 *  register api implementation for venc device.
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
#include "os_util.h"
#include "venc_reg_api.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VENC_RUN(__function, __param)	( _gpRegApi->__function != NULL )? \
												_gpRegApi->__function __param : 0

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern VENC_REG_API_T gpRegApiL9;
extern VENC_REG_API_T gpRegApiH13;


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
static VENC_REG_API_T *_gpRegApi;

/*========================================================================================
	Implementation Group
========================================================================================*/
void	VENC_REG_Initialize( void )
{
	if (lx_chip_rev( ) >= LX_CHIP_REV(H13,A0))
	{	
		_gpRegApi = &gpRegApiH13;
	}
	else //if (lx_chip_rev( ) >= LX_CHIP_REV(L9,A0) )
	{
		_gpRegApi = &gpRegApiL9;
	}
	
	VENC_RUN( Initialize, () );
}

void 	VENC_REG_Finalize( void )
{
	VENC_RUN( Finalize, () );
}

UINT32	VENC_REG_GetCodecData( void **o_pCodec )
{
	return VENC_RUN( GetCodecData, (o_pCodec) );
}

UINT32	VENC_REG_GetFrameRate( void )
{
	return VENC_RUN( GetFrameRate, () );
}

void	VENC_REG_SetProcCtrl( UINT8 i_ui8RunStall, UINT8 i_ui8VecSel )
{
	VENC_RUN( SetProcCtrl, (i_ui8RunStall, i_ui8VecSel) );
}

void	VENC_REG_SetSROMStart( UINT32 i_ui32SromStart )
{
	VENC_RUN( SetSROMStart, (i_ui32SromStart) );
}

void	VENC_REG_SetSRAMStart( UINT32 i_ui32SramStart )
{
	VENC_RUN( SetSRAMStart, (i_ui32SramStart) );
}

void	VENC_REG_SetExtInterruptEnable( UINT32 i_ui32Interrupt )
{
	VENC_RUN( SetExtInterruptEnable, (i_ui32Interrupt) );
}

void	VENC_REG_SetExtInterruptDisable( UINT32 i_ui32Interrupt )
{
	VENC_RUN( SetExtInterruptDisable, (i_ui32Interrupt) );
}

UINT32	VENC_REG_GetInterruptStatus( void )
{
	return VENC_RUN( GetInterruptStatus, () );
}

void	VENC_REG_ClearInterrupt( UINT32 i_ui32IntrSrc )
{
	VENC_RUN( ClearInterrupt, (i_ui32IntrSrc) );
}

void	VENC_REG_SetSTCEnable ( BOOLEAN i_bEnableSTC )
{
	VENC_RUN( SetSTCEnable, ( i_bEnableSTC ) );
}

void 	VENC_REG_ResetSTC ( void )
{
	VENC_RUN( ResetSTC, () );
}

UINT32	VENC_REG_GetSTCBase ( void )
{
	return VENC_RUN( GetSTCBase, () );
}

UINT32 	VENC_REG_GetSTCExt ( void )
{
	return VENC_RUN( GetSTCExt, () );
}

UINT32	VENC_REG_PREP_GetSTC ( void )
{
	return VENC_RUN( PREP_GetSTC, () );
}

UINT32	VENC_REG_PREP_GetDESize ( UINT16 *o_pui16Width, UINT16 *o_pui16Height )
{
	return VENC_RUN( PREP_GetDESize, (o_pui16Width, o_pui16Height) );
}

UINT32	VENC_REG_PREP_GetDEYBase ( void )
{
	return VENC_RUN( PREP_GetDEYBase, () );
}

UINT32	VENC_REG_PREP_GetDECBase ( void )
{
	return VENC_RUN( PREP_GetDECBase, () );
}

UINT32	VENC_REG_PREP_GetDEYStride ( void )
{
	return VENC_RUN( PREP_GetDEYStride, () );
}

UINT32	VENC_REG_PREP_GetDECStride ( void )
{
	return VENC_RUN( PREP_GetDECStride, () );
}

UINT32 	VENC_REG_PREP_GetPictureInfo( BOOLEAN *o_bTopFieldFirst, UINT8 *o_pui8FrameStruct, UINT16 *o_pui16FramePtr )
{
	return VENC_RUN( PREP_GetPictureInfo, (o_bTopFieldFirst, o_pui8FrameStruct, o_pui16FramePtr) );
}

UINT32	VENC_REG_IPC_GetVersion( void )
{
	return VENC_RUN( IPC_GetVersion, () );
}

void	VENC_REG_IPC_SetConfig( BOOLEAN i_bEnableMeLevel1, BOOLEAN i_bEnablePskipOff, BOOLEAN i_bEnableMvnumRst, BOOLEAN i_bEnableMeLevel2  )
{
	VENC_RUN( IPC_SetConfig, (i_bEnableMeLevel1, i_bEnablePskipOff, i_bEnableMvnumRst, i_bEnableMeLevel2) );
}

void	VENC_REG_IPC_SetQPLevel( UINT8 i_ui8QPLevel )
{
	VENC_RUN( IPC_SetQPLevel, (i_ui8QPLevel) );
}

void	VENC_REG_IPC_GetQPLevel( UINT8* o_pui8QPLevel )
{
	VENC_RUN( IPC_GetQPLevel, (o_pui8QPLevel) );
}

void	VENC_REG_IPC_SetInputMode( UINT8 i_ui8InputMode )
{
	VENC_RUN( IPC_SetInputMode, (i_ui8InputMode) );
}

void	VENC_REG_IPC_SetGOP( UINT8 i_ui8GopN, UINT8 i_ui8GopM, UINT8 i_ui8GopIdr )
{
	VENC_RUN( IPC_SetGOP, (i_ui8GopN, i_ui8GopM, i_ui8GopIdr) );
}

void	VENC_REG_IPC_GetGOP( UINT8* o_pui8GopN, UINT8* o_pui8GopM, UINT8* o_pui8GopIdr )
{
	VENC_RUN( IPC_GetGOP, (o_pui8GopN, o_pui8GopM, o_pui8GopIdr) );
}

void	VENC_REG_IPC_SetForceBP( BOOLEAN i_bEnableForceBP )
{
	VENC_RUN( IPC_SetForceBP, (i_bEnableForceBP) );
}

void	VENC_REG_IPC_SetMode( UINT8 i_ui8srcType, UINT8 i_ui8ColorFmt, UINT8 i_ui8YuvMode )
{
	VENC_RUN( IPC_SetMode, (i_ui8srcType, i_ui8ColorFmt, i_ui8YuvMode) );
}

void	VENC_REG_IPC_SetFrameBufferBase( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetFrameBufferBase, (i_ui32Address) );
}

void	VENC_REG_IPC_SetDPBBase( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetDPBBase, (i_ui32Address) );
}

void	VENC_REG_IPC_SetThumbnailBase( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetThumbnailBase, (i_ui32Address) );
}

void	VENC_REG_IPC_SetRateControl( BOOLEAN i_bEnable, UINT16 i_ui16Threshold, UINT16 i_ui16TargetBitrate )
{
	VENC_RUN( IPC_SetRateControl, (i_bEnable, i_ui16Threshold, i_ui16TargetBitrate) );
}

void	VENC_REG_IPC_GetRateControl( BOOLEAN* o_pbEnable, UINT16* o_pui16Threshold, UINT16* o_pui16TargetBitrate )
{
	VENC_RUN( IPC_GetRateControl, (o_pbEnable, o_pui16Threshold, o_pui16TargetBitrate) );
}

UINT32	VENC_REG_IPC_GetInternalIPCState( void )
{
	return VENC_RUN( IPC_GetInternalIPCState, () );
}

void	VENC_REG_IPC_SetSENCModeEnable( BOOLEAN i_bEnable )
{
	VENC_RUN( IPC_SetSENCModeEnable, (i_bEnable) );
}

UINT32	VENC_REG_IPC_GetTSCount( void )
{
	return VENC_RUN( IPC_GetTSCount, () );
}

UINT32	VENC_REG_IPC_GetVTSCount( void )
{
	return VENC_RUN( IPC_GetVTSCount, () );
}

UINT32	VENC_REG_IPC_GetATSCount( void )
{
	return VENC_RUN( IPC_GetATSCount, () );
}

void	VENC_REG_IPC_SetAudioESBaseAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetAudioESBaseAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetAudioESEndAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetAudioESEndAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetAudioAUIBaseAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetAudioAUIBaseAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetAudioAUIEndAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetAudioAUIEndAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetPicResolution( UINT16 i_ui16Width, UINT16 i_ui16Height )
{
	VENC_RUN( IPC_SetPicResolution, (i_ui16Width, i_ui16Height) );
}

void	VENC_REG_IPC_GetPicResolution( UINT16 *o_pui16Width, UINT16 *o_pui16Height )
{
	VENC_RUN( IPC_GetPicResolution, (o_pui16Width, o_pui16Height) );
}

void	VENC_REG_IPC_SetInputBufBaseAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetInputBufBaseAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetInputBufEndAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetInputBufEndAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetWriteIndexOfInputBuffer( UINT32 i_ui23Index )
{
	VENC_RUN( IPC_SetWriteIndexOfInputBuffer, (i_ui23Index) );
}

void	VENC_REG_IPC_SetPictureOffset( UINT32 i_ui32Offset )
{
	VENC_RUN( IPC_SetPictureOffset, (i_ui32Offset) );
}

void	VENC_REG_IPC_SetOffset( UINT16 i_ui16HdrSize, UINT16 i_ui16Stride )
{
	VENC_RUN( IPC_SetOffset, (i_ui16HdrSize, i_ui16Stride) );
}

void	VENC_REG_IPC_StartThumbnail( UINT16 i_ui16Stride, BOOLEAN i_bLockInactive, BOOLEAN i_bSeperatedChrome, BOOLEAN i_bProgressive, UINT8 i_ui8Path )
{
	VENC_RUN( IPC_StartThumbnail, (i_ui16Stride, i_bLockInactive, i_bSeperatedChrome, i_bProgressive, i_ui8Path) );
}

void	VENC_REG_IPC_ResetThumbnail( void )
{
	VENC_RUN( IPC_ResetThumbnail, () );
}

void	VENC_REG_IPC_SetThumbInputSize( UINT16 i_ui16Width, UINT16 i_ui16Height )
{
	VENC_RUN( IPC_SetThumbInputSize, (i_ui16Width, i_ui16Height) );
}

void	VENC_REG_IPC_SetThumbOutputSize( UINT16 i_ui16Width, UINT16 i_ui16Height )
{
	VENC_RUN( IPC_SetThumbOutputSize, (i_ui16Width, i_ui16Height) );
}

void	VENC_REG_IPC_SetThumbInputBufBaseAddr( UINT32 i_ui32Luminance, UINT32 i_ui32Chrominance )
{
	VENC_RUN( IPC_SetThumbInputBufBaseAddr, (i_ui32Luminance, i_ui32Chrominance) );
}

UINT32	VENC_REG_IPC_GetThumbOutputBufBaseAddr( void )
{
	return VENC_RUN( IPC_GetThumbOutputBufBaseAddr, () );
}

void	VENC_REG_IPC_SetVideoAUIBaseAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetVideoAUIBaseAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetVideoAUIEndAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetVideoAUIEndAddr, (i_ui32Address) );
}

UINT32	VENC_REG_IPC_GetESWritePointer( void )
{
	return VENC_RUN( IPC_GetESWritePointer, () );
}

UINT32	VENC_REG_IPC_GetESReadPointer( void )
{
	return VENC_RUN( IPC_GetESReadPointer, () );
}

UINT32	VENC_REG_IPC_GetVideoAUIWritePointer( void )
{
	return VENC_RUN( IPC_GetVideoAUIWritePointer, () );
}

UINT32	VENC_REG_IPC_GetVideoAUIReadPointer( void )
{
	return VENC_RUN( IPC_GetVideoAUIReadPointer, () );
}

void	VENC_REG_IPC_SetCommand( UINT8 i_ui8Command )
{
	VENC_RUN( IPC_SetCommand, (i_ui8Command) );
}

void	VENC_REG_IPC_SetVideoESBaseAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetVideoESBaseAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetVideoESEndAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetVideoESEndAddr, (i_ui32Address) );
}

UINT32	VENC_REG_IPC_GetTSWritePointer( void )
{
	return VENC_RUN( IPC_GetTSWritePointer, () );
}

UINT32	VENC_REG_IPC_GetTSReadPointer( void )
{
	return VENC_RUN( IPC_GetTSReadPointer, () );
}

void	VENC_REG_IPC_SetVideoTSBaseAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetVideoTSBaseAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_SetVideoTSEndAddr( UINT32 i_ui32Address )
{
	VENC_RUN( IPC_SetVideoTSEndAddr, (i_ui32Address) );
}

void	VENC_REG_IPC_GetPerformanceGauge( UINT16 *o_pui32SliceCount, UINT16 *o_pui16EncodingDuration, UINT32 *o_pui32Bitrate )
{
	VENC_RUN( IPC_GetPerformanceGauge, (o_pui32SliceCount, o_pui16EncodingDuration, o_pui32Bitrate) );
}

UINT32 	VENC_REG_IPC_GetSkipFrames( void )
{
	return VENC_RUN( IPC_GetSkipFrames, () );
}

/** @} */

