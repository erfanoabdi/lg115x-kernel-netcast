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


/** @file pe_csc.c
 *
 *  driver for picture enhance color space conversion functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_csc.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CSC_ERROR	printk

#define PE_CSC_DBG_PRINT(fmt,args...)	\
	if(_g_csc_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CSC_CHECK_CODE(_checker,_action,fmt,args...)	{if(_checker){PE_CSC_ERROR(fmt,##args);_action;}}

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

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_CSC_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
static int PE_CSC_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
static int PE_CSC_SetColorGamut(LX_PE_CSC_GAMUT_T *pstParams);
static int PE_CSC_GetColorGamut(LX_PE_CSC_GAMUT_T *pstParams);
static int PE_CSC_SetPostCsc(LX_PE_CSC_POST_T *pstParams);
static int PE_CSC_GetPostCsc(LX_PE_CSC_POST_T *pstParams);
static int PE_CSC_SetInputCsc(LX_PE_CSC_INPUT_T *pstParams);
static int PE_CSC_GetInputCsc(LX_PE_CSC_INPUT_T *pstParams);
static int PE_CSC_SetxvYCC(LX_PE_CSC_XVYCC_T *pstParams);
static int PE_CSC_GetxvYCC(LX_PE_CSC_XVYCC_T *pstParams);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_csc_trace=0x0;	//default should be off.

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * init csc
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_Init(void)
{
	int ret = RET_OK;
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			PE_CSC_DBG_PRINT("init csc.\n");
			PE_P1L_H13B0_QWr05(pe1_xvy_ctrl_00,	outputcsc_en,		0x1, \
												degamma_en,			0x1, \
												pcc_en,				0x1, \
												gamma_en,			0x1, \
												hsv_hsl_selection,	0x0);
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_CSC_DBG_PRINT("init csc.\n");
			PE_P1L_H13_QWr05(pe1_xvy_ctrl_00,	outputcsc_en,		0x1, \
												degamma_en,			0x1, \
												pcc_en,				0x1, \
												gamma_en,			0x1, \
												hsv_hsl_selection,	0x0);
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			PE_CSC_DBG_PRINT("init xvy ctrl .\n");
			PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_00);
			PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, outputcsc_en,		0x1);
			PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, degamma_en,			0x1);
			PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, pcc_en,				0x1);
			PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, gamma_en,			0x1);
			PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, hsv_hsl_selection,	0x0);
			PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_00);
			PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_00);
			PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, outputcsc_en,		0x1);
			PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, degamma_en,			0x1);
			PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, pcc_en,				0x1);
			PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, gamma_en,			0x1);
			PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, hsv_hsl_selection,	0x0);
			PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_00);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			PE_CSC_DBG_PRINT("init xvy ctrl .\n");
			PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_00);
			PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_00, icsc_en,			0x1);
			PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_00, degamma_en,		0x1);
			PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_00, pcc_en,			0x1);
			PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_00, gamma,			0x1);
			PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_00, hsv_hsl_selection,0x0);
			PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_00);
			PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_00);
			PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_00, icsc_en,			0x1);
			PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_00, degamma_en,		0x1);
			PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_00, pcc_en,			0x1);
			PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_00, gamma,			0x1);
			PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_00, hsv_hsl_selection,0x0);
			PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_00);
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}

/**
 * standard function of csc setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CSC_SET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CSC_DBG_PRINT("S %s\n",#_struct);\
			PE_CSC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CSC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			PE_CSC_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CSC_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CSC_SET_FUNC(LX_PE_CSC_INPUT_T,			PE_CSC_SetInputCsc);
		PE_CSC_SET_FUNC(LX_PE_CSC_POST_T,			PE_CSC_SetPostCsc);
		PE_CSC_SET_FUNC(LX_PE_CSC_GAMUT_T,			PE_CSC_SetColorGamut);
		PE_CSC_SET_FUNC(LX_PE_CSC_XVYCC_T,			PE_CSC_SetxvYCC);
		PE_CSC_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CSC_SetDefaultSettings);
		PE_CSC_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CSC_SetDebugSettings);
		default:
		{
			PE_CSC_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of csc getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CSC_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CSC_GET_FUNC(_struct,_func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv,param;\
		do{\
			PE_CSC_DBG_PRINT("S %s\n",#_struct);\
			PE_CSC_CHECK_CODE(datasize!=sizeof(_struct),break,"[%s,%d] size mismatch.\n",__F__,__L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param,p_rcv,datasize);\
			ret = _func(&param);\
			PE_CSC_CHECK_CODE(ret,break,"[%s,%d] %s() error.\n",__F__,__L__,#_func);\
			memcpy(p_rcv,&param,datasize);\
			PE_CSC_DBG_PRINT("E %s\n",#_struct);\
		}while(0);\
	}\
	break

	/* data null check */
	PE_CSC_CHECK_CODE(!data,return RET_ERROR,"[%s,%d] data is null.\n",__F__,__L__);
	switch(functype)
	{
		PE_CSC_GET_FUNC(LX_PE_CSC_INPUT_T,	PE_CSC_GetInputCsc);
		PE_CSC_GET_FUNC(LX_PE_CSC_POST_T,	PE_CSC_GetPostCsc);
		PE_CSC_GET_FUNC(LX_PE_CSC_GAMUT_T,	PE_CSC_GetColorGamut);
		PE_CSC_GET_FUNC(LX_PE_CSC_XVYCC_T,	PE_CSC_GetxvYCC);
		default:
		{
			PE_CSC_ERROR("[%s,%d] functype(%d) default case.\n",__F__,__L__,functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}
/**
 * default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CSC_DBG_PRINT("[win id:%d]\n",pstParams->win_id);
	}while(0);
	return ret;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CSC_DBG_PRINT("wid:%d,type:0x%x,[0x%x]print:0x%x,bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CSC)),\
			pstParams->print_lvl,pstParams->bypass);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_csc_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CSC)))? 0x1:0x0;
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			#ifdef USE_PE_KDRV_CODES_FOR_H13
			if(PE_KDRV_VER_H13BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CSC)))
				{
					PE_CSC_DBG_PRINT("degamma,pcc,gamma,s scaler : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13B0_QWr04(pe1_xvy_ctrl_00, degamma_en,					0x0, \
															pcc_en,						0x0, \
															gamma_en,					0x0, \
															s_adpative_scaler_enable,	0x0);
					}
				}
				else
				{
					PE_CSC_DBG_PRINT("outcsc,degamma,pcc,gamma : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13B0_QWr03(pe1_xvy_ctrl_00, degamma_en,			0x1, \
															pcc_en,				0x1, \
															gamma_en,			0x1);
					}
				}
			}
			else if(PE_KDRV_VER_H13AX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CSC)))
				{
					PE_CSC_DBG_PRINT("degamma,pcc,gamma,s scaler : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13_QWr04(pe1_xvy_ctrl_00,	degamma_en,					0x0, \
															pcc_en,						0x0, \
															gamma_en,					0x0, \
															s_adpative_scaler_enable,	0x0);
					}
				}
				else
				{
					PE_CSC_DBG_PRINT("outcsc,degamma,pcc,gamma : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_H13_QWr03(pe1_xvy_ctrl_00,	degamma_en,			0x1,\
															pcc_en,				0x1, \
															gamma_en,			0x1);
						
					}
				}
			}
			else
			#endif
			#ifdef USE_PE_KDRV_CODES_FOR_L9
			if(PE_KDRV_VER_L9BX)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CSC)))
				{
					PE_CSC_DBG_PRINT("degamma,pcc,gamma,s scaler : disable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_00);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, degamma_en,					0x0);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, pcc_en,						0x0);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, gamma_en,					0x0);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, s_adpative_scaler_enable,	0x0);
						PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_00);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_00);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, degamma_en,					0x0);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, pcc_en,						0x0);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, gamma_en,					0x0);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, s_adpative_scaler_enable,	0x0);
						PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_00);
					}
				}
				else
				{
					PE_CSC_DBG_PRINT("outcsc,degamma,pcc,gamma : enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_00);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, degamma_en,			0x1);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, pcc_en,				0x1);
						PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, gamma_en,			0x1);
						PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_00);
					}
					if(PE_CHECK_WIN1(pstParams->win_id))
					{
						PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_00);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, degamma_en,			0x1);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, pcc_en,				0x1);
						PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, gamma_en,			0x1);
						PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_00);
					}
				}
			}
			else
			#endif
			{
				PE_CSC_DBG_PRINT("do nothing.\n");	ret = RET_OK;
			}
		}
	}while(0);
	return ret;
}
/**
 * set color gamut
 *
 * @param   *pstParams [in] LX_PE_CSC_GAMUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_SetColorGamut(LX_PE_CSC_GAMUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CSC_DBG_PRINT("set pstParams[%d] : 0x%x,0x%x,0x%x, 0x%x,0x%x,0x%x, 0x%x,0x%x,0x%x\n",\
			pstParams->win_id,pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],pstParams->matrix[6],\
			pstParams->matrix[7],pstParams->matrix[8]);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				
				PE_P1L_H13B0_QWr01(pe1_xvy_ctrl_08,	r_pcc_coef0, GET_BITS(pstParams->matrix[0],0,15));
				
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_09,	r_pcc_coef1, GET_BITS(pstParams->matrix[1],0,15),\
													r_pcc_coef2, GET_BITS(pstParams->matrix[2],0,15));
				
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_0a,	r_pcc_coef3, GET_BITS(pstParams->matrix[3],0,15),\
													r_pcc_coef4, GET_BITS(pstParams->matrix[4],0,15));
				
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_0b,	r_pcc_coef5, GET_BITS(pstParams->matrix[5],0,15),\
													r_pcc_coef6, GET_BITS(pstParams->matrix[6],0,15));
				
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_0c,	r_pcc_coef7, GET_BITS(pstParams->matrix[7],0,15),\
													r_pcc_coef8, GET_BITS(pstParams->matrix[8],0,15));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_QWr01(pe1_xvy_ctrl_08,	r_pcc_coef0, GET_BITS(pstParams->matrix[0],0,15));
				
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_09,	r_pcc_coef1, GET_BITS(pstParams->matrix[1],0,15),\
													r_pcc_coef2, GET_BITS(pstParams->matrix[2],0,15));
				
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_0a,	r_pcc_coef3, GET_BITS(pstParams->matrix[3],0,15),\
													r_pcc_coef4, GET_BITS(pstParams->matrix[4],0,15));
				
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_0b,	r_pcc_coef5, GET_BITS(pstParams->matrix[5],0,15),\
													r_pcc_coef6, GET_BITS(pstParams->matrix[6],0,15));
				
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_0c,	r_pcc_coef7, GET_BITS(pstParams->matrix[7],0,15),\
													r_pcc_coef8, GET_BITS(pstParams->matrix[8],0,15));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_08);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_09);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0a);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0b);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0c);
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_08, r_pcc_coef0, GET_BITS(pstParams->matrix[0],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_09, r_pcc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_09, r_pcc_coef2, GET_BITS(pstParams->matrix[2],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0a, r_pcc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0a, r_pcc_coef4, GET_BITS(pstParams->matrix[4],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0b, r_pcc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0b, r_pcc_coef6, GET_BITS(pstParams->matrix[6],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0c, r_pcc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0c, r_pcc_coef8, GET_BITS(pstParams->matrix[8],0,15));
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_0c);
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_0b);
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_0a);
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_09);
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_08);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_08);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_09);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0a);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0b);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0c);
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_08, r_pcc_coef0, GET_BITS(pstParams->matrix[0],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_09, r_pcc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_09, r_pcc_coef2, GET_BITS(pstParams->matrix[2],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0a, r_pcc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0a, r_pcc_coef4, GET_BITS(pstParams->matrix[4],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0b, r_pcc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0b, r_pcc_coef6, GET_BITS(pstParams->matrix[6],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0c, r_pcc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0c, r_pcc_coef8, GET_BITS(pstParams->matrix[8],0,15));
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_0c);
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_0b);
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_0a);
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_09);
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_08);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_08);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_09);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0a);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0b);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0c);
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_08, r_pcc_coef0, GET_BITS(pstParams->matrix[0],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_09, r_pcc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_09, r_pcc_coef2, GET_BITS(pstParams->matrix[2],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0a, r_pcc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0a, r_pcc_coef4, GET_BITS(pstParams->matrix[4],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0b, r_pcc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0b, r_pcc_coef6, GET_BITS(pstParams->matrix[6],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0c, r_pcc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0c, r_pcc_coef8, GET_BITS(pstParams->matrix[8],0,15));
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_0c);
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_0b);
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_0a);
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_09);
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_08);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_08);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_09);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0a);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0b);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0c);
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_08, r_pcc_coef0, GET_BITS(pstParams->matrix[0],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_09, r_pcc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_09, r_pcc_coef2, GET_BITS(pstParams->matrix[2],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0a, r_pcc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0a, r_pcc_coef4, GET_BITS(pstParams->matrix[4],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0b, r_pcc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0b, r_pcc_coef6, GET_BITS(pstParams->matrix[6],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0c, r_pcc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0c, r_pcc_coef8, GET_BITS(pstParams->matrix[8],0,15));
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_0c);
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_0b);
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_0a);
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_09);
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_08);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get color gamut
 *
 * @param   *pstParams [in/out] LX_PE_CSC_GAMUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_GetColorGamut(LX_PE_CSC_GAMUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_xvy_ctrl_08,	r_pcc_coef0, pstParams->matrix[0]);
				
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_09,	r_pcc_coef1, pstParams->matrix[1],\
													r_pcc_coef2, pstParams->matrix[2]);
				
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_0a,	r_pcc_coef3, pstParams->matrix[3],\
													r_pcc_coef4, pstParams->matrix[4]);
				
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_0b,	r_pcc_coef5, pstParams->matrix[5],\
													r_pcc_coef6, pstParams->matrix[6]);
				
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_0c,	r_pcc_coef7, pstParams->matrix[7],\
													r_pcc_coef8, pstParams->matrix[8]);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QRd01(pe1_xvy_ctrl_08,	r_pcc_coef0, pstParams->matrix[0]);
				
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_09,	r_pcc_coef1, pstParams->matrix[1],\
													r_pcc_coef2, pstParams->matrix[2]);
				
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_0a,	r_pcc_coef3, pstParams->matrix[3],\
													r_pcc_coef4, pstParams->matrix[4]);
				
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_0b,	r_pcc_coef5, pstParams->matrix[5],\
													r_pcc_coef6, pstParams->matrix[6]);
				
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_0c,	r_pcc_coef7, pstParams->matrix[7],\
													r_pcc_coef8, pstParams->matrix[8]);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_08);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_09);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0a);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0b);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0c);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_08, r_pcc_coef0, pstParams->matrix[0]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_09, r_pcc_coef1, pstParams->matrix[1]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_09, r_pcc_coef2, pstParams->matrix[2]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0a, r_pcc_coef3, pstParams->matrix[3]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0a, r_pcc_coef4, pstParams->matrix[4]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0b, r_pcc_coef5, pstParams->matrix[5]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0b, r_pcc_coef6, pstParams->matrix[6]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0c, r_pcc_coef7, pstParams->matrix[7]);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0c, r_pcc_coef8, pstParams->matrix[8]);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_08);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_09);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0a);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0b);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0c);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_08, r_pcc_coef0, pstParams->matrix[0]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_09, r_pcc_coef1, pstParams->matrix[1]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_09, r_pcc_coef2, pstParams->matrix[2]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0a, r_pcc_coef3, pstParams->matrix[3]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0a, r_pcc_coef4, pstParams->matrix[4]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0b, r_pcc_coef5, pstParams->matrix[5]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0b, r_pcc_coef6, pstParams->matrix[6]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0c, r_pcc_coef7, pstParams->matrix[7]);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0c, r_pcc_coef8, pstParams->matrix[8]);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_08);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_09);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0a);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0b);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0c);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_08, r_pcc_coef0, pstParams->matrix[0]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_09, r_pcc_coef1, pstParams->matrix[1]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_09, r_pcc_coef2, pstParams->matrix[2]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0a, r_pcc_coef3, pstParams->matrix[3]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0a, r_pcc_coef4, pstParams->matrix[4]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0b, r_pcc_coef5, pstParams->matrix[5]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0b, r_pcc_coef6, pstParams->matrix[6]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0c, r_pcc_coef7, pstParams->matrix[7]);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0c, r_pcc_coef8, pstParams->matrix[8]);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_08);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_09);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0a);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0b);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0c);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_08, r_pcc_coef0, pstParams->matrix[0]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_09, r_pcc_coef1, pstParams->matrix[1]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_09, r_pcc_coef2, pstParams->matrix[2]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0a, r_pcc_coef3, pstParams->matrix[3]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0a, r_pcc_coef4, pstParams->matrix[4]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0b, r_pcc_coef5, pstParams->matrix[5]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0b, r_pcc_coef6, pstParams->matrix[6]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0c, r_pcc_coef7, pstParams->matrix[7]);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0c, r_pcc_coef8, pstParams->matrix[8]);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}

		PE_CSC_DBG_PRINT("get pstParams[%d] : 0x%x,0x%x,0x%x, 0x%x,0x%x,0x%x, 0x%x,0x%x,0x%x\n",\
			pstParams->win_id,pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],pstParams->matrix[3],\
			pstParams->matrix[4],pstParams->matrix[5],pstParams->matrix[6],pstParams->matrix[7],pstParams->matrix[8]);
	}while(0);
	return ret;
}
/**
 * set post csc
 *
 * @param   *pstParams [in] LX_PE_CSC_POST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_SetPostCsc(LX_PE_CSC_POST_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CSC_DBG_PRINT("set pstParams[%d] : \n"\
			"coef:%x,%x,%x, %x,%x,%x, %x,%x,%x, ofs:%x,%x,%x, %x,%x,%x\n",\
			pstParams->win_id,pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],pstParams->matrix[6],\
			pstParams->matrix[7],pstParams->matrix[8],pstParams->offset[0],pstParams->offset[1],\
			pstParams->offset[2],pstParams->offset[3],pstParams->offset[4],pstParams->offset[5]);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_01,	r_csc_coef0, GET_BITS(pstParams->matrix[0],0,15),\
													r_csc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_02,	r_csc_coef2, GET_BITS(pstParams->matrix[2],0,15),\
													r_csc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_03,	r_csc_coef4, GET_BITS(pstParams->matrix[4],0,15),\
													r_csc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_04,	r_csc_coef6, GET_BITS(pstParams->matrix[6],0,15),\
													r_csc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_05,	r_csc_coef8, GET_BITS(pstParams->matrix[8],0,15),\
													r_csc_ofst0, GET_BITS(pstParams->offset[0],0,11));
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_06,	r_csc_ofst1, GET_BITS(pstParams->offset[1],0,11),\
													r_csc_ofst2, GET_BITS(pstParams->offset[2],0,11));
				PE_P1L_H13B0_QWr02(pe1_xvy_ctrl_07,	r_csc_ofst3, GET_BITS(pstParams->offset[3],0,14),\
													r_csc_ofst4, GET_BITS(pstParams->offset[4],0,14));
				PE_P1L_H13B0_QWr01(pe1_xvy_ctrl_08,	r_csc_ofst5, GET_BITS(pstParams->offset[5],0,14));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_01,	r_csc_coef0, GET_BITS(pstParams->matrix[0],0,15),\
													r_csc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_02,	r_csc_coef2, GET_BITS(pstParams->matrix[2],0,15),\
													r_csc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_03,	r_csc_coef4, GET_BITS(pstParams->matrix[4],0,15),\
													r_csc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_04,	r_csc_coef6, GET_BITS(pstParams->matrix[6],0,15),\
													r_csc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_05,	r_csc_coef8, GET_BITS(pstParams->matrix[8],0,15),\
													r_csc_ofst0, GET_BITS(pstParams->offset[0],0,11));
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_06,	r_csc_ofst1, GET_BITS(pstParams->offset[1],0,11),\
													r_csc_ofst2, GET_BITS(pstParams->offset[2],0,11));
				PE_P1L_H13_QWr02(pe1_xvy_ctrl_07,	r_csc_ofst3, GET_BITS(pstParams->offset[3],0,14),\
													r_csc_ofst4, GET_BITS(pstParams->offset[4],0,14));
				PE_P1L_H13_QWr01(pe1_xvy_ctrl_08,	r_csc_ofst5, GET_BITS(pstParams->offset[5],0,14));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_01,	r_csc_coef0, GET_BITS(pstParams->matrix[0],0,15),\
													r_csc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_02,	r_csc_coef2, GET_BITS(pstParams->matrix[2],0,15),\
													r_csc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_03,	r_csc_coef4, GET_BITS(pstParams->matrix[4],0,15),\
													r_csc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_04,	r_csc_coef6, GET_BITS(pstParams->matrix[6],0,15),\
													r_csc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_05,	r_csc_coef8, GET_BITS(pstParams->matrix[8],0,15),\
													r_csc_ofst0, GET_BITS(pstParams->offset[0],0,11));
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_06,	r_csc_ofst1, GET_BITS(pstParams->offset[1],0,11),\
													r_csc_ofst2, GET_BITS(pstParams->offset[2],0,11));
				PE_P1L_L9B_QWr02(pe1_l_xvy_ctrl_07,	r_csc_ofst3, GET_BITS(pstParams->offset[3],0,14),\
													r_csc_ofst4, GET_BITS(pstParams->offset[4],0,14));
				PE_P1L_L9B_QWr01(pe1_l_xvy_ctrl_08,	r_csc_ofst5, GET_BITS(pstParams->offset[5],0,14));
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_01,	r_csc_coef0, GET_BITS(pstParams->matrix[0],0,15),\
													r_csc_coef1, GET_BITS(pstParams->matrix[1],0,15));
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_02,	r_csc_coef2, GET_BITS(pstParams->matrix[2],0,15),\
													r_csc_coef3, GET_BITS(pstParams->matrix[3],0,15));
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_03,	r_csc_coef4, GET_BITS(pstParams->matrix[4],0,15),\
													r_csc_coef5, GET_BITS(pstParams->matrix[5],0,15));
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_04,	r_csc_coef6, GET_BITS(pstParams->matrix[6],0,15),\
													r_csc_coef7, GET_BITS(pstParams->matrix[7],0,15));
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_05,	r_csc_coef8, GET_BITS(pstParams->matrix[8],0,15),\
													r_csc_ofst0, GET_BITS(pstParams->offset[0],0,11));
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_06,	r_csc_ofst1, GET_BITS(pstParams->offset[1],0,11),\
													r_csc_ofst2, GET_BITS(pstParams->offset[2],0,11));
				PE_P1R_L9B_QWr02(pe1_r_xvy_ctrl_07,	r_csc_ofst3, GET_BITS(pstParams->offset[3],0,14),\
													r_csc_ofst4, GET_BITS(pstParams->offset[4],0,14));
				PE_P1R_L9B_QWr01(pe1_r_xvy_ctrl_08,	r_csc_ofst5, GET_BITS(pstParams->offset[5],0,14));
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);

	return ret;
}
/**
 * get post csc
 *
 * @param   *pstParams [in/out] LX_PE_CSC_POST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_GetPostCsc(LX_PE_CSC_POST_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_01,	r_csc_coef0, pstParams->matrix[0],\
													r_csc_coef1, pstParams->matrix[1]);
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_02,	r_csc_coef2, pstParams->matrix[2],\
													r_csc_coef3, pstParams->matrix[3]);
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_03,	r_csc_coef4, pstParams->matrix[4],\
													r_csc_coef5, pstParams->matrix[5]);
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_04,	r_csc_coef6, pstParams->matrix[6],\
													r_csc_coef7, pstParams->matrix[7]);
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_05,	r_csc_coef8, pstParams->matrix[8],\
													r_csc_ofst0, pstParams->offset[0]);
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_06,	r_csc_ofst1, pstParams->offset[1],\
													r_csc_ofst2, pstParams->offset[2]);
				PE_P1L_H13B0_QRd02(pe1_xvy_ctrl_07,	r_csc_ofst3, pstParams->offset[3],\
													r_csc_ofst4, pstParams->offset[4]);
				PE_P1L_H13B0_QRd01(pe1_xvy_ctrl_08,	r_csc_ofst5, pstParams->offset[5]);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_01,	r_csc_coef0, pstParams->matrix[0],\
													r_csc_coef1, pstParams->matrix[1]);
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_02,	r_csc_coef2, pstParams->matrix[2],\
													r_csc_coef3, pstParams->matrix[3]);
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_03,	r_csc_coef4, pstParams->matrix[4],\
													r_csc_coef5, pstParams->matrix[5]);
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_04,	r_csc_coef6, pstParams->matrix[6],\
													r_csc_coef7, pstParams->matrix[7]);
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_05,	r_csc_coef8, pstParams->matrix[8],\
													r_csc_ofst0, pstParams->offset[0]);
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_06,	r_csc_ofst1, pstParams->offset[1],\
													r_csc_ofst2, pstParams->offset[2]);
				PE_P1L_H13_QRd02(pe1_xvy_ctrl_07,	r_csc_ofst3, pstParams->offset[3],\
													r_csc_ofst4, pstParams->offset[4]);
				PE_P1L_H13_QRd01(pe1_xvy_ctrl_08,	r_csc_ofst5, pstParams->offset[5]);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_01,	r_csc_coef0, pstParams->matrix[0],\
													r_csc_coef1, pstParams->matrix[1]);
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_02,	r_csc_coef2, pstParams->matrix[2],\
													r_csc_coef3, pstParams->matrix[3]);
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_03,	r_csc_coef4, pstParams->matrix[4],\
													r_csc_coef5, pstParams->matrix[5]);
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_04,	r_csc_coef6, pstParams->matrix[6],\
													r_csc_coef7, pstParams->matrix[7]);
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_05,	r_csc_coef8, pstParams->matrix[8],\
													r_csc_ofst0, pstParams->offset[0]);
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_06,	r_csc_ofst1, pstParams->offset[1],\
													r_csc_ofst2, pstParams->offset[2]);
				PE_P1L_L9B_QRd02(pe1_l_xvy_ctrl_07,	r_csc_ofst3, pstParams->offset[3],\
													r_csc_ofst4, pstParams->offset[4]);
				PE_P1L_L9B_QRd01(pe1_l_xvy_ctrl_08,	r_csc_ofst5, pstParams->offset[5]);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_01,	r_csc_coef0, pstParams->matrix[0],\
													r_csc_coef1, pstParams->matrix[1]);
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_02,	r_csc_coef2, pstParams->matrix[2],\
													r_csc_coef3, pstParams->matrix[3]);
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_03,	r_csc_coef4, pstParams->matrix[4],\
													r_csc_coef5, pstParams->matrix[5]);
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_04,	r_csc_coef6, pstParams->matrix[6],\
													r_csc_coef7, pstParams->matrix[7]);
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_05,	r_csc_coef8, pstParams->matrix[8],\
													r_csc_ofst0, pstParams->offset[0]);
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_06,	r_csc_ofst1, pstParams->offset[1],\
													r_csc_ofst2, pstParams->offset[2]);
				PE_P1R_L9B_QRd02(pe1_r_xvy_ctrl_07,	r_csc_ofst3, pstParams->offset[3],\
													r_csc_ofst4, pstParams->offset[4]);
				PE_P1R_L9B_QRd01(pe1_r_xvy_ctrl_08,	r_csc_ofst5, pstParams->offset[5]);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CSC_DBG_PRINT("get pstParams[%d] : \n"\
			"coef:%x,%x,%x, %x,%x,%x, %x,%x,%x, ofs:%x,%x,%x, %x,%x,%x\n",\
			pstParams->win_id,pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],pstParams->matrix[6],\
			pstParams->matrix[7],pstParams->matrix[8],pstParams->offset[0],pstParams->offset[1],\
			pstParams->offset[2],pstParams->offset[3],pstParams->offset[4],pstParams->offset[5]);
	}while(0);
	return ret;
}
/**
 * set input csc
 *
 * @param   *pstParams [in] LX_PE_CSC_INPUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_SetInputCsc(LX_PE_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CSC_DBG_PRINT("set pstParams[%d] : en:%d\n"\
			"coef:%x,%x,%x, %x,%x,%x, %x,%x,%x, ofs:%x,%x,%x, %x,%x,%x\n",\
			pstParams->win_id,pstParams->enable,\
			pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],\
			pstParams->matrix[6],pstParams->matrix[7],pstParams->matrix[8],\
			pstParams->offset[0],pstParams->offset[1],pstParams->offset[2],\
			pstParams->offset[3],pstParams->offset[4],pstParams->offset[5]);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			/* If the reg. setting has a transition artifact, use the firmware setting. */
			#if 0	// reg. setting
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CVA_H13B0_RdFL(cva_csc_ctrl0);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl1);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl2);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl3);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl4);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl5);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl6);
				PE_CVA_H13B0_RdFL(cva_csc_ctrl7);
				PE_CVA_H13B0_Wr01(cva_csc_ctrl0, csc_coefficient0,	GET_BITS(pstParams->matrix[0],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl0, csc_coefficient1,	GET_BITS(pstParams->matrix[1],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl1, csc_coefficient2,	GET_BITS(pstParams->matrix[2],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl1, csc_coefficient3,	GET_BITS(pstParams->matrix[3],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl2, csc_coefficient4,	GET_BITS(pstParams->matrix[4],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl2, csc_coefficient5,	GET_BITS(pstParams->matrix[5],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl3, csc_coefficient6,	GET_BITS(pstParams->matrix[6],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl3, csc_coefficient7,	GET_BITS(pstParams->matrix[7],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl4, csc_coefficient8,	GET_BITS(pstParams->matrix[8],0,15));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl4, csc_offset0,		GET_BITS(pstParams->offset[0],0,11));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl5, csc_offset1,		GET_BITS(pstParams->offset[1],0,11));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl5, csc_offset2,		GET_BITS(pstParams->offset[2],0,11));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl6, csc_offset3,		GET_BITS(pstParams->offset[3],0,11));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl6, csc_offset4,		GET_BITS(pstParams->offset[4],0,11));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl7, csc_offset5,		GET_BITS(pstParams->offset[5],0,11));
				PE_CVA_H13B0_Wr01(cva_csc_ctrl7, csc_en,			GET_BITS(pstParams->enable,0,1));
				PE_CVA_H13B0_WrFL(cva_csc_ctrl0);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl1);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl2);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl3);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl4);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl5);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl6);
				PE_CVA_H13B0_WrFL(cva_csc_ctrl7);
				if(pstParams->enable)
				{
					PE_CVA_H13B0_Wr01(cva_csc_ctrl7, csc_coeff_load,	0x1);	//this bit is auto cleared
					PE_CVA_H13B0_WrFL(cva_csc_ctrl7);
				}
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl0);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl1);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl2);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl3);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl4);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl5);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl6);
				PE_CVB_H13B0_RdFL(cvb_csc_ctrl7);
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl0, csc_coefficient0,	GET_BITS(pstParams->matrix[0],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl0, csc_coefficient1,	GET_BITS(pstParams->matrix[1],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl1, csc_coefficient2,	GET_BITS(pstParams->matrix[2],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl1, csc_coefficient3,	GET_BITS(pstParams->matrix[3],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl2, csc_coefficient4,	GET_BITS(pstParams->matrix[4],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl2, csc_coefficient5,	GET_BITS(pstParams->matrix[5],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl3, csc_coefficient6,	GET_BITS(pstParams->matrix[6],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl3, csc_coefficient7,	GET_BITS(pstParams->matrix[7],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl4, csc_coefficient8,	GET_BITS(pstParams->matrix[8],0,15));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl4, csc_offset0,		GET_BITS(pstParams->offset[0],0,11));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl5, csc_offset1,		GET_BITS(pstParams->offset[1],0,11));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl5, csc_offset2,		GET_BITS(pstParams->offset[2],0,11));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl6, csc_offset3,		GET_BITS(pstParams->offset[3],0,11));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl6, csc_offset4,		GET_BITS(pstParams->offset[4],0,11));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl7, csc_offset5,		GET_BITS(pstParams->offset[5],0,11));
				PE_CVB_H13B0_Wr01(cvb_csc_ctrl7, csc_en,			GET_BITS(pstParams->enable,0,1));
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl0);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl1);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl2);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl3);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl4);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl5);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl6);
				PE_CVB_H13B0_WrFL(cvb_csc_ctrl7);
				if(pstParams->enable)
				{
					PE_CVB_H13B0_Wr01(cvb_csc_ctrl7, csc_coeff_load,	0x1);	//this bit is auto cleared
					PE_CVB_H13B0_WrFL(cvb_csc_ctrl7);
				}
			}
			#else	// firmware setting
			LX_PE_WIN_ID win_id = pstParams->win_id;
			if(PE_CHECK_WIN0(win_id))
			{
				pstParams->win_id = LX_PE_WIN_0;
				ret = PE_FWI_SETDATA(DE_IPC_SET_CVI_CSC,(void *)pstParams,sizeof(LX_PE_CSC_INPUT_T));
				PE_CSC_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pstParams->win_id = LX_PE_WIN_1;
				ret = PE_FWI_SETDATA(DE_IPC_SET_CVI_CSC,(void *)pstParams,sizeof(LX_PE_CSC_INPUT_T));
				PE_CSC_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			}
			#endif
		}
		else if(PE_KDRV_VER_H13AX)
		{
			/* If the reg. setting has a transition artifact, use the firmware setting. */
			#if 0	// reg. setting
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CVA_H13_RdFL(cva_csc_ctrl0);
				PE_CVA_H13_RdFL(cva_csc_ctrl1);
				PE_CVA_H13_RdFL(cva_csc_ctrl2);
				PE_CVA_H13_RdFL(cva_csc_ctrl3);
				PE_CVA_H13_RdFL(cva_csc_ctrl4);
				PE_CVA_H13_RdFL(cva_csc_ctrl5);
				PE_CVA_H13_RdFL(cva_csc_ctrl6);
				PE_CVA_H13_RdFL(cva_csc_ctrl7);
				PE_CVA_H13_Wr01(cva_csc_ctrl0, csc_coefficient0,	GET_BITS(pstParams->matrix[0],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl0, csc_coefficient1,	GET_BITS(pstParams->matrix[1],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl1, csc_coefficient2,	GET_BITS(pstParams->matrix[2],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl1, csc_coefficient3,	GET_BITS(pstParams->matrix[3],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl2, csc_coefficient4,	GET_BITS(pstParams->matrix[4],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl2, csc_coefficient5,	GET_BITS(pstParams->matrix[5],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl3, csc_coefficient6,	GET_BITS(pstParams->matrix[6],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl3, csc_coefficient7,	GET_BITS(pstParams->matrix[7],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl4, csc_coefficient8,	GET_BITS(pstParams->matrix[8],0,15));
				PE_CVA_H13_Wr01(cva_csc_ctrl4, csc_offset0,			GET_BITS(pstParams->offset[0],0,11));
				PE_CVA_H13_Wr01(cva_csc_ctrl5, csc_offset1,			GET_BITS(pstParams->offset[1],0,11));
				PE_CVA_H13_Wr01(cva_csc_ctrl5, csc_offset2,			GET_BITS(pstParams->offset[2],0,11));
				PE_CVA_H13_Wr01(cva_csc_ctrl6, csc_offset3,			GET_BITS(pstParams->offset[3],0,11));
				PE_CVA_H13_Wr01(cva_csc_ctrl6, csc_offset4,			GET_BITS(pstParams->offset[4],0,11));
				PE_CVA_H13_Wr01(cva_csc_ctrl7, csc_offset5,			GET_BITS(pstParams->offset[5],0,11));
				PE_CVA_H13_Wr01(cva_csc_ctrl7, csc_en,				GET_BITS(pstParams->enable,0,1));
				PE_CVA_H13_WrFL(cva_csc_ctrl0);
				PE_CVA_H13_WrFL(cva_csc_ctrl1);
				PE_CVA_H13_WrFL(cva_csc_ctrl2);
				PE_CVA_H13_WrFL(cva_csc_ctrl3);
				PE_CVA_H13_WrFL(cva_csc_ctrl4);
				PE_CVA_H13_WrFL(cva_csc_ctrl5);
				PE_CVA_H13_WrFL(cva_csc_ctrl6);
				PE_CVA_H13_WrFL(cva_csc_ctrl7);
				if(pstParams->enable)
				{
					PE_CVA_H13_Wr01(cva_csc_ctrl7, csc_coeff_load,	0x1);	//this bit is auto cleared
					PE_CVA_H13_WrFL(cva_csc_ctrl7);
				}
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_CVB_H13_RdFL(cvb_csc_ctrl0);
				PE_CVB_H13_RdFL(cvb_csc_ctrl1);
				PE_CVB_H13_RdFL(cvb_csc_ctrl2);
				PE_CVB_H13_RdFL(cvb_csc_ctrl3);
				PE_CVB_H13_RdFL(cvb_csc_ctrl4);
				PE_CVB_H13_RdFL(cvb_csc_ctrl5);
				PE_CVB_H13_RdFL(cvb_csc_ctrl6);
				PE_CVB_H13_RdFL(cvb_csc_ctrl7);
				PE_CVB_H13_Wr01(cvb_csc_ctrl0, csc_coefficient0,	GET_BITS(pstParams->matrix[0],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl0, csc_coefficient1,	GET_BITS(pstParams->matrix[1],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl1, csc_coefficient2,	GET_BITS(pstParams->matrix[2],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl1, csc_coefficient3,	GET_BITS(pstParams->matrix[3],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl2, csc_coefficient4,	GET_BITS(pstParams->matrix[4],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl2, csc_coefficient5,	GET_BITS(pstParams->matrix[5],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl3, csc_coefficient6,	GET_BITS(pstParams->matrix[6],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl3, csc_coefficient7,	GET_BITS(pstParams->matrix[7],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl4, csc_coefficient8,	GET_BITS(pstParams->matrix[8],0,15));
				PE_CVB_H13_Wr01(cvb_csc_ctrl4, csc_offset0,			GET_BITS(pstParams->offset[0],0,11));
				PE_CVB_H13_Wr01(cvb_csc_ctrl5, csc_offset1,			GET_BITS(pstParams->offset[1],0,11));
				PE_CVB_H13_Wr01(cvb_csc_ctrl5, csc_offset2,			GET_BITS(pstParams->offset[2],0,11));
				PE_CVB_H13_Wr01(cvb_csc_ctrl6, csc_offset3,			GET_BITS(pstParams->offset[3],0,11));
				PE_CVB_H13_Wr01(cvb_csc_ctrl6, csc_offset4,			GET_BITS(pstParams->offset[4],0,11));
				PE_CVB_H13_Wr01(cvb_csc_ctrl7, csc_offset5,			GET_BITS(pstParams->offset[5],0,11));
				PE_CVB_H13_Wr01(cvb_csc_ctrl7, csc_en,				GET_BITS(pstParams->enable,0,1));
				PE_CVB_H13_WrFL(cvb_csc_ctrl0);
				PE_CVB_H13_WrFL(cvb_csc_ctrl1);
				PE_CVB_H13_WrFL(cvb_csc_ctrl2);
				PE_CVB_H13_WrFL(cvb_csc_ctrl3);
				PE_CVB_H13_WrFL(cvb_csc_ctrl4);
				PE_CVB_H13_WrFL(cvb_csc_ctrl5);
				PE_CVB_H13_WrFL(cvb_csc_ctrl6);
				PE_CVB_H13_WrFL(cvb_csc_ctrl7);
				if(pstParams->enable)
				{
					PE_CVB_H13_Wr01(cvb_csc_ctrl7, csc_coeff_load,	0x1);	//this bit is auto cleared
					PE_CVB_H13_WrFL(cvb_csc_ctrl7);
				}
			}
			#else	// firmware setting
			LX_PE_WIN_ID win_id = pstParams->win_id;
			if(PE_CHECK_WIN0(win_id))
			{
				pstParams->win_id = LX_PE_WIN_0;
				ret = PE_FWI_SETDATA(DE_IPC_SET_CVI_CSC,(void *)pstParams,sizeof(LX_PE_CSC_INPUT_T));
				PE_CSC_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pstParams->win_id = LX_PE_WIN_1;
				ret = PE_FWI_SETDATA(DE_IPC_SET_CVI_CSC,(void *)pstParams,sizeof(LX_PE_CSC_INPUT_T));
				PE_CSC_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			}
			#endif
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			LX_PE_WIN_ID win_id = pstParams->win_id;
			if(PE_CHECK_WIN0(win_id))
			{
				pstParams->win_id = LX_PE_WIN_0;
				ret = PE_FWI_SETDATA(DE_IPC_SET_CVI_CSC,(void *)pstParams,sizeof(LX_PE_CSC_INPUT_T));
				PE_CSC_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				pstParams->win_id = LX_PE_WIN_1;
				ret = PE_FWI_SETDATA(DE_IPC_SET_CVI_CSC,(void *)pstParams,sizeof(LX_PE_CSC_INPUT_T));
				PE_CSC_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_SETDATA() error.\n",__F__,__L__);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get input csc
 *
 * @param   *pstParams [in/out] LX_PE_CSC_INPUT_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_GetInputCsc(LX_PE_CSC_INPUT_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CVA_H13B0_QRd02(cva_csc_ctrl0,	csc_coefficient0,	pstParams->matrix[0],\
													csc_coefficient1,	pstParams->matrix[1]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl1,	csc_coefficient2,	pstParams->matrix[2],\
													csc_coefficient3,	pstParams->matrix[3]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl2,	csc_coefficient4,	pstParams->matrix[4],\
													csc_coefficient5,	pstParams->matrix[5]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl3,	csc_coefficient6,	pstParams->matrix[6],\
													csc_coefficient7,	pstParams->matrix[7]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl4,	csc_coefficient8,	pstParams->matrix[8],\
													csc_offset0,		pstParams->offset[0]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl5,	csc_offset1,		pstParams->offset[1],\
													csc_offset2,		pstParams->offset[2]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl6,	csc_offset3,		pstParams->offset[3],\
													csc_offset4,		pstParams->offset[4]);
				PE_CVA_H13B0_QRd02(cva_csc_ctrl7,	csc_offset5,		pstParams->offset[5],\
													csc_en,				pstParams->enable);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl0,	csc_coefficient0,	pstParams->matrix[0],\
													csc_coefficient1,	pstParams->matrix[1]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl1,	csc_coefficient2,	pstParams->matrix[2],\
													csc_coefficient3,	pstParams->matrix[3]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl2,	csc_coefficient4,	pstParams->matrix[4],\
													csc_coefficient5,	pstParams->matrix[5]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl3,	csc_coefficient6,	pstParams->matrix[6],\
													csc_coefficient7,	pstParams->matrix[7]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl4,	csc_coefficient8,	pstParams->matrix[8],\
													csc_offset0,		pstParams->offset[0]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl5,	csc_offset1,		pstParams->offset[1],\
													csc_offset2,		pstParams->offset[2]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl6,	csc_offset3,		pstParams->offset[3],\
													csc_offset4,		pstParams->offset[4]);
				PE_CVB_H13B0_QRd02(cvb_csc_ctrl7,	csc_offset5,		pstParams->offset[5],\
													csc_en,				pstParams->enable);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CVA_H13_QRd02(cva_csc_ctrl0,	csc_coefficient0,	pstParams->matrix[0],\
												csc_coefficient1,	pstParams->matrix[1]);
				PE_CVA_H13_QRd02(cva_csc_ctrl1,	csc_coefficient2,	pstParams->matrix[2],\
												csc_coefficient3,	pstParams->matrix[3]);
				PE_CVA_H13_QRd02(cva_csc_ctrl2,	csc_coefficient4,	pstParams->matrix[4],\
												csc_coefficient5,	pstParams->matrix[5]);
				PE_CVA_H13_QRd02(cva_csc_ctrl3,	csc_coefficient6,	pstParams->matrix[6],\
												csc_coefficient7,	pstParams->matrix[7]);
				PE_CVA_H13_QRd02(cva_csc_ctrl4,	csc_coefficient8,	pstParams->matrix[8],\
												csc_offset0,		pstParams->offset[0]);
				PE_CVA_H13_QRd02(cva_csc_ctrl5,	csc_offset1,		pstParams->offset[1],\
												csc_offset2,		pstParams->offset[2]);
				PE_CVA_H13_QRd02(cva_csc_ctrl6,	csc_offset3,		pstParams->offset[3],\
												csc_offset4,		pstParams->offset[4]);
				PE_CVA_H13_QRd02(cva_csc_ctrl7,	csc_offset5,		pstParams->offset[5],\
												csc_en,				pstParams->enable);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				
				PE_CVB_H13_QRd02(cvb_csc_ctrl0,	csc_coefficient0,	pstParams->matrix[0],\
												csc_coefficient1,	pstParams->matrix[1]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl1,	csc_coefficient2,	pstParams->matrix[2],\
												csc_coefficient3,	pstParams->matrix[3]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl2,	csc_coefficient4,	pstParams->matrix[4],\
												csc_coefficient5,	pstParams->matrix[5]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl3,	csc_coefficient6,	pstParams->matrix[6],\
												csc_coefficient7,	pstParams->matrix[7]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl4,	csc_coefficient8,	pstParams->matrix[8],\
												csc_offset0,		pstParams->offset[0]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl5,	csc_offset1,		pstParams->offset[1],\
												csc_offset2,		pstParams->offset[2]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl6,	csc_offset3,		pstParams->offset[3],\
												csc_offset4,		pstParams->offset[4]);
				PE_CVB_H13_QRd02(cvb_csc_ctrl7,	csc_offset5,		pstParams->offset[5],\
												csc_en,				pstParams->enable);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CVA_L9B_RdFL(cva_csc_ctrl0);
				PE_CVA_L9B_RdFL(cva_csc_ctrl1);
				PE_CVA_L9B_RdFL(cva_csc_ctrl2);
				PE_CVA_L9B_RdFL(cva_csc_ctrl3);
				PE_CVA_L9B_RdFL(cva_csc_ctrl4);
				PE_CVA_L9B_RdFL(cva_csc_ctrl5);
				PE_CVA_L9B_RdFL(cva_csc_ctrl6);
				PE_CVA_L9B_RdFL(cva_csc_ctrl7);
				PE_CVA_L9B_Rd01(cva_csc_ctrl0, csc_coefficient0,	pstParams->matrix[0]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl0, csc_coefficient1,	pstParams->matrix[1]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl1, csc_coefficient2,	pstParams->matrix[2]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl1, csc_coefficient3,	pstParams->matrix[3]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl2, csc_coefficient4,	pstParams->matrix[4]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl2, csc_coefficient5,	pstParams->matrix[5]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl3, csc_coefficient6,	pstParams->matrix[6]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl3, csc_coefficient7,	pstParams->matrix[7]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl4, csc_coefficient8,	pstParams->matrix[8]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl4, csc_offset0,			pstParams->offset[0]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl5, csc_offset1,			pstParams->offset[1]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl5, csc_offset2,			pstParams->offset[2]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl6, csc_offset3,			pstParams->offset[3]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl6, csc_offset4,			pstParams->offset[4]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl7, csc_offset5,			pstParams->offset[5]);
				PE_CVA_L9B_Rd01(cva_csc_ctrl7, csc_en,				pstParams->enable);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_CVB_L9B_RdFL(cvb_csc_ctrl0);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl1);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl2);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl3);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl4);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl5);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl6);
				PE_CVB_L9B_RdFL(cvb_csc_ctrl7);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl0, csc_coefficient0,	pstParams->matrix[0]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl0, csc_coefficient1,	pstParams->matrix[1]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl1, csc_coefficient2,	pstParams->matrix[2]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl1, csc_coefficient3,	pstParams->matrix[3]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl2, csc_coefficient4,	pstParams->matrix[4]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl2, csc_coefficient5,	pstParams->matrix[5]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl3, csc_coefficient6,	pstParams->matrix[6]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl3, csc_coefficient7,	pstParams->matrix[7]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl4, csc_coefficient8,	pstParams->matrix[8]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl4, csc_offset0,			pstParams->offset[0]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl5, csc_offset1,			pstParams->offset[1]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl5, csc_offset2,			pstParams->offset[2]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl6, csc_offset3,			pstParams->offset[3]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl6, csc_offset4,			pstParams->offset[4]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl7, csc_offset5,			pstParams->offset[5]);
				PE_CVB_L9B_Rd01(cvb_csc_ctrl7, csc_en,				pstParams->enable);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CSC_DBG_PRINT("get pstParams[%d] : en:%d\n"\
			"coef:%x,%x,%x, %x,%x,%x, %x,%x,%x, ofs:%x,%x,%x, %x,%x,%x\n",\
			pstParams->win_id,pstParams->enable,\
			pstParams->matrix[0],pstParams->matrix[1],pstParams->matrix[2],\
			pstParams->matrix[3],pstParams->matrix[4],pstParams->matrix[5],\
			pstParams->matrix[6],pstParams->matrix[7],pstParams->matrix[8],\
			pstParams->offset[0],pstParams->offset[1],pstParams->offset[2],\
			pstParams->offset[3],pstParams->offset[4],pstParams->offset[5]);
	}while(0);
	return ret;
}
/**
 * set xvYcc
 *
 * @param   *pstParams [in] LX_PE_CSC_XVYCC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_SetxvYCC(LX_PE_CSC_XVYCC_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CSC_DBG_PRINT("set pstParams[%d] : en:%d, sclr:0x%x\n",\
			pstParams->win_id,pstParams->enable,pstParams->scaler);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13B0_QWr01(pe1_xvy_ctrl_00, scaler_en,	(pstParams->enable)? 0x1:0x0);
				PE_P1L_H13B0_QWr01(pe1_xvy_ctrl_0d, scaler,		GET_BITS(pstParams->scaler,0,8));
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_QWr01(pe1_xvy_ctrl_00, scaler_en,	(pstParams->enable)? 0x1:0x0);
				PE_P1L_H13_QWr01(pe1_xvy_ctrl_0d, scaler,		GET_BITS(pstParams->scaler,0,8));
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0d);
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_00, scaler_en,	(pstParams->enable)? 0x1:0x0);
				PE_P1L_L9B0_Wr01(pe1_l_xvy_ctrl_0d, scaler,		GET_BITS(pstParams->scaler,0,8));
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_00);
				PE_P1L_L9B0_WrFL(pe1_l_xvy_ctrl_0d);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0d);
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_00, scaler_en,	(pstParams->enable)? 0x1:0x0);
				PE_P1R_L9B0_Wr01(pe1_r_xvy_ctrl_0d, scaler,		GET_BITS(pstParams->scaler,0,8));
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_00);
				PE_P1R_L9B0_WrFL(pe1_r_xvy_ctrl_0d);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_00);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0d);
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_00, scaler_en,	(pstParams->enable)? 0x1:0x0);
				PE_P1L_L9_Wr01(pe1_l_xvy_ctrl_0d, scaler,		GET_BITS(pstParams->scaler,0,8));
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_00);
				PE_P1L_L9_WrFL(pe1_l_xvy_ctrl_0d);
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_00);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0d);
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_00, scaler_en,	(pstParams->enable)? 0x1:0x0);
				PE_P1R_L9_Wr01(pe1_r_xvy_ctrl_0d, scaler,		GET_BITS(pstParams->scaler,0,8));
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_00);
				PE_P1R_L9_WrFL(pe1_r_xvy_ctrl_0d);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * get xvYcc
 *
 * @param   *pstParams [in/out] LX_PE_CSC_XVYCC_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CSC_GetxvYCC(LX_PE_CSC_XVYCC_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		#ifdef USE_PE_KDRV_CODES_FOR_H13
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QRd01(pe1_xvy_ctrl_00, scaler_en,	pstParams->enable);
				PE_P1L_H13B0_QRd01(pe1_xvy_ctrl_0d, scaler,		pstParams->scaler);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QRd01(pe1_xvy_ctrl_00, scaler_en,	pstParams->enable);
				PE_P1L_H13_QRd01(pe1_xvy_ctrl_0d, scaler,		pstParams->scaler);
			}
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_L9
		if(PE_KDRV_VER_L9BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_00);
				PE_P1L_L9B0_RdFL(pe1_l_xvy_ctrl_0d);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_00, scaler_en,	pstParams->enable);
				PE_P1L_L9B0_Rd01(pe1_l_xvy_ctrl_0d, scaler,		pstParams->scaler);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_00);
				PE_P1R_L9B0_RdFL(pe1_r_xvy_ctrl_0d);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_00, scaler_en,	pstParams->enable);
				PE_P1R_L9B0_Rd01(pe1_r_xvy_ctrl_0d, scaler,		pstParams->scaler);
			}
		}
		else if(PE_KDRV_VER_L9AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_00);
				PE_P1L_L9_RdFL(pe1_l_xvy_ctrl_0d);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_00, scaler_en,	pstParams->enable);
				PE_P1L_L9_Rd01(pe1_l_xvy_ctrl_0d, scaler,		pstParams->scaler);
			}
			if(PE_CHECK_WIN1(win_id))
			{
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_00);
				PE_P1R_L9_RdFL(pe1_r_xvy_ctrl_0d);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_00, scaler_en,	pstParams->enable);
				PE_P1R_L9_Rd01(pe1_r_xvy_ctrl_0d, scaler,		pstParams->scaler);
			}
		}
		else
		#endif
		{
			PE_CSC_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CSC_DBG_PRINT("get pstParams[%d] : en:%d, sclr:0x%x\n",\
			pstParams->win_id,pstParams->enable,pstParams->scaler);
	}while(0);
	return ret;
}

