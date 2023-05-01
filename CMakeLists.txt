cmake_minimum_required (VERSION 3.24)

project(spffl)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ Standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(spffl)
add_subdirectory(lib)
add_subdirectory(cli)

enable_testing()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
add_subdirectory(test)

# ----------------------------------------------------------------
install(
  DIRECTORY "spffl/" # The trailing slash is important so "spffl" isn't a part of the install path
  DESTINATION "include/spffl"
  FILES_MATCHING PATTERN "*.h"
)
install(TARGETS spffl DESTINATION lib)
install(TARGETS spiff DESTINATION bin)
