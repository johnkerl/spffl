cmake_minimum_required (VERSION 3.24)

project(random)

add_library(${PROJECT_NAME}
  f2_poly_random.cpp
  f2_polymod_random.cpp
  f2n_poly_random.cpp
  f2n_polymod_random.cpp

  fp_poly_random.cpp
  fp_polymod_random.cpp

  int_random.cpp
  intmod_random.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bitrand
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    bitrand
    intmath
    bits
    polynomials
)
