cmake_minimum_required (VERSION 3.24)

# This directory is headers-only

project(bits)

#add_library(${PROJECT_NAME}
#)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/intmath
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../src/lines
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    intmath
    lines
)
