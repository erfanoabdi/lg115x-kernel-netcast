# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.
#  
#  This program is free software; you can redistribute it and/or 
#  modify it under the terms of the GNU General Public License 
#  version 2 as published by the Free Software Foundation.
#   
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of 
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
#   GNU General Public License for more details.
#
#	FILE NAME	:	makefile
#	VERSION		:	1.0
#	AUTHOR		:	seokjoo.lee (seokjoo.lee@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building vdec module
#

SEPERATED_MODULE		:= YES

ifeq ($(PLATFORM),PIONEER)
SEPERATED_MODULE		:= NO
endif


ifeq ($(PLATFORM_CHIP_REV),B0)
vdec_haldir := lg1154/b0
else
vdec_haldir := lg1154/a0
endif


kdrv_vdec-objs		+= vdec_drv.o
kdrv_vdec-objs		+= vo.o

kdrv_vdec-objs		+= ves/ves_drv.o
kdrv_vdec-objs		+= ves/ves_cpb.o
kdrv_vdec-objs		+= ves/ves_auib.o

kdrv_vdec-objs		+= vdc/vdc_drv.o
kdrv_vdec-objs		+= vdc/vdec_stc_timer.o
kdrv_vdec-objs		+= vdc/vdu_drv.o

kdrv_vdec-objs		+= vds/disp_q.o
kdrv_vdec-objs		+= vds/disp_clear_q.o
kdrv_vdec-objs		+= vds/vdisp_drv.o
kdrv_vdec-objs		+= vds/vdec_rate.o
kdrv_vdec-objs		+= vds/pts_drv.o
kdrv_vdec-objs		+= vds/vsync_drv.o
kdrv_vdec-objs		+= vds/de_if_drv.o

kdrv_vdec-objs		+= mcu/vdec_isr.o
kdrv_vdec-objs		+= mcu/ipc_req.o
kdrv_vdec-objs		+= mcu/ipc_callback.o

kdrv_vdec-objs		+= hal/$(vdec_haldir)/av_lipsync_hal_api.o
kdrv_vdec-objs		+= hal/$(vdec_haldir)/ipc_reg_api.o
kdrv_vdec-objs		+= hal/$(vdec_haldir)/pdec_hal_api.o
kdrv_vdec-objs		+= hal/$(vdec_haldir)/de_ipc_hal_api.o
kdrv_vdec-objs		+= hal/$(vdec_haldir)/top_hal_api.o
kdrv_vdec-objs		+= hal/$(vdec_haldir)/vsync_hal_api.o
kdrv_vdec-objs		+= hal/$(vdec_haldir)/lq_hal_api.o
kdrv_vdec-objs-$(CONFIG_MACH_LG1154) += hal/$(vdec_haldir)/de_vdo_hal_api.o


ifndef VDEC_TOP_MODULE
VDEC_TOP_MODULE 	?= YES

ifeq ($(SEPERATED_MODULE),YES)
obj-m				+= vdec/vdc/vdu/
else
include $(src)/vdec/vdc/vdu/subdir.mk
kdrv_vdec-objs		+= $(addprefix vdc/vdu/,$(cnm-objs))
endif
endif

ifeq ($(SEPERATED_MODULE),NO)
kdrv_vdec-CFLAGS	+= -DINCLUDE_MODULE
endif

# vdec driver that is linked into kdrv_lg115x.ko
#kdrv_vdec-CFLAGS	+= -I$(src)/logfunnel
KDRV_MODULE_OBJS	+= $(addprefix vdec/,$(kdrv_vdec-objs) $(kdrv_vdec-objs-y))
EXTRA_CFLAGS		+= $(kdrv_vdec-CFLAGS)


