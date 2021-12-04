cmake_minimum_required(VERSION 3.20)
project(GraphMan)

set(CMAKE_CXX_STANDARD 14)

add_executable(GraphMan src/main.cpp src/Graph.cpp src/Graph.h src/Vertex.cpp src/Vertex.h src/Edge.cpp src/Edge.h src/GraphMan.cpp src/GraphMan.h src/VectexQueue.h src/Stack.h)
