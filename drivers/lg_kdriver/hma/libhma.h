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

#ifndef _LIBHMA_H
#define _LIBHMA_H

unsigned long libhma_alloc (const char *name, int size, int align, void **vaddr);
unsigned long libhma_alloc_cached (const char *name, int size, int align, void **vaddr);
unsigned int libhma_get_ump_secure_id (unsigned long paddr);
void libhma_free (unsigned long paddr);
int libhma_cache_ctl(unsigned long paddr, void *vaddr, size_t size, int ctl);
int libhma_memcpy_tocpu(void *vaddr_des, void *vaddr_src, void *paddr_src, unsigned int size);

#endif
