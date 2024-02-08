#include <paradox-platform/io.h>

#if _WIN32 & _MSC_VER
    #include <windows.h>
#elif __linux__ & __GNUC__
    #include <unistd.h>
    #include <libgen.h>
    #include <linux/limits.h>
    #include <stdlib.h>
    #include <string.h>
#endif

paradox_cstr_t paradox_program_file_path(void)
{
    static paradox_bool8_t init = 0;
#if _WIN32 & _MSC_VER
    static LPSTR path = NULL;
    if(!init)
    {
        init = 1;
        _get_pgmptr(&path);
    }
    return path;
#elif __linux__ & __GNUC__
    static char path[PATH_MAX];
    if(!init)
    {
        init = 1;
        readlink("/proc/self/exe", path, PATH_MAX);
    }
    return path;
#endif
    return NULL;
}

paradox_cstr_t paradox_program_dir_path(void)
{
    static paradox_bool8_t init = 0;
#if _WIN32 & _MSC_VER
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
#elif __linux__ & __GNUC__
    static char* dir = NULL;
    if(!init)
    {
        init = 1;
        char path[PATH_MAX];
        readlink("/proc/self/exe", path, PATH_MAX);
        dir = dirname(path);
    }
    return dir;
#endif
    return NULL;
}

FILE* paradox_bin_dir_fopen(
    paradox_cstr_t filename,
    paradox_cstr_t mode)
{
    if(filename == NULL) return NULL;

    switch(filename[0])
    {
    case '/':
    case '\\':
    {
#if _WIN32 & _MSC_VER
        FILE* file;
        fopen_s(&file, filename, mode);
        return file;
#elif __linux__ & __GNUC__
        return fopen(filename, mode);
#endif
    }
    default:
    {
#if _WIN32 & _MSC_VER
    if(isalpha(filename[0]) && filename[1] == ':')
    {
        FILE* file;
        fopen_s(&file, filename, mode);
        return file;
    }

    const size_t program_dir_buf_sz = strlen(paradox_program_dir_path());
    const size_t file_buf_sz = strlen(filename);

    LPSTR rel_file_buf = malloc((program_dir_buf_sz + file_buf_sz + 1) * sizeof(CHAR));
    strcpy_s(rel_file_buf,  program_dir_buf_sz + 1, paradox_program_dir_path());
    strcpy_s(rel_file_buf + program_dir_buf_sz, file_buf_sz + 1, filename);
    rel_file_buf[program_dir_buf_sz + file_buf_sz] = '\0';
    
    FILE* file;
    fopen_s(&file, rel_file_buf, mode);
    free(rel_file_buf);
    return file;
#elif __linux__ & __GNUC__
    const size_t program_dir_buf_sz = strlen(paradox_program_dir_path());
    const size_t file_buf_sz = strlen(filename);

    char* rel_file_buf = malloc((program_dir_buf_sz + 1 + file_buf_sz + 1) * sizeof(char));
    strcpy(rel_file_buf, paradox_program_dir_path());
    rel_file_buf[program_dir_buf_sz] = '/';
    strcpy(rel_file_buf + program_dir_buf_sz + 1, filename);

    FILE* file = fopen(rel_file_buf, mode);
    free(rel_file_buf);
    return file;
#endif
    break;
    }
    }
    
    return NULL;
}