//
// Created by Aayush Sharma on 26/08/25.
//

#include <iostream>
#include "P-3/queue_array.h"
using namespace std;

#ifndef DSA_LAB_FILES_STACK_FROM_QUEUE_H
#define DSA_LAB_FILES_STACK_FROM_QUEUE_H

template <typename T>
class stack_from_queue{
private:
    queue_array<T> Q, q;//Q acts as our stack, while q is used for insertion at the front

public:
    void push(T x){
        if(!Q.isFull()) {
            q.enqueue(x);
            while (!isEmpty()) {
                q.enqueue(peek());
                Q.dequeue();
            }
            queue_array<T> temp = q;   //for swapping the values of q and Q
            q = Q;
            Q = temp;
        }
    }

    T pop(){
        if(!isEmpty()) {
            T t = peek();
            Q.dequeue();
            return t;
        }
        else{
            cout<<"STACK UNDERFLOW!!\n"; return T();
        }
    }

    T peek(){
        return Q.peek();
    }

    bool isEmpty(){
        return Q.isEmpty();
    }

    bool display(){
        Q.display_as_stack();
    }

};

#endif //DSA_LAB_FILES_STACK_FROM_QUEUE_H
