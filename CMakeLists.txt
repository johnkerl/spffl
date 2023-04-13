cmake_minimum_required (VERSION 3.24)

# ----------------------------------------------------------------
project(spffl)

# ----------------------------------------------------------------
add_subdirectory(src)

# ----------------------------------------------------------------
enable_testing()
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
add_subdirectory(test)
