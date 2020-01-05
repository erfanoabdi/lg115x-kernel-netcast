
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2010 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 

WARNINGS = -Wextra -Wall -Wwrite-strings -Wstrict-prototypes \
           -Wmissing-prototypes -Wno-long-long -Wstrict-aliasing=2

CFLAGS+= -O2 -I$(TLSF_PATH) $(WARNINGS) 
CFLAGS+= -DTLSF_USE_LOCKS=0
#CFLAGS+= -DUSE_MMAP=1
#CFLAGS+= -DUSE_SBRK=1

# CFLAGS+=-ftest-coverage -fprofile-arcs
CC=gcc

all: tlsf.o

tlsf.o: tlsf.h tlsf.c Makefile

clean:
	$(RM) -rf *.o *~ *.c.gcov *.gcda *.gcno

indent:
	indent -kr -l120 -br -ce -npsl -nut -i4 *.[hc]

