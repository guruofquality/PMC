########################################################################
# find csharp dependencies
########################################################################
find_package(SWIG)
find_package(CSharp)

if(NOT SWIG_FOUND OR NOT CSHARP_FOUND)
    return()
endif()

include(UseSWIG)

########################################################################
# Finding Boost headers
########################################################################
find_package(Boost)

include_directories(${Boost_INCLUDE_DIRS})

########################################################################
# swig build rules
########################################################################

#set the C++ property on the swig .i file so it builds
set_source_files_properties(PMCIndex.i PROPERTIES CPLUSPLUS ON)

set(CMAKE_SWIG_FLAGS -fvirtual -module PMCIndex)

list(APPEND CMAKE_SWIG_FLAGS "-I${PMC_SOURCE_DIR}/include")

include_directories(${PMC_SOURCE_DIR}/include)

SWIG_ADD_MODULE(PMCIndex csharp PMCIndex.i)
SWIG_LINK_LIBRARIES(PMCIndex ${PMC_LIBRARIES})
