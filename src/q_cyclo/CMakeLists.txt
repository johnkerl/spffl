cmake_minimum_required (VERSION 3.24)

project(q_cyclo)

add_library(${PROJECT_NAME}
  qff.cpp
  cyclo_poly.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    bits
    intmath
    polynomials
    rationals
)
