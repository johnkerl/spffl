cmake_minimum_required (VERSION 3.24)

project(spiff)

add_executable(
    spiff
    spiffmain.cpp
    z_handlers.cpp
    f2poly_handlers.cpp
    f2polymod_handlers.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/base
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/bits
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/polynomials
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/rationals
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/random
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/factorization
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/units
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/list
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/linalg
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/convert
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/containers
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src/cliparser
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    bits
    intmath
    polynomials
    rationals
    random
    factorization
    units
    list
    linalg
    convert
    containers
    cliparser
)
