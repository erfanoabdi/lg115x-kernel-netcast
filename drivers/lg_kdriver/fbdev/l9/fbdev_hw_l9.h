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

#ifndef	_FBDEV_HW_L9_H_
#define	_FBDEV_HW_L9_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

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
	union
	{
		struct
		{
			UINT32						// OSD[0:3]_HDR0								
			osd_hdr_ypos		   :12,	//  0:11
                               	   : 4,	// 12:15 reserved
			osd_hdr_xpos           :11,	// 16:26
                           		   : 4,	// 27:30 reserved
			osd_hdr_color_key_en   : 1;	//    31

			UINT32					   // OSD[0:3]_HDR1
			osd_hdr_h_mem         :12, //  0:11
           			              : 4, // 12:15 reserved
			osd_hdr_w_mem         :12; // 16:27

			UINT32					   // OSD[0:3]_HDR2
			osd_hdr_h_out         :12, //  0:11
		                          : 4, // 12:15 reserved
			osd_hdr_w_out         :12, // 16:27
                                  : 3, // 28:30 reserved
			osd_hdr_pixel_order   : 1; //    31
		}
		osd;

		struct
		{
			UINT32
			osd_hdr_ypos           :12,    //  0:11
                                   : 4,    // 12:15 reserved
			osd_hdr_xpos           :11,    // 16:26
                                   : 4,    // 27:30 reserved
			osd_hdr_pos_load       : 1;    //    31

			UINT32
			osd_hdr_h_mem          :12,    //  0:11
                                   : 3,    // 12:14 reserved
			osd_hdr_pixel_order    : 1,    //    15
			osd_hdr_w_mem          :12,    // 16:27
                                   : 3,    // 28:30 reserved
			osd_hdr_color_key_en   : 1;    //    31

			UINT32
			_rsvd0                 ;
		}
		crsr;
	}
	type;

    UINT32								// OSD[0:3]_HDR3
    osd_hdr_wpl                    :16, //  0:15
    osd_hdr_global_alpha           : 8, // 16:23
    osd_hdr_format                 : 4, // 24:27
    osd_hdr_depth                  : 3, // 28:30
    osd_hdr_global_alpha_en        : 1; //    31

    UINT32								// OSD[0:3]_HDR4
    osd_hdr_color_key              ;    // 31: 0

	UINT32
	_rsvd						   ;

    UINT32								// OSD[0:3]_HDR5
    osd_hdr_ptr_plte               ;    // 31: 0

    UINT32								// OSD[0:3]_HDR6
    osd_hdr_ptr_bmp                ;	// 31: 0
}
FBDEV_L9_OSD_HDR_T;


typedef enum
{
	FBDEV_L9_HW_GPU_CLK_320MHZ	= 0,	/* default */
	FBDEV_L9_HW_GPU_CLK_400MHZ	= 1,	/* optimal */
	FBDEV_L9_HW_GPU_CLK_528MHZ	= 2,	/* overclock */
}
FBDEV_L9_HW_GPU_CLK_T;

typedef	enum
{
	FBDEV_L9_HW_CAPS_TRID_CTRL,		/* check if current HW can support 3D OSD control */
}
FBDEV_L9_HW_CAPS_T;

typedef struct
{
	void 	(*L9_InitHWCtx)		(void);
	void	(*L9_SetGPUClk)		(FBDEV_L9_HW_GPU_CLK_T clk);
	int 	(*L9_SetConnCtrl)	(LX_FBDEV_CONN_CTRL_T*);
	int 	(*L9_WriteOSDHeader)(struct scanvas*);
    int		(*L9_SetOSDEnable)	(int,int);
    int		(*L9_GetOSDEnable)	(int);
	void	(*L9_ISRTickHandler)(void);
	int 	(*L9_SetTridCtrl)   (int, LX_FBDEV_TRID_CTRL_T* );
	BOOLEAN (*L9_CheckCaps)		(FBDEV_L9_HW_CAPS_T,UINT32);
}
FBDEV_L9_HW_FUNC_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	FBDEV_L9_HW_FUNC_T	g_fbdev_l9_hw_func;

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FBDEV_HW_L9_H_ */

/** @} */
