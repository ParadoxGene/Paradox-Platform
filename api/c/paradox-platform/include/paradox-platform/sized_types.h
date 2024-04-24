#ifndef OPEN_SOURCE_C_HEADER_PARADOX_PLATFORM_SIZED_TYPES
#define OPEN_SOURCE_C_HEADER_PARADOX_PLATFORM_SIZED_TYPES

#include <inttypes.h>
#include <uchar.h>
#include <wchar.h>

typedef _Bool         paradox_bool8_t;
typedef char          paradox_char8_t;
typedef unsigned char paradox_uchar8_t;
typedef char16_t      paradox_uchar16_t;
typedef char32_t	  paradox_uchar32_t;
typedef wchar_t		  paradox_wchar_t;
typedef char*		  paradox_str_t;
typedef char          paradox_str_char_t;
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

#define PARADOX_UINT64_MAX ((uint64_t)(0xFFFFFFFFFFFFFFFFULL))
#define PARADOX_UINT64_MIN ((uint64_t)(0x0ULL))
#define PARADOX_UINT32_MAX ((uint32_t)(0xFFFFFFFFUL))
#define PARADOX_UINT32_MIN ((uint32_t)(0x0UL))
#define PARADOX_UINT16_MAX ((uint16_t)(0xFFFFU))
#define PARADOX_UINT16_MIN ((uint16_t)(0x0U))
#define PARADOX_UINT8_MAX  ((uint8_t)(0xFFU))
#define PARADOX_UINT8_MIN  ((uint8_t)(0x0U))

#define PARADOX_INT64_MAX ((int64_t)(0x7FFFFFFFFFFFFFFF))
#define PARADOX_INT64_MIN ((int64_t)(0x8000000000000000))
#define PARADOX_INT32_MAX ((int32_t)(0x7FFFFFFF))
#define PARADOX_INT32_MIN ((int32_t)(0x80000000))
#define PARADOX_INT16_MAX ((int16_t)(0x7FFF))
#define PARADOX_INT16_MIN ((int16_t)(0x8000))
#define PARADOX_INT8_MAX  ((int8_t)(0x7F))
#define PARADOX_INT8_MIN  ((int8_t)(0x80))

_Static_assert(sizeof(paradox_bool8_t)   == 1, "paradox_bool8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_char8_t)   == 1, "paradox_char8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_uchar8_t)  == 1, "paradox_uchar8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_uchar16_t) == 2, "paradox_uchar16_t expected size of 2 bytes.");
_Static_assert(sizeof(paradox_uchar32_t) == 4, "paradox_uchar32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_int8_t)    == 1, "paradox_int8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_int16_t)   == 2, "paradox_int16_t expected size of 2 bytes.");
_Static_assert(sizeof(paradox_int32_t)   == 4, "paradox_int32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_int64_t)   == 8, "paradox_int64_t expected size of 8 bytes.");
_Static_assert(sizeof(paradox_uint8_t)   == 1, "paradox_uint8_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_uint16_t)  == 2, "paradox_uint16_t expected size of 2 bytes.");
_Static_assert(sizeof(paradox_uint32_t)  == 4, "paradox_uint32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_uint64_t)  == 8, "paradox_uint64_t expected size of 8 bytes.");
_Static_assert(sizeof(paradox_float32_t) == 4, "paradox_float32_t expected size of 4 bytes.");
_Static_assert(sizeof(paradox_float64_t) == 8, "paradox_float64_t expected size of 8 bytes.");
_Static_assert(sizeof(paradox_byte_t)    == 1, "paradox_byte_t expected size of 1 byte.");
_Static_assert(sizeof(paradox_float_max_t) >= sizeof(paradox_float64_t), "paradox_float_max_t expected size of at least 8 bytes.");

_Static_assert(PARADOX_UINT64_MAX == (uint64_t)(18446744073709551615ULL), "PARADOX_UINT64_MAX expected value of largest unsigned 64 bit integer.");
_Static_assert(PARADOX_UINT64_MIN == (uint64_t)(0),                       "PARADOX_UINT64_MIN expected value of smallest unsigned 64 bit integer.");
_Static_assert(PARADOX_UINT32_MAX == (uint32_t)(4294967295),              "PARADOX_UINT32_MAX expected value of largest unsigned 32 bit integer.");
_Static_assert(PARADOX_UINT32_MIN == (uint32_t)(0),                       "PARADOX_UINT32_MIN expected value of smallest unsigned 32 bit integer.");
_Static_assert(PARADOX_UINT16_MAX == (uint16_t)(65535),                   "PARADOX_UINT16_MAX expected value of largest unsigned 16 bit integer.");
_Static_assert(PARADOX_UINT16_MIN == (uint16_t)(0),                       "PARADOX_UINT16_MIN expected value of smallest unsigned 16 bit integer.");
_Static_assert(PARADOX_UINT8_MAX  == (uint8_t)(255),                      "PARADOX_UINT8_MAX expected value of largest unsigned 8 bit integer.");
_Static_assert(PARADOX_UINT8_MIN  == (uint8_t)(0),                        "PARADOX_UINT8_MIN expected value of smallest unsigned 8 bit integer.");

_Static_assert(PARADOX_INT64_MAX == (int64_t)(9223372036854775807),    "PARADOX_INT64_MAX expected value of largest signed 64 bit integer.");
_Static_assert(PARADOX_INT64_MIN == (int64_t)(-9223372036854775807-1), "PARADOX_INT64_MIN expected value of smallest signed 64 bit integer.");
_Static_assert(PARADOX_INT32_MAX == (int32_t)(2147483647),             "PARADOX_INT32_MAX expected value of largest signed 32 bit integer.");
_Static_assert(PARADOX_INT32_MIN == (int32_t)(-2147483647-1),          "PARADOX_INT32_MIN expected value of smallest signed 32 bit integer.");
_Static_assert(PARADOX_INT16_MAX == (int16_t)(32767),                  "PARADOX_INT16_MAX expected value of largest signed 16 bit integer.");
_Static_assert(PARADOX_INT16_MIN == (int16_t)(-32767-1),               "PARADOX_INT16_MIN expected value of smallest signed 16 bit integer.");
_Static_assert(PARADOX_INT8_MAX  == (int8_t)(127),                     "PARADOX_INT8_MAX expected value of largest signed 8 bit integer.");
_Static_assert(PARADOX_INT8_MIN  == (int8_t)(-127-1),                  "PARADOX_INT8_MIN expected value of smallest signed 8 bit integer.");

#endif