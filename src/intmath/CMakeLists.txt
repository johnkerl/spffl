cmake_minimum_required (VERSION 3.24)

project(intmath)

add_library(${PROJECT_NAME}
  int_power.cpp
  int_sqrt.cpp
  int_gcd.cpp
  int_totient.cpp
)
add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
