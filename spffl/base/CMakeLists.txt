cmake_minimum_required (VERSION 3.24)

project(base)

add_library(${PROJECT_NAME}
  spffl_exception.cpp
  tokenize.cpp
  line_scan.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/../..
)
