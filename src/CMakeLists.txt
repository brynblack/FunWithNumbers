find_package(Threads REQUIRED)

# TODO: Replace everything up to target_sources() with proper implementation
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/release)

target_sources(FunWithNumbers
	PRIVATE
		main.cpp)

target_link_libraries(FunWithNumbers
	PUBLIC
    	"$<$<CONFIG:Debug>:-static;-Og;-g;-Wl,-u,pthread_join>"
		"$<$<CONFIG:Release>:-static;-Ofast;-Wl,-u,pthread_join>"
		Threads::Threads)
