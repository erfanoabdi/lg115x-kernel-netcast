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
 *  application interface header for vdec device
 *
 *  author		seokjoo.lee (seokjoo.lee@lge.com)
 *  version		0.75
 *  date		2010.07.26
 *
 *  @addtogroup lg1150_vdec
 * @{
 */

#ifndef	_VDEC_KAPI_H_
#define	_VDEC_KAPI_H_

//#define LX_VDEC_FP_DTS_MATCHED	1
#undef	VDEC_REDUCE_FLUSH		// 20110318 DVR-VDEC PAUSE¡Æu¡¤A Tuning
//#define VDEC_IO_RATE_DELETED

#include "base_types.h"


#define	LX_VDEC_IOC_MAGIC		'v'

/** maximum video decoder context */
#define	LX_VDEC_CH_MAXN			8


typedef enum
{
	LX_VDEC_DBGCMD_MOD_TOP = 0,
	LX_VDEC_DBGCMD_MOD_PDEC,
	LX_VDEC_DBGCMD_MOD_FEED,
	LX_VDEC_DBGCMD_MOD_MSVC,
	LX_VDEC_DBGCMD_MOD_SYNC,
	LX_VDEC_DBGCMD_MOD_MIN = LX_VDEC_DBGCMD_MOD_TOP,
	LX_VDEC_DBGCMD_MOD_MAX = LX_VDEC_DBGCMD_MOD_SYNC,
	LX_VDEC_DBGCMD_MOD_MAXN = (LX_VDEC_DBGCMD_MOD_MAX+1),
} LX_VDEC_DBGCMD_MOD_T __attribute__((deprecated));

typedef enum
{
	LX_VDEC_DBGCMD_RESET = 0,
	LX_VDEC_DBGCMD_MCU_RESET,
	LX_VDEC_DBGCMD_TOP_MIN = LX_VDEC_DBGCMD_RESET,
	LX_VDEC_DBGCMD_TOP_MAX = LX_VDEC_DBGCMD_MCU_RESET,
	LX_VDEC_DBGCMD_TOP_MAXN = (LX_VDEC_DBGCMD_TOP_MAX+1),
} LX_VDEC_DBGCMD_TOP_TYPE_T __attribute__((deprecated));

typedef enum
{
	LX_VDEC_DBGCMD_SYNC_DISPLAY_OFFSET = 0,
	LX_VDEC_DBGCMD_SYNC_1,
	LX_VDEC_DBGCMD_SYNC_MIN = LX_VDEC_DBGCMD_SYNC_DISPLAY_OFFSET,
	LX_VDEC_DBGCMD_SYNC_MAX = LX_VDEC_DBGCMD_SYNC_1,
	LX_VDEC_DBGCMD_SYNC_MAXN = (LX_VDEC_DBGCMD_SYNC_MAX+1),
} LX_VDEC_DBGCMD_SYNC_TYPE_T __attribute__((deprecated));

/**
 * Video Codec Type.
 * decoding formats supported by the Video decoder.
 */
typedef enum
{
	LX_VDEC_CODEC_H264_HP,
	LX_VDEC_CODEC_H264_MVC,
	LX_VDEC_CODEC_VC1_RCV_V1,
	LX_VDEC_CODEC_VC1_RCV_V2,
	LX_VDEC_CODEC_VC1_ES,
	LX_VDEC_CODEC_MPEG2_HP,
	LX_VDEC_CODEC_MPEG4_ASP,
	LX_VDEC_CODEC_XVID,
	LX_VDEC_CODEC_DIVX3,
	LX_VDEC_CODEC_DIVX4,
	LX_VDEC_CODEC_DIVX5,
	LX_VDEC_CODEC_RVX,
	LX_VDEC_CODEC_AVS,
	LX_VDEC_CODEC_VP8,
	LX_VDEC_CODEC_THEORA,

	LX_VDEC_CODEC_MIN = LX_VDEC_CODEC_H264_HP,
	LX_VDEC_CODEC_MAX = LX_VDEC_CODEC_THEORA,
	LX_VDEC_CODEC_INVALID
} LX_VDEC_CODEC_T;

typedef enum
{
	LX_VCODEC_H264_HP = 0,
	xLX_VCODEC_H264_MVCx,
	LX_VCODEC_VC1_RCV_V1,
	LX_VCODEC_VC1_RCV_V2,
	LX_VCODEC_VC1_ES,
	LX_VCODEC_MPEG2_HP,
	LX_VCODEC_MPEG4_ASP,
	LX_VCODEC_XVID,
	LX_VCODEC_DIVX3,
	LX_VCODEC_DIVX4,
	LX_VCODEC_DIVX5,
	LX_VCODEC_RVX,
	LX_VCODEC_AVS,
	LX_VCODEC_VP8,
	LX_VCODEC_SW,

	LX_VCODEC_MIN = LX_VCODEC_H264_HP,
	LX_VCODEC_MAX = LX_VCODEC_SW,
	LX_VCODEC_INVALID
} LX_VCODEC_T __attribute__((deprecated));	// use LX_VDEC_CODEC_T

/**
 * @var LX_VDEC_SRC_SDEC0
 * Video decoder input can be selected from system decoder 0.
 * 
 * @var LX_VDEC_SRC_SDEC1
 * Video decoder input can be selected from system decoder 1.
 * 
 * @var LX_VDEC_SRC_BUFF
 * Video decoder input is manually controlled by caller.
 */
typedef enum
{
	LX_VDEC_SRC_SDEC0,		// Video decoder input can be selected from system decoder 0.
	LX_VDEC_SRC_SDEC1,		// Video decoder input can be selected from system decoder 1.
	LX_VDEC_SRC_SDEC2,		// Video decoder input can be selected from system decoder 1.
	LX_VDEC_SRC_BUFF,		// Video decoder input is manually controlled by caller.
	xLX_VDEC_SRC_BUFFx,		// Video decoder input is manually controlled by caller.
	LX_VDEC_SRC_BUFFTVP,		// Video decoder input is manually controlled by caller.
	LX_VDEC_SRC_MIN		= LX_VDEC_SRC_SDEC0,
	LX_VDEC_SRC_MAX		= LX_VDEC_SRC_BUFFTVP,
	LX_VDEC_SRC_MAXN	= (LX_VDEC_SRC_MAX+1),
} LX_VDEC_SRC_T;

static const LX_VDEC_SRC_T LX_VDEC_SRC_BUFF0 __attribute__((deprecated));
static const LX_VDEC_SRC_T LX_VDEC_SRC_BUFF1 __attribute__((deprecated));

static const LX_VDEC_SRC_T LX_VDEC_SRC_BUFF0 = LX_VDEC_SRC_BUFF;
static const LX_VDEC_SRC_T LX_VDEC_SRC_BUFF1 = xLX_VDEC_SRC_BUFFx;

/**
 * @var LX_VDEC_DST_DE0
 * Video decoder output shall be directed to Main Window of DE(Display Engine)
 */

/**
 * @var LX_VDEC_DST_DE1
 * Video decoder output shall be directed to Sub Window of DE(Display Engine)
 */

/**
 * @var LX_VDEC_DST_BUFF
 * Video decoder output shall be remains to DPB (Decoded Picture Buffer), not
 * automatically passed to DE.
 */
typedef enum
{
	LX_VDEC_DST_DE0		= 0,	// Video decoder output shall be directed to Main Window of DE(Display Engine)
	LX_VDEC_DST_DE1		= 1,	// Video decoder output shall be directed to Sub Window of DE(Display Engine)
	LX_VDEC_DST_BUFF	= 2,	// Video decoder output shall be remains to DPB (Decoded Picture Buffer),
												// not automatically passed to DE.  use this for thumbnail output.
	LX_VDEC_DST_MIN		= LX_VDEC_DST_DE0,
	LX_VDEC_DST_MAX		= LX_VDEC_DST_BUFF,
	LX_VDEC_DST_MAXN	= (LX_VDEC_DST_MAX+1),
} LX_VDEC_DST_T;


/**
 * @var LX_VDEC_OPMOD_NORMAL
 * Video decoder will be operated on the broadcast/DVR/file play configuration
*/

/**
 * @var LX_VDEC_OPMOD_VCS
 * Video decoder will be operated on the VCS configuration
*/

/**
 * @var LX_VDEC_OPMOD_ONE_FRAME
 * Video decoder will be operated on the channel browser , thumbnail and drip decoding configuration
*/
typedef enum
{
	LX_VDEC_OPMOD_NORMAL = 0,
	LX_VDEC_OPMOD_VCS,
	LX_VDEC_OPMOD_ONE_FRAME,
	LX_VDEC_OPMOD_DUAL,
	LX_VDEC_OPMOD_LOW_LATENCY,
	LX_VDEC_OPMOD_MIN = LX_VDEC_OPMOD_NORMAL,
	LX_VDEC_OPMOD_MAX = LX_VDEC_OPMOD_LOW_LATENCY,
	LX_VDEC_OPMOD_MAXN = (LX_VDEC_OPMOD_MAX+1),
} LX_VDEC_OPMODE_T;

/**
@name VDEC IOCTL List
ioctl list for vdec device.

@{
@def LX_VDEC_IO_OPEN_CH
Initialize vdec channel with codec/data type
VDEC module shall initialize itself with pre-defined configuration.
@li register device, interrupts, buffer memory.

@param LX_VDEC_IO_OPEN_CH* [IN] per-channel initialization parameter.

@def LX_VDEC_IO_CLOSE_CH
closes given VDEC Channel.
reduce CPU burden when given channel shall not be used by closing vdec channel.
TBD: what to do if decoding is not completed or given channel is not responding
@param UINT8	[IN] channel id to close. must be "0<= param < LX_VDEC_CH_MAXN"

@def LX_VDEC_IO_RESET
Reset/Flush vdec module for all channel or per-channel.
When vdec device receives above IOCTL, then reset itself.

@param UITN32	[IN]	one of @ref ESoftReset

@def LX_VDEC_IO_SET_BUFFER_LVL
sets buffer overflow/underflow level.

@param LX_VDEC_IO_BUFFER_LVL_T* [IN]

@def LX_VDEC_IO_GET_BUFFER_LVL
reads buffer almost overflow(aFull)/underflow(aEmpty) level(in bytes).

@param LX_VDEC_IO_BUFFER_LVL_T* [IN] aFull

@def LX_VDEC_IO_PLAY
Starts Decoding with given VDEC CH.
with ioctl paramter, @ref LX_VDEC_IO_PLAY_T.
When Start decoding, initially Lip Sync mode shall be Off.
@param LX_VDEC_IO_PLAY* [IN] see typical value below.

Usual LX_VDEC_IO_PLAY_T value.

for normal transport stream case.
- @ref LX_VDEC_IO_PLAY_T.syncOn = 1 (automatically Lip Sync On after first valid PTS/DTS found.)
- @ref LX_VDEC_IO_PLAY_T.picScanMode = LX_VDEC_PIC_SCAN_MSK_ALL
- @ref LX_VDEC_IO_PLAY_T.step = 0
- @ref LX_VDEC_IO_PLAY_T.userDataEn = 1
- @ref LX_VDEC_IO_PLAY_T.resetStatus shall be: \n
	1 : reset saved information) when channel/source change.\n
	0 : when error recovery if required. within same channel.

for File play or streaming play mode.
[NOTE] File play shall use GSTC for lipsync.
- @ref LX_VDEC_IO_PLAY_T.syncOn = 0
- @ref LX_VDEC_IO_PLAY_T.picScanMode = LX_VDEC_PIC_SCAN_MSK_ALL
- @ref LX_VDEC_IO_PLAY_T.step = 0
- @ref LX_VDEC_IO_PLAY_T.userDataEn = 1 or 0
- @ref LX_VDEC_IO_PLAY_T.resetStatus shall be: \n
	1 : reset saved information) when channel/source change.\n
	0 : when error recovery if required or pause/resume case.

for JPEG or MPEG I Frame decoding.
- @ref LX_VDEC_IO_PLAY_T.syncOn = 0
- @ref LX_VDEC_IO_PLAY_T.picScanMode = LX_VDEC_PIC_SCAN_MSK_I
- @ref LX_VDEC_IO_PLAY_T.step = 1
- @ref LX_VDEC_IO_PLAY_T.userDataEn = 1 or 0
- @ref LX_VDEC_IO_PLAY_T.resetStatus = 1

@def LX_VDEC_IO_STOP
Stops Decoding with given VDEC CH.
@param UINT32 channel to stop.
this will cause all operation of VDEC stopped for given channel.
TODO : what is difference between Stop & pause
TODO : what is difference between SET_SPEED(0)

@def LX_VDEC_IO_RATE	OBSOLETE 20110416 seokjoo.lee moved LX_VDEC_IO_PLAY_T
Set/Get Decoding Rate to nominal rate.

Stops Decoding with given VDEC CH.
@param LX_VDEC_IO_RATE_T
this will cause all operation of VDEC stopped for given channel.
TODO : what is difference between Stop & pause
TODO : what is difference between SET_SPEED(0)

@def LX_VDEC_IO_SET_LIP_SYNC
enable/disable Lip sync mode.
controls lip sync mode of given VDEC Channel.
only allowed for channel 0 and 1.
@param UINT32	[IN] 0 for free run, 1 for synchronized(PTS check).

@def LX_VDEC_IO_GET_LIP_SYNC
get current enable/disable state of Lip sync mode.
controls lip sync mode of given VDEC Channel.
only allowed for channel 0 and 1.

@def LX_VDEC_IO_UPDATE_BUFFER
trigers VDEC input buffer read pointer to be updated.
shall be used only when buffered/file play  mode.
when Updating Video Input buffer, some decoding micro command SHOULD Be attached.
[NOTE] User application SHOULD check command queue availibility via LX_VDEC_IO_GET_BUFFER_LVL,
before calling LX_VDEC_IO_UPDATE_BUFFER with decoding command to command queue.


@def LX_VDEC_IO_SET_FRAME
set number of frames for given channel.
@param UINT32 number of frames.

@def LX_VDEC_IO_GET_OUTPUT
TBD: get decoded output frame information.
TBD: SIC code only, not implemented.\n
- TBD: return value read from register: ch[0~3]_frame_stride,ch[0~3]_frame_width_height \n
- TBD: also used to FILEPLAY_JPEGINFO FILEPLAY_JPEGGETINFO ioctl in Verification source code.

@def LX_VDEC_IO_GET_TIME
returns GSTC (Global STC) value(28bit) which runs monotonic increasing 28 bit unsigned value @ 90KHz.
if negative, some error happened.

@def LX_VDEC_IO_GET_STATUS
Read status of VDEC channel.
control codec_type, speed, and additional parameter.\n
TBD: if a status structure is allocated in kernel driver and mmap'ed to user space,\n
then this IOR ioctl can be implemented as reading member variable from mmap'ed status structure.

@def LX_VDEC_IO_SET_NOTIFY
enable/disable notify events.
such as Sequence header, Picture header, User data, AFD/Bar data.

@def LX_VDEC_IO_GET_NOTIFY
enable/disable notify events.
such as Sequence header, Picture header, User data, AFD/Bar data.

@def LX_VDEC_IO_GET_VERSION
Read version.
version of device driver, firmware version, H/W revision info.
- Kernel level device driver read this information from H/W register when opening device driver and user space application only read this.
- TBD: if status structure is mmap'ed, then simple read version info from mmap'ed address of status structure.

@def LX_VDEC_IO_SET_REG
debugging : write each register.
TBD:

@def LX_VDEC_IO_GET_REG
debugging : read each register.
TBD:

*/
// when opening device driver.
//#define LX_VDEC_IOR_CFG			_IOR(VDEC_IOC_MAGIC, 'Z', CHIP_REV_INFO_T* )
//#define LX_VDEC_IOW_CFG			_IOW(VDEC_IOC_MAGIC, 'Z', CHIP_REV_INFO_T* )

#define LX_VDEC_IO_OPEN_CH			_IOWR(LX_VDEC_IOC_MAGIC,  0, LX_VDEC_IO_OPEN_CH_T)
#define LX_VDEC_IO_CLOSE_CH			_IO(LX_VDEC_IOC_MAGIC,  1)

// decoding control
#define LX_VDEC_IO_PLAY				_IOW(LX_VDEC_IOC_MAGIC,  2, LX_VDEC_IO_PLAY_T)
#define LX_VDEC_IO_PLAY_SET			_IOW(LX_VDEC_IOC_MAGIC,  3, LX_VDEC_IO_PLAY_SET_T)
#define LX_VDEC_IO_PLAY_GET			_IOWR(LX_VDEC_IOC_MAGIC,  4, LX_VDEC_IO_PLAY_GET_T)

#define LX_VDEC_IO_FLUSH			_IO(LX_VDEC_IOC_MAGIC,  5)

#define LX_VDEC_IO_SET_BUFFER_LVL		_IOW(LX_VDEC_IOC_MAGIC,  6, LX_VDEC_IO_BUFFER_LVL_T)
#define LX_VDEC_IO_GET_BUFFER_STATUS		_IOR(LX_VDEC_IOC_MAGIC,  7, LX_VDEC_IO_BUFFER_STATUS_T)

// for buffered/file play only
#define LX_VDEC_IO_UPDATE_BUFFER		_IOW(LX_VDEC_IOC_MAGIC,  8, LX_VDEC_IO_UPDATE_BUFFER_T)

// aux data gathering.
#define LX_VDEC_IO_GET_OUTPUT			_IOR(LX_VDEC_IOC_MAGIC,  9, LX_VDEC_OUTPUT_T)

// misc.
#define LX_VDEC_IO_GET_VERSION			_IOR(LX_VDEC_IOC_MAGIC,  10, LX_VDEC_IO_VERSION_T)

// Frame buffer (DPB)
#define LX_VDEC_IO_UPDATE_FRMBUF		_IOW(LX_VDEC_IOC_MAGIC,  11, LX_VDEC_IO_UPDATE_FRAME_INFO_T)
//#define LX_VDEC_IO_INIT_FRAME_BUFFER		_IOWR(LX_VDEC_IOC_MAGIC,  10, LX_VDEC_IO_INIT_FRAME_BUFFER_T)
//#define LX_VDEC_IO_UPDATE_FRAME_BUFFER	_IOWR(LX_VDEC_IOC_MAGIC,  11, LX_VDEC_IO_UPDATE_FRAME_BUFFER_T)

// debugging.
#define LX_VDEC_IO_SET_REG			_IOW(LX_VDEC_IOC_MAGIC,  12, LX_VDEC_SET_REG_T)
#define LX_VDEC_IO_GET_REG			_IOR(LX_VDEC_IOC_MAGIC,  13, LX_VDEC_GET_REG_T)

#define LX_VDEC_IO_ENABLELOG			_IO(LX_VDEC_IOC_MAGIC,  14)
#define LX_VDEC_IO_DBG_CMD			_IOW(LX_VDEC_IOC_MAGIC,  15, LX_VDEC_DBG_CMD_T)

#define LX_VDEC_IO_GET_MEM_LOG			_IOWR(LX_VDEC_IOC_MAGIC,  16, LX_VDEC_GET_MEM_LOG_T)

#define LX_VDEC_UNREF_DECODEBUFFER		_IOW (LX_VDEC_IOC_MAGIC, 17, unsigned long)
#define LX_VDEC_SET_DECODING_QUEUE_SIZE		_IOW (LX_VDEC_IOC_MAGIC, 18, int)
#define LX_VDEC_GET_DECODED_QUEUE_SIZE		_IOR (LX_VDEC_IOC_MAGIC, 19, int)
#define LX_VDEC_SET_OUTPUT_MEMORY_FORMAT	_IOW (LX_VDEC_IOC_MAGIC, 20, LX_VDEC_MEMORY_FORMAT_T)
#define LX_VDEC_SET_SCAN_PICTURE		_IO  (LX_VDEC_IOC_MAGIC, 21)
#define LX_VDEC_SET_PICTURE_SIZE		_IO  (LX_VDEC_IOC_MAGIC, 22)		// deprecated
#define LX_VDEC_SET_CODEC			_IO  (LX_VDEC_IOC_MAGIC, 23)
#define LX_VDEC_SET_DISPLAY_OFFSET		_IO  (LX_VDEC_IOC_MAGIC, 24)
#define LX_VDEC_SET_INPUT_DEVICE		_IO  (LX_VDEC_IOC_MAGIC, 25)
#define LX_VDEC_SET_OUTPUT_DEVICE		_IO  (LX_VDEC_IOC_MAGIC, 26)
#define LX_VDEC_SET_BASETIME			_IOW (LX_VDEC_IOC_MAGIC, 27, LX_VDEC_BASETIME_T)
#define LX_VDEC_GET_GLOBAL_STC			_IOR (LX_VDEC_IOC_MAGIC, 28, LX_VDEC_STC_T)
#define LX_VDEC_SET_ID				_IO  (LX_VDEC_IOC_MAGIC, 29)
#define LX_VDEC_STEAL_USERDATA			_IO  (LX_VDEC_IOC_MAGIC, 30)
#define LX_VDEC_SET_LOW_LATENCY			_IO  (LX_VDEC_IOC_MAGIC, 31)
#define LX_VDEC_SET_3D_TYPE			_IO  (LX_VDEC_IOC_MAGIC, 32)
#define LX_VDEC_GET_CPB_INFO			_IOR (LX_VDEC_IOC_MAGIC, 33, LX_VDEC_CPB_INFO_T)
#define LX_VDEC_SET_CPB				_IOW (LX_VDEC_IOC_MAGIC, 34, LX_VDEC_BUFFER_T)
#define LX_VDEC_SET_REQUEST_PICTURES		_IO  (LX_VDEC_IOC_MAGIC, 35)
#define LX_VDEC_RESET				_IO  (LX_VDEC_IOC_MAGIC, 36)
#define LX_VDEC_USE_GSTC			_IO  (LX_VDEC_IOC_MAGIC, 37)
#define LX_VDEC_SET_FLAGS			_IO  (LX_VDEC_IOC_MAGIC, 38)

#define LX_VDEC_IOC_LAST			LX_VDEC_USE_GSTC

#define LX_VDEC_IOC_MAXNR			(_IOC_NR(LX_VDEC_IOC_LAST) +1 )
/** @} */


#if defined(_VDEC_KADP_C_) || defined( _VDEC_NOTI_C_)
#define VDEC_EXTERN
#else
#define VDEC_EXTERN	extern
#endif

#define LX_VDEC_CHECK_IF_INVALID (_v, _t, _expr)	\
		if ( ((_v) <  _t ## _MIN) || ( _t ## _MAX  < (_v)) ) _expr


typedef enum
{
	LX_VDEC_MEMORY_FORMAT_RASTER,
	LX_VDEC_MEMORY_FORMAT_TILED,
} LX_VDEC_MEMORY_FORMAT_T;

typedef struct
{
	unsigned int base_stc;
	unsigned int base_pts;
} LX_VDEC_BASETIME_T;

typedef struct
{
	unsigned int stc;
	unsigned int mask;
} LX_VDEC_STC_T;

typedef struct
{
	unsigned long addr;
	int size;
	int read_offset;
	int write_offset;
} LX_VDEC_CPB_INFO_T;

typedef struct
{
	unsigned long addr;
	int size;
} LX_VDEC_BUFFER_T;

/**
 * Open Parameter for Per Channel.
 * Intialization parameter for each VDEC Channel using LX_VDEC_IO_OPEN_CH
 * following operation is done when issuing LX_VDEC_IO_OPEN_CH.
 * 
 * * CODEC setting
 * * INPUT setting.
 * * OUTPUT setting.
 * 
 * for src and dst SHOULD BE properly set before call LX_VDEC_IO_OPEN_CH.
 */
typedef struct
{
	LX_VDEC_CODEC_T vcodec;		///< codec type of Video decoder : @ref LX_VDEC_CODEC_T

	LX_VDEC_SRC_T src;		///< Source of decoder. @ref LX_VDEC_SRC_T
	LX_VDEC_DST_T dst;		///< Destination of decoder @ref LX_VDEC_DST_T

	LX_VDEC_OPMODE_T opmode;	///< Operation mode of decoder. @ref LX_VDEC_OPMODE_T
	UINT32	useRingBufMod;		///< use ring buffer mode. valid at src == LX_VDEC_SRC_BUFF
	UINT32	useAlignedBuf;		///< use linear buffer mode. valid at src == LX_VDEC_SRC_BUFF
	UINT32	useGstc;		///< use GSTC. Not STC
	UINT32	bufDelaySize;		///< buffering level before decoding start
	UINT32	disDelayOffset;		///< display delay offset (ms)
	UINT32	usrPA;			// [out] User Data physical address for mmap.
	UINT32	usrSz;			// [out] User Data Buffer size in bytes.
	UINT8	clkID;			// [out] Clock ID for AV Lipsync
	BOOLEAN	noAdpStr;
} LX_VDEC_IO_OPEN_CH_T;

/**
 * Buffer Almost Full/Empty Notify Parameter for VDEC input buffer ( CPB )
 * used LX_VDEC_IO_SET_BUFFER_LVL
 */
typedef struct
{
	UINT32	AemptyLvl;		///< Almost Empty level of VDEC input buffer (CPB)
	UINT32	AfullLvl;		///< Almost Full level of VDEC input buffer (CPB)
} LX_VDEC_IO_BUFFER_LVL_T;

/**
 * Buffer status for VDEC input buffer ( CPB )
 * used LX_VDEC_IO_GET_BUFFER_STATUS
 */
typedef struct
{
	UINT32	cpb_depth;
	UINT32	cpb_size;
	UINT32	auib_depth;
	UINT32	auib_size;
} LX_VDEC_IO_BUFFER_STATUS_T;

/**
 * Video Decoder Access Unit Type.
 * For update buffer write pointer for which type of this chunk of memory contains.
 * for LX_VDEC_IO_UPDATE_BUFFER_T::au_type
 */
typedef enum
{
	LX_VAU_SEQH = 1,	///< Sequence Header
	LX_VAU_SEQE,		///< Sequence End.
	LX_VAU_DATA,		///< Picture Data.
} LX_VAU_T;

/**
 * For update buffer write pointer for which type of this chunk of memory contains.
 * [NOTE] au_size should be 512 bytes unit.
 */
typedef struct
{
	UINT32	UId;			///< Unique ID
	UINT32	frRes;			///< Frame Rate Residue
	UINT32	frDiv;			///< Frame Rate Divisor : frame_rate = frRes / frDiv;
	UINT32	au_type;		///< access unit type of this chunk memory. @see LX_VAU_T
	UINT32	au_ptr;			///< access unit pointer. in physical address.
	UINT32	au_size;		///< writing size should be multiple of 512 bytes.
#define	VDEC_UNKNOWN_TIMESTAMP		0xFFFFFFFFFFFFFFFFLL
	UINT64	timestamp;		///< time stamp 1 ns.
	BOOLEAN	is90kHzTick;
} LX_VDEC_IO_UPDATE_BUFFER_T;

/**
 * H/W and Firmware version information.
 */
typedef struct
{
	UINT32 ui32RTLVersion;
	UINT32 ui32FirmwareVersion;
} LX_VDEC_IO_VERSION_T;

/**
 * Init parameter for frame buffer(DPB) update (LX_VDEC_IO_UPDATE_FRAME_BUFFER)
 */
typedef struct
{
	UINT32	numOfFrameBuf;
	UINT32	width;
	UINT32	height;
	UINT32	h_Offset;
	UINT32	v_Offset;
	UINT32	frameRateRes;
	UINT32	frameRateDiv;
} LX_VDEC_IO_INIT_FRAME_BUFFER_T;

/**
 * For update frame buffer(DPB) for which type of this chunk of memory contains.
 */
typedef struct
{
	UINT32	addrY;
	UINT32	addrC;
	UINT32	sizeY;
	UINT32	sizeC;
	UINT32	ui32UId;
	UINT64	ui64TimeStamp;
	UINT32	ui32FrameRateRes;
	UINT32	ui32FrameRateDiv;
} LX_VDEC_IO_UPDATE_FRAME_BUFFER_T;

typedef struct
{
	UINT32 ui32DpbType;		// LX_VAU_SEQH (0): Hdr, LX_VAU_DATA(2): Data
	union
	{
		LX_VDEC_IO_INIT_FRAME_BUFFER_T strFrmHdr;
		LX_VDEC_IO_UPDATE_FRAME_BUFFER_T strFrmPic;
	} u;
} LX_VDEC_IO_UPDATE_FRAME_INFO_T;

/**
 * [DEBUG] Direct Register access ioctl parameter.
 */
typedef struct
{
 	UINT32 	addr;
 	UINT32 	value;
} LX_VDEC_SET_REG_T, LX_VDEC_GET_REG_T;

/**
 * [DEBUG] Direct memory log access ioctl parameter.
 */
typedef struct
{
	UINT32 mem_type;	//<<< LX_VDEC_MEM_BUFF_T
	UINT32 enable;		//<<< enable flag
	UINT32 size;		//<<< input : request size / output : actural read size
	UINT32 buff_ptr;	//<<< user buffer to contain memory log info.
} LX_VDEC_GET_MEM_LOG_T;

/**
 * [DEBUG] Debug command ioctl parameter.
 */
typedef struct
{
	UINT32 	ui32Module;
	UINT32	ui32CmdType;
	UINT32	ui32nSize;
	UINT32	ui32Data[4];
} LX_VDEC_DBG_CMD_T;

typedef enum
{
	lx_vdec_interlace_none,
	lx_vdec_interlace_top_first,
	lx_vdec_interlace_bottom_first,
} lx_vdec_interlace_t;

typedef struct
{
	int size;
	int slots;
} lx_vdec_queue_size_t;

typedef struct
{
	void *framebuffer;
	int width, height, stride;
} lx_vdec_convert_to_raster_t;

typedef enum
{
	lx_vdec_flags_pollerr	= (1<<0),
} lx_vdec_flags_t;

/**
 * Mask for enable/disable Notify.
 * used LX_VDEC_IO_PLAY_SET(notifyMask),
 */
#define LX_VDEC_NOTIFY_ID_SEQH	 	0
#define LX_VDEC_NOTIFY_ID_PICD	 	1
#define LX_VDEC_NOTIFY_ID_USRD	 	2
#define LX_VDEC_NOTIFY_ID_DISP	 	3
#define LX_VDEC_NOTIFY_ID_ERR	 	4
#define LX_VDEC_NOTIFY_ID_AFULL 	5
#define LX_VDEC_NOTIFY_ID_AEMPTY	6
#define LX_VDEC_NOTIFY_ID_RTIMEOUT	7
#define LX_VDEC_NOTIFY_ID_MAXN		8

#define LX_VDEC_CB_ID_SEQH	 	LX_VDEC_NOTIFY_ID_SEQH
#define LX_VDEC_CB_ID_PICD	 	LX_VDEC_NOTIFY_ID_PICD
#define LX_VDEC_CB_ID_USRD	 	LX_VDEC_NOTIFY_ID_USRD
#define LX_VDEC_CB_ID_DISP	 	LX_VDEC_NOTIFY_ID_DISP
#define LX_VDEC_CB_ID_ERR	 	LX_VDEC_NOTIFY_ID_ERR
#define LX_VDEC_CB_ID_AFULL 		LX_VDEC_NOTIFY_ID_AFULL
#define LX_VDEC_CB_ID_AEMPTY		LX_VDEC_NOTIFY_ID_AEMPTY
#define LX_VDEC_CB_ID_MAXN		LX_VDEC_NOTIFY_ID_MAXN

typedef enum
{
	LX_VDEC_NOTIFY_MSK_NONE		= 0,
	LX_VDEC_NOTIFY_MSK_SEQH		= 1UL<< LX_VDEC_NOTIFY_ID_SEQH,		///< notify if got or changed SEQuence Header
	LX_VDEC_NOTIFY_MSK_PICD		= 1UL<< LX_VDEC_NOTIFY_ID_PICD,		///< notify if PICture  Decoded
	LX_VDEC_NOTIFY_MSK_USRD		= 1UL<< LX_VDEC_NOTIFY_ID_USRD,		///< notify if got Closed Caption & AFD
	LX_VDEC_NOTIFY_MSK_DISP		= 1UL<< LX_VDEC_NOTIFY_ID_DISP,		///< notify if PICture  Displayed
	LX_VDEC_NOTIFY_MSK_ERR		= 1UL<< LX_VDEC_NOTIFY_ID_ERR,		///< notify if got Error
	LX_VDEC_NOTIFY_MSK_AFULL	= 1UL<< LX_VDEC_NOTIFY_ID_AFULL,	///< notify if Almost Full.
	LX_VDEC_NOTIFY_MSK_AEMPTY	= 1UL<< LX_VDEC_NOTIFY_ID_AEMPTY,	///< notify if Almost Empty.
	LX_VDEC_NOTIFY_MSK_RTIMEOUT	= 1UL<< LX_VDEC_NOTIFY_ID_RTIMEOUT,	///< notify if nothing happened in timeout

	LX_VDEC_NOTIFY_MSK_ALL		= LX_VDEC_NOTIFY_MSK_SEQH
		| LX_VDEC_NOTIFY_MSK_PICD
		| LX_VDEC_NOTIFY_MSK_USRD
		| LX_VDEC_NOTIFY_MSK_DISP
		| LX_VDEC_NOTIFY_MSK_ERR
		| LX_VDEC_NOTIFY_MSK_AFULL
		| LX_VDEC_NOTIFY_MSK_AEMPTY
		| LX_VDEC_NOTIFY_MSK_RTIMEOUT,


	LX_VDEC_NOTIFY_MSK_ENDMARK	= 1UL<< LX_VDEC_NOTIFY_ID_MAXN,		///< notify mask End marker.
} LX_VDEC_NOTIFY_MSK_T;



typedef enum
{
	LX_VDEC_STATUS_START = 1,
	LX_VDEC_STATUS_STOP
} LX_VDEC_STATUS_T;

/**
 * memory buffer type for memory log
 */
typedef enum
{
	LX_VDEC_MEM_BUFF_PDEC,
	LX_VDEC_MEM_BUFF_LQ,
	LX_VDEC_MEM_BUFF_MSVC_CMD,
	LX_VDEC_MEM_BUFF_MSVC_RSP,
	LX_VDEC_MEM_BUFF_DQ,
	LX_VDEC_MEM_BUFF_CPB,		//<<< For future use
	LX_VDEC_MEM_BUFF_DPB		//<<< For future use
} LX_VDEC_MEM_BUFF_T;

/**
 * scan mode of video decoder.
 * only specified picture type of input data, others shall be skipped.\n
 * 
 * @see LX_VDEC_IO_PLAY_SET_T
 */
typedef enum
{
	LX_VDEC_PIC_SCAN_ALL,			///< decode IPB frame.
	LX_VDEC_PIC_SCAN_I,			///< I picture only (PB skip)
	LX_VDEC_PIC_SCAN_IP,			///< IP picture only (B skip only)
	LX_VDEC_PIC_SCAN_MIN = LX_VDEC_PIC_SCAN_ALL,
	LX_VDEC_PIC_SCAN_MAX = LX_VDEC_PIC_SCAN_IP,
	LX_VDEC_PIC_SCAN_MAXN = (LX_VDEC_PIC_SCAN_MAX+1),
} LX_VDEC_PIC_SCAN_T;

/**
 * video decoder sync operation.
 * 
 * @see LX_VDEC_IO_PLAY_SET_T
 */
typedef enum
{
	LX_VDEC_SYNC_OFF,			///< PTS/DTS match off.
	LX_VDEC_SYNC_ON,			///< PTS/DTS match on.
	LX_VDEC_SYNC_MIN = LX_VDEC_SYNC_OFF,
	LX_VDEC_SYNC_MAX = LX_VDEC_SYNC_ON,
	LX_VDEC_SYNC_MAXN = (LX_VDEC_SYNC_MAX+1),
} LX_VDEC_SYNC_T;

/**
 * display freeze state.
 * 
 * @see LX_VDEC_IO_PLAY_SET_T
 */
typedef enum
{
	LX_VDEC_FREEZE_UNSET,			///< freeze unset.
	LX_VDEC_FREEZE_SET,			///< freeze set.
	LX_VDEC_FREEZE_MIN = LX_VDEC_FREEZE_UNSET,
	LX_VDEC_FREEZE_MAX = LX_VDEC_FREEZE_SET,
	LX_VDEC_FREEZE_MAXN = (LX_VDEC_FREEZE_MAX+1),
} LX_VDEC_FREEZE_T;

#define LX_VDEC_WIDTH_INVALID	0xFFFF
#define LX_VDEC_HEIGHT_INVALID 0xFFFF

/**
 * Video encoding state.
 * 
 * @see LX_VDEC_IO_PLAY_SET_T
 */
typedef enum
{
	LX_VDEC_ENCODE_UNSET,			///< venc unset.
	LX_VDEC_ENCODE_SET,			///< venc set.
	LX_VDEC_ENCODE_MIN = LX_VDEC_ENCODE_UNSET,
	LX_VDEC_ENCODE_MAX = LX_VDEC_ENCODE_SET,
	LX_VDEC_ENCODE_MAXN = (LX_VDEC_ENCODE_MAX+1),
} LX_VDEC_ENCODE_T;

/**
 * Parameter for LX_VDEC_IO_PLAY_SET
 */
typedef struct
{
	UINT32	picScanMode;		///< picture scan mode.	@ref LX_VDEC_PIC_SCAN_T,useful when trick mode.
	UINT32	scanSrcType;		///< scanned source type.	@ref LX_VDEC_PIC_SCAN_T,useful when trick mode.
	UINT32	syncOn;			///< PTS/DTS match on. @ref LX_VDEC_SYNC_T
	UINT32	freeze;			///< display the last frame but decoding is going on. @ref LX_VDEC_FREEZE_T
	UINT32	notifyMask;		///< @ref LX_VDEC_NOTIFY_MSK_T
	UINT16	width __attribute__((deprecated));
	UINT16	height __attribute__((deprecated));
	UINT8	clkID;
	UINT32	stcBaseTime;
	UINT32	ptsBaseTime;
	UINT32	encode;
} LX_VDEC_IO_PLAY_SET_T;

/**
 * Parameter for LX_VDEC_IO_PLAY_GET
 */
typedef struct
{
	UINT8	clkID;
	UINT32	stcBaseTime;
	UINT32	ptsBaseTime;
} LX_VDEC_IO_PLAY_GET_T;

/**
 * common frame types
 * fr_type  : output frame struct type.
 * fr_format: pixel format of frame. shared LX_GFX_SURFACE_TYPE_T and LX_VDEC_FRAME_T
 * index    : index of frame [0~31] within decoded frame array.
 * width    : width in pixel.
 * height   : height in pixel.
 * stride   : stride in bytes.
 * pY       : physical start address of Luminance in bytes.
 * 
 * struct size : 0x10
 */

#define LX_FRAME_T				\
	UINT32	fr_type		:8,		\
		fr_format	:8,		\
		index		:8,		\
		_reserved	:8;		\
	UINT16	width;				\
	UINT16	height;				\
	UINT32	stride;				\
	void	*pY;

/**
 * Decoded VDEC Frame structure (common Video(MPEG/AVC/...) & JPEG).
 *
 * @note This structure is basically shared LX_GFX_SURFACE_SETTINS_T and LX_VENC_FRAME_T.
 * @ref LX_VDEC_NOTIFY_MSK_PICD LX_VDEC_IO_GET_OUTPUT
 */
typedef struct
{
	int	width;
	int	height;
	int	stride;

	unsigned long tile_base;
	unsigned long pY;
	unsigned long pCb;
	unsigned long pCr;
} LX_VDEC_FRAME_T;

/**
 * Decoded image information for Video(MPEG/AVC/DIVX/RV).
 * used for MPEG2&4/RV/AVC streams.
 */
typedef struct
{
	UINT32	picType;		///< picture type of decoded image one of {'I', 'P', 'B', 'N'} ('N'for invalid)
	UINT32	interlSeq;		///< interlaced sequence or not.
	UINT32	interlFrm;		///< interlaced frame or not.
	UINT32	avc3DFpaValid;		///< frame packing arrangement cancel flag (AVC SEI info) : cancel flag 0 -> TRUE, cancel flag 1 -> FALSE
	UINT32	avc3DFpaType;		///< frame packing arrangement type (AVC SEI info)
	UINT32	afd;			///< Active Format Descriptor.
					// 	 FrameRate = frameRateRes/ frameRateDiv
	UINT32	frameRateRes;		///< numerator of frame rate.
	UINT32	frameRateDiv;		///< denominator of frame rate - 1. (0 means denominator is 1)
	UINT32	sar;			///< Source Aspect Ratio. if [31:16] == 0 then, translated by codec type.
	UINT16	par_w;			///< Pixel Aspect Ratio.: width.
	UINT16	par_h;
	UINT32	crop_rect[4];		///< Crop Rectangle, 0:Top, 1:Bottom, 2:Left, 3 Right.
} LX_VDEC_MPEG_OUTPUT_T;

/**
 * Decoded image information for Video.
 */
typedef struct
{
	UINT32	UId;			///< Unique ID
	int display;
	UINT32	bGotAnchor;		///< TRUE if H/W initialized by Sequence Header/SPS
	UINT32	bFail;
	UINT32	picErr;			///< decoding done but has error
	UINT32	pts;			///< PTS of decoded frame for non JPEG.
	UINT32	bLowDelay;		// low_delay
	UINT64	u64Timestamp;		///< timestamp of Media framework, usually 1ns tick.
	lx_vdec_interlace_t interlace;
	LX_VDEC_FRAME_T frm;		///< common VDEC decoded frame structure.
	LX_VDEC_MPEG_OUTPUT_T m;	///< selected when vcodec != LX_VDEC_CODEC_JPEG.
} LX_VDEC_DEC_OUTPUT_T;

/**
 * Displayed image information for Video.
 */
typedef struct
{
	UINT32	UId;
	UINT32	pts;			///< PTS of displayed frame.
	UINT32	bPtsMatched;
	UINT32	u32NumDisplayed;	///< number of displayed frame
	UINT32	u32DqOccupancy;
	UINT32	_rsvd;
	UINT32	u32PicWidth;
	UINT32	u32PicHeight;
	UINT64	u64Timestamp;		///< timestamp of Media framework, usually 1ns tick.
} LX_VDEC_DISP_OUTPUT_T;

/**
 * Decoded/Displayed image information for Video.
 */
typedef struct
{
	LX_VDEC_DEC_OUTPUT_T	decode;
	LX_VDEC_DISP_OUTPUT_T	display;
} LX_VDEC_OUTPUT_T;

/**
 * trick play avalable mode
 * 20110416 seokjoo.lee modified,
 * 1/1000th rate, e.g. 1000 is normal speed, 2000 is x2, 500 is half.
 */
#define	LX_SPEED_RATE_NORMAL	1000				// 1L<<0		//normal speed rate

#define	LX_SPEED_RATE_HALF	(LX_SPEED_RATE_NORMAL/2)	// 0			//play -> pause -> x2 play  1/2 speed rate

#define	LX_SPEED_RATE_x2	(LX_SPEED_RATE_NORMAL*2)	// 1L<<1		//normal speed rate , x2
#define	LX_SPEED_RATE_x4	(LX_SPEED_RATE_NORMAL*4)	// 1L<<2		//normal speed rate , x4
#define	LX_SPEED_RATE_x8	(LX_SPEED_RATE_NORMAL*8)	// 1L<<3		//normal speed rate , x8
#define	LX_SPEED_RATE_x16	(LX_SPEED_RATE_NORMAL*16)	// 1L<<4		//normal speed rate , x16
#define	LX_SPEED_RATE_x32	(LX_SPEED_RATE_NORMAL*32)	// 1L<<5		//normal speed rate , x32

/**
* Video decoder play type.
*
* @enum LX_VDEC_CMD_PLAY
*  normal play
*
* @enum LX_VDEC_CMD_STEP
*  one frame display per one call
*/
typedef enum
{
	LX_VDEC_CMD_PLAY,
	LX_VDEC_CMD_STEP,
	LX_VDEC_CMD_MIN = LX_VDEC_CMD_PLAY,
	LX_VDEC_CMD_MAX = LX_VDEC_CMD_STEP,
	LX_VDEC_CMD_MAXN = (LX_VDEC_CMD_MAX+1),
} LX_VDEC_CMD_T;

/**
 * Start Parameter for LX_VDEC_IO_PLAY.
 */
typedef struct
{
	UINT32	cmd;		///< video decoder play type. @ref LX_VDEC_CMD_T
	SINT32	speed;		///< 0 : pause, 500 : 1/2x, 1000 : normal, 2000 : 2x... valid when cmd == LX_VDEC_CMD_PLAY
} LX_VDEC_IO_PLAY_T;

/**
 * Default Paramter for open channel(LX_VDEC_IO_OPEN_CH).
 *
 * @see LX_VDEC_IO_OPEN_CH_T
 */
#define LX_VDEC_IO_OPEN_CH_DEFAULT_PARAM  {	\
	.vcodec=LX_VDEC_CODEC_MPEG2_HP,		\
	.src=LX_VDEC_SRC_SDEC0,			\
	.dst=LX_VDEC_DST_DE0,			\
	.opmode=LX_VDEC_OPMOD_NORMAL, 		\
	.useRingBufMod=1,			\
	.useAlignedBuf=1,			\
	.useGstc=0,				\
	.bufDelaySize=0,			\
	.disDelayOffset=0,			\
	.usrPA=0,				\
	.usrSz=0,				\
	.clkID=0xFF,				\
	.noAdpStr=FALSE				\
}

/**
 * Default Start Paramter for play setting(LX_VDEC_IO_PLAY_SET).
 *
 * @see LX_VDEC_IO_PLAY_SET_T
 */
#define LX_VDEC_IO_PLAY_SET_DEFAULT_PARAM  {	\
	.picScanMode=LX_VDEC_PIC_SCAN_ALL,	\
	.scanSrcType=LX_VDEC_PIC_SCAN_ALL,	\
	.syncOn=LX_VDEC_SYNC_ON,		\
	.freeze=LX_VDEC_FREEZE_UNSET,		\
	.notifyMask=LX_VDEC_NOTIFY_MSK_SEQH|LX_VDEC_NOTIFY_MSK_PICD|LX_VDEC_NOTIFY_MSK_DISP|LX_VDEC_NOTIFY_MSK_RTIMEOUT|LX_VDEC_NOTIFY_MSK_ERR, \
	.width=LX_VDEC_WIDTH_INVALID,		\
	.height =LX_VDEC_HEIGHT_INVALID,	\
	.clkID = 0xFF,				\
	.stcBaseTime = 0x0, 			\
	.ptsBaseTime = 0x0, 			\
	.encode = LX_VDEC_ENCODE_UNSET		\
}

/**
 * Void parameter for desired play setting(LX_VDEC_IO_PLAY_SET).
 *
 * @see LX_VDEC_IO_PLAY_SET_T
 */
#define LX_VDEC_IO_PLAY_SET_VOID_PARAM  {	\
	.picScanMode=LX_VDEC_PIC_SCAN_MAXN,	\
	.scanSrcType=LX_VDEC_PIC_SCAN_MAXN,	\
	.syncOn=LX_VDEC_SYNC_MAXN,		\
	.freeze=LX_VDEC_FREEZE_MAXN,		\
	.notifyMask=LX_VDEC_NOTIFY_MSK_ENDMARK,	\
	.width=LX_VDEC_WIDTH_INVALID,		\
	.height =LX_VDEC_HEIGHT_INVALID,	\
	.clkID = 0xFF,				\
	.stcBaseTime = 0x0,			\
	.ptsBaseTime = 0x0,			\
	.encode = LX_VDEC_ENCODE_MAX		\
}

/**
 * Default Start Paramter for play setting(LX_VDEC_IO_PLAY_GET).
 *
 * @see LX_VDEC_IO_PLAY_SET_T
 */
#define LX_VDEC_IO_PLAY_GET_DEFAULT_PARAM  {	\
	.clkID = 0xFF,				\
	.stcBaseTime = 0x0,			\
	.ptsBaseTime = 0x0			\
}


#ifndef VDEC_IO_RATE_DELETED

#endif	/* VDEC_IO_RATE_DELETED */


#define LX_VDEC_READ_MAGIC(s)		(s[0]<<0|s[1]<<8|s[2]<<16|s[3]<<24)
#define LX_VDEC_READ_MAGIC2(s0,s1,s2,s3)	(s0<<0|s1<<8|s2<<16|s3<<24)

typedef struct decoded_buffer decoded_buffer_t;
struct decoded_buffer
{
	unsigned long addr_y;
	unsigned long addr_cb, addr_cr;
	int buffer_index;

	unsigned long addr_tile_base;
	enum
	{
		vdo_map_type_linear,
		vdo_map_type_frame,
		vdo_map_type_mixed,
	} vdo_map_type;

	int error_blocks;

#define DECODED_REPORT_SEQUENCE_INIT_FAILED	(1<<0)
#define DECODED_REPORT_DECODE_FAILED		(1<<1)
#define DECODED_REPORT_LOW_DELAY			(1<<2)
#define DECODED_REPORT_HW_RESET				(1<<3)
#define DECODED_REPORT_DECODE_STOP			(1<<4)
	unsigned int report;

	int framerate_num;
	int framerate_den;

	int crop_left, crop_right;
	int crop_top, crop_bottom;

	int stride;
	int width;
	int height;

	enum
	{
		decoded_buffer_interlace_top_first,
		decoded_buffer_interlace_bottom_first,
		decoded_buffer_interlace_none		// progressive
	} interlace;

	enum
	{
		decoded_buffer_picture_type_i,
		decoded_buffer_picture_type_p,
		decoded_buffer_picture_type_b,
		decoded_buffer_picture_type_bi,
		decoded_buffer_picture_type_d,
		decoded_buffer_picture_type_s,
		decoded_buffer_picture_type_pskip,
	} picture_type;
	int display_period;

	/*
	 * AFD in MPEG video. See
	 * - http://en.wikipedia.org/wiki/Active_Format_Description
	 * - http://webapp.etsi.org/workprogram/Report_WorkItem.asp?WKI_ID=21480
	 */
	unsigned char active_format;
	
	int par_w, par_h;

	/*
	 * FPA(Frame Packing Arrangement) in MPEG4 video. See
	 * - http://en.wikipedia.org/wiki/H.264/MPEG-4_AVC
	 */
	int frame_packing_arrangement;

	unsigned int stc_discontinuity;
	unsigned int dts;
	unsigned int pts;
	long long timestamp;

	enum
	{
		decoded_buffer_multi_picture_left,
		decoded_buffer_multi_picture_right,
		decoded_buffer_multi_picture_none,
	} multi_picture;

	unsigned long uid;

	void *user_data_addr;
	int user_data_size;
	int top_field_first;
	int repeat_first_field;
};

/*----------------------------------------------------------------------------------------
	Notify Parameters
----------------------------------------------------------------------------------------*/
/**
 * Sequence Header Notify Structure.
 *
 * @note
 * profile, level, bGMC : information of Sequence Header or Sequence Parameter Set
 *
 * Appllication can use this information for waning "this contents is not played properly".
 *
 * [L8] : H.264 GMC option is not supported.
 *
 */
typedef struct
{
						//	0x00
	UINT32	UId;		///< Unique ID
	UINT32	profile;		///< decoded codec profile.
	UINT32	level;		///< deocded codec level.
	UINT32	bGMC;		///< [VCODEC_H264 only] GMC (Global Motion Compensation) of SPS
								// 	0x10
	UINT32	bFailed;
	UINT64	timestamp;	///< timestamp of Media framework, usually 1ns tick.
								//	0x1C
} LX_VDEC_NOTIFY_PARAM_SEQH_T;

/**
 * Picture Decoded notification paramter.
 * reuse LX_VDEC_DEC_OUTPUT_T ;-)
 */
typedef LX_VDEC_DEC_OUTPUT_T	LX_VDEC_NOTIFY_PARAM_PICD_T;

/**
 Userdata notify structure.

 kernel driver shall save user data buffer and notify the offset in user data buffer.
 the format in user data buffer shall be start with user data identifier.
*/
typedef struct
{
	UINT32	picType;		///< picture type of decoded image associated with this user data.
					///< shall be one of {0 for I frame, 1 for P frame, 2 for B frame }
	UINT32	rpt_ff;			///< repeat first field.
	UINT32	top_ff;			///< top    field first.
	UINT32	tmp_ref;		///< temporal reference.
	UINT32	size;			///< size in bytes.
					// 0x14
	SINT16	frm_idx __attribute__((deprecated));	///< decoded frame index.
	SINT16	_rsvd;
					// 0x18
	UINT32	pts;			///< PTS of related frame
					// 0x1c
	UINT32	offset;			///< current received Physical Address from cpb_base
					///< for valid user level address = usrVA + (offset - usrPA)
					// 0x20

	int decoder_id;			// decoder id where this user data came from
} LX_VDEC_NOTIFY_PARAM_USRD_T;

/**
 * Picture Displayed notification paramter.
 * reuse LX_VDEC_DISP_OUTPUT_T ;-)
 */
typedef LX_VDEC_DISP_OUTPUT_T	LX_VDEC_NOTIFY_PARAM_DISP_T;

/**
 * Error notification.
 */
typedef struct
{
	UINT32 dummy;
} LX_VDEC_NOTIFY_PARAM_ERR_T;

/**
 * Almost Full notification.
 */
typedef struct
{
	UINT32 dummy;
} LX_VDEC_NOTIFY_PARAM_AFULL_T;

/**
 * Almost Empty notification.
 */
typedef struct
{
	UINT32 dummy;
} LX_VDEC_NOTIFY_PARAM_AEMPTY_T;

/**
Read Timeout Notify Structure.
TBD: useless? all information is saved in LX_VDEC_IO_OUTPUT_T
*/
typedef struct
{
	UINT32	status;				// LX_VDEC_STATUS_T

} LX_VDEC_NOTIFY_PARAM_RTIMEOUT_T;

VDEC_EXTERN size_t	sSizeByNotifyID[] __attribute__((deprecated))
#if defined (_VDEC_NOTI_C_) || defined( _VDEC_KADP_C_ )
= {
	#define LX_VDEC_NOTIFY_SIZE_ENTRY(_id)	[ LX_VDEC_NOTIFY_ID_ ## _id ] = sizeof( LX_VDEC_NOTIFY_PARAM_ ## _id ## _T)
	LX_VDEC_NOTIFY_SIZE_ENTRY(SEQH	  ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(PICD	  ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(USRD	  ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(DISP	  ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(ERR	  ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(AFULL   ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(AEMPTY  ),
	LX_VDEC_NOTIFY_SIZE_ENTRY(RTIMEOUT),
}
#endif
;

typedef struct
{
#define LX_VDEC_NOTIFY_MAGIC	LX_VDEC_READ_MAGIC("NOTI")
	UINT32 magic;
	UINT32 id;
	union{
		LX_VDEC_NOTIFY_PARAM_SEQH_T	seqh;
		LX_VDEC_NOTIFY_PARAM_PICD_T	picd;
		LX_VDEC_NOTIFY_PARAM_USRD_T	usrd;
		LX_VDEC_NOTIFY_PARAM_DISP_T	disp;
		LX_VDEC_NOTIFY_PARAM_ERR_T	err;
		LX_VDEC_NOTIFY_PARAM_AFULL_T	afull;
		LX_VDEC_NOTIFY_PARAM_AEMPTY_T	aempty;
		LX_VDEC_NOTIFY_PARAM_RTIMEOUT_T	rtimeout;
	} u;
} LX_VDEC_NOTIFY_PARAM2_T;

/*----------------------------------------------------------------------------------------
	Memory Structure of User Data Buffer.
----------------------------------------------------------------------------------------*/
/**
 * User Data Buffer structure.
 *
 * LX_VDEC_USRD_BUFF_T
 * LX_VDEC_USRD_HEAD_T
 * LX_VDEC_USRD_SEG_HEAD_T
 *
 * 20101121 seokjoo.lee
 * [NOTE] BODA Firmware accesses DDR memory 8 byte unit.
 * the firmware version before 0x20101022, define USRD_8BYTE_REVERSED.
 * after then, should undefine this.
 */
#undef USRD_8BYTE_REVERSED

#ifdef USRD_8BYTE_REVERSED
typedef struct
{
	UINT32	_rsvd;
	UINT16	bytes;
	UINT16	type;
} LX_VDEC_USRD_SEG_HEAD_T;

typedef struct
{
								// 0x00
	UINT32	_rsvd;
								// 0x04
	UINT16	bytesTotal;			///< total nmber of bytes for user data segments
	UINT16	nSegment;			///< number of user data segments for given picture decoded.

								// 0x08
	LX_VDEC_USRD_SEG_HEAD_T seg[16];	///< User Data Segment header
} LX_VDEC_USRD_HEAD_T;

#define GET_USRD_16BIT(_u16)	(_u16)

#else

/* C A U T I O N
 * Boda firmware stores.. byte order in every 8 bytes...
 * SEG_HEAD_T.type = ( ((pHead->type & 0x00ff) << 8) | ((pHead->type & 0xff00) >> 8 ) )
 */
typedef struct
{
	UINT16	type;				///< type of user data.(sequence header or picture header)
	UINT16	bytes;				///< bytes of user data.
	UINT32	_rsvd;
} LX_VDEC_USRD_SEG_HEAD_T;

typedef struct
{
								// 0x00
	UINT16	nSegment;			///< number of user data segments.
	UINT16	bytesTotal;			///< total nmber of bytes for user data segments
								// 0x04
	UINT32	_rsvd;
								// 0x08
	LX_VDEC_USRD_SEG_HEAD_T seg[16];	///< User Data Segment header
} LX_VDEC_USRD_HEAD_T;

#define GET_USRD_16BIT(_u16)	( (((_u16) & 0x00ff) << 8) | (((_u16) & 0xff00) >> 8 ) )

#endif

typedef struct
{
	LX_VDEC_USRD_HEAD_T	hdr;
	UINT8				pDat[0x2000 - sizeof(LX_VDEC_USRD_HEAD_T)];
} LX_VDEC_USRD_BUFF_T;

#define LX_VDEC_NOTIFY_BUFFER_SIZE	256

/**
 * Notify packet structure.  When kernel driver has information on enabled
 * notify mask, save those informatioin on per-process queue allocated when
 * first LX_VDEC_IO_SET_NOTIFY.  and then wake up waiting process.
 *
 * monitoring thread which belongs to a client process read stored notifiaction
 * information from per-process queue and copies to user layer buffer.
 *
@code
main ()
{
	LX_VDEC_CTX_T *pCtx;

	LX_VDEC_NOTIFY_T notifyParam;

	pCtx = KADP_VDEC_Open(channel);	// automatically spawn monitoring thread.

	if ( !pCtx ) return;			// error.

	notifyParam.mskNotify = LX_VDEC_NOTIFY_MSK_SEQH | LX_VDEC_NOTIFY_MSK_PICD | LX_VDEC_NOTIFY_MSK_USRD;

	KADP_VDEC_Ioctl(pCtx, LX_VDEC_IO_SET_NOTIFY, &notifyParam);
	...
}


void MonitoringTask(void)
{
	while (1)
	{
		LX_VDEC_NOTIFY_PARAM2_T	pNotifyBuf[256];

		bytes_read = read(pCtx->fd, (void*)pNotifyBuf, sizeof(pNotifyBuf));

		if ( bytes_read <= 0 )	continue;		// nothing received -> skip.

		nNotified = bytes_read / sizeof(LX_VDEC_NOTIFY_PARAM2_T);
		for iNoti = 0;

		// actual handling.
		pNoti = pNotifyBuf;
		for ( iNoti=0 ; iNoti < nNotified; iNoti++, pNoti++)
		{
			switch (pNoti->id)
			{
				case LX_VDEC_NOTIFY_ID_SEQH: // handle Sequence header.
				...
			}
		}
	}
}
@endcode
*/
typedef struct
{
	/**
	which event is enabled per vdec channel.
	mask shall be set per-channel basis with LX_VDEC_NOTIFY_MSK_T
	*/
	UINT32	mask[LX_VDEC_CH_MAXN];

	/**
	notify data payload.
	which shall be filled from kernel driver only contains specified by mask field.
	*/
	UINT8	data[LX_VDEC_CH_MAXN][LX_VDEC_NOTIFY_ID_MAXN][LX_VDEC_NOTIFY_BUFFER_SIZE];
											// 0x80 * 4 + 0x10 = 0x210
} LX_VDEC_NOTIFY_PARAM_T;

// [debugging] build a list of iocmd.
VDEC_EXTERN const char*	gstrVdecIoCmd[] __attribute__((deprecated))
#if defined(_VDEC_KADP_C_) || defined( _VDEC_NOTI_C_)
=
{															// 0123456
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_OPEN_CH)		= "OPEN_CH",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_CLOSE_CH)		= "CLOS_CH",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_PLAY)			= "PLAY",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_PLAY_SET)		= "SET",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_FLUSH)		= "FLUSH",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_SET_BUFFER_LVL)	= "S_BFLVL",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_GET_BUFFER_STATUS)	= "G_BFSTA",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_UPDATE_BUFFER)	= "UP_BUFF",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_GET_OUTPUT)		= "G_OUTP",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_GET_VERSION)		= "GET_VER",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_SET_REG)		= "S_REG",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_GET_REG)		= "G_REG",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_ENABLELOG)		= "E_LOG",
	LX_IOCMD_STRING_HOLDER(LX_VDEC_IO_DBG_CMD)		= "DEBUG",
	[LX_VDEC_IOC_MAXNR] = "unknown"
}
#endif
;

VDEC_EXTERN const char *gstrVdecVcodecName[] __attribute__((deprecated))
#if defined(_VDEC_KADP_C_) || defined( _VDEC_NOTI_C_)
=
{
	[LX_VDEC_CODEC_H264_HP]	= "h264",
	[LX_VDEC_CODEC_VC1_RCV_V1]	= "vc1v1",
	[LX_VDEC_CODEC_VC1_RCV_V2]	= "vc1v2",
	[LX_VDEC_CODEC_VC1_ES]	= "vc1es",
	[LX_VDEC_CODEC_MPEG2_HP]	= "mpg2",
	[LX_VDEC_CODEC_MPEG4_ASP]	= "mpg4",
	[LX_VDEC_CODEC_XVID]	= "xvid",
	[LX_VDEC_CODEC_DIVX3]	= "dvx3",
	[LX_VDEC_CODEC_DIVX4]	= "dvx4",
	[LX_VDEC_CODEC_DIVX5]	= "dvx5",
	[LX_VDEC_CODEC_RVX]		= "rvx",
	[LX_VDEC_CODEC_AVS]		= "avs",
}
#endif
;

VDEC_EXTERN const char *gstrVdecSrcName[] __attribute__((deprecated))
#if defined(_VDEC_KADP_C_) || defined( _VDEC_NOTI_C_)
=
{
	[LX_VDEC_SRC_SDEC0]	= "te0",
	[LX_VDEC_SRC_SDEC1]	= "te1",
	[LX_VDEC_SRC_SDEC2]	= "te2",
	[LX_VDEC_SRC_BUFF]	= "buf",
	[xLX_VDEC_SRC_BUFFx]	= "buf1",
	[LX_VDEC_SRC_BUFFTVP]	= "buftvp",
}
#endif
;
VDEC_EXTERN const char *gstrVdecDstName[] __attribute__((deprecated))
#if defined(_VDEC_KADP_C_) || defined( _VDEC_NOTI_C_)
=
{
	[LX_VDEC_DST_DE0]	= "de0",
	[LX_VDEC_DST_DE1]	= "de1",
	[LX_VDEC_DST_BUFF]	= "buf",
}
#endif
;
VDEC_EXTERN const char *gstrVdecNotifyName[] __attribute__((deprecated))
#if defined(_VDEC_KADP_C_) || defined( _VDEC_NOTI_C_)
=
{
	[LX_VDEC_NOTIFY_ID_SEQH]	= "SEQH",
	[LX_VDEC_NOTIFY_ID_PICD]	= "PICD",
	[LX_VDEC_NOTIFY_ID_USRD]	= "USRD",
	[LX_VDEC_NOTIFY_ID_DISP]	= "DISP",
	[LX_VDEC_NOTIFY_ID_ERR]		= "ERR ",
	[LX_VDEC_NOTIFY_ID_AFULL]	= "FULL",
	[LX_VDEC_NOTIFY_ID_AEMPTY]	= "EMPT",
	[LX_VDEC_NOTIFY_ID_RTIMEOUT]= "TOUT"
}
#endif
;

/**
 * @def LX_VDEC_IOCMD_PREFIX_SIZE
 * [debug] prefix byte size of IO Command.
 * which is used to skip common prefix in @ref LX_VDEC_IOCMD_NAME
 * 
 * @def LX_VDEC_IOCMD_NAME
 * [debug] get string from VDEC IO command value.
 * @param _iocmd	VDEC IO command
 * @return string pointer to given IO command.
 * if valid, returns pointer to string of given _iocmd value.
 * else      returns NULL
 * [NOTE] : prefix shall be removed.
 * @{
 */
#define LX_VDEC_IOCMD_NAME(_iocmd)		LX_IOCMD_NAME(_iocmd, gstrVdecIoCmd, LX_VDEC_IOC_MAXNR, 0)
#define LX_VDEC_CODEC_NAME(_vcodec)			gstrVdecVcodecName[((UINT32)_vcodec)%LX_VDEC_CODEC_INVALID]
#define LX_VCODEC_NAME(_vcodec)			gstrVdecVcodecName[((UINT32)_vcodec)%LX_VDEC_CODEC_INVALID]
#define LX_VDEC_SRC_NAME(_src_id)		gstrVdecSrcName   [((UINT32)_src_id)%LX_VDEC_SRC_MAXN]
#define LX_VDEC_DST_NAME(_dst_id)		gstrVdecDstName   [((UINT32)_dst_id)%LX_VDEC_DST_MAXN]
#define LX_VDEC_NOTIFY_NAME(_noti_id)	gstrVdecNotifyName[((UINT32)_noti_id)%LX_VDEC_NOTIFY_ID_MAXN]
/** @} */


#endif /* _VDEC_DRV_H_ */

/** @} */
/* vim:set ts=8: */
