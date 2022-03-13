find_package(Threads REQUIRED)

# TODO: Replace everything up to target_sources() with proper implementation
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/release)

# TODO: It isn't actually static, need to fix
target_compile_options(compiler_flags INTERFACE
        "$<$<CONFIG:Release>:-static;-Ofast>"
        "$<$<CONFIG:Debug>:-static;-Og;-g>")

target_sources(FunWithNumbers PRIVATE main.cpp)
target_link_libraries(FunWithNumbers PUBLIC Threads::Threads compiler_flags)
