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
# setup SWIG build
########################################################################
set(GR_SWIG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(GR_SWIG_FLAGS -DPMC_SWIG_EXPORTS) #build vs runtime rules
file(GLOB GR_SWIG_SOURCE_DEPS "${CMAKE_CURRENT_SOURCE_DIR}/PMC/*.i")

GR_SWIG_MAKE(PMC PMC.i)

########################################################################
# Install rules
########################################################################
GR_SWIG_INSTALL(
    TARGETS PMC
    DESTINATION ${GR_PYTHON_DIR}
    COMPONENT ${PMC_COMP_PYTHON}
)

install(
    FILES PMC.i
    DESTINATION include/PMC/swig
    COMPONENT ${PMC_COMP_PYTHON}
)
