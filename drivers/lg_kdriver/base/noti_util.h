
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
 *  Header file for LG115x Notification.
 *  general notification queue from kernel to user process.
 *
 *  author     seokjoo.lee
 *  version    1.0
 *  date       2011-04-07
 *
 *  @addtogroup lg1150_base
 *	@{
 */

#ifndef	_LX_NOTI_H_
#define	_LX_NOTI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/list.h>
#include <linux/spinlock.h>
#include "vdec_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 * Notification header structure.
 * @var lock lock for list manipulation.(list add entry/delete entry/traverse)
 */
typedef struct
{
	struct list_head	noti_list;	///< list for LX_NOTI_QUEUE_T
	spinlock_t			lock;		///< lock for LX_NOTI_QUEUE_T list for user process.
	wait_queue_head_t	wq;			///< wait queue for notification.

	UINT32		mskNotifyToCheck;	///< bit-wise OR'ed notify mask for every client process.

	char		name[8];			///< module name.
	UINT32		magic;				///< magic value for a module.
	UINT32		dbg;				///< debug flag

} LX_NOTI_HEAD_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

extern LX_NOTI_HEAD_T* LX_NOTI_Init(char *name, UINT32 magic);
extern void LX_NOTI_Finalize(LX_NOTI_HEAD_T *pHead);

extern int  LX_NOTI_AllocQueue(LX_NOTI_HEAD_T *pHead, size_t length);
extern void LX_NOTI_FreeQueue( LX_NOTI_HEAD_T * pHead );
extern void LX_NOTI_GarbageCollect( LX_NOTI_HEAD_T *pHead );

extern void LX_NOTI_SetMask(LX_NOTI_HEAD_T* pHead, UINT32 mskNotify);
extern UINT32 LX_NOTI_GetMask( LX_NOTI_HEAD_T *pHead );

extern void LX_NOTI_Save(LX_NOTI_HEAD_T *pHead, UINT32 id, void *data, int size);

extern signed long LX_NOTI_WaitTimeout(LX_NOTI_HEAD_T *pHead, signed long timeout);

extern void LX_NOTI_Wakeup(LX_NOTI_HEAD_T *pHead);

extern int  LX_NOTI_CopyToUser(LX_NOTI_HEAD_T *pHead, char __user *buffer, size_t buffer_size);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _LX_NOTI_H_ */

/** @} */
