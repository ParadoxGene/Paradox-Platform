#ifndef PARADOX_SOFTWARE_C_HEADER_PLATFORM_STRING
#define PARADOX_SOFTWARE_C_HEADER_PLATFORM_STRING

#include <paradox-platform/defines.h>

/** a null-terminated string. capacity is allocated using powers of 2. */
typedef struct paradox_string {
    size_t capacity, size;
    paradox_str_t data;
} paradox_string;

PARADOX_PLATFORM_API paradox_string* paradox_create_string(const paradox_str_t src, const size_t size);
PARADOX_PLATFORM_API void paradox_clear_string(paradox_string* src);
PARADOX_PLATFORM_API void paradox_destroy_string(paradox_string* src);
PARADOX_PLATFORM_API paradox_bool8_t paradox_copy_string(paradox_string* dest, const paradox_string* src);

PARADOX_PLATFORM_API paradox_bool8_t paradox_append_string(paradox_string* dest, const paradox_string* src);
PARADOX_PLATFORM_API paradox_bool8_t paradox_append_str2string(paradox_string* dest, const paradox_str_t src, const size_t size);

PARADOX_PLATFORM_API paradox_bool8_t paradox_insert_string(paradox_string* dest, const paradox_string* src, const size_t pos);
PARADOX_PLATFORM_API paradox_bool8_t paradox_insert_str2string(paradox_string* dest, const paradox_str_t src, const size_t size, const size_t pos);

PARADOX_PLATFORM_API paradox_bool8_t paradox_remove_string(paradox_string* dest, const size_t pos, const size_t count);

PARADOX_PLATFORM_API paradox_bool8_t paradox_replace_string(paradox_string* dest, const paradox_string* src, const size_t pos, const size_t count);
PARADOX_PLATFORM_API paradox_bool8_t paradox_replace_string_w_str(paradox_string* dest, const paradox_str_t src, const size_t size, const size_t pos, const size_t count);
#endif
