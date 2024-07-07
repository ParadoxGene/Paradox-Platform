#ifndef PARADOX_SOFTWARE_C_HEADER_PLATFORM_COMMON
#define PARADOX_SOFTWARE_C_HEADER_PLATFORM_COMMON

#define paradox_offsetof(type, member) ((size_t) &(((type *)0)->member))

typedef enum paradox_os_t
{
    PARADOX_OS_WINDOWS,
    PARADOX_OS_LINUX,
    PARADOX_OS_ANDROID
} paradox_os_t;

#endif