#include <paradox-platform/io.hpp>

#if _WIN32 & _MSC_VER
    #include <windows.h>
#elif __linux__ & __GNUC__
    #include <unistd.h>
    #include <libgen.h>
    #include <linux/limits.h>
    #include <stdlib.h>
    #include <string.h>
#endif

namespace Paradox { namespace IO {
    const DataType::String_t& ProgramFilePath()
    {
        static DataType::B8 init = false;
        static DataType::String_t program_file_path;
        
#if _WIN32 & _MSC_VER
        if(!init)
        {
            init = true;
            LPSTR path;
            _get_pgmptr(&path);
            program_file_path = DataType::String_t(path);
        }
#elif __linux__ & __GNUC__
        if(!init)
        {
            init = true;
            char path[PATH_MAX];
            readlink("/proc/self/exe", path, PATH_MAX);
            program_file_path = DataType::String_t(path);
        }
#endif
        return program_file_path;
    }

    const DataType::String_t& ProgramDirPath()
    {
        static DataType::B8 init = false;
        static DataType::String_t program_dir_path;

        if(!init)
        {
            init = true;

            DataType::String_t path(ProgramFilePath());
            size_t last_slash_idx = path.rfind('/');
            if (std::string::npos == last_slash_idx)
                last_slash_idx = path.rfind('\\');
            if (std::string::npos != last_slash_idx)
                program_dir_path = path.substr(0, last_slash_idx) + "/";
        }

        return program_dir_path;
    }

    void OpenBinDirFile(std::fstream& filestream, const DataType::String_t& filename, std::ios_base::openmode mode)
    {
        filestream.open(DataType::String_t(ProgramDirPath()) + filename, mode);
    }
    void OpenBinDirFile(std::ifstream& filestream, const DataType::String_t& filename, std::ios_base::openmode mode)
    {
        filestream.open(DataType::String_t(ProgramDirPath()) + filename, mode);
    }
    void OpenBinDirFile(std::ofstream& filestream, const DataType::String_t& filename, std::ios_base::openmode mode)
    {
        filestream.open(DataType::String_t(ProgramDirPath()) + filename, mode);
    }
}}
