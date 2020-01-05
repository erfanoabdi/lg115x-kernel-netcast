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



/** @file png_kapi.h
 *
 *  application interface header for png device
 *
 *  @author		raxis.lim (raxis.lim@lge.com)
 *  @version		1.0 
 *  @date		2010.10.05
 *
 *  @addtogroup lg_png 
 *	@{
 */

#ifndef	_PNG_KAPI_H_
#define	_PNG_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	PNG_IOC_MAGIC		'p'
/**
@name PNG IOCTL List
ioctl list for png device.

@{
@def PNG_IO_RESET
Reset png module.
When png device receives above IOCTL, then reset itself.

@def PNG_IOR_CHIP_REV_INFO
Reads chip revision information.
Just get chiop revision information. To support automatic changing behavior of device driver or middleware by this ioctl.

@def PNG_IOW_WRITE_UINT32
write 32bit value to png module.
detailed...[minimum two lines of comment required. one line of comment does not generated automatically]

@def PNG_IOW_WRITE_STRUCT		
control complex parameter to png module.
control codec_type, speed, and additional parameter.
no need to use "see also", exact struct name shall be linked automatically.

*/

/*
	------------------------------------------------------
	          bit per pixel	       |   Bits per channel
	------------------------------------------------------
	    Color option   |  Channels |   1   2   4   8   16
	------------------------------------------------------
	Indexed            |     1     |   1   2   4   8   X
	Grayscale          |     1     |   1   2   4   8   16
	Grayscale & alpha  |     2     |   X   X   X   16  32
	Truecolor          |     3     |   X   X   X   24  48
	Truecolor & alpha  |     4     |   X   X   X   32  64
*/


/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define PNG_IOR_GET_CAPS			_IOR(PNG_IOC_MAGIC, 0, LX_PNG_DECODE_CAPS_T )
#define PNG_IOR_GET_MEM_STAT		_IOR(PNG_IOC_MAGIC, 1, LX_PNG_MEM_STAT_T )
#define	PNG_IOR_GET_BUFFER_SIZE		_IOR(PNG_IOC_MAGIC, 2, UINT32 )	
#define	PNG_IOR_GET_HW_STATE		_IOW(PNG_IOC_MAGIC, 3, LX_PNG_STATE_T )
#define PNG_IO_RESET				_IO(PNG_IOC_MAGIC, 	4)
#define	PNG_IOW_DECODE_IDAT			_IOW(PNG_IOC_MAGIC, 5, LX_PNG_DECODE_PARAM_T )

#define PNG_IOC_MAXNR				6
/** @} */

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	LX_PNG_OP_NONE		= 0x00,
	LX_PNG_OP_FULL		= 0x01,
	LX_PNG_OP_PARTIAL	= 0x02,
}
LX_PNG_OP_T;

#define LX_PNG_CAPS_COLOR_TYPE(x)	(1 << x)

typedef enum
{
	LX_PNG_COLOR_GRAYSCALE					= 0,
	LX_PNG_COLOR_INDEXED_GRAYSCALE			= 1,
	LX_PNG_COLOR_TRUECOLOR					= 2,
	LX_PNG_COLOR_INDEXED					= 3,
	LX_PNG_COLOR_GRAYSCALE_ALPHA			= 4,
	LX_PNG_COLOR_INDEXED_GRAYSCALE_ALPHA	= 5,
	LX_PNG_COLOR_TRUECOLOR_ALPHA			= 6,
	LX_PNG_COLOR_INDEXED_ALPHA				= 7,
}
LX_PNG_COLOR_TYPE_T;

typedef enum
{
	LX_PNG_INTERLACING_DISABLED = 0x00,
	LX_PNG_INTERLACING_ENABLED	= 0x01,
	LX_PNG_INTERLACING_DONTCARE	= 0x02,
}
LX_PNG_INTELACING_T;

typedef enum
{
	LX_PNG_COMPRESSION_DISABLED = 0x00,
	LX_PNG_COMPRESSION_ENABLED	= 0x01,
	LX_PNG_COMPRESSION_DONTCARE	= 0x02,
}
LX_PNG_COMPRESSION_T;

typedef enum
{
	LX_PNG_FILTER_DISABLED	= 0x00,
	LX_PNG_FILTER_ENABLED	= 0x01,
}
LX_PNG_FILTER_T;

typedef struct
{
	LX_PNG_OP_T				possible_op;
	UINT32					color_type;
	LX_PNG_INTELACING_T		interlacing;
    UINT32  				min_width;
    UINT32  				min_height;
    UINT32  				max_width;
    UINT32  				max_height;
}
LX_PNG_DECODE_CAPS_T;

/** PNG cfg for application interface
 *
 *	raxis.lim (2012/05/09)
 *	- I want to remove LX_PNG_DECODE_CAPS_T !!!!
 */
typedef struct
{
    UINT16          min_decode_stride;          /** minimum decodable stride */
    UINT16          max_decode_stride;          /** maximum decodable stride */

	UINT32			supported_color_type;		/** @see LX_PNG_COLOR_TYPE_T, LX_PNG_CAPS_COLOR_TYPE */

#define LX_PNG_DECODE_CAPS_NONE                 0x00000000  /** none */
#define LX_PNG_DECODE_CAPS_PARTIAL_DECODE       0x00000001  /** if partial decode supported */
#define LX_PNG_DECODE_CAPS_INTERLACED_IMAGE     0x00000002  /** if interlaced png can be decoded ? */
    UINT32          decode_caps;

    UINT32          rsvd[5];
}
LX_PNG_CFG_T;

/** PNG memory layout 
 *
 *	PNG device supports its own memory space to be used as read buffer of decoder.
 *	application may use this address or use its own address.
 *	
 *	all region of PNG memory is used as read buffer. 
 *	application can partition memory region as it wants but do it carefully.
 *
 */
typedef struct
{
	UINT32			src_buf_addr;			/** physical address for image buffer supported by PNG device */
	UINT32			src_buf_size;			/** buf length for image buffer supported by PNG device */
}
LX_PNG_MEM_STAT_T;

typedef enum
{
    LX_PNG_STATE_CLOSED,
    LX_PNG_STATE_SUSPENDED,
    LX_PNG_STATE_IDLE,
    LX_PNG_STATE_DECODING,
    LX_PNG_STATE_ERROR,
} 
LX_PNG_STATE_T;

/** PNG image header information
 *	this struct has the same structure as the one described in png spec document
 */
typedef struct
{
    UINT32  width;
    UINT32  height;
    UINT8   bit_depth;
	UINT8	color_type;
    UINT8   compression_method;
    UINT8   filter_method;
    
    UINT8   interlace_method;
	UINT8   rsvd[3];
}
LX_PNG_HDR_T;

/** PNG decoder parameter 
 *
 */
typedef struct
{
	LX_MEM_BUF_T		in_buf;				/** read buffer to hold image data. in_buf is not used. */
	LX_MEM_BUF_T		out_buf;			/** output buffer to hold decoded data */

	UINT32				offset;				/** offset value in mmap data of png image buffer based on in_buf*/
	UINT32				length;				/** length written in application based on in_buf */

	UINT32				img_sz;				/** rough image size  */
	UINT32				max_decoding_time;	/** max decoding time which app can tolerate */	
	LX_PNG_OP_T			op_method;			/** decoding op method */
	LX_PNG_HDR_T		img_hdr;			/** png header information */

	UINT32				rsvd[4];
}
LX_PNG_DECODE_PARAM_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PNG_DRV_H_ */

/** @} */
