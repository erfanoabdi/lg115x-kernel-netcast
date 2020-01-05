
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
#	FILE NAME	:	subdir.mk                                                  #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	jaeseop.so (jaeseop.so@lge.com)                            #
#	DATE        :	2011.08.14                                                 #
#	DESCRIPTION	:	Makefile for building venc module 	                       #
#******************************************************************************#

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------

kdrv_venc-objs		+= lgenc/venc_hal_lgenc.o
kdrv_venc-objs		+= lgenc/venc_core.o
kdrv_venc-objs		+= lgenc/venc_isr.o
kdrv_venc-objs		+= lgenc/venc_reg_api.o

ifeq ($(INCLUDE_L9_CHIP_KDRV), YES)
kdrv_venc-objs		+= lgenc/l9/venc_l9_reg.o
endif

ifeq ($(INCLUDE_H13_CHIP_KDRV), YES)
kdrv_venc-objs		+= lgenc/h13/venc_h13_reg.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------

kdrv_venc-CFLAGS	+= -DVENC_USE_LGENC
kdrv_venc-CFLAGS	+=


