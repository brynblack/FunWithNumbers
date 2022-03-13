# TODO: Replace everything up to target_sources() with proper implementation
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/release)

set(CMAKE_CXX_FLAGS_DEBUG "-static -Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-static -Ofast")
set(CMAKE_CXX_FLAGS "-static -Ofast")

find_package(Threads REQUIRED)

target_sources(FunWithNumbers PRIVATE main.cpp)
target_link_libraries(FunWithNumbers PUBLIC Threads::Threads)
