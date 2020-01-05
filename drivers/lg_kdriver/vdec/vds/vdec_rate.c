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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     youngki.lyu@lge.com
 * version    1.0
 * date       2011.02.21
 * note       Additional information.
 *
 * @addtogroup lg115x_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "vdec_rate.h"
#include "vsync_drv.h"
#include "vdisp_drv.h"

#ifdef __XTENSA__
#include <stdio.h>
#include "stdarg.h"
#else
#include <linux/kernel.h>
#include <asm/string.h>	// memset
#endif

#include "../mcu/os_adap.h"

#include "../hal/ipc_reg_api.h"
#include "../hal/vdec_base.h"

#define LOG_NAME	vdec_rate
#include "log.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define	VDEC_RATE_NUM_OF_CHANNEL				VDISP_NUM_OF_CHANNEL
#define	VDEC_RATE_NUM_OF_DIFF_HISTORY_BUFF		0x200
#define	VDEC_RATE_MAX_DIFF_HISTORY_NUM			(0xFFFFFFFF / VDEC_RATE_NUM_OF_DIFF_HISTORY_BUFF)

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define	VDEC_DIFF(_a, _b)		(((_a) >= (_b)) ? (_a) - (_b) : (_b) - (_a))

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef enum
{
	RATE_SRC_NONE,
	RATE_SRC_CONF,
	RATE_SRC_CODEC,
	RATE_SRC_CODEC_DBL
} RATE_SRC_E;

typedef struct
{
	UINT32		ui32_Prev;
	UINT32		ui32Diff_History[VDEC_RATE_NUM_OF_DIFF_HISTORY_BUFF];
	UINT32		ui32Diff_History_Index;
	UINT32		ui32Diff_History_Sum;
	UINT32		ui32Diff_History_Count;
	UINT32		ui32FrameRateRes;
	UINT32		ui32FrameRateDiv;
} S_RATE_MOVING_AVERAGE_T;

typedef struct
{
	SINT32		i32Speed;		// 1x: 1000, 2x: 2000, ...
	BOOLEAN		bFieldPicture;
	BOOLEAN		bInterlaced;
	struct
	{
		UINT8	ui8CodecType;
		UINT32	ui32FrameRateRes_Org;
		UINT32	ui32FrameRateDiv_Org;
		UINT32	ui32FrameDuration90K_Org;
		UINT32	ui32FrameRateRes;
		UINT32	ui32FrameRateDiv;
		UINT32	ui32FrameDuration90K;
	} Config;
	struct
	{
		UINT8	ui8CodecType;
		UINT32	ui32FrameRateRes_Org;
		UINT32	ui32FrameRateDiv_Org;
		UINT32	ui32FrameDuration90K_Org;
		UINT32	ui32FrameRateRes;
		UINT32	ui32FrameRateDiv;
		UINT32	ui32FrameDuration90K;
	} Decoder;
	S_RATE_MOVING_AVERAGE_T DTS;
	S_RATE_MOVING_AVERAGE_T Feed;
	S_RATE_MOVING_AVERAGE_T DecDone;
	S_RATE_MOVING_AVERAGE_T DQ_Pop;
	S_RATE_MOVING_AVERAGE_T PTS;
	struct
	{
		UINT32	ui32FrameRateRes;
		UINT32	ui32FrameRateDiv;
		UINT32	ui32FrameDuration90K;	// frame duration @ 90KHz clock tick. valid only after sequence header found.
	} Status;
} S_VDEC_RATE_DB_T;


/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
static S_VDEC_RATE_DB_T gsVdecRate[VDEC_RATE_NUM_OF_CHANNEL];

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDEC_RATE_Init(void)
{
	log_noti("[RATE][DBG] Init Vdec Rate Drv, %s\n", __FUNCTION__ );
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static void _VDEC_RATE_Reset_MOVING_AVERAGE(S_RATE_MOVING_AVERAGE_T *pMovingAverage)
{
	pMovingAverage->ui32_Prev = 0;
	pMovingAverage->ui32Diff_History_Index = 0;
	pMovingAverage->ui32Diff_History_Sum = 0;
	pMovingAverage->ui32Diff_History_Count = 0xFFFFFFFF;
	pMovingAverage->ui32FrameRateRes = 0;
	pMovingAverage->ui32FrameRateDiv = 0xFFFFFFFF;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDEC_RATE_Reset(UINT8 ui8SyncCh)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return;
	}

	log_noti("[RATE%d][DBG] %s\n", ui8SyncCh, __FUNCTION__ );

	gsVdecRate[ui8SyncCh].i32Speed = 1000;
	gsVdecRate[ui8SyncCh].bFieldPicture = TRUE;
	gsVdecRate[ui8SyncCh].bInterlaced = TRUE;

	gsVdecRate[ui8SyncCh].Config.ui8CodecType = 0xFF;
	gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes_Org = 0x0;
	gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv_Org = 0xFFFFFFFF;
	gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K_Org = 0;
	gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes = 0x0;
	gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv = 0xFFFFFFFF;
	gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K = 0;

	gsVdecRate[ui8SyncCh].Decoder.ui8CodecType = 0xFF;
	gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes_Org = 0x0;
	gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv_Org = 0xFFFFFFFF;
	gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K_Org = 0;
	gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes = 0x0;
	gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv = 0xFFFFFFFF;
	gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K = 0;

	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DTS);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].Feed);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DecDone);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DQ_Pop);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].PTS);

	gsVdecRate[ui8SyncCh].Status.ui32FrameRateRes = VDEC_DEFAULT_FRAME_RATE_RES;
	gsVdecRate[ui8SyncCh].Status.ui32FrameRateDiv = VDEC_DEFAULT_FRAME_RATE_DIV;
	gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K = VSync_CalFrameDuration(VDEC_DEFAULT_FRAME_RATE_RES, VDEC_DEFAULT_FRAME_RATE_DIV);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDEC_RATE_Flush(UINT8 ui8SyncCh)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return;
	}

	log_noti("[RATE%d][DBG] %s\n", ui8SyncCh, __FUNCTION__ );

	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DTS);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].Feed);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DecDone);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DQ_Pop);
	_VDEC_RATE_Reset_MOVING_AVERAGE((S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].PTS);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
BOOLEAN VDEC_RATE_Set_Speed( UINT8 ui8SyncCh, SINT32 i32Speed )
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return FALSE;
	}

	log_noti("[RATE%d][DBG] Speed: %d --> %d\n", ui8SyncCh, gsVdecRate[ui8SyncCh].i32Speed, i32Speed);

	if( i32Speed == gsVdecRate[ui8SyncCh].i32Speed )
	{
		return FALSE;
	}

	gsVdecRate[ui8SyncCh].i32Speed = i32Speed;

	return TRUE;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
SINT32 VDEC_RATE_Get_Speed( UINT8 ui8SyncCh )
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	return gsVdecRate[ui8SyncCh].i32Speed;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static UINT32 _VDEC_RATE_GetAverageFrameDuration90K(UINT8 ui8SyncCh, BOOLEAN bConfig, BOOLEAN bDecoder, BOOLEAN bIO_Update, BOOLEAN bTimeStamp)
{
	UINT32		ui32FrameRate_Config = 0;
	UINT32		ui32FrameRate_Decoder = 0;
	UINT32		ui32FrameRate_DTS = 0;
	UINT32		ui32FrameRate_PTS = 0;
	UINT32		ui32FrameDuration90K_Average = 0;
	UINT32		ui32NumOfFrameDuration90K = 0;
	SINT32		i32Speed;

	i32Speed = gsVdecRate[ui8SyncCh].i32Speed;

	if( (bConfig == TRUE) && gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes && gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv )
		ui32FrameRate_Config = gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes / gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv;
	if( (bDecoder == TRUE) && gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes && gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv )
		ui32FrameRate_Decoder = gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes / gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv;

	if( (ui32FrameRate_Config >= VDEC_FRAMERATE_MIN) && (ui32FrameRate_Config <= VDEC_FRAMERATE_MAX) )
	{
		ui32FrameDuration90K_Average += VSync_CalFrameDuration(gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes, gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv);
		ui32NumOfFrameDuration90K++;
	}
	if( (ui32FrameRate_Decoder >= VDEC_FRAMERATE_MIN) && (ui32FrameRate_Decoder <= VDEC_FRAMERATE_MAX) )
	{
		ui32FrameDuration90K_Average += VSync_CalFrameDuration(gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes, gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv);
		ui32NumOfFrameDuration90K++;
	}

	if( bTimeStamp == TRUE && gsVdecRate[ui8SyncCh].PTS.ui32FrameRateRes
			&& gsVdecRate[ui8SyncCh].PTS.ui32FrameRateDiv )
	{
		ui32FrameRate_PTS = gsVdecRate[ui8SyncCh].PTS.ui32FrameRateRes /
			gsVdecRate[ui8SyncCh].PTS.ui32FrameRateDiv;
		ui32FrameRate_PTS = ui32FrameRate_PTS * i32Speed / 1000;
	}

	if( (ui32FrameRate_PTS >= VDEC_FRAMERATE_MIN) && (ui32FrameRate_PTS <= VDEC_FRAMERATE_MAX) )
	{
		ui32FrameDuration90K_Average += VSync_CalFrameDuration(
				gsVdecRate[ui8SyncCh].PTS.ui32FrameRateRes,
				gsVdecRate[ui8SyncCh].PTS.ui32FrameRateDiv);
		ui32NumOfFrameDuration90K++;
	}
	else if( bTimeStamp == TRUE && gsVdecRate[ui8SyncCh].DTS.ui32FrameRateRes
			&& gsVdecRate[ui8SyncCh].DTS.ui32FrameRateDiv )
	{
		ui32FrameRate_DTS = gsVdecRate[ui8SyncCh].DTS.ui32FrameRateRes /
			gsVdecRate[ui8SyncCh].DTS.ui32FrameRateDiv;
		ui32FrameRate_DTS = ui32FrameRate_DTS * i32Speed / 1000;
	}
	if( (ui32FrameRate_DTS >= VDEC_FRAMERATE_MIN) && (ui32FrameRate_DTS <= VDEC_FRAMERATE_MAX) )
	{
		ui32FrameDuration90K_Average += VSync_CalFrameDuration(
				gsVdecRate[ui8SyncCh].DTS.ui32FrameRateRes,
				gsVdecRate[ui8SyncCh].DTS.ui32FrameRateDiv);
		ui32NumOfFrameDuration90K++;
	}

	log_user2("PTS Intv %d/%d\n", gsVdecRate[ui8SyncCh].PTS.ui32FrameRateRes,
			gsVdecRate[ui8SyncCh].PTS.ui32FrameRateDiv);
	log_user2("DTS Intv %d/%d\n", gsVdecRate[ui8SyncCh].DTS.ui32FrameRateRes,
			gsVdecRate[ui8SyncCh].DTS.ui32FrameRateDiv);
	log_user2("AVG Intv %d/%d\n", ui32FrameDuration90K_Average, ui32NumOfFrameDuration90K );

	if( ui32NumOfFrameDuration90K )
	{
		ui32FrameDuration90K_Average /= ui32NumOfFrameDuration90K;
	}

	return ui32FrameDuration90K_Average;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/

// return : TRUE for config framerate
//			FALSE for decoder framerate
static RATE_SRC_E _VRATE_SelConfDecFrameRate(UINT8 ui8SyncCh)
{
	UINT32		u32FrmIntvAvg = 0xFFFFFFFF;	// Frame Interval Average
	UINT32		u32FrmIntvConf = 0;	// Frame Interval from Config
	UINT32		u32FrmIntvCodec = 0;// Frmae Interval from Codec
	RATE_SRC_E	eRateSrc = RATE_SRC_NONE, eIntvSmall, eIntvLarge;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return eRateSrc;
	}

	// Config: values from container(upper layer)
	// Decoder: values from vpu(BODA, etc.)
	if( (gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes) &&
			(gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv != 0xFFFFFFFF) )
		u32FrmIntvConf = gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K;
	if( (gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes) &&
			(gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv != 0xFFFFFFFF) )
		u32FrmIntvCodec = gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K;

	////////////////////////////////////////////////////////////////////
	// 		Decide More Close Frame Rate from AVG Frame Rate
	//		Between Config FR and Decoder FR
	////////////////////////////////////////////////////////////////////
	if( u32FrmIntvConf && u32FrmIntvCodec )
	{
		if( u32FrmIntvConf == u32FrmIntvCodec )
		{
			eRateSrc = RATE_SRC_CONF;
		}
		else
		{
			UINT32		u32FrmIntvLarge;
			UINT32		u32FrmIntvSmall;
			UINT32		u32FrmIntv30;
			UINT32		u32FrmIntv70;

			if( u32FrmIntvConf > u32FrmIntvCodec )
			{
				u32FrmIntvLarge = u32FrmIntvConf;
				u32FrmIntvSmall = u32FrmIntvCodec;
				eIntvSmall = RATE_SRC_CODEC;
				eIntvLarge = RATE_SRC_CONF;
			}
			else
			{
				u32FrmIntvLarge = u32FrmIntvCodec;
				u32FrmIntvSmall = u32FrmIntvConf;
				eIntvSmall = RATE_SRC_CONF;
				eIntvLarge = RATE_SRC_CODEC;
			}

			if( u32FrmIntvLarge > (u32FrmIntvSmall * 12/10) )
			{
				u32FrmIntv30 = u32FrmIntvSmall + (u32FrmIntvLarge - u32FrmIntvSmall) * 3/10;
				u32FrmIntv70 = u32FrmIntvSmall + (u32FrmIntvLarge - u32FrmIntvSmall) * 7/10;

				u32FrmIntvAvg = _VDEC_RATE_GetAverageFrameDuration90K( ui8SyncCh,
						FALSE, FALSE, FALSE, TRUE );

				if( (u32FrmIntvAvg > (u32FrmIntvSmall * 7/10)) &&
						(u32FrmIntvAvg < u32FrmIntv30) )
				{
					eRateSrc = eIntvSmall;
				}
				else if( (u32FrmIntvAvg < (u32FrmIntvLarge * 13/10)) &&
						(u32FrmIntvAvg > u32FrmIntv70) )
				{
					eRateSrc = eIntvLarge;
				}
				else
				{
					log_noti("[RATE%d] No valid rate src,\n", ui8SyncCh);
					log_noti("	Frame Interval AVG:%d  CONF:%d, CODEC:%d\n",
							u32FrmIntvAvg, u32FrmIntvConf, u32FrmIntvCodec);
				}
			}
			else
			{
				eRateSrc = eIntvSmall;
			}
		}
	}
	else if( u32FrmIntvConf )
	{
		eRateSrc = RATE_SRC_CONF;
	}
	else if( u32FrmIntvCodec )
	{
		u32FrmIntvAvg = _VDEC_RATE_GetAverageFrameDuration90K( ui8SyncCh,
				FALSE, FALSE, FALSE, TRUE );

		if( u32FrmIntvCodec > 6000-100 && u32FrmIntvCodec > u32FrmIntvAvg*9/5 )
		{
			static UINT32 u32DbgCnt;
			// wrong codec frame rate suspected
			if( !((u32DbgCnt++)%100) )
				log_noti("wrong frame rate suspected: frm interval codec %d  pts %d\n",
						u32FrmIntvCodec, u32FrmIntvAvg);

			eRateSrc = RATE_SRC_CODEC_DBL;
		}
		else
			eRateSrc = RATE_SRC_CODEC;
	}
	else
	{
		log_noti("[RATE%d] No Rate Info, CONFIG:%d, Decoder:%d\n",
			ui8SyncCh, u32FrmIntvConf, u32FrmIntvCodec);
	}

	log_debug("[RATE%d] Sel Source %d, Interval AVG %d  CONFIG:%d, Decoder:%d\n", ui8SyncCh,
			(UINT32)eRateSrc, u32FrmIntvAvg, u32FrmIntvConf, u32FrmIntvCodec);

	return eRateSrc;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static BOOLEAN _VDEC_RATE_CorrectDecoderFrameRateError(UINT8 ui8SyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	UINT32		ui32FrameRate = 0;
	SINT32		i32UpDown = 0;
	BOOLEAN		bCorrect = FALSE;

	UINT32		ui32FrameDuration90K_Decoder_Prev = 0;
	UINT32		ui32FrameDuration90K_Decoder_Curr = 0;
	UINT32		ui32FrameDuration90K_PTS;
	//	UINT32		ui32FrameDuration90K_DTS;
	UINT32		ui32FrameDuration90K_Decoder_Diff = 0;

	UINT32		ui32FrameRateRes;
	UINT32		ui32FrameRateDiv;

	UINT32		ui32FrameRate_PTS;
	UINT32		ui32FrameRate_DTS;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	ui32FrameRateRes = *pui32FrameRateRes;
	ui32FrameRateDiv = *pui32FrameRateDiv;
	ui32FrameRate = ui32FrameRateRes / ui32FrameRateDiv;

	ui32FrameDuration90K_Decoder_Prev = VSync_CalFrameDuration(gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes, gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv);
	ui32FrameDuration90K_Decoder_Curr = VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);
	ui32FrameDuration90K_Decoder_Diff = VDEC_DIFF(ui32FrameDuration90K_Decoder_Prev, ui32FrameDuration90K_Decoder_Curr);

	ui32FrameRate_PTS = VDEC_RATE_GetPTSRate( ui8SyncCh, NULL, NULL );
	ui32FrameRate_DTS = VDEC_RATE_GetDTSRate( ui8SyncCh, NULL, NULL );

	if( (ui32FrameRate < VDEC_FRAMERATE_MIN) || (ui32FrameRate > VDEC_FRAMERATE_MAX) )
	{
		log_debug("[RATE%d][Warning] FrameRateRes:%d, FrameRateDiv:%d, %s\n", ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__);

		while( (ui32FrameRate < VDEC_FRAMERATE_MIN) || (ui32FrameRate > VDEC_FRAMERATE_MAX) )
		{
			if( ui32FrameRate < VDEC_FRAMERATE_MIN )
			{
				ui32FrameRateRes *= 10;

				if( i32UpDown < 0 )
				{
					i32UpDown = 0;
					break;
				}
				i32UpDown++;
			}
			if( ui32FrameRate > VDEC_FRAMERATE_MAX )
			{
				ui32FrameRateDiv *= 10;

				if( i32UpDown > 0 )
				{
					i32UpDown = 0;
					break;
				}
				i32UpDown--;
			}

			ui32FrameRate = ui32FrameRateRes / ui32FrameRateDiv;
		}

		if( i32UpDown )
			log_debug("[RATE%d][Warn] Compensate FrameRateRes:%d, FrameRateDiv:%d, %s(%d)\n",
					ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__, __LINE__);

		bCorrect = (i32UpDown == 0) ? FALSE : TRUE;
	}
	else if( (ui32FrameDuration90K_Decoder_Diff >= 1) &&
			(ui32FrameDuration90K_Decoder_Diff <= 3) )
	{
		log_noti("[RATE%d][Warning] Compensate FrameRate:%d/%d --> %d/%d, %s(%d)\n",
				ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv,
				gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes,
				gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv,
				__FUNCTION__, __LINE__);

		ui32FrameRateRes = gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes;
		ui32FrameRateDiv = gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv;
		bCorrect = TRUE;
	}
	else if( (ui32FrameRate_PTS >= VDEC_FRAMERATE_MIN) &&
			(ui32FrameRate_PTS <= VDEC_FRAMERATE_MAX) )
	{
		ui32FrameDuration90K_PTS = VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);

		if( ((ui32FrameDuration90K_Decoder_Curr / 2) < (ui32FrameDuration90K_PTS * 11/10)) &&
				((ui32FrameDuration90K_Decoder_Curr / 2) >= (ui32FrameDuration90K_PTS * 9 / 10)) )
		{
			ui32FrameRateRes *= 2;
			bCorrect = TRUE;
			log_debug("[RATE%d][Warning] Compensate FrameRate P Res:%d, Div:%d, %s(%d)\n",
					ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__, __LINE__);
		}
	}

	if( bCorrect == TRUE )
	{
		*pui32FrameRateRes = ui32FrameRateRes;
		*pui32FrameRateDiv = ui32FrameRateDiv;
	}

	return bCorrect;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static BOOLEAN _VRATE_UpdateFrameRate(UINT8 ui8SyncCh)
{
	BOOLEAN		bUpdated = FALSE;
	RATE_SRC_E	eRateSrc;
	UINT32 ui32FrameRateRes, ui32FrameRateDiv, ui32FrameDuration90K;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return FALSE;
	}

	eRateSrc = _VRATE_SelConfDecFrameRate(ui8SyncCh);

	if( eRateSrc == RATE_SRC_CONF )
	{
		ui32FrameRateRes = gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes;
		ui32FrameRateDiv = gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv;
		ui32FrameDuration90K = gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K;
	}
	else if( eRateSrc == RATE_SRC_CODEC || eRateSrc == RATE_SRC_CODEC_DBL )
	{
		ui32FrameRateRes = gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes;
		ui32FrameRateDiv = gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv;
		ui32FrameDuration90K = gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K;

		if( eRateSrc == RATE_SRC_CODEC_DBL )
		{
			ui32FrameRateRes *= 2;
			ui32FrameDuration90K /= 2;
		}
	}
	else
	{
		ui32FrameRateRes = 0;
		ui32FrameRateDiv = 0;
	}

	if( ui32FrameRateRes && ui32FrameRateDiv )
	{
		if( (gsVdecRate[ui8SyncCh].Status.ui32FrameRateRes != ui32FrameRateRes) ||
			(gsVdecRate[ui8SyncCh].Status.ui32FrameRateDiv != ui32FrameRateDiv) )
		{
			UINT32		ui32FieldRate;
			UINT32		ui32FieldDuration90K;

			ui32FieldRate = (gsVdecRate[ui8SyncCh].bInterlaced == TRUE) ? 2 : 1;
			ui32FieldDuration90K = ui32FrameDuration90K / ui32FieldRate;

			if( ui32FieldDuration90K < 1500 ) // 60Hz
			{
				log_noti("[PTS%d][Err] Over Sync Capability - Field Duration: %d, %c\n",
						ui8SyncCh, ui32FieldDuration90K,
						(gsVdecRate[ui8SyncCh].bInterlaced == TRUE) ? 'i' : 'p');

				ui32FrameRateDiv *= 2;
				ui32FrameDuration90K *= 2;
			}

			if( VDEC_DIFF(ui32FrameDuration90K,
						gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K) > 0 )
			{
				log_noti("[RATE%d][DBG] FrameDuration90k: %d --> %d\n", ui8SyncCh,
						gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K,
						ui32FrameDuration90K);
			}

			gsVdecRate[ui8SyncCh].Status.ui32FrameRateRes = ui32FrameRateRes;
			gsVdecRate[ui8SyncCh].Status.ui32FrameRateDiv = ui32FrameRateDiv;

			if( gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K != ui32FrameDuration90K )
			{
				gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K = ui32FrameDuration90K;
				bUpdated = TRUE;
			}
		}
	}
	else
	{
		log_noti("[RATE%d][DBG] FrameRateRes: %d, FrameRateDiv: %d\n", ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv);
	}

	return bUpdated;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDEC_RATE_UpdateFrameRate_Config(UINT8 ui8SyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv)
{
	BOOLEAN		bUpdated = FALSE;
	UINT32		ui32FrameRate;
	UINT32		ui32FrameDuration90K = 0;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_noti("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return;
	}

	if( (ui32FrameRateRes != gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes_Org) ||
		(ui32FrameRateDiv != gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv_Org) )
	{
		log_noti("[RATE%d][DBG] Config FrameRate_Org: %d/%d --> %d/%d\n", ui8SyncCh,
				gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes_Org,
				gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv_Org,
				ui32FrameRateRes, ui32FrameRateDiv);

		gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes_Org = ui32FrameRateRes;
		gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv_Org = ui32FrameRateDiv;
		gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K_Org = VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);
	}

	if( (ui32FrameRateRes == 0) || (ui32FrameRateDiv == 0) )
	{
		//log_debug("[RATE%d][Err] ui32FrameRateRes:%d, ui32FrameRateDiv:%d, %s\n",
		//	ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__);
		return;
	}

	ui32FrameRate = ui32FrameRateRes / ui32FrameRateDiv;
	if( (ui32FrameRate < VDEC_FRAMERATE_MIN) || (ui32FrameRate > VDEC_FRAMERATE_MAX) )
	{
		log_debug("[RATE%d][Err] Over Range Config FrameRate: %d/%d, %s\n", ui8SyncCh,
				ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__);
		return;
	}

	// Frame Rate Error Correction
//	_VDEC_RATE_CorrectConfigFrameRateError(ui8SyncCh, &ui32FrameRateRes, &ui32FrameRateDiv);

	if( (ui32FrameRateRes != gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes) ||
		(ui32FrameRateDiv != gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv) )
	{
		log_noti("[RATE%d][DBG] Config FrameRate: %d/%d --> %d/%d\n", ui8SyncCh,
				gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes,
				gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv,
				ui32FrameRateRes, ui32FrameRateDiv);

		gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes = ui32FrameRateRes;
		gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv = ui32FrameRateDiv;
		ui32FrameDuration90K = VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);
		gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K = ui32FrameDuration90K;
		bUpdated = TRUE;
	}

	if( bUpdated )
		_VRATE_UpdateFrameRate(ui8SyncCh);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void VDEC_RATE_UpdateFrameRate_Decoder(UINT8 ui8SyncCh, UINT32 ui32FrameRateRes, UINT32 ui32FrameRateDiv, BOOLEAN bFieldPicture, BOOLEAN bInterlaced)
{
	BOOLEAN		bValidRate = TRUE;
	UINT32		ui32FrameDuration90K = 0;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return;
	}

	if( (ui32FrameRateRes != gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes_Org) ||
		(ui32FrameRateDiv != gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv_Org) )
	{
		log_noti("[RATE%d][DBG] Decoder FrameRate_Org: %d/%d --> %d/%d\n", ui8SyncCh,
				gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes_Org,
				gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv_Org,
				ui32FrameRateRes, ui32FrameRateDiv);

		gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes_Org = ui32FrameRateRes;
		gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv_Org = ui32FrameRateDiv;
		gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K_Org = VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);
	}

	if( (ui32FrameRateRes == 0) || (ui32FrameRateDiv == 0) )
	{
		bValidRate = FALSE;
//		log_debug("[RATE%d][Err] ui32FrameRateRes:%d, ui32FrameRateDiv:%d, %s\n", ui8SyncCh, ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__);
	}
	if( (ui32FrameRateRes > 0x3FFFFFFF) || (ui32FrameRateDiv > 0x3FFFFFFF) )
	{
		bValidRate = FALSE;
		log_error("[RATE%d][Err] Decoder FrameRate: %d/%d, %s\n", ui8SyncCh,
				ui32FrameRateRes, ui32FrameRateDiv, __FUNCTION__);
	}

	if( gsVdecRate[ui8SyncCh].bFieldPicture != bFieldPicture )
	{
		log_noti("[RATE%d][DBG] Field Picture: %d\n", ui8SyncCh, bFieldPicture );
		gsVdecRate[ui8SyncCh].bFieldPicture = bFieldPicture;
	}

	if( gsVdecRate[ui8SyncCh].bInterlaced != bInterlaced )
	{
		log_noti("[RATE%d][DBG] %s\n", ui8SyncCh, (bInterlaced == TRUE) ? "Interlaced" : "Progressive" );
		gsVdecRate[ui8SyncCh].bInterlaced = bInterlaced;
	}

	// Frame Rate Error Correction
	if( bValidRate )
	{
		_VDEC_RATE_CorrectDecoderFrameRateError(ui8SyncCh, &ui32FrameRateRes,
				&ui32FrameRateDiv);

		if( (ui32FrameRateRes != gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes) ||
				(ui32FrameRateDiv != gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv) )
		{
			log_noti("[RATE%d][DBG] Decoder FrameRate: %d/%d --> %d/%d\n", ui8SyncCh,
					gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes,
					gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv,
					ui32FrameRateRes, ui32FrameRateDiv);

			gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateRes = ui32FrameRateRes;
			gsVdecRate[ui8SyncCh].Decoder.ui32FrameRateDiv = ui32FrameRateDiv;
			ui32FrameDuration90K = VSync_CalFrameDuration(ui32FrameRateRes, ui32FrameRateDiv);
			gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K = ui32FrameDuration90K;
		}
	}

	// Frame rate could be changed even if codec rate is not changed
	//  , because AVG frame rate can be changed
	_VRATE_UpdateFrameRate(ui8SyncCh);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static UINT32 _VDEC_RATE_UpdateFrameRate_byXXX(UINT32 ui32STC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv, S_RATE_MOVING_AVERAGE_T *pMovingAverage)
{
	UINT32		ui32STCDiff = 0;
	UINT32		ui32STCDiff_Ratio = 0;

	ui32STC &= 0x0FFFFFFF;

	if( pMovingAverage->ui32Diff_History_Count == 0xFFFFFFFF )
	{
		pMovingAverage->ui32Diff_History_Count = 0;

		pMovingAverage->ui32_Prev = ui32STC;

		*pui32FrameRateRes = 0;
		*pui32FrameRateDiv = 1;
	}
	else
	{
		if( ui32STC >= pMovingAverage->ui32_Prev )
			ui32STCDiff = ui32STC - pMovingAverage->ui32_Prev;
		else
			ui32STCDiff = 0x0FFFFFFF - pMovingAverage->ui32_Prev + ui32STC;

		if( ui32STCDiff > VDEC_RATE_MAX_DIFF_HISTORY_NUM )
			ui32STCDiff = VDEC_RATE_MAX_DIFF_HISTORY_NUM;

		if( pMovingAverage->ui32Diff_History_Count >= VDEC_RATE_NUM_OF_DIFF_HISTORY_BUFF )
			pMovingAverage->ui32Diff_History_Sum -= pMovingAverage->ui32Diff_History[pMovingAverage->ui32Diff_History_Index];
		else
			pMovingAverage->ui32Diff_History_Count++;

		log_user2("History sum %d cnt %d, add %d\n", pMovingAverage->ui32Diff_History_Sum,
				pMovingAverage->ui32Diff_History_Count, ui32STCDiff);

		pMovingAverage->ui32Diff_History[pMovingAverage->ui32Diff_History_Index] = ui32STCDiff;
		pMovingAverage->ui32Diff_History_Index++;
		if( pMovingAverage->ui32Diff_History_Index >= VDEC_RATE_NUM_OF_DIFF_HISTORY_BUFF )
			pMovingAverage->ui32Diff_History_Index = 0;

		pMovingAverage->ui32Diff_History_Sum += ui32STCDiff;

		pMovingAverage->ui32_Prev = ui32STC;

		if( pMovingAverage->ui32Diff_History_Count >= 2 )
		{
			*pui32FrameRateRes = 90000 * pMovingAverage->ui32Diff_History_Count;
			*pui32FrameRateDiv = pMovingAverage->ui32Diff_History_Sum;

			if( *pui32FrameRateDiv == 0 )
			{ // All Same PTS
				*pui32FrameRateRes = 0;
				*pui32FrameRateDiv = 1;
			}

			pMovingAverage->ui32FrameRateRes = *pui32FrameRateRes;
			pMovingAverage->ui32FrameRateDiv = *pui32FrameRateDiv;
		}
		else
		{
			*pui32FrameRateRes = 0;
			*pui32FrameRateDiv = 1;
		}

		if( pMovingAverage->ui32Diff_History_Count >= VDEC_RATE_NUM_OF_DIFF_HISTORY_BUFF )
		{
			if( ui32STCDiff == 0 )
				ui32STCDiff = 1;
			ui32STCDiff_Ratio = pMovingAverage->ui32Diff_History_Sum / (pMovingAverage->ui32Diff_History_Count * ui32STCDiff);
		}
	}

//	log_error("[RATE][DBG] STC:0x%X, Diff:0x%X, Count:%u, Sum:%u, Res:0x%X, Div:0x%X\n", ui32STC, ui32STCDiff, pMovingAverage->ui32Diff_History_Count, pMovingAverage->ui32Diff_History_Sum, *pui32FrameRateRes, *pui32FrameRateDiv);

	return ui32STCDiff_Ratio;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_UpdateFrameRate_byDTS(UINT8 ui8SyncCh, UINT32 ui32DTS, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		//log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	return _VDEC_RATE_UpdateFrameRate_byXXX(ui32DTS, pui32FrameRateRes, pui32FrameRateDiv, (S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DTS);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_UpdateFrameRate_byFeed(UINT8 ui8SyncCh, UINT32 ui32GSTC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		//log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	return _VDEC_RATE_UpdateFrameRate_byXXX(ui32GSTC, pui32FrameRateRes, pui32FrameRateDiv, (S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].Feed);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_UpdateFrameRate_byDecDone(UINT8 ui8SyncCh, UINT32 ui32GSTC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	return _VDEC_RATE_UpdateFrameRate_byXXX(ui32GSTC, pui32FrameRateRes, pui32FrameRateDiv, (S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DecDone);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_UpdateFrameRate_byDqPop(UINT8 ui8SyncCh, UINT32 ui32GSTC, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	return _VDEC_RATE_UpdateFrameRate_byXXX(ui32GSTC, pui32FrameRateRes, pui32FrameRateDiv, (S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].DQ_Pop);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_UpdateFrameRate_byPTS(UINT8 ui8SyncCh, UINT32 ui32PTS, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	return _VDEC_RATE_UpdateFrameRate_byXXX(ui32PTS, pui32FrameRateRes, pui32FrameRateDiv, (S_RATE_MOVING_AVERAGE_T *)&gsVdecRate[ui8SyncCh].PTS);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_GetDTSRate(UINT8 ui8SyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	UINT32		ui32FrameRateRes;
	UINT32		ui32FrameRateDiv;
	SINT32		i32Speed;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	i32Speed = gsVdecRate[ui8SyncCh].i32Speed;

	if( i32Speed == 0 )
		return 0;

	ui32FrameRateRes = gsVdecRate[ui8SyncCh].DTS.ui32FrameRateRes;
	ui32FrameRateDiv = gsVdecRate[ui8SyncCh].DTS.ui32FrameRateDiv;

	if( i32Speed != 1000 )
	{
		ui32FrameRateRes /= 1000;
		ui32FrameRateDiv /= i32Speed;
	}

	if( pui32FrameRateRes != NULL && pui32FrameRateDiv != NULL )
	{
		*pui32FrameRateRes = ui32FrameRateRes;
		*pui32FrameRateDiv = ui32FrameRateDiv;
	}

	if( ui32FrameRateDiv == 0 )
		return 0;

	return ui32FrameRateRes / ui32FrameRateDiv;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_GetPTSRate(UINT8 ui8SyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	UINT32		ui32FrameRateRes;
	UINT32		ui32FrameRateDiv;
	SINT32		i32Speed;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	i32Speed = gsVdecRate[ui8SyncCh].i32Speed;

	if( i32Speed == 0 )
		return 0;

	ui32FrameRateRes = gsVdecRate[ui8SyncCh].PTS.ui32FrameRateRes;
	ui32FrameRateDiv = gsVdecRate[ui8SyncCh].PTS.ui32FrameRateDiv;

	if( i32Speed != 1000 )
	{
		ui32FrameRateRes /= 1000;
		ui32FrameRateDiv /= i32Speed;
	}

	if( pui32FrameRateRes != NULL && pui32FrameRateDiv != NULL )
	{
		*pui32FrameRateRes = ui32FrameRateRes;
		*pui32FrameRateDiv = ui32FrameRateDiv;
	}

	if( ui32FrameRateDiv == 0 )
		return 0;

	return ui32FrameRateRes / ui32FrameRateDiv;
}

#if 0
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static BOOLEAN VDEC_RATE_CategorizeFrameRateResDiv(UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	UINT32		ui32FrameDuration90K;

	ui32FrameDuration90K = VSync_CalFrameDuration( *pui32FrameRateRes, *pui32FrameRateDiv );
	if( ui32FrameDuration90K == 0 )
		return FALSE;

	if( (ui32FrameDuration90K >= 4390) && (ui32FrameDuration90K < 4615) ) // 20.5 >= frame rate(19.98) > 19.5
	{
		*pui32FrameRateRes = 90000;
		*pui32FrameRateDiv = 4504; // = 90090 / 20
	}
	else if( (ui32FrameDuration90K >= 3673) && (ui32FrameDuration90K < 3829) ) // 24.5 >= frame rate(23.97) > 23.5
	{
		*pui32FrameRateRes = 90000;
		*pui32FrameRateDiv = 3753; // = 90090 / 24
	}
	else if( (ui32FrameDuration90K >= 3529) && (ui32FrameDuration90K < 3673) ) // 25.5 >= frame rate(24.97) > 24.5
	{
		*pui32FrameRateRes = 90000;
		*pui32FrameRateDiv = 3603; // = 90090 / 25
	}
	else if( (ui32FrameDuration90K >= 2950) && (ui32FrameDuration90K < 3050) ) // 30.5 >= frame rate(29.97) > 29.5
	{
		*pui32FrameRateRes = 90000;
		*pui32FrameRateDiv = 3003; // = 90090 / 30
	}
	else if( (ui32FrameDuration90K >= 1487) && (ui32FrameDuration90K < 1512) ) // 60.5 >= frame rate(59.94) > 59.5
	{
		*pui32FrameRateRes = 90000;
		*pui32FrameRateDiv = 1501; // = 90090 / 60
	}
	else // default frame rate : 29.97
	{
		*pui32FrameRateRes = 90000;
		*pui32FrameRateDiv = 3003; // = 90090 / 30
	}

	return TRUE;
}
#endif

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_GetFrameRateDuration(UINT8 ui8SyncCh)
{
	UINT32		ui32FrameDuration90K = 0;

	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		//log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	if( gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K != 0 )
	{
		ui32FrameDuration90K = gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K;
	}

	return ui32FrameDuration90K;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
UINT32 VDEC_RATE_GetFrameRateResDiv(UINT8 ui8SyncCh, UINT32 *pui32FrameRateRes, UINT32 *pui32FrameRateDiv)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return 0;
	}

	if( (gsVdecRate[ui8SyncCh].Status.ui32FrameRateRes != 0) && (gsVdecRate[ui8SyncCh].Status.ui32FrameRateDiv != 0) )
	{
		*pui32FrameRateRes = gsVdecRate[ui8SyncCh].Status.ui32FrameRateRes;
		*pui32FrameRateDiv = gsVdecRate[ui8SyncCh].Status.ui32FrameRateDiv;
	}
#if 0
	else if( VDEC_RATE_GetPTSRate( ui8SyncCh, pui32FrameRateRes, pui32FrameRateDiv ) >= VDEC_FRAMERATE_MIN )
	{
		VDEC_RATE_CategorizeFrameRateResDiv(pui32FrameRateRes, pui32FrameRateDiv);
	}
	else if( VDEC_RATE_GetDTSRate( ui8SyncCh, pui32FrameRateRes, pui32FrameRateDiv ) >= VDEC_FRAMERATE_MIN )
	{
		VDEC_RATE_CategorizeFrameRateResDiv(pui32FrameRateRes, pui32FrameRateDiv);
	}
#endif
	else
	{
		*pui32FrameRateRes = 0;
		*pui32FrameRateDiv = 1;
	}

	if( *pui32FrameRateDiv == 0 )
		return 0;

	return *pui32FrameRateRes / *pui32FrameRateDiv;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
BOOLEAN VDEC_RATE_IsModifiedFrameRate(UINT8 ui8SyncCh)
{
	if( ui8SyncCh >= VDEC_RATE_NUM_OF_CHANNEL)
	{
		log_error("[RATE%d][Err] Channel Number, %s\n", ui8SyncCh, __FUNCTION__ );
		return FALSE;
	}

	if( (gsVdecRate[ui8SyncCh].Config.ui32FrameRateRes_Org == 0x0) &&
		(gsVdecRate[ui8SyncCh].Config.ui32FrameRateDiv_Org == 0xFFFFFFFF) )
	{
		if( gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K == gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K_Org )
		{
			return FALSE;
		}
	}
	else
	{
		if( (gsVdecRate[ui8SyncCh].Status.ui32FrameDuration90K == gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K_Org) &&
			(gsVdecRate[ui8SyncCh].Decoder.ui32FrameDuration90K_Org == gsVdecRate[ui8SyncCh].Config.ui32FrameDuration90K_Org))
		{
			return FALSE;
		}
	}

	return TRUE;
}

/** @} */
