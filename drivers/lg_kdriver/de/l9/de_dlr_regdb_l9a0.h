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

#ifndef _DBG_DLR_h
#define _DBG_DLR_h

/*------------------------------------
	0x0300 DLR_IN_IMG_FORMAT
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_IN_IMG_FORMAT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"in_image_format"     },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,4  ,"color_format"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,8  ,8  ,"lr_in_order"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,12 ,"progressive"         },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"sample_comb"         },
};

/*------------------------------------
	0x0304 DLR_FRAME_PACK_INFO
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_FRAME_PACK_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"one_frame_height"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"active_blank"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,28 ,"fp_interlace"        },
};

/*------------------------------------
	0x0308 DLR_QUINCUNX_COEFF0
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF0[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff0"     },
};

/*------------------------------------
	0x030c DLR_QUINCUNX_COEFF1
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF1[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff1"     },
};

/*------------------------------------
	0x0310 DLR_QUINCUNX_COEFF2
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF2[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff2"     },
};

/*------------------------------------
	0x0314 DLR_QUINCUNX_COEFF3
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF3[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff3"     },
};

/*------------------------------------
	0x0318 DLR_QUINCUNX_COEFF4
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF4[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff4"     },
};

/*------------------------------------
	0x031c DLR_QUINCUNX_COEFF5
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF5[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff5"     },
};

/*------------------------------------
	0x0320 DLR_QUINCUNX_COEFF6
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_QUINCUNX_COEFF6[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"quincunx_coeff6"     },
};

/*------------------------------------
	0x0324 DLR_STATUS
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"status"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,19 ,8  ,"luma_line_counts"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,20 ,"chroma_line_counts"  },
};

/*------------------------------------
	0x0328 DLR_DEBUG_MODE
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_DEBUG_MODE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"debugmode_en"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"qx_repetition"       },
};

DBG_REG_T gDbgRegDLR[] = {
	{ 0x0300 ,N_FLD(dbg_DLR_IN_IMG_FORMAT)       ,"DLR_IN_IMG_FORMAT"         ,dbg_DLR_IN_IMG_FORMAT       },
	{ 0x0304 ,N_FLD(dbg_DLR_FRAME_PACK_INFO)     ,"DLR_FRAME_PACK_INFO"       ,dbg_DLR_FRAME_PACK_INFO     },
	{ 0x0308 ,N_FLD(dbg_DLR_QUINCUNX_COEFF0)     ,"DLR_QUINCUNX_COEFF0"       ,dbg_DLR_QUINCUNX_COEFF0     },
	{ 0x030c ,N_FLD(dbg_DLR_QUINCUNX_COEFF1)     ,"DLR_QUINCUNX_COEFF1"       ,dbg_DLR_QUINCUNX_COEFF1     },
	{ 0x0310 ,N_FLD(dbg_DLR_QUINCUNX_COEFF2)     ,"DLR_QUINCUNX_COEFF2"       ,dbg_DLR_QUINCUNX_COEFF2     },
	{ 0x0314 ,N_FLD(dbg_DLR_QUINCUNX_COEFF3)     ,"DLR_QUINCUNX_COEFF3"       ,dbg_DLR_QUINCUNX_COEFF3     },
	{ 0x0318 ,N_FLD(dbg_DLR_QUINCUNX_COEFF4)     ,"DLR_QUINCUNX_COEFF4"       ,dbg_DLR_QUINCUNX_COEFF4     },
	{ 0x031c ,N_FLD(dbg_DLR_QUINCUNX_COEFF5)     ,"DLR_QUINCUNX_COEFF5"       ,dbg_DLR_QUINCUNX_COEFF5     },
	{ 0x0320 ,N_FLD(dbg_DLR_QUINCUNX_COEFF6)     ,"DLR_QUINCUNX_COEFF6"       ,dbg_DLR_QUINCUNX_COEFF6     },
	{ 0x0324 ,N_FLD(dbg_DLR_STATUS)              ,"DLR_STATUS"                ,dbg_DLR_STATUS              },
	{ 0x0328 ,N_FLD(dbg_DLR_DEBUG_MODE)          ,"DLR_DEBUG_MODE"            ,dbg_DLR_DEBUG_MODE          },
	{ 0 , } // end marker
};

#endif
