cmake_minimum_required (VERSION 3.24)

project(random)

add_library(${PROJECT_NAME}
  f2poly_random.cpp
  f2polymod_random.cpp
  f2npoly_random.cpp
  f2npolymod_random.cpp

  fppoly_random.cpp
  fppolymod_random.cpp

  int_random.cpp
  intmod_random.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bitrand
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    bitrand
    intmath
    bits
    polynomials
)
