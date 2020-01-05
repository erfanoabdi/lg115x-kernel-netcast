
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 

#                                                                              #
#	FILE NAME	:	makefile                                                   #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	eunjoo.kim (eunjoo.kim@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building ci module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

ci_MODULE			:= ci

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_ci-objs		:= ci_cfg.o
kdrv_ci-objs		+= ci_drv.o
kdrv_ci-objs		+= ci_proc.o
kdrv_ci-objs		+= ci_cis.o
kdrv_ci-objs		+= ci_coredrv.o
kdrv_ci-objs		+= ci_io.o
kdrv_ci-objs		+= ci_isr.o
kdrv_ci-objs		+=

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_ci-CFLAGS	+=
kdrv_ci-CFLAGS	+=
kdrv_ci-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_ci-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(ci_MODULE)/,$(kdrv_ci-objs))
else
obj-m				:= kdrv_ci.o
endif
