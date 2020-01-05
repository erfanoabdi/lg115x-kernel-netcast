
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

ifeq ($(TARGET_PLATFORM),lg115x)
#==============================================================================
# local specific variable
#==============================================================================

include $(SOC_LINUX_DIR)/NC_lg115xSpecific.mk

#==============================================================================
# NetCast rules
#==============================================================================

#need discussion
LOCAL_MODULE := $(TARGET_PLATFORM)_kdriver

.PHONY: $(LOCAL_MODULE) clean clean-$(LOCAL_MODULE)

$(LOCAL_MODULE): PRIVATE_PATH := $(LOCAL_PATH)
$(LOCAL_MODULE):
	@$(MAKE) $(JOB_NR) -C $(PRIVATE_PATH) $(KERNEL_MAKE_OPTS) $(MAKE_OPTS) $(GOAL) $(REL) || exit 1

ifeq ($(GOAL),)
	@mkdir -p $(PREBUILT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/de/firmware
	@mkdir -p $(PREBUILT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/build
	@rsync -uz $(PRIVATE_PATH)/build/* $(PREBUILT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/build
	@rsync -uz $(PRIVATE_PATH)/de/firmware/*  $(PREBUILT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/de/firmware
endif

#	@mkdir -p $(TARGET_OUT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/de/firmware
#	@mkdir -p $(TARGET_OUT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/build
#	@rsync -uz $(PRIVATE_PATH)/build/* $(TARGET_OUT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/build
#	@rsync -uz $(PRIVATE_PATH)/de/firmware/* $(TARGET_OUT_ETC_FILES)/$(TARGET_PLATFORM)_kdriver/de/firmware


clean:	clean-$(LOCAL_MODULE)
clean-$(LOCAL_MODULE) : PRIVATE_PATH := $(LOCAL_PATH)
clean-$(LOCAL_MODULE) :
	@echo "Cleaning $(PRIVATE_PATH) ...."
	@$(MAKE) -C $(PRIVATE_PATH) $(KERNEL_MAKE_OPTS) $(MAKE_OPTS) clean || exit 1

ifeq ($(OS_LG115X_LINUX),)
ALL_PREBUILT += $(LOCAL_MODULE)
endif

#==============================================================================
endif
