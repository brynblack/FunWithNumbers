target_sources(FunWithNumbers
    PRIVATE
    core/buffer.cpp
    core/graph.cpp
    core/menu.cpp
    core/options.cpp
    core/stats.cpp
    modes/checknumberfeatures.cpp
    modes/checkoverallstats.cpp
    modes/createfile.cpp
    modes/credits.cpp
    modes/downloadmoreram.cpp
    modes/plotnumbers.cpp
    modes/randomnumber.cpp
    inconspicuous_file.cpp
    main.cpp
    variables.cpp)

target_include_directories(FunWithNumbers
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(FunWithNumbers
    PRIVATE
    project_options)
