cmake_minimum_required(VERSION 3.14)
project(paradox-platform-cpp-framework CXX)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_CXX_EXTENSIONS ON)
endif()

file(GLOB_RECURSE CXX_SRC **.cpp)

add_library(
    paradox-platform-framework SHARED
    ${CXX_SRC})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(
        paradox-platform-framework PRIVATE
        -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(
        paradox-platform-framework PRIVATE
        /WX)
endif()

target_compile_definitions(
    paradox-platform-framework PRIVATE    
    PARADOX_PLATFORM_BUILD_DLL)

target_include_directories(
    paradox-platform-framework PUBLIC
    ./include)