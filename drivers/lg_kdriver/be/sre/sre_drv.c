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
 *  SRE driver file for BE device
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

#include "be_kapi.h"
#include "be_def.h"
#include "sre_drv.h"
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
int BE_SRE_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOW_SRE_SET_BYPASS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Bypass(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SRE_SET_INPUT_FORMAT: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Input_Format(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_GET_VERSION: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Get_Version(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_GET_STATUS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SRE_CONTROL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SRE_SET_DB_GRADE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_DB_Grade(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SRE_SR_STRENGTH_LEVEL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_SR_Strength_Level(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SRE_UPDATE_ALL: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Update_All(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_SRE_WRITE_DATA: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Write_Data(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_GET_DATA: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Get_Data(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_GLOBAL_SCALE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Global_Scale(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_LOCAL_SCALE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Local_Scale(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_PREPROCESSING:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Preprocessing(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_NOISE_CONTROL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Noise_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_LOCAL_BYPASS:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Local_Bypass(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_CLIP_CONTROL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Clip_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_WEIGHT_CONTROL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Weight_Control(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_SRE_SET_ETC_CONTROL:
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_SRE_Set_Etc_Control(arg);
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

int BE_SRE_Set_Bypass(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_BYPASS_ALL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_BYPASS_ALL_T *)arg, sizeof(BE_SRE_BYPASS_ALL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_BYPASS_ALL, &stParams, sizeof(BE_SRE_BYPASS_ALL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Input_Format(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_INPUT_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_INPUT_MODE_T *)arg, sizeof(BE_SRE_INPUT_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_SET_INPUT_MODE, &stParams, sizeof(BE_SRE_INPUT_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Get_Version(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_VERSION_T stParams;

	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_SRE_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_GET_VERSION, &stParams, sizeof(BE_SRE_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_SRE_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_SRE_VERSION_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_STATUS_T stParams;
	
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_SRE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_GET_STATUS, &stParams, sizeof(BE_SRE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_SRE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_SRE_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_CONTROL_T *)arg, sizeof(BE_SRE_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_CONTROL, &stParams, sizeof(BE_SRE_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_DB_Grade(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_DB_GRADE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_DB_GRADE_T *)arg, sizeof(BE_SRE_DB_GRADE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_SET_DB_GRADE, &stParams, sizeof(BE_SRE_DB_GRADE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_SR_Strength_Level(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_SR_STRENGTH_LEVEL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_SR_STRENGTH_LEVEL_T *)arg, sizeof(BE_SRE_SR_STRENGTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_SR_STRENGTH_LEVEL, &stParams, sizeof(BE_SRE_SR_STRENGTH_LEVEL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Update_All(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_UPDATE_ALL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_UPDATE_ALL_T *)arg, sizeof(BE_SRE_UPDATE_ALL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_UPDATE_ALL, &stParams, sizeof(BE_SRE_UPDATE_ALL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Write_Data(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_WRITE_DATA_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_WRITE_DATA_T *)arg, sizeof(BE_SRE_WRITE_DATA_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_WRITE_DATA, &stParams, sizeof(BE_SRE_WRITE_DATA_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Get_Data(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_GET_DATA_T stParams;
	
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_SRE_GET_DATA_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_GET_DATA, &stParams, sizeof(BE_SRE_GET_DATA_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_SRE_GET_DATA_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_SRE_GET_DATA_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Global_Scale(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_GLOBAL_SCALE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_GLOBAL_SCALE_T *)arg, sizeof(BE_SRE_GLOBAL_SCALE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_GLOBAL_SCALE, &stParams, sizeof(BE_SRE_GLOBAL_SCALE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Local_Scale(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_LOCAL_SCALE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_LOCAL_SCALE_T *)arg, sizeof(BE_SRE_LOCAL_SCALE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_LOCAL_SCALE, &stParams, sizeof(BE_SRE_LOCAL_SCALE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Preprocessing(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_PREPROCESSING_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_PREPROCESSING_T *)arg, sizeof(BE_SRE_PREPROCESSING_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_PREPROCESSING, &stParams, sizeof(BE_SRE_PREPROCESSING_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Noise_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_NOISE_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_NOISE_CONTROL_T *)arg, sizeof(BE_SRE_NOISE_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_NOISE_CONTROL, &stParams, sizeof(BE_SRE_NOISE_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Local_Bypass(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_LOCAL_BYPASS_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_LOCAL_BYPASS_T *)arg, sizeof(BE_SRE_LOCAL_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_LOCAL_BYPASS, &stParams, sizeof(BE_SRE_LOCAL_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Clip_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_CLIP_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_CLIP_CONTROL_T *)arg, sizeof(BE_SRE_CLIP_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_CLIP_CONTROL, &stParams, sizeof(BE_SRE_CLIP_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Weight_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_WEIGHT_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_WEIGHT_CONTROL_T *)arg, sizeof(BE_SRE_WEIGHT_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_WEIGHT_CONTROL, &stParams, sizeof(BE_SRE_WEIGHT_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_SRE_Set_Etc_Control(unsigned long arg)
{
	int ret = RET_OK;
	BE_SRE_ETC_CONTROL_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_SRE_ETC_CONTROL_T *)arg, sizeof(BE_SRE_ETC_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_SRE_ETC_CONTROL, &stParams, sizeof(BE_SRE_ETC_CONTROL_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

