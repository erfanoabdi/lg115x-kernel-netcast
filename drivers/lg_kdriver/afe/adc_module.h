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


/*! \file ADC_module.h
 * \brief VPORT ADC module header
 */

#ifndef ADC_MODULE
#define ADC_MODULE


#include "base_types.h"
 /*
 	define
 */
//#define USE_ADC_TIMER

#define	INPUT_SIGNAL_INFORM_REPEAT	4	// should be pow by 2
#define	INPUT_SIGNAL_INFORM_REPEAT_POW	2	// should be pow by 2

#define	TABLE_COUNT		275	
 
#define	FREQ_CONV_HZ	240000



/*
	Device inform
*/


/*
	structure define
*/
typedef struct 
{
	unsigned long	ext_vsize;
	unsigned long	vd_vsize;
	unsigned long	vd_hsize;
	unsigned long	polarity;
}S_VIDEO_SIZE_INFORM;


typedef struct
{
	unsigned int extau_up;
	unsigned int extau_down;
	unsigned int extau_left;
	unsigned int extau_right;

	float extau_up_offset;
	float extau_left_offset;
}ST_EXTAU;

typedef struct{
	struct work_struct	ifm;
	struct work_struct	ibd;
	struct work_struct	aad;
	struct work_struct	goc;
	struct work_struct	apc;

	struct workqueue_struct *WorkQueue;
}ST_WORK_QUEUE;

typedef struct {
	UINT8	number;
	UINT8	first_sog_lvl;
	UINT8	quantity;
} ST_SOG_LEVEL;



/*
	Enum define
*/


/*
	global variable
*/
//extern volatile VPORT_Reg_T *gVportReg;

/*
	function prototype
*/
void ADC_IFM(void *unused);
void ADC_IBD(void *unused);
void ADC_AAD(void *unused);
int ADC_GOC(LX_AFE_ADC_CALIB_INFO_T *calib_param);

void ADC_IFM_ISR(void *unused);

int ADC_IBD_Mesurement(ST_EXTAU *extau , int iIndex);
int ADC_IBD_main(int iIndex);
int ADC_IBD_Setting(ST_EXTAU *extau , int iIndex);
int ADC_IBD_GetBackPorch(ST_EXTAU *extau);

int ADC_IFM_main(int *iIndex);
//int ADC_GetInputSignalInform(S_VIDEO_SIZE_INFORM *inform);
int ADC_IFM_GetInputSignal(S_VIDEO_SIZE_INFORM *inform);
int ADC_IFM_Routine(S_VIDEO_SIZE_INFORM *adc_size);


int ADC_PHASE_main(int iIndex);
int ADC_PHASE_for_Component(int iIndex);

int ADC_AutoGainControl_main(LX_AFE_ADC_CALIB_INFO_T *calib_param, int iIndex);
int ADC_AutoOffsetControl_main(int iIndex);
int ADC_AutoOffsetControlByInput_main(int iIndex);

int ADC_Initialize(void);
int ADC_PCAdjust(LX_AFE_ADJ_PCMODE_INFO_T *stAdjMode);
int ADC_AutoAdjust(LX_AFE_ADJ_PC_T *stAdj);
void ADC_GetTimingInfo(LX_AFE_ADC_TIMING_INFO_T *stTiming);
int ADC_SetInputFormat(LX_AFE_ADC_SET_INPUT_T *stInput);

#if 0
int ADC_SetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_GetGainValue(LX_AFE_ADC_GAIN_VALUE_T *stGain);
int ADC_SetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
int ADC_GetOffsetValue(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
#else
extern int (*ADC_SetGainValue)(LX_AFE_ADC_GAIN_VALUE_T *stGain);
extern int (*ADC_GetGainValue)(LX_AFE_ADC_GAIN_VALUE_T *stGain);
extern int (*ADC_SetOffsetValue)(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
extern int (*ADC_GetOffsetValue)(LX_AFE_ADC_OFFSET_VALUE_T *stOffset);
#endif

int ADC_SetPCmodeTable(LX_AFE_SET_PCMODE_TABLE_T *stTableInfo);

extern int (*ADC_Enable_Scart_Mode)(BOOLEAN scart_enable);

int ADC_Set_PCMODE_Resoultion(UINT32 arg);

int ADC_GetInputSignalInform(S_VIDEO_SIZE_INFORM *inform);

int ADC_Phase_Convert_to_UI_Value(int reg_phase_value, int gResolution_index);
irqreturn_t VPORT_ADC_irq_handler(int irq, void *dev_id, struct pt_regs *regs);

UINT64 ADC_PHASE_Mesurement_Simple(int iIndex, UINT16 htotal);

int ADC_Enable_Periodic_Signal_Info_Read(UINT32 enable);
int ADC_Execute_Format_Detection(void);
int ADC_Enable_Component_Auto_Phase(UINT32 enable);
int ADC_Test_Program(LX_AFE_ADC_TEST_PARAM_T *stADC_Test_Param);
int ADC_IFM_SearchTable(S_VIDEO_SIZE_INFORM *inform);

int ADC_Periodic_Task(void);
int ADC_Clear_Previous_Size_Info(void);
int ADC_Get_Component_Pseudo_Pulse(LX_AFE_ADC_COMP_PSEUDO_PULSE_T *pComp_PSP_t);
int ADC_Get_ACE_FB_Status(LX_AFE_SCART_MODE_T *pSCMode);
int ADC_Set_SCART_RGB_Operation_Mode(LX_AFE_SCART_BYPASS_MODE_T scart_rgb_mode);
// for test
//int ADC_RunRegister(S_INTERFACE_REG *reg);
void ADC_KernelRun(void);
//int ADC_PHASE_Mesurement_for_Component_HSync(int iIndex);
//int ADC_PHASE_Mesurement_for_Component_HSync_Sampling(int iIndex);
//int ADC_PHASE_Mesurement_for_Component_HSync_Fast(int iIndex);
#endif
