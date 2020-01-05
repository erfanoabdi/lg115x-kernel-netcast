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


/**
 * @file
 *
 *  main driver implementation for vdec device.
 *	vdec device will teach you how to make device driver with new platform.
 *
 *  author		seokjoo.lee (seokjoo.lee@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1152_vdec
 * @{
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <linux/mm.h>
#include <linux/rmap.h>
#include <linux/seq_file.h>
#include <linux/poll.h>
#include <linux/version.h>
#include <linux/smp.h>
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>

#include "hma_alloc.h"

#if 1
#include "proc_util.h"
#include "os_util.h"
#endif

#include "base_device.h"
#include "vdec_drv.h"
#include "vdec_kapi.h"

#include "ves/ves_auib.h"

#include "vdc/vdc_drv.h"

#include "vds/vdec_rate.h"
#include "vds/pts_drv.h"
#include "vds/vdisp_drv.h"
#include "vds/disp_q.h"

#include "mcu/vdec_isr.h"
#include "mcu/ipc_req.h"
#include "mcu/ipc_callback.h"

#include "hal/vdec_base.h"
#include "hal/top_hal_api.h"
#include "hal/lq_hal_api.h"
#include "hal/vsync_hal_api.h"
#include "hal/de_ipc_hal_api.h"
#include "hal/ipc_reg_api.h"
#include "hal/de_vdo_hal_api.h"
#include "hal/av_lipsync_hal_api.h"

#include <vo_kapi.h>


#define	VDEC_MODULE	"vdec"


#include "log.h"

logm_define (vdec, log_level_warning);
logm_define (vdec_userdata, log_level_warning);
logm_define (vdec_dpbdump, log_level_warning);
logm_define (vdec_cpbdump, log_level_warning);

static int vdec_enable_userdata = 1;
module_param (vdec_enable_userdata, int, 0644);

static int vdec_force_raster_memory;
module_param (vdec_force_raster_memory, int, 0644);

static int vdec_default_cpb_size = 0x700000;
module_param (vdec_default_cpb_size, int, 0644);

static int vdec_force_frame_alternation;
module_param (vdec_force_frame_alternation, int, 0644);

static int vdec_force_framerate_num;
static int vdec_force_framerate_den;
module_param (vdec_force_framerate_num, int, 0644);
module_param (vdec_force_framerate_den, int, 0644);

struct proc_dir_entry *vdec_proc_root_entry;

static struct workqueue_struct *vdec_workqueue;;

typedef struct _noti
{
	wait_queue_head_t wq;

	unsigned int mask;
	int size;
	volatile int head;
	volatile int tail;

	void *data;

	spinlock_t write_lock;
	struct mutex read_lock;

	LX_VDEC_OUTPUT_T	output;
} noti_t;


struct dpbdump
{
	wait_queue_head_t wq;

	decoded_buffer_t *cur;

	/* for tiled */
	unsigned char *fb;
	int fb_size;

	/* for raster */
	unsigned char *fb_y, *fb_c;
	int fb_size_y, fb_size_c;

	int fb_readed;

	decoded_buffer_t **data;
	int size;
	int head;
	int tail;
};

struct cpbdump
{
	wait_queue_head_t wq;

	unsigned char *addr;

	int now, readed;
};

struct decoded_info
{
	int user;

	decoded_buffer_t buffer;

	struct decoded_info *next;
};


typedef struct vdec vdec_t;
struct vdec
{
	noti_t noti;

	struct file *file;

	LX_VDEC_SRC_T src;
	LX_VDEC_DST_T dest;

	LX_VDEC_OPMODE_T opmode;
	LX_VDEC_CODEC_T codec;
	LX_VDEC_PIC_SCAN_T scan_mode;

//#define lx_vdec_flags_pollerr	(1<<0)
	unsigned int flags;

	char proc_name[17];
	struct proc_dir_entry *proc_entry;
	struct proc_dir_entry *proc_status;
	struct proc_dir_entry *proc_cpb;
	struct proc_dir_entry *proc_dpb;

	struct mutex submodule_lock;
	spinlock_t submodule_spin_lock;

	/* ??? */
	unsigned char clock_id;

	int new_apiset;
	enum vo_3d_type trid_type;

	int userdata_thief;
	unsigned long id;

	int framerate_num;
	int framerate_den;
	LX_VDEC_MEMORY_FORMAT_T output_memory_format;
	int seqh_done;

	struct vo_vdo_info *vdo_info;

	/* instance of submodules */
	int ves;
	int vdc;
	int sync;

	unsigned long cpb_addr;
	int cpb_size;
	int cpb_allocated;

	/* display queue */
	int display_offset;
	int display_q_maxsize;
	int use_gstc;
	int use_gstc_have_cut;

	/* clear queue */
	clear_q_t *clear_q;
	int kick_decoder_count;

	/* decoded queue */
	decoded_q_t decoded_q;
	struct decoded_info *decoded_infos;
	spinlock_t decoded_buffers_lock;
	int frame_displaied;
	int frame_requested;

	/* decoding queue */
	int decoding_queue_size;
	int decoding_queue_slots;
	int flushed;

	/* dpbdump */
	spinlock_t dpbdump_lock;
	struct dpbdump dpbdump;

	/* cpbdump */
	struct cpbdump cpbdump;

	int debug_counter;

	vdec_t *next;
};

static vdec_t *device_list;
static DEFINE_SPINLOCK (device_list_lock);

static DEFINE_MUTEX (io_lock);


/**
 * get decoded information.
 *
 * @param noti [IN]	from which noti channel to retrive decoded information.
 *
 * @return pointer to saved LX_VDEC_OUTPUT_T structure.
 *
 * @see LX_VDEC_OUTPUT_T
 */
static LX_VDEC_OUTPUT_T *noti_GetOutput (noti_t *noti)
{
	return &noti->output;
}

/**
 * Allocates Notification Queue.
 *
 * After open() before Enable notification via ioctl ( LX_VDEC_IO_SET_NOTIFY )
 *
 * @param size	[IN] queue size in number of events.
 *
 * @return 1 really allocated, zero for previously allocated. negative when error
 */
static int noti_alloc (noti_t *noti, int size)
{
	vdec_t *vdec = container_of (noti, vdec_t, noti);

	noti->mask = 0;
	noti->size = size;
	noti->head = noti->tail = 0;
	noti->data = vmalloc (size);
	init_waitqueue_head(&noti->wq);

	spin_lock_init(&noti->write_lock);
	mutex_init (&noti->read_lock);

	logm_debug (vdec, "vdec:%p, size %d\n", vdec, size);

	if (noti->data == NULL)
	{
		logm_warning (vdec, "vdec:%p, kmalloc failed\n",
				vdec);
		return -ENOMEM;
	}

	return 0;
}

/**
 * Frees a Notification queue.
 * [NOTE]
 * This should be
 * called AFTER detached from notification list.
 * called unlocked for notification list.
 *
 * @param noti	[IN] pointer to a notification queue to be freed.
 */
// [task context]
static void noti_free (noti_t *noti)
{
	vdec_t *vdec = container_of (noti, vdec_t, noti);

	logm_debug (vdec, "vdec:%p\n", vdec);
	vfree (noti->data);
}

/**
 * Enable/Disable notification.
 * Implicitly, only enable/disable for given process.
 * @param noti	[IN] noti for search.
 * @param arg	[IN] notification ID see @ref LX_VDEC_NOTIFY_ID_SEQH
 */
// [task context]
static void noti_set_mask(noti_t *noti, unsigned int mask)
{
	vdec_t *vdec = container_of (noti, vdec_t, noti);

	logm_debug (vdec, "vdec:%p set mask %08x\n", vdec, mask);
	noti->mask = mask;
}

/**
 * save notify paramter
 */
// [interrupt context]
static void noti_save(noti_t *noti, unsigned int id,
		void *data, unsigned int real_size)
{
	vdec_t *vdec = container_of (noti, vdec_t, noti);
	int filled;
	int head;
	int count1, count2;
	unsigned int size;
	unsigned long flag;

	spin_lock_irqsave (&noti->write_lock, flag);
	head = noti->head;

	logm_debug (vdec, "vdec:%p, %c%c%c%c, %d bytes, %d %d\n", vdec,
			(id>>0)&0xff,
			(id>>8)&0xff,
			(id>>16)&0xff,
			(id>>24)&0xff,
			real_size, noti->tail, head);

	/* align 4 bytes */
	size = (real_size+3)&~3;

	/* check buffer overflow */
	filled = head - noti->tail;
	if (filled < 0)
		filled += noti->size;

	if (filled + size + 8 >= noti->size)
	{
		logm_noti (vdec, "vdec:%p, noti queue full %d, %d, "
				"size %d, %c%c%c%c\n",
				vdec, noti->tail, head,
				real_size,
				(id>>0)&0xff,
				(id>>8)&0xff,
				(id>>16)&0xff,
				(id>>24)&0xff
				);
		goto failed;
	}

	/* put size, size includes id */
	*(unsigned int*)(noti->data + head) = real_size+4;
	head += 4;
	head %= noti->size;

	/* put id */
	*(unsigned int*)(noti->data + head) = id;
	head += 4;
	head %= noti->size;

	/* put data */
	if (head + real_size <= noti->size)
	{
		count1 = real_size;
		count2 = 0;
	}
	else
	{
		count1 = noti->size - head;
		count2 = real_size - count1;
	}
	if (count1)
		memcpy (noti->data+head, data, count1);
	if (count2)
		memcpy (noti->data, data+count1, count2);
	head += size;
	head %= noti->size;
	noti->head = head;

	wake_up (&noti->wq);

failed:
	spin_unlock_irqrestore (&noti->write_lock, flag);
}

static void noti_save_SEQH(noti_t *noti, LX_VDEC_NOTIFY_PARAM_SEQH_T *pSeqh)
{
	LX_VDEC_NOTIFY_PARAM2_T	param;

	param.magic = LX_VDEC_NOTIFY_MAGIC;;
	param.id = LX_VDEC_NOTIFY_ID_SEQH;
	param.u.seqh = *pSeqh;

	noti_save(noti, LX_VDEC_NOTIFY_MAGIC, &param.id, sizeof (param)-4);
}

static void noti_save_PICD(noti_t *noti, LX_VDEC_NOTIFY_PARAM_PICD_T *pOut)
{
	LX_VDEC_NOTIFY_PARAM2_T	param;

	param.magic = LX_VDEC_NOTIFY_MAGIC;;
	param.id = LX_VDEC_NOTIFY_ID_PICD;
	param.u.picd = *pOut;

	noti_save(noti, LX_VDEC_NOTIFY_MAGIC, &param.id, sizeof (param)-4);
}

static void noti_save_DISP(noti_t *noti, LX_VDEC_NOTIFY_PARAM_DISP_T *pDisp)
{
	LX_VDEC_NOTIFY_PARAM2_T	param;

	param.magic = LX_VDEC_NOTIFY_MAGIC;;
	param.id = LX_VDEC_NOTIFY_ID_DISP;
	param.u.disp = *pDisp;

	noti_save(noti, LX_VDEC_NOTIFY_MAGIC, &param.id, sizeof (param)-4);
}

static void noti_save_USRD(noti_t *noti, LX_VDEC_NOTIFY_PARAM_USRD_T *user_data)
{
	LX_VDEC_NOTIFY_PARAM2_T	param;

	param.magic = LX_VDEC_NOTIFY_MAGIC;;
	param.id = LX_VDEC_NOTIFY_ID_USRD;
	param.u.usrd = *user_data;

	noti_save(noti, LX_VDEC_NOTIFY_MAGIC, &param.id, sizeof (param)-4);
}


/**
 * copy to user buffer from saved notification queue.
 *
 * @param noti		[IN] channel for search.
 * @param notifyID	[IN] notification ID see @ref LX_VDEC_NOTIFY_ID_SEQH
 * @return non-negative number of bytes copied, negative when error.
 */
// [task context]
static int noti_copy(noti_t *noti, char __user *buffer, size_t buffer_size)
{
	vdec_t *vdec = container_of (noti, vdec_t, noti);
	int ret;
	int tail;
	int count1, count2;
	unsigned int unit_size;

	mutex_lock (&noti->read_lock);

	tail = noti->tail;
	unit_size = *(unsigned int*)(noti->data+tail);
	tail += 4;
	tail %= noti->size;

	logm_debug (vdec, "vdec:%p, read %d bytes, %d %d\n", vdec,
			unit_size, noti->tail, noti->head);

	if (tail + unit_size <= noti->size)
	{
		count1 = unit_size;
		count2 = 0;
	}
	else
	{
		count1 = noti->size - tail;
		count2 = unit_size - count1;
	}

	if (buffer_size < unit_size)
	{
		logm_warning (vdec, "vdec:%p, too small buffer size %d<%d\n",
				vdec, buffer_size, unit_size);
		ret = -EAGAIN;
		goto failed;
	}

	ret = copy_to_user(buffer, noti->data+tail, count1);
	if (ret)
	{
		logm_warning (vdec, "vdec:%p, oops\n", vdec);
		ret = -EFAULT;
		goto failed;
	}
	if (count2)
	{
		ret = copy_to_user(buffer+count1, noti->data, count2);
		if (ret)
		{
			logm_warning (vdec, "vdec:%p, oops\n", vdec);
			ret = -EFAULT;
			goto failed;
		}
	}

	tail += unit_size+3;
	tail &= ~3;
	tail %= noti->size;
	noti->tail = tail;

	ret = unit_size;

failed:
	mutex_unlock (&noti->read_lock);

	return ret;
}

#ifdef _OLD_LOG_H
typedef struct 
{
	char name[24];
	void (*fpSetLogLevel)(int);
} LOG_CMD_T;

static LOG_CMD_T log_cmd[32];

#define _reg_log_cmd(logName, cmdNum)		\
do{		\
	extern void vdec_set_log_level_ ##logName(int);		\
	strcpy(log_cmd[cmdNum].name, #logName);			\
	log_cmd[cmdNum].fpSetLogLevel = vdec_set_log_level_ ##logName;	\
}while(0)

static int _VDEC_PROC_Reader(UINT32 procId, char* buffer )
{
	int ret=0, i;

	for(i=0; i<32; i++)
	{
		if( log_cmd[i].fpSetLogLevel != NULL )
			ret += sprintf( buffer+ret, "%2d : %s\n", i, log_cmd[i].name );
	}

	return ret;
}

static void _VDEC_SetLogLevels( UINT32 u32LogMask, UINT32 lv )
{
	UINT32 i;

	for(i=0;i<32;i++)
	{
		if( u32LogMask & (1<<i) )
		{
			if( log_cmd[i].fpSetLogLevel != NULL )
				log_cmd[i].fpSetLogLevel(lv);
		}
	}
}


enum {
	PROC_ID_LOGMASK	= 0,
	PROC_ID_MAX,
};

static OS_PROC_DESC_TABLE_T	_g_vdec_device_proc_table[] =
{
	{ "logmask",		PROC_ID_LOGMASK, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

static int _VDEC_PROC_Writer( UINT32 procId, char* command )
{
	SINT32	lv;
	UINT32  mask, n=0, ret;
	char	*param[10];

	ret = strlen(command);

	switch( procId )
	{
		case PROC_ID_LOGMASK:
			while( command != NULL && n < 10 )
				param[n++] = strsep(&command, " 	");

			if( param[0][0] == '0' && param[0][1] == 'x' )
			{
				mask = simple_strtoul(param[0], NULL, 0);
				if(n > 1)
					lv = simple_strtol(param[1], NULL, 0);
				else
					lv = 9;
			}
			else
			{
				if(n > 1)
				{
					mask = 1 << simple_strtoul(param[0], NULL, 0);
					lv = simple_strtol(param[1], NULL, 0);
				}
				else
				{
					mask = 0xFFFFFFFF;
					lv = simple_strtoul(param[0], NULL, 0);
				}
			}

			printk("vdec set 0x%X mask's level to %d\n", mask, lv);
			_VDEC_SetLogLevels(mask, lv);

			break;
	}

	return ret;
}
#endif

static void proc_init(void)
{
	vdec_proc_root_entry = proc_mkdir ("lxvdec", NULL);

#ifdef _OLD_LOG_H
	OS_PROC_CreateEntryEx( VDEC_MODULE, _g_vdec_device_proc_table, 
			_VDEC_PROC_Reader, _VDEC_PROC_Writer);

	// TOP
	_reg_log_cmd(vdec, 0);

	// PDEC Related
	_reg_log_cmd(vdec_ves, 4);

	// Feeder&VDC Related
	_reg_log_cmd(vdec_vdc, 5);

	// BODA
	_reg_log_cmd(vdec_vdu, 8);
	_reg_log_cmd(vdec_perf, 10);

	// VO
	_reg_log_cmd(vo_dispq, 12);
	_reg_log_cmd(vdec_cq, 13);
	_reg_log_cmd(vo, 14);

	// SYNC
	_reg_log_cmd(vdec_dqpop, 16);
	_reg_log_cmd(vdec_pts, 17);
	_reg_log_cmd(vdec_hal_deipc, 18);
	_reg_log_cmd(vdec_hal_vdo, 19);
	_reg_log_cmd(vdec_de_if, 20);
	_reg_log_cmd(vdec_rate, 21);
	_reg_log_cmd(vdec_vsync, 22);
	_reg_log_cmd(vdec_hal_vsync, 23);
#endif
}

static void proc_cleanup (void)
{
#ifdef _OLD_LOG_H
	OS_PROC_RemoveEntry( VDEC_MODULE );
#endif

	remove_proc_entry ("lxvdec", NULL);
}

static UINT32	ui32ActiveSrc;
static UINT32	ui32ActiveDst;


static void VDEC_CH_Init(void)
{
	// HAL_Init
	TOP_HAL_Init();
	PDEC_HAL_Init();
	LQ_HAL_Init();
	VSync_HAL_Init();
	DE_IPC_HAL_Init();
	IPC_REG_Init();
	DE_VDO_HAL_Init();
	AV_LipSync_HAL_Init();

	IPC_REQ_Init();
	IPC_CALLBACK_Init();

	ui32ActiveSrc = 0x0;
	ui32ActiveDst = 0x0;

	VES_Init();
	VES_AUIB_Init();
	VES_CPB_Init();

	VDC_Init();

	DISP_CLEAR_Q_Init();
	DISP_Q_Init();
	VDISP_Init();
}

static int kick_decoder_locked (vdec_t *vdec)
{
	if (vdec->vdc == 0xff)
	{
		logm_debug (vdec, "vdec:%p, no vdc\n", vdec);
		return 0;
	}

	if (
			vdec->frame_requested < 0 ||
			vdec->frame_requested > vdec->frame_displaied
	   )
	{
		logm_debug (vdec, "vdec:%p, kick decoder\n", vdec);
		VDC_Update (vdec->vdc);
	}
	else
		logm_debug (vdec, "vdec:%p, no more picture needed\n",
				vdec);

	return 0;
}

static void kick_decoder_ws (struct work_struct *work)
{
	unsigned long flag;
	vdec_t *vdec;
	vdec_t *now;

check_again:
	spin_lock_irqsave (&device_list_lock, flag);
	now = device_list;
	vdec = NULL;
	while (now)
	{
		if (now->kick_decoder_count)
		{
			vdec = now;
			logm_debug (vdec, "vdec:%p, kick decoder count %d\n",
					vdec, vdec->kick_decoder_count);
			vdec->kick_decoder_count = 0;
			break;
		}

		now = now->next;
	}
	spin_unlock_irqrestore (&device_list_lock, flag);

	if (vdec == NULL)
		return;

	mutex_lock (&vdec->submodule_lock);
	kick_decoder_locked (vdec);
	mutex_unlock (&vdec->submodule_lock);

	goto check_again;
}

static DECLARE_WORK (kick_decoder_work, kick_decoder_ws);

static int unref_frame (vdec_t *vdec, unsigned long y)
{
	struct decoded_info *now, *pre = NULL, *selected = NULL, *selected_pre;
	int a;
	int ret;
	unsigned long flag;

	logm_debug (vdec, "vdec:%p, y:%07lx\n", vdec, y);

	if (vdec->vdc == 0xff)
	{
		logm_noti (vdec, "vdec:%p, unref while closing vdc\n",
				vdec);
		return -EFAULT;
	}

	spin_lock_irqsave (&vdec->decoded_buffers_lock, flag);
	for (a=0,now=vdec->decoded_infos; now; now=now->next,a++)
	{
		if (now->buffer.addr_y == y &&
				now->user > 0)
		{

			logm_debug (vdec, "vdec:%p, ""info index %d, "
					"push index:%x, y:%07lx, user %d\n",
					vdec, a,
					now->buffer.buffer_index,
					y, now->user);

			selected = now;
			selected_pre = pre;
		}

		pre = now;
	}

	if (selected)
	{
		selected->user --;
		if (selected->user == 0)
		{
			logm_debug (vdec, "vdec:%p, "
					"push to clear queue\n",
					vdec);
			DISP_CLEAR_Q_Push_Index (vdec->clear_q,
					selected->buffer.buffer_index);

			if (selected == vdec->decoded_infos)
				vdec->decoded_infos = selected->next;
			else
				selected_pre->next = selected->next;

			kfree (selected);
		}

		ret = 0;
	}
	else
	{
		logm_warning (vdec, "vdec:%p, unknown y address %07lx\n", vdec, y);
		ret = -EFAULT;
	}
	spin_unlock_irqrestore (&vdec->decoded_buffers_lock, flag);

	return 0;
}

static int unref_frame_and_kick_decoder_locked (vdec_t *vdec, unsigned long y)
{
	int ret;

	ret = unref_frame (vdec, y);
	if (ret < 0)
		return ret;
	return kick_decoder_locked (vdec);
}

static void unref_frame_fromsync (void *arg, S_DISPQ_BUF_T *buf)
{
	vdec_t *vdec = (vdec_t *)arg;
	LX_VDEC_OUTPUT_T *out;
	unsigned long flag;

	if (buf->bDispResult != 0)
	{
		out = noti_GetOutput (&vdec->noti);

		out->display.UId		= buf->ui32UId;
		out->display.pts 		= buf->ui32PTS;
		out->display.bPtsMatched	= 1;
		out->display.u32NumDisplayed	= 0;
		out->display.u32DqOccupancy	= DISP_Q_NumActive(vdec->sync);
		out->display.u32PicWidth	= buf->ui32PicWidth;
		out->display.u32PicHeight	= buf->ui32PicHeight;
		out->display.u64Timestamp	= buf->ui64TimeStamp;

		logm_debug (vdec, "vdec:%p, uid %08x, pts %08x\n", vdec,
				out->display.UId,
				out->display.pts);

		noti_save_DISP(&vdec->noti,
				(LX_VDEC_NOTIFY_PARAM_DISP_T *)&out->display);
	}
	else
		logm_debug (vdec, "vdec:%p, no display noti\n", vdec);

	spin_lock_irqsave (&vdec->submodule_spin_lock, flag);
	unref_frame (vdec, buf->ui32Y_FrameBaseAddr);
	spin_unlock_irqrestore (&vdec->submodule_spin_lock, flag);

	/* kick decoder */
	vdec->kick_decoder_count ++;
	queue_work (vdec_workqueue, &kick_decoder_work);
}

static int decoded_queue_flush (decoded_q_t *q)
{
	vdec_t *vdec = container_of (q, vdec_t, decoded_q);

	logm_debug (vdec, "vdec:%p, flushing\n", vdec);

	if (vdec->new_apiset)
		noti_save (&vdec->noti, LX_VDEC_READ_MAGIC("FLSH"),
				NULL, 0);

	vdec->frame_displaied = 0;

	return 0;
}

static int display_picture (vdec_t *vdec, struct decoded_info *info)
{
	long long ts;
	unsigned long flag;
	decoded_buffer_t *buf = &info->buffer;

	ts = info->buffer.timestamp;

	vdec->frame_displaied ++;
	logm_debug (vdec, "vdec:%p, pts %08x, ts %llu, %d\n", vdec,
			buf->pts, ts, vdec->frame_displaied);

	/* send user data */
	if (buf->user_data_size > 0 && vdec_enable_userdata)
	{
		LX_VDEC_NOTIFY_PARAM_USRD_T user_data = {0, };
		vdec_t *now;
		unsigned long flag;

		/* log print */
		if (logm_enabled (vdec_userdata, log_level_debug))
		{
			int a, len;

			len = buf->user_data_size;
			if (len > 256)
				len = 256;

			logm_debug (vdec_userdata, "vdec:%p, user data %p, size %d\n",
					vdec, buf->user_data_addr, buf->user_data_size);
			for (a=0; a<len; )
			{
				char tmp[32*3+1];
				int b;

				for (b=0; b<32 && a+b<len; b++)
					sprintf (tmp+b*3, "%02x ",
							((unsigned char*)buf->user_data_addr)[a+b]);
				tmp[b*3] = 0;;

				logm_debug (vdec_userdata, "%3d: %s\n",
						a, tmp);

				a += b;
			}
		}

		switch (buf->picture_type)
		{
		case decoded_buffer_picture_type_i:
			user_data.picType = 0;
			break;

		case decoded_buffer_picture_type_p:
			user_data.picType = 1;
			break;

		default:
		case decoded_buffer_picture_type_b:
			user_data.picType = 2;
			break;
		}
		user_data.offset	= 0;
		user_data.size		= 0;
		user_data.decoder_id	= vdec->id;
		user_data.top_ff	= buf->top_field_first;
		user_data.rpt_ff	= buf->repeat_first_field;
		noti_save_USRD (&vdec->noti, &user_data);

		noti_save (&vdec->noti, LX_VDEC_READ_MAGIC ("USRD"),
				buf->user_data_addr,
				buf->user_data_size);

		/* broad cast for user data thief */
		spin_lock_irqsave (&device_list_lock, flag);
		now = device_list;
		while (now)
		{
			if (now->userdata_thief && now != vdec)
			{
				logm_debug (vdec, "vdec:%p, send to %p\n",
						vdec, now);

				noti_save_USRD (&now->noti, &user_data);

				noti_save (&now->noti,
						LX_VDEC_READ_MAGIC ("USRD"),
						buf->user_data_addr,
						buf->user_data_size);
			}

			now = now->next;
		}
		spin_unlock_irqrestore (&device_list_lock, flag);
	}

	/* put the picture to the output device */
	if (vdec->new_apiset && vdec->sync == 0xff)
	{
		/*
		 * 할 것 없음.  decode 됐을 때 모든 정보가 lxvdec으로 올라가며,
		 * user layer에서 알아서 출력 제어를 함
		 */
	}
	else if (vdec->dest == LX_VDEC_DST_BUFF)
	{
		/* if output to the memory */ 
		LX_VDEC_NOTIFY_PARAM_PICD_T picd;

		/* add to noti */
		memset (&picd, 0, sizeof(picd));

		picd.UId = buf->uid;
		picd.display = 1;
		picd.frm.tile_base = 0;		// middleware do not need this one
		picd.frm.pY  = buf->addr_y;
		picd.frm.pCb = buf->addr_cb;
		picd.frm.pCr = 0;
		picd.frm.width  = buf->width;
		picd.frm.height = buf->height;
		picd.frm.stride = buf->stride;
		picd.m.frameRateRes = buf->framerate_num;
		picd.m.frameRateDiv = buf->framerate_den;
		picd.m.par_w = buf->par_w;
		picd.m.par_h = buf->par_h;
		switch (buf->interlace)
		{
		default:
			logm_warning (vdec, "unknown field info %d\n",
					buf->interlace);
			picd.interlace = lx_vdec_interlace_none;
			break;

		case decoded_buffer_interlace_none:
			picd.interlace = lx_vdec_interlace_none;
			break;

		case decoded_buffer_interlace_top_first:
			picd.interlace = lx_vdec_interlace_top_first;
			break;

		case decoded_buffer_interlace_bottom_first:
			picd.interlace = lx_vdec_interlace_bottom_first;
			break;
		}

		//if (vdec->output_memory_format == LX_VDEC_MEMORY_FORMAT_RASTER)
			vdec->noti.output.decode = picd;

		noti_save_PICD (&vdec->noti, &picd);
	}

	if (vdec->sync != 0xff)
	{
		S_DISPQ_BUF_T _buf;
		int de_id;
		enum vo_3d_type trid_type;
		struct vo_vdo_info *vdo_info =
			(struct vo_vdo_info*)buf->addr_tile_base;

		memset (&_buf, 0, sizeof(_buf));

		if (vdec->opmode == LX_VDEC_OPMOD_LOW_LATENCY)
		{
			logm_debug (vdec, "vdec:%p, low latency, "
					"change framerate %d/%d -> %d/%d\n",
					vdec,
					buf->framerate_num, vdec->framerate_den,
					60, 1);

			buf->framerate_num = 60;
			buf->framerate_den = 1;
		}

		/* cut base_stc and base_pts now if we use gstc */
		if (
				vdec->use_gstc &&
				!vdec->use_gstc_have_cut &&
				LX_VDEC_SRC_SDEC0 <= vdec->src &&
				vdec->src <= LX_VDEC_SRC_SDEC2
		   )
		{
			unsigned int base_stc, base_pts;

			base_stc = TOP_HAL_GetGSTCC();
			base_pts = buf->pts;

			logm_debug (vdec, "vdec:%p, got base stc %x, pts %x\n",
					vdec, base_stc, base_pts);

			AV_Set_AVLipSyncBase (vdec->src - LX_VDEC_SRC_SDEC0, &base_stc, &base_pts);

			logm_debug (vdec, "vdec:%p, set base stc %x, pts %x\n",
					vdec, base_stc, base_pts);
			vdec->use_gstc_have_cut = 1;

			VDISP_SetBaseTime (vdec->sync,	base_stc, base_pts);
		}

		_buf.ui32Tiled_FrameBaseAddr = vdo_info->tile_base;
		switch (vdo_info->map_type)
		{
		default:
		case vdo_map_type_linear:
			_buf.ui32DpbMapMode = DISPQ_LINEAR_MAP_DPB;
			break;

		case vdo_map_type_frame:
			_buf.ui32DpbMapMode = DISPQ_FRAME_MAP_DPB;
			break;

		case vdo_map_type_mixed:
			_buf.ui32DpbMapMode = DISPQ_MIXED_MAP_DPB;
			break;
		}
		_buf.ui32Y_FrameBaseAddr = buf->addr_y;
		_buf.ui32C_FrameBaseAddr = buf->addr_cb;
		_buf.ui32Y_FrameOffset = 0;
		_buf.ui32C_FrameOffset = 0;
		_buf.ui32Stride = buf->stride;
		_buf.FrameFormat = DISPQ_FRAME_FORMAT_420;
		if (
				vdec->framerate_num &&
				(
				 buf->framerate_num != vdec->framerate_num ||
				 buf->framerate_den != vdec->framerate_den
				)
		   )
		{
			logm_debug (vdec, "vdec:%p, change framerate "
					"from %d/%d to %d/%d\n",
					vdec,
					buf->framerate_num,
					buf->framerate_den,
					vdec->framerate_num,
					vdec->framerate_den);
			_buf.ui32FrameRateRes = vdec->framerate_num;
			_buf.ui32FrameRateDiv = vdec->framerate_den;
		}
		else
		{
			_buf.ui32FrameRateRes = buf->framerate_num;
			_buf.ui32FrameRateDiv = buf->framerate_den;
		}
		if (vdec_force_framerate_num)
		{
			logm_debug (vdec, "vdec:%p, force framerate %d/%d\n",
					vdec,
					vdec_force_framerate_num,
					vdec_force_framerate_den);
			_buf.ui32FrameRateRes = vdec_force_framerate_num;
			_buf.ui32FrameRateDiv = vdec_force_framerate_den;
		}
		_buf.bVariableFrameRate = 0;
		_buf.ui32FrameIdx = buf->buffer_index;
		_buf.ui32AspectRatio = 0;
		_buf.ui32PicWidth = buf->width;
		_buf.ui32PicHeight = buf->height;
		_buf.ui32H_Offset = buf->crop_left<<16 | buf->crop_right;
		_buf.ui32V_Offset = buf->crop_top<<16 | buf->crop_bottom;
		_buf.bFieldPicture = 0;
		switch (buf->interlace)
		{
		default:
		case decoded_buffer_interlace_none:
			_buf.ui32DisplayInfo = DISPQ_SCAN_PROG;
			break;

		case decoded_buffer_interlace_top_first:
			_buf.ui32DisplayInfo = DISPQ_SCAN_TFF;
			break;

		case decoded_buffer_interlace_bottom_first:
			_buf.ui32DisplayInfo = DISPQ_SCAN_BFF;
			break;
		}
		_buf.ui32DTS = buf->dts;
		if (buf->pts != VDEC_UNKNOWN_PTS)
			_buf.ui32PTS = buf->pts;
		else if (ts != -1)
		{
			unsigned long long _pts = ts*9;

			do_div(_pts,100000);
			_buf.ui32PTS = _pts;
		}
		else
			_buf.ui32PTS = VDEC_UNKNOWN_PTS;
		_buf.ui64TimeStamp = ts;
		_buf.ui32UId = buf->uid;
		_buf.ui32DisplayPeriod = buf->display_period;
		_buf.i32FramePackArrange = buf->frame_packing_arrangement;
		switch (buf->multi_picture)
		{
		default:
		case decoded_buffer_multi_picture_none:
			_buf.ui32LR_Order = DISPQ_3D_FRAME_NONE;
			break;

		case decoded_buffer_multi_picture_left:
			_buf.ui32LR_Order = DISPQ_3D_FRAME_LEFT;
			break;

		case decoded_buffer_multi_picture_right:
			_buf.ui32LR_Order = DISPQ_3D_FRAME_RIGHT;
			break;
		}
		_buf.ui16ParW = buf->par_w;
		_buf.ui16ParH = buf->par_h;

		_buf.bDiscont = buf->stc_discontinuity;

		DISP_Q_Push_callback (vdec->sync, &_buf, unref_frame_fromsync, vdec);

		logm_debug (vdec, "vdec:%p, display queue pushed. qlen %d\n",
				vdec, DISP_Q_NumActive (vdec->sync));

		/* update output status */
		switch (vdec->dest)
		{
		default:
			logm_warning (vdec, "vdec:%p, unknown dest %d\n",
					vdec, vdec->dest);
			de_id = 0;
			break;

		case LX_VDEC_DST_DE0: de_id = 0; break;
		case LX_VDEC_DST_DE1: de_id = 1; break;
		}

		if (vdec->trid_type != vo_3d_type_none)
			trid_type = vdec->trid_type;
		else if (buf->frame_packing_arrangement < 0)
			trid_type = vo_3d_type_none;
		else if (buf->frame_packing_arrangement > vo_3d_type_fpa_end)
			trid_type = vo_3d_type_none;
		else
			trid_type = buf->frame_packing_arrangement;

		vo_set_output_info (de_id,
				buf->width - buf->crop_left - buf->crop_right,
				buf->height - buf->crop_top - buf->crop_bottom,
				buf->framerate_num, buf->framerate_den,
				_buf.ui16ParH, _buf.ui16ParH,
				buf->interlace == decoded_buffer_interlace_none,
				trid_type
				);
	}

	spin_lock_irqsave (&vdec->dpbdump_lock, flag);
	if (vdec->dpbdump.data)
	{
		int head, tail;

		head = vdec->dpbdump.head;
		tail = vdec->dpbdump.tail;

		if ((head+1)%vdec->dpbdump.size != tail)
		{
			/* give additional user count for dpb dup */
			info->user ++;

			vdec->dpbdump.data[head] = buf;
			head ++;
			head %= vdec->dpbdump.size;
			vdec->dpbdump.head = head;

			wake_up (&vdec->dpbdump.wq);
		}
		else
			logm_warning (vdec, "vdec:%p, dpbdump queue full\n",
					vdec);
	}
	spin_unlock_irqrestore (&vdec->dpbdump_lock, flag);

	return 0;
}

static int decoded_queue_push_locked (vdec_t *vdec, decoded_q_t *q, decoded_buffer_t *buf)
{
	struct decoded_info *info = NULL;
	unsigned long flag;

	if (vdec->vdc == 0xff)
	{
		logm_noti (vdec, "vdec:%p, callback while closed vdc\n",
				vdec);
		return 0;
	}

	if (buf->buffer_index < 0 &&
			buf->report == 0)
	{
		logm_debug (vdec, "vdec:%p, no information\n",
				vdec);

		return 0;
	}

	if (buf->buffer_index >= 0)
	{
		struct vo_vdo_info *vdo_info;
		enum vo_map_type map_type;

		switch (buf->vdo_map_type)
		{
		default:
		case vdo_map_type_linear:
			map_type = vo_map_type_linear;
			break;

		case vdo_map_type_frame:
			map_type = vo_map_type_frame;
			break;

		case vdo_map_type_mixed:
			map_type = vo_map_type_mixed;
			break;
		}

		/* save VDO information on local memory */
		vdo_info = vdec->vdo_info;
		if (
				vdo_info == NULL ||
				vdo_info->tile_base != buf->addr_tile_base ||
				vdo_info->map_type != map_type
				)
		{
			vdo_info = kcalloc (1, sizeof (*vdec->vdo_info),
					GFP_ATOMIC);
			if (vdo_info == NULL)
			{
				logm_warning (vdec, "vdec:%p, no memory?\n",
						vdec);
				return 0;
			}

			vdo_info->next = vdec->vdo_info;
			vdec->vdo_info = vdo_info;

			/* save VDO information */
			vdo_info->tile_base = buf->addr_tile_base;
			vdo_info->map_type = map_type;

			logm_noti (vdec, "vdec:%p, new vdo %p, base %08lx, type %d\n",
					vdec, vdo_info,
					vdo_info->tile_base, vdo_info->map_type);
		}

		buf->addr_tile_base = (unsigned long)vdo_info;

		/* wake cpbdump */
		if (vdec->cpbdump.addr)
			wake_up (&vdec->cpbdump.wq);

		/*
		 * register the index and buffer address to the table that will
		 * be used in pushing to clear queue
		 */
		info = kmalloc (sizeof (*info), GFP_ATOMIC);
		if (info == NULL)
		{
			logm_error (vdec, "vdec:%p, kmalloc failed\n", vdec);
			return 0;
		}
		info->buffer = *buf;
		info->user = 1;

		spin_lock_irqsave (&vdec->decoded_buffers_lock, flag);
		info->next = vdec->decoded_infos;
		vdec->decoded_infos = info;
		spin_unlock_irqrestore (&vdec->decoded_buffers_lock, flag);
	}

	/* log decoded information... */
	if (logm_enabled (vdec, log_level_debug))
	{
		struct decoded_info *now;
		char *tmp;
		int tmp_len;
		const char *field_info, *pic_type;
		int a;
		struct vo_vdo_info *vdo_info =
			(struct vo_vdo_info*)buf->addr_tile_base;

		spin_lock_irqsave (&vdec->decoded_buffers_lock, flag);
		for (
				tmp_len=1, now=vdec->decoded_infos;
				now;
				now=now->next, tmp_len++
		    );
		tmp = kmalloc (tmp_len, GFP_ATOMIC);
		for (
				a=0, now=vdec->decoded_infos;
				now;
				a++, now=now->next
		    )
		{
			if (now->buffer.buffer_index < 10)
				tmp[a] = now->buffer.buffer_index + '0';
			else
				tmp[a] = now->buffer.buffer_index - 10 + 'a';
		}
		tmp[a] = 0;
		spin_unlock_irqrestore (&vdec->decoded_buffers_lock, flag);

		switch (buf->interlace)
		{
		default:
			logm_warning (vdec, "unknown field info %d\n",
					buf->interlace);
			field_info = "XXXX";
			break;

		case decoded_buffer_interlace_none:
			field_info = "pro.";
			break;

		case decoded_buffer_interlace_top_first:
			field_info = "top.";
			break;

		case decoded_buffer_interlace_bottom_first:
			field_info = "bot.";
			break;
		}

		switch (buf->picture_type)
		{
		default:
			logm_warning (vdec, "unknown picture type %d\n",
					buf->picture_type);
			pic_type = "X";
			break;

		case decoded_buffer_picture_type_i:
			pic_type = "I";
			break;

		case decoded_buffer_picture_type_p:
			pic_type = "P";
			break;

		case decoded_buffer_picture_type_b:
			pic_type = "B";
			break;

		case decoded_buffer_picture_type_bi:
			pic_type = "BI";
			break;

		case decoded_buffer_picture_type_d:
			pic_type = "D";
			break;

		case decoded_buffer_picture_type_s:
			pic_type = "S";
			break;

		case decoded_buffer_picture_type_pskip:
			pic_type = "PSKIP";
			break;

		}

		logm_debug (vdec, "vdec:%p, base:%lx(%d),y:%07lx,cb:%07lx, "
				"%2d,%dx%d(%d,%d,%d,%d,%d), "
				"%lld\n",
				vdec,
				buf->addr_tile_base, buf->vdo_map_type,
				buf->addr_y,
				buf->addr_cb,

				buf->buffer_index,
				buf->width, buf->height, buf->stride,
				buf->crop_left, buf->crop_right,
				buf->crop_top, buf->crop_bottom,
				
				buf->timestamp);

		logm_debug (vdec, "vdec:%p, "
				"fr:%d/%d,error blocks:%d,afd:%x,fpa:%d, "
				"tilebase:%lx,maptype:%d, "
				"par:%dx%d,flag:%d,lr:%d,%s(%d),%s,%s\n",
				vdec,
				buf->framerate_num,
				buf->framerate_den,
				buf->error_blocks,
				buf->active_format,
				buf->frame_packing_arrangement,

				vdo_info?vdo_info->tile_base:0,
				vdo_info?vdo_info->map_type:0,

				buf->par_w, buf->par_h,
				buf->report,
				buf->multi_picture,
				field_info, buf->display_period&7,
				pic_type,
				tmp
			  );

		kfree (tmp);
	}

	if (buf->report & DECODED_REPORT_HW_RESET)
	{
		logm_debug (vdec, "vdec:%p, do hardware reset\n",
				vdec);
		//noti_save (&vdec->noti, LX_VDEC_READ_MAGIC("RSET"),
		//		NULL, 0);
		return 0;
	}

	if (vdec->new_apiset)
	{
		if (vdec_force_frame_alternation &&
				buf->buffer_index >= 0)
		{
			int org;

			org = buf->multi_picture;
			buf->multi_picture = decoded_buffer_multi_picture_left;
			noti_save (&vdec->noti, LX_VDEC_READ_MAGIC("DECO"),
					buf, sizeof(*buf));
			buf->multi_picture = decoded_buffer_multi_picture_right;
			noti_save (&vdec->noti, LX_VDEC_READ_MAGIC("DECO"),
					buf, sizeof(*buf));

			buf->multi_picture = org;

			/* one more frame user */
			info->user ++;
		}
		else
		{
			noti_save (&vdec->noti, LX_VDEC_READ_MAGIC("DECO"),
					buf, sizeof(*buf));
		}
	}
	else if (buf->buffer_index >= 0)
	{
		/* decoded noti */
		LX_VDEC_NOTIFY_PARAM_PICD_T picd;

		if (vdec->seqh_done == 0)
		{
			LX_VDEC_NOTIFY_PARAM_SEQH_T notiSeqh = {0, };

			noti_save_SEQH(&vdec->noti, &notiSeqh);

			vdec->seqh_done = 1;
		}

		memset (&picd, 0, sizeof (picd));

		picd.UId = buf->uid;
		picd.display = 0;
		picd.bGotAnchor = 1;
		picd.bFail = !!buf->error_blocks;
		picd.picErr = buf->error_blocks;
		picd.pts = buf->pts;
		picd.bLowDelay = !!(buf->report&DECODED_REPORT_LOW_DELAY);
		picd.u64Timestamp = 0;
		switch (buf->interlace)
		{
		default:
		case decoded_buffer_interlace_none:
			picd.interlace = lx_vdec_interlace_none;
			break;

		case decoded_buffer_interlace_top_first:
			picd.interlace = lx_vdec_interlace_top_first;
			break;

		case decoded_buffer_interlace_bottom_first:
			picd.interlace = lx_vdec_interlace_bottom_first;
			break;
		}
		picd.frm.width = buf->width;
		picd.frm.height = buf->height;
		picd.frm.stride = buf->stride;
		picd.frm.tile_base = 0;		// middleware do not need this information
		picd.frm.pY = buf->addr_y;
		picd.frm.pCb = buf->addr_cb;
		picd.frm.pCr = buf->addr_cr;
		picd.m.picType = buf->picture_type;
		picd.m.interlSeq =
			buf->interlace != decoded_buffer_interlace_none;
		picd.m.interlFrm =
			buf->interlace != decoded_buffer_interlace_none;

		if( buf->frame_packing_arrangement >= 0 )
		{
			picd.m.avc3DFpaValid = 1;
			picd.m.avc3DFpaType = buf->frame_packing_arrangement;
		}
		else
		{
			picd.m.avc3DFpaValid = 0;		
		}
		
		picd.m.sar = -1;	

		picd.m.afd = buf->active_format;
		picd.m.frameRateRes = buf->framerate_num;
		picd.m.frameRateDiv = buf->framerate_den;
		picd.m.par_w = buf->par_w;
		picd.m.par_h = buf->par_h;
		picd.m.crop_rect[0] = 0;
		picd.m.crop_rect[1] = 0;
		picd.m.crop_rect[2] = 0;
		picd.m.crop_rect[3] = 0;

		if (vdec->output_memory_format == LX_VDEC_MEMORY_FORMAT_TILED)
			vdec->noti.output.decode = picd;

		noti_save_PICD (&vdec->noti, &picd);
	}

	if (buf->buffer_index >= 0)
		return display_picture (vdec, info);
	else
	{
		logm_debug (vdec, "vdec:%p, no display\n", vdec);
		return 0;
	}
}

static int decoded_queue_push (decoded_q_t *q, decoded_buffer_t *buf)
{
	unsigned long flag;
	vdec_t *vdec = container_of (q, vdec_t, decoded_q);
	int ret;

	spin_lock_irqsave (&vdec->submodule_spin_lock, flag);
	ret = decoded_queue_push_locked (vdec, q, buf);
	spin_unlock_irqrestore (&vdec->submodule_spin_lock, flag);

	return ret;
}

static int decoded_queue_max_size (decoded_q_t *q)
{
	vdec_t *vdec = container_of (q, vdec_t, decoded_q);
	int maxsize;

	if (vdec->dest == LX_VDEC_DST_BUFF)
		maxsize = vdec->noti.size;
	else
		maxsize = vdec->display_q_maxsize;

	logm_trace (vdec, "vdec:%p, %d\n", vdec, maxsize);

	return maxsize-1;
}

static int decoded_queue_size (decoded_q_t *q)
{
	vdec_t *vdec = container_of (q, vdec_t, decoded_q);

	if (vdec->dest == LX_VDEC_DST_BUFF)
	{
		int head, tail, size;
		int ret;

		head = vdec->noti.head;
		tail = vdec->noti.tail;
		size = vdec->noti.size;

		if (head >= tail)
			ret = head-tail;
		else
			ret = size-tail+head;

		logm_trace (vdec, "vdec:%p, size %d\n", vdec, ret);
		return ret;
	}

	if (vdec->sync != 0xff)
		return DISP_Q_NumActive (vdec->sync);

	logm_noti (vdec, "Closing??\n");

	return INT_MAX;
}

static void initialize_instance (vdec_t *vdec)
{
	S_DISPCLEARQ_BUF_T cq;
	unsigned long flag;

	logm_debug (vdec, "vdec:%p, reset instance vairables\n", vdec);

	/* clear internal decoded buffer */
	while (DISP_CLEAR_Q_Pop (vdec->clear_q, &cq));
	spin_lock_irqsave (&vdec->decoded_buffers_lock, flag);
	while (vdec->decoded_infos)
	{
		struct decoded_info *next;

		next = vdec->decoded_infos->next;
		kfree (vdec->decoded_infos);
		vdec->decoded_infos = next;
	}
	spin_unlock_irqrestore (&vdec->decoded_buffers_lock, flag);

	while (vdec->vdo_info)
	{
		struct vo_vdo_info *t;

		t = vdec->vdo_info->next;

		kfree (vdec->vdo_info);
		logm_noti (vdec, "vdec:%p, free vdo %p\n", vdec,
				vdec->vdo_info);

		vdec->vdo_info = t;
	}

	memset (&vdec->noti.output, 0, sizeof (vdec->noti.output));
	vdec->output_memory_format = LX_VDEC_MEMORY_FORMAT_TILED;
	vdec->scan_mode = LX_VDEC_PIC_SCAN_ALL;
	vdec->frame_displaied = 0;
	vdec->frame_requested = -1;

	vdec->cpbdump.now = 0;
	vdec->cpbdump.readed = 0;

	vdec->cpb_addr = 0;
	vdec->cpb_size = 0;
	vdec->cpb_allocated = 0;

	vdec->trid_type = vo_3d_type_none;
	vdec->kick_decoder_count = 0;

	vdec->use_gstc = 0;
	vdec->use_gstc_have_cut = 0;

	vdec->debug_counter = 0;
}

static int destroy_submodules_locked (vdec_t *vdec)
{
	unsigned long flag;
	int ves, vdc, sync;

	logm_noti (vdec, "vdec:%p\n", vdec);

	if (
			vdec->use_gstc &&
			vdec->use_gstc_have_cut &&
			LX_VDEC_SRC_SDEC0 <= vdec->src &&
			vdec->src <= LX_VDEC_SRC_SDEC2
	   )
	{
		unsigned int a = -1;
		AV_Set_AVLipSyncBase (vdec->src - LX_VDEC_SRC_SDEC0, &a, &a);
	}

	spin_lock_irqsave (&vdec->submodule_spin_lock, flag);
	ves = vdec->ves;
	vdc = vdec->vdc;
	sync = vdec->sync;

	vdec->ves = 0xff;
	vdec->vdc = 0xff;
	vdec->sync = 0xff;
	spin_unlock_irqrestore (&vdec->submodule_spin_lock, flag);
	
	if(sync!=0xFF)
	{
		int de_id;

		logm_info (vdec, "close sync %d\n", sync);
		VDISP_Close (sync);

		switch (vdec->dest)
		{
		default:
		case LX_VDEC_DST_DE0: de_id = 0; break;
		case LX_VDEC_DST_DE1: de_id = 1; break;
		}

		vo_set_output_info (de_id, 0, 0, 0, 0,
				0, 0, 0, vo_3d_type_none);
	}
	if(vdc!=0xFF)
	{
		logm_info (vdec, "close vdc %d\n", vdc);
		VDC_Close(vdc);
	}
	if(ves!=0xFF)
	{
		logm_info (vdec, "close ves %d\n", ves);
		VES_Close(ves);
	}

	if (vdec->cpb_allocated)
	{
		hma_free ("vdec", vdec->cpb_addr);
		vdec->cpb_allocated = 0;
	}

	initialize_instance (vdec);

	ui32ActiveSrc &= ~(1 << vdec->src);
	ui32ActiveDst &= ~(1 << vdec->dest);

	/* wake up any pending poll() or read() system call */
	wake_up (&vdec->noti.wq);

	return 0;
}

static int destroy_submodules (vdec_t *vdec)
{
	int ret;

	/* 먼저 submodule에 대해 동작을 멈춘 후 lock을 잡도록 한다. lock 안에서
	 * 동작을 멈추면 submodule의 callback이 호출돼 deadlock이 발생할 수
	 * 있다 */
	if (vdec->ves != 0xff)
		VES_Stop (vdec->ves);

	/* destroy module instance */
	mutex_lock (&vdec->submodule_lock);
	ret = destroy_submodules_locked (vdec);
	mutex_unlock (&vdec->submodule_lock);

	return ret;
}

static void ves_updated (unsigned char ves_ch,
		void *arg, int stc_invalid, unsigned int uid)
{
	vdec_t *vdec = arg;

	logm_debug (vdec, "vdec:%p, ves%d buffer updated, %d %x\n",
			vdec, vdec->ves, stc_invalid, uid);

	mutex_lock (&vdec->submodule_lock);
	if (vdec->ves != 0xff && vdec->vdc != 0xff)
	{
		logm_debug (vdec, "vdec:%p, auib %d\n", vdec,
				VES_AUIB_NumActive (vdec->ves));

		if (stc_invalid && vdec->sync != 0xff){
			logm_trace(vdec, "vdec:%p, uid:%d stc invalid:%d \n", vdec,uid,vdec->debug_counter++);
			VDISP_SetStcDiscont (vdec->sync, uid);
		}

		kick_decoder_locked (vdec);
	}
	mutex_unlock (&vdec->submodule_lock);
}

static int set_scan_picture(vdec_t *vdec, LX_VDEC_PIC_SCAN_T scan)
{
	vdec->scan_mode = scan;
	logm_debug (vdec, "vdec:%p, scanmode %d\n", vdec, scan);

	if (vdec->vdc != 0xff)
	{
		VDC_SKIP_T _scan = VDC_SKIP_NONE;

		switch(scan)
		{
		case LX_VDEC_PIC_SCAN_ALL:
			_scan = VDC_SKIP_NONE;
			break;
		case LX_VDEC_PIC_SCAN_I:
			_scan = VDC_SKIP_PB;
			break;
		case LX_VDEC_PIC_SCAN_IP:
			_scan = VDC_SKIP_B;
			break;
		default :
			logm_warning (vdec, "vdec:%p, unknown scanmode %d\n", vdec, scan);
			return -EINVAL;
		}

		VDC_SetSkipMode(vdec->vdc, _scan);
	}

	return 0;
}

static int init_submodules (vdec_t *vdec)
{
	int ret = 0;
	BOOLEAN dual_decoding;
	VDC_OPEN_PARAM_T stVdcOpenParam;
	VDC_CODEC_T codec;
	E_VES_SRC_T src;
	const char *src_name;

#define printvar(f,v)	logm_noti (vdec, #v": %"#f"\n", v)
	printvar (p, vdec);
	printvar (d, vdec->src);
	printvar (d, vdec->dest);
	printvar (d, vdec->output_memory_format);
#undef printvar

	if (vdec_force_raster_memory)
	{
		logm_noti (vdec, "vdec:%p, force to use raster memory\n",
				vdec);
		vdec->output_memory_format = LX_VDEC_MEMORY_FORMAT_RASTER;
	}

	/* check codec */
	{
		struct
		{
			LX_VDEC_CODEC_T c1;
			VDC_CODEC_T c2;
			const char *name;
		} cs[] =
		{
			{ LX_VDEC_CODEC_H264_HP,	VDC_CODEC_H264_HP,	"h264_hp",	},
			{ LX_VDEC_CODEC_H264_MVC,	VDC_CODEC_H264_MVC,	"h264_mvc",	},
			{ LX_VDEC_CODEC_VC1_RCV_V1,	VDC_CODEC_VC1_RCV_V1,	"vc1_rcv_v1",	},
			{ LX_VDEC_CODEC_VC1_RCV_V2,	VDC_CODEC_VC1_RCV_V2,	"vc1_rcv_v2",	},
			{ LX_VDEC_CODEC_VC1_ES,		VDC_CODEC_VC1_ES,	"vc1_es",	},
			{ LX_VDEC_CODEC_MPEG2_HP,	VDC_CODEC_MPEG2_HP,	"mpeg2_hp",	},
			{ LX_VDEC_CODEC_MPEG4_ASP,	VDC_CODEC_MPEG4_ASP,	"mpeg4_asp",	},
			{ LX_VDEC_CODEC_XVID,		VDC_CODEC_XVID,		"xvid",		},
			{ LX_VDEC_CODEC_DIVX3,		VDC_CODEC_DIVX3,	"divx3",	},
			{ LX_VDEC_CODEC_DIVX4,		VDC_CODEC_DIVX4,	"divx4",	},
			{ LX_VDEC_CODEC_DIVX5,		VDC_CODEC_DIVX5,	"divx5",	},
			{ LX_VDEC_CODEC_RVX,		VDC_CODEC_RVX,		"rvx",		},
			{ LX_VDEC_CODEC_AVS,		VDC_CODEC_AVS,		"avs",		},
			{ LX_VDEC_CODEC_VP8,		VDC_CODEC_VP8,		"vp8",		},
			{ LX_VDEC_CODEC_THEORA,		VDC_CODEC_THEORA,	"theora",	},
		};
		int a;

		for (a=0; a<ARRAY_SIZE(cs); a++)
		{
			if (cs[a].c1 == vdec->codec)
			{
				codec = cs[a].c2;
				break;
			}
		}
		if (a == ARRAY_SIZE(cs))
		{
			logm_warning (vdec, "vdec:%p, unknown codec %d\n",
					vdec, vdec->codec);
			return -1;
		}

		logm_noti (vdec, "vdec:%p, codec %s\n", vdec, cs[a].name);
	}

	/* check input and output */
	{
		struct
		{
			LX_VDEC_SRC_T s1;
			E_VES_SRC_T s2;
			const char *n;
		} srcs[] =
		{
			{ LX_VDEC_SRC_SDEC0,    VES_SRC_SDEC0, "sdec0" },
			{ LX_VDEC_SRC_SDEC1,    VES_SRC_SDEC1, "sdec1" },
			{ LX_VDEC_SRC_SDEC2,    VES_SRC_SDEC2, "sdec2" },
			{ LX_VDEC_SRC_BUFF,     VES_SRC_BUFF0, "buffer" },
			{ LX_VDEC_SRC_BUFFTVP,  VES_SRC_TVP,   "tvp" },
		};
		int a;

		for (a=0; a<ARRAY_SIZE (srcs); a++)
		{
			if (vdec->src == srcs[a].s1)
			{
				src = srcs[a].s2;
				src_name = srcs[a].n;
				break;
			}
		}
		if (a == ARRAY_SIZE (srcs))
		{
			logm_warning (vdec, "vdec:%p, unknown input device %d\n",
					vdec, vdec->src);
			return -1;
		}

		logm_noti (vdec, "vdec:%p, input %s\n",
				vdec, src_name);
	}

	if (
			LX_VDEC_SRC_SDEC0 <= vdec->src &&
			vdec->src <= LX_VDEC_SRC_SDEC2 &&
			ui32ActiveSrc & (1 << vdec->src)
	   )
	{
		logm_warning (vdec, "vdec:%p, input device already occupied\n",
				vdec);
		return -1;
	}
	if (
			LX_VDEC_DST_DE0 <= vdec->dest &&
			vdec->dest <= LX_VDEC_DST_DE1 &&
			ui32ActiveDst & (1 << vdec->dest)
	   )
	{
		logm_warning (vdec, "vdec:%p, output device already occupied\n",
				vdec);
		return -1;
	}

	if (vdec->use_gstc)
		logm_noti (vdec, "vdec:%p, use gstc\n", vdec);
	if (vdec->src == LX_VDEC_SRC_BUFF && !vdec->use_gstc)
	{
		logm_noti (vdec, "vdec:%p, use STC while memory input source. use GSTC!\n",
				vdec);
		vdec->use_gstc = 1;
	}

	/* open input device */
	if( vdec->src <= LX_VDEC_SRC_BUFFTVP )
	{
		if (!vdec->cpb_size)
		{
			if( vdec->opmode == LX_VDEC_OPMOD_ONE_FRAME )
				vdec->cpb_size = 0x1F0000;
			else
			{
				vdec->cpb_size = vdec_default_cpb_size;
				vdec->cpb_size &= PAGE_MASK;
			}
		}

		if (!vdec->cpb_addr)
		{
			vdec->cpb_addr = hma_alloc_user ("vdec", vdec->cpb_size, 1<<12, "cpb");
			vdec->cpb_allocated = 1;
		}

		logm_noti (vdec, "vdec:%p, opening ves, cpb_size %x\n",
				vdec, vdec->cpb_size);
		vdec->ves = VES_Open(src, vdec->codec,
				vdec->cpb_addr, vdec->cpb_size,
				vdec->use_gstc, 0,
				ves_updated, vdec);
		if(vdec->ves == 0xFF)
		{
			ret = -1;
			logm_warning (vdec, "vdec:%p, ves open failed\n", vdec);
			goto error;
		}
	}

	dual_decoding = (vdec->opmode == LX_VDEC_OPMOD_DUAL) ?
		TRUE : FALSE;

	logm_noti (vdec, "vdec:%p, dual decoding %d\n",
			vdec, dual_decoding);

	/* open output device */
	if (vdec->dest < LX_VDEC_DST_BUFF)
	{
		VDISP_CLK_SRC clock_src;
		BOOLEAN fixed_vsync;
		PTS_MATCH_MODE_E match_mode;

		fixed_vsync = (vdec->opmode == LX_VDEC_OPMOD_LOW_LATENCY) ?
			TRUE : FALSE;
		match_mode = (vdec->opmode == LX_VDEC_OPMOD_LOW_LATENCY) ?
			PTS_MATCH_FREERUN_IGNORE_SYNC : PTS_MATCH_ENABLE;

		logm_noti (vdec, "vdec:%p, fixed vsync %d\n",
				vdec, fixed_vsync);
		logm_noti (vdec, "vdec:%p, match mode %d\n",
				vdec, match_mode);

		if( vdec->use_gstc )
			clock_src = VDISP_CLK_GSTC;
		else if (LX_VDEC_SRC_SDEC0 <= vdec->src &&
				vdec->src <= LX_VDEC_SRC_SDEC2)
			//clock_src = VDISP_CLK_PDEC0 + vdec->src - LX_VDEC_SRC_SDEC0;
			clock_src = VDISP_CLK_PDEC0 + vdec->ves;
		else
		{
			logm_warning (vdec, "vdec:%p, use STC while input source %s\n",
					vdec, src_name);
			goto error;
		}

		vdec->sync = VDISP_Open(vdec->dest,
				clock_src,
				vdec->display_offset,
				vdec->display_q_maxsize,
				dual_decoding,
				fixed_vsync,
				match_mode,
				NULL
				);

		if(vdec->sync == 0xFF)
		{
			ret = -1;
			logm_warning (vdec, "vdec:%p, sync open failed\n", vdec);
			goto error;
		}

		if (vdec->opmode == LX_VDEC_OPMOD_LOW_LATENCY)
			VDEC_RATE_UpdateFrameRate_Config (vdec->sync, 60, 1);

		if( lx_chip_rev() < LX_CHIP_REV(H13, B0) )
		{
			if( vdec->src <= LX_VDEC_SRC_SDEC2 )
			{
				TOP_HAL_SetLQInputSelection(vdec->sync, vdec->ves);
				TOP_HAL_EnableLQInput(vdec->sync);
			}
			else
			{
				TOP_HAL_DisableLQInput(vdec->sync);
			}
		}
	}

	if( vdec->src <= LX_VDEC_SRC_BUFFTVP )
	{
		BOOLEAN nRet = TRUE;

		nRet = VES_SetOpenParam(vdec->ves, vdec->sync, vdec,
				TRUE, TRUE);
		if( nRet == FALSE )
		{
			ret = -1;
			logm_warning (vdec, "vdec:%p, VES_SetOpenParam failed\n", vdec);
			goto error;
		}
	}

	/* open decoder */
	stVdcOpenParam.ui8VesCh = vdec->ves;
	stVdcOpenParam.priv = vdec;
	stVdcOpenParam.ui8Src = vdec->src;
	stVdcOpenParam.ui8Vcodec = codec;
	stVdcOpenParam.ui32CpbBufAddr = vdec->cpb_addr;
	stVdcOpenParam.ui32CpbBufSize = vdec->cpb_size;
	stVdcOpenParam.clear_q = vdec->clear_q;
	stVdcOpenParam.decoded_q = &vdec->decoded_q;
	switch (vdec->output_memory_format)
	{
	default:
	case LX_VDEC_MEMORY_FORMAT_RASTER:
		stVdcOpenParam.output_memory_format = VDC_MEMORY_FORMAT_RASTER;
		break;

	case LX_VDEC_MEMORY_FORMAT_TILED:
		stVdcOpenParam.output_memory_format = VDC_MEMORY_FORMAT_TILED;
		break;
	}

	vdec->vdc = VDC_Open(&stVdcOpenParam);
	if( vdec->vdc == 0xFF )
	{
		ret = -1;
		logm_warning (vdec, "vdec:%p, vdc open failed\n", vdec);
		goto error;
	}
	VDC_SetUserDataOutput(vdec->vdc, TRUE);
	if (vdec->scan_mode != LX_VDEC_PIC_SCAN_ALL)
		set_scan_picture (vdec, vdec->scan_mode);

	logm_noti (vdec, "opened vdc %d\n", vdec->vdc);
	logm_noti (vdec, "opened ves %d\n", vdec->ves);
	logm_noti (vdec, "opened sync %d\n", vdec->sync);

	ui32ActiveSrc |= (1 << vdec->src);
	ui32ActiveDst |= (1 << vdec->dest);

	if (dual_decoding)
		vdec->trid_type = vo_3d_type_dual;

error:
	if(ret < 0)
	{
		logm_warning (vdec, "vdec:%p, failed to open ch ret %d\n",
				vdec, ret);

		destroy_submodules (vdec);

		return -1;
	}

	logm_noti (vdec, "vdec:%p\n", vdec);
	return 0;
}

static void hardware_reset(vdec_t *vdec)
{
	/*
	 * FIXME
	 *
	 * not yet implemented. we should hole running vdec instance now.
	 */

	S_DISPCLEARQ_BUF_T buf;

	logm_warning (vdec, "vdec:%p, do decoder reset\n", vdec);

	if (vdec->ves != 0xff)
	{
		//VES_Reset(vdec->ves);
		//VES_Flush(vdec->ves);
	}

	if (vdec->vdc != 0xff)
		VDC_Reset(vdec->vdc);

	if (vdec->sync != 0xff)
		VDISP_Reset (vdec->sync);

	/* empty cleal_q */
	while (DISP_CLEAR_Q_Pop (vdec->clear_q, &buf) == TRUE);
}

#if 0
static void VDEC_CH_SetDBGDisplayOffset(vdec_t *vdec, UINT32 ui32DisplayOffset_ms)
{
	VDISP_Debug_Set_DisplayOffset(vdec->sync, ui32DisplayOffset_ms);
}
#endif

static int set_basetime(vdec_t *vdec, int clock_id,
		unsigned int base_stc, unsigned int base_pts)
{
	if(vdec->clock_id != clock_id)
	{
		logm_warning (vdec, "vdec%p, unknown clock %d/%d\n", vdec,
				vdec->clock_id, clock_id);

		return -1;
	}

	logm_debug (vdec, "vdec:%p, clock id %d, basetime %08x, pts %08x\n", vdec,
			clock_id, base_stc, base_pts);

	VDISP_SetBaseTime(vdec->sync, base_stc, base_pts);

	return 0;
}

static int get_basetime(vdec_t *vdec, int clock_id,
		unsigned int *base_stc, unsigned int *base_pts)
{
	if(vdec->clock_id != clock_id)
	{
		logm_warning (vdec, "vdec%p, unknown clock %d/%d\n", vdec,
				vdec->clock_id, clock_id);

		return -1;
	}

	VDISP_GetBaseTime(vdec->sync, base_stc, base_pts);

	logm_debug (vdec, "vdec:%p, clock id %d, basetime %08x, pts %08x\n", vdec,
			clock_id, *base_stc, *base_pts);

	return 0;
}


/* deprecated api. only for L9 vdec interface */
static int open_channel(vdec_t *vdec, LX_VDEC_IO_OPEN_CH_T *init_param)
{
	int ret = 0;

	mutex_lock (&io_lock);

	switch(init_param->src)
	{
	case LX_VDEC_SRC_SDEC0:
	case LX_VDEC_SRC_SDEC1:
	case LX_VDEC_SRC_SDEC2:
	case LX_VDEC_SRC_BUFF:
	case LX_VDEC_SRC_BUFFTVP:
		vdec->src = init_param->src;
		break;

	default:
		logm_warning (vdec, "vdec:%p, unknown input source %d\n",
				vdec, init_param->src);
		vdec->src = LX_VDEC_SRC_BUFF;
		break;
	}

	switch(init_param->dst)
	{
	case LX_VDEC_DST_DE0:
	case LX_VDEC_DST_DE1:
	case LX_VDEC_DST_BUFF:
		vdec->dest = init_param->dst;
		break;

	default:
		logm_warning (vdec, "vdec:%p, unknown output device %d\n",
				vdec, init_param->dst);
		break;
	}

	vdec->opmode = init_param->opmode;
	vdec->clock_id = init_param->clkID;
	vdec->framerate_num = 0;
	vdec->seqh_done = 0;
	vdec->use_gstc = init_param->useGstc;
	vdec->display_offset = init_param->disDelayOffset;
	vdec->codec = init_param->vcodec;

	/* empty cleal_q */
	{
		S_DISPCLEARQ_BUF_T buf;
		while (DISP_CLEAR_Q_Pop (vdec->clear_q, &buf) == TRUE);
	}

	ret = init_submodules(vdec);

	if(ret < 0)
	{
		ret = -1;
		logm_warning (vdec, "vdec:%p, failed to initialize\n",
				vdec);
		goto error;
	}

error:
	mutex_unlock (&io_lock);

	return (ret);
}

static int start_channel(vdec_t *vdec, LX_VDEC_IO_PLAY_T *pioStart)
{
	int ret = 0;

	if (vdec->vdc == 0xff && vdec->codec == LX_VDEC_CODEC_INVALID)
	{
		logm_warning (vdec, "no channel\n");
		return -1;
	}

	if (vdec->vdc == 0xff)
	{
		ret = init_submodules (vdec);
		if (ret < 0)
		{
			logm_warning (vdec, "vdec:%p, "
					"cannot initialize submodules\n",
					vdec);
			return ret;
		}
	}

	mutex_lock (&io_lock);

	switch( pioStart->cmd )
	{
	case LX_VDEC_CMD_PLAY :
		logm_debug (vdec, "vdec:%p, pause speed %d\n",
				vdec, pioStart->speed);

		if (vdec->sync != 0xff)
		{
			VDISP_SetSpeed(vdec->sync, pioStart->speed);

			if(pioStart->speed == 0)
				VDISP_Stop(vdec->sync);
			else
				VDISP_Start(vdec->sync, FALSE);
		}

		if (pioStart->speed != 0)
		{
			VES_Start(vdec->ves);
			VDC_Start(vdec->vdc);
		}
		break;
	case LX_VDEC_CMD_STEP :
		logm_debug (vdec, "vdec:%p, step\n", vdec);
		if (vdec->sync != 0xff)
			VDISP_Start(vdec->sync, TRUE);

		VES_Start(vdec->ves);
		VDC_Start(vdec->vdc);
		break;
	default :
		logm_warning (vdec, "vdec:%p, unknown command %d\n",
				vdec, pioStart->cmd);
		ret = -1;
		break;
	}

	mutex_unlock (&io_lock);

	return (ret);
}

static int set_play_option(vdec_t *vdec, LX_VDEC_IO_PLAY_SET_T *playSetOp)
{
	int ret = 0;

	if (vdec->vdc == 0xff)
	{
		logm_warning (vdec, "no channel\n");
		return -1;
	}

	mutex_lock (&io_lock);

	if(playSetOp->picScanMode < LX_VDEC_PIC_SCAN_MAXN)
	{
		ret = set_scan_picture(vdec, playSetOp->picScanMode);
		if(ret !=0 )
			goto error;
	}

	if(playSetOp->notifyMask < LX_VDEC_NOTIFY_MSK_ENDMARK)
		noti_set_mask(&vdec->noti, (UINT32)playSetOp->notifyMask);

	if(vdec->sync != 0xff &&
			playSetOp->syncOn < LX_VDEC_SYNC_MAXN)
	{
		if( vdec->opmode == LX_VDEC_OPMOD_LOW_LATENCY )
			logm_warning (vdec, "vdec:%p, "
					"setting lipsync while low latency mode\n",
					vdec);
		else
		{
			if (
					vdec->use_gstc &&
					LX_VDEC_SRC_SDEC0 <= vdec->src &&
					vdec->src <= LX_VDEC_SRC_SDEC2
			   )
			{
				unsigned int a = -1;

				/* clear base time */
				AV_Set_AVLipSyncBase (vdec->src - LX_VDEC_SRC_SDEC0, &a, &a);
			}

			if(playSetOp->syncOn)
			{
				VDISP_SetMatchMode(vdec->sync,
						PTS_MATCH_ENABLE);

				/* cut gstc again */
				vdec->use_gstc_have_cut = 0;
			}
			else
				VDISP_SetMatchMode(vdec->sync,
						PTS_MATCH_FREERUN_BASED_SYNC);
		}
	}

	if(vdec->sync != 0xff &&
			playSetOp->freeze < LX_VDEC_FREEZE_MAXN)
		VDISP_Freeze(vdec->sync, playSetOp->freeze);

	if(playSetOp->clkID != 0xFF)
	{
		ret = set_basetime(vdec, playSetOp->clkID,
				playSetOp->stcBaseTime, playSetOp->ptsBaseTime);
	}

error :
	mutex_unlock (&io_lock);

	return ret;
}

static int get_play_option(vdec_t *vdec, LX_VDEC_IO_PLAY_GET_T *playGetOp)
{
	int ret = 0;

	if (vdec->vdc == 0xff)
	{
		logm_warning (vdec, "no channel\n");
		return -1;
	}

	mutex_lock (&io_lock);

	if(playGetOp->clkID != 0xFF)
	{
		ret = get_basetime(vdec, playGetOp->clkID,
				&playGetOp->stcBaseTime, &playGetOp->ptsBaseTime);
	}

	mutex_unlock (&io_lock);

	return ret;
}

static int _flush(vdec_t *vdec)
{
	int ret = 0;

	logm_debug (vdec, "vdec:%p\n", vdec);

	mutex_lock (&io_lock);

	vdec->flushed = 1;
	if (vdec->vdc != 0xff){
		VDC_Stop(vdec->vdc);
		VDC_Flush(vdec->vdc);
	}
	if (vdec->ves != 0xff)
	{
		VES_Flush(vdec->ves);	
	}

	if (
			vdec->use_gstc &&
			LX_VDEC_SRC_SDEC0 <= vdec->src &&
			vdec->src <= LX_VDEC_SRC_SDEC2
	   )
	{
		unsigned int a = -1;

		/* clear base time */
		AV_Set_AVLipSyncBase (vdec->src - LX_VDEC_SRC_SDEC0, &a, &a);
	}

	if (vdec->sync != 0xff)
	{
		VDISP_Flush (vdec->sync);

		/* cut gstc again */
		vdec->use_gstc_have_cut = 0;
	}

	//VDC_CheckFlushed(vdec->vdc);
	decoded_queue_flush (&vdec->decoded_q);

	if (vdec->vdc != 0xff)
		VDC_Start(vdec->vdc);

	mutex_unlock (&io_lock);

	return (ret);
}

static int get_buffer_status(vdec_t *vdec, LX_VDEC_IO_BUFFER_STATUS_T *status)
{
	int ret = 0;

	if (vdec->vdc == 0xff)
	{
		logm_debug (vdec, "no channel\n");
		return -1;
	}

	mutex_lock (&io_lock);

	status->cpb_size = VES_CPB_GetBufferSize(vdec->ves);
	status->cpb_depth = VES_CPB_GetUsedBuffer(vdec->ves);
	status->auib_size = VES_AUIB_NUM_OF_NODE;
	status->auib_depth = VES_AUIB_NumActive(vdec->ves);

	mutex_unlock (&io_lock);

	return (ret);
}

static int get_firmware_version(LX_VDEC_IO_VERSION_T *stpLXIOVersion)
{
	int ret = 0;

	mutex_lock (&io_lock);

	stpLXIOVersion->ui32RTLVersion = TOP_HAL_GetVersion();
	stpLXIOVersion->ui32FirmwareVersion = 0;

	logm_info (vdec, "RTLVersion 0x%08x\n", stpLXIOVersion->ui32RTLVersion);

	mutex_unlock (&io_lock);
	return (ret);
}

#define REG_WRITE32( addr, value )	( *( volatile UINT32 * )( addr ) ) = ( volatile UINT32 )( value )
#define REG_READ32( addr )		( *( volatile UINT32 * )( addr ) )
static int set_register(LX_VDEC_SET_REG_T *set_reg)
{
	int ret = 0;

	mutex_lock (&io_lock);

	REG_WRITE32(set_reg ->addr, set_reg ->value);
	logm_info (vdec, "0x%08x = 0x%08x\n",
			set_reg->addr, set_reg ->value);

	mutex_unlock (&io_lock);

	return (ret);
}

static int get_register(LX_VDEC_GET_REG_T *get_reg)
{
	int ret = 0;
	unsigned int value = 0x0;

	mutex_lock (&io_lock);

	value = REG_READ32(get_reg->addr);
	get_reg->value = value;
	logm_info (vdec, "0x%08x : 0x%08x\n",
			get_reg->addr, value);

	mutex_unlock (&io_lock);
	return (ret);
}

static int update_buffer(vdec_t *vdec, LX_VDEC_IO_UPDATE_BUFFER_T *buffer)
{
	int ret = 0;
	wait_queue_head_t *wq;

	if (vdec->vdc == 0xff)
	{
		logm_warning (vdec, "no vdc\n");
		return -EFAULT;
	}

	if(buffer->au_size==0)
	{
		logm_warning (vdec, "no data\n");
		return -EFAULT;
	}

	/* flush check */
	if (vdec->flushed)
		vdec->flushed = 0;

	wq = VES_AUIB_GetWaitQueueHead (vdec->ves);
	ret = wait_event_interruptible (*wq,
			vdec->decoding_queue_size > VES_CPB_GetUsedBuffer (vdec->ves) &&
			vdec->decoding_queue_slots > VES_AUIB_NumActive (vdec->ves));
	if (ret < 0)
		return ret;

	/* check this buffer should be flushed */
	if (vdec->flushed)
	{
		logm_debug (vdec, "vdec:%p, flush this buffer\n",
				vdec);
		vdec->flushed = 0;
		return 0;
	}

	mutex_lock (&io_lock);

	if (logm_enabled (vdec, log_level_debug))
	{
		char tmp[64];
		int a, len = 16;
		int qlen;

		qlen = VES_AUIB_NumActive (vdec->ves);

		if (len > buffer->au_size)
			len = buffer->au_size;

		if (vdec->src != LX_VDEC_SRC_BUFFTVP)
		{
			for (a=0; a<len; a++)
				sprintf (tmp+a*3, "%02x ",
						((unsigned char*)buffer->au_ptr)[a]);
			tmp[a*3] = 0;
		}
		else
			tmp[0] = 0;

		logm_debug (vdec, "vdec:%p, qlen:%d, %d/%d, %llu(%08llx), data(%d):%s\n", vdec,
				qlen,
				buffer->frRes, buffer->frDiv,
				buffer->timestamp, buffer->timestamp,
				buffer->au_size,
				tmp);
	}

	/* save framerate */
	if (buffer->frRes)
	{
		vdec->framerate_num = buffer->frRes;
		vdec->framerate_den = buffer->frDiv;
	}

	if (buffer->is90kHzTick)
	{
		buffer->timestamp *= 100000;
		do_div (buffer->timestamp, 9);
	}

	if(
			vdec->ves != 0xff &&
			VES_ES_UpdateBuffer(vdec->ves,
				buffer->au_type,
				buffer->au_ptr,
				buffer->au_size,
				(fpCpbCopyfunc)copy_from_user,
				buffer->UId,
				buffer->timestamp,
				VDEC_UNKNOWN_PTS,
				buffer->frRes,
				buffer->frDiv) == FALSE
	  )
	{
		logm_warning (vdec, "Oops\n");
		ret = -EBUSY;
	}
	else
	{
		kick_decoder_locked (vdec);
	}

	mutex_unlock (&io_lock);

	return (ret);
}

static int get_output(noti_t *noti, LX_VDEC_OUTPUT_T *stpLXVdecOutput)
{
	int ret = 0;
	LX_VDEC_OUTPUT_T *pOut;

	pOut = noti_GetOutput(noti);

	mutex_lock (&io_lock);

	memcpy( stpLXVdecOutput, pOut, sizeof(*stpLXVdecOutput));

	mutex_unlock (&io_lock);

	return (ret);
}

static void VDEC_IO_UpdateCpbStatus(S_IPC_CALLBACK_BODY_CPBSTATUS_T *pCpbStatus)
{
	vdec_t *vdec = (vdec_t *)pCpbStatus->priv;

	logm_debug (vdec, "vdec:%p, cpb status %d\n", vdec, pCpbStatus->eBufStatus);
	if (vdec == NULL)
	{
		logm_warning (vdec, "no vdec???\n");
		return;
	}

	switch( pCpbStatus->eBufStatus )
	{
	case CPB_STATUS_ALMOST_FULL :
		VES_Flush(vdec->ves);
		break;
	case CPB_STATUS_NORMAL :
	case CPB_STATUS_ALMOST_EMPTH :
	default :
		break;
	}
}

static void VDEC_IO_RequestCmdReset(S_IPC_CALLBACK_BODY_REQUEST_CMD_T *pReqCmd)
{
	vdec_t *vdec = (vdec_t *)pReqCmd->priv;

	logm_warning (vdec, "vdec:%p, %d, %08x, %d\n", vdec,
			pReqCmd->bReset,
			pReqCmd->ui32Addr,
			pReqCmd->ui32Size);

	if (vdec->vdc == 0xff)
	{
		logm_warning (vdec, "no channel\n");
		return;
	}

	mutex_lock (&io_lock);
	//if(pReqCmd->bReset)
	//	reset(vdec);

	if(pReqCmd->ui32Addr == 0 || pReqCmd->ui32Size ==0)
		logm_debug (vdec, "vdec:%p, no seq data\n", vdec);
	else
	{
		logm_debug (vdec, "vdec:%p, seq data %08x, %08x\n", vdec,
				pReqCmd->ui32Addr,
				pReqCmd->ui32Size);

		if(
				vdec->ves != 0xff &&
				VES_ES_UpdateBuffer(vdec->ves,
					AU_SEQUENCE_HEADER,
					pReqCmd->ui32Addr,
					pReqCmd->ui32Size,
					(fpCpbCopyfunc)memcpy,
					0 /*ioUpdateBuffer.UId*/ ,
					-1 /*ioUpdateBuffer.timestamp*/,
					VDEC_UNKNOWN_PTS /*ui32TimeStamp_90kHzTick*/,
					0 /*ioUpdateBuffer.frRes*/,
					0 /*ioUpdateBuffer.frDiv*/) == FALSE
		  )
			logm_warning (vdec, "Oops\n");
	}
	mutex_unlock (&io_lock);
}

static irqreturn_t irq_handler(int irq, void *dev_id)
{
	if (VDEC_ISR_Handler() < 0)
		return IRQ_NONE;
	return IRQ_HANDLED;
}


/* vdec status proc */
static int status_show (struct seq_file *m, void *data)
{
	decoded_buffer_t current_decoded;
	vdec_t *vdec = m->private;
	unsigned long flag;
	int cpb_read, cpb_write, cpb_size;
	int auib_depth;
	struct vo_vdo_info *vdo_info;

	spin_lock_irqsave (&vdec->decoded_buffers_lock, flag);
	if (vdec->decoded_infos == NULL)
		memset (&current_decoded, 0, sizeof (current_decoded));
	else
		current_decoded = vdec->decoded_infos->buffer;
	spin_unlock_irqrestore (&vdec->decoded_buffers_lock, flag);

	vdo_info = (struct vo_vdo_info*)current_decoded.addr_tile_base;

#define seq_print_vdec(v,f)	seq_printf (m, #v"="f"\n", vdec->v)
	seq_print_vdec (ves, "%d");
	seq_print_vdec (vdc, "%d");
	seq_print_vdec (sync, "%d");
	seq_print_vdec (src, "%d");
	seq_print_vdec (dest, "%d");
	seq_print_vdec (opmode, "%d");
	seq_print_vdec (codec, "%d");
	seq_print_vdec (id, "%ld");
	seq_print_vdec (output_memory_format, "%d");
	seq_print_vdec (noti.tail, "%d");
	seq_print_vdec (noti.head, "%d");
	seq_print_vdec (decoding_queue_slots, "%d");
	seq_print_vdec (cpb_addr, "%08lx");
	seq_print_vdec (cpb_size, "%d");
	seq_print_vdec (vdo_info, "%p");
	if (vdo_info)
	{
		seq_print_vdec (vdo_info->tile_base, "%08lx");
		seq_print_vdec (vdo_info->map_type, "%d");
	}
#undef seq_print_vdec

	if (vdec->ves != 0xff)
	{
		cpb_read = VES_CPB_GetPhyRdPtr(vdec->ves)-vdec->cpb_addr;
		cpb_write = VES_CPB_GetPhyWrPtr(vdec->ves)-vdec->cpb_addr;
		auib_depth = VES_AUIB_NumActive(vdec->ves);
	}
	else
		cpb_read = cpb_write = auib_depth = 0;

	cpb_size = cpb_write - cpb_read;
	if (cpb_size < 0)
		cpb_size += vdec->cpb_size;

	seq_printf (m, "cpb_read=%d\n", cpb_read);
	seq_printf (m, "cpb_write=%d\n", cpb_write);
	seq_printf (m, "cpb_data=%d bytes\n", cpb_size);
	seq_printf (m, "auib_depth=%d\n", auib_depth);

#define seq_print_buf(v,f)	seq_printf (m, #v"="f"\n", v)
	seq_print_buf (current_decoded.addr_tile_base, "%08lx");
	seq_print_buf (current_decoded.addr_y, "%07lx");
	seq_print_buf (current_decoded.addr_cb, "%07lx");
	seq_print_buf (current_decoded.addr_cr, "%07lx");
	seq_print_buf (current_decoded.buffer_index, "%d");
	seq_print_buf (current_decoded.error_blocks, "%d");
	seq_print_buf (current_decoded.report, "%d");
	seq_print_buf (current_decoded.framerate_num, "%d");
	seq_print_buf (current_decoded.framerate_den, "%d");
	seq_print_buf (current_decoded.crop_left, "%d");
	seq_print_buf (current_decoded.crop_right, "%d");
	seq_print_buf (current_decoded.crop_top, "%d");
	seq_print_buf (current_decoded.crop_bottom, "%d");
	seq_print_buf (current_decoded.stride, "%d");
	seq_print_buf (current_decoded.width, "%d");
	seq_print_buf (current_decoded.height, "%d");
	seq_print_buf (current_decoded.interlace, "%d");
	seq_print_buf (current_decoded.picture_type, "%d");
	seq_print_buf (current_decoded.display_period, "%d");
	seq_print_buf (current_decoded.active_format, "%d");
	seq_print_buf (current_decoded.par_w, "%d");
	seq_print_buf (current_decoded.par_h, "%d");
	seq_print_buf (current_decoded.frame_packing_arrangement, "%d");
	seq_print_buf (current_decoded.dts, "%u");
	seq_print_buf (current_decoded.pts, "%u");
	seq_print_buf (current_decoded.timestamp, "%lld");
	seq_print_buf (current_decoded.multi_picture, "%d");
	seq_print_buf (current_decoded.uid, "%ld");
#undef seq_print_buf

	return 0;
}

static int status_open (struct inode *inode, struct file *file)
{
	vdec_t *vdec;
	struct proc_dir_entry *dp;
	int ret;

	dp = PDE (inode);
	vdec = dp->data;

	ret = single_open (file, status_show, vdec);
	if (ret < 0)
		return ret;

	mutex_lock (&vdec->submodule_lock);

	return ret;
}

static int status_release (struct inode *inode, struct file *file)
{
	int ret;
	struct proc_dir_entry *dp;
	vdec_t *vdec;

	dp = PDE (inode);
	vdec = dp->data;

	mutex_unlock (&vdec->submodule_lock);

	ret = single_release (inode, file);

	return ret;
}

static struct file_operations proc_status_fops =
{
	.open = status_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = status_release,
};


/* vdec cpb dump proc */
static int cpb_read (vdec_t *vdec)
{
	int read;
	int offset;
       
	read = VES_CPB_GetPhyRdPtr(vdec->ves);
	offset = read - vdec->cpb_addr;

	if (offset < 0 || offset >= vdec->cpb_size)
	{
		logm_warning (vdec_cpbdump, "vdec:%p, wrong cpb read pointer. "
				"%08x, %08lx\n", vdec,
				read, vdec->cpb_addr);
		offset = -1;
	}

	return offset;
}

static int cpbdump_open (struct inode *inode, struct file *file)
{
	vdec_t *vdec;
	struct proc_dir_entry *dp;
	int ret = 0;

	dp = PDE (inode);
	vdec = dp->data;
	file->private_data = vdec;

	if (!atomic_long_inc_not_zero (&vdec->file->f_count))
	{
		logm_warning (vdec_cpbdump, "vdec:%p, already closed?\n", vdec);
		return -EINVAL;
	}

	if (vdec->cpb_addr == 0 || vdec->cpb_size == 0)
	{
		logm_warning (vdec_cpbdump, "vdec:%p, no cpb address\n", vdec);
		ret = -EINVAL;
		goto failed;
	}

	if (vdec->cpbdump.addr == NULL)
	{
		init_waitqueue_head (&vdec->cpbdump.wq);
		vdec->cpbdump.now = cpb_read (vdec);
		logm_debug (vdec_cpbdump, "vdec:%p, current read %d\n", vdec,
				vdec->cpbdump.now);
		if (vdec->cpbdump.now < 0)
		{
			logm_warning (vdec_cpbdump, "vdec:%p, wrong cpb read\n",
					vdec);
			ret = -EINVAL;
			goto failed;
		}
		vdec->cpbdump.readed = vdec->cpbdump.now;

		vdec->cpbdump.addr = ioremap (vdec->cpb_addr, vdec->cpb_size);
		if (vdec->cpbdump.addr == NULL)
		{
			logm_warning (vdec_cpbdump, "vdec:%p, ioremap failed\n", vdec);
			ret = -EINVAL;
			goto failed;
		}
	}
	else
	{
		logm_warning (vdec_cpbdump, "vdec:%p, already opened?\n", vdec);
		ret = -EBUSY;
		goto failed;
	}

	return ret;

failed:
	fput (vdec->file);
	return ret;
}

static int cpbdump_release (struct inode *inode, struct file *file)
{
	vdec_t *vdec = file->private_data;

	logm_debug (vdec_cpbdump, "vdec:%p, close...\n", vdec);

	iounmap (vdec->cpbdump.addr);
	vdec->cpbdump.addr = NULL;

	fput (vdec->file);

	return 0;
}

static ssize_t cpbdump_read( struct file *file,
			char __user *data,
			size_t size,
			loff_t *off  )
{
	vdec_t *vdec = file->private_data;
	struct cpbdump *d = &vdec->cpbdump;
	int count1, count2;
	int ret;

	if (d->now == d->readed)
	{
		int got;

		ret = wait_event_interruptible (d->wq,
				(vdec->ves != 0xff &&
				 d->now != cpb_read (vdec)));
		if (ret < 0)
			return ret;

		d->now = cpb_read (vdec);
		if (d->now < 0)
		{
			logm_warning (vdec_cpbdump, "vdec:%p, wrong cpb read\n",
					vdec);
			return -EINVAL;
		}

		got = d->now - d->readed;
		if (got < 0)
			got += vdec->cpb_size;

		logm_debug (vdec_cpbdump, "vdec:%p, readed %d, now %d, got %d bytes\n",
				vdec, d->readed, d->now, got);
	}

	count1 = d->now - d->readed;
	count2 = 0;
	if (count1 < 0)
	{
		count1 = vdec->cpb_size - d->readed;
		count2 = d->now;
	}

	if (count1 > size)
	{
		count1 = size;
		count2 = 0;
	}
	if (count1+count2 > size)
		count2 = size-count1;
	logm_debug (vdec_cpbdump, "vdec:%p, copy %d, %d bytes\n", vdec,
			count1, count2);

	ret = copy_to_user (data, d->addr+d->readed, count1);
	if (ret > 0)
	{
		logm_warning (vdec_cpbdump, "vdec:%p, copy failed\n", vdec);
		return -EINVAL;
	}
	if (count2 > 0)
	{
		ret = copy_to_user (data+count1, d->addr, count2);
		if (ret > 0)
		{
			logm_warning (vdec_cpbdump, "vdec:%p, copy failed\n", vdec);
			return -EINVAL;
		}
	}

	d->readed += count1 + count2;
	d->readed %= vdec->cpb_size;

	return count1+count2;
}

static struct file_operations proc_cpbdump_fops =
{
	.open = cpbdump_open,
	.read = cpbdump_read,
	.release = cpbdump_release,
};


/* vdec dpb dump proc */
static int dpbdump_open (struct inode *inode, struct file *file)
{
	vdec_t *vdec;
	struct proc_dir_entry *dp;
	int ret = 0;

	dp = PDE (inode);
	vdec = dp->data;
	file->private_data = vdec;

	if (!atomic_long_inc_not_zero (&vdec->file->f_count))
	{
		logm_warning (vdec_dpbdump, "vdec:%p, already closed?\n", vdec);
		return -EINVAL;
	}

	if (vdec->dpbdump.data == NULL)
	{
		int size;

		memset (&vdec->dpbdump, 0, sizeof (vdec->dpbdump));

		init_waitqueue_head (&vdec->dpbdump.wq);
		vdec->dpbdump.size = 64;
		size = vdec->dpbdump.size * sizeof (decoded_buffer_t *);

		vdec->dpbdump.data = kmalloc (size, GFP_KERNEL);
		if (vdec->dpbdump.data == NULL)
		{
			logm_warning (vdec_dpbdump, "vdec:%p, no memory\n", vdec);
			ret = -ENOMEM;
		}
	}
	else
	{
		logm_warning (vdec_dpbdump, "vdec:%p, dpbdump already opened\n",
				vdec);
		ret = -EBUSY;
	}

	return ret;
}

static int dpbdump_release (struct inode *inode, struct file *file)
{
	vdec_t *vdec = file->private_data;
	unsigned long flag;
	decoded_buffer_t **data;

	spin_lock_irqsave (&vdec->dpbdump_lock, flag);
	data = vdec->dpbdump.data;
	vdec->dpbdump.data = NULL;
	spin_unlock_irqrestore (&vdec->dpbdump_lock, flag);

	/* free remaining decoded buffer */
	mutex_lock (&vdec->submodule_lock);
	if (vdec->dpbdump.cur)
		unref_frame_and_kick_decoder_locked (vdec,
				vdec->dpbdump.cur->addr_y);
	while (vdec->dpbdump.head != vdec->dpbdump.tail)
	{
		decoded_buffer_t *buf;

		buf = data[vdec->dpbdump.tail];
		vdec->dpbdump.tail ++;
		vdec->dpbdump.tail %= vdec->dpbdump.size;

		unref_frame_and_kick_decoder_locked (vdec, buf->addr_y);
	}
	mutex_unlock (&vdec->submodule_lock);

	/* free framebuffer or iounmap */
	if (vdec->dpbdump.fb)
		vfree (vdec->dpbdump.fb);
	if (vdec->dpbdump.fb_y)
	{
		iounmap (vdec->dpbdump.fb_y);
		iounmap (vdec->dpbdump.fb_c);
	}

	/* free queue data buffer */
	kfree (data);

	fput (vdec->file);

	return 0;
}

static ssize_t dpbdump_read( struct file *file,
			char __user *data,
			size_t size,
			loff_t *off  )
{
	vdec_t *vdec = file->private_data;
	int ret = -1;
	decoded_buffer_t *buf;
	int copied = 0;

	if (vdec->dpbdump.fb_size <= vdec->dpbdump.fb_readed)
	{
		logm_debug (vdec_dpbdump, "vdec:%p, get new buffer\n", vdec);

		/* get new buffer */
		ret = wait_event_interruptible (vdec->dpbdump.wq,
				(vdec->dpbdump.head != vdec->dpbdump.tail));
		if (ret < 0)
			return ret;

		buf = vdec->dpbdump.data[vdec->dpbdump.tail];
		vdec->dpbdump.tail ++;
		vdec->dpbdump.tail %= vdec->dpbdump.size;

		/* unref previous frame */
		if (vdec->dpbdump.cur)
		{
			mutex_lock (&vdec->submodule_lock);
			unref_frame_and_kick_decoder_locked (vdec,
					vdec->dpbdump.cur->addr_y);
			mutex_unlock (&vdec->submodule_lock);
		}
		vdec->dpbdump.cur = buf;

		logm_debug (vdec_dpbdump, "vdec:%p, get %dx%d(%d), "
				"base %08lx, y %07lx, c %07lx\n",
				vdec, buf->width, buf->height, buf->stride,
				buf->addr_tile_base,
				buf->addr_y, buf->addr_cb);

		if (vdec->dpbdump.fb_y)
		{
			iounmap (vdec->dpbdump.fb_y);
			iounmap (vdec->dpbdump.fb_c);
			vdec->dpbdump.fb_y = NULL;
			vdec->dpbdump.fb_c = NULL;
		}

		if (vdec->output_memory_format == LX_VDEC_MEMORY_FORMAT_RASTER)
		{
			/* ioremap for new framebuffer */
			logm_debug (vdec_dpbdump, "vdec:%p, raster memory,\n", vdec);

			vdec->dpbdump.fb_size_y = buf->stride*buf->height;
			vdec->dpbdump.fb_size_c = vdec->dpbdump.fb_size_y/2;
			vdec->dpbdump.fb_size = vdec->dpbdump.fb_size_y + vdec->dpbdump.fb_size_c;
			logm_debug (vdec_dpbdump, "vdec:%p, size_y %d, size_c %d\n", vdec, 
					vdec->dpbdump.fb_size_y,
					vdec->dpbdump.fb_size_c);

			vdec->dpbdump.fb_y = ioremap (buf->addr_y, vdec->dpbdump.fb_size_y);
			vdec->dpbdump.fb_c = ioremap (buf->addr_cb, vdec->dpbdump.fb_size_c);
		}
		else
		{
			if (vdec->dpbdump.fb == NULL)
			{
				vdec->dpbdump.fb_size = buf->stride * buf->height * 3 / 2;
				logm_debug (vdec_dpbdump, "vdec:%p, allocate fb %d bytes\n",
						vdec, vdec->dpbdump.fb_size);

				vdec->dpbdump.fb = vmalloc (vdec->dpbdump.fb_size);
			}

			/* convert tiled memory to raster */
			VDC_GetFrame (vdec->vdc,
					buf->buffer_index, vdec->dpbdump.fb);
		}

		/* reset read pointer */
		vdec->dpbdump.fb_readed = 0;
	}

	/* copy real framebuffer to user space */
	if (vdec->output_memory_format == LX_VDEC_MEMORY_FORMAT_RASTER)
	{
		int count;

		if (vdec->dpbdump.fb_size_y > vdec->dpbdump.fb_readed)
		{
			count = vdec->dpbdump.fb_size_y - vdec->dpbdump.fb_readed;
			if (count > size)
				count = size;

			logm_debug (vdec_dpbdump, "vdec:%p, copy y %d bytes\n", vdec,
					count);
			ret = copy_to_user (data,
					vdec->dpbdump.fb_y+vdec->dpbdump.fb_readed,
					count);
			if (ret)
				ret = -EFAULT;
			else
			{
				copied += count;
				vdec->dpbdump.fb_readed += count;
			}
		}

		if (vdec->dpbdump.fb_size_y <= vdec->dpbdump.fb_readed)
		{
			int coffset;
			coffset = vdec->dpbdump.fb_readed - vdec->dpbdump.fb_size_y;
			count = vdec->dpbdump.fb_size_c - coffset;
			if (count > size-copied)
				count = size-copied;

			logm_debug (vdec_dpbdump, "vdec:%p, copy y %d bytes\n", vdec,
					count);
			ret = copy_to_user (data,
					vdec->dpbdump.fb_c+coffset,
					count);
			if (ret)
				ret = -EFAULT;
			else
			{
				copied += count;
				vdec->dpbdump.fb_readed += count;
			}
		}
	}
	else
	{
		int count;

		count = vdec->dpbdump.fb_size - vdec->dpbdump.fb_readed;
		if (count > size)
			count = size;

		logm_debug (vdec_dpbdump, "vdec:%p, copy %d bytes\n", vdec,
				count);
		if (count > 0)
		{
			ret = copy_to_user (data,
					vdec->dpbdump.fb+vdec->dpbdump.fb_readed,
					count);
			if (ret)
				ret = -EFAULT;
			else
			{
				copied += count;
				vdec->dpbdump.fb_readed += count;
			}
		}
	}

	logm_debug (vdec_dpbdump, "vdec:%p, copied %d, readed %d\n",
			vdec, copied,
			vdec->dpbdump.fb_readed);

	if (ret < 0)
	{
		logm_warning (vdec_dpbdump, "vdec:%p, failed\n", vdec);
		return ret;
	}

	return copied;
}

static struct file_operations proc_dpbdump_fops =
{
	.open = dpbdump_open,
	.read = dpbdump_read,
	.release = dpbdump_release,
};


static int vdec_users;

/*
 * open handler for vdec device
 */
static int open(struct inode *inode, struct file *filp)
{
	vdec_t *vdec;
	int ret;

	vdec = kcalloc (1, sizeof(*vdec), GFP_KERNEL);
	if (vdec == NULL)
	{
		logm_error (vdec, "kcmalloc failed\n");
		return -ENOMEM;
	}

	vdec_users ++;
	logm_noti (vdec, "vdec:%p, opening.. user %d\n",
			vdec,
			vdec_users);

	filp->private_data = vdec;

	vdec->file = filp;

	/* default values */
	ret = noti_alloc (&vdec->noti, 64*1024);
	if (ret < 0)
		return ret;

	vdec->codec = LX_VDEC_CODEC_INVALID;
	vdec->src = LX_VDEC_SRC_BUFF;
	vdec->dest = LX_VDEC_DST_BUFF;
	vdec->output_memory_format = LX_VDEC_MEMORY_FORMAT_TILED;

	vdec->ves = 0xff;
	vdec->vdc = 0xff;
	vdec->sync = 0xff;

	vdec->clear_q = DISP_CLEAR_Q_Open (32);
	vdec->opmode = LX_VDEC_OPMOD_NORMAL;
	vdec->clock_id = 0;
	vdec->framerate_num = 0;
	vdec->seqh_done = 0;

	vdec->display_q_maxsize = 0x20;

	/* decoding q */
	vdec->decoding_queue_size = INT_MAX;
	vdec->decoding_queue_slots = INT_MAX;

	/* decoded q */
	vdec->decoded_q.push = decoded_queue_push;
	vdec->decoded_q.max_size = decoded_queue_max_size;
	vdec->decoded_q.size = decoded_queue_size;

	spin_lock_init (&vdec->decoded_buffers_lock);
	mutex_init (&vdec->submodule_lock);
	spin_lock_init (&vdec->submodule_spin_lock);

	/* dpbdump q */
	spin_lock_init (&vdec->dpbdump_lock);

	initialize_instance (vdec);

	/* initialize proc directory */
	sprintf (vdec->proc_name, "%p", vdec);
	logm_debug (vdec, "vdec:%p, proc dir name %s\n",
			vdec, vdec->proc_name);
	vdec->proc_entry = proc_mkdir (vdec->proc_name, vdec_proc_root_entry);
	vdec->proc_status = proc_create_data ("status", 0440,
			vdec->proc_entry, &proc_status_fops, vdec);
	vdec->proc_cpb = proc_create_data ("cpb", 0440,
			vdec->proc_entry, &proc_cpbdump_fops, vdec);
	vdec->proc_dpb = proc_create_data ("dpb", 0440,
			vdec->proc_entry, &proc_dpbdump_fops, vdec);

	/* add to device list */
	vdec->next = device_list;
	device_list = vdec;

	logm_trace (vdec, "vdec:%p, opened\n", vdec);

	return 0;
}

/*
 * release handler for vdec device
 */
static int close(struct inode *inode, struct file *file)
{
	vdec_t *vdec = file->private_data;
	vdec_t *now;
	unsigned long flag;

	logm_trace (vdec, "vdec:%p, closing...\n",
			vdec);
	/* del from device list */
	spin_lock_irqsave (&device_list_lock, flag);
	if (device_list == vdec)
		device_list = vdec->next;
	else
	{
		now = device_list;
		while (now->next != NULL && now->next != vdec)
			now = now->next;
		if (now->next == vdec)
			now->next = vdec->next;
		else
			logm_error (vdec, "vdec:%p, BUG???\n", vdec);
	}
	spin_unlock_irqrestore (&device_list_lock, flag);

	vdec_users --;
	logm_noti (vdec, "vdec:%p, users %d\n", vdec, vdec_users);

	/* remove proc entry */
	remove_proc_entry ("dpb", vdec->proc_entry);
	remove_proc_entry ("cpb", vdec->proc_entry);
	remove_proc_entry ("status", vdec->proc_entry);
	remove_proc_entry (vdec->proc_name, vdec_proc_root_entry);

	/* destroy submodules */
	destroy_submodules (vdec);
	noti_free (&vdec->noti);
	DISP_CLEAR_Q_Close (vdec->clear_q);

	/* make sure the workqueue empty */
	flush_workqueue (vdec_workqueue);

	logm_noti (vdec, "vdec:%p, closed.\n", vdec);
	kfree (vdec);

	return 0;
}

/*
 * ioctl handler for vdec device.
 */
static long ioctl (struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret = 0;

	vdec_t *vdec;
	union
	{
		LX_VDEC_IO_OPEN_CH_T open_ch;
		LX_VDEC_IO_PLAY_T play;
		LX_VDEC_IO_PLAY_SET_T play_set;
		LX_VDEC_IO_PLAY_GET_T play_get;
		LX_VDEC_IO_BUFFER_STATUS_T buffer_status;
		LX_VDEC_IO_UPDATE_BUFFER_T update_buffer;
		LX_VDEC_IO_UPDATE_FRAME_INFO_T update_framebuffer;
		LX_VDEC_OUTPUT_T get_output;
		unsigned long unref_decodebuffer;
		LX_VDEC_IO_VERSION_T get_version;
		LX_VDEC_SET_REG_T set_reg;
		LX_VDEC_GET_REG_T get_reg;
		unsigned int enable_log;
		LX_VDEC_DBG_CMD_T debug_command;
		LX_VDEC_GET_MEM_LOG_T get_memlog;
		LX_VDEC_IO_BUFFER_LVL_T buffer_level;
		int queue_size;
		LX_VDEC_MEMORY_FORMAT_T memory_format;
		LX_VDEC_BASETIME_T basetime;
		LX_VDEC_STC_T stc;
		LX_VDEC_CPB_INFO_T cpb_info;
		LX_VDEC_BUFFER_T buffer;
	} a;

	vdec	= file->private_data;

	logm_trace (vdec, "vdec:%p, cmd = %08x (cmd_idx=%d)\n",
			vdec, cmd, _IOC_NR(cmd));

	if (_IOC_TYPE(cmd) != LX_VDEC_IOC_MAGIC)
	{
		logm_warning (vdec, "invalid magic. magic=0x%02x\n",
				_IOC_TYPE(cmd) );
		return -ENOIOCTLCMD;
	}
	if (_IOC_NR(cmd) > LX_VDEC_IOC_MAXNR)
	{
		logm_warning (vdec, "out of ioctl command. cmd_idx=%d\n",
				_IOC_NR(cmd) );
		return -ENOIOCTLCMD;
	}


	if (_IOC_DIR(cmd) & _IOC_WRITE)
	{
		int r;

		r = copy_from_user (&a, (void*)arg, _IOC_SIZE(cmd));
		if (r)
		{
			logm_warning (vdec, "copy_from_user failed. "
					"cmd %08x, arg %08lx\n",
					cmd, arg);
			return -EFAULT;
		}
	}

	switch(cmd)
	{
		/* deprecated ioctl. used for L9 */
	case LX_VDEC_IO_OPEN_CH:
		if (vdec->vdc == 0xff)
			ret = open_channel(vdec, &a.open_ch);
		else
		{
			logm_warning (vdec, "channel already opened\n");
			ret = -EBUSY;
		}
		break;

	case LX_VDEC_IO_CLOSE_CH:
		ret = destroy_submodules(vdec);
		break;

	case LX_VDEC_IO_PLAY:
		ret = start_channel(vdec, &a.play);
		break;

	case LX_VDEC_IO_PLAY_SET:
		ret = set_play_option(vdec, &a.play_set);
		break;

	case LX_VDEC_IO_PLAY_GET:
		ret = get_play_option(vdec, &a.play_get);
		break;

	case LX_VDEC_IO_FLUSH:
		ret = _flush(vdec);
		break;

	case LX_VDEC_IO_GET_BUFFER_STATUS:
		ret = get_buffer_status(vdec, &a.buffer_status);
		break;

	case LX_VDEC_IO_UPDATE_BUFFER:
		ret = update_buffer(vdec, &a.update_buffer);
		break;

	case LX_VDEC_IO_GET_OUTPUT:
		ret = get_output(&vdec->noti, &a.get_output);
		break;

	case LX_VDEC_UNREF_DECODEBUFFER:
		mutex_lock (&vdec->submodule_lock);
		ret = unref_frame_and_kick_decoder_locked (vdec,
				a.unref_decodebuffer);
		mutex_unlock (&vdec->submodule_lock);
		break;

	case LX_VDEC_SET_DECODING_QUEUE_SIZE:
		vdec->decoding_queue_slots = a.queue_size;
		break;

	case LX_VDEC_SET_OUTPUT_MEMORY_FORMAT:
		if (vdec->vdc != 0xff)
		{
			logm_warning (vdec, "vdec:%p, setting memory format after vdc open\n",
					vdec);
			ret = -EBUSY;
			break;
		}

		vdec->output_memory_format = a.memory_format;
		logm_debug (vdec, "vdec:%p, output_memory_format %d\n",
				vdec, vdec->output_memory_format);
		break;

	case LX_VDEC_SET_SCAN_PICTURE:
		ret = set_scan_picture (vdec, arg);
		break;

	case LX_VDEC_GET_DECODED_QUEUE_SIZE:
		{
			int head, tail;

			head = vdec->noti.head;
			tail = vdec->noti.tail;

			if (head >= tail)
				a.queue_size = head - tail;
			else
				a.queue_size = vdec->noti.size - tail + head;

			logm_debug (vdec, "vdec:%p, decoded queue size %d\n",
					vdec, a.queue_size);
		}
		break;

	case LX_VDEC_SET_CODEC:
		vdec->codec = arg;
		vdec->new_apiset = 1;
		logm_debug (vdec, "vdec:%p, set codec %d\n", vdec,
				vdec->codec);
		break;

	case LX_VDEC_SET_DISPLAY_OFFSET:
		vdec->display_offset = arg;
		logm_debug (vdec, "vdec;%p, set display offset %dms\n",
				vdec, vdec->display_offset);
		if (vdec->sync != 0xff)
		{
			logm_debug (vdec, "vdec;%p, set to VDISP\n", vdec);
			VDISP_Debug_Set_DisplayOffset(vdec->sync,
					vdec->display_offset);
		}
		break;

	case LX_VDEC_SET_INPUT_DEVICE:
		vdec->src = arg;
		break;

	case LX_VDEC_SET_OUTPUT_DEVICE:
		vdec->dest = arg;
		break;

	case LX_VDEC_SET_BASETIME:
		set_basetime (vdec, vdec->clock_id,
				a.basetime.base_stc, a.basetime.base_pts);
		break;

	case LX_VDEC_GET_GLOBAL_STC:
		a.stc.stc = TOP_HAL_GetGSTCC();
		a.stc.mask = 0xffffffff;
		logm_debug (vdec, "vdec:%p, stc %08x\n", vdec, a.stc.stc);
		break;

	case LX_VDEC_SET_ID:
		vdec->id = arg;
		logm_debug (vdec, "vdec:%p, id %ld\n",
				vdec, vdec->id);
		break;

	case LX_VDEC_STEAL_USERDATA:
		vdec->userdata_thief = !!arg;
		logm_debug (vdec, "vdec:%p, userdata thief %d\n",
				vdec, vdec->userdata_thief);
		break;

	case LX_VDEC_SET_LOW_LATENCY:
		if (vdec->sync != 0xff)
		{
			logm_warning (vdec, "vdec:%p, we have sync already\n",
					vdec);
			break;
		}

		if (arg)
			vdec->opmode = LX_VDEC_OPMOD_LOW_LATENCY;
		else
			vdec->opmode = LX_VDEC_OPMOD_NORMAL;
		logm_debug (vdec, "vdec:%p, set low latency %d\n",
				vdec, vdec->opmode);

		break;

	case LX_VDEC_SET_3D_TYPE:
		logm_debug (vdec, "vdec:%p, set 3d type %ld\n",
				vdec, arg);
		if (arg > vo_3d_type_none)
		{
			logm_warning (vdec, "vdec:%p, unknown 3d type %08lx\n",
					vdec, arg);
			ret = -EINVAL;
			break;
		}
		vdec->trid_type = arg;
		break;

	case LX_VDEC_SET_CPB:
		if (vdec->cpb_addr)
		{
			logm_warning (vdec, "vdec:%p, we have cpb already.\n",
					vdec);
			ret = -EBUSY;
			break;
		}
		logm_debug (vdec, "vdec:%p, set cpb %08lx, %d\n", vdec,
				a.buffer.addr, a.buffer.size);
		vdec->cpb_addr = a.buffer.addr;
		vdec->cpb_size = a.buffer.size;
		break;

	case LX_VDEC_GET_CPB_INFO:
		a.cpb_info.addr = vdec->cpb_addr;
		a.cpb_info.size = vdec->cpb_size;
		if (vdec->ves != 0xff)
		{
			a.cpb_info.read_offset =
				VES_CPB_GetPhyRdPtr (vdec->ves) -
				vdec->cpb_addr;
			a.cpb_info.write_offset =
				VES_CPB_GetPhyWrPtr (vdec->ves) -
				vdec->cpb_addr;
		}
		else
		{
			a.cpb_info.read_offset = 0;
			a.cpb_info.write_offset = 0;
		}

		logm_debug (vdec, "vdec:%p, cpb info %08lx(%x), %d, %d\n",
				vdec,
				a.cpb_info.addr,
				a.cpb_info.size,
				a.cpb_info.read_offset,
				a.cpb_info.write_offset);
		break;

	case LX_VDEC_SET_REQUEST_PICTURES:
		vdec->frame_requested = arg;
		logm_debug (vdec, "vdec:%p, requested frame %d\n",
				vdec, vdec->frame_requested);
		break;

	case LX_VDEC_RESET:
		hardware_reset (vdec);
		logm_debug (vdec, "vdec:%p, do hardware_reset\n", vdec);
		break;

	case LX_VDEC_USE_GSTC:
		logm_debug (vdec, "vdec:%p, use gstc %ld\n", vdec, arg);
		vdec->use_gstc = !!arg;
		break;

	//case LX_VDEC_CONVERT_TO_RASTER:
	//	convert_to_raster (vdec, a.convert_to_raster);
	//	break;
	
	case LX_VDEC_SET_FLAGS:
		logm_debug (vdec, "vdec:%p, set flags %08lx\n", vdec, arg);
		vdec->flags = arg;
		break;

		/* deprecated ioctls */
	case LX_VDEC_IO_GET_VERSION:
		ret = get_firmware_version(&a.get_version);
		break;

	case LX_VDEC_IO_SET_REG:
		ret = set_register(&a.set_reg);
		break;

	case LX_VDEC_IO_GET_REG:
		ret = get_register(&a.get_reg);
		break;

	case LX_VDEC_SET_PICTURE_SIZE:
	case LX_VDEC_IO_DBG_CMD:
	case LX_VDEC_IO_GET_MEM_LOG:
	case LX_VDEC_IO_SET_BUFFER_LVL:
	case LX_VDEC_IO_UPDATE_FRMBUF:
	case LX_VDEC_IO_ENABLELOG:
		/* not supported more */
		logm_warning (vdec, "not supported ioctl\n");
		ret = -ENOIOCTLCMD;
		break;

	default:
		/* not supported more */
		logm_warning (vdec, "unknown ioctl\n");
		ret = -ENOIOCTLCMD;
		break;
	}

	if(ret < 0 && cmd != LX_VDEC_IO_GET_BUFFER_STATUS)
	{
		logm_warning (vdec, "ioctl failed (cmd:%d, ret:%d)\n",
				_IOC_NR(cmd),
				ret);
	}

	if (ret >= 0 && _IOC_DIR(cmd) & _IOC_READ)
	{
		int r;

		r = copy_to_user ((void*)arg, &a, _IOC_SIZE(cmd));
		if (r)
		{
			logm_warning (vdec, "copy_to_user failed. "
					"cmd %08x, arg %08lx\n",
					cmd, arg);
			return -EFAULT;
		}
	}

	logm_trace (vdec, "vdec:%p, cmd = %08x (cmd_idx=%d) ret %08x\n",
			vdec, cmd, _IOC_NR(cmd), ret);
	return ret;
}

static unsigned int poll (struct file *file, struct poll_table_struct *pt)
{
	vdec_t *vdec = file->private_data;
	int ret = 0;
	wait_queue_head_t *wait_decoding;
	wait_queue_head_t *wait_decoder;
	VDC_CODEC_STATE_T decoder_state;

	mutex_lock (&vdec->submodule_lock);

	/* get wait queue from submodules */
	if (vdec->ves != 0xff)
		wait_decoding = VES_AUIB_GetWaitQueueHead (vdec->ves);
	else
		wait_decoding = NULL;

	if (vdec->vdc != 0xff)
	{
		wait_decoder = NULL;
		decoder_state = VDC_GetCoreState (vdec->vdc, &wait_decoder);
	}
	else
	{
		decoder_state = VDC_CODEC_STATE_NULL;
		wait_decoder = NULL;
	}

	/* add the waits to poll table */
	poll_wait (file, &vdec->noti.wq, pt);
	if (wait_decoding)
		poll_wait (file, wait_decoding, pt);
	if (wait_decoder)
		poll_wait (file, wait_decoder, pt);

	/* check event */
	if (vdec->noti.head != vdec->noti.tail)
		ret |= POLLIN | POLLRDNORM;

	if (vdec->ves == 0xff)
	{
		ret |= POLLOUT | POLLWRNORM;

		if (vdec->flags & lx_vdec_flags_pollerr)
			ret |= POLLERR;
	}
	else if (
			vdec->decoding_queue_size > VES_CPB_GetUsedBuffer (vdec->ves) &&
			vdec->decoding_queue_slots > VES_AUIB_NumActive (vdec->ves)
		)
			ret |= POLLOUT | POLLWRNORM;

	if (
			vdec->ves != 0xff &&
			VES_AUIB_NumActive(vdec->ves) == 0 &&
			VES_CPB_GetUsedBuffer (vdec->ves) == 0 &&
			vdec->noti.head == vdec->noti.tail &&
			decoder_state == VDC_CODEC_STATE_READY
	   )
	{
		/* vdec doing nothing. all queues are empty. report error to
		 * the application the end of decoding.
		 */
		if (vdec->flags & lx_vdec_flags_pollerr)
			ret |= POLLERR;
	}

	mutex_unlock (&vdec->submodule_lock);

	return ret;
}

static unsigned long mem_base;
static int mem_size;

#if 0
static int mmap (struct file *filep, struct vm_area_struct *vma )
{
	ULONG phy_start,phy_end;
	ULONG offset = vma->vm_pgoff << PAGE_SHIFT;
	ULONG size = vma->vm_end - vma->vm_start;
	ULONG end = PAGE_ALIGN(offset + size);

	if (size & (PAGE_SIZE-1)) return -EINVAL;

	phy_start = mem_base & PAGE_MASK;
	phy_end   = PAGE_ALIGN( phy_start + mem_size);

	if ( phy_start <= offset && end <= phy_end ) goto allowed;

	return -EINVAL;

allowed:
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	if (remap_pfn_range(vma, vma->vm_start,
				vma->vm_pgoff,
				size,
				vma->vm_page_prot))
		return -EAGAIN;

	return 0;
}
#endif

static ssize_t read( struct file *file,
			char __user *data,
			size_t size,
			loff_t *off  )
{
	vdec_t *vdec = file->private_data;
	int timeout;
	int ret;

	logm_trace (vdec, "vdec:%p, size %d\n", vdec, size);

	timeout = wait_event_interruptible_timeout (vdec->noti.wq,
			vdec->noti.head != vdec->noti.tail,
			HZ/1
			);
	if (timeout < 0)
	{
		logm_debug (vdec, "vdec:%p, signaled\n", vdec);
		return timeout;
	}

	if (timeout == 0)
	{
		logm_trace (vdec, "vdec:%p, timeout\n", vdec);
		return -ETIME;
	}

	ret = noti_copy(&vdec->noti, data, size);
	logm_debug (vdec, "vdec:%p, copied %d bytes\n", vdec, ret);

	return ret;
}

#if 0
static int flush (struct file *file, fl_owner_t id)
{
	vdec_t *vdec;

	vdec = file->private_data;

	logm_noti (vdec, "vdec:%p\n", vdec);

	return _flush (vdec);
}
#endif


static struct file_operations vdec_fops =
{
	.open = open,
	.release = close,
	.unlocked_ioctl = ioctl,
	//.flush = flush,
	.read = read,
	//.mmap = mmap,
	.poll = poll,
};

void VDEC_PreInit(void)
{
}

static int vdec_major = VDEC_MAJOR;

int VDEC_Init(void)
{
	int ret;

	vdec_workqueue = create_workqueue("video decoder");

	/* proc debug interface */
	proc_init();

	/* memory pool */
	mem_size = 160*1024*1024;
	mem_base = hma_alloc_user ("ddr0", mem_size, 1<<12, "vdec");
	if (mem_base == 0)
	{
		logm_error (vdec, "no memory for vdec driver %d\n", mem_size);
		return -ENOMEM;
	}
	ret = hma_pool_register ("vdec",
			mem_base, mem_size);
	if (ret < 0)
		return ret;

	/* character device */
	ret = register_chrdev (vdec_major, "vdec", &vdec_fops);
	if (ret < 0)
	{
		logm_error (vdec, "register_chrdev failed.\n");
		return ret;
	}
	if (vdec_major == 0)
	{
		vdec_major = ret;
		logm_info (vdec, "vdec major %d\n", ret);
	}

	VDEC_CH_Init();

	//IPC_CALLBACK_Register_DecInfo(VDEC_IO_UpdateDecodingInfo);
	IPC_CALLBACK_Register_CpbStatus(VDEC_IO_UpdateCpbStatus);
	IPC_CALLBACK_Register_ReqReset(VDEC_IO_RequestCmdReset);

	/* irq */
	ret = request_irq(VDEC_MAIN_ISR_HANDLE,
			(irq_handler_t)irq_handler,
			IRQF_SHARED,
			"vdec",
			(void*)0xdecdec);
	if (ret)
	{
		logm_error (vdec, "request_irq failed %d\n", ret);
		return ret;
	}

	logm_info (vdec, "vdec initialized\n");
//	CTOP_CTRL_L9_Wr01(ctr29, jtag_sel, 	0x0);	// setting JTAG for VDEC

	/* vo device */
	{
		extern int vo_init (void);
		vo_init ();
	}

	return 0;
}

void VDEC_Cleanup(void)
{
	/* vo device */
	extern void vo_exit (void);
	vo_exit ();

	proc_cleanup ();

	/* character device */
	unregister_chrdev (vdec_major, "vdec");

	free_irq(VDEC_MAIN_ISR_HANDLE, (void*)0xdecdec);

	/* memory pool */
	hma_pool_unregister ("vdec");
	hma_free ("ddr0", mem_base);

	destroy_workqueue (vdec_workqueue);

	logm_info (vdec, "vdec device cleanup\n");
}


/**
 * @} */

