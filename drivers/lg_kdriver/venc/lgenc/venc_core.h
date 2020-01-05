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
 *  core api for venc device.
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

#ifndef	_VENC_CORE_H_
#define	_VENC_CORE_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "venc_cfg.h"

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
typedef enum {
	VENC_EVENT_SCALER		= 1 << 0,
	VENC_EVENT_ES_WPTR		= 1 << 1,
#ifdef VENC_ENABLE_TS_OUT
	VENC_EVENT_TS_WPTR		= 1 << 2,
#endif /* VENC_ENABLE_TS_OUT */
} VENC_EVENT_T;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern OS_EVENT_T			gstEvent;
extern UINT32				gui32BufferIndex;
extern UINT32				gui32NumberOfFrames;
extern UINT32				gaFrameBytes[VENC_BIT_RATE_BUFFER];

extern UINT32				gui32ESWptr;
extern UINT32				gui32ESRptr;
extern UINT32				gui32AUIWptr;
extern UINT32				gui32AUIRptr;

#ifdef VENC_ENABLE_TS_OUT
extern UINT32				gui32TSWptr;
extern UINT32				gui32TSRptr;
#endif /* VENC_ENABLE_TS_OUT */

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/
void	VENC_DeviceInit( void );
void	VENC_DeviceFinal( void );
void	VENC_Initailize( void );
void	VENC_GetBufferInfo( LX_VENC_BUFFER_T *o_pstInfo );
SINT32	VENC_SetEncoderInput( LX_VENC_ENC_INPUT_T *i_pstParam );
SINT32	VENC_SetCommand( LX_VENC_ENC_COMMAND_T i_eCommand );
SINT32	VENC_SetPictureQuality( LX_VENC_ENC_QUALITY_T i_eQuality );
SINT32	VENC_SetTargetBitrate( UINT32 i_ui32TargetBitrate );
SINT32	VENC_GetEncodingInfomation( LX_VENC_ENC_INFO_T *o_pstInfo );
//SINT32	VENC_StartScaler( LX_VENC_SCL_START_T *i_pstParam );
//SINT32	VENC_GetScaledImage( LX_VENC_SCL_IMAGE_T *o_pstInfo );

SINT32	VENC_GetOutputBufferState( LX_VENC_ENC_OUTPUT_T *o_pstOutputParam );
SINT32	VENC_GetOutputTSBufferState( LX_VENC_ENC_TS_OUTPUT_T *o_pstOutputParam );
SINT32 	VENC_SetGOP( UINT8 i_ui8GopNValue );
SINT32 	VENC_SetQPValue( UINT8 i_ui8QPValue );
SINT32 	VENC_GetQPValue( UINT8* o_pui8QPValue );
SINT32 	VENC_SetForceBP( BOOLEAN enableForceBP );
SINT32	VENC_SetSTCEnable ( BOOLEAN enableSTC );
SINT32 	VENC_ResetSTC ( void );
SINT32	VENC_GetSTC( LX_VENC_ENC_STC_T *o_pstSTC );
SINT32	VENC_PREP_GetSTC( UINT32 *o_ui32STC );
SINT32	VENC_PREP_GetDEStatus( LX_VENC_DE_STATUS_T *o_pstDEStatus );
SINT32	VENC_GetInputFrameImage( LX_VENC_ENC_FRAME_IMAGE_T *o_pstFrameImage );

void	VENC_GetTsCounts( LX_VENC_ENC_TS_COUNT_T *o_pstParam );
SINT32 	VENC_GetPerformanceGauge( LX_VENC_ENC_PERPERMANCE_T *o_pstParam );

void 	VENC_RunSuspend( void );
void 	VENC_RunResume( void );

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VENC_CORE_H_ */

/** @} */

