//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_VERTEX_H
#define GRAPHMAN_VERTEX_H


#include <string>
#include <vector>

class Edge;
class Vertex {
    std::string name;
    int64_t weight = -1;
public:
    int64_t getWeight() const {
        return weight;
    }
    void setWeight(int64_t weight) {
        Vertex::weight = weight;
    }
    std::vector<Edge*> edges;
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Vertex::name = name;
    }

    Vertex(std::string name){
        this->name = name;
    }
};


#endif //GRAPHMAN_VERTEX_H
