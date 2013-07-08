########################################################################
# Include swig generation macros
########################################################################
find_package(SWIG)
if(NOT SWIG_FOUND)
    return()
endif()

find_package(PythonLibs)
if(NOT PYTHONLIBS_FOUND)
    return()
endif()

include(UseSWIG)
include(GrPython)

########################################################################
# Local includes
########################################################################
list(APPEND CMAKE_SWIG_INC_FLAGS "-I${PMC_SOURCE_DIR}/include")
include_directories(${PMC_SOURCE_DIR}/include)

########################################################################
# Python library setup
########################################################################
include_directories(${PYTHON_INCLUDE_PATH})
include_directories(${PYTHON_INCLUDE_DIRS})

########################################################################
# Finding Boost headers
########################################################################
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

########################################################################
# swig build modules
########################################################################
set(pmc_swig_modules
    PMCIndex
    PMCPool
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

foreach(pmc_swig_module ${pmc_swig_modules})
    message(STATUS "Configuring swig python module ${pmc_swig_module}...")

    #set the C++ property on the swig .i file so it builds
    set_source_files_properties(${pmc_swig_module}.i PROPERTIES CPLUSPLUS ON)

    set(CMAKE_SWIG_FLAGS -fvirtual -module ${pmc_swig_module} ${CMAKE_SWIG_INC_FLAGS})
    file(GLOB SWIG_MODULE_${pmc_swig_module}_EXTRA_DEPS "${PMC_SOURCE_DIR}/include/PMC/*.i")
    SWIG_ADD_MODULE(${pmc_swig_module} python ${pmc_swig_module}.i)
    SWIG_LINK_LIBRARIES(${pmc_swig_module} ${PMC_LIBRARIES} ${PYTHON_LIBRARIES})

    install(
        TARGETS ${SWIG_MODULE_${pmc_swig_module}_REAL_NAME}
        DESTINATION ${GR_PYTHON_DIR}/PMC
        COMPONENT ${PMC_COMP_PYTHON}
    )
    install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/${pmc_swig_module}.py
        DESTINATION ${GR_PYTHON_DIR}/PMC
        COMPONENT ${PMC_COMP_PYTHON}
    )
endforeach(pmc_swig_module)

########################################################################
# install other python files
########################################################################
INSTALL(
    FILES __init__.py
    DESTINATION ${GR_PYTHON_DIR}/PMC
    COMPONENT ${PMC_COMP_PYTHON}
)
