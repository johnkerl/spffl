cmake_minimum_required (VERSION 3.24)

project(polynomials)

# f2n/fpn: types from fpn_f2n_aliases.h (polynomial_of / residue_of), no .cpp
add_library(${PROJECT_NAME}
  f2_poly_t.cpp
  f2_polymod_t.cpp
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
