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


/** @file de_kapi.h
 *
 *	application interface header for de device
 *
 *	@author		dongho7.park (dongho7.park@lge.com)
 *	@version		0.6a
 *	@date		2009.12.30
 *
 *	@addtogroup lg1150_de
 *	@{
 */

#ifndef _DE_KAPI_EVAL_H_
#define _DE_KAPI_EVAL_H_

typedef enum {
	LX_DE_EVAL_CMD_DBI,

	LX_DE_EVAL_CMD_MAX
}
LX_DE_EVAL_CMD_T;

/**
 * de Debug argument for evaluation.
 */
typedef struct {
	int  argc;
	char **argv;
}
LX_DE_EVAL_ARG_T;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_KAPI_EVAL_H_ */
