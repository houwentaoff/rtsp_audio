###############################################
#
#    2010/02/03 - [Jian Tang] created file
#
# Copyright (C) 2010, Ambarella, Inc.
#
# All rights reserved. No Part of this file may be reproduced, stored
# in a retrieval system, or transmitted, in any form, or by any means,
# electronic, mechanical, photocopying, recording, or otherwise,
# without the prior consent of Ambarella, Inc.
#
###############################################

default: all

AMBABUILD_TOPDIR  = $(word 1, $(subst /app/ipcam, ,$(shell pwd)))
MODULE_NAME		:= mediaServer

export AMBABUILD_TOPDIR

INCLUDES = -I../UsageEnvironment/include -I../groupsock/include \
		-I../liveMedia/include -I../BasicUsageEnvironment/include

-include $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/config.mk


##################### Local dependences:
live555MediaServer,$(CPP):	DynamicRTSPServer.hh version.hh
DynamicRTSPServer.$(CPP):	DynamicRTSPServer.hh

MEDIA_SERVER_OBJS = live555MediaServer.$(OBJ) \
		DynamicRTSPServer.$(OBJ)
##################### End of local dependences:


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
LIBS =	$(LOCAL_LIBS) $(LIBS_FOR_CONSOLE_APPLICATION)
##################### End of Included LIBS:


##################### Executable apps:
live555MediaServer$(EXE):	$(MEDIA_SERVER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MEDIA_SERVER_OBJS) $(LIBS)
##################### End of executable apps:


MEDIA_SERVER = live555MediaServer$(EXE)

MODULE_TARGETS = $(MEDIA_SERVER)

EXE_DIR	=	.
$(EXE_DIR):
	@$(MKDIR) $(EXE_DIR)

-include $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/rules.mk

##### Any additional, platform-specific rules come here:

