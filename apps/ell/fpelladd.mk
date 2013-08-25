# ================================================================
# Makefile for project fpelladd
# Automatically generated from "fpelladd.mki" at Fri Mar 25 23:24:05 2005

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

build: mk_obj_dir ./fpelladd

mk_obj_dir:
	mkdir -p ./fpelladd_objs

./fpelladd_objs/fpelladd.o:  /ud/matgrd/kerl/bin/sp/inc/bit_matrix_t.h /ud/matgrd/kerl/bin/sp/inc/bit_t.h /ud/matgrd/kerl/bin/sp/inc/bit_vector_t.h /ud/matgrd/kerl/bin/sp/inc/cmdinterp.h /ud/matgrd/kerl/bin/sp/inc/cmdlineedmatops.h /ud/matgrd/kerl/bin/sp/inc/cmdlinematops.h /ud/matgrd/kerl/bin/sp/inc/cmdlineops.h /ud/matgrd/kerl/bin/sp/inc/cmdlinevecops.h /ud/matgrd/kerl/bin/sp/inc/cmps.h /ud/matgrd/kerl/bin/sp/inc/count_bits.h /ud/matgrd/kerl/bin/sp/inc/cyclopoly.h /ud/matgrd/kerl/bin/sp/inc/f2ipoly_factor.h /ud/matgrd/kerl/bin/sp/inc/f2ipoly_random.h /ud/matgrd/kerl/bin/sp/inc/f2ipoly_t.h /ud/matgrd/kerl/bin/sp/inc/f2ipolymod_random.h /ud/matgrd/kerl/bin/sp/inc/f2ipolymod_t.h /ud/matgrd/kerl/bin/sp/inc/f2ipolyrat_t.h /ud/matgrd/kerl/bin/sp/inc/f2linalg.h /ud/matgrd/kerl/bin/sp/inc/f2npoly_factor.h /ud/matgrd/kerl/bin/sp/inc/f2npoly_random.h /ud/matgrd/kerl/bin/sp/inc/f2npoly_t.h /ud/matgrd/kerl/bin/sp/inc/f2npoly_totient.h /ud/matgrd/kerl/bin/sp/inc/f2npolymod_random.h /ud/matgrd/kerl/bin/sp/inc/f2npolymod_t.h /ud/matgrd/kerl/bin/sp/inc/f2npolymod_units.h /ud/matgrd/kerl/bin/sp/inc/f2npolyrat_t.h /ud/matgrd/kerl/bin/sp/inc/f2pmlinalg.h /ud/matgrd/kerl/bin/sp/inc/f2poly_factor.h /ud/matgrd/kerl/bin/sp/inc/f2poly_random.h /ud/matgrd/kerl/bin/sp/inc/f2poly_t.h /ud/matgrd/kerl/bin/sp/inc/f2poly_totient.h /ud/matgrd/kerl/bin/sp/inc/f2polymod_convert.h /ud/matgrd/kerl/bin/sp/inc/f2polymod_random.h /ud/matgrd/kerl/bin/sp/inc/f2polymod_t.h /ud/matgrd/kerl/bin/sp/inc/f2polymod_units.h /ud/matgrd/kerl/bin/sp/inc/f2polyrat_t.h /ud/matgrd/kerl/bin/sp/inc/fp_scan_tuples.h /ud/matgrd/kerl/bin/sp/inc/fp_units.h /ud/matgrd/kerl/bin/sp/inc/fplinalg.h /ud/matgrd/kerl/bin/sp/inc/fpnpoly_t.h /ud/matgrd/kerl/bin/sp/inc/fpnpolymod_t.h /ud/matgrd/kerl/bin/sp/inc/fppoly_factor.h /ud/matgrd/kerl/bin/sp/inc/fppoly_random.h /ud/matgrd/kerl/bin/sp/inc/fppoly_t.h /ud/matgrd/kerl/bin/sp/inc/fppoly_totient.h /ud/matgrd/kerl/bin/sp/inc/fppolymod_random.h /ud/matgrd/kerl/bin/sp/inc/fppolymod_t.h /ud/matgrd/kerl/bin/sp/inc/fppolyrat_t.h /ud/matgrd/kerl/bin/sp/inc/fpscantuples.h /ud/matgrd/kerl/bin/sp/inc/ft_scan_tuples.h /ud/matgrd/kerl/bin/sp/inc/int_factor.h /ud/matgrd/kerl/bin/sp/inc/int_gcd.h /ud/matgrd/kerl/bin/sp/inc/int_power.h /ud/matgrd/kerl/bin/sp/inc/int_random.h /ud/matgrd/kerl/bin/sp/inc/int_sqrt.h /ud/matgrd/kerl/bin/sp/inc/int_totient.h /ud/matgrd/kerl/bin/sp/inc/intfc.h /ud/matgrd/kerl/bin/sp/inc/intmod_random.h /ud/matgrd/kerl/bin/sp/inc/intmod_t.h /ud/matgrd/kerl/bin/sp/inc/intrat_t.h /ud/matgrd/kerl/bin/sp/inc/isprime.h /ud/matgrd/kerl/bin/sp/inc/libspffl.h /ud/matgrd/kerl/bin/sp/inc/linescan.h /ud/matgrd/kerl/bin/sp/inc/log10.h /ud/matgrd/kerl/bin/sp/inc/log2.h /ud/matgrd/kerl/bin/sp/inc/moebius.h /ud/matgrd/kerl/bin/sp/inc/msb_table.h /ud/matgrd/kerl/bin/sp/inc/primes16.h /ud/matgrd/kerl/bin/sp/inc/psdes.h /ud/matgrd/kerl/bin/sp/inc/qff.h /ud/matgrd/kerl/bin/sp/inc/qpoly_t.h /ud/matgrd/kerl/bin/sp/inc/rsstring_t.h /ud/matgrd/kerl/bin/sp/inc/sp_list_elts.h /ud/matgrd/kerl/bin/sp/inc/spminchar.h /ud/matgrd/kerl/bin/sp/inc/tfacinfo.h /ud/matgrd/kerl/bin/sp/inc/tmatrix.h /ud/matgrd/kerl/bin/sp/inc/tmvpoly.h /ud/matgrd/kerl/bin/sp/inc/tmvpolyscan.h /ud/matgrd/kerl/bin/sp/inc/tmvrat.h /ud/matgrd/kerl/bin/sp/inc/tmvratscan.h /ud/matgrd/kerl/bin/sp/inc/tokenize.h /ud/matgrd/kerl/bin/sp/inc/tstack.h /ud/matgrd/kerl/bin/sp/inc/tvector.h fpelladd.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  fpelladd.cpp -o ./fpelladd_objs/fpelladd.o

OBJS = \
	./fpelladd_objs/fpelladd.o

./fpelladd: $(OBJS)
	g++ -L$(SPBIN)/static $(OBJS) -o ./fpelladd $(LINK_FLAGS)

install: build
	cp ./fpelladd $HOME/bin/sp

clean:
	-@rm -f $(OBJS)
	-@rm -f ./fpelladd
