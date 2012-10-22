include(GrMiscUtils)
add_library(PMC SHARED PMC.cpp)
target_link_libraries(PMC ${Boost_LIBRARIES})
#GR_LIBRARY_FOO(PMC RUNTIME_COMPONENT "gruel_runtime" DEVEL_COMPONENT "gruel_devel")
