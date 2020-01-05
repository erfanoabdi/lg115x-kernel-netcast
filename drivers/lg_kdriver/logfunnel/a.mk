
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 


libs += liblog.so
objs_liblog.so += log.o
LDFLAGS_liblog.so += -lpthread

apps += logpiped
objs_logpiped += logpiped.o
LDFLAGS_logpiped += -llog

apps += test_logfunnel
objs_test_logfunnel += test.o
LDFLAGS_test_logfunnel += -llog

#apps += buffer2text

