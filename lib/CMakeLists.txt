cmake_minimum_required (VERSION 3.24)

project(spffl)

# TODO: try to get these from globbing

#file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src **.cpp)
#add_library(
#  spffl # results in libspffl.so / libspffl.dylib, so, say "spffl" here not "libspffl"
#  SHARED
#  ${SOURCES}
#)

add_library(
  spffl # results in libspffl.so / libspffl.dylib, so, say "spffl" here not "libspffl"
  SHARED
  ../src/base/line_scan.cpp
  ../src/base/spffl_exception.cpp
  ../src/base/tokenize.cpp
  ../src/bitrand/psdes.cpp
  ../src/bits/bit_matrix_t.cpp
  ../src/bits/bit_t.cpp
  ../src/bits/bit_vector_t.cpp
  ../src/bits/count_bits.cpp
  ../src/cliparser/cmd_interp.cpp
  ../src/containers/containers.cpp
  ../src/factorization/f2_poly_factor.cpp
  ../src/factorization/f2_poly_totient.cpp
  ../src/factorization/f2n_poly_factor.cpp
  ../src/factorization/f2n_poly_totient.cpp
  ../src/factorization/fp_poly_factor.cpp
  ../src/factorization/fp_poly_totient.cpp
  ../src/factorization/int_factor.cpp
  ../src/intmath/int_gcd.cpp
  ../src/intmath/int_power.cpp
  ../src/intmath/int_sqrt.cpp
  ../src/intmath/int_totient.cpp
  ../src/intmath/intmod_t.cpp
  ../src/intmath/is_prime.cpp
  ../src/intmath/log10.cpp
  ../src/intmath/log2.cpp
  ../src/intmath/primes_16.cpp
  ../src/linalg/f2_linear_algebra.cpp
  ../src/linalg/f2_polymod_convert.cpp
  ../src/linalg/f2_polymod_linear_algebra.cpp
  ../src/linalg/fp_linear_algebra.cpp
  ../src/linalg/min_char_polys.cpp
  ../src/list/list_elements.cpp
  ../src/polynomials/f2_poly_t.cpp
  ../src/polynomials/f2_polymod_t.cpp
  ../src/polynomials/f2n_poly_t.cpp
  ../src/polynomials/f2n_polymod_t.cpp
  ../src/polynomials/fp_poly_t.cpp
  ../src/polynomials/fp_polymod_t.cpp
  ../src/polynomials/fpn_poly_t.cpp
  ../src/polynomials/fpn_polymod_t.cpp
  ../src/q_cyclo/cyclo_poly.cpp
  ../src/q_cyclo/qff.cpp
  ../src/random/f2_poly_random.cpp
  ../src/random/f2_polymod_random.cpp
  ../src/random/f2n_poly_random.cpp
  ../src/random/f2n_polymod_random.cpp
  ../src/random/fp_poly_random.cpp
  ../src/random/fp_polymod_random.cpp
  ../src/random/int_random.cpp
  ../src/random/intmod_random.cpp
  ../src/rationals/f2_polyrat_t.cpp
  ../src/rationals/f2n_polyrat_t.cpp
  ../src/rationals/fp_polyrat_t.cpp
  ../src/rationals/intrat_t.cpp
  ../src/rationals/qpoly_t.cpp
  ../src/units/f2_polymod_units.cpp
  ../src/units/f2n_polymod_units.cpp
  ../src/units/fp_units.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/base
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/intmath
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/bitrand
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/bits
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/polynomials
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/rationals
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/q_cyclo
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/random
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/factorization
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/units
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/list
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/linalg
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/containers
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    base
    intmath
    bitrand
    bits
    polynomials
    rationals
    q_cyclo
    random
    factorization
    units
    list
    linalg
    containers
    cliparser
)
