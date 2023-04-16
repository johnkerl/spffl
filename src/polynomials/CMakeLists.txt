cmake_minimum_required (VERSION 3.24)

project(polynomials)

add_library(${PROJECT_NAME}
  f2poly_t.cpp
  fppoly_t.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    intmath
    bits
)
