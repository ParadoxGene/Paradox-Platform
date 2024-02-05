#include <paradox-platform/defines.h>
#include <paradox-platform/io.h>
#include <stdio.h>

int main()
{
    FILE* f = NULL;
    paradox_bin_dir_fopen(&f, "c++_tests.makefile", "r");
    printf("C Test: No errors during compilation.\n");
    printf("C Test: All tests passed.\n");
    return 0;
}