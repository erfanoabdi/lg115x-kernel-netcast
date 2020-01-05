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
 *  register interface implementation for png device of h13. ( used only within kdriver )
 *	png device will teach you how to make device driver with new platform.
 *
 *  @author		Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version	1.0
 *  @date		2011.04.21
 *
 *  @addtogroup h13
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "../../../mcu/vdec_type_defs.h"
#include "../lg1154_vdec_base.h"
#include "../../../mcu/os_adap.h"

#include "vdo_reg.h"
#include "vdogdi_reg.h"
#include "../de_vdo_hal_api.h"
#include "../top_hal_api.h"

#define LOG_NAME	vdec_hal_vdo
#define LOG_LEVEL	log_level_error
#include "log.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	TILED_MAP_LINEAR  = 0,
	TILED_MAP_FRAME_V = 1,
	TILED_MAP_MIXED_V = 2,
	TILED_MAP_MAX
} TILED_MAP_T;

typedef struct {
	UINT32		ui32Data[69];
} TILED_MAP_CONFIG_T;

typedef struct
{
	BOOLEAN			bAutoVsync;
	UINT32			ui32CurDpbMapType;
	UINT32			ui32CurDpbTiledBase;
	UINT32			ui32CurDpbStride;
} VDO_CH_T;

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
static void _SetTiledMapType(UINT8 ui8VdoCh, UINT32 u32FrameBufStartAddr, TILED_MAP_T mapType, UINT32 ui32Stride);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static volatile UINT32 stpVdoReg = 0;//NULL;
static volatile UINT32 stpVdoGdiReg = 0;//NULL;
static VDO_CH_T	stVdoCh[DE_VDO_NUM_OF_CHANNEL];

static unsigned char update_channel[DE_VDO_NUM_OF_CHANNEL];
static unsigned int tiled[DE_IF_NUM_OF_CHANNEL];
static unsigned int bTiedChannel = FALSE;

const static TILED_MAP_CONFIG_T	_gastTiledMapConfig[TILED_MAP_MAX][2] =
{
	{	// TILED_MAP_LINEAR
		{	// < 1024
/*XY2CA*/	{	0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
/*XY2BA*/		0x00004040, 0x00004040, 0x00004040, 0x00004040,
/*XY2RA*/		0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
/*XY2RBC*/		0x00000000,
/*RBC2AXI*/		0x00000C30, 0x00000C30, 0x00000000, 0x00000041, 0x00000082, 0x000000C3, 0x00000104, 0x00000145,
				0x00000186, 0x000001C7, 0x00000208, 0x00000249, 0x00000410, 0x00000451, 0x00000492, 0x00000820,
				0x00000861, 0x000008A2, 0x000008E3, 0x00000924, 0x00000965, 0x000009A6, 0x000009E7, 0x00000A28,
				0x00000A69, 0x00000AAA, 0x00000AEB, 0x00000B2C, 0x00000C30, 0x00000C30, 0x00000C30, 0x00000C30	}
		},
		{	// > 1024
			{	0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00000000,
				0x00000C30, 0x00000C30, 0x00000000, 0x00000041, 0x00000082, 0x000000C3, 0x00000104, 0x00000145,
				0x00000186, 0x000001C7, 0x00000208, 0x00000249, 0x00000410, 0x00000451, 0x00000492, 0x00000820,
				0x00000861, 0x000008A2, 0x000008E3, 0x00000924, 0x00000965, 0x000009A6, 0x000009E7, 0x00000A28,
				0x00000A69, 0x00000AAA, 0x00000AEB, 0x00000B2C, 0x00000C30, 0x00000C30, 0x00000C30, 0x00000C30	}
		}
	},
	{	// TILED_MAP_FRAME_V
		{	// < 1024
			{	0x00003030, 0x00001010, 0x00001111, 0x00001212, 0x00001313, 0x00000303, 0x00000404, 0x00000505,
				0x00000606, 0x00001414, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00000787, 0x00000888, 0x00001595, 0x00004040,
				0x00000909, 0x00001616, 0x00001717, 0x00001818, 0x00001919, 0x00001A1A, 0x00001B1B, 0x00001C1C,
				0x00001D1D, 0x00001E1E, 0x00001F1F, 0x00003030, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x0003F0F0,
				0x00000C30, 0x00000C30, 0x00000000, 0x00000041, 0x00000082, 0x000000C3, 0x00000104, 0x00000145,
				0x00000186, 0x000001C7, 0x00000208, 0x00000249, 0x00000410, 0x00000451, 0x00000492, 0x00000820,
				0x00000861, 0x000008A2, 0x000008E3, 0x00000924, 0x00000965, 0x000009A6, 0x000009E7, 0x00000A28,
				0x00000A69, 0x00000AAA, 0x00000AEB, 0x00000B2C, 0x00000C30, 0x00000C30, 0x00000C30, 0x00000C30	}
		},
		{	// > 1024
			{	0x00003030, 0x00001010, 0x00001111, 0x00001212, 0x00001313, 0x00000303, 0x00000404, 0x00000505,
				0x00000606, 0x00001414, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00000787, 0x00000888, 0x00001595, 0x00004040,
				0x00000909, 0x00000A0A, 0x00001616, 0x00001717, 0x00001818, 0x00001919, 0x00001A1A, 0x00001B1B,
				0x00001C1C, 0x00001D1D, 0x00001E1E, 0x00001F1F, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x0003F0F0,
				0x00000C30, 0x00000C30, 0x00000000, 0x00000041, 0x00000082, 0x000000C3, 0x00000104, 0x00000145,
				0x00000186, 0x000001C7, 0x00000208, 0x00000249, 0x00000410, 0x00000451, 0x00000492, 0x00000820,
				0x00000861, 0x000008A2, 0x000008E3, 0x00000924, 0x00000965, 0x000009A6, 0x000009E7, 0x00000A28,
				0x00000A69, 0x00000AAA, 0x00000AEB, 0x00000B2C, 0x00000C30, 0x00000C30, 0x00000C30, 0x00000C30	}
		}
	},
	{	// TILED_MAP_MIXED_V
		{	// < 1024
			{	0x00003030, 0x00001111, 0x00001212, 0x00001313, 0x00001010, 0x00000303, 0x00000404, 0x00000505,
				0x00000606, 0x00001414, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00000787, 0x00000888, 0x00001595, 0x00004040,
				0x00000909, 0x00001616, 0x00001717, 0x00001818, 0x00001919, 0x00001A1A, 0x00001B1B, 0x00001C1C,
				0x00001D1D, 0x00001E1E, 0x00001F1F, 0x00003030, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00077777,
				0x00000C30, 0x00000C30, 0x00000000, 0x00000041, 0x00000082, 0x000000C3, 0x00000104, 0x00000145,
				0x00000186, 0x000001C7, 0x00000208, 0x00000249, 0x00000410, 0x00000451, 0x00000492, 0x00000820,
				0x00000861, 0x000008A2, 0x000008E3, 0x00000924, 0x00000965, 0x000009A6, 0x000009E7, 0x00000A28,
				0x00000A69, 0x00000AAA, 0x00000AEB, 0x00000B2C, 0x00000C30, 0x00000C30, 0x00000C30, 0x00000C30	}
		},
		{	// > 1024
			{	0x00003030, 0x00001111, 0x00001212, 0x00001313, 0x00001010, 0x00000303, 0x00000404, 0x00000505,
				0x00000606, 0x00001414, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00000787, 0x00000888, 0x00001595, 0x00004040,
				0x00000909, 0x00000A0A, 0x00001616, 0x00001717, 0x00001818, 0x00001919, 0x00001A1A, 0x00001B1B,
				0x00001C1C, 0x00001D1D, 0x00001E1E, 0x00001F1F, 0x00004040, 0x00004040, 0x00004040, 0x00004040,
				0x00077777,
				0x00000C30, 0x00000C30, 0x00000000, 0x00000041, 0x00000082, 0x000000C3, 0x00000104, 0x00000145,
				0x00000186, 0x000001C7, 0x00000208, 0x00000249, 0x00000410, 0x00000451, 0x00000492, 0x00000820,
				0x00000861, 0x000008A2, 0x000008E3, 0x00000924, 0x00000965, 0x000009A6, 0x000009E7, 0x00000A28,
				0x00000A69, 0x00000AAA, 0x00000AEB, 0x00000B2C, 0x00000C30, 0x00000C30, 0x00000C30, 0x00000C30	}
		}
	}
};

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetPicSize(UINT8 ui8VdoCh, UINT32 ui32PicHeight, UINT32 ui32PicWidth)
{
	UINT32		ui32PicSize = 0;

	if( ui8VdoCh >= DE_VDO_NUM_OF_CHANNEL )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

	ui32PicSize = ((ui32PicWidth & 0xFFF) << 16) | (ui32PicHeight & 0xFFF);
	VDO_CH_PIC_SIZE(ui8VdoCh) = ui32PicSize;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetBufIdx(UINT8 ui8VdoCh, UINT32 ui32BufIdx)
{
	if( ui8VdoCh >= DE_VDO_NUM_OF_CHANNEL )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

	VDO_CH_BUF_IDX(ui8VdoCh) = (ui32BufIdx & 0x1F);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetChromaFormat(UINT8 ui8VdoCh)
{
	if( ui8VdoCh >= DE_VDO_NUM_OF_CHANNEL )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

	//VDO_CH_CHROMA_FORMAT(ui8VdoCh) = ;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetScanMode(UINT8 ui8VdoCh, UINT32 ui32ScanModeType)
{
	UINT32		ui32ScanMode = 0;

	if( ui8VdoCh >= (DE_VDO_NUM_OF_CHANNEL * 2) )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}
	if( (ui32ScanModeType > 3) || (ui32ScanModeType == 0) )
	{
		log_error("[DE_VDO%d][Err] Scan Mode: %d, %s\n", ui8VdoCh, ui32ScanModeType, __FUNCTION__ );
		return;
	}

	ui32ScanMode = VDO_CH_SCAN_MODE(ui8VdoCh);

/*
	scan mode (4th bit)
	0: interlaced scan mode
	1: progressive scan mode
*/

	if( ui32ScanModeType == 3 ) // progressive
	{
		ui32ScanMode |= (1 << 4);
	}
	else if( ui8VdoCh < 2 ) // interlaced
	{
		ui32ScanMode &= ~(1 << 4);
		if( ui32ScanModeType == 1 ) // Top Field First
			ui32ScanMode &= ~(1 << 0);
		else // Bottom Field First
			ui32ScanMode |= (1 << 0);
	}

	VDO_CH_SCAN_MODE(ui8VdoCh) = ui32ScanMode;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_EnableMifWaitReqb(UINT8 ui8VdoCh, UINT8 ui32ReqbWaitCycle)
{
	VDO_CH_WAIT_REQB(ui8VdoCh) = ((1 << 28) | (ui32ReqbWaitCycle & 0xFF));
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_DisableMifWaitReqb(UINT8 ui8VdoCh)
{
	VDO_CH_WAIT_REQB(ui8VdoCh) &= ~(1 << 28);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetLineWait(UINT8 ui8VdoCh, UINT32 ui32LineWaitCycle)
{
	UINT32 ui32VdoConf;
	if( ui8VdoCh >= DE_VDO_NUM_OF_CHANNEL )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

	ui32VdoConf = VDO_CH_VDO_CONF(ui8VdoCh) & 0xFFFF;
	ui32VdoConf |= ((ui32LineWaitCycle & 0xFFFF) << 16 );

	VDO_CH_VDO_CONF(ui8VdoCh) = ui32VdoConf;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetVSyncSel(UINT8 ui8VdoCh, UINT32 ui32VSyncSrc)
{
	UINT32		ui32SyncCmd;

	if( ui8VdoCh >= (DE_VDO_NUM_OF_CHANNEL * 2) )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

	log_noti("[VDO%d] sel vsync %d\n", ui8VdoCh, ui32VSyncSrc);
/*
	vsync source sel (2bits)
	It should be set to one of the four sync source in VDEC.
*/
	ui32SyncCmd = VDO_CH_VSYNC_CMD(ui8VdoCh);

	ui32SyncCmd &= ~(0x3 << 16);
	ui32SyncCmd |= ((ui32VSyncSrc & 0x3) << 16);

	VDO_CH_VSYNC_CMD(ui8VdoCh) = ui32SyncCmd;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetVSyncMode(UINT8 ui8VdoCh, BOOLEAN bAutoGen)
{
	if( ui8VdoCh >= (DE_VDO_NUM_OF_CHANNEL * 2) )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

/*
	vsync mode (3~0 bits)
	0: MCU generation using VSYNC_GEN register
	1: Automatic generation using VBP_NUM and VSYNC_NUM registers
*/
	if( bAutoGen == TRUE )
		VDO_CH_VSYNC_CMD(ui8VdoCh) |= (1 << 8);
	else
		VDO_CH_VSYNC_CMD(ui8VdoCh) &= ~(1 << 8);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetVActvMode(UINT8 ui8VdoCh, BOOLEAN bAutoGen)
{
	if( ui8VdoCh >= (DE_VDO_NUM_OF_CHANNEL * 2) )
	{
		log_error("[DE_VDO][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

/*
	vactive mode (7~4 bits)
	0: MCU generation using VACTV_GEN register
	1: Automatic generation using VBP_NUM and VSYNC_NUM and VFP registers

	vactive automatic generation when chx_vactv_mode set to '0' (11~8 bits)
	0: MCU should set VACTV_GEN register after ch_vsync_rdy interrupt occur
	1: Automatic generation of vactive after receiption of ch_vsync_rdy from DE
*/
	if( bAutoGen == TRUE )
	{
		VDO_CH_VSYNC_CMD(ui8VdoCh) |= (1 << 9);
		VDO_CH_VSYNC_CMD(ui8VdoCh) |= (1 << 10);
	}
	else
	{
		VDO_CH_VSYNC_CMD(ui8VdoCh) &= ~(1 << 9);
		VDO_CH_VSYNC_CMD(ui8VdoCh) &= ~(1 << 10);
	}
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetVSyncGen(UINT8 ui8VdoCh)
{
/*
	vsync generation
	It is automatically cleared when set to '1'
*/
	VDO_CH_VSYNC_CMD(ui8VdoCh) |= (1 << 0);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_SetVActvGen(UINT8 ui8VdoCh)
{
/*
	vsync generation
	It is automatically cleared when set to '1'
*/
	VDO_CH_VSYNC_CMD(ui8VdoCh) |= (1 << 4);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_Init(void)
{
	UINT32 i;
	stpVdoReg		= (UINT32)VDEC_TranselateVirualAddr(VDEC_VDO_BASE, 0x100);
	stpVdoGdiReg	= (UINT32)VDEC_TranselateVirualAddr(VDEC_VDO_GDI_BASE, 0x200);

	log_noti("VDO Init\n");

	bTiedChannel = lx_chip_rev() < LX_CHIP_REV(H13, B0);

	// Vsync/Vactive Setting
	for(i=0;i<4;i++)
	{
		VDO_CH_VSYNC_CMD(i) &= ~((0x7<<8) | (0x3<<16));
		VDO_CH_VSYNC_CMD(i) |= ((0x5<<8) | ((i%2)<<16) );
		//VDO_CH_VSYNC_VACT_TERM(i&1) |= 1<<31;
		VDO_CH_VSYNC_NUM(i) = 0x00000898;//0x00000780;
	}

	stVdoCh[0].bAutoVsync = TRUE;
	stVdoCh[1].bAutoVsync = TRUE;

	stVdoCh[0].ui32CurDpbMapType = 0xFF;
	stVdoCh[1].ui32CurDpbMapType = 0xFF;
	stVdoCh[0].ui32CurDpbTiledBase = 0xFFFFFFFF;
	stVdoCh[1].ui32CurDpbTiledBase = 0xFFFFFFFF;
	stVdoCh[0].ui32CurDpbStride = 0xFFFFFFFF;
	stVdoCh[1].ui32CurDpbStride = 0xFFFFFFFF;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void	DE_VDO_HAL_InitFrameBuffer(UINT8 ui8VdoCh)
{
	if( ui8VdoCh >= DE_IF_NUM_OF_CHANNEL )
	{
		log_error("[VDEC][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}

	// TILED MAP
	//if( pFrameBuf->bInterlaced )
	//	_SetTiledMapType(ui8VdoCh, VDEC_TILED_BUF_BASE, TILED_MAP_MIXED_V);
	//else
	//	_SetTiledMapType(ui8VdoCh, VDEC_TILED_BUF_BASE, TILED_MAP_FRAME_V);
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_Update(UINT8 ui8VdoCh, S_DE_IPC_T *pDisBuf, UINT32 ui32SyncField)
{
	UINT32 ui32Size;
	UINT32 ui32PreAPBVal;

	log_user1("VdoCh %d: Y 0x%X  C 0x%X  DispMode %d, Field %d\n",
			ui8VdoCh, pDisBuf->ui32Y_FrameBaseAddr,
			pDisBuf->ui32C_FrameBaseAddr, pDisBuf->ui32DisplayMode, ui32SyncField);

	if( ui8VdoCh >= DE_IF_NUM_OF_CHANNEL )
	{
		log_error("[VDEC][Err] Channel Number(%d), %s\n", ui8VdoCh, __FUNCTION__ );
		return;
	}
	// Init for first received frame
	if( (stVdoCh[ui8VdoCh].ui32CurDpbMapType != pDisBuf->ui32DpbMapType) ||
		(stVdoCh[ui8VdoCh].ui32CurDpbTiledBase != pDisBuf->ui32Tiled_FrameBaseAddr) ||
		(stVdoCh[ui8VdoCh].ui32CurDpbStride != pDisBuf->ui32Stride) )
	{
		log_noti("VDO:%d: set dpb map type %d->%d stride %d\n", ui8VdoCh,
				stVdoCh[ui8VdoCh].ui32CurDpbMapType, pDisBuf->ui32DpbMapType,
				pDisBuf->ui32Stride);

		stVdoCh[ui8VdoCh].ui32CurDpbMapType = pDisBuf->ui32DpbMapType;
		stVdoCh[ui8VdoCh].ui32CurDpbTiledBase = pDisBuf->ui32Tiled_FrameBaseAddr;
		stVdoCh[ui8VdoCh].ui32CurDpbStride = pDisBuf->ui32Stride;

		switch(pDisBuf->ui32DpbMapType)
		{
			case 1: // Frame Mmap
				_SetTiledMapType(ui8VdoCh, pDisBuf->ui32Tiled_FrameBaseAddr,
						TILED_MAP_FRAME_V, pDisBuf->ui32Stride);
				break;
			case 2: // Mixed Map
				_SetTiledMapType(ui8VdoCh, pDisBuf->ui32Tiled_FrameBaseAddr,
						TILED_MAP_MIXED_V, pDisBuf->ui32Stride);
				break;

			case 0:	// Linear
				break;

			default :
				break;
		}
	}

	if( VDO_CH_MIF_STATUS(ui8VdoCh) || VDO_CH_RDC_STATUS(ui8VdoCh) )
	{
		static UINT32 u32DbgCnt=0;
		if( !((u32DbgCnt++) % 100 ) )
		{
			log_warning("[DE_VDO%d][Err] Status : MIF(0x%08X/0x%08X), RDC(0x%08X/0x%08X), %s\n",
					ui8VdoCh, VDO_CH_MIF_STATUS(ui8VdoCh), VDO_CH_MIF_LINE_CNT(ui8VdoCh),
					VDO_CH_RDC_STATUS(ui8VdoCh), VDO_CH_RDC_LINE_CNT(ui8VdoCh), __FUNCTION__ );
			log_warning("[DE_VDO #%d][DBG]   StallCnt Luma %d Croma %d\n",
					ui8VdoCh, VDO_CH_LUMA_STALL_CNT(ui8VdoCh),
					VDO_CH_CHMA_STALL_CNT(ui8VdoCh) );
		}
	}

//	RC0_VDO_RST_COUNT = 0x00400040			//??

	VDO_CH_VDO_CMD(ui8VdoCh) = 0x00000010;        // pic_init

	VDO_CH_WAIT_REQB(ui8VdoCh)  = 0x10000010;

	// VDO flush
	VDO_CH_FLUSH_CONF(ui8VdoCh) = 0x30000040;
	VDO_CH_VDO_CMD(ui8VdoCh) = 0x00000100;        // flush_run

	while((VDO_CH_MIF_STATUS(ui8VdoCh) & 0x1f) != 0x0)
	{
		UINT32 u32Cnt=0;
		u32Cnt++;
		if( u32Cnt > 0x100000 )
		{
			log_error("vdo #%d infinite loop: MIF Status 0x%X\n",
					ui8VdoCh, VDO_CH_MIF_STATUS(ui8VdoCh));
			break;
		}
	}

	VDO_CH_VDO_CONF(ui8VdoCh) = 0x00409000;

	// Crop (Requested by DE)
	ui32Size = ((pDisBuf->ui16PicWidth - (pDisBuf->ui32H_Offset & 0xFFFF)) << 16) |
				((pDisBuf->ui16PicHeight - (pDisBuf->ui32V_Offset & 0xFFFF)) & 0xFFFF);

	if( pDisBuf->ui16PicHeight > 1080 )
		ui32Size = (ui32Size & 0xFFFF0000) | 1080;

//	VDO_CH_VBP_NUM(ui8VdoCh)        = 0x00000780;
//	VDO_CH_VFP_NUM(ui8VdoCh)        = 0x00000780;
//	VDO_CH_VSYNC_NUM(ui8VdoCh)      = 0x00000898;//0x00000780;

	VDO_CH_PIC_SIZE(ui8VdoCh)       = ui32Size;//(pDisBuf->ui16PicWidth << 16) | (pDisBuf->ui16PicHeight & 0xFFFF);
	VDO_CH_BUF_IDX(ui8VdoCh)        = ui8VdoCh;//pDisBuf->ui32FrameIdx + (ui8VdoCh*10); /* Fixed 11 total frame each channel */
	VDO_CH_CHROMA_FORMAT(ui8VdoCh)  = 0x00040004;

	if( pDisBuf->ui32DisplayMode == 3 )
	{
		/* Progressive*/
		VDO_CH_SCAN_MODE(ui8VdoCh)  |= 0x00000010;
	}
	else
	{
		/* Interaced */
		VDO_CH_SCAN_MODE(ui8VdoCh)  &= ~(0x00000010);

		if( pDisBuf->ui32DisplayMode == 2 )
			VDO_CH_SCAN_MODE(ui8VdoCh)	|=  (0x1);
		else if( pDisBuf->ui32DisplayMode == 1 )
			VDO_CH_SCAN_MODE(ui8VdoCh)	&= ~(0x1);

		/*
		if( ui32SyncField == 0 )
		{
			if( pDisBuf->ui32DisplayMode == 2 )
				VDO_CH_SCAN_MODE(ui8VdoCh)	|=  (0x01);
			else if( pDisBuf->ui32DisplayMode == 1 )
				VDO_CH_SCAN_MODE(ui8VdoCh)	&= ~(0x01);
		}
		else
		{
			if( pDisBuf->ui32DisplayMode == 2 )
				VDO_CH_SCAN_MODE(ui8VdoCh)	&=  ~(0x01);
			else if( pDisBuf->ui32DisplayMode == 1 )
				VDO_CH_SCAN_MODE(ui8VdoCh)	|= (0x01);
		}
		*/
	}

	VDO_GDI_PIC_INIT_HOST  = 0x1;
	VDO_GDI_PIC_INIT_HOST  = 0x0;

	ui32PreAPBVal = TOP_HAL_SetApbVDO(1, 2);

	// [21:20]TILED_MIXED_MAP, [19:17]color_format(4:2:0),
	//	[16]CbCr_Interleaved, [15:0]Stride_Size
	VDO_GDI_INFO_CONTROL(ui8VdoCh)  = 0x00210000 | pDisBuf->ui32Stride;
		//_gpstFrameBuf[ui8VdoCh]->ui32Stride;
	VDO_GDI_INFO_PIC_SIZE(ui8VdoCh) = ui32Size;
	{
		//UINT32 ui32BaseAddr = (((_gpstFrameBuf[ui8VdoCh]->ui32Tiled_FrameBaseAddr +
			//pDisBuf->ui32FrameIdx * 0x003C0000)>>16)*0x4)&0xFFFF;
		VDO_GDI_INFO_BASE_Y(ui8VdoCh)   = pDisBuf->ui32Y_FrameBaseAddr;
			//_gastTiledAddr[ui8VdoCh][pDisBuf->ui32FrameIdx].ui32AddrY;
			//((ui32BaseAddr+0x50)<<16)|ui32BaseAddr;
		VDO_GDI_INFO_BASE_CB(ui8VdoCh)  = pDisBuf->ui32C_FrameBaseAddr;
			//_gastTiledAddr[ui8VdoCh][pDisBuf->ui32FrameIdx].ui32AddrCb;
			//((ui32BaseAddr+0xC8)<<16)|(ui32BaseAddr+0xA0);
		VDO_GDI_INFO_BASE_CR(ui8VdoCh)  = pDisBuf->ui32C_FrameBaseAddr;
			//_gastTiledAddr[ui8VdoCh][pDisBuf->ui32FrameIdx].ui32AddrCr;
			//((ui32BaseAddr+0xC8)<<16)|(ui32BaseAddr+0xA0);
	}

	TOP_HAL_SetApbVDO(1, ui32PreAPBVal);

//	VDO_CH_VSYNC_CMD(ui8VdoCh) |= 0x00000400;

	// VSYNC Generation
	if( !stVdoCh[ui8VdoCh].bAutoVsync )
		VDO_CH_VSYNC_CMD(ui8VdoCh) |= 0x01;

	// Run Command
	VDO_CH_VDO_CMD(ui8VdoCh) = 0x01;
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_InitCmd(void)
{
}

/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
void DE_VDO_HAL_RunCmd(UINT8 ui8DeIfCh[], UINT32 aui32DisplayInfo[], UINT32 ui32SyncField)
{
}

void DE_VDO_HAL_Register(UINT8 u8VdoCh, UINT8 u8DeIfCh, BOOLEAN bTiled)
{
	if( u8VdoCh >= DE_VDO_NUM_OF_CHANNEL )
	{
		log_error("wrong vdo channel num %d\n", u8VdoCh);
		return;
	}

	log_noti("VDO Register %d deif %d tiled %d\n", u8VdoCh, u8DeIfCh, bTiled);

	update_channel[u8VdoCh] = u8DeIfCh;

	if( !bTiedChannel )
		tiled[u8VdoCh] = bTiled;
}

void	DE_VDO_HAL_SetInterlaced(UINT8 ui8VdoCh, BOOLEAN bInterlaced)
{
	if( ui8VdoCh >= DE_VDO_NUM_OF_CHANNEL )
	{
		log_error("wrong vdo channel num %d\n", ui8VdoCh);
		return;
	}

	if( bInterlaced == TRUE )
	{
		/* Interlaced */
		VDO_CH_SCAN_MODE(ui8VdoCh)  &= ~0x00000010;
	}
	else
	{
		/* Progressive */
		VDO_CH_SCAN_MODE(ui8VdoCh)  |= 0x00000010;
	}
}

/*========================================================================================
	Static Implementation Group
========================================================================================*/
/**
********************************************************************************
* @brief
*
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*
********************************************************************************
*/
static void _SetTiledMapType(UINT8 ui8VdoCh, UINT32 u32FrameBufStartAddr, TILED_MAP_T mapType, UINT32 ui32Stride)
{
	const TILED_MAP_CONFIG_T*	pstMapCfg;
	UINT32 						ui32PreAPBVal;

	if( mapType >= TILED_MAP_MAX )
	{
		log_error("wrong tiled map type %d\n", ui8VdoCh);
		goto GOTO_END;
	}

	pstMapCfg = &_gastTiledMapConfig[(UINT32)mapType][(ui32Stride < 1024)? 0 : 1];

	// VDO GDI Setting /*{{{*/
	switch( ui8VdoCh )
	{
	case 0:
		ui32PreAPBVal = TOP_HAL_SetApbVDO(1, 4);

		VDO_GDI_XY2_CAS_0 = pstMapCfg->ui32Data[ 0];
		VDO_GDI_XY2_CAS_1 = pstMapCfg->ui32Data[ 1];
		VDO_GDI_XY2_CAS_2 = pstMapCfg->ui32Data[ 2];
		VDO_GDI_XY2_CAS_3 = pstMapCfg->ui32Data[ 3];
		VDO_GDI_XY2_CAS_4 = pstMapCfg->ui32Data[ 4];
		VDO_GDI_XY2_CAS_5 = pstMapCfg->ui32Data[ 5];
		VDO_GDI_XY2_CAS_6 = pstMapCfg->ui32Data[ 6];
		VDO_GDI_XY2_CAS_7 = pstMapCfg->ui32Data[ 7];
		VDO_GDI_XY2_CAS_8 = pstMapCfg->ui32Data[ 8];
		VDO_GDI_XY2_CAS_9 = pstMapCfg->ui32Data[ 9];
		VDO_GDI_XY2_CAS_A = pstMapCfg->ui32Data[10];
		VDO_GDI_XY2_CAS_B = pstMapCfg->ui32Data[11];
		VDO_GDI_XY2_CAS_C = pstMapCfg->ui32Data[12];
		VDO_GDI_XY2_CAS_D = pstMapCfg->ui32Data[13];
		VDO_GDI_XY2_CAS_E = pstMapCfg->ui32Data[14];
		VDO_GDI_XY2_CAS_F = pstMapCfg->ui32Data[15];

		VDO_GDI_XY2_BA_0  = pstMapCfg->ui32Data[16];
		VDO_GDI_XY2_BA_1  = pstMapCfg->ui32Data[17];
		VDO_GDI_XY2_BA_2  = pstMapCfg->ui32Data[18];
		VDO_GDI_XY2_BA_3  = pstMapCfg->ui32Data[19];

		VDO_GDI_XY2_RAS_0 = pstMapCfg->ui32Data[20];
		VDO_GDI_XY2_RAS_1 = pstMapCfg->ui32Data[21];
		VDO_GDI_XY2_RAS_2 = pstMapCfg->ui32Data[22];
		VDO_GDI_XY2_RAS_3 = pstMapCfg->ui32Data[23];
		VDO_GDI_XY2_RAS_4 = pstMapCfg->ui32Data[24];
		VDO_GDI_XY2_RAS_5 = pstMapCfg->ui32Data[25];
		VDO_GDI_XY2_RAS_6 = pstMapCfg->ui32Data[26];
		VDO_GDI_XY2_RAS_7 = pstMapCfg->ui32Data[27];
		VDO_GDI_XY2_RAS_8 = pstMapCfg->ui32Data[28];
		VDO_GDI_XY2_RAS_9 = pstMapCfg->ui32Data[29];
		VDO_GDI_XY2_RAS_A = pstMapCfg->ui32Data[30];
		VDO_GDI_XY2_RAS_B = pstMapCfg->ui32Data[31];
		VDO_GDI_XY2_RAS_C = pstMapCfg->ui32Data[32];
		VDO_GDI_XY2_RAS_D = pstMapCfg->ui32Data[33];
		VDO_GDI_XY2_RAS_E = pstMapCfg->ui32Data[34];
		VDO_GDI_XY2_RAS_F = pstMapCfg->ui32Data[35];

		//xy2rbc_config
		VDO_GDI_XY2_RBC_CONFIG = pstMapCfg->ui32Data[36];

		VDO_GDI_RBC2_AXI_0  = pstMapCfg->ui32Data[37];
		VDO_GDI_RBC2_AXI_1  = pstMapCfg->ui32Data[38];
		VDO_GDI_RBC2_AXI_2  = pstMapCfg->ui32Data[39];
		VDO_GDI_RBC2_AXI_3  = pstMapCfg->ui32Data[40];
		VDO_GDI_RBC2_AXI_4  = pstMapCfg->ui32Data[41];
		VDO_GDI_RBC2_AXI_5  = pstMapCfg->ui32Data[42];
		VDO_GDI_RBC2_AXI_6  = pstMapCfg->ui32Data[43];
		VDO_GDI_RBC2_AXI_7  = pstMapCfg->ui32Data[44];
		VDO_GDI_RBC2_AXI_8  = pstMapCfg->ui32Data[45];
		VDO_GDI_RBC2_AXI_9  = pstMapCfg->ui32Data[46];
		VDO_GDI_RBC2_AXI_A  = pstMapCfg->ui32Data[47];
		VDO_GDI_RBC2_AXI_B  = pstMapCfg->ui32Data[48];
		VDO_GDI_RBC2_AXI_C  = pstMapCfg->ui32Data[49];
		VDO_GDI_RBC2_AXI_D  = pstMapCfg->ui32Data[50];
		VDO_GDI_RBC2_AXI_E  = pstMapCfg->ui32Data[51];
		VDO_GDI_RBC2_AXI_F  = pstMapCfg->ui32Data[52];
		VDO_GDI_RBC2_AXI_10 = pstMapCfg->ui32Data[53];
		VDO_GDI_RBC2_AXI_11 = pstMapCfg->ui32Data[54];
		VDO_GDI_RBC2_AXI_12 = pstMapCfg->ui32Data[55];
		VDO_GDI_RBC2_AXI_13 = pstMapCfg->ui32Data[56];
		VDO_GDI_RBC2_AXI_14 = pstMapCfg->ui32Data[57];
		VDO_GDI_RBC2_AXI_15 = pstMapCfg->ui32Data[58];
		VDO_GDI_RBC2_AXI_16 = pstMapCfg->ui32Data[59];
		VDO_GDI_RBC2_AXI_17 = pstMapCfg->ui32Data[60];
		VDO_GDI_RBC2_AXI_18 = pstMapCfg->ui32Data[61];
		VDO_GDI_RBC2_AXI_19 = pstMapCfg->ui32Data[62];
		VDO_GDI_RBC2_AXI_1A = pstMapCfg->ui32Data[63];
		VDO_GDI_RBC2_AXI_1B = pstMapCfg->ui32Data[64];
		VDO_GDI_RBC2_AXI_1C = pstMapCfg->ui32Data[65];
		VDO_GDI_RBC2_AXI_1D = pstMapCfg->ui32Data[66];
		VDO_GDI_RBC2_AXI_1E = pstMapCfg->ui32Data[67];
		VDO_GDI_RBC2_AXI_1F = pstMapCfg->ui32Data[68];

		VDO_GDI_TILEDBUF_BASE = (u32FrameBufStartAddr);

		TOP_HAL_SetApbVDO(1, ui32PreAPBVal);
		break;

	case 1:
		ui32PreAPBVal = TOP_HAL_SetApbVDO(1, 5);
		VDO_GDI_CH1_XY2_CAS_0 = pstMapCfg->ui32Data[ 0];
		VDO_GDI_CH1_XY2_CAS_1 = pstMapCfg->ui32Data[ 1];
		VDO_GDI_CH1_XY2_CAS_2 = pstMapCfg->ui32Data[ 2];
		VDO_GDI_CH1_XY2_CAS_3 = pstMapCfg->ui32Data[ 3];
		VDO_GDI_CH1_XY2_CAS_4 = pstMapCfg->ui32Data[ 4];
		VDO_GDI_CH1_XY2_CAS_5 = pstMapCfg->ui32Data[ 5];
		VDO_GDI_CH1_XY2_CAS_6 = pstMapCfg->ui32Data[ 6];
		VDO_GDI_CH1_XY2_CAS_7 = pstMapCfg->ui32Data[ 7];
		VDO_GDI_CH1_XY2_CAS_8 = pstMapCfg->ui32Data[ 8];
		VDO_GDI_CH1_XY2_CAS_9 = pstMapCfg->ui32Data[ 9];
		VDO_GDI_CH1_XY2_CAS_A = pstMapCfg->ui32Data[10];
		VDO_GDI_CH1_XY2_CAS_B = pstMapCfg->ui32Data[11];
		VDO_GDI_CH1_XY2_CAS_C = pstMapCfg->ui32Data[12];
		VDO_GDI_CH1_XY2_CAS_D = pstMapCfg->ui32Data[13];
		VDO_GDI_CH1_XY2_CAS_E = pstMapCfg->ui32Data[14];
		VDO_GDI_CH1_XY2_CAS_F = pstMapCfg->ui32Data[15];

		VDO_GDI_CH1_XY2_BA_0  = pstMapCfg->ui32Data[16];
		VDO_GDI_CH1_XY2_BA_1  = pstMapCfg->ui32Data[17];
		VDO_GDI_CH1_XY2_BA_2  = pstMapCfg->ui32Data[18];
		VDO_GDI_CH1_XY2_BA_3  = pstMapCfg->ui32Data[19];

		VDO_GDI_CH1_XY2_RAS_0 = pstMapCfg->ui32Data[20];
		VDO_GDI_CH1_XY2_RAS_1 = pstMapCfg->ui32Data[21];
		VDO_GDI_CH1_XY2_RAS_2 = pstMapCfg->ui32Data[22];
		VDO_GDI_CH1_XY2_RAS_3 = pstMapCfg->ui32Data[23];
		VDO_GDI_CH1_XY2_RAS_4 = pstMapCfg->ui32Data[24];
		VDO_GDI_CH1_XY2_RAS_5 = pstMapCfg->ui32Data[25];
		VDO_GDI_CH1_XY2_RAS_6 = pstMapCfg->ui32Data[26];
		VDO_GDI_CH1_XY2_RAS_7 = pstMapCfg->ui32Data[27];
		VDO_GDI_CH1_XY2_RAS_8 = pstMapCfg->ui32Data[28];
		VDO_GDI_CH1_XY2_RAS_9 = pstMapCfg->ui32Data[29];
		VDO_GDI_CH1_XY2_RAS_A = pstMapCfg->ui32Data[30];
		VDO_GDI_CH1_XY2_RAS_B = pstMapCfg->ui32Data[31];
		VDO_GDI_CH1_XY2_RAS_C = pstMapCfg->ui32Data[32];
		VDO_GDI_CH1_XY2_RAS_D = pstMapCfg->ui32Data[33];
		VDO_GDI_CH1_XY2_RAS_E = pstMapCfg->ui32Data[34];
		VDO_GDI_CH1_XY2_RAS_F = pstMapCfg->ui32Data[35];

		//xy2rbc_config
		VDO_GDI_CH1_XY2_RBC_CONFIG = pstMapCfg->ui32Data[36];

		VDO_GDI_CH1_RBC2_AXI_0  = pstMapCfg->ui32Data[37];
		VDO_GDI_CH1_RBC2_AXI_1  = pstMapCfg->ui32Data[38];
		VDO_GDI_CH1_RBC2_AXI_2  = pstMapCfg->ui32Data[39];
		VDO_GDI_CH1_RBC2_AXI_3  = pstMapCfg->ui32Data[40];
		VDO_GDI_CH1_RBC2_AXI_4  = pstMapCfg->ui32Data[41];
		VDO_GDI_CH1_RBC2_AXI_5  = pstMapCfg->ui32Data[42];
		VDO_GDI_CH1_RBC2_AXI_6  = pstMapCfg->ui32Data[43];
		VDO_GDI_CH1_RBC2_AXI_7  = pstMapCfg->ui32Data[44];
		VDO_GDI_CH1_RBC2_AXI_8  = pstMapCfg->ui32Data[45];
		VDO_GDI_CH1_RBC2_AXI_9  = pstMapCfg->ui32Data[46];
		VDO_GDI_CH1_RBC2_AXI_A  = pstMapCfg->ui32Data[47];
		VDO_GDI_CH1_RBC2_AXI_B  = pstMapCfg->ui32Data[48];
		VDO_GDI_CH1_RBC2_AXI_C  = pstMapCfg->ui32Data[49];
		VDO_GDI_CH1_RBC2_AXI_D  = pstMapCfg->ui32Data[50];
		VDO_GDI_CH1_RBC2_AXI_E  = pstMapCfg->ui32Data[51];
		VDO_GDI_CH1_RBC2_AXI_F  = pstMapCfg->ui32Data[52];
		VDO_GDI_CH1_RBC2_AXI_10 = pstMapCfg->ui32Data[53];
		VDO_GDI_CH1_RBC2_AXI_11 = pstMapCfg->ui32Data[54];
		VDO_GDI_CH1_RBC2_AXI_12 = pstMapCfg->ui32Data[55];
		VDO_GDI_CH1_RBC2_AXI_13 = pstMapCfg->ui32Data[56];
		VDO_GDI_CH1_RBC2_AXI_14 = pstMapCfg->ui32Data[57];
		VDO_GDI_CH1_RBC2_AXI_15 = pstMapCfg->ui32Data[58];
		VDO_GDI_CH1_RBC2_AXI_16 = pstMapCfg->ui32Data[59];
		VDO_GDI_CH1_RBC2_AXI_17 = pstMapCfg->ui32Data[60];
		VDO_GDI_CH1_RBC2_AXI_18 = pstMapCfg->ui32Data[61];
		VDO_GDI_CH1_RBC2_AXI_19 = pstMapCfg->ui32Data[62];
		VDO_GDI_CH1_RBC2_AXI_1A = pstMapCfg->ui32Data[63];
		VDO_GDI_CH1_RBC2_AXI_1B = pstMapCfg->ui32Data[64];
		VDO_GDI_CH1_RBC2_AXI_1C = pstMapCfg->ui32Data[65];
		VDO_GDI_CH1_RBC2_AXI_1D = pstMapCfg->ui32Data[66];
		VDO_GDI_CH1_RBC2_AXI_1E = pstMapCfg->ui32Data[67];
		VDO_GDI_CH1_RBC2_AXI_1F = pstMapCfg->ui32Data[68];

		VDO_GDI_CH1_TILEDBUF_BASE = (u32FrameBufStartAddr);

		TOP_HAL_SetApbVDO(1, ui32PreAPBVal);
		break;

	default:
		log_error("wrong vdo channel num %d\n", ui8VdoCh);
		break;
	}
	// VDO GDI Setting /*}}}*/

GOTO_END:
	return;
}
