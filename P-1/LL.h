#ifndef LL_H
#define LL_H

#include <iostream>

class LL {
private:
    // Declare struct for Node
    struct Node { 
        int data; 
        Node* next; 
    };
    Node* head;

public:
    // Constructors
    LL();
    LL(int element);

    // Destructor
    ~LL();

    bool isEmpty() const;
    
    // Print the list
    void printList() const;
    
    // Insertion operations
    void insertAtBeginning(int x);
    void insertAtEnd(int x);
    void insertAtIndex(int x, int k);
    
    // Deletion operations
    void delFromBeginning();
    void delFromEnd();
    void delFromIndex(int k);
    void delElement(int x);
    
    // Search operation
    int searchList(int x);
    
    // Sorting, merging, and reversal operations
    void sort_asc();
    LL merge(const LL& b);
    void reverse();

    Node* reverse_recursive_help(Node* r);

    void reverse_recurse();

    Node* getHead() const;
};

#endif // LL_H