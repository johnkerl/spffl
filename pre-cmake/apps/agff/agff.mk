# ================================================================
# Makefile for project agff
# Automatically generated from "agff.mki" at Thu Mar 10 16:48:57 2005

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================

SPBIN=$(HOME)/bin/sp

INCLUDE_DIRS = -I$(SPBIN)/inc
LIB_DIRS =
DEFINES = -DF2POLY_SMALL
MISC_CFLAGS =
MISC_LFLAGS = -lspfflf
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir ./agff

mk_obj_dir:
	mkdir -p ./agff_objs

./agff_objs/agff.o:  /ud/matgrd/kerl/bin/sp/inc/bit_t.h /ud/matgrd/kerl/bin/sp/inc/count_bits.h /ud/matgrd/kerl/bin/sp/inc/f2npoly_t.h /ud/matgrd/kerl/bin/sp/inc/f2npolymod_t.h /ud/matgrd/kerl/bin/sp/inc/f2poly_factor.h /ud/matgrd/kerl/bin/sp/inc/f2poly_t.h /ud/matgrd/kerl/bin/sp/inc/f2polymod_t.h /ud/matgrd/kerl/bin/sp/inc/fppoly_factor.h /ud/matgrd/kerl/bin/sp/inc/fppoly_t.h /ud/matgrd/kerl/bin/sp/inc/fppolymod_t.h /ud/matgrd/kerl/bin/sp/inc/int_power.h /ud/matgrd/kerl/bin/sp/inc/int_totient.h /ud/matgrd/kerl/bin/sp/inc/intfc.h /ud/matgrd/kerl/bin/sp/inc/intmod_t.h /ud/matgrd/kerl/bin/sp/inc/linescan.h /ud/matgrd/kerl/bin/sp/inc/log2.h /ud/matgrd/kerl/bin/sp/inc/sp_list_elts.h /ud/matgrd/kerl/bin/sp/inc/tfacinfo.h /ud/matgrd/kerl/bin/sp/inc/tmatrix.h /ud/matgrd/kerl/bin/sp/inc/tmvpoly.h /ud/matgrd/kerl/bin/sp/inc/tmvpolyscan.h /ud/matgrd/kerl/bin/sp/inc/tmvrat.h /ud/matgrd/kerl/bin/sp/inc/tmvratscan.h /ud/matgrd/kerl/bin/sp/inc/tokenize.h /ud/matgrd/kerl/bin/sp/inc/tvector.h agff.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  agff.cpp -o ./agff_objs/agff.o

OBJS = \
	./agff_objs/agff.o

./agff: $(OBJS)
	g++ -L$(SPBIN)/static $(OBJS) -o ./agff $(LINK_FLAGS)

install: build
	cp ./agff $HOME/bin/sp

clean:
	-@rm -f $(OBJS)
	-@rm -f ./agff
