#ifndef PARADOX_SOFTWARE_C_HEADER_PLATFORM_CHARACTERS
#define PARADOX_SOFTWARE_C_HEADER_PLATFORM_CHARACTERS

#include <paradox-platform/defines.h>
#define PARADOX_UTF8_ERR_CODE (0x10FFFF + 0x1)

PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_lower_eq(const paradox_char8_t c1, const paradox_char8_t c2);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_lower_eq(const paradox_uchar8_t c1, const paradox_uchar8_t c2);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_lower_eq(const paradox_uchar16_t c1, const paradox_uchar16_t c2);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_lower_eq(const paradox_uchar32_t c1, const paradox_uchar32_t c2);

PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_isdigit(const paradox_char8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_isalpha(const paradox_char8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_isalnum(const paradox_char8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_isbinary(const paradox_char8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_isternary(const paradox_char8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_isoctal(const paradox_char8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_ishex(const paradox_char8_t c);

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_isdigit(const paradox_uchar8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_isalpha(const paradox_uchar8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_isalnum(const paradox_uchar8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_isbinary(const paradox_uchar8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_isternary(const paradox_uchar8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_isoctal(const paradox_uchar8_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_ishex(const paradox_uchar8_t c);

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_isdigit(const paradox_uchar16_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_isalpha(const paradox_uchar16_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_isalnum(const paradox_uchar16_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_isbinary(const paradox_uchar16_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_isternary(const paradox_uchar16_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_isoctal(const paradox_uchar16_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_ishex(const paradox_uchar16_t c);

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isdigit(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isalpha(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isalnum(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isbinary(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isternary(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isoctal(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_ishex(const paradox_uchar32_t c);
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isunicode(const paradox_uchar32_t c);

PARADOX_PLATFORM_API paradox_uint32_t paradox_utf8_to_codepoint(paradox_cstr_t utf8, size_t* num_bytes);
PARADOX_PLATFORM_API paradox_bool8_t paradox_codepoint_to_utf8(const paradox_uint32_t code, paradox_str_t utf8);

#endif
