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
 *  PWM reg driver file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2012.06.30
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_def.h"
#include "be_kapi.h"
#include "pwm_reg_h13.h"

#include "../../reg/h13/be_frc_reg_h13.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PWM_DUTY_MAX_S		255

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	PWM_ORD_1ST_S  ,
	PWM_ORD_2ND_S  ,
	PWM_ORD_3RD_S  ,
	PWM_ORD_4TH_S  ,
	PWM_ORD_5TH_S  ,
	PWM_ORD_6TH_S  ,
	PWM_ORD_7TH_S  ,
	PWM_ORD_8TH_S  ,
	PWM_ORD_MAX_S
} PWM_ORD_S_T;

typedef enum {
	PWM_FREQ_60HZ_S  ,
	PWM_FREQ_120HZ_S ,
	PWM_FREQ_240HZ_S ,
	PWM_FREQ_480HZ_S ,
	PWM_FREQ_MAX_S
} PWM_FREQ_S_T;

typedef enum {
	PWM_FREE_OFF_S ,
	PWM_FREE_ON_S  ,
	PWM_FREE_MAX_S
} PWM_FREE_S_T;

typedef enum {
	PWM_RES_256_S   ,
	PWM_RES_512_S   ,
	PWM_RES_1024_S  ,
	PWM_RES_MAX_S
} PWM_RES_S_T;

typedef enum {
	PWM_MODE_DUTY_S	,
	PWM_MODE_WIDTH_S	,
	PWM_MODE_MAX_S
} PWM_MODE_S_T;

typedef enum {
	PWM_CTRL_ENB_S ,
	PWM_CTRL_FRQ_S ,
	PWM_CTRL_FRE_S ,
	PWM_CTRL_RES_S ,
	PWM_CTRL_INV_S ,
	PWM_CTRL_MOD_S ,
	PWM_CTRL_POS_S ,
	PWM_CTRL_LOW_S ,
	PWM_CTRL_HIG_S ,
	PWM_CTRL_WDH_S ,
	PWM_CTRL_MSK_S ,
	PWM_CTRL_MAX_S
} PWM_CTRL_TYPE_S_T;

typedef struct {
	BOOLEAN						enable;
	BE_PWM_ADAPT_FREQ_DB_T	freqDb;
} PWM_ADAPT_FREQ_CTRL_S_T;

typedef struct {
	// ctrl0 reg
	UINT32 pwm_en		;
	UINT32 pwm_freq_mode;
	UINT32 pwm_resolution;
	UINT32 pwm_inv		;
	UINT32 pwm_sel		;
	UINT32 pwm_width_falling_pos;
	// ctrl1 reg
	UINT32 pwm_free_width       ;
	// ctrl2 reg
	UINT32 pwm_intr_mask	;
	UINT32 pwm_method	;
	UINT32 pwm_mux	;
	UINT32 pwm_fc_h_disp;
	UINT32 pwm_fc_l_disp;
} PWM_CTRL_S_T;

typedef struct {
	UINT32 pwm_v_f;		// rising count
	UINT32 pwm_v_r;		// falling count
	UINT32 pwm_v_id;	// Duty range ID
	UINT32 pwm_v_we;	// load/write
} PWM_TIMING_S_T;

typedef struct {
	PWM_ADAPT_FREQ_CTRL_S_T adaptFreqCtrl;
	UINT32             unit;
	UINT32             ordr;
	UINT32             pxls;
	UINT32			   mask;
	UINT32			   wdth;
	PWM_CTRL_S_T   ctrl;
	PWM_TIMING_S_T t1st;
	PWM_TIMING_S_T t2nd;
	UINT32             duty;
	UINT32             offs;
	UINT32             freq;
} PWM_INFO_S_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern FRC_DVO_REG_H13_T gFRC_DVO_H13;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PWM_INFO_S_T gPwmInfo[BE_PWM_MAX];
static UINT32 vSyncFreq = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PWM_InitCtrl(void);
static int PWM_SetCtrl(UINT32 pwmId, PWM_CTRL_TYPE_S_T ctrId, UINT32 ctrVal);
static int PWM_SetTiming(UINT32 pwmId, PWM_ORD_S_T pwmOrd, UINT32 *pR1st, UINT32 *pFall, UINT32 *pR2nd);
static int PWM_GetTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall);
static int PWM_SetRegCtrl(UINT32 pwmId, BOOLEAN zeroDuty);
static int _REG_SetPwmCtrl(UINT32 pwmId, BOOLEAN zeroDuty);
static int _REG_SetPwmTiming(UINT32 pwmId);
static int _REG_GetPwmTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall);

/*========================================================================================
	Implementation Group
========================================================================================*/
int PWM_REG_H13_Init(void)
{
	int ret = RET_OK;
	BE_PWM_ID_T pwmId;
	static UINT8 init_flag = FALSE;

	do {
		if(init_flag) break;
		ret = PWM_InitCtrl();
		if (ret) break;
		pwmId = BE_PWM2;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_ENB_S, TRUE);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_FRQ_S, PWM_FREQ_120HZ_S);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_MOD_S, PWM_MODE_DUTY_S);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_FRE_S, PWM_FREE_ON_S);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_RES_S, PWM_RES_1024_S);
		if (ret) break;

		ret = PWM_SetCtrl(pwmId, PWM_CTRL_MSK_S, 0x00);	// mask intr
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_WDH_S, FALSE);	// duty mode
		if (ret) break;

		init_flag = TRUE;
	} while ( 0 );

	return ret;
}

int PWM_REG_H13_SetPwmControl(BE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		PWM_SetCtrl(pstParams->port, PWM_CTRL_ENB_S, pstParams->enable); // force to high

		if(!pstParams->enable) break;

		switch (pstParams->pwmOutput)
		{
			case BE_PWM_LOW :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_LOW_S, TRUE);
				break;
			case BE_PWM_NORMAL :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_LOW_S, FALSE);
				PWM_SetCtrl(pstParams->port, PWM_CTRL_HIG_S, FALSE);
				PWM_SetCtrl(pstParams->port, PWM_CTRL_INV_S, FALSE);
				break;
			case BE_PWM_HIGH :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_HIG_S, TRUE);
				break;
			case BE_PWM_INVERSION :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_INV_S, TRUE);
				break;
			default :
				BREAK_WRONG(pstParams->pwmOutput);
		}

		PWM_SetCtrl(pstParams->port, PWM_CTRL_FRE_S, (pstParams->pwmMode)?PWM_FREE_OFF_S:PWM_FREE_ON_S);
	} while(0);

	return ret;
}

int PWM_REG_H13_SetPwmAdaptFreqControl(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		gPwmInfo[pstParams->port].adaptFreqCtrl.freqDb = pstParams->freqDb;
		gPwmInfo[pstParams->port].adaptFreqCtrl.enable = pstParams->enable;

		if(vSyncFreq)
		{
			ret = PWM_REG_H13_SetPwmSync(vSyncFreq);
			if(ret) BREAK_WRONG(ret);
		}
	} while(0);

	return ret;
}

int PWM_REG_H13_SetPwmFrequency(BE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;
	BE_PWM_DUTY_T stParams;

	do {
		if(!pstParams) BREAK_WRONG(pstParams);
		if(!pstParams->frequency) BREAK_WRONG(pstParams->frequency);

		gPwmInfo[pstParams->port].unit = 1024;
		gPwmInfo[pstParams->port].freq = pstParams->frequency;

		if( gPwmInfo[pstParams->port].ctrl.pwm_method == PWM_FREE_OFF_S ) // locking mode
		{
			/*
			 * h      = hactive + hsync + h_bp + h_fp
			 * v      = vactive + vsync + v_bp + v_fp
			 * pixels = h * v
			 *
			 * result ->
			 * 60_h   = 1920    + 44    + 148  + 88   = 2200
			 * 60_v   = 1080    +  5    + 36   + 4    = 1125
			 *    h*v = 2475000
			 * 50_h   = 1920    + 44    + 148  + 88   = 2200
			 * 50_v   = 1080    +  5    + 36   + 229  = 1350
			 *    h*v = 2970000
			 * 48_h   = 1920    + 44    + 148  + 638  = 2750
			 * 48_v   = 1080    +  5    + 36   + 4    = 1125
			 *    h*v = 3093750
			 *
			 *    for UD (3820x2160 30p,25p,24p)
			 * 30_h   = 1920    + 44    + 88   + 72   = 2124
			 * 30_v   = 2160    + 148   + 10   + 8    = 2326
			 *    h*v = 4940424
			 * 25_h   = 1920    + 44    + 88   + 72   = 2124
			 * 25_v   = 2160    + 148   + 10   + 458  = 2776
			 *    h*v = 5896224
			 * 24_h   = 1920    + 44    + 638  + 72   = 2674
			 * 24_v   = 2160    + 148   + 10   + 8    = 2326
			 *    h*v = 6219724

			 */
			#define PWM_PIXELS_60HZ	2475000
			#define PWM_PIXELS_50HZ	2970000
			#define PWM_PIXELS_48HZ	3093750
			#define PWM_PIXELS_30HZ 	4940424
			#define PWM_PIXELS_25HZ 	5896224
			#define PWM_PIXELS_24HZ 	6219724

			pstParams->frequency = pstParams->frequency/2; //For temp
			switch ( pstParams->frequency )
			{
				case 384 :
				case 400 :
				case 480 :
					gPwmInfo[pstParams->port].ordr				  = PWM_ORD_8TH_S;
					gPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
					gPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 3;
					if( pstParams->frequency == 384) 		gPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 3;
					else if(pstParams->frequency == 400) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 3;
					else if(pstParams->frequency == 480) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 3;
					break;
				case 192 :
				case 200 :
				case 240 :
					gPwmInfo[pstParams->port].ordr				  = PWM_ORD_4TH_S;
					gPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
					gPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 2;
					if( pstParams->frequency == 192) 		gPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 2;
					else if(pstParams->frequency == 200) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 2;
					else if(pstParams->frequency == 240) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 2;
					break;
				case 96 :
				case 100 :
				case 120 :
					gPwmInfo[pstParams->port].ordr				  = PWM_ORD_2ND_S;
					gPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
					gPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 1;
					if( pstParams->frequency == 96) 		gPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 1;
					else if(pstParams->frequency == 100) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 1;
					else if(pstParams->frequency == 120) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 1;
					break;
				case 48 :
				case 50 :
				case 60 :
					gPwmInfo[pstParams->port].ordr				  = PWM_ORD_1ST_S;
					gPwmInfo[pstParams->port].ctrl.pwm_method	  = FALSE;
					gPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 0;
					if( pstParams->frequency == 48) 		gPwmInfo[pstParams->port].pxls = PWM_PIXELS_48HZ >> 0;
					else if(pstParams->frequency == 50) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_50HZ >> 0;
					else if(pstParams->frequency == 60) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_60HZ >> 0;
					break;
				case 24 :
				case 25 :
				case 30 :
					gPwmInfo[pstParams->port].ordr               = PWM_ORD_1ST_S;
					gPwmInfo[pstParams->port].ctrl.pwm_method    = TRUE;
					gPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 0;
					if( pstParams->frequency == 24) 		gPwmInfo[pstParams->port].pxls = PWM_PIXELS_24HZ >> 0;
					else if(pstParams->frequency == 25) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_25HZ >> 0;
					else if(pstParams->frequency == 30) 	gPwmInfo[pstParams->port].pxls = PWM_PIXELS_30HZ >> 0;
					break;
				case 180 :
				case 160 :
				default :
					gPwmInfo[pstParams->port].ordr				  = PWM_ORD_1ST_S;
					gPwmInfo[pstParams->port].pxls				  = 2475000 * 60 / pstParams->frequency; // For temp
					gPwmInfo[pstParams->port].ctrl.pwm_free_width= 2475000 * 60 / pstParams->frequency; // For temp
					gPwmInfo[pstParams->port].ctrl.pwm_method	  = TRUE;
					gPwmInfo[pstParams->port].ctrl.pwm_freq_mode = 0;
					break;
			}
		}
		else	// freeeun mode
		{
			gPwmInfo[pstParams->port].ordr				   = PWM_ORD_1ST_S;
			gPwmInfo[pstParams->port].pxls				   = 2475000 * 120 / pstParams->frequency; // For temp
			gPwmInfo[pstParams->port].ctrl.pwm_free_width = 2475000 * 120 / pstParams->frequency; // For temp
			gPwmInfo[pstParams->port].ctrl.pwm_method	   = TRUE;
			gPwmInfo[pstParams->port].ctrl.pwm_freq_mode  = 0;
		}

		stParams.port	= pstParams->port;
		stParams.offset = gPwmInfo[pstParams->port].offs;
		stParams.duty	= gPwmInfo[pstParams->port].duty;
		ret = PWM_REG_H13_SetPwmDutyCycle(&stParams);

		// Workaround for minimizing pwm_free_width transition effect on freerun mode
		if(gPwmInfo[pstParams->port].ctrl.pwm_en && gPwmInfo[pstParams->port].ctrl.pwm_method)
		{
			switch(pstParams->port)
			{
				case 0 :
					FRC_DVO_H13_RdFL(dvo_pwm0_ctrl0);
					FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_en, 0);
					FRC_DVO_H13_WrFL(dvo_pwm0_ctrl0);

					FRC_DVO_H13_RdFL(dvo_pwm0_ctrl0);
					FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_en, gPwmInfo[pstParams->port].ctrl.pwm_en);
					FRC_DVO_H13_WrFL(dvo_pwm0_ctrl0);
					break;

				case 1 :
					FRC_DVO_H13_RdFL(dvo_pwm1_ctrl0);
					FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_en, 0);
					FRC_DVO_H13_WrFL(dvo_pwm1_ctrl0);

					FRC_DVO_H13_RdFL(dvo_pwm1_ctrl0);
					FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_en, gPwmInfo[pstParams->port].ctrl.pwm_en);
					FRC_DVO_H13_WrFL(dvo_pwm1_ctrl0);
					break;

				case 2 :
					FRC_DVO_H13_RdFL(dvo_pwm2_ctrl0);
					FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_en, 0);
					FRC_DVO_H13_WrFL(dvo_pwm2_ctrl0);

					FRC_DVO_H13_RdFL(dvo_pwm2_ctrl0);
					FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_en, gPwmInfo[pstParams->port].ctrl.pwm_en);
					FRC_DVO_H13_WrFL(dvo_pwm2_ctrl0);
					break;

				default :
					break;
			}
		}

	} while(0);

	return ret;
}

int PWM_REG_H13_SetPwmDutyCycle(BE_PWM_DUTY_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	UINT32 ordr;
	UINT32 offs;
	UINT32 high;
	UINT32 falt;
	UINT32 unit_pixel;

	do {
		if(pstParams->duty > PWM_DUTY_MAX_S)
			break;
		gPwmInfo[pstParams->port].duty = pstParams->duty;
		gPwmInfo[pstParams->port].offs = pstParams->offset;

		unit_pixel = gPwmInfo[pstParams->port].pxls / gPwmInfo[pstParams->port].unit;
		ordr	   = gPwmInfo[pstParams->port].ordr;

		if((pstParams->offset + pstParams->duty) > PWM_DUTY_MAX_S)
			BREAK_WRONG(pstParams->offset);

		offs = (unit_pixel * pstParams->offset)/PWM_DUTY_MAX_S;
		high = (unit_pixel * pstParams->duty)/PWM_DUTY_MAX_S;
		falt = offs + high;

		for(i=PWM_ORD_1ST_S; i<ordr+1; i++)
		{
			BE_DEBUG("Port[%d] : ordr[%d] -  unit_pixel[%d] offs[%d] falt[%d] high[%d] \n", pstParams->port, i, unit_pixel, offs, falt, high);

			ret = PWM_SetTiming(pstParams->port, i, &offs, &falt, &offs);
			if(ret) break;
		}
		ret = PWM_SetRegCtrl(pstParams->port, offs == falt ? TRUE : FALSE); /* In case of zero duty, force to low PWM signal. */
	} while(0);

	return ret;
}

int PWM_REG_H13_GetPwmInfo(BE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;
	UINT32 freq_mode = 0;
	UINT32 time_low[4] = { 0 };
	UINT32 time_high[4] = { 0 };
	UINT32 i=0, iteration=0;
	UINT32 duty = 0, duty_sum = 0;
	static UINT16 prev_freq = 0;

	do {
		CHECK_NULL(pstParams);

		switch (pstParams->frequency)
		{
			case 48 :
			case 50 :
			case 60 :
				freq_mode = PWM_FREQ_60HZ_S;
				iteration = 1;
				break;
			case 96 :
			case 100 :
			case 120 :
				freq_mode = PWM_FREQ_120HZ_S;
				iteration = 2;
				break;
			case 192 :
			case 200 :
			case 240 :
				freq_mode = PWM_FREQ_240HZ_S;
				iteration = 4;
				break;
			default :
				freq_mode = PWM_FREQ_120HZ_S;
				iteration = 2;
				break;
		}

		if(prev_freq != pstParams->frequency)
		{
			 ret = PWM_SetCtrl(BE_PWM3, PWM_CTRL_FRQ_S, freq_mode);
			 if(ret) break;
			 ret = PWM_SetRegCtrl(BE_PWM3, FALSE);
			 if(ret) break;
		}
		prev_freq = pstParams->frequency;

		for(i=0;i<iteration;i++)
		{
			PWM_GetTiming(i, &time_low[i], &time_high[i]);
			if(time_low[i] == 0 && time_high[i] == 0)
			{
				BE_DEBUG("%s : low & high are zero  (ord %d)\n", __F__, i);
				pstParams->duty = 0;
				break;
			}
			duty = (time_high[i] * 1023) / (time_low[i] + time_high[i]);
			duty_sum += duty;
			BE_DEBUG("%d : high[%d] low[%d] -> duty[%d]\n", i, time_high[i], time_low[i], duty);
		}
		pstParams->duty = duty_sum/iteration;
		BE_DEBUG("avg duty[%d]\n", duty_sum/iteration);
	} while(0);

	return ret;
}

int PWM_REG_H13_SetPwmSync(UINT32 u32Frequency)
{
	int ret = RET_OK;
	BE_PWM_FREQ_T stParams;
	UINT32 i;

	do {
		if(!u32Frequency) BREAK_WRONG(u32Frequency);
		vSyncFreq = u32Frequency;

		for(i=0;i<BE_PWM_MAX;i++)
		{
			if(!gPwmInfo[i].adaptFreqCtrl.enable)
				continue;

			stParams.port		 = i;
			/* u32Frequency가 48/50/60의 공배수(ex.240Hz)가 올 수 없다는 전제가 필요함 */
			if(u32Frequency%48 == 0)
			{
				stParams.frequency = gPwmInfo[i].adaptFreqCtrl.freqDb.freq_48nHz;
			}
			else if(u32Frequency%50 == 0)
			{
				stParams.frequency = gPwmInfo[i].adaptFreqCtrl.freqDb.freq_50nHz;
			}
			else if(u32Frequency%60 == 0)
			{
				stParams.frequency = gPwmInfo[i].adaptFreqCtrl.freqDb.freq_60nHz;
			}
			else
			{
				stParams.frequency = u32Frequency;
			}

			if(gPwmInfo[i].ctrl.pwm_method == PWM_FREE_OFF_S)
			{
				PWM_SetCtrl(i, PWM_CTRL_FRE_S, PWM_FREE_ON_S);
				ret = PWM_REG_H13_SetPwmFrequency(&stParams);
				if(ret) break;

				PWM_SetCtrl(i, PWM_CTRL_FRE_S, PWM_FREE_OFF_S);
				ret = PWM_REG_H13_SetPwmFrequency(&stParams);
				if(ret) break;
			}
			else
			{
				ret = PWM_REG_H13_SetPwmFrequency(&stParams);
				if(ret) break;
			}
		}
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

static int PWM_InitCtrl(void)
{
	int ret = RET_OK;
	UINT32 pwmId;

	for (pwmId=0;pwmId<BE_PWM_MAX;pwmId++) {
		gPwmInfo[pwmId].ctrl.pwm_en				 = FALSE;
		gPwmInfo[pwmId].ctrl.pwm_freq_mode			 = PWM_FREQ_60HZ_S;
		gPwmInfo[pwmId].ctrl.pwm_resolution		 = PWM_RES_1024_S;
		gPwmInfo[pwmId].ctrl.pwm_inv				 = FALSE;
		gPwmInfo[pwmId].ctrl.pwm_sel				 = PWM_MODE_DUTY_S;
		gPwmInfo[pwmId].ctrl.pwm_width_falling_pos  = 0;
		gPwmInfo[pwmId].ctrl.pwm_method			 = PWM_FREE_OFF_S;
		gPwmInfo[pwmId].ctrl.pwm_fc_h_disp			 = FALSE;
		gPwmInfo[pwmId].ctrl.pwm_fc_l_disp			 = FALSE;
		gPwmInfo[pwmId].wdth						 = 0;
		gPwmInfo[pwmId].mask						 = 0xff;
		gPwmInfo[pwmId].unit						 = 2417;
		gPwmInfo[pwmId].duty					= 0;
		gPwmInfo[pwmId].freq					= 0;
		gPwmInfo[pwmId].adaptFreqCtrl.enable		= FALSE;
	}

	return ret;
}

static int PWM_SetCtrl(UINT32 pwmId, PWM_CTRL_TYPE_S_T ctrId, UINT32 ctrVal)
{
	int ret = RET_OK;

	switch (ctrId) {
		case PWM_CTRL_ENB_S :
			gPwmInfo[pwmId].ctrl.pwm_en				= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_FRQ_S :
			gPwmInfo[pwmId].ctrl.pwm_freq_mode			= ctrVal & 0x3;
			break;
		case PWM_CTRL_FRE_S :
			gPwmInfo[pwmId].ctrl.pwm_method			= ctrVal & 0x1;
			break;
		case PWM_CTRL_RES_S :
			gPwmInfo[pwmId].ctrl.pwm_resolution		= ctrVal & 0x3;
			break;
		case PWM_CTRL_INV_S :
			gPwmInfo[pwmId].ctrl.pwm_inv				= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_MOD_S :
			gPwmInfo[pwmId].ctrl.pwm_sel				= ctrVal;
			break;
		case PWM_CTRL_POS_S :
			gPwmInfo[pwmId].ctrl.pwm_width_falling_pos = ctrVal & 0x3FFFFF;
			break;
		case PWM_CTRL_LOW_S :
			gPwmInfo[pwmId].ctrl.pwm_fc_l_disp			= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_HIG_S :
			gPwmInfo[pwmId].ctrl.pwm_fc_h_disp			= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_WDH_S :
			gPwmInfo[pwmId].wdth						= ctrVal;
			break;
		case PWM_CTRL_MSK_S :
			gPwmInfo[pwmId].mask						= ctrVal;
			break;
		default :
			break;
	}

	return ret;
}

static int PWM_SetTiming(UINT32 pwmId, PWM_ORD_S_T pwmOrd, UINT32 *pR1st, UINT32 *pFall, UINT32 *pR2nd)
{
	PWM_TIMING_S_T t1st;
	PWM_TIMING_S_T t2nd;

	t1st = gPwmInfo[pwmId].t1st;
	t2nd = gPwmInfo[pwmId].t2nd;
	t1st.pwm_v_id = pwmOrd & 0x7;
	t2nd.pwm_v_id = pwmOrd & 0x7;
	t1st.pwm_v_we = TRUE;
	t2nd.pwm_v_we = TRUE;
	do {
		if (pR1st) t1st.pwm_v_r = *pR1st;
		if (pFall) t1st.pwm_v_f = *pFall;
		if (pR2nd) t2nd.pwm_v_r = *pR2nd;
		if (pR2nd) break;
		if (pR1st) t2nd.pwm_v_r = *pR1st;
	} while ( 0 );
	gPwmInfo[pwmId].t1st = t1st;
	gPwmInfo[pwmId].t2nd = t2nd;

	return _REG_SetPwmTiming(pwmId);
}

static int PWM_GetTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall)
{
	int ret = RET_OK;

	ret = _REG_GetPwmTiming(freq_mode, pRising, pFall);

	return ret;
}

static int PWM_SetRegCtrl(UINT32 pwmId, BOOLEAN zeroDuty)
{
	int ret = RET_OK;

	ret = _REG_SetPwmCtrl(pwmId, zeroDuty);

	return ret;
}

static int _REG_SetPwmCtrl(UINT32 pwmId, BOOLEAN zeroDuty)
{
	int ret = RET_OK;

	switch (pwmId) {
		case 0 :
			FRC_DVO_H13_RdFL(dvo_pwm0_ctrl0);
			FRC_DVO_H13_RdFL(dvo_pwm0_ctrl1);
			FRC_DVO_H13_RdFL(dvo_pwm0_ctrl2);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_en, gPwmInfo[pwmId].ctrl.pwm_en);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_resolution, gPwmInfo[pwmId].ctrl.pwm_resolution);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_inv, gPwmInfo[pwmId].ctrl.pwm_inv);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_sel, gPwmInfo[pwmId].ctrl.pwm_sel);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl0, pwm0_width_falling_pos, gPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl1, pwm0_free_width, gPwmInfo[pwmId].ctrl.pwm_free_width);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl2, pwm0_method, gPwmInfo[pwmId].ctrl.pwm_method);
			FRC_DVO_H13_Wr01(dvo_pwm0_ctrl2, pwm0_fc_h_disp, gPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			if(zeroDuty && (!gPwmInfo[pwmId].ctrl.pwm_fc_h_disp))
			{
				FRC_DVO_H13_Wr01(dvo_pwm0_ctrl2, pwm0_fc_l_disp, 1);
			}
			else
			{
				FRC_DVO_H13_Wr01(dvo_pwm0_ctrl2, pwm0_fc_l_disp, gPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			}
			FRC_DVO_H13_WrFL(dvo_pwm0_ctrl0);
			FRC_DVO_H13_WrFL(dvo_pwm0_ctrl1);
			FRC_DVO_H13_WrFL(dvo_pwm0_ctrl2);
			break;
		case 1 :
			FRC_DVO_H13_RdFL(dvo_pwm1_ctrl0);
			FRC_DVO_H13_RdFL(dvo_pwm1_ctrl1);
			FRC_DVO_H13_RdFL(dvo_pwm1_ctrl2);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_en, gPwmInfo[pwmId].ctrl.pwm_en);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_resolution, gPwmInfo[pwmId].ctrl.pwm_resolution);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_inv, gPwmInfo[pwmId].ctrl.pwm_inv);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_sel, gPwmInfo[pwmId].ctrl.pwm_sel);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl0, pwm1_width_falling_pos, gPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl1, pwm1_free_width, gPwmInfo[pwmId].ctrl.pwm_free_width);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl2, pwm1_method, gPwmInfo[pwmId].ctrl.pwm_method);
			FRC_DVO_H13_Wr01(dvo_pwm1_ctrl2, pwm1_fc_h_disp, gPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			if(zeroDuty && (!gPwmInfo[pwmId].ctrl.pwm_fc_h_disp))
			{
				FRC_DVO_H13_Wr01(dvo_pwm1_ctrl2, pwm1_fc_l_disp, 1);
			}
			else
			{
				FRC_DVO_H13_Wr01(dvo_pwm1_ctrl2, pwm1_fc_l_disp, gPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			}
			FRC_DVO_H13_WrFL(dvo_pwm1_ctrl0);
			FRC_DVO_H13_WrFL(dvo_pwm1_ctrl1);
			FRC_DVO_H13_WrFL(dvo_pwm1_ctrl2);
			break;
		case 2 :
			FRC_DVO_H13_RdFL(dvo_pwm2_ctrl0);
			FRC_DVO_H13_RdFL(dvo_pwm2_ctrl1);
			FRC_DVO_H13_RdFL(dvo_pwm2_ctrl2);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_en, gPwmInfo[pwmId].ctrl.pwm_en);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_resolution, gPwmInfo[pwmId].ctrl.pwm_resolution);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_inv, gPwmInfo[pwmId].ctrl.pwm_inv);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_sel, gPwmInfo[pwmId].ctrl.pwm_sel);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl0, pwm2_width_falling_pos, gPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl1, pwm2_free_width, gPwmInfo[pwmId].ctrl.pwm_free_width);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl2, pwm2_method, gPwmInfo[pwmId].ctrl.pwm_method);
			FRC_DVO_H13_Wr01(dvo_pwm2_ctrl2, pwm2_fc_h_disp, gPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			if(zeroDuty && (!gPwmInfo[pwmId].ctrl.pwm_fc_h_disp))
			{
				FRC_DVO_H13_Wr01(dvo_pwm2_ctrl2, pwm2_fc_l_disp, 1);
			}
			else
			{
				FRC_DVO_H13_Wr01(dvo_pwm2_ctrl2, pwm2_fc_l_disp, gPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			}
			FRC_DVO_H13_WrFL(dvo_pwm2_ctrl0);
			FRC_DVO_H13_WrFL(dvo_pwm2_ctrl1);
			FRC_DVO_H13_WrFL(dvo_pwm2_ctrl2);
			break;
		case 3 :
			FRC_DVO_H13_RdFL(dvo_pwm3_ctrl0);
			FRC_DVO_H13_Wr01(dvo_pwm3_ctrl0, pwm3_en, gPwmInfo[pwmId].ctrl.pwm_en);
			FRC_DVO_H13_Wr01(dvo_pwm3_ctrl0, pwm3_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			FRC_DVO_H13_WrFL(dvo_pwm3_ctrl0);
			break;
		default :
			BREAK_WRONG(pwmId);
	}

	return ret;
}

static int _REG_SetPwmTiming(UINT32 pwmId)
{
	int ret = RET_OK;

	switch (pwmId) {
		case 0 :
			FRC_DVO_H13_RdFL(dvo_pwm_v_load_write);
			FRC_DVO_H13_RdFL(dvo_pwm0_v_r);
			FRC_DVO_H13_RdFL(dvo_pwm0_v_f);
			FRC_DVO_H13_RdFL(dvo_pwm0_v_sub);
			FRC_DVO_H13_Wr01(dvo_pwm_v_load_write, pwm0_v_we, gPwmInfo[pwmId].t1st.pwm_v_we);
			FRC_DVO_H13_Wr01(dvo_pwm0_v_r, pwm0_v_r, gPwmInfo[pwmId].t1st.pwm_v_r);
			FRC_DVO_H13_Wr01(dvo_pwm0_v_r, pwm0_v_r_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			FRC_DVO_H13_Wr01(dvo_pwm0_v_f, pwm0_v_f, gPwmInfo[pwmId].t1st.pwm_v_f);
			FRC_DVO_H13_Wr01(dvo_pwm0_v_f, pwm0_v_f_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			FRC_DVO_H13_Wr01(dvo_pwm_v_load_write, pwm0_v_sub_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			FRC_DVO_H13_Wr01(dvo_pwm0_v_sub, pwm0_v_sub, gPwmInfo[pwmId].t2nd.pwm_v_r);
			FRC_DVO_H13_Wr01(dvo_pwm0_v_sub, pwm0_v_sub_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			FRC_DVO_H13_WrFL(dvo_pwm_v_load_write);
			FRC_DVO_H13_WrFL(dvo_pwm0_v_r);
			FRC_DVO_H13_WrFL(dvo_pwm0_v_f);
			FRC_DVO_H13_WrFL(dvo_pwm0_v_sub);
			break;
		case 1 :
			FRC_DVO_H13_RdFL(dvo_pwm_v_load_write);
			FRC_DVO_H13_RdFL(dvo_pwm1_v_r);
			FRC_DVO_H13_RdFL(dvo_pwm1_v_f);
			FRC_DVO_H13_RdFL(dvo_pwm1_v_sub);
			FRC_DVO_H13_Wr01(dvo_pwm_v_load_write, pwm1_v_we, gPwmInfo[pwmId].t1st.pwm_v_we);
			FRC_DVO_H13_Wr01(dvo_pwm1_v_r, pwm1_v_r, gPwmInfo[pwmId].t1st.pwm_v_r);
			FRC_DVO_H13_Wr01(dvo_pwm1_v_r, pwm1_v_r_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			FRC_DVO_H13_Wr01(dvo_pwm1_v_f, pwm1_v_f, gPwmInfo[pwmId].t1st.pwm_v_f);
			FRC_DVO_H13_Wr01(dvo_pwm1_v_f, pwm1_v_f_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			FRC_DVO_H13_Wr01(dvo_pwm_v_load_write, pwm1_v_sub_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			FRC_DVO_H13_Wr01(dvo_pwm1_v_sub, pwm1_v_sub, gPwmInfo[pwmId].t2nd.pwm_v_r);
			FRC_DVO_H13_Wr01(dvo_pwm1_v_sub, pwm1_v_sub_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			FRC_DVO_H13_WrFL(dvo_pwm_v_load_write);
			FRC_DVO_H13_WrFL(dvo_pwm1_v_r);
			FRC_DVO_H13_WrFL(dvo_pwm1_v_f);
			FRC_DVO_H13_WrFL(dvo_pwm1_v_sub);
			break;
		case 2 :
			FRC_DVO_H13_RdFL(dvo_pwm_v_load_write);
			FRC_DVO_H13_RdFL(dvo_pwm2_v_r);
			FRC_DVO_H13_RdFL(dvo_pwm2_v_f);
			FRC_DVO_H13_RdFL(dvo_pwm2_v_sub);
			FRC_DVO_H13_Wr01(dvo_pwm_v_load_write, pwm2_v_we, gPwmInfo[pwmId].t1st.pwm_v_we);
			FRC_DVO_H13_Wr01(dvo_pwm2_v_r, pwm2_v_r, gPwmInfo[pwmId].t1st.pwm_v_r);
			FRC_DVO_H13_Wr01(dvo_pwm2_v_r, pwm2_v_r_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			FRC_DVO_H13_Wr01(dvo_pwm2_v_f, pwm2_v_f, gPwmInfo[pwmId].t1st.pwm_v_f);
			FRC_DVO_H13_Wr01(dvo_pwm2_v_f, pwm2_v_f_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			FRC_DVO_H13_Wr01(dvo_pwm_v_load_write, pwm2_v_sub_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			FRC_DVO_H13_Wr01(dvo_pwm2_v_sub, pwm2_v_sub, gPwmInfo[pwmId].t2nd.pwm_v_r);
			FRC_DVO_H13_Wr01(dvo_pwm2_v_sub, pwm2_v_sub_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			FRC_DVO_H13_WrFL(dvo_pwm_v_load_write);
			FRC_DVO_H13_WrFL(dvo_pwm2_v_r);
			FRC_DVO_H13_WrFL(dvo_pwm2_v_f);
			FRC_DVO_H13_WrFL(dvo_pwm2_v_sub);
			break;
		default :
			BREAK_WRONG(pwmId);
	}

	return ret;
}

static int _REG_GetPwmTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall)
{
	int ret = RET_OK;

	do {
		switch (freq_mode)
		{
			case 0 :
				FRC_DVO_H13_RdFL(dvo_pwm3_0_low);
				FRC_DVO_H13_RdFL(dvo_pwm3_0_high);
				FRC_DVO_H13_Rd01(dvo_pwm3_0_low, pwm3_0_low, *pRising);
				FRC_DVO_H13_Rd01(dvo_pwm3_0_high, pwm3_0_high, *pFall);
				break;
			case 1 :
				FRC_DVO_H13_RdFL(dvo_pwm3_1_low);
				FRC_DVO_H13_RdFL(dvo_pwm3_1_high);
				FRC_DVO_H13_Rd01(dvo_pwm3_1_low, pwm3_1_low, *pRising);
				FRC_DVO_H13_Rd01(dvo_pwm3_1_high, pwm3_1_high, *pFall);
				break;
			case 2 :
				FRC_DVO_H13_RdFL(dvo_pwm3_2_low);
				FRC_DVO_H13_RdFL(dvo_pwm3_2_high);
				FRC_DVO_H13_Rd01(dvo_pwm3_2_low, pwm3_2_low, *pRising);
				FRC_DVO_H13_Rd01(dvo_pwm3_2_high, pwm3_2_high, *pFall);
				break;
			case 3 :
				FRC_DVO_H13_RdFL(dvo_pwm3_3_low);
				FRC_DVO_H13_RdFL(dvo_pwm3_3_high);
				FRC_DVO_H13_Rd01(dvo_pwm3_3_low, pwm3_3_low, *pRising);
				FRC_DVO_H13_Rd01(dvo_pwm3_3_high, pwm3_3_high, *pFall);
				break;
			default :
				BREAK_WRONG(freq_mode);
		}
	} while(0);

	return ret;
}
