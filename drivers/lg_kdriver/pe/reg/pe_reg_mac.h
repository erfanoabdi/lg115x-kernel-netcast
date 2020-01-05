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


/** @file pe_reg_mac.h
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.16
 * note		  Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */
#ifndef  _PE_REG_MAC_H_
#define  _PE_REG_MAC_H_
/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define PE_REG_PHYS_COPY(_dst, _src, _r)				((_dst->_r)=(_src->_r))
#define PE_REG_SHDW_READ(_shdw, _r)						(*((UINT32*)(&(_shdw->_r))))
#define PE_REG_SHDW_WfCM(_shdw, _r, _f, _c, _m)			((_shdw->_r._f)=(_c)?((_m)|_shdw->_r._f):(~(_m)&_shdw->_r._f))
#define PE_REG_SHDW_WfCV(_shdw, _r, _f, _c, _v1, _v2)	((_shdw->_r._f)=(_c)?(_v1):(_v2))

#define PE_REG_PHYS_VER_RdFL(_reg, _ver, _r)						PE_REG_PHYS_COPY(_reg.shdw._ver, _reg.phys._ver, _r)
#define PE_REG_PHYS_VER_WrFL(_reg, _ver, _r)						PE_REG_PHYS_COPY(_reg.phys._ver, _reg.shdw._ver, _r)
#define PE_REG_SHDW_VER_Rd32(_reg, _ver, _r)						PE_REG_SHDW_READ(_reg.shdw._ver, _r)
#define PE_REG_SHDW_VER_Wr32(_reg, _ver, _r, _v)					PE_REG_SHDW_READ(_reg.shdw._ver, _r) = ((UINT32)(_v))
#define PE_REG_SHDW_VER_WfCM(_reg, _ver, _r, _f, _c, _m)			PE_REG_SHDW_WfCM(_reg.shdw._ver, _r, _f, _c, _m)
#define PE_REG_SHDW_VER_WfCV(_reg, _ver, _r, _f, _c, _v1, _v2)		PE_REG_SHDW_WfCV(_reg.shdw._ver, _r, _f, _c, _v1, _v2)

#define PE_REG_SHDW_Rd01(_r, _f01, _v01)																								\
do {																																\
	(_v01) = (_r._f01);																												\
} while (0)

#define PE_REG_SHDW_Rd02(_r, _f01, _v01, _f02, _v02)																					\
do {																																\
	(_v01) = (_r._f01);																												\
	(_v02) = (_r._f02);																												\
} while (0)

#define PE_REG_SHDW_Rd03(_r, _f01, _v01, _f02, _v02, _f03, _v03)																		\
do {																																\
	(_v01) = (_r._f01);																												\
	(_v02) = (_r._f02);																												\
	(_v03) = (_r._f03);																												\
} while (0)

#define PE_REG_SHDW_Rd04(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)															\
do {																																\
	(_v01) = (_r._f01);																												\
	(_v02) = (_r._f02);																												\
	(_v03) = (_r._f03);																												\
	(_v04) = (_r._f04);																												\
} while (0)

#define PE_REG_SHDW_Rd05(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,															\
		_f05, _v05)																													\
do {																																\
	(_v01) = (_r._f01);																												\
	(_v02) = (_r._f02);																												\
	(_v03) = (_r._f03);																												\
	(_v04) = (_r._f04);																												\
	(_v05) = (_r._f05);																												\
} while (0)

#define PE_REG_SHDW_Rd06(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,															\
		_f05, _v05, _f06, _v06)																										\
do {																																\
	(_v01) = (_r._f01);																												\
	(_v02) = (_r._f02);																												\
	(_v03) = (_r._f03);																												\
	(_v04) = (_r._f04);																												\
	(_v05) = (_r._f05);																												\
	(_v06) = (_r._f06);																												\
} while (0)

#define PE_REG_SHDW_Rd07(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,															\
		_f05, _v05, _f06, _v06, _f07, _v07)																							\
do {																																\
	(_v01) = (_r._f01);																												\
	(_v02) = (_r._f02);																												\
	(_v03) = (_r._f03);																												\
	(_v04) = (_r._f04);																												\
	(_v05) = (_r._f05);																												\
	(_v06) = (_r._f06);																												\
	(_v07) = (_r._f07);																												\
} while (0)

#define PE_REG_SHDW_Wr01(_r, _f01, _v01)																								\
do {																																\
	(_r._f01) = (_v01);																												\
} while (0)

#define PE_REG_SHDW_Wr02(_r, _f01, _v01, _f02, _v02)																					\
do {																																\
	(_r._f01) = (_v01);																												\
	(_r._f02) = (_v02);																												\
} while (0)

#define PE_REG_SHDW_Wr03(_r, _f01, _v01, _f02, _v02, _f03, _v03)																		\
do {																																\
	(_r._f01) = (_v01);																												\
	(_r._f02) = (_v02);																												\
	(_r._f03) = (_v03);																												\
} while (0)

#define PE_REG_SHDW_Wr04(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)															\
do {																																\
	(_r._f01) = (_v01);																												\
	(_r._f02) = (_v02);																												\
	(_r._f03) = (_v03);																												\
	(_r._f04) = (_v04);																												\
} while (0)

#define PE_REG_SHDW_Wr05(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,															\
		_f05, _v05)																													\
do {																																\
	(_r._f01) = (_v01);																												\
	(_r._f02) = (_v02);																												\
	(_r._f03) = (_v03);																												\
	(_r._f04) = (_v04);																												\
	(_r._f05) = (_v05);																												\
} while (0)

#define PE_REG_SHDW_Wr06(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,															\
		_f05, _v05, _f06, _v06)																										\
do {																																\
	(_r._f01) = (_v01);																												\
	(_r._f02) = (_v02);																												\
	(_r._f03) = (_v03);																												\
	(_r._f04) = (_v04);																												\
	(_r._f05) = (_v05);																												\
	(_r._f06) = (_v06);																												\
} while (0)

#define PE_REG_SHDW_Wr07(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,															\
		_f05, _v05, _f06, _v06, _f07, _v07)																							\
do {																																\
	(_r._f01) = (_v01);																												\
	(_r._f02) = (_v02);																												\
	(_r._f03) = (_v03);																												\
	(_r._f04) = (_v04);																												\
	(_r._f05) = (_v05);																												\
	(_r._f06) = (_v06);																												\
	(_r._f07) = (_v07);																												\
} while (0)

#define PE_FN_CHIP_RdFL(_fn, _chip, _r)																								\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_RdFL(g##_fn##_##_chip, b0, _r);																			\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_RdFL(g##_fn##_##_chip, a0, _r);																			\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_WrFL(_fn, _chip, _r)																								\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_WrFL(g##_fn##_##_chip, b0, _r);																			\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_WrFL(g##_fn##_##_chip, a0, _r);																			\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd32(_fn, _chip, _r)																								\
	(LX_CHIP_REV(_chip, A1) == lx_chip_rev())?PE_REG_SHDW_VER_Rd32(g##_fn##_##_chip, a0, _r):											\
	(LX_CHIP_REV(_chip, A0) == lx_chip_rev())?PE_REG_SHDW_VER_Rd32(g##_fn##_##_chip, a0, _r):											\
	PE_REG_SHDW_VER_Rd32(g##_fn##_##_chip, b0, _r)

#define PE_FN_CHIP_Wr32(_fn, _chip, _r, _v)																							\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr32(g##_fn##_##_chip, b0, _r, _v);																		\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr32(g##_fn##_##_chip, a0, _r, _v);																		\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_WfCM(_fn, _chip, _r, _f, _c, _m)																					\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_WfCM(g##_fn##_##_chip, b0, _r, _f, _c, _m);																\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_WfCM(g##_fn##_##_chip, a0, _r, _f, _c, _m);																\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_WfCV(_fn, _chip, _r, _f, _c, _v1, _v2)																				\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_WfCV(g##_fn##_##_chip, b0, _r, _f, _c, _v1, _v2);															\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_WfCV(g##_fn##_##_chip, a0, _r, _f, _c, _v1, _v2);															\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd01(_fn, _chip, _r, _f01, _v01)																					\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd01(g##_fn##_##_chip, b0, _r, _f01, _v01);																\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd01(g##_fn##_##_chip, a0, _r, _f01, _v01);																\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd02(_fn, _chip, _r, _f01, _v01, _f02, _v02)																		\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd02(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02);													\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd02(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02);													\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd03(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03)															\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd03(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03);										\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd03(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03);										\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd04(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)												\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd04(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04);							\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd04(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04);							\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd05(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05)																													\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd05(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05);																									\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd05(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05);																									\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd06(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06)																										\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd06(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06);																						\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd06(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06);																						\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Rd07(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06, _f07, _v07)																							\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Rd07(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06, _f07, _v07);																			\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Rd07(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06, _f07, _v07);																			\
			break;																													\
	}																																\
} while (0) 

#define PE_FN_CHIP_Wr01(_fn, _chip, _r, _f01, _v01)																					\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr01(g##_fn##_##_chip, b0, _r, _f01, _v01);																\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr01(g##_fn##_##_chip, a0, _r, _f01, _v01);																\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Wr02(_fn, _chip, _r, _f01, _v01, _f02, _v02)																		\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr02(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02);													\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr02(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02);													\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Wr03(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03)															\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr03(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03);										\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr03(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03);										\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Wr04(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)												\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr04(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04);							\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr04(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04);							\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Wr05(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05)																													\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr05(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05);																									\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr05(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05);																									\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Wr06(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06)																										\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr06(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06);																						\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr06(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06);																						\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_Wr07(_fn, _chip, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06, _f07, _v07)																							\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_SHDW_VER_Wr07(g##_fn##_##_chip, b0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06, _f07, _v07);																			\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_SHDW_VER_Wr07(g##_fn##_##_chip, a0, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,								\
					_f05, _v05, _f06, _v06, _f07, _v07);																			\
			break;																													\
	}																																\
} while (0)

#define PE_REG_SHDW_VER_Rd01(_reg, _ver, _r, _f01, _v01)																				\
	PE_REG_SHDW_Rd01(_reg.shdw._ver->_r, _f01, _v01)

#define PE_REG_SHDW_VER_Rd02(_reg, _ver, _r, _f01, _v01, _f02, _v02)																	\
	PE_REG_SHDW_Rd02(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02)

#define PE_REG_SHDW_VER_Rd03(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03)														\
	PE_REG_SHDW_Rd03(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03)

#define PE_REG_SHDW_VER_Rd04(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)											\
	PE_REG_SHDW_Rd04(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)

#define PE_REG_SHDW_VER_Rd05(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,											\
		_f05, _v05)																													\
	PE_REG_SHDW_Rd05(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05)

#define PE_REG_SHDW_VER_Rd06(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,											\
		_f05, _v05, _f06, _v06)																										\
	PE_REG_SHDW_Rd06(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06)

#define PE_REG_SHDW_VER_Rd07(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,											\
		_f05, _v05, _f06, _v06, _f07, _v07)																							\
	PE_REG_SHDW_Rd07(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06, _f07, _v07)

#define PE_REG_SHDW_VER_Wr01(_reg, _ver, _r, _f01, _v01)																				\
	PE_REG_SHDW_Wr01(_reg.shdw._ver->_r, _f01, _v01)

#define PE_REG_SHDW_VER_Wr02(_reg, _ver, _r, _f01, _v01, _f02, _v02)																	\
	PE_REG_SHDW_Wr02(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02)

#define PE_REG_SHDW_VER_Wr03(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03)														\
	PE_REG_SHDW_Wr03(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03)

#define PE_REG_SHDW_VER_Wr04(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)											\
	PE_REG_SHDW_Wr04(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)

#define PE_REG_SHDW_VER_Wr05(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,											\
		_f05, _v05)																													\
	PE_REG_SHDW_Wr05(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05)

#define PE_REG_SHDW_VER_Wr06(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,											\
		_f05, _v05, _f06, _v06)																										\
	PE_REG_SHDW_Wr06(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06)

#define PE_REG_SHDW_VER_Wr07(_reg, _ver, _r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,											\
		_f05, _v05, _f06, _v06, _f07, _v07)																							\
	PE_REG_SHDW_Wr07(_reg.shdw._ver->_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04,												\
		_f05, _v05, _f06, _v06, _f07, _v07)

#define PE_REG_PHYS_FLRd(_phys, _shdw, _r, _v)																							\
do {																																\
	PE_REG_PHYS_COPY(_shdw, _phys, _r);																								\
	(*((UINT32*)(&(_v)))) = PE_REG_SHDW_READ(_shdw, _r);																				\
} while (0)

#define PE_REG_PHYS_FLWr(_phys, _shdw, _r, _v)																							\
do {																																\
	PE_REG_SHDW_READ(_shdw, _r) = ((UINT32)(_v));																						\
	PE_REG_PHYS_COPY(_phys, _shdw, _r);																								\
} while (0)

#define PE_REG_PHYS_FLRf(_dst, _src, _r, _f01, _v01)																					\
do {																																\
	PE_REG_PHYS_COPY(_src, _dst, _r);																									\
	PE_REG_SHDW_Rd01(_src->_r, _f01, _v01);																							\
} while (0)

#define PE_REG_PHYS_FLWf(_dst, _src, _r, _f01, _v01)																					\
do {																																\
	PE_REG_PHYS_COPY(_src, _dst, _r);																									\
	PE_REG_SHDW_Wr01(_src->_r, _f01, _v01);																							\
	PE_REG_PHYS_COPY(_dst, _src, _r);																									\
} while (0)

#define PE_REG_PHYS_FLCM(_dst, _src, _r, _f, _c, _m)																					\
do {																																\
	PE_REG_PHYS_COPY(_src, _dst, _r);																									\
	PE_REG_SHDW_WfCM(_src, _r, _f, _c, _m);																							\
	PE_REG_PHYS_COPY(_dst, _src, _r);																									\
} while (0)

#define PE_REG_PHYS_FLCV(_dst, _src, _r, _f, _c, _v1, v2)																				\
do {																																\
	PE_REG_PHYS_COPY(_src, _dst, _r);																									\
	PE_REG_SHDW_WfCV(_src, _r, _c, _v1, _v2);																							\
	PE_REG_PHYS_COPY(_dst, _src, _r);																									\
} while (0)

#define PE_REG_PHYS_VER_FLRd(_reg, _ver, _r, _v)				 PE_REG_PHYS_FLRd(_reg.phys._ver, _reg.shdw._ver, _r, _v)
#define PE_REG_PHYS_VER_FLWr(_reg, _ver, _r, _v)				 PE_REG_PHYS_FLWr(_reg.phys._ver, _reg.shdw._ver, _r, _v)
#define PE_REG_PHYS_VER_FLRf(_reg, _ver, _r, _f01, _v01)		 PE_REG_PHYS_FLRf(_reg.phys._ver, _reg.shdw._ver, _r, _f01, _v01)
#define PE_REG_PHYS_VER_FLWf(_reg, _ver, _r, _f01, _v01)		 PE_REG_PHYS_FLWf(_reg.phys._ver, _reg.shdw._ver, _r, _f01, _v01)
#define PE_REG_PHYS_VER_FLCM(_reg, _ver, _r, _f, _c, _m)		 PE_REG_PHYS_FLCM(_reg.phys._ver, _reg.shdw._ver, _r, _f, _c, _m)
#define PE_REG_PHYS_VER_FLCV(_reg, _ver, _r, _f, _c, _v1, _v2)	 PE_REG_PHYS_FLCV(_reg.phys._ver, _reg.shdw._ver, _r, _f, _c, _v1, _v2)

#define PE_FN_CHIP_FLRd(_fn, _chip, _r, _v)																							\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_FLRd(g##_fn##_##_chip, b0, _r, _v);																		\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_FLRd(g##_fn##_##_chip, a0, _r, _v);																		\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_FLWr(_fn, _chip, _r, _v)																							\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_FLWr(g##_fn##_##_chip, b0, _r, _v);																		\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_FLWr(g##_fn##_##_chip, a0, _r, _v);																		\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_FLRf(_fn, _chip, _r, _f01, _v01)																					\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_FLRf(g##_fn##_##_chip, b0, _r, _f01, _v01);																\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_FLRf(g##_fn##_##_chip, a0, _r, _f01, _v01);																\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_FLWf(_fn, _chip, _r, _f01, _v01)																					\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_FLWf(g##_fn##_##_chip, b0, _r, _f01, _v01);																\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_FLWf(g##_fn##_##_chip, a0, _r, _f01, _v01);																\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_FLCM(_fn, _chip, _r, _f, _c, _m)																					\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_FLCM(g##_fn##_##_chip, b0, _r, _f, _c, _m);																\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_FLCM(g##_fn##_##_chip, a0, _r, _f, _c, _m);																\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_FLCV(_fn, _chip, _r, _f, _c, _v1, _v2)																				\
do {																																\
	switch (lx_chip_rev()) {																										\
		default :																													\
		case LX_CHIP_REV(_chip, B0) :																								\
			PE_REG_PHYS_VER_FLCV(g##_fn##_##_chip, b0, _r, _f, _c, _v1, _v2);															\
			break;																													\
		case LX_CHIP_REV(_chip, A1) :																								\
		case LX_CHIP_REV(_chip, A0) :																								\
			PE_REG_PHYS_VER_FLCV(g##_fn##_##_chip, a0, _r, _f, _c, _v1, _v2);															\
			break;																													\
	}																																\
} while (0)

#define PE_FN_CHIP_VER_RdFL(_fn, _chip, _ver, _r)						PE_REG_PHYS_VER_RdFL(g##_fn##_##_chip, _ver, _r)
#define PE_FN_CHIP_VER_WrFL(_fn, _chip, _ver, _r)						PE_REG_PHYS_VER_WrFL(g##_fn##_##_chip, _ver, _r)
#define PE_FN_CHIP_VER_Rd32(_fn, _chip, _ver, _r)						PE_REG_SHDW_VER_Rd32(g##_fn##_##_chip, _ver, _r)
#define PE_FN_CHIP_VER_Wr32(_fn, _chip, _ver, _r, _v)					PE_REG_SHDW_VER_Wr32(g##_fn##_##_chip, _ver, _r, _v)
#define PE_FN_CHIP_VER_Rd01(_fn, _chip, _ver, _r, _f01, _v01)			PE_REG_SHDW_VER_Rd01(g##_fn##_##_chip, _ver, _r, _f01, _v01)
#define PE_FN_CHIP_VER_Wr01(_fn, _chip, _ver, _r, _f01, _v01)			PE_REG_SHDW_VER_Wr01(g##_fn##_##_chip, _ver, _r, _f01, _v01)
#define PE_FN_CHIP_VER_WfCM(_fn, _chip, _ver, _r, _f, _c, _m)			PE_REG_SHDW_VER_WfCM(g##_fn##_##_chip, _ver, _r, _f, _c, _m)
#define PE_FN_CHIP_VER_WfCV(_fn, _chip, _ver, _r, _f, _c, _v1, _v2)		PE_REG_SHDW_VER_WfCV(g##_fn##_##_chip, _ver, _r, _f, _c, _v1, _v2)
#define PE_FN_CHIP_VER_FLRd(_fn, _chip, _ver, _r, _v) 					PE_REG_PHYS_VER_FLRd(g##_fn##_##_chip, _ver, _r, _v)
#define PE_FN_CHIP_VER_FLWr(_fn, _chip, _ver, _r, _v) 					PE_REG_PHYS_VER_FLWr(g##_fn##_##_chip, _ver, _r, _v)
#define PE_FN_CHIP_VER_FLRf(_fn, _chip, _ver, _r, _f01, _v01) 			PE_REG_PHYS_VER_FLRf(g##_fn##_##_chip, _ver, _r, _f01, _v01)
#define PE_FN_CHIP_VER_FLWf(_fn, _chip, _ver, _r, _f01, _v01) 			PE_REG_PHYS_VER_FLWf(g##_fn##_##_chip, _ver, _r, _f01, _v01)
#define PE_FN_CHIP_VER_FLCM(_fn, _chip, _ver, _r, _f, _c, _m) 			PE_REG_PHYS_VER_FLCM(g##_fn##_##_chip, _ver, _r, _f, _c, _m)
#define PE_FN_CHIP_VER_FLCV(_fn, _chip, _ver, _r, _f, _c, _v1, _v2) 	PE_REG_PHYS_VER_FLCV(g##_fn##_##_chip, _ver, _r, _f, _c, _v1, _v2)

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

#endif	 /* _PE_REG_MAC_H_ */

