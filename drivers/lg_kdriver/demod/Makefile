
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
#	AUTHOR		:	jeongpil.yun (jeongpil.yun@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building demod module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

demod_MODULE			:= demod

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_demod-objs		:= demod_cfg.o
kdrv_demod-objs		+= demod_drv.o
kdrv_demod-objs		+= demod_proc.o
kdrv_demod-objs		+= demod_module.o
kdrv_demod-objs		+= demod_hw.o
kdrv_demod-objs		+= h13/demod_drv_h13.o
kdrv_demod-objs		+= h13/demod_common_h13.o
kdrv_demod-objs		+= h13/demod_dvb_h13.o
kdrv_demod-objs		+= h13/demod_vqi_h13.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_demod-CFLAGS	+=
kdrv_demod-CFLAGS	+=
kdrv_demod-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_demod-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(demod_MODULE)/,$(kdrv_demod-objs))
else
obj-m				:= kdrv_demod.o
endif
