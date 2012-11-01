########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(PMC CXX C)
enable_testing()

set(PMC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PMC_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH ${PMC_SOURCE_DIR}/cmake/Modules)
include(CMakeDefsHelper)

########################################################################
# Component names for install rules
########################################################################
if (NOT DEFINED PMC_COMP_DEVEL)
    set(PMC_COMP_DEVEL "devel")
endif()
if (NOT DEFINED PMC_COMP_RUNTIME)
    set(PMC_COMP_RUNTIME "runtime")
endif()
if (NOT DEFINED PMC_COMP_PYTHON)
    set(PMC_COMP_PYTHON "python")
endif()

########################################################################
# Setup cmake subdirs
########################################################################
include_directories(include)
add_subdirectory(include/PMC)
add_subdirectory(lib)
add_subdirectory(python/PMC)
add_subdirectory(tests)
