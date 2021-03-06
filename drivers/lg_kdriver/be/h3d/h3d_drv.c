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
 *  h3d(3d depth) driver file for BE device
 *	
 *  author		won.hur	
 *  version		1.0
 *  date		2012.04.27
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
#include <asm/uaccess.h>
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"

#include "h3d_drv.h"
#include "be_kapi.h"
#include "be_def.h"
#include "ipc_def.h"
#include "ipc_drv.h"
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

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_H3D_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOR_H3D_GET_VERSION: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_H3D_GET_STATUS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_RESET_BLOCK: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Reset_Block(arg);
			#else
			//Added macro code
			#endif
		}
		break;
		
		case BE_IOW_H3D_BYPASS_ALL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Bypass_All(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_SET_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_GET_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Get_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_IN_FORMAT: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_In_Format(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_T3C_DEPTH_LEVEL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_T3C_Depth_Level(arg);
			#else
			//Added macro code
			#endif
		}
		break;
		
		case BE_IOW_H3D_A3C_DEPTH_LEVEL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_A3C_Depth_Level(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_A3C_AUTOCONVERGENCE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_A3C_AutoConvergence(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_H3D_GET_A3C_DMINMAX: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_H3D_Get_A3C_DMinMax(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		default :
		{
			BE_ERROR("WARNING! WRONG IOCTL CALL!!\n");
			ret = RET_ERROR;
		}
		break;
	}

	return ret;
}

int BE_H3D_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_VERSION_T stParams;

	do{
		IPC_SET_GET_PARAM(BE_H3D_VERSION_T, stParams);
		ret = BE_KIPC_SetData(BE_H3D_GET_VERSION, &stParams, sizeof(BE_H3D_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_H3D_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_STATUS_T stParams;

	do{
		ret = BE_KIPC_SetData(BE_H3D_GET_STATUS, &stParams, sizeof(BE_H3D_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_H3D_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_H3D_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_Reset_Block(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_RESET_BLOCK_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_RESET_BLOCK_T *)arg, sizeof(BE_H3D_RESET_BLOCK_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_RESET_BLOCK, &stParams, sizeof(BE_H3D_RESET_BLOCK_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_Bypass_All(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_BYPASS_ALL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_BYPASS_ALL_T *)arg, sizeof(BE_H3D_BYPASS_ALL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_BYPASS_ALL, &stParams, sizeof(BE_H3D_BYPASS_ALL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_MODE_T *)arg, sizeof(BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_SET_MODE, &stParams, sizeof(BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_Get_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_MODE_T stParams;

	do{
		IPC_SET_GET_PARAM(BE_H3D_MODE_T, stParams);
		ret = BE_KIPC_SetData(BE_H3D_SET_MODE, &stParams, sizeof(BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_H3D_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_In_Format(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_IN_FORMAT_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_IN_FORMAT_T *)arg, sizeof(BE_H3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_IN_FORMAT, &stParams, sizeof(BE_H3D_IN_FORMAT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_T3C_Depth_Level(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_T3C_DEPTH_LEVEL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_T3C_DEPTH_LEVEL_T *)arg, sizeof(BE_H3D_T3C_DEPTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_T3C_DEPTH_LEVEL, &stParams, sizeof(BE_H3D_T3C_DEPTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_A3C_Depth_Level(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_A3C_DEPTH_LEVEL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_A3C_DEPTH_LEVEL_T *)arg, sizeof(BE_H3D_A3C_DEPTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_A3C_DEPTH_LEVEL, &stParams, sizeof(BE_H3D_A3C_DEPTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_A3C_AutoConvergence(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_A3C_AUTOCONVERGENCE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_H3D_A3C_AUTOCONVERGENCE_T *)arg, sizeof(BE_H3D_A3C_AUTOCONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_H3D_A3C_AUTOCONVERGENCE, &stParams, sizeof(BE_H3D_A3C_AUTOCONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_H3D_Get_A3C_DMinMax(unsigned long arg)
{
	int ret = RET_OK;
	BE_H3D_A3C_DMINMAX_T stParams;

	do{
		ret = BE_KIPC_SetData(BE_H3D_GET_A3C_DMINMAX, &stParams, sizeof(BE_H3D_A3C_DMINMAX_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_H3D_A3C_DMINMAX_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_H3D_A3C_DMINMAX_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

