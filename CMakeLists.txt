cmake_minimum_required(VERSION 3.22.2)
project(FunWithNumbers
        VERSION 4.2.5.3
        DESCRIPTION "A C++ recreation of the program Fun With Numbers, for a Software Design and Development assignment."
        HOMEPAGE_URL "https://github.com/brynblack/FunWithNumbers"
        LANGUAGES CXX)

# TODO: Replace these with target_compile_features()
set(CMAKE_CXX_STANDARD 23)
# Temporarily set to false because CI
set(CMAKE_CXX_STANDARD_REQUIRED False)

add_executable(FunWithNumbers)

add_subdirectory(src)
