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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/mutex.h>

#include "vo_kapi.h"

#include "hal/top_hal_api.h"
#include "hal/vdec_base.h"
#include "vds/vdisp_drv.h"
#include "vds/vdec_rate.h"
#include "vds/vsync_drv.h"
#include "vds/disp_q.h"

#include "log.h"

logm_define (vo, log_level_warning);
logm_define (vo_mon, log_level_warning);
logm_define (vo_irq, log_level_warning);

#define MAX_QUEUE_SIZE	16

static int major = 1818;
static int force_2d;
module_param_named (vo_major, major, int, 0444);
module_param_named (vo_force_2d, force_2d, int, 0644);

static int force_framerate_num;
static int force_framerate_den;
module_param_named (vo_force_framerate_num, force_framerate_num, int, 0644);
module_param_named (vo_force_framerate_den, force_framerate_den, int, 0644);

static int force_par_w;
static int force_par_h;
module_param_named (vo_force_par_w, force_par_w, int, 0644);
module_param_named (vo_force_par_h, force_par_h, int, 0644);

static int donot_update_info;
module_param_named (vo_donot_update_info, donot_update_info, int, 0644);

static struct vo_vdo_info vdo_info_raster =
{
	.tile_base = 0,
	.map_type = vo_map_type_linear,
};

struct vo
{
	int sync;
	int sync2;

	int open_dual;
	int flushed;

	int de_id;

	int width;
	int height;
	int stride;

	int framerate_es_num;
	int framerate_es_den;
	int framerate_container_num;
	int framerate_container_den;
	int force_framerate_num;
	int force_framerate_den;
	enum DISPQ_FRAME_FORMAT frame_format;
	int queue_size;
	int inited;
	enum vo_3d_type trid_type;
	struct vo_vdo_info *vdo_info;
	int speed;
	struct vo_basetime basetime;
	int display_offset;

	int low_delay;
	int constant_delay;

	int par_w, par_h;

	/* displayed queue */
	spinlock_t displayed_queue_lock;
	wait_queue_head_t displayed_wait;
	struct vo_displayed_info *displayed_queue;
	int displayed_queue_size;
	volatile int displayed_queue_head;
	volatile int displayed_queue_tail;
	unsigned int displayed_queue_last_written_id;

	struct vo *next;
};

static DEFINE_MUTEX (initialize_lock);
static unsigned int used;
static struct vo *device_list;

static int mirror_mode;
static DEFINE_SPINLOCK (mirror_mode_lock);
static int mirror_de_id = -1;

struct vo_output_info output_info[2];

int vo_set_output_info (int de_id, int width, int height,
		int framerate_num, int framerate_den,
		int par_w, int par_h,
		int progressive,
		enum vo_3d_type trid_type)
{
	struct vo_output_info *info;
	unsigned long flag;

	if (
			de_id < 0 ||
			de_id >= ARRAY_SIZE (output_info)
	   )
	{
		logm_warning (vo, "wrong de index %d\n", de_id);
		return -EINVAL;
	}

	if (donot_update_info)
		return 0;

	if (framerate_den == 0)
	{
		logm_debug (vo, "wrong framerate %d/%d\n",
				framerate_num, framerate_den);
		framerate_num = 0;
		framerate_den = 1;
	}

	/* when par_w and par_h == -1, */
	if (par_w == par_h)
		par_w = par_h = 1;

	info = output_info+de_id;

	info->width = width;
	info->height = height;
	info->framerate_num = framerate_num;
	info->framerate_den = framerate_den;
	info->progressive = progressive;
	info->par_w = par_w;
	info->par_h = par_h;
	info->trid_type = trid_type;

	spin_lock_irqsave (&mirror_mode_lock, flag);
	if (mirror_mode)
	{
		if (de_id == 0)
			mirror_de_id = 1;
		else
			mirror_de_id = 0;

		info = output_info+mirror_de_id;

		info->width = width;
		info->height = height;
		info->framerate_num = framerate_num;
		info->framerate_den = framerate_den;
		info->progressive = progressive;
		info->par_w = par_w;
		info->par_h = par_h;
		info->trid_type = trid_type;
	}
	spin_unlock_irqrestore (&mirror_mode_lock, flag);

	return 0;
}

static int running_info (struct vo *vo,
		int *framerate_num, int *framerate_den,
		int *width, int *height)
{
	struct vo *now;

	mutex_lock (&initialize_lock);
	now = device_list;
	do
	{
		if (now->de_id == vo->de_id && now->sync >= 0)
			break;

		now = now->next;
	}
	while (now);

	if (framerate_num && framerate_den)
	{
		*framerate_num = 0;
		*framerate_den = 0;
		if (now == NULL)
			logm_debug (vo_mon, "no device opened\n");
		else
			VDEC_RATE_GetFrameRateResDiv (now->sync,
					framerate_num, framerate_den);

		if (*framerate_den == 0)
		{
			logm_debug (vo_mon, "wrong framerate %d/%d\n",
					*framerate_num, *framerate_den);

			*framerate_num = output_info[vo->de_id].framerate_num;
			*framerate_den = output_info[vo->de_id].framerate_den;
		}

		logm_debug (vo_mon, "de id %d, framerate %d/%d\n",
				vo->de_id,
				*framerate_num,
				*framerate_den);
	}

	if (width && height)
	{
		S_VDISP_DISP_INFO_T info;

		memset (&info, 0, sizeof(info));

		VDISP_GetCurrentInfo (vo->de_id, &info);

		*width  = info.width;
		*height = info.height;
	}

	mutex_unlock (&initialize_lock);

	return 0;
}

static int vo_open (struct inode *inode, struct file *file)
{
	struct vo *vo;

	vo = kcalloc (1, sizeof(*vo), GFP_KERNEL);;
	file->private_data = vo;

	/* set default parameter */
	vo->width = 1920;
	vo->height = 1080;
	vo->stride = 2048;
	if (force_framerate_num && force_framerate_den)
	{
		vo->framerate_es_num = force_framerate_num;
		vo->framerate_es_den = force_framerate_den;
	}
	else
	{
		vo->framerate_es_num = 30;
		vo->framerate_es_den = 1;
	}
	vo->framerate_container_num = vo->framerate_es_num;
	vo->framerate_container_den = vo->framerate_es_den;
	vo->frame_format = DISPQ_FRAME_FORMAT_420;
	vo->queue_size = 4;
	vo->inited = 0;
	vo->sync = -1;
	vo->sync2 = -1;
	vo->open_dual = 0;
	vo->trid_type = vo_3d_type_none;
	vo->speed = 0x10000;
	vo->par_w = vo->par_h = 1;
	vo->vdo_info = &vdo_info_raster;

	/* displayed queue */
	spin_lock_init (&vo->displayed_queue_lock);
	init_waitqueue_head (&vo->displayed_wait);
	vo->displayed_queue_head = 0;
	vo->displayed_queue_tail = 0;
	vo->displayed_queue_size = 64;
	vo->displayed_queue = kmalloc (
			sizeof(vo->displayed_queue[0])*vo->displayed_queue_size,
			GFP_KERNEL);

	/* register at the device list */
	mutex_lock (&initialize_lock);
	vo->next = device_list;
	device_list = vo;
	mutex_unlock (&initialize_lock);

	logm_debug (vo, "vo:%p, opened\n", vo);

	return 0;
}

static int vo_release (struct inode *inode, struct file *file)
{
	struct vo *vo = file->private_data;

	logm_trace (vo, "vo:%p, releasing\n", vo);

	mutex_lock (&initialize_lock);
	if (vo->sync >= 0)
	{
		VDISP_Close (vo->sync);
		used &= ~(1<<vo->de_id);

		memset (&output_info[vo->de_id], 0,
				sizeof (struct vo_output_info));

		vo_set_output_info (vo->de_id, 0, 0, 0, 0,
				0, 0, 0, vo_3d_type_none);
	}
	if (vo->sync2 >= 0)
	{
		VDISP_Close (vo->sync2);
		used &= ~(1<<1);

		memset (&output_info[1], 0,
				sizeof (struct vo_output_info));

		vo_set_output_info (1, 0, 0, 0, 0,
				0, 0, 0, vo_3d_type_none);
	}

	/* remove from device list */
	if (device_list == vo)
		device_list = vo->next;
	else
	{
		struct vo *now;
		now = device_list;

		while (now->next != NULL && now->next != vo)
			now = now->next;

		if (now->next == vo)
			now->next = vo->next;
		else
			logm_error (vo, "vo:%p, Oops\n", vo);
	}

	kfree (vo->displayed_queue);

	logm_debug (vo, "vo:%p, released\n", vo);

	kfree (vo);
	mutex_unlock (&initialize_lock);

	return 0;
}

static ssize_t vo_read (struct file *file, char __user *buf, size_t len, loff_t *off)
{
	struct vo *vo = (struct vo*)file->private_data;
	int ret = 0;
	int head, tail;
	int written = 0;
	int unit_size = sizeof (vo->displayed_queue[0]);

	logm_trace (vo, "vo:%p\n", vo);
	logm_debug (vo, "vo:%p, len %d, head %d, tail %d\n",
			vo,
			len,
			vo->displayed_queue_head,
			vo->displayed_queue_tail
			);
	while (written < len)
	{
		int count1, count2;

		/* check the queue */
		if (file->f_flags&O_NONBLOCK)
		{
			if (vo->displayed_queue_head != vo->displayed_queue_tail)
			{
				logm_debug (vo, "vo:%p, nonblock\n", vo);
				ret = -EAGAIN;
				break;
			}
		}
		else
		{
			ret = wait_event_interruptible (vo->displayed_wait,
					vo->displayed_queue_head != vo->displayed_queue_tail);
			if (ret < 0)
			{
				logm_debug (vo, "vo:%p, signaled\n", vo);
				break;
			}
		}

		/* get queue head, tail offset */
		head = vo->displayed_queue_head;
		tail = vo->displayed_queue_tail;

		if (head == tail)
		{
			break;
		}
		else if (head > tail)
		{
			count1 = head - tail;
			count2 = 0;
		}
		else
		{
			count1 = vo->displayed_queue_size - tail;
			count2 = head;
		}

		if ((count1+count2)*unit_size > len-written)
		{
			logm_debug (vo, "vo:%p, not enough buffer\n", vo);
			if (count1*unit_size > len-written)
			{
				count1 = (len-written)/unit_size;
				count2 = 0;
			}
			else
				count2 = (len-written)/unit_size-count1;
		}

		/* copy the data from queue */
		if (count1)
		{
			ret = copy_to_user (buf+written, vo->displayed_queue+tail,
					count1*unit_size);
			if (ret)
			{
				ret = -EFAULT;
				logm_warning (vo, "vo:%p, oops\n", vo);
				break;
			}
		}

		if (count2)
		{
			ret = copy_to_user (buf+written, vo->displayed_queue,
					count2*unit_size);
			if (ret)
			{
				ret = -EFAULT;
				logm_warning (vo, "vo:%p, oops\n", vo);
				break;
			}
		}
		written += (count1+count2)*unit_size;

		logm_debug (vo, "vo:%p, written %d, ret %d\n", vo, written, ret);

		/* update queue tail offset */
		tail += (count1+count2);
		tail %= vo->displayed_queue_size;
		vo->displayed_queue_tail = tail;
	}

	logm_trace (vo, "vo:%p, written %d, ret %d\n", vo, written, ret);

	if (written == 0)
		return ret;

	return written;
}

static void push_info (struct vo *vo,
		unsigned int id, unsigned long priv)
{
	int filled;
	int head, tail;
	struct vo_displayed_info info;
	unsigned int size = sizeof (info);
	unsigned long flag;

	info.id = id;
	info.priv = priv;

	spin_lock_irqsave (&vo->displayed_queue_lock, flag);

	head = vo->displayed_queue_head;
	tail = vo->displayed_queue_tail;

	logm_debug (vo, "vo:%p, %c%c%c%c, %d bytes, %d %d\n", vo,
			(info.id>>24)&0xff,
			(info.id>>16)&0xff,
			(info.id>>8)&0xff,
			(info.id>>0)&0xff,
			size, tail, head);

	/* check buffer overflow */
	filled = head - tail;
	if (filled < 0)
		filled += vo->displayed_queue_size;

	if (filled + 1 >= vo->displayed_queue_size)
	{
		logm_noti (vo, "vo:%p, displayed queue full %d, %d, "
				"size %d, %c%c%c%c\n",
				vo, tail, head,
				size,
				(info.id>>24)&0xff,
				(info.id>>16)&0xff,
				(info.id>>8)&0xff,
				(info.id>>0)&0xff
				);
		goto failed;
	}

	if (info.id == VO_FCC('E','M','P','T') &&
			vo->displayed_queue_last_written_id == info.id)
	{
		logm_debug (vo, "vo:%p, skip empty info\n", vo);
		goto skip;
	}

	vo->displayed_queue_last_written_id = info.id;

	/* put data */
	memcpy (vo->displayed_queue+head, &info, size);
	head += 1;
	head %= vo->displayed_queue_size;
	vo->displayed_queue_head = head;

	wake_up (&vo->displayed_wait);

failed:

skip:

	spin_unlock_irqrestore (&vo->displayed_queue_lock, flag);
	return;
}

static void displayed_callback (void *arg, S_DISPQ_BUF_T *buffer)
{
	struct vo *vo = (struct vo*)arg;

	logm_debug (vo, "vo:%p, displayed y %07x, priv %08x, "
			"queue tail %d, queue head %d\n",
			vo,
			buffer->ui32Y_FrameBaseAddr,
			buffer->ui32UId,
			vo->displayed_queue_tail,
			vo->displayed_queue_head
		   );

	if (buffer->bDispResult)
		push_info (vo, VO_FCC ('D','I','S','P'), buffer->ui32UId);
	else
		push_info (vo, VO_FCC ('D','R','O','P'), buffer->ui32UId);
}

static void status_callback (unsigned char sync,
		VDISP_STATUS_TYPE type, unsigned int data)
{
	struct vo *vo;

	logm_debug (vo, "vo:<xxxxxx>, sync %d, type %d, data %08x\n",
			sync, type, data);
	vo = device_list;
	while (vo)
	{
		if (vo->sync == sync || vo->sync2 == sync)
			break;

		vo = vo->next;
	}

	if (vo == NULL)
	{
		logm_error (vo, "vo:<null>, Oops? unknown sync %d\n",
				sync);

		return;
	}

	logm_debug (vo, "vo:%p, status %d\n", vo, type);

	switch (type)
	{
	case VDISP_ST_EMPTY:
		if (!vo->low_delay)
			push_info (vo, VO_FCC ('E','M','P','T'), 0);
		break;
	default:
		logm_warning (vo, "vo:%p, unknown status type %d\n",
				vo, type);
		break;
	}
}

static int initialize_locked (struct vo *vo, int dual, int open_dual)
{
	int match_mode;

	if (used & 1<<vo->de_id)
	{
		logm_warning (vo, "vo:%p, id %d already occupied\n",
				vo,
				vo->de_id);
		return -EINVAL;
	}

	if (open_dual && used & 1<<1)
	{
		logm_warning (vo, "vo:%p, id 1 already occupied for dual channel\n", vo);
		return -EINVAL;
	}

	used |= 1<<vo->de_id;

	if (vo->low_delay)
	{
		logm_debug (vo, "vo:%p, setting low delay\n", vo);
		match_mode = PTS_MATCH_FREERUN_IGNORE_SYNC;
	}
	else if (vo->constant_delay > 0)
	{
		logm_debug (vo, "vo:%p, set adaptive freerun\n", vo);
		match_mode = PTS_MATCH_ADAPTIVE_FREERUN;
	}
	else
	{
		match_mode = PTS_MATCH_ENABLE;
	}
	vo->sync = VDISP_Open (
			open_dual?0:vo->de_id,// Dst
			VDISP_CLK_GSTC,
			vo->display_offset,// DisplayOffset_ms
			MAX_QUEUE_SIZE,	// NumOfDq
			dual,		// IsDualDecoding
			0,		// FixedVSync ??
			match_mode,	// MatchMode
			status_callback	
			);
	if (vo->sync == 0xff)
	{
		logm_warning (vo, "vo:%p, sync open failed\n", vo);
		vo->sync = -1;
		used &= ~(1<<vo->de_id);
		return -EINVAL;
	}

	VDEC_RATE_UpdateFrameRate_Config (vo->sync,
			vo->framerate_container_num,
			vo->framerate_container_den
			);

	VDISP_SetSpeed (vo->sync, vo->speed*1000/0x10000);
	VDISP_SetBaseTime (vo->sync, vo->basetime.base_stc,
			vo->basetime.base_pts);
	VDISP_Start (vo->sync, 0);

	if (open_dual)
	{
		used |= 1<<1;
		vo->sync2 = VDISP_Open (
				1,		// Dst
				VDISP_CLK_GSTC,
				vo->display_offset,// DisplayOffset_ms
				MAX_QUEUE_SIZE,	// NumOfDq
				dual,		// IsDualDecoding
				0,		// FixedVSync ??
				match_mode,	// MatchMode
				status_callback	
				);
		if (vo->sync2 == 0xff)
		{
			logm_warning (vo, "vo:%p, sync2 open failed\n", vo);
			vo->sync2 = -1;
			used &= ~(1<<1);

			VDISP_Close (vo->sync);
			vo->sync = -1;
			used &= ~(1<<vo->de_id);
			return -EINVAL;
		}

		VDEC_RATE_UpdateFrameRate_Config (vo->sync2,
				vo->framerate_container_num,
				vo->framerate_container_den
				);

		VDISP_SetSpeed (vo->sync2, vo->speed*1000/0x10000);
		VDISP_SetBaseTime (vo->sync2, vo->basetime.base_stc,
				vo->basetime.base_pts);
		VDISP_Start (vo->sync2, 0);

		logm_debug (vo, "vo:%p, sync: %d, sync2: %d\n",
				vo,
				vo->sync, vo->sync2);
	}

	return 0;
}

static ssize_t vo_write (struct file *file,
		const char __user *buf, size_t len, loff_t *off)
{
	S_DISPQ_BUF_T picture;
	struct vo *vo = file->private_data;
	int written;
	int dual = 0;

	logm_trace (vo, "vo:%p, size %d\n", vo, len);

	memset (&picture, 0, sizeof(picture));

	written = 0;
	while (len >= sizeof(struct vo_write))
	{
		wait_queue_head_t *wait;
		int sync, de_id;
		struct vo_write write;
		int ret;
		long long pts;

		ret = copy_from_user (&write, buf+written, sizeof(write));
		if (ret)
		{
			ret = -EFAULT;
			logm_error (vo, "vo:%p, copy_from_user failed\n", vo);
			break;
		}
		written += sizeof(write);
		len -= sizeof(write);

		/* 3D type 이 dual 인 경우 두가지 vo 드라이버 제어방법이 있을 수 있다.
		 *
		 * - 첫번째로 두개의 vo 드라이버를 열어 각각 de_id 를 다르게 설정 한
		 *   다음 picture를 쓰는 방법과
		 * - 하나의 vo 드라이버를 열어 multi_picture_index를 0 혹은 1로 설정해
		 *   왼쪽 혹은 오른쪽 그림을 구분하는 방법이다.
		 *
		 * 첫번째 방법은 3D type은 dual 이지만 하나의 sync module을 열어야
		 * 하며, 두번째 방법은 하나의 vo 드라이버에서 두개의 sync module을 열어
		 * 한번에 제어해야 한다.
		 */
		if (vo->trid_type == vo_3d_type_dual)
			dual = 1;

		if (!vo->inited)
		{
			int ret;

			if (dual && write.multi_picture_index >= 0)
				vo->open_dual = 1;

			if (vo->open_dual && vo->de_id != 0)
			{
				logm_warning (vo, "vo:%p, dual open while de_id %d\n", vo,
						vo->de_id);
				vo->de_id = 0;
			}

			mutex_lock (&initialize_lock);
			ret = initialize_locked (vo, dual, vo->open_dual);
			mutex_unlock (&initialize_lock);

			if (ret < 0)
			{
				logm_warning (vo, "vo:%p, initialize failed\n",
						vo);
				return ret;
			}

			vo->inited = 1;
		}

		/* select writing sync module for dual 3D */
		if (!vo->open_dual || write.multi_picture_index <= 0)
		{
			sync = vo->sync;
			de_id = vo->de_id;

			logm_debug (vo, "vo:%p, de_id %d, 1st sync selected\n",
					vo, de_id);
		}
		else
		{
			sync = vo->sync2;
			de_id = 1;

			logm_debug (vo, "vo:%p, de_id %d, 2nd sync selected\n",
					vo, de_id);
		}
		wait = DISP_Q_GetWait (sync);

		if (vo->flushed)
			vo->flushed = 0;
		logm_debug (vo, "vo:%p, active number %d\n", vo,
				DISP_Q_NumActive (sync));
		ret = wait_event_interruptible (*wait,
				DISP_Q_NumActive(sync)<vo->queue_size);
		if (ret)
		{
			logm_debug (vo, "vo:%p, signaled\n", vo);
			break;
		}
		if (vo->flushed)
		{
			logm_debug (vo, "vo:%p, flushed.\n", vo);
			push_info (vo, VO_FCC ('D','R','O','P'), (unsigned long)write.priv);
			vo->flushed = 0;
			continue;
		}

		picture.ui32Tiled_FrameBaseAddr = vo->vdo_info->tile_base;
		switch (vo->vdo_info->map_type)
		{
		default:
		case vo_map_type_linear:
			picture.ui32DpbMapMode = DISPQ_LINEAR_MAP_DPB;
			break;

		case vo_map_type_frame:
			picture.ui32DpbMapMode = DISPQ_FRAME_MAP_DPB;
			break;

		case vo_map_type_mixed:
			picture.ui32DpbMapMode = DISPQ_MIXED_MAP_DPB;
			break;
		}
		picture.ui32Y_FrameBaseAddr = write.addr_y;
		picture.ui32C_FrameBaseAddr = write.addr_cb;
		picture.ui32Y_FrameOffset = 0;
		picture.ui32C_FrameOffset = 0;
		picture.ui32Stride = vo->stride;
		picture.FrameFormat = vo->frame_format;

		picture.ui32FrameRateRes = vo->framerate_es_num;
		picture.ui32FrameRateDiv = vo->framerate_es_den;
		//picture.bVariableFrameRate;	// not used

		picture.ui32FrameIdx = 0;
		picture.ui32AspectRatio = 3;
		picture.ui32PicWidth = vo->width;
		picture.ui32PicHeight = vo->height;
		picture.ui32H_Offset =
			write.crop_left<<16 | write.crop_right;
		picture.ui32V_Offset =
			write.crop_top<<16 | write.crop_bottom;
		//picture.bFieldPicture;		// ??
		switch (write.interlace)
		{
		case vo_interlace_top_first:
			picture.ui32DisplayInfo =
				DISPQ_SCAN_TFF;
			break;
		case vo_interlace_bottom_first:
			picture.ui32DisplayInfo =
				DISPQ_SCAN_BFF;
			break;
		default:
		case vo_interlace_progressive:
			picture.ui32DisplayInfo =
				DISPQ_SCAN_PROG;
			break;
		}
		if (vo->constant_delay == 0)
		{
			pts = write.pts;
			if (pts != -1)
			{
				pts *= 9;
				do_div (pts, 100000);
				picture.ui32PTS = pts;
			}
			else
				picture.ui32PTS = VDEC_UNKNOWN_PTS;
		}
		else
			picture.ui32PTS = VDEC_UNKNOWN_PTS;
		//picture.ui32DTS;
		//picture.ui64TimeStamp;
		picture.ui32UId = (unsigned long)write.priv;
		picture.ui32DisplayPeriod = write.display_period;
		if (vo_3d_type_checkerboard <= vo->trid_type &&
				vo->trid_type <= vo_3d_type_fpa_end)
			picture.i32FramePackArrange = vo->trid_type;
		else
			picture.i32FramePackArrange = -2;
		if (dual)
			picture.ui32LR_Order = DISPQ_3D_FRAME_NONE;
		else
		{
			if (write.multi_picture_index < 0)
				picture.ui32LR_Order = DISPQ_3D_FRAME_NONE;
			else if (write.multi_picture_index == 0)
				picture.ui32LR_Order = DISPQ_3D_FRAME_LEFT;
			else
				picture.ui32LR_Order = DISPQ_3D_FRAME_RIGHT;
		}
		picture.ui16ParW = vo->par_w;
		picture.ui16ParH = vo->par_h;

		logm_debug (vo,  "vo:%p, "
				"vdo_info:%p, tile_base:%lx,maptype:%d,y:%07lx,c:%07lx, "
				"%dx%d(%d),ts:%lld,pts:%08x,%d/%dfps, "
				"par:%ux%u,3d:%d,lr:%d,interlace:%d\n", vo,
				vo->vdo_info, vo->vdo_info->tile_base,
				vo->vdo_info->map_type,
				write.addr_y, write.addr_cb,

				vo->width, vo->height,
				vo->stride,
				write.pts, picture.ui32PTS,
				vo->framerate_es_num, vo->framerate_es_den,

				vo->par_w, vo->par_h,
				vo->trid_type, write.multi_picture_index,
				write.interlace
			   );
		logm_debug (vo, "vo:%p, crop(lrtb):%d,%d,%d,%d\n", vo,
				write.crop_left, write.crop_right,
				write.crop_top, write.crop_bottom);

		DISP_Q_Push_callback (sync, &picture,
				displayed_callback, vo);

		vo_set_output_info (de_id,
				vo->width-write.crop_left-write.crop_right,
				vo->height-write.crop_top-write.crop_bottom,
				vo->framerate_es_num,
				vo->framerate_es_den,
				picture.ui16ParW, picture.ui16ParH,
				write.interlace == vo_interlace_progressive,
				vo->trid_type);
	}

	logm_trace (vo, "vo:%p, written %d\n", vo, written);
	return written;
}

static unsigned int vo_poll (struct file *file, struct poll_table_struct *pt)
{
	struct vo *vo = file->private_data;
	wait_queue_head_t *wait;
	unsigned int ret = 0;
	int display_queue_num;

	if (vo->sync < 0)
		return POLLERR;

	wait = DISP_Q_GetWait (vo->sync);
	display_queue_num = DISP_Q_NumActive (vo->sync);

	poll_wait (file, &vo->displayed_wait, pt);
	poll_wait (file, wait, pt);

	if (vo->displayed_queue_head != vo->displayed_queue_tail)
		ret |= POLLIN | POLLRDNORM;

	if (display_queue_num < vo->queue_size)
		ret |= POLLOUT | POLLWRNORM;

	if (
			vo->displayed_queue_head == vo->displayed_queue_tail &&
			display_queue_num == 0
	   )
		ret |= POLLERR;

	return ret;
}

static long vo_ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	union
	{
		struct vo_framebuffer_info fb_info;
		struct vo_basetime basetime;
		struct vo_stc stc;
		unsigned long tile_base;
		int queue_size;
		struct vo_output_info output_info;
	} a;
	long ret = -ENOIOCTLCMD;
	struct vo *vo = file->private_data;
	wait_queue_head_t *wait;

	if (cmd != VO_GET_OUTPUT_INFO)
		logm_trace (vo, "vo:%p, cmd = %08x (cmd_idx=%d)\n", vo, cmd, _IOC_NR(cmd));

	if (_IOC_TYPE(cmd) != VO_TYPE)
	{
		logm_warning (vo, "vo:%p, invalid magic. magic=0x%02x\n", vo,
				_IOC_TYPE(cmd) );
		return -ENOIOCTLCMD;
	}
	if (_IOC_DIR(cmd) & _IOC_WRITE)
	{
		int r;

		r = copy_from_user (&a, (void*)arg, _IOC_SIZE(cmd));
		if (r)
		{
			logm_error (vo, "vo:%p, copy_from_user failed\n", vo);
			return -EFAULT;
		}
	}

	switch (cmd)
	{
	case VO_SET_DE_ID:
		if (arg >= ARRAY_SIZE (output_info))
		{
			logm_warning (vo, "vo:%p, unknown de id %ld\n", vo, arg);
			ret = -EINVAL;
		}

		vo->de_id = arg;

		logm_debug (vo, "vo:%p, set de id %d\n", vo, vo->de_id);
		ret = 0;
		break;

	case VO_FLUSH:
		if (vo->sync < 0)
		{
			logm_debug (vo, "vo:%p, no device while flushing\n", vo);
			ret = -EINVAL;
			break;
		}

		logm_noti (vo, "vo:%p, flush\n", vo);
		VDISP_Flush (vo->sync);
		vo->flushed = 1;
		wait = DISP_Q_GetWait (vo->sync);

		wake_up (&vo->displayed_wait);
		wake_up (wait);

		ret = 0;
		break;

	case VO_GET_STC:
		a.stc.stc = TOP_HAL_GetGSTCC ();
		a.stc.mask = 0xffffffff;

		logm_debug (vo, "vo:%p, stc %08x\n", vo, a.stc.stc);
		ret = 0;
		break;

	case VO_SET_BASETIME:
		logm_noti (vo, "vo:%p, set base stc %08x, pts %08x\n", vo,
				a.basetime.base_stc,
				a.basetime.base_pts);
		vo->basetime = a.basetime;

		if (vo->sync >= 0)
			VDISP_SetBaseTime (vo->sync, vo->basetime.base_stc,
					vo->basetime.base_pts);
		ret = 0;
		break;

	case VO_SET_DISPLAY_POSITION:
		break;

	case VO_SET_FRAMEBUFFER_INFO:
		vo->width  = a.fb_info.width;
		vo->height = a.fb_info.height;
		vo->stride = a.fb_info.stride;

		logm_debug (vo, "vo:%p, set framebuffer info %dx%d %d\n", vo,
				vo->width, vo->height, vo->stride);
		ret = 0;
		break;

	case VO_SET_INTERLACE:
		logm_warning (vo, "vo:%p, not supported anymore\n", vo);
		break;

	case VO_SET_COLOR_SUBSAMPLE:
		if (arg == 0x00020002)
			vo->frame_format = DISPQ_FRAME_FORMAT_420;
		else if (arg == 0x00010002)
			vo->frame_format = DISPQ_FRAME_FORMAT_422;
		else
		{
			logm_warning (vo, "vo:%p, not supported subsampling. %ldx%ld\n", vo,
					arg & 0xffff,
					arg>>16);
			break;
		}

		logm_debug (vo, "vo:%p, set color subsample %ldx%ld\n", vo,
				arg & 0xffff,
				arg >> 16);
		ret = 0;
		break;

	case VO_SET_FRAMERATE_ES:
		vo->framerate_es_num = arg >> 16;
		vo->framerate_es_den = arg & 0xffff;

		logm_debug (vo, "vo:%p, set es framerate %d/%d\n", vo,
				vo->framerate_es_num, vo->framerate_es_den);

		if (vo->force_framerate_num && vo->force_framerate_den)
		{
			vo->framerate_es_num = vo->force_framerate_num;
			vo->framerate_es_den = vo->force_framerate_den;
			logm_debug (vo, "vo:%p, overide framerate %d/%d\n", vo,
					vo->framerate_es_num,
					vo->framerate_es_den);
		}

		if (force_framerate_num && force_framerate_den)
		{
			vo->framerate_es_num = force_framerate_num;
			vo->framerate_es_den = force_framerate_den;
			logm_debug (vo, "vo:%p, overide framerate %d/%d\n", vo,
					vo->framerate_es_num,
					vo->framerate_es_den);
		}

		ret = 0;
		break;

	case VO_SET_FRAMERATE_CONTAINER:
		vo->framerate_container_num = arg >> 16;
		vo->framerate_container_den = arg & 0xffff;

		logm_debug (vo, "vo:%p, set container framerate %d/%d\n", vo,
				vo->framerate_container_num,
				vo->framerate_container_den);

		if (vo->force_framerate_num && vo->force_framerate_den)
		{
			vo->framerate_container_num = vo->force_framerate_num;
			vo->framerate_container_den = vo->force_framerate_den;
			logm_debug (vo, "vo:%p, overide framerate %d/%d\n", vo,
					vo->framerate_es_num,
					vo->framerate_es_den);
		}

		if (force_framerate_num && force_framerate_den)
		{
			vo->framerate_container_num = force_framerate_num;
			vo->framerate_container_den = force_framerate_den;
			logm_debug (vo, "vo:%p, overide framerate %d/%d\n", vo,
					vo->framerate_es_num,
					vo->framerate_es_den);
		}

		ret = 0;
		break;

	case VO_SET_QUEUE_SIZE:
		if (arg < MAX_QUEUE_SIZE)
		{
			vo->queue_size = arg;
			logm_debug (vo, "vo:%p, set queue size %d\n", vo,
					vo->queue_size);
			ret = 0;
		}
		else
		{
			logm_warning (vo, "vo:%p, too big queue size %d\n", vo,
					(int)arg);
			ret = -EINVAL;
		}

		break;

	case VO_GET_DISPLAYING_QUEUE_SIZE:
		if (vo->sync >= 0)
			a.queue_size = DISP_Q_NumActive (vo->sync);
		else
			a.queue_size = 0;
		logm_trace (vo, "vo:%p, get displaying queue size %d\n", vo,
				a.queue_size);
		ret = 0;
		break;

	case VO_GET_DISPLAYED_QUEUE_SIZE:
		{
			int head, tail;

			head = vo->displayed_queue_head;
			tail = vo->displayed_queue_tail;

			if (head >= tail)
				a.queue_size = head-tail;
			else
				a.queue_size = vo->displayed_queue_size
					- tail + head;

			logm_trace (vo, "vo:%p, get displayed queue size %d\n",
					vo, a.queue_size);

			ret = 0;
		}
		break;

	case VO_SET_3D:
		logm_debug (vo, "vo:%p, set 3d type %ld\n", vo, arg);
		if (arg > vo_3d_type_none)
		{
			logm_warning (vo, "vo:%p, unknown 3d type %08lx\n", vo, arg);
			ret = -EINVAL;
			break;
		}
		if (force_2d)
		{
			logm_debug (vo, "vo:%p, force set 2D\n", vo);
			vo->trid_type = vo_3d_type_none;
		}
		else
			vo->trid_type = arg;

		ret = 0;
		break;

	case VO_SET_TILE_BASE:
		vo->vdo_info = (struct vo_vdo_info*)a.tile_base;
		if (vo->vdo_info == NULL)
		{
			logm_debug (vo, "vo:%p, null vdo info. use raster\n",
					vo);
			vo->vdo_info = &vdo_info_raster;
		}

		logm_debug (vo, "vo:%p, tile base %08lx, maptype %d\n", vo,
				vo->vdo_info->tile_base,
				vo->vdo_info->map_type
				);

		ret = 0;
		break;

	case VO_SET_SPEED:
		vo->speed = arg;
		logm_noti (vo, "vo:%p, set speed %lx\n", vo, arg);
		if (vo->sync >= 0)
			VDISP_SetSpeed (vo->sync, vo->speed*1000/0x10000);
		ret = 0;
		break;

	case VO_GET_OUTPUT_INFO:
	case VO_GET_OUTPUT_INFO2:
		{
			int fr_num, fr_den;
			int width, height;

			a.output_info = output_info[vo->de_id];

			running_info (vo, &fr_num, &fr_den,
					&width, &height);

			if (!donot_update_info)
			{
				if (fr_den)
				{
					a.output_info.framerate_num = fr_num;
					a.output_info.framerate_den = fr_den;
				}

				if (cmd == VO_GET_OUTPUT_INFO2 &&
						width >= 0 && height >= 0)
				{
					a.output_info.width  = width;
					a.output_info.height = height;
				}
			}

			logm_debug (vo_mon, "output info %dx%d(%dx%d) %d/%d, %d\n",
					a.output_info.width,
					a.output_info.height,
					a.output_info.par_w,
					a.output_info.par_h,
					a.output_info.framerate_num,
					a.output_info.framerate_den,
					a.output_info.trid_type);

			ret = 0;
		}
		break;

	case VO_SET_DISPLAY_OFFSET:
		if (vo->sync >= 0)
		{
			logm_warning (vo, "vo:%p, set display offset after initialization\n", vo);
			ret = -EBUSY;
			break;
		}

		vo->display_offset = arg;
		logm_noti (vo, "vo:%p, set display offset %d\n", vo, vo->display_offset);
		ret = 0;
		break;

	case VO_SET_PAR:
		vo->par_w = arg>>16;
		vo->par_h = arg&0xffff;
		logm_noti (vo, "vo:%p, set par %dx%d\n", vo,
				vo->par_w, vo->par_h);

		if (force_par_w > 0 && force_par_h > 0)
		{
			vo->par_w = force_par_w;
			vo->par_h = force_par_h;
			logm_noti (vo, "vo:%p, fixup par %dx%d\n", vo,
					vo->par_w, vo->par_h);
		}

		if (vo->par_w <= 0 || vo->par_h <= 0)
		{
			logm_warning (vo, "vo:%p, wrong par %dx%d\n", vo,
					vo->par_w, vo->par_h);
			vo->par_w = vo->par_h = 1;
		}

		ret = 0;
		break;

	case VO_SET_LOW_LATENCY:
		if (vo->sync >= 0)
		{
			logm_warning (vo, "vo:%p, we have sync already\n", vo);
			ret = -EINVAL;
			break;
		}
		vo->low_delay = !!arg;
		if (vo->height <= 720)
		{
			logm_debug (vo, "vo:%p, set framerate 60\n", vo);
			vo->force_framerate_num = 60;
			vo->force_framerate_den = 1;
		}
		logm_debug (vo, "vo:%p, set low delay %d\n", vo, vo->low_delay);

		ret = 0;
		break;

	case VO_SET_CONSTANT_DELAY:
		vo->constant_delay = arg;
		logm_debug (vo, "vo:%p, set constant delay %d\n", vo,
				vo->constant_delay);
		ret = 0;
		break;

	case VO_SET_MIRROR_MODE:
		logm_debug (vo, "vo:%p, set mirror mode %d\n",
				vo, !!arg);

		VDISP_SetDualOutput (!!arg);

		{
			unsigned long flag;
			int m_deid;

			spin_lock_irqsave (&mirror_mode_lock, flag);
			mirror_mode = !!arg;
			m_deid = mirror_de_id;
			if (!mirror_mode)
				mirror_de_id = -1;
			spin_unlock_irqrestore (&mirror_mode_lock, flag);

			/* cleanup mirror */
			if (!mirror_mode && m_deid >= 0)
				vo_set_output_info (m_deid, 0, 0, 0, 0,
						0, 0, 0, vo_3d_type_none);
		}
		ret = 0;
		break;

	case VO_REPEAT_FRAME:
		/* repeat frames for paused output */
		logm_debug (vo, "vo:%p, repeat frames\n", vo);

		VDISP_RepeatFrame (0, (int)arg);
		VDISP_RepeatFrame (1, (int)arg);
		ret = 0;
		break;

	default:
		logm_warning (vo, "vo:%p, unknown ioctl %08x\n", vo, cmd);
		break;
	}

	if(ret < 0)
	{
		logm_warning (vo, "vo:%p, ioctl failed (cmd:%d, ret:%ld)\n",
				vo,
				_IOC_NR(cmd),
				ret);
	}

	if (ret >= 0 && _IOC_DIR(cmd) & _IOC_READ)
	{
		int r;

		r = copy_to_user ((void*)arg, &a, _IOC_SIZE(cmd));
		if (r)
		{
			logm_error (vo, "vo:%p, copy_to_user failed\n", vo);
			return -EFAULT;
		}
	}

	if (cmd != VO_GET_OUTPUT_INFO)
		logm_trace (vo, "vo:%p, cmd = %08x (cmd_idx=%d)\n", vo, cmd, _IOC_NR(cmd));
	return ret;
}


static struct file_operations vo_fops =
{
	.open		= vo_open,
	.release	= vo_release,
	.read		= vo_read,
	.write		= vo_write,
	.unlocked_ioctl	= vo_ioctl,
	.poll		= vo_poll,
};

static irqreturn_t vo_irq (int num, void *arg)
{
	unsigned int irqstatus = 0;
	unsigned int int_clear = 0;

	irqstatus = TOP_HAL_GetExtIntrStatus();
	if (!irqstatus)
		return IRQ_NONE;

	logm_trace (vo_irq, "status: %08x\n", irqstatus);

	if (irqstatus&(1<<VSYNC0))
	{
		static unsigned long long pre;
		static int gap_pre;

		unsigned long long now;
		int gap_now;

		now = sched_clock ();

		VDEC_ISR_VSync(0);

		gap_now = ((int)(now-pre))/1000;

		if (gap_now-gap_pre > 700 || gap_pre-gap_now > 700)
			logm_noti (vo_irq, "interval %dus, pre %dus\n",
					gap_now, gap_pre);
		else
			logm_debug (vo_irq, "interval %dus, pre %dus\n",
					gap_now, gap_pre);

		gap_pre = gap_now;
		pre = now;

		int_clear |= 1<<VSYNC0;
	}
	if (irqstatus&(1<<VSYNC1))
	{
		VDEC_ISR_VSync(1);

		int_clear |= 1<<VSYNC1;
	}
	if (irqstatus&(1<<VSYNC2))
	{
		VDEC_ISR_VSync(2);

		int_clear |= 1<<VSYNC2;
	}
	if (irqstatus&(1<<VSYNC3))
	{
		VDEC_ISR_VSync(3);

		int_clear |= 1<<VSYNC3;
	}
#if 0
	if (irqstatus&(1<<VSYNC4))
	{

		int_clear |= 1<<VSYNC4;
	}
#endif

	TOP_HAL_ClearExtIntrMsk(int_clear);
	logm_trace (vo_irq, "done\n");

	if (int_clear)
		return IRQ_HANDLED;
	else
		return IRQ_NONE;
}

int vo_init (void)
{
	int ret;

	logm_info (vo, "init..\n");

	ret = register_chrdev (major, "vo", &vo_fops);
	if (ret < 0)
	{
		logm_error (vo, "register_chrdev failed\n");
		return ret;
	}
	if (major == 0)
	{
		major = ret;
		logm_debug (vo, "major %d\n", major);
	}

	ret = request_irq (VDEC_MAIN_ISR_HANDLE, vo_irq, IRQF_SHARED, "video out", (void*)123);
	if (ret < 0)
	{
		logm_error (vo, "request_irq failed\n");
		return ret;
	}

	DISP_Q_Init ();
	VDISP_Init ();

	return 0;
}

void vo_exit (void)
{
	logm_info (vo, "exit..\n");
	free_irq (VDEC_MAIN_ISR_HANDLE, (void*)123);

	unregister_chrdev (major, "vo");
}

MODULE_LICENSE ("GPL");
//module_init (vo_init);
//module_exit (vo_exit);

