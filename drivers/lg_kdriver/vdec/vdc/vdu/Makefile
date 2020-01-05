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
#	AUTHOR		:	youngwoo.jin (youngwoo.jin@lge.com)
#	DATE        :	2013.01.07
#	DESCRIPTION	:	Makefile for building vdec module
#

ifndef VDEC_TOP_MODULE
VDEC_TOP_MODULE 	?= YES
endif

include $(src)/../../../base/Makefile
include $(src)/../../Makefile

obj-m			+= vdec_vdu.o
vdec_vdu-objs	+= vdec_vdu_drv.o

ifeq ($(SEPERATED_MODULE),YES)
include $(src)/subdir.mk
vdec_vdu-objs	+= $(cnm-objs)
endif

