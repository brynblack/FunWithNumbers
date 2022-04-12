target_sources(FunWithNumbers
	PRIVATE
        graph.cpp
		main.cpp
		menu.cpp
		stats.cpp)

target_include_directories(FunWithNumbers
	PRIVATE
		${CMAKE_SOURCE_DIR}/include)

target_link_libraries(FunWithNumbers
	PRIVATE
		project_options)
