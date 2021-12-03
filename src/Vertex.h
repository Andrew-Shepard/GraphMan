//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_VERTEX_H
#define GRAPHMAN_VERTEX_H


#include <string>
#include <vector>

class Edge;
class Vertex {
    int64_t weight = -1;
public:
    std::string name;
    std::string path;

    const std::string &getPath() const {
        return path;
    }

    void setPath(const std::string &path) {
        Vertex::path = path;
    }

    int64_t getWeight() const {
        return weight;
    }
    void setWeight(int64_t weight) {
        Vertex::weight = weight;
    }
    std::vector<Edge*> edges;

    const std::vector<Edge *> &getEdges() const {
        return edges;
    }

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
