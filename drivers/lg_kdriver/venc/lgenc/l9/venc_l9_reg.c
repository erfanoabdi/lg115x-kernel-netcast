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
 *  register api implementation for venc device of L9.
 *	venc device will teach you how to make device driver with new platform.
 *
 *  author		youngwoo.jin (youngwoo.jin@lge.com)
 *  version		1.0
 *  date		2011.05.19
 *  note		Additional information.
 *
 *  @addtogroup lg1152_venc
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "venc_l9_codec.h"
#include "venc_l9_reg.h"
#include "../venc_reg_api.h"
#include "l9/base_addr_sw_l9.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VENC_MCU_REG_BASE			( L9_VENC_BASE + 0x0700 )
#define VENC_IPC_REG_BASE			( L9_VENC_BASE + 0x0800 )

#define VENC_PREP_DE_DSIZE			( 0x00A4 )
#define VENC_PREP_DE_SEQINFO		( 0x00B4 )
#define VENC_PREP_DE_YBASE			( 0x00C0 )
#define VENC_PREP_DE_YSTRIDE		( 0x00C4 )
#define VENC_PREP_DE_CBASE			( 0x00C8 )
#define VENC_PREP_DE_CSTRIDE		( 0x00CC )
#define VENC_PREP_STC_VALUE			( 0x00D4 )

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define VENC_MCU2ARM(addr)			( addr - 0x60000000 + _gpMcuReg->sram_start0.ui32Val )
#define VENC_REG_RD32( offset )		(*(volatile UINT32 *)( (UINT32)_gpVencBase + offset ))

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
volatile VENC_L9_REG_MCU_T *_gpMcuReg;
volatile VENC_L9_REG_IPC_T *_gpIpcReg;
volatile UINT32			   *_gpVencBase;

/*========================================================================================
	Implementation Group
========================================================================================*/
static void
_VENC_REG_RunIPC( void )
{
	if ( _gpMcuReg->i_intr_st.le.ipc == 1 )
	{
		OS_UsecDelay( 100 );
	}
	_gpMcuReg->e_intr_ev.le.ipc = 1;
}

static void
_VENC_REG_Initialize( void )
{
	LX_ADDR_SW_CFG_T	addr_sw_cfg_venc;

	_gpMcuReg = (volatile VENC_L9_REG_MCU_T *) ioremap(VENC_MCU_REG_BASE, sizeof(VENC_L9_REG_MCU_T));
	_gpIpcReg = (volatile VENC_L9_REG_IPC_T *) &_gpMcuReg->ipc;

	_gpVencBase = (volatile UINT32 *) ioremap( L9_VENC_BASE, 0x100 );

	//Address switching
	BASE_L9_GetAddrSwCfg ( ADDR_SW_CFG_VENC, &addr_sw_cfg_venc);

	_gpMcuReg->axi_addr_sw_de_sav		= addr_sw_cfg_venc.de_sav;
	_gpMcuReg->axi_addr_sw_cpu_gpu		= addr_sw_cfg_venc.cpu_gpu;
	_gpMcuReg->axi_addr_sw_cpu_shadow	= addr_sw_cfg_venc.cpu_shadow;

	/* Reset the IPC registers */
	memset ( (void *) _gpIpcReg, 0, sizeof(VENC_L9_REG_IPC_T));

#if 0
	// 2011.10.17 - SD급 화질 인코딩시 Block color 깨짐현상 개선을 위해서 delay 제거함.
	/* Delay count for prepmw */
	*((volatile UINT32 *)(0xC000A0F8)) = 0x00000028;
	/* Delay count for gmau_bmw */
	*((volatile UINT32 *)(0xc000A0FC)) = 0x00000014;
#endif
}

static void
_VENC_REG_Finalize( void )
{
	if (_gpMcuReg != NULL )
	{
		iounmap( _gpMcuReg );
	}

	if (_gpVencBase != NULL )
	{
		iounmap( _gpVencBase );
	}
}

static UINT32
_VENC_REG_GetCodecData( void **o_pCodec )
{
	*o_pCodec = (void *)aui8VencCodec;
	return sizeof( aui8VencCodec );
}

static UINT32
_VENC_REG_GetFrameRate( void )
{
	UINT32 ui32FrameRate = 0;
	UINT32 ui32SeqInfo = VENC_REG_RD32( VENC_PREP_DE_SEQINFO );

	ui32FrameRate = ui32SeqInfo >> 28;

	return ui32FrameRate;
}

static void
_VENC_REG_SetProcCtrl ( UINT8 i_ui8RunStall, UINT8 i_ui8VecSel )
{
	PROC_CTRL stVal = {
		.le.vec_sel = i_ui8VecSel,
		.le.run_stall = i_ui8RunStall,
	};
	_gpMcuReg->proc_ctrl = stVal;
}

static void
_VENC_REG_SetSROMStart ( UINT32 i_ui32SromStart )
{
	_gpMcuReg->srom_start.le.srom_start = i_ui32SromStart >> 12;
}

static void
_VENC_REG_SetSRAMStart ( UINT32 i_ui32SramStart )
{
	_gpMcuReg->sram_start0.le.sram_start = i_ui32SramStart >> 12;
	_gpMcuReg->sram_start1.le.sram_start = i_ui32SramStart >> 12;
	_gpMcuReg->sram_start2.le.sram_start = i_ui32SramStart >> 12;
}

static void
_VENC_REG_SetExtInterruptEnable( UINT32 i_ui32Interrupt )
{
	_gpMcuReg->e_intr_en.ui32Val |= i_ui32Interrupt & 0x1FFF;
}

static void
_VENC_REG_SetExtInterruptDisable( UINT32 i_ui32Interrupt )
{
	_gpMcuReg->e_intr_en.ui32Val &= ~(i_ui32Interrupt & 0x1FFF);
}

static UINT32
_VENC_REG_GetInterruptStatus( void )
{
	return _gpMcuReg->e_intr_st.ui32Val;
}

static void
_VENC_REG_ClearInterrupt( UINT32 i_ui32IntrSrc )
{
	_gpMcuReg->e_intr_cl.ui32Val = i_ui32IntrSrc & 0x1FFF;
}

static void
_VENC_REG_SetSTCEnable ( BOOLEAN i_bEnableSTC )
{
	STC_CTRL stVal = _gpMcuReg->stc_ctrl;

	stVal.le.en = i_bEnableSTC ? 1 : 0;

	_gpMcuReg->stc_ctrl = stVal;
}

static void
_VENC_REG_ResetSTC ( void )
{
	_gpMcuReg->stc_ctrl.le.rst = 1;	// reset the stcc. It doesn't need to set to '0'.
}

static UINT32
_VENC_REG_GetSTCBase( void )
{
	return	_gpMcuReg->stc_base.le.stcc_41_10;
}

static UINT32
_VENC_REG_GetSTCExt( void )
{
	return _gpMcuReg->stc_ext.le.stcc_9_0;
}

static UINT32
_VENC_REG_PREP_GetSTC( void )
{
	return VENC_REG_RD32( VENC_PREP_STC_VALUE );
}

static UINT32
_VENC_REG_PREP_GetDESize( UINT16 *o_pui16Width, UINT16 *o_pui16Height )
{
	UINT32 ui32DecodeSize;

	if ( o_pui16Width == NULL || o_pui16Height == NULL )
	{
		return RET_ERROR;
	}

	ui32DecodeSize = VENC_REG_RD32( VENC_PREP_DE_DSIZE );

	*o_pui16Width  = (ui32DecodeSize & 0x0FFF0000) >> 16;
	*o_pui16Height = (ui32DecodeSize & 0x0FFF);

	return RET_OK;
}

static UINT32
_VENC_REG_PREP_GetDEYBase( void )
{
	return VENC_REG_RD32( VENC_PREP_DE_YBASE );
}

static UINT32
_VENC_REG_PREP_GetDEYStride( void )
{
	return VENC_REG_RD32( VENC_PREP_DE_YSTRIDE);
}

static UINT32
_VENC_REG_PREP_GetDECBase( void )
{
	return VENC_REG_RD32( VENC_PREP_DE_CBASE );
}

static UINT32
_VENC_REG_PREP_GetDECStride( void )
{
	return VENC_REG_RD32( VENC_PREP_DE_CSTRIDE );
}

static UINT32
_VENC_REG_IPC_GetVersion( void )
{
	return _gpIpcReg->sw_version.ui32Val;
}

static void
_VENC_REG_IPC_SetConfig( BOOLEAN i_bEnableMeLevel1, BOOLEAN i_bEnablePskipOff, BOOLEAN i_bEnableMvnumRst, BOOLEAN i_bEnableMeLevel2  )
{
	//_gpIpcReg->venc_config0.ui32Val = i_ui32Value;

	VENC_CONFIG0 stVal = _gpIpcReg->venc_config0;

	stVal.le.spe_modesel				= 0;
	stVal.le.dbg_me_level0_enable	= 1;
	//stVal.le.qp_level				= 0;
	stVal.le.deblock_off				= 0;
	stVal.le.hlambda					= 0;
	stVal.le.me_level1_enable		= i_bEnableMeLevel1 ? 1 : 0;
	stVal.le.en_pskip_off			= i_bEnablePskipOff ? 1 : 0;
	stVal.le.en_mvnum_rst			= i_bEnableMvnumRst ? 1 : 0;
	stVal.le.me_level2_enable		= i_bEnableMeLevel2 ? 1 : 0;

	_gpIpcReg->venc_config0 = stVal;

}

static void
_VENC_REG_IPC_SetQPLevel( UINT8 i_ui8QPLevel )
{
	VENC_CONFIG0 stVal = _gpIpcReg->venc_config0;

	stVal.le.qp_level 	= i_ui8QPLevel & 0x1F;	// 0 ~ 31 (Default=15)

	_gpIpcReg->venc_config0 = stVal;
}

static void
_VENC_REG_IPC_GetQPLevel( UINT8* o_pui8QPLevel )
{
	if ( o_pui8QPLevel != NULL )
	{
		*o_pui8QPLevel = _gpIpcReg->venc_config0.le.qp_level;
	}
}

static void
_VENC_REG_IPC_SetInputMode( UINT8 i_ui8InputMode )
{
	_gpIpcReg->venc_mode_in.le.input_mode = i_ui8InputMode & 0x0F;
}

static void
_VENC_REG_IPC_SetMode( UINT8 i_ui8srcType, UINT8 i_ui8ColorFmt, UINT8 i_ui8YuvMode )
{
	VENC_MODE2_IN stVal = _gpIpcReg->venc_mode2_in;

	stVal.le.source			= i_ui8srcType	& 0x03;
	stVal.le.color_format	= i_ui8ColorFmt	& 0x0F;
	stVal.le.yuyv			= i_ui8YuvMode	& 0x03;

	_gpIpcReg->venc_mode2_in = stVal;
}

static void
_VENC_REG_IPC_SetGOP( UINT8 i_ui8GopN, UINT8 i_ui8GopM, UINT8 i_ui8GopIdr )
{
	VENC_MODE2_IN stVal = _gpIpcReg->venc_mode2_in;

	// GOP_N: Length of GOP
	// GOP_M: Length of anchor ( < 3 )
	// GOP_IDR: (0: Only one IDR, 1: an IDR is in the evry GOP)
	stVal.le.gop_n 			= i_ui8GopN 		& 0xFF;
	stVal.le.gop_m 			= i_ui8GopM 		& 0x03;
	stVal.le.gop_idr 		= i_ui8GopIdr 	& 0x01;

	_gpIpcReg->venc_mode2_in = stVal;
}

static void
_VENC_REG_IPC_GetGOP( UINT8* o_pui8GopN, UINT8* o_pui8GopM, UINT8* o_pui8GopIdr )
{
	if ( o_pui8GopN != NULL )
	{
		*o_pui8GopN = _gpIpcReg->venc_mode2_in.le.gop_n;
	}

	if ( o_pui8GopM != NULL )
	{
		*o_pui8GopM = _gpIpcReg->venc_mode2_in.le.gop_m;
	}

	if ( o_pui8GopIdr != NULL )
	{
		*o_pui8GopIdr = _gpIpcReg->venc_mode2_in.le.gop_idr;
	}
}

static void
_VENC_REG_IPC_SetForceBP( BOOLEAN i_bEnableForceBP )
{
	VENC_MODE2_IN stVal = _gpIpcReg->venc_mode2_in;

	// Forcing Profile_idc Baseline set 1, main profile set 0
	stVal.le.dbg_force_bp = i_bEnableForceBP ? 1 : 0;

	_gpIpcReg->venc_mode2_in = stVal;
}

static void
_VENC_REG_IPC_SetFrameBufferBase( UINT32 i_ui32Address )
{
	_gpIpcReg->venc_frame_ba.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetDPBBase( UINT32 i_ui32Address )
{
	_gpIpcReg->venc_dpb_ba.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetThumbnailBase( UINT32 i_ui32Address )
{
	_gpIpcReg->thumbnail_ba.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetRateControl( BOOLEAN i_bEnable, UINT16 i_ui16Threshold, UINT16 i_ui16TargetBitrate )
{
	RD_CTRL stVal = _gpIpcReg->rd_ctrl;

	stVal.le.rd_ctrl_enable	= i_bEnable;
	stVal.le.threshold		= i_ui16Threshold & 0xFFF;
	stVal.le.target_bitrate	= i_ui16TargetBitrate & 0xFFFF;	// kbit/frame

	_gpIpcReg->rd_ctrl = stVal;
}

static void
_VENC_REG_IPC_GetRateControl( BOOLEAN* o_pbEnable, UINT16* o_pui16Threshold, UINT16* o_pui16TargetBitrate )
{
	if ( o_pbEnable != NULL )
	{
		*o_pbEnable 	= _gpIpcReg->rd_ctrl.le.rd_ctrl_enable;
	}

	if ( o_pui16Threshold != NULL )
	{
		*o_pui16Threshold = _gpIpcReg->rd_ctrl.le.threshold;
	}

	if ( o_pui16TargetBitrate != NULL )
	{
		*o_pui16TargetBitrate = _gpIpcReg->rd_ctrl.le.target_bitrate;
	}
}

static UINT32
_VENC_REG_IPC_GetInternalIPCState( void )
{
	return _gpIpcReg->int_ipc_state.ui32Val;
}

static void
_VENC_REG_IPC_SetSENCModeEnable( BOOLEAN i_bEnable )
{
	UINT8 ui8Disable = (i_bEnable)? 0 : 1;
	_gpIpcReg->senc_ctrl.le.senc_disable = ui8Disable & 0x01;
}

static UINT32
_VENC_REG_IPC_GetTSCount( void )
{
	return _gpIpcReg->ts_cnt.ui32Val;
}

static UINT32
_VENC_REG_IPC_GetVTSCount( void )
{
	return _gpIpcReg->v_ts_cnt.ui32Val;
}

static UINT32
_VENC_REG_IPC_GetATSCount( void )
{
	return _gpIpcReg->a_ts_cnt.ui32Val;
}

static void
_VENC_REG_IPC_SetAudioESBaseAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->aes_base_addr.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetAudioESEndAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->aes_end_addr.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetAudioAUIBaseAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->aaui_base_addr.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetAudioAUIEndAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->aaui_end_addr.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetPicResolution( UINT16 i_ui16Width, UINT16 i_ui16Height )
{
	VENC_RES_PIC stVal = {
		.le.width = i_ui16Width & 0x07FF,
		.le.height = i_ui16Height & 0x07FF,
	};
	_gpIpcReg->venc_res_pic = stVal;
}

static void
_VENC_REG_IPC_SetInputBufBaseAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->venc_bsa_ibf.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetInputBufEndAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->venc_eda_ibf.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetWriteIndexOfInputBuffer( UINT32 i_ui23Index )
{
	_gpIpcReg->venc_widx_ibf.ui32Val = i_ui23Index;
	_gpIpcReg->ext_ipc_state.le.venc_widx_ibf = 1;
	_VENC_REG_RunIPC();
}

static void
_VENC_REG_IPC_SetPictureOffset( UINT32 i_ui32Offset )
{
	_gpIpcReg->venc_offset_ibf.ui32Val = i_ui32Offset;
}

static void
_VENC_REG_IPC_SetOffset( UINT16 i_ui16HdrSize, UINT16 i_ui16Stride )
{
	VENC_OFFSET2_IBF stVal = {
		.le.hdr_sz_pic = i_ui16HdrSize & 0x07FF,
		.le.stride_pic = i_ui16Stride,
	};
	_gpIpcReg->venc_offset2_ibf = stVal;
}

static void
_VENC_REG_IPC_StartThumbnail( UINT16 i_ui16Stride, BOOLEAN i_bLockInactive, BOOLEAN i_bSeperatedChrome, BOOLEAN i_bProgressive, UINT8 i_ui8Path )
{
	THUMB_CTRL stVal = _gpIpcReg->thumb_ctrl;

	stVal.le.path					= i_ui8Path & 0x01;
	stVal.le.progressive			= (i_bProgressive)? 1 : 0;
	stVal.le.seperated_chrom_in		= (i_bProgressive)? 1 : 0;
	stVal.le.lock_inactive			= (i_bLockInactive)? 1 : 0;
	stVal.le.sw_rst					= 0;
	stVal.le.start					= 1;
	stVal.le.stride_in_thumbnail	= i_ui16Stride & 0x0FFF;

	_gpIpcReg->thumb_ctrl = stVal;
	_gpIpcReg->ext_ipc_state.le.thumb_ctrl = 1;
	_VENC_REG_RunIPC();
}

static void
_VENC_REG_IPC_ResetThumbnail( void )
{
	THUMB_CTRL stVal;

	stVal.ui32Val = 0x00;
	stVal.le.sw_rst					= 1;

	_gpIpcReg->thumb_ctrl = stVal;
	_gpIpcReg->ext_ipc_state.le.thumb_ctrl = 1;
	_VENC_REG_RunIPC();
}

static void
_VENC_REG_IPC_SetThumbInputSize( UINT16 i_ui16Width, UINT16 i_ui16Height )
{
	THUMB_SZ_IN stVal = {
		.le.width = i_ui16Width & 0x07FF,
		.le.height = i_ui16Height & 0x07FF,
	};
	_gpIpcReg->thumb_sz_in = stVal;
}

static void
_VENC_REG_IPC_SetThumbOutputSize( UINT16 i_ui16Width, UINT16 i_ui16Height )
{
	THUMB_SZ_OUT stVal = {
		.le.width = i_ui16Width & 0x07FF,
		.le.height = i_ui16Height & 0x07FF,
	};
	_gpIpcReg->thumb_sz_out = stVal;
}

static void
_VENC_REG_IPC_SetThumbInputBufBaseAddr( UINT32 i_ui32Luminance, UINT32 i_ui32Chrominance )
{
	_gpIpcReg->thumb_bsa_in.ui32Val = i_ui32Luminance;
	_gpIpcReg->thumb_bsa_in_ch.ui32Val = i_ui32Chrominance;
}

static UINT32
_VENC_REG_IPC_GetThumbOutputBufBaseAddr( void )
{
	return _gpIpcReg->thumb_bsa_out.ui32Val;
}

static void
_VENC_REG_IPC_SetVideoAUIBaseAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->vaui_bsa.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetVideoAUIEndAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->vaui_eda.ui32Val = i_ui32Address;
}

static UINT32
_VENC_REG_IPC_GetESWritePointer( void )
{
	return _gpIpcReg->venc_ext_eswptr.ui32Val;
}

static UINT32
_VENC_REG_IPC_GetESReadPointer( void )
{
	return _gpIpcReg->venc_ext_esrptr.ui32Val;
}

static UINT32
_VENC_REG_IPC_GetVideoAUIWritePointer( void )
{
	UINT32 wptr = _gpIpcReg->ves_aui_wptr.ui32Val;

#if 1
	// 2011.08.19
	// ves_aui_wptr 레지스터의 주소가 MCU 기준으로 되어있어 ARM 기준으로 변환이 필요함.
	// 차후 ARM 기준으로 변경될 경우 변환하지 않아도 됨.
	wptr = VENC_MCU2ARM(wptr);
#endif

	return wptr;
}

static UINT32
_VENC_REG_IPC_GetVideoAUIReadPointer( void )
{
	UINT32 rptr = _gpIpcReg->ves_aui_rptr.ui32Val;

#if 1
	// 2011.08.19
	// ves_aui_rptr 레지스터의 주소가 MCU 기준으로 되어있어 ARM 기준으로 변환이 필요함.
	// 차후 ARM 기준으로 변경될 경우 변환하지 않아도 됨.
	rptr = VENC_MCU2ARM(rptr);
#endif

	return rptr;
}

static void
_VENC_REG_IPC_SetCommand( UINT8 i_ui8Command )
{
	_gpIpcReg->venc_ctrl.le.enc_ctrl = i_ui8Command & 0x0F;
	_gpIpcReg->ext_ipc_state.le.venc_ctrl = 1;
	_VENC_REG_RunIPC();
}

static void
_VENC_REG_IPC_SetVideoESBaseAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->ves_bsa.ui32Val = i_ui32Address;
	_gpIpcReg->ext_ipc_state.le.ves_bsa = 1;
	_VENC_REG_RunIPC();
}

static void
_VENC_REG_IPC_SetVideoESEndAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->ves_eda.ui32Val = i_ui32Address;
	_gpIpcReg->ext_ipc_state.le.ves_eda = 1;
	_VENC_REG_RunIPC();
}

static UINT32
_VENC_REG_IPC_GetTSWritePointer( void )
{
	UINT32 wptr = _gpIpcReg->tsdump_wr_addr.ui32Val;

#if 1
	// 2011.08.29
	// test버전 firmware에서 해당 레지스터 값을 MCU기준으로 기록함.
	// 수정된 버전의 firmware받을 경우 변환하지 않아도 됨.
	wptr = VENC_MCU2ARM( wptr );
#endif

	return wptr;
}

static UINT32
_VENC_REG_IPC_GetTSReadPointer( void )
{
	UINT32 rptr = _gpIpcReg->tsdump_rd_addr.ui32Val;

	return rptr;
}

static void
_VENC_REG_IPC_SetVideoTSBaseAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->tsdump_base_addr.ui32Val = i_ui32Address;
}

static void
_VENC_REG_IPC_SetVideoTSEndAddr( UINT32 i_ui32Address )
{
	_gpIpcReg->tsdump_end_addr.ui32Val = i_ui32Address;
}

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
VENC_REG_API_T gpRegApiL9 =
{
	.Initialize						= _VENC_REG_Initialize,
	.Finalize 						= _VENC_REG_Finalize,
	.GetCodecData					= _VENC_REG_GetCodecData,
	.GetFrameRate					= _VENC_REG_GetFrameRate,

	.SetProcCtrl					= _VENC_REG_SetProcCtrl,
	.SetSROMStart					= _VENC_REG_SetSROMStart,
	.SetSRAMStart					= _VENC_REG_SetSRAMStart,
	.SetExtInterruptEnable			= _VENC_REG_SetExtInterruptEnable,
	.SetExtInterruptDisable			= _VENC_REG_SetExtInterruptDisable,
	.GetInterruptStatus				= _VENC_REG_GetInterruptStatus,
	.ClearInterrupt					= _VENC_REG_ClearInterrupt,
	.SetSTCEnable					= _VENC_REG_SetSTCEnable,
	.ResetSTC						= _VENC_REG_ResetSTC,
	.GetSTCBase						= _VENC_REG_GetSTCBase,
	.GetSTCExt						= _VENC_REG_GetSTCExt,

	.PREP_GetSTC					= _VENC_REG_PREP_GetSTC,
	.PREP_GetDESize					= _VENC_REG_PREP_GetDESize,
	.PREP_GetDEYBase				= _VENC_REG_PREP_GetDEYBase,
	.PREP_GetDEYStride				= _VENC_REG_PREP_GetDEYStride,
	.PREP_GetDECBase				= _VENC_REG_PREP_GetDECBase,
	.PREP_GetDECStride				= _VENC_REG_PREP_GetDECStride,

	.IPC_GetVersion					= _VENC_REG_IPC_GetVersion,
	.IPC_SetConfig					= _VENC_REG_IPC_SetConfig,
	.IPC_SetQPLevel					= _VENC_REG_IPC_SetQPLevel,
	.IPC_GetQPLevel 				= _VENC_REG_IPC_GetQPLevel,

	.IPC_SetInputMode				= _VENC_REG_IPC_SetInputMode,
	.IPC_SetGOP						= _VENC_REG_IPC_SetGOP,
	.IPC_GetGOP 					= _VENC_REG_IPC_GetGOP,
	.IPC_SetForceBP					= _VENC_REG_IPC_SetForceBP,
	.IPC_SetMode					= _VENC_REG_IPC_SetMode,
	.IPC_SetFrameBufferBase			= _VENC_REG_IPC_SetFrameBufferBase,
	.IPC_SetDPBBase					= _VENC_REG_IPC_SetDPBBase,
	.IPC_SetThumbnailBase			= _VENC_REG_IPC_SetThumbnailBase,
	.IPC_SetRateControl				= _VENC_REG_IPC_SetRateControl,
	.IPC_GetRateControl 			= _VENC_REG_IPC_GetRateControl,
	.IPC_GetInternalIPCState		= _VENC_REG_IPC_GetInternalIPCState,
	.IPC_SetSENCModeEnable			= _VENC_REG_IPC_SetSENCModeEnable,
	.IPC_GetTSCount					= _VENC_REG_IPC_GetTSCount,
	.IPC_GetVTSCount				= _VENC_REG_IPC_GetVTSCount,
	.IPC_GetATSCount				= _VENC_REG_IPC_GetATSCount,
	.IPC_SetAudioESBaseAddr			= _VENC_REG_IPC_SetAudioESBaseAddr,
	.IPC_SetAudioESEndAddr			= _VENC_REG_IPC_SetAudioESEndAddr,
	.IPC_SetAudioAUIBaseAddr		= _VENC_REG_IPC_SetAudioAUIBaseAddr,
	.IPC_SetAudioAUIEndAddr			= _VENC_REG_IPC_SetAudioAUIEndAddr,
	.IPC_SetPicResolution			= _VENC_REG_IPC_SetPicResolution,
	.IPC_SetInputBufBaseAddr		= _VENC_REG_IPC_SetInputBufBaseAddr,
	.IPC_SetInputBufEndAddr			= _VENC_REG_IPC_SetInputBufEndAddr,
	.IPC_SetWriteIndexOfInputBuffer	= _VENC_REG_IPC_SetWriteIndexOfInputBuffer,
	.IPC_SetPictureOffset			= _VENC_REG_IPC_SetPictureOffset,
	.IPC_SetOffset					= _VENC_REG_IPC_SetOffset,
	.IPC_StartThumbnail				= _VENC_REG_IPC_StartThumbnail,
	.IPC_ResetThumbnail				= _VENC_REG_IPC_ResetThumbnail,
	.IPC_SetThumbInputSize			= _VENC_REG_IPC_SetThumbInputSize,
	.IPC_SetThumbOutputSize			= _VENC_REG_IPC_SetThumbOutputSize,
	.IPC_SetThumbInputBufBaseAddr	= _VENC_REG_IPC_SetThumbInputBufBaseAddr,
	.IPC_GetThumbOutputBufBaseAddr	= _VENC_REG_IPC_GetThumbOutputBufBaseAddr,
	.IPC_SetVideoAUIBaseAddr			= _VENC_REG_IPC_SetVideoAUIBaseAddr,
	.IPC_SetVideoAUIEndAddr			= _VENC_REG_IPC_SetVideoAUIEndAddr,
	.IPC_GetESWritePointer			= _VENC_REG_IPC_GetESWritePointer,
	.IPC_GetESReadPointer			= _VENC_REG_IPC_GetESReadPointer,
	.IPC_GetVideoAUIWritePointer		= _VENC_REG_IPC_GetVideoAUIWritePointer,
	.IPC_GetVideoAUIReadPointer		= _VENC_REG_IPC_GetVideoAUIReadPointer,
	.IPC_SetCommand					= _VENC_REG_IPC_SetCommand,
	.IPC_SetVideoESBaseAddr			= _VENC_REG_IPC_SetVideoESBaseAddr,
	.IPC_SetVideoESEndAddr			= _VENC_REG_IPC_SetVideoESEndAddr,
	.IPC_GetTSWritePointer			= _VENC_REG_IPC_GetTSWritePointer,
	.IPC_GetTSReadPointer			= _VENC_REG_IPC_GetTSReadPointer,
	.IPC_SetVideoTSBaseAddr 			= _VENC_REG_IPC_SetVideoTSBaseAddr,
	.IPC_SetVideoTSEndAddr			= _VENC_REG_IPC_SetVideoTSEndAddr,
};


/** @} */

