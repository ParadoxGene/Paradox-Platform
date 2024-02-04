#include <paradox-platform/io.h>
#include <stdio.h>
#include <ctype.h>

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
#endif
    }
    }
    return 1;
}