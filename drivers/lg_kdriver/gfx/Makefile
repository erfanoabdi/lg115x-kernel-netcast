
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
#	AUTHOR		:	raxis.lim (raxis.lim@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building gfx module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

gfx_MODULE			:= gfx

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_gfx-objs		:= gfx_cfg.o
kdrv_gfx-objs		+= gfx_drv.o
kdrv_gfx-objs		+= gfx_proc.o
kdrv_gfx-objs       += gfx_hw.o
kdrv_gfx-objs       += gfx_surface.o
kdrv_gfx-objs       += gfx_draw.o
kdrv_gfx-objs       += gfx_sw_draw.o
kdrv_gfx-objs       += l9/gfx_drv_l9.o
kdrv_gfx-objs       += l9/gfx_hw_l9.o
kdrv_gfx-objs       += h13/gfx_drv_h13.o
kdrv_gfx-objs       += h13/gfx_hw_h13.o
kdrv_gfx-objs		+= 

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_gfx-CFLAGS	+=
kdrv_gfx-CFLAGS	+=
kdrv_gfx-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_gfx-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(gfx_MODULE)/,$(kdrv_gfx-objs)) 
else
obj-m				:= kdrv_gfx.o
endif
