cmake_minimum_required (VERSION 3.24)

project(units)

add_library(${PROJECT_NAME}
  f2polymod_units.cpp
  f2npolymod_units.cpp
  fp_units.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/containers
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/factorization
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/random
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  base
  intmath
  bits
  polynomials
  containers
  factorization
  random
)
