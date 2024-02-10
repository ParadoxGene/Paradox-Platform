cmake_minimum_required(VERSION 3.14)
project(paradox-platform-swift-framework Swift)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

file(GLOB_RECURSE SWIFT_SRC **.swift)

add_executable(
    paradox-platform-framework
    ${SWIFT_SRC})