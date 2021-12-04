//
// Created by andre on 12/2/2021.
//

#include "Vertex.h"

int64_t Vertex::getWeight() const {
    return weight;
}

void Vertex::setWeight(int64_t weight) {
    Vertex::weight = weight;
}

const std::string &Vertex::getName() const {
    return name;
}

void Vertex::setName(const std::string &name) {
    Vertex::name = name;
}

const std::string &Vertex::getPath() const {
    return path;
}

void Vertex::setPath(const std::string &path) {
    Vertex::path = path;
}

const std::vector<Edge *> &Vertex::getEdges() const {
    return edges;
}

void Vertex::setEdges(const std::vector<Edge *> &edges) {
    Vertex::edges = edges;
}
std::ostream& operator<<(std::ostream& os, const Vertex& vertex){
    os << vertex.name << std::endl;
    return os;
}