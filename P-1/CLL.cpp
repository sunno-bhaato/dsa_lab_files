#include <iostream>

class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class CircularSinglyLinkedList {
private:
    Node* head;

public:
    CircularSinglyLinkedList() : head(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }

    // a) Insert at the beginning
    void insert_at_beginning(int data) {
        Node* new_node = new Node(data);
        if (is_empty()) {
            head = new_node;
            new_node->next = head;
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = new_node;       //current is now tail
            new_node->next = head;         //new_node next points to first element
            head = new_node;        //head updated
        }
    }

    // b) Insert at the end
    void insert_at_end(int data) {
        Node* new_node = new Node(data);
        if (is_empty()) {
            head = new_node;
            new_node->next = head;
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = new_node;
            new_node->next = head;          //only difference from insert_at_beginning is to not update head
        }
    }

    // c) Insert at a specific position (given an index)
    void insert_at_position(int data, int index) {
        if (index < 0) {
            std::cout << "Index cannot be negative." << std::endl;
            return;
        }
        if (index == 0) {
            insert_at_beginning(data);
            return;
        }

        Node* new_node = new Node(data);
        Node* current = head;
        int count = 0;
        while (current != nullptr && count < index - 1) {
            current = current->next;
            count++;
            if (current == head) {
                std::cout << "Index out of bounds." << std::endl;
                return;
            }
        }
        if (current == nullptr) {
            std::cout << "Index out of bounds." << std::endl;
            return;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    // d) Delete from the beginning
    void delete_from_beginning() {
        if (is_empty()) {
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next != head) {
                current = current->next;
            }
            Node* temp = head;      //temp stores current head
            current->next = head->next;     //current is the tail
            head = head->next;          //update head
            delete temp;          //delete original head
        }
    }

    // e) Delete from the end
    void delete_from_end() {
        if (is_empty()) {
            return;
        }
        if (head->next == head) {
            delete head;
            head = nullptr;
        } else {
            Node* current = head;
            while (current->next->next != head) {
                current = current->next;
            }
            Node* temp = current->next;
            current->next = head;
            delete temp;
        }
    }

    // f) Delete from a specific index position
    void delete_from_position(int index) {
        if (is_empty()) {
            return;
        }
        if (index < 0) {
            std::cout << "Index cannot be negative." << std::endl;
            return;
        }
        if (index == 0) {
            delete_from_beginning();
            return;
        }

        Node* current = head;
        int count = 0;
        while (current->next != head && count < index - 1) {
            current = current->next;
            count++;
        }
        if (count != index - 1 || current->next == head) {
            std::cout << "Index out of bounds." << std::endl;
            return;
        }
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    // g) Delete a specific element if it exists in the list
    void delete_element(int data) {
        if (is_empty()) {
            return;
        }

        if (head->data == data) {
            delete_from_beginning();
            return;
        }

        Node* current = head;
        while (current->next != head && current->next->data != data) {
            current = current->next;
        }

        if (current->next != head) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
    }

    // h) Search for an element and return its index
    int search_element(int data) {
        if (is_empty()) {
            return -1;
        }

        Node* current = head;
        int index = 0;
        do {
            if (current->data == data) {
                return index;
            }
            current = current->next;
            index++;
        } while (current != head);

        return -1;
    }

    // i) Sort the elements in ascending order
    void sort_list() {
        if (is_empty() || head->next == head) {
            return;
        }

        bool swapped;
        Node* current;
        Node* last_node = nullptr;

        do {
            swapped = false;
            current = head;
            while (current->next != head) {
                if (current->data > current->next->data) {
                    // Swap data
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
            last_node = current; // To optimize, but doesn't fully work for circular lists
        } while (swapped);
    }
    
    // j) Merge two circular singly linked lists
    void merge_lists(CircularSinglyLinkedList& other_list) {
        if (other_list.is_empty()) {
            return;
        }
        if (this->is_empty()) {
            this->head = other_list.head;
            other_list.head = nullptr;
            return;
        }

        Node* current_tail = this->head;
        while (current_tail->next != this->head) {
            current_tail = current_tail->next;
        }
        
        Node* other_tail = other_list.head;
        while (other_tail->next != other_list.head) {
            other_tail = other_tail->next;
        }
        
        current_tail->next = other_list.head;
        other_tail->next = this->head;
        other_list.head = nullptr;
    }


    void print_list() {
        if (is_empty()) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* current = head;
        do {
            std::cout << current->data << " -> ";
            current = current->next;
        } while (current != head);
        std::cout << "(back to " << head->data << ")" << std::endl;
    }
};