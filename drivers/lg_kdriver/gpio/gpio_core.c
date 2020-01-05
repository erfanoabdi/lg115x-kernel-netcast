
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
 *  main driver implementation for gpio device.
 *
 *  author		ks.hyun (ks.hyun@lge.com)
 *  version		1.0
 *  date		2012.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg115x_gpio
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#include "mach/platform.h"
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "gpio_drv.h"
#include "gpio_reg.h"
#include "sys_regs.h"
#include "sys_io.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define GPIO_LOCK_INIT(dev)		OS_InitMutex(&dev->lock, OS_SEM_ATTR_DEFAULT)
#define GPIO_LOCK(dev)			OS_LockMutex(&dev->lock)
#define GPIO_UNLOCK(dev)		OS_UnlockMutex(&dev->lock)

#define GPIO_EX_LOCK_INIT(dev)	OS_InitMutex(&dev->ex_lock, OS_SEM_ATTR_DEFAULT)
#define GPIO_EX_LOCK(dev)		OS_LockMutex(&dev->ex_lock)
#define GPIO_EX_UNLOCK(dev)		OS_UnlockMutex(&dev->ex_lock)


#if 0
#define GPIO_CORE_DEBUG(format, args...)	GPIO_ERROR(format, ##args)
#else
#define GPIO_CORE_DEBUG(format, args...)	do{}while(0)
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT8	direction;
	UINT8	data;
} GPIO_PM_DATA_T;


typedef struct GPIO_DEV
{
	OS_SEM_T	lock;
	UINT32		max_num;

	int 		(*SetPinMux)(UINT32 port, BOOLEAN enable);
	int 		(*GetPinMux)(UINT32 port, BOOLEAN *enable);
	int 		(*SetValue)	(UINT32 port, LX_GPIO_VALUE_T value);
	int 		(*GetValue)	(UINT32 port, LX_GPIO_VALUE_T *value);
	int 		(*SetMode)	(UINT32 port, LX_GPIO_MODE_T mode);
	int 		(*GetMode)	(UINT32 port, LX_GPIO_MODE_T *mode);

	/* To access gpio pins in LG115xAN(ACE) */
	OS_SEM_T	ex_lock;
	UINT32		max_ex_num;
	int 		(*ExSetPinMux)(UINT32 port, BOOLEAN enable);
	int 		(*ExGetPinMux)(UINT32 port, BOOLEAN *enable);
	int 		(*ExSetValue) (UINT32 port, LX_GPIO_VALUE_T value);
	int 		(*ExGetValue) (UINT32 port, LX_GPIO_VALUE_T *value);
	int 		(*ExSetMode)  (UINT32 port, LX_GPIO_MODE_T mode);
	int 		(*ExGetMode)  (UINT32 port, LX_GPIO_MODE_T *mode);

#ifdef KDRV_CONFIG_PM
	int			(*Resume)	(void);
	int			(*Suspend)	(void);
	GPIO_PM_DATA_T*	pmdata;
#endif
} GPIO_DEV_T;


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

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

static GPIO_DEV_T *_pGpioDev;
static UINT32*	_gpioBaseAddr;


/*************************************************************************
* Set Pinmux
*************************************************************************/
static int _GPIO_SetPinMux_H13Ax(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;

#if 0
#define GPIO_SET_PINMUX_H13A0(_reg, _mask, _en)		\
	do{												\
		UINT32 _value;								\
		CTOP_CTRL_H13A0_RdFL(_reg);					\
		_value = CTOP_CTRL_H13A0_Rd(_reg);			\
		if(_en)	_value |= _mask;					\
		else	_value &= (~_mask);					\
		CTOP_CTRL_H13A0_Wr(_reg, _value);			\
		CTOP_CTRL_H13A0_WrFL(_reg);					\
	} while(0)
#endif

	if(port < 32)
	{
		// Do nothing...
	}
	else 	/* 32 ~ 144 */
	{
		UINT32 offset, value;

		/* CTOP_CTRL_BASE + 0x84 = CTR33(GPIO[39:32] enable) */
		offset = 0x84 + ((port - 32)/8)*4;
		value = CTOP_CTRL_H13_READ(offset);
		mask = 1 << ((port % 8)* 4 + 3);
		if(enable)	value |= mask;
		else		value &= (~mask);
		CTOP_CTRL_H13_WRITE(offset, value);
	}

	return rc;
}

static int _GPIO_GetPinMux_H13Ax(UINT32 port, BOOLEAN *enable)
{
	if(port < 32)
	{
		*enable = 1;
	}
	else 	/* 32 ~ 144 */
	{
		UINT32 mask;
		UINT32 offset, value;

		/* CTOP_CTRL_BASE + 0x84 = CTR33(GPIO[39:32] enable) */
		offset = 0x84 + ((port - 32)/8)*4;
		value = CTOP_CTRL_H13_READ(offset);
		mask = 1 << ((port % 8)* 4 + 3);
		*enable = (value & mask) ? 1 : 0;
	}

	return 0;
}



static int _GPIO_SetPinMux_L9Bx(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;

#define GPIO_SET_PINMUX_L9BX(_reg, _mask, _en)			\
		do{ 											\
			UINT32 _value;								\
			CTOP_CTRL_L9B_RdFL(_reg); 					\
			_value = CTOP_CTRL_L9B_Rd(_reg);			\
			if(_en) _value |= _mask;					\
			else	_value &= (~_mask); 				\
			CTOP_CTRL_L9B_Wr(_reg, _value);				\
			CTOP_CTRL_L9B_WrFL(_reg); 					\
		} while(0)

	if(port < 32)
	{
		// Do nothing...
	}
	else if(port < 40)	/* 32 ~ 39 */
	{
		mask = 1 << ((port % 8) + 24);
		GPIO_SET_PINMUX_L9BX(ctr32_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 48)	/* 40 ~ 47 */
	{
		mask = 1 << ((port % 8)*4+3);
		GPIO_SET_PINMUX_L9BX(ctr53_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 51)	/* 48 ~ 50 */
	{
		mask = 1 << ((port % 8)*4+23);
		GPIO_SET_PINMUX_L9BX(ctr35_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 56)	/* 51 ~ 55 */
	{
		if(port == 51)		mask=1<<0;
		else if(port == 52)	mask=1<<7;
		else if(port == 53)	mask=1<<15;
		else if(port == 54)	mask=1<<23;
		else if(port == 55)	mask=1<<31;

		GPIO_SET_PINMUX_L9BX(ctr34_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 61)	/* 56 ~ 60 */
	{
		if(port == 56)		mask=1<<15;
		else if(port == 57) mask=1<<19;
		else if(port == 58) mask=1<<23;
		else if(port == 59) mask=1<<27;
		else if(port == 60) mask=1<<31;

		GPIO_SET_PINMUX_L9BX(ctr37_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 64)	/* 61 ~ 63 */
	{
		if(port == 61)		mask=1<<11;
		else if(port == 62)	mask=1<<15;
		else if(port == 63)	mask=1<<19;

		GPIO_SET_PINMUX_L9BX(ctr35_reg_gpio_mux_enable, mask, enable);
	}
	else if(port == 64)	/* 64 */
	{
		mask=1<<31;
		GPIO_SET_PINMUX_L9BX(ctr39_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 69)	/* 65 ~ 68 */
	{
		if(port == 65)		mask=1<<19;
		else if(port == 66)	mask=1<<23;
		else if(port == 67)	mask=1<<27;
		else if(port == 68)	mask=1<<31;

		GPIO_SET_PINMUX_L9BX(ctr38_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 72)	/* 69 ~ 71 */
	{
		if(port == 69)		mask=1<<3;
		else if(port == 70) mask=1<<7;
		else if(port == 71) mask=1<<11;

		GPIO_SET_PINMUX_L9BX(ctr37_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 80)	/* 72 ~ 79 */
	{
		mask = 1 << ((port % 8) + 23);
		GPIO_SET_PINMUX_L9BX(ctr39_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 82)	/* 80 ~ 81 */
	{
		if(port == 80)		mask=1<<27;
		else if(port == 81) mask=1<<31;

		GPIO_SET_PINMUX_L9BX(ctr51_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 88)	/* 82 ~ 87 */
	{
		mask = 1 << ((port % 8) + 15);
		GPIO_SET_PINMUX_L9BX(ctr39_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 94)	/* 88 ~ 93 */
	{
		mask = 1 << ((port % 8)*4 + 11);
		GPIO_SET_PINMUX_L9BX(ctr52_reg_gpio_mux_enable, mask, enable);
	}
	else if(port < 96)	/* 94 ~ 95 */
	{
		if(port == 94)		mask=1<<19;
		else if(port == 95)	mask=1<<23;
		GPIO_SET_PINMUX_L9BX(ctr52_reg_gpio_mux_enable, mask, enable);
	}

	return rc;
}

static int _GPIO_SetPinMux_L9Ax(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask = 0;

#define GPIO_SET_PINMUX_L9AX(_reg, _mask, _en)		\
	do{ 											\
		UINT32 _value;								\
		CTOP_CTRL_L9_RdFL(_reg);					\
		_value = CTOP_CTRL_L9_Rd(_reg);				\
		if(_en) _value |= _mask;					\
		else	_value &= (~_mask); 				\
		CTOP_CTRL_L9_Wr(_reg, _value); 				\
		CTOP_CTRL_L9_WrFL(_reg);					\
	} while(0)

	if(port < 32)
	{
		//Do nothing... dedicated ports
	}
	else if(port < 40)	/* 32 ~ 39 */
	{
		mask = 1 << ((port % 8) + 24);
		GPIO_SET_PINMUX_L9AX(ctr32, mask, enable);
	}
	else if(port < 48)	/* 40 ~ 47 */
	{
		mask = 1 << ((port % 8)*4+3);
		GPIO_SET_PINMUX_L9AX(ctr53, mask, enable);
	}
	else if(port < 51)	/* 48 ~ 50 */
	{
		mask = 1 << ((port % 8)*4+23);
		GPIO_SET_PINMUX_L9AX(ctr35, mask, enable);
	}
	else if(port < 56)	/* 51 ~ 55 */
	{
		if(port == 51)		mask=1<<0;
		else if(port == 52) mask=1<<7;
		else if(port == 53) mask=1<<15;
		else if(port == 54) mask=1<<23;
		else if(port == 55) mask=1<<31;

		GPIO_SET_PINMUX_L9AX(ctr34, mask, enable);
	}
	else if(port < 61)	/* 56 ~ 60 */
	{
		if(port == 56)		mask=1<<15;
		else if(port == 57) mask=1<<19;
		else if(port == 58) mask=1<<23;
		else if(port == 59) mask=1<<27;
		else if(port == 60) mask=1<<31;

		GPIO_SET_PINMUX_L9AX(ctr37, mask, enable);
	}
	else if(port < 64)	/* 61 ~ 63 */
	{
		if(port == 61)		mask=1<<11;
		else if(port == 62) mask=1<<15;
		else if(port == 63) mask=1<<19;

		GPIO_SET_PINMUX_L9AX(ctr35, mask, enable);
	}
	else if(port < 65)
	{
		mask=1<<31;
		GPIO_SET_PINMUX_L9AX(ctr39, mask, enable);
	}
	else if(port < 69)	/* 65 ~ 68 */
	{
		if(port == 65)		mask=1<<19;
		else if(port == 66) mask=1<<23;
		else if(port == 67) mask=1<<27;
		else if(port == 68) mask=1<<31;

		GPIO_SET_PINMUX_L9AX(ctr38, mask, enable);
	}
	else if(port < 72)	/* 69 ~ 71 */
	{
		if(port == 69)		mask=1<<3;
		else if(port == 70) mask=1<<7;
		else if(port == 71) mask=1<<11;

		GPIO_SET_PINMUX_L9AX(ctr37, mask, enable);
	}
	else if(port < 79)	/* 72 ~ 79 */
	{
		mask = 1 << ((port % 8) + 23);
		GPIO_SET_PINMUX_L9AX(ctr39, mask, enable);
	}
	else if(port < 82)	/* 80 ~ 81 */
	{
		if(port == 80)		mask=1<<27;
		else if(port == 81) mask=1<<31;

		GPIO_SET_PINMUX_L9AX(ctr51, mask, enable);
	}
	else if(port < 88)	/* 82 ~ 87 */
	{
		mask = 1 << ((port % 8) + 15);
		GPIO_SET_PINMUX_L9AX(ctr39, mask, enable);
	}
	else if(port < 94)	/* 88 ~ 93 */
	{
		mask = 1 << ((port % 8)*4 + 11);
		GPIO_SET_PINMUX_L9AX(ctr52, mask, enable);
	}
	else if(port < 96)	/* 94 ~ 95 */
	{
		if(port == 94)		mask=1<<19;
		else if(port == 95) mask=1<<23;
		GPIO_SET_PINMUX_L9AX(ctr52, mask, enable);
	}

	return rc;
}


#ifdef INCLUDE_L8_CHIP_KDRV
static int _GPIO_SetPinMux_L8(UINT32 port, BOOLEAN enable)
{
	int rc = 0;
	UINT32 mask, value;

	if(port < 32)
	{
		// Do nothing...
	}
	else if(port < 32 * 2)
	{
		mask = 1 << ( 31 - (port % 32));

		CTOP_CTRL_RdFL(ctr24);
		value = CTOP_CTRL_Rd(ctr24) | mask;
		CTOP_CTRL_Wr(ctr24, value);
		CTOP_CTRL_WrFL(ctr24);
	}
	else if(port < 32 * 3)
	{
		if(lx_chip_rev() < LX_CHIP_REV(L8,B0))
		{
			// for work-around : Top control register connection error - start
			if(port == 81) { mask = 0x4000; }
			else if(port == 82) { mask = 0x400; }
			else if(port == 83) { mask = 0x1000; }
			else if(port == 84) { mask = 0x2000; }
			else if(port == 85) { mask = 0x800; }
			// for work-around : Top control register connection error - end
			else { mask = 1 << ( 31 - (port % 32)); }
		}
		else
		{
			mask = 1 << ( 31 - (port % 32));
		}

		CTOP_CTRL_RdFL(ctr25);
		value = CTOP_CTRL_Rd(ctr25) | mask;
		CTOP_CTRL_Wr(ctr25, value);
		CTOP_CTRL_WrFL(ctr25);
	}

	return rc;
}
#endif


/*************************************************************************
* Get Value
*************************************************************************/
#ifdef INCLUDE_L8_CHIP_KDRV
static int _GPIO_GetValue_L8Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	UINT32 data = GPIONDATA(port/8);

	if(port < 32) 		{ data = (data >> (port % 8)) & 0x1; }
	// for work-around : Top control register connection error - start
	else if(port == 81)	{ data = (data >> 6) & 0x1; } // 0x40
	else if(port == 82)	{ data = (data >> 2) & 0x1; } // 0x4
	else if(port == 83)	{ data = (data >> 4) & 0x1; } // 0x10
	else if(port == 84)	{ data = (data >> 5) & 0x1; } // 0x20
	else if(port == 85)	{ data = (data >> 3) & 0x1; } // 0x8
	// for work-around : Top control register connection error - end
	else				{ data = (data >> (7 - (port % 8))) & 0x1; }

	*value = data ? LX_GPIO_VALUE_HIGH : LX_GPIO_VALUE_LOW;
	return 0;
}

static int _GPIO_GetValue_L8Bx(UINT32 port, LX_GPIO_VALUE_T *value)
{
	UINT32 data = GPIONDATA(port/8);

	if(port < 32)	{ data = (data >> (port % 8)) & 0x1; }
	else			{ data = (data >> (7 - (port % 8))) & 0x1; }

	*value = data ? LX_GPIO_VALUE_HIGH : LX_GPIO_VALUE_LOW;
	return 0;
}
#endif

static int _GPIO_GetValue(UINT32 port, LX_GPIO_VALUE_T *value)
{
	UINT32 data = GPIONDATA(port/8);
	*value = ((data >> (port % 8)) & 0x1) ? LX_GPIO_VALUE_HIGH : LX_GPIO_VALUE_LOW;
	return 0;
}



/*************************************************************************
* Set Value
*************************************************************************/
#ifdef INCLUDE_L8_CHIP_KDRV
static int _GPIO_SetValue_L8Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	UINT32 mask, data;

	if(port < 32) 		{ mask = 1 << (2 + (port % 8)); }
	// for work-around : Top control register connection error - start
	else if(port == 81)	{ mask = 0x40 << 2; }
	else if(port == 82)	{ mask = 0x4	<< 2; }
	else if(port == 83)	{ mask = 0x10 << 2; }
	else if(port == 84)	{ mask = 0x20 << 2; }
	else if(port == 85)	{ mask = 0x8	<< 2; }
	// for work-around : Top control register connection error - end
	else				{ mask = 1 << (2 + (7-(port % 8))); }

	data = (value == LX_GPIO_VALUE_HIGH) ? 0xff : 0x0;
	SYS_REG_WRITE32(GPION_BASE(port/8) + mask, data);
	return 0;
}

static int _GPIO_SetValue_L8Bx(UINT32 port, LX_GPIO_VALUE_T value)
{
	UINT32 mask, data;

	if(port < 32)	{ mask = 1 << (2 + (port % 8)); }
	else			{ mask = 1 << (2 + (7-(port % 8))); }

	data = (value == LX_GPIO_VALUE_HIGH) ? 0xff : 0x0;
	SYS_REG_WRITE32(GPION_BASE(port/8) + mask, data);
	return 0;
}
#endif

static int _GPIO_SetValue(UINT32 port, LX_GPIO_VALUE_T value)
{
	UINT32 mask, data;

	mask = 1 << (2 + (port % 8));

	data = (value == LX_GPIO_VALUE_HIGH) ? 0xff : 0x0;
	SYS_WRITE32(GPION_BASE(port/8) + mask, data);
	return 0;
}



/*************************************************************************
* Set Mode
*************************************************************************/
#ifdef INCLUDE_L8_CHIP_KDRV
static int _GPIO_SetMode_L8Ax(UINT32 port, LX_GPIO_MODE_T mode)
{
	UINT32 direction, mask;

	direction = GPIONDIR(port/8);

	if(port < 32) 		{ mask = 1 << (port % 8); }
	// for work-around : Top control register connection error - start
	else if(port == 81)	{ mask = 0x40; }
	else if(port == 82)	{ mask = 0x4; }
	else if(port == 83)	{ mask = 0x10; }
	else if(port == 84)	{ mask = 0x20; }
	else if(port == 85)	{ mask = 0x8; }
	// for work-around : Top control register connection error - end
	else				{ mask = 1 << (7 - (port % 8)); }

	direction = (mode == LX_GPIO_MODE_INPUT) ?
					direction & (~mask) : direction | mask;

	GPIONDIR(port/8) = direction;
	return 0;
}

static int _GPIO_SetMode_L8Bx(UINT32 port, LX_GPIO_MODE_T mode)
{
	UINT32 direction, mask;

	direction = GPIONDIR(port/8);
	if(port < 32)	{ mask = 1 << (port % 8); }
	else			{ mask = 1 << (7 - (port % 8)); }
	direction = (mode == LX_GPIO_MODE_INPUT) ?
				direction & (~mask) : direction | mask;

	GPIONDIR(port/8) = direction;
	return 0;
}
#endif

static int _GPIO_SetMode(UINT32 port, LX_GPIO_MODE_T mode)
{
	UINT32 direction, mask;

	direction = GPIONDIR(port/8);
	mask = 1 << (port % 8);
	direction = (mode == LX_GPIO_MODE_INPUT) ?
				direction & (~mask) : direction | mask;

	GPIONDIR(port/8) = direction;
	return 0;
}

static int _GPIO_GetMode(UINT32 port, LX_GPIO_MODE_T *mode)
{
	UINT32 direction, mask;

	direction = GPIONDIR(port/8);
	mask = 1 << (port % 8);
	*mode = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;
	return 0;
}


#ifdef KDRV_CONFIG_PM

#ifdef INCLUDE_L8_CHIP_KDRV
static int _GPIO_Resume_L8(void)
{
	int i;

#if 0	// It's not used any longer, so I don't care this code
	CTOP_CTRL_Wr(ctr24, drv_data->top_control_24);
	CTOP_CTRL_WrFL(ctr24);
	CTOP_CTRL_Wr(ctr25, drv_data->top_control_25);
	CTOP_CTRL_WrFL(ctr25);
#endif

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDIR(i) = _pGpioDev->pmdata[i].direction;
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		GPIONDATA(i) = _pGpioDev->pmdata[i].data;
	}
}

static int _GPIO_Suspend_L8(void)
{
	int i;

#if 0	// It's not used any longer, so I don't care this code
	CTOP_CTRL_RdFL(ctr24);
	drv_data->top_control_24 = CTOP_CTRL_Rd(ctr24);
	CTOP_CTRL_RdFL(ctr25);
	drv_data->top_control_25 = CTOP_CTRL_Rd(ctr25);
#endif

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].direction = GPIONDIR(i);
	}

	for(i = 0; i < _pGpioDev->max_num/8; i++)
	{
		_pGpioDev->pmdata[i].data = GPIONDATA(i);
	}

}
#endif

int GPIO_DevResume(void)
{
	if(_pGpioDev->Resume) _pGpioDev->Resume();
	return 0;
}

int GPIO_DevSuspend(void)
{
	if(_pGpioDev->Suspend) _pGpioDev->Suspend();
	return 0;
}
#endif




int GPIO_DevSetPinMux(UINT32 port, BOOLEAN enable)
{
	int rc = -1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev);
		rc = _pGpioDev->SetPinMux(port, enable);
		GPIO_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevGetPinMux(UINT32 port, BOOLEAN *enable)
{
	int rc = -1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev);
		rc = _pGpioDev->GetPinMux(port, enable);
		GPIO_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevSetValue(UINT32 port, LX_GPIO_VALUE_T value)
{
	int rc = -1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev);
		rc = _pGpioDev->SetValue(port, value);
		GPIO_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevGetValue(UINT32 port, LX_GPIO_VALUE_T *value)
{
	int rc = -1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev);
		rc = _pGpioDev->GetValue(port, value);
		GPIO_UNLOCK(_pGpioDev);
	}
	return rc;
}


int GPIO_DevSetMode(UINT32 port, LX_GPIO_MODE_T mode)
{
	int rc = -1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev);
		rc = _pGpioDev->SetMode(port, mode);
		GPIO_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevGetMode(UINT32 port, LX_GPIO_MODE_T *mode)
{
	int rc = -1;
	if(port < _pGpioDev->max_num)
	{
		GPIO_LOCK(_pGpioDev);
		rc = _pGpioDev->GetMode(port, mode);
		GPIO_UNLOCK(_pGpioDev);
	}
	return rc;
}


/*****************************************
 * ACCESS GPIOs in LG115xAN(ACE)         *
 *****************************************/
static int _GPIO_ExSetPinMux(UINT32 port, BOOLEAN enable)
{
	// do nothing
	return 0;
}

static int _GPIO_ExGetPinMux(UINT32 port, BOOLEAN *enable)
{
	*enable = 1;
	return 0;
}

static int _GPIO_ExGetValue_H13Ax(UINT32 port, LX_GPIO_VALUE_T *value)
{
	UINT8 mask, data;

	GPIO_CORE_DEBUG("_GPIO_ExGetValue_H13Ax. port:%d\n", port);

	mask = 1 << (port % 8);
	if(port < 8)
	{
		ACE_REG_H13A0_RdFL(gpio_16);
		data = ACE_REG_H13A0_Rd(gpio_16);
	}
	else
	{
		ACE_REG_H13A0_RdFL(gpio_17);
		data = ACE_REG_H13A0_Rd(gpio_17);
	}
	GPIO_CORE_DEBUG("DATA:0x%02x\n", data);

	/*
	(3) GPIO_IEV 가 1일면 input level인 ‘1’ 인 경우 High, ‘0’이면 Low
	(4) GPIO_IEV 가 0일면 input level인 ‘0’ 인 경우 High, ‘1’이면 Low
	*/
	*value = (data&mask) ? LX_GPIO_VALUE_HIGH : LX_GPIO_VALUE_LOW;
	return 0;
}

static int _GPIO_ExSetValue_H13Ax(UINT32 port, LX_GPIO_VALUE_T value)
{
	UINT8 mask, data;

	GPIO_CORE_DEBUG("_GPIO_ExSetValue_H13Ax. port:%d, value:%d\n", port, value);

	mask = 1 << (port % 8);
	if(port < 8)
	{
		ACE_REG_H13A0_RdFL(gpio_0);
		data = ACE_REG_H13A0_Rd(gpio_0);
	}
	else
	{
		ACE_REG_H13A0_RdFL(gpio_1);
		data = ACE_REG_H13A0_Rd(gpio_1);
	}
	data = (value == LX_GPIO_VALUE_LOW) ?
				data & (~mask) : data | mask;

	if(port < 8)
	{
		ACE_REG_H13A0_Wr(gpio_0, data);
		ACE_REG_H13A0_WrFL(gpio_0);
	}
	else
	{
		ACE_REG_H13A0_Wr(gpio_1, data);
		ACE_REG_H13A0_WrFL(gpio_1);
	}
	return 0;
}

static int _GPIO_ExSetMode_H13Ax(UINT32 port, LX_GPIO_MODE_T mode)
{
	UINT8 direction, mask;

	GPIO_CORE_DEBUG("_GPIO_ExSetMode_H13Ax. port:%d, mode:%d\n", port, mode);

	mask = 1 << (port % 8);
	if(port < 8)
	{
		ACE_REG_H13A0_RdFL(gpio_2);
		direction = ACE_REG_H13A0_Rd(gpio_2);
	}
	else
	{
		ACE_REG_H13A0_RdFL(gpio_3);
		direction = ACE_REG_H13A0_Rd(gpio_3);
	}
	GPIO_CORE_DEBUG("DIR:0x%02x\n", direction);

	direction = (mode == LX_GPIO_MODE_INPUT) ?
				direction & (~mask) : direction | mask;

	if(port < 8)
	{
		ACE_REG_H13A0_Wr(gpio_2, direction);
		ACE_REG_H13A0_WrFL(gpio_2);
	}
	else
	{
		ACE_REG_H13A0_Wr(gpio_3, direction);
		ACE_REG_H13A0_WrFL(gpio_3);
	}
	return 0;
}

static int _GPIO_ExGetMode_H13Ax(UINT32 port, LX_GPIO_MODE_T *mode)
{
	UINT8 direction, mask;

	GPIO_CORE_DEBUG("_GPIO_ExGetMode_H13Ax. port:%d\n", port);

	mask = 1 << (port % 8);
	if(port < 8)
	{
		ACE_REG_H13A0_RdFL(gpio_2);
		direction = ACE_REG_H13A0_Rd(gpio_2);
	}
	else
	{
		ACE_REG_H13A0_RdFL(gpio_3);
		direction = ACE_REG_H13A0_Rd(gpio_3);
	}
	GPIO_CORE_DEBUG("DIR:0x%02x\n", direction);
	*mode = (direction & mask) ? LX_GPIO_MODE_OUTPUT : LX_GPIO_MODE_INPUT;

	return 0;
}



int GPIO_DevExSetPinMux(UINT32 port, BOOLEAN enable)
{
	int rc = -1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev);
		rc = _pGpioDev->ExSetPinMux(port, enable);
		GPIO_EX_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevExGetPinMux(UINT32 port, BOOLEAN *enable)
{
	int rc = -1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev);
		rc = _pGpioDev->ExGetPinMux(port, enable);
		GPIO_EX_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevExSetValue(UINT32 port, LX_GPIO_VALUE_T value)
{
	int rc = -1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev);
		rc = _pGpioDev->ExSetValue(port, value);
		GPIO_EX_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevExGetValue(UINT32 port, LX_GPIO_VALUE_T *value)
{
	int rc = -1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev);
		rc = _pGpioDev->ExGetValue(port, value);
		GPIO_EX_UNLOCK(_pGpioDev);
	}
	return rc;
}


int GPIO_DevExSetMode(UINT32 port, LX_GPIO_MODE_T mode)
{
	int rc = -1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev);
		rc = _pGpioDev->ExSetMode(port, mode);
		GPIO_EX_UNLOCK(_pGpioDev);
	}
	return rc;
}

int GPIO_DevExGetMode(UINT32 port, LX_GPIO_MODE_T *mode)
{
	int rc = -1;
	if(port < _pGpioDev->max_ex_num)
	{
		GPIO_EX_LOCK(_pGpioDev);
		rc = _pGpioDev->ExGetMode(port, mode);
		GPIO_EX_UNLOCK(_pGpioDev);
	}
	return rc;
}



int GPIO_DevInit(void)
{
	UINT32 i, num_blocks;
	UINT32 phys_base, addr_gap;
	
	_pGpioDev = (GPIO_DEV_T*)OS_Malloc(sizeof(GPIO_DEV_T));
	memset(_pGpioDev, 0, sizeof(GPIO_DEV_T));


	GPIO_LOCK_INIT(_pGpioDev);
	GPIO_EX_LOCK_INIT(_pGpioDev);

	if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_H13)) 		/* H13 */
	{
		phys_base		= H13_GPIO__BASE;
		addr_gap		= 0x10000;

		_pGpioDev->max_num	= 136;		// 144, Not supported GPIO(17) in CTOP
		num_blocks = (_pGpioDev->max_num+7)/8;
		
		_pGpioDev->GetValue 	= _GPIO_GetValue;
		_pGpioDev->SetValue 	= _GPIO_SetValue;
		_pGpioDev->SetMode		= _GPIO_SetMode;
		_pGpioDev->GetMode		= _GPIO_GetMode;
		_pGpioDev->SetPinMux	= _GPIO_SetPinMux_H13Ax;
		_pGpioDev->GetPinMux	= _GPIO_GetPinMux_H13Ax;

		_pGpioDev->max_ex_num	= 16;
		_pGpioDev->ExGetValue 	= _GPIO_ExGetValue_H13Ax;
		_pGpioDev->ExSetValue 	= _GPIO_ExSetValue_H13Ax;
		_pGpioDev->ExSetMode	= _GPIO_ExSetMode_H13Ax;
		_pGpioDev->ExGetMode	= _GPIO_ExGetMode_H13Ax;
		_pGpioDev->ExSetPinMux	= _GPIO_ExSetPinMux;
		_pGpioDev->ExGetPinMux	= _GPIO_ExGetPinMux;

		/* Set Interrupt Sense to get the value */
		ACE_REG_H13A0_Wr(gpio_4, 0xFF);
		ACE_REG_H13A0_WrFL(gpio_4);
		ACE_REG_H13A0_Wr(gpio_5, 0xFF);
		ACE_REG_H13A0_WrFL(gpio_5);

		/*
		(3) GPIO_IEV 가 1일면 input level인 ‘1’ 인 경우 High, ‘0’이면 Low
		(4) GPIO_IEV 가 0일면 input level인 ‘0’ 인 경우 High, ‘1’이면 Low
		*/
		ACE_REG_H13A0_Wr(gpio_8, 0xFF);
		ACE_REG_H13A0_WrFL(gpio_8);
		ACE_REG_H13A0_Wr(gpio_9, 0xFF);
		ACE_REG_H13A0_WrFL(gpio_9);

	}
	else if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L9))	/* L9 */
	{
		phys_base		= L9_GPIO0_BASE;
		addr_gap		= 0x100000;
		_pGpioDev->max_num	= 96;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->GetValue = _GPIO_GetValue;
		_pGpioDev->SetValue = _GPIO_SetValue;
		_pGpioDev->SetMode	= _GPIO_SetMode;

		if(lx_chip_rev() >= LX_CHIP_REV(L9,B0))
		{
			_pGpioDev->SetPinMux	= _GPIO_SetPinMux_L9Bx;
		}
		else
		{
			_pGpioDev->SetPinMux	= _GPIO_SetPinMux_L9Ax;
		}
	}
#ifdef INCLUDE_L8_CHIP_KDRV
	else if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L8))	/* L8 */
	{
		phys_base		= L8_GPIO0_BASE;
		addr_gap		= 0x100000;
		_pGpioDev->max_num	= 96;
		num_blocks = (_pGpioDev->max_num+7)/8;

		_pGpioDev->SetPinMux = _GPIO_SetPinMux_L8;
#ifdef KDRV_CONFIG_PM
		_pGpioDev->Resume	= _GPIO_Resume_L8;
		_pGpioDev->Suspend	= _GPIO_Suspend_L8;
		_pGpioDev->pmdata	= (GPIO_PM_DATA_T*)OS_Malloc(sizeof(GPIO_PM_DATA_T) * (_pGpioDev->max_num/8));
#endif

		if(lx_chip_rev() >= LX_CHIP_REV(L8,B0))
		{
			_pGpioDev->GetValue	= _GPIO_GetValue_L8Bx;
			_pGpioDev->SetValue	= _GPIO_SetValue_L8Bx;
			_pGpioDev->SetMode	= _GPIO_SetMode_L8Bx;
		}
		else
		{
			_pGpioDev->GetValue = _GPIO_GetValue_L8Ax;
			_pGpioDev->SetValue = _GPIO_SetValue_L8Ax;
			_pGpioDev->SetMode	= _GPIO_SetMode_L8Ax;
		}
	}
#endif
	else
	{
		GPIO_ERROR("Unsupported chip !!!\n");
		return -1;
	}

	_gpioBaseAddr = (UINT32*)OS_Malloc(num_blocks * sizeof(UINT32));
	for(i=0; i<num_blocks; i++)
	{
		_gpioBaseAddr[i] = (UINT32)ioremap(phys_base + i*addr_gap , 0x10000);
	}

	return 0;
}


/** @} */
