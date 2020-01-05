/****************************************************************************************
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 * GNU General Public License for more details.
 * ***************************************************************************************/



/** @file 
 *
 *  Brief description. 
 *  Detailed description starts here. 
 *
 *  @author		wonsik.do
 *  @version	1.0 
 *  @date		2012-04-25
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "afe_drv.h"
#include "os_util.h"
#include "cvd_task_l9b0.h"
#include "cvd_control_l9b0.h"
#include "cvd_hw.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define L9_ADAPTIVE_BURST_GATE_END_MODE

#undef CVD_USE_NO_BURST_FLAG

//Workaround for Field Stream(양천구 신월동 11채널 영상 Sync흔들림)
//Set hstate_fixed to '1' on NTSC RF signal
#define L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC

#define	SYSTEM_DETECTION_BY_CORDIC_ONLY
//#define	SYSTEM_DETECTION_BY_CORDIC_CS0_CS1

// Workaround for stable AGC on EBC field stream
#define L9_WA_FOR_EBS_STABLE_AGC
#define	CVD_STABLE_COUNT_1	1
#define	CVD_STABLE_COUNT_2	20

//Workaround for PERU noisy field signal(low freq cut-off, status_noise is 0x3ff), flickering and unstable sync
#define L9_AGC_BYPASS_WA_FOR_NOISY_SIGNAL

//Workaround for Field Stream(대전 대덕구 화면 펄럭임발생 문제 : 수직 동기 떨림 빈도 100%)
//Set vsync_cntl 0x2, vsync_cntl_noisy 0x1, vloop_tc 0x3
//#define L9_VSYNC_CNTL_FOR_STABLE_VSYNC

// Workaround for DONG_GO_DONG_RAK stream :	20120208
#define L9_CHANGE_FIELD_DETECT_MODE_ON_DONG_GO_DONG_RAK

#define L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
#define L9_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST
#define L9_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE

#define CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD	10

#define CVD_ADAPTIVE_BURST_GATE_COUNT_ITERATION	20	// 20 is about 1 sec.
#define CVD_ADAPTIVE_BURST_GATE_THRESHOLD_0	0x3D090		// Threshold for enter CDTO value(hex value of 250K)
#define CVD_ADAPTIVE_BURST_GATE_THRESHOLD_1	0xCE4			// Threshold for CORDIC FREQ VALUE *20 (hex value of 3.3k)
#define CVD_ADAPTIVE_BURST_GATE_THRESHOLD_3	0x27100		// Threshold for leave CDTO value(hex value of 160K)
#define CVD_STABLE_COUNT_FOR_AGC_CONTROL	20

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern CVD_STATUS_3CS_T	g_CVD_Status_3CS ;

//extern CVD_STATE_T	gMainCVD_State;
//extern CVD_STATE_T	gPrevious_Main_System;
//extern CVD_STATE_T	Current_State ;
//extern CVD_STATE_T	Next_State ;
//extern LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T g_CVD_Color_System_Support;
//extern int		gAutoProgramming;
//extern BOOLEAN gPortChangeDetected;
extern CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;
//extern BOOLEAN g_CVD_RF_Input_Mode;
extern CVD_SET_SYSTEM_MAIN_T g_SetColorSystemMain[];
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static CVD_STATE_T CVD_L9Bx_Check_Color_System_Support(LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	forced_color_system);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int g_Stable_AGC_WA_for_EBS_Enabled = 0;

static UINT8 MainCVD_Same_State_Count=0;
/*========================================================================================
	Implementation Group
========================================================================================*/

int	CVD_L9Bx_Task_3cdetect(void)
{
#ifdef L9_ADAPTIVE_BURST_GATE_END_MODE
	static UINT32 gVariance_Status_Cdto_Inc = 0;
	static int	  gAdaptive_Burst_Gate_Counter = 0;
	int	Adaptive_Burst_Gate_Enable = 0;
	static int Prev_Adaptive_Burst_Gate_Enable = 0;
	static UINT32 gAccumulated_Cordic_Freq_Value = 0;
#endif
	static UINT8	No_Signal_Flag, HV_Lock_Flag;
	//static UINT8	No_Signal_Count = 0;

	static UINT8	 MainCVD_No_Signal = 0;
	static UINT8	 MainCVD_Prev_Written_Color_System = 0;
	static BOOLEAN	 MainCVD_Is_Prev_RF_Input = FALSE;

	//	static UINT8 MainCVD_State_Transition_Count=0;
	//AFE_PRINT("In MainCVD Work\n");
	//CVD_DEBUG("MainCVD State = [%d]\n ", g_CVD_Status_3CS.cvd_color_system);
	//static	UINT32 Same_State_Count = 0;
	static UINT32	cvd_noise_sum	= 0;
	unsigned int avg_noise_level;
	static int stable_state2_count = 0;

	static UINT8 burst_mag_prev = 0, burst_mag_next = 0;
	static UINT32 burst_mag_array[10];
	UINT32 burst_mag_sum = 0;
	UINT32 burst_mag_avg;
	static UINT32 prev_burst_mag_avg ;
	static UINT32 cagc_target ;
	static UINT32 cagc_written ;

	static UINT16	status_noise_array[8] = {0,};
	static UINT16	status_agc_gain_array[8] = {0,};

	//LX_AFE_CVD_PQ_MODE_T	cvd_pe_color_system;
	int loop, avg_tmp = 0;
	int	agc_gain_tmp = 0;
#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
	static UINT8	vcr_detect_count;
	static int 		gHstateMaxCounter = 0;
#endif
	CVD_STATE_T	check_supporting_color_system;

	/* Read Status CVD Registers */
	g_CVD_Status_3CS.no_signal_flag = CVD_L9Bx_Get_No_Signal_Flag();
	g_CVD_Status_3CS.h_lock_flag = CVD_L9Bx_Get_HLock_Flag();
	g_CVD_Status_3CS.v_lock_flag = CVD_L9Bx_Get_VLock_Flag();
	// ORing hlock & vlock makes frequent state transition to NO_SIGNAL_STATE on noisy signal.
	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	// So ANDing hlock & vlock will be used for cheking cvd lock state.
	//HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag || g_CVD_Status_3CS.v_lock_flag;
	g_CVD_Status_3CS.vline_625_flag = CVD_L9Bx_Get_Vline_625_Flag();
	g_CVD_Status_3CS.cvd_pal_flag = CVD_L9Bx_Get_PAL_Flag();
	g_CVD_Status_3CS.cvd_secam_flag = CVD_L9Bx_Get_SECAM_Flag();//gogosing
	g_CVD_Status_3CS.cvd_chromalock_flag = CVD_L9Bx_Get_Chromalock_Flag();
	g_CVD_Status_3CS.status_noise = CVD_L9Bx_Get_Noise_Status();
	g_CVD_Status_3CS.no_burst_flag = CVD_L9Bx_Get_NoBurst_Flag();
	g_CVD_Status_3CS.cvd_fc_flag = CVD_L9Bx_Get_FC_Flag(LX_CVD_MAIN);
	g_CVD_Status_3CS.cvd_cordic_freq = CVD_L9Bx_Get_Cordic_Freq(LX_CVD_MAIN);
	g_CVD_Status_3CS.cvd_cordic_freq += CVD_L9Bx_Get_Cordic_Freq(LX_CVD_MAIN);
	g_CVD_Status_3CS.cvd_cordic_freq += CVD_L9Bx_Get_Cordic_Freq(LX_CVD_MAIN);
	g_CVD_Status_3CS.cvd_cordic_freq += CVD_L9Bx_Get_Cordic_Freq(LX_CVD_MAIN);
	g_CVD_Status_3CS.cvd_cordic_freq = (g_CVD_Status_3CS.cvd_cordic_freq>>2);
	//g_CVD_Status_3CS.cvd_cordic_freq += CVD_Get_Cordic_Freq(LX_CVD_MAIN);
	//g_CVD_Status_3CS.cvd_cordic_freq = g_CVD_Status_3CS.cvd_cordic_freq /5;
	if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0 )) {
		 g_CVD_Status_3CS.status_agc_gain = CVD_L9Bx_Get_Status_AGC_Gain();
		 g_CVD_Status_3CS.hnon_standard_flag = CVD_L9Bx_Get_HNon_Standard_Flag();
		 g_CVD_Status_3CS.vnon_standard_flag = CVD_L9Bx_Get_VNon_Standard_Flag();
	}
	else	{
		 g_CVD_Status_3CS.status_agc_gain = 0;
		 g_CVD_Status_3CS.hnon_standard_flag = 0;
		 g_CVD_Status_3CS.vnon_standard_flag = 0;
	}
	/*
	if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
		CVD_AGC_Bypass_Function((UINT32)g_CVD_Status_3CS.status_noise, (UINT32)g_CVD_Status_3CS.h_lock_flag, (UINT32)g_CVD_Status_3CS.no_signal_flag );
		*/

	// test only 120217
/*
	if( ( !g_CVD_Status_3CS.v_lock_flag ) && (!g_CVD_Status_3CS.h_lock_flag ) && (g_CVD_Status_3CS.no_signal_flag) ) {
		CVD_DEBUG("H/V Unlock & No signal !!! \n");
#ifdef CVD_CH42_SKIP_WORKAROUND
//				CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
#endif
	}
	*/

	for(loop = 7;loop > 0;loop--) {
		status_noise_array[loop] = status_noise_array[loop-1] ;
		avg_tmp += status_noise_array[loop];
	}
	status_noise_array[0] = g_CVD_Status_3CS.status_noise;
	avg_tmp += status_noise_array[0];

	g_CVD_Status_3CS.avg_status_noise = avg_tmp >> 3;

	for(loop = 7;loop > 0;loop--) {
		status_agc_gain_array[loop] = status_agc_gain_array[loop-1] ;
		agc_gain_tmp += status_agc_gain_array[loop];
	}
	status_agc_gain_array[0] = g_CVD_Status_3CS.status_agc_gain;
	agc_gain_tmp += status_agc_gain_array[0];

	g_CVD_Status_3CS.avg_status_agc_gain = agc_gain_tmp >> 3;

	if ( lx_chip_rev() >= LX_CHIP_REV( L9, A0 ))
	{
		g_CVD_Status_3CS.cs0_pal_flag = CVD_L9Bx_Get_PAL_Flag_CS0();
		g_CVD_Status_3CS.cs0_secam_flag = CVD_L9Bx_Get_SECAM_Flag_CS0();//gogosing
		g_CVD_Status_3CS.cs0_chromalock_flag = CVD_L9Bx_Get_Chromalock_Flag_CS0();
		g_CVD_Status_3CS.cs0_fc_flag = CVD_L9Bx_Get_FC_Flag_CS0();
		g_CVD_Status_3CS.cs0_cordic_freq = CVD_L9Bx_Get_Cordic_Freq_CS0();
		g_CVD_Status_3CS.cs0_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS0();
		g_CVD_Status_3CS.cs0_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS0();
		g_CVD_Status_3CS.cs0_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS0();
		g_CVD_Status_3CS.cs0_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS0();
		g_CVD_Status_3CS.cs0_cordic_freq = g_CVD_Status_3CS.cs0_cordic_freq /5;

		g_CVD_Status_3CS.cs1_pal_flag = CVD_L9Bx_Get_PAL_Flag_CS1();
		g_CVD_Status_3CS.cs1_secam_flag = CVD_L9Bx_Get_SECAM_Flag_CS1();//gogosing
		g_CVD_Status_3CS.cs1_chromalock_flag = CVD_L9Bx_Get_Chromalock_Flag_CS1();
		g_CVD_Status_3CS.cs1_fc_flag = CVD_L9Bx_Get_FC_Flag_CS1();
		g_CVD_Status_3CS.cs1_cordic_freq = CVD_L9Bx_Get_Cordic_Freq_CS1();
		g_CVD_Status_3CS.cs1_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS1();
		g_CVD_Status_3CS.cs1_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS1();
		g_CVD_Status_3CS.cs1_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS1();
		//g_CVD_Status_3CS.cs1_cordic_freq += CVD_L9Bx_Get_Cordic_Freq_CS1();
		g_CVD_Status_3CS.cs1_cordic_freq = (g_CVD_Status_3CS.cs1_cordic_freq>>2);
		//g_CVD_Status_3CS.cs1_cordic_freq = g_CVD_Status_3CS.cs1_cordic_freq /5;

	}
	//CVD_DEBUG("NO[%d],HL[%d],VL[%d],V625[%d],PAL[%d],SECAM[%d],ChromaL[%d]\n cordic_freq[%d], noise[%d], , noburst[%d], c_state[%d], g_State[%d]\n ",No_Signal_Flag, CVD_Get_HLock_Flag(), CVD_Get_VLock_Flag(), Vline_625_Flag, Pal_Flag, Secam_Flag, Chromalock_Flag, cvd_cordic_freq, status_noise, NoBurst_Flag, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_color_system);

	//110414 No_Signal_Flag is not working well
	No_Signal_Flag = 0;

	switch(g_CVD_Status_3CS.cvd_color_system)
	{
		case CVD_STATE_VideoNotReady:
#ifdef CVD_CH42_SKIP_WORKAROUND
			//CVD_ClampAGC_OnOff(0); // agc off on No signal for ch42 no signal workaround
//			if ( lx_chip_rev( ) < LX_CHIP_REV( L9, A0 ) )
//				CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
//			else
//			{
				//Disable Clampagc reset workaround (Clamp AGC problem is fixed by disabling x2 LPF setting at Set_AAF_Params)
				//CVD_Reset_Clampagc();
				//CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
//			}
#endif
			// dws 0809 for 42ch no signal problem
			if(g_CVD_Status_3CS.cvd_no_signal_count > 4) 
			{
			}
			else if(g_CVD_Status_3CS.cvd_no_signal_count == 4) // Remain No Signal for 2 seconds
			{
				// dws 0906 for color kill on no signal
				CVD_Force_Color_Kill(1);
				g_CVD_Status_3CS.cvd_no_signal_count++;
			}
			else
				g_CVD_Status_3CS.cvd_no_signal_count++;
			MainCVD_No_Signal = 1;
#if 0
			if ( HV_Lock_Flag /* || !No_Signal_Flag */)	// HV sync detected
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoReadyToDetect;
			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			break;
#endif

		case CVD_STATE_VideoReadyToDetect:
			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;
			else if(g_CVD_Status_3CS.color_system_support == (LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_M | LX_COLOR_SYSTEM_PAL_NC) )	// For Brazil
			{
				if ( g_CVD_Status_3CS.vline_625_flag ) //Vertical 625 Line
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
				else
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
			}
			else // for Multi System
			{
				if ( g_CVD_Status_3CS.vline_625_flag ) //Vertical 625 Line
				{
					if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
					else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
					else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
				}
				else
				{
					if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
					else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
					else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
					else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
						g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
				}
			}

			break;

		case CVD_STATE_NTSC:
			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;
#ifdef CVD_USE_NO_BURST_FLAG
			else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// For No burst signal, with 525 line system remain in NTSC
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
#endif
			else if(g_CVD_Status_3CS.vline_625_flag)
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
			}
			// 111028 wonsik.do : Check PAL-M before NTSC-M to fix slow color system transition to PAL-M (both NTSC-M & PAL-M locked for long time)
			else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Transition to PALm
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

			else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Remain in NTSC
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

			else if(g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Transition to PAL60
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

			else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Transition to NTSC443
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
			break;

		case CVD_STATE_NTSC443:
			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
			else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// For no burst signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
#endif

			else if(g_CVD_Status_3CS.vline_625_flag)
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
			}

			else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Remain in NTSC443
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

			else if(!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Transition to NTSC
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

			else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Transition to PALm
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

			else if(g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Transition to PAL60
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
			break;

		case CVD_STATE_PALi:

			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
			else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 625 line signal
			{
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
			}
#endif

			else if(!g_CVD_Status_3CS.vline_625_flag)	// Transition to 525 line system
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
			}

			else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Remain in PALi
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

			//111028 added cvd choromalock flag to AND with cvd pal flag to determine SECAM detection
			//110809 added cvd pal flag
			else if(!(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag) && !g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_secam_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

			else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

#ifdef	SYSTEM_DETECTION_BY_CORDIC_ONLY
			else if((g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Remain in PALi
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#ifdef SYSTEM_DETECTION_BY_CORDIC_CS0_CS1
			else if((g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
			else if((g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
#endif
#endif
			else
			{
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
			}

			break;

		case CVD_STATE_PALm:

			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
			else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 525 line
			{
				if(g_CVD_Status_3CS.color_system_support == (LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_M | LX_COLOR_SYSTEM_PAL_NC) )	// For Brazil
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
				else
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
			}
#endif

			else if(g_CVD_Status_3CS.vline_625_flag)
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
			}

			else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= ( FC_MORE_THRESHOLD + 0x40) ) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Remain in PALm
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

			else if(g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Transition to PAL60
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

			else if(!g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Transition to NTSC
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

			else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Transition to NTSC443
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

			break;

		case CVD_STATE_PALCn:

			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
			else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 625 line
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#endif

			else if(!g_CVD_Status_3CS.vline_625_flag)		// Transition to 525 line systems
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
			}

			else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Remain in PALCn
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

			else if(!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_secam_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

			else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

#ifdef	SYSTEM_DETECTION_BY_CORDIC_ONLY
			else if((g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Remain in PALCn
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

#ifdef SYSTEM_DETECTION_BY_CORDIC_CS0_CS1
			else if((g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

			else if((g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#endif
#endif

			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

			break;
		case CVD_STATE_PAL60:

			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
			else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 525 line
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
#endif

			else if(g_CVD_Status_3CS.vline_625_flag)
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
			}

			else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Remain in PAL60
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

			else if(!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Transition to NTSC
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

			else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Transition to PALm
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

			else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Transition to NTSC443
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

			break;

		case CVD_STATE_SECAM:

			if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

			// For user force color system
			else if ((check_supporting_color_system = CVD_L9Bx_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
				g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
			else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 625line
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#endif

			else if(!g_CVD_Status_3CS.vline_625_flag)		//Transition to 625line system
			{
				if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
				else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
					g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
			}

			else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_secam_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Remain in SECAM
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

			else if(g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

			else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

#ifdef	SYSTEM_DETECTION_BY_CORDIC_ONLY
			else if((g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Remain in SECAM
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
#ifdef SYSTEM_DETECTION_BY_CORDIC_CS0_CS1
			else if((g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

			else if((g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
#endif
#endif

			else
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

			break;

		default:
			break;
	}

#ifdef L9_FAST_3DCOMB_WORKAROUND
	if( (g_CVD_Status_3CS.hnon_standard_flag) && (g_CVD_Status_3CS.in_atv_tunning == FALSE) && (g_CVD_Status_3CS.cvd_next_state != CVD_STATE_SECAM) && (g_CVD_Status_3CS.cvd_next_state != CVD_STATE_NTSC443)) {	// hnon standard detected  && not in auto tuning && color system is not in SECAM/NTSC443
		CVD_L9Bx_Set_HNon_Standard_Threshold(0);
	}
	else if(g_CVD_Status_3CS.cvd_next_state < CVD_STATE_VideoNotReady) {
		CVD_L9Bx_Set_HNon_Standard_Threshold(g_SetColorSystemMain[g_CVD_Status_3CS.cvd_next_state].reg_hnon_std_threshold);
	}
	else {
//		CVD_DEBUG("HNon_Std not detected in not locked state \n");
	}

#endif
	// #1 	: sync lock detected
	//		: reset "g_CVD_Status_3CS.cvd_no_signal_count"
	if((g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoNotReady) && (g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoReadyToDetect))
	{
		g_CVD_Status_3CS.cvd_no_signal_count = 0;
		// Continuous Write on ckill register when signal locked state.
		//		CVD_Force_Color_Kill(0);
	}

	// #2 	: State Change Detected !!!!!
	//		:
	if( (g_CVD_Status_3CS.cvd_next_state != g_CVD_Status_3CS.cvd_color_system) || (g_CVD_Status_3CS.port_change_detected == TRUE))
	{
		g_CVD_Status_3CS.cvd_lock_stable_count = 0;
		cvd_noise_sum = 0;	//clear noise sum value
		g_CVD_Status_3CS.port_change_detected = FALSE;

		//g_CVD_Status_3CS.cvd_color_system = g_CVD_Status_3CS.cvd_next_state;
		CVD_DEBUG("CVD State Change to [%d]\n", g_CVD_Status_3CS.cvd_next_state);
		CVD_DEBUG("NO[%d],HL[%d],VL[%d],V625[%d],PAL[%d],SECAM[%d],ChromaL[%d]\n cordic_freq[%d], noise[%d], , noburst[%d], c_state[%d], g_State[%d]\n ",g_CVD_Status_3CS.no_signal_flag, g_CVD_Status_3CS.h_lock_flag, g_CVD_Status_3CS.v_lock_flag, g_CVD_Status_3CS.vline_625_flag, g_CVD_Status_3CS.cvd_pal_flag, g_CVD_Status_3CS.cvd_secam_flag, g_CVD_Status_3CS.cvd_chromalock_flag, g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.status_noise, g_CVD_Status_3CS.no_burst_flag, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_color_system);
		CVD_DEBUG("CS0:PAL[%d],SECAM[%d],ChromaL[%d] cordic_freq[%d]\n ", g_CVD_Status_3CS.cs0_pal_flag, g_CVD_Status_3CS.cs0_secam_flag, g_CVD_Status_3CS.cs0_chromalock_flag, g_CVD_Status_3CS.cs0_cordic_freq);
		CVD_DEBUG("CS1:PAL[%d],SECAM[%d],ChromaL[%d] cordic_freq[%d]\n ", g_CVD_Status_3CS.cs1_pal_flag, g_CVD_Status_3CS.cs1_secam_flag, g_CVD_Status_3CS.cs1_chromalock_flag, g_CVD_Status_3CS.cs1_cordic_freq);

		// For proper color system detection, at first set cstate value to default.
		CVD_L9Bx_Program_Color_System_PreJob(&g_SetColorSystemMain[CVD_STATE_Default]);

		//120328 : not to excute following function on signal transition period.
		//CVD_NoBurst_CKill_Control(&g_CVD_Status_3CS);

		for(loop = 0;loop < 10;loop++) {
			burst_mag_array[loop] = 0xFFFF ;
			burst_mag_sum += burst_mag_array[loop];
		}

		burst_mag_prev=0;
		burst_mag_next=0;
		prev_burst_mag_avg = 0xbc0;
		cagc_target = 0xbc0;

	// #2.1 	: State Change & Previously Locked State is NTSC
		if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_NTSC)
		{
			// Restore cagc value to default
			CVD_DEBUG("Cagc value to default \n");
			CVD_L9Bx_Set_CVD_CAGC(CVD_BURST_MAG_STATE_BIG,&g_SetColorSystemMain[g_CVD_Status_3CS.cvd_prev_color_system], g_CVD_Status_3CS.cvd_prev_color_system);

			//120131
			/*
			//if saturation value is adjusted, restoring initial value is needed (for same color system detection case)
			if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0) ) {
			CVD_L9Bx_Set_CVD_Saturation_Value(g_SetColorSystemMain[g_CVD_Status_3CS.cvd_prev_color_system].reg_saturation);
			}
			 */

#ifdef L9_WA_FOR_EBS_STABLE_AGC
			// restore default values of reg_agc_half_en to '0', and reg_nstd_hysis to '7' for EBS field stream support.
			// restore default values of reg_agc_peak_cntl to '1', and reg_dcrestore_gain to '0' for stable AGC on NTSC RF
			if ( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_Stable_AGC_WA_for_EBS_Enabled))
			{
				g_Stable_AGC_WA_for_EBS_Enabled = 0;
				CVD_L9Bx_Program_Color_System_PreJob2();
			}
#endif
#ifdef L9_AGC_BYPASS_WA_FOR_NOISY_SIGNAL
			// for PERU Weak RF signal
			if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) {
				if (g_CVD_Status_3CS.noisy_signal_detected == 1) {
					CVD_DEBUG("CVD Normal RF Signal(default) \n");
					// changed to normal signal
					g_CVD_Status_3CS.noisy_signal_detected = 0;
					CVD_L9Bx_Set_for_Normal_Signal();
				}
			}
#endif
#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
			if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) {
				//		CVD_DEBUG("Set hstate_fixed value to 0 (default) \n");
				CVD_L9Bx_Set_Hstate_Fixed(0);
				CVD_L9Bx_Set_Hstate_Max(5);
			}
#endif
#ifdef L9_VSYNC_CNTL_FOR_STABLE_VSYNC // disabled
			if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0))  {
				CVD_L9Bx_Set_for_Stable_Vsync(0);
			}
#endif
#ifdef L9_CHANGE_FIELD_DETECT_MODE_ON_DONG_GO_DONG_RAK

			if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0))  {
				CVD_L9Bx_Set_for_Field_Detect_Mode(2);
			}
#endif
#ifdef L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
			//120222 setting agc_peak_en to initial value is moved to CVD_STABLE_COUNT_1
			// for NTSC system agc_peak_en should be '1' on no signal state.
			//CVD_AGC_Peak_En_Control(2, 0, 0);	//force on peak_en
#endif
		}
		// #2.2 	: State Change & Previously Locked State is PALm
		else if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_PALm)
		{
#ifdef L9_WA_FOR_EBS_STABLE_AGC
			// restore default values of reg_agc_half_en to '0', and reg_nstd_hysis to '7' for EBS field stream support.
			// restore default values of reg_agc_peak_cntl to '1', and reg_dcrestore_gain to '0' for stable AGC on NTSC RF
			if ( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_Stable_AGC_WA_for_EBS_Enabled))
			{
				g_Stable_AGC_WA_for_EBS_Enabled = 0;
				CVD_L9Bx_Program_Color_System_PreJob2();
			}
#endif
#ifdef L9_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST
 			if( lx_chip_rev() >= LX_CHIP_REV(L9,B0))	CVD_OnOff_Chromalock_Ckill(1);
#endif
#ifdef L9_ADAPTIVE_BURST_GATE_END_MODE
			if( lx_chip_rev() >= LX_CHIP_REV(L9,B0))
			{
				CVD_L9Bx_Set_for_Burst_Gate_End_On_Noisy(g_SetColorSystemMain[CVD_STATE_PALm].reg_burst_gate_end_new ,0);
#ifdef L9_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE
				CVD_L9Bx_AGC_Bypass(0);
#endif
			}
#endif

		}
		// #2.3 	: State Change & Previously Locked State is PALi
		else if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_PALi) {
#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
			if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) {
				//		CVD_DEBUG("Set hstate_fixed value to 0 (default) \n");
				CVD_L9Bx_Set_Hstate_Fixed(0);
			}
#endif
			//120217 : added for PAL channel change
#ifdef L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
			//120222 setting agc_peak_en to initial value is moved to CVD_STABLE_COUNT_1
			// for PAL system agc_peak_en should be '0' on no signal state.
			//CVD_AGC_Peak_En_Control(0, 0, 0);	//force off peak_en
#endif
		} // #2.4 	: State Change & Previously Locked State is SECAM
		else if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_SECAM) {
#ifdef L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
			//120222 setting agc_peak_en to initial value is moved to CVD_STABLE_COUNT_1
			// for SECAM to PAL system change agc_peak_en should be '0' on no signal state.
			//CVD_AGC_Peak_En_Control(0, 0, 0);	//force off peak_en
#endif
		} // #2.5 	: State Change & Previously Locked State is not NTSC/PALm/PALi/SECAM
		else {
#ifdef L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
			//120222 setting agc_peak_en to initial value is moved to CVD_STABLE_COUNT_1
		// for PAL system agc_peak_en should be '0' on no signal state.
//		CVD_AGC_Peak_En_Control(0, 0, 0);	//force off peak_en
#endif
		}
		// NTSC Pattern Detection Function
		if( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && ( g_CVD_Pattern_Detection_t.bEnable == TRUE ) )
		{
			g_CVD_Pattern_Detection_t.pattern_found = 0x0 ;
			g_CVD_Pattern_Detection_t.prev_motion_value = 0x0 ;
			g_CVD_Pattern_Detection_t.global_motion_count = 0x0 ;
		}


		if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
			CVD_L9Bx_AGC_Bypass_Function(0, 0, 1 );
			//CVD_AGC_Bypass_Function((UINT32)g_CVD_Status_3CS.status_noise, (UINT32)g_CVD_Status_3CS.h_lock_flag, (UINT32)g_CVD_Status_3CS.no_signal_flag );

		//if((g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) ||(g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALi))
		// Sync Detected !!!

		// #3 	: State Change Detected && Sync Lock Detected !!!
		//		:
		if(g_CVD_Status_3CS.cvd_next_state < CVD_STATE_VideoNotReady)
		{

			// If any color system is detected, disable color kill.
			CVD_Force_Color_Kill(0);

			/*
			//120217 for test only
			if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
				CVD_L9Bx_Reset_mif(0);
				*/

			//		if(g_CVD_Status_3CS.cvd_prev_color_system != g_CVD_Status_3CS.cvd_next_state) // IF from no signal, do not re-setting cvd register to the same value

			// #4 	: State Change from No signal
			//		:
			if((g_CVD_Status_3CS.cvd_prev_color_system != g_CVD_Status_3CS.cvd_next_state)|(g_CVD_Status_3CS.cvd_color_system==CVD_STATE_VideoNotReady))
			{
				//120217 : removed comb2d_only settting
#if 0
				//120109 : reset lbadrgen_rst and comb2d_only register on sync lock to reduce comb-filter artifact on channel change.
				//120216 : com2d_only setting on NTSC RF makes 3dcomb artifact on channel change
				if ( ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) ) && (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALi))  {
					CVD_L9Bx_Set_comb2d_only(1);
					OS_MsecSleep(5);
					CVD_L9Bx_Set_comb2d_only(0);
				}
#endif
				// #5 	: State Change from No signal, and different color system from previously locked color system
				//		:
				if( ( MainCVD_Prev_Written_Color_System != g_CVD_Status_3CS.cvd_next_state) || (MainCVD_Is_Prev_RF_Input != g_CVD_Status_3CS.in_rf_mode))
				{
					CVD_DEBUG("Setting CVD [%d]\n", g_CVD_Status_3CS.cvd_next_state);

					/*
					   if((g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) ||(g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSCj)|| (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC443) )
					   {
					   gEnable_SW3DCOMBControl = 1;
					   cvd_pe_color_system = LX_CVD_PQ_NTSC_M;
					   }
					   else
					   {
					   gEnable_SW3DCOMBControl = 0;
					   CVD_Set_motion_mode(0x1, 0x0) ;
					   cvd_pe_color_system = LX_CVD_PQ_PAL;
					   }

					   CVD_Set_PQ_Mode(cvd_pe_color_system);

					 */
					{
						//AFE_PRINT("HDCT/CDCT Reset 1\n");
						CVD_L9Bx_Reset_hdct(1);
						CVD_L9Bx_Reset_cdct(1);

						//by dws : remove mdelay
						//mdelay(10);
						OS_MsecSleep(10);
					}

					CVD_L9Bx_Set_Color_System_3CS(g_CVD_Status_3CS.cvd_next_state);
					MainCVD_Prev_Written_Color_System = g_CVD_Status_3CS.cvd_next_state;
					MainCVD_Is_Prev_RF_Input = g_CVD_Status_3CS.in_rf_mode;

					{
						CVD_L9Bx_Reset_hdct(0);
						CVD_L9Bx_Reset_cdct(0);
					}
				}
				// #6 	: State Change from No signal, and but same color system with previsouly locked system.
				//		: IF from VideoReadyToDetect, do not re-setting cvd register to the same value
				else
				{
					CVD_DEBUG("Same system [%d] again\n", g_CVD_Status_3CS.cvd_next_state);

#if 0
					if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
					{
						//111122 : disable 2dcomb only mode
						if( (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALi) || (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALCn) || (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALm) || (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC))
							CVD_L9Bx_Set_comb2d_only(0);
					}
#endif
				}

				//	CVD_Force_Color_Kill(0);
#ifdef CVD_CH42_SKIP_WORKAROUND
				//CVD_Clamp_Current_Control(0);	// 1118 change clamp current to zero
#endif
			}
			//Program_Color_System_Main_only_system_set(g_SetColorSystemMain[g_CVD_Status_3CS.cvd_next_state]);
			//SW reset is needed here???
			//CVD_SW_Reset(LX_CVD_MAIN);
			g_CVD_Status_3CS.cvd_prev_color_system = g_CVD_Status_3CS.cvd_next_state;
			//gMainCVD_State = g_CVD_Status_3CS.cvd_next_state;
			g_CVD_Status_3CS.cvd_color_system = g_CVD_Status_3CS.cvd_next_state;
		}
		// #7 	: State Change to NO SIGNAL !!!!!
		//		:
		else if(g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoReadyToDetect)  // No Signal or color system change
		{
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoNotReady;

			CVD_DEBUG("Set No Burst CKill\n");
			//120328 : set burst_ckill on no signal

			g_CVD_Status_3CS.no_color_detected = 1;
			if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))
				CVD_L9Bx_Set_Noburst_Ckill(1);

#ifdef CVD_CH42_SKIP_WORKAROUND
			if ( lx_chip_rev( ) < LX_CHIP_REV( L9, A0 ) )
				CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
			else
			{
				//Disable Clampagc reset workaround (Clamp AGC problem is fixed by disabling x2 LPF setting at Set_AAF_Params)
				//CVD_Reset_Clampagc();
				CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
			}
#endif
#if 0
			//111122 : set to 2d comb only mode on no signal state.
			if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
				CVD_L9Bx_Set_comb2d_only(1);
#endif
			/*
			//120217 for test only
			if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
				CVD_L9Bx_Reset_mif(1);
				*/

		}
		// #8 	: State Change to videoreadytodetect !!!!!
		//		: never enter here
		else
		{
			// From Ok : SW workaround for 3D comb operation 2010/06/04
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoReadyToDetect;
		}
		MainCVD_Same_State_Count = 0;

		//1126 for fast standard detection
		//gMainCVD_State = g_CVD_Status_3CS.cvd_next_state;
		g_CVD_Status_3CS.cvd_prev_color_system = g_CVD_Status_3CS.cvd_next_state;
	}
	// #8 	: Same State Again
	//		:
	else // same state again
	{

		// #9 	: Same State and Sync Lock
		//		:
//		CVD_DEBUG("Same State and Sync Lock , g_CVD_Status_3CS.cvd_next_state[%d], g_CVD_Status_3CS.in_atv_tunning[%d]\n",g_CVD_Status_3CS.cvd_next_state, g_CVD_Status_3CS.in_atv_tunning );
		
		// 120305 : not to execute SW workaround routines while ATV auto searching
//		if(g_CVD_Status_3CS.cvd_next_state < CVD_STATE_VideoNotReady)
		if (g_CVD_Status_3CS.cvd_next_state < CVD_STATE_VideoNotReady)
		{
			CVD_L9Bx_NoBurst_CKill_Control(&g_CVD_Status_3CS);
			if(g_CVD_Status_3CS.in_atv_tunning == FALSE) {

				cvd_noise_sum += g_CVD_Status_3CS.status_noise;


				if(g_CVD_Status_3CS.cvd_lock_stable_count > CVD_STABLE_COUNT_2) {
#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC

					if ( (lx_chip_rev() >= LX_CHIP_REV( L9, B0))&&(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)  && (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
						gHstateMaxCounter++;
						if(CVD_L9Bx_Read_VCR_Detected()) vcr_detect_count++;

						if(gHstateMaxCounter >= 20)
						{
							if(vcr_detect_count >=  CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD)
								CVD_L9Bx_Set_Hstate_Max(3);
							else CVD_L9Bx_Set_Hstate_Max(5);

							gHstateMaxCounter = 0;
							vcr_detect_count = 0;
						}
					}
#endif

#ifdef L9_ADAPTIVE_BURST_GATE_END_MODE
					if ( (lx_chip_rev() >= LX_CHIP_REV( L9, B0))&& (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE)  )
					{
						if(gAdaptive_Burst_Gate_Counter == 0)
						{
							if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
								gVariance_Status_Cdto_Inc = CVD_L9Bx_Differential_Status_Cdto_Inc_Value();
								gAccumulated_Cordic_Freq_Value = CVD_L9Bx_Read_Cordic_Freq_Value();
							}
							gAdaptive_Burst_Gate_Counter++;
						}
						else if(gAdaptive_Burst_Gate_Counter < CVD_ADAPTIVE_BURST_GATE_COUNT_ITERATION)
						{
							if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
								gVariance_Status_Cdto_Inc += CVD_L9Bx_Differential_Status_Cdto_Inc_Value();
								gAccumulated_Cordic_Freq_Value += CVD_L9Bx_Read_Cordic_Freq_Value();
							}
							gAdaptive_Burst_Gate_Counter++;
						}
						else if(gAdaptive_Burst_Gate_Counter >= CVD_ADAPTIVE_BURST_GATE_COUNT_ITERATION)
						{
							if((gVariance_Status_Cdto_Inc >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_0)&&(gAccumulated_Cordic_Freq_Value >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_1))
								Adaptive_Burst_Gate_Enable = 1;
							else if(gVariance_Status_Cdto_Inc <= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_3)
								Adaptive_Burst_Gate_Enable = 0;
							else
								Adaptive_Burst_Gate_Enable = 2;

							if((Adaptive_Burst_Gate_Enable == Prev_Adaptive_Burst_Gate_Enable)&&(Adaptive_Burst_Gate_Enable != 2))
							{
								CVD_L9Bx_Set_for_Burst_Gate_End_On_Noisy(g_SetColorSystemMain[CVD_STATE_PALm].reg_burst_gate_end_new ,Adaptive_Burst_Gate_Enable);
#ifdef L9_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE
								CVD_L9Bx_AGC_Bypass(Adaptive_Burst_Gate_Enable);
#endif
							}
							Prev_Adaptive_Burst_Gate_Enable = Adaptive_Burst_Gate_Enable;

							//AFE_PRINT("AVERAGE CDTO_INC[%x] CORDIC_FREQ[%d] RESULT[%d]\n", gVariance_Status_Cdto_Inc, gAccumulated_Cordic_Freq_Value, Adaptive_Burst_Gate_Enable );
							gAdaptive_Burst_Gate_Counter = 0;
						}
					}
#endif
#ifdef L9_AGC_BYPASS_WA_FOR_NOISY_SIGNAL

					stable_state2_count ++;

					if(stable_state2_count >= CVD_STABLE_COUNT_FOR_AGC_CONTROL) {

						avg_noise_level = cvd_noise_sum / stable_state2_count;
						stable_state2_count = 0;
						cvd_noise_sum = 0;

						//CVD_DEBUG("# avg noise level(stable state) [0x%x]#\n", avg_noise_level);

						// for PERU Weak RF signal
						//for noisy signal , diable agc(agc_bypass) & set dcrestore gain to 1/8 for stable sync and AGC.
						if ( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
							if( avg_noise_level >=  (CVD_L9B0_NOISE_MAX - 0x10) ) {
								if (g_CVD_Status_3CS.noisy_signal_detected == 0) {
									CVD_DEBUG("CVD Noisy RF Signal(stable state) \n");
									// changed to noisy signal
									g_CVD_Status_3CS.noisy_signal_detected = 1;
									CVD_L9Bx_Set_for_Noisy_Signal();
								}
							}
							else if( avg_noise_level < (CVD_L9B0_NOISE_MAX - 0x30) ) {
								if (g_CVD_Status_3CS.noisy_signal_detected == 1) {
									CVD_DEBUG("CVD Normal RF Signal(stable state) \n");
									// changed to normal signal
									g_CVD_Status_3CS.noisy_signal_detected = 0;
									CVD_L9Bx_Set_for_Normal_Signal();
								}
							}
						}

					}
#endif
					/* On Brazil (PAL-M) weak RF Signal, AGC gain sometimes became high value result in white picture.
					   Disabling AGC is needed on this weak RF signal( No h-lock, high noise level )
					 */
					if( (g_CVD_Status_3CS.in_atv_tunning == FALSE) && (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm))
						CVD_L9Bx_AGC_Bypass_Function((UINT32)g_CVD_Status_3CS.avg_status_noise, (UINT32)g_CVD_Status_3CS.h_lock_flag, (UINT32)g_CVD_Status_3CS.no_signal_flag );

				}
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == CVD_STABLE_COUNT_2) {

#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
					if ( (lx_chip_rev() >= LX_CHIP_REV( L9, B0))&&(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
						if(vcr_detect_count >=  CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD)
							CVD_L9Bx_Set_Hstate_Max(3);
						else CVD_L9Bx_Set_Hstate_Max(5);
						vcr_detect_count = 0;
						gHstateMaxCounter = 0;
					}
#endif

					//				CVD_DEBUG("### CVD Same State Max 2 !!! ###\n");

#ifdef L9_AGC_BYPASS_WA_FOR_NOISY_SIGNAL
					avg_noise_level = cvd_noise_sum / (g_CVD_Status_3CS.cvd_lock_stable_count + 1);
					cvd_noise_sum = 0;	//
					stable_state2_count = 0;
					CVD_DEBUG("#avg noise level [0x%x]#\n", avg_noise_level);

					// for PERU Weak RF signal
					//for noisy signal , diable agc(agc_bypass) & set dcrestore gain to 1/8 for stable sync and AGC.
					if ( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
						// use long-time averaged value
						if( avg_noise_level >=  (CVD_L9B0_NOISE_MAX - 0x10) ) {
							if (g_CVD_Status_3CS.noisy_signal_detected == 0) {
								CVD_DEBUG("CVD Noisy RF Signal \n");
								// changed to noisy signal
								g_CVD_Status_3CS.noisy_signal_detected = 1;
								CVD_L9Bx_Set_for_Noisy_Signal();
							}
						}
					}
#endif
#ifdef L9_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST
					if(( lx_chip_rev() >= LX_CHIP_REV(L9,B0)) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
						CVD_OnOff_Chromalock_Ckill(0);
#endif
#ifdef L9_ADAPTIVE_BURST_GATE_END_MODE
					if ( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
						if((gVariance_Status_Cdto_Inc >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_0)&&(gAccumulated_Cordic_Freq_Value >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_1))
							Adaptive_Burst_Gate_Enable = 1;
						else if(gVariance_Status_Cdto_Inc <= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_3)
							Adaptive_Burst_Gate_Enable = 0;
						else
							Adaptive_Burst_Gate_Enable = 2;

						if((Adaptive_Burst_Gate_Enable == Prev_Adaptive_Burst_Gate_Enable)&&(Adaptive_Burst_Gate_Enable != 2))
						{
							CVD_L9Bx_Set_for_Burst_Gate_End_On_Noisy( g_SetColorSystemMain[CVD_STATE_PALm].reg_burst_gate_end_new , Adaptive_Burst_Gate_Enable);
#ifdef L9_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE
							CVD_L9Bx_AGC_Bypass(Adaptive_Burst_Gate_Enable);
#endif
						}
						//AFE_PRINT("AVERAGE CDTO_INC[%x] CORDIC_FREQ[%d] RESULT[%d]\n", gVariance_Status_Cdto_Inc, gAccumulated_Cordic_Freq_Value, Adaptive_Burst_Gate_Enable);
						gAdaptive_Burst_Gate_Counter = 0;
					}
#endif
#if 0
#ifdef L9_WA_FOR_EBS_STABLE_AGC
					// set reg_agc_half_en to '1', and reg_nstd_hysis to '0' for EBS field stream
					// set reg_agc_peak_cntl to '0', and reg_dcrestore_gain to '3' for stable AGC on NTSC RF
					if (( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
					{
						g_Stable_AGC_WA_for_EBS_Enabled = 1;
						CVD_L9Bx_Program_Color_System_PostJob2();
					}
#endif
#endif
#ifdef L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
					//Enable agc_peak_en for AWC test
					if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
						CVD_L9Bx_AGC_Peak_En_Control(1, g_CVD_Status_3CS.avg_status_noise, g_CVD_Status_3CS.avg_status_agc_gain);
					else
						CVD_L9Bx_AGC_Peak_En_Control(2, 0, 0);	// force on peak_en
#endif
#ifdef L9_VSYNC_CNTL_FOR_STABLE_VSYNC // disabled
					if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
						CVD_L9Bx_Set_for_Stable_Vsync(1);
					}
#endif


					g_CVD_Status_3CS.cvd_lock_stable_count++;
				}
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == CVD_STABLE_COUNT_1)
				{
					//					CVD_DEBUG("### CVD Same State Max 1 !!! ###\n");

					//won.hur : added chip selection for L9B0
					//@2011.08.24
					if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0))
					{

#ifdef L9_CHANGE_FIELD_DETECT_MODE_ON_DONG_GO_DONG_RAK
						if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
							CVD_L9Bx_Set_for_Field_Detect_Mode(1);
#endif
						CVD_L9Bx_Program_Color_System_PostJob(&g_SetColorSystemMain[g_CVD_Status_3CS.cvd_next_state]);
#ifdef L9_WA_FOR_EBS_STABLE_AGC
						// set reg_agc_half_en to '1', and reg_nstd_hysis to '0' for EBS field stream
						// set reg_agc_peak_cntl to '0', and reg_dcrestore_gain to '3' for stable AGC on NTSC RF
						// 120309 : modified not to execute SW workaround for stable AGC during ATV auto searching. This workaround sometimes makes channel skips.
						if (((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) || (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm)) && (g_CVD_Status_3CS.in_rf_mode == TRUE)  && (g_CVD_Status_3CS.in_atv_tunning == FALSE))
						{
							g_Stable_AGC_WA_for_EBS_Enabled = 1;
							CVD_L9Bx_Program_Color_System_PostJob2();
						}
#endif

#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
						if ( ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) || (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi) )&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
							//	CVD_DEBUG("Set hstate_fixed value to 1 \n");
							CVD_L9Bx_Set_Hstate_Fixed(1);
							if(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)
							{	CVD_L9Bx_Set_Hstate_Max(3);
								vcr_detect_count = 0;
							}
						}
#endif
#ifdef L9_ADAPTIVE_BURST_GATE_END_MODE
						if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
							gVariance_Status_Cdto_Inc = CVD_L9Bx_Differential_Status_Cdto_Inc_Value();
							gAccumulated_Cordic_Freq_Value = CVD_L9Bx_Read_Cordic_Freq_Value();
						}
#endif
					}

					g_CVD_Status_3CS.cvd_lock_stable_count++;
#ifdef CVD_CH42_SKIP_WORKAROUND
					CVD_Clamp_Current_Control(0);	// 1118 change clamp current to zero
#endif
					//120222 : setting agc_peak_en initial values
					// PALi & SECAM RF : initially off
					// NTSC & others : initially on
#ifdef L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
					if ((/* ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_SECAM) ||*/ (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi) )&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
						// for PAL system agc_peak_en should be '0' on no signal state.
						CVD_L9Bx_AGC_Peak_En_Control(0, 0, 0);	//force off peak_en
					}
					else
						CVD_L9Bx_AGC_Peak_En_Control(2, 0, 0);	//force on peak_en
#endif
					// Move CVD PQ setting function from DDI to Kernel
					if(1) {
						if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M_RF);
						}
						else if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_RF);
						}
						else if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_SECAM) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_SECAM);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_SECAM_RF);
						}
						else if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC443) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_443);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_443_RF);
						}
						else if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PAL60) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_60);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_60_RF);
						}
						else if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_M);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_M_RF);
						}
						else if ( g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALCn) {
							if(g_CVD_Status_3CS.in_rf_mode == TRUE)
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_NC);
							else
								CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_NC_RF);
						}
						else
							AFE_ERROR("ERROR Invalid Color system [%s][%d]\n", __func__, __LINE__);
					}

				}

				else if(g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_2)
				{
#ifdef L9_ADAPTIVE_BURST_GATE_END_MODE
					if ( ( lx_chip_rev() >= LX_CHIP_REV( L9, B0)) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
						gVariance_Status_Cdto_Inc += CVD_L9Bx_Differential_Status_Cdto_Inc_Value();
						gAccumulated_Cordic_Freq_Value += CVD_L9Bx_Read_Cordic_Freq_Value();
					}
#endif
#ifdef L9_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
					if ( (lx_chip_rev() >= LX_CHIP_REV( L9, B0))&&(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
						if(CVD_L9Bx_Read_VCR_Detected()) vcr_detect_count++;
					}

					if((lx_chip_rev() >= LX_CHIP_REV( L9, B0))&&(g_CVD_Status_3CS.cvd_lock_stable_count == 10))
					{
						if(vcr_detect_count+1 >= CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD>>2)
							CVD_L9Bx_Set_Hstate_Max(3);
						else CVD_L9Bx_Set_Hstate_Max(5);
					}

#endif
					g_CVD_Status_3CS.cvd_lock_stable_count++;
				}

				if(g_CVD_Status_3CS.cvd_lock_stable_count > CVD_STABLE_COUNT_1)
				{
					if (( g_CVD_Pattern_Detection_t.bEnable == TRUE) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
						CVD_L9Bx_Pattern_Detection(&g_CVD_Pattern_Detection_t );
#if 1
					//gogosing burst mag status check for color burst level test (color 틀어짐 대응) 2011.06.11
					//Apply cagc control for NTSC(color 틀어짐 대응) 2011.10.14
					if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
					{
						burst_mag_prev = burst_mag_next;
						burst_mag_next = CVD_L9Bx_Get_CVD_Burst_Mag_Flag(g_CVD_Status_3CS.cvd_color_system);

						if ( (burst_mag_next != burst_mag_prev)  )
						{
							//	CVD_DEBUG("burst_mag_prev = %d , burst_mag_next = %d \n",(int)burst_mag_prev,(int)burst_mag_next);
							CVD_L9Bx_Set_CVD_CAGC(burst_mag_next,&g_SetColorSystemMain[g_CVD_Status_3CS.cvd_color_system], g_CVD_Status_3CS.cvd_color_system);
							//CVD_DEBUG("################# CAGC changed gogosing ############### \n");
						}
					}
					else if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
					{
						//	burst_mag_prev = burst_mag_next;
						//	burst_mag_next = CVD_Get_CVD_Burst_Mag_Flag(g_CVD_Status_3CS.cvd_color_system);

						burst_mag_sum = 0;

						for(loop = 9;loop > 0;loop--) {
							burst_mag_array[loop] = burst_mag_array[loop-1] ;
							burst_mag_sum += burst_mag_array[loop];
						}

						if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0) )
							burst_mag_array[0] = CVD_L9Bx_Get_CVD_Burst_Mag_Value();

						burst_mag_sum += burst_mag_array[0];

						burst_mag_avg = burst_mag_sum / 10;


						//120127 : modified by kd.park
						//120131 : if pattern not found do not adjust cagc register
#if 0
						if( (burst_mag_avg > 0xbc0) )
#endif
							if( (burst_mag_avg > 0xbc0) || ( g_CVD_Pattern_Detection_t.pattern_found != 1)) {
								burst_mag_next = CVD_BURST_MAG_STATE_BIG;
								prev_burst_mag_avg = 0xbc0;
								cagc_target = g_SetColorSystemMain[CVD_STATE_NTSC].reg_saturation;
							}
							else if(burst_mag_avg < 0x280) {
								burst_mag_next = CVD_BURST_MAG_STATE_VERY_SMALL;
								prev_burst_mag_avg = 0x280;
								cagc_target = 0x20;
							}
							else {
								burst_mag_next = (burst_mag_avg / 0x17) + 0x5;
								if(burst_mag_next > g_SetColorSystemMain[CVD_STATE_NTSC].reg_saturation)
									burst_mag_next = g_SetColorSystemMain[CVD_STATE_NTSC].reg_saturation;
								cagc_target = burst_mag_next;
							}

						//CVD_DEBUG("burst_mag = [0x%x], burst_mag_avg = [0x%x], prev_burst_mag_avg = [0x%x], burst_mag_next [0x%x], burst_mag_prev[0x%x] \n",burst_mag_array[0], burst_mag_avg, prev_burst_mag_avg, burst_mag_next, burst_mag_prev);

						if ( ( ( (burst_mag_next >= 0x5) && ( abs(prev_burst_mag_avg - burst_mag_avg) > 0x80) )  \
									||  ( ( burst_mag_next < 5) && (burst_mag_next != burst_mag_prev) ) ) \
								&& (g_CVD_Status_3CS.cvd_lock_stable_count > (CVD_STABLE_COUNT_1 + 10 )) )
						{
							CVD_DEBUG("burst_mag_prev = 0x%x , burst_mag_next = 0x%x \n",burst_mag_prev,burst_mag_next);
							CVD_DEBUG("burst_mag_avg = 0x%x\n",burst_mag_avg);

							if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0))
								cagc_written = CVD_L9Bx_Get_CAGC_Value();

							CVD_DEBUG("cagc_written = 0x%x , cagc_target = 0x%x \n",cagc_written,cagc_target);

							if(cagc_written > cagc_target)
								burst_mag_next = cagc_written - 1;
							else if(cagc_written < cagc_target)
								burst_mag_next = cagc_written + 1;
							else {
								CVD_DEBUG("CAGC Target Reached !!! [0x%x]\n",cagc_written);
								prev_burst_mag_avg = burst_mag_avg;
								burst_mag_prev = burst_mag_next;
								burst_mag_next = cagc_written;
							}

							CVD_L9Bx_Set_CVD_CAGC(burst_mag_next,&g_SetColorSystemMain[g_CVD_Status_3CS.cvd_color_system], g_CVD_Status_3CS.cvd_color_system);
							//CVD_DEBUG("################# CAGC changed gogosing ############### \n");
						}

					}
					else
					{
						/*
						   burst_mag_prev=0;//pal 이외 시스템에서 초기화
						   burst_mag_next=0;
						 */
					}
#endif

				}
			}
		}
		// #10 	: Same State , but no signal
		//		:
		else
			g_CVD_Status_3CS.cvd_lock_stable_count = 0;

		//gMainCVD_State = g_CVD_Status_3CS.cvd_next_state;
#if 0
	//periodic reset of CS0/CS1 is needed???
	if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
	{
		CVD_L9Bx_swrst_CS( CVD_SEL_CS_CS0);
		CVD_L9Bx_swrst_CS( CVD_SEL_CS_CS1);
	}
#endif


	}

	return 0;
}

static CVD_STATE_T CVD_L9Bx_Check_Color_System_Support(LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	forced_color_system)
{
	CVD_STATE_T	system_ret = CVD_STATE_Default;

	// For user force color system
	if(forced_color_system == LX_COLOR_SYSTEM_NTSC_M)		// For Kor/US
		system_ret = CVD_STATE_NTSC;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_G)
		system_ret = CVD_STATE_PALi;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_NC)
		system_ret = CVD_STATE_PALCn;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_M)
		system_ret = CVD_STATE_PALm;
	else if(forced_color_system == LX_COLOR_SYSTEM_SECAM)
		system_ret = CVD_STATE_SECAM;
	else if(forced_color_system == LX_COLOR_SYSTEM_NTSC_443)
		system_ret = CVD_STATE_NTSC443;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_60)
		system_ret = CVD_STATE_PAL60;

	return system_ret;
}

int CVD_L9Bx_Set_Color_System_3CS(CVD_STATE_T cvd_next_state)
{
	switch(cvd_next_state)
	{
		case CVD_STATE_NTSC:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_NTSC;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_PAL60;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALm;
			break;

		case CVD_STATE_NTSC443:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_NTSC443;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_NTSC;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALm;
			break;

		case CVD_STATE_PALm:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PALm;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_PAL60;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_NTSC;
			break;

		case CVD_STATE_PAL60:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PAL60;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_NTSC;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALm;
			break;

		case CVD_STATE_PALi:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PALi;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_SECAM;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALCn;
			break;

		case CVD_STATE_PALCn:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PALCn;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_SECAM;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALi;
			break;

		case CVD_STATE_SECAM:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_SECAM;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_PALi;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALCn;
			break;

		default:
			AFE_PRINT("ERROR INVALID COLOR SYSTEM!!!\n");
			break;
	}

	CVD_DEBUG("Set Color System : CVD[%d], CS0[%d], CS1[%d]\n", g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cs0_color_system, g_CVD_Status_3CS.cs1_color_system);
	CVD_L9Bx_Program_Color_System_Main_Multi(&g_SetColorSystemMain[g_CVD_Status_3CS.cvd_color_system]);


	//won.hur : added chip selection for L9B0 migration
	if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0 ))
	{
		CVD_L9Bx_Program_Color_System_CS(CVD_SEL_CS_CS0, &g_SetColorSystemMain[g_CVD_Status_3CS.cs0_color_system]);
		CVD_L9Bx_Program_Color_System_CS(CVD_SEL_CS_CS1, &g_SetColorSystemMain[g_CVD_Status_3CS.cs1_color_system]);

		//111221 by kim.min for better color standard detection performance
		CVD_L9Bx_swrst_CS( CVD_SEL_CS_CS0);
		CVD_L9Bx_swrst_CS( CVD_SEL_CS_CS1);

	}

	return 0;
}

