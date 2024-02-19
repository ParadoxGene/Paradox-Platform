#ifndef PARADOX_WORKS_C_PLATFORM_CHAR_H
#define PARADOX_WORKS_C_PLATFORM_CHAR_H

#include <paradox-platform/defines.h>
#define PARADOX_UTF8_ERR_CODE (0x10FFFF + 0x1)

PARADOX_PLATFORM_API const paradox_bool8_t paradox_char8_lower_eq(const paradox_char8_t c1, const paradox_char8_t c2);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar8_lower_eq(const paradox_uchar8_t c1, const paradox_uchar8_t c2);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar16_lower_eq(const paradox_uchar16_t c1, const paradox_uchar16_t c2);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_lower_eq(const paradox_uchar32_t c1, const paradox_uchar32_t c2);

PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isdigit(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isalpha(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isalnum(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isbinary(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isternary(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isoctal(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_ishex(const paradox_uchar32_t c);
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isunicode(const paradox_uchar32_t c);

PARADOX_PLATFORM_API const paradox_uint32_t paradox_utf8_to_code(paradox_cstr_t utf8, size_t* num_bytes);

#endif
