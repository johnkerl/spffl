cmake_minimum_required (VERSION 3.24)

project(cli_parser)

add_library(${PROJECT_NAME}
  cmd_interp.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../spffl
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    containers
)
