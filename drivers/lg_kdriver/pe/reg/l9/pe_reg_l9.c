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


/** @file pe_reg_l9.c
 *
 *  driver for picture enhance register read, write functions. ( used only within kdriver )
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
#include "pe_def.h"
#include "pe_reg_l9.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_REG_L9_ERROR	printk

#ifdef PE_USE_DBG_PRINT
#define PE_REG_L9_DBG_PRINT(fmt,args...)	printk("[%x][%s,%d] "fmt,PE_CHIP_VER,__F__,__L__,##args)
#else
#define PE_REG_L9_DBG_PRINT(fmt,args...)
#endif

#define PE_REG_L9_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_REG_L9_ERROR(fmt,##args);_action;}}

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
PE_P0L_REG_L9_T gPE_P0L_L9;
PE_P0R_REG_L9_T gPE_P0R_L9;
PE_P1L_REG_L9_T gPE_P1L_L9;
PE_P1R_REG_L9_T gPE_P1R_L9;
PE_P0L_REG_L9B_T gPE_P0L_L9B;
PE_P0R_REG_L9B_T gPE_P0R_L9B;
PE_P1L_REG_L9B_T gPE_P1L_L9B;
PE_P1R_REG_L9B_T gPE_P1R_L9B;
PE_MSL_REG_L9_T gPE_MSL_L9;
PE_MSR_REG_L9_T gPE_MSR_L9;
PE_SSC_REG_L9_T gPE_SSC_L9;
PE_CVA_REG_L9_T gPE_CVA_L9;
PE_CVB_REG_L9_T gPE_CVB_L9;
PE_OVL_REG_L9_T gPE_OVL_L9;
PE_OVR_REG_L9_T gPE_OVR_L9;
PE_DEB_REG_L9_T gPE_DEB_L9;
PE_DEC_REG_L9_T gPE_DEC_L9;
PE_DED_REG_L9_T gPE_DED_L9;
PE_MIB_REG_L9_T gPE_MIB_L9;
PE_MID_REG_L9_T gPE_MID_L9;
PE_MIF_REG_L9_T gPE_MIF_L9;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_L9_InitPhyToVirt(void)
{
	int ret = RET_OK;
	do {
		if(PE_KDRV_VER_L9BX)
		{
			gPE_DEB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DEB_REG_L9B0_T));
			gPE_DEC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DEC_REG_L9B0_T));
			gPE_DED_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DED_REG_L9B0_T));
			gPE_CVA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CVA_REG_L9B0_T));
			gPE_CVB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CVB_REG_L9B0_T));
			gPE_P0L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0L_REG_L9B0_T));
			gPE_P0R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0R_REG_L9B0_T));
			gPE_P0L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0L_REG_L9B0_T));
			gPE_P0R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0R_REG_L9B0_T));
			gPE_MIB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MIB_REG_L9B0_T));
			gPE_MID_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MID_REG_L9B0_T));
			gPE_MIF_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MIF_REG_L9B0_T));
			gPE_MSL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MSL_REG_L9B0_T));
			gPE_MSR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MSR_REG_L9B0_T));
			gPE_OVL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OVL_REG_L9B0_T));
			gPE_OVR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OVR_REG_L9B0_T));
			gPE_P1L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1L_REG_L9B0_T));
			gPE_P1R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1R_REG_L9B0_T));
			gPE_P1L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1L_REG_L9B0_T));
			gPE_P1R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1R_REG_L9B0_T));
			gPE_SSC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SSC_REG_L9B0_T));
			gPE_DEB_L9.phys.addr = (volatile UINT32 *)ioremap(PE_DEB_REG_L9_BASE, sizeof(PE_DEB_REG_L9B0_T));
			gPE_DEC_L9.phys.addr = (volatile UINT32 *)ioremap(PE_DEC_REG_L9_BASE, sizeof(PE_DEC_REG_L9B0_T));
			gPE_DED_L9.phys.addr = (volatile UINT32 *)ioremap(PE_DED_REG_L9_BASE, sizeof(PE_DED_REG_L9B0_T));
			gPE_CVA_L9.phys.addr = (volatile UINT32 *)ioremap(PE_CVA_REG_L9_BASE, sizeof(PE_CVA_REG_L9B0_T));
			gPE_CVB_L9.phys.addr = (volatile UINT32 *)ioremap(PE_CVB_REG_L9_BASE, sizeof(PE_CVB_REG_L9B0_T));
			gPE_P0L_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P0L_REG_L9_BASE, sizeof(PE_P0L_REG_L9B0_T));
			gPE_P0R_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P0R_REG_L9_BASE, sizeof(PE_P0R_REG_L9B0_T));
			gPE_P0L_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P0L_REG_L9_BASE, sizeof(PE_P0L_REG_L9B0_T));
			gPE_P0R_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P0R_REG_L9_BASE, sizeof(PE_P0R_REG_L9B0_T));
			gPE_MIB_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MIB_REG_L9_BASE, sizeof(PE_MIB_REG_L9B0_T));
			gPE_MID_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MID_REG_L9B0_BASE, sizeof(PE_MID_REG_L9B0_T));
			gPE_MIF_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MIF_REG_L9B0_BASE, sizeof(PE_MIF_REG_L9B0_T));
			gPE_MSL_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MSL_REG_L9_BASE, sizeof(PE_MSL_REG_L9B0_T));
			gPE_MSR_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MSR_REG_L9_BASE, sizeof(PE_MSR_REG_L9B0_T));
			gPE_OVL_L9.phys.addr = (volatile UINT32 *)ioremap(PE_OVL_REG_L9_BASE, sizeof(PE_OVL_REG_L9B0_T));
			gPE_OVR_L9.phys.addr = (volatile UINT32 *)ioremap(PE_OVR_REG_L9_BASE, sizeof(PE_OVR_REG_L9B0_T));
			gPE_P1L_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P1L_REG_L9_BASE, sizeof(PE_P1L_REG_L9B0_T));
			gPE_P1R_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P1R_REG_L9_BASE, sizeof(PE_P1R_REG_L9B0_T));
			gPE_P1L_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P1L_REG_L9_BASE, sizeof(PE_P1L_REG_L9B0_T));
			gPE_P1R_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P1R_REG_L9_BASE, sizeof(PE_P1R_REG_L9B0_T));
			gPE_SSC_L9.phys.addr = (volatile UINT32 *)ioremap(PE_SSC_REG_L9_BASE, sizeof(PE_SSC_REG_L9B0_T));
		}
		else if(PE_KDRV_VER_L9AX)
		{
			gPE_DEB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DEB_REG_L9A0_T));
			gPE_DEC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DEC_REG_L9A0_T));
			gPE_DED_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_DED_REG_L9A0_T));
			gPE_CVA_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CVA_REG_L9A0_T));
			gPE_CVB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_CVB_REG_L9A0_T));
			gPE_P0L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0L_REG_L9A0_T));
			gPE_P0R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0R_REG_L9A0_T));
			gPE_P0L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0L_REG_L9B0_T));
			gPE_P0R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P0R_REG_L9B0_T));
			gPE_MIB_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MIB_REG_L9A0_T));
			gPE_MID_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MID_REG_L9A0_T));
			gPE_MSL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MSL_REG_L9A0_T));
			gPE_MSR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_MSR_REG_L9A0_T));
			gPE_OVL_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OVL_REG_L9A0_T));
			gPE_OVR_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_OVR_REG_L9A0_T));
			gPE_P1L_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1L_REG_L9A0_T));
			gPE_P1R_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1R_REG_L9A0_T));
			gPE_P1L_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1L_REG_L9B0_T));
			gPE_P1R_L9B.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_P1R_REG_L9B0_T));
			gPE_SSC_L9.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(PE_SSC_REG_L9A0_T));
			gPE_DEB_L9.phys.addr = (volatile UINT32 *)ioremap(PE_DEB_REG_L9_BASE, sizeof(PE_DEB_REG_L9A0_T));
			gPE_DEC_L9.phys.addr = (volatile UINT32 *)ioremap(PE_DEC_REG_L9_BASE, sizeof(PE_DEC_REG_L9A0_T));
			gPE_DED_L9.phys.addr = (volatile UINT32 *)ioremap(PE_DED_REG_L9_BASE, sizeof(PE_DED_REG_L9A0_T));
			gPE_CVA_L9.phys.addr = (volatile UINT32 *)ioremap(PE_CVA_REG_L9_BASE, sizeof(PE_CVA_REG_L9A0_T));
			gPE_CVB_L9.phys.addr = (volatile UINT32 *)ioremap(PE_CVB_REG_L9_BASE, sizeof(PE_CVB_REG_L9A0_T));
			gPE_P0L_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P0L_REG_L9_BASE, sizeof(PE_P0L_REG_L9A0_T));
			gPE_P0R_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P0R_REG_L9_BASE, sizeof(PE_P0R_REG_L9A0_T));
			gPE_P0L_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P0L_REG_L9_BASE, sizeof(PE_P0L_REG_L9B0_T));
			gPE_P0R_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P0R_REG_L9_BASE, sizeof(PE_P0R_REG_L9B0_T));
			gPE_MIB_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MIB_REG_L9_BASE, sizeof(PE_MIB_REG_L9A0_T));
			gPE_MID_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MID_REG_L9_BASE, sizeof(PE_MID_REG_L9A0_T));
			gPE_MSL_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MSL_REG_L9_BASE, sizeof(PE_MSL_REG_L9A0_T));
			gPE_MSR_L9.phys.addr = (volatile UINT32 *)ioremap(PE_MSR_REG_L9_BASE, sizeof(PE_MSR_REG_L9A0_T));
			gPE_OVL_L9.phys.addr = (volatile UINT32 *)ioremap(PE_OVL_REG_L9_BASE, sizeof(PE_OVL_REG_L9A0_T));
			gPE_OVR_L9.phys.addr = (volatile UINT32 *)ioremap(PE_OVR_REG_L9_BASE, sizeof(PE_OVR_REG_L9A0_T));
			gPE_P1L_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P1L_REG_L9_BASE, sizeof(PE_P1L_REG_L9A0_T));
			gPE_P1R_L9.phys.addr = (volatile UINT32 *)ioremap(PE_P1R_REG_L9_BASE, sizeof(PE_P1R_REG_L9A0_T));
			gPE_P1L_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P1L_REG_L9_BASE, sizeof(PE_P1L_REG_L9B0_T));
			gPE_P1R_L9B.phys.addr = (volatile UINT32 *)ioremap(PE_P1R_REG_L9_BASE, sizeof(PE_P1R_REG_L9B0_T));
			gPE_SSC_L9.phys.addr = (volatile UINT32 *)ioremap(PE_SSC_REG_L9_BASE, sizeof(PE_SSC_REG_L9A0_T));
		}
		else
		{
			PE_REG_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	return ret;
}
/**
 * free phy to virtual addr
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_L9_FreePhyToVirt(void)
{
	OS_Free((void *)gPE_DEB_L9.shdw.addr);
	OS_Free((void *)gPE_DEC_L9.shdw.addr);
	OS_Free((void *)gPE_DED_L9.shdw.addr);
	OS_Free((void *)gPE_CVA_L9.shdw.addr);
	OS_Free((void *)gPE_CVB_L9.shdw.addr);
	OS_Free((void *)gPE_P0L_L9.shdw.addr);
	OS_Free((void *)gPE_P0R_L9.shdw.addr);
	OS_Free((void *)gPE_P0L_L9B.shdw.addr);
	OS_Free((void *)gPE_P0R_L9B.shdw.addr);
	OS_Free((void *)gPE_MIB_L9.shdw.addr);
	OS_Free((void *)gPE_MID_L9.shdw.addr);
	OS_Free((void *)gPE_MIF_L9.shdw.addr);
	OS_Free((void *)gPE_MSL_L9.shdw.addr);
	OS_Free((void *)gPE_MSR_L9.shdw.addr);
	OS_Free((void *)gPE_OVL_L9.shdw.addr);
	OS_Free((void *)gPE_OVR_L9.shdw.addr);
	OS_Free((void *)gPE_P1L_L9.shdw.addr);
	OS_Free((void *)gPE_P1R_L9.shdw.addr);
	OS_Free((void *)gPE_P1L_L9B.shdw.addr);
	OS_Free((void *)gPE_P1R_L9B.shdw.addr);
	OS_Free((void *)gPE_SSC_L9.shdw.addr);
	if(gPE_DEB_L9.phys.addr) iounmap((void *)gPE_DEB_L9.phys.addr);
	if(gPE_DEC_L9.phys.addr) iounmap((void *)gPE_DEC_L9.phys.addr);
	if(gPE_DED_L9.phys.addr) iounmap((void *)gPE_DED_L9.phys.addr);
	if(gPE_CVA_L9.phys.addr) iounmap((void *)gPE_CVA_L9.phys.addr);
	if(gPE_CVB_L9.phys.addr) iounmap((void *)gPE_CVB_L9.phys.addr);
	if(gPE_P0L_L9.phys.addr) iounmap((void *)gPE_P0L_L9.phys.addr);
	if(gPE_P0R_L9.phys.addr) iounmap((void *)gPE_P0R_L9.phys.addr);
	if(gPE_P0L_L9B.phys.addr) iounmap((void *)gPE_P0L_L9B.phys.addr);
	if(gPE_P0R_L9B.phys.addr) iounmap((void *)gPE_P0R_L9B.phys.addr);
	if(gPE_MIB_L9.phys.addr) iounmap((void *)gPE_MIB_L9.phys.addr);
	if(gPE_MID_L9.phys.addr) iounmap((void *)gPE_MID_L9.phys.addr);
	if(gPE_MIF_L9.phys.addr) iounmap((void *)gPE_MIF_L9.phys.addr);
	if(gPE_MSL_L9.phys.addr) iounmap((void *)gPE_MSL_L9.phys.addr);
	if(gPE_MSR_L9.phys.addr) iounmap((void *)gPE_MSR_L9.phys.addr);
	if(gPE_OVL_L9.phys.addr) iounmap((void *)gPE_OVL_L9.phys.addr);
	if(gPE_OVR_L9.phys.addr) iounmap((void *)gPE_OVR_L9.phys.addr);
	if(gPE_P1L_L9.phys.addr) iounmap((void *)gPE_P1L_L9.phys.addr);
	if(gPE_P1R_L9.phys.addr) iounmap((void *)gPE_P1R_L9.phys.addr);
	if(gPE_P1L_L9B.phys.addr) iounmap((void *)gPE_P1L_L9B.phys.addr);
	if(gPE_P1R_L9B.phys.addr) iounmap((void *)gPE_P1R_L9B.phys.addr);
	if(gPE_SSC_L9.phys.addr) iounmap((void *)gPE_SSC_L9.phys.addr);
	return RET_OK;
}
/**
 * write address data
 *
 * @param   addr [in] UINT32
 * @param   value [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_REG_L9_WD(UINT32 addr, UINT32 value)
{
	int ret = RET_OK;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 virtAddr = 0;
	do{
		if(PE_KDRV_VER_L9BX)
		{
	        recvAddr = addr;
	        if      (recvAddr <= 0x6000) recvAddr += PE_DTVSOC_DE_L9_BASE;
	        else if (recvAddr <= 0xffff) recvAddr += PE_DTVSOC_DE_L9_BASE;
	        currAddr = recvAddr;
	        currAddr >>= 2;
	        currAddr <<= 2;

			virtAddr = (UINT32)ioremap(currAddr, 0x8);
	        if (currAddr == recvAddr) {
	            REG_WD(virtAddr, value);
	            break;
	        }
	        currValue = REG_RD(virtAddr);
	        nextValue = REG_RD((virtAddr+4));

	        dBit = (recvAddr - currAddr)<<3;
	        wBit = (32 - dBit);

	        currValue  = GET_BITS(currValue ,0    ,dBit);
	        currValue += GET_PVAL(value     ,dBit ,wBit);

	        nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
	        nextValue += GET_BITS(value     ,0    ,dBit);
	        REG_WD(virtAddr     ,currValue);
	        REG_WD((virtAddr+4) ,nextValue);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			recvAddr = addr;
			if		(recvAddr <= 0x4000) recvAddr += L9_DE_BASE;
			else if (recvAddr <= 0xffff) recvAddr += L9_PL301_BASE;
			currAddr = recvAddr;
			currAddr >>= 2;
			currAddr <<= 2;

			virtAddr = (UINT32)ioremap(currAddr, 0x8);
			if (currAddr == recvAddr) {
				REG_WD(virtAddr, value);
				break;
			}
			currValue = REG_RD(virtAddr);
			nextValue = REG_RD((virtAddr+4));

			dBit = (recvAddr - currAddr)<<3;
			wBit = (32 - dBit);

			currValue  = GET_BITS(currValue ,0	  ,dBit);
			currValue += GET_PVAL(value		,dBit ,wBit);

			nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
			nextValue += GET_BITS(value		,0	  ,dBit);
			REG_WD(virtAddr		,currValue);
			REG_WD((virtAddr+4) ,nextValue);
		}
		else
		{
			PE_REG_L9_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	if (virtAddr) iounmap((void *)virtAddr);
	return ret;
}

/**
 * read address data
 *
 * @param   addr [in] UINT32, accessing for register
 * @return  value of register
 * @see
 * @author
 */
UINT32 PE_REG_L9_RD(UINT32 addr)
{
	UINT32 value = 0x0;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	UINT32 virtAddr = 0;
	do{
		if(PE_KDRV_VER_L9BX)
		{
	        recvAddr = addr;
	        if      (recvAddr <= 0x6000) recvAddr += PE_DTVSOC_DE_L9_BASE;
	        else if (recvAddr <= 0xffff) recvAddr += PE_DTVSOC_DE_L9_BASE;

	        currAddr = recvAddr;
	        currAddr >>= 2;
	        currAddr <<= 2;
			virtAddr = (UINT32)ioremap(currAddr, 0x8);

	        value = REG_RD(virtAddr);
	        if (currAddr == recvAddr) break;

	        nextValue = REG_RD(virtAddr+4);
	        dBit = (recvAddr - currAddr)<<3;
	        wBit = (32 - dBit);
	        value  = GET_BITS(value, dBit, wBit);
	        value += GET_PVAL(nextValue, wBit, dBit);
		}
		else if(PE_KDRV_VER_L9AX)
		{
			recvAddr = addr;
			if		(recvAddr <= 0x4000) recvAddr += L9_DE_BASE;
			else if (recvAddr <= 0xffff) recvAddr += L9_PL301_BASE;

			currAddr = recvAddr;
			currAddr >>= 2;
			currAddr <<= 2;
			virtAddr = (UINT32)ioremap(currAddr, 0x8);

			value = REG_RD(virtAddr);
			if (currAddr == recvAddr) break;

			nextValue = REG_RD(virtAddr+4);
			dBit = (recvAddr - currAddr)<<3;
			wBit = (32 - dBit);
			value  = GET_BITS(value, dBit, wBit);
			value += GET_PVAL(nextValue, wBit, dBit);
		}
		else
		{
			PE_REG_L9_DBG_PRINT("nothing to do.\n");
		}
	}while(0);
	if (virtAddr) iounmap((void *)virtAddr);
	return value;
}

