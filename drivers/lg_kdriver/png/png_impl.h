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


/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     raxis.lim
 *  @version    1.0
 *  @date       2012-06-12
 *  @note       Additional information.
 */

#ifndef	_PNG_IMPL_H_
#define	_PNG_IMPL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "png_kapi.h"
#include "png_cfg.h"
#include "debug_util.h"
#include "os_util.h"

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
#define PNG_PRINT(fmt, args...)   DBG_PRINT( g_png_debug_fd, 0, fmt, ##args)
#define PNG_TRACE(fmt, args...)   DBG_PRINT( g_png_debug_fd, 1, fmt, ##args)
#define PNG_WARN(fmt, args...)    DBG_PRINT( g_png_debug_fd, 2, "^y^[png-warn] %s:%d -- " fmt, __F__, __L__, ##args)
#define PNG_ERROR(fmt, args...)   DBG_PRINT( g_png_debug_fd, 3, "^y^[png-err] %s:%d -- " fmt, __F__, __L__, ##args)

#define PNG_TRACE_BEGIN()         PNG_TRACE("[png:%d] BEGIN -- %s:%d\n", g_png_trace_depth++, __F__, __L__ )
#define PNG_TRACE_END()           PNG_TRACE("[png:%d] END    -- %s:%d\n", --g_png_trace_depth, __F__, __L__ )
#define PNG_TRACE_MARK()          PNG_TRACE("[png] LOGGING  -- %s:%d\n", __F__, __L__ )

#define PNG_CHECK_CODE(__checker,__if_action,fmt,args...)   \
             __CHECK_IF_ERROR(__checker, PNG_WARN, __if_action , fmt, ##args )

#define PNG_ASSERT(__checker)   \
            __CHECK_IF_ERROR( !(__checker), PNG_ERROR, /* nop */, "ASSERT FAILED" )


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
	PNG_EV_DECODE_READ_DONE	= 0x0001,	/* all PNG image stream is read to PNG H/W pipe line */
    PNG_EV_DECODE_DONE		= 0x0002,	/* PNG decode is done */
	PNG_EV_DECODE_ERROR		= 0x0010,	/* decoding error detected */
	PNG_EV_DECODE_TIMEOUT	= 0x0020,	/* PNG stuck & timeout */
};

/**
 *	main control block for png device.
 *	each minor device has unique control block
 *
 */
struct PNG_T
{
	/* chip dependent private hande */
	void*					plt_ctx;

	/*=============       Chip & Platform Independent        =================*/
	//No need to be locked
	char*					module_name;
	UINT32					chip;
	UINT32					platform;
	int						devno;
	struct cdev				cdev;			///< char device structure
	LX_PNG_DECODE_CAPS_T	caps;
	UINT32			 		max_devices;
	UINT32					max_rst_timeout;
	
	/* State machine */
	wait_queue_head_t	wq_requesters;
	rwlock_t			state_lock;
	LX_PNG_STATE_T 		cur_state;
	int 		(*changeState)(struct PNG_T* pPNG, LX_PNG_STATE_T state);

	/*=============         Chip & Platform Specific          =================*/
	OS_EVENT_T				ev;
	/* Wait queue for ISR */
	wait_queue_head_t	wq_irq;
	unsigned int 		irq_nr;
	UINT32 				handled; 
	UINT32 				max_decode_timeout; //jiffies
	int 		(*waitISR)(struct PNG_T* pPNG);
	int 		(*doneISR)(struct PNG_T* pPNG);
	int 		(*ISRHandler)(struct PNG_T* pPNG);
	int 		(*enableISR)(struct PNG_T* pPNG);
	int 		(*disableISR)(struct PNG_T* pPNG);

	/* Buffer memory */
	LX_PNG_MEM_CFG_T	*pPhyBuf;
	UINT32				window_buf_addr;
	UINT32				filter_buf_addr;
	UINT32				src_buf_addr;
	UINT32				*src_buf;
	UINT32				src_buf_size;

	/* IO memory */
	spinlock_t		IO_lock;
	UINT32			*IO_PNG_mem;
	UINT32			*IO_PNG_shadow_mem;
	UINT32			IO_PNG_mem_addr;
	UINT32			IO_PNG_mem_size;
	UINT32			*IO_ICOD_mem;
	UINT32			*IO_ICOD_shadow_mem;
	UINT32			IO_ICOD_mem_addr;
	UINT32			IO_ICOD_mem_size;

	/* public fns */
	int (*reset)(struct PNG_T* pPNG);
	int (*decodeIDAT)(struct PNG_T* pPNG, LX_PNG_DECODE_PARAM_T *pRequest);
	int (*getCurState)(void);
};

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern int	PNG_Config	(struct PNG_T **ppPNG);
extern void PNG_Unconfig(struct PNG_T *pPNG);

/*----------------------------------------------------------------------------------------
	Generic Usage Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int	g_png_debug_fd;
extern int	g_png_trace_depth;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

