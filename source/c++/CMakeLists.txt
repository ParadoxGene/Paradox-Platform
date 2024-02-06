cmake_minimum_required(VERSION 3.14)
project(Paradox-Platform-C++-Framework CXX)

if(LINUX)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)
elseif(WIN32)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

file(GLOB_RECURSE CXX_SRC **.cpp)

add_library(
    paradox-platform-pp
    ${CXX_SRC}
)

target_include_directories(
    paradox-platform-pp PUBLIC
    ./include
)