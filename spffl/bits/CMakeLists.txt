cmake_minimum_required (VERSION 3.24)

project(bits)

add_library(${PROJECT_NAME}
  bit_t.cpp
  bit_vector_t.cpp
  bit_matrix_t.cpp
  count_bits.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    intmath
)
