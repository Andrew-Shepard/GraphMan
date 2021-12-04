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
                graph.vertices.push_back(new Vertex(line_contents[0]));
            } else { //case where the read line defines an edge object
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
/**
Vertex GraphMan::depthFirstSearch(){

}
Vertex GraphMan::depthFirstSearch(Graph increasing_order){

}**/
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
