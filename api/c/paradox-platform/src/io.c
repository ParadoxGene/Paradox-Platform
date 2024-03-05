#include <paradox-platform/io.h>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <libgen.h>
    #include <linux/limits.h>
#endif

#include <stdlib.h>
#include <string.h>

PARADOX_PLATFORM_API paradox_cstr_t paradox_program_file_path(void)
{
    static paradox_bool8_t init = 0;
#if defined(_WIN32)
    static LPSTR path = NULL;
    if(!init)
    {
        init = 1;
        DWORD buffer_len = MAX_PATH;
        path = malloc(sizeof(CHAR) * buffer_len);
        GetModuleFileNameA(NULL, path, buffer_len);
    }
    return path;
#elif defined(__linux__)
    static char path[PATH_MAX];
    if(!init)
    {
        init = 1;
        if(-1 == readlink("/proc/self/exe", path, PATH_MAX))
        {   // on error
            init = 0;
            return NULL;
        }
    }
    return path;
#else
    #error Operating System is not supported.
#endif
}

PARADOX_PLATFORM_API paradox_cstr_t paradox_program_dir_path(void)
{
    static paradox_bool8_t init = 0;
#if defined(_WIN32)
    static LPSTR dir = NULL;
    if(!init)
    {
        init = 1;
        LPCSTR path = paradox_program_file_path();

        CHAR program_drive_buf[_MAX_DRIVE];
        CHAR program_dir_buf[_MAX_DIR];
        _splitpath_s(path, program_drive_buf, _MAX_DRIVE, program_dir_buf, _MAX_DIR, NULL, 0, NULL, 0);
        const size_t program_dir_buf_sz = strlen(program_dir_buf);

        dir = malloc(((_MAX_DRIVE - 1) + program_dir_buf_sz + 1) * sizeof(CHAR));
        strcpy_s(dir, _MAX_DRIVE, program_drive_buf);
        strcpy_s(dir + (_MAX_DRIVE - 1),  program_dir_buf_sz + 1, program_dir_buf);
        dir[(_MAX_DRIVE - 1) + program_dir_buf_sz] = '\0';
    }
    return dir;
#elif defined(__linux__)
    static char* dir = NULL;
    if(!init)
    {
        init = 1;
        char path[PATH_MAX];
        if(-1 == readlink("/proc/self/exe", path, PATH_MAX))
        {   // on error
            init = 0;
            return NULL;
        }
        else dir = dirname(path);
    }
    return dir;
#else
    #error Operating System is not supported.
#endif
}

PARADOX_PLATFORM_API FILE* paradox_bin_dir_fopen(
    paradox_cstr_t filename,
    paradox_cstr_t mode)
{
    if(filename == NULL) return NULL;

    switch(filename[0])
    {
    case '/':
    case '\\': return fopen(filename, mode);
    default:
    {
#if defined(_WIN32)
    if(isalpha(filename[0]) && filename[1] == ':') return fopen(filename, mode);

    const size_t program_dir_buf_sz = strlen(paradox_program_dir_path());
    const size_t file_buf_sz = strlen(filename);

    LPSTR rel_file_buf = malloc((program_dir_buf_sz + file_buf_sz + 1) * sizeof(CHAR));
    strcpy_s(rel_file_buf,  program_dir_buf_sz + 1, paradox_program_dir_path());
    strcpy_s(rel_file_buf + program_dir_buf_sz, file_buf_sz + 1, filename);
    rel_file_buf[program_dir_buf_sz + file_buf_sz] = '\0';
    
    FILE* file = fopen(rel_file_buf, mode);
    free(rel_file_buf);
    return file;
#elif defined(__linux__)
    const size_t program_dir_buf_sz = strlen(paradox_program_dir_path());
    const size_t file_buf_sz = strlen(filename);

    char* rel_file_buf = malloc((program_dir_buf_sz + 1 + file_buf_sz + 1) * sizeof(char));
    strcpy(rel_file_buf, paradox_program_dir_path());
    rel_file_buf[program_dir_buf_sz] = '/';
    strcpy(rel_file_buf + program_dir_buf_sz + 1, filename);

    FILE* file = fopen(rel_file_buf, mode);
    free(rel_file_buf);
    return file;
#else
    #error Operating System is not supported.
#endif
    }
    }
}

PARADOX_PLATFORM_API paradox_str_t paradox_file_to_str(FILE* file, size_t* len)
{
    paradox_str_t buffer = NULL;
    if(!file) goto ret_val;
    
    fseek(file, 0, SEEK_END);
    long flen = ftell(file);
    if(flen <= 0) goto rst_file;
    *len = (size_t)flen;
    
    fseek(file, 0, SEEK_SET);
    buffer = malloc(*len + 1);
    if(buffer)
    {
        size_t count = fread(buffer, 1, *len, file);
        buffer[count] = '\0';
    }

    rst_file:
    fseek(file, 0, SEEK_SET);

    ret_val:
    return buffer;
}
