cmake_minimum_required (VERSION 3.24)

project(qcyclo)

add_library(${PROJECT_NAME}
  qff.cpp
  cyclopoly.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/rationals
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    bits
    intmath
    polynomials
    rationals
)
