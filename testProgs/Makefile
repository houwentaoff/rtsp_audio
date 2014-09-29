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
MODULE_NAME		:= testProgs

export AMBABUILD_TOPDIR

INCLUDES = -I../UsageEnvironment/include -I../groupsock/include \
		-I../liveMedia/include -I../BasicUsageEnvironment/include
# ccz +:
-include $(AMBABUILD_TOPDIR)/.config
-include $(AMBABUILD_TOPDIR)/build/app/common.mk
-include $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/config.mk

RTSP_PATH		= $(APP_PATH)

##################### Local dependences:
openRTSP.$(CPP):	playCommon.hh
playCommon.$(CPP):	playCommon.hh
playSIP.$(CPP):		playCommon.hh

MP3_STREAMER_OBJS = testMP3Streamer.$(OBJ)
MP3_RECEIVER_OBJS = testMP3Receiver.$(OBJ)
RELAY_OBJS = testRelay.$(OBJ)
MPEG_1OR2_SPLITTER_OBJS = testMPEG1or2Splitter.$(OBJ)
MPEG_1OR2_VIDEO_STREAMER_OBJS = testMPEG1or2VideoStreamer.$(OBJ)
MPEG_1OR2_VIDEO_RECEIVER_OBJS = testMPEG1or2VideoReceiver.$(OBJ)
MPEG_1OR2_AUDIO_VIDEO_STREAMER_OBJS = testMPEG1or2AudioVideoStreamer.$(OBJ)
MPEG2_TRANSPORT_STREAMER_OBJS = testMPEG2TransportStreamer.$(OBJ)
MPEG4_VIDEO_STREAMER_OBJS = testMPEG4VideoStreamer.$(OBJ)
DV_VIDEO_STREAMER_OBJS = testDVVideoStreamer.$(OBJ)
WAV_AUDIO_STREAMER_OBJS = testWAVAudioStreamer.$(OBJ)
AMR_AUDIO_STREAMER_OBJS	= testAMRAudioStreamer.$(OBJ)
ON_DEMAND_RTSP_SERVER_OBJS	= testOnDemandRTSPServer.$(OBJ)
VOB_STREAMER_OBJS	= vobStreamer.$(OBJ)
OPEN_RTSP_OBJS    = openRTSP.$(OBJ) playCommon.$(OBJ)
PLAY_SIP_OBJS     = playSIP.$(OBJ) playCommon.$(OBJ)
SAP_WATCH_OBJS = sapWatch.$(OBJ)
MPEG_1OR2_AUDIO_VIDEO_TO_DARWIN_OBJS = testMPEG1or2AudioVideoToDarwin.$(OBJ)
MPEG_4_VIDEO_TO_DARWIN_OBJS = testMPEG4VideoToDarwin.$(OBJ)
MPEG_1OR2_PROGRAM_TO_TRANSPORT_STREAM_OBJS = testMPEG1or2ProgramToTransportStream.$(OBJ)
MPEG2_TRANSPORT_STREAM_INDEXER_OBJS = MPEG2TransportStreamIndexer.$(OBJ)
MPEG2_TRANSPORT_STREAM_TRICK_PLAY_OBJS = testMPEG2TransportStreamTrickPlay.$(OBJ)
GSM_STREAMER_OBJS = testGSMStreamer.$(OBJ) testGSMEncoder.$(OBJ)
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
LIBS =	$(LOCAL_LIBS)
##################### End of Included LIBS:


##################### Executable apps:
testMP3Streamer$(EXE):	$(MP3_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MP3_STREAMER_OBJS) $(LIBS)
testMP3Receiver$(EXE):	$(MP3_RECEIVER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MP3_RECEIVER_OBJS) $(LIBS)
testRelay$(EXE):	$(RELAY_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(RELAY_OBJS) $(LIBS)
testMPEG1or2Splitter$(EXE):	$(MPEG_1OR2_SPLITTER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_1OR2_SPLITTER_OBJS) $(LIBS)
testMPEG1or2VideoStreamer$(EXE):	$(MPEG_1OR2_VIDEO_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_1OR2_VIDEO_STREAMER_OBJS) $(LIBS)
testMPEG1or2VideoReceiver$(EXE):	$(MPEG_1OR2_VIDEO_RECEIVER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_1OR2_VIDEO_RECEIVER_OBJS) $(LIBS)
testMPEG1or2AudioVideoStreamer$(EXE):	$(MPEG_1OR2_AUDIO_VIDEO_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_1OR2_AUDIO_VIDEO_STREAMER_OBJS) $(LIBS)
testMPEG2TransportStreamer$(EXE):	$(MPEG2_TRANSPORT_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG2_TRANSPORT_STREAMER_OBJS) $(LIBS)
testMPEG4VideoStreamer$(EXE):	$(MPEG4_VIDEO_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG4_VIDEO_STREAMER_OBJS) $(LIBS)
testDVVideoStreamer$(EXE):	$(DV_VIDEO_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(DV_VIDEO_STREAMER_OBJS) $(LIBS)
testWAVAudioStreamer$(EXE):	$(WAV_AUDIO_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(WAV_AUDIO_STREAMER_OBJS) $(LIBS)
testAMRAudioStreamer$(EXE):	$(AMR_AUDIO_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(AMR_AUDIO_STREAMER_OBJS) $(LIBS)
	@$(STRIP) testAMRAudioStreamer
testOnDemandRTSPServer$(EXE):	$(ON_DEMAND_RTSP_SERVER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(ON_DEMAND_RTSP_SERVER_OBJS) $(LIBS)
	@$(STRIP) testOnDemandRTSPServer
vobStreamer$(EXE):	$(VOB_STREAMER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(VOB_STREAMER_OBJS) $(LIBS)
openRTSP$(EXE):	$(OPEN_RTSP_OBJS) $(LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(OPEN_RTSP_OBJS) $(LIBS)
playSIP$(EXE):	$(PLAY_SIP_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(PLAY_SIP_OBJS) $(LIBS)
sapWatch$(EXE):	$(SAP_WATCH_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(SAP_WATCH_OBJS) $(LIBS)
testMPEG1or2AudioVideoToDarwin$(EXE):	$(MPEG_1OR2_AUDIO_VIDEO_TO_DARWIN_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_1OR2_AUDIO_VIDEO_TO_DARWIN_OBJS) $(LIBS)
testMPEG4VideoToDarwin$(EXE):	$(MPEG_4_VIDEO_TO_DARWIN_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_4_VIDEO_TO_DARWIN_OBJS) $(LIBS)
testMPEG1or2ProgramToTransportStream$(EXE):	$(MPEG_1OR2_PROGRAM_TO_TRANSPORT_STREAM_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG_1OR2_PROGRAM_TO_TRANSPORT_STREAM_OBJS) $(LIBS)
MPEG2TransportStreamIndexer$(EXE):	$(MPEG2_TRANSPORT_STREAM_INDEXER_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG2_TRANSPORT_STREAM_INDEXER_OBJS) $(LIBS)
testMPEG2TransportStreamTrickPlay$(EXE):	$(MPEG2_TRANSPORT_STREAM_TRICK_PLAY_OBJS) $(LOCAL_LIBS)
	@$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(MPEG2_TRANSPORT_STREAM_TRICK_PLAY_OBJS) $(LIBS)
testGSMStreamer$(EXE):	$(GSM_STREAMER_OBJS) $(LOCAL_LIBS)
	$(LINK)$(EXE_DIR)/$@ $(CONSOLE_LINK_OPTS) $(GSM_STREAMER_OBJS) $(LIBS)
##################### End of executable apps:


MULTICAST_STREAMER_APPS = testMP3Streamer$(EXE) testMPEG1or2VideoStreamer$(EXE) \
			testMPEG1or2AudioVideoStreamer$(EXE) testMPEG2TransportStreamer$(EXE) \
			testMPEG4VideoStreamer$(EXE) testDVVideoStreamer$(EXE) \
			testWAVAudioStreamer$(EXE) testAMRAudioStreamer$(EXE) vobStreamer$(EXE)
MULTICAST_RECEIVER_APPS = testMP3Receiver$(EXE) sapWatch$(EXE) \
			testMPEG1or2VideoReceiver$(EXE)
MULTICAST_MISC_APPS = testRelay$(EXE)
MULTICAST_APPS = $(MULTICAST_STREAMER_APPS) \
				$(MULTICAST_RECEIVER_APPS) \
				$(MULTICAST_MISC_APPS)

UNICAST_STREAMER_APPS = testOnDemandRTSPServer$(EXE) testMPEG4VideoToDarwin$(EXE) \
			testMPEG1or2AudioVideoToDarwin$(EXE)
UNICAST_RECEIVER_APPS = openRTSP$(EXE) playSIP$(EXE)
UNICAST_APPS = $(UNICAST_STREAMER_APPS) \
				$(UNICAST_RECEIVER_APPS)

MISC_APPS = testMPEG1or2Splitter$(EXE) testMPEG1or2ProgramToTransportStream$(EXE) \
			MPEG2TransportStreamIndexer$(EXE) testMPEG2TransportStreamTrickPlay$(EXE)

ALL_APPS = $(MULTICAST_APPS) $(UNICAST_APPS) $(MISC_APPS)

MODULE_TARGETS = $(ALL_APPS)

EXE_DIR	=	.
$(EXE_DIR):
	@$(MKDIR) $(EXE_DIR)

-include $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/rules.mk

##### Any additional, platform-specific rules come here:
