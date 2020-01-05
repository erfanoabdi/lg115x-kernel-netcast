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
 *  driver interface header for fbdev device. ( used only within kdriver )
 *
 *  @author		raxis
 *  @version	1.0
 *  @date		2009.11.15
 *
 *  @addtogroup lg1150_fbdev
 *	@{
 */

#ifndef	_FBDEV_IMPL_H_
#define	_FBDEV_IMPL_H_

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
#include <linux/fb.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"
#include "misc_util.h"

#include "fbdev_kapi.h"
#include "fbdev_cfg.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define MODULE_NAME         	"lg115x_fb"
#define OSD0_FBNAME				"osd0_fb"
#define OSD1_FBNAME				"osd1_fb"
#define OSD2_FBNAME				"osd2_fb"
#define OSD3_FBNAME				"crsr_fb"
#define OSD_CURSOR_FBNAME   	OSD3_FBNAME

#define is_win(name, x) 		((strcmp(name, x ## _FBNAME) == 0) ? 1 : 0)

#define	BYTES_PER_WORD			8		/* 1 bitmap word =  8 byte */
#define BITS_PER_WORD			64		/* 1 bitmap word = 64 bit  */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define FBDEV_PRINT(fmt, args...)   DBG_PRINT( g_fbdev_debug_fd, 0, fmt, ##args)
#define FBDEV_TRACE(fmt, args...)   DBG_PRINT( g_fbdev_debug_fd, 1, fmt, ##args)
#define FBDEV_WARN(fmt, args...)    DBG_PRINT( g_fbdev_debug_fd, 2, "^y^[FB-WRN] %s:%d -- " fmt, __F__, __L__, ##args)
#define FBDEV_ERROR(fmt, args...)   DBG_PRINT( g_fbdev_debug_fd, 3, "^y^[FB-ERR] %s:%d -- " fmt, __F__, __L__, ##args)

#define FBDEV_TRACE_BEGIN()         FBDEV_TRACE("[FB:%d] BEGIN -- %s:%d\n", g_fbdev_trace_depth++, __F__, __L__ )
#define FBDEV_TRACE_END()           FBDEV_TRACE("[FB:%d] END    -- %s:%d\n", --g_fbdev_trace_depth, __F__, __L__ )
#define FBDEV_TRACE_MARK()          FBDEV_TRACE("[FB] LOGGING  -- %s:%d\n", __F__, __L__ )

#define FBDEV_CHECK_CODE(__checker,__if_action,fmt,args...)   \
             __CHECK_IF_ERROR(__checker, FBDEV_WARN, __if_action , fmt, ##args )

#define FBDEV_ASSERT(__checker)   \
            __CHECK_IF_ERROR( !(__checker), FBDEV_ERROR, /* nop */, "ASSERT FAILED" )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct fb_var_screeninfo    FBDEV_VAR_SCREEN_T;
typedef struct fb_fix_screeninfo    FBDEV_FIX_SCREEN_T;

typedef struct _FBDEV_CTX_T			FBDEV_CTX_T;
typedef struct _FBDEV_WIN_CTX_T		FBDEV_WIN_CTX_T;

struct scanvas
{
	/*! Stores OSD Plane id to which this image is attached. It is updated in the AttachImage function */
	int				fb_dev_id;

	UINT32			uiOSDHeaderPTR;		/* ioremapped address of OSD header */
	UINT32			uiPalettePTR;		/* physical address of palette data.
										   WORD(64 bit) Pointer to Palette allocated in SDRAM  */
	UINT32			uiBasePTR;
	UINT32			uiBitmapDataYPTR;	/* physical address of current bitmap data. 
										   WORD(64 bit) Pointer to Image (Y Component) allocated in SDRAM  */

//	UINT8			eOSDPixFmt;		 	/* Pixel Format ( represented as OSD data type )*/
//	UINT8			eOSDPixDepth; 		/* Pixel Depth ( represented as OSD data type ) */

	UINT8			bits_per_pixel;		/* pixel depth, 1,2,8,16,32... */
	UINT32			stride;				/* byte size of single line. it is humna reable value of usWordsPerLine */

	LX_RECT_T		input_win;			/* input window is used to determine area within OSD bitmap data.	
										 * when updating screen, driver finds the start address of real base
										 * address to be displayed with input_win.
										 * input_win shoule be area inside of the real OSD bitmap data.
										 * for example, if OSD bitmap data is 1366x768, input_win area should
										 * be located within (0,0,1366,768).
										 * kdriver also uses xoffset and yoffset for pan_display requet.
										 * simple equation to calucate the base address is :
										 *
										 * base_address = ( bitmap_addr + (input_win.y + yoffset) * bitmap_stride
										 *				    + ( input_win.x + xoffset )
										 */

	LX_RECT_T		output_win;			/* output window is used to determine area within display region.
										 * output window is mapped to the real display ( normally 1920x1080 )
										 * by customizing both input_win and output_win, we can display any area 
										 * of bitmap data onto any area of display region.
										 *
										 * output_win data is direactly written to the L8 OSD register.
										 */

	UINT8			bColorKeyEnable;	/* Color Key Enable */
	UINT8			bPixelOrderEnable;	/* Pixel order Enable */
	UINT8			bGlobalAlphaEnable; /* Global Alpha for 0 and 4 Pixel format */
	UINT8			bReverseScreenEnable;/* Reverse display mode enabled ? */
	UINT8			bBackImageEnable;	/* OSD has its own back image? test only */

	UINT32*			palette;			/* palette is allocated at initialiation time */

	UINT32			uiOSDColorKey;
	UINT32			uiLfsrSeed;
	UINT16  		usGlobalAlpha;

	LX_MEM_BUF_T	back_image_mem;		/* test only */

	LX_DIMENSION_T	csr_size;			/* valid only for cursor layer. user defined cursor size */
	LX_POSITION_T	csr_hotspot;		/* valid only for cursor layer. user defined hotspot position */

	FBDEV_WIN_CTX_T* dm;				/* link to image memory info (not used) */
};

/** context strucutre for each FBDEV device 
 *
 *
 */
struct _FBDEV_WIN_CTX_T
{
	/* raxis.lim (2010/11/20) -- device index 
	 * this field supports the quick access to the internal structure of OSD device driver.
	 * In L8 platform, valid range is between 0 ~ 3 
	 */
	UINT16			fb_dev_id;				
	SINT16 			users; 					/* number of requests to open fb device */

	struct fb_info	fbinfo;					/* linux fb info */
	struct scanvas	pixel;					/* image description info */

	/* framebuffer area */
  	unsigned long	fb_base_phys;			/* physical address of OSD bitmap data */
	unsigned long	fb_base;				/* N/A */
  	unsigned long	fb_size;				/* byte size of OSD bitmap data */

	/*osd header info*/
	unsigned long	osd_header_base_phys;	/* physical address of indirect OSD header data */
	unsigned long	osd_header_base;		/* ioremapped address */
	unsigned long	osd_header_size;		/* byte size of OSD header (register) */

	/*palette header info*/
	unsigned long	osd_pal_base_phys;		/* physical address of palette data */
	unsigned long	osd_pal_base;			/* ioremapped address. Not used */
	unsigned long	osd_pal_size;			/* number of color in palette, fixed ad 256 */

	dma_addr_t		map_dma;				/* N/A */
	UINT8			*map_cpu;				/* N/A */
	UINT32			map_size;				/* page aligend byte size of fb_size ( bitmap data ) */

	UINT8			*screen_cpu;			/* N/A */
	dma_addr_t		screen_dma;				/* same as fb_base_phys ( physical addres of bitmap data ) */

  	UINT32			pseudo_palette[17];		/* linux fb: fake palette of 16 colors. not used ? */

 	/* flag to identify if framebuffer area is fixed already or not */
  	int				alloc_fb_mem;			/* N/A */
  	unsigned long	sdram_address;			/* N/A */

	OS_SEM_T		fb_dev_mtx;				/* mutex for each FB device */

	struct
	{
		BOOLEAN		b_use_vsync;			/* current FB should wait for vsync for every flip operaration or not */
	}
	status;

	int				vsync_cnt_on_flip;		/* vsync count that will be used to
											   wait on flipping. <0 will not
											   care the vsync. */
	int				vsync_cnt;

	UINT32			freeze_ctrl_mask;		/* if freeze mask is non-zero value, fb kdriver should block some operation
											   accoring to freeze_mask 
											 */
	/* pointer to parent context */
	FBDEV_CTX_T*	dm;
};

/** main context structure for FBDEV controller 
 *
 *
 */
struct _FBDEV_CTX_T
{
	FBDEV_WIN_CTX_T*	winfo[FBDEV_MAX_DEVICE];

	/** memory mapped I/O access 
	 *	mmio_base_phys points the ioremapped address of OSD register.
	 *	mmio_size is the total byte size of OSD register
	 */
	unsigned long		mmio_base_phys;
	unsigned long		mmio_size;

	/** handle for the linux platform device */
	struct device		*dev;
};

/* FBDEV regiseter configuration 
 *
 *
 */
typedef struct
{
    char*       chip_name;
    UINT32      reg_base_addr;
    UINT32      reg_size;
    UINT32      irq_num;

	UINT32		slkrd_prefix_mask;
	UINT32		slkrd_mmap_mask;

#define	FBDEV_HDR_OP_MMIO	0
#define FBDEV_HDR_OP_REG	1
	UINT32		hdr_op_method:1,		/* heaer operation method */
				:31;

	UINT32		frame_base_addr;		/* predefined FB device memory adress. value 0x0 means dynamic allocation */
	UINT32		frame_base_size;		/* FB device memory size */
}
LX_FBDEV_REG_IO_CTX_T;

typedef enum
{
	/* issued when FB pixel format changing
	 * data[0] = layerId, data[1] = bpp
	 */
	FBDEV_HW_EVENT_PXL_FMT_CHANGE			= 0,	
	FBDEV_HW_EVENT_REVERSE_SCREEN_CHANGE,
	FBDEV_HW_EVENT_VSYNC,

	/* issued when FB is opened or closed 
	 * data[0] = layerId
	 */
	FBDEV_HW_EVENT_POSD_OPEN,
	FBDEV_HW_EVENT_POSD_CLOSE,
}
FBDEV_HW_EVENT_T;

typedef union
{
	/* general data */
	struct
	{
		UINT32	arg[4];
	}
	gen;

	/* FBDEV_HW_EVENT_PXL_FMT_CHANGE */
	struct 
	{
		UINT32	fb_dev_id;
		UINT32	bits_per_pixel;;
	} 
	pxl_fmt_change;

	struct
	{
		UINT32	fb_dev_id;
		UINT32	enable;
	}
	reverse_screen_change;

	/* FBDEV_HW_EVENT_VSYNC */
	struct
	{
		UINT32	sync_counter;
	}
	vsync;

	/* FBDEV_HW_EVENT_POSD_OPEN, FBDEV_HW_EVENT_POSD_CLOSE */
	struct
	{
		UINT32	fb_dev_id;	
	}
	osd;
}
FBDEV_HW_EVENT_DATA_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	struct fb_var_screeninfo*	FBDEV_GetVarScreenObject 	(int idx);

void			FBDEV_InitCfg				(void);
void			FBDEV_InitHWCtx				(void);

void			FBDEV_GetDefaultPalData     (UINT32* pPal);
void			FBDEV_InitCanvas            (FBDEV_WIN_CTX_T *w);
int				FBDEV_CleanupLayer          (FBDEV_WIN_CTX_T *w);

void			FBDEV_SetPalette			(FBDEV_WIN_CTX_T *w, UINT32* palette, int num_pal );	
void			FBDEV_SetOSDImageEndian     (int layer, int bpp);

/** execute FBDEV internal event 
 *
 */
void			FBDEV_ExecFBHWHandler			(FBDEV_HW_EVENT_T ev, FBDEV_HW_EVENT_DATA_T* data );

/** get FB main context
 *
 * @return pointer to FB device driver 
 */
FBDEV_CTX_T*	FBDEV_GetCtx		(void);

/** get windows context based on OSD layer
 *
 *
 * @return pointer to dm_win_info if valid layer, NULL otherwise
 */
FBDEV_WIN_CTX_T* FBDEV_GetWinCtx 	(int layer);

/** get window canvas based on OSD layer
 *
 *
 * @return pointer to scanvas if valid layer, NULL otherwise
 */
struct scanvas*	FBDEV_GetWinCanvas	( int layer );


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int						g_fbdev_debug_fd;		/** debug id */	
extern	int						g_fbdev_trace_depth;	/** debug trace */

extern	int						g_fbdev_osd_freeze;
extern  LX_FBDEV_CFG_T*			g_fbdev_cfg;
extern  FBDEV_CTX_T*			g_dm_ctx;				/** FBDEV main context */ 
extern	LX_FBDEV_REG_IO_CTX_T*	g_reg_io_ctx;			/** FBDEV register I/O context */

extern	UINT32					g_fbdev_vsync_cnt;		/** current VSYNC count status */

/* FBDEV config access macro */
#define LX_FBDEV_CFG(_fld)  g_fbdev_cfg->_fld

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_DRV_H_ */

/** @} */
