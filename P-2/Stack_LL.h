//
// Created by Aayush Sharma on 18/08/25.
//

#ifndef DSA_LAB_FILES_STACK_LL_H
#define DSA_LAB_FILES_STACK_LL_H

#include "P-1/LL.h"

class Stack_LL
{   private:
        LL myLLstack;
    public:
        bool isEmpty() const;
        void display() const;
        void push(int);
        int pop();
        int peek() const;
};


#endif //DSA_LAB_FILES_STACK_LL_H