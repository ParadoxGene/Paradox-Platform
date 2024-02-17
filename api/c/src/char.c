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

PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isbinary(const paradox_uchar32_t c)
{
    switch(c) {
    case '0':
    case '1': return PARADOX_TRUE;
    default : return PARADOX_FALSE; }   
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isternary(const paradox_uchar32_t c)
{
    switch(c) {
    case '0':
    case '1':
    case '2': return PARADOX_TRUE;
    default : return PARADOX_FALSE; }   
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isoctal(const paradox_uchar32_t c)
{
    switch(c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7': return PARADOX_TRUE;
    default : return PARADOX_FALSE; }   
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_ishex(const paradox_uchar32_t c)
{
    switch(c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F': return PARADOX_TRUE;
    default : return PARADOX_FALSE; }   
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_isunicode(const paradox_uchar32_t c)
{ return 0x0 <= c && c < 0x10FFFF; }