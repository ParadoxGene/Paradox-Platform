#ifndef PARADOX_WORKS_C_PLATFORM_IO_H
#define PARADOX_WORKS_C_PLATFORM_IO_H

#include <paradox-platform/defines.h>
#include <errno.h>

const errno_t paradox_bin_dir_fopen(
    FILE** streamptr,
    const char* filename,
    const char* mode);
    
#endif