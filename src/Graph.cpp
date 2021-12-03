//
// Created by andre on 12/2/2021.
//

#include "Graph.h"
Vertex* Graph::getVertex(std::string name){
    for(int i = 0; i<vertices.size(); i++){
        if(vertices.at(i).getName() == name)
            return &vertices.at(i);
    }
    return nullptr;
}
int64_t Graph::getVertexIndex(Vertex vertex){
    for (uint64_t i = 0; i<vertices.size(); i++){
        if(vertex.getName() == vertices.at(i).getName()){
            return i;
        }
    }
    return 0;
}