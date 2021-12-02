//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_GRAPH_H
#define GRAPHMAN_GRAPH_H


#include <vector>
#include "Vertex.h"
#include "Edge.h"

class Graph {
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};


#endif //GRAPHMAN_GRAPH_H
