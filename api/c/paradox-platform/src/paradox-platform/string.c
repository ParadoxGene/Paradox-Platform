#include <paradox-platform/string.h>
#include <stdlib.h>
#include <string.h>

#define PARADOX_DEFAULT_STRING_CAPACITY 32

size_t paradox_calc_string_alloc_size(const size_t size)
{
    size_t next_size = 1;
    for(size_t i = size; i > 0 ; i >>= 1) next_size <<= 1;
    if(PARADOX_DEFAULT_STRING_CAPACITY + 1 > next_size) return (PARADOX_DEFAULT_STRING_CAPACITY + 1) * sizeof(paradox_str_char_t);
    else return (next_size) * sizeof(paradox_str_char_t);
}

PARADOX_PLATFORM_API paradox_string* paradox_create_string()
{
    paradox_string* str = malloc(sizeof(paradox_string));
    str->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_DEFAULT_STRING_CAPACITY);
    str->data = calloc(str->capacity, sizeof(paradox_str_char_t));
    str->size = 0;
    return str;
}

PARADOX_PLATFORM_API paradox_string* paradox_create_string_from_str(paradox_str_t data, const size_t size)
{
    paradox_string* str = malloc(sizeof(paradox_string));
    if(NULL == data || !size)
    {
        str->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_DEFAULT_STRING_CAPACITY);
        str->data = calloc(str->capacity, sizeof(paradox_str_char_t));
        str->size = 0;
    }
    else
    {
        str->size = size;
        str->capacity = paradox_calc_string_alloc_size(str->size + 1);
        str->data = malloc(str->capacity);
        str->data = memcpy(str->data, data, str->size);
        str->data[str->size] = '\0';
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
        str->size = 0;
    }
    else
    {
        if(str->size)
        {
            memset(str->data, 0, str->size);
            str->size = 0;
        }
    }
}
PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* str)
{
    if(NULL == str) return;
    free(str->data);
    free(str);
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_append_str_to_string(paradox_string* str, paradox_str_t data, const size_t size)
{
    if(NULL == str) return PARADOX_STRING_BAD_PTR;
    size_t new_capacity = paradox_calc_string_alloc_size(str->size + size + 1);
    if(new_capacity > str->capacity)
    {
        str->capacity = new_capacity;
        str->data = realloc(str->data, str->capacity);
    }
    memcpy(str->data + str->size, data, size);
    str->size += size;
    str->data[str->size] = '\0';
    return PARADOX_STRING_SUCCESS;
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_append_string_to_string(paradox_string* dest, paradox_string* src)
{
    if(NULL == dest || NULL == src) return PARADOX_STRING_BAD_PTR;
    size_t new_capacity = paradox_calc_string_alloc_size(dest->size + src->size + 1);
    if(new_capacity > dest->capacity)
    {
        dest->capacity = new_capacity;
        dest->data = realloc(dest->data, dest->capacity);
    }
    memcpy(dest->data + dest->size, src->data, src->size);
    dest->size += src->size;
    dest->data[dest->size] = '\0';
    return PARADOX_STRING_SUCCESS;
}

PARADOX_PLATFORM_API paradox_string_errno_t paradox_remove_from_string(paradox_string* str, const size_t pos, const size_t size)
{
    if(NULL == str) return PARADOX_STRING_BAD_PTR;
    if(str->size < pos + size) return PARADOX_STRING_BAD_RANGE;
    memcpy(str->data + pos, str->data + pos + size, (pos + size) - str->size + 1);
    str->size -= size;
    size_t new_capacity = paradox_calc_string_alloc_size(str->size + 1);
    if(new_capacity > str->capacity)
    {
        str->capacity = new_capacity;
        str->data = realloc(str->data, str->capacity);
    }
    return PARADOX_STRING_SUCCESS;
}
