
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 


#
# hma library description
#
libs += libhma.so
objs_libhma.so += libhma.o
#LDFLAGS_libhma.so += -llog

#libs += libhma.a
#objs_libhma.a += libhma.o

apps += test_hma
objs_test_hma += test.o
LDFLAGS_test_hma += -lhma


$(eval $(call build_doxygen_document,hma))

