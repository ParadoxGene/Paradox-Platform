#ifndef PARADOX_WORKS_C_PLATFORM_DEFINES_H
#define PARADOX_WORKS_C_PLATFORM_DEFINES_H

#include <inttypes.h>
#include <uchar.h>
#include <wchar.h>

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
    #define PARADOX_WINDOWS
#elif defined(__linux__)
    #if defined(__ANDROID__)
        #define PARADOX_ANDROID
    #else
        #define PARADOX_LINUX
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

typedef _Bool         paradox_bool8_t;
typedef char          paradox_char8_t;
typedef unsigned char paradox_uchar8_t;
typedef char16_t      paradox_uchar16_t;
typedef char32_t	  paradox_uchar32_t;
typedef wchar_t		  paradox_wchar_t;
typedef char*		  paradox_str_t;
typedef const char*	  paradox_cstr_t;
typedef int8_t		  paradox_int8_t;
typedef int16_t		  paradox_int16_t;
typedef int32_t		  paradox_int32_t;
typedef int64_t		  paradox_int64_t;
typedef uint8_t		  paradox_uint8_t;
typedef uint16_t	  paradox_uint16_t;
typedef uint32_t	  paradox_uint32_t;
typedef uint64_t	  paradox_uint64_t;
typedef float		  paradox_float32_t;
typedef double		  paradox_float64_t;
typedef long double	  paradox_float_max_t;
typedef unsigned char paradox_byte_t;
typedef int           paradox_errno_t;

_Static_assert(sizeof(paradox_bool8_t) == 1, "paradox_bool8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_char8_t) == 1, "paradox_char8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_uchar8_t) == 1, "paradox_uchar8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_uchar16_t) == 2, "paradox_uchar16_t expected size of 2 bytes.");
_Static_assert(sizeof(paradox_uchar32_t) == 4, "paradox_uchar32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_int8_t) == 1, "paradox_int8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_int16_t) == 2, "paradox_int16_t expected size of 2 bytes.");
_Static_assert(sizeof(paradox_int32_t) == 4, "paradox_int32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_int64_t) == 8, "paradox_int64_t expected size of 8 bytes.");
_Static_assert(sizeof(paradox_uint8_t) == 1, "paradox_uint8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_uint16_t) == 2, "paradox_uint16_t expected size of 2 bytes.");
_Static_assert(sizeof(paradox_uint32_t) == 4, "paradox_uint32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_uint64_t) == 8, "paradox_uint64_t expected size of 8 bytes.");
_Static_assert(sizeof(paradox_float32_t) == 4, "paradox_float32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_float64_t) == 8, "paradox_float64_t expected size of 8 bytes.");
_Static_assert(sizeof(paradox_float_max_t) >= sizeof(paradox_float64_t), "paradox_float_max_t expected size of at least 8 bytes.");
_Static_assert(sizeof(paradox_byte_t) == 1, "paradox_byte_t expected size of 1 byte.");

#endif
