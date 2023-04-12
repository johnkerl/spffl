# ================================================================
# Makefile for project f2pmop
# Automatically generated from "f2pmop.mki" at Fri Nov 26 21:54:54 2004

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

build: mk_obj_dir $(SPBIN)/f2pmop

mk_obj_dir:
	mkdir -p $(SPBIN)/sobjs

$(SPBIN)/sobjs/f2pmop.o:  ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../classes/cmdlineops.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/f2polyrat_t.h ../classes/fpnpoly_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/fppolyrat_t.h ../classes/intmod_t.h ../classes/intrat_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tstack.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2pmlinalg.h ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/f2polymod_convert.h ../utils/f2polymod_random.h ../utils/f2polymod_units.h ../utils/fppoly_factor.h ../utils/fppoly_random.h ../utils/fppolymod_random.h ../utils/int_factor.h ../utils/int_gcd.h ../utils/int_random.h ../utils/int_totient.h ../utils/intfc.h ../utils/intmod_random.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h f2pmop.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  f2pmop.cpp -o $(SPBIN)/sobjs/f2pmop.o

OBJS = \
	$(SPBIN)/sobjs/f2pmop.o

$(SPBIN)/f2pmop: $(OBJS)
	g++ -L$(SPBIN)/dynamic $(OBJS) -o $(SPBIN)/f2pmop $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f $(SPBIN)/f2pmop
