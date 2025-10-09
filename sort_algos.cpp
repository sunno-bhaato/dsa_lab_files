#include <vector>
#include <iostream>
#include "Heap.h"  // Use heapify, extractMax etc. from your Heap class

// Insertion Sort
// Iteratively inserts each element into its correct position within the sorted portion
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        // Move elements > key one position forward
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Bubble Sort
// Compares adjacent elements and swaps them if out of order; optimized with swapped flag
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no swaps, array is sorted
        if (!swapped)
            break;
    }
}

// Selection Sort
// Repeatedly finds the minimum element and places it at the beginning
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        std::swap(arr[i], arr[min_idx]);
    }
}

// Merge Sort Helper: merges two sorted halves
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Merge Sort
// Recursively splits array and merges sorted halves
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Heap Sort
// Uses Heap class for optimal heap-sort leveraging heapify and extractMax
void heapSort(std::vector<int>& arr) {
    Heap heap(arr); // Create max-heap from input
    for (int i = arr.size() - 1; i >= 0; --i) {
        arr[i] = heap.extractMax(); // Each extractMax places max at end
    }
}

// Utility function to print array
void printArray(const std::vector<int>& arr) {
    for (int val : arr)
        std::cout << val << " ";
    std::cout << std::endl;
}
