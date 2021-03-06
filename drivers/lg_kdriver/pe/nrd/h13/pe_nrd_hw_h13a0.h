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


/** @file pe_nrd_hw_h13a0.h
 *
 *  driver header for picture enhance noise reduction parameters. ( used only within kdriver )
 *	- initial settings
 *	- default settings for each format
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.05.12
 *	@see		
 */

#ifndef	_PE_NRD_HW_H13A0_H_
#define	_PE_NRD_HW_H13A0_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_reg.h"

#include "h13a0/pe_nr_l_init_h13a0.h"
#include "h13a0/pe_nr_r_init_h13a0.h"
#include "h13a0/pe_tnr_l_crg_init_ia_h13a0.h"
#include "h13a0/pe_tnr_r_crg_init_ia_h13a0.h"
#include "h13a0/pe_tnr_l_alphalut_init_ia_h13a0.h"
#include "h13a0/pe_tnr_r_alphalut_init_ia_h13a0.h"
#include "h13a0/pe_tnr_l_hd_i_default_h13a0.h"
#include "h13a0/pe_tnr_l_hd_p_default_h13a0.h"
#include "h13a0/pe_tnr_l_sd_i_default_h13a0.h"
#include "h13a0/pe_tnr_l_sd_p_default_h13a0.h"
#include "h13a0/pe_tnr_r_hd_i_default_h13a0.h"
#include "h13a0/pe_tnr_r_hd_p_default_h13a0.h"
#include "h13a0/pe_tnr_r_sd_i_default_h13a0.h"
#include "h13a0/pe_tnr_r_sd_p_default_h13a0.h"
#include "h13a0/pe_dnr_l_hd_i_default_h13a0.h"
#include "h13a0/pe_dnr_l_hd_p_default_h13a0.h"
#include "h13a0/pe_dnr_l_sd_i_default_h13a0.h"
#include "h13a0/pe_dnr_l_sd_p_default_h13a0.h"
#include "h13a0/pe_dnr_l_pc_default_h13a0.h"
#include "h13a0/pe_dnr_l_av_default_h13a0.h"
#include "h13a0/pe_dnr_l_dtv_sd_default_h13a0.h"
#include "h13a0/pe_dnr_r_hd_i_default_h13a0.h"
#include "h13a0/pe_dnr_r_hd_p_default_h13a0.h"
#include "h13a0/pe_dnr_r_sd_i_default_h13a0.h"
#include "h13a0/pe_dnr_r_sd_p_default_h13a0.h"
#include "h13a0/pe_dnr_r_pc_default_h13a0.h"
#include "h13a0/pe_dnr_r_av_default_h13a0.h"
#include "h13a0/pe_dnr_r_dtv_sd_default_h13a0.h"

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

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_HW_H13A0_H_ */
