cmake_minimum_required(VERSION 3.22)
project("imgtool")

add_subdirectory("lib") # Separated, in case other people want to use this as a library
add_subdirectory("3rd/argparse")

add_executable("imgtool"
    "src/main.cpp"
)
target_link_libraries("imgtool" "libimgtool" "argparse")
