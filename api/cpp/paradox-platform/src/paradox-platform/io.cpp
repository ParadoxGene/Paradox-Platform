#include <paradox-platform/io.hpp>

#if defined(_WIN32)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>
    #include <libgen.h>
    #include <linux/limits.h>
#endif

namespace Paradox { namespace IO {
    const DataType::String_t& ProgramFilePath()
    {
        static DataType::B8 init = false;
        static DataType::String_t program_file_path;
        
#if defined(_WIN32)
        if(!init)
        {
            init = true;
            LPSTR path;
            DWORD buffer_len = MAX_PATH;
            path = new CHAR[buffer_len];
            GetModuleFileNameA(NULL, path, buffer_len);
            program_file_path = DataType::String_t(path);
            delete [] path;
        }
#elif defined(__linux__)
        if(!init)
        {
            init = true;
            char path[PATH_MAX];
            if(-1 == readlink("/proc/self/exe", path, PATH_MAX))
            {   // on error
                init = false;
                return program_file_path;
            }
            else program_file_path = DataType::String_t(path);
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
