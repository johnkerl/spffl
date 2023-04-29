cmake_minimum_required (VERSION 3.24)

project(base)

add_library(${PROJECT_NAME}
  tokenize.cpp
  line_scan.cpp
)
