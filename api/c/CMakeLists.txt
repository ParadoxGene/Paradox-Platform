cmake_minimum_required(VERSION 3.14)
project(paradox-platform-c-framework C)

# Use this variable to make the cmakefile once during the call.
set(PARADOX_PLATFORM_C_FRAMEWORK_BUILD CACHE INTERNAL ON PARENT_SCOPE)
set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_C_EXTENSIONS ON)
endif()

file(GLOB_RECURSE C_SRC **.c)

add_library(paradox-platform SHARED ${C_SRC})
set_target_properties(paradox-platform PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-static/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-static/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-shared/$<CONFIG>")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(paradox-platform PRIVATE -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(paradox-platform PRIVATE /WX)
endif()

target_compile_definitions(paradox-platform PRIVATE PARADOX_PLATFORM_BUILD_DLL)
target_include_directories(paradox-platform PUBLIC "./include")