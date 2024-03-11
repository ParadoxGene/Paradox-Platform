#ifndef PARADOX_WORKS_C_PLATFORM_STRING_H
#define PARADOX_WORKS_C_PLATFORM_STRING_H

#include <paradox-platform/defines.h>

typedef enum paradox_string_errno_t
{
    PARADOX_STRING_OK,
    PARADOX_STRING_BAD_PTR,
    PARADOX_STRING_BAD_ALLOC,
    PARADOX_STRING_BAD_RANGE,
} paradox_string_errno_t;

/**
 * Represents a null-terminated string that shrinks/grows by a factor of 2.
 */
typedef struct paradox_string
{
    paradox_str_t data;
    size_t data_len;
    size_t alloc_len;
} paradox_string;

PARADOX_PLATFORM_API paradox_string* paradox_create_string(paradox_str_t data);
PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* str);

PARADOX_PLATFORM_API paradox_string_errno_t paradox_string_append_str(paradox_string* str, paradox_str_t data);
PARADOX_PLATFORM_API paradox_string_errno_t paradox_string_append_string(paradox_string* dest, paradox_string* src);
PARADOX_PLATFORM_API paradox_string_errno_t paradox_string_remove(const size_t pos, const size_t len);

#endif
