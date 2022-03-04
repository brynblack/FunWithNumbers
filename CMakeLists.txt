cmake_minimum_required(VERSION 3.20)
project(FunWithNumbers
        VERSION 1.1.0.0
        DESCRIPTION "A c++ recreation of the program Fun With Numbers."
        HOMEPAGE_URL "https://github.com/brynblack/FunWithNumbers"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory("src")
