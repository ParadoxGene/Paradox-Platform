#include <paradox-platform/io.h>
#include <ctype.h>
#include <stdio.h>

#if _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <string.h>

const errno_t paradox_bin_dir_fopen(
    FILE** streamptr,
    const char* filename,
    const char* mode)
{
    if(filename == NULL) return 1;

    switch(filename[0])
    {
    case '/':
    case '\\': return fopen_s(streamptr, filename, mode);
    default:
    {
#if _WIN32
    if(isalpha(filename[0]) && filename[1] == ':') return fopen_s(streamptr, filename, mode);
    CHAR program_drive_buf[_MAX_DRIVE];
    CHAR program_dir_buf[_MAX_DIR];
    _splitpath_s(_pgmptr, program_drive_buf, _MAX_DRIVE, program_dir_buf, _MAX_DIR, NULL, 0, NULL, 0);
    const DWORD program_dir_buf_sz = strlen(program_dir_buf);
    const DWORD file_path_buf_sz = strlen(filename);
    CHAR full_file_path_buf[(_MAX_DRIVE - 1) + program_dir_buf_sz + file_path_buf_sz + 1];
    strcpy_s(full_file_path_buf, _MAX_DRIVE, program_drive_buf);
    strcpy_s(full_file_path_buf + (_MAX_DRIVE - 1),  program_dir_buf_sz + 1, program_dir_buf);
    strcpy_s(full_file_path_buf + (_MAX_DRIVE - 1) + program_dir_buf_sz, file_path_buf_sz + 1, filename);
    full_file_path_buf[(_MAX_DRIVE - 1) + program_dir_buf_sz + file_path_buf_sz] = '\0';
    return fopen_s(streamptr, full_file_path_buf, mode);
#endif
    break;
    }
    }
    return 1;
}