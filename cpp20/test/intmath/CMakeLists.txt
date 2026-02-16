project(test_intmod_t)

add_executable(test_intmod_t
  test_intmod_t.cpp
)
target_include_directories(test_intmod_t
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(test_intmod_t PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_intmod_t)

