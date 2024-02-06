cmake_minimum_required(VERSION 3.14)
project(paradox-platform-c-framework C)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(LINUX)
    set(CMAKE_C_EXTENSIONS ON)
endif()

file(GLOB_RECURSE C_SRC **.c)

add_library(
    paradox-platform
    ${C_SRC}
)

target_include_directories(
    paradox-platform PUBLIC
    ./include
)