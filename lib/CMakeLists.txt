cmake_minimum_required (VERSION 3.24)

project(spffl)

# TODO: try to get these from globbing

#file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../spffl **.cpp)
#add_library(
#  spffl # results in libspffl.so / libspffl.dylib, so, say "spffl" here not "libspffl"
#  SHARED
#  ${SOURCES}
#)

add_library(
  spffl # results in libspffl.so / libspffl.dylib, so, say "spffl" here not "libspffl"
  SHARED
  ../spffl/base/line_scan.cpp
  ../spffl/base/spffl_exception.cpp
  ../spffl/base/tokenize.cpp

  ../spffl/bitrand/psdes.cpp

  ../spffl/bits/bit_matrix_t.cpp
  ../spffl/bits/bit_t.cpp
  ../spffl/bits/bit_vector_t.cpp
  ../spffl/bits/count_bits.cpp

  ../spffl/cli_parser/cmd_interp.cpp

  ../spffl/containers/containers.cpp

  ../spffl/factorization/f2_poly_factor.cpp
  ../spffl/factorization/f2_poly_totient.cpp
  ../spffl/factorization/f2n_poly_factor.cpp
  ../spffl/factorization/f2n_poly_totient.cpp
  ../spffl/factorization/fp_poly_factor.cpp
  ../spffl/factorization/fp_poly_totient.cpp
  ../spffl/factorization/int_factor.cpp

  ../spffl/intmath/int_gcd.cpp
  ../spffl/intmath/int_power.cpp
  ../spffl/intmath/int_sqrt.cpp
  ../spffl/intmath/int_totient.cpp
  ../spffl/intmath/intrat_t.cpp
  ../spffl/intmath/is_prime.cpp
  ../spffl/intmath/log10.cpp
  ../spffl/intmath/log2.cpp
  ../spffl/intmath/primes_16.cpp

  ../spffl/linalg/f2_linear_algebra.cpp
  ../spffl/linalg/f2_polymod_convert.cpp
  ../spffl/linalg/f2_polymod_linear_algebra.cpp
  ../spffl/linalg/fp_linear_algebra.cpp
  ../spffl/linalg/min_char_polys.cpp

  ../spffl/list/list_elements.cpp

  ../spffl/polynomials/f2_poly_t.cpp
  ../spffl/polynomials/f2_polymod_t.cpp
  ../spffl/polynomials/q_poly_t.cpp

  ../spffl/q_cyclotomic/cyclo_poly.cpp
  ../spffl/q_cyclotomic/qff.cpp

  ../spffl/random/f2_poly_random.cpp
  ../spffl/random/f2_polymod_random.cpp
  ../spffl/random/f2n_poly_random.cpp
  ../spffl/random/f2n_polymod_random.cpp
  ../spffl/random/fp_poly_random.cpp
  ../spffl/random/fp_polymod_random.cpp
  ../spffl/random/int_random.cpp
  ../spffl/random/intmod_random.cpp

  ../spffl/rationals/f2_polyrat_t.cpp
  ../spffl/rationals/f2n_polyrat_t.cpp
  ../spffl/rationals/fp_polyrat_t.cpp

  ../spffl/units/f2_polymod_units.cpp
  ../spffl/units/f2n_polymod_units.cpp
  ../spffl/units/fp_units.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    base
    intmath
    bitrand
    bits
    polynomials
    rationals
    q_cyclotomic
    random
    factorization
    units
    list
    linalg
    containers
    cli_parser
)
