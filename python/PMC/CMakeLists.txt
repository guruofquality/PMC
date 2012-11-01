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

########################################################################
# Setup Finding Boost headers
########################################################################
find_package(Boost)

########################################################################
# setup SWIG build
########################################################################
set(pmc_swig_modules
    PMCNone
    PMCBool
    PMCIntegers
    PMCFloats
    PMCComplex
    PMCString
    PMCTuple
    PMCSet
    PMCList
    PMCDict
    PMCNumericArray
)

list(APPEND GR_SWIG_INCLUDE_DIRS ${PMC_SOURCE_DIR}/include)
list(APPEND GR_SWIG_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

foreach(pmc_swig_module ${pmc_swig_modules})
    message(STATUS "Configuring swig module ${pmc_swig_module}...")
    GR_SWIG_MAKE(${pmc_swig_module} ${pmc_swig_module}.i)
    GR_SWIG_INSTALL(
        TARGETS ${pmc_swig_module}
        DESTINATION ${GR_PYTHON_DIR}/PMC
        COMPONENT ${PMC_COMP_PYTHON}
    )
endforeach(pmc_swig_module)

########################################################################
# Install rules
########################################################################
GR_PYTHON_INSTALL(
    FILES __init__.py
    DESTINATION ${GR_PYTHON_DIR}/PMC
    COMPONENT ${PMC_COMP_PYTHON}
)
