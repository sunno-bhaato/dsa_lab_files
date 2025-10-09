// Heap.h
#pragma once
#include <vector>

// This class implements a standard max-heap using a dynamic array (vector)
class Heap {
public:
    // Constructor: Initializes an empty heap
    Heap();

    // Constructor: Build heap from an existing array
    Heap(const std::vector<int>& arr);

    // Insert a new element into the heap
    void insert(int val);

    // Extract the maximum element from the heap
    int extractMax();

    // Get the maximum element (peek) without removing it
    int getMax() const;

    // Get the current size of the heap
    int size() const;

    // Check if the heap is empty
    bool isEmpty() const;

    // Optional: Build heap from arbitrary vector (heapify)
    void heapify(const std::vector<int>& arr);

    // Utility: Print the heap contents (for debugging)
    void printHeap() const;

private:
    std::vector<int> data; // Container for heap elements

    // Swap elements at indices i and j
    void swap(int i, int j);

    // Maintain heap property by shifting up
    void shiftUp(int idx);

    // Maintain heap property by shifting down
    void shiftDown(int idx);
};
