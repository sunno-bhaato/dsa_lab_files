//
// Created by Aayush Sharma on 18/08/25.
//

#include <iostream>
#include "Stack_LL.h"
using namespace std;

bool Stack_LL::isEmpty() const
{
    return myLLstack.isEmpty();
}

void Stack_LL::display() const
{
    if (Stack_LL::isEmpty())
    {
        cout<<"Stack Underflow"<<endl;
    }
    else
    {
        cout<<"TOP-->";
        myLLstack.printList();
    }
}

void Stack_LL::push(int x)
{
    myLLstack.insertAtBeginning(x);
}

int Stack_LL::pop()
{
    if (Stack_LL::isEmpty())
    {
        cout<<"Stack Underflow"<<endl;
        return -1;
    }
    else
    {
        int cur = Stack_LL::peek();
        myLLstack.delFromBeginning();
        return cur;
    }
}

int Stack_LL::peek() const
{
    return myLLstack.getHead()->data;
}


