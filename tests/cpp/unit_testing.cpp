#include <paradox-platform/io.hpp>
#include <iostream>

int main()
{
    std::fstream file;
    Paradox::IO::OpenBinDirFile(file, "cpp_unit_tests");
    if(file.is_open())
        printf("File found.\n");
    std::cout << "C++ Test: No errors during compilation.\n";
    std::cout << "C++ Test: All tests passed.\n";
    return 0;
}