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


/** @file pe_reg_l9.h
 *
 *  driver header for picture enhance register read, write functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_REG_L9_H_
#define	_PE_REG_L9_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_reg_def_l9.h"
#include "pe_mif_reg_l9.h"
#include "pe_cvi_reg_l9.h"
#include "pe_pe0_reg_l9.h"
#include "pe_pe1_reg_l9.h"
#include "pe_wcp_reg_l9.h"
#include "pe_ctr_reg_l9.h"
#include "pe_msc_reg_l9.h"
#include "pe_ssc_reg_l9.h"

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

/* l9b0 pe0 l */
#define PE_P0L_L9B_QWr01(_a,_f,_d)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f,_d);PE_P0L_L9B0_WrFL(_a);	}

#define PE_P0L_L9B_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f1,_d1);PE_P0L_L9B0_Wr01(_a,_f2,_d2);PE_P0L_L9B0_WrFL(_a); }

#define PE_P0L_L9B_QWr03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f1,_d1);PE_P0L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0L_L9B0_Wr01(_a,_f3,_d3);PE_P0L_L9B0_WrFL(_a); }

#define PE_P0L_L9B_QWr04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f1,_d1);PE_P0L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0L_L9B0_Wr01(_a,_f3,_d3);PE_P0L_L9B0_Wr01(_a,_f4,_d4);PE_P0L_L9B0_WrFL(_a); }

#define PE_P0L_L9B_QWr05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f1,_d1);PE_P0L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0L_L9B0_Wr01(_a,_f3,_d3);PE_P0L_L9B0_Wr01(_a,_f4,_d4);PE_P0L_L9B0_Wr01(_a,_f5,_d5);\
		PE_P0L_L9B0_WrFL(_a); }

#define PE_P0L_L9B_QWr06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f1,_d1);PE_P0L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0L_L9B0_Wr01(_a,_f3,_d3);PE_P0L_L9B0_Wr01(_a,_f4,_d4);PE_P0L_L9B0_Wr01(_a,_f5,_d5);\
		PE_P0L_L9B0_Wr01(_a,_f6,_d6);PE_P0L_L9B0_WrFL(_a); }

#define PE_P0L_L9B_QWr07(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Wr01(_a,_f1,_d1);PE_P0L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0L_L9B0_Wr01(_a,_f3,_d3);PE_P0L_L9B0_Wr01(_a,_f4,_d4);PE_P0L_L9B0_Wr01(_a,_f5,_d5);\
		PE_P0L_L9B0_Wr01(_a,_f6,_d6);PE_P0L_L9B0_Wr01(_a,_f7,_d7);PE_P0L_L9B0_WrFL(_a); }

#define PE_P0L_L9B_QRd01(_a,_f,_d)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Rd01(_a,_f,_d);	}

#define PE_P0L_L9B_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Rd01(_a,_f1,_d1);PE_P0L_L9B0_Rd01(_a,_f2,_d2);	}

#define PE_P0L_L9B_QRd03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Rd01(_a,_f1,_d1);PE_P0L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0L_L9B0_Rd01(_a,_f3,_d3); }

#define PE_P0L_L9B_QRd04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Rd01(_a,_f1,_d1);PE_P0L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0L_L9B0_Rd01(_a,_f3,_d3);PE_P0L_L9B0_Rd01(_a,_f4,_d4); }

#define PE_P0L_L9B_QRd05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Rd01(_a,_f1,_d1);PE_P0L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0L_L9B0_Rd01(_a,_f3,_d3);PE_P0L_L9B0_Rd01(_a,_f4,_d4);PE_P0L_L9B0_Rd01(_a,_f5,_d5); }

#define PE_P0L_L9B_QRd06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P0L_L9B0_RdFL(_a);PE_P0L_L9B0_Rd01(_a,_f1,_d1);PE_P0L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0L_L9B0_Rd01(_a,_f3,_d3);PE_P0L_L9B0_Rd01(_a,_f4,_d4);PE_P0L_L9B0_Rd01(_a,_f5,_d5);\
		PE_P0L_L9B0_Rd01(_a,_f6,_d6); }

/* l9b0 pe0 r */
#define PE_P0R_L9B_QWr01(_a,_f,_d)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f,_d);PE_P0R_L9B0_WrFL(_a);	}

#define PE_P0R_L9B_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f1,_d1);PE_P0R_L9B0_Wr01(_a,_f2,_d2);PE_P0R_L9B0_WrFL(_a); }

#define PE_P0R_L9B_QWr03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f1,_d1);PE_P0R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0R_L9B0_Wr01(_a,_f3,_d3);PE_P0R_L9B0_WrFL(_a); }

#define PE_P0R_L9B_QWr04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f1,_d1);PE_P0R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0R_L9B0_Wr01(_a,_f3,_d3);PE_P0R_L9B0_Wr01(_a,_f4,_d4);PE_P0R_L9B0_WrFL(_a); }

#define PE_P0R_L9B_QWr05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f1,_d1);PE_P0R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0R_L9B0_Wr01(_a,_f3,_d3);PE_P0R_L9B0_Wr01(_a,_f4,_d4);PE_P0R_L9B0_Wr01(_a,_f5,_d5);\
		PE_P0R_L9B0_WrFL(_a); }

#define PE_P0R_L9B_QWr06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f1,_d1);PE_P0R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0R_L9B0_Wr01(_a,_f3,_d3);PE_P0R_L9B0_Wr01(_a,_f4,_d4);PE_P0R_L9B0_Wr01(_a,_f5,_d5);\
		PE_P0R_L9B0_Wr01(_a,_f6,_d6);PE_P0R_L9B0_WrFL(_a); }

#define PE_P0R_L9B_QWr07(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Wr01(_a,_f1,_d1);PE_P0R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P0R_L9B0_Wr01(_a,_f3,_d3);PE_P0R_L9B0_Wr01(_a,_f4,_d4);PE_P0R_L9B0_Wr01(_a,_f5,_d5);\
		PE_P0R_L9B0_Wr01(_a,_f6,_d6);PE_P0R_L9B0_Wr01(_a,_f7,_d7);PE_P0R_L9B0_WrFL(_a); }

#define PE_P0R_L9B_QRd01(_a,_f,_d)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Rd01(_a,_f,_d);	}

#define PE_P0R_L9B_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Rd01(_a,_f1,_d1);PE_P0R_L9B0_Rd01(_a,_f2,_d2);	}

#define PE_P0R_L9B_QRd03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Rd01(_a,_f1,_d1);PE_P0R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0R_L9B0_Rd01(_a,_f3,_d3); }

#define PE_P0R_L9B_QRd04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Rd01(_a,_f1,_d1);PE_P0R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0R_L9B0_Rd01(_a,_f3,_d3);PE_P0R_L9B0_Rd01(_a,_f4,_d4); }

#define PE_P0R_L9B_QRd05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Rd01(_a,_f1,_d1);PE_P0R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0R_L9B0_Rd01(_a,_f3,_d3);PE_P0R_L9B0_Rd01(_a,_f4,_d4);PE_P0R_L9B0_Rd01(_a,_f5,_d5); }

#define PE_P0R_L9B_QRd06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P0R_L9B0_RdFL(_a);PE_P0R_L9B0_Rd01(_a,_f1,_d1);PE_P0R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P0R_L9B0_Rd01(_a,_f3,_d3);PE_P0R_L9B0_Rd01(_a,_f4,_d4);PE_P0R_L9B0_Rd01(_a,_f5,_d5);\
		PE_P0R_L9B0_Rd01(_a,_f6,_d6); }

/* l9b0 pe1 l */
#define PE_P1L_L9B_QWr01(_a,_f,_d)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f,_d);PE_P1L_L9B0_WrFL(_a);	}

#define PE_P1L_L9B_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f1,_d1);PE_P1L_L9B0_Wr01(_a,_f2,_d2);PE_P1L_L9B0_WrFL(_a); }

#define PE_P1L_L9B_QWr03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f1,_d1);PE_P1L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1L_L9B0_Wr01(_a,_f3,_d3);PE_P1L_L9B0_WrFL(_a); }

#define PE_P1L_L9B_QWr04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f1,_d1);PE_P1L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1L_L9B0_Wr01(_a,_f3,_d3);PE_P1L_L9B0_Wr01(_a,_f4,_d4);PE_P1L_L9B0_WrFL(_a); }

#define PE_P1L_L9B_QWr05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f1,_d1);PE_P1L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1L_L9B0_Wr01(_a,_f3,_d3);PE_P1L_L9B0_Wr01(_a,_f4,_d4);PE_P1L_L9B0_Wr01(_a,_f5,_d5);\
		PE_P1L_L9B0_WrFL(_a); }

#define PE_P1L_L9B_QWr06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f1,_d1);PE_P1L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1L_L9B0_Wr01(_a,_f3,_d3);PE_P1L_L9B0_Wr01(_a,_f4,_d4);PE_P1L_L9B0_Wr01(_a,_f5,_d5);\
		PE_P1L_L9B0_Wr01(_a,_f6,_d6);PE_P1L_L9B0_WrFL(_a); }

#define PE_P1L_L9B_QWr07(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Wr01(_a,_f1,_d1);PE_P1L_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1L_L9B0_Wr01(_a,_f3,_d3);PE_P1L_L9B0_Wr01(_a,_f4,_d4);PE_P1L_L9B0_Wr01(_a,_f5,_d5);\
		PE_P1L_L9B0_Wr01(_a,_f6,_d6);PE_P1L_L9B0_Wr01(_a,_f7,_d7);PE_P1L_L9B0_WrFL(_a); }

#define PE_P1L_L9B_QRd01(_a,_f,_d)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Rd01(_a,_f,_d);	}

#define PE_P1L_L9B_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Rd01(_a,_f1,_d1);PE_P1L_L9B0_Rd01(_a,_f2,_d2);	}

#define PE_P1L_L9B_QRd03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Rd01(_a,_f1,_d1);PE_P1L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1L_L9B0_Rd01(_a,_f3,_d3); }

#define PE_P1L_L9B_QRd04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Rd01(_a,_f1,_d1);PE_P1L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1L_L9B0_Rd01(_a,_f3,_d3);PE_P1L_L9B0_Rd01(_a,_f4,_d4); }

#define PE_P1L_L9B_QRd05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Rd01(_a,_f1,_d1);PE_P1L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1L_L9B0_Rd01(_a,_f3,_d3);PE_P1L_L9B0_Rd01(_a,_f4,_d4);PE_P1L_L9B0_Rd01(_a,_f5,_d5); }

#define PE_P1L_L9B_QRd06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P1L_L9B0_RdFL(_a);PE_P1L_L9B0_Rd01(_a,_f1,_d1);PE_P1L_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1L_L9B0_Rd01(_a,_f3,_d3);PE_P1L_L9B0_Rd01(_a,_f4,_d4);PE_P1L_L9B0_Rd01(_a,_f5,_d5);\
		PE_P1L_L9B0_Rd01(_a,_f6,_d6); }

/* l9b0 pe1 r */
#define PE_P1R_L9B_QWr01(_a,_f,_d)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f,_d);PE_P1R_L9B0_WrFL(_a);	}

#define PE_P1R_L9B_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f1,_d1);PE_P1R_L9B0_Wr01(_a,_f2,_d2);PE_P1R_L9B0_WrFL(_a); }

#define PE_P1R_L9B_QWr03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f1,_d1);PE_P1R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1R_L9B0_Wr01(_a,_f3,_d3);PE_P1R_L9B0_WrFL(_a); }

#define PE_P1R_L9B_QWr04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f1,_d1);PE_P1R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1R_L9B0_Wr01(_a,_f3,_d3);PE_P1R_L9B0_Wr01(_a,_f4,_d4);PE_P1R_L9B0_WrFL(_a); }

#define PE_P1R_L9B_QWr05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f1,_d1);PE_P1R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1R_L9B0_Wr01(_a,_f3,_d3);PE_P1R_L9B0_Wr01(_a,_f4,_d4);PE_P1R_L9B0_Wr01(_a,_f5,_d5);\
		PE_P1R_L9B0_WrFL(_a); }

#define PE_P1R_L9B_QWr06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f1,_d1);PE_P1R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1R_L9B0_Wr01(_a,_f3,_d3);PE_P1R_L9B0_Wr01(_a,_f4,_d4);PE_P1R_L9B0_Wr01(_a,_f5,_d5);\
		PE_P1R_L9B0_Wr01(_a,_f6,_d6);PE_P1R_L9B0_WrFL(_a); }

#define PE_P1R_L9B_QWr07(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6,_f7,_d7)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Wr01(_a,_f1,_d1);PE_P1R_L9B0_Wr01(_a,_f2,_d2);\
		PE_P1R_L9B0_Wr01(_a,_f3,_d3);PE_P1R_L9B0_Wr01(_a,_f4,_d4);PE_P1R_L9B0_Wr01(_a,_f5,_d5);\
		PE_P1R_L9B0_Wr01(_a,_f6,_d6);PE_P1R_L9B0_Wr01(_a,_f7,_d7);PE_P1R_L9B0_WrFL(_a); }

#define PE_P1R_L9B_QRd01(_a,_f,_d)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Rd01(_a,_f,_d);	}

#define PE_P1R_L9B_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Rd01(_a,_f1,_d1);PE_P1R_L9B0_Rd01(_a,_f2,_d2);	}

#define PE_P1R_L9B_QRd03(_a,_f1,_d1,_f2,_d2,_f3,_d3)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Rd01(_a,_f1,_d1);PE_P1R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1R_L9B0_Rd01(_a,_f3,_d3); }

#define PE_P1R_L9B_QRd04(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Rd01(_a,_f1,_d1);PE_P1R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1R_L9B0_Rd01(_a,_f3,_d3);PE_P1R_L9B0_Rd01(_a,_f4,_d4); }

#define PE_P1R_L9B_QRd05(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Rd01(_a,_f1,_d1);PE_P1R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1R_L9B0_Rd01(_a,_f3,_d3);PE_P1R_L9B0_Rd01(_a,_f4,_d4);PE_P1R_L9B0_Rd01(_a,_f5,_d5); }

#define PE_P1R_L9B_QRd06(_a,_f1,_d1,_f2,_d2,_f3,_d3,_f4,_d4,_f5,_d5,_f6,_d6)	\
	{	PE_P1R_L9B0_RdFL(_a);PE_P1R_L9B0_Rd01(_a,_f1,_d1);PE_P1R_L9B0_Rd01(_a,_f2,_d2);\
		PE_P1R_L9B0_Rd01(_a,_f3,_d3);PE_P1R_L9B0_Rd01(_a,_f4,_d4);PE_P1R_L9B0_Rd01(_a,_f5,_d5);\
		PE_P1R_L9B0_Rd01(_a,_f6,_d6); }

/* l9a0 pe0 l */
#define PE_P0L_L9A_QWr01(_a,_f,_d)	\
	{	PE_P0L_L9_RdFL(_a);PE_P0L_L9_Wr01(_a,_f,_d);PE_P0L_L9_WrFL(_a);	}

#define PE_P0L_L9A_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0L_L9_RdFL(_a);PE_P0L_L9_Wr01(_a,_f1,_d1);PE_P0L_L9_Wr01(_a,_f2,_d2);PE_P0L_L9_WrFL(_a); }

#define PE_P0L_L9A_QRd01(_a,_f,_d)	\
	{	PE_P0L_L9_RdFL(_a);PE_P0L_L9_Rd01(_a,_f,_d);	}

#define PE_P0L_L9A_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0L_L9_RdFL(_a);PE_P0L_L9_Rd01(_a,_f1,_d1);PE_P0L_L9_Rd01(_a,_f2,_d2);	}

/* l9a0 pe0 r */
#define PE_P0R_L9A_QWr01(_a,_f,_d)	\
	{	PE_P0R_L9_RdFL(_a);PE_P0R_L9_Wr01(_a,_f,_d);PE_P0R_L9_WrFL(_a);	}

#define PE_P0R_L9A_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0R_L9_RdFL(_a);PE_P0R_L9_Wr01(_a,_f1,_d1);PE_P0R_L9_Wr01(_a,_f2,_d2);PE_P0R_L9_WrFL(_a); }

#define PE_P0R_L9A_QRd01(_a,_f,_d)	\
	{	PE_P0R_L9_RdFL(_a);PE_P0R_L9_Rd01(_a,_f,_d);	}

#define PE_P0R_L9A_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P0R_L9_RdFL(_a);PE_P0R_L9_Rd01(_a,_f1,_d1);PE_P0R_L9_Rd01(_a,_f2,_d2);	}

/* l9a0 pe1 l */
#define PE_P1L_L9A_QWr01(_a,_f,_d)	\
	{	PE_P1L_L9_RdFL(_a);PE_P1L_L9_Wr01(_a,_f,_d);PE_P1L_L9_WrFL(_a);	}

#define PE_P1L_L9A_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1L_L9_RdFL(_a);PE_P1L_L9_Wr01(_a,_f1,_d1);PE_P1L_L9_Wr01(_a,_f2,_d2);PE_P1L_L9_WrFL(_a); }

#define PE_P1L_L9A_QRd01(_a,_f,_d)	\
	{	PE_P1L_L9_RdFL(_a);PE_P1L_L9_Rd01(_a,_f,_d);	}

#define PE_P1L_L9A_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1L_L9_RdFL(_a);PE_P1L_L9_Rd01(_a,_f1,_d1);PE_P1L_L9_Rd01(_a,_f2,_d2);	}

/* l9a0 pe1 r */
#define PE_P1R_L9A_QWr01(_a,_f,_d)	\
	{	PE_P1R_L9_RdFL(_a);PE_P1R_L9_Wr01(_a,_f,_d);PE_P1R_L9_WrFL(_a);	}

#define PE_P1R_L9A_QWr02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1R_L9_RdFL(_a);PE_P1R_L9_Wr01(_a,_f1,_d1);PE_P1R_L9_Wr01(_a,_f2,_d2);PE_P1R_L9_WrFL(_a); }

#define PE_P1R_L9A_QRd01(_a,_f,_d)	\
	{	PE_P1R_L9_RdFL(_a);PE_P1R_L9_Rd01(_a,_f,_d);	}

#define PE_P1R_L9A_QRd02(_a,_f1,_d1,_f2,_d2)	\
	{	PE_P1R_L9_RdFL(_a);PE_P1R_L9_Rd01(_a,_f1,_d1);PE_P1R_L9_Rd01(_a,_f2,_d2);	}

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_REG_L9_WD(UINT32 addr, UINT32 value);
UINT32 PE_REG_L9_RD(UINT32 addr);
int PE_REG_L9_InitPhyToVirt(void);
int PE_REG_L9_FreePhyToVirt(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

extern PE_P0L_REG_L9_T gPE_P0L_L9;
extern PE_P0R_REG_L9_T gPE_P0R_L9;
extern PE_P1L_REG_L9_T gPE_P1L_L9;
extern PE_P1R_REG_L9_T gPE_P1R_L9;
extern PE_P0L_REG_L9B_T gPE_P0L_L9B;
extern PE_P0R_REG_L9B_T gPE_P0R_L9B;
extern PE_P1L_REG_L9B_T gPE_P1L_L9B;
extern PE_P1R_REG_L9B_T gPE_P1R_L9B;
extern PE_MSL_REG_L9_T gPE_MSL_L9;
extern PE_MSR_REG_L9_T gPE_MSR_L9;
extern PE_SSC_REG_L9_T gPE_SSC_L9;
extern PE_CVA_REG_L9_T gPE_CVA_L9;
extern PE_CVB_REG_L9_T gPE_CVB_L9;
extern PE_OVL_REG_L9_T gPE_OVL_L9;
extern PE_OVR_REG_L9_T gPE_OVR_L9;
extern PE_DEB_REG_L9_T gPE_DEB_L9;
extern PE_DEC_REG_L9_T gPE_DEC_L9;
extern PE_DED_REG_L9_T gPE_DED_L9;
extern PE_MIB_REG_L9_T gPE_MIB_L9;
extern PE_MID_REG_L9_T gPE_MID_L9;
extern PE_MIF_REG_L9_T gPE_MIF_L9;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_REG_L9_H_ */
