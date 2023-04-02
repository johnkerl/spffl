# ================================================================
# Makefile for project f2pmchart
# Automatically generated from "f2pmchart.mki" at Sun Apr  2 00:20:43 2023

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================

SPBIN=$(HOME)/bin/sp

INCLUDE_DIRS = -I../classes -I../utils
LIB_DIRS =
DEFINES = -DF2POLY_SMALL
MISC_CFLAGS =
MISC_LFLAGS = -lspfflf
EXTRA_DEPS =
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir $(SPBIN)/f2pmchart

mk_obj_dir:
	mkdir -p $(SPBIN)/fobjs

$(SPBIN)/fobjs/f2pmchart.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.h ../utils/f2polymod_units.h ../utils/int_gcd.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log10.h ../utils/log2.h ../utils/moebius.h ../utils/spminchar.h ../utils/tokenize.h f2pmchart.cpp
	g++ -Wall -O2 $(COMPILE_FLAGS)  f2pmchart.cpp -o $(SPBIN)/fobjs/f2pmchart.o

OBJS = \
	$(SPBIN)/fobjs/f2pmchart.o

$(SPBIN)/f2pmchart: $(OBJS) $(EXTRA_DEPS)
	g++ -L$(SPBIN)/dynamic $(OBJS) -o $(SPBIN)/f2pmchart $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f $(SPBIN)/f2pmchart
