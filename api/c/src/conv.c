#include <paradox-platform/conv.h>

PARADOX_PLATFORM_API const paradox_bool8_t paradox_hex_to_uint32(paradox_str_t hex, const size_t len, paradox_uint32_t* code)
{
    if(!code) return PARADOX_FALSE;
    *code = 0;
    for(size_t i = 0; i < len; ++i)
    {
        *code *= 16;
        paradox_char8_t c = hex[i];
        if('0' <= c && c <= '9') *code += c - '0';
        else if('a' <= c && c <= 'f') *code += c - 'a' + 10;
        else if('A' <= c && c <= 'F') *code += c - 'A' + 10;
        else return PARADOX_FALSE;
    }
    return PARADOX_TRUE;
}