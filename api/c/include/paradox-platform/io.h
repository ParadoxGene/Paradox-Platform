#ifndef PARADOX_WORKS_C_PLATFORM_IO_H
#define PARADOX_WORKS_C_PLATFORM_IO_H

#include <paradox-platform/defines.h>
#include <stdio.h>

paradox_cstr_t paradox_program_file_path(void);
paradox_cstr_t paradox_program_dir_path(void);

FILE* paradox_bin_dir_fopen(
    paradox_cstr_t filename,
    paradox_cstr_t mode);
    
#endif