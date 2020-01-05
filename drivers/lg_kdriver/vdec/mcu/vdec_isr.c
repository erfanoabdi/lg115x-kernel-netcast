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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     sooya.joo@lge.com
 * version    0.1
 * date       2010.03.11
 * note       Additional information.
 *
 * @addtogroup lg1152_vdec
 * @{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "vdec_type_defs.h"

#include "../hal/top_hal_api.h"

#include "../vdc/vdu_drv.h"
#include "../vdc/vdec_stc_timer.h"

#if (defined(USE_MCU_FOR_VDEC_VES) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VES) && !defined(__XTENSA__))
#include "../ves/ves_drv.h"
#endif
#if ( (defined(USE_MCU_FOR_VDEC_VDC) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VDC) && !defined(__XTENSA__)) )
#include "../ves/ves_cpb.h"
#include "../ves/ves_auib.h"
#endif
#if (defined(USE_MCU_FOR_VDEC_VDS) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VDS) && !defined(__XTENSA__))
#include "../vds/vsync_drv.h"
#endif

#include "log.h"

logm_define (vdec_isr, log_level_warning);

int VDEC_ISR_Handler(void)
{
	UINT32 u32IntReason = 0;
	int ret = -1;

#ifdef __XTENSA__
	u32IntReason = TOP_HAL_GetInterIntrStatus();
#else // !__XTENSA__
	u32IntReason = TOP_HAL_GetExtIntrStatus();
#endif // ~__XTENSA__

//	logm_debug (vdec_isr, "VDEC ISR :: %x \n", u32IntReason);

#if	(!defined(USE_MCU_FOR_VDEC_VDC) && !defined(__XTENSA__))
	if( u32IntReason & (1 << MACH0) )
	{
		TOP_HAL_ClearExtIntrMsk(1 << MACH0);
		VDU_Isr(0);
		++ret;
	}

	if( u32IntReason & (1 << MACH1) )
	{
		TOP_HAL_ClearExtIntrMsk(1 << MACH1);
		VDU_Isr(0);
		++ret;
	}

	if( u32IntReason & (1 << MACH0_SRST_DONE) )
	{
		TOP_HAL_ClearExtIntrMsk(1 << MACH0_SRST_DONE);
		logm_debug(vdec_isr, "Intr MACH0_SRST_DONE\n");
		++ret;
	}

	if( u32IntReason & (1 << MACH1_SRST_DONE) )
	{
		logm_debug(vdec_isr, "Intr MACH1_SRST_DONE\n");
		TOP_HAL_ClearExtIntrMsk(1 << MACH1_SRST_DONE);
		++ret;
	}
#endif

	if( u32IntReason & (1 << LQ3_DONE) )
	{
//		logm_debug (vdec_isr, "LQ Done Interrupt for IPC");
#ifdef __XTENSA__		// Receive IPC in MCU
		TOP_HAL_ClearInterIntrMsk(1 << LQ3_DONE);
#else //!__XTENSA__
//		TOP_HAL_ClearExtIntrMsk(1<<LQ3_DONE);
#endif //~__XTENSA__

#ifdef __XTENSA__		// Receive IPC in MCU
//		IPC_CMD_Receive();
#endif //~__XTENSA__
		ret ++;
	}

	if( u32IntReason & (1 << BUFFER_STATUS) ) {
		UINT32 u32BufIntReason = 0;

		TOP_HAL_ClearExtIntrMsk(1 << BUFFER_STATUS);
		u32BufIntReason = TOP_HAL_GetBufIntrStatus();

		if( u32BufIntReason & (1 << LQC0_ALMOST_EMPTY) )
		{
			STC_TIMER_ISR(0);
			TOP_HAL_ClearBufIntrMsk(1 << LQC0_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << LQC1_ALMOST_EMPTY) )
		{
			STC_TIMER_ISR(1);
			TOP_HAL_ClearBufIntrMsk(1 << LQC1_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << LQC2_ALMOST_EMPTY) )
		{
			STC_TIMER_ISR(2);
			TOP_HAL_ClearBufIntrMsk(1 << LQC2_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << LQC3_ALMOST_EMPTY) )
		{
			STC_TIMER_ISR(3);
			TOP_HAL_ClearBufIntrMsk(1 << LQC3_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << PDEC0_CPB_ALMOST_FULL) )
		{
			VDEC_ISR_CPB_AlmostFull(0);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC0_CPB_ALMOST_FULL);
		}
		if( u32BufIntReason & (1 << PDEC0_CPB_ALMOST_EMPTY) )
		{
			VDEC_ISR_CPB_AlmostEmpty(0);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC0_CPB_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << PDEC0_AUB_ALMOST_FULL) )
		{
			VDEC_ISR_AUIB_AlmostFull(0);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC0_AUB_ALMOST_FULL);
		}
		if( u32BufIntReason & (1 << PDEC0_AUB_ALMOST_EMPTY) )
		{
			VDEC_ISR_AUIB_AlmostEmpty(0);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC0_AUB_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << PDEC1_CPB_ALMOST_FULL) )
		{
			VDEC_ISR_CPB_AlmostFull(1);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC1_CPB_ALMOST_FULL);
		}
		if( u32BufIntReason & (1 << PDEC1_CPB_ALMOST_EMPTY) )
		{
			VDEC_ISR_CPB_AlmostEmpty(1);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC1_CPB_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << PDEC1_AUB_ALMOST_FULL) )
		{
			VDEC_ISR_AUIB_AlmostFull(1);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC1_AUB_ALMOST_FULL);
		}
		if( u32BufIntReason & (1 << PDEC1_AUB_ALMOST_EMPTY) )
		{
			VDEC_ISR_AUIB_AlmostEmpty(1);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC1_AUB_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << PDEC2_CPB_ALMOST_FULL) )
		{
			VDEC_ISR_CPB_AlmostFull(2);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC2_CPB_ALMOST_FULL);
		}
		if( u32BufIntReason & (1 << PDEC2_CPB_ALMOST_EMPTY) )
		{
			VDEC_ISR_CPB_AlmostEmpty(2);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC2_CPB_ALMOST_EMPTY);
		}
		if( u32BufIntReason & (1 << PDEC2_AUB_ALMOST_FULL) )
		{
			VDEC_ISR_AUIB_AlmostFull(2);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC2_AUB_ALMOST_FULL);
		}
		if( u32BufIntReason & (1 << PDEC2_AUB_ALMOST_EMPTY) )
		{
			VDEC_ISR_AUIB_AlmostEmpty(2);
			TOP_HAL_ClearBufIntrMsk(1 << PDEC2_AUB_ALMOST_EMPTY);
		}

		ret ++;
	}

	if( u32IntReason & (1 << PDEC0_AU_DETECT) ) {
		VDEC_ISR_PIC_Detected(0);
		TOP_HAL_ClearExtIntrMsk(1 << PDEC0_AU_DETECT);
		ret ++;
	}
	if( u32IntReason & (1 << PDEC1_AU_DETECT) ) {
		VDEC_ISR_PIC_Detected(1);
		TOP_HAL_ClearExtIntrMsk(1 << PDEC1_AU_DETECT);
		ret ++;
	}
	if( u32IntReason & (1 << PDEC2_AU_DETECT) ) {
		VDEC_ISR_PIC_Detected(2);
		TOP_HAL_ClearExtIntrMsk(1 << PDEC2_AU_DETECT);
		ret ++;
	}

	if( u32IntReason & (1 <<PDEC_SRST_DONE) ) {
		logm_debug(vdec_isr,  "Intr PDEC_SRST_DONE\n");
		TOP_HAL_ClearExtIntrMsk(1 << PDEC_SRST_DONE);
		ret ++;
	}

#if 0
#if (defined(USE_MCU_FOR_VDEC_VDS) && defined(__XTENSA__)) || \
	(!defined(USE_MCU_FOR_VDEC_VDS) && !defined(__XTENSA__))
	if (u32IntReason&(1<<VSYNC0)) {
		VDEC_ISR_VSync(0);
		TOP_HAL_ClearInterIntrMsk(1 << VSYNC0);
		ret ++;
	}
	if (u32IntReason&(1<<VSYNC1)) {
		VDEC_ISR_VSync(1);
		TOP_HAL_ClearInterIntrMsk(1 << VSYNC1);
		ret ++;
	}
	if (u32IntReason&(1<<VSYNC2)) {
		VDEC_ISR_VSync(2);
		TOP_HAL_ClearInterIntrMsk(1 << VSYNC2);
		ret ++;
	}
	if (u32IntReason&(1<<VSYNC3)) {
		VDEC_ISR_VSync(3);
		TOP_HAL_ClearInterIntrMsk(1 << VSYNC3);
		ret ++;
	}
	if (u32IntReason&(1<<VSYNC4)) {
		TOP_HAL_ClearInterIntrMsk(1 << VSYNC4);
		ret ++;
	}
#endif
#endif

	return ret;
}

