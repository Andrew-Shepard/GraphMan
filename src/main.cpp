#include <iostream>
#include "GraphMan.h"
#include "Vertex.h"
int main() {
    GraphMan gm;
    gm.loadGraph("../input/samplegraph.txt");
    gm.shortestPath(*gm.getGraph().vertices[0],*gm.getGraph().vertices[1]);
    gm.breadthFirstSearch(*gm.getGraph().vertices[0],"d");
    std::cout << std::endl;
    gm.depthFirstSearch(*gm.getGraph().vertices[0],"c");
    //gm.print(std::cout);
    return 0;
}
