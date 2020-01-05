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

#ifndef _DBG_DVR_h
#define _DBG_DVR_h

/*--------------------------------
	0x5400 DVR_STATUS
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_STATUS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,2  ,0  ,"de_status"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"ctrl_mode"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,17 ,16 ,"rd_indx"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,18 ,"de_info"             },
};

/*--------------------------------
	0x5404 DVR_DSIZE
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_DSIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"vsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hsize"               },
};

/*--------------------------------
	0x5408 DVR_DECSIZE
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_DECSIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"vsize"               },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"hsize"               },
};

/*--------------------------------
	0x540c DVR_HOFFSET
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_HOFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"roffset"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"loffset"             },
};

/*--------------------------------
	0x5410 DVR_VOFFSET
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_VOFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"boffset"             },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,27 ,16 ,"toffset"             },
};

/*--------------------------------
	0x5414 DVR_SEQINFO
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_SEQINFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,0  ,"aspect_ratio"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,16 ,16 ,"prog_seq"            },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,28 ,"frame_rate"          },
};

/*--------------------------------
	0x5418 DVR_PICINFO
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_PICINFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"prog_frame"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,4  ,4  ,"topfield_first"      },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,5  ,5  ,"repeat_firstfield"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,6  ,"frame_struct"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,8  ,"frame_ptr"           },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"clr_info"            },
};

/*--------------------------------
	0x5420 DVR_Y_ADDR
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_Y_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"y_addr"              },
};

/*--------------------------------
	0x5424 DVR_Y_STRIDE
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_Y_STRIDE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"y_stride"            },
};

/*--------------------------------
	0x5428 DVR_C_ADDR
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_C_ADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"c_addr"              },
};

/*--------------------------------
	0x542c DVR_C_STRIDE
--------------------------------*/
const DBG_REG_FIELD_T dbg_DVR_C_STRIDE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"c_stride"            },
};

DBG_REG_T gDbgRegDVR[] = {
	{ 0x5400 ,N_FLD(dbg_DVR_STATUS)          ,"DVR_STATUS"            ,dbg_DVR_STATUS          },
	{ 0x5404 ,N_FLD(dbg_DVR_DSIZE)           ,"DVR_DSIZE"             ,dbg_DVR_DSIZE           },
	{ 0x5408 ,N_FLD(dbg_DVR_DECSIZE)         ,"DVR_DECSIZE"           ,dbg_DVR_DECSIZE         },
	{ 0x540c ,N_FLD(dbg_DVR_HOFFSET)         ,"DVR_HOFFSET"           ,dbg_DVR_HOFFSET         },
	{ 0x5410 ,N_FLD(dbg_DVR_VOFFSET)         ,"DVR_VOFFSET"           ,dbg_DVR_VOFFSET         },
	{ 0x5414 ,N_FLD(dbg_DVR_SEQINFO)         ,"DVR_SEQINFO"           ,dbg_DVR_SEQINFO         },
	{ 0x5418 ,N_FLD(dbg_DVR_PICINFO)         ,"DVR_PICINFO"           ,dbg_DVR_PICINFO         },
	{ 0x5420 ,N_FLD(dbg_DVR_Y_ADDR)          ,"DVR_Y_ADDR"            ,dbg_DVR_Y_ADDR          },
	{ 0x5424 ,N_FLD(dbg_DVR_Y_STRIDE)        ,"DVR_Y_STRIDE"          ,dbg_DVR_Y_STRIDE        },
	{ 0x5428 ,N_FLD(dbg_DVR_C_ADDR)          ,"DVR_C_ADDR"            ,dbg_DVR_C_ADDR          },
	{ 0x542c ,N_FLD(dbg_DVR_C_STRIDE)        ,"DVR_C_STRIDE"          ,dbg_DVR_C_STRIDE        },
	{ 0 , } // end marker
};

#endif
