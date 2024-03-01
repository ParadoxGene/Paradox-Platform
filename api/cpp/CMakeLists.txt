cmake_minimum_required(VERSION 3.14)
project(paradox-platform-cpp-framework CXX)

# Use this variable to make the cmakefile once during the call.
set(PARADOX_PLATFORM_CPP_FRAMEWORK_BUILD CACHE INTERNAL ON PARENT_SCOPE)
set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

file(GLOB_RECURSE CXX_SRC **.cpp)

add_library(paradox-platform-framework SHARED ${CXX_SRC})
set_target_properties(paradox-platform-framework PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-static/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-static/$<CONFIG>"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../paradox-shared/$<CONFIG>")

target_compile_options(paradox-platform-framework PRIVATE ${PARADOX_DEBUG_FLAGS})

target_compile_definitions(paradox-platform-framework PRIVATE PARADOX_PLATFORM_BUILD_DLL)
target_include_directories(paradox-platform-framework PUBLIC "./include")