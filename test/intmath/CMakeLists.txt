project(test_intmath)

# ----------------------------------------------------------------
# catch2 has a set-but-unused-variable warning as of MacOS 13.3.
# So we need to not use -Werror, as that's third-party code out of our control.
#
# See also:
# https://discourse.cmake.org/t/how-to-turn-off-warning-flags-for-project-added-by-fetchcontent-declare/2461

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
add_executable(test_intmath
  test_gcd.cpp
  test_power.cpp
  test_sqrt.cpp
  test_totient.cpp
  test_primes.cpp
  test_log2.cpp
  test_log10.cpp
)
target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    base
    intmath
    Catch2::Catch2WithMain
)

# ----------------------------------------------------------------
# This makes the following work:
# cmake --build build --target test
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(test_intmath)
