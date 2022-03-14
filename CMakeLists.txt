cmake_minimum_required(VERSION 3.13...3.22.3)

project(
    FunWithNumbers
    VERSION 5.4.6.4
    DESCRIPTION "A C++ recreation of the program Fun With Numbers, for a Software Design and Development assignment."
    HOMEPAGE_URL "https://github.com/brynblack/FunWithNumbers"
    LANGUAGES CXX)

# Set default build type if not already set
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_executable(FunWithNumbers)
add_library(project_options INTERFACE)

set_target_properties(FunWithNumbers
    PROPERTIES
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/debug"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/release")

target_compile_features(project_options
    INTERFACE
        cxx_std_23)

target_link_options(project_options
    INTERFACE
        "$<$<CONFIG:Debug>:-static;-Og;-g;-Wl,-u,pthread_join>"
        "$<$<CONFIG:Release>:-static;-Ofast;-Wl,-u,pthread_join>")

# Check if compiler supports Interprocedural Optimization, and enable if it is supported
include(CheckIPOSupported)
check_ipo_supported(RESULT result)
if(result)
    set_target_properties(FunWithNumbers PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_subdirectory(src)
