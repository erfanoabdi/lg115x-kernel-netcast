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
 *  led(dppb) driver file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.06
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

#include "be_kapi.h"
#include "be_def.h"
#include "led_drv.h"
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
int BE_LED_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOR_LED_GET_VERSION: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_LED_GET_STATUS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_SET_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_LED_CONTROL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_LED_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_HDR_GET_VERSION: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_HDR_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_HDR_GET_STATUS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_HDR_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_HDR_SET_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_HDR_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_HDR_CONTROL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_HDR_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_WCG_GET_VERSION: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_WCG_GET_STATUS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_WCG_SET_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Set_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_WCG_CONTROL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_WCG_Control(arg);
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

int BE_LED_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	BE_LED_VERSION_T stParams;
		
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_LED_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_LED_GET_VERSION, &stParams, sizeof(BE_LED_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_LED_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_LED_VERSION_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_LED_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_LED_STATUS_T stParams;

	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_LED_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_LED_GET_STATUS, &stParams, sizeof(BE_LED_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_LED_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_LED_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_LED_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_LED_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_LED_MODE_T *)arg, sizeof(BE_LED_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_LED_SET_MODE, &stParams, sizeof(BE_LED_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_LED_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_LED_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_LED_CONTROL_T *)arg, sizeof(BE_LED_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_LED_CONTROL, &stParams, sizeof(BE_LED_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_HDR_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	BE_HDR_VERSION_T stParams;
	
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_HDR_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_HDR_GET_VERSION, &stParams, sizeof(BE_HDR_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_HDR_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_HDR_VERSION_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_HDR_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_HDR_STATUS_T stParams;
	
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_HDR_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_HDR_GET_STATUS, &stParams, sizeof(BE_HDR_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_HDR_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_HDR_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_HDR_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_HDR_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_HDR_MODE_T *)arg, sizeof(BE_HDR_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_HDR_SET_MODE, &stParams, sizeof(BE_HDR_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_HDR_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_HDR_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_HDR_CONTROL_T *)arg, sizeof(BE_HDR_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_HDR_CONTROL, &stParams, sizeof(BE_HDR_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_WCG_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	BE_WCG_VERSION_T stParams;

	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_WCG_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_WCG_GET_VERSION, &stParams, sizeof(BE_WCG_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_WCG_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_WCG_VERSION_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_WCG_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_WCG_STATUS_T stParams;
		
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_WCG_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_WCG_GET_STATUS, &stParams, sizeof(BE_WCG_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_WCG_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_WCG_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_WCG_Set_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_WCG_MODE_T stParams;
	unsigned long *ulParam = (unsigned long *)&stParams;

	do{
		ret = copy_from_user(&stParams, (BE_WCG_MODE_T *)arg, sizeof(BE_WCG_MODE_T));
		if(ret) BREAK_WRONG(ret);

		if(*ulParam == 0xFFFFFFFF) break;
		
		ret = BE_KIPC_SetData(BE_WCG_SET_MODE, &stParams, sizeof(BE_WCG_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_WCG_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_WCG_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_WCG_CONTROL_T *)arg, sizeof(BE_WCG_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_WCG_CONTROL, &stParams, sizeof(BE_WCG_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

