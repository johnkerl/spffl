cmake_minimum_required (VERSION 3.24)

project(spffl_cli)

add_executable(cli_psdes cli_psdes.cpp)

target_include_directories(cli_psdes
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bitrand
)
target_link_libraries(cli_psdes PRIVATE
    bitrand
)
