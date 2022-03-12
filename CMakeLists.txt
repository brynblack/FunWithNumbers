cmake_minimum_required(VERSION 3.20)
project(FunWithNumbers
        VERSION 2.8.2.4
        DESCRIPTION "A C++ recreation of the program Fun With Numbers, for a Software Design and Development assignment."
        HOMEPAGE_URL "https://github.com/brynblack/FunWithNumbers"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory("src")
