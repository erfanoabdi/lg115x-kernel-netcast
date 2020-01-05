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
 *  firmware loader file for BE device
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.05
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
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_kapi.h"
#include "be_def.h"
#include "ipc_def.h"
#include "ipc_drv.h"

#include "fwl_drv.h"
#include "fwl_hal.h"

#include "h13/frc_fw_h13a0.h"
#include "h13/frc_fw_h13b0.h"
#include "h13/sre_fw_h13a0.h"
#include "h13/sre_fw_h13b0.h"
#include "h13/wcg_fw_h13a0.h"
#include "h13/wcg_fw_h13b0.h"
#include "h13/led_fw_h13a0.h"
#include "h13/led_fw_h13b0.h"
#include "h13/hdr_fw_h13a0.h"
#include "h13/hdr_fw_h13b0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define FWL_FW_INIT_REQ_MASK_FRC		1 << BE_FW_DWLD_TYPE_FRC
#define FWL_FW_INIT_REQ_MASK_SRE		1 << BE_FW_DWLD_TYPE_SRE
#define FWL_FW_INIT_REQ_MASK_WCG	1 << BE_FW_DWLD_TYPE_WCG
#define FWL_FW_INIT_REQ_MASK_LED		1 << BE_FW_DWLD_TYPE_LED
#define FWL_FW_INIT_REQ_MASK_HDR		1 << BE_FW_DWLD_TYPE_HDR

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	BOOLEAN bMcuIsAlive;
	UINT32 ui32FwInitReqMask;
	UINT32 ui32FwBaseAddr[BE_FW_DWLD_TYPE_MAXNUM];
} FWL_INFO_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BE_FIRMWARE_T gHeader_Firmware_H13A0[BE_FW_DWLD_TYPE_MAXNUM] = 
	{
		{ BE_FW_DWLD_TYPE_FRC, sizeof(ui32FrcFirmware_H13A0), (char *)ui32FrcFirmware_H13A0, TRUE },
		{ BE_FW_DWLD_TYPE_SRE, sizeof(ui32SreFirmware_H13A0), (char *)ui32SreFirmware_H13A0, FALSE },
		{ BE_FW_DWLD_TYPE_WCG, sizeof(ui32WcgFirmware_H13A0), (char *)ui32WcgFirmware_H13A0, FALSE },
		{ BE_FW_DWLD_TYPE_LED, sizeof(ui32LedFirmware_H13A0), (char *)ui32LedFirmware_H13A0, FALSE },
		{ BE_FW_DWLD_TYPE_HDR, sizeof(ui32HdrFirmware_H13A0), (char *)ui32HdrFirmware_H13A0, FALSE }
	};

BE_FIRMWARE_T gHeader_Firmware_H13B0[BE_FW_DWLD_TYPE_MAXNUM] = 
	{
		{ BE_FW_DWLD_TYPE_FRC, sizeof(ui32FrcFirmware_H13B0), (char *)ui32FrcFirmware_H13B0, TRUE },
		{ BE_FW_DWLD_TYPE_SRE, sizeof(ui32SreFirmware_H13B0), (char *)ui32SreFirmware_H13B0, FALSE },
		{ BE_FW_DWLD_TYPE_WCG, sizeof(ui32WcgFirmware_H13B0), (char *)ui32WcgFirmware_H13B0, FALSE },
		{ BE_FW_DWLD_TYPE_LED, sizeof(ui32LedFirmware_H13B0), (char *)ui32LedFirmware_H13B0, FALSE },
		{ BE_FW_DWLD_TYPE_HDR, sizeof(ui32HdrFirmware_H13B0), (char *)ui32HdrFirmware_H13B0, FALSE }
	};

BE_FW_FILE_T gFile_Firmware_H13A0[BE_FW_DWLD_TYPE_MAXNUM] = 
	{
		{ BE_FW_DWLD_TYPE_FRC, "/root/h13_firmware/frc_fw_h13a0.bin", TRUE },
		{ BE_FW_DWLD_TYPE_SRE, "/root/h13_firmware/sre_fw_h13a0.bin", FALSE },
	  	{ BE_FW_DWLD_TYPE_WCG, "/root/h13_firmware/wcg_fw_h13a0.bin", FALSE },
	  	{ BE_FW_DWLD_TYPE_LED, "/root/h13_firmware/led_fw_h13a0.bin", FALSE },
	  	{ BE_FW_DWLD_TYPE_HDR, "/root/h13_firmware/hdr_fw_h13a0.bin", FALSE }
	}; 

BE_FW_FILE_T gFile_Firmware_H13B0[BE_FW_DWLD_TYPE_MAXNUM] = 
	{
		{ BE_FW_DWLD_TYPE_FRC, "/root/h13_firmware/frc_fw_h13b0.bin", TRUE },
		{ BE_FW_DWLD_TYPE_SRE, "/root/h13_firmware/sre_fw_h13b0.bin", FALSE },
		{ BE_FW_DWLD_TYPE_WCG, "/root/h13_firmware/wcg_fw_h13b0.bin", FALSE },
		{ BE_FW_DWLD_TYPE_LED, "/root/h13_firmware/led_fw_h13b0.bin", FALSE },
		{ BE_FW_DWLD_TYPE_HDR, "/root/h13_firmware/hdr_fw_h13b0.bin", FALSE }
	}; 

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int FWL_FW_DownloadFromFile(int index);
static int FWL_FW_DownloadFromHead(int index);
static int FWL_FW_Download(BE_FW_DWLD_T param, BOOLEAN fromFile);
static int FWL_FW_InitializeFirmware(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static FWL_INFO_T gstFwlInfo = 
	{
		.bMcuIsAlive = FALSE, 
		.ui32FwInitReqMask = 0x0
	};
const static UINT32 gui32FwInitReqMask[BE_FW_DWLD_TYPE_MAXNUM] = 
	{
		FWL_FW_INIT_REQ_MASK_FRC,
		FWL_FW_INIT_REQ_MASK_SRE,
		FWL_FW_INIT_REQ_MASK_WCG,
		FWL_FW_INIT_REQ_MASK_LED,
		FWL_FW_INIT_REQ_MASK_HDR
	};

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief download BE firmware
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_FW_Update(unsigned long arg)
{
	int ret = RET_OK;
	BE_FW_DWLD_T stParams;

	do {
		ret = copy_from_user(&stParams, (BE_FW_DWLD_T *)arg, sizeof(BE_FW_DWLD_T));
		if(ret) BREAK_WRONG(ret);
		
		ret = FWL_FW_Download(stParams, FALSE);	// fromFile == TRUE : for debug
		if(ret) BREAK_WRONG(ret);

		ret = FWL_FW_InitializeFirmware();
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

static int FWL_FW_Download(BE_FW_DWLD_T param, BOOLEAN fromFile)
{
	int ret = RET_OK;
	UINT32 idx;
	UINT32 count = 0;
	#define FW_DOWNLOAD_TIMEOUT	5000

	do {
		for(idx = 0 /* BE_FW_DWLD_TYPE_FRC */; idx < BE_FW_DWLD_TYPE_MAXNUM; idx++)
		{
			if(param.type == idx && param.size && param.pData)	// case : from user buffer
			{
				BE_FIRMWARE_T fwParam;
				UINT32 fwBaseAddr = (UINT32)NULL;

				if(param.size > FWL_HAL_GetFwMemBaseSize(param.type)) BREAK_WRONG(param.size);
				
				fwParam.index = param.type;
				fwParam.size = param.size;
				fwParam.pBuffer = NULL;
				fwParam.isMcuFw = FALSE;
				
				if(param.type == BE_FW_DWLD_TYPE_FRC)
				{
					fwParam.isMcuFw = TRUE;
				}
				fwParam.pBuffer = OS_Malloc(param.size);
			 	CHECK_NULL(fwParam.pBuffer);
			    	ret = copy_from_user(fwParam.pBuffer, (void __user *)param.pData, param.size);
			    	if (ret) 
				{
					OS_Free(fwParam.pBuffer);
					BREAK_WRONG(ret);
			     	}
				
				fwBaseAddr = FWL_HAL_FW_Download(&fwParam);
				OS_Free(fwParam.pBuffer);
				CHECK_NULL(fwBaseAddr);
				
				gstFwlInfo.ui32FwInitReqMask |= gui32FwInitReqMask[idx];
				gstFwlInfo.ui32FwBaseAddr[idx] = fwBaseAddr;
				break;
			}
			else if(param.type == idx || (param.type == BE_FW_DWLD_TYPE_ALL && (!param.size || !param.pData))) // case : from header or (file)
			{
				if (fromFile) // for debug only
				{
					ret = FWL_FW_DownloadFromFile(idx);
					if(ret) BREAK_WRONG(ret);
				} 
				else 
				{
					ret = FWL_FW_DownloadFromHead(idx);
					if(ret) BREAK_WRONG(ret);
				}
				
				if(param.type != BE_FW_DWLD_TYPE_ALL || idx == BE_FW_DWLD_TYPE_MAXNUM-1) break;
			}
		}
		if(idx == BE_FW_DWLD_TYPE_MAXNUM)
		{
			ret = RET_INVALID_PARAMS;
			BREAK_WRONG(ret);
		}
		if(ret) break;

		while (param.type == BE_FW_DWLD_TYPE_ALL || param.type == BE_FW_DWLD_TYPE_FRC) {
			if (FWL_HAL_MCUisAlive()) 
			{
				gstFwlInfo.bMcuIsAlive = TRUE;
				break;
			}
			msleep(1);
			count++;
			if(count == FW_DOWNLOAD_TIMEOUT)
			{
				BE_ERROR("<error> BE firmware is not working\n");
			}
			if(count == (FW_DOWNLOAD_TIMEOUT<<1))
			{
				ret = RET_ERROR;
				BREAK_WRONG(ret);			
			}
		}
	} while(0);

	return ret;
}

static int FWL_FW_DownloadFromFile(int index)
{
	int ret = RET_OK;
	int    fw_size;
	char*    fw_data;
	OS_FILE_T fw_file;
	BE_FIRMWARE_T stParams;
	BE_FW_FILE_T *pFw;
	UINT32 fwBaseAddr = (UINT32)NULL;

	do {
		if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
			pFw = &gFile_Firmware_H13B0[index];
		else
			pFw = &gFile_Firmware_H13A0[index];

		CHECK_NULL(pFw->fwName);
		if( RET_OK != OS_OpenFile(&fw_file, pFw->fwName, O_RDONLY | O_LARGEFILE, 0666) )
		{
			BE_ERROR("<error> file open (%s)\n", pFw->fwName);
			ret = RET_ERROR;
			break;
		}
		fw_size = OS_SizeOfFile(&fw_file);
		if(fw_size < 0)
		{
			BE_ERROR("<error> file size %d\n", fw_size);
			ret = RET_ERROR;
			break;
		}
		fw_data = OS_KMalloc(fw_size);
		OS_ReadFile(&fw_file, fw_data, fw_size);

		stParams.index = pFw->inx;
		stParams.size    = fw_size;
		stParams.pBuffer = fw_data;
		stParams.isMcuFw = pFw->isMcuFw;
		fwBaseAddr = FWL_HAL_FW_Download(&stParams);

		OS_CloseFile(&fw_file);
		OS_KFree(fw_data);
		CHECK_NULL(fwBaseAddr);

		gstFwlInfo.ui32FwInitReqMask |= gui32FwInitReqMask[index];
		gstFwlInfo.ui32FwBaseAddr[index] = fwBaseAddr;
	} while(0);

	return ret;
}

static int FWL_FW_DownloadFromHead(int index)
{
	int ret = RET_OK;
	BE_FIRMWARE_T* pFw;
	UINT32 fwBaseAddr = (UINT32)NULL;

	do {
		if(lx_chip_rev() >= LX_CHIP_REV(H13, B0))
			pFw = &gHeader_Firmware_H13B0[index];
		else
			pFw = &gHeader_Firmware_H13A0[index];
		
		fwBaseAddr = FWL_HAL_FW_Download(pFw);
		CHECK_NULL(fwBaseAddr);

		gstFwlInfo.ui32FwInitReqMask |= gui32FwInitReqMask[index];
		gstFwlInfo.ui32FwBaseAddr[index] = fwBaseAddr;
	} while(0);

	return ret;
}

static int FWL_FW_InitializeFirmware(void)
{
	int ret = RET_OK;
	UINT32 idx;

	do {
		if(!gstFwlInfo.bMcuIsAlive) break;

		for(idx = 0 /* BE_FW_DWLD_TYPE_FRC */; idx < BE_FW_DWLD_TYPE_MAXNUM; idx++)
		{
			switch(gstFwlInfo.ui32FwInitReqMask & gui32FwInitReqMask[idx])
			{
				case FWL_FW_INIT_REQ_MASK_FRC :
				{
					BE_INIT_T fwTopInitParam;
					BE_FRC_INIT_T fwFrcInitParam;
					BE_H3D_INIT_BLOCK_T fwH3dInitParam;
					BE_PE_INIT_BLOCK_T fwPeInitParam;

					fwTopInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_TOP_INIT, &fwTopInitParam, sizeof(BE_INIT_T));
					if(ret) BREAK_WRONG(ret);

					fwFrcInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_FRC_INIT_BLOCK, &fwFrcInitParam, sizeof(BE_FRC_INIT_T));
					if(ret) BREAK_WRONG(ret);

					fwH3dInitParam.bInitA3C = TRUE;
					fwH3dInitParam.bInitT3C = TRUE;
					ret = BE_KIPC_SetData(BE_H3D_INIT_BLOCK, &fwH3dInitParam, sizeof(BE_H3D_INIT_BLOCK_T));
					if(ret) BREAK_WRONG(ret);

					fwPeInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_PE_INIT_BLOCK, &fwPeInitParam, sizeof(BE_PE_INIT_BLOCK_T));
					if(ret) BREAK_WRONG(ret);

					gstFwlInfo.ui32FwInitReqMask &= (~gui32FwInitReqMask[idx]);
				}
					break;
				case FWL_FW_INIT_REQ_MASK_SRE :
				{
					BE_SRE_INIT_BLOCK_T fwSreInitParam;
					BE_SRE_LUT_ADDR_T fwSreLutAddr;
					BE_SRE_LOAD_LUT_T fwSreLoadLutParam;

					fwSreInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_SRE_INIT_BLOCK, &fwSreInitParam, sizeof(BE_SRE_INIT_BLOCK_T));
					if(ret) BREAK_WRONG(ret);

					fwSreLutAddr.u32SreLutDDRAddr = gstFwlInfo.ui32FwBaseAddr[idx];
					ret = BE_KIPC_SetData(BE_SRE_SET_LUT_ADDR, &fwSreLutAddr, sizeof(BE_SRE_LUT_ADDR_T));
					if(ret) BREAK_WRONG(ret);

					fwSreLoadLutParam.bLoad = TRUE;
					ret = BE_KIPC_SetData(BE_SRE_LOAD_LUT, &fwSreLoadLutParam, sizeof(BE_SRE_LOAD_LUT_T));
					if(ret) BREAK_WRONG(ret);

					gstFwlInfo.ui32FwInitReqMask &= (~gui32FwInitReqMask[idx]);
				}
					break;
				case FWL_FW_INIT_REQ_MASK_WCG :
				{
					BE_WCG_INIT_BLOCK_T fwWcgInitParam;
					BE_WCG_LUT_ADDR_T fwWcgLutAddr;
					BE_WCG_LOAD_LUT_T fwWcgLoadLutParam;

					fwWcgInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_WCG_INIT_BLOCK, &fwWcgInitParam, sizeof(BE_WCG_INIT_BLOCK_T));
					if(ret) BREAK_WRONG(ret);

					fwWcgLutAddr.u32WcgLutDDRAddr = gstFwlInfo.ui32FwBaseAddr[idx];
					ret = BE_KIPC_SetData(BE_WCG_SET_LUT_ADDR, &fwWcgLutAddr, sizeof(BE_WCG_LUT_ADDR_T));
					if(ret) BREAK_WRONG(ret);

					fwWcgLoadLutParam.bLoad = TRUE;
					ret = BE_KIPC_SetData(BE_WCG_LOAD_LUT, &fwWcgLoadLutParam, sizeof(BE_WCG_LOAD_LUT_T));
					if(ret) BREAK_WRONG(ret);

					gstFwlInfo.ui32FwInitReqMask &= (~gui32FwInitReqMask[idx]);
				}
					break;
				case FWL_FW_INIT_REQ_MASK_LED :
				{
					BE_LED_INIT_BLOCK_T fwLedInitParam;
					BE_LED_LUT_ADDR_T fwLedLutAddr;
					BE_LED_LOAD_LUT_T fwLedLoadLutParam;

					fwLedInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_LED_INIT_BLOCK, &fwLedInitParam, sizeof(BE_LED_INIT_BLOCK_T));
					if(ret) BREAK_WRONG(ret);

					fwLedLutAddr.u32LedLutDDRAddr = gstFwlInfo.ui32FwBaseAddr[idx];
					ret = BE_KIPC_SetData(BE_LED_SET_LUT_ADDR, &fwLedLutAddr, sizeof(BE_LED_LUT_ADDR_T));
					if(ret) BREAK_WRONG(ret);

					fwLedLoadLutParam.bLoad = TRUE;
					ret = BE_KIPC_SetData(BE_LED_LOAD_LUT, &fwLedLoadLutParam, sizeof(BE_LED_LOAD_LUT_T));
					if(ret) BREAK_WRONG(ret);

					gstFwlInfo.ui32FwInitReqMask &= (~gui32FwInitReqMask[idx]);
				}
					break;
				case FWL_FW_INIT_REQ_MASK_HDR : 
				{
					BE_HDR_INIT_BLOCK_T fwHdrInitParam;
					BE_HDR_LUT_ADDR_T fwHdrLutAddr;
					BE_HDR_LOAD_LUT_T fwHdrLoadLutParam;

					fwHdrInitParam.bInit = TRUE;
					ret = BE_KIPC_SetData(BE_HDR_INIT_BLOCK, &fwHdrInitParam, sizeof(BE_HDR_INIT_BLOCK_T));
					if(ret) BREAK_WRONG(ret);

					fwHdrLutAddr.u32HdrLutDDRAddr = gstFwlInfo.ui32FwBaseAddr[idx];
					ret = BE_KIPC_SetData(BE_HDR_SET_LUT_ADDR, &fwHdrLutAddr, sizeof(BE_HDR_LUT_ADDR_T));
					if(ret) BREAK_WRONG(ret);

					fwHdrLoadLutParam.bLoad = TRUE;
					ret = BE_KIPC_SetData(BE_HDR_LOAD_LUT, &fwHdrLoadLutParam, sizeof(BE_HDR_LOAD_LUT_T));
					if(ret) BREAK_WRONG(ret);

					gstFwlInfo.ui32FwInitReqMask &= (~gui32FwInitReqMask[idx]);
				}
					break;
				default :
					/* Do nothing */
					break;
			}
			if(ret) break;
		}
	} while(0);

	return ret;
}
