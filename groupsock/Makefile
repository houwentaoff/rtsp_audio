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

AMBABUILD_TOPDIR	= $(word 1, $(subst /app/ipcam, ,$(shell pwd)))
MODULE_NAME		= groupsock

export AMBABUILD_TOPDIR

INCLUDES = -Iinclude -I../UsageEnvironment/include

-include $(AMBABUILD_TOPDIR)/build/app/common.mk
-include $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/config.mk

LIB_OBJS = GroupsockHelper.$(OBJ) GroupEId.$(OBJ) inet.$(OBJ) \
		Groupsock.$(OBJ) NetInterface.$(OBJ) NetAddress.$(OBJ) \
		IOHandlers.$(OBJ)

MODULE_TARGETS = $(MODULE_LIBS)

-include $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/rules.mk

##### Any additional, platform-specific rules come here:

