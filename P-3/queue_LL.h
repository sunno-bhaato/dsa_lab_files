#include <iostream>
#include "P-1/DLL.h"
using namespace std;

#ifndef DSA_LAB_FILES_QUEUE_LL_H
#define DSA_LAB_FILES_QUEUE_LL_H

template <typename T>
class queue_LL{
private:
    DLL<T> mydll;

public:
    void enqueue(T x){
        mydll.InsertAtEnd(x);
    }

    void dequeue(){
        mydll.delFromBeg();
    }

    T peek(){
        return mydll.headElement();
    }

    bool isEmpty(){
        return mydll.isEmpty();
    };

    void display(){
        cout<<"FRONT --->\t";
        mydll.display();
        cout<<"<--- REAR\n";
    }

    void display_as_stack(){        //display with formatting for stack_from_queue class
        cout<<"TOP --->\t";
        mydll.display();
        cout<<"\n";
    }

};

#endif //DSA_LAB_FILES_QUEUE_LL_H
