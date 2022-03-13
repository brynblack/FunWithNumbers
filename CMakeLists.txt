cmake_minimum_required(VERSION 3.22.2)
project(FunWithNumbers
        VERSION 4.3.5.4
        DESCRIPTION "A C++ recreation of the program Fun With Numbers, for a Software Design and Development assignment."
        HOMEPAGE_URL "https://github.com/brynblack/FunWithNumbers"
        LANGUAGES CXX)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)

add_executable(FunWithNumbers)

add_subdirectory(src)
