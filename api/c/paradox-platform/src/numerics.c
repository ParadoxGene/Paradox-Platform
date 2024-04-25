#include <paradox-platform/numerics.h>
#include <paradox-platform/characters.h>
#include <stdlib.h>

PARADOX_PLATFORM_API paradox_str_t paradox_numerics_errno_to_string(paradox_numerics_errno_t err_code)
{
    switch(err_code)
    {
        case PARADOX_NUMERICS_SUCCESS:   return "PARADOX_NUMERICS_SUCCESS";
        case PARADOX_NUMERICS_BAD_SIZE:  return "PARADOX_NUMERICS_BAD_SIZE";
        case PARADOX_NUMERICS_BAD_HEX:   return "PARADOX_NUMERICS_BAD_HEX";
        case PARADOX_NUMERICS_BAD_DEC:   return "PARADOX_NUMERICS_BAD_DEC";
        case PARADOX_NUMERICS_BAD_OCT:   return "PARADOX_NUMERICS_BAD_OCT";
        case PARADOX_NUMERICS_BAD_TER:   return "PARADOX_NUMERICS_BAD_TER";
        case PARADOX_NUMERICS_BAD_BIN:   return "PARADOX_NUMERICS_BAD_BIN";
        case PARADOX_NUMERICS_BAD_PTR:   return "PARADOX_NUMERICS_BAD_PTR";
        case PARADOX_NUMERICS_BAD_ALLOC: return "PARADOX_NUMERICS_BAD_ALLOC";
        default: return "";
    }
}

void skip_hex_prefix(paradox_str_t* hex) { if((*hex)[0] == '0' && ((*hex)[1] == 'x' || (*hex)[1] == 'X')) *hex = (*hex) + 2; }
paradox_numerics_errno_t paradox_hex_to_uint(paradox_str_t hex, size_t len, void* codepoint, const size_t max_len)
{
    // error-checking
    // null check
    if(hex == NULL || codepoint == NULL) return PARADOX_NUMERICS_BAD_PTR;
    // len check
    if( len <= 0) return PARADOX_NUMERICS_BAD_SIZE;
    skip_hex_prefix(&hex); // ignores case insensitive "0x" sequence
    switch(max_len) // type-generic hacky stuff
    {
    case 16:
        *((paradox_uint64_t*)(codepoint)) = 0x0;
        break;
    case 8:
        *((paradox_uint32_t*)(codepoint)) = 0x0;
        break;
    case 4:
        *((paradox_uint16_t*)(codepoint)) = 0x0;
        break;
    case 2:
        *((paradox_uint8_t*)(codepoint)) = 0x0;
        break;
    }

    paradox_bool8_t leading_zero = PARADOX_TRUE;
    size_t index = 0;
    size_t curr_len = 0;
    while(curr_len < len && curr_len <= max_len)
    {  
        paradox_str_char_t c = hex[index++];
        if(!c) return PARADOX_NUMERICS_SUCCESS; // stops accumulating on null character
        // non-hex character found
        if(!paradox_uchar32_ishex(c)) return PARADOX_NUMERICS_BAD_HEX;
        // grabs next digit
        paradox_uint8_t digit;
        if('0' <= c && c <= '9') digit = (paradox_uint8_t)(c - '0');
        else if('a' <= c && c <= 'f') digit = (paradox_uint8_t)(c - 'a' + 10);
        else if('A' <= c && c <= 'F') digit = (paradox_uint8_t)(c - 'A' + 10);
        // skips leading zeros
        if(leading_zero && !digit) continue;
        leading_zero = PARADOX_FALSE;
        // bad size error if too many hex letters are being accumulated
        if(max_len < ++curr_len) return PARADOX_NUMERICS_BAD_SIZE; 

        // multiplies curr value by radix then add next digit
        switch(max_len) // type-generic hacky stuff
        {
        case 16:
            *((paradox_uint64_t*)(codepoint)) = (*((paradox_uint64_t*)(codepoint)) << 4) + digit;
            break;
        case 8:
            *((paradox_uint32_t*)(codepoint)) = (*((paradox_uint32_t*)(codepoint)) << 4) + digit;
            break;
        case 4:
            *((paradox_uint16_t*)(codepoint)) = (*((paradox_uint16_t*)(codepoint)) << 4) + digit;
            break;
        case 2:
            *((paradox_uint8_t*)(codepoint)) = (*((paradox_uint8_t*)(codepoint)) << 4) + digit;
            break;
        }
    }
    // hexadecimal string successfully converted.
    return PARADOX_NUMERICS_SUCCESS;
}

#define paradox_generic_hex_to_uint(definition)\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_hex(const paradox_uint64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_hex(const paradox_uint32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_hex(const paradox_uint16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_hex(const paradox_uint8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; definition; }

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint64(paradox_str_t hex, const size_t len, paradox_uint64_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 16); }

paradox_generic_hex_to_uint(
{
    // error-checking
    // null check
    if(base_str == NULL || len == NULL) return PARADOX_NUMERICS_BAD_PTR;
    if(radix == 16)
    {
         if(codepoint > 0xFFFFFFFFFFFFFFF) *len = 16;
    else if(codepoint > 0xFFFFFFFFFFFFFF) *len = 15;
    else if(codepoint > 0xFFFFFFFFFFFFF) *len = 14;
    else if(codepoint > 0xFFFFFFFFFFFF) *len = 13;
    else if(codepoint > 0xFFFFFFFFFFF) *len = 12;
    else if(codepoint > 0xFFFFFFFFFF) *len = 11;
    else if(codepoint > 0xFFFFFFFFF) *len = 10;
    else if(codepoint > 0xFFFFFFFF) *len = 9;
    else if(codepoint > 0xFFFFFFF) *len = 8;
    else if(codepoint > 0xFFFFFF) *len = 7;
    else if(codepoint > 0xFFFFF) *len = 6;
    else if(codepoint > 0xFFFF) *len = 5;
    else if(codepoint > 0xFFF) *len = 4;
    else if(codepoint > 0xFF) *len = 3;
    else if(codepoint > 0xF) *len = 2;
    else                    *len = 1;
    }
    *base_str = malloc(((*len) + 1) * sizeof(paradox_str_char_t));
    if((*base_str) == NULL) return PARADOX_NUMERICS_BAD_ALLOC;
    (*base_str)[(*len)] = '\0';
    paradox_uint64_t code = codepoint;
    for(size_t i = 0; i < (*len); i++)
    {
        paradox_uint8_t char_code = code % radix;
        if(radix == 16)
        {
            if(0xA <= char_code && char_code <= 0xF) (*base_str)[(*len) - i - 1] = 'A' + char_code - 0xA;
            else (*base_str)[(*len) - i - 1] = '0' + char_code;
        }
        code /= radix;
    }
    return PARADOX_NUMERICS_SUCCESS;
});

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int64(paradox_str_t hex, const size_t len, paradox_int64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_hex(const paradox_int64_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint32(paradox_str_t hex, const size_t len, paradox_uint32_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 8); }
// PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_hex(const paradox_uint32_t codepoint, paradox_str_t* hex, size_t* len)
// {
//     return PARADOX_NUMERICS_SUCCESS;
// }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int32(paradox_str_t hex, const size_t len, paradox_int32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_hex(const paradox_int32_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint16(paradox_str_t hex, const size_t len, paradox_uint16_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 4); }
// PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_hex(const paradox_uint16_t codepoint, paradox_str_t* hex, size_t* len)
// {
//     return PARADOX_NUMERICS_SUCCESS;
// }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int16(paradox_str_t hex, const size_t len, paradox_int16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_hex(const paradox_int16_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint8(paradox_str_t hex, const size_t len, paradox_uint8_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 2); }
// PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_hex(const paradox_uint8_t codepoint, paradox_str_t* hex, size_t* len)
// {
//     return PARADOX_NUMERICS_SUCCESS;
// }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int8(paradox_str_t hex, const size_t len, paradox_int8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_hex(const paradox_int8_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint64(paradox_str_t dec, const size_t len, paradox_uint64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_dec(const paradox_uint64_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int64(paradox_str_t dec, const size_t len, paradox_int64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_dec(const paradox_int64_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint32(paradox_str_t dec, const size_t len, paradox_uint32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_dec(const paradox_uint32_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int32(paradox_str_t dec, const size_t len, paradox_int32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_dec(const paradox_int32_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint16(paradox_str_t dec, const size_t len, paradox_uint16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_dec(const paradox_uint16_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int16(paradox_str_t dec, const size_t len, paradox_int16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_dec(const paradox_int16_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint8(paradox_str_t dec, const size_t len, paradox_uint8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_dec(const paradox_uint8_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int8(paradox_str_t dec, const size_t len, paradox_int8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_dec(const paradox_int8_t codepoint, paradox_str_t* dec, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint64(paradox_str_t oct, const size_t len, paradox_uint64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_oct(const paradox_uint64_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int64(paradox_str_t oct, const size_t len, paradox_int64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_oct(const paradox_int64_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint32(paradox_str_t oct, const size_t len, paradox_uint32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_oct(const paradox_uint32_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int32(paradox_str_t oct, const size_t len, paradox_int32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_oct(const paradox_int32_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint16(paradox_str_t oct, const size_t len, paradox_uint16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_oct(const paradox_uint16_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int16(paradox_str_t oct, const size_t len, paradox_int16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_oct(const paradox_int16_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint8(paradox_str_t oct, const size_t len, paradox_uint8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_oct(const paradox_uint8_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int8(paradox_str_t oct, const size_t len, paradox_int8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_oct(const paradox_int8_t codepoint, paradox_str_t* oct, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint64(paradox_str_t ter, const size_t len, paradox_uint64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_ter(const paradox_uint64_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int64(paradox_str_t ter, const size_t len, paradox_int64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_ter(const paradox_int64_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint32(paradox_str_t ter, const size_t len, paradox_uint32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_ter(const paradox_uint32_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int32(paradox_str_t ter, const size_t len, paradox_int32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_ter(const paradox_int32_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint16(paradox_str_t ter, const size_t len, paradox_uint16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_ter(const paradox_uint16_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int16(paradox_str_t ter, const size_t len, paradox_int16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_ter(const paradox_int16_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint8(paradox_str_t ter, const size_t len, paradox_uint8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_ter(const paradox_uint8_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int8(paradox_str_t ter, const size_t len, paradox_int8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_ter(const paradox_int8_t codepoint, paradox_str_t* ter, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint64(paradox_str_t bin, const size_t len, paradox_uint64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_bin(const paradox_uint64_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int64(paradox_str_t bin, const size_t len, paradox_int64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_bin(const paradox_int64_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint32(paradox_str_t bin, const size_t len, paradox_uint32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_bin(const paradox_uint32_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int32(paradox_str_t bin, const size_t len, paradox_int32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_bin(const paradox_int32_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint16(paradox_str_t bin, const size_t len, paradox_uint16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_bin(const paradox_uint16_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int16(paradox_str_t bin, const size_t len, paradox_int16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_bin(const paradox_int16_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint8(paradox_str_t bin, const size_t len, paradox_uint8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_bin(const paradox_uint8_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int8(paradox_str_t bin, const size_t len, paradox_int8_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_bin(const paradox_int8_t codepoint, paradox_str_t* bin, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
