cmake_minimum_required (VERSION 3.24)

# ----------------------------------------------------------------
project(ctools)

# ----------------------------------------------------------------
add_subdirectory(src)

# ----------------------------------------------------------------
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
list(APPEND CMAKE_PREFIX_PATH "${EP_INSTALL_PREFIX}")
find_package(Catch_EP REQUIRED)

add_subdirectory(test)
