
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
#	DESCRIPTION	:	Makefile for building frc module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

frc_MODULE			:= frc

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_frc-objs		:= frc_cfg.o
kdrv_frc-objs		+= frc_drv.o
kdrv_frc-objs		+= frc_proc.o
kdrv_frc-objs		+= frc_io.o
kdrv_frc-objs		+= mcu/io_frc.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_frc-CFLAGS	+=
kdrv_frc-CFLAGS	+=
kdrv_frc-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_frc-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(frc_MODULE)/,$(kdrv_frc-objs)) 
else
obj-m				:= kdrv_frc.o
endif
