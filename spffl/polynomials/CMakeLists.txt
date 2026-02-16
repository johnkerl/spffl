cmake_minimum_required (VERSION 3.24)

project(polynomials)

add_library(${PROJECT_NAME}
  f2_poly_t.cpp

  f2_polymod_t.cpp

  # Phase 1.4 Option B: f2n/fpn are polynomial_of/residue_of (see fpn_f2n_aliases.hpp)
  # f2n_poly_t.cpp
  # fpn_poly_t.cpp
  # f2n_polymod_t.cpp
  # fpn_polymod_t.cpp

  q_poly_t.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    intmath
    bits
)
