cmake_minimum_required (VERSION 3.24)

project(convert)

add_library(${PROJECT_NAME}
  f2polymod_convert.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/containers
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/factorization
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/units
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/linalg
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  base
  intmath
  bits
  polynomials
  containers
  factorization
  units
  linalg
)
