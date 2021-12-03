#include <iostream>
#include "GraphMan.h"
int main() {
    GraphMan gm;
    gm.loadGraph("../input/samplegraph.txt");
    gm.shortestPath(gm.getGraph().vertices[0].getName(),gm.getGraph().vertices[1].getName());
    return 0;
}
