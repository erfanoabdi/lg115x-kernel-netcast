
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
#	AUTHOR		:	root
#	DATE        :	2009.12.07
#	DESCRIPTION	:	Makefile for building lgbus module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

lgbus_MODULE			:= lgbus

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_lgbus-objs		:= lgbus_cfg.o
kdrv_lgbus-objs		+= lgbus_drv.o
kdrv_lgbus-objs		+= lgbus_proc.o
kdrv_lgbus-objs		+= h13/lgbus_core.o
kdrv_lgbus-objs		+= h13/lgbus_wrap.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_lgbus-CFLAGS	+=
kdrv_lgbus-CFLAGS	+=
kdrv_lgbus-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_lgbus-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(lgbus_MODULE)/,$(kdrv_lgbus-objs)) 
else
obj-m				:= kdrv_lgbus.o
endif
