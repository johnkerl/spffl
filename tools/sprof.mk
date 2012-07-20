# ================================================================
# Makefile for project sprof
# Automatically generated from "sprof.mki" at Fri Nov 19 22:47:57 2004

# yamm v1.0
# John Kerl
# 2002/05/04
# ================================================================


INCLUDE_DIRS = -I../classes -I../utils
LIB_DIRS =
DEFINES = -DF2POLY_SMALL
MISC_CFLAGS =
MISC_LFLAGS =
COMPILE_FLAGS = -c $(INCLUDE_DIRS) $(DEFINES) $(MISC_CFLAGS)
LINK_FLAGS =  $(LIB_DIRS) $(MISC_LFLAGS)

build: mk_obj_dir ../../../bin/sp/spiffsprof

mk_obj_dir:
	mkdir -p ../../../bin/sp/sprof_objs

../../../bin/sp/sprof_objs/spiffmain.o:  ../classes/bit_t.h ../classes/cmdlinematops.h ../classes/cmdlineops.h ../classes/cmdlinevecops.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2npolyrat_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/f2polyrat_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/fppolyrat_t.h ../classes/intmod_t.h ../classes/intrat_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tstack.h ../classes/tvector.h ../utils/cmdinterp.h ../utils/count_bits.h ../utils/f2linalg.h ../utils/f2npoly_factor.h ../utils/f2npoly_random.h ../utils/f2npoly_totient.h ../utils/f2npolymod_random.h ../utils/f2npolymod_units.h ../utils/f2pmlinalg.h ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/f2poly_totient.h ../utils/f2polymod_convert.h ../utils/f2polymod_random.h ../utils/f2polymod_units.h ../utils/fp_units.h ../utils/fplinalg.h ../utils/fppoly_factor.h ../utils/fppoly_random.h ../utils/fppoly_totient.h ../utils/fppolymod_random.h ../utils/int_factor.h ../utils/int_gcd.h ../utils/int_random.h ../utils/int_totient.h ../utils/intfc.h ../utils/intmod_random.h ../utils/isprime.h ../utils/linescan.h ../utils/log2.h ../utils/sp_list_elts.h ../utils/spminchar.h ../utils/tokenize.h spiffmain.cpp
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  spiffmain.cpp -o ../../../bin/sp/sprof_objs/spiffmain.o

../../../bin/sp/sprof_objs/cmdinterp.o:  ../utils/cmdinterp.cpp ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/cmdinterp.cpp -o ../../../bin/sp/sprof_objs/cmdinterp.o

../../../bin/sp/sprof_objs/intrat_t.o:  ../classes/cmps.h ../classes/intrat_t.cpp ../classes/intrat_t.h ../utils/int_gcd.h ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/intrat_t.cpp -o ../../../bin/sp/sprof_objs/intrat_t.o

../../../bin/sp/sprof_objs/intmod_t.o:  ../classes/intmod_t.cpp ../classes/intmod_t.h ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/intmod_t.cpp -o ../../../bin/sp/sprof_objs/intmod_t.o

../../../bin/sp/sprof_objs/bit_t.o:  ../classes/bit_t.cpp ../classes/bit_t.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/bit_t.cpp -o ../../../bin/sp/sprof_objs/bit_t.o

../../../bin/sp/sprof_objs/bit_vector_t.o:  ../classes/bit_t.h ../classes/bit_vector_t.cpp ../classes/bit_vector_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/bit_vector_t.cpp -o ../../../bin/sp/sprof_objs/bit_vector_t.o

../../../bin/sp/sprof_objs/bit_matrix_t.o:  ../classes/bit_matrix_t.cpp ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../utils/linescan.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/bit_matrix_t.cpp -o ../../../bin/sp/sprof_objs/bit_matrix_t.o

../../../bin/sp/sprof_objs/f2poly_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2poly_t.cpp ../classes/f2poly_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/f2poly_t.cpp -o ../../../bin/sp/sprof_objs/f2poly_t.o

../../../bin/sp/sprof_objs/f2polymod_t.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.cpp ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/f2polymod_t.cpp -o ../../../bin/sp/sprof_objs/f2polymod_t.o

../../../bin/sp/sprof_objs/f2polyrat_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2poly_t.h ../classes/f2polyrat_t.cpp ../classes/f2polyrat_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/f2polyrat_t.cpp -o ../../../bin/sp/sprof_objs/f2polyrat_t.o

../../../bin/sp/sprof_objs/f2npoly_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2npoly_t.cpp ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/f2npoly_t.cpp -o ../../../bin/sp/sprof_objs/f2npoly_t.o

../../../bin/sp/sprof_objs/f2npolymod_t.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.cpp ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/f2npolymod_t.cpp -o ../../../bin/sp/sprof_objs/f2npolymod_t.o

../../../bin/sp/sprof_objs/f2npolyrat_t.o:  ../classes/bit_t.h ../classes/cmps.h ../classes/f2npoly_t.h ../classes/f2npolyrat_t.cpp ../classes/f2npolyrat_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/f2npolyrat_t.cpp -o ../../../bin/sp/sprof_objs/f2npolyrat_t.o

../../../bin/sp/sprof_objs/fppoly_t.o:  ../classes/cmps.h ../classes/fppoly_t.cpp ../classes/fppoly_t.h ../classes/intmod_t.h ../classes/rsstring_t.h ../utils/int_totient.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/fppoly_t.cpp -o ../../../bin/sp/sprof_objs/fppoly_t.o

../../../bin/sp/sprof_objs/fppolymod_t.o:  ../classes/fppoly_t.h ../classes/fppolymod_t.cpp ../classes/fppolymod_t.h ../classes/intmod_t.h ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/fppolymod_t.cpp -o ../../../bin/sp/sprof_objs/fppolymod_t.o

../../../bin/sp/sprof_objs/fppolyrat_t.o:  ../classes/cmps.h ../classes/fppoly_t.h ../classes/fppolyrat_t.cpp ../classes/fppolyrat_t.h ../classes/intmod_t.h ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/fppolyrat_t.cpp -o ../../../bin/sp/sprof_objs/fppolyrat_t.o

../../../bin/sp/sprof_objs/linescan.o:  ../utils/linescan.cpp ../utils/linescan.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/linescan.cpp -o ../../../bin/sp/sprof_objs/linescan.o

../../../bin/sp/sprof_objs/log2.o:  ../utils/intfc.h ../utils/log2.cpp ../utils/log2.h ../utils/msb_table.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/log2.cpp -o ../../../bin/sp/sprof_objs/log2.o

../../../bin/sp/sprof_objs/log10.o:  ../utils/intfc.h ../utils/log10.cpp ../utils/log10.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/log10.cpp -o ../../../bin/sp/sprof_objs/log10.o

../../../bin/sp/sprof_objs/count_bits.o:  ../utils/count_bits.cpp ../utils/count_bits.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/count_bits.cpp -o ../../../bin/sp/sprof_objs/count_bits.o

../../../bin/sp/sprof_objs/int_gcd.o:  ../utils/int_gcd.cpp ../utils/int_gcd.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/int_gcd.cpp -o ../../../bin/sp/sprof_objs/int_gcd.o

../../../bin/sp/sprof_objs/int_totient.o:  ../utils/int_gcd.h ../utils/int_totient.cpp ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/int_totient.cpp -o ../../../bin/sp/sprof_objs/int_totient.o

../../../bin/sp/sprof_objs/int_power.o:  ../utils/int_power.cpp ../utils/int_power.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/int_power.cpp -o ../../../bin/sp/sprof_objs/int_power.o

../../../bin/sp/sprof_objs/int_sqrt.o:  ../utils/int_sqrt.cpp ../utils/int_sqrt.h ../utils/intfc.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/int_sqrt.cpp -o ../../../bin/sp/sprof_objs/int_sqrt.o

../../../bin/sp/sprof_objs/moebius.o:  ../classes/tfacinfo.h ../classes/tvector.h ../utils/int_factor.h ../utils/moebius.cpp ../utils/moebius.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/moebius.cpp -o ../../../bin/sp/sprof_objs/moebius.o

../../../bin/sp/sprof_objs/isprime.o:  ../utils/isprime.cpp ../utils/isprime.h ../utils/primes16.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/isprime.cpp -o ../../../bin/sp/sprof_objs/isprime.o

../../../bin/sp/sprof_objs/tokenize.o:  ../utils/tokenize.cpp ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/tokenize.cpp -o ../../../bin/sp/sprof_objs/tokenize.o

../../../bin/sp/sprof_objs/rsstring_t.o:  ../classes/rsstring_t.cpp ../classes/rsstring_t.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../classes/rsstring_t.cpp -o ../../../bin/sp/sprof_objs/rsstring_t.o

../../../bin/sp/sprof_objs/psdes.o:  ../utils/psdes.cpp ../utils/psdes.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/psdes.cpp -o ../../../bin/sp/sprof_objs/psdes.o

../../../bin/sp/sprof_objs/int_random.o:  ../utils/int_random.cpp ../utils/int_random.h ../utils/psdes.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/int_random.cpp -o ../../../bin/sp/sprof_objs/int_random.o

../../../bin/sp/sprof_objs/int_factor.o:  ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/int_factor.cpp ../utils/int_factor.h ../utils/linescan.h ../utils/primes16.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/int_factor.cpp -o ../../../bin/sp/sprof_objs/int_factor.o

../../../bin/sp/sprof_objs/primes16.o:  ../utils/primes16.cpp
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/primes16.cpp -o ../../../bin/sp/sprof_objs/primes16.o

../../../bin/sp/sprof_objs/intmod_random.o:  ../classes/intmod_t.h ../utils/int_random.h ../utils/int_totient.h ../utils/intmod_random.cpp ../utils/intmod_random.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/intmod_random.cpp -o ../../../bin/sp/sprof_objs/intmod_random.o

../../../bin/sp/sprof_objs/fp_units.o:  ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tvector.h ../utils/fp_units.cpp ../utils/fp_units.h ../utils/int_factor.h ../utils/int_gcd.h ../utils/int_sqrt.h ../utils/int_totient.h ../utils/intfc.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/fp_units.cpp -o ../../../bin/sp/sprof_objs/fp_units.o

../../../bin/sp/sprof_objs/f2poly_factor.o:  ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../classes/f2poly_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.cpp ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2poly_factor.cpp -o ../../../bin/sp/sprof_objs/f2poly_factor.o

../../../bin/sp/sprof_objs/f2poly_random.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../utils/count_bits.h ../utils/f2poly_random.cpp ../utils/f2poly_random.h ../utils/int_random.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2poly_random.cpp -o ../../../bin/sp/sprof_objs/f2poly_random.o

../../../bin/sp/sprof_objs/f2poly_totient.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/tfacinfo.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.h ../utils/f2poly_totient.cpp ../utils/f2poly_totient.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2poly_totient.cpp -o ../../../bin/sp/sprof_objs/f2poly_totient.o

../../../bin/sp/sprof_objs/f2polymod_random.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/f2poly_random.h ../utils/f2polymod_random.cpp ../utils/f2polymod_random.h ../utils/int_random.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2polymod_random.cpp -o ../../../bin/sp/sprof_objs/f2polymod_random.o

../../../bin/sp/sprof_objs/f2polymod_units.o:  ../classes/bit_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2poly_factor.h ../utils/f2poly_random.h ../utils/f2poly_totient.h ../utils/f2polymod_units.cpp ../utils/f2polymod_units.h ../utils/int_factor.h ../utils/int_sqrt.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2polymod_units.cpp -o ../../../bin/sp/sprof_objs/f2polymod_units.o

../../../bin/sp/sprof_objs/f2polymod_convert.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2linalg.h ../utils/f2npoly_factor.h ../utils/f2polymod_convert.cpp ../utils/f2polymod_convert.h ../utils/f2polymod_units.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2polymod_convert.cpp -o ../../../bin/sp/sprof_objs/f2polymod_convert.o

../../../bin/sp/sprof_objs/f2npoly_factor.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_factor.cpp ../utils/f2npoly_factor.h ../utils/f2npoly_random.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2npoly_factor.cpp -o ../../../bin/sp/sprof_objs/f2npoly_factor.o

../../../bin/sp/sprof_objs/f2npoly_random.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/f2npoly_random.cpp ../utils/f2npoly_random.h ../utils/f2polymod_random.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2npoly_random.cpp -o ../../../bin/sp/sprof_objs/f2npoly_random.o

../../../bin/sp/sprof_objs/f2npoly_totient.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_factor.h ../utils/f2npoly_totient.cpp ../utils/f2npoly_totient.h ../utils/int_power.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2npoly_totient.cpp -o ../../../bin/sp/sprof_objs/f2npoly_totient.o

../../../bin/sp/sprof_objs/f2npolymod_random.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../utils/count_bits.h ../utils/f2npoly_random.h ../utils/f2npolymod_random.cpp ../utils/f2npolymod_random.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2npolymod_random.cpp -o ../../../bin/sp/sprof_objs/f2npolymod_random.o

../../../bin/sp/sprof_objs/f2npolymod_units.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_totient.h ../utils/f2npolymod_units.cpp ../utils/f2npolymod_units.h ../utils/int_factor.h ../utils/int_sqrt.h ../utils/intfc.h ../utils/log2.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2npolymod_units.cpp -o ../../../bin/sp/sprof_objs/f2npolymod_units.o

../../../bin/sp/sprof_objs/fppoly_factor.o:  ../classes/fppoly_t.h ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/fppoly_factor.cpp ../utils/fppoly_factor.h ../utils/fppoly_random.h ../utils/int_totient.h ../utils/linescan.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/fppoly_factor.cpp -o ../../../bin/sp/sprof_objs/fppoly_factor.o

../../../bin/sp/sprof_objs/fppoly_random.o:  ../classes/fppoly_t.h ../classes/intmod_t.h ../utils/fppoly_random.cpp ../utils/fppoly_random.h ../utils/int_totient.h ../utils/intmod_random.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/fppoly_random.cpp -o ../../../bin/sp/sprof_objs/fppoly_random.o

../../../bin/sp/sprof_objs/fppoly_totient.o:  ../classes/fppoly_t.h ../classes/intmod_t.h ../classes/tfacinfo.h ../classes/tvector.h ../utils/fppoly_factor.h ../utils/fppoly_totient.cpp ../utils/fppoly_totient.h ../utils/int_power.h ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/fppoly_totient.cpp -o ../../../bin/sp/sprof_objs/fppoly_totient.o

../../../bin/sp/sprof_objs/fppolymod_random.o:  ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../utils/fppoly_random.h ../utils/fppolymod_random.cpp ../utils/fppolymod_random.h ../utils/int_totient.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/fppolymod_random.cpp -o ../../../bin/sp/sprof_objs/fppolymod_random.o

../../../bin/sp/sprof_objs/f2linalg.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/f2polyrat_t.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2linalg.cpp ../utils/f2linalg.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2linalg.cpp -o ../../../bin/sp/sprof_objs/f2linalg.o

../../../bin/sp/sprof_objs/fplinalg.o:  ../classes/fppoly_t.h ../classes/fppolyrat_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../classes/tvector.h ../utils/fplinalg.cpp ../utils/fplinalg.h ../utils/int_totient.h ../utils/linescan.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/fplinalg.cpp -o ../../../bin/sp/sprof_objs/fplinalg.o

../../../bin/sp/sprof_objs/f2pmlinalg.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolyrat_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/tfacinfo.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_factor.h ../utils/f2pmlinalg.cpp ../utils/f2pmlinalg.h ../utils/f2poly_factor.h ../utils/f2polymod_convert.h ../utils/f2polymod_units.h ../utils/int_gcd.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/f2pmlinalg.cpp -o ../../../bin/sp/sprof_objs/f2pmlinalg.o

../../../bin/sp/sprof_objs/spminchar.o:  ../classes/bit_matrix_t.h ../classes/bit_t.h ../classes/bit_vector_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmatrix.h ../classes/tvector.h ../utils/count_bits.h ../utils/int_totient.h ../utils/intfc.h ../utils/linescan.h ../utils/log2.h ../utils/spminchar.cpp ../utils/spminchar.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/spminchar.cpp -o ../../../bin/sp/sprof_objs/spminchar.o

../../../bin/sp/sprof_objs/sp_list_elts.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tvector.h ../utils/count_bits.h ../utils/f2npoly_totient.h ../utils/f2poly_totient.h ../utils/fppoly_totient.h ../utils/int_gcd.h ../utils/int_power.h ../utils/int_totient.h ../utils/intfc.h ../utils/log2.h ../utils/sp_list_elts.cpp ../utils/sp_list_elts.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/sp_list_elts.cpp -o ../../../bin/sp/sprof_objs/sp_list_elts.o

../../../bin/sp/sprof_objs/tmvpolyscan.o:  ../classes/bit_t.h ../classes/f2npoly_t.h ../classes/f2npolymod_t.h ../classes/f2poly_t.h ../classes/f2polymod_t.h ../classes/fppoly_t.h ../classes/fppolymod_t.h ../classes/intmod_t.h ../classes/tmvpoly.h ../classes/tvector.h ../utils/count_bits.h ../utils/int_totient.h ../utils/intfc.h ../utils/log2.h ../utils/tmvpolyscan.cpp ../utils/tmvpolyscan.h ../utils/tokenize.h
	gcc -pg -Wall -Werror $(COMPILE_FLAGS)  ../utils/tmvpolyscan.cpp -o ../../../bin/sp/sprof_objs/tmvpolyscan.o

OBJS = \
	../../../bin/sp/sprof_objs/spiffmain.o \
	../../../bin/sp/sprof_objs/cmdinterp.o \
	../../../bin/sp/sprof_objs/intrat_t.o \
	../../../bin/sp/sprof_objs/intmod_t.o \
	../../../bin/sp/sprof_objs/bit_t.o \
	../../../bin/sp/sprof_objs/bit_vector_t.o \
	../../../bin/sp/sprof_objs/bit_matrix_t.o \
	../../../bin/sp/sprof_objs/f2poly_t.o \
	../../../bin/sp/sprof_objs/f2polymod_t.o \
	../../../bin/sp/sprof_objs/f2polyrat_t.o \
	../../../bin/sp/sprof_objs/f2npoly_t.o \
	../../../bin/sp/sprof_objs/f2npolymod_t.o \
	../../../bin/sp/sprof_objs/f2npolyrat_t.o \
	../../../bin/sp/sprof_objs/fppoly_t.o \
	../../../bin/sp/sprof_objs/fppolymod_t.o \
	../../../bin/sp/sprof_objs/fppolyrat_t.o \
	../../../bin/sp/sprof_objs/linescan.o \
	../../../bin/sp/sprof_objs/log2.o \
	../../../bin/sp/sprof_objs/log10.o \
	../../../bin/sp/sprof_objs/count_bits.o \
	../../../bin/sp/sprof_objs/int_gcd.o \
	../../../bin/sp/sprof_objs/int_totient.o \
	../../../bin/sp/sprof_objs/int_power.o \
	../../../bin/sp/sprof_objs/int_sqrt.o \
	../../../bin/sp/sprof_objs/moebius.o \
	../../../bin/sp/sprof_objs/isprime.o \
	../../../bin/sp/sprof_objs/tokenize.o \
	../../../bin/sp/sprof_objs/rsstring_t.o \
	../../../bin/sp/sprof_objs/psdes.o \
	../../../bin/sp/sprof_objs/int_random.o \
	../../../bin/sp/sprof_objs/int_factor.o \
	../../../bin/sp/sprof_objs/primes16.o \
	../../../bin/sp/sprof_objs/intmod_random.o \
	../../../bin/sp/sprof_objs/fp_units.o \
	../../../bin/sp/sprof_objs/f2poly_factor.o \
	../../../bin/sp/sprof_objs/f2poly_random.o \
	../../../bin/sp/sprof_objs/f2poly_totient.o \
	../../../bin/sp/sprof_objs/f2polymod_random.o \
	../../../bin/sp/sprof_objs/f2polymod_units.o \
	../../../bin/sp/sprof_objs/f2polymod_convert.o \
	../../../bin/sp/sprof_objs/f2npoly_factor.o \
	../../../bin/sp/sprof_objs/f2npoly_random.o \
	../../../bin/sp/sprof_objs/f2npoly_totient.o \
	../../../bin/sp/sprof_objs/f2npolymod_random.o \
	../../../bin/sp/sprof_objs/f2npolymod_units.o \
	../../../bin/sp/sprof_objs/fppoly_factor.o \
	../../../bin/sp/sprof_objs/fppoly_random.o \
	../../../bin/sp/sprof_objs/fppoly_totient.o \
	../../../bin/sp/sprof_objs/fppolymod_random.o \
	../../../bin/sp/sprof_objs/f2linalg.o \
	../../../bin/sp/sprof_objs/fplinalg.o \
	../../../bin/sp/sprof_objs/f2pmlinalg.o \
	../../../bin/sp/sprof_objs/spminchar.o \
	../../../bin/sp/sprof_objs/sp_list_elts.o \
	../../../bin/sp/sprof_objs/tmvpolyscan.o

../../../bin/sp/spiffsprof: $(OBJS)
	gcc -pg -lstdc++ $(OBJS) -o ../../../bin/sp/spiffsprof $(LINK_FLAGS)

clean:
	-@rm -f $(OBJS)
	-@rm -f ../../../bin/sp/spiffsprof
