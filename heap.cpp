// Heap.cpp
#include "Heap.h"
#include <iostream> // For printHeap()

// Constructor: Create an empty heap
Heap::Heap() { }

// Constructor: Build a heap from an array, using heapify
Heap::Heap(const std::vector<int>& arr) {
    heapify(arr);
}

// Insert a new value, then maintain heap property
void Heap::insert(int val) {
    data.push_back(val);           // Add at end
    shiftUp(data.size() - 1);      // Restore heap property by shifting up
}

// Get the maximum element (root), remove it, then maintain heap property
int Heap::extractMax() {
    if (isEmpty())
        throw std::out_of_range("Heap is empty!");

    int maxVal = data[0];
    data[0] = data.back();         // Move last to root
    data.pop_back();               // Remove last
    shiftDown(0);                  // Restore heap property
    return maxVal;
}

// Get maximum element (root) without removing
int Heap::getMax() const {
    if (isEmpty())
        throw std::out_of_range("Heap is empty!");
    return data[0];
}

// Return number of elements
int Heap::size() const {
    return data.size();
}

// Check if heap is empty
bool Heap::isEmpty() const {
    return data.empty();
}

// Build heap using bottom-up heapify algorithm
void Heap::heapify(const std::vector<int>& arr) {
    data = arr;
    for (int i = (data.size() / 2) - 1; i >= 0; --i) {
        shiftDown(i);
    }
}

// Swap elements at indices i and j
void Heap::swap(int i, int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

// Shift up: move element at idx up to restore heap property
void Heap::shiftUp(int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (data[idx] > data[parent]) {
            swap(idx, parent);
            idx = parent;
        } else {
            break;
        }
    }
}

// Shift down: move element at idx down to restore heap property
void Heap::shiftDown(int idx) {
    int n = data.size();
    while (true) {
        int left = (2 * idx) + 1;
        int right = (2 * idx) + 2;
        int largest = idx;

        if (left < n && data[left] > data[largest])
            largest = left;
        if (right < n && data[right] > data[largest])
            largest = right;
        if (largest != idx) {
            swap(idx, largest);
            idx = largest;
        } else {
            break;
        }
    }
}

// Print heap contents for debugging
void Heap::printHeap() const {
    for (int val : data)
        std::cout << val << " ";
    std::cout << std::endl;
}
