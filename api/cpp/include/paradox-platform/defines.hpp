#ifndef PARADOX_WORKS_CPP_PLATFORM_DEFINES_HPP
#define PARADOX_WORKS_CPP_PLATFORM_DEFINES_HPP

#include <inttypes.h>
#include <uchar.h>
#include <wchar.h>
#include <string>

namespace Paradox::DataType
{
    typedef bool		  B8;
	typedef char		  C8;
	typedef unsigned char UC8;
	typedef char16_t	  UC16;
	typedef char32_t	  UC32;
	typedef wchar_t		  WC_t;
	typedef char*		  Str_t;
	typedef const char*	  CStr_t;
	typedef std::string   String_t;
	typedef int8_t		  I8;
	typedef int16_t		  I16;
	typedef int32_t		  I32;
	typedef int64_t		  I64;
	typedef uint8_t		  U8;
	typedef uint16_t	  U16;
	typedef uint32_t	  U32;
	typedef uint64_t	  U64;
	typedef float		  F32;
	typedef double		  F64;
	typedef long double	  FMax_t;
	typedef unsigned char Byte_t;

    static_assert(sizeof(B8) == 1, "B8 expected size of 1 byte.");
	static_assert(sizeof(C8) == 1, "C8 expected size of 1 byte.");
	static_assert(sizeof(UC8) == 1, "UC8 expected size of 1 byte.");
	static_assert(sizeof(UC16) == 2, "UC16 expected size of 2 bytes.");
	static_assert(sizeof(UC32) == 4, "UC32 expected size of 4 bytes.");
	static_assert(sizeof(I8) == 1, "I8 expected size of 1 byte.");
	static_assert(sizeof(I16) == 2, "I16 expected size of 2 bytes.");
	static_assert(sizeof(I32) == 4, "I32 expected size of 4 bytes.");
	static_assert(sizeof(I64) == 8, "I64 expected size of 8 bytes.");
	static_assert(sizeof(U8) == 1, "U8 expected size of 1 byte.");
	static_assert(sizeof(U16) == 2, "U16 expected size of 2 bytes.");
	static_assert(sizeof(U32) == 4, "U32 expected size of 4 bytes.");
	static_assert(sizeof(U64) == 8, "U64 expected size of 8 bytes.");
	static_assert(sizeof(F32) == 4, "F32 expected size of 4 bytes.");
	static_assert(sizeof(F64) == 8, "F64 expected size of 8 bytes.");
	static_assert(sizeof(FMax_t) >= sizeof(F64), "FMax_t expected size of at least 8 bytes.");
	static_assert(sizeof(Byte_t) == 1, "Byte_t expected size of 1 byte.");
}

#endif