
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

#include <generated/autoconf.h>

#if defined (CONFIG_MACH_LG1152)
#include "lg1152/lq_hal_api.h"
#elif defined (CONFIG_MACH_LG1154)
#include "lg1154/lq_hal_api.h"
#else
#error "unknown platform chip"
#endif

