
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


/**
 *	platform dependent memory configuration header
 *
 */
#ifndef __PLATFORM_MEM_MAP_H__
#define __PLATFORM_MEM_MAP_H__

/*----------------------------------------------------------------------------------------
 * 2D GFX device 
 ----------------------------------------------------------------------------------------*/
#define	GFX_DEV_MEM_BASE		0x0			/* auto allocation */
#define GFX_DEV_MEM_SIZE		(512<<20)	/* NC4 UHD GFX = 512MB */

#if 0
#define GFX_DEV_MEM_SIZE_UHD	(512<<20)	/* NC4 UHD GFX = 512MB */
#endif

/*----------------------------------------------------------------------------------------
 * XX device 
 ----------------------------------------------------------------------------------------*/

#endif /* __PLATFORM_MEM_MAP_H__ */

