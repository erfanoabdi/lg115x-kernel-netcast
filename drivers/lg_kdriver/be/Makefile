
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
#	AUTHOR		:	justine.jeong@lge.com
#	DATE		:	2012.02.13
#	DESCRIPTION	:	Makefile for building be module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

be_MODULE			:= be

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_be-objs		:= be_drv.o
kdrv_be-objs		+= be_cfg.o

kdrv_be-objs		+= reg/be_reg.o
kdrv_be-objs		+= fwi/fwl_drv.o
kdrv_be-objs		+= fwi/fwl_hal.o
kdrv_be-objs		+= fwi/ipc_drv.o
kdrv_be-objs		+= fwi/ipc_hal.o
kdrv_be-objs		+= fwi/int_drv.o
kdrv_be-objs		+= fwi/int_hal.o
kdrv_be-objs		+= led/led_drv.o
kdrv_be-objs		+= frc/frc_drv.o
kdrv_be-objs		+= frc/frc_hal.o

kdrv_be-objs		+= h3d/h3d_drv.o
kdrv_be-objs		+= pwm_pe/pwm_pe_drv.o
kdrv_be-objs		+= pwm_pe/pwm_hal.o
kdrv_be-objs		+= sre/sre_drv.o


kdrv_be-objs		+= fwi/h13/fwl_reg_h13.o
kdrv_be-objs		+= fwi/mcu/mcu_ipc_test.o
kdrv_be-objs		+= fwi/h13/ipc_reg_h13.o
kdrv_be-objs		+= fwi/h13/int_reg_h13.o
kdrv_be-objs		+= led/h13/led_reg_h13.o
kdrv_be-objs		+= frc/h13/frc_reg_h13.o
kdrv_be-objs		+= pwm_pe/h13/pwm_reg_h13.o
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/reg
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/fwi
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/h3d
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/frc
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/sre
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/led
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/pwm_pe

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_be-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(be_MODULE)/,$(kdrv_be-objs))
else
obj-m				:= kdrv_be.o
endif

