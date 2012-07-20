# ================================================================
# Makefile for project zop
# Automatically generated from "zop.mki" at Fri Nov 26 21:58:33 2004

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================

SPBIN=$(HOME)/bin/sp

INCLUDE_DIRS = -I../classes -I../utils
LIB_DIRS =
DEFINES =
MISC_CFLAGS =
MISC_LFLAGS = -lspffl
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir $(SPBIN)/zop

mk_obj_dir:
	mkdir -p $(SPBIN)/sobjs

$(SPBIN)/sobjs/zop.o:  ../classes/cmdlineops.h ../classes/tstack.h zop.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  zop.cpp -o $(SPBIN)/sobjs/zop.o

OBJS = \
	$(SPBIN)/sobjs/zop.o

$(SPBIN)/zop: $(OBJS)
	g++ -L$(SPBIN)/dynamic $(OBJS) -o $(SPBIN)/zop $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f $(SPBIN)/zop
