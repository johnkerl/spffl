cmake_minimum_required (VERSION 3.24)

project(polymods)

add_library(${PROJECT_NAME}
  f2polymod_t.cpp
  fppolymod_t.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    intmath
    bits
    polynomials
)
