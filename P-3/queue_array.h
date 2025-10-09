#include <iostream>
using namespace std;

#ifndef DSA_LAB_FILES_QUEUE_ARRAY_H
#define DSA_LAB_FILES_QUEUE_ARRAY_H

template <typename T>
class queue_array{
private:
    static const int size = 100;
    T arr[size];
    int front = 0;
    int rear = 0;
    bool Full = false;
    bool Empty = true;

public:
    bool isEmpty() {return Empty;}

    bool isFull() {return Full;}

    void enqueue(T x){
        if(isFull()){
            cout<<"queue is full...\n"; return;
        }
        else{
            arr[rear] = x;
            rear = (rear+1) % size;
            if(Empty) Empty = false;
            if(rear == front) Full = true;
        }
    }

    void dequeue(){
        if(isEmpty()){
            cout<<"queue is empty...\n"; return;
        }
        else{
            front = (front+1) % size;
            if(Full) Full = false;
            if(rear == front) Empty = true;
        }
    }

    T peek(){
        if(isEmpty()){
            cout<<"queue is empty...\n"; return T();
        }
        else{
            return arr[front];
        }
    }

    void display(){
        if(!(isEmpty())){
            int temp = front;
            cout<<"FRONT --->\t"<<arr[temp]<<'\t';        //done this way to handle the case when the array is full and rear == front
            while((temp+1) % size != rear){         //to prevent entering the loop and printing value at rear - index for next insertion in queue
                temp = (temp+1) % size;
                cout<<arr[temp]<<'\t';
            }
            cout<<"<--- REAR\n";
        }
    }

    void display_as_stack(){
        int temp = front;
        cout<<"TOP --->\t"<<arr[temp]<<'\t';        //done this way to handle the case when the array is full and rear == front
        while((temp+1) % size != rear){         //to prevent entering the loop and printing value at rear - index for next insertion in queue
            temp = (temp+1) % size;
            cout<<arr[temp]<<'\t';
        }
        cout<<"\n";
    }
};

#endif //DSA_LAB_FILES_QUEUE_ARRAY_H
