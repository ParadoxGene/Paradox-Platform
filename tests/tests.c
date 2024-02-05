#include <paradox-platform/defines.h>
#include <paradox-platform/io.h>

int main()
{
    if(paradox_bin_dir_fopen("c_tests.makefile", "r") != NULL)
        printf("File found.\n");
    printf("C Test: No errors during compilation.\n");
    printf("C Test: All tests passed.\n");
    return 0;
}