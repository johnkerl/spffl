cmake_minimum_required (VERSION 3.24)

project(bitrand)

add_library(${PROJECT_NAME}
  psdes.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/../../spffl
)
