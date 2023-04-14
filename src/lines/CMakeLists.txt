cmake_minimum_required (VERSION 3.24)

project(lines)

add_library(${PROJECT_NAME}
  linescan.cpp
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
