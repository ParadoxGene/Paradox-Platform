cmake_minimum_required(VERSION 3.14)
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.")
set(PARADOX_BUILD_SYSTEM_VER main)
set(PARADOX_BUILD_SYSTEM_REPO https://github.com/ParadoxGene/Paradox-Build-System.git)
set(PARADOX_BUILD_SYSTEM_FLAGS --version "${PARADOX_BUILD_SYSTEM_VER}" --repo "${PARADOX_BUILD_SYSTEM_REPO}")

if(WIN32)
    execute_process(COMMAND "${PROJECT_DIR}\\config\\windows-build.bat" ${PARADOX_BUILD_SYSTEM_FLAGS})
elseif(LINUX)
    execute_process(COMMAND chmod +x "${PROJECT_DIR}/config/linux-build.sh" COMMAND "${PROJECT_DIR}/config/linux-build.sh" ${PARADOX_BUILD_SYSTEM_FLAGS})
elseif(APPLE)
    execute_process(COMMAND chmod +x "${PROJECT_DIR}/config/macintosh-build.sh" COMMAND "${PROJECT_DIR}/config/macintosh-build.sh" ${PARADOX_BUILD_SYSTEM_FLAGS})
endif()

include("${PROJECT_DIR}/build/build-system/cmake/project.cmake")

paradox_library_options()
paradox_tests_options()
paradox_documentation_options()

project(paradox-project ${PARADOX_BUILD_LANG})
set(PARADOX_PLATFORM_DIR ${PROJECT_DIR})
include("${PROJECT_DIR}/library.cmake")
paradox_add_tests(PARADOX_PLATFORM paradox-platform)