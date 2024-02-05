cmake_minimum_required(VERSION 3.14)
project(Paradox-Platform-C-Framework C)

if(LINUX)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS ON)
elseif(WIN32)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
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