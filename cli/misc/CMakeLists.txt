cmake_minimum_required (VERSION 3.24)

project(misc_main)

add_executable(
    misc_main
    misc_main.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    bits
    intmath
    polynomials
    rationals
    q_cyclo
    random
    factorization
    units
    list
    linalg
    containers
    cliparser
)
