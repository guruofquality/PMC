
include(GrTest)

########################################################################
# unit test suite
########################################################################
find_package(Boost COMPONENTS unit_test_framework)

if (NOT Boost_FOUND)
    return()
endif()

set(test_sources
    basic_test.cpp
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
    set(GR_TEST_LIBRARY_DIRS ${Boost_LIBRARY_DIRS})
    GR_ADD_TEST(${test_name} ${test_name})
endforeach(test_source)

########################################################################
# Python unit tests
########################################################################
include(GrPython)

set(GR_TEST_PYTHON_DIRS ${CMAKE_CURRENT_BINARY_DIR}/../swig)
GR_ADD_TEST(basic_types_test ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/basic_types_test.py)
GR_ADD_TEST(container_types_test ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/container_types_test.py)
GR_ADD_TEST(operator_overloads_test ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/operator_overloads_test.py)

GR_PYTHON_CHECK_MODULE("numpy support" numpy None HAVE_NUMPY)
if (HAVE_NUMPY)
    GR_ADD_TEST(numeric_array_test ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/numeric_array_test.py)
endif()

########################################################################
# Swig custom type test
########################################################################
find_package(SWIG)
find_package(PythonLibs)
if(NOT SWIG_FOUND OR NOT PYTHONLIBS_FOUND)
    return()
endif()
include(GrSwig)
include(GrPython)

list(APPEND GR_SWIG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../include)
list(APPEND GR_SWIG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../swig)
list(APPEND GR_SWIG_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

GR_SWIG_MAKE(foo_bar foo_bar.i)

unset(GR_TEST_PYTHON_DIRS)
list(APPEND GR_TEST_PYTHON_DIRS ${CMAKE_CURRENT_BINARY_DIR}/../swig)
list(APPEND GR_TEST_PYTHON_DIRS ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND GR_TEST_PYTHON_DIRS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
GR_ADD_TEST(custom_type_test ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/custom_type_test.py)
