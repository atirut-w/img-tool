#include <argparse/argparse.hpp>
#include <fstream>
#include <iostream>

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

    std::ifstream file(program.get<std::string>("archive"), std::ios::binary);
    if (!file)
    {
        std::cout << "Failed to open archive" << std::endl;
        return 1;
    }
    
    return 0;
}
