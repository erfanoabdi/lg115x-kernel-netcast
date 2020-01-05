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
	0x0308 DLR_STATUS_PIC_CNT
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_STATUS_PIC_CNT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"status"              },
};

/*------------------------------------
	0x030c DLR_STATUS_LINE_CNT
------------------------------------*/
const DBG_REG_FIELD_T dbg_DLR_STATUS_LINE_CNT[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,12 ,0  ,"luma_line_counts"    },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,28 ,16 ,"chroma_line_counts"  },
};

DBG_REG_T gDbgRegDLR[] = {
	{ 0x0300 ,N_FLD(dbg_DLR_IN_IMG_FORMAT)       ,"DLR_IN_IMG_FORMAT"         ,dbg_DLR_IN_IMG_FORMAT       },
	{ 0x0304 ,N_FLD(dbg_DLR_FRAME_PACK_INFO)     ,"DLR_FRAME_PACK_INFO"       ,dbg_DLR_FRAME_PACK_INFO     },
	{ 0x0308 ,N_FLD(dbg_DLR_STATUS_PIC_CNT)      ,"DLR_STATUS_PIC_CNT"        ,dbg_DLR_STATUS_PIC_CNT      },
	{ 0x030c ,N_FLD(dbg_DLR_STATUS_LINE_CNT)     ,"DLR_STATUS_LINE_CNT"       ,dbg_DLR_STATUS_LINE_CNT     },
	{ 0 , } // end marker
};

#endif
