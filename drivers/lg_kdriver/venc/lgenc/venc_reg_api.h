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
 *  register api for venc device.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  @author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2010.05.19
 *  note		Additional information.
 *
 *  @addtogroup lg1152_venc
 *	@{
 */

#ifndef	_VENC_REG_API_H_
#define	_VENC_REG_API_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	void	(*Initialize)(void);
	void	(*Finalize)(void);
	UINT32	(*GetCodecData)( void **o_pCodec );
	UINT32	(*GetFrameRate)( void );

	void	(*SetProcCtrl)( UINT8 i_ui8RunStall, UINT8 i_ui8VecSel );
	void	(*SetSROMStart)( UINT32 i_ui32SromStart );
	void	(*SetSRAMStart)( UINT32 i_ui32SramStart );
	void	(*SetExtInterruptEnable)( UINT32 i_ui32Interrupt );
	void	(*SetExtInterruptDisable)( UINT32 i_ui32Interrupt );
	UINT32	(*GetInterruptStatus)( void );
	void	(*ClearInterrupt)( UINT32 i_ui32IntrSrc );
	void	(*SetSTCEnable)( BOOLEAN i_bEnableSTC );
	void	(*ResetSTC)( void );
	UINT32	(*GetSTCBase)( void );
	UINT32	(*GetSTCExt)( void );

	UINT32	(*PREP_GetSTC)( void );

// 2012/06/14 (For Timemachine2.0 Thumbnail)
	UINT32	(*PREP_GetDESize)( UINT16 *o_pui16Width, UINT16 *o_pui16Height );
	UINT32 	(*PREP_GetDEYBase)( void );
	UINT32	(*PREP_GetDECBase)( void );
	UINT32 	(*PREP_GetDEYStride)( void );
	UINT32 	(*PREP_GetDECStride)( void );
	UINT32	(*PREP_GetPictureInfo)( BOOLEAN *o_bTopFieldFirst, UINT8 *o_pui8FrameStruct, UINT16 *o_pui16FramePtr );

	UINT32	(*IPC_GetVersion)( void );
	void	(*IPC_SetConfig)( BOOLEAN i_bMeLevel1Enable, BOOLEAN i_bEnablePskipOff, BOOLEAN i_bEnableMvnumRst, BOOLEAN i_bMeLevel2Enable  );
	void	(*IPC_SetQPLevel)( UINT8 i_ui8QPLevel );
	void	(*IPC_GetQPLevel)( UINT8* o_pui8QPLevel );
	void	(*IPC_SetInputMode)( UINT8 i_ui8InputMode );
	void	(*IPC_SetGOP)( UINT8 i_ui8GopN, UINT8 i_ui8GopM, UINT8 i_ui8GopIdr );
	void	(*IPC_GetGOP)( UINT8* o_pui8GopN, UINT8* o_pui8GopM, UINT8* o_pui8GopIdr );
	void	(*IPC_SetForceBP)( BOOLEAN i_bEnableForceBP );
	void	(*IPC_SetMode)( UINT8 i_ui8srcType, UINT8 i_ui8ColorFmt, UINT8 i_ui8YuvMode );
	void	(*IPC_SetFrameBufferBase)( UINT32 i_ui32Address );
	void	(*IPC_SetDPBBase)( UINT32 i_ui32Address );
	void	(*IPC_SetThumbnailBase)( UINT32 i_ui32Address );
	void	(*IPC_SetRateControl)( BOOLEAN i_bEnable, UINT16 i_ui16Threshold, UINT16 i_ui16TargetBitrate );
	void	(*IPC_GetRateControl)( BOOLEAN* o_pbEnable, UINT16* o_pui16Threshold, UINT16* o_pui16TargetBitrate );
	UINT32	(*IPC_GetInternalIPCState)( void );
	void	(*IPC_SetSENCModeEnable)( BOOLEAN i_bEnable );
	UINT32	(*IPC_GetTSCount)( void );
	UINT32	(*IPC_GetVTSCount)( void );
	UINT32	(*IPC_GetATSCount)( void );
	void	(*IPC_SetAudioESBaseAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetAudioESEndAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetAudioAUIBaseAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetAudioAUIEndAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetPicResolution)( UINT16 i_ui16Width, UINT16 i_ui16Height );
	void	(*IPC_GetPicResolution)( UINT16 *o_pui16Width, UINT16 *o_pui16Height );
	void	(*IPC_SetInputBufBaseAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetInputBufEndAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetWriteIndexOfInputBuffer)( UINT32 i_ui23Index );
	void	(*IPC_SetPictureOffset)( UINT32 i_ui32Offset );
	void	(*IPC_SetOffset)( UINT16 i_ui16HdrSize, UINT16 i_ui16Stride );
	void	(*IPC_StartThumbnail)( UINT16 i_ui16Stride, BOOLEAN i_bLockInactive, BOOLEAN i_bSeperatedChrome, BOOLEAN i_bProgressive, UINT8 i_ui8Path );
	void	(*IPC_ResetThumbnail)( void );
	void	(*IPC_SetThumbInputSize)( UINT16 i_ui16Width, UINT16 i_ui16Height );
	void	(*IPC_SetThumbOutputSize)( UINT16 i_ui16Width, UINT16 i_ui16Height );
	void	(*IPC_SetThumbInputBufBaseAddr)( UINT32 i_ui32Luminance, UINT32 i_ui32Chrominance );
	UINT32	(*IPC_GetThumbOutputBufBaseAddr)( void );
	void	(*IPC_SetVideoAUIBaseAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetVideoAUIEndAddr)( UINT32 i_ui32Address );
	UINT32	(*IPC_GetESWritePointer)( void );
	UINT32	(*IPC_GetESReadPointer)( void );
	UINT32	(*IPC_GetVideoAUIWritePointer)( void );
	UINT32	(*IPC_GetVideoAUIReadPointer)( void );
	void	(*IPC_SetCommand)( UINT8 i_ui8Command );
	void	(*IPC_SetVideoESBaseAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetVideoESEndAddr)( UINT32 i_ui32Address );
	UINT32	(*IPC_GetTSWritePointer)( void );
	UINT32	(*IPC_GetTSReadPointer)( void );
	void	(*IPC_SetVideoTSBaseAddr)( UINT32 i_ui32Address );
	void	(*IPC_SetVideoTSEndAddr)( UINT32 i_ui32Address );
	void 	(*IPC_GetPerformanceGauge)( UINT16 *o_pui32SliceCount, UINT16 *o_pui16EncodingDuration, UINT32 *o_pui32Bitrate );
	UINT32	(*IPC_GetSkipFrames)( void );
} VENC_REG_API_T;

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/
void	VENC_REG_Initialize( void );
void	VENC_REG_Finalize( void );
UINT32	VENC_REG_GetCodecData( void **o_pCodec );
UINT32	VENC_REG_GetFrameRate( void );

/******************************************************************************
 * Public functions/APIs
 ******************************************************************************/
void	VENC_REG_SetProcCtrl( UINT8 i_ui8RunStall, UINT8 i_ui8VecSel );
void	VENC_REG_SetSROMStart( UINT32 i_ui32SromStart );
void	VENC_REG_SetSRAMStart( UINT32 i_ui32SramStart );
void	VENC_REG_SetExtInterruptEnable( UINT32 i_ui32Interrupt );
void	VENC_REG_SetExtInterruptDisable( UINT32 i_ui32Interrupt );
UINT32	VENC_REG_GetInterruptStatus( void );
void	VENC_REG_ClearInterrupt( UINT32 i_ui32IntrSrc );
void	VENC_REG_SetSTCEnable ( BOOLEAN i_bEnableSTC );
void	VENC_REG_ResetSTC ( void );
UINT32	VENC_REG_GetSTCBase( void );
UINT32	VENC_REG_GetSTCExt( void );

UINT32	VENC_REG_PREP_GetSTC ( void );

// For Timemachine2.0 Thumbnail
UINT32	VENC_REG_PREP_GetDESize( UINT16 *o_pui16Width, UINT16 *o_pui16Height );
UINT32	VENC_REG_PREP_GetDEYBase( void );
UINT32	VENC_REG_PREP_GetDECBase( void );
UINT32	VENC_REG_PREP_GetDEYStride( void );
UINT32	VENC_REG_PREP_GetDECStride( void );
UINT32 	VENC_REG_PREP_GetPictureInfo( BOOLEAN *o_bTopFieldFirst, UINT8 *o_pui8FrameStruct, UINT16 *o_pui16FramePtr );

/******************************************************************************
 * Public functions for IPC Register Control
 ******************************************************************************/
UINT32	VENC_REG_IPC_GetVersion( void );
void	VENC_REG_IPC_SetConfig( BOOLEAN i_bMeLevel1Enable, BOOLEAN i_bEnablePskipOff, BOOLEAN i_bEnableMvnumRst, BOOLEAN i_bMeLevel2Enable  );
void	VENC_REG_IPC_SetQPLevel( UINT8 i_ui8QPLevel );
void	VENC_REG_IPC_GetQPLevel( UINT8* o_pui8QPLevel );
void	VENC_REG_IPC_SetInputMode( UINT8 i_ui8InputMode );
void	VENC_REG_IPC_SetMode( UINT8 i_ui8srcType, UINT8 i_ui8ColorFmt, UINT8 i_ui8YuvMode );
void 	VENC_REG_IPC_SetGOP( UINT8 i_ui8GopN, UINT8 i_ui8GopM, UINT8 i_ui8GopIdr );
void 	VENC_REG_IPC_GetGOP( UINT8* o_pui8GopN, UINT8* o_pui8GopM, UINT8* o_pui8GopIdr );
void	VENC_REG_IPC_SetForceBP( BOOLEAN i_bEnableForceBP );
void	VENC_REG_IPC_SetFrameBufferBase( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetDPBBase( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetThumbnailBase( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetRateControl( BOOLEAN i_bEnable, UINT16 i_ui16Threshold, UINT16 i_ui16TargetBitrate );
void	VENC_REG_IPC_GetRateControl( BOOLEAN* o_pbEnable, UINT16* o_pui16Threshold, UINT16* o_pui16TargetBitrate );
UINT32	VENC_REG_IPC_GetInternalIPCState( void );
void	VENC_REG_IPC_SetSENCModeEnable( BOOLEAN i_bEnable );
UINT32	VENC_REG_IPC_GetTSCount( void );
UINT32	VENC_REG_IPC_GetVTSCount( void );
UINT32	VENC_REG_IPC_GetATSCount( void );
void	VENC_REG_IPC_SetAudioESBaseAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetAudioESEndAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetAudioAUIBaseAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetAudioAUIEndAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetPicResolution( UINT16 i_ui16Width, UINT16 i_ui16Height );
void	VENC_REG_IPC_GetPicResolution( UINT16 *o_pui16Width, UINT16 *o_pui16Height );
void	VENC_REG_IPC_SetInputBufBaseAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetInputBufEndAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetWriteIndexOfInputBuffer( UINT32 i_ui23Index );
void	VENC_REG_IPC_SetPictureOffset( UINT32 i_ui32Offset );
void	VENC_REG_IPC_SetOffset( UINT16 i_ui16HdrSize, UINT16 i_ui16Stride );
void	VENC_REG_IPC_StartThumbnail( UINT16 i_ui16Stride, BOOLEAN i_bLockInactive, BOOLEAN i_bSeperatedChrome, BOOLEAN i_bProgressive, UINT8 i_ui8Path );
void	VENC_REG_IPC_ResetThumbnail( void );
void	VENC_REG_IPC_SetThumbInputSize( UINT16 i_ui16Width, UINT16 i_ui16Height );
void	VENC_REG_IPC_SetThumbOutputSize( UINT16 i_ui16Width, UINT16 i_ui16Height );
void	VENC_REG_IPC_SetThumbInputBufBaseAddr( UINT32 i_ui32Luminance, UINT32 i_ui32Chrominance );
UINT32	VENC_REG_IPC_GetThumbOutputBufBaseAddr( void );
void	VENC_REG_IPC_SetVideoAUIBaseAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetVideoAUIEndAddr( UINT32 i_ui32Address );
UINT32	VENC_REG_IPC_GetESWritePointer( void );
UINT32	VENC_REG_IPC_GetESReadPointer( void );
UINT32	VENC_REG_IPC_GetVideoAUIWritePointer( void );
UINT32	VENC_REG_IPC_GetVideoAUIReadPointer( void );
void	VENC_REG_IPC_SetCommand( UINT8 i_ui8Command );
void	VENC_REG_IPC_SetVideoESBaseAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetVideoESEndAddr( UINT32 i_ui32Address );
UINT32	VENC_REG_IPC_GetTSWritePointer( void );
UINT32	VENC_REG_IPC_GetTSReadPointer( void );
void	VENC_REG_IPC_SetVideoTSBaseAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_SetVideoTSEndAddr( UINT32 i_ui32Address );
void	VENC_REG_IPC_GetPerformanceGauge( UINT16 *o_pui32SliceCount, UINT16 *o_pui16EncodingDuration, UINT32 *o_pui32Bitrate );
UINT32 	VENC_REG_IPC_GetSkipFrames( void );
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VENC_REG_API_H_ */

/** @} */

