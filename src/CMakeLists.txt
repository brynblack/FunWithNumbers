find_package(Threads REQUIRED)

target_sources(FunWithNumbers
	PRIVATE
		main.cpp)

target_link_libraries(FunWithNumbers
	PRIVATE
	    "$<$<CONFIG:Debug>:-static;-Og;-g;-Wl,-u,pthread_join>"
	    "$<$<CONFIG:Release>:-static;-Ofast;-Wl,-u,pthread_join>"
	PUBLIC
		Threads::Threads)
