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
 *  main driver implementation for sys device.
 *	sys device will teach you how to make device driver with new platform.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2010.12.13
 *  note		Additional information.
 *
 *  @addtogroup lg1150_sys
 *	@{
 */


/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "sys_drv.h"
#include "reg_ctrl.h"
#include "i2c_drv.h"
#include "i2c_core.h"

#include "ctop_regs.h"


#include "sys_regs.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct{
	UINT8	ch;
	UINT8	clock;
} LX_I2C_INTERNAL_T;

typedef struct
{
	UINT32				chip;
	UINT32				num_internals;
	LX_I2C_INTERNAL_T*	internal;		/* channels should be inited at initial time */
} LX_REG_CTRL_CFG_T;


/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/
CTOP_CTRL_T gCTOP_CTRL;				// CTOP for L8
CTOP_CTRL_REG_L9_T gCTOP_CTRL_L9;	// CTOP for L9 A0
CTOP_CTRL_REG_L9B_T gCTOP_CTRL_L9B;	// CTOP for L9 B0
CTOP_CTRL_REG_H13_T gCTOP_CTRL_H13;

// ACE Registers
ACE_REG_CTRL_L9_T	gACE_REG_CTRL_L9;
ACE_REG_CTRL_H13_T	gACE_REG_CTRL_H13;

// CPU TOP Control Registers
CPU_TOP_REG_H13_T	gCPU_TOP_REG_H13;


/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/

static LX_I2C_INTERNAL_T _stI2cInternalL9A0[] ={
	{4, I2C_CLOCK_400KHZ},
};
static LX_I2C_INTERNAL_T _stI2cInternalL9A1[] = {
	{8, I2C_CLOCK_2MHZ}
};
static LX_I2C_INTERNAL_T _stI2cInternalH13A0[] = {
	{8, I2C_CLOCK_400KHZ},	// ACE
	{9, I2C_CLOCK_400KHZ}	// HIDMI PHY
};


static LX_REG_CTRL_CFG_T _stRegCtrlConfigs[] =
{
	{
		.chip = LX_CHIP_REV(L9,A0),
		.num_internals = 1,
		.internal = _stI2cInternalL9A0,
	},
	{
		.chip = LX_CHIP_REV(L9,A1),
		.num_internals = 1,
		.internal = _stI2cInternalL9A1,
	},
	{
		.chip = LX_CHIP_REV(H13,A0),
		.num_internals = 2,
		.internal = _stI2cInternalH13A0,
	},
};

static LX_REG_CTRL_CFG_T _stDummyConfig =
{
	.num_internals = 0,
};

static LX_I2C_DEV_HANDLE *_i2c_handle;
static LX_REG_CTRL_CFG_T *_config = &_stDummyConfig;

static void InitConfig(void)
{
	int i;
	UINT32 chip = lx_chip_rev();

	for(i=0; i < sizeof(_stRegCtrlConfigs)/sizeof(LX_REG_CTRL_CFG_T); i++)
	{
		if(chip >= _stRegCtrlConfigs[i].chip) _config = &_stRegCtrlConfigs[i];
		else break;
	}
}


int REG_CTRL_Init(void)
{
	int regs_size;

	InitConfig();

	if (lx_chip_rev() >= LX_CHIP_REV(H13,B0))
	{
		regs_size = sizeof(CTOP_CTRL_REG_H13B0_T);
		gCTOP_CTRL_H13.phys.addr = (volatile UINT32 *)ioremap(H13_CTOP_REG_BASE, regs_size);
		gCTOP_CTRL_H13.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);

		regs_size = sizeof(CPU_TOP_REG_H13A0_T);
		gCPU_TOP_REG_H13.phys.addr = (volatile UINT32 *)ioremap(H13_TOPCTRL_BASE, regs_size);
		gCPU_TOP_REG_H13.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);
	}
	else if (lx_chip_rev() >= LX_CHIP_REV(H13,A0))
	{
		regs_size = sizeof(CTOP_CTRL_REG_H13A0_T);
		gCTOP_CTRL_H13.phys.addr = (volatile UINT32 *)ioremap(H13_CTOP_REG_BASE, regs_size);
		gCTOP_CTRL_H13.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);

		regs_size = sizeof(CPU_TOP_REG_H13A0_T);
		gCPU_TOP_REG_H13.phys.addr = (volatile UINT32 *)ioremap(H13_TOPCTRL_BASE, regs_size);
		gCPU_TOP_REG_H13.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);
	}
	else if(lx_chip_rev() >= LX_CHIP_REV(L9,A0))
	{
		if (lx_chip_rev() >= LX_CHIP_REV(L9,B0))
		{
			regs_size = sizeof(CTOP_CTRL_REG_L9B0_T);

			gCTOP_CTRL_L9B.phys.addr = (volatile UINT32 *)ioremap(L9_TOPCTRL_BASE, regs_size);
			gCTOP_CTRL_L9B.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);
		}

		/* A1 & B0 ctop are used at same time */
		regs_size = sizeof(CTOP_CTRL_REG_L9A0_T);

		gCTOP_CTRL_L9.phys.addr = (volatile UINT32 *)ioremap(L9_TOPCTRL_BASE, regs_size);
		gCTOP_CTRL_L9.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);
	}
 	else if (lx_chip_rev() >= LX_CHIP_REV(L8,B0))
	{
		regs_size = sizeof(CTOP_CTRL_REG_B0_T);

		gCTOP_CTRL.phys.addr = (volatile UINT32 *)ioremap(L8_TOP_CTRL, regs_size);
		gCTOP_CTRL.shadow.addr = (UINT32 *)OS_KMalloc(regs_size);
	}
	else
	{
		regs_size = sizeof(CTOP_CTRL_REG_A0_T);

		gCTOP_CTRL.phys.addr = (volatile UINT32 *)ioremap(L8_TOP_CTRL, regs_size);
		gCTOP_CTRL.shadow.addr = (UINT32 *)OS_KMalloc(regs_size);
	}


	// Init ACE registers and etc...
	if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_H13)) 	/* H13 */
	{
		regs_size = sizeof(ACE_REG_H13A0_T);	// max size
		gACE_REG_CTRL_H13.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);

		/* select HDMI PHY i2c clock : 0(3Mhz), 1(24Mhz) */
		CTOP_CTRL_H13A0_RdFL(ctr01);
		CTOP_CTRL_H13A0_Wr01(ctr01,phy_i2c_clk_sel,1);
		CTOP_CTRL_H13A0_WrFL(ctr01);
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L9))	/* L9 */
	{
		regs_size = sizeof(ACE_REG_L9B0_T);		// max size
		gACE_REG_CTRL_L9.shdw.addr = (UINT32 *)OS_KMalloc(regs_size);
	}


	if(_config->num_internals > 0)
	{
		int i;

		I2C_Init();

		_i2c_handle = (LX_I2C_DEV_HANDLE*)OS_KMalloc(sizeof(LX_I2C_DEV_HANDLE) * _config->num_internals);
		for(i=0; i<_config->num_internals; i++)
		{
			_i2c_handle[i] = I2C_DevOpenPriv(_config->internal[i].ch, 1);

			if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_H13)) 	/* H13 */
			{
				I2C_DevSetClock(_i2c_handle[i], _config->internal[i].clock);
				if(i == 0)
				{
					ACE_REG_H13A0_RdFL(h13a_version_0);
					SYS_DEBUG("H13A VER : 0x%02x\n", ACE_REG_H13A0_Rd(h13a_version_0));
				}
			}
			else if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L9))	/* L9 */
			{
				UINT32 initial_clock = (_config->internal[i].clock > I2C_CLOCK_2MHZ) ?
													I2C_CLOCK_2MHZ : _config->internal[i].clock;
				I2C_DevSetClock(_i2c_handle[i], initial_clock);
				if ( lx_chip_rev() >= LX_CHIP_REV_L9_A0)
				{
					ACE_REG_L9B0_RdFL(soft_reset_0);
					ACE_REG_L9B0_Wr01(soft_reset_0,swrst_f24m,0);
					ACE_REG_L9B0_WrFL(soft_reset_0);

					ACE_REG_L9B0_RdFL(main_pll_4);
					ACE_REG_L9B0_Wr01(main_pll_4,dr3p_pdb,0);
					ACE_REG_L9B0_WrFL(main_pll_4);

					ACE_REG_L9B0_RdFL(main_pll_4);
					ACE_REG_L9B0_Wr01(main_pll_4,dr3p_pdb,1);
					ACE_REG_L9B0_WrFL(main_pll_4);

					if(_config->internal[i].clock > I2C_CLOCK_2MHZ)
					{
						mdelay(1);
						// Internal I2C support upto 8Mhz
						ACE_REG_L9B0_RdFL(hostif_control_0);
						ACE_REG_L9B0_Wr01(hostif_control_0,reg_sel_hostif_clock,1);
						ACE_REG_L9B0_WrFL(hostif_control_0);

						mdelay(1);
						ACE_REG_L9B0_RdFL(hostif_control_0);
						if(ACE_REG_L9B0_RdFd(hostif_control_0,ro_hostif_is_162mhz) == 1)
							SYS_DEBUG("Set Internal I2C 162MHZ Clock !!!!\n");

						I2C_DevSetClock(_i2c_handle[i], _config->internal[i].clock);
					}
				}
			}
			else
			{
				I2C_DevSetClock(_i2c_handle[i], _config->internal[i].clock);
			}
		}
	}


#if 0	// MACRO TEST
	ACE_REG_H13A0_RdFL(h13a_version_0);

	CTOP_CTRL_H13A0_RdFL(ctr00_reg_rst_sel);
	CTOP_CTRL_H13A0_Wr01(ctr00_reg_rst_sel,reg_afifo_r,0);
	CTOP_CTRL_H13A0_WrFL(ctr00_reg_rst_sel);

	CPU_TOP_H13A0_RdFL(cpu0_addr_sw_reg_0);
	CPU_TOP_H13A0_Wr01(cpu0_addr_sw_reg_0,cpu0_paddr_app_nor_boot,2);
	CPU_TOP_H13A0_WrFL(cpu0_addr_sw_reg_0);
#endif

	return 0;
}

int REG_CTRL_Free(void)
{
	if (lx_chip_rev() >= LX_CHIP_REV(H13,A0))
	{
		OS_Free((void *)gCTOP_CTRL_H13.shdw.addr);
		if(gCTOP_CTRL_H13.phys.addr) iounmap((void *)gCTOP_CTRL_H13.phys.addr);

		OS_Free((void *)gCPU_TOP_REG_H13.shdw.addr);
		if(gCPU_TOP_REG_H13.phys.addr) iounmap((void *)gCPU_TOP_REG_H13.phys.addr);
	}
	else if(lx_chip_rev() >= LX_CHIP_REV(L9,A0))
	{
		if (lx_chip_rev() >= LX_CHIP_REV(L9,B0))
		{
			OS_Free((void *)gCTOP_CTRL_L9B.shdw.addr);
			if(gCTOP_CTRL_L9B.phys.addr) iounmap((void *)gCTOP_CTRL_L9B.phys.addr);
		}

		/* A1 & B0 ctop are used at same time */
		OS_Free((void *)gCTOP_CTRL_L9.shdw.addr);
		if (gCTOP_CTRL_L9.phys.addr) iounmap((void *)gCTOP_CTRL_L9.phys.addr);
	}
	else
	{
		OS_Free((void *)gCTOP_CTRL.shadow.addr);
		if (gCTOP_CTRL.phys.addr) iounmap((void *)gCTOP_CTRL.phys.addr);
	}

	// ACE Registers
	if (lx_chip_rev() >= LX_CHIP_REV(H13,A0))
	{
		OS_Free((void *)gACE_REG_CTRL_H13.shdw.addr);
	}
	else if(lx_chip_rev() >= LX_CHIP_REV(L9,B0))
	{
		OS_Free((void *)gACE_REG_CTRL_L9.shdw.addr);
	}

	return 0;
}


int REG_WriteI2C(UINT32 idx, UINT8 slave, UINT8 reg, UINT8 data)
{
	UINT32 i;
	int rc = -1;
	LX_I2C_RW_DATA_T param;
	UINT32 retry = 1;

	if(idx >= _config->num_internals)
	{
		SYS_ERROR("Not supported !!!\n");
		return -1;
	}

	param.slaveAddr		= slave;
	param.subAddrSize	= 1;
	param.subAddr[0]	= reg;
	param.buf			= &data;
	param.bufSize		= 1;
	param.clock			= I2C_CLOCK_INVALID;	//use initial clock
	param.flag			= 0;

	for(i=0; i<retry; i++)
	{
		rc = I2C_DevTransfer(_i2c_handle[idx], &param, I2C_WRITE_MODE);
		if(rc >= 0) break;
	}

	if(rc < 0)
	{
		SYS_ERROR("Internal i2c write failed. slave=0x%02x, reg=0x%02x\n",
			slave, reg);
	}

	return rc;
}

int REG_ReadI2C(UINT32 idx, UINT8 slave, UINT8 reg, UINT8* data)
{
	UINT32 i;
	int rc = -1;
	LX_I2C_RW_DATA_T param;
	UINT32 retry = 1;

//printk("REG_ReadI2C....idx:%d,slave:0x%2x,reg:0x%02x,data:%x\n",idx,slave,reg,data);

	if(idx >= _config->num_internals)
	{
		SYS_ERROR("Not supported !!!\n");
		return -1;
	}

	param.slaveAddr		= slave;
	param.subAddrSize	= 1;
	param.subAddr[0]	= reg;
	param.buf			= data;
	param.bufSize		= 1;
	param.clock			= I2C_CLOCK_INVALID;	//use initial clock
	param.flag			= 0;

	for(i=0; i<retry; i++)
	{
		rc = I2C_DevTransfer(_i2c_handle[idx], &param, I2C_READ_MODE);
		if(rc >= 0) break;
	}

	if(rc < 0)
	{
		SYS_ERROR("Internal i2c read failed. slave=0x%02x, reg=0x%02x\n",
			slave, reg);
	}

	return rc;
}


int ACE_RegWrite(UINT8 slave, UINT8 reg, UINT8 data)
{
	return REG_WriteI2C(0, slave, reg, data);
}

int ACE_RegRead(UINT8 slave, UINT8 reg, UINT8* data)
{
	return REG_ReadI2C(0, slave, reg, data);
}

