#ifndef DLL_H
#define DLL_H

#include <iostream>

template <typename T>
class DLL {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    Node* tail;

public:
    //constructor
    DLL() {
        head = nullptr;
        tail = nullptr;
    }

    // Destructor
    ~DLL() {
        Node* cur = head;
        while(cur != nullptr){
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    // a) Insert at the beginning
    void InsertAtBeginning(T x) {
        Node* NN = new Node;
        NN->data = x;
        NN->prev = nullptr;

        if (head == nullptr) {
            head = NN;
            tail = NN;
            NN->next = nullptr;
        } else {
            NN->next = head;
            head->prev = NN;
            head = NN;
        }
    }

    // b) Insert at the end
    void InsertAtEnd(T x) {
        Node* NN = new Node;
        NN->data = x;
        NN->next = nullptr;

        if(tail == nullptr) {
            head = NN;
            tail = NN;
            NN->prev = nullptr;
        } else {
            NN->prev = tail;
            tail->next = NN;
            tail = NN;
        }
    }

    // c) Insert at a specific position (given an index)
    void InsertAtIndex(T data, int index) {
        if (index < 0) {
            std::cout << "Error: Index cannot be negative." << std::endl;
            return;
        }
        if (index == 0) {
            InsertAtBeginning(data);
            return;
        }

        Node* current = head;
        int i;
        for (i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }

        if (current == nullptr) {
            if (i == index) { // The list is exactly `index` long, so insert at end
                InsertAtEnd(data);
            } else {
                std::cout << "Error: Index out of bounds." << std::endl;
            }
            return;
        }

        Node* new_node = new Node;
        new_node->data = data;
        new_node->next = current;
        new_node->prev = current->prev;
        current->prev->next = new_node;
        current->prev = new_node;
    }

    // d) Delete from the beginning
    void delFromBeg() {
        Node* temp = nullptr;
        if (head != nullptr) {
            if (tail == head) {
                temp = head;
                head = nullptr;
                tail = nullptr;
            } else {
                temp = head;
                head = head->next;
                head->prev = nullptr;
            }
            delete temp;
        }
    }

    // e) Delete from the end
    void delFromEnd() {
        Node* temp = nullptr;
        if (tail != nullptr) {
            if (tail == head) {
                temp = tail;
                head = nullptr;
                tail = nullptr;
            } else {
                temp = tail;
                tail = tail->prev;
                tail->next = nullptr;
            }
            delete temp;
        }
    }

    // f) Delete from a specific index position
    void delFromIndex(int index) {
        if (head == nullptr) {
            return;
        }
        if (index < 0) {
            std::cout << "Error: Index cannot be negative." << std::endl;
            return;
        }
        if (index == 0) {
            delFromBeg();
            return;
        }

        Node* current = head;
        int i;
        for (i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Error: Index out of bounds." << std::endl;
            return;
        }

        current->prev->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
    }

    // h) Search for an element and return its index
    int searchElement(T x) {
        Node* cur = head;
        int index = 0;
        while(cur != nullptr) {
            if(cur->data == x) return index;
            index++;
            cur = cur->next;
        }
        return -1;
    }

    // g) Delete a specific element if it exists in the list
    void delElement(int x) {
        int index = searchElement(x);
        if(index == -1) {
            std::cout << "Given element " << x << " not found.\n";
        } else {
            delFromIndex(index);
        }
    }

    // i) Sort the elements in ascending order
    void sort_list() {
        if (head == nullptr || head == tail) {
            return;
        }

        bool swapped;
        Node* i;
        Node* j = nullptr;

        do {
            swapped = false;
            i = head;
            while (i->next != j) {
                if (i->data > i->next->data) {
                    T temp = i->data;

                    i->data = i->next->data;
                    i->next->data = temp;
                    swapped = true;
                }
                i = i->next;
            }
            j = i;
        } while (swapped);
    }

    // j) Merge two doubly linked lists
    void merge_lists(DLL& other_list) {
        if (other_list.head == nullptr) {
            return;
        }
        if (this->head == nullptr) {
            this->head = other_list.head;
            this->tail = other_list.tail;
            other_list.head = nullptr;
            other_list.tail = nullptr;
            return;
        }

        this->tail->next = other_list.head;
        other_list.head->prev = this->tail;
        this->tail = other_list.tail;

        other_list.head = nullptr;
        other_list.tail = nullptr;
    }

    // Helper function to print the list
    void printList() {
        if (head == nullptr) {
            std::cout << "List is empty.\n";
            return;
        }
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }

    bool isEmpty(){
        return head == nullptr;
    }

    T headElement(){
        if(!isEmpty()) return head->data;
        else return T();
    }

    //pretty much same as printList, just added to help in queue implementation
    void display(){
        Node* current = head;
        while(current!=nullptr){
            std::cout<<current->data<<"\t";
            current = current->next;
        }
    }

};

#endif // DLL_H