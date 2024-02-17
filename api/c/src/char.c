#include <paradox-platform/char.h>
#include <ctype.h>

PARADOX_PLATFORM_API const paradox_bool8_t paradox_char8_lower_eq(const paradox_char8_t c1, const paradox_char8_t c2)
{ return tolower(c1) == tolower(c2); }
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar8_lower_eq(const paradox_uchar8_t c1, const paradox_uchar8_t c2)
{ return tolower(c1) == tolower(c2); }
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar16_lower_eq(const paradox_uchar16_t c1, const paradox_uchar16_t c2)
{ return tolower(c1) == tolower(c2); }
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_lower_eq(const paradox_uchar32_t c1, const paradox_uchar32_t c2)
{ return (isascii(c1) && isascii(c2)) ? (tolower(c1) == tolower(c2)) : (c1 == c2); }

PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isdigit(const paradox_uchar32_t c)
{ return isascii(c) ? (isdigit(c) != 0) : PARADOX_FALSE; }

PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isalpha(const paradox_uchar32_t c)
{ return isascii(c) ? (isalpha(c) != 0) : PARADOX_FALSE; }

PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isalnum(const paradox_uchar32_t c)
{ return isascii(c) ? (isalnum(c) != 0) : PARADOX_FALSE; }