#include <iostream>
#include "P-2/Stack_Array.h"
#ifndef DSA_LAB_FILES_QUEUE_FROM_STACK_H
#define DSA_LAB_FILES_QUEUE_FROM_STACK_H

template <typename T>
class queue_from_stack{
private:
    Stack<T> input, output;

public:
    void enqueue(T x) {
        if (!input.isFull()) {
            input.push(x);
        }
    }

    void dequeue(){
        if(!output.isEmpty()){
            output.pop();
        }
        else{
            while(!input.isEmpty()){
                output.push(input.pop());
            }
            if(!output.isEmpty()) output.pop();
        }
    }

    T peek(){
        if(!output.isEmpty()){
            output.peek();
        }
        else{
            while(!input.isEmpty()){
                output.push(input.pop());
            }
            if(!output.isEmpty()) return output.peek();
            else return T();
        }
    }

    bool isEmpty(){
        return input.isEmpty() && output.isEmpty();
    }

    void display(){
        cout<<"FRONT --->\t";
        if(!output.isEmpty()){
            output.display_simply();
        }
        if(!input.isEmpty()) {
            Stack<T> temp{};
            while (!input.isEmpty()) temp.push(input.pop());
            temp.display_simply();
            while (!temp.isEmpty()) {
                input.push(temp.pop());
            }
        }
        cout<<"<--- REAR\n";
    }

};

#endif //DSA_LAB_FILES_QUEUE_FROM_STACK_H
