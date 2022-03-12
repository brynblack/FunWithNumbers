set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/Release)

set(CMAKE_CXX_FLAGS_DEBUG "-static -Og -g -pthread -Wl,-u,pthread_join")
set(CMAKE_CXX_FLAGS_RELEASE "-static -Ofast -pthread -Wl,-u,pthread_join")

add_executable(FunWithNumbers main.cpp)
