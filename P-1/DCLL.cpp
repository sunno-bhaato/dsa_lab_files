#include <iostream>

class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class CircularDoublyLinkedList {
public:
    Node* head;

    CircularDoublyLinkedList() : head(nullptr) {}

    bool is_empty() {
        return head == nullptr;
    }

    // a) Insert at the beginning
    void insert_at_beginning(int data) {
        Node* new_node = new Node(data);
        if (is_empty()) {
            head = new_node;
            new_node->next = head;
            new_node->prev = head;
        } else {
            Node* tail = head->prev;
            new_node->next = head;
            new_node->prev = tail;
            head->prev = new_node;
            tail->next = new_node;
            head = new_node;
        }
    }

    // b) Insert at the end
    void insert_at_end(int data) {
        Node* new_node = new Node(data);
        if (is_empty()) {
            head = new_node;
            new_node->next = head;
            new_node->prev = head;
        } else {
            Node* tail = head->prev;
            new_node->next = head;
            new_node->prev = tail;
            tail->next = new_node;
            head->prev = new_node;
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

        Node* current = head;
        int count = 0;
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
            if (current == head) {
                if (count != index) {
                    std::cout << "Index out of bounds." << std::endl;
                    return;
                }
            }
        }

        if (current == head) { // inserting at the end
            insert_at_end(data);
            return;
        }
        
        Node* new_node = new Node(data);
        Node* prev_node = current->prev;
        
        new_node->next = current;
        new_node->prev = prev_node;
        prev_node->next = new_node;
        current->prev = new_node;
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
            Node* tail = head->prev;
            Node* to_delete = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete to_delete;
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
            Node* tail = head->prev;
            Node* new_tail = tail->prev;
            new_tail->next = head;
            head->prev = new_tail;
            delete tail;
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
        while (current->next != head && count < index) {
            current = current->next;
            count++;
        }
        if (count != index) {
            std::cout << "Index out of bounds." << std::endl;
            return;
        }

        Node* prev_node = current->prev;
        prev_node->next = current->next;
        current->next->prev = prev_node;
        delete current;
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
        
        Node* current = head->next;
        while (current != head && current->data != data) {
            current = current->next;
        }

        if (current != head) { // Element found
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
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

        do {
            swapped = false;
            current = head;
            while (current->next != head) {
                if (current->data > current->next->data) {
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
    
    // j) Merge two circular doubly linked lists
    void merge_lists(CircularDoublyLinkedList& other_list) {
        if (other_list.is_empty()) {
            return;
        }
        if (this->is_empty()) {
            this->head = other_list.head;
            other_list.head = nullptr;
            return;
        }
        
        Node* this_tail = this->head->prev;
        Node* other_head = other_list.head;
        Node* other_tail = other_list.head->prev;

        this_tail->next = other_head;
        other_head->prev = this_tail;

        other_tail->next = this->head;
        this->head->prev = other_tail;

        other_list.head = nullptr;
    }

    void print_list() {
        if (is_empty()) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node* current = head;
        do {
            std::cout << current->data << " <-> ";
            current = current->next;
        } while (current != head);
        std::cout << "(back to " << head->data << ")" << std::endl;
    }
};