#ifndef PARADOX_SOFTWARE_C_HEADER_PLATFORM_DEFINES
#define PARADOX_SOFTWARE_C_HEADER_PLATFORM_DEFINES

#if defined(_WIN32) && defined(_MSC_VER)
    // Microsoft Visual C/C++
    #define PARADOX_MSVC

    #define PARADOX_EXPORT __declspec(dllexport)
    #define PARADOX_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    // GCC or Clang C/C++
    #if defined(__clang__)
        #define PARADOX_CLANG
    #else
        #define PARADOX_GCC
    #endif

    #define PARADOX_EXPORT __attribute__((visibility("default")))
    #define PARADOX_IMPORT
#else
    // Unrecognized Compiler

    #define PARADOX_EXPORT
    #define PARADOX_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#if defined(_WIN32)
    #define PARADOX_WINDOWS_BUILD
    #define PARADOX_DESKTOP_BUILD
#elif defined(__linux__)
    #if defined(__ANDROID__)
        #define PARADOX_ANDROID_BUILD
        #define PARADOX_MOBILE_BUILD
    #else
        #define PARADOX_LINUX_BUILD
        #define PARADOX_DESKTOP_BUILD
    #endif
#endif

#ifdef PARADOX_PLATFORM_STATIC
    #define PARADOX_PLATFORM_API
#elif PARADOX_PLATFORM_BUILD_DLL
    #define PARADOX_PLATFORM_API PARADOX_EXPORT
#else
    #define PARADOX_PLATFORM_API PARADOX_IMPORT
#endif

#define PARADOX_TRUE  1
#define PARADOX_FALSE 0

#include <paradox-platform/sized_types.h>
#include <paradox-platform/common.h>

#endif
