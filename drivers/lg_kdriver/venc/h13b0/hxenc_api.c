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
 *  hxenc api implementation for venc device.
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

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define	HXENC_DEBUG

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "h1encode.h"

#include "ewl.h"
#include "memalloc.h"
#include "h264encapi.h"
#include "vp8encapi.h"
#include "hxenc_api.h"

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
int hx280enc_init( unsigned int base, unsigned int size );
void hx280enc_cleanup(void);

#if !defined(H1ENCODE_USE_POLLING)
u32 EWLReadIRQ( void );
void EWLWriteIRQ( u32 value );
i32 EWLWakeupIRQ( void );
#endif

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
#ifdef H1ENCODE_ENABLE_SEI_USERDATA
u8 sei_userdata[16] = { 0x20, 0x13, 0x01, 0x22, };	// for testing
#endif

/*========================================================================================
	Implementation Group
========================================================================================*/

int	HXENC_Init( u32 regBase, u32 regSize )
{
	return hx280enc_init( regBase, regSize );
}

void HXENC_Cleanup( void )
{
	hx280enc_cleanup();
}

int HXENC_MemallocInit( u32 startAddress, u32 endAddress )
{
	return MemallocInit( startAddress, endAddress );
}

u32 HXENC_ReadIRQ( void )
{
#if !defined(H1ENCODE_USE_POLLING)
	return EWLReadIRQ();
#else
	return 0;
#endif
}

void HXENC_WriteIRQ( u32 value )
{
#if !defined(H1ENCODE_USE_POLLING)
	EWLWriteIRQ(value);
#endif
}

i32 HXENC_WakeupIRQ( void )
{
#if !defined(H1ENCODE_USE_POLLING)
	return EWLWakeupIRQ();
#else
	return 0;
#endif
}

HXENC_RET_T	HXENC_H264Init( const HXENC_CONFIG_T *pstConfig, HXENC_H264INST_T * pInst )
{
	H264EncRet ret;
	H264EncConfig cfg = {0};

	cfg.frameRateDenom = pstConfig->frameRateDenom;
	cfg.frameRateNum = pstConfig->frameRateNum;
	cfg.width = pstConfig->width;
	cfg.height = pstConfig->height;
	cfg.streamType = H264ENC_BYTE_STREAM;
	cfg.scaledWidth = 0;
	cfg.scaledHeight = 0;	
	cfg.refFrameAmount = 1;
	
	if ( cfg.width >= 1920 && cfg.height >= 1080 )
	{
		// 1080p
		cfg.level = H264ENC_LEVEL_4;
	}
	else if ( cfg.width >= 1280 && cfg.height >= 720 )
	{
		// HD 720p
		cfg.level = H264ENC_LEVEL_3_1;
	}
	else
	{
		// VGA,PAL
		cfg.level = H264ENC_LEVEL_3;
	}
	
	if ( pstConfig->eFrameType == LX_VENC_FRAME_TYPE_PROGRESSIVE )
	{
		// Progressive Frame
		cfg.viewMode = H264ENC_BASE_VIEW_DOUBLE_BUFFER;
	}
	else
	{
		// Interlaced Frame
		cfg.viewMode = H264ENC_INTERLACED_FIELD;
	}

	HXENC_TRACE( "cfg = { .viewMode=%d .width = %d .height = %d } \n", 
		cfg.viewMode, cfg.width, cfg.height );

	ret = H264EncInit( &cfg, (H264EncInst *)pInst );

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_H264Release( HXENC_H264INST_T inst )
{
	H264EncRet ret;

	ret = H264EncRelease( (H264EncInst)inst );

	return (HXENC_RET_T)ret;
}

HXENC_RET_T	HXENC_H264SetRateCtrl( HXENC_H264INST_T inst, const HXENC_RATECTRL_T *pstRateCtrl )
{
	H264EncRet ret;
	H264EncRateCtrl rcCfg = {0};

	if ( inst == NULL || pstRateCtrl == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}
	
	if ( (ret = H264EncGetRateCtrl( (H264EncInst)inst, &rcCfg)) != H264ENC_OK )
	{
		HXENC_ERROR( "H264EncGetRateCtrl: %d\n", ret );

		return (HXENC_RET_T)ret;
	}

	if ( pstRateCtrl->bEnableTargetBitrate )
	{
		rcCfg.pictureRc = 1;
		rcCfg.mbRc = 1;
		rcCfg.hrd = 1;
		rcCfg.hrdCpbSize = pstRateCtrl->hrdCpbSize;

		rcCfg.bitPerSecond = pstRateCtrl->bitPerSecond - (pstRateCtrl->bitPerSecond/10);	// 90%

		rcCfg.qpHdr = -1;	// -1 lets RC calculate initial QP.
		
		// for Constant BitRate
		//rcCfg.qpMin = pstRateCtrl->qpMin;
		rcCfg.qpMin = 25;
		//rcCfg.fixedIntraQp = 0;
#ifdef H1ENCODE_ENABLE_SCD
		rcCfg.intraQpDelta = 0;
#else
		rcCfg.intraQpDelta = -1;
#endif

	}
	else if ( pstRateCtrl->bEnableFixedQP )
	{
		rcCfg.qpHdr = pstRateCtrl->qp;
		rcCfg.fixedIntraQp = pstRateCtrl->qp;
		rcCfg.pictureRc = 0;
		rcCfg.mbRc = 0;
		rcCfg.hrd = 0;

		// clear qp min/max
		rcCfg.qpMin = 0;
		rcCfg.qpMax = 0;
	}
	
	if ( pstRateCtrl->bEnableGOPLength )
	{
		rcCfg.gopLen = pstRateCtrl->gopLength;
	}

	ret = H264EncSetRateCtrl( (H264EncInst)inst, &rcCfg );

#ifdef HXENC_DEBUG
	if ( ret == H264ENC_OK )
	{
		HXENC_PRINT("H264EncRateCtrl = { .pictureRc = %d, .qpHdr = %d, .bitPerSecond = %d, .hrd = %d, .gopLen = %d }\n",
			rcCfg.pictureRc, rcCfg.qpHdr, rcCfg.bitPerSecond, rcCfg.hrd, rcCfg.gopLen );
	}
#endif

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_H264GetRateCtrl( HXENC_H264INST_T inst, HXENC_RATECTRL_T *pstRateCtrl )
{
	H264EncRet ret;
	H264EncRateCtrl rcCfg = {0};

	if ( inst == NULL || pstRateCtrl == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}

	if((ret = H264EncGetRateCtrl( (H264EncInst)inst, &rcCfg)) != H264ENC_OK)
	{
		return (HXENC_RET_T)ret;
	}

	pstRateCtrl->bitPerSecond = rcCfg.bitPerSecond;
	pstRateCtrl->qp = rcCfg.qpHdr;
	pstRateCtrl->gopLength = rcCfg.gopLen;

	return (HXENC_RET_T)ret; 
}

HXENC_RET_T HXENC_H264SetCodingCtrl( HXENC_H264INST_T inst, const HXENC_CODINGCTRL_T *pstCodingCtrl )
{
	H264EncRet ret;
	H264EncCodingCtrl codingCfg = {0};

	if ( inst == NULL || pstCodingCtrl == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}

	if ( (ret = H264EncGetCodingCtrl( (H264EncInst)inst, &codingCfg )) != H264ENC_OK )
	{
		return (HXENC_RET_T)ret;
	}

	codingCfg.fieldOrder = pstCodingCtrl->fieldOrder;
	codingCfg.enableCabac = 2; // 1 = CABAC - Main profile, 2 = CABAC/CAVLC frame based
	codingCfg.transform8x8Mode = 2; // 2=always 8x8
	codingCfg.quarterPixelMv = 2; // 2=enabled

	// Insert SAR infomation
	codingCfg.sampleAspectRatioWidth = pstCodingCtrl->sarWidth;
	codingCfg.sampleAspectRatioHeight = pstCodingCtrl->sarHeight;

	ret = H264EncSetCodingCtrl( (H264EncInst)inst, &codingCfg);

#ifdef HXENC_DEBUG
	if ( ret == H264ENC_OK )
	{
		HXENC_PRINT("H264EncCodingCtrl = { .sampleAspectRatioWidth = %d, .sampleAspectRatioHeight = %d, .enableCabac = %d, .fieldOrder = %d }\n",
			codingCfg.sampleAspectRatioWidth, codingCfg.sampleAspectRatioHeight, codingCfg.enableCabac, codingCfg.fieldOrder);
	}
#endif

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_H264SetPreProcessing( HXENC_H264INST_T inst, const HXENC_PREPROCESSING_CFG_T *pstPreProcCfg )
{
	H264EncRet ret;
	H264EncPreProcessingCfg preCfg = {0};

	if ( inst == NULL || pstPreProcCfg == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}

	if((ret = H264EncGetPreProcessing( (H264EncInst)inst, &preCfg)) != H264ENC_OK)
	{
		return (HXENC_RET_T) ret;
	}

	preCfg.inputType = H264ENC_YUV420_SEMIPLANAR;
	preCfg.origWidth = pstPreProcCfg->inputWidth;
	preCfg.origHeight = pstPreProcCfg->inputHeight;
	preCfg.interlacedFrame = 0;
	preCfg.videoStabilization = pstPreProcCfg->videoStabilization;

	ret = H264EncSetPreProcessing( (H264EncInst)inst, &preCfg );

#ifdef HXENC_DEBUG
	if ( ret == H264ENC_OK )
	{
		HXENC_PRINT("H264EncPreProcessingCfg = { .inputType = %d, .orgWidth = %d, .orgHeight = %d }\n",
			preCfg.inputType, preCfg.origWidth, preCfg.origHeight );
	}
#endif

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_H264StrmStart( HXENC_H264INST_T inst, const HXENC_INPUT_T *pstInput, HXENC_H264_OUTPUT_T *pstOutput )
{
	H264EncRet ret;
	H264EncIn encIn = {0};
	H264EncOut encOut = {0};

	if ( inst == NULL || pstInput == NULL || pstOutput == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}

	encIn.busLuma = pstInput->busLuma;
	encIn.busChromaU = pstInput->busChromaU;
	encIn.busChromaV = pstInput->busChromaV;
	encIn.timeIncrement = pstInput->timeIncrement;
	encIn.pOutBuf = pstInput->pOutBuf;
	encIn.busOutBuf = pstInput->busOutBuf;
	encIn.outBufSize = pstInput->outBufSize;
	encIn.codingType = (H264EncPictureCodingType)pstInput->codingType;

	ret = H264EncStrmStart( (H264EncInst)inst, &encIn, &encOut );

#ifdef H1ENCODE_ENABLE_SEI_USERDATA
	if ( H264EncSetSeiUserData( (H264EncInst)inst, sei_userdata, sizeof( sei_userdata ) ) != H264ENC_OK )
	{
		HXENC_ERROR("H264EncSetSeiUserData: Error\n");
	}
#endif

	pstOutput->streamSize = encOut.streamSize;

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_H264StrmEncode( HXENC_H264INST_T inst, const HXENC_INPUT_T *pstInput, HXENC_H264_OUTPUT_T *pstOutput )
{
	H264EncRet ret;
	H264EncIn encIn = {0};
	H264EncOut encOut = {0};

	if ( inst == NULL || pstInput == NULL || pstOutput == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}

	encIn.busLuma = pstInput->busLuma;
	encIn.busChromaU = pstInput->busChromaU;
	encIn.busChromaV = pstInput->busChromaV;
	encIn.timeIncrement = pstInput->timeIncrement;
	encIn.pOutBuf = pstInput->pOutBuf;
	encIn.busOutBuf = pstInput->busOutBuf;
	encIn.outBufSize = pstInput->outBufSize;
	encIn.codingType = (H264EncPictureCodingType)pstInput->codingType;

	encIn.ipf = H264ENC_REFERENCE_AND_REFRESH;
	encIn.ltrf = H264ENC_REFERENCE;
	encIn.busLumaStab = pstInput->busLumaStab;

#if 0
	HXENC_TRACE("encIn = { .busLuma = 0x%08x .busChromaU = 0x%08x .busChromaV = 0x%08x .pOutBuf = 0x%08x, .busOutBuf = 0x%08x }\n",
		encIn.busLuma, encIn.busChromaU, encIn.busChromaV, encIn.pOutBuf, encIn.busOutBuf );
#endif

	ret = H264EncStrmEncode( (H264EncInst)inst, &encIn, &encOut, NULL, NULL );

	pstOutput->streamSize = encOut.streamSize;
	pstOutput->codingType = (HXENC_PICTURE_CODING_TYPE_T)encOut.codingType;

	if ( (ret == H264ENC_OK || ret == H264ENC_FRAME_READY) && encOut.streamSize == 0 )
	{
		HXENC_ERROR("H264EncStrmEncode: picture skipped.\n");
	}
	else if ( ret != H264ENC_OK && ret != H264ENC_FRAME_READY)
	{
		HXENC_ERROR("H264EncStrmEncode: error %d.\n", ret);
	}
	
	return (HXENC_RET_T)ret;

}

HXENC_RET_T HXENC_VP8Init( const HXENC_CONFIG_T *pstConfig, HXENC_VP8INST_T *pInst )
{
	VP8EncRet ret;
	VP8EncConfig cfg = {0};

	if ( pstConfig == NULL || pInst == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}
	
	cfg.frameRateDenom = pstConfig->frameRateDenom;
	cfg.frameRateNum = pstConfig->frameRateNum;
	cfg.width = pstConfig->width;
	cfg.height = pstConfig->height;
	cfg.scaledWidth = 0;
	cfg.scaledHeight = 0;	
	cfg.refFrameAmount = 2;

	ret = VP8EncInit( &cfg, (VP8EncInst *)pInst );

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_VP8Release( HXENC_VP8INST_T inst )
{
	VP8EncRet ret;

	if ( inst == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}
	
	ret = VP8EncRelease( (VP8EncInst)inst );

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_VP8SetRateCtrl( HXENC_VP8INST_T inst, const HXENC_RATECTRL_T *pstRateCtrl )
{
	VP8EncRet ret;
	VP8EncRateCtrl rcCfg = {0};

	if ( inst == NULL || pstRateCtrl == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}
	
	if((ret = VP8EncGetRateCtrl( (VP8EncInst)inst, &rcCfg)) != VP8ENC_OK)
	{
		return (HXENC_RET_T)ret;
	}

	if ( pstRateCtrl->bEnableTargetBitrate )
	{
		rcCfg.pictureRc = 1;
		rcCfg.pictureSkip = 0;
		rcCfg.bitrateWindow = 20;
		rcCfg.bitPerSecond = pstRateCtrl->bitPerSecond;
		rcCfg.qpHdr = -1;
	}
	else if ( pstRateCtrl->bEnableFixedQP )
	{
		rcCfg.qpHdr = pstRateCtrl->qp;
		rcCfg.fixedIntraQp = pstRateCtrl->qp;
		rcCfg.pictureRc = 0;
	}

	ret = VP8EncSetRateCtrl( (VP8EncInst)inst, &rcCfg );

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_VP8SetCodingCtrl( HXENC_VP8INST_T inst, const HXENC_CODINGCTRL_T *pstCodingCtrl )
{
	VP8EncRet ret;
	VP8EncCodingCtrl codingCfg = {0};

	if ( inst == NULL || pstCodingCtrl == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}
	
	if((ret = VP8EncGetCodingCtrl( (VP8EncInst)inst, &codingCfg)) != VP8ENC_OK)
	{
		return (HXENC_RET_T)ret;
	}

	// Setting for default
	// ...

	ret = VP8EncSetCodingCtrl( (VP8EncInst)inst, &codingCfg);

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_VP8SetPreProcessing( HXENC_VP8INST_T inst, const HXENC_PREPROCESSING_CFG_T *pstPreProcCfg )
{
	VP8EncRet ret;
	VP8EncPreProcessingCfg preCfg = {0};

	if ( inst == NULL || pstPreProcCfg == NULL )
	{
		return HXENC_NULL_ARGUMENT;
	}
	
	if((ret = VP8EncGetPreProcessing( (VP8EncInst)inst, &preCfg)) != VP8ENC_OK)
	{
		return (HXENC_RET_T)ret;
	}

	preCfg.inputType = VP8ENC_YUV420_SEMIPLANAR;
	preCfg.origWidth = pstPreProcCfg->inputWidth;
	preCfg.origHeight = pstPreProcCfg->inputHeight;

	ret = VP8EncSetPreProcessing( (VP8EncInst)inst, &preCfg);

	return (HXENC_RET_T)ret;
}

HXENC_RET_T HXENC_VP8StrmEncode( HXENC_VP8INST_T inst, const HXENC_INPUT_T *pstInput, HXENC_VP8_OUTPUT_T *pstOutput )
{
	VP8EncRet ret;
	VP8EncIn encIn = {0};
	VP8EncOut encOut = {0};
	int i;

	if ( inst == NULL || pstInput == NULL || pstOutput == NULL )
	{
		return HXENC_ERROR;
	}

	encIn.busLuma = pstInput->busLuma;
	encIn.busChromaU = pstInput->busChromaU;
	encIn.busChromaV = pstInput->busChromaV;
	encIn.timeIncrement = pstInput->timeIncrement;
	encIn.pOutBuf = pstInput->pOutBuf;
	encIn.busOutBuf = pstInput->busOutBuf;
	encIn.outBufSize = pstInput->outBufSize;

	encIn.codingType = (VP8EncPictureCodingType)pstInput->codingType;

	encIn.ipf = VP8ENC_REFERENCE_AND_REFRESH;
	encIn.grf = VP8ENC_REFERENCE;
	encIn.arf = VP8ENC_REFERENCE;

	ret = VP8EncStrmEncode( (VP8EncInst)inst, &encIn, &encOut );

	pstOutput->frameSize = encOut.frameSize;

	for( i = 0; i < 9; i++ )
	{
		pstOutput->pOutBuf[i] = encOut.pOutBuf[i];
		pstOutput->streamSize[i] = encOut.streamSize[i];
	}

	return (HXENC_RET_T)ret;
}

/*----------------------------------------------------------------------------------------
	Static Function Definition
----------------------------------------------------------------------------------------*/

/** @} */

