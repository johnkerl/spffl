cmake_minimum_required (VERSION 3.24)

project(intmath)

add_library(${PROJECT_NAME}
  int_power.cpp
  int_sqrt.cpp
  int_gcd.cpp
  int_totient.cpp
  intmod_t.cpp
  intrat_t.cpp
  primes_16.cpp
  is_prime.cpp
  log2.cpp
  log10.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
)
