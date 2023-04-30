cmake_minimum_required (VERSION 3.24)

project(rationals)

add_library(${PROJECT_NAME}
  f2n_polyrat_t.cpp
  f2_polyrat_t.cpp
  fp_polyrat_t.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../spffl
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    intmath
    bits
    polynomials
)
