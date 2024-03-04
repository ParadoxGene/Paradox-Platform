#include <paradox-platform/char.h>
#include <ctype.h>

PARADOX_PLATFORM_API paradox_bool8_t paradox_char8_lower_eq(const paradox_char8_t c1, const paradox_char8_t c2)
{ return tolower(c1) == tolower(c2); }
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar8_lower_eq(const paradox_uchar8_t c1, const paradox_uchar8_t c2)
{ return tolower(c1) == tolower(c2); }
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar16_lower_eq(const paradox_uchar16_t c1, const paradox_uchar16_t c2)
{ return tolower(c1) == tolower(c2); }
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_lower_eq(const paradox_uchar32_t c1, const paradox_uchar32_t c2)
{ return (c1 < 0x100 && c2 < 0x100) ? (tolower((int)c1) == tolower((int)c2)) : (c1 == c2); }

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isdigit(const paradox_uchar32_t c)
{ return (c < 0x100) ? (isdigit((int)c) != 0) : PARADOX_FALSE; }

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isalpha(const paradox_uchar32_t c)
{ return (c < 0x100) ? (isalpha((int)c) != 0) : PARADOX_FALSE; }

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isalnum(const paradox_uchar32_t c)
{ return (c < 0x100) ? (isalnum((int)c) != 0) : PARADOX_FALSE; }

PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isbinary(const paradox_uchar32_t c)
{
    switch(c) {
    case '0':
    case '1': return PARADOX_TRUE;
    default : return PARADOX_FALSE; }   
}
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isternary(const paradox_uchar32_t c)
{
    switch(c) {
    case '0':
    case '1':
    case '2': return PARADOX_TRUE;
    default : return PARADOX_FALSE; }   
}
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isoctal(const paradox_uchar32_t c)
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
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_ishex(const paradox_uchar32_t c)
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
PARADOX_PLATFORM_API paradox_bool8_t paradox_uchar32_isunicode(const paradox_uchar32_t c)
{ return c < 0x10FFFF; }

PARADOX_PLATFORM_API paradox_uint32_t paradox_utf8_to_code(paradox_cstr_t utf8, size_t* num_bytes)
{
    if(!utf8) return PARADOX_UTF8_ERR_CODE;    
	paradox_uchar32_t c0 = (paradox_uchar32_t)utf8[0];
	if(c0 <= 0x7F)
	{   // utf-8 one byte char range: 0000 0000 - 0111 1111
		if(num_bytes) *num_bytes = 1;
		return c0;
	}
    else if(0xC0 <= c0 && c0 <= 0xDF)
    {   // utf-8 two byte char range: 1100 0000 - 1101 1111
        paradox_uchar32_t c1 = (paradox_uchar32_t)utf8[1];
        if(0x80 <= c1 && c1 <= 0xBF)
        {
            if(num_bytes) *num_bytes = 2;
            return (paradox_uchar32_t)(((c0 - 0xC0) << 6) + (c1 - 0x80));
        }
    }
    else if(0xE0 <= c0 && c0 <= 0xEF)
    {   // utf-8 three byte char range: 1110 0000 - 1110 1111
        paradox_uchar32_t c1 = (paradox_uchar32_t)utf8[1];
        paradox_uchar32_t c2 = (paradox_uchar32_t)utf8[2];
        if(0x80 <= c1 && c1 <= 0xBF && 0x80 <= c2 && c2 <= 0xBF)
        {
            if(num_bytes) *num_bytes = 3;
            return (paradox_uchar32_t)(((c0 - 0xE0) << 12) + ((c1 - 0x80) << 6) + (c2 - 0x80));
        }
    }
    else if(0xF0 <= c0 && c0 <= 0xF7)
    {   // utf-8 four byte char range: 1111 0000 - 1111 0111
        paradox_uchar32_t c1 = (paradox_uchar32_t)utf8[1];
        paradox_uchar32_t c2 = (paradox_uchar32_t)utf8[2];
        paradox_uchar32_t c3 = (paradox_uchar32_t)utf8[3];
        if(0x80 <= c1 && c1 <= 0xBF && 0x80 <= c2 && c2 <= 0xBF && 0x80 <= c3 && c3 <= 0xBF)
        {
            if(num_bytes) *num_bytes = 4;
            return (paradox_uchar32_t)(((c0 - 0xF0) << 18) + ((c1 - 0x80) << 12) + ((c2 - 0x80) << 6) + (c3 - 0x80));
        }
    }

	// not defined in any utf-8 ranges
	if(num_bytes) *num_bytes = 0;
	return PARADOX_UTF8_ERR_CODE;
}