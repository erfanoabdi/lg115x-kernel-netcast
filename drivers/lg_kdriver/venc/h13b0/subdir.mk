
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
#	FILE NAME	:	subdir.mk                                                  #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	jaeseop.so (jaeseop.so@lge.com)                            #
#	DATE        :	2011.08.14                                                 #
#	DESCRIPTION	:	Makefile for building venc module 	                       #
#******************************************************************************#

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------

H1ENCODE_USE_POLLING	:= NO

VENC_HXENC_BUILTIN		:= NO

ifeq ($(VENC_HXENC_BUILTIN), YES)
HXENC_TOP       		:= $(KDRV_TOP_DIR)/venc/h13b0
include $(src)/venc/h13b0/hxenc.mk
endif

#obj-m               	+= venc/h13b0/

kdrv_venc-objs			+= h13b0/venc_hal_h13b0.o
kdrv_venc-objs      	+= h13b0/h1encode.o
kdrv_venc-objs      	+= h13b0/h1encode_common.o
kdrv_venc-objs      	+= h13b0/h1encode_h264.o
kdrv_venc-objs    		+= h13b0/h1encode_vp8.o
kdrv_venc-objs      	+= h13b0/h1encode_aui.o
kdrv_venc-objs      	+= h13b0/h1encode_wrapper.o

ifeq ($(VENC_HXENC_BUILTIN), YES)
kdrv_venc-objs          += $(HXENC_OBJS)
kdrv_venc-CFLAGS		+= $(HXENC_CFLAGS)
kdrv_venc-CFLAGS		+= -DVENC_HXENC_BUILTIN
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/inc
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/h264
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/vp8
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/memalloc
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/common
kdrv_venc-CFLAGS		+= -I$(HXENC_TOP)/camstab
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------

kdrv_venc-CFLAGS		+= -DVENC_USE_H1ENCODE
kdrv_venc-CFLAGS		+= -DH1ENCODE_EDIT_LGE

ifeq ($(H1ENCODE_USE_POLLING), YES)
	kdrv_venc-CFLAGS		+= -DH1ENCODE_USE_POLLING
endif

