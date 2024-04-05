#ifndef OPEN_SOURCE_C_HEADER_PARADOX_PLATFORM_FILE_SYSTEM
#define OPEN_SOURCE_C_HEADER_PARADOX_PLATFORM_FILE_SYSTEM

#include <paradox-platform/defines.h>
#include <stdio.h>

typedef enum paradox_file_system_errno_t
{
    PARADOX_FILE_SYSTEM_SUCCESS,
    PARADOX_FILE_SYSTEM_BAD_PATH,
    PARADOX_FILE_SYSTEM_BAD_FILE
} paradox_file_system_errno_t;

/** @return The path to the program file. */
PARADOX_PLATFORM_API paradox_cstr_t paradox_program_file_path(void);

/** @returns The path to the program directory. */
PARADOX_PLATFORM_API paradox_cstr_t paradox_program_dir_path(void);


/** Attempts to open a file from the program's binary directory.
 * @param filename The path, relative to the program's binary directory.
 * @param mode The mode that the file will be opened as.
 * @return A pointer to the opened file or NULL. */
PARADOX_PLATFORM_API FILE* paradox_bin_dir_fopen(paradox_cstr_t filename, paradox_cstr_t mode);
    

PARADOX_PLATFORM_API paradox_str_t paradox_file_to_str(FILE* file, size_t* len);
#endif
