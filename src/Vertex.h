//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_VERTEX_H
#define GRAPHMAN_VERTEX_H


#include <string>
#include <vector>
#include "Edge.h"

class Vertex {
    std::string name;
    std::vector<Edge*> source_of_edge;
};


#endif //GRAPHMAN_VERTEX_H
