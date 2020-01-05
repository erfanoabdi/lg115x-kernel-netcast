
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
#	AUTHOR		:	sh.myoung (sh.myoung@lge.com)
#	DATE        :	2010.01.06
#	DESCRIPTION	:	Makefile for building dimm module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

dimm_MODULE			:= dimm

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_dimm-objs		:= dimm_cfg.o
kdrv_dimm-objs		+= dimm_drv.o
kdrv_dimm-objs		+= dimm_proc.o
kdrv_dimm-objs		+=
kdrv_dimm-objs		+= dimm_io.o
kdrv_dimm-objs		+= dimm_hal.o
kdrv_dimm-objs		+= dimm_lst.o
kdrv_dimm-objs		+= mcu/io_dimm.o
kdrv_dimm-objs		+=
ifeq ($(USE_VIDEO_UART2_FOR_MCU), YES)
ifneq ($(KDRV_GLOBAL_LINK), YES)
kdrv_dimm-objs		:= dimm_hal.o
endif
endif
ifeq ($(INCLUDE_L9_CHIP_KDRV), YES)
kdrv_dimm-objs		+= l9/dimm_reg_l9.o
endif
ifeq ($(INCLUDE_L8_CHIP_KDRV), YES)
kdrv_dimm-objs		+= l8/dimm_reg_l8.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_dimm-CFLAGS	+=
kdrv_dimm-CFLAGS	+=
kdrv_dimm-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_dimm-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(dimm_MODULE)/,$(kdrv_dimm-objs))
else
obj-m				:= kdrv_dimm.o
endif
