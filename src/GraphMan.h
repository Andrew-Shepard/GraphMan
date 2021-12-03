//
// Created by andre on 12/2/2021.
//

#ifndef GRAPHMAN_GRAPHMAN_H
#define GRAPHMAN_GRAPHMAN_H


#include <vector>
#include "Vertex.h"
#include "Graph.h"
#include "Edge.h"

class GraphMan {
    Graph graph;
public:
    const Graph &getGraph() const;

    void setGraph(const Graph &graph);

private:
    uint64_t getVertexIndex(std::string name, std::vector<Vertex> vertices);
public:
    void print(std::ostream &os);
    void loadGraph(std::string path);
    void shortestPath(Vertex origin, Vertex destination);
    Vertex breadthFirstSearch();
    Vertex depthFirstSearch();
    Vertex depthFirstSearch(Graph increasing_order);
};


#endif //GRAPHMAN_GRAPHMAN_H
