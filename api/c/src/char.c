#include <paradox-platform/char.h>
#include <ctype.h>

PARADOX_PLATFORM_API const paradox_bool8_t paradox_char8_lower_eq(const paradox_char8_t c1, const paradox_char8_t c2)
{
    return (tolower(c1) == tolower(c2)) ? PARADOX_TRUE : PARADOX_FALSE;
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar8_lower_eq(const paradox_uchar8_t c1, const paradox_uchar8_t c2)
{
    return (tolower(c1) == tolower(c2)) ? PARADOX_TRUE : PARADOX_FALSE;
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar16_lower_eq(const paradox_uchar16_t c1, const paradox_uchar16_t c2)
{
    return (tolower(c1) == tolower(c2)) ? PARADOX_TRUE : PARADOX_FALSE;
}
PARADOX_PLATFORM_API const paradox_bool8_t paradox_uchar32_lower_eq(const paradox_uchar32_t c1, const paradox_uchar32_t c2)
{
    if(c1 < 0x100 && c2 < 0x100)
        return (tolower(c1) == tolower(c2)) ? PARADOX_TRUE : PARADOX_FALSE;
    else return c1 == c2;
}