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
 *	OVI module control Drivers linux module
 *
 *  author     dj911.kim@lge.com
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/interrupt.h>
#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hal.h"
#include "h13/ovi_hw_h13.h"

// Add here for register header file
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
int (*OVI_HWInitialize)(void);
int (*OVI_HWClose)(void);

int (*OVI_HWSetLvds)(LX_OVI_LVDS_T *pstParams);
int (*OVI_HWSetVx1)(LX_OVI_VX1_T *pstParams);
int (*OVI_HWSetEpi)(LX_OVI_EPI_T *pstParams);
int (*OVI_HWSetDarkScreen)(BOOLEAN bParam);
int (*OVI_HWSetReverse)(BOOLEAN bParam);
int (*OVI_HWGetTconBaseAddr)(UINT32 *pstParams);
int (*OVI_HWGetInfo)(LX_OVI_INFO_T *pstParams);
int (*OVI_HWGetConfigVer)(LX_OVI_CONFIG_VER_T *pstParams);
int (*OVI_HWSetCombination)(UINT32 eParam);
int (*OVI_HWSetSpreadSpectrum)(LX_OVI_SPREAD_SPECTRUM_T stParam);

/*----------------------------------------------------------------------------------------
	External Variables
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

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
* OVI Module Initialize
*
* @param void
* @return int
*/
int OVI_HAL_Init(void)
{
	int ret = RET_OK;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( H13, B0) )
	{
		OVI_PRINT("OVI chip revision is set to H13 B0\n");
		OVI_HWInitialize	    			= OVI_HW_H13_Initialize;
		OVI_HWSetLvds				= OVI_HW_H13_SetLvds;
		OVI_HWSetVx1				= OVI_HW_H13_SetVx1;
		OVI_HWSetEpi				= OVI_HW_H13_SetEpi;
		OVI_HWSetDarkScreen		= OVI_HW_H13_SetDarkScreen;
		OVI_HWSetReverse			= OVI_HW_H13_SetReverse;
		OVI_HWGetTconBaseAddr 	= OVI_HW_H13_GetTconBaseAddr;
		OVI_HWGetInfo				= OVI_HW_H13_GetInfo;
		OVI_HWGetConfigVer			= OVI_HW_H13_GetConfigVer;
		OVI_HWSetCombination		= OVI_HW_H13_SetCombination;
		OVI_HWSetSpreadSpectrum 	= OVI_HW_H13_SetSpreadSpectrum;
		OVI_HWClose				= OVI_HW_H13_Close;
	}
	else
	{ 
		OVI_ERROR("OVI ERROR! Unknown chip revision at OVI module\n");
		OVI_HWInitialize    			= NULL;
		OVI_HWSetLvds				= NULL;
		OVI_HWSetVx1				= NULL;
		OVI_HWSetEpi				= NULL;
		OVI_HWSetDarkScreen		= NULL;
		OVI_HWSetReverse			= NULL;
		OVI_HWGetTconBaseAddr 	= NULL;
		OVI_HWGetInfo				= NULL;
		OVI_HWGetConfigVer			= OVI_HW_H13_GetConfigVer;
		OVI_HWSetCombination		= NULL;
		OVI_HWSetSpreadSpectrum 	= NULL;
		OVI_HWClose				= NULL;
		ret = RET_ERROR;    
	}

	if(OVI_HWInitialize)
	{
		ret = OVI_HWInitialize();
	}
	
	return ret;
}

int OVI_HAL_SetLvds(LX_OVI_LVDS_T *pstParams)
{
	int ret = RET_OK;

	if(OVI_HWSetLvds)
	{
		ret = OVI_HWSetLvds(pstParams);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_SetVx1(LX_OVI_VX1_T *pstParams)
{
	int ret = RET_OK;

	if(OVI_HWSetVx1)
	{
		ret = OVI_HWSetVx1(pstParams);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_SetEpi(LX_OVI_EPI_T *pstParams)
{
	int ret = RET_OK;

	if(OVI_HWSetEpi)
	{
		ret = OVI_HWSetEpi(pstParams);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_SetDarkScreen(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(OVI_HWSetDarkScreen)
	{
		ret = OVI_HWSetDarkScreen(bParam);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_SetReverse(BOOLEAN bParam)
{
	int ret = RET_OK;

	if(OVI_HWSetReverse)
	{
		ret = OVI_HWSetReverse(bParam);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_GetTconBaseAddr(UINT32 *pstParams)
{
	int ret = RET_OK;

	if(OVI_HWGetTconBaseAddr)
	{
		ret = OVI_HWGetTconBaseAddr(pstParams);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_GetInfo(LX_OVI_INFO_T *pstParams)
{
	int ret = RET_OK;

	if(OVI_HWGetInfo)
	{
		ret = OVI_HWGetInfo(pstParams);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_GetConfigVer(LX_OVI_CONFIG_VER_T *pstParams)
{
	int ret = RET_OK;

	if(OVI_HWGetConfigVer)
	{
		ret = OVI_HWGetConfigVer(pstParams);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_SetCombination(UINT32 eParam)
{
	int ret = RET_OK;

	if(OVI_HWSetCombination)
	{
		ret = OVI_HWSetCombination(eParam);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

int OVI_HAL_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T stParam)
{
	int ret = RET_OK;

	if(OVI_HWSetSpreadSpectrum)
	{
		ret = OVI_HWSetSpreadSpectrum(stParam);
	}
	else
	{
		OVI_ERROR("OVI ERROR! This function is not supported!\n");
		ret = RET_ERROR;    
	}

	return ret;
}

/** @} */
