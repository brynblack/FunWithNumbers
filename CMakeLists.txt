cmake_minimum_required(VERSION 3.22.3)
project(FunWithNumbers
        VERSION 4.2.5.0
        DESCRIPTION "A C++ recreation of the program Fun With Numbers, for a Software Design and Development assignment."
        HOMEPAGE_URL "https://github.com/brynblack/FunWithNumbers"
        LANGUAGES CXX)

# TODO: Replace these with target_compile_features()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(FunWithNumbers)

add_subdirectory(src)
