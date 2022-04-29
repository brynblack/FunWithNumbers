target_sources(FunWithNumbers
    PRIVATE
    core/buffer.cpp
    core/graph.cpp
    main.cpp
    core/menu.cpp
    core/options.cpp
    core/stats.cpp)

target_include_directories(FunWithNumbers
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(FunWithNumbers
    PRIVATE
    project_options)
