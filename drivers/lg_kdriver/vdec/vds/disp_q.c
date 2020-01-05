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

/**
 * @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     youngki.lyu@lge.com
 * version    1.0
 * date       2011.02.21
 * note       Additional information.
 *
 * @addtogroup lg1152_vdec
 * @{
 */


#include "disp_q.h"
#include "disp_clear_q.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <asm/string.h>	// memset

#include "../mcu/os_adap.h"

#include "../hal/ipc_reg_api.h"

#define LOG_NAME	vo_dispq
#include "log.h"



static struct
{
	S_DISPQ_BUF_T *buf;
	int head, tail;
	int size;

	wait_queue_head_t wait;
}q[DISP_Q_NUM_OF_CHANNEL];



void DISP_Q_Init(void)
{
	int ch;

	log_debug ("\n");

	for( ch = 0; ch < DISP_Q_NUM_OF_CHANNEL; ch++ )
		init_waitqueue_head (&q[ch].wait);

}

BOOLEAN DISP_Q_Open(int ch, UINT32 size)
{
	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_warning("dispq%d, wrong channel\n", ch);
		return FALSE;
	}

	q[ch].head = 0;
	q[ch].tail = 0;
	q[ch].buf = kmalloc (sizeof (q[ch].buf[0]) * size, GFP_KERNEL);
	if (q[ch].buf == NULL)
	{
		log_error ("dispq%d, no memory?? %d\n", ch, size);
		return FALSE;
	}

	q[ch].size = size;

	log_noti ("dispq%d,\n", ch);

	return TRUE;
}

void DISP_Q_Close(int ch)
{
	log_noti ("dispq%d,\n", ch);

	kfree (q[ch].buf);
	q[ch].buf = NULL;
	q[ch].size = 0;
}

BOOLEAN DISP_Q_Push_callback(int ch, S_DISPQ_BUF_T *data,
		void (*displayed_callback) (void *arg, S_DISPQ_BUF_T *buffer),
		void *displayed_callback_arg)
{
	int head, tail;

	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_warning("dispq%d, wrong channel\n", ch);
		return FALSE;
	}

	head = q[ch].head;
	tail = q[ch].tail;
	if ((head+1)%q[ch].size == tail)
	{
		log_warning ("dispq%d, queue overflowed %d, %d\n", ch, head, tail);
		return FALSE;
	}

	data->displayed_callback = displayed_callback;
	data->displayed_callback_arg = displayed_callback_arg;
	q[ch].buf[head] = *data;
	q[ch].head = (head+1)%q[ch].size;

	log_debug ("dispq%d, push %d %d\n", ch,
			q[ch].tail, q[ch].head);

	return TRUE;
}

static void add_to_clear_queue (void *arg, S_DISPQ_BUF_T *data)
{
	clear_q_t *clear_q = (clear_q_t*)arg;

	log_trace ("dispq%d,\n", 999);
	DISP_CLEAR_Q_Push_Index (clear_q, data->ui32FrameIdx);
}

BOOLEAN DISP_Q_Push_clearq (int ch, S_DISPQ_BUF_T *disp_buf, clear_q_t *clear_q)
{
	log_trace ("dispq%d,\n", ch);
	return DISP_Q_Push_callback (ch, disp_buf,
			add_to_clear_queue, (void*)clear_q);
}

wait_queue_head_t *DISP_Q_GetWait (int ch)
{
	return &q[ch].wait;
}


UINT32 DISP_Q_GetLatestDTS(int ch)
{
	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_error("[DISP_Q%d][Err] Channel Number, %s\n", ch, __FUNCTION__ );
		return 0xFFFFFFFF;
	}

	if( DISP_Q_NumActive( ch ) ==  0 )
		return 0xFFFFFFFF;

	return q[ch].buf[q[ch].tail].ui32DTS;
}

S_DISPQ_BUF_T* DISP_Q_Peep(int ch)
{
	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_error("[DISP_Q%d][Err] Channel Number, %s\n", ch, __FUNCTION__ );
		return NULL;
	}

	if( DISP_Q_NumActive( ch ) ==  0 )
		return NULL;

	return q[ch].buf + q[ch].tail;
}

UINT32 DISP_Q_GetLatestPTS(int ch)
{
	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_error("[DISP_Q%d][Err] Channel Number, %s\n", ch, __FUNCTION__ );
		return 0xFFFFFFFF;
	}

	if( DISP_Q_NumActive( ch ) ==  0 )
		return 0xFFFFFFFF;

	return q[ch].buf[q[ch].tail].ui32PTS;
}

BOOLEAN DISP_Q_Pop(int ch, S_DISPQ_BUF_T *buf)
{
	int tail;

	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_error("[DISP_Q%d][Err] Channel Number, %s\n", ch, __FUNCTION__ );
		return FALSE;
	}

	if( DISP_Q_NumActive( ch ) ==  0 )
		return FALSE;

	if (buf)
		*buf = q[ch].buf[q[ch].tail];

	/* proceed tail pointer */
	tail = q[ch].tail + 1;
	tail %= q[ch].size;
	q[ch].tail = tail;

	log_debug ("dispq%d, wakeup %d %d\n", ch,
			q[ch].tail, q[ch].head);

	wake_up (&q[ch].wait);

	return TRUE;
}

UINT32 DISP_Q_NumActive(int ch)
{
	int size;

	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		//log_error("[DISPQ%d][Err] Channel Number, %s\n", ch, __FUNCTION__ );
		return 0;
	}

	size = q[ch].head - q[ch].tail;
	if (size < 0)
		size += q[ch].size;

	log_trace ("dispq,%d, %d\n", ch,
			size);

	return size;
}

UINT32 DISP_Q_NumFree(int ch)
{
	int free;

	if( ch >= DISP_Q_NUM_OF_CHANNEL )
	{
		log_error("[DISPQ%d][Err] Channel Number, %s\n", ch, __FUNCTION__ );
		return 0;
	}

	free = q[ch].size - DISP_Q_NumActive(ch) - 1;

	log_debug ("dispq%d, %d\n", ch,
			free);

	return free;
}

