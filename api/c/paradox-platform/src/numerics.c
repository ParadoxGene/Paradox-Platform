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
paradox_bool8_t has_neg_sign(paradox_str_t* base_str)
{
    if('-' == (*base_str)[0])
    {
        ++(*base_str);
        return PARADOX_TRUE;
    }
    return PARADOX_FALSE;
}
void skip_hex_prefix(paradox_str_t* hex) { if('0' == (*hex)[0] && ('x' == (*hex)[1] || 'X' == (*hex)[1])) *hex = (*hex) + 2; }
void skip_oct_prefix(paradox_str_t* oct) { if('0' == (*oct)[0] && ('o' == (*oct)[1] || 'O' == (*oct)[1])) *oct = (*oct) + 2; }

#define paradox_generic_integral_type_to_radix_string(definition)\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint64(paradox_str_t base_str, const size_t len, paradox_uint64_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 64; paradox_uint64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint32(paradox_str_t base_str, const size_t len, paradox_uint32_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 32; paradox_uint32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint16(paradox_str_t base_str, const size_t len, paradox_uint16_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 16; paradox_uint16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_uint8(paradox_str_t base_str, const size_t len, paradox_uint8_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 8; paradox_uint8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint64(paradox_str_t base_str, const size_t len, paradox_uint64_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 64; paradox_uint64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint32(paradox_str_t base_str, const size_t len, paradox_uint32_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 32; paradox_uint32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint16(paradox_str_t base_str, const size_t len, paradox_uint16_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 16; paradox_uint16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_uint8(paradox_str_t base_str, const size_t len, paradox_uint8_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 8; paradox_uint8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint64(paradox_str_t base_str, const size_t len, paradox_uint64_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 64; paradox_uint64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint32(paradox_str_t base_str, const size_t len, paradox_uint32_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 32; paradox_uint32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint16(paradox_str_t base_str, const size_t len, paradox_uint16_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 16; paradox_uint16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_uint8(paradox_str_t base_str, const size_t len, paradox_uint8_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 8; paradox_uint8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint64(paradox_str_t base_str, const size_t len, paradox_uint64_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 64; paradox_uint64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint32(paradox_str_t base_str, const size_t len, paradox_uint32_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 32; paradox_uint32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint16(paradox_str_t base_str, const size_t len, paradox_uint16_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 16; paradox_uint16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_uint8(paradox_str_t base_str, const size_t len, paradox_uint8_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 8; paradox_uint8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint64(paradox_str_t base_str, const size_t len, paradox_uint64_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 64; paradox_uint64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint32(paradox_str_t base_str, const size_t len, paradox_uint32_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 32; paradox_uint32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint16(paradox_str_t base_str, const size_t len, paradox_uint16_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 16; paradox_uint16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_uint8(paradox_str_t base_str, const size_t len, paradox_uint8_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 8; paradox_uint8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_FALSE; definition; }\
    \
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int64(paradox_str_t base_str, const size_t len, paradox_int64_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 64; paradox_int64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int32(paradox_str_t base_str, const size_t len, paradox_int32_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 32; paradox_int32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int16(paradox_str_t base_str, const size_t len, paradox_int16_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 16; paradox_int16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_hex_to_int8(paradox_str_t base_str, const size_t len, paradox_int8_t* codepoint)\
    { const paradox_uint8_t radix = 16; const paradox_uint8_t bit_sz = 8; paradox_int8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int64(paradox_str_t base_str, const size_t len, paradox_int64_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 64; paradox_int64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int32(paradox_str_t base_str, const size_t len, paradox_int32_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 32; paradox_int32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int16(paradox_str_t base_str, const size_t len, paradox_int16_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 16; paradox_int16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_dec_to_int8(paradox_str_t base_str, const size_t len, paradox_int8_t* codepoint)\
    { const paradox_uint8_t radix = 10; const paradox_uint8_t bit_sz = 8; paradox_int8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int64(paradox_str_t base_str, const size_t len, paradox_int64_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 64; paradox_int64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int32(paradox_str_t base_str, const size_t len, paradox_int32_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 32; paradox_int32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int16(paradox_str_t base_str, const size_t len, paradox_int16_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 16; paradox_int16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_oct_to_int8(paradox_str_t base_str, const size_t len, paradox_int8_t* codepoint)\
    { const paradox_uint8_t radix = 8; const paradox_uint8_t bit_sz = 8; paradox_int8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int64(paradox_str_t base_str, const size_t len, paradox_int64_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 64; paradox_int64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int32(paradox_str_t base_str, const size_t len, paradox_int32_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 32; paradox_int32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int16(paradox_str_t base_str, const size_t len, paradox_int16_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 16; paradox_int16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_ter_to_int8(paradox_str_t base_str, const size_t len, paradox_int8_t* codepoint)\
    { const paradox_uint8_t radix = 3; const paradox_uint8_t bit_sz = 8; paradox_int8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int64(paradox_str_t base_str, const size_t len, paradox_int64_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 64; paradox_int64_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int32(paradox_str_t base_str, const size_t len, paradox_int32_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 32; paradox_int32_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int16(paradox_str_t base_str, const size_t len, paradox_int16_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 16; paradox_int16_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_bin_to_int8(paradox_str_t base_str, const size_t len, paradox_int8_t* codepoint)\
    { const paradox_uint8_t radix = 2; const paradox_uint8_t bit_sz = 8; paradox_int8_t code_cap; const paradox_bool8_t allow_neg_sign = PARADOX_TRUE; definition; }

paradox_generic_integral_type_to_radix_string(
{
    // error-checking | null check
    if(NULL == base_str || NULL == codepoint) return PARADOX_NUMERICS_BAD_PTR;
    // len check
    if( len <= 0) return PARADOX_NUMERICS_BAD_SIZE;
    const paradox_bool8_t neg_sign = allow_neg_sign && has_neg_sign(&base_str); // ignores case insensitive "0x" sequence
    if(16 == radix) skip_hex_prefix(&base_str); // ignores case insensitive "0x" sequence
    if(8 == radix) skip_oct_prefix(&base_str); // ignores case insensitive "0o" sequence
    *codepoint = 0;

    size_t index = 0;
    size_t curr_len = 0;

    switch(radix)
    {
    case 16: {
        switch(bit_sz)
        {
        case 64: {
            if(allow_neg_sign) {}
            else code_cap = 1152921504606846975ULL;
            break;
        }
        case 32: {
            if(allow_neg_sign) {}
            else code_cap = 268435455ULL;
            break;
        }
        case 16: {
            if(allow_neg_sign) {}
            else code_cap = 4095ULL;
            break;
        }
        case 8: {
            if(allow_neg_sign) {}
            else code_cap = 15ULL;
            break;
        }
        };
        break;
    }
    case 10: {
        switch(bit_sz)
        {
        case 64: {
            break;
        }
        case 32: {
            break;
        }
        case 16: {
            break;
        }
        case 8: {
            break;
        }
        };
        break;
    }
    case 8: {
        switch(bit_sz)
        {
        case 64: {
            break;
        }
        case 32: {
            break;
        }
        case 16: {
            break;
        }
        case 8: {
            break;
        }
        };
        break;
    }
    case 3: {
        switch(bit_sz)
        {
        case 64: {
            break;
        }
        case 32: {
            break;
        }
        case 16: {
            break;
        }
        case 8: {
            break;
        }
        };
        break;
    }
    case 2: {
        switch(bit_sz)
        {
        case 64: {
            break;
        }
        case 32: {
            break;
        }
        case 16: {
            break;
        }
        case 8: {
            break;
        }
        };
        break;
    }
    };
    
    while(curr_len++ < len)
    {
        // bad size error if too many radix value are being accumulated
        if((!neg_sign && *codepoint > code_cap) || (neg_sign && *codepoint < code_cap))
        {
            switch(radix)
            {
            case 16: return PARADOX_NUMERICS_BAD_HEX;
            case 10: return PARADOX_NUMERICS_BAD_DEC;
            case 8: return PARADOX_NUMERICS_BAD_OCT;
            case 3: return PARADOX_NUMERICS_BAD_TER;
            case 2: return PARADOX_NUMERICS_BAD_BIN;
            }
        }
        
        paradox_str_char_t c = base_str[index++];
        if(!c) return PARADOX_NUMERICS_SUCCESS; // stops accumulating on null character
        switch(radix)
        {
            case 16:
            {
                // non-hex character found
                if(!paradox_uchar32_ishex(c)) return PARADOX_NUMERICS_BAD_HEX;
                break;
            }
            case 10:
            {
                // non-dec character found
                if(!paradox_uchar32_isdigit(c)) return PARADOX_NUMERICS_BAD_DEC;
                break;
            }
            case 8:
            {
                // non-oct character found
                if(!('0' <= c && c <= '7')) return PARADOX_NUMERICS_BAD_DEC;
                break;
            }
            case 3:
            {
                // non-ter character found
                if(!('0' <= c && c <= '2')) return PARADOX_NUMERICS_BAD_TER;
                break;
            }
            case 2:
            {
                // non-bin character found
                if(!('0' <= c && c <= '1')) return PARADOX_NUMERICS_BAD_BIN;
                break;
            }
        }
        
        // grabs next digit
        paradox_uint8_t digit;
        if('0' <= c && c <= '9') digit = (paradox_uint8_t)(c - '0');
        else if('a' <= c && c <= 'f') digit = (paradox_uint8_t)(c - 'a' + 10);
        else if('A' <= c && c <= 'F') digit = (paradox_uint8_t)(c - 'A' + 10);
        // multiplies curr value by radix then add next digit
        *codepoint = *codepoint * radix + digit;
    }
    // hexadecimal string successfully converted.
    return PARADOX_NUMERICS_SUCCESS;
});

#define paradox_generic_radix_string_to_integral_type(definition)\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_hex(const paradox_uint64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_uint64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_hex(const paradox_uint32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_uint32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_hex(const paradox_uint16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_uint16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_hex(const paradox_uint8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_uint8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_dec(const paradox_uint64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_uint64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_dec(const paradox_uint32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_uint32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_dec(const paradox_uint16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_uint16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_dec(const paradox_uint8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_uint8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_oct(const paradox_uint64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_uint64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_oct(const paradox_uint32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_uint32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_oct(const paradox_uint16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_uint16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_oct(const paradox_uint8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_uint8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_ter(const paradox_uint64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_uint64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_ter(const paradox_uint32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_uint32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_ter(const paradox_uint16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_uint16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_ter(const paradox_uint8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_uint8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint64_to_bin(const paradox_uint64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_uint64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint32_to_bin(const paradox_uint32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_uint32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint16_to_bin(const paradox_uint16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_uint16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_uint8_to_bin(const paradox_uint8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_uint8_t code = codepoint; definition; }\
    \
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_hex(const paradox_int64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_int64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_hex(const paradox_int32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_int32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_hex(const paradox_int16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_int16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_hex(const paradox_int8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 16; paradox_int8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_dec(const paradox_int64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_int64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_dec(const paradox_int32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_int32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_dec(const paradox_int16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_int16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_dec(const paradox_int8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 10; paradox_int8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_oct(const paradox_int64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_int64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_oct(const paradox_int32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_int32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_oct(const paradox_int16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_int16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_oct(const paradox_int8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 8; paradox_int8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_ter(const paradox_int64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_int64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_ter(const paradox_int32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_int32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_ter(const paradox_int16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_int16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_ter(const paradox_int8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 3; paradox_int8_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int64_to_bin(const paradox_int64_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_int64_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int32_to_bin(const paradox_int32_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_int32_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int16_to_bin(const paradox_int16_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_int16_t code = codepoint; definition; }\
    PARADOX_PLATFORM_API paradox_numerics_errno_t paradox_int8_to_bin(const paradox_int8_t codepoint, paradox_str_t* base_str, size_t* len)\
    { const paradox_uint8_t radix = 2; paradox_int8_t code = codepoint; definition; }

paradox_generic_radix_string_to_integral_type(
{
    // error-checking | null check
    if(NULL == base_str || NULL == len) return PARADOX_NUMERICS_BAD_PTR;

    if(0 == code) *len = 1;
    else
    {
        *len = (code < 0 ? 2 : 1);
        while(code /= radix) ++(*len);
        code = codepoint;
    }

    *base_str = malloc(((*len) + 1) * sizeof(paradox_str_char_t));
    if(NULL == (*base_str)) return PARADOX_NUMERICS_BAD_ALLOC;
    if(code < 0) (*base_str)[0] = '-';
    (*base_str)[*len] = '\0';
    for(size_t i = 0 + (code < 0); i < (*len); i++)
    {
        paradox_uint8_t char_code = (code % radix + radix) % radix;
        if(0xA <= char_code && char_code <= 0xF) (*base_str)[(*len) - i - 1] = 'A' + char_code - 0xA;
        else (*base_str)[(*len) - i - 1] = '0' + char_code;
        code /= radix;
    }
    return PARADOX_NUMERICS_SUCCESS;
});