
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
 *	board specific configuration
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version		1.0
 *  date		2009.11.14
 *
 *  @addtogroup lg1150_base
 * @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "debug_util.h"
#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32	chip;
	UINT32	plt;
	void (*InitPlatform)(void);
}
LX_PLATFORM_INIT_DATA_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void	L9_GP_InitPlatform(void);
extern void	L9_COSMO_InitPlatform(void);
extern void	H13_GP_InitPlatform(void);
extern void	H13_COSMO_InitPlatform(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
/**
 *
 *
 */
static LX_PLATFORM_INIT_DATA_T	g_platform_init_table[] =
{
	{	LX_CHIP_L9,		LX_CHIP_PLATFORM_GP,		L9_GP_InitPlatform },		
	{	LX_CHIP_L9, 	LX_CHIP_PLATFORM_COSMO,		L9_COSMO_InitPlatform },

	{	LX_CHIP_H13,	LX_CHIP_PLATFORM_GP,		H13_GP_InitPlatform },
	{	LX_CHIP_H13,	LX_CHIP_PLATFORM_COSMO,		H13_COSMO_InitPlatform },	
};

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void		BASE_PLT_Init	( void )
{
	int	ret = RET_ERROR;
	int i;
	int	num_platform = NELEMENTS(g_platform_init_table);

	/* find the current platform */
	for ( i=0; i<num_platform; i++ )
	{
		if ( !LX_COMP_CHIP( lx_chip_rev(), g_platform_init_table[i].chip ) && lx_chip_plt() == g_platform_init_table[i].plt )
		{
			if ( g_platform_init_table[i].InitPlatform) 
			{
				g_platform_init_table[i].InitPlatform( ); ret = RET_OK; break;
			}
		}
	}

	if ( ret != RET_OK ) DBG_PRINT_ERROR("valid platform not found !!!\n");
}

/*========================================================================================
	Implementation Group
========================================================================================*/

/** @} */

