#include <iostream>
#include "GraphMan.h"
#include "Vertex.h"
int main() {
    GraphMan gm;
    gm.loadGraph("../input/samplegraph.txt");
    //gm.shortestPath(*gm.getGraph().vertices[0],*gm.getGraph().vertices[1]);
    gm.breadthFirstSearch(*gm.getGraph().vertices[0],"e");
    //gm.print(std::cout);
    return 0;
}
