# ================================================================
# Makefile for project single
# Automatically generated from "single.mki" at Thu Jun  9 21:46:31 2005

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================

SPBIN=$(HOME)/bin/sp

INCLUDE_DIRS = -I$(SPBIN)/inc
LIB_DIRS =
DEFINES =
MISC_CFLAGS =
MISC_LFLAGS = -lspffl
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir ./single

mk_obj_dir:
	mkdir -p $(SPBIN)/sobjs

$(SPBIN)/sobjs/single.o:  /u5/kerl/bin/sp/inc/bit_matrix_t.h /u5/kerl/bin/sp/inc/bit_t.h /u5/kerl/bin/sp/inc/bit_vector_t.h /u5/kerl/bin/sp/inc/cmdinterp.h /u5/kerl/bin/sp/inc/cmdlineedmatops.h /u5/kerl/bin/sp/inc/cmdlinematops.h /u5/kerl/bin/sp/inc/cmdlineops.h /u5/kerl/bin/sp/inc/cmdlinevecops.h /u5/kerl/bin/sp/inc/cmps.h /u5/kerl/bin/sp/inc/count_bits.h /u5/kerl/bin/sp/inc/cyclopoly.h /u5/kerl/bin/sp/inc/f2ipoly_factor.h /u5/kerl/bin/sp/inc/f2ipoly_random.h /u5/kerl/bin/sp/inc/f2ipoly_t.h /u5/kerl/bin/sp/inc/f2ipolymod_random.h /u5/kerl/bin/sp/inc/f2ipolymod_t.h /u5/kerl/bin/sp/inc/f2ipolyrat_t.h /u5/kerl/bin/sp/inc/f2linalg.h /u5/kerl/bin/sp/inc/f2npoly_factor.h /u5/kerl/bin/sp/inc/f2npoly_random.h /u5/kerl/bin/sp/inc/f2npoly_t.h /u5/kerl/bin/sp/inc/f2npoly_totient.h /u5/kerl/bin/sp/inc/f2npolymod_random.h /u5/kerl/bin/sp/inc/f2npolymod_t.h /u5/kerl/bin/sp/inc/f2npolymod_units.h /u5/kerl/bin/sp/inc/f2npolyrat_t.h /u5/kerl/bin/sp/inc/f2pmlinalg.h /u5/kerl/bin/sp/inc/f2poly_factor.h /u5/kerl/bin/sp/inc/f2poly_random.h /u5/kerl/bin/sp/inc/f2poly_t.h /u5/kerl/bin/sp/inc/f2poly_totient.h /u5/kerl/bin/sp/inc/f2polymod_convert.h /u5/kerl/bin/sp/inc/f2polymod_random.h /u5/kerl/bin/sp/inc/f2polymod_t.h /u5/kerl/bin/sp/inc/f2polymod_units.h /u5/kerl/bin/sp/inc/f2polyrat_t.h /u5/kerl/bin/sp/inc/fp_scan_tuples.h /u5/kerl/bin/sp/inc/fp_units.h /u5/kerl/bin/sp/inc/fplinalg.h /u5/kerl/bin/sp/inc/fpnpoly_t.h /u5/kerl/bin/sp/inc/fpnpolymod_t.h /u5/kerl/bin/sp/inc/fppoly_factor.h /u5/kerl/bin/sp/inc/fppoly_random.h /u5/kerl/bin/sp/inc/fppoly_t.h /u5/kerl/bin/sp/inc/fppoly_totient.h /u5/kerl/bin/sp/inc/fppolymod_random.h /u5/kerl/bin/sp/inc/fppolymod_t.h /u5/kerl/bin/sp/inc/fppolyrat_t.h /u5/kerl/bin/sp/inc/fpscantuples.h /u5/kerl/bin/sp/inc/ft_scan_tuples.h /u5/kerl/bin/sp/inc/int_factor.h /u5/kerl/bin/sp/inc/int_gcd.h /u5/kerl/bin/sp/inc/int_power.h /u5/kerl/bin/sp/inc/int_random.h /u5/kerl/bin/sp/inc/int_sqrt.h /u5/kerl/bin/sp/inc/int_totient.h /u5/kerl/bin/sp/inc/intfc.h /u5/kerl/bin/sp/inc/intmod_random.h /u5/kerl/bin/sp/inc/intmod_t.h /u5/kerl/bin/sp/inc/intrat_t.h /u5/kerl/bin/sp/inc/isprime.h /u5/kerl/bin/sp/inc/libspffl.h /u5/kerl/bin/sp/inc/linescan.h /u5/kerl/bin/sp/inc/log10.h /u5/kerl/bin/sp/inc/log2.h /u5/kerl/bin/sp/inc/moebius.h /u5/kerl/bin/sp/inc/msb_table.h /u5/kerl/bin/sp/inc/primes16.h /u5/kerl/bin/sp/inc/psdes.h /u5/kerl/bin/sp/inc/qff.h /u5/kerl/bin/sp/inc/qpoly_t.h /u5/kerl/bin/sp/inc/rsstring_t.h /u5/kerl/bin/sp/inc/sp_list_elts.h /u5/kerl/bin/sp/inc/spminchar.h /u5/kerl/bin/sp/inc/tfacinfo.h /u5/kerl/bin/sp/inc/tmatrix.h /u5/kerl/bin/sp/inc/tmvpoly.h /u5/kerl/bin/sp/inc/tmvpolyscan.h /u5/kerl/bin/sp/inc/tmvrat.h /u5/kerl/bin/sp/inc/tmvratscan.h /u5/kerl/bin/sp/inc/tokenize.h /u5/kerl/bin/sp/inc/tstack.h /u5/kerl/bin/sp/inc/tvector.h single.cpp
	g++ -Wall -Werror -O2 $(COMPILE_FLAGS)  single.cpp -o $(SPBIN)/sobjs/single.o

OBJS = \
	$(SPBIN)/sobjs/single.o

./single: $(OBJS)
	g++ -L$(SPBIN)/dynamic $(OBJS) -o ./single $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f ./single
