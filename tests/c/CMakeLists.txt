cmake_minimum_required(VERSION 3.14)
project(c_unit_testing C)

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_C_EXTENSIONS ON)
endif()

include("${PROJECT_DIR}/cmake/unity.cmake")
add_subdirectory("${PROJECT_DIR}/modules/Unity" "./unity")

add_executable(c_unit_tests "${PROJECT_DIR}/tests/c/unit_testing.c")
set_target_properties(c_unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-platform-c-unit-tests/$<CONFIG>")

target_include_directories(c_unit_tests PRIVATE "${PROJECT_DIR}/api/c/include")
target_link_libraries(c_unit_tests PRIVATE paradox-platform unity::framework)
target_link_directories(c_unit_tests PRIVATE "${PROJECT_DIR}/build/paradox-static/$<CONFIG>")

if(WIN32)
    add_custom_command(TARGET c_unit_tests POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy "${PROJECT_DIR}/build/paradox-shared/$<CONFIG>/paradox-platform.dll" "$<TARGET_FILE_DIR:c_unit_tests>/paradox-platform.dll"
        COMMENT "Copying shared libraries to bin")
endif()