# ================================================================
# Makefile for project ftelladd
# Automatically generated from "ftelladd.mki" at Sun Apr  2 00:23:16 2023

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
EXTRA_DEPS =
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir ./ftelladd

mk_obj_dir:
	mkdir -p ./ftelladd_objs

./ftelladd_objs/ftelladd.o:  /Users/johnkerl/bin/sp/inc/bit_matrix_t.h /Users/johnkerl/bin/sp/inc/bit_t.h /Users/johnkerl/bin/sp/inc/bit_vector_t.h /Users/johnkerl/bin/sp/inc/cmdinterp.h /Users/johnkerl/bin/sp/inc/cmdlineedmatops.h /Users/johnkerl/bin/sp/inc/cmdlinematops.h /Users/johnkerl/bin/sp/inc/cmdlineops.h /Users/johnkerl/bin/sp/inc/cmdlinevecops.h /Users/johnkerl/bin/sp/inc/cmps.h /Users/johnkerl/bin/sp/inc/count_bits.h /Users/johnkerl/bin/sp/inc/cyclopoly.h /Users/johnkerl/bin/sp/inc/f2linalg.h /Users/johnkerl/bin/sp/inc/f2npoly_factor.h /Users/johnkerl/bin/sp/inc/f2npoly_random.h /Users/johnkerl/bin/sp/inc/f2npoly_t.h /Users/johnkerl/bin/sp/inc/f2npoly_totient.h /Users/johnkerl/bin/sp/inc/f2npolymod_random.h /Users/johnkerl/bin/sp/inc/f2npolymod_t.h /Users/johnkerl/bin/sp/inc/f2npolymod_units.h /Users/johnkerl/bin/sp/inc/f2npolyrat_t.h /Users/johnkerl/bin/sp/inc/f2pmlinalg.h /Users/johnkerl/bin/sp/inc/f2poly_factor.h /Users/johnkerl/bin/sp/inc/f2poly_random.h /Users/johnkerl/bin/sp/inc/f2poly_t.h /Users/johnkerl/bin/sp/inc/f2poly_totient.h /Users/johnkerl/bin/sp/inc/f2polymod_convert.h /Users/johnkerl/bin/sp/inc/f2polymod_random.h /Users/johnkerl/bin/sp/inc/f2polymod_t.h /Users/johnkerl/bin/sp/inc/f2polymod_units.h /Users/johnkerl/bin/sp/inc/f2polyrat_t.h /Users/johnkerl/bin/sp/inc/fp_scan_tuples.h /Users/johnkerl/bin/sp/inc/fp_units.h /Users/johnkerl/bin/sp/inc/fplinalg.h /Users/johnkerl/bin/sp/inc/fpnpoly_t.h /Users/johnkerl/bin/sp/inc/fpnpolymod_t.h /Users/johnkerl/bin/sp/inc/fppoly_factor.h /Users/johnkerl/bin/sp/inc/fppoly_random.h /Users/johnkerl/bin/sp/inc/fppoly_t.h /Users/johnkerl/bin/sp/inc/fppoly_totient.h /Users/johnkerl/bin/sp/inc/fppolymod_random.h /Users/johnkerl/bin/sp/inc/fppolymod_t.h /Users/johnkerl/bin/sp/inc/fppolyrat_t.h /Users/johnkerl/bin/sp/inc/ft_scan_tuples.h /Users/johnkerl/bin/sp/inc/int_factor.h /Users/johnkerl/bin/sp/inc/int_gcd.h /Users/johnkerl/bin/sp/inc/int_power.h /Users/johnkerl/bin/sp/inc/int_random.h /Users/johnkerl/bin/sp/inc/int_sqrt.h /Users/johnkerl/bin/sp/inc/int_totient.h /Users/johnkerl/bin/sp/inc/intfc.h /Users/johnkerl/bin/sp/inc/intmod_random.h /Users/johnkerl/bin/sp/inc/intmod_t.h /Users/johnkerl/bin/sp/inc/intrat_t.h /Users/johnkerl/bin/sp/inc/isprime.h /Users/johnkerl/bin/sp/inc/libspffl.h /Users/johnkerl/bin/sp/inc/linescan.h /Users/johnkerl/bin/sp/inc/log10.h /Users/johnkerl/bin/sp/inc/log2.h /Users/johnkerl/bin/sp/inc/moebius.h /Users/johnkerl/bin/sp/inc/primes16.h /Users/johnkerl/bin/sp/inc/psdes.h /Users/johnkerl/bin/sp/inc/qff.h /Users/johnkerl/bin/sp/inc/qpoly_t.h /Users/johnkerl/bin/sp/inc/rsstring_t.h /Users/johnkerl/bin/sp/inc/sp_list_elts.h /Users/johnkerl/bin/sp/inc/spminchar.h /Users/johnkerl/bin/sp/inc/tfacinfo.h /Users/johnkerl/bin/sp/inc/tmatrix.h /Users/johnkerl/bin/sp/inc/tmvpoly.h /Users/johnkerl/bin/sp/inc/tmvpolyscan.h /Users/johnkerl/bin/sp/inc/tmvrat.h /Users/johnkerl/bin/sp/inc/tmvratscan.h /Users/johnkerl/bin/sp/inc/tokenize.h /Users/johnkerl/bin/sp/inc/tstack.h /Users/johnkerl/bin/sp/inc/tvector.h ftelladd.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  ftelladd.cpp -o ./ftelladd_objs/ftelladd.o

OBJS = \
	./ftelladd_objs/ftelladd.o

./ftelladd: $(OBJS) $(EXTRA_DEPS)
	g++ -L$(SPBIN)/dynamic $(OBJS) -o ./ftelladd $(LINK_FLAGS)

install: build
	cp ./ftelladd $HOME/bin/sp

clean:
	-@rm -f $(OBJS)
	-@rm -f ./ftelladd
