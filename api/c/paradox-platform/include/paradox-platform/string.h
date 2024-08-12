#ifndef PARADOX_SOFTWARE_C_HEADER_PLATFORM_STRING
#define PARADOX_SOFTWARE_C_HEADER_PLATFORM_STRING

#include <paradox-platform/defines.h>

typedef enum paradox_string_errno_t
{
    PARADOX_STRING_SUCCESS,
    PARADOX_STRING_BAD_PTR,
    PARADOX_STRING_BAD_ALLOC,
    PARADOX_STRING_BAD_RANGE,
} paradox_string_errno_t;

/**
 * Represents a null-terminated string that shrinks/grows by powers of 2.
 */
typedef struct paradox_string
{
    size_t capacity;
    size_t len;
    paradox_str_t data;
} paradox_string;

PARADOX_PLATFORM_API paradox_string* paradox_create_string(paradox_str_t data);
PARADOX_PLATFORM_API void paradox_clear_string(paradox_string* str);
PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* str);

PARADOX_PLATFORM_API paradox_string_errno_t paradox_append_str_to_string(paradox_string* str, paradox_str_t data);
PARADOX_PLATFORM_API paradox_string_errno_t paradox_append_string_to_string(paradox_string* dest, paradox_string* src);
PARADOX_PLATFORM_API paradox_string_errno_t paradox_remove_from_string(paradox_string* str, const size_t pos, const size_t len);

#endif
