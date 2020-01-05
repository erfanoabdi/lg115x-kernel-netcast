
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
#ifndef _TARGET_H_
#define _TARGET_H_

#include <pthread.h>

#define TLSF_MLOCK_T            pthread_mutex_t
#define TLSF_CREATE_LOCK(l)     pthread_mutex_init (l, NULL)
#define TLSF_DESTROY_LOCK(l)    pthread_mutex_destroy(l)
#define TLSF_ACQUIRE_LOCK(l)    pthread_mutex_lock(l)
#define TLSF_RELEASE_LOCK(l)    pthread_mutex_unlock(l)

#endif
