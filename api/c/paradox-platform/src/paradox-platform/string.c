#include <paradox-platform/string.h>
#include <stdlib.h>
#include <string.h>

#define PARADOX_PLATFORM_DEFAULT_STRING_CAPACITY 32

// Auxiliary
size_t paradox_calculate_string_capacity(const size_t size) {
    size_t next_size = 1;
    for(size_t i = size; i > 0 ; i >>= 1) next_size <<= 1;
    if(PARADOX_PLATFORM_DEFAULT_STRING_CAPACITY + 1 > next_size) return (PARADOX_PLATFORM_DEFAULT_STRING_CAPACITY + 1) * sizeof(paradox_str_char_t);
    else return (next_size) * sizeof(paradox_str_char_t);
}

PARADOX_PLATFORM_API paradox_string* paradox_create_string(const paradox_str_t src, const size_t size) {
    paradox_string* str = malloc(sizeof(paradox_string));
    if(!src || !size) {
        str->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_PLATFORM_DEFAULT_STRING_CAPACITY);
        str->data = calloc(str->capacity, sizeof(paradox_str_char_t));
        str->size = 0;
    }
    else {
        str->size = size;
        str->capacity = paradox_calculate_string_capacity(str->size + 1);
        str->data = malloc(str->capacity);
        str->data = memcpy(str->data, src, size);
        str->data[size] = '\0';
    }
    
    return str;
}

PARADOX_PLATFORM_API void paradox_clear_string(paradox_string* src) {
    if(!src) return;
    if((1 + PARADOX_PLATFORM_DEFAULT_STRING_CAPACITY) != src->capacity) {
        free(src->data);
        src->capacity = sizeof(paradox_str_char_t)*(1 + PARADOX_PLATFORM_DEFAULT_STRING_CAPACITY);
        src->data = calloc(src->capacity, sizeof(paradox_str_char_t));
        src->size = 0;
    }
    else if(src->size) {
        memset(src->data, 0, src->size);
        src->size = 0;
    }
}

PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* src) {
    if(!src) return;
    free(src->data);
    free(src);
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_copy_string(paradox_string* dest, const paradox_string* src) {
    if(!src || !dest || !src->data) return PARADOX_FALSE;
    paradox_str_t new_data = malloc(src->capacity);
    if(!new_data) return PARADOX_FALSE;
    if(src->data != dest->data) paradox_clear_string(dest);
    memcpy(new_data, src->data, src->size + 1);
    dest->data = new_data;
    dest->size = src->size;
    dest->capacity = src->capacity;
    return PARADOX_TRUE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_append_string(paradox_string* dest, const paradox_string* src) {
    if(!dest || !src) return PARADOX_FALSE;
    size_t new_capacity = paradox_calculate_string_capacity(dest->size + src->size + 1);
    if(new_capacity > dest->capacity) {
        paradox_str_t new_data = realloc(dest->data, new_capacity);
        if(!new_data) return PARADOX_FALSE;
        dest->data = new_data;
        dest->capacity = new_capacity;
    }
    memcpy(dest->data + dest->size, src->data, src->size);
    dest->size += src->size;
    dest->data[dest->size] = '\0';
    return PARADOX_TRUE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_append_str2string(paradox_string* dest, const paradox_str_t src, const size_t size) {
    if(!dest || !src || !size) return PARADOX_FALSE;
    size_t new_capacity = paradox_calculate_string_capacity(dest->size + size + 1);
    if(new_capacity > dest->capacity) {
        paradox_str_t new_data = realloc(dest->data, new_capacity);
        if(!new_data) return PARADOX_FALSE;
        dest->data = new_data;
        dest->capacity = new_capacity;
    }
    memcpy(dest->data + dest->size, src, size);
    dest->size += size;
    dest->data[dest->size] = '\0';
    return PARADOX_TRUE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_insert_string(paradox_string* dest, const paradox_string* src, const size_t pos) {
    if(!dest || !src || pos > dest->size) return PARADOX_FALSE;
    size_t new_capacity = paradox_calculate_string_capacity(dest->size + src->size + 1);
    if(new_capacity > dest->capacity) {
        paradox_str_t new_data = realloc(dest->data, new_capacity);
        if(!new_data) return PARADOX_FALSE;
        dest->data = new_data;
        dest->capacity = new_capacity;
    }
    if(pos == dest->size) memcpy(dest->data + dest->size, src, src->size);
    else {
        const size_t rightmost_size = dest->size - pos;
        paradox_str_t rightmost_data = malloc(rightmost_size*sizeof(paradox_str_char_t));
        memcpy(rightmost_data, dest->data + pos, rightmost_size);
        memcpy(dest->data + pos, src, src->size);
        memcpy(dest->data + pos + src->size, rightmost_data, rightmost_size);
        free(rightmost_data);
    }
    dest->size += src->size;
    dest->data[dest->size] = '\0';
    return PARADOX_TRUE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_insert_str2string(paradox_string* dest, const paradox_str_t src, const size_t size, const size_t pos) {
    if(!dest || !src || pos > dest->size) return PARADOX_FALSE;
    size_t new_capacity = paradox_calculate_string_capacity(dest->size + size + 1);
    if(new_capacity > dest->capacity) {
        paradox_str_t new_data = realloc(dest->data, new_capacity);
        if(!new_data) return PARADOX_FALSE;
        dest->data = new_data;
        dest->capacity = new_capacity;
    }
    if(pos == dest->size) memcpy(dest->data + dest->size, src, size);
    else {
        const size_t rightmost_size = dest->size - pos;
        paradox_str_t rightmost_data = malloc(rightmost_size*sizeof(paradox_str_char_t));
        memcpy(rightmost_data, dest->data + pos, rightmost_size);
        memcpy(dest->data + pos, src, size);
        memcpy(dest->data + pos + size, rightmost_data, rightmost_size);
        free(rightmost_data);
    }
    dest->size += size;
    dest->data[dest->size] = '\0';
    return PARADOX_TRUE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_remove_string(paradox_string* dest, const size_t pos, const size_t count) {
    if(!dest || !count || dest->size < pos + count) return PARADOX_FALSE;
    memcpy(dest->data + pos, dest->data + pos + count, (pos + count) - dest->size + 1);
    dest->size -= count;
    size_t new_capacity = paradox_calculate_string_capacity(dest->size + 1);
    if(new_capacity > dest->capacity) {
        paradox_str_t new_data = realloc(dest->data, new_capacity);
        if(!new_data) return PARADOX_FALSE;
        dest->data = new_data;
        dest->capacity = new_capacity;
    }
    return PARADOX_TRUE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_replace_string(paradox_string* dest, const paradox_string* src, const size_t pos, const size_t count) {
    if(PARADOX_TRUE == paradox_remove_string(dest, pos, count)
    && PARADOX_TRUE == paradox_insert_string(dest, src, pos)) return PARADOX_TRUE;
    else return PARADOX_FALSE;
}

PARADOX_PLATFORM_API paradox_bool8_t paradox_replace_string_w_str(paradox_string* dest, const paradox_str_t src, const size_t size, const size_t pos, const size_t count) {
    if(PARADOX_TRUE == paradox_remove_string(dest, pos, count)
    && PARADOX_TRUE == paradox_insert_str2string(dest, src, size, pos)) return PARADOX_TRUE;
    else return PARADOX_FALSE;
}