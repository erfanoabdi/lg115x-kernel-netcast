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
 *  @date		2010-11-16
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <mach/irqs.h>
#include <linux/kthread.h>
#include <linux/signal.h>
#include <linux/semaphore.h>

#include "afe_drv.h"

#include "os_util.h"
//#include "hdmi_phy_reg.h"

#include "afe_cfg.h"
#ifdef INCLUDE_L8_CHIP_KDRV
//#include "vport_reg.h"
//#include "vport_reg_B0.h"
#endif

#include "cvd_hw.h"
#ifdef INCLUDE_L9_CHIP_KDRV
#include "l9/vport_reg_l9a0.h"
#include "l9/vport_reg_l9b0.h" // added by won.hur for L9B0
#include "l9/cvd_task_l9b0.h"
#include "l9/cvd_control_l9b0.h"
#endif
//#include "pe_dcm.h"
#include "h13/de_cvd_reg_h13bx.h"
#include "h13/de_cvd_reg_h13ax.h"
#include "h13/cvd_hw_h13a0.h"
#include "h13/cvd_hw_h13b0.h"
#include "h13/cvd_control_h13a0.h"
#include "h13/cvd_control_h13b0.h"

#include "h13/cvd_task_h13a0.h"
#include "h13/cvd_task_h13b0.h"


#include <asm/io.h>
#include <linux/slab.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	MAINCVD_TIMEOUT	150	// 1000 msec
#define	L9_CVD_TIMEOUT	50	// 1000 msec


#define ENABLE_CVD_THREAD				///<< Must define this to make CVD driver work.


#define CVD_STATE_TRANSITION_MAX	15

#define ENABLE_CVD_STATE_TRANSITION_LIMIT 1
#define ENABLE_CVD_INTERRUPT_CONTROL 0

#define CVD_FC_FOR_SECAM_LOW	190
#define CVD_FC_FOR_SECAM_HIGH	240
#define CVD_FC_FOR_PALCn_LOW	170
#define CVD_FC_FOR_PALCn_HIGH	220
//#define CVD_KERNEL_DEBUG

//#define DCRESTORE_ACCUM_WIDTH_INITIAL			0x25

// Workaround for chroma lost on brasil streams : 20120202

// moved to cvd_hw.h
//#define L9_FAST_3DCOMB_WORKAROUND

// Workaround for stable AGC on weak RF signal
//#define CVD_AGC_PEAK_CONTROL_WORKAROUND
//#define L9_ADAPTIVE_AGC_PEAK_NOMINAL_CONTROL
#define AGC_PEAK_NOMINAL_INITIAL_VALUE	0x30
#define AGC_PEAK_NOMINAL_DEFAULT_VALUE	0x0a

#define USE_REGISTER_VALUE_FOR_SYNC_STATES
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
//	function pointer
//void (*CVD_Program_Color_System_Main_Multi)(CVD_SET_SYSTEM_MAIN_T *pSet_system_t);
void (*CVD_Set_Picture_Enhancement)(BOOLEAN ycrdc_lcr_on, BOOLEAN cyrdc_lcr_on);
void (*CVD_SW_Reset)(LX_AFE_CVD_SELECT_T select_main_sub);
void (*CVD_Power_Down)(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN PowerOnOFF);
UINT8 (*CVD_Get_FC_Flag)(LX_AFE_CVD_SELECT_T select_main_sub);
#if 1 //gogosing burst mag status check for color burst level test (color Æ²¾îÁü ´ëÀÀ) 2011.06.11
UINT8 (*CVD_Get_CVD_Burst_Mag_Flag)(CVD_STATE_T	color_system);
//int (*CVD_Set_CVD_CAGC)(UINT8 state,CVD_SET_SYSTEM_MAIN_T *pSet_system_t, CVD_STATE_T	color_system);
#endif
UINT8 (*CVD_Get_Cordic_Freq)(LX_AFE_CVD_SELECT_T select_main_sub);
void (*CVD_Program_Color_System_Main)(CVD_SET_SYSTEM_MAIN_T set_system_t);

int (*CVD_Set_Source_Type)(UINT32 arg);
int (*CVD_Clamp_Current_Control)(UINT8 value);
int (*CVD_Force_Color_Kill)(UINT8 color_kill_enable);

int (*CVD_Set_Scart_Overlay)(BOOLEAN arg);
void (*CVD_Reg_Init)(LX_AFE_CVD_SELECT_T select_main_sub);
int (*CVD_Get_Scart_AR)(UINT32 arg);
void (*CVD_Print_Vport_Version)(void);
int (*CVD_Vport_Output)(UINT32 arg);
int (*CVD_Vport_Reg_Read)(UINT32 arg);
int (*CVD_Vport_Reg_Write)(UINT32 arg);
int (*CVD_Get_FB_Status)(UINT32 arg);
int (*CVD_Get_No_Signal_Flag)(void);
int (*CVD_Get_HLock_Flag)(void);
int (*CVD_Get_VLock_Flag)(void);
int (*CVD_Get_Vline_625_Flag)(void);
int	(*CVD_Get_PAL_Flag)(void);
int	(*CVD_Get_SECAM_Flag)(void);
int	(*CVD_Get_Chromalock_Flag)(void);
int	(*CVD_Get_Noise_Status)(void);
int	(*CVD_Get_NoBurst_Flag)(void);
int (*CVD_Reset_irisyc)(int enable);
int (*CVD_Reset_hdct)(int enable);
int (*CVD_Reset_cdct)(int enable);
int	(*CVD_Get_PAL_Flag_CS0)(void);
int	(*CVD_Get_SECAM_Flag_CS0)(void);
int	(*CVD_Get_Chromalock_Flag_CS0)(void);
UINT8 (*CVD_Get_FC_Flag_CS0)(void);
UINT8 (*CVD_Get_Cordic_Freq_CS0)(void);
int	(*CVD_Get_PAL_Flag_CS1)(void);
int	(*CVD_Get_SECAM_Flag_CS1)(void);
int	(*CVD_Get_Chromalock_Flag_CS1)(void);
UINT8 (*CVD_Get_FC_Flag_CS1)(void);
UINT8 (*CVD_Get_Cordic_Freq_CS1)(void);
/*
void (*CVD_Set_AAF_Params)(CVD_SET_AAF_T *pSet_aaf_t);
void (*CVD_Set_ADC_Params)(CVD_SET_CRES54MHZ_T *pSet_cresampler_t);
void (*CVD_Set_Cresampler_Params)(CVD_SET_CRES54MHZ_T *pSet_cresampler_t);
void (*CVD_Set_Dot_Crawl_Params)(CVD_SET_DOT_CRAWL_T *pSet_dotcrawl_t);
void (*CVD_Set_Cross_Color_Reducer)(CVD_SET_CROSS_COLOR_REDUCER_T *pSet_crosscolor_t);
void (*CVD_Set_Motion_Detector)(CVD_SET_MOTION_DETECTOR_T *pSet_motiondetector_t);
void (*CVD_Set_Global_Classifier)(   CVD_SET_GLOBAL_CLASSIFIER_T *pSet_globalclassifier);
void (*CVD_Set_Output_Delay)( CVD_SET_OUPUT_DELAY_T        	*pSet_outputdelay_t);
void (*CVD_Set_Output_Range)(CVD_SET_OUPUT_RANGE_T	*pSet_outputrange_t);
void (*CVD_Set_Blending)(CVD_SET_BLENDING_T	*pSet_blending);
*/
int	(*CVD_Read_fld_cnt_value)(UINT16 *pfld_hfcnt_value, UINT16 *pfld_lfcnt_value);
int (*CVD_Set_motion_mode)(UINT8	md_mode_value, UINT8 motion_mode_value) ;
int (*CVD_Channel_Power_Control)(UINT32 on_off) ;
int (*CVD_Reset_Clampagc)(void) ;
int (*CVD_Bypass_Control)(LX_AFE_CVD_BYPASS_CONTROL_T *cvd_bypass_control_t);

int (*CVD_Get_Vline_625_Reg)(void);	// Read user forced vline 625 value
//void (*CVD_Program_Color_System_PreJob)(CVD_SET_SYSTEM_MAIN_T *pSet_system_t);
int (*CVD_Set_Hstate_Max)(UINT32	hstate_max_value);
int (*CVD_OnOff_Chromalock_Ckill)(BOOLEAN bonoff);
int (*CVD_Set_for_Tunning)(BOOLEAN bEnable);
int (*CVD_Set_PQ_Mode)(LX_AFE_CVD_PQ_MODE_T cvd_pq_mode);
int (*CVD_Get_Crunky_Status)(LX_AFE_CVD_CK_T *pCK_Detection_t);
int (*CVD_Set_Scart_FB_En)(int fb_en_ctrl);
int (*CVD_OnOff_VDAC)(BOOLEAN bonoff);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
//extern volatile VPORT_RegAx_T *gVportRegAx;
//extern volatile VPORT_RegBx_T *gVportRegBx;
extern LX_CVD_REG_T *pVportRegCfg;

//extern LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T g_CVD_Color_System_Support;
//extern PE_DCM_DCE_HISTO_T _g_dce_histo_info[LX_PE_WIN_NUM];
//extern CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;
// Register Values for L9B0 
extern CVD_SET_SYSTEM_MAIN_T g_SetColorSystemMain[];


extern CVD_SET_SYSTEM_3CS_H13B0_T g_SetColorSystem_3CS_H13B0[];
extern CVD_SET_SYSTEM_3CS_H13A0_T g_SetColorSystem_3CS_H13A0[];




/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_L8_CHIP_KDRV
//volatile VPORT_RegAx_T *gVportRegAx;
//volatile VPORT_RegBx_T *gVportRegBx;
#endif
//		 VPORT_RegBx_T *gpRegVPORT;		// for shadow register

// H13A0 CVD Register Access
volatile DE_CVD_REG_H13Bx_T __iomem *gpRegCVD_H13Bx;
volatile DE_CVD_REG_H13Bx_T __iomem *gpRealRegCVD_H13Bx; 
#ifdef H13_3DCOMB_ERROR_WORKAROUND
volatile DE_CVD_REG_H13Bx_T __iomem *gpRegCVD_Backup_H13Bx;
#endif

volatile DE_CVD_REG_H13Ax_T __iomem *gpRegCVD_H13Ax;
volatile DE_CVD_REG_H13Ax_T __iomem *gpRealRegCVD_H13Ax; 

#ifdef INCLUDE_L9_CHIP_KDRV
volatile VPORT_L9B0_REG_T __iomem *gpRegVPORT_L9B0;	// won.hur(11.08.23) : L9B0 register added
volatile VPORT_L9B0_REG_T __iomem *gpRealRegVPORT_L9B0; // won.hur

volatile VPORT_L9A0_REG_T __iomem *gpRegVPORT_L9A0;
volatile VPORT_L9A0_REG_T __iomem *gpRealRegVPORT_L9A0;
#endif


BOOLEAN gCVDInitStatus = FALSE;

//UINT8 	gEnable_Monitor_3DCOMB_State = 0;

//spinlock_t 	cvd_lock;
//ULONG		cvd_irq_flags = 0;

#ifdef ENABLE_CVD_THREAD
struct task_struct	*stCVD_Thread;
//long	gPid_cvd_thread = -1;

int		gForce_thread_sleep = 1;
int		gCVD_thread_running = 0;
int		gWait_return = -1;

DECLARE_WAIT_QUEUE_HEAD(WaitQueue_CVD);
#endif
#ifdef	KDRV_CONFIG_PM
typedef	struct{
	BOOLEAN CVDInitStatus;
	LX_AFE_CVD_SELECT_T SelectMainSub;
}S_AFE_PM_DATA;

S_AFE_PM_DATA *gAfePmData;
#endif

OS_SEM_T	g_CVD_Sema;

//CVD_AGC_PEAK_CONTROL_T	g_CVD_AGC_Peak_Control;

CVD_STATUS_3CS_T	g_CVD_Status_3CS ;

//LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	g_CVD_Color_System_Support = LX_COLOR_SYSTEM_MULTI;
//int		gAutoProgramming	= 0;
CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;

//BOOLEAN g_CVD_RF_Input_Mode = FALSE;
//BOOLEAN		gNTSC_ONLY_Main = FALSE;
//BOOLEAN gPortChangeDetected = FALSE;

//CVD_STATE_T	gMainCVD_State	=	CVD_STATE_VideoNotReady; 
//CVD_STATE_T	gPrevious_Main_System	= CVD_STATE_VideoNotReady;;
//CVD_STATE_T	Current_State = CVD_STATE_VideoNotReady;
//CVD_STATE_T	Next_State = CVD_STATE_VideoNotReady;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef CVD_AGC_PEAK_CONTROL_WORKAROUND		//disabled
static int CVD_Adaptive_AGC_Peak_Control(CVD_AGC_PEAK_CONTROL_T *pCVD_AGC_Peak_Control );
#endif

static int MainCVD_Thread(void *data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef CVD_AGC_PEAK_CONTROL_WORKAROUND		//disabled
static UINT32	g_AGC_Peak_Nominal_Value = AGC_PEAK_NOMINAL_DEFAULT_VALUE;
#endif

CVD_ADAPTIVE_PEAK_NOMINAL_CONTROL_T g_CVD_AGC_Peak_Nominal_Control ;

static	int CVD_Set_Initial_Color_System(void);
/*========================================================================================
	Implementation Group
========================================================================================*/


int CVD_InitChipRev(void)
{
	if (lx_chip_rev() >= LX_CHIP_REV(H13, B0))
		{
	
			CVD_Set_PQ_Mode 	=	CVD_H13Bx_Set_PQ_Mode;
			CVD_Set_for_Tunning = CVD_H13Bx_Set_for_Tunning;
	//		CVD_Program_Color_System_Main_Multi =	CVD_H13Bx_Program_Color_System_Main_Multi;
			CVD_Set_Picture_Enhancement =		CVD_H13Bx_Set_Picture_Enhancement;
			CVD_SW_Reset		=						CVD_H13Bx_SW_Reset;
			CVD_Power_Down		=					CVD_H13Bx_Power_Down;
			CVD_Get_FC_Flag 	=					CVD_H13Bx_Get_FC_Flag;
			CVD_Get_CVD_Burst_Mag_Flag		=	CVD_H13Bx_Get_CVD_Burst_Mag_Flag;
	//		CVD_Set_CVD_CAGC			=	CVD_H13Bx_Set_CVD_CAGC;
			CVD_Get_Cordic_Freq 	=					CVD_H13Bx_Get_Cordic_Freq;
			//		CVD_Program_Color_System_Main		=		CVD_H13Bx_Program_Color_System_Main;
			CVD_Set_Source_Type 	=				CVD_H13Bx_Set_Source_Type;
			CVD_Clamp_Current_Control		=		CVD_H13Bx_Clamp_Current_Control;
			CVD_Force_Color_Kill		=				CVD_H13Bx_Force_Color_Kill;
	
			CVD_Set_Scart_Overlay		=			CVD_H13Bx_Set_Scart_Overlay;
			CVD_Reg_Init		=					CVD_H13Bx_Reg_Init;
			CVD_Get_Scart_AR		=				CVD_H13Bx_Get_Scart_AR;
			CVD_Print_Vport_Version 	=			CVD_H13Bx_Print_Vport_Version;
			CVD_Vport_Output		=				CVD_H13Bx_Vport_Output;
			CVD_Vport_Reg_Read		=				CVD_H13Bx_Vport_Reg_Read;
			CVD_Vport_Reg_Write 	=				CVD_H13Bx_Vport_Reg_Write;
			CVD_Get_FB_Status		=				CVD_H13Bx_Get_FB_Status;
			CVD_Get_No_Signal_Flag	=				CVD_H13Bx_Get_No_Signal_Flag;
			CVD_Get_HLock_Flag		=				CVD_H13Bx_Get_HLock_Flag;
			CVD_Get_VLock_Flag		=				CVD_H13Bx_Get_VLock_Flag;
			CVD_Get_Vline_625_Flag	=				CVD_H13Bx_Get_Vline_625_Flag;
			CVD_Get_PAL_Flag		=				CVD_H13Bx_Get_PAL_Flag;
			CVD_Get_SECAM_Flag		=				CVD_H13Bx_Get_SECAM_Flag;
			CVD_Get_Chromalock_Flag =				CVD_H13Bx_Get_Chromalock_Flag;
			CVD_Get_Noise_Status	=				CVD_H13Bx_Get_Noise_Status;
			CVD_Get_NoBurst_Flag	=				CVD_H13Bx_Get_NoBurst_Flag;
			CVD_Reset_irisyc			=			CVD_H13Bx_Reset_irisyc;
			CVD_Reset_hdct				=			CVD_H13Bx_Reset_hdct;
			CVD_Reset_cdct				=			CVD_H13Bx_Reset_cdct;
			/*
			   CVD_Set_AAF_Params			=			CVD_H13Bx_Set_AAF_Params;
			   CVD_Set_ADC_Params			=			CVD_H13Bx_Set_ADC_Params;
			   CVD_Set_Cresampler_Params	=			CVD_H13Bx_Set_Cresampler_Params;
			   CVD_Set_Dot_Crawl_Params =			CVD_H13Bx_Set_Dot_Crawl_Params;
			   CVD_Set_Cross_Color_Reducer	=			CVD_H13Bx_Set_Cross_Color_Reducer;
			   CVD_Set_Motion_Detector		=			CVD_H13Bx_Set_Motion_Detector;
			   CVD_Set_Global_Classifier	=			CVD_H13Bx_Set_Global_Classifier;
			   CVD_Set_Output_Delay 	=			CVD_H13Bx_Set_Output_Delay;
			   CVD_Set_Output_Range 	=			CVD_H13Bx_Set_Output_Range;
			   CVD_Set_Blending 		=			CVD_H13Bx_Set_Blending;
			 */
			CVD_Read_fld_cnt_value		=			CVD_H13Bx_Read_fld_cnt_value;
			CVD_Set_motion_mode 		=			CVD_H13Bx_Set_motion_mode;
			CVD_Channel_Power_Control	=			CVD_H13Bx_Channel_Power_Control;
			CVD_Reset_Clampagc	=			CVD_H13Bx_Reset_Clampagc;
			CVD_Get_PAL_Flag_CS0		=			CVD_H13Bx_Get_PAL_Flag_CS0;
			CVD_Get_SECAM_Flag_CS0		=			CVD_H13Bx_Get_SECAM_Flag_CS0;
			CVD_Get_Chromalock_Flag_CS0 	=			CVD_H13Bx_Get_Chromalock_Flag_CS0;
			CVD_Get_FC_Flag_CS0 		=			CVD_H13Bx_Get_FC_Flag_CS0;
			CVD_Get_Cordic_Freq_CS0 	=			CVD_H13Bx_Get_Cordic_Freq_CS0;
			CVD_Get_PAL_Flag_CS1		=			CVD_H13Bx_Get_PAL_Flag_CS1;
			CVD_Get_SECAM_Flag_CS1		=			CVD_H13Bx_Get_SECAM_Flag_CS1;
			CVD_Get_Chromalock_Flag_CS1 	=			CVD_H13Bx_Get_Chromalock_Flag_CS1;
			CVD_Get_FC_Flag_CS1 		=			CVD_H13Bx_Get_FC_Flag_CS1;
			CVD_Get_Cordic_Freq_CS1 	=			CVD_H13Bx_Get_Cordic_Freq_CS1;
			CVD_Bypass_Control			=			CVD_H13Bx_Bypass_Control;
			CVD_Get_Vline_625_Reg	=				CVD_H13Bx_Get_Vline_625_Reg;
	//		CVD_Program_Color_System_PreJob =	CVD_H13Bx_Program_Color_System_PreJob;
			CVD_Set_Hstate_Max			=			CVD_H13Bx_Set_Hstate_Max;
			CVD_OnOff_Chromalock_Ckill	=			CVD_H13Bx_OnOff_Chromalock_Ckill;
			CVD_Get_Crunky_Status	=			CVD_H13Bx_Get_Crunky_Status;
			CVD_Set_Scart_FB_En =			CVD_H13Bx_Set_Scart_FB_En;
			CVD_OnOff_VDAC	=			CVD_H13Bx_OnOff_VDAC;
		}

	else if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
	{

		CVD_Set_PQ_Mode		=	CVD_H13Ax_Set_PQ_Mode;
		CVD_Set_for_Tunning = CVD_H13Ax_Set_for_Tunning;
//		CVD_Program_Color_System_Main_Multi	=	CVD_H13Ax_Program_Color_System_Main_Multi;
		CVD_Set_Picture_Enhancement	=    	CVD_H13Ax_Set_Picture_Enhancement;
		CVD_SW_Reset		=                   	CVD_H13Ax_SW_Reset;
		CVD_Power_Down		=                 	CVD_H13Ax_Power_Down;
		CVD_Get_FC_Flag		=                	CVD_H13Ax_Get_FC_Flag;
		CVD_Get_CVD_Burst_Mag_Flag		=	CVD_H13Ax_Get_CVD_Burst_Mag_Flag;
//		CVD_Set_CVD_CAGC			=	CVD_H13Ax_Set_CVD_CAGC;
		CVD_Get_Cordic_Freq		=                	CVD_H13Ax_Get_Cordic_Freq;
		//		CVD_Program_Color_System_Main		=      	CVD_H13Ax_Program_Color_System_Main;
		CVD_Set_Source_Type		=            	CVD_H13Ax_Set_Source_Type;
		CVD_Clamp_Current_Control		=      	CVD_H13Ax_Clamp_Current_Control;
		CVD_Force_Color_Kill		=           	CVD_H13Ax_Force_Color_Kill;

		CVD_Set_Scart_Overlay		=          	CVD_H13Ax_Set_Scart_Overlay;
		CVD_Reg_Init		=                  	CVD_H13Ax_Reg_Init;
		CVD_Get_Scart_AR		=              	CVD_H13Ax_Get_Scart_AR;
		CVD_Print_Vport_Version		=        	CVD_H13Ax_Print_Vport_Version;
		CVD_Vport_Output		=              	CVD_H13Ax_Vport_Output;
		CVD_Vport_Reg_Read		=             	CVD_H13Ax_Vport_Reg_Read;
		CVD_Vport_Reg_Write		=            	CVD_H13Ax_Vport_Reg_Write;
		CVD_Get_FB_Status		=              	CVD_H13Ax_Get_FB_Status;
		CVD_Get_No_Signal_Flag	=				CVD_H13Ax_Get_No_Signal_Flag;
		CVD_Get_HLock_Flag		=				CVD_H13Ax_Get_HLock_Flag;
		CVD_Get_VLock_Flag		=				CVD_H13Ax_Get_VLock_Flag;
		CVD_Get_Vline_625_Flag	=				CVD_H13Ax_Get_Vline_625_Flag;
		CVD_Get_PAL_Flag		=				CVD_H13Ax_Get_PAL_Flag;
		CVD_Get_SECAM_Flag		=				CVD_H13Ax_Get_SECAM_Flag;
		CVD_Get_Chromalock_Flag	=				CVD_H13Ax_Get_Chromalock_Flag;
		CVD_Get_Noise_Status	=				CVD_H13Ax_Get_Noise_Status;
		CVD_Get_NoBurst_Flag	=				CVD_H13Ax_Get_NoBurst_Flag;
		CVD_Reset_irisyc			=			CVD_H13Ax_Reset_irisyc;
		CVD_Reset_hdct				=			CVD_H13Ax_Reset_hdct;
		CVD_Reset_cdct				=			CVD_H13Ax_Reset_cdct;
		/*
		   CVD_Set_AAF_Params			=			CVD_H13Ax_Set_AAF_Params;
		   CVD_Set_ADC_Params			=			CVD_H13Ax_Set_ADC_Params;
		   CVD_Set_Cresampler_Params	=			CVD_H13Ax_Set_Cresampler_Params;
		   CVD_Set_Dot_Crawl_Params	=			CVD_H13Ax_Set_Dot_Crawl_Params;
		   CVD_Set_Cross_Color_Reducer	=			CVD_H13Ax_Set_Cross_Color_Reducer;
		   CVD_Set_Motion_Detector		=			CVD_H13Ax_Set_Motion_Detector;
		   CVD_Set_Global_Classifier	=			CVD_H13Ax_Set_Global_Classifier;
		   CVD_Set_Output_Delay		=			CVD_H13Ax_Set_Output_Delay;
		   CVD_Set_Output_Range		=			CVD_H13Ax_Set_Output_Range;
		   CVD_Set_Blending			=			CVD_H13Ax_Set_Blending;
		 */
		CVD_Read_fld_cnt_value		=			CVD_H13Ax_Read_fld_cnt_value;
		CVD_Set_motion_mode			=			CVD_H13Ax_Set_motion_mode;
		CVD_Channel_Power_Control	=			CVD_H13Ax_Channel_Power_Control;
		CVD_Reset_Clampagc	=			CVD_H13Ax_Reset_Clampagc;
		CVD_Get_PAL_Flag_CS0		=			CVD_H13Ax_Get_PAL_Flag_CS0;
		CVD_Get_SECAM_Flag_CS0		=			CVD_H13Ax_Get_SECAM_Flag_CS0;
		CVD_Get_Chromalock_Flag_CS0		=			CVD_H13Ax_Get_Chromalock_Flag_CS0;
		CVD_Get_FC_Flag_CS0			=			CVD_H13Ax_Get_FC_Flag_CS0;
		CVD_Get_Cordic_Freq_CS0		=			CVD_H13Ax_Get_Cordic_Freq_CS0;
		CVD_Get_PAL_Flag_CS1		=			CVD_H13Ax_Get_PAL_Flag_CS1;
		CVD_Get_SECAM_Flag_CS1		=			CVD_H13Ax_Get_SECAM_Flag_CS1;
		CVD_Get_Chromalock_Flag_CS1		=			CVD_H13Ax_Get_Chromalock_Flag_CS1;
		CVD_Get_FC_Flag_CS1			=			CVD_H13Ax_Get_FC_Flag_CS1;
		CVD_Get_Cordic_Freq_CS1		=			CVD_H13Ax_Get_Cordic_Freq_CS1;
		CVD_Bypass_Control			=			CVD_H13Ax_Bypass_Control;
		CVD_Get_Vline_625_Reg	=				CVD_H13Ax_Get_Vline_625_Reg;
//		CVD_Program_Color_System_PreJob	=	CVD_H13Ax_Program_Color_System_PreJob;
		CVD_Set_Hstate_Max			=			CVD_H13Ax_Set_Hstate_Max;
		CVD_OnOff_Chromalock_Ckill	=			CVD_H13Ax_OnOff_Chromalock_Ckill;
		CVD_Get_Crunky_Status	=			CVD_H13Ax_Get_Crunky_Status;
		CVD_Set_Scart_FB_En	=			CVD_H13Ax_Set_Scart_FB_En;
		CVD_OnOff_VDAC	=			CVD_H13Ax_OnOff_VDAC;
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(L9, B0))	// won.hur @2011.08.24
	{
#ifdef INCLUDE_L9_CHIP_KDRV
		CVD_Set_PQ_Mode		=	CVD_L9Bx_Set_PQ_Mode;
		CVD_Set_for_Tunning = CVD_L9Bx_Set_for_Tunning;
//		CVD_Program_Color_System_Main_Multi	=	CVD_L9Bx_Program_Color_System_Main_Multi;
		CVD_Set_Picture_Enhancement	=    	CVD_L9Bx_Set_Picture_Enhancement;
		CVD_SW_Reset		=                   	CVD_L9Bx_SW_Reset;
		CVD_Power_Down		=                 	CVD_L9Bx_Power_Down;
		CVD_Get_FC_Flag		=                	CVD_L9Bx_Get_FC_Flag;
		CVD_Get_CVD_Burst_Mag_Flag		=	CVD_L9Bx_Get_CVD_Burst_Mag_Flag;
//		CVD_Set_CVD_CAGC			=	CVD_L9Bx_Set_CVD_CAGC;
		CVD_Get_Cordic_Freq		=                	CVD_L9Bx_Get_Cordic_Freq;
//		CVD_Program_Color_System_Main		=      	CVD_L9Bx_Program_Color_System_Main;
		CVD_Set_Source_Type		=            	CVD_L9Bx_Set_Source_Type;
		CVD_Clamp_Current_Control		=      	CVD_L9Bx_Clamp_Current_Control;
		CVD_Force_Color_Kill		=           	CVD_L9Bx_Force_Color_Kill;

		CVD_Set_Scart_Overlay		=          	CVD_L9Bx_Set_Scart_Overlay;
		CVD_Reg_Init		=                  	CVD_L9Bx_Reg_Init;
		CVD_Get_Scart_AR		=              	CVD_L9Bx_Get_Scart_AR;
		CVD_Print_Vport_Version		=        	CVD_L9Bx_Print_Vport_Version;
		CVD_Vport_Output		=              	CVD_L9Bx_Vport_Output;
		CVD_Vport_Reg_Read		=             	CVD_L9Bx_Vport_Reg_Read;
		CVD_Vport_Reg_Write		=            	CVD_L9Bx_Vport_Reg_Write;
		CVD_Get_FB_Status		=              	CVD_L9Bx_Get_FB_Status;
		CVD_Get_No_Signal_Flag	=				CVD_L9Bx_Get_No_Signal_Flag;
		CVD_Get_HLock_Flag		=				CVD_L9Bx_Get_HLock_Flag;
		CVD_Get_VLock_Flag		=				CVD_L9Bx_Get_VLock_Flag;
		CVD_Get_Vline_625_Flag	=				CVD_L9Bx_Get_Vline_625_Flag;
		CVD_Get_PAL_Flag		=				CVD_L9Bx_Get_PAL_Flag;
		CVD_Get_SECAM_Flag		=				CVD_L9Bx_Get_SECAM_Flag;
		CVD_Get_Chromalock_Flag	=				CVD_L9Bx_Get_Chromalock_Flag;
		CVD_Get_Noise_Status	=				CVD_L9Bx_Get_Noise_Status;
		CVD_Get_NoBurst_Flag	=				CVD_L9Bx_Get_NoBurst_Flag;
		CVD_Reset_irisyc			=			CVD_L9Bx_Reset_irisyc;
		CVD_Reset_hdct				=			CVD_L9Bx_Reset_hdct;
		CVD_Reset_cdct				=			CVD_L9Bx_Reset_cdct;
		/*
		CVD_Set_AAF_Params			=			CVD_L9Bx_Set_AAF_Params;
		CVD_Set_ADC_Params			=			CVD_L9Bx_Set_ADC_Params;
    	CVD_Set_Cresampler_Params	=			CVD_L9Bx_Set_Cresampler_Params;
    	CVD_Set_Dot_Crawl_Params	=			CVD_L9Bx_Set_Dot_Crawl_Params;
		CVD_Set_Cross_Color_Reducer	=			CVD_L9Bx_Set_Cross_Color_Reducer;
		CVD_Set_Motion_Detector		=			CVD_L9Bx_Set_Motion_Detector;
		CVD_Set_Global_Classifier	=			CVD_L9Bx_Set_Global_Classifier;
		CVD_Set_Output_Delay		=			CVD_L9Bx_Set_Output_Delay;
		CVD_Set_Output_Range		=			CVD_L9Bx_Set_Output_Range;
		CVD_Set_Blending			=			CVD_L9Bx_Set_Blending;
		*/
		CVD_Read_fld_cnt_value		=			CVD_L9Bx_Read_fld_cnt_value;
		CVD_Set_motion_mode			=			CVD_L9Bx_Set_motion_mode;
		CVD_Channel_Power_Control	=			CVD_L9Bx_Channel_Power_Control;
		CVD_Reset_Clampagc	=			CVD_L9Bx_Reset_Clampagc;
		CVD_Get_PAL_Flag_CS0		=			CVD_L9Bx_Get_PAL_Flag_CS0;
		CVD_Get_SECAM_Flag_CS0		=			CVD_L9Bx_Get_SECAM_Flag_CS0;
		CVD_Get_Chromalock_Flag_CS0		=			CVD_L9Bx_Get_Chromalock_Flag_CS0;
		CVD_Get_FC_Flag_CS0			=			CVD_L9Bx_Get_FC_Flag_CS0;
		CVD_Get_Cordic_Freq_CS0		=			CVD_L9Bx_Get_Cordic_Freq_CS0;
		CVD_Get_PAL_Flag_CS1		=			CVD_L9Bx_Get_PAL_Flag_CS1;
		CVD_Get_SECAM_Flag_CS1		=			CVD_L9Bx_Get_SECAM_Flag_CS1;
		CVD_Get_Chromalock_Flag_CS1		=			CVD_L9Bx_Get_Chromalock_Flag_CS1;
		CVD_Get_FC_Flag_CS1			=			CVD_L9Bx_Get_FC_Flag_CS1;
		CVD_Get_Cordic_Freq_CS1		=			CVD_L9Bx_Get_Cordic_Freq_CS1;
		CVD_Bypass_Control			=			CVD_L9Bx_Bypass_Control;
		CVD_Get_Vline_625_Reg	=				CVD_L9Bx_Get_Vline_625_Reg;
		//CVD_Program_Color_System_PreJob	=	CVD_L9Bx_Program_Color_System_PreJob;
		CVD_Set_Hstate_Max			=			CVD_L9Bx_Set_Hstate_Max;
		CVD_OnOff_Chromalock_Ckill	=			CVD_L9Bx_OnOff_Chromalock_Ckill;
		CVD_Get_Crunky_Status	=			CVD_L9Bx_Get_Crunky_Status;
		CVD_Set_Scart_FB_En			=			CVD_L9Bx_Set_Scart_FB_En;
		CVD_OnOff_VDAC				=			CVD_L9Bx_OnOff_VDAC;
#endif
	}
	else
	{
		return -1;
	}

	return 0;

}

/* CVD_Init 	: Initialize CVD registers to default value
					: Enables Kenel_threads(CVD main & CHB)
					: Enable CVD Interrupt 						*/
int CVD_Init(LX_AFE_CVD_SELECT_T select_main_sub)
{
	int result;

	result	= 0;


#ifdef	KDRV_CONFIG_PM
	gAfePmData = (S_AFE_PM_DATA *)kmalloc(sizeof(S_AFE_PM_DATA) , GFP_KERNEL);
	gAfePmData->CVDInitStatus = FALSE;
	gAfePmData->SelectMainSub = select_main_sub;
#endif

	if(select_main_sub != LX_CVD_MAIN)
		return -1;

	printk("gRegCfg [0x%x]\n", pVportRegCfg->vport_reg_base_addr);

	/*-----------------------------------------------------------------------------------
	 * [H13B0] CVD Register Base Address configuration
	 *----------------------------------------------------------------------------------*/
	if (lx_chip_rev() >= LX_CHIP_REV( H13, B0))
	{
		gpRealRegCVD_H13Bx = (volatile DE_CVD_REG_H13Bx_T __iomem *)ioremap(pVportRegCfg->vport_reg_base_addr , pVportRegCfg->vport_reg_size);
		if(gpRealRegCVD_H13Bx == NULL)
		{
			printk("ERROR : can't allocate for register\n");
			return -1;
		}
		gpRegCVD_H13Bx = (volatile DE_CVD_REG_H13Bx_T __iomem *)kmalloc(sizeof(DE_CVD_REG_H13Bx_T), GFP_ATOMIC);
		if(gpRegCVD_H13Bx == NULL)
		{
			printk("ERROR : can't allocate for shadow register\n");
			return -1;
		}
#ifdef H13_3DCOMB_ERROR_WORKAROUND
		gpRegCVD_Backup_H13Bx = (volatile DE_CVD_REG_H13Bx_T __iomem *)kmalloc(sizeof(DE_CVD_REG_H13Bx_T), GFP_ATOMIC);
		if(gpRegCVD_Backup_H13Bx == NULL)
		{
			printk("ERROR : can't allocate for shadow register\n");
			return -1;
		}
#endif
	}
	/*-----------------------------------------------------------------------------------
	 * [H13Ax] CVD Register Base Address configuration
	 *----------------------------------------------------------------------------------*/
	else if (lx_chip_rev() >= LX_CHIP_REV( H13, A0))
	{
		gpRealRegCVD_H13Ax = (volatile DE_CVD_REG_H13Ax_T __iomem *)ioremap(pVportRegCfg->vport_reg_base_addr , pVportRegCfg->vport_reg_size);
		if(gpRealRegCVD_H13Ax == NULL)
		{
			printk("ERROR : can't allocate for register\n");
			return -1;
		}
		gpRegCVD_H13Ax = (volatile DE_CVD_REG_H13Ax_T __iomem *)kmalloc(sizeof(DE_CVD_REG_H13Ax_T), GFP_ATOMIC);
		if(gpRegCVD_H13Ax == NULL)
		{
			printk("ERROR : can't allocate for shadow register\n");
			return -1;
		}


	}
	/*-----------------------------------------------------------------------------------
	 * [L9B0] CVD Register Base Address configuration
	 *----------------------------------------------------------------------------------*/
	else if (lx_chip_rev() >= LX_CHIP_REV( L9, B0)) // won.hur : added of L9B0 migration @2011.08.24
	{
#ifdef INCLUDE_L9_CHIP_KDRV
		gpRealRegVPORT_L9B0 = (volatile VPORT_L9B0_REG_T __iomem *)ioremap(pVportRegCfg->vport_reg_base_addr , pVportRegCfg->vport_reg_size);
		if(gpRealRegVPORT_L9B0 == NULL)
		{
			AFE_ERROR("ERROR : can't allocate for register\n");
			return -1;
		}
		gpRegVPORT_L9B0 = (volatile VPORT_L9B0_REG_T __iomem *)kmalloc(sizeof(VPORT_L9B0_REG_T), GFP_ATOMIC);
		if(gpRegVPORT_L9B0 == NULL)
		{
			AFE_ERROR("ERROR : can't allocate for shadow register\n");
			return -1;
		}
#endif

	}
	else
	{
	}
		//spin_lock_init(&cvd_lock);
	/*
		CVD_DEBUG("Real [0x%x], Reg [0x%x]\n", gpRealRegCVD_H13Ax, gpRegCVD_H13Ax);
		{
			UINT32 readAddr;
			UINT32  j;
			for(j =0x0;j<0x200;j+=4)
			{
				readAddr = (UINT32)gpRealRegCVD_H13Ax + j;
				CVD_DEBUG("Offset[0x%x], Real [0x%x]=value[0x%x]\n", j,  readAddr, REG_RD(readAddr) );
			}
		}
		*/

		CVD_InitChipRev();

		CVD_Power_Down(LX_CVD_MAIN, FALSE);
		CVD_Reg_Init(LX_CVD_MAIN);

		//Init Register to NTSC Mode
		CVD_Set_Initial_Color_System();
		/*
		CVD_Program_Color_System_Main_Multi(&g_SetColorSystemMain[CVD_STATE_NTSC]);

		if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0 ))  //won.hur : added for L9B0 migration
		{
			CVD_L9Bx_Program_Color_System_CS(CVD_SEL_CS_CS0, &g_SetColorSystemMain[CVD_STATE_PAL60]);
			CVD_L9Bx_Program_Color_System_CS(CVD_SEL_CS_CS1, &g_SetColorSystemMain[CVD_STATE_PALm]);
		}
		*/

#ifdef CVD_CH42_SKIP_WORKAROUND
		CVD_Clamp_Current_Control(0x3);
#endif

		CVD_SW_Reset(LX_CVD_MAIN);

	//Initialize CVD semaphore
	OS_InitMutex(&g_CVD_Sema, OS_SEM_ATTR_DEFAULT);


#ifdef ENABLE_CVD_THREAD

			stCVD_Thread = kthread_create( MainCVD_Thread, (void*)NULL, "cvd_thread");

			if(stCVD_Thread)
			{
				wake_up_process(stCVD_Thread);
	//			gCVD_thread_running = 1;
				AFE_PRINT("CVD Thread [%d]\n", stCVD_Thread->pid);
			}


			else
			{
				AFE_ERROR("CVD Thread Already Created\n");
			}

#endif

	CVD_Power_Down(LX_CVD_SUB, FALSE);
#if 0
	if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0 ) )	// won.hur : added for L9B0 migration @2011.08.24
	{
		VPORT_L9B0_Wr(cvd_intr1_enable0, L9_CVD_INTERRUPT_MASK);
		VPORT_L9B0_WrFL(cvd_intr1_enable0);
	}
	//Enable CVD Interrupt (No Signal, VLock, HLock)
	//gVportReg->intr_vp1_enable.intr_vp1_enable |= L8_MAIN_CVD_INTERRUPT_MASK;
	// TODO : dws
	// L9A0 has two cvd interrupt. One is for CVD main & the other is for VBI.
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, A0 ) )
	{
		//VPORT_L9A0_RdFL(cvd_intr1_enable0);
		VPORT_L9A0_Wr(cvd_intr1_enable0, L9_CVD_INTERRUPT_MASK);
		VPORT_L9A0_WrFL(cvd_intr1_enable0);
	}

	if (!gCVDInitStatus)
	{
		result = request_irq(L9_IRQ_CVD_BCPU, (irq_handler_t)CVD_L9_IRQ_Handler, 0, "CVD", NULL);

		if(result)
		{
			AFE_PRINT("!!! CVD Request IRQ Failed : return[%d]\n", result);
			return -1;
		}
		gCVDInitStatus = TRUE;
#ifdef	KDRV_CONFIG_PM
		gAfePmData->CVDInitStatus = TRUE;
#endif
	}
#endif

	CVD_Print_Vport_Version();

	return 0;
}

void CVD_UnInit(void)
{
	if(gCVDInitStatus)
	{
		free_irq(L9_IRQ_CVD_BCPU, NULL);
		gCVDInitStatus = FALSE;
#ifdef	KDRV_PM_CONFIG
		kfree(gAfePmData);
#endif
	}

}


int CVD_Set_NTSC_Only(UINT32 arg)
{
	LX_AFE_VIDEO_SYSTEM_INFO_T system_info;

	if (copy_from_user(&system_info, (void __user *)arg, sizeof(LX_AFE_VIDEO_SYSTEM_INFO_T)))
	{
		return -1;
	}

	if(system_info.cvd_video_system == LX_COLOR_SYSTEM_NTSC_M)
	{
		AFE_PRINT("############ Setting NTSC ONLY MODE ##################\n");
		g_CVD_Status_3CS.cvd_ntsc_only_mode = TRUE;
	}
	else
		g_CVD_Status_3CS.cvd_ntsc_only_mode = FALSE;

	return 0;
}


static int MainCVD_Thread(void *data)
{
	while(1)
	{
		CVD_THREAD_DEBUG("gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);

		if(gForce_thread_sleep > 0)
		{
			CVD_THREAD_DEBUG("User force sleep CVD Thread\n");
			gForce_thread_sleep = 0;
			gCVD_thread_running = 0;
			CVD_THREAD_DEBUG("CVD Sleep : gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);
			interruptible_sleep_on(&WaitQueue_CVD);

			// added : in case CVD power off/on h/v unlock sometimes do not occur.
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoReadyToDetect;
		//	g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
		//	g_CVD_Status_3CS.cvd_prev_color_system = CVD_STATE_VideoNotReady;

			gCVD_thread_running = 1;
			CVD_THREAD_DEBUG("CVD Wakeup : gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);
			//gWait_return = wait_event_interruptible(WaitQueue_CVD, gForce_thread_sleep>0);
		}

		if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
		{
			CVD_H13Bx_Task_3cdetect();
		
		}
		else if (lx_chip_rev() >= LX_CHIP_REV(H13, A0))
			CVD_H13Ax_Task_3cdetect();
#ifdef INCLUDE_L9_CHIP_KDRV
		else
			CVD_L9Bx_Task_3cdetect();
#endif

		OS_MsecSleep(L9_CVD_TIMEOUT);
	}

	return 0;
}


int CVD_Start_Timer(UINT32 arg)
{
#ifdef ENABLE_CVD_THREAD
	if(gCVD_thread_running > 0)
		CVD_DEBUG("CVD Thread already running !!!\n");
	else
	{
		gForce_thread_sleep = 0;
		wake_up_interruptible(&WaitQueue_CVD);
		CVD_DEBUG("Starting CVD Thread\n");
	}

	return 0;
#endif

}

int CVD_Stop_Timer(UINT32 arg)
{
#ifdef ENABLE_CVD_THREAD
		CVD_DEBUG("Stopping CVD Thread\n");
		gForce_thread_sleep = 1;

	return 0;
#endif
}

int CVD_Program_Color_System(UINT32 arg)
{
	LX_AFE_CVD_PROGRAM_COLOR_SYSTEM_T program_color_system_t;

	if (copy_from_user(&program_color_system_t, (void __user *)arg, sizeof(LX_AFE_CVD_PROGRAM_COLOR_SYSTEM_T)))
	{
		return -EFAULT;
	}

	if(program_color_system_t.color_system >= LX_NON_STANDARD ) return -1;

	if( lx_chip_rev( ) >= LX_CHIP_REV(H13,B0) )
		CVD_H13Bx_Set_Color_System_3CS(program_color_system_t.color_system);
	else if( lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
		CVD_H13Ax_Set_Color_System_3CS(program_color_system_t.color_system);
#ifdef INCLUDE_L9_CHIP_KDRV
	else 
		CVD_L9Bx_Set_Color_System_3CS(program_color_system_t.color_system);
#endif

	//gMainCVD_State = program_color_system_t.color_system;
	CVD_DEBUG("CVD Main : Program Color System to [%d]\n", program_color_system_t.color_system);

	return 0;
}

#ifdef	KDRV_CONFIG_PM
int CVD_RunSuspend(void)
{
	if (!gAfePmData->CVDInitStatus)
		return 0;

	return 0;
}

int CVD_RunResume(void)
{

	if (!gAfePmData->CVDInitStatus)
		return 0;

	//ALL_Power_Down();
	CVD_Power_Down(LX_CVD_MAIN, FALSE);
	CVD_Reg_Init(LX_CVD_MAIN);
	//Init Register to NTSC Mode
	CVD_Program_Color_System_Main_Multi(&g_SetColorSystemMain[CVD_STATE_NTSC]);
	CVD_SW_Reset(LX_CVD_MAIN);
	//Program_Color_System_Main_tmp();

	return 0;
}

#endif


int CVD_Set_SW_3DCOMB_Control(UINT32 arg)
{
	return 0;
}

int CVD_Set_Source_Type_Control(UINT32 arg)
{

	LX_AFE_CVD_SET_INPUT_T	cvd_input_info;
	static LX_AFE_CVD_SET_INPUT_T	prev_cvd_input_info = { LX_CVD_MAX_NUM, LX_CVD_INPUT_SOURCE_NUM, LX_AFE_CVBS_NONE, LX_AFE_CVBS_NONE, LX_CVD_INPUT_SOURCE_ATTRIBUTE_NUM} ;

	//AFE_PRINT("Entered CVD_Set_Source_Type_Control\n");

	if (copy_from_user(&cvd_input_info, (void __user *)arg, sizeof(LX_AFE_CVD_SET_INPUT_T)))
	{
		AFE_PRINT("Error return at CVD_Set_Source_Type_Control\n");
		return -1;
	}

	if( (cvd_input_info.cvd_main_sub == prev_cvd_input_info.cvd_main_sub) && (cvd_input_info.cvd_input_source_type == prev_cvd_input_info.cvd_input_source_type) && (cvd_input_info.cvbs_input_port == prev_cvd_input_info.cvbs_input_port) && (cvd_input_info.cvd_input_source_attribute == prev_cvd_input_info.cvd_input_source_attribute))  // Same Input Setting.
	{
		AFE_PRINT("CVD Set Source Type to Same Port !!!!????\n");
		return 0;
	}
	else
		memcpy (&prev_cvd_input_info, &cvd_input_info, sizeof(LX_AFE_CVD_SET_INPUT_T)) ;	// Save Current Port Settings.

	CVD_Set_Source_Type(arg);

	//		AFE_PRINT("Main CVD input\n");
	if(cvd_input_info.cvd_input_source_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF)
	{
		CVD_DEBUG("CVD : RF Input Mode\n");
		g_CVD_Status_3CS.in_rf_mode = TRUE;
	}
	else
	{
		CVD_DEBUG("CVD : AV Input Mode\n");
		g_CVD_Status_3CS.in_rf_mode = FALSE;
	}

//	g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoNotReady;
//	g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
//	g_CVD_Status_3CS.cvd_prev_color_system = CVD_STATE_VideoNotReady;		//121228 Added 
	g_CVD_Status_3CS.port_change_detected = TRUE;

	return 0;

}

int CVD_Get_States_Detail(UINT32 arg)
{
	LX_AFE_CVD_STATES_DETAIL_T	cvd_states_detail_t;
	//UINT32 status_reg;

	if( lx_chip_rev( ) >= LX_CHIP_REV(H13,B0) )
		CVD_H13Bx_Get_Reg_States_Detail(&cvd_states_detail_t);
	else if( lx_chip_rev( ) >= LX_CHIP_REV(H13,A0) )
		CVD_H13Ax_Get_Reg_States_Detail(&cvd_states_detail_t);
#ifdef INCLUDE_L9_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) )
		CVD_L9Bx_Get_Reg_States_Detail(&cvd_states_detail_t);
#endif

	CVD_Read_fld_cnt_value(&cvd_states_detail_t.hfcnt_value, &cvd_states_detail_t.lfcnt_value);
	cvd_states_detail_t.MainCVD_State = g_CVD_Status_3CS.cvd_color_system;
	cvd_states_detail_t.Current_State = g_CVD_Status_3CS.cvd_color_system;
	cvd_states_detail_t.Next_State = g_CVD_Status_3CS.cvd_next_state;


	cvd_states_detail_t.CVD_Color_System = g_CVD_Status_3CS.cvd_color_system;
	cvd_states_detail_t.CS0_Color_System = g_CVD_Status_3CS.cs0_color_system;
	cvd_states_detail_t.CS1_Color_System = g_CVD_Status_3CS.cs1_color_system;
	cvd_states_detail_t.color_system_support = g_CVD_Status_3CS.color_system_support;

	cvd_states_detail_t.motion_diff = g_CVD_Pattern_Detection_t.global_motion_diff;
	cvd_states_detail_t.pattern_found = g_CVD_Pattern_Detection_t.pattern_found;
	cvd_states_detail_t.tunning_mode	= g_CVD_Status_3CS.in_atv_tunning;
	cvd_states_detail_t.lock_stable_count	= g_CVD_Status_3CS.cvd_lock_stable_count;
	cvd_states_detail_t.no_signal_count	= g_CVD_Status_3CS.cvd_no_signal_count;
	cvd_states_detail_t.black_level	= g_CVD_Status_3CS.cvd_black_level;

	if (copy_to_user((UINT32*)arg, (UINT32*)&cvd_states_detail_t, sizeof(LX_AFE_CVD_STATES_DETAIL_T)))
	{
		return -1;
	}

	return 0;
}


int CVD_Null_Function(void)
{
	return 0;
}

int CVD_Test_Program(LX_AFE_CVD_TEST_PARAM_T *stCVD_Test_Param)
{
	int ret = 0;

	switch(stCVD_Test_Param -> item_to_test)
	{
		case CVD_TEST_ENABLE_3DCOMB_STATE_PRINT:
			break;
		case CVD_TEST_HSTATEMAX_WRITE:
			CVD_Set_Hstate_Max(stCVD_Test_Param->hstate_max_value);
			break;
		case CVD_TEST_AGC_PEAK_NOMINAL:
			/*
			g_CVD_AGC_Peak_Control.bEnable = 			stCVD_Test_Param->agc_peak_enable;
			g_CVD_AGC_Peak_Control.white_ratio_th = 	stCVD_Test_Param->agc_pean_white_ratio_th;
			g_CVD_AGC_Peak_Control.white_frame_max_th = stCVD_Test_Param->agc_pean_white_frame_max_th;
			g_CVD_AGC_Peak_Control.white_frame_on = 	stCVD_Test_Param->agc_pean_white_frame_on;
			g_CVD_AGC_Peak_Control.white_frame_off = 	stCVD_Test_Param->agc_pean_white_frame_off;
			g_CVD_AGC_Peak_Control.print_en = 			stCVD_Test_Param->agc_pean_print_en;
			g_CVD_AGC_Peak_Nominal_Control.bEnable 				= stCVD_Test_Param->agc_peak_enable ;
			g_CVD_AGC_Peak_Nominal_Control.tnr_x_avg_t_th 		= stCVD_Test_Param->agc_peak_x_avg_t_th;
			g_CVD_AGC_Peak_Nominal_Control.tnr_x_avg_s_th 		= stCVD_Test_Param->agc_peak_x_avg_s_th;
			g_CVD_AGC_Peak_Nominal_Control.tpd_s_status_th 		= stCVD_Test_Param->agc_peak_s_staus_th;
			g_CVD_AGC_Peak_Nominal_Control.pattern_frame_max_th = stCVD_Test_Param->agc_peak_white_frame_max_th ;
			g_CVD_AGC_Peak_Nominal_Control.pattern_frame_on 	= stCVD_Test_Param->agc_peak_white_frame_on ;
			g_CVD_AGC_Peak_Nominal_Control.pattern_frame_off 	= stCVD_Test_Param->agc_peak_white_frame_off ;
			g_CVD_AGC_Peak_Nominal_Control.noise_th			 	= stCVD_Test_Param->agc_peak_noise_th ;
			g_CVD_AGC_Peak_Nominal_Control.print_en 			= stCVD_Test_Param->agc_peak_print_en ;
			*/
			break;
		case CVD_TEST_STABLE_SYNC_MODE:
			if ( lx_chip_rev() >= LX_CHIP_REV( H13, B0 )) {
				CVD_H13Bx_Enable_Stable_Sync_Mode(stCVD_Test_Param->stable_sync_value);		//for RF nosignal (dcrestore_lpf_en ON)
			}
			break;
		case CVD_TEST_COMB2D_ONLY:
			if ( lx_chip_rev() >= LX_CHIP_REV( H13, B0 )) {
				CVD_H13Bx_Comb2d_Only_Test(1, stCVD_Test_Param->comb2d_only_test_enable, stCVD_Test_Param->comb2d_only_on_time, \
						stCVD_Test_Param->comb2d_only_off_time, stCVD_Test_Param->comb2d_only_md_on_time, stCVD_Test_Param->comb2d_only_md_off_time);
			}
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}

void CVD_Get_Timing_Info(UINT32 arg)
{
	LX_AFE_CVD_TIMING_INFO_T	timing_info;
	CVD_STATE_T	cvd_state;

	if (copy_from_user(&timing_info, (void __user *)arg, sizeof(LX_AFE_CVD_TIMING_INFO_T)))
	{
		return;
	}
	cvd_state = g_CVD_Status_3CS.cvd_color_system;

	switch(cvd_state)
	{
		case CVD_STATE_NTSC:
			timing_info.cvd_standard = LX_NTSC_M;
			timing_info.u16_VFreq = 599;
			break;
		case CVD_STATE_NTSC443:
			timing_info.cvd_standard = LX_NTSC_443;
			timing_info.u16_VFreq = 599;
			break;
		case CVD_STATE_PALi:
			timing_info.cvd_standard = LX_PAL_BG;
			timing_info.u16_VFreq = 500;
			break;
		case CVD_STATE_PALm:
			timing_info.cvd_standard = LX_PAL_M;
			timing_info.u16_VFreq = 599;
			break;
		case CVD_STATE_PALCn:
			timing_info.cvd_standard = LX_PAL_CN;
			timing_info.u16_VFreq = 500;
			break;
		case CVD_STATE_PAL60:
			timing_info.cvd_standard = LX_PAL_60;
			timing_info.u16_VFreq = 599;
			break;
		case CVD_STATE_SECAM:
			timing_info.cvd_standard = LX_SECAM;
			timing_info.u16_VFreq = 500;
			break;
		default:
			timing_info.cvd_standard = LX_NON_STANDARD;//gogosing
			if (CVD_Get_Vline_625_Reg())	// 625 line : 50Hz System
				timing_info.u16_VFreq = 500;
			else
				timing_info.u16_VFreq = 599;
			break;
	}

	if( g_CVD_Status_3CS.vline_625_stable )		// stable 50Hz
		timing_info.u16_VFreq_Stable = 500;
	else
		timing_info.u16_VFreq_Stable = 599;
	/*
	//Instead of reading input VFreq., read forced VFreq. of CVD to determine CVD's running VFreq.
	//if (CVD_Get_Vline_625_Flag())	// 625 line : 50Hz System
	if (CVD_Get_Vline_625_Reg())	// 625 line : 50Hz System
			timing_info.u16_VFreq = 500;
	else
			timing_info.u16_VFreq = 599;
			*/

	if (copy_to_user((UINT32*)arg, (UINT32*)&timing_info, sizeof(LX_AFE_CVD_TIMING_INFO_T)))
	{
		return;
	}
}
int CVD_Get_States(UINT32 arg)
{
	LX_AFE_CVD_STATES_INFO_T	cvd_states_info;
	//UINT32 status_reg;

	if (copy_from_user(&cvd_states_info, (void __user *)arg, sizeof(LX_AFE_CVD_STATES_INFO_T)))
	{
		return -1;
	}

#ifdef USE_REGISTER_VALUE_FOR_SYNC_STATES
	/* Returns Current Sync Register values(NOT the status of CVD thread) */

	cvd_states_info.cvd_status =0;

	if(CVD_Get_No_Signal_Flag())
	{
		//110414 No_Signal_Flag is not working well
		cvd_states_info.cvd_status |= LX_NO_SIGNAL;
		//		CVD_ClampAGC_OnOff(0); // agc off on No signal for ch42 no signal workaround
	}
	if(CVD_Get_HLock_Flag())
		cvd_states_info.cvd_status |= LX_HLOCK;
	if(CVD_Get_VLock_Flag())
		cvd_states_info.cvd_status |= LX_VLOCK;
	if(CVD_Get_Chromalock_Flag())
		cvd_states_info.cvd_status |= LX_CHROMALOCK;
	if(CVD_Get_Vline_625_Flag())
		cvd_states_info.cvd_status |= LX_625LINES_DETECTED;

#else
	/* Returns Sync Status of CVD thread */
	if(g_CVD_Status_3CS.cvd_color_system < CVD_STATE_VideoNotReady)
		cvd_states_info.cvd_status = LX_HLOCK|LX_VLOCK;
	else
		cvd_states_info.cvd_status = LX_NO_SIGNAL;

#endif
	if (copy_to_user((UINT32*)arg, (UINT32*)&cvd_states_info, sizeof(LX_AFE_CVD_STATES_INFO_T)))
	{
		return -1;
	}

	return 0;
}

int CVD_Set_Color_System(UINT32 arg)
{
	LX_AFE_VIDEO_SYSTEM_INFO_T system_info;

	if (copy_from_user(&system_info, (void __user *)arg, sizeof(LX_AFE_VIDEO_SYSTEM_INFO_T)))
	{
		return -1;
	}

	if(system_info.cvd_video_system <= LX_COLOR_SYSTEM_MULTI)
	{
		g_CVD_Status_3CS.color_system_support = system_info.cvd_video_system;
		CVD_DEBUG("### Setting Color System to [0x%x] ###\n", g_CVD_Status_3CS.color_system_support);
	}
	else
	{
		CVD_DEBUG("### Invalid Color System [%d] ###\n", system_info.cvd_video_system);
		return -1;
	}

	return 0;
}

/**
 * @brief Initialize Color System Related Registers to NTSC System
 *
 * @return 
 */
int CVD_Set_Initial_Color_System(void)
{
	
	g_CVD_Status_3CS.noisy_signal_detected = 0;
	g_CVD_Status_3CS.no_color_detected = 0;

	g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoNotReady;
	g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
	g_CVD_Status_3CS.cvd_prev_color_system = CVD_STATE_VideoNotReady;
	
	g_CVD_Status_3CS.in_atv_tunning = 0;
	g_CVD_Status_3CS.color_system_support =  LX_COLOR_SYSTEM_MULTI;
	
	g_CVD_Status_3CS.in_rf_mode = FALSE;
	g_CVD_Status_3CS.prev_av_rf_mode = TRUE;
	g_CVD_Status_3CS.port_change_detected = FALSE;
	g_CVD_Status_3CS.cvd_ntsc_only_mode = FALSE;
	g_CVD_Status_3CS.cvd_lock_stable_count = 0;
	g_CVD_Status_3CS.cvd_no_signal_count = 0;
	
	g_CVD_Status_3CS.cvd_black_level = LX_AFE_CVD_BLACK_LEVEL_AUTO;
	g_CVD_Status_3CS.vline_625_stable = 1;
	//Init Register to NTSC Mode
		if ( lx_chip_rev() >= LX_CHIP_REV( H13, B0 )) {
	//		CVD_H13Bx_Program_Color_System_buffer_only(&g_SetColorSystem_3CS[CVD_STATE_NTSC]);
			CVD_H13Bx_Program_Color_System_Main_Multi(&g_SetColorSystem_3CS_H13B0[CVD_STATE_NTSC]);
			CVD_H13Bx_Program_Color_System_CS(CVD_SEL_CS_CS0, &g_SetColorSystem_3CS_H13B0[CVD_STATE_PAL60]);
			CVD_H13Bx_Program_Color_System_CS(CVD_SEL_CS_CS1, &g_SetColorSystem_3CS_H13B0[CVD_STATE_PALm]);
	
			CVD_H13Bx_Init_Global_Params();
		}

	else if ( lx_chip_rev() >= LX_CHIP_REV( H13, A0 )) {
//		CVD_H13Ax_Program_Color_System_buffer_only(&g_SetColorSystem_3CS[CVD_STATE_NTSC]);
		CVD_H13Ax_Program_Color_System_Main_Multi(&g_SetColorSystem_3CS_H13A0[CVD_STATE_NTSC]);
		CVD_H13Ax_Program_Color_System_CS(CVD_SEL_CS_CS0, &g_SetColorSystem_3CS_H13A0[CVD_STATE_PAL60]);
		CVD_H13Ax_Program_Color_System_CS(CVD_SEL_CS_CS1, &g_SetColorSystem_3CS_H13A0[CVD_STATE_PALm]);

		CVD_H13Ax_Init_Global_Params();
	}
#ifdef INCLUDE_L9_CHIP_KDRV
	else {	// For L9B0

		CVD_L9Bx_Program_Color_System_Main_Multi(&g_SetColorSystemMain[CVD_STATE_NTSC]);

		CVD_L9Bx_Program_Color_System_CS(CVD_SEL_CS_CS0, &g_SetColorSystemMain[CVD_STATE_PAL60]);
		CVD_L9Bx_Program_Color_System_CS(CVD_SEL_CS_CS1, &g_SetColorSystemMain[CVD_STATE_PALm]);

		CVD_L9Bx_Init_Global_Params();
	}
#endif

	AFE_PRINT("CVD Init Color System Ended\n");

	return 0;

}

/**
 * @brief Set CVD Black Level
 *
 * @return 
 */
int CVD_Set_Black_Level(LX_AFE_CVD_BLACK_LEVEL_T cvd_black_level)
{
	
	g_CVD_Status_3CS.cvd_black_level = cvd_black_level;

	return 0;

}

int CVD_H13Bx_Backup_CVD_Registers(int backup)
{
#ifdef H13_3DCOMB_ERROR_WORKAROUND
	if (lx_chip_rev() >= LX_CHIP_REV(H13, B0))
	{
		if(backup)
			memcpy( (void *)gpRegCVD_Backup_H13Bx, (void *)gpRealRegCVD_H13Bx, sizeof(DE_CVD_REG_H13Bx_T) );
		else	// Restore
			memcpy( (void *)gpRealRegCVD_H13Bx, (void *)gpRegCVD_Backup_H13Bx, sizeof(DE_CVD_REG_H13Bx_T) );
	}
#endif

	return 0;
}

