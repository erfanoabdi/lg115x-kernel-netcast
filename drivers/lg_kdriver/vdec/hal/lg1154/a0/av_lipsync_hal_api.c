
/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2010 by LG Electronics Inc.
 *  
 *  This program is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU General Public License 
 *  version 2 as published by the Free Software Foundation.
 *   
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *   GNU General Public License for more details.
*/ 

/** @file
 *
 *  AV LipSync HAL.
 *  (Register Access Hardware Abstraction Layer )
 *
 *  author	youngki.lyu@lge.com
 *  version	1.0
 *  date		2011-10-19
 * @addtogroup h13_vdec
 * @{
 */

#include <linux/kernel.h>

#include "base_drv.h"

#include "../lg1154_vdec_base.h"


#define LOG_NAME	vdec_hal_avsync
#include "log.h"


#define	VDEC_AV_LIPSYNC_BASE(ch)	(H13_VDEC_BASE + 0x08F0 + (ch * 0x8))	// write
#define	ADEC_H13_AV_LIPSYNC_BASE(ch)	(0xC00096C0 + (ch * 0x8))		// read



typedef struct {
	unsigned int	stc;	// 0:27
	unsigned int	pts;	// 0:27
} AV_LIPSYNC_BASE_REG_T;


static volatile AV_LIPSYNC_BASE_REG_T		*vdec_base[SRCBUF_NUM_OF_CHANNEL];
static volatile AV_LIPSYNC_BASE_REG_T		*adec_base[SRCBUF_NUM_OF_CHANNEL];

void AV_LipSync_HAL_Init(void)
{
	int a;

	log_noti ("init\n");

	for( a = 0; a < SRCBUF_NUM_OF_CHANNEL; a++ )
	{
		vdec_base[a] = (volatile AV_LIPSYNC_BASE_REG_T *)
			ioremap (VDEC_AV_LIPSYNC_BASE(a), 
					sizeof (AV_LIPSYNC_BASE_REG_T));
		adec_base[a] = (volatile AV_LIPSYNC_BASE_REG_T *)
			ioremap (ADEC_H13_AV_LIPSYNC_BASE(a),
					sizeof (AV_LIPSYNC_BASE_REG_T));
	}
}

void AV_LipSync_HAL_Vdec_SetBase(int ch,
		unsigned int base_stc, unsigned int base_pts)
{
	log_debug ("src%d, set vdec base time %x, pts %x\n",
			ch, base_stc, base_pts );

	if( ch >= SRCBUF_NUM_OF_CHANNEL )
	{
		log_warning ("unknown channel number %d\n", ch);
		return;
	}

	vdec_base[ch]->stc = base_stc;
	vdec_base[ch]->pts = base_pts;
}

void AV_LipSync_HAL_Vdec_GetBase(int ch, unsigned int *base_stc, unsigned int *base_pts)
{
	if( ch >= SRCBUF_NUM_OF_CHANNEL )
	{
		log_warning ("worng channel number %d\n", ch);
		return;
	}

	*base_stc = vdec_base[ch]->stc;
	*base_pts = vdec_base[ch]->pts;

	log_debug ("src%d get vdec base time %x, pts %x\n", ch,
			*base_stc, *base_pts);
}

void AV_LipSync_HAL_Adec_GetBase(int ch, unsigned int *base_stc, unsigned int *base_pts)
{
	if( ch >= SRCBUF_NUM_OF_CHANNEL )
	{
		log_warning ("wrong channel number %d\n", ch);
		return;
	}

	*base_stc = adec_base[ch]->stc;
	*base_pts = adec_base[ch]->pts;

	log_debug ("src%d get adec base time %x, pts %x\n", ch,
			*base_stc, *base_pts);
}

void AV_Set_AVLipSyncBase(int ch, unsigned int *_base_stc, unsigned int *_base_pts)
{
	unsigned int base_stc = *_base_stc;
	unsigned int base_pts = *_base_pts;

	if( ch >= SRCBUF_NUM_OF_CHANNEL )
	{
		log_warning ("wrong channel %d\n", ch);
		return;
	}

	log_debug ("src%d got base stc %x, base pts %x\n", ch,
			base_stc, base_pts);

	BASE_AVLIPSYNC_LOCK();

	if( (base_stc != 0xFFFFFFFF) && (base_pts != 0xFFFFFFFF) )
	{
		unsigned int  adec_base_stc, adec_base_pts;

		AV_LipSync_HAL_Adec_GetBase(ch, &adec_base_stc, &adec_base_pts);
		log_debug ("src%d, adec base stc %x, base pts %x\n", ch,
				adec_base_stc, adec_base_pts);

		if( (adec_base_stc == 0xFFFFFFFF) || (adec_base_pts == 0xFFFFFFFF) )
			log_debug ("src%d adec have no base time. use mine.\n", ch);
		else
		{
			log_debug ("src%d adec have base time. use adec.\n", ch);

			*_base_stc = base_stc = adec_base_stc;
			*_base_pts = base_pts = adec_base_pts;
		}
	}

	log_debug ("src%d set base stc %x, base pts %x\n", ch,
			base_stc, base_pts);
	AV_LipSync_HAL_Vdec_SetBase(ch, base_stc, base_pts);

	BASE_AVLIPSYNC_UNLOCK();
}

/** @} */

