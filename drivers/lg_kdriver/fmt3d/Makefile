
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
#	AUTHOR		:	dongho7.park (dongho7.park@lge.com)
#	DATE        :	2010.01.06
#	DESCRIPTION	:	Makefile for building fmt3d module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

fmt3d_MODULE			:= fmt3d

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_fmt3d-objs		:= fmt3d_cfg.o
kdrv_fmt3d-objs		+= fmt3d_drv.o
kdrv_fmt3d-objs		+= fmt3d_proc.o
kdrv_fmt3d-objs		+=
kdrv_fmt3d-objs		+= fmt3d_io.o
kdrv_fmt3d-objs		+= mcu/io_fmt3d.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_fmt3d-CFLAGS	+=
kdrv_fmt3d-CFLAGS	+=
kdrv_fmt3d-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_fmt3d-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(fmt3d_MODULE)/,$(kdrv_fmt3d-objs))
else
obj-m				:= kdrv_fmt3d.o
endif
