
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
 *	kdriver main
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
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
#include <linux/mm.h>		// si_meminfo()
#include <linux/spinlock.h>

#include "base_drv.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
DEFINE_SPINLOCK (g_Base_AVLipsync_Lock);

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
    /**< digital chip revision information
     *
     * [note] please refer to LX_CHIP_REV macro in base_types.h
     */
    UINT32                  chip_rev;

    /**< analog chip revision information
     *
     * [note] please refer to LX_CHIP_REV macro in base_types.h
     */
    UINT32                  ace_rev;

    /**< platform information for customizing kdriver
     *
     * [note] LX_CHIP_PLATFORM_GP, LX_CHIP_PLATFORM_COSMO, LX_CHIP_PLATFORM_FPGA
     */
    UINT32                  chip_plt;
}
LX_BASE_DEV_CFG_T;

/*----------------------------------------------------------------------------------------
    Board Basic Configuration
----------------------------------------------------------------------------------------*/
static LX_BASE_DEV_CFG_T   g_base_dev_cfg;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern char *simple_strtok(char *s, const char *delim, char **save_ptr);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern void	BASE_DEV_PreInit(void);
extern void	BASE_DEV_Init(void);
extern void BASE_DEV_Cleanup(void);
extern void	BASE_PLT_Init(void);

extern void	BASE_PROC_Init(void);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void	BASE_ProbeChipRev(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * initialize base device.
 * if global link mode, this device calls all init function of each module.
 *
*/
int
BASE_Init(void)
{
	OS_CORE_Init( ); 		/* initialize OS framework */
	BASE_ProbeChipRev( );	/* read chip info */

	OS_DEBUG_Init( ); 		/* initialize debug framework 	*/
	OS_PROC_Init( );		/* initialize proc framework 	*/

	BASE_DEV_PreInit( );
#if 1
	BASE_PLT_Init( );		/* initialize platform (board) */
#else
	BASE_MEMCFG_Init( );
	BASE_MEMCFG_Print(NULL, NULL, 0);
#endif
	BASE_DEV_Init( );

	BASE_PROC_Init( );		/* initialize BASE module proc */

	return 0;
}

/**
 * cleanup base device.
 * if global link mode, this function calls all cleanup function of each module.
*/
static void
BASE_Cleanup(void)
{
	DBG_MSG("<!> %s : BEGIN\n", __FUNCTION__);

	/* cleanup custom board */
	BASE_DEV_Cleanup( );

	DBG_MSG("<!> custom board  cleanup..\n");

#ifdef USE_QEMU_SYSTEM
	/* cleanup QEMU emulation */
	QEMU_Cleanup( );		DBG_MSG("<!> qemu  system cleanup..\n");
#endif

	/* cleanup all the base system */
	OS_PROC_Cleanup( );		DBG_MSG("<!> proc  system cleanup..\n");
	OS_DEBUG_Cleanup( );	DBG_MSG("<!> debug system cleanup..\n");
	OS_CORE_Cleanup( );

	DBG_MSG("<!> %s : END\n", __FUNCTION__);
}

/**
 *
 *
 */
static void	BASE_ProbeChipRev(void)
{
	char*	cmd_buf;
	int		cmd_buf_sz = 511;

	char *tok, *sav_tok;
	char delim[] = " \t\n";

	if( NULL == ( cmd_buf = OS_Malloc( cmd_buf_sz+1 )  ) ) goto func_exit;

#ifdef	MODULE
	{
		OS_FILE_T	file;
		if( RET_OK != OS_OpenFile( &file, "/proc/cmdline", O_RDONLY|O_LARGEFILE, 0666 ) )
		{
			printk("<error> can't open /proc/cmdline\n"); goto func_exit;
		}

		if ( 0 >= OS_ReadFile( &file, cmd_buf, cmd_buf_sz ) )
		{
			OS_CloseFile(&file);
			printk("<error> can't read /proc/cmdline\n"); goto func_exit;
		}
		OS_CloseFile(&file);
	}
#else
	{
		extern char *saved_command_line;
		cmd_buf_sz = snprintf( cmd_buf, cmd_buf_sz, "%s", saved_command_line );
	}
#endif

	/* initialize data */
	g_base_dev_cfg.chip_rev = 0x0;
	g_base_dev_cfg.ace_rev  = 0x0;
	g_base_dev_cfg.chip_plt = 0x0;

	{
#define	TOKEN_DCHIP		0x1
#define TOKEN_ACHIP		0x2
#define	TOKEN_PLATFORM	0x4
		UINT8	status = TOKEN_DCHIP|TOKEN_ACHIP|TOKEN_PLATFORM;
		UINT8	chip_model;
		UINT32	chip_rev;
		char	plat_str[0x20];

		char	chip_model0, chip_rev0;
		int		chip_model1, chip_rev1;

		tok = simple_strtok( cmd_buf, delim, &sav_tok );

		while (tok)
		{
			chip_model  = 0x0;
			chip_rev 	= 0x0;

#if 1
			/* find chip = L,9,A,0 or H,13,A,0 .. */
	        if ( (status & TOKEN_DCHIP) && sscanf( tok, "chip=%c%d%c%d", &chip_model0, &chip_model1, &chip_rev0, &chip_rev1 ) == 4 )
			{
				chip_model	= (((chip_model1/10) << 4)&0xf0) + ((chip_model1%10)&0xf);
				chip_rev 	= ((( chip_rev0 - 'A' ) + 0xA) << 4 ) + chip_rev1 ;

				g_base_dev_cfg.chip_rev = MAKE_CHIP_REV( chip_model, chip_rev );
				status &= ~TOKEN_DCHIP;
			}
#else
			/* find chip=Lxyy */
			if ( (status & TOKEN_DCHIP) && sscanf( tok, "chip=L%c %x", &chip_model, &chip_rev ) == 2 /* num of token */ )
			{
				chip_model -= '0';
				g_base_dev_cfg.chip_rev = MAKE_CHIP_REV( chip_model, chip_rev );
				status &= ~TOKEN_DCHIP;
			}
			else if ( (status & TOKEN_DCHIP) && strcmp("chip=H13A0", tok) == 0 )	// TEMP
			{
				chip_model = LX_CHIP_H13;
				chip_rev = 0xA0;
				g_base_dev_cfg.chip_rev = MAKE_CHIP_REV( chip_model, chip_rev );

				status &= ~TOKEN_DCHIP;
			}
#endif

#if 1
			/* find ace = L,9,A,0 or H,13,A,0 .. */
	        if ( (status & TOKEN_ACHIP) && sscanf( tok, "ace=%c%d%c%d", &chip_model0, &chip_model1, &chip_rev0, &chip_rev1 ) == 4 )
			{
				chip_model	= (((chip_model1/10) << 4)&0xf0) + ((chip_model1%10)&0xf);
				chip_rev 	= ((( chip_rev0 - 'A' ) + 0xA) << 4 ) + chip_rev1 ;

				g_base_dev_cfg.ace_rev = MAKE_CHIP_REV( chip_model, chip_rev );
			}
#else
			/* find ace=Lxyy */
			else if ( (status & TOKEN_ACHIP) && sscanf( tok, "ace=L%c %x", &chip_model, &chip_rev ) == 2 /* num of token */ )
			{
				chip_model -= '0';
				g_base_dev_cfg.ace_rev = MAKE_CHIP_REV( chip_model, chip_rev );

				status &= ~TOKEN_ACHIP;
			}
			else if ( (status & TOKEN_DCHIP) && strcmp("ace=H13A0", tok) == 0 )	// TEMP
			{
				chip_model = LX_CHIP_H13;
				chip_rev = 0xA0;
				g_base_dev_cfg.ace_rev = MAKE_CHIP_REV( chip_model, chip_rev );

				status &= ~TOKEN_ACHIP;
			}
#endif
			else if ( (status & TOKEN_PLATFORM) && sscanf( tok, "platform=%s", plat_str ) == 1 /* num of token */ )
			{
				g_base_dev_cfg.chip_plt = !strncmp( plat_str, "FPGA", 4 )? LX_CHIP_PLATFORM_FPGA :
										  !strncmp( plat_str, "COSMO",5 )? LX_CHIP_PLATFORM_COSMO: LX_CHIP_PLATFORM_GP;
				status &= ~TOKEN_PLATFORM;
			}

			/* all tokens done, break loop !! */
			if ( !status ) break;

			tok = simple_strtok( NULL, delim, &sav_tok );
		}
	}
func_exit:
	if ( cmd_buf ) OS_Free( cmd_buf );

	/* check if all parameters are parsed successfully.
	 * when valid token is not found, use the some default value.
	 * espacially, the default value of ace_rev is the same value as chip_rev
	 */
	if ( g_base_dev_cfg.chip_rev == 0x0 ) g_base_dev_cfg.chip_rev = LX_CHIP_REV(L9,A1);
	if ( g_base_dev_cfg.ace_rev  == 0x0 ) g_base_dev_cfg.ace_rev  = g_base_dev_cfg.chip_rev;
	if ( g_base_dev_cfg.chip_plt == 0x0 ) g_base_dev_cfg.chip_plt = LX_CHIP_PLATFORM_GP;

	printk("^Y^CHIP_REV=0x%04X ACE_REV=0x%04X CHIP_PLT=0x%04X\n", g_base_dev_cfg.chip_rev, g_base_dev_cfg.ace_rev, g_base_dev_cfg.chip_plt );
}

UINT32   lx_chip_rev    ( void )
{
    return g_base_dev_cfg.chip_rev;
}
EXPORT_SYMBOL(lx_chip_rev);


UINT32  lx_ace_rev      ( void )
{
    return g_base_dev_cfg.ace_rev;
}

UINT32  lx_chip_plt ( void )
{
    return g_base_dev_cfg.chip_plt;
}
EXPORT_SYMBOL(lx_chip_plt);


/////////////////////////////////////////////////////////////////////////////////////////
#if defined(CONFIG_LG_BUILTIN_KDRIVER) && defined(CONFIG_LGSNAP)
user_initcall_grp("kdrv",BASE_Init);
#else
module_init(BASE_Init);
#endif
module_exit(BASE_Cleanup);

MODULE_AUTHOR("LGE");
MODULE_DESCRIPTION("lg115x base driver");
//MODULE_LICENSE("LGE");
MODULE_LICENSE("GPL");

/** @} */

