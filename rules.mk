###############################################
#
# app/ipcam/rtsp/rules.mk
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


###############################################
#		rules
###############################################

.PHONY: prebuild_echo all clean

SRCS = *.cpp

all: prebuild_echo $(MODULE_TARGETS)

prebuild_echo:
	@echo '  [Build $(MODULE_NAME)]:'


clean:
	@echo '  [Clean $(MODULE_NAME)]:'
	@$(RM) *.$(OBJ) $(MODULE_TARGETS) core *.core *~ include/*~ .depend
	@$(RM) $(LIB_OBJS)
	@$(RM) $(AMBABUILD_TOPDIR)/app/ipcam/rtsp_audio/obj
	@$(RM) $(EXE_DIR)/$(MODULE_TARGETS)

###############################################
#		compile
###############################################

%.o: %.c
	@echo '    compiling $<...'
	@$(C_COMPILER) -c $(C_FLAGS) -o $@ $<

%.o: %.cpp
	@echo '    compiling $<...'
	@$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) -o $@ $<

$(MODULE_LIBS): $(LIB_OBJS) $(PLATFORM_SPECIFIC_LIB_OBJS)
	@$(LIBRARY_LINK) $@ $(LIBRARY_LINK_OPTS) $(LIB_OBJS)

depend:
	@$(CPLUSPLUS_COMPILER) $(CPLUSPLUS_FLAGS) -MM $(SRCS) > .depend

-include .depend
