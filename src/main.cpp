#include <argparse/argparse.hpp>
#include <filesystem>
#include <iostream>
#include <imgtool.hpp>

int main(int argc, char *argv[])
{
    argparse::ArgumentParser program("imgtool");
    
    program.add_argument("archive")
        .help("The archive to operate on");
    
    auto &actions = program.add_mutually_exclusive_group();

    actions.add_argument("-l", "--list")
        .help("List the contents of the archive")
        .flag();
    
    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    std::filesystem::path path(program.get<std::string>("archive"));
    if (!std::filesystem::exists(path) && !std::filesystem::is_directory(path))
    {
        std::cout << "The specified archive does not exist" << std::endl;
        exit(0);
    }

    IMGTool::Archive archive(path);

    if (program.get<bool>("--list"))
    {
        for (auto &file : archive.files)
        {
            std::cout << file.first << std::endl;
        }
    }
    
    return 0;
}
