########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

set(GR_SWIG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(GR_SWIG_FLAGS -DPMC_SWIG_BUILDING)


file(GLOB swig_types_files "${CMAKE_CURRENT_SOURCE_DIR}/PMC/*.i")

set(GR_SWIG_SOURCE_DEPS ${swig_types_files})

GR_SWIG_MAKE(PMC PMC.i)
