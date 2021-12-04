//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_VERTEX_H
#define GRAPHMAN_VERTEX_H


#include <string>
#include <vector>
#include <iostream>

class Edge;
class Vertex {
    int64_t weight = -1;
public:
    std::string name;
    std::string path;
    std::vector<Edge*> edges;
    friend std::ostream &operator<<(std::ostream &os, const Vertex &vertex);
    bool operator == (const Vertex &vertex) const {return name == vertex.name;}
    bool operator != (const Vertex &vertex) const {return !(*this==vertex);}
    Vertex(std::string name){
        this->name = name;
    }
    Vertex(){}

    int64_t getWeight() const;

    void setWeight(int64_t weight);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getPath() const;

    void setPath(const std::string &path);

    const std::vector<Edge *> &getEdges() const;

    void setEdges(const std::vector<Edge *> &edges);



};


#endif //GRAPHMAN_VERTEX_H
