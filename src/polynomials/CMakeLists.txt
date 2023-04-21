cmake_minimum_required (VERSION 3.24)

project(polynomials)

add_library(${PROJECT_NAME}
  f2_poly_t.cpp
  fp_poly_t.cpp

  f2_polymod_t.cpp
  fp_polymod_t.cpp

  f2n_poly_t.cpp
  fpn_poly_t.cpp

  f2n_polymod_t.cpp
  fpn_polymod_t.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    intmath
    bits
)
