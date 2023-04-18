cmake_minimum_required (VERSION 3.24)

project(bitrand)

add_library(${PROJECT_NAME}
  psdes.cpp
)
#add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
