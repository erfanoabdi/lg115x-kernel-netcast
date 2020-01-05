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



/** @file fmt3d_kapi.h
 *
 *  application interface header for fmt3d device
 *
 *  @author		dongho7.park (dongho7.park@lge.com)
 *  @version		0.6a
 *  @date		2010.01.06
 *
 *  @addtogroup lg1150_fmt3d
 *	@{
 */

#ifndef	_FMT3D_KAPI_H_
#define	_FMT3D_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifndef USE_XTENSA
#include "base_types.h"
#endif

#include "de_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	FMT3D_IOC_MAGIC		'a'
/**
@name FMT3D IOCTL List
ioctl list for fmt3d device.

@{
@def FMT3D_IO_INIT
initialize 3D formatter module.
set default register values.

@def FMT3D_IOW_SET_CONVERGENCE
set 3D formatter convergence

@def FMT3D_IOW_SET_DEPTH_CTRL
set 2D to 3D depth control value.

@def FMT3D_IOW_SET_FPR_FHD
set FPR FHD type on off

@def FMT3D_IOW_SET_INOUT_CTRL
set 3D IN/OUT control value.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/

// initialize
#define FMT3D_IO_INIT						_IO(FMT3D_IOC_MAGIC, 0 )

#define FMT3D_IOW_SET_CONVERGENCE      		_IOW(FMT3D_IOC_MAGIC, 1, LX_3D_CONVERGENCE_CTRL_T )
#define FMT3D_IOW_SET_DEPTH_CTRL   			_IOW(FMT3D_IOC_MAGIC, 2, UINT16 )
#define FMT3D_IOW_SET_FPR_FHD   			_IOW(FMT3D_IOC_MAGIC, 3, LX_3D_FPR_FHD_MODE_T )
#define FMT3D_IOW_SET_INOUT_CTRL   			_IOW(FMT3D_IOC_MAGIC, 4, LX_3D_INOUT_CTRL_T )

#define FMT3D_IOC_MAXNR				10
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * 3D formatter convergence control type.
 */
typedef struct {
	UINT16		conv_val;		///< convergence value
	UINT16		edge_val;		///< black edge bar value
}
LX_3D_CONVERGENCE_CTRL_T;

/**
 * 3D formatter FPR FHD type.
 */
typedef enum {
	LX_3D_FPR_FHD_OFF = 0,			///< normal PG mode
	LX_3D_FPR_FHD_ON				///< FPR FHD mode
}
LX_3D_FPR_FHD_MODE_T;

/**
 * 3D formatter running mode parameter.
 * select 3D formatter operation mode. it controls 3D mode ON/OFF.
 */
typedef enum
{
	LX_3D_RUNMODE_OFF = 0,	///< 2D mode, 3D off(bypass)
	LX_3D_RUNMODE_ON,		///< 3D mode, 3D on
	LX_3D_RUNMODE_3DTO2D,	///< 3D input 2D output
	LX_3D_RUNMODE_MAX		///< max number
}
LX_3D_RUNMODE_T;

/**
 * 3D formatter image format parameter.
 * used for input image format and output image format.
 */
typedef enum {
	LX_3D_IMG_IN_TOPNBOTTOM = 0,		///< top and bottom
	LX_3D_IMG_IN_SIDEBYSIDE,			///< side by side
	LX_3D_IMG_IN_QUINCUNX,				///< quincunx
	LX_3D_IMG_IN_CHECKERBOARD,			///< check board
	LX_3D_IMG_IN_FRAMEPACKING,			///< frame packing
	LX_3D_IMG_IN_FRAMEINTERLACE,		///< frame packing interlace
	LX_3D_IMG_IN_FIELDALTERNATE,		///< field alternate
	LX_3D_IMG_IN_FRAMESEQ,				///< frame sequence
	LX_3D_IMG_IN_LINEALTERNATIVE,		///< line alternative full
	LX_3D_IMG_IN_SIDEBYSIDE_FULL,		///< side by side full
	LX_3D_IMG_IN_DUAL_HD,				///< dual HD e.g.) One is mpeg-2 ts, the other is mpeg-4 ts scenario
	LX_3D_IMG_IN_COLUMNALTERNATIVE,		///< column alternate(interleaving) - mpeg
	LX_3D_IMG_IN_LINEALTERNATIVE_HALF,	///< line alternative half
	LX_3D_IMG_IN_MAX					///< max number
}
LX_3D_IMG_FMT_IN_T;

/**
 * 3D formatter image format parameter.
 * used for input image format and output image format.
 */
typedef enum {
	LX_3D_IMG_OUT_SINGLE_2D    = 0,		///< single nomal
	LX_3D_IMG_OUT_SINGLE_TB,			///< top and bottom
	LX_3D_IMG_OUT_SINGLE_SS,			///< side by side
	LX_3D_IMG_OUT_SINGLE_FS,			///< Frame Sequential(Interleaving)
	LX_3D_IMG_OUT_DUAL_FULL,			///< dual screen
	LX_3D_IMG_OUT_MAX					///< max number
}
LX_3D_IMG_FMT_OUT_T;

/**
 * 3D formatter Left Roght order parameter.
 * used for input image and output image.
 */
typedef enum
{
	LX_3D_LR_ORDER_R_FIRST = 0,		///< right first
	LX_3D_LR_ORDER_L_FIRST,			///< left first
	LX_3D_LR_ORDER_MAX				///< max number
}
LX_3D_LR_ORDER_T;

/**
 * 3D formatter input/output control type.
 *  0xFF   : invalid
 *  Others :   valid
 */
typedef struct {
	LX_3D_RUNMODE_T		run_mode;			///< select formatter operation mode. it controls 3D mode ON/OFF.
	LX_3D_IMG_FMT_IN_T		in_img_fmt;			///< input image format(top/bottom, sidebyside, checkboard, frame, field seq, dual 2d)
	LX_3D_LR_ORDER_T 		in_lr_order;		///< input left/right first order
	LX_3D_IMG_FMT_OUT_T 	out_img_fmt;		///< output image format(top/bottom, sidebyside, checkboard, frame, field seq)
	LX_3D_LR_ORDER_T  	out_lr_order;		///< output left/right first order
}
LX_3D_INOUT_CTRL_T;

/**
 * pre 3D block source mux parameter.
 * select source from external or memory.
 */
typedef enum {
	LX_3D_EXT_IN = 0,		///< from external
	LX_3D_MEM_IN			///< from memory
}
LX_3D_SRC_MUX_TYPE_T;

/**
 * 3D formatter block convergence parameter.
 * adjust 3D effect.
 */
typedef enum {
	LX_3D_VARIABLE_WIDTH_BLACK_BAR = 0,	///< variable width mode
	LX_3D_FIXED_WIDTH_BLACK_BAR			///< fixed width mode
}
LX_3D_CONVERGENCE_MODE_T;

/**
 * 3D formatter image format parameter.
 * used for input image format and output image format.
 */
typedef enum {
	LX_3D_IMG_TOPNBOTTOM = 0,	///< top and bottom
	LX_3D_IMG_SIDEBYSIDE,		///< side by side
	LX_3D_IMG_CHECKERBOARD,		///< check board
	LX_3D_IMG_FRAMESEQ,			///< frame sequence
	LX_3D_IMG_FIELDSEQ,			///< field sequence
	LX_3D_IMG_MAX				///< max number
}
LX_3D_IMG_FMT_T;

/**
 * 3D formatter image size parameter.
 * used for input image size and output image size.
 */
typedef struct {
	UINT16  w;		///< image width
	UINT16  h;		///< image height
}
LX_3D_IMG_SIZE_T;

/**
 * 3D formatter image sampling mode parameter.
 * used for input image sub-sampling.
 */
typedef enum {
	LX_3D_MODE_QUINCUNX = 0,	///< quincunx sampling mode
	LX_3D_MODE_LINE_BY_LINE,	///< line by line quincunx sampling mode
	LX_3D_MODE_MAX				///< max number
}
LX_3D_SAMPLE_MODE_T;

/**
 * 3D formatter image sub sampling combination parameter.
 * used for input image sub-sampling.
 */
typedef enum {
	LX_3D_COMB_LORO = 0,	///< left odd, right odd
	LX_3D_COMB_LORE,		///< left odd, right even
	LX_3D_COMB_LERO,		///< left even, right odd
	LX_3D_COMB_LERE,		///< left even, right even
	LX_3D_COMB_MAX			///< max number
}
LX_3D_SAMPLE_COMBI_T;

/**
 * 3D formatter image bit resolution parameter.
 * used for input image setting.
 */
typedef enum {
	LX_3D_IMG_8BIT = 0,		///< 8bit resolution
	LX_3D_IMG_10BIT			///< 10bit resolution
}
LX_3D_IMG_BIT_RES_T;

/**
 * 3D formatter image scan method parameter.
 * used for input image setting.
 */
typedef enum {
	LX_3D_IMG_INTERLACE = 0,	///< interlaced scan
	LX_3D_IMG_PROGRASSIVE		///< prograssive scan
}
LX_3D_IMG_SCAN_TYPE_T;

/**
 * 3D formatter image color format parameter.
 * used for input image setting.
 */
typedef enum {
	LX_3D_IMG_YUV420 = 0,		///< YUV 4:2:0
	LX_3D_IMG_YUV422,			///< YUV 4:2:2
	LX_3D_IMG_YUV444			///< YUV 4:4:4
}
LX_3D_IMG_COLOR_FMT_T;

/**
 * 3D formatter image double picture parameter.
 * used for input image setting.
 */
typedef enum {
	LX_3D_IMG_ONE_FRAME_PER_VSYNC = 0,	///< one frame or field per vsync
	LX_3D_IMG_TWO_FRAME_PER_VSYNC		///< two frames or fields per vsync
}
LX_3D_IMG_DOUBLE_PIC_T;

/**
 * 3D formatter image input frequency parameter.
 */
typedef enum {
	LX_3D_IMG_FREQ_60HZ = 0,		///< under 60Hz
	LX_3D_IMG_FREQ_120HZ			///< 120Hz
}
LX_3D_IMG_FREQ_T;
/**
 * 3D formatter display format parameter.
 * used for output setting according to panel attribute.
 */
typedef enum
{
	LX_3D_DIS_FMT_LINEINTER = 0,	///< line interleaved
	LX_3D_DIS_FMT_FRAMESEQ,			///< frame sequential
	LX_3D_DIS_FMT_MAX				///< max number
}
LX_3D_DIS_FMT_TYPE_T;

/**
 * 3D formatter display format parameter for FRC .
 * used for output setting according to panel attribute.
 */
typedef enum
{
	LX_3D_OUT_OFF = 0,
	LX_3D_OUT_LINEINTERLEAVED,
	LX_3D_OUT_FRAMESEQ,
	LX_3D_OUT_DUAL
}
LX_3D_OUT_TYPE_T;

/**
 * 3D formatter display frequency parameter.
 */
typedef enum {
	LX_3D_DIS_FREQ_120HZ = 0,		///< 120Hz
	LX_3D_DIS_FREQ_240HZ			///< 240Hz ( L8 support or not ?)
}
LX_3D_DIS_FREQ_T;

/**
 * 3D formatter frame flip parameter.
 * used when spatial_flip is '1'(ON) and T/B or S/S formats
 */
typedef enum {
	LX_3D_BR_FRAME_FLIP = 0,		///< bottom/right frame flip
	LX_3D_TL_FRAME_FLIP				///< top/left frame flip
}
LX_3D_TL_FRAME_FLIP_T;

/**
 * 3D formatter input config type.
 */
typedef struct {
	LX_3D_IMG_FMT_T 		in_img_fmt;			///< input image format(top/bottom, sidebyside, checkboard, frame, field seq)
	LX_3D_IMG_SIZE_T 		in_img_size;		///< input image width/height  ; ucom
	UINT16 					crop_offset;		///< horizontal crop offset
	LX_3D_SAMPLE_MODE_T 	sample_mode;		///< input sub sampling mode(quincunx, linebyline)
	LX_3D_SAMPLE_COMBI_T 	sample_comb;		///< input sub sampling combination(left/right, odd/even)
	BOOLEAN					spatial_flip;		///< spatial flip when T/B or S/S formats
	LX_3D_TL_FRAME_FLIP_T	is_tl_flip;			///< bottom right/ top left frame flip
	LX_3D_LR_ORDER_T 		in_lr_order;		///< input left/right first order
	LX_3D_IMG_BIT_RES_T 	bit_res;			///< input stream bit resolution(8 or 10bit)
	LX_3D_IMG_SCAN_TYPE_T 	is_prog;			///< input scan type(interlace or prograssive)
	LX_3D_IMG_COLOR_FMT_T  	color_fmt;			///< input color sampling format
	LX_3D_IMG_FREQ_T 		input_fr;			///< input frame rate (<60Hz or120Hz)
	LX_3D_IMG_DOUBLE_PIC_T  is_dbl_pic;			///< double picture mode or not
}
LX_3D_IN_CONFIG_T;

/**
 * 3D formatter processing mode type.
 */

typedef struct {
	LX_3D_SRC_MUX_TYPE_T		src_mux;			///< select source from external(0) or memory(1)
	LX_3D_RUNMODE_T				run_mode;			///< select formatter operation mode. it controls 3D mode ON/OFF.
	LX_3D_DIS_FMT_TYPE_T 		dis_fmt;			///< display format -- line interleaved(0) or frame sequential(1)
	LX_3D_DIS_FREQ_T			dis_freq;			///< display frequency 120Hz(0) 240Hz(1)
	LX_3D_LR_ORDER_T  			out_lr_order;		///< output left/right first order
	LX_3D_CONVERGENCE_MODE_T 	cvg_mode;			///< variable width mode(0) fixed width mode(1)
	UINT16						cvg_value;			///< convergence value, two's complement
	UINT16						cvg_min;			///< convergence minimum value, two's complement 0x100(-256)
	UINT16						cvg_max;			///< convergence maximum value, two's complement 0x0FF(256)
}
LX_3D_PROCESS_MODE_T;

/**
 * 3D formatter output config type.
 */
typedef struct {
	LX_3D_IMG_FMT_T 		out_img_fmt;		///< output image format(top/bottom, sidebyside, checkboard, frame, field seq)
	LX_3D_IMG_SIZE_T 		out_img_size;		///< output image width/height
}
LX_3D_OUT_IMG_INFO_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _FMT3D_DRV_H_ */

/** @} */
