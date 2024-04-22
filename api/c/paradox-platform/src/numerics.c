#include <paradox-platform/numerics.h>
#include <paradox-platform/characters.h>

PARADOX_PLATFORM_API paradox_str_t paradox_numerics_errno_to_string(paradox_numerics_errno_t err_code)
{
    switch(err_code)
    {
        case PARADOX_NUMERICS_SUCCESS: return "PARADOX_NUMERICS_SUCCESS";
        case PARADOX_NUMERICS_BAD_SIZE: return "PARADOX_NUMERICS_BAD_SIZE";
        case PARADOX_NUMERICS_BAD_HEX: return "PARADOX_NUMERICS_BAD_HEX";
        case PARADOX_NUMERICS_BAD_DEC: return "PARADOX_NUMERICS_BAD_DEC";
        case PARADOX_NUMERICS_BAD_OCT: return "PARADOX_NUMERICS_BAD_OCT";
        case PARADOX_NUMERICS_BAD_TER: return "PARADOX_NUMERICS_BAD_TER";
        case PARADOX_NUMERICS_BAD_BIN: return "PARADOX_NUMERICS_BAD_BIN";
        case PARADOX_NUMERICS_BAD_ALLOC: return "PARADOX_NUMERICS_BAD_ALLOC";
        case PARADOX_NUMERICS_BAD_PTR: return "PARADOX_NUMERICS_BAD_PTR";
        default: return "";
    }
}

// PARADOX_PLATFORM_API paradox_bool8_t paradox_hex_to_uint32(paradox_str_t hex, const size_t len, paradox_uint32_t* code)
// {
//     if(!code) return PARADOX_FALSE;
//     *code = 0;
//     for(size_t i = 0; i < len; ++i)
//     {
//         *code *= 16;
//         paradox_char8_t c = hex[i];
//         if('0' <= c && c <= '9') *code += (paradox_uint8_t)(c - '0');
//         else if('a' <= c && c <= 'f') *code += (paradox_uint8_t)(c - 'a' + 10);
//         else if('A' <= c && c <= 'F') *code += (paradox_uint8_t)(c - 'A' + 10);
//         else return PARADOX_FALSE;
//     }
//     return PARADOX_TRUE;
// }

void skip_hex_prefix(paradox_str_t* hex) { if((*hex)[0] == '0' && ((*hex)[1] == 'x' || (*hex)[1] == 'X')) *hex = (*hex) + 2; }
paradox_numerics_errno_t paradox_hex_to_uint(paradox_str_t hex, const size_t len, void* codepoint, const size_t max_len)
{
    if(hex == NULL || codepoint == NULL) return PARADOX_NUMERICS_BAD_PTR;
    if( len <= 0 || max_len < len) return PARADOX_NUMERICS_BAD_SIZE;
    skip_hex_prefix(&hex);
    switch(max_len)
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
    for(size_t i = 0; i < len; ++i)
    {  
        paradox_str_char_t c = hex[i];
        if(!c) return PARADOX_NUMERICS_BAD_SIZE;
        if(!paradox_uchar32_ishex(c)) return PARADOX_NUMERICS_BAD_HEX;
        paradox_uint8_t digit;
        if('0' <= c && c <= '9') digit = (paradox_uint8_t)(c - '0');
        else if('a' <= c && c <= 'f') digit = (paradox_uint8_t)(c - 'a' + 10);
        else if('A' <= c && c <= 'F') digit = (paradox_uint8_t)(c - 'A' + 10);

        switch(max_len)
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
    return PARADOX_NUMERICS_SUCCESS;
}

PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint64(paradox_str_t hex, const size_t len, paradox_uint64_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 16); }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_hex(const paradox_uint64_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int64(paradox_str_t hex, const size_t len, paradox_int64_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_hex(const paradox_int64_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint32(paradox_str_t hex, const size_t len, paradox_uint32_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 8); }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_hex(const paradox_uint32_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int32(paradox_str_t hex, const size_t len, paradox_int32_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_hex(const paradox_int32_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint16(paradox_str_t hex, const size_t len, paradox_uint16_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 4); }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_hex(const paradox_uint16_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int16(paradox_str_t hex, const size_t len, paradox_int16_t* codepoint)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_hex(const paradox_int16_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint8(paradox_str_t hex, const size_t len, paradox_uint8_t* codepoint) { return paradox_hex_to_uint(hex, len, codepoint, 2); }
PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_hex(const paradox_uint8_t codepoint, paradox_str_t* hex, size_t* len)
{
    return PARADOX_NUMERICS_SUCCESS;
}
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
