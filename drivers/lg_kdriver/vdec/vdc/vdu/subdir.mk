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

cnm-objs		+= cnm/cnm_drv.o
cnm-objs		+= cnm/cnm_debug.o

cnm-objs		+= cnm/vdi/vdi.o
cnm-objs		+= cnm/vdi/vdi_osal.o

cnm-objs		+= cnm/vpuapi/vpuapi.o
cnm-objs		+= cnm/vpuapi/vpuapifunc.o

