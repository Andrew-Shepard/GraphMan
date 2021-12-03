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
            if (line_contents[2] == ""){
                Vertex added_vertex(line_contents[0]);
                graph.vertices.push_back(added_vertex);
            } else { //case where the read line defines an edge object
                Vertex *origin = graph.getVertex(line_contents[0]);
                Vertex *destination = graph.getVertex(line_contents[1]);
                uint64_t weight = stoi(line_contents[2]);
                Edge added_edge(origin,destination,weight);
                graph.edges.push_back(added_edge);
                origin->edges.push_back(&graph.edges.at(graph.edges.size()-1));
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
        vertices.push_back(graph.vertices[i]);
        distance.push_back(graph.vertices[i]);
    }
    Vertex focused_vertex = graph.vertices.at(graph.getVertexIndex(origin));
    //vector of visited vertices
    std::vector<std::string> shortest_path_set(graph.vertices.size());
    //vector of distances
    std::vector<uint64_t> shortest_distance_set(graph.vertices.size(), -1);
    while(vertices.size() > 0){
        Edge smallest;
        smallest.setWeight(-1);
        for(int i = 0; i<focused_vertex.edges.size(); i++){
            //if it hasn't been visited and there's a path
            if (distance[i].getWeight() == -1)
                distance[i].setWeight(focused_vertex.edges[i]->getWeight());
            //if this path is shorter than the logged path

            if ( (focused_vertex.edges[i]->getWeight()+focused_vertex.getWeight()) <
                    distance[getVertexIndex(focused_vertex.edges[i]->getDestination()->getName(),distance)]
                            .getWeight()){
                distance[i].setWeight(focused_vertex.getWeight() + focused_vertex.edges[i]->getWeight());
            }
            std::cout << focused_vertex.edges.size();
            //find the smallest unvisited link
            if (smallest.getWeight() == -1 || (smallest.getWeight() > focused_vertex.edges[i]->getWeight())){
                //if it has not been visited yet
                bool exists_in_vertices = false;
                for (int j = 0; j < vertices.size(); j++){
                    if (smallest.getName() == vertices[j].getName())
                        exists_in_vertices = true;
                }
                if (!exists_in_vertices)
                    smallest = *focused_vertex.edges[i];
            }
        }
        vertices.erase(vertices.begin() + getVertexIndex(focused_vertex.getName(),vertices));
        shortest_path_set.push_back(focused_vertex.getName());
        focused_vertex = *smallest.getDestination();
    }
    std::string path = "";
    for(int i =0; i<shortest_path_set.size(); i++){
        path += shortest_path_set[i];
    }
    std::cout << "Path: " << path << "Total weight: "
        << distance[getVertexIndex(destination.getName(),distance)].getWeight();

}
uint64_t GraphMan::getVertexIndex(std::string name, std::vector<Vertex> vertices){
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i].getName() == name)
            return i;
    }
    return 0;
}
/**
Vertex GraphMan::breadthFirstSearch(){

}
Vertex GraphMan::depthFirstSearch(){

}
Vertex GraphMan::depthFirstSearch(Graph increasing_order){

}**/
void GraphMan::print(std::ostream &os){
    for(int i = 0; i < graph.edges.size(); i++){
        std::string edge = "Source: " + graph.edges[i].getSource()->getName() +
                " Destination: " + graph.edges[i].getDestination()->getName() +
                " Weight: " + std::to_string(graph.edges[i].getWeight()) +"\n";
        os << edge;
    }
}

const Graph &GraphMan::getGraph() const {
    return graph;
}

void GraphMan::setGraph(const Graph &graph) {
    GraphMan::graph = graph;
}
