cmake_minimum_required(VERSION 3.25)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

option(PARADOX_PLATFORM_BUILD_LIBS "Build the libs" ON)
option(PARADOX_PLATFORM_BUILD_TESTS "Build the test cases" OFF)
option(PARADOX_PLATFORM_BUILD_DOCS "Build the documentation" OFF)

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.")

set(PARADOX_PLATFORM_BUILD_SYSTEM_VER main)
set(PARADOX_PLATFORM_BUILD_SYSTEM_REPO https://github.com/ParadoxGene/Paradox-Build-System.git)
set(PARADOX_PLATFORM_BUILD_SYSTEM_FLAGS --version "${PARADOX_PLATFORM_BUILD_SYSTEM_VER}" --repo "${PARADOX_PLATFORM_BUILD_SYSTEM_REPO}")

if(WIN32)
    execute_process(
        COMMAND "${PROJECT_DIR}\\config\\windows-build.bat" ${PARADOX_PLATFORM_BUILD_SYSTEM_FLAGS})
elseif(LINUX)
    execute_process(
        COMMAND chmod +x "${PROJECT_DIR}/config/linux-build.sh"
        COMMAND "${PROJECT_DIR}/config/linux-build.sh" ${PARADOX_PLATFORM_BUILD_SYSTEM_FLAGS})
elseif(APPLE)
    execute_process(
        COMMAND chmod +x "${PROJECT_DIR}/config/macintosh-build.sh"
        COMMAND "${PROJECT_DIR}/config/macintosh-build.sh" ${PARADOX_PLATFORM_BUILD_SYSTEM_FLAGS})
endif()

include("${PROJECT_DIR}/build/build-system/cmake/library-config.cmake")

if(PARADOX_LANGUAGE STREQUAL "c")
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS ON)
    project(PARADOX_PLATFORM C)
elseif(PARADOX_LANGUAGE STREQUAL "cpp")
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS ON)
    project(PARADOX_PLATFORM CXX)
endif()

paradox_add_library(paradox-platform PARADOX_PLATFORM)
paradox_add_tests(paradox-platform PARADOX_PLATFORM "paradox-platform")
