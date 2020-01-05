
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
 *	main configuration for lg1150 driver
 *
 *  author		daeyoung lim ( raxis.lim@lge.com )
 *  version		1.0
 *  date		2009.11.04
 *
 *  @addtogroup lg1150_base
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
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/ctype.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/delay.h>

#include "base_types.h"
#include "base_device.h"
#include "debug_util.h"
#include "os_util.h"

#ifdef INCLUDE_KDRV_ADEC
#include "adec_cfg.h"
#endif
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif
#ifdef INCLUDE_KDRV_FBDEV
#include "fbdev_cfg.h"
#endif
#ifdef INCLUDE_KDRV_GFX
#include "gfx_cfg.h"
#endif
#ifdef INCLUDE_KDRV_PVR
#include "pvr_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VBI
#include "vbi_cfg.h"
#endif
#ifdef INCLUDE_KDRV_BE
#include "be_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VDEC
//#include "vdec_cfg.h"
#endif
#ifdef INCLUDE_KDRV_SDEC
#include "sdec_cfg.h"
#endif
#ifdef INCLUDE_KDRV_SE
#include "se_cfg.h"
#endif
#ifdef INCLUDE_KDRV_VENC
#include "venc_cfg.h"
#endif
#ifdef INCLUDE_KDRV_PNG
#include "png_cfg.h"
#endif
#ifdef INCLUDE_KDRV_AFE
#include "afe_cfg.h"
#endif
#ifdef INCLUDE_KDRV_MJPEG
#include "mjpeg_cfg.h"
#endif
#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	MAX_DDR_NUM		3

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define LX_MEMCFG_ENTRY(_m_entry)	{ .name= _STR(_m_entry), .pM=(LX_MEMCFG_T*)&(_m_entry), .nM=sizeof(_m_entry)/sizeof(LX_MEMCFG_T) }
#define LX_MEMCFG_ENTRY_END			{ .name="Total", .pM=NULL, .nM=0}

#define _MB_(_sz)	(( _sz)>>20)
#define _KB_(_sz)	(((_sz)>>10)&0x3ff)
#define _BB_(_sz)	(( _sz)     &0x3ff)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern 	char*	simple_strtok(char *s, const char *delim, char **save_ptr);
extern	int     BASE_DEVMEM_InitDevMem( LX_MEMCFG_ENTRY_T* pEntry );

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
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
static LX_MEMCFG_T	g_memory_desc_table[MAX_DDR_NUM]	= { { .name = "DDR0", .base = 0x0,	.size = 0 },
															{ .name = "DDR1", .base = 0x0,	.size = 0 },
															{ .name = "DDR2", .base = 0x0,	.size = 0 } };

static LX_MEMCFG_T	sMemCfgHdr[MAX_DDR_NUM]={ 	{ .name = "[header] DDR0", .base = 0x0, .size = 0 /* do not allocate */ },
												{ .name = "[header] DDR1", .base = 0x0, .size = 0 /* do not allocate */ },
												{ .name = "[header] DDR2", .base = 0x0, .size = 0 /* do not allocate */ } };

static LX_MEMCFG_T	gMemCfgGPU	= 	{ .name = "GPU", .base = 0x0, .size = 60<<20 };

/*---------------------------------------------------------------------------------------
 * Global Memory Configuration data base (L9/GP)
 *--------------------------------------------------------------------------------------*/
static LX_MEMCFG_ENTRY_T	g_mem_desc_table[] =
{
	LX_MEMCFG_ENTRY(sMemCfgHdr[0]),				/* DDR0 START */
	LX_MEMCFG_ENTRY(gMemCfgGPU),				/* MALI */
#ifdef INCLUDE_KDRV_GFX
	LX_MEMCFG_ENTRY(gMemCfgGfx),				/* GFX */
#endif
#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY(gMemCfgFBDev[0]),			/* FBDEV OSD0 */
	LX_MEMCFG_ENTRY(gMemCfgFBDev[1]),			/* FBDEV OSD1 */
	LX_MEMCFG_ENTRY(gMemCfgFBDev[2]),			/* FBDEV OSD2 */
//	LX_MEMCFG_ENTRY(gMemCfgFBDev[3]),			/* FBDEV OSD3 */
	LX_MEMCFG_ENTRY(gMemCfgFBHdr[0]),			/* FBDEV OSD0 */
	LX_MEMCFG_ENTRY(gMemCfgFBHdr[1]),			/* FBDEV OSD1 */
	LX_MEMCFG_ENTRY(gMemCfgFBHdr[2]),			/* FBDEV OSD2 */
//	LX_MEMCFG_ENTRY(gMemCfgFBHdr[3]),			/* FBDEV OSD3 */
#endif

	LX_MEMCFG_ENTRY(sMemCfgHdr[1]),				/* DDR1 START */
#ifdef INCLUDE_KDRV_VDEC
	//LX_MEMCFG_ENTRY(gMemCfgVdec[1]),			/* VDEC for DDR1 */
#endif
#ifdef INCLUDE_KDRV_ADEC
	LX_MEMCFG_ENTRY(gstMemCfgADEC[0]),			/* ADEC */
#endif
#ifdef INCLUDE_KDRV_PNG
	LX_MEMCFG_ENTRY(gMemCfgPng[1]),				/* PNG */
#endif
#ifdef INCLUDE_KDRV_SDEC
	LX_MEMCFG_ENTRY(gMemCfgSDECGPB[1]),			/* SDEC/TE */
#endif
#ifdef INCLUDE_KDRV_PVR
	LX_MEMCFG_ENTRY(gMemCfgDvr[1]),				/* SDEC/PVR */
#endif
#ifdef INCLUDE_KDRV_SE
	LX_MEMCFG_ENTRY(gMemCfgSE),					/* SE */
	LX_MEMCFG_ENTRY(gMemCfgSE_TZFW),			/* SE/TZ */
#endif
#ifdef INCLUDE_KDRV_VBI
	LX_MEMCFG_ENTRY(gstBufMemCfgVBIRev[1]),		/* VBI Buffer */
#endif
#ifdef INCLUDE_KDRV_AFE
	LX_MEMCFG_ENTRY(gMemCfgCvd[1]),				/* CVD (3DComb H/W Memory) */
#endif
#ifdef INCLUDE_KDRV_VENC
	LX_MEMCFG_ENTRY(gMemCfgVenc[0]),			/* VENC */
#endif
#ifdef INCLUDE_KDRV_MJPEG
	LX_MEMCFG_ENTRY(gMemCfgMjpeg),				/* MJPEG */
#endif

    LX_MEMCFG_ENTRY(sMemCfgHdr[2]),          /* DDR2 START */
#ifdef INCLUDE_KDRV_DE
	LX_MEMCFG_ENTRY(gMemCfgDe[2]),				/* DE */
#endif
#ifdef INCLUDE_KDRV_FBDEV
	LX_MEMCFG_ENTRY(gMemCfgFBDev[3]),			/* FBDEV OSD3 */
	LX_MEMCFG_ENTRY(gMemCfgFBHdr[3]),			/* FBDEV OSD3 */
#endif
	LX_MEMCFG_ENTRY_END
};

/*========================================================================================
	Implementation Group
========================================================================================*/
void	L9_COSMO_InitPlatform	( void )
{
	int	i;
	int	ret = RET_ERROR;

	/* determine memory layout */
	g_memory_desc_table[0].base = 0x28000000;
	g_memory_desc_table[0].size = 128<<20;
	g_memory_desc_table[1].base = 0x70000000;
	g_memory_desc_table[1].size = 256<<20;
	g_memory_desc_table[2].base = 0x80000000;
	g_memory_desc_table[2].size = 128<<20;

	/* make sMemCfgHdr */
	for (i=0; i<MAX_DDR_NUM; i++ )
	{
		sMemCfgHdr[i].base	= g_memory_desc_table[i].base;
		sMemCfgHdr[i].size	= g_memory_desc_table[i].size;
	}

	ret = BASE_DEVMEM_InitDevMem( g_mem_desc_table );

	if ( ret != RET_OK ) DBG_PRINT_ERROR("fatal error during making device memory layout\n");
}

/** @} */

