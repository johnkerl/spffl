# ================================================================
# Makefile for project libspffl.so
# Automatically generated from "libspffl.so.mki" at Sat Apr  1 18:14:35 2023

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================

SPBIN=$(HOME)/bin/sp

INCLUDE_DIRS = -I../classes -I../utils
LIB_DIRS =
DEFINES =
MISC_CFLAGS =
MISC_LFLAGS =
EXTRA_DEPS =
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir $(SPBIN)/dynamic/libspffl.so

mk_obj_dir:
	mkdir -p $(SPBIN)/sobjs

$(SPBIN)/sobjs/intrat_t.o:  ../classes/cmps.h ../classes/intrat_t.cpp ../classes/intrat_t.h ../utils/int_gcd.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/intrat_t.cpp -o $(SPBIN)/sobjs/intrat_t.o

$(SPBIN)/sobjs/intmod_t.o:  ../classes/intmod_t.cpp ../classes/intmod_t.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/intmod_t.cpp -o $(SPBIN)/sobjs/intmod_t.o

$(SPBIN)/sobjs/bit_t.o:  ../classes/bit_t.cpp ../classes/bit_t.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/bit_t.cpp -o $(SPBIN)/sobjs/bit_t.o

$(SPBIN)/sobjs/bit_vector_t.o:  ../classes/bit_t.h ../classes/bit_vector_t.cpp ../classes/bit_vector_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/bit_vector_t.cpp -o $(SPBIN)/sobjs/bit_vector_t.o

$(SPBIN)/sobjs/bit_matrix_t.o:  ../classes/bit_matrix_t.cpp ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../utils/linescan.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/bit_matrix_t.cpp -o $(SPBIN)/sobjs/bit_matrix_t.o

$(SPBIN)/sobjs/f2poly_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2poly_t.cpp ../classes/f2poly_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/f2poly_t.cpp -o $(SPBIN)/sobjs/f2poly_t.o

$(SPBIN)/sobjs/f2polymod_t.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.cpp ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/f2polymod_t.cpp -o $(SPBIN)/sobjs/f2polymod_t.o

$(SPBIN)/sobjs/f2polyrat_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2poly_t.h ../classes/f2polyrat_t.cpp ../classes/f2polyrat_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/f2polyrat_t.cpp -o $(SPBIN)/sobjs/f2polyrat_t.o

$(SPBIN)/sobjs/f2npoly_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2npoly_t.cpp ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/f2npoly_t.cpp -o $(SPBIN)/sobjs/f2npoly_t.o

$(SPBIN)/sobjs/f2npolymod_t.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.cpp ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/f2npolymod_t.cpp -o $(SPBIN)/sobjs/f2npolymod_t.o

$(SPBIN)/sobjs/f2npolyrat_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2npoly_t.h ../classes/f2npolyrat_t.cpp ../classes/f2npolyrat_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/f2npolyrat_t.cpp -o $(SPBIN)/sobjs/f2npolyrat_t.o

$(SPBIN)/sobjs/fppoly_t.o:  ../classes/cmps.h ../classes/fppoly_t.cpp ../classes/fppoly_t.h ../classes/intmod_t.h ../classes/rsstring_t.h ../utils/int_totient.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/fppoly_t.cpp -o $(SPBIN)/sobjs/fppoly_t.o

$(SPBIN)/sobjs/fppolymod_t.o:  ../classes/fppoly_t.h ../classes/fppolymod_t.cpp ../classes/fppolymod_t.h ../classes/intmod_t.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/fppolymod_t.cpp -o $(SPBIN)/sobjs/fppolymod_t.o

$(SPBIN)/sobjs/fppolyrat_t.o:  ../classes/cmps.h ../classes/fppoly_t.h ../classes/fppolyrat_t.cpp ../classes/fppolyrat_t.h ../classes/intmod_t.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/fppolyrat_t.cpp -o $(SPBIN)/sobjs/fppolyrat_t.o

$(SPBIN)/sobjs/fpnpoly_t.o:  ../classes/cmps.h ../classes/fpnpoly_t.cpp ../classes/fpnpoly_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../utils/int_totient.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/fpnpoly_t.cpp -o $(SPBIN)/sobjs/fpnpoly_t.o

$(SPBIN)/sobjs/fpnpolymod_t.o:  ../classes/fpnpoly_t.h ../classes/fpnpolymod_t.cpp ../classes/fpnpolymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/fpnpolymod_t.cpp -o $(SPBIN)/sobjs/fpnpolymod_t.o

$(SPBIN)/sobjs/linescan.o:  ../utils/linescan.cpp ../utils/linescan.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/linescan.cpp -o $(SPBIN)/sobjs/linescan.o

$(SPBIN)/sobjs/log2.o:  ../utils/intfc.h ../utils/log2.cpp ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/log2.cpp -o $(SPBIN)/sobjs/log2.o

$(SPBIN)/sobjs/log10.o:  ../utils/intfc.h ../utils/log10.cpp ../utils/log10.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/log10.cpp -o $(SPBIN)/sobjs/log10.o

$(SPBIN)/sobjs/count_bits.o:  ../utils/count_bits.cpp ../utils/count_bits.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/count_bits.cpp -o $(SPBIN)/sobjs/count_bits.o

$(SPBIN)/sobjs/int_gcd.o:  ../utils/int_gcd.cpp ../utils/int_gcd.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/int_gcd.cpp -o $(SPBIN)/sobjs/int_gcd.o

$(SPBIN)/sobjs/int_totient.o:  ../utils/int_gcd.h ../utils/int_totient.cpp ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/int_totient.cpp -o $(SPBIN)/sobjs/int_totient.o

$(SPBIN)/sobjs/int_power.o:  ../utils/int_power.cpp ../utils/int_power.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/int_power.cpp -o $(SPBIN)/sobjs/int_power.o

$(SPBIN)/sobjs/int_sqrt.o:  ../utils/int_sqrt.cpp ../utils/int_sqrt.h ../utils/intfc.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/int_sqrt.cpp -o $(SPBIN)/sobjs/int_sqrt.o

$(SPBIN)/sobjs/moebius.o:  ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/int_factor.h ../utils/linescan.h ../utils/moebius.cpp ../utils/moebius.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/moebius.cpp -o $(SPBIN)/sobjs/moebius.o

$(SPBIN)/sobjs/isprime.o:  ../utils/isprime.cpp ../utils/isprime.h ../utils/primes16.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/isprime.cpp -o $(SPBIN)/sobjs/isprime.o

$(SPBIN)/sobjs/tokenize.o:  ../utils/tokenize.cpp ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/tokenize.cpp -o $(SPBIN)/sobjs/tokenize.o

$(SPBIN)/sobjs/rsstring_t.o:  ../classes/rsstring_t.cpp ../classes/rsstring_t.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/rsstring_t.cpp -o $(SPBIN)/sobjs/rsstring_t.o

$(SPBIN)/sobjs/psdes.o:  ../utils/psdes.cpp ../utils/psdes.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/psdes.cpp -o $(SPBIN)/sobjs/psdes.o

$(SPBIN)/sobjs/int_random.o:  ../utils/int_random.cpp ../utils/int_random.h ../utils/psdes.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/int_random.cpp -o $(SPBIN)/sobjs/int_random.o

$(SPBIN)/sobjs/int_factor.o:  ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/int_factor.cpp ../utils/int_factor.h ../utils/linescan.h ../utils/primes16.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/int_factor.cpp -o $(SPBIN)/sobjs/int_factor.o

$(SPBIN)/sobjs/primes16.o:  ../utils/primes16.cpp
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/primes16.cpp -o $(SPBIN)/sobjs/primes16.o

$(SPBIN)/sobjs/intmod_random.o:  ../classes/intmod_t.h ../utils/int_random.h ../utils/int_totient.h ../utils/intmod_random.cpp ../utils/intmod_random.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/intmod_random.cpp -o $(SPBIN)/sobjs/intmod_random.o

$(SPBIN)/sobjs/fp_units.o:  ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/fp_units.cpp ../utils/fp_units.h ../utils/int_factor.h ../utils/int_gcd.h ../utils/int_sqrt.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fp_units.cpp -o $(SPBIN)/sobjs/fp_units.o

$(SPBIN)/sobjs/fp_scan_tuples.o:  ../classes/intmod_t.h ../utils/fp_scan_tuples.cpp ../utils/fp_scan_tuples.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fp_scan_tuples.cpp -o $(SPBIN)/sobjs/fp_scan_tuples.o

$(SPBIN)/sobjs/ft_scan_tuples.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/ft_scan_tuples.cpp ../utils/ft_scan_tuples.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/ft_scan_tuples.cpp -o $(SPBIN)/sobjs/ft_scan_tuples.o

$(SPBIN)/sobjs/f2poly_factor.o:  ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../classes/f2poly_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.cpp ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2poly_factor.cpp -o $(SPBIN)/sobjs/f2poly_factor.o

$(SPBIN)/sobjs/f2poly_random.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../utils/count_bits.h ../utils/f2poly_random.cpp ../utils/f2poly_random.h ../utils/int_random.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2poly_random.cpp -o $(SPBIN)/sobjs/f2poly_random.o

$(SPBIN)/sobjs/f2poly_totient.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.h ../utils/f2poly_totient.cpp ../utils/f2poly_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2poly_totient.cpp -o $(SPBIN)/sobjs/f2poly_totient.o

$(SPBIN)/sobjs/f2polymod_random.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/f2poly_random.h ../utils/f2polymod_random.cpp ../utils/f2polymod_random.h ../utils/int_random.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2polymod_random.cpp -o $(SPBIN)/sobjs/f2polymod_random.o

$(SPBIN)/sobjs/f2polymod_units.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/f2poly_totient.h ../utils/f2polymod_units.cpp ../utils/f2polymod_units.h ../utils/int_factor.h ../utils/int_sqrt.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2polymod_units.cpp -o $(SPBIN)/sobjs/f2polymod_units.o

$(SPBIN)/sobjs/f2polymod_convert.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2linalg.h ../utils/f2npoly_factor.h ../utils/f2polymod_convert.cpp ../utils/f2polymod_convert.h ../utils/f2polymod_units.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2polymod_convert.cpp -o $(SPBIN)/sobjs/f2polymod_convert.o

$(SPBIN)/sobjs/f2npoly_factor.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_factor.cpp ../utils/f2npoly_factor.h ../utils/f2npoly_random.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2npoly_factor.cpp -o $(SPBIN)/sobjs/f2npoly_factor.o

$(SPBIN)/sobjs/f2npoly_random.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/f2npoly_random.cpp ../utils/f2npoly_random.h ../utils/f2polymod_random.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2npoly_random.cpp -o $(SPBIN)/sobjs/f2npoly_random.o

$(SPBIN)/sobjs/f2npoly_totient.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_factor.h ../utils/f2npoly_totient.cpp ../utils/f2npoly_totient.h ../utils/int_power.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2npoly_totient.cpp -o $(SPBIN)/sobjs/f2npoly_totient.o

$(SPBIN)/sobjs/f2npolymod_random.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/f2npoly_random.h ../utils/f2npolymod_random.cpp ../utils/f2npolymod_random.h ../utils/intfc.h ../utils/log2.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2npolymod_random.cpp -o $(SPBIN)/sobjs/f2npolymod_random.o

$(SPBIN)/sobjs/f2npolymod_units.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_totient.h ../utils/f2npolymod_units.cpp ../utils/f2npolymod_units.h ../utils/int_factor.h ../utils/int_sqrt.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2npolymod_units.cpp -o $(SPBIN)/sobjs/f2npolymod_units.o

$(SPBIN)/sobjs/fppoly_factor.o:  ../classes/fppoly_t.h ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/fppoly_factor.cpp ../utils/fppoly_factor.h ../utils/fppoly_random.h ../utils/int_totient.h ../utils/linescan.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fppoly_factor.cpp -o $(SPBIN)/sobjs/fppoly_factor.o

$(SPBIN)/sobjs/fppoly_random.o:  ../classes/fppoly_t.h ../classes/intmod_t.h ../utils/fppoly_random.cpp ../utils/fppoly_random.h ../utils/int_totient.h ../utils/intmod_random.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fppoly_random.cpp -o $(SPBIN)/sobjs/fppoly_random.o

$(SPBIN)/sobjs/fppoly_totient.o:  ../classes/fppoly_t.h ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/fppoly_factor.h ../utils/fppoly_totient.cpp ../utils/fppoly_totient.h ../utils/int_power.h ../utils/int_totient.h ../utils/linescan.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fppoly_totient.cpp -o $(SPBIN)/sobjs/fppoly_totient.o

$(SPBIN)/sobjs/fppolymod_random.o:  ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../utils/fppoly_random.h ../utils/fppolymod_random.cpp ../utils/fppolymod_random.h ../utils/int_totient.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fppolymod_random.cpp -o $(SPBIN)/sobjs/fppolymod_random.o

$(SPBIN)/sobjs/f2linalg.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tmatrix.h ../utils/count_bits.h ../utils/f2linalg.cpp ../utils/f2linalg.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2linalg.cpp -o $(SPBIN)/sobjs/f2linalg.o

$(SPBIN)/sobjs/fplinalg.o:  ../classes/fpnpoly_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../utils/fplinalg.cpp ../utils/fplinalg.h ../utils/int_totient.h ../utils/linescan.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/fplinalg.cpp -o $(SPBIN)/sobjs/fplinalg.o

$(SPBIN)/sobjs/f2pmlinalg.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_factor.h ../utils/f2pmlinalg.cpp ../utils/f2pmlinalg.h ../utils/f2poly_factor.h ../utils/f2polymod_convert.h ../utils/f2polymod_units.h ../utils/int_gcd.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/f2pmlinalg.cpp -o $(SPBIN)/sobjs/f2pmlinalg.o

$(SPBIN)/sobjs/spminchar.o:  ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../utils/count_bits.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/spminchar.cpp ../utils/spminchar.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/spminchar.cpp -o $(SPBIN)/sobjs/spminchar.o

$(SPBIN)/sobjs/sp_list_elts.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_totient.h ../utils/f2poly_totient.h ../utils/fppoly_totient.h ../utils/int_gcd.h ../utils/int_power.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/sp_list_elts.cpp ../utils/sp_list_elts.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/sp_list_elts.cpp -o $(SPBIN)/sobjs/sp_list_elts.o

$(SPBIN)/sobjs/qpoly_t.o:  ../classes/cmps.h ../classes/intrat_t.h ../classes/qpoly_t.cpp ../classes/qpoly_t.h ../classes/rsstring_t.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../classes/qpoly_t.cpp -o $(SPBIN)/sobjs/qpoly_t.o

$(SPBIN)/sobjs/cyclopoly.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fpnpoly_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/intrat_t.h ../classes/qpoly_t.h ../utils/count_bits.h ../utils/cyclopoly.cpp ../utils/cyclopoly.h ../utils/int_totient.h ../utils/intfc.h ../utils/log2.h ../utils/qff.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/cyclopoly.cpp -o $(SPBIN)/sobjs/cyclopoly.o

$(SPBIN)/sobjs/qff.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fpnpoly_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/intrat_t.h ../classes/qpoly_t.h ../utils/count_bits.h ../utils/int_totient.h ../utils/intfc.h ../utils/log2.h ../utils/qff.cpp ../utils/qff.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/qff.cpp -o $(SPBIN)/sobjs/qff.o

$(SPBIN)/sobjs/tmvpolyscan.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../classes/tmvpoly.h ../classes/tvector.h ../utils/count_bits.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tmvpolyscan.cpp ../utils/tmvpolyscan.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/tmvpolyscan.cpp -o $(SPBIN)/sobjs/tmvpolyscan.o

$(SPBIN)/sobjs/tmvratscan.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../classes/tmvpoly.h ../classes/tmvrat.h ../classes/tvector.h ../utils/count_bits.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tmvpolyscan.h ../utils/tmvratscan.cpp ../utils/tmvratscan.h ../utils/tokenize.h
	g++ -Wall -O2 -shared $(COMPILE_FLAGS)  ../utils/tmvratscan.cpp -o $(SPBIN)/sobjs/tmvratscan.o

OBJS = \
	$(SPBIN)/sobjs/intrat_t.o \
	$(SPBIN)/sobjs/intmod_t.o \
	$(SPBIN)/sobjs/bit_t.o \
	$(SPBIN)/sobjs/bit_vector_t.o \
	$(SPBIN)/sobjs/bit_matrix_t.o \
	$(SPBIN)/sobjs/f2poly_t.o \
	$(SPBIN)/sobjs/f2polymod_t.o \
	$(SPBIN)/sobjs/f2polyrat_t.o \
	$(SPBIN)/sobjs/f2npoly_t.o \
	$(SPBIN)/sobjs/f2npolymod_t.o \
	$(SPBIN)/sobjs/f2npolyrat_t.o \
	$(SPBIN)/sobjs/fppoly_t.o \
	$(SPBIN)/sobjs/fppolymod_t.o \
	$(SPBIN)/sobjs/fppolyrat_t.o \
	$(SPBIN)/sobjs/fpnpoly_t.o \
	$(SPBIN)/sobjs/fpnpolymod_t.o \
	$(SPBIN)/sobjs/linescan.o \
	$(SPBIN)/sobjs/log2.o \
	$(SPBIN)/sobjs/log10.o \
	$(SPBIN)/sobjs/count_bits.o \
	$(SPBIN)/sobjs/int_gcd.o \
	$(SPBIN)/sobjs/int_totient.o \
	$(SPBIN)/sobjs/int_power.o \
	$(SPBIN)/sobjs/int_sqrt.o \
	$(SPBIN)/sobjs/moebius.o \
	$(SPBIN)/sobjs/isprime.o \
	$(SPBIN)/sobjs/tokenize.o \
	$(SPBIN)/sobjs/rsstring_t.o \
	$(SPBIN)/sobjs/psdes.o \
	$(SPBIN)/sobjs/int_random.o \
	$(SPBIN)/sobjs/int_factor.o \
	$(SPBIN)/sobjs/primes16.o \
	$(SPBIN)/sobjs/intmod_random.o \
	$(SPBIN)/sobjs/fp_units.o \
	$(SPBIN)/sobjs/fp_scan_tuples.o \
	$(SPBIN)/sobjs/ft_scan_tuples.o \
	$(SPBIN)/sobjs/f2poly_factor.o \
	$(SPBIN)/sobjs/f2poly_random.o \
	$(SPBIN)/sobjs/f2poly_totient.o \
	$(SPBIN)/sobjs/f2polymod_random.o \
	$(SPBIN)/sobjs/f2polymod_units.o \
	$(SPBIN)/sobjs/f2polymod_convert.o \
	$(SPBIN)/sobjs/f2npoly_factor.o \
	$(SPBIN)/sobjs/f2npoly_random.o \
	$(SPBIN)/sobjs/f2npoly_totient.o \
	$(SPBIN)/sobjs/f2npolymod_random.o \
	$(SPBIN)/sobjs/f2npolymod_units.o \
	$(SPBIN)/sobjs/fppoly_factor.o \
	$(SPBIN)/sobjs/fppoly_random.o \
	$(SPBIN)/sobjs/fppoly_totient.o \
	$(SPBIN)/sobjs/fppolymod_random.o \
	$(SPBIN)/sobjs/f2linalg.o \
	$(SPBIN)/sobjs/fplinalg.o \
	$(SPBIN)/sobjs/f2pmlinalg.o \
	$(SPBIN)/sobjs/spminchar.o \
	$(SPBIN)/sobjs/sp_list_elts.o \
	$(SPBIN)/sobjs/qpoly_t.o \
	$(SPBIN)/sobjs/cyclopoly.o \
	$(SPBIN)/sobjs/qff.o \
	$(SPBIN)/sobjs/tmvpolyscan.o \
	$(SPBIN)/sobjs/tmvratscan.o

$(SPBIN)/dynamic/libspffl.so: $(OBJS) $(EXTRA_DEPS)
	g++ -shared $(OBJS) -o $(SPBIN)/dynamic/libspffl.so $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f $(SPBIN)/dynamic/libspffl.so
