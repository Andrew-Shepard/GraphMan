//
// Created by andre on 12/4/2021.
//

#ifndef GRAPHMAN_STACK_H
#define GRAPHMAN_STACK_H
//
// Created by andre on 10/29/2021.
//
#include <iostream>
#include "Vertex.h"
class Stack {
protected:
    Vertex *stack = nullptr;
    Vertex *first = nullptr;
    Vertex *top_of_stack = nullptr;
    Vertex *elements = nullptr;
    uint64_t length = 0;
protected:
    size_t capacity = 0;
public:

    Stack(uint64_t capacity){
        this->capacity = capacity;
        stack = new Vertex[capacity];
        elements = stack;
        first = stack;
    }
    uint64_t getLength() const {
        return length;
    }
    void push(Vertex data) {
        if (length == capacity){
            return;
        }
        length++;
        top_of_stack = first;
        *first = data;

        if (first != &elements[capacity - 1]) {
            first++;
        }else{
            first = stack;
        }


    }

    void pop(){
        //Moves the focused element to the next in the stack
        if (length == 0){
            return;
        }
        length--;
        if(first != elements){
            first--;
            top_of_stack--;
        }
        else{
            first = stack;
        }
    }

    Vertex* top(){
        return top_of_stack;
    }

    void clear() {
        first = stack;
        length = 0;
    }

    uint64_t getSize() {
        return length;
    }

    void setCapacity(size_t capacity){
        //create a new array of size changed capacity
        Vertex* new_stack = new Vertex[capacity];
        //loop through the current array and copy each element
        for(int i = 0; i<this->capacity; i++){
            //dont exceed the new size
            if (i <= capacity){
                new_stack[i] = elements[i];
            }
        }
        // delete the contents of the elements pointer
        delete[] stack;
        // point to the new array
        stack = new_stack;
        //delete the temporary pointer
        delete new_stack;
        new_stack = nullptr;
        // set the objects capacity to the parameterized capacity
        elements = stack;
        first = stack;
    }

    void printStack() {
        Vertex *p = elements;
        for (uint64_t i = 0; i < length; i++) {
            std::cout << *p << std::endl;
            if (p != &elements[capacity - 1]) {
                p++;
            } else {
                p = elements;
            }
        }
    }

    virtual ~Stack() {
        if (stack)
            delete[] stack;
    }

};
#endif //GRAPHMAN_STACK_H
