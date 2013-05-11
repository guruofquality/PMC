########################################################################
# find csharp dependencies
########################################################################
find_package(SWIG)
if(NOT SWIG_FOUND)
    return()
endif()

find_package(CSharp)
if(NOT CSHARP_FOUND)
    return()
endif()

find_program(GACUTIL_EXE gacutil)
if(NOT GACUTIL_EXE)
    return()
endif()

include(UseSWIG)

########################################################################
# Finding Boost headers
########################################################################
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

########################################################################
# swig build constants
########################################################################
list(APPEND CMAKE_SWIG_INC_FLAGS "-I${PMC_SOURCE_DIR}/include")
include_directories(${PMC_SOURCE_DIR}/include)

########################################################################
# swig build modules
########################################################################
set(pmc_swig_modules
    PMCIndex
    PMCBool
)

foreach(pmc_swig_module ${pmc_swig_modules})
    message(STATUS "Configuring swig csharp module ${pmc_swig_module}...")

    #set the C++ property on the swig .i file so it builds
    set_source_files_properties(${pmc_swig_module}.i PROPERTIES CPLUSPLUS ON)

    set(CMAKE_SWIG_FLAGS -fvirtual -module ${pmc_swig_module} ${CMAKE_SWIG_INC_FLAGS})
    list(APPEND SWIG_MODULE_${pmc_swig_module}_EXTRA_DEPS ${PMC_SOURCE_DIR}/include/PMC/PMC.i)
    SWIG_ADD_MODULE(${pmc_swig_module} csharp ${pmc_swig_module}.i)
    SWIG_LINK_LIBRARIES(${pmc_swig_module} ${PMC_LIBRARIES})

    list(APPEND generated_swig_modules ${SWIG_MODULE_${pmc_swig_module}_REAL_NAME})

    #can the gac do this?
    #install(
    #    TARGETS ${SWIG_MODULE_${pmc_swig_module}_REAL_NAME}
    #    DESTINATION what
    #    COMPONENT ${PMC_COMP_PYTHON}
    #)
endforeach(pmc_swig_module)

########################################################################
# assembly library creation
########################################################################
set(pmc_mono_assembly ${CMAKE_CURRENT_BINARY_DIR}/pmcmono.dll)

set(pmc_cs_sources ${CMAKE_CURRENT_SOURCE_DIR}/PMCRegistry.cs)

add_custom_command(
    OUTPUT ${pmc_mono_assembly}
    DEPENDS ${generated_swig_modules} ${pmc_cs_sources}
    COMMAND ${CSHARP_COMPILER}
        -target:library
        -out:${pmc_mono_assembly}
        -keyfile:${CMAKE_CURRENT_SOURCE_DIR}/pmc.snk
        ${CMAKE_CURRENT_BINARY_DIR}/*.cs
        ${pmc_cs_sources}
    COMMAND ${GACUTIL_EXE}
        -i ${pmc_mono_assembly}
        -package PMC
        -gacdir ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(make_pmc_mono_assembly ALL DEPENDS ${pmc_mono_assembly})
