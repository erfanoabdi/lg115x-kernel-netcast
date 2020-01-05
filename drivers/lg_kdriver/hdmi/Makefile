
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
#	DESCRIPTION	:	Makefile for building hdmi module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

hdmi_MODULE			:= hdmi

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_hdmi-objs		:= hdmi_cfg.o
kdrv_hdmi-objs		+= hdmi_drv.o
kdrv_hdmi-objs		+= hdmi_proc.o
kdrv_hdmi-objs		+= hdmi_module.o

ifeq ($(INCLUDE_L9_CHIP_KDRV),YES)
kdrv_hdmi-objs		+= l9/hdmi_hw_l9_b0.o
endif

ifeq ($(INCLUDE_H13_CHIP_KDRV),YES)
kdrv_hdmi-objs		+= h13/hdmi_hw_h13.o
endif

kdrv_hdmi-objs		+=

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_hdmi-CFLAGS	+= $(call cond_assign, NO, INCLUDE_KDRV_AFE, 	-D_WITHOUT_AFE_)
kdrv_hdmi-CFLAGS	+=
kdrv_hdmi-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_hdmi-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(hdmi_MODULE)/,$(kdrv_hdmi-objs))
else
obj-m				:= kdrv_hdmi.o
endif
