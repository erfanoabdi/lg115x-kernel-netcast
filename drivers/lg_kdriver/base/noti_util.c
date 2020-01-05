
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
 *  Notification utility of LG115x kernel driver.
 *  Notifies event to user layer processes from kernel driver.
 *
 *  author		seokjoo.lee
 *  version	1.0
 *  date		2011-04-07
 *
 *  @addtogroup lg1150_base
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
/*
 * debug point. and mask.
 *
 * 0x0001 LX_NOTI_Alloc()
 * 0x0002 LX_NOTI_Free()
 * 0x0004 LX_NOTI_GarbageCollect()
 * 0x0008 LX_NOTI_SetMask()
 * 0x0010 LX_NOTI_Save()
 * 0x0020 LX_NOTI_CopyToUser()
 */
#define LX_NOTI_DEBUG 0x0

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/version.h>

#include "os_util.h"
#include "debug_util.h"
#include "noti_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#if ( LX_NOTI_DEBUG == 0)
#define LX_NOTI_PRINT
#else
#define LX_NOTI_PRINT		printk
#endif

/**
 * Duplication check method.
 *
 * @def _NOTI_A_QUEUE_FOR_A_PROCESS
 * allocate a queue for a process, and notification should be done in one thread for given process.
 */
#define _NOTI_A_QUEUE_FOR_A_PROCESS(_pNoti, _pTsk)	(_pNoti->tgid ==  task_tgid_nr(_pTsk))

/**
 * Duplication check method for sharing same notification queue.
 *
 * if this macro failes, allocates a new notification queue.
 *
 */
#define IS_SAME_CHECK(_pNoti, _pTsk)				_NOTI_A_QUEUE_FOR_A_PROCESS(_pNoti, _pTsk)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *  per process, per channel, notification queue.
 *
 *  stored from interrupt context
 *
 *  retrieved from task context.
 *
 */
typedef struct LX_NOTI_QUEUE
{
	struct list_head
			noti_list;		///< list member.
	spinlock_t	lock;		///< lock for read & write rofs/wofs


	UINT32		mskNotify;	///< notify Mask. see LX_VDEC_NOTIFY_MSK_T or LX_ADEC_NOTIFY_MSK_T
	void		*tsk;		///< task structure that is listening notification.
	pid_t		tgid;		///< task group id for a process.

	#define	LX_NOTI_QUEUE_FLAG_ENABLED	0x01
	#define LX_NOTI_QUEUE_FLAG_OVERFLOW	0x02

	UINT32		length;		///< length of buffer in number of unit.
	UINT32		rofs;		///< read  offset.

							// above : mainly written from task layer.
							// below : mainly written from interrupt layer.

	UINT32		wofs;		///< write offset. (updated interrupt context.)
	UINT32		flag;		///< flag enabled or not is enabled via LX_VDEC_IO_PLAY_SET -> notifyMask

	char		*buffer;	///< notification buffer.
} LX_NOTI_QUEUE_T;


/**
 * initialize LX_NOTI_HEAD_T.
 * with SPIN_LOCK_UNLOCKED, noti_list to be Empty.
 */
static inline void INIT_NOTI_HEAD(LX_NOTI_HEAD_T *noti_head)
{
	noti_head->lock = __SPIN_LOCK_UNLOCKED(noti_head->lock);
	INIT_LIST_HEAD(&noti_head->noti_list);
	init_waitqueue_head(&noti_head->wq);
	noti_head->mskNotifyToCheck = 0;
}

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
//static LX_NOTI_HEAD_T	sNotifyHead[LX_VDEC_CH_MAXN];

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * Initialize notify header for all channel and all notify ID.
 * shall be called in @ref VDEC_Init, or @ref ADEC_Init
 * [NOTE] No need to de-initialize.
 *
 * [Usage]
 *
 * 1. call LX_NOTI_Init() before enabling any interrupt / ioctl / notification.
 *
 * 2. call LX_NOTI_AllocQueue() in open()
 * example
 * @code
 * 	VDEC_Open(...)
 * 	{
 * 		if ( !Opened )
 * 		{
 * 		}
 *
 * 		LX_NOTI_AllocQueue();	// always call this function, automatically do or skip to alloc.
 * 	}
 * @endcode
 *
 * 3. call LX_NOTI_SetMask() in IO_SET_NOTIFY ioctl.
 * 4. make per-module own NOTI_Save() using LX_NOTI_Save() in appropriate position.
 *    example
 *  @code
 *	void VDEC_NOTI_SavePICH(UINT8 ch, LX_VDEC_NOTIFY_PARAM_PICH_T	*pPich)
 *	{
 *		LX_VDEC_NOTIFY_PARAM2_T	param;
 *		LX_NOTI_HEAD_T *pHead	= &sNotifyHead[ch];
 *
 *		param.magic = LX_VDEC_NOTIFY_MAGIC;;
 *		param.id = LX_VDEC_NOTIFY_ID_PICH;
 *		param.u.pich = *pPich;
 *
 *		LX_NOTI_Save(pHead, &param, sizeof(param));
 *	}
 *	@endcode

 * 5. call LX_NOTI_Wakeup() after saving notification is done.
 *
 * 6. make poll() or read() with LX_NOTI_WaitTimeout(), and LX_NOTI_CopyToUser().
 * example
 * @code
 *  VDEC_NOTI_CopyToUser(ch, buffer, size)
 *  {
 *		LX_NOTI_HEAD_T *pHead	= &sNotifyHead[ch];
 *		return LX_NOTI_CopyToUser(pHead, buffer, size);
 *  }
 *
 *	VDEC_Read()
 *	{
 *		timeout  = VDEC_NOTI_WaitTimeout(ui8Ch, timeout);
 *		if ( !timeout ) // handle timeout.
 *		{
 *		}
 *		return VDEC_NOTI_CopyToUser(ui8Ch, buffer, size);
 *	}
 *
 * @endcode
 *
 * 7. call LX_NOTI_FreeQueue() in close()
 *
 * 8. call LX_NOTI_Finalize() in module finalize()
 *
 * @param name	[IN]	name of module.
 * @param magic [IN]	magic value for each module.
 * @param nOfModule	[IN]	number of sub module.
 *
 * @return allocated LX_NOTI_HEAD_T, NULL if error.
 */
LX_NOTI_HEAD_T* LX_NOTI_Init(char *name, UINT32 magic)
{
	LX_NOTI_HEAD_T	*pHead;

	pHead = OS_KMalloc( sizeof(LX_NOTI_HEAD_T));

	if ( !pHead ) return pHead;

	INIT_NOTI_HEAD(pHead);

	strncpy(pHead->name, name, 8);
	pHead->magic = magic;

	return pHead;
}

/**
 * Deinitialize notify header.
 *
 * [NOTE] should be called
 */
void LX_NOTI_Finalize(LX_NOTI_HEAD_T *pHead)
{
	if ( !pHead ) OS_KFree(pHead);

	return;
}

/**
 * find previously allocated queue for target pid(process).
 *
 * @param ch			[IN] channel for search.
 * @param target_tsk	[IN] task struct for search.
 * @param bToDelete		[IN] if non zero, then detached from list.
 * @return previously allocated notify queue for given process, or NULL if not allocated yet.
 */
static LX_NOTI_QUEUE_T	*lx_NOTI_FindQueue(LX_NOTI_HEAD_T *pHead, struct task_struct *pTsk)
{
	LX_NOTI_QUEUE_T	*pNoti;
	unsigned long	irq_flag;

	spin_lock_irqsave(&pHead->lock, irq_flag);		//{
	list_for_each_entry(pNoti, &pHead->noti_list, noti_list)
	{
		if ( IS_SAME_CHECK(pNoti, pTsk) )
		{
			spin_unlock_irqrestore(&pHead->lock, irq_flag);
			return pNoti;
		}
	}
	spin_unlock_irqrestore(&pHead->lock, irq_flag);	//}

	return NULL;
}

/**
 * find previously allocated queue for target pid(process) to be deleted.
 *
 * [Note] automatically detached from pHead list.
 *
 * @param ch			[IN] channel for search.
 * @param target_tsk	[IN] task struct for search.
 * @return previously allocated notify queue for given process, or NULL if not allocated yet.
 */
static LX_NOTI_QUEUE_T	*lx_NOTI_FindQueueToDelete(LX_NOTI_HEAD_T *pHead, struct task_struct *pTsk)
{
	LX_NOTI_QUEUE_T	*pNoti;
	unsigned long	irq_flag;

	if ( !pHead ) return NULL;

	spin_lock_irqsave(&pHead->lock, irq_flag);		//{
	list_for_each_entry(pNoti, &pHead->noti_list, noti_list)
	{
		if ( IS_SAME_CHECK(pNoti, pTsk) )
		{
			list_del(&pNoti->noti_list);

			spin_unlock_irqrestore(&pHead->lock, irq_flag);

			return pNoti;
		}
	}
	spin_unlock_irqrestore(&pHead->lock, irq_flag);	//}

	return NULL;
}

/**
 * allocates notify event Queue.(internal)
 *
 * @param length	[IN]	length of queue in number of notify parameter.
 * @param size		[IN]	byte size of notify parameter
 * @return allocated notify queue, NULL on error.
 */
static LX_NOTI_QUEUE_T *lx_NOTI_AllocQueue( UINT16 length )
{
	LX_NOTI_QUEUE_T	*pNoti;
	unsigned long			irq_flag;

	pNoti = OS_KMalloc( sizeof ( LX_NOTI_QUEUE_T ) + length );

	if ( NULL == pNoti ) return pNoti;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
	pNoti->lock		= SPIN_LOCK_UNLOCKED;
#else
	spin_lock_init(&pNoti->lock);
#endif

	spin_lock_irqsave(&pNoti->lock, irq_flag);		//{

	INIT_LIST_HEAD(&pNoti->noti_list);
	pNoti->rofs		= 0;
	pNoti->wofs		= 0;
	pNoti->length	= length;
	pNoti->buffer	= (char*)&pNoti[1];
	pNoti->flag		= 0;
	pNoti->tsk		= current;
	pNoti->tgid		= task_tgid_nr(current);
	pNoti->mskNotify= 0;

	spin_unlock_irqrestore(&pNoti->lock, irq_flag);//}

	#if ( LX_NOTI_DEBUG & 0x0001 )
	LX_NOTI_PRINT("%s: length = %d, %p : for %4d,%4d\n", __FUNCTION__,
						pNoti->length, pNoti->buffer, task_pid_nr(current), task_tgid_nr(current));
	#endif

	return pNoti;
}

/**
 * Allocates Notification Queue.
 *
 * should be called when open() a device file.
 *
 * @param ch		[IN] channel for search.
 * @param length	[IN] queue length in number of events.
 *
 * @return 1 really allocated, zero for previously allocated. negative when error
 */
int LX_NOTI_AllocQueue(LX_NOTI_HEAD_T *pHead, size_t length)
{
	LX_NOTI_QUEUE_T	*pNoti;
	unsigned long	irq_flag;
	int				rc = 0;

	if ( !pHead ) return -1;

	pNoti = lx_NOTI_FindQueue(pHead, current);

	if ( !pNoti )
	{
		pNoti = lx_NOTI_AllocQueue( length );

		if ( NULL == pNoti ) { rc = -ENOMEM; goto LX_NOTI_Alloc_exit; }

		spin_lock_irqsave(&pHead->lock, irq_flag);		//{
		list_add_tail(&pNoti->noti_list, &pHead->noti_list);
		spin_unlock_irqrestore(&pHead->lock, irq_flag);	//}

		rc = 1;
	}
	else
	{
		rc = 0;
	}

LX_NOTI_Alloc_exit:

	#if ( LX_NOTI_DEBUG & 0x0001 )
	if ( rc != 0)
		LX_NOTI_PRINT("%7.7s ] pid %4d,%4d,%s:%d: ptr: %p len %d rc = %d\n",
				pHead->name, task_pid_nr(current), task_tgid_nr(current), __FUNCTION__, __LINE__, pNoti, length, rc);
	#endif

	return rc;
}

/**
 * Frees a Notification queue.
 *
 * should be called when close().
 *
 * [NOTE]
 * This should be
 * called AFTER detached from notification list.
 * called unlocked for notification list.
 *
 * @param pNoti	[IN] pointer to a notification queue to be freed.
 */
// [task context]
void LX_NOTI_FreeQueue( LX_NOTI_HEAD_T * pHead )
{
	LX_NOTI_QUEUE_T	*to_delete;

	if ( !pHead )	return;

	to_delete = lx_NOTI_FindQueueToDelete( pHead, current );

	if (to_delete)
	{
		OS_KFree( to_delete );

		#if (LX_NOTI_DEBUG & 0x0002  )
		if ( pHead->dbg & 0x0002 )
			LX_NOTI_PRINT("%7.7s ] %s:%d\n", pHead->name, __FUNCTION__, __LINE__);
		#endif
	}
}

/**
 * Garbage Collect for registered queue.
 *
 * to automatically free registered queue when client process was killed without explicit call of close().
 *
 * @param ch	[IN]	whcich channel to check for GC.
 *
 */
void LX_NOTI_GarbageCollect( LX_NOTI_HEAD_T *pHead )
{
	LX_NOTI_QUEUE_T	*pNoti;
	unsigned long 			irq_flag;

// 20110419 seokjoo.lee GarbageCollectiong bug.
// when a process spawns a thread and calls LX_VDEC_IO_PLAY_SET(notifyMask) and thread exits,
// then pNoti->tsk->exit_state = EXIT_DEAD and so free notify queue.
// and then another thread monitoring notification queue becomes nothing to be read.
// TODO : how can I find out parent process is alive? how many back tracking its parent?
return;

	spin_lock_irqsave(&pHead->lock, irq_flag);		//{

	list_for_each_entry(pNoti, &pHead->noti_list, noti_list)
	{
		struct task_struct *tsk = pNoti->tsk;

		if ( tsk->exit_state == EXIT_DEAD || tsk->exit_state == EXIT_ZOMBIE )
		{
			LX_NOTI_QUEUE_T	*to_delete;

			to_delete	= pNoti;
			pNoti		= list_entry(pNoti->noti_list.prev, typeof(*pNoti), noti_list);

			list_del(&to_delete->noti_list);
			spin_unlock_irqrestore(&pHead->lock, irq_flag);

			OS_KFree(to_delete);

			#if (LX_NOTI_DEBUG & 0x0004)
			if ( pHead->dbg & 0x0004 )
			LX_NOTI_PRINT("%7.7s ] NOTI_GC: %s :pid %4d,%4d, %d, %d\n",
				pHead->name,
				task_tgid_nr(tsk) == task_tgid_nr(current) ? "current":"other  ",
				task_pid_nr(tsk), task_tgid_nr(tsk),
				tsk->exit_state, tsk->exit_code);
			#endif

			spin_lock_irqsave(&pHead->lock, irq_flag);
		}
	}
	spin_unlock_irqrestore(&pHead->lock, irq_flag);	//}
}

/**
 * Enable/Disable notification.
 * Implicitly, only enable/disable for given process.
 * @param ch	[IN] channel for search.
 * @param arg	[IN] notification ID see @ref LX_VDEC_NOTIFY_ID_SEQH
 */
// [task context]
void LX_NOTI_SetMask(LX_NOTI_HEAD_T* pHead, UINT32 mskNotify)
{
	LX_NOTI_QUEUE_T	*pNoti;
	int				bMaskChanged = 0;
	unsigned long	irq_flag;
	UINT32			collected_mask = 0;

	if ( !pHead ) return;

	pNoti = lx_NOTI_FindQueue(pHead, current);

	if ( pNoti )
	{
		spin_lock_irqsave(&pNoti->lock, irq_flag);		//{
		if ( pNoti->mskNotify != mskNotify)
		{
			pNoti->mskNotify = mskNotify;
			bMaskChanged = 1;
		}

		spin_unlock_irqrestore(&pNoti->lock, irq_flag);	//}
	}

	if ( bMaskChanged )
	{

		spin_lock_irqsave(&pHead->lock, irq_flag);		//{
		list_for_each_entry(pNoti, &pHead->noti_list, noti_list)
		{
			collected_mask |= pNoti->mskNotify;
		}
		pHead->mskNotifyToCheck = collected_mask;
		spin_unlock_irqrestore(&pHead->lock, irq_flag);	//}
	}

	#if ( LX_NOTI_DEBUG & 0x0008 )
	if ( pHead->dbg & 0x0008 )
	LX_NOTI_PRINT("%7.7s ] %s:%d: mskNotify %x %x pid %d,%d\n", pHead->name, __FUNCTION__, __LINE__,
					mskNotify, collected_mask, task_pid_nr(current), task_tgid_nr(current));
	#endif
}

/**
 * Enable/Disable notification.
 * Implicitly, only enable/disable for given process.
 * @param ch	[IN] channel for search.
 * @param arg	[IN] notification ID see @ref LX_VDEC_NOTIFY_ID_SEQH
 */
// [task context]
UINT32 LX_NOTI_GetMask( LX_NOTI_HEAD_T *pHead )
{
	LX_NOTI_QUEUE_T	*pNoti;
	unsigned long	irq_flag;
	UINT32			mskNotify = 0;

	pNoti = lx_NOTI_FindQueue(pHead, current);

	if ( pNoti )
	{
		spin_lock_irqsave(&pNoti->lock, irq_flag);		//{
		mskNotify = pNoti->mskNotify;
		spin_unlock_irqrestore(&pNoti->lock, irq_flag);	//}
	}

	return mskNotify;
}

#define __noti_ofs_diff1( _len, _wofs, _rofs)	((_wofs >= _rofs) ? (wofs - rofs) : _len - rofs)
#define __noti_ofs_diff2( _len, _wofs, _rofs)	((_wofs >= _rofs) ? 0             : _wofs)

/**
 * save notify data to given queue for per-task(process) queue.
 *
 * @pre
 * [interrupt context]
 *
 * [ OBSOLETE ] 20110413 seokjoo.lee overflow check modified. T.T
 *
 * Normal condition.
 * ----------------
 * 0.0. initial condition.
 * +-------------------+
 * | | | | | | | | | | |
 * +-------------------+
 *       R=W			ISR
 *       r=w			USR
 *
 * 0.1.Save notify param to queue: 	ISR Happened and read process does not read it yet.
 * +-------------------+
 * | | | |1| | | | | | |
 * +-------------------+
 *        R>W			ISR		(locked)capture R,W to local variable. (unlocked)
 *       r=w			USR		copy_to_user( user_buffer, r, (w - r) )
 *
 * 0.2. user process read notifcation.
 * +-------------------+
 * | | | | | | | | | | |
 * +-------------------+
 *         R=W					(locked)re-read W, if W is not overflowed, then synchronize local R = W (unlocked)
 *         r=w					because overflow margin can prevent "rofs" race condition.
 *
 * 0.3.Lazy read cae
 * +-------------------+
 * | | | |1| | | | | | |
 * +-------------------+
 *        R>W
 *        r w			USR		process read r=R, w=W,
 *        				USR		copy_to_user(user_buffer, &r, (w-r))
 *
 * 0.3.1 ISR Happened during copy_to_user
 * +-------------------+
 * | | | | |1|1| | | | |
 * +-------------------+
 *        R   ->W
 *        r w			USR 	after copying is done.
 *       				USR		re-read r2=R, r2=W, and if r2 (read pointer after copied safely) is preserved before copying.
 *          R   W      	USR		update and R=w, (advance queue read pointer by pop'ed size)
 *         r=w
 *
 * overflow check.
 * --------------
 *
 * 1.1. before copy, 8 ISR with out readiing. and currently 9 th ISR happened.
 * +-------------------+
 * |1|1| | |1|1|1|1|1|1|
 * +-------------------+
 *      W   R					above condition, reader task holds R=W in local varable.
 *          O
 *
 * 1.2. after save parameter, and increasing write offset
 * +-------------------+
 * |1|1|1| |1|1|1|1|1|1|
 * +-------------------+
 *      ->W R
 *          O
 *
 * 1.3. Check Overflow in ISR
 * +-------------------+
 * |1|1|1| |1|1|1|1|1|1|
 * +-------------------+
 *        W R				if ( W + 1 == R ) R ++; // overflow warning.
 *          O
 *
 * 1.4. if (R == W+1) R++ : causes USR vs ISR rofs/wofs mismatch.
 * +-------------------+
 * |1|1|1| |1|1|1|1|1|1|
 * +-------------------+
 *        W ->R
 *          O
 *
 * 1.5. repeated 2 ISR 1.1 ~ 1.4 ( total queue length + 1 ISR happened ) -> Actual Overflow!!!
 * +-------------------+
 * |1|1|1|1|2|1|1|1|1|1|
 * +-------------------+
 *            W ->R
 *          O				-> causes copied parameter can not guarentee integrity at [w(USR) ~ W-1]
 *
 * 1.6. repeated queue length ISR happened (1.1 ~ 1.4) (ISR happened in queue length * 2 +1 times )
 * +-------------------+
 * |2|2|2|2|3|2|2|2|2|2|
 * +-------------------+
 *            W ->R
 *          O				-> what happened??
 *
 * 2.0 Extreme case.
 * How can we discriminate 1.5 between 1.6 ?
 *  -> use of notify sequence number generated by ISR.
 *
 * @endpre
 *
 * @return if success, returns zero. if error, then returns negative.
 */
// [interrupt context]
static void lx_NOTI_SaveOneQueue(LX_NOTI_QUEUE_T *pNoti, void* data, int size)
{
	unsigned long irq_flag;
	int		bOverflowed = 0;
	unsigned long	wofs2;
	int		size1, size2;

	spin_lock_irqsave(&pNoti->lock, irq_flag);		//{

	if ( size > (pNoti->length >> 1 )) size = ((pNoti->length) >> 1) ;
	//size = min((pNoti->length)>>1, size);		// heuristic. max size limited to length /2... ^.^;;

	wofs2= (pNoti->wofs + size) % pNoti->length;

	size1 = (pNoti->wofs + size > pNoti->length ) ? pNoti->length - pNoti->wofs : size;
	size2 = size - size1;

	/*
	 *  w...w2  r  : ok.
	 *  w...r...w2 : overflow.
	 *  r   w...w2 : ok..
	 * .r...w2  w. : overflow. overwrap.
	 * .w2  w...r. : overflow. overwrap.
	 * .w2  r   w. : ok.
	 */

		if ( pNoti->wofs < pNoti->rofs && pNoti->rofs < wofs2       )	bOverflowed = 1;
	if ( size2 )
	{
		if ( pNoti->rofs < wofs2       && wofs2       < pNoti->wofs )	bOverflowed = 1;
		if ( wofs2       < pNoti->wofs && pNoti->wofs < pNoti->rofs )	bOverflowed = 1;
	}

	memcpy(pNoti->buffer+pNoti->wofs, data,              size1);
	if ( size2 )
	memcpy(pNoti->buffer,             ((char*)data)+size1, size2);

	pNoti->wofs = wofs2;

	spin_unlock_irqrestore(&pNoti->lock, irq_flag);	//}

	return;
}

/**
 * save notify paramter to all process registered when enabled.
 * @param pHead		[IN]	notify Header.
 * @param notifyID	[IN]	notify ID.
 * @param data		[IN]	data to be saved into queue.
 * @param size		[IN]	byte size of data.
 */
// [interrupt context]
void LX_NOTI_Save(LX_NOTI_HEAD_T *pHead, UINT32 notifyID, void *data, int size)
{
	LX_NOTI_QUEUE_T	*pNoti;

	if ( !data )						return;

	list_for_each_entry(pNoti, &pHead->noti_list, noti_list)
	{
		#if (LX_NOTI_DEBUG & 0x0010 )
		char *p = pNoti->buffer + pNoti->wofs;
		#endif

		if ( pNoti->mskNotify & (1 << notifyID) )
		{
			lx_NOTI_SaveOneQueue(pNoti, data, size);
		}

		#if (LX_NOTI_DEBUG & 0x0010 )
		if ( pHead->dbg & 0x10)
		LX_NOTI_PRINT("%7.7s ] save (pid/tgid,%4d,%4d),{%04x, %5u,%5u, %p, %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x}\n",
			pHead->name,
			task_pid_nr(pNoti->tsk), task_tgid_nr(pNoti->tsk),
			pNoti->mskNotify, pNoti->rofs, pNoti->wofs, p,
			p[3], p[2], p[1], p[0], p[4], p[5], p[6], p[7],
			p[8+0], p[8+1], p[8+2], p[8+3], p[8+4], p[8+5], p[8+6], p[8+7]
			);
		#endif
	}

	return;
}


/**
 * Wait for notification.
 *
 * @param ch		[IN]	which channel is current process waiting for.
 * @param timeout	[IN] timeout value in jiffies.
 *
 * @return remaining timeout value. zero for timeout.
 */
signed long LX_NOTI_WaitTimeout(LX_NOTI_HEAD_T* pHead, signed long timeout)
{
	return interruptible_sleep_on_timeout(&pHead->wq, timeout);
}

/**
 * Wake up all process.
 *
 *
 * @param ch		[IN] channel
 */
void LX_NOTI_Wakeup(LX_NOTI_HEAD_T *pHead)
{
	wake_up_interruptible_all(&pHead->wq);
}

/**
 * copy to user buffer from saved notification queue.
 *
 * @param ch			[IN] channel for search.
 * @param notifyID		[IN] notification ID see @ref LX_VDEC_NOTIFY_ID_SEQH
 * @return non-negative number of bytes copied, negative when error.
 */
// [task context]
int LX_NOTI_CopyToUser(LX_NOTI_HEAD_T *pHead, char __user *buffer, size_t buffer_size)
{
	UINT16	rofs = 0, wofs = 0;
	UINT16	rofs2, wofs2;
	UINT16	length;
	LX_NOTI_QUEUE_T	*pNoti;
	size_t	count1=0, count2=0;
	size_t	unit_size = 1;
	int		bytes_copied = 0;
	int		rc = 0;

	unsigned long irq_flag;

	if ( !pHead )	return bytes_copied;

	pNoti = lx_NOTI_FindQueue(pHead, current);

	if ( !pNoti ) goto LX_NOTI_CopyToUser_exit;

	spin_lock_irqsave(&pNoti->lock, irq_flag);		//{
	rofs	= pNoti->rofs;
	wofs	= pNoti->wofs;
	length	= pNoti->length;
	spin_unlock_irqrestore(&pNoti->lock, irq_flag);	//}

	count1		= __noti_ofs_diff1(length, wofs, rofs);
	count2		= __noti_ofs_diff2(length, wofs, rofs);

	// TODO
	// insufficient 일 경우 대책?
	// oldest notification을 넘겨 줄 것인가?
	// newest notification을 넘겨 줄 것인가?
	if ( buffer_size < (count1+count2) * unit_size )
	{
		#if (LX_NOTI_DEBUG & 0x0020 )
		if ( pHead->dbg & 0x0020 )
		printk("%s: insufficient buffer size %d < (%d * %d) *%d \n", __FUNCTION__, buffer_size, count1, count2, unit_size);
		#endif
		bytes_copied = -EFAULT;
		goto LX_NOTI_CopyToUser_exit;
	}

	rc = copy_to_user(buffer,		 			pNoti->buffer + (rofs * unit_size), count1*unit_size);
	if ( count2 )
	rc = copy_to_user(buffer+count1*unit_size,	pNoti->buffer                     , count2*unit_size);

	// overflow check only.
	spin_lock_irqsave(&pNoti->lock, irq_flag);		//{
	rofs2 = pNoti->rofs;
	wofs2 = pNoti->wofs;

	// if not overflowed(is not updated by writer == ISR), then update it.
	if ( rofs == rofs2 ) pNoti->rofs = wofs;
	else
	{
		// TODO :
	}
	spin_unlock_irqrestore(&pNoti->lock, irq_flag);	//}

	bytes_copied = ((count1 + count2 ) * unit_size);

LX_NOTI_CopyToUser_exit:

	#if (LX_NOTI_DEBUG & 0x0020 )
	if ( pHead->dbg & 0x0020 )
		LX_NOTI_PRINT("%7.7s ] CopyToUser  %3d,%3d, sz %d + %d, \n", pHead->name,rofs, wofs, count1, count2);
	#endif

	return bytes_copied;
}

/** @} */
