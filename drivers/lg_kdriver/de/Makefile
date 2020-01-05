
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 

#	---------------------------------------------------------------------------#
#																			   #
#	FILE NAME	:	makefile												   #
#	VERSION		:	1.0														   #
#	AUTHOR		:	dongho7.park (dongho7.park@lge.com)
#	DATE		:	2009.12.30
#	DESCRIPTION :	Makefile for building de module						 #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

de_MODULE			:= de

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_de-objs		:= de_cfg.o
kdrv_de-objs		+= de_drv.o
kdrv_de-objs		+= de_proc.o
kdrv_de-objs		+=
kdrv_de-objs		+= de_io.o
kdrv_de-objs		+= de_hal.o
kdrv_de-objs		+=
kdrv_de-objs		+= mcu/mcu_test.o
kdrv_de-objs		+= mcu/io_video.o
kdrv_de-objs		+=
ifeq ($(USE_VIDEO_UART2_FOR_MCU), YES)
ifneq ($(KDRV_GLOBAL_LINK), YES)
kdrv_de-objs		:= de_hal.o
endif
endif
kdrv_de-objs		+=
ifeq ($(INCLUDE_H13_CHIP_KDRV), YES)
kdrv_de-objs		+= h13/de_reg_h13.o
kdrv_de-objs		+= h13/de_prm_h13.o
kdrv_de-objs		+= h13/de_fw_h13.o
kdrv_de-objs		+= h13/de_ipc_h13.o
kdrv_de-objs		+= h13/de_init_h13.o
endif
ifeq ($(INCLUDE_L9_CHIP_KDRV), YES)
kdrv_de-objs		+= l9/de_reg_l9.o
kdrv_de-objs		+= l9/de_prm_l9.o
kdrv_de-objs		+= l9/de_fw_l9.o
kdrv_de-objs		+= l9/de_ipc_l9.o
kdrv_de-objs		+= l9/de_init_l9.o
kdrv_de-objs		+= l9/vp_reg_l9.o
endif
kdrv_de-objs		+= de_fw.o
kdrv_de-objs		+= de_ipc.o
kdrv_de-objs		+= de_int.o
#kdrv_de-objs		+= de_dbi.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_de-CFLAGS	+=
kdrv_de-CFLAGS	+=
kdrv_de-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_de-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(de_MODULE)/,$(kdrv_de-objs))
else
obj-m				:= kdrv_de.o
endif
