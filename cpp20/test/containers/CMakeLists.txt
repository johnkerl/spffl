project(test_containers)

add_executable(test_vector_over test_vector_over.cpp)
target_include_directories(test_vector_over
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(test_vector_over PRIVATE Catch2::Catch2WithMain)

add_executable(test_matrix_over test_matrix_over.cpp)
target_include_directories(test_matrix_over
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(test_matrix_over PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_vector_over)
catch_discover_tests(test_matrix_over)
