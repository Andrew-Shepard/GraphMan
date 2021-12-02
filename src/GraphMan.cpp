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

Graph GraphMan::shortestPath(Vertex origin, Vertex destination){
    //Dijkstra’s Algorithm
    //int traversed distance
    uint64_t traversed_distance = 0;
    uint64_t origin_index;
    //vector of all vertices
    std::vector<Vertex> vertices = graph.vertices;
    Vertex focused_vertex = graph.vertices.at(graph.getVertexIndex(origin));
    //vector of visited vertices
    std::vector<std::string> shortest_path_set(10);
    //vector of distances
    std::vector<uint64_t> shortest_distance_set(10, -1);
    while (shortest_path_set.size()<vertices.size()){
        for(int i = 0; i<focused_vertex.edges.size(); i++){
            //if the edge destination is not in the list
            std::string destination_name = focused_vertex.edges.at(i)->getDestination()->getName();
            if( std::find(shortest_path_set.begin(),shortest_path_set.end(),destination_name) != shortest_path_set.end()){
                shortest_path_set.push_back(focused_vertex.edges.at(i)->getDestination()->getName());
                shortest_distance_set.push_back(traversed_distance + focused_vertex.edges.at(i)->getWeight());
            } else {
                if(traversed_distance + focused_vertex.edges.at(i)->getWeight()){}
            }

        }
        //if distance is less than the vertex's previous distance
    }

    //take shortest length of current vertex
    //if the destination of this edge has not been traversed
    //add destination to the set
    //
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
