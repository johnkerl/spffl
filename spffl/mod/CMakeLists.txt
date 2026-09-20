cmake_minimum_required(VERSION 3.24)

project(mod)

add_library(${PROJECT_NAME} foo.cpp)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
