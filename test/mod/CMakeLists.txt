cmake_minimum_required(VERSION 3.24)

project(test_mod)

# ----------------------------------------------------------------
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)

cmake_host_system_information(RESULT OS_RELEASE QUERY OS_RELEASE)

if(APPLE AND OS_RELEASE VERSION_GREATER_EQUAL "13.0.0")
  get_property(
    compile_options
    DIRECTORY
    PROPERTY COMPILE_OPTIONS
  )
  set_property(
    DIRECTORY
    APPEND
    PROPERTY COMPILE_OPTIONS -Wno-error=unused-but-set-variable
  )
endif()

FetchContent_MakeAvailable(Catch2)

if(APPLE AND OS_RELEASE VERSION_GREATER_EQUAL "13.0.0")
  set_property(
    DIRECTORY
    PROPERTY COMPILE_OPTIONS ${compile_options}
  )
  unset(compile_options)
endif()

# ----------------------------------------------------------------
add_executable(test_mod test_mod.cpp)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  mod
  Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_mod)
