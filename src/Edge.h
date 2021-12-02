//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_EDGE_H
#define GRAPHMAN_EDGE_H


#include <string>
#include "Vertex.h"

class Edge {
    std::string name;
    Vertex* source;
    Vertex* destination;
    uint64_t weight;
};


#endif //GRAPHMAN_EDGE_H
