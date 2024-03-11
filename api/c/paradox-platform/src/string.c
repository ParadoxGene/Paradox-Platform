#include <paradox-platform/string.h>
#include <stdlib.h>
#include <string.h>

size_t paradox_string_calc_alloc_size(size_t len)
{
    size_t next_len = 1;
    while(len >>= 2) next_len <<= 2;
    return next_len * sizeof(paradox_char8_t);
}

PARADOX_PLATFORM_API paradox_string* paradox_create_string(paradox_str_t data)
{
    paradox_string* str = malloc(sizeof(paradox_string));
    str->data_len = strlen(data);
    if(!str->data_len) str->data = NULL;
    else
    {
        str->alloc_len = paradox_string_calc_alloc_size(str->data_len + 1);
        str->data = malloc(str->alloc_len);
        str->data = memcpy(str->data, data, str->data_len);
        str->data[str->data_len] = '\0';
    }
    return str;
}

PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* str)
{
    if(NULL == str) return;
    if(str->data) free(str->data);
    free(str);
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_string_append_str(paradox_string* str, paradox_str_t data)
{
    if(NULL == str) return PARADOX_STRING_BAD_PTR;
    size_t data_len = strlen(data);
    size_t new_alloc_len = paradox_string_calc_alloc_size(str->data_len + data_len + 1);
    if(new_alloc_len > str->alloc_len)
    {
        str->alloc_len = new_alloc_len;
        str->data = realloc(str->data, str->alloc_len);
    }
    memcpy(str->data + str->data_len, data, data_len);
    str->data_len += data_len;
    str->data[str->data_len] = '\0';
    return PARADOX_STRING_OK;
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_string_append_string(paradox_string* dest, paradox_string* src)
{
    if(NULL == dest || NULL == src) return PARADOX_STRING_BAD_PTR;
    size_t new_alloc_len = paradox_string_calc_alloc_size(dest->data_len + src->data_len + 1);
    if(new_alloc_len > dest->alloc_len)
    {
        dest->alloc_len = new_alloc_len;
        dest->data = realloc(dest->data, dest->alloc_len);
    }
    memcpy(dest->data + dest->data_len, src->data, src->data_len);
    dest->data_len += src->data_len;
    dest->data[dest->data_len] = '\0';
    return PARADOX_STRING_OK;
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_string_remove(const size_t pos, const size_t len)
{
    // TODO Later
    return PARADOX_STRING_OK;
}
