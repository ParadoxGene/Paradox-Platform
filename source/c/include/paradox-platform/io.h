#ifndef PARADOX_WORKS_C_PLATFORM_IO_H
#define PARADOX_WORKS_C_PLATFORM_IO_H

#include <paradox-platform/defines.h>
#include <errno.h>

const errno_t paradox_bin_dir_fopen(
    FILE *restrict *restrict streamptr,
    const char *restrict filename,
    const char *restrict mode);
    
#endif