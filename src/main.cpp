#include <iostream>
#include "GraphMan.h"
#include "Vertex.h"
int main() {
    GraphMan gm;
    gm.loadGraph("../input/samplegraph.txt");
    uint32_t continue_ = 1;
    while (continue_ == 1) {
        gm.displayMenu();
        std::cout << "Continue? Type 1 " << std::endl;
        std::cin >> continue_;
    }
    return 0;
}
