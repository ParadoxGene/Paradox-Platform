cmake_minimum_required(VERSION 3.14)
project(c++_unit_testing C)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

include(${PROJECT_DIR}/cmake/googletest.cmake)
add_subdirectory(${PROJECT_DIR}/modules/googletest googletest)

enable_testing()

add_executable(
    c++_unit_tests
    ${PROJECT_DIR}/tests/c++/unit_testing.cpp
)

target_include_directories(
    c++_unit_tests PRIVATE
    ${PROJECT_DIR}/source/c++/include
)

target_link_libraries(
    c++_unit_tests PRIVATE
    paradox-platform-pp
    GTest::gtest_main
)

target_link_directories(
    c++_unit_tests PRIVATE
    ${PROJECT_DIR}/build/paradox-platform/c++_framework/Debug
)

include(GoogleTest)
gtest_discover_tests(c++_unit_tests)