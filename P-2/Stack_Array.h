//
// Created by Aayush Sharma on 18/08/25.
//

#ifndef DSA_LAB_FILES_STACK_ARRAY_H
#define DSA_LAB_FILES_STACK_ARRAY_H

#include <iostream>
using namespace std;
const int MAX_SIZE = 100;

template <typename T>
class Stack {
private:
    T arr[MAX_SIZE]{};
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool isEmpty() const
    {
        return top == -1;
    }

    bool isFull() const
    {
        return top == MAX_SIZE-1;
    }

    void push(T x)
    {
        if (!isFull())
        {
            top++;
            arr[top] = x;
        }
        else
        {
            cout<<"Stack Overflow"<<endl;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            cout<<("Stack Underflow")<<'\n';
            return T();
        }
        else
        {
            T curr = arr[top];
            top --;
            return curr;
        }
    }

    void display() const
    {
        if (isEmpty())
        {
            cout<<"Stack Underflow"<<endl;
        }
        else
        {
            int it = top;
            cout<<"TOP-->";
            while (it != -1)
            {
                cout<<arr[it]<<"\t\n"[!it];
                it--;
            }
        }
    }

    void display_simply() const     //used for queue implementation
    {
        if (isEmpty())
        {
            cout<<"queue is empty..."<<endl;
        }
        else
        {
            int it = top;
            while (it != -1)
            {
                cout<<arr[it]<<"\t";
                it--;
            }
        }
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw std::out_of_range("Stack Underflow");
        }
        else
        {
            return arr[top];
        }
    }

    int size() const
    {
        int count = 0;
        while (count <= top)
        {
            count++;
        }
        return count;
    }

};

#endif //DSA_LAB_FILES_STACK_ARRAY_H