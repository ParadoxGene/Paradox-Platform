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
    LPSTR program_path;
    _get_pgmptr(&program_path);
    CHAR program_drive_buf[_MAX_DRIVE];
    CHAR program_dir_buf[_MAX_DIR];
    _splitpath_s(program_path, program_drive_buf, _MAX_DRIVE, program_dir_buf, _MAX_DIR, NULL, 0, NULL, 0);
    const size_t program_dir_buf_sz = strlen(program_dir_buf);
    const size_t file_path_buf_sz = strlen(filename);
    CHAR* full_file_path_buf = malloc(((_MAX_DRIVE - 1) + program_dir_buf_sz + file_path_buf_sz + 1) * sizeof(CHAR));
    strcpy_s(full_file_path_buf, _MAX_DRIVE, program_drive_buf);
    strcpy_s(full_file_path_buf + (_MAX_DRIVE - 1),  program_dir_buf_sz + 1, program_dir_buf);
    strcpy_s(full_file_path_buf + (_MAX_DRIVE - 1) + program_dir_buf_sz, file_path_buf_sz + 1, filename);
    full_file_path_buf[(_MAX_DRIVE - 1) + program_dir_buf_sz + file_path_buf_sz] = '\0';
    errno_t err = fopen_s(streamptr, full_file_path_buf, mode);
    free(full_file_path_buf);
    return err;
#endif
    break;
    }
    }
    return 1;
}