#include <paradox-platform/io.h>


#if _WIN32
    #include <windows.h>
    #include <ctype.h>
#elif __linux__
    #include <unistd.h>
    #include <libgen.h>
    #include <linux/limits.h>
#endif

#include <stdlib.h>
#include <string.h>

FILE* paradox_bin_dir_fopen(
    const char* restrict filename,
    const char* restrict mode)
{
    if(filename == NULL) return NULL;

    switch(filename[0])
    {
    case '/':
    case '\\': return fopen(filename, mode);
    
    default:
    {
#if _WIN32
    if(isalpha(filename[0]) && filename[1] == ':') return fopen(filename, mode);

    LPSTR program_file_buf;
    _get_pgmptr(&program_file_buf);

    CHAR program_drive_buf[_MAX_DRIVE];
    CHAR program_dir_buf[_MAX_DIR];
    _splitpath_s(program_file_buf, program_drive_buf, _MAX_DRIVE, program_dir_buf, _MAX_DIR, NULL, 0, NULL, 0);
    const size_t program_dir_buf_sz = strlen(program_dir_buf);
    const size_t file_buf_sz = strlen(filename);

    CHAR* rel_file_buf = malloc(((_MAX_DRIVE - 1) + program_dir_buf_sz + file_buf_sz + 1) * sizeof(CHAR));
    strcpy_s(rel_file_buf, _MAX_DRIVE, program_drive_buf);
    strcpy_s(rel_file_buf + (_MAX_DRIVE - 1),  program_dir_buf_sz + 1, program_dir_buf);
    strcpy_s(rel_file_buf + (_MAX_DRIVE - 1) + program_dir_buf_sz, file_buf_sz + 1, filename);
    rel_file_buf[(_MAX_DRIVE - 1) + program_dir_buf_sz + file_buf_sz] = '\0';
    
    FILE* file = fopen(rel_file_buf, mode);
    free(rel_file_buf);
    return file;
#elif __linux__
    char program_file_buf[PATH_MAX];
    readlink("/proc/self/exe", program_file_buf, PATH_MAX);

    const char* program_dir_buf = dirname(program_file_buf);
    const size_t program_dir_buf_sz = strlen(program_dir_buf);
    const size_t file_buf_sz = strlen(filename);

    char* rel_file_buf = malloc((program_dir_buf_sz + 1 + file_buf_sz + 1) * sizeof(char));
    strcpy(rel_file_buf, program_dir_buf);
    rel_file_buf[program_dir_buf_sz] = '/';
    strcpy(rel_file_buf + program_dir_buf_sz + 1, filename);

    FILE* file = fopen(rel_file_buf, mode);
    free(rel_file_buf);
    return file;
#else
    #error Unsupported Compiler and/or Platform.
#endif
    break;
    }
    }
    
    return NULL;
}