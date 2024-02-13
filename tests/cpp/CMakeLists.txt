cmake_minimum_required(VERSION 3.14)
project(cpp_unit_testing C)

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

include("${PROJECT_DIR}/cmake/googletest.cmake")
add_subdirectory("${PROJECT_DIR}/modules/googletest" "./googletest")

enable_testing()

add_executable(cpp_unit_tests "${PROJECT_DIR}/tests/cpp/unit_testing.cpp")
set_target_properties(cpp_unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-platform-cpp-unit-tests/$<CONFIG>")

target_include_directories(cpp_unit_tests PRIVATE "${PROJECT_DIR}/api/cpp/include")
target_link_libraries(cpp_unit_tests PRIVATE paradox-platform-framework GTest::gtest_main)
target_link_directories(cpp_unit_tests PRIVATE "${PROJECT_DIR}/build/paradox-static/$<CONFIG>")

if(WIN32)
    add_custom_command(TARGET cpp_unit_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_DIR}/build/paradox-shared/$<CONFIG>/paradox-platform-framework.dll" "$<TARGET_FILE_DIR:cpp_unit_tests>/paradox-platform-framework.dll"
        COMMENT "Copying shared libraries to bin")
endif()

include(GoogleTest)
gtest_discover_tests(cpp_unit_tests)