
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
#   FILE NAME   :   makefile                                                   #
#   VERSION     :   1.0                                                        #
#   AUTHOR      :   raxis@lge.com                                              #
#   DATE        :   2010/11/17                                                 #
#   DESCRIPTION :   Makefile for building LG1150 kernel driver                 #
#******************************************************************************#

ifeq ($(KERNEL_NAME),)
$(error KERNEL_NAME is not defined, please define this variable above )
endif
ifeq ($(PLATFORM_CHIP),)
$(error PLATFORM_CHIP is not defined, please define this variable above )
endif

#==============================================================================
#
#	BUILD FLAGS
#
#==============================================================================
# if KDRV_GLOBAL_LINK is YES, the big one kernel module is created.
# if NO, all modules creates its own kernel module.
# default value is YES
KDRV_GLOBAL_LINK	?= YES

# if you want to test a power management, set KDRV_CONFIG_PM to YES
# default value is NO
KDRV_CONFIG_PM		?= NO

# enable debug feature
DEBUG				?= y

SIC_LAB_BOARD		?= NO

# default platform = NetCast
KDRV_PLATFORM_CFG	?= h13_nc4

export KDRV_GLOBAL_LINK KDRV_CONFIG_PM DEBUG KDRV_PLATFORM_CFG

ifeq ($(KERNELVERSION),)
#==============================================================================
#
#	KERNEL MODULE
#
#==============================================================================
KDRV_TOP_DIR		:= $(shell pwd)
KDRV_BUILD_DIR		:= $(KDRV_TOP_DIR)/build
ROOT_DIR 			:= $(shell cd ../../../.. && pwd)

OUT_DIR				?= /share/global_platform/$(PLATFORM_CHIP)/$(USER)/res/lglib
TFTP_DIR			?= /tftpboot/$(PLATFORM_CHIP)/$(USER)/pak-pioneer_columbus/res/lglib/kdrv


# KERNEL_NAME should be defined outside of this makefile
# If you want to fix KERNEL_NAME for test. uncomment the below line
# KERNEL_NAME		?= linux-2.6.33-mvista
KERNEL_DIR			:= $(KDRV_TOP_DIR)/../../kernel/$(KERNEL_NAME)

# this flag makes kdriver to be kernel module regardless of kernel configuration
KDRV_MODULE_BUILD 	?= YES

# export core environment variable for each module Makefile
export KDRV_TOP_DIR OUT_DIR KDRV_OUT_DIR TFTP_DIR KERNEL_DIR KERNEL_NAME
export KDRV_MODULE_BUILD

include $(KDRV_TOP_DIR)/modules.mk

export INCLUDE_L8_CHIP_KDRV
export INCLUDE_L9_CHIP_KDRV
export INCLUDE_H13_CHIP_KDRV

KDIFF				=	../../tools/kdiff.sh

#------------------------------------------------------------------------------
# default target
#------------------------------------------------------------------------------
all : build_kdriver
	# KDRIVER BUILD DONE...

clean : clean_kdriver
	# KDRIVER CLEAN DONE...

#------------------------------------------------------------------------------
# PHONEY target list
#------------------------------------------------------------------------------
.PHONEY: pre_build_kdriver

build_kdriver : pre_build_kdriver
ifeq ($(KDRV_MODULE_BUILD), YES)
	$(MAKE) -C $(KERNEL_DIR) M=$(KDRV_TOP_DIR) ARCH=arm modules
	rm -rf $(KDRV_TOP_DIR)/target
	$(MAKE) -C $(KERNEL_DIR) M=$(KDRV_TOP_DIR) modules_install INSTALL_MOD_PATH=$(KDRV_TOP_DIR)/target
	find ${KDRV_TOP_DIR}/target -name \*.ko -print0 | xargs -0 cp -t ${KDRV_BUILD_DIR}
	for ko in $(KDRV_BUILD_DIR)/*.ko; do $(STRIP) -d $$ko; done;
	find ${KDRV_TOP_DIR}/mem_prot_en.sh  -print0 | xargs -0 cp -t ${KDRV_BUILD_DIR}


ifeq ($(USE_CITRIX_SERVER), YES)
	$(MAKE) prodgsync_kdriver
else
	cd $(KDRV_BUILD_DIR) && find . -name \*.ko -exec $(IS_DIFFER) {} $(KDRV_OUT_DIR) $(OUT_DIR) \; | $(CPIO_CMD) $(KDRV_OUT_DIR)
endif
endif

clean_kdriver :
	rm -rf $(KDRV_TOP_DIR)/target
	$(MAKE) -C $(KERNEL_DIR) M=$(KDRV_TOP_DIR) clean





#------------------------------------------------------------------------------
# copy kernel driver to predefined directory ( USE_CITRIX_SERVER=YES )
#------------------------------------------------------------------------------
prodgsync_kdriver:
	$(ECHO)
	$(ECHO) "<!> LG KERNEL DRIVER : COPYING(SYNC) DRIVER.."
	$(ECHO)

	$(RM) $(CHANGE_FILE_LIST) && touch $(CHANGE_FILE_LIST)

ifeq ($(KDRV_GLOBAL_LINK), YES)
ifeq ($(KDRV_MODULE_BUILD), YES)
	cd $(KDRV_BUILD_DIR) && find . -name \*.ko -exec $(IS_DIFFER) {} $(KDRV_OUT_DIR) $(OUT_DIR) \; | $(CPIO_CMD) $(KDRV_OUT_DIR)
endif
endif
	cd $(KDRV_BUILD_DIR) && find lgmknods.sh	 -exec $(IS_DIFFER) {} $(KDRV_OUT_DIR) $(OUT_DIR) \; | $(CPIO_CMD) $(KDRV_OUT_DIR)


	# Copying DE firmware...
	cd $(KDRV_TOP_DIR)/de && find firmware -exec $(IS_DIFFER) {} $(KDRV_OUT_DIR) $(OUT_DIR) \; | $(CPIO_CMD) $(KDRV_OUT_DIR)

	$(TRANS_IMAGES) $(OUT_DIR)

	# progsync kernel driver if file is not empty...
	if [ -s $(CHANGE_FILE_LIST) ]; then						\
		GZIP="--fast" $(PROD_GSYNC) $(OUT_DIR) | tr ":" ".";	\
	else														\
		touch $(CHANGE_FILE_FLAG);								\
	fi


check_kver:
	$(MAKE)  -C ../../kernel check_kver

#------------------------------------------------------------------------------
# TODO) check if kdriver is patched successfully or not
#------------------------------------------------------------------------------
pre_build_kdriver : check_kver
	@$(ECHO)
	@$(ECHO) "<!> LG KERNEL DRIVER : MAKING OUT_DIR & TFTP_DIR..."
	@$(ECHO)
	@$(MKDIR) $(OUT_DIR)
	@$(MKDIR) $(TFTP_DIR)



else # KERNELVERSION

#==============================================================================
#
#	KERNEL BUILTIN
#
#==============================================================================
# the below paramter is used when kdriver is built into kernel
KDRV_TOP_DIR        := drivers/lg_kdriver
export KDRV_TOP_DIR

include $(KDRV_TOP_DIR)/modules.mk
include $(addprefix $(KDRV_TOP_DIR)/,$(addsuffix /Makefile,$(BASE_MODULE)))

#
# raxis.lim (2010/11/17)
# if KDRV_MODULE_BUILD is defined, we will make kdrv_lg1150.ko regardless of kernel configuration
# kDRV_MODULE_BUILD is defined at build/Makefile
#
ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif

obj-y	+= hma/
obj-y	+= logfunnel/

obj-$(CONFIG_LG_BUILTIN_KDRIVER)	+= kdrv_$(PLATFORM_CHIP).o
kdrv_$(PLATFORM_CHIP)-objs 			:= $(KDRV_MODULE_OBJS)

endif # KERNELVERSION
