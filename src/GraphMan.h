//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_GRAPHMAN_H
#define GRAPHMAN_GRAPHMAN_H


#include <vector>
#include "Vertex.h"
#include "Graph.h"

class GraphMan {
    Graph graph;
public:
    void loadGraph(std::string path);
    Graph shortestPath();
    Vertex breadthFirstSearch();
    Vertex depthFirstSearch();
    Vertex depthFirstSearch(Graph increasing_order);
};


#endif //GRAPHMAN_GRAPHMAN_H
