cmake_minimum_required (VERSION 3.24)

project(spiff)

add_executable(
    spiff
    spiff_main.cpp

    z_handlers.cpp
    q_handlers.cpp

    f2_handlers.cpp

    f2_poly_handlers.cpp
    f2_polymod_handlers.cpp
    f2_polyrat_handlers.cpp

    f2n_poly_handlers.cpp
    f2n_polymod_handlers.cpp
    f2n_polyrat_handlers.cpp

    fp_handlers.cpp

    fp_poly_handlers.cpp
    fp_polymod_handlers.cpp
    fp_polyrat_handlers.cpp

    fpn_poly_handlers.cpp
    fpn_polymod_handlers.cpp
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
