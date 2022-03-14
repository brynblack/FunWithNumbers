find_package(Threads REQUIRED)

set_target_properties(FunWithNumbers PROPERTIES
	# TODO: Replace everything up to target_sources() with proper implementation
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/debug"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/release"
)

target_sources(FunWithNumbers
	PRIVATE
		main.cpp)

target_link_libraries(FunWithNumbers
	PUBLIC
    	"$<$<CONFIG:Debug>:-static;-Og;-g;-Wl,-u,pthread_join>"
		"$<$<CONFIG:Release>:-static;-Ofast;-Wl,-u,pthread_join>"
		Threads::Threads)

