########################################################################
# unit test suite
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

set(test_sources
    build_test.cpp
    serialize_test.cpp
)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#turn each test cpp file into an executable with an int main() function
add_definitions(-DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN)

#for each source: build an executable, register it as a test
foreach(test_source ${test_sources})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} ${Boost_LIBRARIES})
    add_test(${test_name} ${test_name})
endforeach(test_source)
