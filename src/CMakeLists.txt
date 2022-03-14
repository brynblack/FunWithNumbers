find_package(Threads REQUIRED)

target_sources(FunWithNumbers
	PRIVATE
		main.cpp)

target_link_libraries(FunWithNumbers
	PRIVATE
		project_options
	PUBLIC
		Threads::Threads)
