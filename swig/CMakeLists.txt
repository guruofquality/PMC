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


set(GR_SWIG_SOURCE_DEPS pmc_default_types.i pmc_utils.i pmc_none.i pmc_dict.i)

GR_SWIG_MAKE(PMC pmc_swig.i)
