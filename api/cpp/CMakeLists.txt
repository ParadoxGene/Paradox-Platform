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
    paradox-platform-framework
    ${CXX_SRC}
)

target_include_directories(
    paradox-platform-framework PUBLIC
    ./include
)