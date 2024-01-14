#include <imgtool.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace IMGTool;

template <typename T>
T read(std::ifstream &file)
{
    T value;
    file.read(reinterpret_cast<char *>(&value), sizeof(T));
    return value;
}

Archive::Archive(std::filesystem::path path)
{
    archive_file.open(path, std::ios::binary);
    
    std::string magic;
    magic.resize(4);
    archive_file.read(&magic[0], magic.size());

    if (magic == "\xce\xa1\xa3\x67") // Version 1, LZO-compressed
    {
        throw std::runtime_error("LZO-compressed archives are not supported");
    }
    else if (magic == "VER2")
    {
        throw std::runtime_error("Version 2 archives are not supported");
    }
    else
    {
        version = 1;
        dir_file.open(path.replace_extension(".dir"), std::ios::binary);
        if (!dir_file)
        {
            throw std::runtime_error("Could not open directory file");
        }

        int dirsize = std::filesystem::file_size(path.replace_extension(".dir"));
        int n_entries = dirsize / 32;
        if (dirsize % 32 != 0)
        {
            std::cout << "[libimgtool] Warning: Directory file size is not a multiple of 32. This may indicate a corrupt archive." << std::endl;
        }

        for (int i = 0; i < n_entries; i++)
        {
            char name[24];
            DirEntry entry;

            entry.offset = read<int>(dir_file);
            entry.size = read<int>(dir_file);
            dir_file.read(name, 24);

            files[name] = entry;
        }
    }
}
