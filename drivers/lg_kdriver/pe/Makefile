
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 

#   ---------------------------------------------------------------------------#
#                                                                              #
#	FILE NAME	:	makefile                                                   #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	sj.youm (sj.youm@lge.com)
#	DATE		:	2011.06.22
#	DESCRIPTION	:	Makefile for building pe module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

pe_MODULE			:= pe

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_pe-objs		:= pe_drv.o
kdrv_pe-objs		+= pe_io.o
kdrv_pe-objs		+= ccm/pe_ccm.o
kdrv_pe-objs		+= cmg/pe_cmg.o
kdrv_pe-objs		+= cmn/pe_cmn.o
kdrv_pe-objs		+= csc/pe_csc.o
kdrv_pe-objs		+= dcm/pe_dcm.o
kdrv_pe-objs		+= dnt/pe_dnt.o
kdrv_pe-objs		+= nrd/pe_nrd.o
kdrv_pe-objs		+= shp/pe_shp.o
kdrv_pe-objs		+= win/pe_win.o
kdrv_pe-objs		+= util/pe_spd.o
kdrv_pe-objs		+= util/pe_etc.o
kdrv_pe-objs		+= reg/pe_reg.o

ifeq ($(INCLUDE_H13_CHIP_KDRV), YES)
kdrv_pe-objs		+= reg/h13/pe_reg_h13.o
kdrv_pe-objs		+= cmn/h13/pe_cmn_hw_h13.o
kdrv_pe-objs		+= ccm/h13/pe_ccm_hw_h13.o
kdrv_pe-objs		+= cmg/h13/pe_cmg_hw_h13.o
kdrv_pe-objs		+= dcm/h13/pe_dcm_hw_h13.o
kdrv_pe-objs		+= dcm/h13/pe_hst_hw_h13.o
kdrv_pe-objs		+= nrd/h13/pe_nrd_hw_h13.o
kdrv_pe-objs		+= dnt/h13/pe_dnt_hw_h13.o
kdrv_pe-objs		+= shp/h13/pe_shp_hw_h13.o
kdrv_pe-objs		+= util/h13/pe_fwi_h13.o
kdrv_pe-objs		+= util/h13/pe_tsk_h13.o
kdrv_pe-objs		+= util/h13/pe_inf_h13.o
kdrv_pe-objs		+= win/h13/pe_win_hw_h13.o
endif

ifeq ($(INCLUDE_L9_CHIP_KDRV), YES)
kdrv_pe-objs		+= reg/l9/pe_reg_l9.o
kdrv_pe-objs		+= cmn/l9/pe_cmn_hw_l9.o
kdrv_pe-objs		+= ccm/l9/pe_ccm_hw_l9.o
kdrv_pe-objs		+= cmg/l9/pe_cmg_hw_l9.o
kdrv_pe-objs		+= dcm/l9/pe_dcm_hw_l9.o
kdrv_pe-objs		+= nrd/l9/pe_nrd_hw_l9.o
kdrv_pe-objs		+= dnt/l9/pe_dnt_hw_l9.o
kdrv_pe-objs		+= shp/l9/pe_shp_hw_l9.o
kdrv_pe-objs		+= util/l9/pe_fwi_l9.o
kdrv_pe-objs		+= util/l9/pe_d3d_l9.o
kdrv_pe-objs		+= util/l9/pe_tsk_l9.o
kdrv_pe-objs		+= util/l9/pe_inf_l9.o
kdrv_pe-objs		+= win/l9/pe_win_hw_l9.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_pe-CFLAGS   := -I$(KDRV_TOP_DIR)/de
kdrv_pe-CFLAGS   := -I$(KDRV_TOP_DIR)/be/fwi
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/util
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/cmn
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/ccm
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/dcm
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/win
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/csc
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/cmg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/nrd
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/dnt
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/shp

ifeq ($(INCLUDE_H13_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/de/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/reg/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/util/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/cmn/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/ccm/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/cmg/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/dcm/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/nrd/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/dnt/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/shp/h13
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/win/h13
endif

ifeq ($(INCLUDE_L9_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/de/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/reg/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/util/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/cmn/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/ccm/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/cmg/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/dcm/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/nrd/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/dnt/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/shp/l9
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/win/l9
endif

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_pe-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(pe_MODULE)/,$(kdrv_pe-objs))
else
obj-m				:= kdrv_pe.o
endif
