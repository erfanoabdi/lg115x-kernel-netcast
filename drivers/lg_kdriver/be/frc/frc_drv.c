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
 *  frc driver file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.16
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
#include "frc_hal.h"
#include "frc_drv.h"
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
int BE_FRC_Ioctl(unsigned int cmd, unsigned long arg)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case BE_IOW_FRC_CONTROL_MEMC: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Control_Memc(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_DEMO_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Demo_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_DEBUG_BOX: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Debug_Box(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_BYPASS_MEMC_REG: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Bypass_Memc_Reg(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_YUV_444_MODE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_YUV_444_Mode(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_LOW_DELAY: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Low_Delay(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_FRC_GET_FIRMWARE_VER: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Get_Firmware_Ver(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOR_FRC_GET_STATUS: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Get_Status(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_FORCE_FRAME_RATE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Force_Frame_Rate(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_FAST_MV_TH: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Fast_Mv_Th(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_STILL_DET_TH: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Still_Det_Th(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_SAME_DET_TH: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Same_Det_Th(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_DIFF_DET_TH: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Diff_Det_Th(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_VMODE_ERR_CNT: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Vmode_Err_Cnt(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_JUDDER_SLOPE: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Judder_Slope(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_MIN_ERR_TH: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Min_Err_Th(arg);
			#else
			//Added macro code
			#endif
		}
		break;

		case BE_IOW_FRC_SET_ABNORM_SYNC_CNT: 
		{
			#ifndef USE_BE_IOCTL_MACROS
			ret = BE_FRC_Set_Abnorm_Sync_Cnt(arg);
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

int BE_FRC_Control_Memc(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_MEMC_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_MEMC_MODE_T *)arg, sizeof(BE_FRC_MEMC_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_MEMC_MODE, &stParams, sizeof(BE_FRC_MEMC_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Demo_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_DEMO_MODE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_DEMO_MODE_T *)arg, sizeof(BE_FRC_DEMO_MODE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_DEMO_MODE, &stParams, sizeof(BE_FRC_DEMO_MODE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Debug_Box(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_ENABLE_DEBUG_BOX_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_ENABLE_DEBUG_BOX_T *)arg, sizeof(BE_FRC_ENABLE_DEBUG_BOX_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_ENABLE_DEBUG_BOX, &stParams, sizeof(BE_FRC_ENABLE_DEBUG_BOX_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Bypass_Memc_Reg(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_MEMC_BYPASS_REGION_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_MEMC_BYPASS_REGION_T *)arg, sizeof(BE_FRC_MEMC_BYPASS_REGION_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION, &(stParams.u32BypassEn), sizeof(BE_FRC_MEMC_BYPASS_ENABLE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION0_XY, &(stParams.u32BypassXY), sizeof(BE_FRC_MEMC_BYPASS_XY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION0_WH, &(stParams.u32BypassWH), sizeof(BE_FRC_MEMC_BYPASS_WH_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION1_XY, &(stParams.u32BypassXY), sizeof(BE_FRC_MEMC_BYPASS_XY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION1_WH, &(stParams.u32BypassWH), sizeof(BE_FRC_MEMC_BYPASS_WH_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION2_XY, &(stParams.u32BypassXY), sizeof(BE_FRC_MEMC_BYPASS_XY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION2_WH, &(stParams.u32BypassWH), sizeof(BE_FRC_MEMC_BYPASS_WH_T));
		if(ret) BREAK_WRONG(ret);

		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION3_XY, &(stParams.u32BypassXY), sizeof(BE_FRC_MEMC_BYPASS_XY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_BYPASS_REGION3_WH, &(stParams.u32BypassWH), sizeof(BE_FRC_MEMC_BYPASS_WH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_YUV_444_Mode(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_COLOR_YUV444_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_COLOR_YUV444_T *)arg, sizeof(BE_FRC_COLOR_YUV444_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_YUV444, &stParams, sizeof(BE_FRC_COLOR_YUV444_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Low_Delay(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_LOW_DELAY_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_LOW_DELAY_T *)arg, sizeof(BE_FRC_LOW_DELAY_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_LOW_DELAY, &stParams, sizeof(BE_FRC_LOW_DELAY_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Get_Firmware_Ver(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_VERSION_T stParams;

	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_FRC_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_GET_FIRMWARE_VERSION, &stParams, sizeof(BE_FRC_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_FRC_VERSION_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_FRC_VERSION_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Get_Status(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_STATUS_T stParams;
	
	do{
		ret = copy_from_user(&stParams, (void __user *)arg, sizeof(BE_FRC_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_GET_STATUS, &stParams, sizeof(BE_FRC_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_GetData(&stParams, sizeof(BE_FRC_STATUS_T));
		if(ret) BREAK_WRONG(ret);
		ret = copy_to_user((void __user *)arg, &stParams, sizeof(BE_FRC_STATUS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Force_Frame_Rate(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_FRAME_RATE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_FRAME_RATE_T *)arg, sizeof(BE_FRC_FRAME_RATE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_FORCE_FRAME_RATE, &stParams, sizeof(BE_FRC_FRAME_RATE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Fast_Mv_Th(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_FAST_MV_TH_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_FAST_MV_TH_T *)arg, sizeof(BE_FRC_FAST_MV_TH_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_FAST_MV_TH, &stParams, sizeof(BE_FRC_FAST_MV_TH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Still_Det_Th(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_STILL_DET_TH_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_STILL_DET_TH_T *)arg, sizeof(BE_FRC_STILL_DET_TH_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_STILL_DET_TH, &stParams, sizeof(BE_FRC_STILL_DET_TH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Same_Det_Th(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_VMODE_SAME_TH_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_VMODE_SAME_TH_T *)arg, sizeof(BE_FRC_VMODE_SAME_TH_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_SAME_DET_TH, &stParams, sizeof(BE_FRC_VMODE_SAME_TH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Diff_Det_Th(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_VMODE_DIFF_TH_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_VMODE_DIFF_TH_T *)arg, sizeof(BE_FRC_VMODE_DIFF_TH_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_DIFF_DET_TH, &stParams, sizeof(BE_FRC_VMODE_DIFF_TH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Vmode_Err_Cnt(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_VMODE_ERR_CNT_TH_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_VMODE_ERR_CNT_TH_T *)arg, sizeof(BE_FRC_VMODE_ERR_CNT_TH_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_VMODE_ERR_CNT, &stParams, sizeof(BE_FRC_VMODE_ERR_CNT_TH_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Judder_Slope(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_JUDDER_CONTROL_SLOPE_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_JUDDER_CONTROL_SLOPE_T *)arg, sizeof(BE_FRC_JUDDER_CONTROL_SLOPE_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_JUDDER_SLOPE, &stParams, sizeof(BE_FRC_JUDDER_CONTROL_SLOPE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Min_Err_Th(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_MIN_ERROR_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_MIN_ERROR_T *)arg, sizeof(BE_FRC_MIN_ERROR_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_MIN_ERR_TH, &stParams, sizeof(BE_FRC_MIN_ERROR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

int BE_FRC_Set_Abnorm_Sync_Cnt(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_ABNORMAL_SYNC_CNT_T stParams;

	do{
		ret = copy_from_user(&stParams, (BE_FRC_ABNORMAL_SYNC_CNT_T *)arg, sizeof(BE_FRC_ABNORMAL_SYNC_CNT_T));
		if(ret) BREAK_WRONG(ret);
		ret = BE_KIPC_SetData(BE_FRC_SET_ABNORMAL_SYNC_CNT, &stParams, sizeof(BE_FRC_ABNORMAL_SYNC_CNT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);
	return ret;
}

/* Previous codes... */
/*	

int BE_FRC_Init(unsigned long arg)
{
	int ret = RET_OK;
	BE_FRC_INIT_T stParams;

	do {
		ret = BE_KIPC_SetData(BE_FRC_INIT_BLOCK, &stParams, sizeof(BE_FRC_INIT_T));
		if(ret) BREAK_WRONG(ret);
		ret = FRC_HAL_Init();
	} while(0);

	return ret;
}
*/
