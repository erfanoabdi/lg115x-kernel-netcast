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
 *	GFX hw control
 *
 *  author      sinchul.jung (sinchul.jung@lge.com)
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define GFX_PALETTE_AUTO_INC

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "gfx_impl.h"
#include "gfx_reg_l9a0.h"
#include <linux/delay.h>
#include <asm/io.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define GFX_WRITE_REG(reg,val)	\
    __raw_writel(val , (ULONG)(g_gfx_reg_l9a0) + (ULONG)OFFSET(GFX_L9A0_REG_T,reg))

#define GFX_READ_REG(reg)	\
    __raw_readl( (ULONG)(g_gfx_reg_l9a0) + (ULONG)OFFSET(GFX_L9A0_REG_T,reg))

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32	addr;
	UINT32	data0;
	UINT32	data1;
	UINT32	data2;
}
GFX_SCALER_HPHASE_DATA_T;

typedef struct
{
	UINT32	addr;
	UINT32	data0;
	UINT32	data1;
}
GFX_SCALER_VPHASE_DATA_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile GFX_L9A0_REG_T	*g_gfx_reg_l9a0;
extern GFX_L9A0_REG_T 			*g_gfx_reg_l9a0_cache;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile UINT32 g_ui_ack_mode_l9a0 = 0;

#ifdef	KDRV_CONFIG_PM
unsigned int g_pm_cmd_delay_l9a0	= 0;
unsigned int g_pm_intr_ctrl_l9a0	= 0;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/** initialize scaler
 *
 *
 */
void	GFX_L9_InitScaler(void)
{
	int	i;

	const static GFX_SCALER_HPHASE_DATA_T	hphase_data[] = {
		{ 0x00000010, 0x3fd00400, 0x0ffc0340, 0x00000000 },
		{ 0x00000011, 0xff6013ff, 0x1ff00b3f, 0x00000000 },
		{ 0x00000012, 0x7f001bfe, 0x3fe4143f, 0x0000ffc0 },
		{ 0x00000013, 0xbea027fd, 0x4fd81d3e, 0x0000ffc0 },
		{ 0x00000014, 0x3e502ffc, 0x6fc8263e, 0x0000ff80 },
		{ 0x00000015, 0x3e0037fb, 0x7fbc303d, 0x0000ff80 },
		{ 0x00000016, 0x7dc03bfa, 0x9fac3a3c, 0x0000ff40 },
		{ 0x00000017, 0xbd9043fa, 0xafa0443a, 0x0000ff40 },
		{ 0x00000018, 0x7d6047f9, 0xbf944f39, 0x0000ff00 },
		{ 0x00000019, 0x3d404bf9, 0xdf885a37, 0x0000ff00 },
		{ 0x0000001a, 0x7d204ff9, 0xef7c6535, 0x0000fec0 },
		{ 0x0000001b, 0x7d1053f8, 0xff707033, 0x0000fec0 },
		{ 0x0000001c, 0x7d0053f8, 0x0f647c31, 0x0000fe81 },
		{ 0x0000001d, 0xfd0053f8, 0x1f5c872e, 0x0000fe81 },
		{ 0x0000001e, 0x3d1053f9, 0x2f54922c, 0x0000fe41 },
		{ 0x0000001f, 0xfd204ff9, 0x3f4c9c29, 0x0000fe41 }
	};

	const static GFX_SCALER_VPHASE_DATA_T	vphase_data[] = {
		{ 0x00000010, 0x002403fe, 0x00000000 },
		{ 0x00000011, 0xc09403f8, 0x000000ff },
		{ 0x00000012, 0x8103fbf4, 0x000000ff },
		{ 0x00000013, 0x4183eff0, 0x000000ff },
		{ 0x00000014, 0xc203e7ec, 0x000000fe },
		{ 0x00000015, 0x8293cfea, 0x000000fe },
		{ 0x00000016, 0x0323bfe7, 0x000000fe },
		{ 0x00000017, 0xc3c3a3e5, 0x000000fd },
		{ 0x00000018, 0x446387e4, 0x000000fd },
		{ 0x00000019, 0xc5036be3, 0x000000fc },
		{ 0x0000001a, 0x45b347e3, 0x000000fc },
		{ 0x0000001b, 0xc66323e3, 0x000000fb },
		{ 0x0000001c, 0x4712fbe4, 0x000000fb },
		{ 0x0000001d, 0xc7d2d3e4, 0x000000fa },
		{ 0x0000001e, 0x8882a7e5, 0x000000fa },
		{ 0x0000001f, 0x09327be7, 0x000000fa }
	};

	const int	num_hphase_data = NELEMENTS(hphase_data);
	const int	num_vphase_data = NELEMENTS(vphase_data);

	/* initialize scaler line memory */
	g_gfx_reg_l9a0->scaler_line_init.scaler_line_init = 0x1;
	g_gfx_reg_l9a0->scaler_line_init.scaler_line_init = 0x0;

	/* initialize H coefficient */
	for ( i=0; i<num_hphase_data; i++ )
	{
		g_gfx_reg_l9a0->scaler_hphase_data0 = hphase_data[i].data0;
		g_gfx_reg_l9a0->scaler_hphase_data1 = hphase_data[i].data1;
		g_gfx_reg_l9a0->scaler_hphase_data2 = hphase_data[i].data2;
		g_gfx_reg_l9a0->scaler_hphase_addr 	= hphase_data[i].addr;
	}

	/* initialize V coefficient */
	for ( i=0; i<num_vphase_data; i++ )
	{
		g_gfx_reg_l9a0->scaler_vphase_data0 = vphase_data[i].data0;
		g_gfx_reg_l9a0->scaler_vphase_data1 = vphase_data[i].data1;
		g_gfx_reg_l9a0->scaler_vphase_addr 	= vphase_data[i].addr;
	}
}

/** generate CQ BATCH RUN command after single or multiple CQ operation group.
 *	-- single CQ operation group is consist of single or multi normal CQs and CQ START
 *
 */
int GFX_L9_RunFlushCommand(void)
{
	GFX_TRACE_BEGIN();
	GFX_WARN("%s:%d -- CQ BATCH RUN issue !!!\n", __F__, __L__ );

#if 1
	GFX_WRITE_REG( gfx_batch_run, 0x1 );
#else
	g_gfx_reg_l9a0->gfx_pause.gfx_pause				= 0x0;
	g_gfx_reg_l9a0->gfx_reset.gfx_reset				= 0x0;
	g_gfx_reg_l9a0->gfx_start.gfx_start				= 0x0;
	g_gfx_reg_l9a0->gfx_batch_run.gfx_batch_run		= 0x1;
#endif

	GFX_TRACE_END();
	return RET_OK;
}

/** generate CQ START command after every GFX operation such write, blit etc.
 *
 *
 */
int GFX_L9_RunStartCommand(void)
{
	GFX_TRACE_BEGIN();
	GFX_PRINT("%s:%d -- CQ START issue !!!\n", __F__, __L__ );

#if 1
	GFX_WRITE_REG( gfx_start, 0x1 );
#else
	g_gfx_reg_l9a0->gfx_pause.gfx_pause				= 0x0;
	g_gfx_reg_l9a0->gfx_reset.gfx_reset				= 0x0;
	g_gfx_reg_l9a0->gfx_batch_run.gfx_batch_run		= 0x0;
	g_gfx_reg_l9a0->gfx_start.gfx_start				= 0x1;
#endif
	GFX_TRACE_END();
	return RET_OK;
}

/** pause GFX command
 *
 */
int GFX_L9_PauseCommand(void)
{
	GFX_TRACE_BEGIN();
	g_gfx_reg_l9a0->gfx_reset.gfx_reset				= 0x0;
	g_gfx_reg_l9a0->gfx_batch_run.gfx_batch_run		= 0x0;
	g_gfx_reg_l9a0->gfx_start.gfx_start				= 0x0;
	g_gfx_reg_l9a0->gfx_pause.gfx_pause				= 0x1;
	GFX_TRACE_END();

	return 0;
}

/** resume GFX command
 *
 */
int GFX_L9_ResumeCommand(void)
{
	GFX_TRACE_BEGIN();
	g_gfx_reg_l9a0->gfx_reset.gfx_reset				= 0x0;
	g_gfx_reg_l9a0->gfx_batch_run.gfx_batch_run		= 0x0;
	g_gfx_reg_l9a0->gfx_start.gfx_start				= 0x0;
	g_gfx_reg_l9a0->gfx_pause.gfx_pause				= 0x2;
	GFX_TRACE_END();

	return 0;
}

/** stop GFX command ( reset GFX & flush command queue )
 *
 */
int GFX_L9_StopCommand(void)
{
	GFX_TRACE_BEGIN();
//	printk("[gfx recovery start]\n");
//	printk( "gfx reg 0x%4x : 0x%08x\n", 0x4, GFX_READ_REG( gfx_status0 ) );
//	printk( "gfx reg 0x%4x : 0x%08x\n", 0x8, GFX_READ_REG( gfx_status1 ) );
//	printk( "gfx reg 0x%4x : 0x%08x\n", 0xC, GFX_READ_REG( gfx_status2 ) );

	GFX_WRITE_REG( gfx_reset, 0x1 );
	OS_NsecDelay(1);
	GFX_WRITE_REG( scaler_soft_reset, 0x1 );
	GFX_WRITE_REG( scaler_soft_reset, 0x0 );

	return 0;
}

/** Do soft reset 
 *
 * @return RET_OK when sucess, RET_ERROR otherwise
 */
int GFX_L9_SwResetCommand(void)
{
	int	i;

	GFX_TRACE_BEGIN();
	GFX_WRITE_REG( gfx_reset, 0x1 );

	/* raxis.lim (2011/05/21)
	 * After gfx_reset, GFX should wait until the memory flush status become to zero.
	 * Test result shows that flush status goes to zero within a few system clocks.
     * So the below loop breaks at loop count value 0 !!
	 */
	for ( i=0; i<100; i++ )
	{
		if( g_gfx_reg_l9a0->gfx_status2.mflust_st == 0x0 ) break;
	}

	GFX_WRITE_REG( scaler_soft_reset, 0x1 );
	GFX_WRITE_REG( scaler_soft_reset, 0x0 );
	GFX_TRACE_END();

	return (i>0)? RET_OK:RET_ERROR;
}

/** get command queue status 
 *
 */
void GFX_L9_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue)
{
	GFX_TRACE_BEGIN();
	GFX_RdFL( gfx_status0 );
	GFX_RdFL( gfx_status1 );
	GFX_RdFL( gfx_status2 );

	GFX_Rd01( gfx_status0, exec_line, queue->usLine );
	GFX_Rd01( gfx_status0, exec_status, queue->bStatus );
	GFX_Rd01( gfx_status1, que_remain, queue->usRemainSpace );
	GFX_Rd01( gfx_status1, cmd_que_full, queue->bFull );
	GFX_Rd01( gfx_status1, cmd_que_status, queue->bCmdQStatus );
	GFX_Rd01( gfx_status2, batch_status, queue->bBatchStatus );
	GFX_Rd01( gfx_status2, batch_remain, queue->usRemainParam );

	queue->status[0] = GFX_Rd( gfx_status0 );
	queue->status[1] = GFX_Rd( gfx_status1 );
	queue->status[2] = GFX_Rd( gfx_status2 );

	GFX_TRACE_END();
}

/**	check if GFX engine is idle or busy state.
 *	this function is used for detecting graphic sync.
 *
 *	@param	none
 *	@return TRUE if GFX is idle, FALSE otherwise
 *	@note check code seems tbe be somewhat hureustric.
 *
 *	@see	GFX_IOW_WAIT_FOR_SYNC
 */
BOOLEAN GFX_L9_IsGfxIdle(void)
{
    BOOLEAN ret;

	GFX_RdFL( gfx_status0 );
	GFX_RdFL( gfx_status1 );
	GFX_RdFL( gfx_status2 );

	ret = ( g_gfx_reg_l9a0_cache->gfx_status0.exec_status	== 0 &&
			g_gfx_reg_l9a0_cache->gfx_status1.cmd_que_status== 0 )? TRUE : FALSE;
//   ret = ( g_gfx_reg_l9a0->status0.bwCmdStatus == 0 &&
//          g_gfx_reg_l9a0->status0.abwProcessingLine == 0 &&
//          g_gfx_reg_l9a0->status1.bwCmdQueueStatus == 0 )? TRUE : FALSE ;

//	printk("GFX IDLE = (%s) %d-%d-%d\n", (ret)? "IDLE":"BUSY", g_gfx_reg_l9a0_cache->gfx_status0.exec_status, g_gfx_reg_l9a0_cache->gfx_status0.exec_line, g_gfx_reg_l9a0_cache->gfx_status1.cmd_que_status );

    return ret;
}

/** get operation status & chroma filtering mode
 *
 *
 */
void GFX_L9_GetOperationStatus(GFX_CMD_OP_T *operate)
{
	GFX_TRACE_BEGIN();
	GFX_RdFL( gfx_op_mode );
	GFX_RdFL( cflt_coef0 );
	GFX_RdFL( cflt_coef1 );

	GFX_Rd04( gfx_op_mode,	op_mode,	operate->sPort,	
							burst_mode,	operate->bBurstModeEnable,							
							clut_up_en, operate->bUpdateCLUT,
							cflt_mode, 	operate->sFmode );

//	operate->sPort = g_gfx_reg_l9a0->op_mode.abwOpMode;	// pixel format
//	operate->bBurstModeEnable = g_gfx_reg_l9a0->op_mode.bwEnableBusrtMode;		// burst mode enable
//	operate->bUpdateCLUT = g_gfx_reg_l9a0->op_mode.bwEnableCLUTUpdate;
	operate->bChromaFilterEnable = 0 ; //g_gfx_reg_l9a0->op_mode.bwEnChromaFilter;
//	operate->sFmode = g_gfx_reg_l9a0->op_mode.abwChromaFilterMode;

	GFX_Rd02( cflt_coef0, 	cflt_coef_0, operate->usCoef[0],
							cflt_coef_1, operate->usCoef[1] );
	GFX_Rd02( cflt_coef1, 	cflt_coef_2, operate->usCoef[2],
							cflt_coef_3, operate->usCoef[3] );

//	operate->usCoef[0] = g_gfx_reg_l9a0->cflt_coef0.abwCfltCoef0;
//	operate->usCoef[1] = g_gfx_reg_l9a0->cflt_coef0.abwCfltCoef1;
//	operate->usCoef[2] = g_gfx_reg_l9a0->cflt_coef1.abwCfltCoef2;
//	operate->usCoef[3] = g_gfx_reg_l9a0->cflt_coef1.abwCfltCoef3;
	GFX_TRACE_END();
}

/** Set operation status
 *
 *	@note operation status should be read at GFX_L9_GetOperationStatus
 */
void GFX_L9_SetOperationStatus(GFX_CMD_OP_T *operate)
{
	GFX_TRACE_BEGIN();

	GFX_Wr04( gfx_op_mode,	op_mode,	operate->sPort,	
							burst_mode,	operate->bBurstModeEnable,							
							clut_up_en, operate->bUpdateCLUT,
							cflt_mode, 	operate->sFmode );

//	g_gfx_reg_l9a0_cache->op_mode.abwOpMode = operate->sPort;	// pixel format
//	g_gfx_reg_l9a0_cache->op_mode.bwEnableBusrtMode = operate->bBurstModeEnable;		// burst mode enable
//	g_gfx_reg_l9a0_cache->op_mode.bwEnableCLUTUpdate = operate->bUpdateCLUT;
//	g_gfx_reg_l9a0_cache->op_mode.bwEnChromaFilter = operate->bChromaFilterEnable;
//	g_gfx_reg_l9a0_cache->op_mode.abwChromaFilterMode = operate->sFmode;

	GFX_Wr02( cflt_coef0, 	cflt_coef_0, operate->usCoef[0],
							cflt_coef_1, operate->usCoef[1] );
	GFX_Wr02( cflt_coef1, 	cflt_coef_2, operate->usCoef[2],
							cflt_coef_3, operate->usCoef[3] );

//	g_gfx_reg_l9a0_cache->cflt_coef0.abwCfltCoef0 = operate->usCoef[0];
//	g_gfx_reg_l9a0_cache->cflt_coef0.abwCfltCoef1 = operate->usCoef[1];
//	g_gfx_reg_l9a0_cache->cflt_coef1.abwCfltCoef2 = operate->usCoef[2];
//	g_gfx_reg_l9a0_cache->cflt_coef1.abwCfltCoef3 = operate->usCoef[3];

	/* writer register ( memory cache -> register )
	 *
	 * - gfx_op_mode  
	 * - cflt_coef0
	 * - cflt_coef1
	 */
#if 0
    GFX_REG_MEMCPY( &g_gfx_reg_l9a0->op_mode, &g_gfx_reg_l9a0_cache->op_mode, 3 /* reg count = 3 */ );
#else
	GFX_WrFL(gfx_op_mode);
	GFX_WrFL(cflt_coef0);
	GFX_WrFL(cflt_coef1);
#endif

	GFX_TRACE_END();
}

/** get inpurt port configuration
 *
 *
 */
void GFX_L9_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port)
{
	GFX_TRACE_BEGIN();

	switch(iPort)
	{
		case ePort0:
		{
			GFX_RdFL( r0_base_addr );
			GFX_RdFL( r0_stride );
			GFX_RdFL( r0_pformat );
			GFX_RdFL( r0_galpha );
			GFX_RdFL( r0_clut_ctrl );
			GFX_RdFL( r0_clut_data );
			GFX_RdFL( r0_ctrl );
			GFX_RdFL( r0_ckey_key0 );
			GFX_RdFL( r0_ckey_key1 );
			GFX_RdFL( r0_ckey_replace_color );
			GFX_RdFL( r0_coc_ctrl );

			GFX_Rd00( r0_base_addr, port->ulAddr );
//			port->ulAddr 		= g_gfx_reg_l9a0->in0_base_addr;
			GFX_Rd01( r0_stride, 	r0_stride, 		port->usStride );
//			port->usStride 		= g_gfx_reg_l9a0->in0_stride.abwStride;
			GFX_Rd02( r0_pformat,	pixel_format,	port->sFmt,
									endian_mode,	port->sEndian );
//			port->sEndian 		= g_gfx_reg_l9a0->in0_format.bwEndian;
//			port->sFmt 			= g_gfx_reg_l9a0->in0_format.abwPft;
			GFX_Rd00( r0_galpha,	port->uiGlobalAlpha );
//			port->uiGlobalAlphaa = g_gfx_reg_l9a0->in0_galpha.abwAlpha;

			GFX_Rd03( r0_clut_ctrl,	clut0_addr,		port->usAddrCLUT,
									clut0_rw,		port->bRW_CLUT,	
									clut0_wai,		port->bAuto_Inc_CLUT );
//			port->usAddrCLUT 	= g_gfx_reg_l9a0->in0_clut_ctrl.abwAddr;
//			port->bRW_CLUT 		= g_gfx_reg_l9a0->in0_clut_ctrl.bwRW;
//			port->bAuto_Inc_CLUT= g_gfx_reg_l9a0->in0_clut_ctrl.bwAutoUp;

			GFX_Rd00( r0_clut_data,	port->ulDataCLUT );
//			port->ulDataCLUT 	= g_gfx_reg_l9a0->in0_data_clut;

			GFX_Rd06( r0_ctrl,		color_key_en,	port->bColorKeyEnable,
									bitmask_en,		port->bBitMaskEnable,
									coc_en,			port->bCOCEnable,
									csc_en,			port->bCSCEnable,
									color_key_mode,	port->bColorKeyMode,
									csc_coef_sel,	port->sCSCSel );
//			port->bColorKeyEnable = g_gfx_reg_l9a0->in0_ctrl.bwCKeyEnable;
//			port->bBitMaskEnable = g_gfx_reg_l9a0->in0_ctrl.bwBitMaskEnable;
//			port->bCOCEnable = g_gfx_reg_l9a0->in0_ctrl.bwCOCEnable;
//			port->bCSCEnable = g_gfx_reg_l9a0->in0_ctrl.bwCSCEnable;
//			port->bColorKeyMode = g_gfx_reg_l9a0->in0_ctrl.bwCKeyMode;
//			port->sCSCSel = g_gfx_reg_l9a0->in0_ctrl.abwCSCCoefSel;

			GFX_Rd00( r0_ckey_key0,			port->ulKeyLow );
			GFX_Rd00( r0_ckey_key1, 		port->ulKeyHigh );
			GFX_Rd00( r0_ckey_replace_color, port->ulReplaceColor );
			GFX_Rd00( r0_bitmask, 			 port->ulBitMask );
//			port->ulKeyLow = g_gfx_reg_l9a0->in0_uiCKeyLowThr;
//			port->ulKeyHigh = g_gfx_reg_l9a0->in0_uiCKeyHighThr;
//			port->ulReplaceColor = g_gfx_reg_l9a0->in0_uiReplaceColor;
//			port->ulBitMask = g_gfx_reg_l9a0->in0_uiBitMask;
			GFX_Rd00( r0_coc_ctrl, 	port->ulCOCCtrl );
//			port->ulCOCCtrl = g_gfx_reg_l9a0->in0_coc_ctrl;
		}
		break;

		case ePort1:
		{
			GFX_RdFL( r1_base_addr );
			GFX_RdFL( r1_stride );
			GFX_RdFL( r1_pformat );
			GFX_RdFL( r1_galpha );
			GFX_RdFL( r1_clut_ctrl );
			GFX_RdFL( r1_clut_data );
			GFX_RdFL( r1_ctrl );
			GFX_RdFL( r1_ckey_key0 );
			GFX_RdFL( r1_ckey_key1 );
			GFX_RdFL( r1_ckey_replace_color );
			GFX_RdFL( r1_coc_ctrl );

			GFX_Rd00( r1_base_addr, port->ulAddr );
//			port->ulAddr 		= g_gfx_reg_l9a0->in1_base_addr;
			GFX_Rd01( r1_stride, 	r1_stride, 		port->usStride );
//			port->usStride 		= g_gfx_reg_l9a0->in1_stride.abwStride;
			GFX_Rd02( r1_pformat,	pixel_format,	port->sFmt,
									endian_mode,	port->sEndian );
//			port->sEndian 		= g_gfx_reg_l9a0->in1_format.bwEndian;
//			port->sFmt 			= g_gfx_reg_l9a0->in1_format.abwPft;
			GFX_Rd00( r1_galpha,	port->uiGlobalAlpha );
//			port->uiGlobalAlphaa = g_gfx_reg_l9a0->in1_galpha.abwAlpha;

			GFX_Rd03( r1_clut_ctrl,	clut1_addr,		port->usAddrCLUT,
									clut1_rw,		port->bRW_CLUT,	
									clut1_wai,		port->bAuto_Inc_CLUT );
//			port->usAddrCLUT 	= g_gfx_reg_l9a0->in1_clut_ctrl.abwAddr;
//			port->bRW_CLUT 		= g_gfx_reg_l9a0->in1_clut_ctrl.bwRW;
//			port->bAuto_Inc_CLUT= g_gfx_reg_l9a0->in1_clut_ctrl.bwAutoUp;

			GFX_Rd00( r1_clut_data,	port->ulDataCLUT );
//			port->ulDataCLUT 	= g_gfx_reg_l9a0->in1_data_clut;

			GFX_Rd06( r1_ctrl,		color_key_en,	port->bColorKeyEnable,
									bitmask_en,		port->bBitMaskEnable,
									coc_en,			port->bCOCEnable,
									csc_en,			port->bCSCEnable,
									color_key_mode,	port->bColorKeyMode,
									csc_coef_sel,	port->sCSCSel );
//			port->bColorKeyEnable = g_gfx_reg_l9a0->in1_ctrl.bwCKeyEnable;
//			port->bBitMaskEnable = g_gfx_reg_l9a0->in1_ctrl.bwBitMaskEnable;
//			port->bCOCEnable = g_gfx_reg_l9a0->in1_ctrl.bwCOCEnable;
//			port->bCSCEnable = g_gfx_reg_l9a0->in1_ctrl.bwCSCEnable;
//			port->bColorKeyMode = g_gfx_reg_l9a0->in1_ctrl.bwCKeyMode;
//			port->sCSCSel = g_gfx_reg_l9a0->in1_ctrl.abwCSCCoefSel;

			GFX_Rd00( r1_ckey_key0,	port->ulKeyLow );
			GFX_Rd00( r1_ckey_key1, port->ulKeyHigh );
			GFX_Rd00( r1_ckey_replace_color, port->ulReplaceColor );
			GFX_Rd00( r1_bitmask, 			 port->ulBitMask );
//			port->ulKeyLow = g_gfx_reg_l9a0->in1_uiCKeyLowThr;
//			port->ulKeyHigh = g_gfx_reg_l9a0->in1_uiCKeyHighThr;
//			port->ulReplaceColor = g_gfx_reg_l9a0->in1_uiReplaceColor;
//			port->ulBitMask = g_gfx_reg_l9a0->in1_uiBitMask;
			GFX_Rd00( r1_coc_ctrl, 	port->ulCOCCtrl );
//			port->ulCOCCtrl = g_gfx_reg_l9a0->in1_coc_ctrl;
		}
		break;

		case ePort2:
		{
			GFX_RdFL( r2_base_addr );
			GFX_RdFL( r2_stride );
			GFX_RdFL( r2_pformat );
			GFX_RdFL( r2_galpha );

			GFX_Rd00( r2_base_addr, port->ulAddr );
//			port->ulAddr 		= g_gfx_reg_l9a0->in2_base_addr;
			GFX_Rd01( r2_stride, 	r2_stride, 		port->usStride );
//			port->usStride 		= g_gfx_reg_l9a0->in2_stride.abwStride;
			GFX_Rd02( r2_pformat,	pixel_format,	port->sFmt,
									endian_mode,	port->sEndian );
//			port->sEndian 		= g_gfx_reg_l9a0->in2_format.bwEndian;
//			port->sFmt 			= g_gfx_reg_l9a0->in2_format.abwPft;
			GFX_Rd00( r2_galpha,	port->uiGlobalAlpha );
//			port->uiGlobalAlphaa = g_gfx_reg_l9a0->in2_galpha.abwAlpha;
		}
		break;

		default:
		{
			GFX_WARN(" Invalid port %d\n", port->sPort );
		}
		break;
	}

	GFX_TRACE_END();
}

void GFX_L9_SetInputConfigure(GFX_PORT_CONFIGURE_T *port)
{
	GFX_TRACE_BEGIN();

	switch(port->sPort)
	{
		case ePort0:
		{
			GFX_Wr00( r0_base_addr, port->ulAddr );
			GFX_Wr01( r0_stride, 	r0_stride, 		port->usStride );
			GFX_Wr02( r0_pformat,	pixel_format,	port->sFmt,
									endian_mode,	port->sEndian );
			GFX_Wr00( r0_galpha,	port->uiGlobalAlpha );
			GFX_Wr03( r0_clut_ctrl,	clut0_addr,		port->usAddrCLUT,
									clut0_rw,		port->bRW_CLUT,	
									clut0_wai,		port->bAuto_Inc_CLUT );
//			GFX_Wr00( r0_clut_data,	port->ulDataCLUT );
			GFX_Wr06( r0_ctrl,		color_key_en,	port->bColorKeyEnable,
									bitmask_en,		port->bBitMaskEnable,
									coc_en,			port->bCOCEnable,
									csc_en,			port->bCSCEnable,
									color_key_mode,	port->bColorKeyMode,
									csc_coef_sel,	port->sCSCSel );
			GFX_Wr00( r0_ckey_key0,	port->ulKeyLow );
			GFX_Wr00( r0_ckey_key1, port->ulKeyHigh );
			GFX_Wr00( r0_ckey_replace_color, port->ulReplaceColor );
			GFX_Wr00( r0_bitmask, 			 port->ulBitMask );
			GFX_Wr00( r0_coc_ctrl, 	port->ulCOCCtrl );

			/* write regiseter ( memory cache -> register ) */
			GFX_WrFL( r0_base_addr );
			GFX_WrFL( r0_stride );
			GFX_WrFL( r0_pformat );
			GFX_WrFL( r0_galpha );
			GFX_WrFL( r0_clut_ctrl );
			//GFX_WrFL( r0_clut_data );	<<-- useless for setting input configure !!
			GFX_WrFL( r0_ctrl );
			GFX_WrFL( r0_ckey_key0 );
			GFX_WrFL( r0_ckey_key1 );
			GFX_WrFL( r0_ckey_replace_color );
			GFX_WrFL( r0_coc_ctrl );
		}
		break;

		case ePort1:
		{
			GFX_Wr00( r1_base_addr, port->ulAddr );
			GFX_Wr01( r1_stride, 	r1_stride, 		port->usStride );
			GFX_Wr02( r1_pformat,	pixel_format,	port->sFmt,
									endian_mode,	port->sEndian );
			GFX_Wr00( r1_galpha,	port->uiGlobalAlpha );
			GFX_Wr03( r1_clut_ctrl,	clut1_addr,		port->usAddrCLUT,
									clut1_rw,		port->bRW_CLUT,	
									clut1_wai,		port->bAuto_Inc_CLUT );
//			GFX_Wr00( r1_clut_data,	port->ulDataCLUT );
			GFX_Wr06( r1_ctrl,		color_key_en,	port->bColorKeyEnable,
									bitmask_en,		port->bBitMaskEnable,
									coc_en,			port->bCOCEnable,
									csc_en,			port->bCSCEnable,
									color_key_mode,	port->bColorKeyMode,
									csc_coef_sel,	port->sCSCSel );
			GFX_Wr00( r1_ckey_key0,	port->ulKeyLow );
			GFX_Wr00( r1_ckey_key1, port->ulKeyHigh );
			GFX_Wr00( r1_ckey_replace_color, port->ulReplaceColor );
			GFX_Wr00( r1_bitmask, 			 port->ulBitMask );
			GFX_Wr00( r1_coc_ctrl, 	port->ulCOCCtrl );

			/* write regiseter ( memory cache -> register ) */
			GFX_WrFL( r1_base_addr );
			GFX_WrFL( r1_stride );
			GFX_WrFL( r1_pformat );
			GFX_WrFL( r1_galpha );
			GFX_WrFL( r1_clut_ctrl );
			//GFX_WrFL( r1_clut_data );	<<-- useless for setting input configure !!
			GFX_WrFL( r1_ctrl );
			GFX_WrFL( r1_ckey_key0 );
			GFX_WrFL( r1_ckey_key1 );
			GFX_WrFL( r1_ckey_replace_color );
			GFX_WrFL( r1_coc_ctrl );
		}
		break;

		case ePort2:
		{
			GFX_Wr00( r2_base_addr, port->ulAddr );
			GFX_Wr01( r2_stride, 	r2_stride, 		port->usStride );
			GFX_Wr02( r2_pformat,	pixel_format,	port->sFmt,
									endian_mode,	port->sEndian );
			GFX_Wr00( r2_galpha,	port->uiGlobalAlpha );

			/* write regiseter ( memory cache -> register ) */
			GFX_WrFL( r2_base_addr );
			GFX_WrFL( r2_stride );
			GFX_WrFL( r2_pformat );
			GFX_WrFL( r2_galpha );
		}
		break;

		default:
		break;
	}
	GFX_TRACE_END();
}

/** get blending config
 *
 *	this function reads out_sel, blend_ctrl0, blend_ctrl1, blend_ctrl_const, rop_ctrl
 *
 */
void GFX_L9_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend)
{
	UINT32	color_a;
	UINT32	color_c;

	GFX_TRACE_BEGIN();

	GFX_RdFL( out_sel );
	GFX_RdFL( blend_ctrl0 );
	GFX_RdFL( blend_ctrl1 );
	GFX_RdFL( blend_ctrl_const );
	GFX_RdFL( rop_ctrl );
	
	GFX_Rd01( out_sel, 	out_sel,	blend->sOut );
//	blend->sOut 		= g_gfx_reg_l9a0->out_sel.abwOutSel;

	GFX_Rd11( blend_ctrl0,	pma0,			blend->bPMA0Enable,
							pma1,			blend->bPMA1Enable,
							xor0,			blend->bXOR0Enable,
							xor1,			blend->bXOR1Enable,		
							div_en,			blend->bDIVEnable,
							c_m0,			blend->usC_m0,
							alpha_m0,		blend->usAlpha_m0,
							comp_sel_b,		blend->sBBlend,
							comp_sel_g,		blend->sGBlend,
							comp_sel_r,		blend->sRBlend,
							comp_sel_a,		blend->sAlphaBlend );
//	blend->sAlphaBlend	= g_gfx_reg_l9a0->out_ctrl0.abwComSelAlpha	;
//	blend->sRBlend		= g_gfx_reg_l9a0->out_ctrl0.abwComSelR;
//	blend->sGBlend		= g_gfx_reg_l9a0->out_ctrl0.abwComSelG;
//	blend->sBBlend		= g_gfx_reg_l9a0->out_ctrl0.abwComSelB;
//	blend->usAlpha_m0	= g_gfx_reg_l9a0->out_ctrl0.abwAlpham0;
//	blend->usC_m0		= g_gfx_reg_l9a0->out_ctrl0.abwCm0;
//	blend->bDIVEnable	= g_gfx_reg_l9a0->out_ctrl0.bwDIVEnable;
//	blend->bXOR0Enable	= g_gfx_reg_l9a0->out_ctrl0.bwXOR0Enable;
//	blend->bXOR1Enable	= g_gfx_reg_l9a0->out_ctrl0.bwXOR1Enable;
//	blend->bPMA0Enable	= g_gfx_reg_l9a0->out_ctrl0.bwPMA0Enable;
//	blend->bPMA1Enable	= g_gfx_reg_l9a0->out_ctrl0.bwPMA1Enable;

	GFX_Rd08( blend_ctrl1,	b3_sel,		blend->usB3_B,
							a3_sel,		blend->usA3_B,
							b2_sel,		blend->usB2_G,
							a2_sel,		blend->usA2_G,
							b1_sel,		blend->usB1_R,
							a1_sel,		blend->usA1_R,
							b0_sel,		blend->usB0_Alpha,
							a0_sel,		blend->usA0_Alpha );
//	blend->usA0_Alpha	= g_gfx_reg_l9a0->out_ctrl1.abwA0Sel;
//	blend->usB0_Alpha	= g_gfx_reg_l9a0->out_ctrl1.abwB0Sel;
//	blend->usA1_R		= g_gfx_reg_l9a0->out_ctrl1.abwA1Sel;
//	blend->usB1_R		= g_gfx_reg_l9a0->out_ctrl1.abwB1Sel;
//	blend->usA2_G		= g_gfx_reg_l9a0->out_ctrl1.abwA2Sel;
//	blend->usB2_G		= g_gfx_reg_l9a0->out_ctrl1.abwB2Sel;
//	blend->usA3_B		= g_gfx_reg_l9a0->out_ctrl1.abwA3Sel;
//	blend->usB3_B		= g_gfx_reg_l9a0->out_ctrl1.abwB3Sel;

	GFX_Rd02( blend_ctrl_const, c_c,		color_c,
								alpha_c,	color_a );
	blend->ulBlendConstant	= ((color_a & 0xff)<<24)|(color_c & 0xffffff);
//	blend->ulBlendConstant	= g_gfx_reg_l9a0->out_const_ctrl.abwConstantCtrl;
	GFX_Rd01( rop_ctrl,		rop_ctrl,		blend->sRaster );
//	blend->sRaster			= g_gfx_reg_l9a0->out_rop_ctrl.abwRasterSel;

	GFX_TRACE_END();
}

/** set bleding output config 
 *
 *	@note out_sel should be read before this function at GFX_L9_GetBlendConfigure
 */
void GFX_L9_SetBlendingOut(GFX_ENUM_OUT_T type)
{
	GFX_TRACE_BEGIN();
	GFX_Wr01( out_sel, out_sel,	type );
	/* write regiseter ( memory cache -> register ) */
	GFX_WrFL( out_sel );
	GFX_TRACE_END();
}

/* set blend configure 
 * this function write out_sel, blend_ctrl0, blend_ctrl1, blend_ctrl_const, rop_ctrl registers 
 *
 * 	@note all data should be read before this function at GFX_L9_GetBlendConfigure
 */
void GFX_L9_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend)
{
	UINT32	color_a, color_c;
	GFX_TRACE_BEGIN();
	
	GFX_Wr01( out_sel, 	out_sel,	blend->sOut );
//	blend->sOut 		= g_gfx_reg_l9a0->out_sel.abwOutSel;

	GFX_Wr11( blend_ctrl0,	pma0,			blend->bPMA0Enable,
							pma1,			blend->bPMA1Enable,
							xor0,			blend->bXOR0Enable,
							xor1,			blend->bXOR1Enable,		
							div_en,			blend->bDIVEnable,
							c_m0,			blend->usC_m0,
							alpha_m0,		blend->usAlpha_m0,
							comp_sel_b,		blend->sBBlend,
							comp_sel_g,		blend->sGBlend,
							comp_sel_r,		blend->sRBlend,
							comp_sel_a,		blend->sAlphaBlend );

	GFX_Wr08( blend_ctrl1,	b3_sel,		blend->usB3_B,
							a3_sel,		blend->usA3_B,
							b2_sel,		blend->usB2_G,
							a2_sel,		blend->usA2_G,
							b1_sel,		blend->usB1_R,
							a1_sel,		blend->usA1_R,
							b0_sel,		blend->usB0_Alpha,
							a0_sel,		blend->usA0_Alpha );

	color_a = (blend->ulBlendConstant>>24) & 0xff;
	color_c = blend->ulBlendConstant & 0xffffff;
	GFX_Wr02( blend_ctrl_const, c_c,		color_c,
								alpha_c,	color_a );

	GFX_Wr01( rop_ctrl,		rop_ctrl,		blend->sRaster );

	/* write regiseter ( memory cache -> register ) */
	GFX_WrFL( out_sel );
	GFX_WrFL( blend_ctrl0 );
	GFX_WrFL( blend_ctrl1 );
	GFX_WrFL( blend_ctrl_const );
	GFX_WrFL( rop_ctrl );

	GFX_TRACE_END();
}

void GFX_L9_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port)
{
	GFX_TRACE_BEGIN();

	GFX_RdFL( wr_base_addr );
	GFX_RdFL( wr_stride );
	GFX_RdFL( wr_pformat );
	GFX_RdFL( wr_size );
	GFX_RdFL( wr_galpha );
//	GFX_RdFL( wr_clut_ctrl );
//	GFX_RdFL( wr_clut_data );
	GFX_RdFL( wr_ctrl );
	GFX_RdFL( wr_coc_ctrl );
	
	GFX_RdFL( wr_csc_coef_00 );
	GFX_RdFL( wr_csc_coef_01 );
	GFX_RdFL( wr_csc_coef_02 );
	GFX_RdFL( wr_csc_coef_03 );
	GFX_RdFL( wr_csc_coef_04 );
	GFX_RdFL( wr_csc_coef_05 );
	GFX_RdFL( wr_csc_coef_06 );
	GFX_RdFL( wr_csc_coef_07 );

	GFX_Rd00( wr_base_addr, port->ulAddr );
//	port->ulAddr = g_gfx_reg_l9a0->out_base_addr;		// out base address

	GFX_Rd01( wr_stride, 	wr_stride, 		port->usStride );
//	port->usStride = g_gfx_reg_l9a0->out_stride.abwStride;	// out stride. bytes per line

	GFX_Rd02( wr_pformat,	pixel_format,	port->sFmt,
							endian_mode,	port->sEndian );
//	port->sEndian = g_gfx_reg_l9a0->out_format.bwEndian;	// endian
//	port->sFmt = g_gfx_reg_l9a0->out_format.abwPft;	// pixel format

	GFX_Rd00( wr_galpha,	port->ulGAlpha );
//	port->uiGlobalAlpha = g_gfx_reg_l9a0->out_galpha.abwAlpha;

	GFX_Rd02( wr_ctrl,		coc_en,			port->bCOCEnable,
							csc_en,			port->bCSCEnable );
//	port->bCSCEnable = g_gfx_reg_l9a0->out_ctrl.bwCSCEnable;
//	port->bCOCEnable = g_gfx_reg_l9a0->out_ctrl.bwCOCEnable;

	GFX_Rd00( wr_coc_ctrl, 	port->ulCOCCtrl );
//	port->ulCOCCtrl = g_gfx_reg_l9a0->out_coc_ctrl;

	GFX_Rd02( wr_size,		hsize,			port->usHSize,
							vsize,			port->usVSize );
//	port->usVSize = g_gfx_reg_l9a0->out_size.abwVSIZE;
//	port->usHSize = g_gfx_reg_l9a0->out_size.abwHSIZE;

	GFX_Rd00( wr_csc_coef_00, port->uiCSCCoef[0] );
	GFX_Rd00( wr_csc_coef_01, port->uiCSCCoef[1] );
	GFX_Rd00( wr_csc_coef_02, port->uiCSCCoef[2] );
	GFX_Rd00( wr_csc_coef_03, port->uiCSCCoef[3] );
	GFX_Rd00( wr_csc_coef_04, port->uiCSCCoef[4] );
	GFX_Rd00( wr_csc_coef_05, port->uiCSCCoef[5] );
	GFX_Rd00( wr_csc_coef_06, port->uiCSCCoef[6] );
	GFX_Rd00( wr_csc_coef_07, port->uiCSCCoef[7] );
//	port->uiCSCCoef[0] = g_gfx_reg_l9a0->out_coef0.abwCSCCoef;
//	port->uiCSCCoef[1] = g_gfx_reg_l9a0->out_coef1.abwCSCCoef;
//	port->uiCSCCoef[2] = g_gfx_reg_l9a0->out_coef2.abwCSCCoef;
//	port->uiCSCCoef[3] = g_gfx_reg_l9a0->out_coef3.abwCSCCoef;
//	port->uiCSCCoef[4] = g_gfx_reg_l9a0->out_coef4.abwCSCCoef;
//	port->uiCSCOffset[0] = g_gfx_reg_l9a0->out_coef5.abwCSCCoef;
//	port->uiCSCOffset[1] = g_gfx_reg_l9a0->out_coef6.abwCSCCoef;
//	port->uiCSCOffset[2] = g_gfx_reg_l9a0->out_coef7.abwCSCCoef;

	GFX_TRACE_END();
}

void GFX_L9_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port)
{
	GFX_TRACE_BEGIN();

	GFX_Wr00( wr_base_addr, port->ulAddr );
	GFX_Wr01( wr_stride, 	wr_stride, 		port->usStride );
	GFX_Wr02( wr_pformat,	pixel_format,	port->sFmt,
							endian_mode,	port->sEndian );
	GFX_Wr00( wr_galpha,	port->ulGAlpha );
	GFX_Wr02( wr_ctrl,		coc_en,			port->bCOCEnable,
							csc_en,			port->bCSCEnable );
	GFX_Wr00( wr_coc_ctrl, 	port->ulCOCCtrl );
	GFX_Wr02( wr_size,		hsize,			port->usHSize,
							vsize,			port->usVSize );
	GFX_Wr00( wr_csc_coef_00, port->uiCSCCoef[0] );
	GFX_Wr00( wr_csc_coef_01, port->uiCSCCoef[1] );
	GFX_Wr00( wr_csc_coef_02, port->uiCSCCoef[2] );
	GFX_Wr00( wr_csc_coef_03, port->uiCSCCoef[3] );
	GFX_Wr00( wr_csc_coef_04, port->uiCSCCoef[4] );
	GFX_Wr00( wr_csc_coef_05, port->uiCSCCoef[5] );
	GFX_Wr00( wr_csc_coef_06, port->uiCSCCoef[6] );
	GFX_Wr00( wr_csc_coef_07, port->uiCSCCoef[7] );

	/* write regiseter ( memory cache -> register ) */
	GFX_WrFL( wr_base_addr );
	GFX_WrFL( wr_stride );
	GFX_WrFL( wr_pformat );
	GFX_WrFL( wr_size );
	GFX_WrFL( wr_galpha );
	GFX_WrFL( wr_ctrl );
	GFX_WrFL( wr_coc_ctrl );
	
	GFX_WrFL( wr_csc_coef_00 );
	GFX_WrFL( wr_csc_coef_01 );
	GFX_WrFL( wr_csc_coef_02 );
	GFX_WrFL( wr_csc_coef_03 );
	GFX_WrFL( wr_csc_coef_04 );
	GFX_WrFL( wr_csc_coef_05 );
	GFX_WrFL( wr_csc_coef_06 );
	GFX_WrFL( wr_csc_coef_07 );

	GFX_TRACE_END();
}

void GFX_L9_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler)
{
	switch( scaler->cmd )
	{
		case GFX_SCALER_CMD_SOFT_RESET:
		{
			GFX_ERROR("not supported\n");
		}
		break;
		
		case GFX_SCALER_CMD_START:
		{
			GFX_RdFL( scaler_bypass );
			GFX_RdFL( scaler_in_pic_width );	
			GFX_RdFL( scaler_in_pic_height );	
			GFX_RdFL( scaler_out_pic_width );	
			GFX_RdFL( scaler_out_pic_height );	

			GFX_RdFL( scaler_bilinear );

			GFX_RdFL( scaler_phase_offset );
			GFX_RdFL( scaler_boundary_mode );
			GFX_RdFL( scaler_sampling_mode );
			GFX_RdFL( scaler_numerator );
			GFX_RdFL( scaler_denominator );
			GFX_RdFL( scaler_hcoef_index );
			GFX_RdFL( scaler_vcoef_index );

			GFX_Wr01( scaler_bypass, scaler_bypass, 0 );
			GFX_Wr01( scaler_in_pic_width,  scaler_in_pic_width, 	scaler->in_dim.w);
			GFX_Wr01( scaler_in_pic_height, scaler_in_pic_height,	scaler->in_dim.h);
			GFX_Wr01( scaler_out_pic_width, scaler_out_pic_width, 	scaler->out_dim.w);
			GFX_Wr01( scaler_out_pic_height,scaler_out_pic_height,	scaler->out_dim.h);

			GFX_Wr01( scaler_phase_offset, 	scaler_phase_offset, 	0x0 );
			GFX_Wr01( scaler_boundary_mode, scaler_boundary_mode, 	0x1 );
			GFX_Wr01( scaler_sampling_mode, scaler_sampling_mode, 	0x0 );
			GFX_Wr01( scaler_numerator,   	scaler_numerator, 		0x0 );
			GFX_Wr01( scaler_denominator, 	scaler_denominator, 	0x0 );
			GFX_Wr01( scaler_hcoef_index, 	scaler_hcoef_index, 	0x0 );
			GFX_Wr01( scaler_vcoef_index, 	scaler_vcoef_index, 	0x0 );

			GFX_Wr01( scaler_bilinear, 		scaler_bilinear, 		0x1 );	// fixed to bilinear. custom filter not tested

			/* disable scaler bypass */
			GFX_WrFL( scaler_bypass );

			GFX_WrFL( scaler_in_pic_width );
			GFX_WrFL( scaler_out_pic_width );
			GFX_WrFL( scaler_in_pic_height );
			GFX_WrFL( scaler_out_pic_height );

			/* reinit scaler line every scaler operation */
			g_gfx_reg_l9a0->scaler_line_init.scaler_line_init = 0x1;
			g_gfx_reg_l9a0->scaler_line_init.scaler_line_init = 0x0;

//			GFX_WrFL( scaler_phase_offset );
			GFX_WrFL( scaler_boundary_mode );
//			GFX_WrFL( scaler_sampling_mode );
//			GFX_WrFL( scaler_numerator );
//			GFX_WrFL( scaler_denominator );
			GFX_WrFL( scaler_bilinear );
//			GFX_WrFL( scaler_hcoef_index );
//			GFX_WrFL( scaler_vcoef_index );

			/* make START command for the scaler */
			g_gfx_reg_l9a0->scaler_frame_start.scaler_frame_start = 0x1;
		}
		break;

		case GFX_SCALER_CMD_BYPASS:
		default:
		{
		    g_gfx_reg_l9a0->scaler_bypass.scaler_bypass = 1;
		}
		break;
	}
}

void GFX_L9_SetInterruptMode(UINT32 uiMode)
{
	/* do nothing */
}

/* what is it ? */
void GFX_L9_SetAckMode(UINT32 *mode)
{
	GFX_TRACE_BEGIN();
	g_ui_ack_mode_l9a0 = *mode;
	g_ui_ack_mode_l9a0 = 1;
	GFX_TRACE_END();
}

/* what is it ? */
void GFX_L9_GetAckMode(UINT32 *mode)
{
	*mode = g_ui_ack_mode_l9a0;
}

int GFX_L9_SetCLUT(int port, int size , UINT32 *data)
{
	int i , ret = 0;

	GFX_TRACE_BEGIN();

    for ( i=0; i<100; i++ )
    {
        if( GFX_L9_IsGfxIdle() ) break;
        GFX_ERROR("GFX BUSY...\n"); OS_MsecSleep(1);
    }

	switch(port)
	{
        case 0:
        {
            g_gfx_reg_l9a0->r0_clut_ctrl.clut0_addr	= 0;
            g_gfx_reg_l9a0->r0_clut_ctrl.clut0_rw	= 0;
#ifdef GFX_PALETTE_AUTO_INC
            g_gfx_reg_l9a0->r0_clut_ctrl.clut0_wai	= 1;
#else
            g_gfx_reg_l9a0->r0_clut_ctrl.clut0_wai	= 0;
#endif
            for(i=0 ; i<size ; i++)
            {
#ifdef GFX_PALETTE_AUTO_INC

#else
                g_gfx_reg_l9a0->r0_clut_ctrl.clut0_addr = i;
#endif
                g_gfx_reg_l9a0->r0_clut_data			= *data++;
            }
        }
        break;

        case 1:
        {
            g_gfx_reg_l9a0->r1_clut_ctrl.clut1_addr	= 0;
            g_gfx_reg_l9a0->r1_clut_ctrl.clut1_rw	= 0;
#ifdef GFX_PALETTE_AUTO_INC
            g_gfx_reg_l9a0->r1_clut_ctrl.clut1_wai	= 1;
#else
            g_gfx_reg_l9a0->r1_clut_ctrl.clut1_wai	= 0;
#endif
            for(i=0 ; i<size ; i++)
            {
#ifdef GFX_PALETTE_AUTO_INC

#else
                g_gfx_reg_l9a0->r1_clut_ctrl.clut1_addr = i;
#endif
                g_gfx_reg_l9a0->r1_clut_data			= *data++;
			}
        }
        break;

		default:
		{
			GFX_WARN("invalid port: %d\n", port );
		}
		break;
	}

	udelay(10); /* wait for gfx sync */

	GFX_TRACE_END();
	return ret;
}

/**
 *
 * command delay register setting function
 *
 * @param	delay count
 * @return	void
 *
 */
void GFX_L9_SetCommandDelayReg(UINT16 delay)
{
	GFX_TRACE_BEGIN();
	g_gfx_reg_l9a0->gfx_cmd_dly.gfx_cmd_dly = delay;
	GFX_TRACE_END();

}
/**
 *
 * command delay register getting function
 *
 * @param	void
 * @return	delay count
 *
 * @ingroup osd_ddi_func
*/
UINT16 GFX_L9_GetCommandDelayReg(void)
{
	UINT16	val;
	GFX_TRACE_BEGIN();
	val = g_gfx_reg_l9a0->gfx_cmd_dly.gfx_cmd_dly;
	GFX_TRACE_END();
	return val;
}

/** register setting function
 *
 * @param	variable, address
 * @return	void
 *
 * @ingroup osd_ddi_func
*/
void GFX_L9_SetRegister(UINT32 addr, UINT32 val)
{
	/* do nothing */
}

UINT32 GFX_L9_GetRegister(UINT32 addr)
{
	/* do nothing */ return 0;
}

/** dump GFX register value for debug.
 *  this function is used for debugging the crtical issues or proc 
 */
void GFX_L9_DumpRegister(void)
{
    int i;
    UINT32* reg_ptr = (UINT32*)g_gfx_reg_l9a0;

	printk("L9_GFX_REG\n");
    for ( i = 0; i < gpGfxRegCfg->reg_size; i+=4 )
    {
        printk("0x%08x [0x%04x] 0x%08x\n", (gpGfxRegCfg->reg_base_addr+i), i, *reg_ptr++ );
    }
}

int GFX_L9_RunSuspend(void)
{
#ifdef KDRV_CONFIG_PM
	return 0;
#else
	return RET_NOT_SUPPORTED;
#endif
}

int GFX_L9_RunResume(void)
{
#ifdef KDRV_CONFIG_PM
	return 0;
#else
	return RET_NOT_SUPPORTED;
#endif
}


/** @} */

