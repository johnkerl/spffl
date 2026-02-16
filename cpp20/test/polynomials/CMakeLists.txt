project(test_polynomial_of)

add_executable(test_polynomial_of
  test_polynomial_of.cpp
)
target_include_directories(test_polynomial_of
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(test_polynomial_of PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_polynomial_of)

