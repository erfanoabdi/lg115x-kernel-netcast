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



/** @file adec_kapi.h
 *
 *  application interface header for adec device
 *
 *  @author		JongSang Oh(jongsang.oh@lge.com)
 *  @version		0.6d
 *  @date		2010.01.28
 *
 *  @addtogroup lg1150_adec
 *	@{
 */

#ifndef	_ADEC_KAPI_H_
#define	_ADEC_KAPI_H_

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
#define	ADEC_IOC_MAGIC		'A'

/**
@name ADEC IOCTL List
ioctl list for adec device.

@{
@def ADEC_IOW_INIT_MODULE
Initializes the adec module.
ADEC module shall be initialized itself with pre-defined configuration value.\n
ADEC module includes audio codec, post-processing and SPDIF parts.\n
And, serveral global variable is set by LX_ADEC_INIT_TYPE_T value.
@li register device, interrupts, buffer memory and firmware download.

@def ADEC_IOW_SET_EVENT
Sets a ADEC event to be getted.
In order to get a device event, use a ADEC_IOR_GET_EVENT ioctl function.\n
If once setted event, send event and reset by ADEC_IOW_RESET_EVENT ioctl function.

@def ADEC_IOW_RESET_EVENT
Resets a ADEC event to be getted.
This function clears a event to be getted.
Before clearing a event, a pending event must be notified.

@def ADEC_IOR_GET_EVENT
Gets a ADEC event to have been setted and arised from device driver.
Returns any of the setted events from the ADEC device.\n
When the pending events have been read by the DDI module,\n
the ADEC device¡¯s internal event bit field shall be cleared.\n
If any event does not arises, this function is polled.\n
If event has a memory data, use a LX_ADEC_EVENT_INFO_T with location and size info.

@def ADEC_IOR_GET_MEM_INFO
Gets a ADEC memory information to have been setted.
Returns a memory information from the memory structure(LX_ADEC_MEM_INFO_T).

@def ADEC_IOR_GET_BUFFER_INFO
Gets a current ADEC Buffer(CPBM, CPBA, MPB0, MPB1, MPB2, MPB3) information.
Returns a CPB information from the LX_ADEC_BUF_INFO_T structure.

@def ADEC_IOR_GET_DECODING_INFO
Gets a current ADEC decoding information.
Returns a decoding information from the LX_ADEC_DEC_INFO_T structure.

@def ADEC_IOW_RESET_AAD_MODULE
Resets a AAD Module using H/W reset signal.
This function resets a AAD module to clear previous setting.


@def ADEC_IOW_SET_SOURCE
Sets an audio device source to adec module.
ADEC module sets the input source, the number of ADC port and the input stream type.

@def ADEC_IOW_START_DECODING
Starts the decoding of the DTV Stream.
The source types defined in enum LX_ADEC_START_DEC_T must be reset.

@def ADEC_IO_STOP_DECODING
Stops the decoding of the DTV Stream.
This function also mutes audio output.

@def ADEC_IOR_GET_DECODING_TYPE
Gets the current decoding audio type.
This function returns the value that was set by the ADEC_IOW_START_DECODING function.

@def ADEC_IOR_GET_ES_EXISTENCE
Checks whether audio ES(Elementary Stream) exists or not.
This function is used for checking the existence of the current ES.

@def ADEC_IOR_GET_ES_INFO
Gets the audio ES(Elementatry Stream) information such as HEAAC, MPEG and AC3.
ES info may be added other information further.

@def ADEC_IOW_START_AD_DECODING
Starts the audio description decoding.
Audio description sound should be mixed with the main audio sound.

@def ADEC_IO_STOP_AD_DECODING
Stops the audio description decoding.
This function also mutes audio output.

@def ADEC_IOW_SET_SPK_OUT_MODE
Sets a speaker output mode(L+R, L+L, R+R).
Controls the speaker output mode by DDI function.
The speaker output means a I2S, DAC and S/PDIF output ports.

@def ADEC_IOW_SET_DECODER_MODE
Sets a decoder mode(DRC, Downmix).
Controls the decoder DRC and Downmix mode by DDI function.


@def ADEC_IOW_SET_VOLUME
Sets an audio D-AMP I2S volume.
Range of input parameter value is 0 to 0xFF FFFF(24 bit, UINT32).

@def ADEC_IOW_SET_AD_VOLUME
Sets an audio description volume before mixing main audio.
Range of input parameter value is 0 to 0xFF FFFF(24 bit, UINT32).
This function is used when only ADEC_IOW_START_AD_DECODING is called.

@def ADEC_IOW_SET_DAC_OUT_VOLUME
Sets the volume of DAC output.
Range of input parameter value is 0 to 0xFF FFFF(24 bit, UINT32).

@def ADEC_IOW_SET_OUTPUT_PORT_MUTE
Sets the mute of each DAC and I2S output port.
The SPDIF output is implemented by another IOCTL.(ADEC_IOW_SET_SPDIF_MUTE)

@def ADEC_IOW_SET_MIX_VOLUME
Sets an audio mix volume before mixing main audio.
Range of input parameter value is 0 to 0xFF FFFF(24 bit, UINT32).

@def ADEC_IOW_SET_DAMP_VOLUME
Sets an audio D-AMP main volume after mixing main/sub audio.
Range of input parameter value is 0 to 100.

@def ADEC_IOW_SET_DAMP_MUTE
Sets a D-AMP mute on or off.
Stops the audio output.


@def ADEC_IOW_SET_SPDIF_OUTPUT_TYPE
Sets a S/PDIF output type.
When adecType of ADEC_IOW_START_DECODING is LX_ADEC_SRC_TYPE_EAC3:\n
If eSpdifMode is set as LX_ADEC_SPDIF_AC3, it outputs after transcoding.\n
When adecType of ADEC_IOW_START_DECODING is LX_ADEC_SRC_TYPE_HEAAC:\n
If eSpdifMode is set as LX_ADEC_SPDIF_DTS, it outputs after transcoding.\n
Only LX_ADEC_SPIDF_AC3, LX_ADEC_SPIDF_DTS and LX_ADEC_SPIDF_PCM are valid for this function.

@def ADEC_IOW_SET_SPDIF_SCMS_CTRL
Sets a S/PDIF SCMS(Serial Copy Management System) control type.
Refer a LX_ADEC_SPDIF_SCMS_T structure.

@def ADEC_IOW_SET_SPDIF_VOLUME
Sets a S/PDIF output volume.
Range of input parameter value is 0 to 0xFF FFFF(24 bit, UINT32).

@def ADEC_IOW_SET_SPDIF_MUTE
Sets a S/PDIF mute on or off.
Stops the audio digital data output.


@def ADEC_IOW_ENABLE_AV_LIPSYNC
Enables or disables the AV Lipsync mechanism.
Controls the lipsync function manually.

@def ADEC_IOW_SET_I2S_OUT_DELAY_TIME
Sets a delay time in milli-second of I2S Out of PCM.
Add a delay time for PCM input audio data.

@def ADEC_IOW_SET_DAC_OUT_DELAY_TIME
Sets a delay time in milli-second of DAC out of PCM.
Add a delay time for PCM input audio data.

@def ADEC_IOW_SET_SPDIF_DELAY_TIME
Sets a delay time in milli-second of S/PDIF.
Add a delay time for SPDIF input audio data.

@def ADEC_IOW_SET_TRICK_STATE
Sets a trick state of ADEC.
If ADEC is running in DVR mode(Pause or Resume state), ADEC trick state can be changed.

@def ADEC_IORW_GET_SET_CLOCK_INFO
Gets and sets a clock information of ADEC driver.
This function gets and sets a clock information of ADEC driver.
A clock information has STC, PTS and GSTC value.


@def ADEC_IOW_SET_BALANCE
Sets a audio balance.
Range of input parameter value is 0 to 100.\n
Value 50 is the center value.

@def ADEC_IOW_SET_BASS
Sets a audio bass.
Range of input parameter value is 0 to 100.\n
Value 50 is the center value.

@def ADEC_IOW_SET_TREBLE
Sets a audio Treble.
Range of input parameter value is 0 to 100.\n
Value 50 is the center value.


@def ADEC_IOW_SE_SET_FUNCTION
Sets a SE(Sound Engine) mode annd parameters.
The SE mode is enabled or disabled by functions's each field value.

@def ADEC_IORW_SE_GET_FUNCTION
Gets the parameter's SE(Sound Engine).
The SE parameters are get from Audio DSP SE engine.


@def ADEC_IOW_FEED_AUDIO_CLIP
Feeds an audio clip and sets clip memory info.
This function copies the audio clip data into ADEC driver memory.

@def ADEC_IOW_START_AUDIO_CLIP
Starts a playing of the audio clip.
Audio clip must be loaded by the ADEC_IOW_LOAD_AUDIO_CLIP function for using this function.

@def ADEC_IO_STOP_AUDIO_CLIP
Stops a playing of the audio clip.
This function stops a playing of the audio clip.

@def ADEC_IO_PAUSE_AUDIO_CLIP
Pauses a playing of the audio clip.
After calling this IOCTL function, resume must be enabled by the ADEC_IO_RESUME_AUDIO_CLIP IOCTL function.

@def ADEC_IO_RESUME_AUDIO_CLIP
Resumes a paused audio clip playing.
After calling this IOCTL function, a audio clip is played at the paused position.

@def ADEC_IOW_FLUSH_AUDIO_CLIP
Flushes a audio clip data when paused.
After calling this IOCTL function, a audio clip data is flushed at the paused position.

@def ADEC_IOW_RESET_AUDIO_CLIP
Resets a audio playing.
After calling this IOCTL function, a audio clip play is reset to recover current error state.

@def ADEC_IOW_SET_AV_CLOCK_CTRL
Controls a AV clock for av lip sync operation.
After calling this IOCTL function, a presenting audio is resumed and paused.


@def ADEC_IOR_GET_ENC_BUF_INFO
Gets a audio encode memory buffer information.
This value is used for copying encoded ES and AUI info by mmap function.

@def ADEC_IOW_SET_ENC_PARAM
Sets a audio encoding parameter.
A audio encoding parameter is set by this function(audio codec, bitrate, sampling frequency, number of channel, bit per sample).

@def ADEC_IOR_GET_ENC_PARAM
Gets a audio encoded parameter.
A audio encoded parameter is get by this function(audio codec, bitrate, sampling frequency, number of channel, bit per sample).

@def ADEC_IOW_START_ENCODING
Starts a encoding of the audio input source(TP, AAD, ADC and HDMI).
Audio encoding data is saved ES(Elementary Stream) data and AUI(Access Unit Information) by the LX_ADEC_ENC_START_T parameters.

@def ADEC_IOW_STOP_ENCODING
Stops a encoding of the audio input source.
This function stops a encoding of the audio input source(TP, AAD, ADC and HDMI).

@def ADEC_IOR_GET_ENCODING_INFO
Gets a encoding information of the audio clip.
This function gets a current encoding AUI buffer information to get ES data using mmap memory.


@def ADEC_IOR_GET_PCM_BUF_INFO
Gets a audio pcm data memory buffer information.
This value is used for copying decpmpressed PCM and AUI info by mmap function.

@def ADEC_IORW_GET_CAPTURING_INFO
Copys a PCM audio data information of the audio clip.
This function copys a current AUI buffer information to get PCM data using mmap memory.


@def ADEC_IORW_READ_AND_WRITE_REG
Do read and write adec register.
This function is used to debug ADEC module for debug purpose.

@def ADEC_IOW_CUSTOM_IPC
Set a custom command for IPC for debug.
This function is used to debug ADEC module for debug purpose.

@def ADEC_IO_SHOW_STATUS_REGISTER
Show a ADEC buffer status for debug.
This function is used to debug ADEC module for debug purpose.

@def ADEC_IOW_DEBUG_PRINT_CTRL
Enable or disable debug print for debug.
This function is used to debug ADEC module for debug purpose.

@def ADEC_IORW_READ_ADEC_MEMORY
Read a ADEC memory data from DDR memory for debug.
This function is used to debug ADEC module for debug purpose.

*/
/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
/* adec module */
#define	ADEC_IOW_INIT_MODULE						_IOW(ADEC_IOC_MAGIC,  0, LX_ADEC_INIT_TYPE_T)
#define ADEC_IOW_SET_EVENT							_IOW(ADEC_IOC_MAGIC,  1, LX_ADEC_EVENT_TYPE_T)
#define ADEC_IOW_RESET_EVENT						_IOW(ADEC_IOC_MAGIC,  2, LX_ADEC_EVENT_TYPE_T)
#define ADEC_IORW_GET_EVENT							_IOWR(ADEC_IOC_MAGIC, 3, LX_ADEC_EVENT_INFO_T)
#define ADEC_IORW_GET_BUFFER_INFO					_IOWR(ADEC_IOC_MAGIC, 4, LX_ADEC_BUF_INFO_T)
#define ADEC_IORW_GET_DECODING_INFO					_IOWR(ADEC_IOC_MAGIC, 5, LX_ADEC_DEC_INFO_T)
#define ADEC_IO_RESET_AAD_MODULE					_IO(ADEC_IOC_MAGIC,   6)
#define ADEC_IOW_SET_AAD_BIT_SHIFT					_IOW(ADEC_IOC_MAGIC,  7, UINT32)

/* adec decoder control */
#define ADEC_IOW_SET_SOURCE							_IOW(ADEC_IOC_MAGIC,  10, LX_ADEC_SET_SOURCE_T)
#define ADEC_IOW_START_DECODING						_IOW(ADEC_IOC_MAGIC,  11, LX_ADEC_START_DEC_T)
#define	ADEC_IOW_STOP_DECODING						_IOW(ADEC_IOC_MAGIC,  12, LX_ADEC_STOP_DEC_T)
#define ADEC_IORW_GET_ES_EXISTENCE					_IOWR(ADEC_IOC_MAGIC, 13, LX_ADEC_ES_EXIST_T)
#define ADEC_IORW_GET_ES_INFO						_IOWR(ADEC_IOC_MAGIC, 14, LX_ADEC_GET_ES_INFO_T)
#define ADEC_IOW_START_AD_DECODING					_IOW(ADEC_IOC_MAGIC,  15, LX_ADEC_SRC_TYPE_T)
#define	ADEC_IO_STOP_AD_DECODING					_IO(ADEC_IOC_MAGIC,   16)
#define	ADEC_IOW_SET_SPK_OUT_MODE					_IOW(ADEC_IOC_MAGIC,  17, LX_ADEC_OUTPUT_MODE_T)
#define	ADEC_IOW_SET_DECODER_MODE					_IOW(ADEC_IOC_MAGIC,  18, LX_ADEC_DECODER_MODE_T)

/* volume control */
#define ADEC_IOW_SET_VOLUME							_IOW(ADEC_IOC_MAGIC, 50, UINT32)
#define ADEC_IOW_SET_AD_VOLUME						_IOW(ADEC_IOC_MAGIC, 51, UINT32)
#define ADEC_IOW_SET_DAC_OUT_VOLUME					_IOW(ADEC_IOC_MAGIC, 52, LX_ADEC_DAC_VOL_T)
#define ADEC_IOW_SET_OUTPUT_PORT_MUTE				_IOW(ADEC_IOC_MAGIC, 53, LX_ADEC_OUTPUT_PORT_MUTE_T)
#define ADEC_IOW_SET_MIX_VOLUME						_IOW(ADEC_IOC_MAGIC, 54, LX_ADEC_MIX_VOL_T)
#define ADEC_IOW_SET_DAMP_VOLUME					_IOW(ADEC_IOC_MAGIC, 55, UINT8)
#define ADEC_IOW_SET_DAMP_MUTE						_IOW(ADEC_IOC_MAGIC, 56, BOOLEAN)

/* SPDIF control */
#define ADEC_IOW_SET_SPDIF_OUTPUT_TYPE				_IOW(ADEC_IOC_MAGIC, 60, LX_ADEC_SPDIF_MODE_T)
#define ADEC_IOW_SET_SPDIF_SCMS_CTRL				_IOW(ADEC_IOC_MAGIC, 61, LX_ADEC_SPDIF_SCMS_T)
#define ADEC_IOW_SET_SPDIF_VOLUME					_IOW(ADEC_IOC_MAGIC, 62, UINT32)
#define ADEC_IOW_SET_SPDIF_MUTE						_IOW(ADEC_IOC_MAGIC, 63, BOOLEAN)

/* AV lipsync control */
#define ADEC_IOW_ENABLE_AV_LIPSYNC					_IOW(ADEC_IOC_MAGIC, 70, LX_ADEC_SYNC_T)
#define ADEC_IOW_SET_I2S_OUT_DELAY_TIME				_IOW(ADEC_IOC_MAGIC, 71, UINT32)
#define ADEC_IOW_SET_DAC_OUT_DELAY_TIME				_IOW(ADEC_IOC_MAGIC, 72, UINT32)
#define ADEC_IOW_SET_SPDIF_DELAY_TIME				_IOW(ADEC_IOC_MAGIC, 73, UINT32)
#define ADEC_IOW_SET_TRICK_STATE					_IOW(ADEC_IOC_MAGIC, 74, LX_ADEC_TRICK_MODE_T)
#define ADEC_IOR_GET_CLOCK_INFO						_IOR(ADEC_IOC_MAGIC, 75, LX_ADEC_CLOCK_INFO_T)

/* Sound Effect control */
#define ADEC_IOW_SET_BALANCE						_IOW(ADEC_IOC_MAGIC, 80, UINT8)
#define ADEC_IOW_SET_BASS							_IOW(ADEC_IOC_MAGIC, 81, UINT8)
#define ADEC_IOW_SET_TREBLE							_IOW(ADEC_IOC_MAGIC, 82, UINT8)

/* SE(Sound Engine) control */
#define ADEC_IOW_SE_SET_FUNCTION					_IOW(ADEC_IOC_MAGIC,  90, LX_ADEC_SE_FN_PARAM_T)
#define ADEC_IORW_SE_GET_FUNCTION					_IOWR(ADEC_IOC_MAGIC, 91, LX_ADEC_SE_FN_PARAM_T)

/* Clip play control */
#define ADEC_IOW_FEED_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 120, LX_ADEC_CLIP_MEM_INFO_T)
#define ADEC_IOW_START_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 121, LX_ADEC_CLIP_START_INFO_T)
#define	ADEC_IOW_STOP_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 122, LX_ADEC_DEC_MODE_T)
#define	ADEC_IOW_PAUSE_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 123, LX_ADEC_DEC_MODE_T)
#define	ADEC_IOW_RESUME_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 124, LX_ADEC_DEC_MODE_T)
#define	ADEC_IOW_FLUSH_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 125, LX_ADEC_DEC_MODE_T)
#define ADEC_IOW_RESET_AUDIO_CLIP					_IOW(ADEC_IOC_MAGIC, 126, LX_ADEC_DEC_MODE_T)
#define ADEC_IOW_SET_AV_CLOCK_CTRL					_IOW(ADEC_IOC_MAGIC, 127, LX_ADEC_AV_CLOCK_INFO_T)


/* Audio Encoding control */
#define ADEC_IOR_GET_ENC_BUF_INFO					_IOR(ADEC_IOC_MAGIC,  130, LX_ADEC_ENC_BUF_T)
#define ADEC_IOW_SET_ENC_PARAM						_IOW(ADEC_IOC_MAGIC,  131, LX_ADEC_ENC_PARAM_T)
#define	ADEC_IOR_GET_ENC_PARAM						_IOR(ADEC_IOC_MAGIC,  132, LX_ADEC_ENC_PARAM_T)
#define ADEC_IOW_START_ENCODING						_IOW(ADEC_IOC_MAGIC,  133, LX_ADEC_ENC_START_T)
#define	ADEC_IOW_STOP_ENCODING						_IOW(ADEC_IOC_MAGIC,  134, LX_ADEC_ENC_STOP_T)
#define	ADEC_IORW_GET_ENCODING_INFO					_IOWR(ADEC_IOC_MAGIC, 135, LX_ADEC_ENC_INFO_T)


/* Audio PCM Capture control */
#define ADEC_IOR_GET_PCM_BUF_INFO					_IOR(ADEC_IOC_MAGIC,  140, LX_ADEC_PCM_BUF_T)
#define	ADEC_IORW_GET_CAPTURING_INFO				_IOWR(ADEC_IOC_MAGIC, 141, LX_ADEC_CAP_INFO_T)


/* Debug control */
#define ADEC_IORW_READ_AND_WRITE_REG				_IOWR(ADEC_IOC_MAGIC, 190, LX_ADEC_REG_INFO_T)
#define ADEC_IOW_CUSTOM_IPC							_IOW(ADEC_IOC_MAGIC,  191, LX_ADEC_CUSTOM_IPC_T)
#define	ADEC_IO_SHOW_STATUS_REGISTER				_IO(ADEC_IOC_MAGIC,   192)
#define ADEC_IOW_DEBUG_PRINT_CTRL					_IOW(ADEC_IOC_MAGIC,  193, LX_ADEC_DEBUG_CTRL_T)

#define ADEC_IOC_MAXNR								200


/** @} */

//Enable D-AMP Volume Control
//#define ENABLE_DAMP_VOLUME_CONTROL

//define max size of AUI index
#define MAX_TRANSFER_NUM_OF_INDEX     		8

// The Size of ADEC KDRV IPC Command
#define LX_IPC_ARRAY_SIZE 					20


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * ADEC Init Module Type.
 * ADEC Init Module Type is defined.\n
 * If type is LX_ADEC_INIT_TYPE_NONE, ADEC is set to default mode.
 * If type is LX_ADEC_INIT_TYPE_SYS_ATSC, AC3(EAC3) decoding DRC mode is set to LINE Mode not RF Mode(DVB).
 *
 */
typedef  enum
{
	LX_ADEC_INIT_TYPE_NONE			= 0x0,		///< INIT TYPE : NONE
	LX_ADEC_INIT_TYPE_SYS_ATSC		= 0x1,		///< DTV System is ATSC. SCART output is disabled.
	LX_ADEC_INIT_TYPE_SYS_DVB		= 0x2,		///< DTV System is DVB. SCART output is enabled.

	LX_ADEC_INIT_TYPE_SYS_ATSC_GCD	= 0x10,		///< DTV System is ATSC_GCD. Allout output is mixed. and SPDIF output is always dolby digital.

	LX_ADEC_INIT_TYPE_MAX						///< INIT TYPE : MAX
} LX_ADEC_INIT_TYPE_T;

/**
 * ADEC EVENT Type.
 * ADEC Event type is defined.
 *
 */
typedef  enum
{
	LX_ADEC_EVENT_NONE					= 0x00000000,		///< Event : NONE

/* 0 ~ 15 bit : DSP0 Interrupt is defined. */
//mask : info error decoding(2) buffer frame(index) enc input debug
	LX_ADEC_EVENT_DEC0_DECODING_INFO	= 0x00000001,		///< Event : ADEC has info.
	LX_ADEC_EVENT_DEC0_DECODING_ERROR	= 0x00000002,		///< Event : ADEC decoder has error.
	LX_ADEC_EVENT_DEC0_DECODING_START	= 0x00000004,		///< Event : ADEC starts decoding for 1 frame.
	LX_ADEC_EVENT_DEC0_DECODING_STOP	= 0x00000008,		///< Event : ADEC stops decoding.

	LX_ADEC_EVENT_DEC0_BUF_OVERFLOW		= 0x00000010,		///< Event : Decoder Buffer is overflow.
	LX_ADEC_EVENT_DEC0_BUF_UNDERFLOW	= 0x00000020,		///< Event : Decoder Buffer is underflow.
	LX_ADEC_EVENT_DEC0_FRAME_DEC_DONE	= 0x00000040,		///< Event : ADEC 1 Frame Decoding Done.
	LX_ADEC_EVENT_DEC0_INDEX_DEC_DONE	= 0x00000080,		///< Event : ADEC Index Frame Decoding Done.

	LX_ADEC_EVENT_DEC0_INTERRUPT		= 0x000000FF,		///< Event : ADEC DEC0 Interrupt
	LX_ADEC_EVENT_DEC0_CLIP_UNMASK		= 0x0000003F,		///< Event : ADEC DEC0 Clip default Event for un-mask.

	LX_ADEC_EVENT_DEC1_DECODING_INFO	= 0x00000100,		///< Event : ADEC has info.
	LX_ADEC_EVENT_DEC1_DECODING_ERROR	= 0x00000200,		///< Event : ADEC decoder has error.
	LX_ADEC_EVENT_DEC1_DECODING_START	= 0x00000400,		///< Event : ADEC starts decoding for 1 frame.
	LX_ADEC_EVENT_DEC1_DECODING_STOP	= 0x00000800,		///< Event : ADEC stops decoding.

	LX_ADEC_EVENT_DEC1_BUF_OVERFLOW		= 0x00001000,		///< Event : Decoder Buffer is overflow.
	LX_ADEC_EVENT_DEC1_BUF_UNDERFLOW	= 0x00002000,		///< Event : Decoder Buffer is underflow.
	LX_ADEC_EVENT_DEC1_FRAME_DEC_DONE	= 0x00004000,		///< Event : ADEC 1 Frame Decoding Done.
	LX_ADEC_EVENT_DEC1_INDEX_DEC_DONE	= 0x00008000,		///< Event : ADEC Index Frame Decoding Done.

	LX_ADEC_EVENT_DEC1_INTERRUPT		= 0x0000FF00,		///< Event : ADEC DEC1 Interrupt
	LX_ADEC_EVENT_DEC1_CLIP_UNMASK		= 0x00003F00,		///< Event : ADEC DEC1 Clip default Event for un-mask.

	LX_ADEC_EVENT_AUI_ENC_DONE			= 0x00010000,		///< Event : ADEC AUI Encoding Done.

	LX_ADEC_EVENT_DSP0_UNMASK_ALL		= 0x00013F3F,		///< Event : ADEC DSP0's all Event for un-mask.

/* add for debug function for DSP0 */
	LX_ADEC_EVENT_SIF_DATA				= 0x00100000,		///< Event : Audio SIF Data Received..
	LX_ADEC_EVENT_ADC_DATA				= 0x00200000,		///< Event : Audio ADC Data Received..
	LX_ADEC_EVENT_HDMI_DATA				= 0x00400000,		///< Event : Audio HDMI Data Received..
	LX_ADEC_EVENT_TPI0_DATA				= 0x00800000,		///< Event : Audio TPI0 Data Received..
	LX_ADEC_EVENT_TPI1_DATA				= 0x01000000,		///< Event : Audio TPI1 Data Received..
	LX_ADEC_EVENT_DEC0_DEBUG			= 0x20000000,		///< Event : ADEC DSP0 Codec Error  info.
	LX_ADEC_EVENT_DEC1_DEBUG			= 0x40000000,		///< Event : ADEC DSP1 Codec Error  info.

/* 16 ~ 30 bit : DSP1 Interrupt is defined. */
	LX_ADEC_EVENT_DSP1_INFO				= 0x00010000,		///< Event : ADEC DSP1 decoder has info.
	LX_ADEC_EVENT_DSP1_ERROR			= 0x00020000,		///< Event : ADEC DSP1 decoder has error.

	LX_ADEC_EVENT_PRESENT_START			= 0x00040000,		///< Event : Audio DSP1 Presentation starts.
	LX_ADEC_EVENT_PRESENT_STOP			= 0x00080000,		///< Event : Audio DSP1 Presentation stops.
	LX_ADEC_EVENT_PRESENT_PAUSE			= 0x00100000,		///< Event : Audio DSP1 Presentation pauses.
	LX_ADEC_EVENT_PRESENT_END			= 0x00200000,		///< Event : Audio DSP1 Presentation ends.

	LX_ADEC_EVENT_DEC0_UNDERFLOW		= 0x00400000,		///< Event : Decoder0 Mix Buffer is underflow.
	LX_ADEC_EVENT_DEC1_UNDERFLOW		= 0x00800000,		///< Event : Decoder1 Mix Buffer is underflow.

	LX_ADEC_EVENT_CLIP0_UNMASK_ALL		= 0x007C0032,		///< Event : ADEC Clip0 default Event for un-mask.
	LX_ADEC_EVENT_CLIP1_UNMASK_ALL		= 0x00BC3200,		///< Event : ADEC Clip1 default Event for un-mask.
	LX_ADEC_EVENT_CLIP_UNMASK_ALL		= 0x00FC3232,		///< Event : ADEC Clip default Event for un-mask.

	LX_ADEC_EVENT_DSP_RESET_DONE 		= 0x01000000,		///< Event : DSP0 / 1  codec reset is done to restart emp play..
	LX_ADEC_EVENT_PRSENT_NOTI			= 0x02000000,		///< Event : ADEC DSP1 Presentation Notification.
	LX_ADEC_EVENT_SET_PCM_RATE			= 0x04000000,		///< Event : ADEC Set D-AMP PCM Rate.
	LX_ADEC_EVENT_DSP1_CLOCK_RESET		= 0x08000000,		///< Event : ADEC DSP1 has requested I2S and SPDIF clock H/W reset.

	LX_ADEC_EVENT_DSP1_LIPSYNC_INFO		= 0x10000000,		///< Event : ADEC DSP1 libsync info.
	LX_ADEC_EVENT_USE_GSTC				= 0x20000000,		///< Event : ADEC Use GSTC.
	LX_ADEC_EVENT_SET_DTO_RATE			= 0x40000000,		///< Event : ADEC Set SPDIF DTO Rate.
	LX_ADEC_EVENT_CALLED_KDRV_CLOSE 	= 0x80000000,		///< Event : KDRV close funtion is called by abnormal system operation.

	LX_ADEC_EVENT_DSP1_UNMASK_ALL		= 0x00FC0000,		///< Event : ADEC DSP1's default Event for un-mask.

	/* 31 bit : DSP0 / DSP1 Interrupt is defined. */
	LX_ADEC_EVENT_CODEC_DOWNLOAD_DONE 	= 0x80000000		///< Event : DSP0 / 1  codec download is done.
} LX_ADEC_EVENT_TYPE_T;

#define	LX_ADEC_EVENT_INPUT_DEBUG		0x01F00000			///< Debug : ADEC DSP0 interrupt print.
#define	LX_ADEC_EVENT_DSP0_DEBUG		0x61000000			///< Debug : ADEC DSP0/lipsync interrupt print.
#define LX_ADEC_EVENT_LIPSYNC_CHECK 	0x10000000			///< Debug : ADEC DSP1 lipsync check task debug print.


/**
 * ADEC Source Input Type.
 * TP, PCM, and SPDIF.
 *
 */
typedef  enum
{
	LX_ADEC_IN_PORT_NONE	=  0,	///< No Input
	LX_ADEC_IN_PORT_TP		=  1,	///< From TPA Stream Input
	LX_ADEC_IN_PORT_SPDIF 	=  2,	///< From SERIAL INTERFACE 0
	LX_ADEC_IN_PORT_SIF		=  3,	///< From Analog Front End(SIF)
	LX_ADEC_IN_PORT_ADC		=  4,	///< Fron ADC Input
	LX_ADEC_IN_PORT_HDMI	=  5,	///< From HDMI
	LX_ADEC_IN_PORT_I2S		=  6,	///< From I2S
	LX_ADEC_IN_PORT_SYSTEM	=  7,	///< From System Memory
	LX_ADEC_IN_PORT_MIC		=  8,	///< From MIC Input
	LX_ADEC_IN_PORT_MIRROR 	=  9,	// Same with Main Source for 2nd TV Encoder
} LX_ADEC_IN_PORT_T;

/**
 * ADEC Source Format Type.
 * Audio Source type is defined.
 *
 */
typedef  enum
{
	LX_ADEC_SRC_TYPE_UNKNOWN       = 0,		///< Unknown
	LX_ADEC_SRC_TYPE_PCM           = 1,		///< PCM
	LX_ADEC_SRC_TYPE_AC3           = 2,		///< AC3(Dolby Digital)
	LX_ADEC_SRC_TYPE_EAC3          = 3,		///< Enhanced AC3(Dolby Digital Plus)
	LX_ADEC_SRC_TYPE_MPEG          = 4,		///< MPEG
	LX_ADEC_SRC_TYPE_AAC           = 5,		///< AAC
	LX_ADEC_SRC_TYPE_HEAAC         = 6,		///< HEAAC
	LX_ADEC_SRC_TYPE_DRA           = 7,		///< DRA
	LX_ADEC_SRC_TYPE_MP3           = 8,		///< MP3
	LX_ADEC_SRC_TYPE_DTS           = 9,		///< DTS
	LX_ADEC_SRC_TYPE_SIF           = 10,	///< SIF, PCM
	LX_ADEC_SRC_TYPE_SIF_BTSC      = 11, 	///< SIF(BTSC), PCM, PCM
	LX_ADEC_SRC_TYPE_SIF_A2        = 12,	///< SIF(A2), PCM
	LX_ADEC_SRC_TYPE_DEFAULT       = 13,	///< DEFAULT
	LX_ADEC_SRC_TYPE_NONE 	       = 14, 	///< NONE
	LX_ADEC_SRC_TYPE_MULTI 	       = 15, 	///< PCM, AC3, AAC, MPEG support(KDRV only used.)

	LX_ADEC_SRC_TYPE_WMA_PRO       = 20,	///< WMA, WMA_PRO
	LX_ADEC_SRC_TYPE_ADPCM	       = 21,	///< ADPCM
	LX_ADEC_SRC_TYPE_VORBIS        = 22,	///< VORBIS
	LX_ADEC_SRC_TYPE_AMR_NB        = 23,	///< AMR NB
	LX_ADEC_SRC_TYPE_AMR_WB        = 24,	///< AMR WB
	LX_ADEC_SRC_TYPE_RA10		   = 25,	///< RA10
	LX_ADEC_SRC_TYPE_AAC_LC        = 26,	///< AAC LC
	LX_ADEC_SRC_TYPE_AAC_LC_ENC    = 27,	///< AAC LC ENC
	LX_ADEC_SRC_TYPE_MS10_DDCO	   = 28,	///< MS10 DDCO

} LX_ADEC_SRC_TYPE_T;


/**
 * ADEC Audio Sample Frequency.
 * Sample frequency values merged from HDMI Audio InfoFrame and Audio Channel Status.
 * Also, this enumeration describes the sampling rate for ADEC driver.
 * If this value is changed, LX_HDMI_SAMPLING_FREQ_T is also changed in HDMI kernel driver.
 */
typedef enum
{
	LX_ADEC_SAMPLING_FREQ_NONE		= 0,		///< None
	LX_ADEC_SAMPLING_FREQ_4_KHZ		= 4,		///< 4 Kbps
	LX_ADEC_SAMPLING_FREQ_8_KHZ		= 8,		///< 8 Kbps
	LX_ADEC_SAMPLING_FREQ_11_025KHZ	= 11,		///< 11.025 Kbps
	LX_ADEC_SAMPLING_FREQ_12_KHZ	= 12,		///< 12 kbps
	LX_ADEC_SAMPLING_FREQ_16_KHZ	= 16,		///< 16 Kbps
	LX_ADEC_SAMPLING_FREQ_22_05KHZ	= 22,		///< 22.05 Kbps
	LX_ADEC_SAMPLING_FREQ_24_KHZ	= 24,		///< 24 Kbps
	LX_ADEC_SAMPLING_FREQ_32_KHZ	= 32,		///< 32 Kbps
	LX_ADEC_SAMPLING_FREQ_44_1KHZ	= 44,		///< 44.1 Kbps
	LX_ADEC_SAMPLING_FREQ_48_KHZ	= 48,		///< 48 Kbps
	LX_ADEC_SAMPLING_FREQ_64_KHZ	= 64,		///< 64 Kbps
	LX_ADEC_SAMPLING_FREQ_88_2KHZ	= 88,		///< 88.2 Kbps
	LX_ADEC_SAMPLING_FREQ_96_KHZ	= 96,		///< 96 Kbps
	LX_ADEC_SAMPLING_FREQ_128_KHZ 	= 128,		///< 128 Kbps
	LX_ADEC_SAMPLING_FREQ_176_4KHZ	= 176,		///< 176.4 Kbps
	LX_ADEC_SAMPLING_FREQ_192_KHZ	= 192,		///< 192 Kbps
	LX_ADEC_SAMPLING_FREQ_768_KHZ	= 768,		///< 768 Kbps
	LX_ADEC_SAMPLING_FREQ_DEFAULT	= 999		///< default
} LX_ADEC_SAMPLING_FREQ_T;

/**
 * ADEC Decoder Set Mode
 * This enumeration describes the ADEC decoder set mode.
 *
*/
typedef enum
{
	LX_ADEC_DECODER_MODE_NONE 	= 0x0,	///< Decoder Mode None
	LX_ADEC_DOLBY_DRC_MODE	 	= 0x1,	///< Dolby DRC Mode
	LX_ADEC_DOWNMIX_MODE 		= 0x2,	///< Downmix Mode
} LX_ADEC_DECODER_SET_T;

/**
 * ADEC Dolby DRC Mode
 * This enumeration describes the ADEC Dolby DRC mode.
 *
*/
typedef enum
{
	LX_ADEC_DOLBY_LINE_MODE	 	= 0,	///< Dolby Line Mode
	LX_ADEC_DOLBY_RF_MODE 		= 1,	///< Dolby Line Mode
	LX_ADEC_DOLBY_DRC_OFF 		= 2,	///< Dolby DRC Off Mode
} LX_ADEC_DRC_MODE_T;

/**
 * ADEC DownmixMode
 * This enumeration describes the ADEC Downmix mode.
 *
*/
typedef enum
{
	LX_ADEC_LORO_MODE	 	= 0,	///< LoRo Mode
	LX_ADEC_LTRT_MODE 		= 1,	///< LtRt  Mode
} LX_ADEC_DOWNMIX_MODE_T;

/**
 * ADEC Audio Dual-mono Mode
 * This enumeration describes the ADEC audio mode.
 *
*/
typedef enum
{
	LX_ADEC_AUDIO_MODE_MONO	 			= 0,	///< Mono
	LX_ADEC_AUDIO_MODE_JOINT_STEREO 	= 1,	///< Joint Stereo
	LX_ADEC_AUDIO_MODE_STEREO		 	= 2,	///< Stereo
	LX_ADEC_AUDIO_MODE_DUAL_MONO 		= 3,	///< Dual Mono
	LX_ADEC_AUDIO_MODE_MULTI			= 4,	///< Multi
	LX_ADEC_AUDIO_MODE_UNKNOWN			= 5		///< Unknown
} LX_ADEC_AUDIO_MODE_T;

/**
 * Audio Speaker Output Mode
 * Audio speaker output mode is defined.
 *
 */
typedef enum
{
	LX_ADEC_SPK_MODE_LR		= 0,		///< LR
	LX_ADEC_SPK_MODE_LL		= 1,		///< LL
	LX_ADEC_SPK_MODE_RR		= 2,		///< RR
	LX_ADEC_SPK_MODE_MIX	= 3			///< Mix
} LX_ADEC_SPK_OUTPUT_MODE_T;

/**
 * Audio Output Port Number.
 * Audio output port number is defined.
 *
 */
typedef enum
{
	LX_ADEC_OUTPUT_NONE	= 0x00,		///< None
	LX_ADEC_OUTPUT_DAC0	= 0X01,		///< DAC Output 0(SCART)
	LX_ADEC_OUTPUT_DAC1	= 0X02,		///< DAC Output 1(Line Out)
	LX_ADEC_OUTPUT_DAC2	= 0X04,		///< DAC Output 2(HeadPhone)
	LX_ADEC_OUTPUT_DAC3	= 0X08,		///< DAC Output 3
	LX_ADEC_OUTPUT_I2S0	= 0X10,		///< I2S Output 0(AMP)
	LX_ADEC_OUTPUT_I2S1	= 0X20,		///< I2S Output 1(SCART)
	LX_ADEC_OUTPUT_I2S2	= 0X40,		///< I2S Output 2(Line Out)
	LX_ADEC_OUTPUT_I2S3	= 0X80,		///< I2S Output 3(HeadPhone) for Gain
	LX_ADEC_OUTPUT_ALL	= 0XFF		///< ALL Output Port
} LX_ADEC_OUTPUT_PORT_T;

/**
 * Audio DAC control mode for volume and mute control.
 * Audio DAC control mode is defined.
 *
 */
typedef enum
{
	LX_ADEC_DAC_NONE		= 0x00,		///< None
	LX_ADEC_DAC_DSP			= 0x01,		///< DAC Control by DSP
	LX_ADEC_DAC_MIXEDIP		= 0x02,		///< DAC Control by Mixed IP
	LX_ADEC_DAC_ALL			= 0x03,		///< DAC Control by DSP & Mixed IP
	LX_ADEC_DAC_SCART		= 0x04,		///< SCART Volume Control by Mixed IP(12 bB boost for NICAM)
	LX_ADEC_DAC_SCART_RESET	= 0x08,		///< SCART Reset Control by Mixed IP

	LX_ADEC_DAMP_FOR_GCD	= 0x10,		///< D-AMP Contol for GCD volume contol
} LX_ADEC_DAC_MODE_T;

/**
 * ADEC SE(Sound Engine) FN(FuNction) Mode Type
 * Audio SE(Sound Engine) FN(FuNction) Mode is defined.
 *
 */
typedef enum
{
	LX_ADEC_SE_FN_MODE_FN000		= 0, 	///< FN(FuNction) mode 000
	LX_ADEC_SE_FN_MODE_FN001		= 1, 	///< FN(FuNction) mode 001
	LX_ADEC_SE_FN_MODE_FN002		= 2, 	///< FN(FuNction) mode 002
	LX_ADEC_SE_FN_MODE_FN003		= 3, 	///< FN(FuNction) mode 003
	LX_ADEC_SE_FN_MODE_FN004_MODE1	= 4, 	///< FN(FuNction) mode 004(Sub Mode1)
	LX_ADEC_SE_FN_MODE_FN004_MODE2	= 5, 	///< FN(FuNction) mode 004(Sub Mode2)
	LX_ADEC_SE_FN_MODE_FN004_MODE3	= 6, 	///< FN(FuNction) mode 004(Sub Mode3)
	LX_ADEC_SE_FN_MODE_FN005		= 7, 	///< FN(FuNction) mode 005
	LX_ADEC_SE_FN_MODE_FN006		= 8, 	///< FN(FuNction) mode 006
	LX_ADEC_SE_FN_MODE_FN007		= 9, 	///< FN(FuNction) mode 007
	LX_ADEC_SE_FN_MODE_FN008		= 10, 	///< FN(FuNction) mode 008
	LX_ADEC_SE_FN_MODE_FN009		= 11, 	///< FN(FuNction) mode 009
	LX_ADEC_SE_FN_MODE_FN010		= 12, 	///< FN(FuNction) mode 010
	LX_ADEC_SE_FN_MODE_SET			= 20, 	///< FN(FuNction) mode set(Function Control)
	LX_ADEC_SE_FN_MODE_UPDTAE_PARAM	= 30 	///< FN(FuNction) mode set(Update parameters after dsp auto reset)
} LX_ADEC_SE_FN_MODE_T;

/**
 * ADEC SE(Sound Engine) Parameter Setting Type
 * Audio SE(Sound Engine) Parameter Setting Type is defined.
 *
 */
typedef enum
{
	LX_ADEC_SE_INIT_ONLY 	= 0, 	///< init only" parameter will be written
	LX_ADEC_SE_VARIABLES 	= 1, 	///< "variables" will be writen
	LX_ADEC_SE_ALL			= 2  	///< "init only" and "variables" will be written simultaneously
} LX_ADEC_SE_DATA_MODE_T;

/**
 * ADEC SE(Sound Engine) FN004 Mode Variable Type
 * Audio SE(Sound Engine) FN004 Mode Variable Type is defined.
 *
 */
typedef enum
{
	LX_ADEC_SE_MODE_VARIABLES0		= 0, 	///< "VARIABLES_00" will be written
	LX_ADEC_SE_MODE_VARIABLES1		= 1, 	///< "VARIABLES_01" will be written
	LX_ADEC_SE_MODE_VARIABLES2		= 2,	///< "VARIABLES_02" will be written
	LX_ADEC_SE_MODE_VARIABLES3		= 3, 	///< "VARIABLES_03" will be written
	LX_ADEC_SE_MODE_VARIABLES4		= 4, 	///< "VARIABLES_04" will be written
	LX_ADEC_SE_MODE_VARIABLESALL 	= 5  	///< All "VARIABLES" will be written simultaneously. Data will be arranged from 0 to 4.
} LX_ADEC_SE_VAR_MODE_T;

/**
 * ADEC SE(Sound Engine) Parameter Access Type
 * Audio SE(Sound Engine) Parameter Access is defined.
 *
 */
typedef enum
{
	LX_ADEC_SE_WRITE	= 0, 	///< "pParams" data will be written to DSP
	LX_ADEC_SE_READ		= 1 	///< "pParams" data will be read from DSP to CPU
} LX_ADEC_SE_DATA_ACCESS_T;

/**
 * ADEC SPDIF Type.
 * SPDIF type is defined.
 *
 */
typedef  enum
{
	LX_ADEC_SPDIF_NONE			= 0,		///< NONE
	LX_ADEC_SPDIF_PCM			= 1,		///< PCM type
	LX_ADEC_SPDIF_AC3			= 2,		///< AC3 type
	LX_ADEC_SPDIF_MP1			= 3,		///< MP1 type
	LX_ADEC_SPDIF_MP2			= 4,		///< MP2 type
	LX_ADEC_SPDIF_MP3			= 5,		///< MP3 type
	LX_ADEC_SPDIF_AAC			= 6,		///< AAC type
	LX_ADEC_SPDIF_DTS			= 7,		///< DTS type
	LX_ADEC_SPDIF_DDCO			= 8			///< DDCO type
} LX_ADEC_SPDIF_MODE_T;

/**
 * ADEC SPDIF SCMS(Serial Copy Management System) Type.
 * SPDIF SCMS type is defined.
 *
 */
typedef  enum
{
	LX_ADEC_SPDIF_COPY_FREE		= 0,		///< COPY FREE
	LX_ADEC_SPDIF_COPY_NO_MORE	= 1,		///< COPY NO MORE
	LX_ADEC_SPDIF_COPY_ONCE		= 2,		///< COPY ONCE
	LX_ADEC_SPDIF_COPY_NEVER	= 3,		///< COPY NEVER
	LX_ADEC_SPDIF_COPY_DEFAULT	= 4			///< Default
} LX_ADEC_SPDIF_SCMS_T;


/**
 * ADEC DVR Trick Mode Type.
 * ADEC DVR trick mode type is defined.
 *
 */
typedef  enum
{
	LX_ADEC_TRICK_FORCED_STOP_OFF		= 0,	///< forceStopped : OFF
	LX_ADEC_TRICK_FORCED_STOP_ON		= 1,	///< forceStopped : ON
	LX_ADEC_TRICK_MUTE_OFF				= 2,	///< muted : OFF during Trick Play
	LX_ADEC_TRICK_MUTE_ON				= 3,	///< muted : ON during Trick Play
	LX_ADEC_TRICK_TSM_DISABLED			= 4, 	///< TSM(Time Stamp Managed) : Disabled
	LX_ADEC_TRICK_TSM_ENABLED			= 5, 	///< TSM(Time Stamp Managed) : Enabled
	LX_ADEC_TRICK_PAUSE					= 6, 	///< rate : 0 - Pause
	LX_ADEC_TRICK_NORMAL_PLAY			= 7, 	///< rate : NORMAL_DECODE_RATE - Normal Play
	LX_ADEC_TRICK_FAST_FOWARD_1P2X		= 8, 	///< rate : NORMAL_DECODE_RATE x 1.2  - 1.2 speed Play
	LX_ADEC_TRICK_FAST_FOWARD_1P5X		= 9, 	///< rate : NORMAL_DECODE_RATE x 1.5  - 1.5 speed Play
	LX_ADEC_TRICK_FAST_FOWARD_2X		= 10, 	///< rate : NORMAL_DECODE_RATE x 2.0  - 2.0 speed Play
	LX_ADEC_TRICK_SLOW_MOTION_0P8X		= 11, 	///< rate : NORMAL_DECODE_RATE / 1.25 - 0.8 speed Play
	LX_ADEC_TRICK_SLOW_MOTION_0P5X		= 12	///< rate : NORMAL_DECODE_RATE / 2.0  - 0.5 speed Play
} LX_ADEC_TRICK_MODE_T ;

/**
 * ADEC Clip Play Mode Type.
 *
 */
typedef enum
{
	LX_ADEC_CLIP_MODE_NONE		= 0,		///< None
	LX_ADEC_CLIP_MODE_LOAD		= 1,		///< Load
	LX_ADEC_CLIP_MODE_PLAY		= 2,		///< Play
	LX_ADEC_CLIP_MODE_STOP		= 3,		///< Stop
	LX_ADEC_CLIP_MODE_PAUSE		= 4,		///< Pause
	LX_ADEC_CLIP_MODE_RESUME	= 5,		///< Resume
	LX_ADEC_CLIP_MODE_FLUSH		= 6,		///< Flush
	LX_ADEC_CLIP_MODE_RESET		= 7			///< Reset
} LX_ADEC_CLIP_MODE_T;

/**
 * ADEC Clock Control Mode Type.
 *
 */
typedef enum
{
	LX_ADEC_CTRL_MODE_NONE		= 0,	///< None
	LX_ADEC_CTRL_SET_TIME		= 1,	///< Set base time by clockBaseTime and streamBaseTime.
	LX_ADEC_CTRL_PLAY			= 2,	///< Play(Start Presenting)
	LX_ADEC_CTRL_PAUSE			= 3		///< Pause(Stop Presenting)
} LX_ADEC_CTRL_MODE_T;

/**
 * ADEC Decoder and Mix Mode for Audio Clip Play.
 * This enumeration describes the ADEC decoder and mix for playing audio clip.
 *
 */
typedef  enum
{
	LX_ADEC_DEC_MODE_NONE	= 0x00,		///< None

	LX_ADEC_DECODE_MAIN		= 0x01,		///< Main Audio Decoding, PESM, CPBM buffer is used.
	LX_ADEC_DECODE_ASSO		= 0x02,		///< Associate Audio Decoding, PESA, CPBA buffer is used.

	LX_ADEC_MIX_BUF0		= 0x10,		///< PCM Audio Mix in PCM Buffer0
	LX_ADEC_MIX_BUF1		= 0x20,		///< PCM Audio Mix in PCM Buffer1
	LX_ADEC_MIX_BUF2		= 0x40,		///< PCM Audio Mix in PCM Buffer2
	LX_ADEC_MIX_BUF3		= 0x80,		///< PCM Audio Mix in PCM Buffer3

	LX_ADEC_PCM_CAPTURE		= 0x100		///< PCM Audio Capture Device
} LX_ADEC_DEC_MODE_T;

/**
 * ADEC Clip Buffer Status for Audio Clip Play.
 * This enumeration describes the ADEC clip buffer status for playing audio clip.
 *
 */
typedef  enum
{
	LX_ADEC_CLIP_BUF_NONE		= 0,	///< None
	LX_ADEC_CLIP_BUF_START		= 1,	///< Start
	LX_ADEC_CLIP_BUF_MIDDLE		= 2,	///< Middle
	LX_ADEC_CLIP_BUF_END		= 3		///< End
} LX_ADEC_CLIP_BUF_T;


/**
 * ADEC AAC CODEC Type.
 * Audio AAC CODEC type is defined.
 *
 */
typedef  enum
{
	LX_AAC_CODEC_TYPE_NOT_DEF		= 0,	///< Not defined codec
	LX_AAC_CODEC_TYPE_AAC			= 1,	///< AAC codec
	LX_AAC_CODEC_TYPE_HE_AAC		= 2,	///< HE-AAC V.1 codec
	LX_AAC_CODEC_TYPE_HE_AAC_V2		= 3		///< HE-AAC V.2 codec
} LX_ADEC_AAC_CODEC_TYPE_T;

/**
 * ADEC AAC Format Type.
 * Audio AAC Format type is defined.
 *
 */
typedef  enum
{
	LX_ADEC_AAC_FORMAT_TYPE_RAW		= 0,	///< RAW format
	LX_ADEC_AAC_FORMAT_TYPE_ADTS    = 1,	///< ADTS format
	LX_ADEC_AAC_FORMAT_TYPE_ADIF	= 2,	///< ADIF format
	LX_ADEC_AAC_FORMAT_TYPE_LOAS    = 3,	///< LOAS format
	LX_ADEC_AAC_FORMAT_TYPE_LATM    = 4		///< LATM format
} LX_ADEC_AAC_FORMAT_TYPE_T;

/**
 * ADEC ADPCM CODEC Type.
 * Audio ADPCM CODEC type is defined.
 *
 */
typedef  enum
{
	LX_ADPCM_CODEC_TYPE_NONE			= 0,	///< Not defined codec
	LX_ADPCM_CODEC_TYPE_IMA_QT			= 1,	///< ADPCM IMA QT codec
	LX_ADPCM_CODEC_TYPE_IMA_WAV			= 2,	///< ADPCM IMA WAV codec
	LX_ADPCM_CODEC_TYPE_IMA_DK3			= 3,	///< ADPCM IMA DK3 codec
	LX_ADPCM_CODEC_TYPE_IMA_DK4			= 4,	///< ADPCM IMA DK4 codec
	LX_ADPCM_CODEC_TYPE_IMA_WS			= 5,	///< ADPCM IMA WS codec
	LX_ADPCM_CODEC_TYPE_IMA_SMJPEG		= 6,	///< ADPCM IMA SMJPEG codec
	LX_ADPCM_CODEC_TYPE_MS				= 7,	///< ADPCM MS codec
	LX_ADPCM_CODEC_TYPE_4XM				= 8,	///< ADPCM 4XM codec
	LX_ADPCM_CODEC_TYPE_XA				= 9,	///< ADPCM XA codec
	LX_ADPCM_CODEC_TYPE_ADX				= 10,	///< ADPCM ADX codec
	LX_ADPCM_CODEC_TYPE_EA				= 11,	///< ADPCM EA codec
	LX_ADPCM_CODEC_TYPE_G726			= 12,	///< ADPCM G726 codec
	LX_ADPCM_CODEC_TYPE_CT				= 13,	///< ADPCM CT codec
	LX_ADPCM_CODEC_TYPE_SWF				= 14,	///< ADPCM SWF codec
	LX_ADPCM_CODEC_TYPE_YAMAHA       	= 15,	///< ADPCM YAMAHA codec
	LX_ADPCM_CODEC_TYPE_SBPRO_4      	= 16,	///< ADPCM SBPRO_4 codec
	LX_ADPCM_CODEC_TYPE_SBPRO_3      	= 17,	///< ADPCM SBPRO_3 codec
	LX_ADPCM_CODEC_TYPE_SBPRO_2      	= 18,	///< ADPCM SBPRO_2 codec
	LX_ADPCM_CODEC_TYPE_THP          	= 19,	///< ADPCM THP codec
	LX_ADPCM_CODEC_TYPE_IMA_AMV      	= 20,	///< ADPCM IMA_AMV codec
	LX_ADPCM_CODEC_TYPE_EA_R1        	= 21,	///< ADPCM EA_R1 codec
	LX_ADPCM_CODEC_TYPE_EA_R3        	= 22,	///< ADPCM EA_R3 codec
	LX_ADPCM_CODEC_TYPE_EA_R2        	= 23,	///< ADPCM EA_R2 codec
	LX_ADPCM_CODEC_TYPE_IMA_EA_SEAD  	= 24,	///< ADPCM IMA_EA_SEAD codec
	LX_ADPCM_CODEC_TYPE_IMA_EA_EACS  	= 25,	///< ADPCM IMA_EA_EACS codec
	LX_ADPCM_CODEC_TYPE_EA_XAS       	= 26,	///< ADPCM EA_XAS codec
	LX_ADPCM_CODEC_TYPE_EA_MAXIS_XA  	= 27,	///< ADPCM EA_MAXIS_XA codec
	LX_ADPCM_CODEC_TYPE_IMA_ISS      	= 28,	///< ADPCM IMA_ISS codec
	LX_ADPCM_CODEC_TYPE_G722          	= 29	///< ADPCM G722 codec
} LX_ADEC_ADPCM_TYPE_T;

/**
 * ADEC Callback Status for Audio Clip Play.
 * This enumeration describes the ADEC callback status for playing audio clip.
 *
 */
typedef  enum
{
	LX_ADEC_CLIP_NONE_MSG	= 0,	///< None
	LX_ADEC_CLIP_START		= 1,	///< Start
	LX_ADEC_CLIP_STOP		= 2,	///< Stop
	LX_ADEC_CLIP_PAUSE		= 2,	///< Pause
	LX_ADEC_CLIP_OVERFLOW	= 4,	///< Overflow
	LX_ADEC_CLIP_UNDERFLOW	= 5,	///< Underflow
	LX_ADEC_CLIP_DECODED    = 6,	///< 1 index frame is decoded.
	LX_ADEC_CLIP_LIPSYNC	= 7,	///< Lipsync Check.
	LX_ADEC_CLIP_ERROR		= 8,	///< Decoding Error.
	LX_ADEC_CLIP_NOTIFY		= 9,	///< Notify(Request clip data for next playing)
	LX_ADEC_CLIP_DSP_RESET	= 10	///< Notify to app. after DSP Reset(Request clip playing again)
} LX_ADEC_CLIP_MESSAGE_T;

/**
 * ADEC REG(Register) Mode.
 * This enumeration describes the ADEC REG mode to read and write.
 *
 */
typedef  enum
{
	LX_ADEC_REG_READ		 = 0,		///< Read
	LX_ADEC_REG_WRITE		 = 1,		///< Write
	LX_ADEC_REG_WRNRD		 = 2,		///< Write and Read
	LX_ADEC_REG_READ_ARRAY	 = 3,		///< Read a set of register
	LX_ADEC_REG_READ_ALL	 = 4,		///< Read a full register
	LX_ADEC_REG_GET_MAX_ADDR = 5,		///< Get a max address for ADEC
	LX_ADEC_REG_READ_DSP1_PC = 6,		///< Read DSP1 PC callstack trace
	LX_ADEC_REG_READ_DESC	 = 7,		///< Read Register with description

	LX_CTOP_REG_READ		 = 10,		///< Read(CTOP CTRL REG)
	LX_CTOP_REG_WRITE		 = 11,		///< Write(CTOP CTRL REG)
	LX_CTOP_REG_WRNRD		 = 12,		///< Write and Read(CTOP CTRL REG)
	LX_CTOP_REG_READ_ARRAY	 = 13,		///< Read a set of register (CTOP CTRL REG)
	LX_CTOP_REG_READ_ALL	 = 14,		///< Read a full register (CTOP CTRL REG)
	LX_CTOP_REG_GET_MAX_ADDR = 15,		///< Get a max address for CTOP
	LX_CTOP_REG_SET_CPU_JTAG = 16,		///< Set a ADEC DSP JTAG for CPU Port
	LX_CTOP_REG_SET_PER_JTAG = 17,		///< Set a ADEC DSP JTAG for PERiperal Port
	LX_CTOP_REG_SET_CPU_UART = 18,		///< Set a ADEC DSP UART for CPU Port(UART0)
	LX_CTOP_REG_SET_PER_UART = 19,		///< Set a ADEC DSP UART for PERiperal Port(UART1)

	LX_ANALOG_REG_READ		 = 20,		///< Read(ANALOG REG)
	LX_ANALOG_REG_WRITE		 = 21,		///< Write(ANALOG REG)
	LX_ANALOG_REG_WRNRD		 = 22,		///< Write and Read(ANALOG REG)
	LX_ANALOG_REG_READ_ARRAY = 23		///< Read a set of register (ANALOG REG)
} LX_ADEC_REG_MODE_T;

/**
 * ADEC Get Event Info.
 * Get a event info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_EVENT
 *
*/
typedef struct LX_ADEC_EVENT_INFO
{
	LX_ADEC_DEC_MODE_T		adecMode;	///< The mode of ADEC decoder

	LX_ADEC_EVENT_TYPE_T 	eventID;	///< ADEC Event ID Type.
	LX_ADEC_DEC_MODE_T		eventMode;	///< The Event Mode according to ADEC Event ID Type
} LX_ADEC_EVENT_INFO_T;

/**
 * ADEC Buffer Info.
 * Define a ADEC Buffer Info.
 *
*/
typedef struct LX_ADEC_BUF_INFO
{
	LX_ADEC_DEC_MODE_T		adecMode;	///< The mode of ADEC decoder

	UINT32		maxMemSize;				///< The free size of memory for current buffer
	UINT32		freeMemSize;			///< The free size of memory for current buffer
	UINT32		maxAuiSize;				///< The free size of AUI(Access Unit Index) for current buffer
	UINT32		freeAuiSize;			///< The free size of AUI(Access Unit Index) for current buffer

	UINT32		currentIndex;			///< The current decoding(decoder) or present(mixer) index for current buffer
	UINT64		timestamp;				///< The current decoding(decoder) or present(mixer) timestamp of the buffer in unit of nono-seconds

	UINT32		currentIndexPresent;	///< The current present(decoder) index for current buffer
	UINT64		timestampPresent;		///< The current present(decoder) timestamp of the buffer in unit of nono-seconds
} LX_ADEC_BUF_INFO_T;



/**
 * AUI info structure
 * Get a AUI info struct
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_DECODING_INFO
 *
*/
typedef struct
{
	UINT64					timestamp;		///< The timestamp of the buffer in unit of nono-seconds
	UINT64					dtsGstc;		///< The DTS(Decoding Time Stamp) value of the GSTC HW clock matching timestamp
}LX_ADEC_AUI_T;


/**
 * ADEC Get Decoding Info.
 * Get a Decoding info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_DECODING_INFO
 *
*/
typedef struct LX_ADEC_DEC_INFO
{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder used by

	LX_ADEC_IN_PORT_T 		adecSource;		///< ADEC Source Input Type.
	LX_ADEC_SRC_TYPE_T		adecType;		///< Audio Source Type
	BOOLEAN					spdifPcm;		///< Audio SPDIF PCM Output

	UINT8					decodedCount;	/// < The count of decoded AUI index
	LX_ADEC_AUI_T 			decInfo[MAX_TRANSFER_NUM_OF_INDEX];	/// < The info of AUI index
} LX_ADEC_DEC_INFO_T;

/**
 * ADEC Set Source Params
 * Set Source Parameters(Source, Port Number and Type).
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_SOURCE
 *
*/
typedef struct LX_ADEC_SET_SOURCE
{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder used by

	LX_ADEC_IN_PORT_T 		adecSource;		///< ADEC Source Input Type.
	UINT8			 		portNum;		///< The physical number of ADC Port for ADEC.(0 ~ 6)
	LX_ADEC_SRC_TYPE_T		adecType;		///< Audio Source Type
	LX_ADEC_SAMPLING_FREQ_T	samplingFreq;	///< Sampling Frequency for HDMI PCM Input
} LX_ADEC_SET_SOURCE_T;

/**
 * ADEC Audio Decoder Mode Info.
 * This enumeration describes the ADEC decoder mode information.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_DECODER_MODE
*/
typedef struct LX_ADEC_DECODER_MODE{
	LX_ADEC_DEC_MODE_T			adecMode;		///< The mode of ADEC decoder

	LX_ADEC_DECODER_SET_T		setMode;		///< The decoder set mode of ADEC decoder
	LX_ADEC_DRC_MODE_T			drcMode;		///< AC-3, AAC DRC Mode.
	LX_ADEC_DOWNMIX_MODE_T		downmixMode; 	///< AC-3, AAC Downmix Mode..
} LX_ADEC_DECODER_MODE_T;

/**
 * ADEC Audio Decoding Start Info.
 * This enumeration describes the ADEC decoding start information.
 * adec ioctl parameter.
 * @see ADEC_IOW_START_DECODING
*/
typedef struct LX_ADEC_START_DEC{
	LX_ADEC_DEC_MODE_T		adecMode;			///< The mode of ADEC decoder

	LX_ADEC_SRC_TYPE_T		adecType;			///< Audio Source Codec Type
	BOOLEAN					bPcrExist; 			///< PCR Existence flag to play MHP stream that has no PCR value.
	BOOLEAN					bAdExist; 			///< AD(Audio Description) Exist flag to start main and AD decoding at the same time..
} LX_ADEC_START_DEC_T;

/**
 * ADEC Audio Decoding Stop Info.
 * This enumeration describes the ADEC decoding stop information.
 * adec ioctl parameter.
 * @see ADEC_IOW_STOP_DECODING
*/
typedef struct LX_ADEC_STOP_DEC{
	LX_ADEC_DEC_MODE_T		adecMode;			///< The mode of ADEC decoder

//	LX_ADEC_SRC_TYPE_T		adecType;			///< Audio Source Codec Type
//	BOOLEAN					bPcrExist; 		///< PCR Existence flag to play MHP stream that has no PCR value.
} LX_ADEC_STOP_DEC_T;

/**
 * ADEC Audio ES Exist Information.
 * This enumeration describes the ADEC Audio ES Existence Information..
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ES_EXISTENCE
*/
typedef struct LX_ADEC_ES_EXIST{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder

	BOOLEAN 				bEsExist;		///< The ES Existence info.
} LX_ADEC_ES_EXIST_T;

/**
 * ADEC Audio Decoder Output Mode.
 * This enumeration describes the ADEC Audio Decoder Output Mode.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_SPK_OUT_MODE
*/
typedef struct LX_ADEC_OUTPUT_MODE{
	LX_ADEC_DEC_MODE_T			adecMode;	///< The mode of ADEC decoder

	LX_ADEC_SPK_OUTPUT_MODE_T 	outputMode;	///< The Audio Decoder Output Mode.
} LX_ADEC_OUTPUT_MODE_T;

/**
 * ADEC Audio Lip Sync Info.
 * This enumeration describes the ADEC Audio Lip Sync information.
 * adec ioctl parameter.
 * @see ADEC_IOW_ENABLE_AV_LIPSYNC
*/
typedef struct LX_ADEC_SYNC{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder

	BOOLEAN 				bOnOff;			///< The Lipsync mechanism on or off.
} LX_ADEC_SYNC_T;


/**
 * ADEC HE-AAC ES Info
 * This structure describes ADEC HEAAC ES(Elementary Stream) information.
 * adec ioctl parameter.
 *
*/
typedef struct LX_ADEC_HEAAC_ES_INFO{
	UINT8 version;       			///< Version : AAC = 0x0, HE-AACv1 = 0x1, HE-AACv2 = 0x2
	UINT8 transmissionformat;     	///< Transmission format : LOAS/LATM = 0x0, ADTS = 0x1
	UINT8 channelNum;				///< Refer LX_ADEC_AUDIO_MODE_T
} LX_ADEC_HEAAC_ES_INFO_T;

/**
 * ADEC MPEG ES Info
 * This structure describes ADEC MPEG ES(Elementary Stream) information.
 * adec ioctl parameter.
 *
*/
typedef struct LX_ADEC_MPEG_ES_INFO{
	UINT8 bitRate;			///< Bit rate(Value is divide by 1000.(Value/KBps))
	UINT8 sampleRate;		///< Sampling rate((Value is divide by 1000.(Value/KHz))
	UINT8 layer;			///< MPEG audio layer
	UINT8 channelNum; 		///< Refer LX_ADEC_AUDIO_MODE_T
} LX_ADEC_MPEG_ES_INFO_T;

/**
 * ADEC AC3 ES Info
 * This structure describes ADEC AC3/EAC3 ES(Elementary Stream) information.
 * adec ioctl parameter.
 *
*/
typedef struct LX_ADEC_AC3_ES_INFO{
	UINT8 bitRate;			///< Bit rate(Value is divide by 1000.(Value/KBps))
	UINT8 sampleRate;		///< Sampling rate((Value is divide by 1000.(Value/KHz))
	UINT8 channelNum;		///< Refer LX_ADEC_AUDIO_MODE_T
	UINT8 EAC3;       		///< EAC3 or not : AC3 0x0, EAC3 0x1
} LX_ADEC_AC3_ES_INFO_T;

/**
 * ADEC ES Info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ES_INFO
*/
typedef struct LX_ADEC_ES_INFO{
	LX_ADEC_SRC_TYPE_T 			adecFormat;		///< Audio Source Type
	LX_ADEC_AUDIO_MODE_T 		audioMode;		///< Audio Dual-mono Mode
	LX_ADEC_HEAAC_ES_INFO_T 	heAAcEsInfo;	///< HE-AAC Audio ES Information
	LX_ADEC_MPEG_ES_INFO_T  	mpegESInfo;		///< MPEG Audio ES Information
	LX_ADEC_AC3_ES_INFO_T   	ac3ESInfo;		///< AC3 Audio ES Information
} LX_ADEC_ES_INFO_T;

/**
 * ADEC Get ES Info Structure.
 * adec ioctl parameter.
 * @see LX_ADEC_ES_INFO_T
*/
typedef struct LX_ADEC_GET_ES_INFO{
	LX_ADEC_DEC_MODE_T			adecMode;		///< The mode of ADEC decoder

	LX_ADEC_ES_INFO_T 			esInfo;			///< The ADEC ES Info.
} LX_ADEC_GET_ES_INFO_T;

/**
 * ADEC Mix Volume Info.
 * This enumeration describes the ADEC Mix Volume information.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_MIX_VOLUME
*/
typedef struct LX_ADEC_MIX_VOL{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder

	UINT32 					mixVolume;		///< The value of mix audio volume.
} LX_ADEC_MIX_VOL_T;

/**
 * ADEC DAC Output Volume.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_DAC_OUT_VOLUME
*/
typedef struct LX_ADEC_DAC_VOL{
	LX_ADEC_OUTPUT_PORT_T	portNum;	///< The number of DAC Port(DAC2 : HEADPHONE, DAC0 : SCART)
	UINT32 					swVolume;	///< The Volume Level for DSP
	UINT16 					hwVolume;	///< The Volume Level for Mixed IP
	LX_ADEC_DAC_MODE_T		mode;		///< Volume control mode
	UINT8 					scartGain;	///< The SCART Gain db level for Mixed IP(0 ~ 12 dB)
} LX_ADEC_DAC_VOL_T;

/**
 * ADEC Output Port Mute.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_OUTPUT_PORT_MUTE
*/
typedef struct LX_ADEC_OUTPUT_PORT_MUTE{
	LX_ADEC_OUTPUT_PORT_T	portNum;	///< The number of Output Port
	BOOLEAN					bSwOnOff;	///< Mute On/Off DSP : FALSE => off, TRUE => on
	BOOLEAN					bHwOnOff;	///< Mute On/Off Mixed IP : FALSE => off, TRUE => on
	LX_ADEC_DAC_MODE_T		mode;		///< Mute control mode
} LX_ADEC_OUTPUT_PORT_MUTE_T;

/**
 * ADEC Clock Info.
 * adec ioctl parameter.
 * @see
*/
typedef struct LX_ADEC_CLOCK_INFO{
	UINT32		clockGSTCH;			///< The value of GSTC High Word
	UINT32		clockGSTCL;			///< The value of GSTC Low Word
	UINT32		clockSTC;			///< The value of STC
	UINT32		clockPTSM;			///< The value of PTS Main
	UINT32		clockPTSA;			///< The value of PTS Associate
} LX_ADEC_CLOCK_INFO_T;


/**
 *  ADEC SE(Sound Engine) Set / Get Function for Setting Parameters.
 * adec ioctl parameter.
 * @see ADEC_IOW_SE_SET_FUNCTION, ADEC_IORW_SE_GET_FUNCTION.
*/
typedef struct LX_ADEC_SE_FN_PARAM{
	LX_ADEC_SE_FN_MODE_T		fnMode;			///< SE FN mode

	LX_ADEC_SE_DATA_MODE_T		dataOption;		///< SE Parameters Options
	LX_ADEC_SE_VAR_MODE_T	 	varOption;		///< SE Variable Options
	LX_ADEC_SE_DATA_ACCESS_T	accessMode;		///< SE Parameters Access Modes

	UINT32 						*pParams;		///< The pointer of Parameters Buffer
	UINT16 						noParam;		///< The number of Parameters
} LX_ADEC_SE_FN_PARAM_T;


/**
 * ADEC Audio Clip Memory Info.
 * adec ioctl parameter.
 * @see ADEC_IOW_FEED_AUDIO_CLIP
*/
typedef struct LX_ADEC_CLIP_MEM_INFO{
	LX_ADEC_DEC_MODE_T		adecMode;			///< The mode of ADEC decoder

	void 					*pClipBuffer;		///< The pointer of Clip Data Memory Address in user space
	UINT32 					bufSize;			///< The size of buffer
	LX_ADEC_CLIP_BUF_T		bufStatus;			///< The status of clip play buffer

	UINT64					timestamp;			///< The timestamp of the buffer in unit of nono-seconds
	UINT64					dtsGstc;			///< The DTS(Decoding Time Stamp) value of the GSTC HW clock matching timestamp
	UINT64					duration;			///< The duration in time of the buffer data in unit of nono-seconds

	BOOLEAN					bIsTvpPath;			///< The status of TVP path for Feed Audio Clip(TVP: bIsTvp = TRUE, non-TVP: bIsTvp=FALSE)
} LX_ADEC_CLIP_MEM_INFO_T;

/**
 * ADEC Audio Clip Start Info.
 * This enumeration describes the ADEC clip start information for playing audio clip.
 * adec ioctl parameter.
 * @see ADEC_IOW_START_AUDIO_CLIP
*/
typedef struct LX_ADEC_CLIP_START_INFO{
	LX_ADEC_DEC_MODE_T		adecMode;			///< The mode of ADEC decoder

	LX_ADEC_SRC_TYPE_T		adecType;			///< Audio Source Codec Type
	UINT32					bitRate; 			///< Bit Rate
	LX_ADEC_SAMPLING_FREQ_T samplingFreq;		///< Sampling Frequency

	UINT8					numberOfChannel;	///< The number of channel of codec or PCM data
	UINT8					pcmBitsPerSample;	///< The bit per sample of PCM data

	UINT32					avgBytesPerSec; 	///< The average bytes per seconds for WMA codec
	UINT16					blockAlign; 		///< The block alignment for WMA codec
	UINT16					encoderOption;		///< The encoder option for WMA codec

	UINT32					repeatNumber;		///< The number of repeat

	void 					*pDSIBuffer;		///< The pointer of DSI(Decoding Specific Info.) buffer for AAC file decoding
	UINT32 					lengthOfDSI;		///< The length of DSI buffer

	UINT32 					wmaFormatTag;		///< The format tag of WMA codec.

	LX_ADEC_ADPCM_TYPE_T	adpcmType;			///< The type of ADPCM codec(The flag of checking previous CBT).

	UINT16					leafSize;			///< The leaf size of RA codec.(Real Audio 8)
} LX_ADEC_CLIP_START_INFO_T;

/**
 * ADEC Audio Clip AAC CODEC Start Info.
 * This enumeration describes the ADEC clip start information for playing AAC audio clip.
 * adec ioctl parameter.
 * @see ADEC_IOW_START_AAC_AUDIO_CLIP
*/
typedef struct LX_ADEC_AAC_START_INFO{
	LX_ADEC_DEC_MODE_T			adecMode;		///< The mode of ADEC decoder

	LX_ADEC_AAC_CODEC_TYPE_T	aacCodec;		///< The mode of ADEC decoder
	LX_ADEC_AAC_FORMAT_TYPE_T	aacFormat;		///< AAC Format Type(Used only in KADP module)

	LX_ADEC_SAMPLING_FREQ_T 	samplingFreq;	///< Sampling Frequency
} LX_ADEC_AAC_START_INFO_T;

/**
 * ADEC Audio Clip Message Callback Info.
 * adec ioctl parameter.
 * @see ADEC_IOW_START_AUDIO_CLIP
*/
typedef struct LX_ADEC_CLIP_CB_INFO{
	LX_ADEC_CLIP_MESSAGE_T	msg;			///< ADEC Callback Status for Audio Clip Play.
	UINT64					timestamp;		///< The timestamp of the buffer in unit of nono-seconds
	UINT64					dtsGstc;		///< The DTS(Decoding Time Stamp) value of the GSTC HW clock matching timestamp
} LX_ADEC_CLIP_CB_INFO_T;

/**
 * ADEC Audio Clip Clock Control Info.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_AV_CLOCK_CTRL
*/
typedef struct LX_ADEC_AV_CLOCK_INFO{
	LX_ADEC_DEC_MODE_T		adecMode;			///< The mode of ADEC decoder

	LX_ADEC_CTRL_MODE_T		adecCtrl;			///< The control mode of ADEC decoder
	UINT64					clockBaseTime;		///< The PTS(Presenting Time Stamp) value of the GSTC HW clock matching timestamp
	UINT64					streamBaseTime;		///< The timestamp of the buffer in unit of nono-seconds
} LX_ADEC_AV_CLOCK_INFO_T;


/**
 * ADEC Audio Encoder Buffer Info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ENC_BUF_INFO
*/
typedef struct LX_ADEC_ENC_BUF{
	UINT16		writeIndex;			///< The current write index in Audio Encoder AUI Buffer
	UINT16		sizeofAU;			///< The current Audio Encoder AU ES size info.
	UINT16		readIndex;			///< The current read index in Audio Encoder AUI Buffer
	UINT16		remainIndex;		///< The current remain index in Audio Encoder AUI Buffer

//later use
	UINT32		encEsMemoryBase;	///< The base address of Audio Encoder ES Buffer of mmap memory by assigned kernel driver
	UINT32		encEsMemorySize;	///< The Audio Encoder ES Buffer size of mmap memory
	UINT32		encAuiMemoryBase;	///< The base address of Audio Encoder AUI Buffer of mmap memory by assigned kernel driver
	UINT32		encAuiMemorySize;	///< The Audio Encoder AUI Buffer size of mmap memory
} LX_ADEC_ENC_BUF_T;

/**
 * ADEC Audio Encoder AUI(Access Unit Info.) Info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ENCODING_INFO
*/
typedef struct LX_ADEC_AU_INFO_T
{
	UINT64		size;				///< Audio Encoder ES size info.
	UINT32		timestamp;			///< Audio Encoder ES timestamp info.(mili-seconds)
	UINT32		gstc;				///< Audio Encoder ES gstc info.(90khz clock)
	UINT16		index;				///< Audio Encoder ES index info.
	UINT8		error;				///< Audio Encoder ES error info.
	UINT8 		discontinuity;		///< Audio Encoder ES discontinuity info.
	UINT32		reserved[2];		///< Reserved.
}LX_ADEC_AU_INFO_T;

/**
 * ADEC Audio Encoder Parameter Info.
 * adec ioctl parameter.
 * @see ADEC_IOW_SET_ENC_PARAM, ADEC_IOR_GET_ENC_PARAM
*/
typedef struct LX_ADEC_ENC_PARAM{
	LX_ADEC_SRC_TYPE_T		adecType;			///< Audio Encoder Codec Type

	UINT32					bitRate; 			///< Bit Rate(bps)
	LX_ADEC_SAMPLING_FREQ_T samplingFreq;		///< Sampling Frequency

	UINT8					numberOfChannel;	///< The number of channel of codec or PCM data
	UINT8					pcmBitsPerSample;	///< The bit per sample of PCM data
	UINT32					duration;			///< The duration in time of the buffer data in unit of micro-seconds
} LX_ADEC_ENC_PARAM_T;

/**
 * ADEC Audio Encoder Start Info.
 * adec ioctl parameter.
 * @see ADEC_IOW_START_ENCODING
*/
typedef struct LX_ADEC_ENC_START{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder
	LX_ADEC_SRC_TYPE_T		adecType;		///< Audio Encoder Codec Type
} LX_ADEC_ENC_START_T;

/**
 * ADEC Audio Encoder Stop Info.
 * adec ioctl parameter.
 * @see ADEC_IOW_STOP_ENCODING
*/
typedef struct LX_ADEC_ENC_STOP{
	LX_ADEC_DEC_MODE_T		adecMode;		///< The mode of ADEC decoder
} LX_ADEC_ENC_STOP_T;

/**
 * ADEC Audio Encoder Buffer Info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_ENCODING_INFO
*/
typedef struct LX_ADEC_ENC_INFO{
	LX_ADEC_AU_INFO_T	auInfo;				///< The AU Info. of current buffer

	void 				*pBuffer;			///< The pointer of App. defined Memory Address in user space(max size : 1024)
	UINT16 				bufSize;			///< The size of buffer

//later use
	UINT16				writeIndex;			///< The current write index in Audio Encoder AUI Buffer
	UINT16				readIndex;			///< The current read index in Audio Encoder AUI Buffer
	UINT16				remainIndex;		///< The current remain index in Audio Encoder AUI Buffer

	UINT32				writeOffset;		///< The current write offset in Audio Encoder ES Buffer
	UINT32				readOffset;			///< The current read offset in Audio Encoder ES Buffer
} LX_ADEC_ENC_INFO_T;


/**
 * ADEC Audio PCM Buffer Info.
 * adec ioctl parameter.
 * @see ADEC_IOR_GET_PCM_BUF_INFO
*/
typedef struct LX_ADEC_PCM_BUF{
	UINT32		writeIndex;			///< The current write index in Audio PCM Buffer AUI Buffer
	UINT32		sizeofAU;			///< The current Audio PCM Buffer AU size info.
	UINT32		readIndex;			///< The current read index in Audio PCM Buffer AUI Buffer
	UINT32		remainIndex;		///< The current remain index in Audio PCM Buffer AUI Buffer

//later use
	UINT32		pcmMemoryBase;		///< The base address of Audio PCM Buffer of mmap memory by assigned kernel driver
	UINT32		pcmMemorySize;		///< The Audio PCM Buffer size of mmap memory
	UINT32		pcmAuiMemoryBase;	///< The base address of Audio PCM AUI Buffer of mmap memory by assigned kernel driver
	UINT32		pcmAuiMemorySize;	///< The Audio PCM AUI Buffer size of mmap memory
} LX_ADEC_PCM_BUF_T;

/**
 * ADEC Audio PCM Capture Buffer Info.
 * adec ioctl parameter.
 * @see ADEC_IORW_GET_CAPTURING_INFO
*/
typedef struct LX_ADEC_CAP_INFO{
	LX_ADEC_AU_INFO_T	auInfo;				///< The AU Info. of current buffer

	void 				*pBuffer;			///< The pointer of App. defined Memory Address in user space
	UINT32 				bufSize;			///< The size of buffer

//later use
	UINT32				writeIndex;			///< The current write index in Audio PCM Capture AUI Buffer
	UINT32				readIndex;			///< The current read index in Audio PCM Capture AUI Buffer
	UINT32				remainIndex;		///< The current remain index in Audio PCM Capture AUI Buffer

	UINT32				writeOffset;		///< The current write offset in Audio PCM Capture ES Buffer
	UINT32				readOffset;			///< The current read offset in Audio PCM Capture ES Buffer
} LX_ADEC_CAP_INFO_T;



/**
 * Get and Set ADEC REG Info.
 * adec ioctl parameter.
 * @see ADEC_IORW_READ_AND_WRITE_REG
*/
typedef struct LX_ADEC_REG_INFO{
	LX_ADEC_REG_MODE_T	mode;				///< The operation mode to read and write
	UINT32				addr;				///< The address to read and write
	UINT32				readdata;			///< The data to read
	UINT32				writedata;			///< The data to write
} LX_ADEC_REG_INFO_T;

/**
 * Set ADEC IPC Command.
 * adec ioctl parameter.
 * @see ADEC_IOW_CUSTOM_IPC
*/
typedef struct LX_ADEC_CUSTOM_IPC{
	UINT32				hdr;						///< The data of header for IPC command
	UINT32				bodySize;					///< The size of IPC command
	UINT32				param[LX_IPC_ARRAY_SIZE];	///< The data of parameters for IPC command
} LX_ADEC_CUSTOM_IPC_T;

 /**
  * Enable or Disable ADEC Debug Print.
  * adec ioctl parameter.
  * @see ADEC_IOW_DEBUG_PRINT_CTRL
 */

 typedef struct LX_ADEC_DEBUG_CTRL{
	UINT32				printType;				///< The type of print module
	UINT32				printColor;				///< The color of print
} LX_ADEC_DEBUG_CTRL_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _ADEC_DRV_H_ */

/** @} */
