#ifndef PARADOX_WORKS_CPP_PLATFORM_IO_HPP
#define PARADOX_WORKS_CPP_PLATFORM_IO_HPP

#include <paradox-platform/defines.hpp>
#include <fstream>

namespace Paradox { namespace IO {
    PARADOX_PLATFORM_API const DataType::String_t& ProgramFilePath();
    PARADOX_PLATFORM_API const DataType::String_t& ProgramDirPath();

    PARADOX_PLATFORM_API void OpenBinDirFile(
        std::fstream& filestream,
        const DataType::String_t& filename,
        std::ios_base::openmode mode = std::ios_base::in);
    PARADOX_PLATFORM_API void OpenBinDirFile(
        std::ifstream& filestream,
        const DataType::String_t& filename,
        std::ios_base::openmode mode = std::ios_base::in);
    PARADOX_PLATFORM_API void OpenBinDirFile(
        std::ofstream& filestream,
        const DataType::String_t& filename,
        std::ios_base::openmode mode = std::ios_base::in);
}}

#endif