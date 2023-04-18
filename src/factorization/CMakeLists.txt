cmake_minimum_required (VERSION 3.24)

project(factorization)

add_library(${PROJECT_NAME}
  f2poly_factor.cpp
  f2npoly_factor.cpp
  fppoly_factor.cpp
  int_factor.cpp

  f2npoly_totient.cpp
  f2poly_totient.cpp
  fppoly_totient.cpp
  # int_totient.cpp is in intmath
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/containers
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/random
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    intmath
    bits
    polynomials
    containers
    random
)
