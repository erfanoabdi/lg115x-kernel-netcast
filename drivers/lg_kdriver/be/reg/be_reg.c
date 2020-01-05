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
 *  BE reg driver file for BE device
 *	
 *  author		won.hur	
 *  version		1.0
 *  date		2012.04.18
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
#include <asm/io.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_reg.h"
#include "be_kapi.h"
#include "h13/be_reg_def_h13.h"
#include "h13/be_dppb_reg_h13.h"
#include "h13/be_frc_reg_h13.h"

#include "../sys/sys_regs.h"
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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
FRC_LRX_REG_H13_T gFRC_LRX_H13;
FRC_P3D_REG_H13_T gFRC_P3D_H13;
FRC_DVI_REG_H13_T gFRC_DVI_H13;
FRC_DVO_REG_H13_T gFRC_DVO_H13;

DPPB_TOP_REG_H13_T gDPPB_TOP_H13;
DPPB_TXM_REG_H13_T gDPPB_TXM_H13;
DPPB_LED_REG_H13_T gDPPB_LED_H13;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _BE_REG_RegWrite(UINT32 arg);
static int _BE_REG_RegRead(UINT32 arg);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_REG_Init(void)
{
	int ret = RET_OK;

	/* Comment from won.hur 2012.05.18 
	 * Added chip revision selection code for multi-usages of this code
	 */
	if(lx_chip_rev() >= LX_CHIP_REV( H13, A0))
	{
		gFRC_LRX_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(FRC_LRX_REG_H13A0_T));
		gFRC_P3D_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(FRC_P3D_REG_H13A0_T));
		gFRC_DVI_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(FRC_DVI_REG_H13A0_T));
		gFRC_DVO_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(FRC_DVO_REG_H13A0_T));

		gDPPB_TOP_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DPPB_TOP_REG_H13A0_T));
		gDPPB_TXM_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DPPB_TXM_REG_H13A0_T));
		gDPPB_LED_H13.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(DPPB_LED_REG_H13A0_T));

		gFRC_LRX_H13.phys.addr = (volatile UINT32 *)ioremap(FRC_LRX_REG_H13_BASE, sizeof(FRC_LRX_REG_H13A0_T));
		gFRC_P3D_H13.phys.addr = (volatile UINT32 *)ioremap(FRC_P3D_REG_H13_BASE, sizeof(FRC_P3D_REG_H13A0_T));
		gFRC_DVI_H13.phys.addr = (volatile UINT32 *)ioremap(FRC_DVI_REG_H13_BASE, sizeof(FRC_DVI_REG_H13A0_T));
		gFRC_DVO_H13.phys.addr = (volatile UINT32 *)ioremap(FRC_DVO_REG_H13_BASE, sizeof(FRC_DVO_REG_H13A0_T));

		gDPPB_TOP_H13.phys.addr = (volatile UINT32 *)ioremap(DPPB_TOP_REG_H13_BASE, sizeof(DPPB_TOP_REG_H13A0_T));
		gDPPB_TXM_H13.phys.addr = (volatile UINT32 *)ioremap(DPPB_TXM_REG_H13_BASE, sizeof(DPPB_TXM_REG_H13A0_T));
		gDPPB_LED_H13.phys.addr = (volatile UINT32 *)ioremap(DPPB_LED_REG_H13_BASE, sizeof(DPPB_LED_REG_H13A0_T));
	}

	return ret;
}

int BE_REG_Free(void)
{
	int ret = RET_OK;
    
	OS_Free((void *)gFRC_LRX_H13.shdw.addr);
	OS_Free((void *)gFRC_P3D_H13.shdw.addr);
	OS_Free((void *)gFRC_DVI_H13.shdw.addr);
	OS_Free((void *)gFRC_DVO_H13.shdw.addr);

	OS_Free((void *)gDPPB_TOP_H13.shdw.addr);
	OS_Free((void *)gDPPB_TXM_H13.shdw.addr);
	OS_Free((void *)gDPPB_LED_H13.shdw.addr);

    	if (gFRC_LRX_H13.phys.addr) iounmap((void *)gFRC_LRX_H13.phys.addr);
    	if (gFRC_P3D_H13.phys.addr) iounmap((void *)gFRC_P3D_H13.phys.addr);
    	if (gFRC_DVI_H13.phys.addr) iounmap((void *)gFRC_DVI_H13.phys.addr);
	if (gFRC_DVO_H13.phys.addr) iounmap((void *)gFRC_DVO_H13.phys.addr);
	
    	if (gDPPB_TOP_H13.phys.addr) iounmap((void *)gDPPB_TOP_H13.phys.addr);
    	if (gDPPB_TXM_H13.phys.addr) iounmap((void *)gDPPB_TXM_H13.phys.addr);
    	if (gDPPB_LED_H13.phys.addr) iounmap((void *)gDPPB_LED_H13.phys.addr);
	
	return ret;
}

int BE_REG_SwReset(void)
{
	int ret = RET_OK;

	CTOP_CTRL_H13A0_RdFL(ctr29);
	CTOP_CTRL_H13A0_Wr01(ctr29, swrst_dppb_cpu, 1); // MCU reset 1
	CTOP_CTRL_H13A0_WrFL(ctr29);
	
	CTOP_CTRL_H13A0_RdFL(ctr29);
	CTOP_CTRL_H13A0_Wr01(ctr29, swrst_dppb_cpu, 0); // MCU reset 0
	CTOP_CTRL_H13A0_WrFL(ctr29);
	
	return ret;
}

int BE_REG_Uart0_Switch(BOOLEAN isForMcu)
{
	int ret = RET_OK;

	CTOP_CTRL_H13A0_RdFL(ctr58);
	if(isForMcu)
	{
		CTOP_CTRL_H13A0_Wr01(ctr58, uart0_sel, 6); // UART0 =hdp 
		CTOP_CTRL_H13A0_Wr01(ctr58, uart1_sel, 2); // UART1 = cpu0
		CTOP_CTRL_H13A0_Wr01(ctr58, rx_sel_hdpmcu1, 0); // 0:HDP from UART0
	}
	else
	{
		CTOP_CTRL_H13A0_Wr01(ctr58, uart0_sel, 2); // UART0 = cpu0
		CTOP_CTRL_H13A0_Wr01(ctr58, uart1_sel, 1); // UART1 = de
		CTOP_CTRL_H13A0_Wr01(ctr58, rx_sel_hdpmcu0, 1); // 2:DE from UART1
	}
	CTOP_CTRL_H13A0_WrFL(ctr58);

	return ret;
}

int BE_REG_RegAccess(UINT32 arg)
{
	int ret = RET_ERROR;

	BOOLEAN isRead = FALSE;

	BE_REG_RW_TYPE_T type;
	BE_REG_RW_T reg_addr_data_t;
	
	if( copy_from_user(&reg_addr_data_t, (void __user *)arg, sizeof(BE_REG_RW_T)))
	{
		return -EFAULT;
	}

	type   = reg_addr_data_t.type;
	isRead = reg_addr_data_t.isRead;

	BE_DEBUG("BE_REG_RegAccess(%d, %d, 0x%08x, 0x%08x) is called. \n", type, isRead, reg_addr_data_t.addr, reg_addr_data_t.data);

	if(isRead) ret = _BE_REG_RegRead(arg);
	else ret = _BE_REG_RegWrite(arg);

	return ret;
}



/* Comment from won.hur 2012.05.18
 * Added TXM register access function for free-access-to-register from user level
 */
static int _BE_REG_RegRead(UINT32 arg)
{
	UINT32 value;
	BE_REG_RW_TYPE_T recvType = BE_REG_RW_TYPE_NONE;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 dBit;
	UINT32 wBit;
	
	BE_REG_RW_T	reg_addr_data_t;

	/* Step 1. Get data from user-level */
	if( copy_from_user(&reg_addr_data_t, (void __user *)arg, sizeof(BE_REG_RW_T)))
	{
		return -EFAULT;
	}

	/* Step 2. Read HW register */
	do{
		recvAddr  = reg_addr_data_t.addr;
		recvType  = reg_addr_data_t.type;

		switch(recvType)
		{
			case BE_REG_RW_TYPE_NONE:
				return RET_ERROR;
				break;
			case BE_REG_RW_TYPE_DPPB_TXM:
				recvAddr += (UINT32)gDPPB_TXM_H13.phys.addr;
				break;
			case BE_REG_RW_TYPE_DPPB_TOP:
				recvAddr += (UINT32)gDPPB_TOP_H13.phys.addr;
				break;
			case BE_REG_RW_TYPE_DPPB_LED:
				recvAddr += (UINT32)gDPPB_LED_H13.phys.addr;
				break;
		default :
				return RET_ERROR;
				break;
		}

		currAddr = recvAddr;
		/* for safety */
		currAddr >>= 2; 
		currAddr <<= 2;

		value = REG_RD(currAddr);
		if(currAddr == recvAddr) break;
		nextValue = REG_RD(currAddr+4);
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		value  = GET_BITS(value, dBit, wBit);
		value += GET_PVAL(nextValue, wBit, dBit);
	} while(0);
	
	reg_addr_data_t.data = value;

	if(copy_to_user((UINT32*)arg, (UINT32*)&reg_addr_data_t, sizeof(BE_REG_RW_T)))
	{
		return -EFAULT;
	}

	return 0;
}

static int _BE_REG_RegWrite(UINT32 arg)
{
	UINT32 value;
	BE_REG_RW_TYPE_T recvType = BE_REG_RW_TYPE_NONE;
	UINT32 recvAddr;
	UINT32 currAddr;
	UINT32 nextValue;
	UINT32 currValue;
	UINT32 dBit;
	UINT32 wBit;
	
	BE_REG_RW_T	reg_addr_data_t;

	/* Step 1. Get data from user-level */
	if( copy_from_user(&reg_addr_data_t, (void __user *)arg, sizeof(BE_REG_RW_T)))
	{
		return -EFAULT;
	}

	/* Step 2. Read HW register */
	do{
		recvAddr  = reg_addr_data_t.addr;
		value = reg_addr_data_t.data;
		recvType  = reg_addr_data_t.type;

		switch(recvType)
		{
			case BE_REG_RW_TYPE_NONE:
				return RET_ERROR;
				break;
			case BE_REG_RW_TYPE_DPPB_TXM:
				recvAddr += (UINT32)gDPPB_TXM_H13.phys.addr;
				break;
			case BE_REG_RW_TYPE_DPPB_TOP:
				recvAddr += (UINT32)gDPPB_TOP_H13.phys.addr;
				break;
			case BE_REG_RW_TYPE_DPPB_LED:
				recvAddr += (UINT32)gDPPB_LED_H13.phys.addr;
				break;
		default :
				return RET_ERROR;
				break;
		}

		currAddr = recvAddr;
		
		/* for safety */
		currAddr >>= 2; 
		currAddr <<= 2;

		if(currAddr == recvAddr)
		{
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(currAddr);
		nextValue = REG_RD((currAddr+4));
		dBit = (recvAddr - currAddr)<<3;
		wBit = (32 - dBit);
		currValue  = GET_BITS(currValue, 0, dBit);
		currValue += GET_PVAL(value    , dBit, wBit);
		nextValue  = GET_PVAL(nextValue, dBit, wBit);
		nextValue += GET_BITS(value    , 0	 , dBit);
		REG_WD(currAddr	, currValue);
		REG_WD((currAddr+4), nextValue);
	}
	while(0);
	
	return 0;
}

