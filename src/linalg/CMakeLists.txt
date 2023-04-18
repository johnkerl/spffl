cmake_minimum_required (VERSION 3.24)

project(linalg)

add_library(${PROJECT_NAME}
  f2linalg.cpp
  f2pmlinalg.cpp
  fplinalg.cpp
  spminchar.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/containers
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/factorization
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/units
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  base
  bits
  intmath
  polynomials
  containers
  factorization
  units
)
