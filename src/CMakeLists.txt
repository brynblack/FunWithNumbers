set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release)

set(CMAKE_CXX_FLAGS_DEBUG "-static -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-static -Ofast")

add_executable(FunWithNumbers main.cpp)
