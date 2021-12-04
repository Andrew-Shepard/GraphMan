//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_GRAPH_H
#define GRAPHMAN_GRAPH_H


#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include <iostream>

class Graph {
public:
    std::vector<Vertex *> vertices;
    std::vector<Edge *> edges;
    Vertex* getVertex(std::string name);
    int64_t getVertexIndex(Vertex vertex);
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};


#endif //GRAPHMAN_GRAPH_H
