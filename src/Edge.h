//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_EDGE_H
#define GRAPHMAN_EDGE_H


#include <string>
class Vertex;
class Edge {
    std::string name;
    Vertex * source = nullptr;
    Vertex * destination = nullptr;
    uint64_t weight;
public:
    uint64_t getWeight() const {
        return weight;
    }

    void setWeight(uint64_t weight) {
        Edge::weight = weight;
    }
    Vertex *getDestination() const {
        return destination;
    }
    void setDestination(Vertex *destination) {
        Edge::destination = destination;
    }
    Vertex *getSource() const {
        return source;
    }
    void setSource(Vertex *source) {
        Edge::source = source;
    }
    Edge(Vertex* source, Vertex* destination, uint64_t weight){
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }
    const std::string &getName() const {
        return name;
    }
    void setName(const std::string &name) {
        Edge::name = name;
    }
};


#endif //GRAPHMAN_EDGE_H
