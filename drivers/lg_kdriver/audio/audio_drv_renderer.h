/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2010 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 


/** @file audio_drv_renderer.h
 *
 *  driver interface header for audio device. ( used only within kdriver )
 *	audio device will teach you how to make device driver with new platform.
 *
 *  @author	wonchang.shin (wonchang.shin@lge.com)
 *  @version	0.1
 *  @date		2012.04.25
 *
 *  @addtogroup lg1150_audio
 *	@{
 */

#ifndef	_AUDIO_DRV_RENDERER_H_
#define	_AUDIO_DRV_RENDERER_H_

#include "audio_kapi_renderer.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


#define AUD_RENDER_CONNECT_NUM	5

/**
 * AUDIO Renderer Connect Information.
 */
typedef struct
{
	LX_AUD_DEV_TYPE_T devType;
	LX_AUD_ALLOC_DEV_T connectDev;
} AUD_RENDER_CONNECT_T;

/**
 * AUDIO Renderer Connect Information.
 */
typedef struct
{
	UINT32 bCtrlSrcOnOff;
	LX_AUD_ALLOC_MOD_T allocCtrlSrc;
} AUD_CTRLSRC_INFO_T;


/**
 * AUDIO Renderer Information.
 */
typedef struct {
	UINT32								ui32AllocDev;

	LX_AUD_RENDER_PARAM_T				renderParam;
	LX_AUD_RENDER_PARAM_LIPSYNC_T		renderLipsync;
	LX_AUD_RENDERED_STATUS_T			renderStatus;
	LX_AUD_RENDER_CLK_TYPE_T			renderClockType;
	AUD_EVENT_T							renderEvent[AUD_EVENT_NUM];
	AUD_RENDER_CONNECT_T				renderConnect[AUD_RENDER_CONNECT_NUM];	///< For Reset Recovery

	UINT32				ui32MixerPort;			///< mixer port
	UINT32				bStarted;
	UINT32				bClosed;
	UINT32				bResetting;
	UINT32				bLipsyncOnOff;
	UINT32				ui32Volume;
	UINT32				ui32EventNum;
	UINT32				ui32ConnectNum;			///< For Reset Recovery

	BOOLEAN				bBufferRepeat;			///< The status of buffer repeat is set previously.
	UINT32				bRTSOnOff;				///< the flag of RTS mode enable/disable
	AUD_CTRLSRC_INFO_T				ctrlSrcInfo;			///< the Info of Control SRC
} AUD_RENDER_INFO_T;


SINT32	KDRV_AUDIO_OpenRenderer(struct inode *inode, struct file *filp);
SINT32	KDRV_AUDIO_CloseRenderer(struct inode *inode, struct file *filp);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
int KDRV_AUDIO_IoctlRenderer(struct inode *, struct file *, unsigned int, unsigned long );
#else
long KDRV_AUDIO_IoctlRenderer (struct file *filp, unsigned int cmd, unsigned long arg );
#endif
void	KDRV_AUDIO_ResetRenderer(void);
void	KDRV_AUDIO_ResetRendererParam(void);
void	KDRV_AUDIO_RestartRenderer(void);
void	KDRV_AUDIO_RedemandDecodedNofiRenderer(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _AUDIO_DRV_RENDERER_H_ */

