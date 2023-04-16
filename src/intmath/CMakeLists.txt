cmake_minimum_required (VERSION 3.24)

project(intmath)

add_library(${PROJECT_NAME}
  int_power.cpp
  int_sqrt.cpp
  int_gcd.cpp
  primes16.cpp
  isprime.cpp
  log2.cpp
  log10.cpp
  intmod_t.cpp
  int_totient.cpp
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
