#include <paradox-platform/string.h>
#include <stdlib.h>
#include <string.h>

#define PARADOX_DEFAULT_STRING_CAPACITY 32

size_t paradox_calc_string_alloc_size(const size_t len)
{
    size_t next_len = 1;
    for(size_t i = len; i > 0 ; i >>= 1) next_len <<= 1;
    if(PARADOX_DEFAULT_STRING_CAPACITY + 1 > next_len) return (PARADOX_DEFAULT_STRING_CAPACITY + 1) * sizeof(paradox_str_char_t);
    else return (next_len) * sizeof(paradox_str_char_t);
}

PARADOX_PLATFORM_API paradox_string* paradox_create_string(paradox_str_t data)
{
    paradox_string* str = malloc(sizeof(paradox_string));
    if(NULL == data)
    {
        str->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_DEFAULT_STRING_CAPACITY);
        str->data = calloc(str->capacity, sizeof(paradox_str_char_t));
        str->len = 0;
    }
    else
    {
        str->len = strlen(data);
        if(!str->len)
        {
            str->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_DEFAULT_STRING_CAPACITY);
            str->data = calloc(str->capacity, sizeof(paradox_str_char_t));
        }
        else
        {
            str->capacity = paradox_calc_string_alloc_size(str->len + 1);
            str->data = malloc(str->capacity);
            str->data = memcpy(str->data, data, str->len);
            str->data[str->len] = '\0';
        }
    }
    
    return str;
}
PARADOX_PLATFORM_API void paradox_clear_string(paradox_string* str)
{
    if(NULL == str) return;
    if((1 + PARADOX_DEFAULT_STRING_CAPACITY) != str->capacity)
    {
        free(str->data);
        str->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_DEFAULT_STRING_CAPACITY);
        str->data = calloc(str->capacity, sizeof(paradox_str_char_t));
        str->len = 0;
    }
    else
    {
        if(str->len)
        {
            memset(str->data, 0, str->len);
            str->len = 0;
        }
    }
}
PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* str)
{
    if(NULL == str) return;
    free(str->data);
    free(str);
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_append_str_to_string(paradox_string* str, paradox_str_t data)
{
    if(NULL == str) return PARADOX_STRING_BAD_PTR;
    size_t len = strlen(data);
    size_t new_capacity = paradox_calc_string_alloc_size(str->len + len + 1);
    if(new_capacity > str->capacity)
    {
        str->capacity = new_capacity;
        str->data = realloc(str->data, str->capacity);
    }
    memcpy(str->data + str->len, data, len);
    str->len += len;
    str->data[str->len] = '\0';
    return PARADOX_STRING_SUCCESS;
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_append_string_to_string(paradox_string* dest, paradox_string* src)
{
    if(NULL == dest || NULL == src) return PARADOX_STRING_BAD_PTR;
    size_t new_capacity = paradox_calc_string_alloc_size(dest->len + src->len + 1);
    if(new_capacity > dest->capacity)
    {
        dest->capacity = new_capacity;
        dest->data = realloc(dest->data, dest->capacity);
    }
    memcpy(dest->data + dest->len, src->data, src->len);
    dest->len += src->len;
    dest->data[dest->len] = '\0';
    return PARADOX_STRING_SUCCESS;
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_remove_from_string(paradox_string* str, const size_t pos, const size_t len)
{
    if(NULL == str) return PARADOX_STRING_BAD_PTR;
    if(str->len < pos + len) return PARADOX_STRING_BAD_RANGE;
    memcpy(str->data + pos, str->data + pos + len, (pos + len) - str->len + 1);
    str->len -= len;
    size_t new_capacity = paradox_calc_string_alloc_size(str->len + 1);
    if(new_capacity > str->capacity)
    {
        str->capacity = new_capacity;
        str->data = realloc(str->data, str->capacity);
    }
    return PARADOX_STRING_SUCCESS;
}
