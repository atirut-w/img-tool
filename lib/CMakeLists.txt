add_library("libimgtool"
    "imgtool.cpp"
)
target_include_directories("libimgtool" PUBLIC "include")
target_compile_features("libimgtool" PUBLIC cxx_std_17)
