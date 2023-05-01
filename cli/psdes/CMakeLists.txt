cmake_minimum_required (VERSION 3.24)

project(cli_psdes)

add_executable(
  cli_psdes
  cli_psdes.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    bitrand
)
