
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
 *	platform dependent configuration header
 *
 */
#ifndef __PLATFORM_CONFIG_H__
#define __PLATFORM_CONFIG_H__

/*----------------------------------------------------------------------------------------
 * BOARD TYPE
 *
 * CONFIG_LX_BOARD_FHD     -- support FHD display
 * CONFIG_LX_BOARD_UD      -- support UD display
 * CONFIG_LX_BOARD_STBBOX  -- support Settop Box
 ----------------------------------------------------------------------------------------*/
#define CONFIG_LX_BOARD_FHD			0		/* ON  */
#define CONFIG_LX_BOARD_UD			1		/* OFF */
#define CONFIG_LX_BOARD_STBBOX		0		/* OFF */

/*----------------------------------------------------------------------------------------
 * COMMON 
 *
 * CONFIG_LX_BOOT_LOGO     -- kdriver manage boot logo 
 *
 ----------------------------------------------------------------------------------------*/
#define	CONFIG_LX_BOOT_LOGO			1		/* ON */

/*----------------------------------------------------------------------------------------
 * OSD device 
 *
 * CONFIG_LX_BOOT_LOGO_FBDEV -- OSD layer for supporting boot logo
 * CONFIG_LX_BUILTIN_FBMEM   -- OSD driver supports builtin frame buffer
 ----------------------------------------------------------------------------------------*/
#define CONFIG_LX_BOOT_LOGO_FBDEV	0		/* POSD 0 */
#define CONFIG_LX_BUILTIN_FBMEM		0		/* OFF */

/*----------------------------------------------------------------------------------------
 * XX device 
 *
 ----------------------------------------------------------------------------------------*/

#endif /* __PLATFORM_CONFIG_H__ */

