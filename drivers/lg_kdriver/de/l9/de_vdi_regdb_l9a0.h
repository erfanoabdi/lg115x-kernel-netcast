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

#ifndef _DBG_VDI_h
#define _DBG_VDI_h

/*--------------------------------------------
	0x4d00 VDI_FRAME_INX
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_FRAME_INX[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,7  ,0  ,"frame_index"         },
};

/*--------------------------------------------
	0x4d04 VDI_PIC_INFO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_PIC_INFO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,1  ,0  ,"display_type"        },
};

/*--------------------------------------------
	0x4d08 VDI_FRAME_RATE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_FRAME_RATE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"framerateresidual"   },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"frameratedivminus1"  },
};

/*--------------------------------------------
	0x4d0c VDI_ASPECT_RATIO
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_ASPECT_RATIO[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,3  ,0  ,"aspect_ratio"        },
};

/*--------------------------------------------
	0x4d10 VDI_PICTURE_SIZE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_PICTURE_SIZE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"height"              },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"width"               },
};

/*--------------------------------------------
	0x4d14 VDI_H_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_H_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"right_offset"        },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"left_offset"         },
};

/*--------------------------------------------
	0x4d18 VDI_V_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_V_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"bottom_offset"       },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,16 ,"top_offset"          },
};

/*--------------------------------------------
	0x4d1c VDI_FRAMEUPDATED
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_FRAMEUPDATED[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,0  ,0  ,"updated"             },
};

/*--------------------------------------------
	0x4d20 VDI_Y_FRAME_BASE_ADDRESS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_Y_FRAME_BASE_ADDRESS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"start_addr"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,12 ,"base_addr"           },
};

/*--------------------------------------------
	0x4d24 VDI_C_FRAME_BASE_ADDRESS
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_C_FRAME_BASE_ADDRESS[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,11 ,0  ,"start_addr"          },
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,12 ,"base_addr"           },
};

/*--------------------------------------------
	0x4d28 VDI_Y_FRAME_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_Y_FRAME_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"frame_offset"        },
};

/*--------------------------------------------
	0x4d2c VDI_C_FRAME_OFFSET
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_C_FRAME_OFFSET[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"frame_offset"        },
};

/*--------------------------------------------
	0x4d30 VDI_STRIDE
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_STRIDE[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,15 ,0  ,"stride"              },
};

/*--------------------------------------------
	0x4d34 VDI_USERDATABASEADDR
--------------------------------------------*/
const DBG_REG_FIELD_T dbg_VDI_USERDATABASEADDR[] = {
	{ REG_XS_N_RW ,0 ,0 ,0 ,0 ,31 ,0  ,"userdatabaseaddr"    },
};

DBG_REG_T gDbgRegVDI[] = {
	{ 0x4d00 ,N_FLD(dbg_VDI_FRAME_INX)                   ,"VDI_FRAME_INX"                     ,dbg_VDI_FRAME_INX                   },
	{ 0x4d04 ,N_FLD(dbg_VDI_PIC_INFO)                    ,"VDI_PIC_INFO"                      ,dbg_VDI_PIC_INFO                    },
	{ 0x4d08 ,N_FLD(dbg_VDI_FRAME_RATE)                  ,"VDI_FRAME_RATE"                    ,dbg_VDI_FRAME_RATE                  },
	{ 0x4d0c ,N_FLD(dbg_VDI_ASPECT_RATIO)                ,"VDI_ASPECT_RATIO"                  ,dbg_VDI_ASPECT_RATIO                },
	{ 0x4d10 ,N_FLD(dbg_VDI_PICTURE_SIZE)                ,"VDI_PICTURE_SIZE"                  ,dbg_VDI_PICTURE_SIZE                },
	{ 0x4d14 ,N_FLD(dbg_VDI_H_OFFSET)                    ,"VDI_H_OFFSET"                      ,dbg_VDI_H_OFFSET                    },
	{ 0x4d18 ,N_FLD(dbg_VDI_V_OFFSET)                    ,"VDI_V_OFFSET"                      ,dbg_VDI_V_OFFSET                    },
	{ 0x4d1c ,N_FLD(dbg_VDI_FRAMEUPDATED)                ,"VDI_FRAMEUPDATED"                  ,dbg_VDI_FRAMEUPDATED                },
	{ 0x4d20 ,N_FLD(dbg_VDI_Y_FRAME_BASE_ADDRESS)        ,"VDI_Y_FRAME_BASE_ADDRESS"          ,dbg_VDI_Y_FRAME_BASE_ADDRESS        },
	{ 0x4d24 ,N_FLD(dbg_VDI_C_FRAME_BASE_ADDRESS)        ,"VDI_C_FRAME_BASE_ADDRESS"          ,dbg_VDI_C_FRAME_BASE_ADDRESS        },
	{ 0x4d28 ,N_FLD(dbg_VDI_Y_FRAME_OFFSET)              ,"VDI_Y_FRAME_OFFSET"                ,dbg_VDI_Y_FRAME_OFFSET              },
	{ 0x4d2c ,N_FLD(dbg_VDI_C_FRAME_OFFSET)              ,"VDI_C_FRAME_OFFSET"                ,dbg_VDI_C_FRAME_OFFSET              },
	{ 0x4d30 ,N_FLD(dbg_VDI_STRIDE)                      ,"VDI_STRIDE"                        ,dbg_VDI_STRIDE                      },
	{ 0x4d34 ,N_FLD(dbg_VDI_USERDATABASEADDR)            ,"VDI_USERDATABASEADDR"              ,dbg_VDI_USERDATABASEADDR            },
	{ 0 , } // end marker
};

#endif
