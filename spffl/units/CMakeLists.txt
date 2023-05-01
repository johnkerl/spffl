cmake_minimum_required (VERSION 3.24)

project(units)

add_library(${PROJECT_NAME}
  f2_polymod_units.cpp
  f2n_polymod_units.cpp
  fp_units.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..
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
