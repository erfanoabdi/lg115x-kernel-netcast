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
 *  PNG register details. ( used only within kdriver )
 *
 *  @author		Youngwoo Jin (youngwoo.jin@lge.com)
 *  @version	1.0 
 *  @date		2011.04.21
 *
 *  @addtogroup lg1152_png
 */

#ifndef _PNG_REG_L9_H_
#define _PNG_REG_L9_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0000 cmd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	start                           : 1,	//     0
	                                : 7,	//  1: 7 reserved
	mid_start                       : 1;	//     8
} CMD;

/*-----------------------------------------------------------------------------
	0x0004 read_base_addr ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0008 read_byte_size ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x000c write_base_addr ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0010 image_info1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	image_height                    :16,	//  0:15
	image_width                     :16;	// 16:31
} IMAGE_INFO1;

/*-----------------------------------------------------------------------------
	0x0014 image_info2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bitdepth                        : 5,	//  0: 4
	                                : 3,	//  5: 7 reserved
	color_type                      : 3;	//  8:10
} IMAGE_INFO2;

/*-----------------------------------------------------------------------------
	0x0018 intr_enable ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	filter_done_en                  : 1,	//     0
	inflate_done_en                 : 1,	//     1
	tcopt_err_en                    : 1,	//     2
	tlen_err_en                     : 1,	//     3
	tgen_err_en                     : 1,	//     4
	win_err_en                      : 1,	//     5
	code_err_en                     : 1,	//     6
	btype_err_en                    : 1,	//     7
	len_err_en                      : 1,	//     8
	row_err_en                      : 1,	//     9
	ftype_err_en                    : 1,	//    10
	read_done_en                    : 1;	//    11
} INTR_ENABLE;

/*-----------------------------------------------------------------------------
	0x001c intr_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	filter_done                     : 1,	//     0
	inflate_done                    : 1,	//     1
	tcopt_err                       : 1,	//     2
	tlen_err                        : 1,	//     3
	tgen_err                        : 1,	//     4
	win_err                         : 1,	//     5
	code_err                        : 1,	//     6
	btype_err                       : 1,	//     7
	len_err                         : 1,	//     8
	row_err                         : 1,	//     9
	ftype_err                       : 1,	//    10
	read_done                       : 1;	//    11
} INTR_STATUS;

/*-----------------------------------------------------------------------------
	0x0020 intr_clear ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	filter_done_clear               : 1,	//     0
	inflate_done_clear              : 1,	//     1
	tcopt_err_clear                 : 1,	//     2
	tlen_err_clear                  : 1,	//     3
	tgen_err_clear                  : 1,	//     4
	win_err_clear                   : 1,	//     5
	code_err_clear                  : 1,	//     6
	btype_err_clear                 : 1,	//     7
	len_err_clear                   : 1,	//     8
	row_err_clear                   : 1,	//     9
	ftype_err_clear                 : 1,	//    10
	read_done_clear                 : 1;	//    11
} INTR_CLEAR;

/*-----------------------------------------------------------------------------
	0x0024 dma_read_value ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	read_pri2                       : 4,	//  0: 3
	read_pri1                       : 4,	//  4: 7
	read_delay                      :16,	//  8:23
	read_txid                       : 2;	// 24:25
} DMA_READ_VALUE;

/*-----------------------------------------------------------------------------
	0x0028 dma_write_value ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	write_pri2                      : 4,	//  0: 3
	write_pri1                      : 4,	//  4: 7
	write_delay                     :16,	//  8:23
	write_txid                      : 2;	// 24:25
} DMA_WRITE_VALUE;

/*-----------------------------------------------------------------------------
	0x002c fifo_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	in_fifo_valid_bits              : 8;	//  0: 7
} FIFO_STATUS;

/*-----------------------------------------------------------------------------
	0x0034 read_byte_drop ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	start_read_byte_drop            : 4,	//  0: 3
	                                :12,	//  4:15 reserved
	end_read_byte_drop              : 4;	// 16:19
} READ_BYTE_DROP;

/*-----------------------------------------------------------------------------
	0x0038 read_base_addr_win ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x003c write_base_addr_win ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0040 dma_read_value_win ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	read_pri2                       : 4,	//  0: 3
	read_pri1                       : 4,	//  4: 7
	read_delay                      :16,	//  8:23
	read_txid                       : 2;	// 24:25
} DMA_READ_VALUE_WIN;

/*-----------------------------------------------------------------------------
	0x0044 dma_write_value_win ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	write_pri2                      : 4,	//  0: 3
	write_pri1                      : 4,	//  4: 7
	write_delay                     :16,	//  8:23
	write_txid                      : 2;	// 24:25
} DMA_WRITE_VALUE_WIN;

/*-----------------------------------------------------------------------------
	0x0048 read_base_addr_filter ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x004c write_base_addr_filter ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0050 dma_read_value_filter ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	read_pri2                       : 4,	//  0: 3
	read_pri1                       : 4,	//  4: 7
	read_delay                      :16,	//  8:23
	read_txid                       : 2;	// 24:25
} DMA_READ_VALUE_FILTER;

/*-----------------------------------------------------------------------------
	0x0054 dma_write_value_filter ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	write_pri2                      : 4,	//  0: 3
	write_pri1                      : 4,	//  4: 7
	write_delay                     :16,	//  8:23
	write_txid                      : 2;	// 24:25
} DMA_WRITE_VALUE_FILTER;

typedef struct {
	CMD                             	cmd                             ;	// 0x0000 : ''
	UINT32                          	read_base_addr                  ;	// 0x0004 : ''
	UINT32                          	read_byte_size                  ;	// 0x0008 : ''
	UINT32                          	write_base_addr                 ;	// 0x000c : ''
	IMAGE_INFO1                     	image_info1                     ;	// 0x0010 : ''
	IMAGE_INFO2                     	image_info2                     ;	// 0x0014 : ''
	INTR_ENABLE                     	intr_enable                     ;	// 0x0018 : ''
	INTR_STATUS                     	intr_status                     ;	// 0x001c : ''
	INTR_CLEAR                      	intr_clear                      ;	// 0x0020 : ''
	DMA_READ_VALUE                  	dma_read_value                  ;	// 0x0024 : ''
	DMA_WRITE_VALUE                 	dma_write_value                 ;	// 0x0028 : ''
	FIFO_STATUS                     	fifo_status                     ;	// 0x002c : ''
	UINT32                          	                 __rsvd_00[   1];	// 0x0030
	READ_BYTE_DROP                  	read_byte_drop                  ;	// 0x0034 : ''
	UINT32                          	read_base_addr_win              ;	// 0x0038 : ''
	UINT32                          	write_base_addr_win             ;	// 0x003c : ''
	DMA_READ_VALUE_WIN              	dma_read_value_win              ;	// 0x0040 : ''
	DMA_WRITE_VALUE_WIN             	dma_write_value_win             ;	// 0x0044 : ''
	UINT32                          	read_base_addr_filter           ;	// 0x0048 : ''
	UINT32                          	write_base_addr_filter          ;	// 0x004c : ''
	DMA_READ_VALUE_FILTER           	dma_read_value_filter           ;	// 0x0050 : ''
	DMA_WRITE_VALUE_FILTER          	dma_write_value_filter          ;	// 0x0054 : ''
// TODO : got no Category name T.T -> make up as 'PNG' } %s_REG_T;
/* %d regs, %d types */


} PNG_REG_T;
/* 21 regs, 21 types */

/* 21 regs, 21 types in Total*/

/*
 * @{
 * Naming for register pointer.
 * gpRealRegPNG : real register of PNG.
 * gpRegPNG     : shadow register.
 *
 * @def PNG_RdFL: Read  FLushing : Shadow <- Real.
 * @def PNG_WrFL: Write FLushing : Shadow -> Real.
 * @def PNG_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def PNG_Wr  : Write whole register(UINT32) from Shadow register.
 * @def PNG_Rd01 ~ PNG_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def PNG_Wr01 ~ PNG_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define PNG_RdFL(_r)			((gpRegPNG->_r)=(gpRealRegPNG->_r))
#define PNG_WrFL(_r)			((gpRealRegPNG->_r)=(gpRegPNG->_r))

#define PNG_Rd(_r)			*((UINT32*)(&(gpRegPNG->_r)))
#define PNG_Wr(_r,_v)			((PNG_Rd(_r))=((UINT32)(_v)))

#define PNG_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
								} while(0)

#define PNG_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
								} while(0)

#define PNG_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
								} while(0)

#define PNG_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
								} while(0)

#define PNG_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
								} while(0)

#define PNG_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
								} while(0)

#define PNG_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
								} while(0)

#define PNG_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
								} while(0)

#define PNG_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
								} while(0)

#define PNG_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
								} while(0)

#define PNG_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
									(_v11) = (gpRegPNG->_r._f11);				\
								} while(0)

#define PNG_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
									(_v11) = (gpRegPNG->_r._f11);				\
									(_v12) = (gpRegPNG->_r._f12);				\
								} while(0)

#define PNG_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
									(_v11) = (gpRegPNG->_r._f11);				\
									(_v12) = (gpRegPNG->_r._f12);				\
									(_v13) = (gpRegPNG->_r._f13);				\
								} while(0)

#define PNG_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
									(_v11) = (gpRegPNG->_r._f11);				\
									(_v12) = (gpRegPNG->_r._f12);				\
									(_v13) = (gpRegPNG->_r._f13);				\
									(_v14) = (gpRegPNG->_r._f14);				\
								} while(0)

#define PNG_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
									(_v11) = (gpRegPNG->_r._f11);				\
									(_v12) = (gpRegPNG->_r._f12);				\
									(_v13) = (gpRegPNG->_r._f13);				\
									(_v14) = (gpRegPNG->_r._f14);				\
									(_v15) = (gpRegPNG->_r._f15);				\
								} while(0)

#define PNG_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (gpRegPNG->_r._f01);				\
									(_v02) = (gpRegPNG->_r._f02);				\
									(_v03) = (gpRegPNG->_r._f03);				\
									(_v04) = (gpRegPNG->_r._f04);				\
									(_v05) = (gpRegPNG->_r._f05);				\
									(_v06) = (gpRegPNG->_r._f06);				\
									(_v07) = (gpRegPNG->_r._f07);				\
									(_v08) = (gpRegPNG->_r._f08);				\
									(_v09) = (gpRegPNG->_r._f09);				\
									(_v10) = (gpRegPNG->_r._f10);				\
									(_v11) = (gpRegPNG->_r._f11);				\
									(_v12) = (gpRegPNG->_r._f12);				\
									(_v13) = (gpRegPNG->_r._f13);				\
									(_v14) = (gpRegPNG->_r._f14);				\
									(_v15) = (gpRegPNG->_r._f15);				\
									(_v16) = (gpRegPNG->_r._f16);				\
								} while(0)


#define PNG_Wr01(_r,_f01,_v01)													\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
								} while(0)

#define PNG_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
								} while(0)

#define PNG_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
								} while(0)

#define PNG_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
								} while(0)

#define PNG_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
								} while(0)

#define PNG_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
								} while(0)

#define PNG_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
								} while(0)

#define PNG_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
								} while(0)

#define PNG_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
								} while(0)

#define PNG_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
								} while(0)

#define PNG_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
									(gpRegPNG->_r._f11) = (_v11);				\
								} while(0)

#define PNG_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
									(gpRegPNG->_r._f11) = (_v11);				\
									(gpRegPNG->_r._f12) = (_v12);				\
								} while(0)

#define PNG_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
									(gpRegPNG->_r._f11) = (_v11);				\
									(gpRegPNG->_r._f12) = (_v12);				\
									(gpRegPNG->_r._f13) = (_v13);				\
								} while(0)

#define PNG_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
									(gpRegPNG->_r._f11) = (_v11);				\
									(gpRegPNG->_r._f12) = (_v12);				\
									(gpRegPNG->_r._f13) = (_v13);				\
									(gpRegPNG->_r._f14) = (_v14);				\
								} while(0)

#define PNG_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
									(gpRegPNG->_r._f11) = (_v11);				\
									(gpRegPNG->_r._f12) = (_v12);				\
									(gpRegPNG->_r._f13) = (_v13);				\
									(gpRegPNG->_r._f14) = (_v14);				\
									(gpRegPNG->_r._f15) = (_v15);				\
								} while(0)

#define PNG_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(gpRegPNG->_r._f01) = (_v01);				\
									(gpRegPNG->_r._f02) = (_v02);				\
									(gpRegPNG->_r._f03) = (_v03);				\
									(gpRegPNG->_r._f04) = (_v04);				\
									(gpRegPNG->_r._f05) = (_v05);				\
									(gpRegPNG->_r._f06) = (_v06);				\
									(gpRegPNG->_r._f07) = (_v07);				\
									(gpRegPNG->_r._f08) = (_v08);				\
									(gpRegPNG->_r._f09) = (_v09);				\
									(gpRegPNG->_r._f10) = (_v10);				\
									(gpRegPNG->_r._f11) = (_v11);				\
									(gpRegPNG->_r._f12) = (_v12);				\
									(gpRegPNG->_r._f13) = (_v13);				\
									(gpRegPNG->_r._f14) = (_v14);				\
									(gpRegPNG->_r._f15) = (_v15);				\
									(gpRegPNG->_r._f16) = (_v16);				\
								} while(0)

/* Indexed Register Access.
 * 
 * There is in-direct field specified by 'index' field within a register.
 * Normally a register has only one meaning for a 'field_name', but indexed register
 * can hold several data for a 'field_name' specifed by 'index' field of indexed register.
 * When writing an 3rd data for given 'field_name' register, you need to set 'rw' = 0, 'index' = 2,
 * and 'load' = 0.
 * 
 * ASSUMPTION
 * For Writing indexed register load bit 
 * 
 * parameter list
 * _r     : name of register
 * _lname : name of load  bit field	: shall be 0 after macro executed.
 * _rwname: name of rw    bit field : shall be 0 after PNG_Wind(), 1 for PNG_Rind()
 * _iname : name of index bit field
 * _ival  : index value
 * _fname : field name
 * _fval  : field variable that field value shall be stored.
 *
 * PNG_Rind : General indexed register Read.(
 * PNG_Wind : General indexed register Read.
 *
 * PNG_Ridx : For 'index', 'rw', 'load' field name
 * PNG_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define PNG_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
							do {												\
								PNG_Wr03(_r,_lname,0,_rwname,1,_iname,_ival);	\
								PNG_WrFL(_r);									\
								PNG_RdFL(_r);									\
								PNG_Rd01(_r,_fname,_fval);						\
							} while (0)

#define PNG_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)				\
				PNG_Wr04(_r, _lname,0, _rwname,0, _iname,_ival, _fname,_fval)


#define PNG_Ridx(_r, _ival, _fname, _fval)	PNG_Rind(_r,load,rw,index,_ival,_fname,_fval)

#define PNG_Widx(_r, _ival, _fname, _fval)	PNG_Wind(_r,load,rw,index,_ival,_fname,_fval)

/** @} *//* end of macro documentation */

#ifdef __cplusplus
}
#endif

#endif	/* _PNG_REG_L9_H_ */

/* from 'LG1152_ICOD_MAN_01_v1.0.csv' 20110408 12:03:08   대한민국 표준시 by getregs v2.7 */
