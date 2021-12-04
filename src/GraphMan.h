//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_GRAPHMAN_H
#define GRAPHMAN_GRAPHMAN_H


#include <vector>
#include "Vertex.h"
#include "Graph.h"
#include "Edge.h"
#include "VectexQueue.h"
#include "Stack.h"

class GraphMan {
    Graph graph;
public:
    const Graph &getGraph() const;

    void setGraph(const Graph &graph);

private:
    uint64_t getVertexIndex(std::string name, std::vector<Vertex> vertices);
    Vertex depthFirstSearch(Vertex start, std::string search, std::vector<Vertex> vq);
public:
    void print(std::ostream &os);
    void loadGraph(std::string path);
    void shortestPath(Vertex origin, Vertex destination);
    Vertex breadthFirstSearch(Vertex starting_vertex,std::string search);
    Vertex depthFirstSearch(Vertex start, std::string search);
    Vertex depthFirstSearch(Graph increasing_order);
};


#endif //GRAPHMAN_GRAPHMAN_H
