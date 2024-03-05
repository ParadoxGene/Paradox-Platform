#ifndef PARADOX_WORKS_CPP_PLATFORM_IO_HPP
#define PARADOX_WORKS_CPP_PLATFORM_IO_HPP

#include <paradox-platform/defines.hpp>
#include <fstream>

namespace Paradox { namespace IO {
    /** @return The path to the program file. */
    PARADOX_PLATFORM_API const DataType::String_t& ProgramFilePath();
    /** @returns The path to the program directory. */
    PARADOX_PLATFORM_API const DataType::String_t& ProgramDirPath();


    /** Attempts to open a file from the program's binary directory.
     * @param filestream The file stream that will open the file.
     * @param filename The path, relative to the program's binary directory.
     * @param mode The mode that the file will be opened as.*/
    PARADOX_PLATFORM_API void OpenBinDirFile(std::fstream& filestream, const DataType::String_t& filename, std::ios_base::openmode mode = std::ios_base::in);
    /** Attempts to open a file from the program's binary directory.
     * @param filestream The file stream that will open the file.
     * @param filename The path, relative to the program's binary directory.
     * @param mode The mode that the file will be opened as.*/
    PARADOX_PLATFORM_API void OpenBinDirFile(std::ifstream& filestream, const DataType::String_t& filename, std::ios_base::openmode mode = std::ios_base::in);
    /** Attempts to open a file from the program's binary directory.
     * @param filestream The file stream that will open the file.
     * @param filename The path, relative to the program's binary directory.
     * @param mode The mode that the file will be opened as.*/
    PARADOX_PLATFORM_API void OpenBinDirFile(std::ofstream& filestream, const DataType::String_t& filename, std::ios_base::openmode mode = std::ios_base::in);
}}

#endif
