# ================================================================
# Makefile for project fppmchart
# Automatically generated from "fppmchart.mki" at Sun Nov 14 22:46:16 2004

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================


INCLUDE_DIRS = -I../classes -I../utils
LIB_DIRS =
DEFINES =
MISC_CFLAGS =
MISC_LFLAGS =
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir ../../../bin/sp/fppmchart

mk_obj_dir:
	mkdir -p ../../../bin/sp/tools_objs

../../../bin/sp/tools_objs/fppmchart.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/fppoly_factor.h ../utils/intfc.h ../utils/linescan.h ../utils/log10.h ../utils/log2.h ../utils/moebius.h ../utils/spminchar.h ../utils/tokenize.h fppmchart.cpp
	gcc -Wall -Werror -O2 $(COMPILE_FLAGS)  fppmchart.cpp -o ../../../bin/sp/tools_objs/fppmchart.o

OBJS = \
	../../../bin/sp/tools_objs/fppmchart.o

../../../bin/sp/fppmchart: $(OBJS)
	gcc -L../../../bin/sp -lspffl -lstdc++ $(OBJS) -o ../../../bin/sp/fppmchart $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f ../../../bin/sp/fppmchart
