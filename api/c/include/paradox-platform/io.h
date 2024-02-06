#ifndef PARADOX_WORKS_C_PLATFORM_IO_H
#define PARADOX_WORKS_C_PLATFORM_IO_H

#include <paradox-platform/defines.h>
#include <stdio.h>

FILE* paradox_bin_dir_fopen(
    const char* filename,
    const char* mode);
    
#endif