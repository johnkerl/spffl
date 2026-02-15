project(test_concepts)

add_executable(test_concepts test_concepts.cpp)
target_include_directories(test_concepts
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(test_concepts PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_concepts)
