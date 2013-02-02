########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 2.6)
project(PMC CXX C)
enable_testing()

set(PMC_VERSION "0.0.0")
set(PMC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PMC_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(PMC_INCLUDE_DIRS ${PMC_SOURCE_DIR}/include)
set(PMC_LIBRARIES pmc)

list(APPEND CMAKE_MODULE_PATH ${PMC_SOURCE_DIR}/cmake/Modules)
include(CMakeDefsHelper)

include(CheckTypeSize)
enable_language(C)
check_type_size("void*[8]" SIZEOF_CPU BUILTIN_TYPES_ONLY)
if(CMAKE_COMPILER_IS_GNUCXX AND ${SIZEOF_CPU} EQUAL 64)
    add_definitions(-fPIC)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    #add_definitions(-fvisibility=hidden)
endif()

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
