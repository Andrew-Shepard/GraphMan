//
// Created by andre on 12/2/2021.
//

#include "GraphMan.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <map>

void GraphMan::loadGraph(std::string path){
    //using the text in default.txt
    std::ifstream graph_file;
    std::string delimiter = ",";
    size_t delimiter_pos = 0;
    graph_file.open(path);
    //while there is another line in the txt
    //load the new line
    for( std::string line; getline(graph_file, line ); )
    {
        std::string line_contents[3] = {}; //Vertex, Vertex, Weight
        for(int i = 0; i<3; i++){
            //split the line by commas into an array of strings
            if((delimiter_pos = line.find(delimiter)) != std::string::npos){
                //find returns the location of the delimiter if it exists or returns npos
                line_contents[i] = line.substr(0,delimiter_pos);
                line.erase(0,delimiter_pos+1);
            } else { //end of line case where , is not the delimiter
                line_contents[i] = line.substr(0,line.length());
                line.erase(0,line.length());
            }
        }
        //handle read line
        // in the case the txt line defines the number of vertices / is a vertex
        if (!std::isdigit(line_contents[0][0])){
            if (line_contents[2] == "" && line_contents[0] != ""){
                graph.vertices.push_back(new Vertex(line_contents[0]));
            } else if (line_contents[0] != ""){ //case where the read line defines an edge object
                Vertex *origin = graph.vertices[graph.getVertexIndex(line_contents[0])];
                Vertex *destination = graph.vertices[graph.getVertexIndex(line_contents[1])];
                uint64_t weight = stoi(line_contents[2]);
                graph.edges.push_back(new Edge(origin,destination,weight));
                origin->edges.push_back(new Edge(origin,destination,weight));
            }
        }
    }
    graph_file.close();
}

void GraphMan::shortestPath(Vertex origin, Vertex destination){
    //vector of all vertices
    std::vector<Vertex> vertices;
    std::vector<Vertex> distance;

    for(int i = 0; i<graph.vertices.size(); i++){
        vertices.push_back(*graph.vertices[i]);
        distance.push_back(*graph.vertices[i]);
    }
    Vertex focused_vertex = *graph.vertices.at(graph.getVertexIndex(origin));
    focused_vertex.setPath(focused_vertex.getName());
    //vector of visited vertices
    std::vector<std::string> shortest_path_set(graph.vertices.size());
    //vector of distances
    std::vector<uint64_t> shortest_distance_set(graph.vertices.size(), -1);
    Edge smallest;
    smallest.setWeight(0);
    uint64_t traversed_distance = 0;
    while(vertices.size() > 0){

        for(int i = 0; i<focused_vertex.getEdges().size(); i++){
            //if it hasn't been visited and there's a path
            if (distance[i].getWeight() == -1){
                distance[i].setWeight(focused_vertex.getEdges()[i]->getWeight());
                focused_vertex.setWeight(0);
            }
            //if this path is shorter than the logged path
            if ( (focused_vertex.getEdges()[i]->getWeight()+focused_vertex.getWeight()) <
                    distance[getVertexIndex(focused_vertex.edges[i]->getDestination()->getName(),distance)]
                            .getWeight()){
                distance[getVertexIndex(focused_vertex.edges[i]->getDestination()->getName(),distance)]
                    .setPath(distance[getVertexIndex(focused_vertex.edges[i]->getDestination()->getName(),distance)].getPath() + focused_vertex.getName());
                distance[getVertexIndex(focused_vertex.edges[i]->getDestination()->getName(),distance)].setWeight(focused_vertex.getWeight() + focused_vertex.getEdges()[i]->getWeight());
            }
            //find the smallest unvisited link
            if (smallest.getWeight() == 0 || (smallest.getWeight() > focused_vertex.getEdges()[i]->getWeight())){
                //if it has not been visited yet
                bool exists_in_vertices = false;
                for (int j = 0; j < vertices.size(); j++){
                    if (smallest.getName() == vertices[j].getName())
                        exists_in_vertices = true;
                }
                if (!exists_in_vertices)
                    smallest = *focused_vertex.getEdges()[i];
            }
        }
        vertices.erase(vertices.begin() + getVertexIndex(focused_vertex.getName(),vertices));
        shortest_path_set.push_back(focused_vertex.getName());
        traversed_distance += smallest.getWeight();
        focused_vertex = *smallest.getDestination();
        focused_vertex.setWeight(focused_vertex.getWeight()+traversed_distance+1);

    }
    std::cout << "Path: " << distance[getVertexIndex(destination.getName(),distance)].getPath()+destination.getName() << " Total weight: "
        << distance[getVertexIndex(destination.getName(),distance)].getWeight() << std::endl;

}
uint64_t GraphMan::getVertexIndex(std::string name, std::vector<Vertex> vertices){
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i].getName() == name)
            return i;
    }
    return 0;
}

Vertex GraphMan::breadthFirstSearch(Vertex starting_vertex,std::string search){
    int64_t total_vertices = graph.vertices.size();
    Vertex searched_vertex;
    searched_vertex.setName(search);
    VertexQueue vq(total_vertices);
    VertexQueue order_searched(total_vertices);

    vq.enqueue(starting_vertex);
    while( vq.size() >= 0 ){
        for(int i = 0; i < vq.size(); i++){
            if(vq.first()->getEdges().size() > 0){
               for (int j = 0; j<vq.first()->getEdges().size(); j++){
                   if (!order_searched.contains(*vq.first()->getEdges()[j]->getDestination()))
                        vq.enqueue(*vq.first()->getEdges()[j]->getDestination());
               }
            }
            if(*vq.first() == searched_vertex){
                std::cout << "Found, order queued with BFS: "<< std::endl;
                order_searched.print(std::cout);
                std::cout << searched_vertex.getName() << std::endl;
                return *vq.first();
            }
        }
        order_searched.enqueue(*vq.first());
        vq.dequeue();
    }
    order_searched.enqueue(*vq.first());
    std::cout << "Not Found, order queued taken with BFS: "<<std::endl;
    order_searched.print(std::cout);
    return starting_vertex;
}

Vertex GraphMan::depthFirstSearch(Vertex start, std::string search){
    Vertex searched(search);
    bool not_visited = true;
    std::vector<Vertex> visited(graph.vertices.size());
    visited.push_back(start);
    std::cout << start.getName() << std::endl;
    //until everything is visited
    if(start == searched){
        std::cout << "Found: " << start.getName() << std::endl;;
        return searched;
    }
    if (start.getEdges().size() > 0){
        for (int i = 0; i < start.getEdges().size(); i++){
            //if it has not been visited
            not_visited = true;
            for(int j = 0; j<visited.size(); j++){
                if (*start.edges[i]->getDestination() == visited[j])
                    not_visited = false;
            }
            if(not_visited){
                visited.push_back(*start.edges[i]->getDestination());
                return depthFirstSearch(*start.edges[i]->getDestination(),search, visited);
            }
        }
    }
    return start;
}
Vertex GraphMan::depthFirstSearch(Vertex start, std::string search, std::vector<Vertex> vq){
    Vertex searched(search);
    bool not_visited = true;
    std::vector<Vertex> visited = vq;
    std::cout << start.getName() << std::endl;
    //until everything is visited
    if(start == searched){
        std::cout << "Found: " << start.getName() << std::endl;;
        return searched;
    }
    if (start.getEdges().size() > 0){
        for (int i = 0; i < start.getEdges().size(); i++){
            //if it has not been visited
            not_visited = true;
            for(int j = 0; j<visited.size(); j++){
                if (*start.edges[i]->getDestination() == visited[j])
                    not_visited = false;
            }
            if(not_visited){
                visited.push_back(*start.edges[i]->getDestination());
                return depthFirstSearch(*start.edges[i]->getDestination(),search, visited);
            }
        }
    }
    return start;
}

Vertex GraphMan::depthFirstSearchIncreasing(Vertex start, std::string search){
    Vertex searched(search);
    bool not_visited = true;
    std::vector<Vertex> visited(graph.vertices.size());
    std::vector<Vertex> search_queue(graph.vertices.size());
    visited.push_back(start);
    std::cout << start.getName() << std::endl;
    //until everything is visited
    if(start == searched){
        std::cout << "Found: " << start.getName() << std::endl;
        return searched;
    }
    bubbleSortEdges(start.edges);
    if (start.getEdges().size() > 0){
        for (int i = 0; i < start.getEdges().size(); i++){
            //if it has not been visited
            not_visited = true;
            for(int j = 0; j<visited.size(); j++){
                if (*start.edges[i]->getDestination() == visited[j]){
                    not_visited = false;
                }
            }
            if(not_visited){
                return depthFirstSearch(*start.edges[i]->getDestination(),search, visited);
            }
        }
    }
    std::cout << "Path not found" << std::endl;
    return start;
}
Vertex GraphMan::depthFirstSearchIncreasing(Vertex start, std::string search, std::vector<Vertex> vq){
    Vertex searched(search);
    bool not_visited = true;
    std::vector<Vertex> visited(graph.vertices.size());
    std::vector<Vertex> search_queue(graph.vertices.size());
    std::cout << start.getName() << std::endl;
    //until everything is visited
    if(start == searched){
        std::cout << "Found: " << start.getName() << std::endl;;
        return searched;
    }
    bubbleSortEdges(start.edges);
    if (start.getEdges().size() > 0){
        for (int i = 0; i < start.getEdges().size(); i++){
            //if it has not been visited
            not_visited = true;
            for(int j = 0; j<visited.size(); j++){
                if (*start.edges[i]->getDestination() == visited[j]){
                    not_visited = false;
                }
            }
            if(not_visited){
                Vertex next = *start.edges[0]->getDestination();
                for(int k = 1; k<search_queue.size(); k++){
                    if(next.getWeight() > search_queue.at(k).getWeight())
                        next = search_queue.at(k);
                }
                visited.push_back(next);
                return depthFirstSearch(next,search, visited);
            }
        }
    }
    std::cout << "Path not found" << std::endl;
    return start;
}
void GraphMan::print(std::ostream &os){
    std::string vertex = "";
    std::string edge = "";
    for(int i = 0; i < graph.edges.size(); i++){
        edge += "Source: " + graph.edges[i]->getSource()->getName() +
                " Destination: " + graph.edges[i]->getDestination()->getName() +
                " Weight: " + std::to_string(graph.edges[i]->getWeight()) +"\n";
    }
    for(int i = 0; i<graph.vertices.size(); i++){
        vertex += graph.vertices[i]->getName()+" ";
    }
    os << vertex << "\n" <<  edge << std::endl;
}

const Graph &GraphMan::getGraph() const {
    return graph;
}

void GraphMan::setGraph(const Graph &graph) {
    GraphMan::graph = graph;
}
void GraphMan::displayMenu() {
    //print the table
    std::cout << "\tWelcome to FLPoly Simple Graph System.\n"
            "\t-----------------------------------------------\n"
            "Please select on one of the following:\n"
            "[1] Shortest path between two nodes\n"
            "[2] Print the adjacency list.\n"
            "[3] Breadth-first search\n"
            "[4] Depth-first search\n"
            "[5] Depth-first search with ordered edges\n"
            "\n"
            "Enter your selection:" << std::endl;
    takeMenuInput();
}
void GraphMan::takeMenuInput() {
    uint32_t input_int = 0;
    double input_double = 0;
    std::string input_string = "";
    std::string input_string2 = "";
    std::cin >> input_int;
    switch (input_int) {
        case 1: //Shortest path between two nodes
            std::cout << "Node 1 name:";
            std::cin >> input_string;
            std::cout << "Node 2 name:";
            std::cin >> input_string2;
            shortestPath(*graph.getVertex(input_string),*graph.getVertex(input_string2));
            break;
        case 2: //Print the adjacency list.
            std::cout << graph << std::endl;
            break;
        case 3: //Breadth-first search
            std::cout << "Starting node name:";
            std::cin >> input_string;
            std::cout << "Search node name:";
            std::cin >> input_string2;
            breadthFirstSearch(*graph.getVertex(input_string),input_string2);
            break;
        case 4: //Depth-first search
            std::cout << "Starting node name:";
            std::cin >> input_string;
            std::cout << "Search node name:";
            std::cin >> input_string2;
            depthFirstSearch(*graph.getVertex(input_string),input_string2);
            break;
        case 5: //Depth-first search with ordered edges
            std::cout << "Starting node name:";
            std::cin >> input_string;
            std::cout << "Search node name:";
            std::cin >> input_string2;
            depthFirstSearchIncreasing(*graph.getVertex(input_string),input_string2);
            break;
            break;
    }
}
void GraphMan::swap(Edge *xv, Edge *yv){
    Edge temp = *xv;
    *xv = *yv;
    *yv = temp;
}
void GraphMan::bubbleSortEdges(std::vector<Edge*> edges) {
    int i, j;
    int n = edges.size();
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (edges[j]->getDestination()->edges.size() > edges[j + 1]->getDestination()->edges.size()) {
                swap(edges[j], edges[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
