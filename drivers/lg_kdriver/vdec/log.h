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

#if 1

#ifndef _OLD_LOG_H
#define _OLD_LOG_H

#include <linux/kernel.h>
#include <linux/module.h>

enum
{
	log_level_error	= 1,
	log_level_warning,
	log_level_noti,
	log_level_info,
	log_level_debug,
	log_level_trace,

	log_level_user1,
	log_level_user2,
	log_level_user3,

	log_level_max = log_level_user3,
};


#define _log_print(level, name, levelstr, format, args...)	\
	printk (level " %10s %s %20s %-4d:" format, name, levelstr, __func__, __LINE__, ##args)



#ifdef LOG_NAME
/* we have onlf one log module */

#ifndef LOG_LEVEL
#define LOG_LEVEL	log_level_warning
#endif

#ifndef _TO_STR
#define _TO_STR(str) #str
#ifndef TO_STR
#define TO_STR(str) _TO_STR(str)
#endif
#endif

static int log_level __attribute__((unused)) = LOG_LEVEL;
static char *log_name __attribute__((unused)) = TO_STR(LOG_NAME);

#define _TO_LOGNAME(n)	log_##n
#define TO_LOGNAME(n)	_TO_LOGNAME(n)
module_param_named (TO_LOGNAME(LOG_NAME), log_level, int, 0640);


#define MAKE_FNAME(t)	vdec_set_log_level_ ##t
#define VDEC_SET_LOG_LV_FUNC_NAME(t)	MAKE_FNAME(t)

// function name will be vdec_set_log_level_(LOG_NAME)
void VDEC_SET_LOG_LV_FUNC_NAME(LOG_NAME) (int level)
{
	log_level = level;
	return;
}

#define log_print(format, args...)		\
	printk (KERN_ERR format, ##args)


#define log_error(format, args...)	do{ \
	if ((log_level>=log_level_error  ) || (log_level==-1)) \
	_log_print (KERN_ERR,     log_name, "ERROR", format, ##args); }while(0)
#define log_warning(format, args...)	do{ \
	if ((log_level>=log_level_warning) || (log_level==-2)) \
	_log_print (KERN_WARNING, log_name, "WARN ", format, ##args); }while(0)
#define log_noti(format, args...)	do{ \
	if ((log_level>=log_level_noti   ) || (log_level==-3)) \
	_log_print (KERN_NOTICE,  log_name, "NOTI ", format, ##args); }while(0)
#define log_info(format, args...)	do{ \
	if ((log_level>=log_level_info   ) || (log_level==-4)) \
	_log_print (KERN_INFO,    log_name, "INFO ", format, ##args); }while(0)
#define log_debug(format, args...)	do{ \
	if ((log_level>=log_level_debug  ) || (log_level==-5)) \
	_log_print (KERN_DEBUG,   log_name, "DEBUG", format, ##args); }while(0)
#define log_trace(format, args...)	do{ \
	if ((log_level>=log_level_trace  ) || (log_level==-6)) \
	_log_print (KERN_DEBUG,   log_name, "TRACE", format, ##args); }while(0)

#define log_user1(format, args...)	do{ \
	if ((log_level>=log_level_user1  ) || (log_level==-7)) \
	_log_print (KERN_ERR,     log_name, "USER1", format, ##args); }while(0)
#define log_user2(format, args...)	do{ \
	if ((log_level>=log_level_user2  ) || (log_level==-8)) \
	_log_print (KERN_ERR,     log_name, "USER2", format, ##args); }while(0)
#define log_user3(format, args...)	do{ \
	if ((log_level>=log_level_user3  ) || (log_level==-9)) \
	_log_print (KERN_ERR,     log_name, "USER3", format, ##args); }while(0)

#define log_enabled(l)		((log_level>=l) || (log_level == -l))

#endif

/* we can have multiple log molule */

#define logm_define(name,level) \
	int log_level_##name __attribute__((unused)) = level; \
	EXPORT_SYMBOL(log_level_##name); \
	module_param_named (log_##name, log_level_##name, int, 0644); \
	void vdec_set_log_level_##name (int level) \
	{ log_level_##name = level; }


#define logm_error(name,format, args...)	do{ \
	extern int log_level_##name; \
	if ((log_level_##name>=log_level_error  ) || (log_level_##name==-1)) \
	_log_print (KERN_ERR,     #name, "ERROR", format, ##args); }while(0)
#define logm_warning(name,format, args...)	do{ \
	extern int log_level_##name; \
	if ((log_level_##name>=log_level_warning) || (log_level_##name==-2)) \
	_log_print (KERN_WARNING, #name, "WARN ", format, ##args); }while(0)
#define logm_noti(name,format, args...)	do{ \
	extern int log_level_##name; \
	if ((log_level_##name>=log_level_noti   ) || (log_level_##name==-3)) \
	_log_print (KERN_NOTICE,  #name, "NOTI ", format, ##args); }while(0)
#define logm_info(name,format, args...)	do{ \
	extern int log_level_##name; \
	if ((log_level_##name>=log_level_info   ) || (log_level_##name==-4)) \
	_log_print (KERN_INFO,    #name, "INFO ", format, ##args); }while(0)
#define logm_debug(name,format, args...)	do{ \
	extern int log_level_##name; \
	if ((log_level_##name>=log_level_debug  ) || (log_level_##name==-5)) \
	_log_print (KERN_DEBUG,   #name, "DEBUG", format, ##args); }while(0)
#define logm_trace(name,format, args...)	do{ \
	extern int log_level_##name; \
	if ((log_level_##name>=log_level_trace  ) || (log_level_##name==-6)) \
	_log_print (KERN_DEBUG,   #name, "TRACE", format, ##args); }while(0)

#define logm_enabled(name,level)	({ \
	extern int log_level_##name; \
	((log_level_##name>=level) || (log_level_##name == -level)); \
	})


#endif
#else

#include "../logfunnel/log.h"

#endif
