#ifndef PARADOX_WORKS_C_PLATFORM_DEFINES_H
#define PARADOX_WORKS_C_PLATFORM_DEFINES_H

#include <inttypes.h>
#include <uchar.h>
#include <wchar.h>

typedef bool		  paradox_bool8_t;
typedef char		  paradox_char8_t;
typedef unsigned char paradox_uchar8_t;
typedef char16_t	  paradox_uchar16_t;
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

static_assert(sizeof(paradox_bool8_t) == 1, "paradox_bool8_t expected size of 1 byte.");
static_assert(sizeof(paradox_char8_t) == 1, "paradox_char8_t expected size of 1 byte.");
static_assert(sizeof(paradox_uchar8_t) == 1, "paradox_uchar8_t expected size of 1 byte.");
static_assert(sizeof(paradox_uchar16_t) == 2, "paradox_uchar16_t expected size of 2 bytes.");
static_assert(sizeof(paradox_uchar32_t) == 4, "paradox_uchar32_t expected size of 4 bytes.");
static_assert(sizeof(paradox_int8_t) == 1, "paradox_int8_t expected size of 1 byte.");
static_assert(sizeof(paradox_int16_t) == 2, "paradox_int16_t expected size of 2 bytes.");
static_assert(sizeof(paradox_int32_t) == 4, "paradox_int32_t expected size of 4 bytes.");
static_assert(sizeof(paradox_int64_t) == 8, "paradox_int64_t expected size of 8 bytes.");
static_assert(sizeof(paradox_uint8_t) == 1, "paradox_uint8_t expected size of 1 byte.");
static_assert(sizeof(paradox_uint16_t) == 2, "paradox_uint16_t expected size of 2 bytes.");
static_assert(sizeof(paradox_uint32_t) == 4, "paradox_uint32_t expected size of 4 bytes.");
static_assert(sizeof(paradox_uint64_t) == 8, "paradox_uint64_t expected size of 8 bytes.");
static_assert(sizeof(paradox_float32_t) == 4, "paradox_float32_t expected size of 4 bytes.");
static_assert(sizeof(paradox_float64_t) == 8, "paradox_float64_t expected size of 8 bytes.");
static_assert(sizeof(paradox_float_max_t) >= sizeof(paradox_float64_t), "paradox_float_max_t expected size of at least 8 bytes.");
static_assert(sizeof(paradox_byte_t) == 1, "paradox_byte_t expected size of 1 byte.");

#endif