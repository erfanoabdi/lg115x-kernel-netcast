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
 *  register interface implementation for png device of lg1152. ( used only within kdriver )
 *	png device will teach you how to make device driver with new platform.
 *
 *  @author		Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version	1.0 
 *  @date		2011.04.21
 *
 *  @addtogroup lg1152_png
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define SUPPORT_ROBUST_PNG_RESET

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
#include "png_reg_l9.h"
#include "icod_reg_l9.h"
#include "png_reg_api_type.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PNG_REG_BASE		( L9_IOCD_BASE + 0x0400 )
#define ICOD_REG_BASE		( L9_IOCD_BASE + 0x0C00 )

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
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void		PNG_REG_Initialize(void);
static void		PNG_REG_Reset(void);
static void		PNG_REG_SetInterruptMask(UINT32 i_ui32Interrupts, BOOLEAN i_bEnable);
static UINT32	PNG_REG_GetInterruptStatus(void);
static void		PNG_REG_ClearInterrupt(UINT32 i_ui32Interrupts);
static void		PNG_REG_Start(void);
static void		PNG_REG_MidStart(void);
static void		PNG_REG_SetReadBaseAddress(UINT32 i_ui32Address);
static void		PNG_REG_SetReadByteSzie(UINT32 i_ui32Size);
static void		PNG_REG_SetWriteBaseAddress(UINT32 i_ui32Address);
static void		PNG_REG_SetImageInfo(UINT16 i_ui16Width, UINT16 i_ui16Height, UINT8 i_ui8BitDepth, UINT8 ui8ColorType);
static void		PNG_REG_SetDMAReadValue(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2);
static void		PNG_REG_SetDMAWriteValue(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2);
static void		PNG_REG_SetReadByteDrop(UINT8 i_ui32Start, UINT8 i_ui32End);
static void		PNG_REG_SetReadBaseAddressWin(UINT32 i_ui32Address);
static void		PNG_REG_SetWriteBaseAddressWin(UINT32 i_ui32Address);
static void		PNG_REG_SetDMAReadValueWin(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2);
static void		PNG_REG_SetDMAWriteValueWin(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2);
static void		PNG_REG_SetReadBaseAddressFilter(UINT32 i_ui32Address);
static void		PNG_REG_SetWriteBaseAddressFilter(UINT32 i_ui32Address);
static void		PNG_REG_SetDMAReadValueFilter(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2);
static void		PNG_REG_SetDMAWriteValueFilter(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2);

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
PNG_REG_API_T g_stRegAPI_l9 = {
	PNG_REG_Initialize,
	PNG_REG_Reset,
	PNG_REG_SetInterruptMask,
	PNG_REG_GetInterruptStatus,
	PNG_REG_ClearInterrupt,
	PNG_REG_Start,
	PNG_REG_MidStart,
	PNG_REG_SetReadBaseAddress,
	PNG_REG_SetReadByteSzie,
	PNG_REG_SetWriteBaseAddress,
	PNG_REG_SetImageInfo,
	PNG_REG_SetDMAReadValue,
	PNG_REG_SetDMAWriteValue,
	PNG_REG_SetReadByteDrop,
	PNG_REG_SetReadBaseAddressWin,
	PNG_REG_SetWriteBaseAddressWin,
	PNG_REG_SetDMAReadValueWin,
	PNG_REG_SetDMAWriteValueWin,
	PNG_REG_SetReadBaseAddressFilter,
	PNG_REG_SetWriteBaseAddressFilter,
	PNG_REG_SetDMAReadValueFilter,
	PNG_REG_SetDMAWriteValueFilter
};

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static volatile PNG_REG_T* _g_pRegPNG = NULL;		/** PNG register */
static volatile ICOD_REG_T* _g_pRegICOD = NULL;		/** ICOD register */

/*========================================================================================
	Implementation Group
========================================================================================*/
#include "l9/base_addr_sw_l9.h"

static void
PNG_REG_Initialize(void)
{
	LX_ADDR_SW_CFG_T addr_sw_cfg;

	_g_pRegPNG = (volatile PNG_REG_T*)PNG_REG_BASE;
	_g_pRegICOD = (volatile ICOD_REG_T*)ICOD_REG_BASE; 

	BASE_L9_GetAddrSwCfg( ADDR_SW_CFG_ICOD, &addr_sw_cfg );

	// Address switching
	_g_pRegICOD->addr_sw_de_sav = addr_sw_cfg.de_sav;
	_g_pRegICOD->addr_sw_cpu_gpu = addr_sw_cfg.cpu_gpu;
	_g_pRegICOD->addr_sw_cpu_shadow = addr_sw_cfg.cpu_shadow;
}

static void
PNG_REG_Reset(void)
{
	UINT32	rst_clk_cnt = 0;

	/* reset PNG H/W and wait for completion */
	_g_pRegICOD->sw_rst.sw_rst_png = 1;
#ifdef SUPPORT_ROBUST_PNG_RESET
	while(1)
	{
		if ( rst_clk_cnt < 600 )	/* I think 600 clk ( 3 usec ) in 5ns/1clk is enough to wait. average wait time is 500 clk ( 2.5 usec ) */
		{
			OS_NsecDelay(5);
		}
		else
		{
			DBG_PRINT_ERROR("[png] too many clk %d for PNG reset. critical error\n", rst_clk_cnt);
			OS_MsecSleep(1);	/* 1 msec means that 200,000 clk !!!!! it's very critical case !! */
		}

		rst_clk_cnt++;

		if ( _g_pRegICOD->intr_status_sw_rst_done.intr_status_sw_rst_done_png == 0x1 )
		{
			_g_pRegICOD->intr_clear_sw_rst_done.intr_clear_sw_rst_done_png = 0x1;
//			printk("[png] png reset time = %d clk\n", rst_clk_cnt );
			break;
		}

	}
#else
	while(  _g_pRegICOD->sw_rst.sw_rst_status_png != 0 ) {;}
#endif
}

static void
PNG_REG_SetInterruptMask(UINT32 i_ui32Interrupts, BOOLEAN i_bEnable)
{
	if( i_bEnable ) { *((volatile UINT32*)(&(_g_pRegPNG->intr_enable))) = *((UINT32*)(&(_g_pRegPNG->intr_enable))) |  i_ui32Interrupts; }
	else			{ *((volatile UINT32*)(&(_g_pRegPNG->intr_enable))) = *((UINT32*)(&(_g_pRegPNG->intr_enable))) & ~i_ui32Interrupts; }
}

static UINT32
PNG_REG_GetInterruptStatus(void)
{
	return *((UINT32*)(&(_g_pRegPNG->intr_status)));
}

static void
PNG_REG_ClearInterrupt(UINT32 i_ui32Interrupts)
{
	*((volatile UINT32*)(&(_g_pRegPNG->intr_clear))) = i_ui32Interrupts;
}

static void
PNG_REG_Start(void)
{
	_g_pRegPNG->cmd.start = 1;
}

static void
PNG_REG_MidStart(void)
{
	_g_pRegPNG->cmd.mid_start = 1;
}

static void
PNG_REG_SetReadBaseAddress(UINT32 i_ui32Address)
{
	_g_pRegPNG->read_base_addr = i_ui32Address;
}

static void
PNG_REG_SetReadByteSzie(UINT32 i_ui32Size)
{
	_g_pRegPNG->read_byte_size = i_ui32Size;
}

static void
PNG_REG_SetWriteBaseAddress(UINT32 i_ui32Address)
{
	_g_pRegPNG->write_base_addr = i_ui32Address;
}

static void
PNG_REG_SetImageInfo(UINT16 i_ui16Width, UINT16 i_ui16Height, UINT8 i_ui8BitDepth, UINT8 ui8ColorType)
{
	*((volatile UINT32*)(&(_g_pRegPNG->image_info1))) = (i_ui16Width<<16) | i_ui16Height;
	*((volatile UINT32*)(&(_g_pRegPNG->image_info2))) = ((ui8ColorType&0x07)<<8) | (i_ui8BitDepth&0x1F);
}

static void
PNG_REG_SetDMAReadValue(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2)
{
	*((volatile UINT32*)(&(_g_pRegPNG->dma_read_value))) = ((i_ui8TxID&0x03)<<24) | (i_ui16Delay<<8) | ((i_ui8Priority1&0x0F)<<4) | (i_ui8Priority2&0x0F);
}

static void
PNG_REG_SetDMAWriteValue(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2)
{
	*((volatile UINT32*)(&(_g_pRegPNG->dma_write_value))) = ((i_ui8TxID&0x03)<<24) | (i_ui16Delay<<8) | ((i_ui8Priority1&0x0F)<<4) | (i_ui8Priority2&0x0F);
}

static void
PNG_REG_SetReadByteDrop(UINT8 i_ui32Start, UINT8 i_ui32End)
{
	*((volatile UINT32*)(&(_g_pRegPNG->read_byte_drop))) = ((i_ui32End&0x0F)<<16) | (i_ui32End&0x0F);
}

static void
PNG_REG_SetReadBaseAddressWin(UINT32 i_ui32Address)
{
	_g_pRegPNG->read_base_addr_win = i_ui32Address;
}

static void
PNG_REG_SetWriteBaseAddressWin(UINT32 i_ui32Address)
{
	_g_pRegPNG->write_base_addr_win = i_ui32Address;
}

static void
PNG_REG_SetDMAReadValueWin(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2)
{
	*((volatile UINT32*)(&(_g_pRegPNG->dma_read_value_win))) = ((i_ui8TxID&0x03)<<24) | (i_ui16Delay<<8) | ((i_ui8Priority1&0x0F)<<4) | (i_ui8Priority2&0x0F);
}

static void
PNG_REG_SetDMAWriteValueWin(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2)
{
	*((volatile UINT32*)(&(_g_pRegPNG->dma_write_value_win))) = ((i_ui8TxID&0x03)<<24) | (i_ui16Delay<<8) | ((i_ui8Priority1&0x0F)<<4) | (i_ui8Priority2&0x0F);
}

static void
PNG_REG_SetReadBaseAddressFilter(UINT32 i_ui32Address)
{
	_g_pRegPNG->read_base_addr_filter= i_ui32Address;
}

static void
PNG_REG_SetWriteBaseAddressFilter(UINT32 i_ui32Address)
{
	_g_pRegPNG->write_base_addr_filter= i_ui32Address;
}

static void
PNG_REG_SetDMAReadValueFilter(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2)
{
	*((volatile UINT32*)(&(_g_pRegPNG->dma_read_value_filter))) = ((i_ui8TxID&0x03)<<24) | (i_ui16Delay<<8) | ((i_ui8Priority1&0x0F)<<4) | (i_ui8Priority2&0x0F);
}

static void
PNG_REG_SetDMAWriteValueFilter(UINT8 i_ui8TxID, UINT16 i_ui16Delay, UINT8 i_ui8Priority1, UINT8 i_ui8Priority2)
{
	*((volatile UINT32*)(&(_g_pRegPNG->dma_write_value_filter))) = ((i_ui8TxID&0x03)<<24) | (i_ui16Delay<<8) | ((i_ui8Priority1&0x0F)<<4) | (i_ui8Priority2&0x0F);
}

