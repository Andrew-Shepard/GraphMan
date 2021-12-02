#include <iostream>
#include "GraphMan.h"
int main() {
    GraphMan gm;
    gm.loadGraph("../input/samplegraph.txt");
    gm.print(std::cout);
    return 0;
}
