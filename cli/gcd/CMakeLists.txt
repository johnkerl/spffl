cmake_minimum_required (VERSION 3.24)

project(cli_gcd)

add_executable(cli_gcd cli_gcd.cpp)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    intmath
)
