# ================================================================
# Makefile for project fpelladd
# Automatically generated from "fpelladd.mki" at Tue Jan 22 14:48:52 2013

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

build: mk_obj_dir ./fpelladd

mk_obj_dir:
	mkdir -p ./fpelladd_objs

./fpelladd_objs/fpelladd.o:  /home/kerl/bin/sp/inc/bit_matrix_t.h /home/kerl/bin/sp/inc/bit_t.h /home/kerl/bin/sp/inc/bit_vector_t.h /home/kerl/bin/sp/inc/cmdinterp.h /home/kerl/bin/sp/inc/cmdlineedmatops.h /home/kerl/bin/sp/inc/cmdlinematops.h /home/kerl/bin/sp/inc/cmdlineops.h /home/kerl/bin/sp/inc/cmdlinevecops.h /home/kerl/bin/sp/inc/cmps.h /home/kerl/bin/sp/inc/count_bits.h /home/kerl/bin/sp/inc/cyclopoly.h /home/kerl/bin/sp/inc/f2linalg.h /home/kerl/bin/sp/inc/f2npoly_factor.h /home/kerl/bin/sp/inc/f2npoly_random.h /home/kerl/bin/sp/inc/f2npoly_t.h /home/kerl/bin/sp/inc/f2npoly_totient.h /home/kerl/bin/sp/inc/f2npolymod_random.h /home/kerl/bin/sp/inc/f2npolymod_t.h /home/kerl/bin/sp/inc/f2npolymod_units.h /home/kerl/bin/sp/inc/f2npolyrat_t.h /home/kerl/bin/sp/inc/f2pmlinalg.h /home/kerl/bin/sp/inc/f2poly_factor.h /home/kerl/bin/sp/inc/f2poly_random.h /home/kerl/bin/sp/inc/f2poly_t.h /home/kerl/bin/sp/inc/f2poly_totient.h /home/kerl/bin/sp/inc/f2polymod_convert.h /home/kerl/bin/sp/inc/f2polymod_random.h /home/kerl/bin/sp/inc/f2polymod_t.h /home/kerl/bin/sp/inc/f2polymod_units.h /home/kerl/bin/sp/inc/f2polyrat_t.h /home/kerl/bin/sp/inc/fp_scan_tuples.h /home/kerl/bin/sp/inc/fp_units.h /home/kerl/bin/sp/inc/fplinalg.h /home/kerl/bin/sp/inc/fpnpoly_t.h /home/kerl/bin/sp/inc/fpnpolymod_t.h /home/kerl/bin/sp/inc/fppoly_factor.h /home/kerl/bin/sp/inc/fppoly_random.h /home/kerl/bin/sp/inc/fppoly_t.h /home/kerl/bin/sp/inc/fppoly_totient.h /home/kerl/bin/sp/inc/fppolymod_random.h /home/kerl/bin/sp/inc/fppolymod_t.h /home/kerl/bin/sp/inc/fppolyrat_t.h /home/kerl/bin/sp/inc/ft_scan_tuples.h /home/kerl/bin/sp/inc/int_factor.h /home/kerl/bin/sp/inc/int_gcd.h /home/kerl/bin/sp/inc/int_power.h /home/kerl/bin/sp/inc/int_random.h /home/kerl/bin/sp/inc/int_sqrt.h /home/kerl/bin/sp/inc/int_totient.h /home/kerl/bin/sp/inc/intfc.h /home/kerl/bin/sp/inc/intmod_random.h /home/kerl/bin/sp/inc/intmod_t.h /home/kerl/bin/sp/inc/intrat_t.h /home/kerl/bin/sp/inc/isprime.h /home/kerl/bin/sp/inc/libspffl.h /home/kerl/bin/sp/inc/linescan.h /home/kerl/bin/sp/inc/log10.h /home/kerl/bin/sp/inc/log2.h /home/kerl/bin/sp/inc/moebius.h /home/kerl/bin/sp/inc/msb_table.h /home/kerl/bin/sp/inc/primes16.h /home/kerl/bin/sp/inc/psdes.h /home/kerl/bin/sp/inc/qff.h /home/kerl/bin/sp/inc/qpoly_t.h /home/kerl/bin/sp/inc/rsstring_t.h /home/kerl/bin/sp/inc/sp_list_elts.h /home/kerl/bin/sp/inc/spminchar.h /home/kerl/bin/sp/inc/tfacinfo.h /home/kerl/bin/sp/inc/tmatrix.h /home/kerl/bin/sp/inc/tmvpoly.h /home/kerl/bin/sp/inc/tmvpolyscan.h /home/kerl/bin/sp/inc/tmvrat.h /home/kerl/bin/sp/inc/tmvratscan.h /home/kerl/bin/sp/inc/tokenize.h /home/kerl/bin/sp/inc/tstack.h /home/kerl/bin/sp/inc/tvector.h fpelladd.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  fpelladd.cpp -o ./fpelladd_objs/fpelladd.o

OBJS = \
	./fpelladd_objs/fpelladd.o

./fpelladd: $(OBJS) $(EXTRA_DEPS)
	g++ -L$(SPBIN)/static $(OBJS) -o ./fpelladd $(LINK_FLAGS)

install: build
	cp ./fpelladd $HOME/bin/sp

clean:
	-@rm -f $(OBJS)
	-@rm -f ./fpelladd
