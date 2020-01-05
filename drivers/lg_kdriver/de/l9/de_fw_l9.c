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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2010.07.16
 * note       Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "os_util.h"
#include "proc_util.h"

#include "de_model.h"
#include "de_ver_def.h"

#ifdef USE_KDRV_CODES_FOR_L9
#include "de_kapi.h"
#include "de_int_def.h"
#include "de_hal_def.h"
#include "de_fw_def.h"
#include "de_fw.h"
#include "l9/de_ipc_def_l9.h"
#include "l9/de_reg_l9.h"
#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_KENEL
#if defined(USE_DE_FIRMWARE_RUN_IN_PAK)
#include "l9/de_fw_pak_l9b0.h"
#include "l9/de_fw_pak_l9a0.h"
#elif defined(USE_DE_FIRMWARE_RUN_IN_ROM)
#include "l9/de_fw_rom_l9b0.h"
#include "l9/de_fw_rom_l9a0.h"
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR)
#include "l9/de_fw_ddr_l9b0.h"
#include "l9/de_fw_ddr_l9a0.h"
#else
#include "l9/de_fw_l9b0.h"
#include "l9/de_fw_l9a0.h"
#endif
#endif
/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/
#ifdef USE_DE_FIRMWARE_DWONLOAD_IN_DRIVER
#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_FILE
static DE_FW_FILE_T sDeFirmwareFromFile_L9A0[] = {
/* [L9] minjun.kim 2010-09-28 아래 값은 수정하지 마시요 */
	//{ 1, "/mnt/nsu/base/res/lglib/kdrv/firmware/led_l8_ddr.bin"},
	{ 2, "/mnt/nsu/base/res/lglib/kdrv/firmware/video_asc.bin"},
	//{ 3, "/mnt/nsu/base/res/lglib/kdrv/firmware/video_ddr.bin"},
};
#endif
#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_KENEL
LX_DE_FW_DWLD_T sDeFirmwareFromHeader_L9B0[] = {
#if defined(USE_DE_FIRMWARE_RUN_IN_PAK)
	{ 3, sizeof(gDeFirmwareInDDR_PAK_L9B0),	 (char *)gDeFirmwareInDDR_PAK_L9B0  },
#elif defined(USE_DE_FIRMWARE_RUN_IN_ROM)
	{ 1, sizeof(gDeFirmwareInIRM_ROM_L9B0),	 (char *)gDeFirmwareInIRM_ROM_L9B0  },
	{ 2, sizeof(gDeFirmwareInDRM_ROM_L9B0),	 (char *)gDeFirmwareInDRM_ROM_L9B0  },
	{ 3, sizeof(gDeFirmwareInDDR_ROM_L9B0),	 (char *)gDeFirmwareInDDR_ROM_L9B0  },
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR)
	{ 1, sizeof(gDeFirmwareInIRM_DDR_L9B0),	 (char *)gDeFirmwareInIRM_DDR_L9B0  },
	{ 2, sizeof(gDeFirmwareInDRM_DDR_L9B0),	 (char *)gDeFirmwareInDRM_DDR_L9B0  },
	{ 3, sizeof(gDeFirmwareInDDR_DDR_L9B0),	 (char *)gDeFirmwareInDDR_DDR_L9B0  },
#else
	{ 2, sizeof(gDeFirmwareInRAM_L9B0),	     (char *)gDeFirmwareInRAM_L9B0      },
#endif
};
LX_DE_FW_DWLD_T sDeFirmwareFromHeader_L9A0[] = {
#if defined(USE_DE_FIRMWARE_RUN_IN_ROM) || defined(USE_DE_FIRMWARE_RUN_IN_PAK)
	{ 1, sizeof(gDeFirmwareInIRM_ROM_L9A0),	 (char *)gDeFirmwareInIRM_ROM_L9A0  },
	{ 2, sizeof(gDeFirmwareInDRM_ROM_L9A0),	 (char *)gDeFirmwareInDRM_ROM_L9A0  },
	{ 3, sizeof(gDeFirmwareInDDR_ROM_L9A0),	 (char *)gDeFirmwareInDDR_ROM_L9A0  },
#elif defined(USE_DE_FIRMWARE_RUN_IN_DDR)
	{ 1, sizeof(gDeFirmwareInIRM_DDR_L9A0),	 (char *)gDeFirmwareInIRM_DDR_L9A0  },
	{ 2, sizeof(gDeFirmwareInDRM_DDR_L9A0),	 (char *)gDeFirmwareInDRM_DDR_L9A0  },
	{ 3, sizeof(gDeFirmwareInDDR_DDR_L9A0),	 (char *)gDeFirmwareInDDR_DDR_L9A0  },
#else
	{ 2, sizeof(gDeFirmwareInRAM_L9A0),	     (char *)gDeFirmwareInRAM_L9A0      },
#endif
};
#endif
#endif

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/

int DE_FW_L9_DownloadFromBin(void)
{
	int ret = RET_OK;
#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_FILE
	int i;

	for (i=0;i<ARRAY_SIZE(sDeFirmwareFromFile_L9A0);i++) {
		ret = DE_FW_DownloadFromFile(&sDeFirmwareFromFile_L9A0[i]);
		if (ret) break;
	}
#endif

	return ret;
}

int DE_FW_L9_DownloadFromHead(void)
{
	int ret;
	int i;
	int headerSize;
	LX_DE_FW_DWLD_T *lpDeFirmwareFromHeader = NULL;

#ifdef USE_DE_FIRMWARE_DOWNLOAD_FROM_KENEL
	if (lx_chip_rev() >= LX_CHIP_REV(L9, B0)) {
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_L9B0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_L9B0);
	} else {
		lpDeFirmwareFromHeader = sDeFirmwareFromHeader_L9A0;
		headerSize = ARRAY_SIZE(sDeFirmwareFromHeader_L9A0);
	}

	for (i=0;i<headerSize;i++) {
		ret = DE_REG_L9_FW_Download(&lpDeFirmwareFromHeader[i]);
		if (ret) break;
	}
#endif

	return ret;
}
#endif

/**  @} */
