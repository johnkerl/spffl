project(test_algorithms)

add_executable(test_algorithms
  test_algorithms.cpp
)
target_include_directories(test_algorithms
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(test_algorithms PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_algorithms)
