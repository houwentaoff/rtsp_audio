##
## unit_test/common.mk
##
## History:
##    2008/02/18 - [Cao Rongrong] Create
##
## Copyright (C) 2004-2008, Ambarella, Inc.
##
## All rights reserved. No Part of this file may be reproduced, stored
## in a retrieval system, or transmitted, in any form, or by any means,
## electronic, mechanical, photocopying, recording, or otherwise,
## without the prior consent of Ambarella, Inc.
##


PWD			:= $(shell pwd)
MODULE_DIR		:= $(word 2, $(subst /unit_test/linux/, ,$(PWD)))
AMBABUILD_TOPDIR	?= $(word 1, $(subst /app/ipcam, ,$(PWD)))
PRIVATE_DIR		:= $(shell echo ./$(MODULE_DIR)|sed 's/\/[0-9a-zA-Z_]*/\/../g' )
MODULE_NAME		:= "Audio Test"

-include $(AMBABUILD_TOPDIR)/.config

INCLUDE_FLAG    := -I$(AMBABUILD_TOPDIR)/prebuild/third-party/alsa/include
LINK_FLAG	:= -L$(AMBABUILD_TOPDIR)/prebuild/third-party/alsa/lib
LIBS		:= -lasound -lpthread -ldl


LIB_SUFFIX = a
INCLUDE_FLAG += -I../UsageEnvironment/include -I../groupsock/include \
				-I../liveMedia/include -I../BasicUsageEnvironment/include
##################### Included LIBS:
USAGE_ENVIRONMENT_DIR = ../UsageEnvironment
USAGE_ENVIRONMENT_LIB = $(USAGE_ENVIRONMENT_DIR)/libUsageEnvironment.$(LIB_SUFFIX)
BASIC_USAGE_ENVIRONMENT_DIR = ../BasicUsageEnvironment
BASIC_USAGE_ENVIRONMENT_LIB = $(BASIC_USAGE_ENVIRONMENT_DIR)/libBasicUsageEnvironment.$(LIB_SUFFIX)
LIVEMEDIA_DIR = ../liveMedia
LIVEMEDIA_LIB = $(LIVEMEDIA_DIR)/libliveMedia.$(LIB_SUFFIX)
GROUPSOCK_DIR = ../groupsock
GROUPSOCK_LIB = $(GROUPSOCK_DIR)/libgroupsock.$(LIB_SUFFIX)
LOCAL_LIBS = $(LIVEMEDIA_LIB) $(GROUPSOCK_LIB) \
			$(BASIC_USAGE_ENVIRONMENT_LIB) \
			$(USAGE_ENVIRONMENT_LIB)
LIBS += $(LOCAL_LIBS)
INCLUDE_G711 = -I$(AMBABUILD_TOPDIR)/build/include
LIBS_G711 = -L$(AMBABUILD_TOPDIR)/prebuild/g711 -lg711
INCLUDE_FLAG += $(INCLUDE_G711)
LIBS += $(LIBS_G711)

RTSP_AUDIO_PATH		= $(APP_PATH)

export AMBABUILD_TOPDIR

default:all

include $(AMBABUILD_TOPDIR)/build/app/common.mk

.PHONY: all clean

all:pre_all
	$(AMBA_MAKEFILE_V)echo "  [Build $(MODULE_NAME)]:"
	@echo "    compile testG711... "
	@$(AMBA_MAKEFILE_V)$(CROSS_COMPILE)g++ $(APP_CFLAG) -c test_audio.cpp $(INCLUDE_FLAG)
	@$(AMBA_MAKEFILE_V)$(CROSS_COMPILE)g++ $(APP_CFLAG) -c G711AudioStreamServerMediaSubsession.cpp $(INCLUDE_FLAG)
	@$(AMBA_MAKEFILE_V)$(CROSS_COMPILE)g++ $(APP_CFLAG) -c G711AudioStreamSource.cpp $(INCLUDE_FLAG)
	@$(AMBA_MAKEFILE_V)$(CROSS_COMPILE)g++ $(APP_CFLAG) -o \
		testG711 test_audio.o G711AudioStreamServerMediaSubsession.o G711AudioStreamSource.o \
		$(LINK_FLAG) $(LIBS)
	@$(AMBA_MAKEFILE_V)$(CROSS_COMPILE)strip testG711
	$(AMBA_MAKEFILE_V)mkdir -p $(RTSP_AUDIO_PATH)
	$(AMBA_MAKEFILE_V)cp -a testG711 $(RTSP_AUDIO_PATH)
	$(AMBA_MAKEFILE_V)chmod +x $(RTSP_AUDIO_PATH)/testG711

clean:pre_clean
	$(AMBA_MAKEFILE_V)echo "  [Clean $(MODULE_NAME)]:"
	$(AMBA_MAKEFILE_V)rm -f testG711 *.o

pre_all:
	@echo " "

pre_clean:
	@echo " "
