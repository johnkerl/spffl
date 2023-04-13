cmake_minimum_required (VERSION 3.24)

project(spffl_cli)

add_executable(cli_gcd cli_gcd.cpp)

target_include_directories(cli_gcd
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
)
target_link_libraries(cli_gcd PRIVATE
    intmath
)
