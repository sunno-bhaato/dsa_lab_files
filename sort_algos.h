// sort_algos.h
#pragma once
#include <vector>

// Function prototypes for all sorting algorithms

// Insertion Sort
// Iteratively inserts each element into its correct position within the sorted portion
void insertionSort(std::vector<int>& arr);

// Bubble Sort
// Compares adjacent elements and swaps them if out of order; optimized with swapped flag
void bubbleSort(std::vector<int>& arr);

// Selection Sort
// Repeatedly finds the minimum element and places it at the beginning
void selectionSort(std::vector<int>& arr);

// Merge Sort Helper: merges two sorted halves
void merge(std::vector<int>& arr, int left, int mid, int right);

// Merge Sort
// Recursively splits array and merges sorted halves
void mergeSort(std::vector<int>& arr, int left, int right);

// Heap Sort
// Uses Heap class for optimal heap-sort leveraging heapify and extractMax
void heapSort(std::vector<int>& arr);

// Quick Sort Helper: Partition function
// Places pivot in correct position, elements smaller than pivot go to left, larger go to right
int partition(std::vector<int>& arr, int low, int high);

// Quick Sort: Main recursive function
void quickSort(std::vector<int>& arr, int low, int high);

// Utility function to print array
void printArray(const std::vector<int>& arr);
