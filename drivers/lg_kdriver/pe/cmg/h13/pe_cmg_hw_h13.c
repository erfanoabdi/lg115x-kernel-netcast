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


/** @file pe_cmg_hw_h13.c
 *
 *  driver for picture enhance color management functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
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
#include "pe_etc_hw.h"
#include "pe_cmg_hw.h"
#include "pe_cmg_cen_init_ia_h13a0.h"
#include "pe_cmg_cen_init_ia_h13b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMG_HW_H13_ERROR	printk

#define PE_CMG_HW_H13_DBG_PRINT(fmt,args...)	\
	if(_g_cmg_hw_h13_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMG_HW_H13_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_CMG_HW_H13_ERROR(fmt,##args);_action;}}

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
static int PE_CMG_HW_H13B_Set_Init_Coeff(const PE_REG_PARAM_T *reg,UINT32 *tableSize);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmg_hw_h13_trace=0x0;	//default should be off.
static PE_CMG_HW_H13_SETTINGS_T _g_pe_cmg_hw_h13_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set debug print on off
 *
 * @param   on_off [in] UINT8
 * @return  void
 * @see
 * @author
 */
void PE_CMG_HW_H13_SetDbgPrint(UINT32 on_off)
{
	_g_cmg_hw_h13_trace = on_off? 1:0;
	return;
}
/**
 * init color management
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_Init(void)
{
	int ret = RET_OK;
	do{
		if(PE_KDRV_VER_H13BX)
		{
			UINT32 table_size = sizeof(cen_init_ia_h13b0)/sizeof(PE_REG_PARAM_T);
			PE_CMG_HW_H13_DBG_PRINT("write cen_init_ia_h13b0. \n");
			ret = PE_CMG_HW_H13B_Set_Init_Coeff(cen_init_ia_h13b0,&table_size);
			PE_CMG_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_CMG_HW_H13B_Set_Init_Coeff() error.\n",__F__,__L__);
			memset(&_g_pe_cmg_hw_h13_info,0xffff,sizeof(PE_CMG_HW_H13_SETTINGS_T));
		}
		else if(PE_KDRV_VER_H13AX)
		{
			PE_CMG_HW_H13_DBG_PRINT("write cen_init_ia_h13a0. \n");
			ret = PE_REG_SetTable(cen_init_ia_h13a0,0,sizeof(cen_init_ia_h13a0));
			PE_CMG_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_REG_SetTable() error.\n",__F__,__L__);
		}
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * set initial param for color management 
 *
 * @param   *reg [in] const PE_REG_PARAM_T
 * @param	*tableSize [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMG_HW_H13B_Set_Init_Coeff(const PE_REG_PARAM_T *reg,UINT32 *tableSize)
{
	UINT32 i;
#define PE_CMG_HW_H13_P1L_WR(_a,_d)	\
	do{\
		PE_P1L_H13B0_Wr(_a,_d);PE_P1L_H13B0_WrFL(_a);\
	}while(0)
	
	for(i=0;i<*tableSize ;i++)
	{
		switch(reg[i].addr)
		{
			case 0x5614:	PE_CMG_HW_H13_P1L_WR(pe1_cen_ia_ctrl,	reg[i].data);	break;
			case 0x5618:	PE_CMG_HW_H13_P1L_WR(pe1_cen_ia_data,	reg[i].data);	break;
			default:
				PE_CMG_HW_H13_ERROR("[%s,%d]wrong case. [%03d]addr:0x%08x,data:0x%08x\n",\
					__F__,__L__,i,reg[i].addr,reg[i].data);
				break;
		}
	}
	return RET_OK;
}

/**
 * set cen region
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_SetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count=0;
	UINT32 startAddr=0;
	UINT32 x_wdata,y_wdata;
	#ifdef PE_FWI_H13_CHK_CEN_DOUBLE_SET
	UINT32 set_flag=0;
	PE_CMG_HW_H13_SETTINGS_T *pInfo=&_g_pe_cmg_hw_h13_info;
	#endif
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_H13_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pstParams->region_num);
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_FWI_H13_CHK_CEN_DOUBLE_SET
				/* check double setting */
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					if(pInfo->rgn_set[pstParams->region_num].hue_x[count]!=pstParams->hue_x[count] || \
						pInfo->rgn_set[pstParams->region_num].hue_g[count]!=pstParams->hue_g[count] || \
						pInfo->rgn_set[pstParams->region_num].sat_x[count]!=pstParams->sat_x[count] || \
						pInfo->rgn_set[pstParams->region_num].sat_g[count]!=pstParams->sat_g[count] || \
						pInfo->rgn_set[pstParams->region_num].val_x[count]!=pstParams->val_x[count] || \
						pInfo->rgn_set[pstParams->region_num].val_g[count]!=pstParams->val_g[count])
					{
						set_flag=1;
						break;
					}
				}
				if(set_flag)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0, 	//[15] 0:host access, 1:normal mode
														hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
														hif_cen_address,	0x0);	//[7:0] address
					startAddr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
					/* H color region table : 000 */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						/* hue_x,x_wdata : 0~1024(0~720 degree) */
						x_wdata = (UINT32)GET_BITS(pstParams->hue_x[count],0,10);
						y_wdata = GET_BITS(pstParams->hue_g[count],0,7);	// 0~127
						PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					}
					/* S color region table : 001 */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pstParams->sat_x[count],0,7);	// 0~100
						y_wdata = GET_BITS(pstParams->sat_g[count],0,7);	// 0~127

						PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					}
					/* V color region table : 010 */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						x_wdata = GET_BITS(pstParams->val_x[count],0,8);	// 0~255
						y_wdata = GET_BITS(pstParams->val_g[count],0,7);	// 0~127

						PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
						PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
						PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					}
					/* show color region table : 011 */
					startAddr = pstParams->region_num;
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x3);		//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						PE_P1L_H13B0_Wr(pe1_cen_ia_data,	0x0);
						PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					}
					/* normal operation */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
					{
						pInfo->rgn_set[pstParams->region_num].hue_x[count]=pstParams->hue_x[count];
						pInfo->rgn_set[pstParams->region_num].hue_g[count]=pstParams->hue_g[count];
						pInfo->rgn_set[pstParams->region_num].sat_x[count]=pstParams->sat_x[count];
						pInfo->rgn_set[pstParams->region_num].sat_g[count]=pstParams->sat_g[count];
						pInfo->rgn_set[pstParams->region_num].val_x[count]=pstParams->val_x[count];
						pInfo->rgn_set[pstParams->region_num].val_g[count]=pstParams->val_g[count];
					}
				}
				#else
				PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
				PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0, 	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address
				startAddr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
				/* H color region table : 000 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					/* hue_x,x_wdata : 0~1024(0~720 degree) */
					x_wdata = (UINT32)GET_BITS(pstParams->hue_x[count],0,10);
					y_wdata = GET_BITS(pstParams->hue_g[count],0,7);	// 0~127
					PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
					PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				}
				/* S color region table : 001 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					x_wdata = GET_BITS(pstParams->sat_x[count],0,7);	// 0~100
					y_wdata = GET_BITS(pstParams->sat_g[count],0,7);	// 0~127

					PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
					PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				}
				/* V color region table : 010 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					x_wdata = GET_BITS(pstParams->val_x[count],0,8);	// 0~255
					y_wdata = GET_BITS(pstParams->val_g[count],0,7);	// 0~127

					PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
					PE_P1L_H13B0_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				}
				/* show color region table : 011 */
				startAddr = pstParams->region_num;
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x3);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13B0_Wr(pe1_cen_ia_data,	0x0);
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				}
				/* normal operation */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
				#endif
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_RdFL(pe1_cen_ia_data);
				PE_P1L_H13_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0, 	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address
				startAddr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
				/* H color region table : 000 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);				
				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					/* hue_x,x_wdata : 0~1024(0~720 degree) */
					x_wdata = (UINT32)GET_BITS(pstParams->hue_x[count],0,10);
					y_wdata = GET_BITS(pstParams->hue_g[count],0,7);	// 0~127
					PE_P1L_H13_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
					PE_P1L_H13_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
					PE_P1L_H13_WrFL(pe1_cen_ia_data);
				}
				/* S color region table : 001 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					x_wdata = GET_BITS(pstParams->sat_x[count],0,7);	// 0~100
					y_wdata = GET_BITS(pstParams->sat_g[count],0,7);	// 0~127

					PE_P1L_H13_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
					PE_P1L_H13_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
					PE_P1L_H13_WrFL(pe1_cen_ia_data);
				}
				/* V color region table : 010 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					x_wdata = GET_BITS(pstParams->val_x[count],0,8);	// 0~255
					y_wdata = GET_BITS(pstParams->val_g[count],0,7);	// 0~127

					PE_P1L_H13_Wr01(pe1_cen_ia_data,	hif_cen_x_wdata, 	x_wdata);	//[25:16] x data
					PE_P1L_H13_Wr01(pe1_cen_ia_data,	hif_cen_y_wdata, 	y_wdata);	//[9:0] y data
					PE_P1L_H13_WrFL(pe1_cen_ia_data);
				}
				/* show color region table : 011 */
				startAddr = pstParams->region_num;
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x3);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13_Wr(pe1_cen_ia_data,	0x0);
					PE_P1L_H13_WrFL(pe1_cen_ia_data);
				}
				/* normal operation */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while(0);
	return ret;
}
/**
 * get cen region
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_GetCenRegion(LX_PE_CMG_REGION_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 startAddr=0;
	UINT32 x_wdata=0,y_wdata=0;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_H13_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pstParams->region_num);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		startAddr = pstParams->region_num*LX_PE_CMG_TBLPOINT;
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_RdFL(pe1_cen_ia_ctrl);
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x1);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address


				/* H color region table : 000 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					PE_P1L_H13B0_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_P1L_H13B0_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					/* x_wdata,hue_x 0~1024 (0~720 degree) */
					pstParams->hue_x[count] = (UINT16)GET_BITS(x_wdata,0,10);
					pstParams->hue_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* S color region table : 001 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					PE_P1L_H13B0_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_P1L_H13B0_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->sat_x[count] = (UINT8)GET_BITS(x_wdata,0,7);	// 0~100
					pstParams->sat_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* V color region table : 010 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					PE_P1L_H13B0_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_P1L_H13B0_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->val_x[count] = (UINT8)GET_BITS(x_wdata,0,8);	// 0~255
					pstParams->val_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* normal operation */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_RdFL(pe1_cen_ia_ctrl);
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x1);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address


				/* H color region table : 000 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13_RdFL(pe1_cen_ia_data);
					PE_P1L_H13_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_P1L_H13_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					/* x_wdata,hue_x 0~1024 (0~720 degree) */
					pstParams->hue_x[count] = (UINT16)GET_BITS(x_wdata,0,10);
					pstParams->hue_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* S color region table : 001 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x1);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13_RdFL(pe1_cen_ia_data);
					PE_P1L_H13_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_P1L_H13_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->sat_x[count] = (UINT8)GET_BITS(x_wdata,0,7);	// 0~100
					pstParams->sat_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* V color region table : 010 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x2);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_TBLPOINT;count++)
				{
					PE_P1L_H13_RdFL(pe1_cen_ia_data);
					PE_P1L_H13_Rd01(pe1_cen_ia_data,	hif_cen_x_wdata,	x_wdata);	//[25:16] x data
					PE_P1L_H13_Rd01(pe1_cen_ia_data,	hif_cen_y_wdata,	y_wdata);	//[9:0] y data

					pstParams->val_x[count] = (UINT8)GET_BITS(x_wdata,0,8);	// 0~255
					pstParams->val_g[count] = (UINT8)GET_BITS(y_wdata,0,7);	// 0~127
				}
				/* normal operation */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);
			}
		}		
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * set cen region ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count=0;
	UINT32 startAddr=0;
	UINT32 delta[3];		// -128 ~ 127, hsv or gbr
	UINT32 wdata=0;
	#ifdef PE_FWI_H13_USE_CEN_RGN_CTRL
	PE_FWI_H13_CEN_CTRL fw_param;
	#else
	#ifdef PE_FWI_H13_CHK_CEN_DOUBLE_SET
	UINT32 set_flag=0;
	PE_CMG_HW_H13_SETTINGS_T *pInfo=&_g_pe_cmg_hw_h13_info;
	#endif
	#endif
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMG_HW_H13_CHECK_CODE(pstParams->region_num>LX_PE_CMG_REGION_MAX,ret=RET_ERROR;break,\
			"[%s,%d] region_num(%d) is out of range.\n",__F__,__L__,pstParams->region_num);
		
		PE_CMG_HW_H13_DBG_PRINT(" Set: path:%d num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n",\
				pstParams->win_id,pstParams->region_num,pstParams->master_gain,\
				pstParams->region_delta[0],pstParams->region_delta[1],pstParams->region_delta[2],\
				pstParams->region_delta[3],pstParams->region_delta[4],pstParams->region_delta[5]);
		if(PE_KDRV_VER_H13BX)
		{
			#ifdef PE_FWI_H13_USE_CEN_RGN_CTRL
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				fw_param.rgn_num = (UINT8)pstParams->region_num;
				fw_param.delta_h = (UINT8)pstParams->region_delta[0];
				fw_param.delta_s = (UINT8)pstParams->region_delta[1];
				fw_param.delta_v = (UINT8)pstParams->region_delta[2];
				fw_param.delta_g = (UINT8)pstParams->region_delta[3];
				fw_param.delta_b = (UINT8)pstParams->region_delta[4];
				fw_param.delta_r = (UINT8)pstParams->region_delta[5];
				fw_param.ma_gain = pstParams->master_gain;
				ret = PE_FWI_H13_SetCenCtrl(&fw_param);
				PE_CMG_HW_H13_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_H13_SetCenCtrl() error.\n",__F__,__L__);
			}
			#else
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_FWI_H13_CHK_CEN_DOUBLE_SET
				/* check double setting */
				if(pInfo->rgn_ctrl[pstParams->region_num].region_delta[0]!=pstParams->region_delta[0] || \
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[1]!=pstParams->region_delta[1] || \
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[2]!=pstParams->region_delta[2] || \
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[3]!=pstParams->region_delta[3] || \
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[4]!=pstParams->region_delta[4] || \
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[5]!=pstParams->region_delta[5] || \
					pInfo->rgn_ctrl[pstParams->region_num].master_gain!=pstParams->master_gain)
				{
					set_flag=1;
				}
				if(set_flag)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
														hif_cen_ai, 		0x1,   //[12] ai 0:disable, 1:enable
														hif_cen_address,	0x0);	//[7:0] address				
					/* region delta gain : 100 */
					startAddr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;
			
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x4);		//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++)
					{
						wdata=0;
						delta[0] = GET_BITS(pstParams->region_delta[count*3],0,8);		// -128 ~ 127
						delta[1] = GET_BITS(pstParams->region_delta[count*3+1],0,8);	// -128 ~ 127
						delta[2] = GET_BITS(pstParams->region_delta[count*3+2],0,8);	// -128 ~ 127
						wdata = (delta[0]<<16)|(delta[1]<<8)|(delta[2]);
						PE_P1L_H13B0_Wr(pe1_cen_ia_data,	wdata);
						PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					}
					/* region master gain : 101 */
					startAddr = pstParams->region_num;

					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x5);		//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

					wdata = GET_BITS(pstParams->master_gain,0,8);	// 0~128~255
					PE_P1L_H13B0_Wr(pe1_cen_ia_data,	wdata);
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					/* normal operation */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[0]=pstParams->region_delta[0];
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[1]=pstParams->region_delta[1];
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[2]=pstParams->region_delta[2];
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[3]=pstParams->region_delta[3];
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[4]=pstParams->region_delta[4];
					pInfo->rgn_ctrl[pstParams->region_num].region_delta[5]=pstParams->region_delta[5];
					pInfo->rgn_ctrl[pstParams->region_num].master_gain=pstParams->master_gain;
				}
				#else
				PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
				PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,   //[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address				
				/* region delta gain : 100 */
				startAddr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;
		
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x4);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++)
				{
					wdata=0;
					delta[0] = GET_BITS(pstParams->region_delta[count*3],0,8);		// -128 ~ 127
					delta[1] = GET_BITS(pstParams->region_delta[count*3+1],0,8);	// -128 ~ 127
					delta[2] = GET_BITS(pstParams->region_delta[count*3+2],0,8);	// -128 ~ 127
					wdata = (delta[0]<<16)|(delta[1]<<8)|(delta[2]);
					PE_P1L_H13B0_Wr(pe1_cen_ia_data,	wdata);
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				}
				/* region master gain : 101 */
				startAddr = pstParams->region_num;

				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x5);		//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				wdata = GET_BITS(pstParams->master_gain,0,8);	// 0~128~255
				PE_P1L_H13B0_Wr(pe1_cen_ia_data,	wdata);
				PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				/* normal operation */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
				#endif
			}
			#endif
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_RdFL(pe1_cen_ia_data);
				PE_P1L_H13_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,   //[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address
				
				/* region delta gain : 100 */
				startAddr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;
		
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x4);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);				
				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++)
				{
					wdata=0;
					delta[0] = GET_BITS(pstParams->region_delta[count*3],0,8);		// -128 ~ 127
					delta[1] = GET_BITS(pstParams->region_delta[count*3+1],0,8);	// -128 ~ 127
					delta[2] = GET_BITS(pstParams->region_delta[count*3+2],0,8);	// -128 ~ 127
					wdata = (delta[0]<<16)|(delta[1]<<8)|(delta[2]);
					PE_P1L_H13_Wr(pe1_cen_ia_data,	wdata);
					PE_P1L_H13_WrFL(pe1_cen_ia_data);
				}
				/* region master gain : 101 */
				startAddr = pstParams->region_num;

				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x5);		//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				wdata = GET_BITS(pstParams->master_gain,0,8);	// 0~128~255
				PE_P1L_H13_Wr(pe1_cen_ia_data,	wdata);
				PE_P1L_H13_WrFL(pe1_cen_ia_data);
				/* normal operation */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get cen region ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_REGION_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 startAddr=0;
	UINT32 reMgain=0;
	UINT32 reDgain[LX_PE_CMG_DELTA_SETNUM];	// hsv or gbr
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[4:0] address
				/* region master gain : 101 */
				startAddr = pstParams->region_num;
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x5);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
				reMgain = PE_P1L_H13B0_Rd(pe1_cen_ia_data);
				/* region delta gain : 100 */
				startAddr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;

				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x4);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					reDgain[count] = PE_P1L_H13B0_Rd(pe1_cen_ia_data);
				}
				pstParams->master_gain = (UINT8)GET_BITS(reMgain,0,8);	// region master gain, 0~128~255
				pstParams->region_delta[0] = (SINT8)GET_BITS(reDgain[0],16,8);	// h, -128 ~ 127
				pstParams->region_delta[1] = (SINT8)GET_BITS(reDgain[0],8,8);	// s, -128 ~ 127
				pstParams->region_delta[2] = (SINT8)GET_BITS(reDgain[0],0,8);	// v, -128 ~ 127
				pstParams->region_delta[3] = (SINT8)GET_BITS(reDgain[1],16,8);	// g, -128 ~ 127
				pstParams->region_delta[4] = (SINT8)GET_BITS(reDgain[1],8,8);	// b, -128 ~ 127
				pstParams->region_delta[5] = (SINT8)GET_BITS(reDgain[1],0,8);	// r, -128 ~ 127
				/* normal operation */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[4:0] address
				/* region master gain : 101 */
				startAddr = pstParams->region_num;
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x5);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				PE_P1L_H13_RdFL(pe1_cen_ia_data);
				reMgain = PE_P1L_H13_Rd(pe1_cen_ia_data);
				/* region delta gain : 100 */
				startAddr = pstParams->region_num*LX_PE_CMG_DELTA_SETNUM;

				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x4);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	startAddr); //[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTA_SETNUM;count++)
				{
					PE_P1L_H13_RdFL(pe1_cen_ia_data);
					reDgain[count] = PE_P1L_H13_Rd(pe1_cen_ia_data);
				}
				pstParams->master_gain = (UINT8)GET_BITS(reMgain,0,8);	// region master gain, 0~128~255
				pstParams->region_delta[0] = (SINT8)GET_BITS(reDgain[0],16,8);	// h, -128 ~ 127
				pstParams->region_delta[1] = (SINT8)GET_BITS(reDgain[0],8,8);	// s, -128 ~ 127
				pstParams->region_delta[2] = (SINT8)GET_BITS(reDgain[0],0,8);	// v, -128 ~ 127
				pstParams->region_delta[3] = (SINT8)GET_BITS(reDgain[1],16,8);	// g, -128 ~ 127
				pstParams->region_delta[4] = (SINT8)GET_BITS(reDgain[1],8,8);	// b, -128 ~ 127
				pstParams->region_delta[5] = (SINT8)GET_BITS(reDgain[1],0,8);	// r, -128 ~ 127
				/* normal operation */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMG_HW_H13_DBG_PRINT(" Get: path:%d num:%d, m_g:%d, delta(hsvgbr):%d,%d,%d,%d,%d,%d\n",\
				pstParams->win_id,pstParams->region_num,pstParams->master_gain,\
				pstParams->region_delta[0],pstParams->region_delta[1],pstParams->region_delta[2],\
				pstParams->region_delta[3],pstParams->region_delta[4],pstParams->region_delta[5]);
	} while (0);
	return ret;
}
/**
 * set cen global ctrl
 *
 * @param   *pstParams [in] LX_PE_CMG_GLOBAL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_SetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 count=0;
	UINT32 wdata=0;	// h,s,v,g,b,r
	#ifdef PE_FWI_H13_CHK_CEN_DOUBLE_SET
	UINT32 set_flag=0;
	PE_CMG_HW_H13_SETTINGS_T *pInfo=&_g_pe_cmg_hw_h13_info;
	#endif
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_FWI_H13_CHK_CEN_DOUBLE_SET
				/* check double setting */
				if(pInfo->gbl_ctrl.global_delta[0]!=pstParams->global_delta[0] || \
					pInfo->gbl_ctrl.global_delta[1]!=pstParams->global_delta[1] || \
					pInfo->gbl_ctrl.global_delta[2]!=pstParams->global_delta[2] || \
					pInfo->gbl_ctrl.global_delta[3]!=pstParams->global_delta[3] || \
					pInfo->gbl_ctrl.global_delta[4]!=pstParams->global_delta[4] || \
					pInfo->gbl_ctrl.global_delta[5]!=pstParams->global_delta[5])
				{
					set_flag=1;
				}
				if(set_flag)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
														hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
														hif_cen_address,	0x0);	//[7:0] address
					/* global master gain : 110 */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x6);	//[10:8]
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
					for(count=0;count<LX_PE_CMG_DELTANUM;count++)
					{
						wdata = GET_BITS(pstParams->global_delta[count],0,10);		// -512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
						PE_P1L_H13B0_Wr(pe1_cen_ia_data,	wdata);
						PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
					}
					/* normal operation */
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
					PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
					PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
					pInfo->gbl_ctrl.global_delta[0]=pstParams->global_delta[0];
					pInfo->gbl_ctrl.global_delta[1]=pstParams->global_delta[1];
					pInfo->gbl_ctrl.global_delta[2]=pstParams->global_delta[2];
					pInfo->gbl_ctrl.global_delta[3]=pstParams->global_delta[3];
					pInfo->gbl_ctrl.global_delta[4]=pstParams->global_delta[4];
					pInfo->gbl_ctrl.global_delta[5]=pstParams->global_delta[5];
				}
				#else
				PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
				PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address
				/* global master gain : 110 */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x6);	//[10:8]
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
				for(count=0;count<LX_PE_CMG_DELTANUM;count++)
				{
					wdata = GET_BITS(pstParams->global_delta[count],0,10);		// -512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
					PE_P1L_H13B0_Wr(pe1_cen_ia_data,	wdata);
					PE_P1L_H13B0_WrFL(pe1_cen_ia_data);
				}
				/* normal operation */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
				#endif
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_P1L_H13_RdFL(pe1_cen_ia_data);
				PE_P1L_H13_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address

				/* global master gain : 110 */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x6);	//[10:8]
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);				
				for(count=0;count<LX_PE_CMG_DELTANUM;count++)
				{
					wdata = GET_BITS(pstParams->global_delta[count],0,10);		// -512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
					PE_P1L_H13_Wr(pe1_cen_ia_data,	wdata);
					PE_P1L_H13_WrFL(pe1_cen_ia_data);
				}
				/* normal operation */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}
/**
 * get cen global ctrl
 *
 * @param   *pstParams [in/out] LX_PE_CMG_GLOBAL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMG_HW_H13_GetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	UINT32 count=0;
	UINT32 rdata=0;	// h,s,v,g,b,r
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_H13BX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13B0_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address
				/* global master gain : 110 for L9A0*/
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x6);	//[10:8]
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTANUM;count++)
				{
					PE_P1L_H13B0_RdFL(pe1_cen_ia_data);
					rdata = PE_P1L_H13B0_Rd(pe1_cen_ia_data);
					pstParams->global_delta[count] = (SINT16)PE_CONVHEX2DEC(rdata,9);// -512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
				}
				/* normal operation */
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13B0_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13B0_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else if(PE_KDRV_VER_H13AX)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_P1L_H13_QWr03(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x0,	//[15] 0:host access, 1:normal mode
													hif_cen_ai, 		0x1,	//[12] ai 0:disable, 1:enable
													hif_cen_address,	0x0);	//[7:0] address
				/* global master gain : 110 for L9A0*/
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x6);	//[10:8]
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);

				for(count=0;count<LX_PE_CMG_DELTANUM;count++)
				{
					PE_P1L_H13_RdFL(pe1_cen_ia_data);
					rdata = PE_P1L_H13_Rd(pe1_cen_ia_data);
					pstParams->global_delta[count] = (SINT16)PE_CONVHEX2DEC(rdata,9);// -512 ~ 511, [0]h [1]s [2]v [3]g [4]b [5]r
				}
				/* normal operation */
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_enable, 	0x1);	//[15] 0:host access, 1:normal mode
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai, 		0x0);	//[12] ai 0:disable, 1:enable
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_ai_sel, 	0x0);	//[10:8]
				PE_P1L_H13_Wr01(pe1_cen_ia_ctrl,	hif_cen_address,	0x0);	//[7:0] address
				PE_P1L_H13_WrFL(pe1_cen_ia_ctrl);
			}
		}
		else
		{
			PE_CMG_HW_H13_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	} while (0);
	return ret;
}

