###############################################
#
# app/ipcam/rtsp/livemedia
#
# 2010/02/03 - [Jian Tang] created file
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

PWD			:= $(shell pwd)
AMBABUILD_TOPDIR	?= $(word 1, $(subst /app/ipcam, ,$(PWD)))

export AMBABUILD_TOPDIR

include $(AMBABUILD_TOPDIR)/build/app/common.mk

.PHONY: all depend clean

all:
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/liveMedia $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/groupsock $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/UsageEnvironment $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/BasicUsageEnvironment $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testProgs $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testG711 $@
	$(AMBA_MAKEFILE_V)mkdir -p $(APP_PATH)
	$(AMBA_MAKEFILE_V)cp -a $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testProgs/testAMRAudioStreamer $(APP_PATH)
	$(AMBA_MAKEFILE_V)chmod +x $(APP_PATH)/testAMRAudioStreamer
	$(AMBA_MAKEFILE_V)cp -a $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testProgs/testOnDemandRTSPServer $(APP_PATH)
	$(AMBA_MAKEFILE_V)chmod +x $(APP_PATH)/testOnDemandRTSPServer
	$(AMBA_MAKEFILE_V)cp -a $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testG711/testG711 $(APP_PATH)
	$(AMBA_MAKEFILE_V)chmod +x $(APP_PATH)/testG711
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/mediaServer $@

clean:
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/liveMedia $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/groupsock $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/UsageEnvironment $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/BasicUsageEnvironment $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testProgs $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/mediaServer $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testG711 $@

	rm -rf obj/
	
depend:
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/liveMedia $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/groupsock $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/UsageEnvironment $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/BasicUsageEnvironment $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/testProgs $@
	$(AMBA_MAKEFILE_V)$(MAKE) -C $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/mediaServer $@

