########################################################################
# Setup the PMC library build
########################################################################
include_directories(${PMC_INCLUDE_DIRS})

########################################################################
# Setup Boost
########################################################################
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND PMC_LIBRARIES ${Boost_LIBRARIES})

########################################################################
# Append PMC library sources
########################################################################
list(APPEND PMC_SOURCES
    InternPool.cpp
)

########################################################################
# Build library
########################################################################
add_library(pmc SHARED ${PMC_SOURCES})
target_link_libraries(pmc ${PMC_LIBRARIES})
set_target_properties(pmc PROPERTIES VERSION ${PMC_VERSION})
set_target_properties(pmc PROPERTIES DEFINE_SYMBOL "PMC_DLL_EXPORTS")

install(TARGETS pmc
    LIBRARY DESTINATION lib${LIB_SUFFIX} COMPONENT ${PMC_COMP_RUNTIME} # .so file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} COMPONENT ${PMC_COMP_DEVEL}   # .lib file
    RUNTIME DESTINATION bin              COMPONENT ${PMC_COMP_RUNTIME} # .dll file
)

########################################################################
# Build pkg config file
########################################################################
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/pmc.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/pmc.pc
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/pmc.pc
    DESTINATION lib${LIB_SUFFIX}/pkgconfig
    COMPONENT ${PMC_COMP_DEVEL}
)
