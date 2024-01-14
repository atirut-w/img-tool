#pragma once
#include <filesystem>
#include <string>
#include <map>
#include <fstream>

namespace IMGTool
{
    struct DirEntry
    {
        int offset;
        int size;
    };
    
    class Archive
    {
    private:
        std::ifstream archive_file;
        std::ifstream dir_file;
    public:
        Archive(std::filesystem::path path);

        int version;
        std::map<std::string, DirEntry> files;
    };
}
