cmake_minimum_required(VERSION 3.8)
project(C_Graph)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        lib/Arrangement.c
        lib/Arrangement.h
        src/Graph.c
        src/Graph.h
        lib/Vector.c
        lib/Vector.h
        src/c_graph.c)

add_executable(C_Graph ${SOURCE_FILES})