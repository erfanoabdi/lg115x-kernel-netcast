
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
#	AUTHOR		:	won.hur (won.hur@lge.com)
#	DATE        :	2012.04.18
#	DESCRIPTION	:	Makefile for building vbi module                           #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

vbi_MODULE			:= vbi

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_vbi-objs		:= vbi_cfg.o
kdrv_vbi-objs		+= vbi_drv.o
kdrv_vbi-objs		+= vbi_proc.o
kdrv_vbi-objs		+= vbi_data.o
kdrv_vbi-objs		+= vbi_module.o

ifeq ($(INCLUDE_L9_CHIP_KDRV),YES)
kdrv_vbi-objs		+= hwl_l9_b0/ttx_hw_l9b0.o
kdrv_vbi-objs		+= hwl_l9_b0/cc_hw_l9b0.o
endif
kdrv_vbi-objs		+= hwl_h13_a0/ttx_hw_h13a0.o
kdrv_vbi-objs		+= hwl_h13_a0/cc_hw_h13a0.o
kdrv_vbi-objs		+=

kdrv_vbi-objs		+= hwl_h13_b0/ttx_hw_h13b0.o
kdrv_vbi-objs		+= hwl_h13_b0/cc_hw_h13b0.o
kdrv_vbi-objs		+=
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_vbi-CFLAGS	+=
kdrv_vbi-CFLAGS	+=
kdrv_vbi-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_vbi-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(vbi_MODULE)/,$(kdrv_vbi-objs))
else
obj-m				:= kdrv_vbi.o
endif
