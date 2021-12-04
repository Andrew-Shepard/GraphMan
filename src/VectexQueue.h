//
// Created by andre on 12/4/2021.
//

#ifndef GRAPHMAN_VECTEXQUEUE_H
#define GRAPHMAN_VECTEXQUEUE_H
#include <iostream>
#include <vector>

class VertexQueue {
    Vertex *queue = nullptr;
    Vertex *first_in_queue = nullptr;
    Vertex *last = nullptr;
    std::vector<Vertex> *elements = nullptr;
    uint64_t length = 0;
    size_t capacity = 0;
public:
    VertexQueue(){
        this->capacity = 100;
        elements = new std::vector<Vertex>(capacity);
    }
    VertexQueue(uint64_t capacity){
        this->capacity = capacity;
        elements = new std::vector<Vertex>(capacity);
        queue = &elements->front();
        first_in_queue = last = queue;
    }
    bool contains(Vertex data){
        for(int i = 0; i<elements->size(); i++){
            if (last[i] == data){
                return true;
            }
        }
        return false;
    }
    void enqueue(Vertex data) {
        if (length == capacity){
            return;
        }

        length++;

        *last = data;

        if (last != &(elements->back())) {
            last++;
        }else{
            last = queue;
        }


    }

    void dequeue(){
        //Removes the last element in the queue
        if (length == 0){
            return;
        }

        length--;
        if (first_in_queue != &(elements->back())){
            first_in_queue++;
        }
        else{
            first_in_queue = &(elements->front());
        }
    }

    Vertex* first(){
        return first_in_queue;
    }

    uint64_t size() {
        return length;
    }

    void print(std::ostream &os) {
        Vertex *p = first_in_queue;
        for (uint64_t i = 0; i < length; i++) {
            os << *p;
            if (p != &queue[capacity - 1]) {
                p++;
            } else {
                p = queue;
            }
        }
    }

    void printEdges(std::ostream &os) {
        Vertex *p = first_in_queue;
        for (uint64_t i = 0; i < length; i++) {
            for (int j = 0; j < p->getEdges().size(); j++){
                os << p->getEdges()[j]->getSource()->getName()
                   << p->getEdges()[j]->getDestination()->getName() << std::endl;
            }
            if (p != &queue[capacity - 1]) {
                p++;
            } else {
                p = queue;
            }
        }
    }

    ~VertexQueue() {
        elements->clear();
        delete elements;
    }

};
#endif //GRAPHMAN_VECTEXQUEUE_H
