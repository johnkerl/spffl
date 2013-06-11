# ================================================================
# Makefile for project spiff
# Automatically generated from "spiff.mki" at Tue Jan 22 14:57:42 2013

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
EXTRA_DEPS =
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir $(SPBIN)/spiff

mk_obj_dir:
	mkdir -p $(SPBIN)/sobjs

$(SPBIN)/sobjs/spiffmain.o:  ../classes/bit_t.h ../classes/cmdlineedmatops.h ../classes/cmdlinematops.h ../classes/cmdlineops.h ../classes/cmdlinevecops.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2npolyrat_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/f2polyrat_t.h ../classes/fpnpoly_t.h ../classes/fpnpolymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/fppolyrat_t.h ../classes/intmod_t.h ../classes/intrat_t.h ../classes/qpoly_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tstack.h ../classes/tvector.h ../utils/cmdinterp.h ../utils/count_bits.h ../utils/cyclopoly.h ../utils/f2linalg.h ../utils/f2npoly_factor.h ../utils/f2npoly_random.h ../utils/f2npoly_totient.h ../utils/f2npolymod_random.h ../utils/f2npolymod_units.h ../utils/f2pmlinalg.h ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/f2poly_totient.h ../utils/f2polymod_convert.h ../utils/f2polymod_random.h ../utils/f2polymod_units.h ../utils/fp_units.h ../utils/fplinalg.h ../utils/fppoly_factor.h ../utils/fppoly_random.h ../utils/fppoly_totient.h ../utils/fppolymod_random.h ../utils/int_factor.h ../utils/int_gcd.h ../utils/int_random.h ../utils/int_totient.h ../utils/intfc.h ../utils/intmod_random.h ../utils/isprime.h ../utils/linescan.h ../utils/log2.h ../utils/qff.h ../utils/sp_list_elts.h ../utils/spminchar.h ../utils/tokenize.h spiffmain.cpp
	g++ -Wall -O2 $(COMPILE_FLAGS)  spiffmain.cpp -o $(SPBIN)/sobjs/spiffmain.o

$(SPBIN)/sobjs/cmdinterp.o:  ../utils/cmdinterp.cpp ../utils/tokenize.h
	g++ -Wall -O2 $(COMPILE_FLAGS)  ../utils/cmdinterp.cpp -o $(SPBIN)/sobjs/cmdinterp.o

OBJS = \
	$(SPBIN)/sobjs/spiffmain.o \
	$(SPBIN)/sobjs/cmdinterp.o

$(SPBIN)/spiff: $(OBJS) $(EXTRA_DEPS)
	g++ -L$(SPBIN)/dynamic -L$(SPBIN) $(OBJS) -o $(SPBIN)/spiff $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f $(SPBIN)/spiff
