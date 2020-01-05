
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
#	AUTHOR		:	wonsik.do (wonsik.do@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building afe module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

afe_MODULE			:= afe

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_afe-objs		:= afe_cfg.o
kdrv_afe-objs		+= afe_drv.o
kdrv_afe-objs		+= afe_proc.o
kdrv_afe-objs		+= adc_AAD.o
kdrv_afe-objs           += adc_IBD.o
kdrv_afe-objs           += adc_IFM.o
kdrv_afe-objs           += adc_AGOC.o
kdrv_afe-objs           += adc_control.o
kdrv_afe-objs           += adc_module.o
kdrv_afe-objs           += resolution.o

ifeq ($(INCLUDE_L9_CHIP_KDRV),YES)
kdrv_afe-objs			+= l9/adc_hw_l9b0.o	
kdrv_afe-objs			+= l9/cvd_hw_l9b0.o
kdrv_afe-objs			+= l9/cvd_control_l9b0.o 
kdrv_afe-objs			+= l9/cvd_task_l9b0.o 
kdrv_afe-objs           += l9/vport_i2c_l9a0.o
kdrv_afe-objs           += l9/vport_i2c_l9b0.o
endif

kdrv_afe-objs			+= h13/adc_hw_h13a0.o	
kdrv_afe-objs			+= h13/cvd_control_h13a0.o	
kdrv_afe-objs			+= h13/cvd_hw_h13a0.o	
kdrv_afe-objs			+= h13/cvd_task_h13a0.o	


kdrv_afe-objs			+= h13/cvd_control_h13b0.o	
kdrv_afe-objs			+= h13/cvd_hw_h13b0.o	
kdrv_afe-objs			+= h13/cvd_task_h13b0.o

kdrv_afe-objs           += cvd_module.o

#--- for Pioneer Platform ---
ifeq ($(PLATFORM),PIONEER)
ifeq ($(PLATFORM_CHIP),lg1154)
ifeq ($(PLATFORM_CHIP_REV),B0)
kdrv_afe-CFLAGS	+= -DH13B0_CVD_USE_LBUS
endif
endif
endif
#--- for NC4 Platform ---
ifeq ($(PROJECT_NAME),GP4-L9)
ifeq ($(PLATFORM_CHIP_VER),lg1154)
ifeq ($(PLATFORM_CHIP_REV),B0)
kdrv_afe-CFLAGS	+= -DH13B0_CVD_USE_LBUS
endif
endif
endif
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_afe-CFLAGS	+=
kdrv_afe-CFLAGS	+=
kdrv_afe-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_afe-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(afe_MODULE)/,$(kdrv_afe-objs))
else
obj-m				:= kdrv_afe.o
endif
