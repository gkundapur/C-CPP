#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// A heapify function to maintain the max heap property
void maxHeapify(int heap[], int n, int i) {
    int largest = i;      // Initialize largest as root
    int left = 2 * i + 1;  // Left child index
    int right = 2 * i + 2; // Right child index

    if (left < n && heap[left] > heap[largest]) {
        largest = left;
    }

    if (right < n && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, n, largest);
    }
}

// Function to build a max heap
void buildMaxHeap(int heap[], int n) {
    // Start from the last non-leaf node and heapify each one
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, n, i);
    }
}

// Function to find the kth smallest element using max heap
int kthSmallestUsingMaxHeap(int arr[], int n, int k) {
    // Create a max heap of the first k elements
    int heap[k];
    for (int i = 0; i < k; i++) {
        heap[i] = arr[i];
    }

    buildMaxHeap(heap, k);

    // Iterate through the remaining elements
    for (int i = k; i < n; i++) {
        // If current element is smaller than the root of the max heap
        if (arr[i] < heap[0]) {
            heap[0] = arr[i];
            maxHeapify(heap, k, 0);  // Heapify the root element
        }
    }

    // The root of the max heap is the kth smallest element
    return heap[0];
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    printf("Kth smallest element is %d\n", kthSmallestUsingMaxHeap(arr, n, k));

    return 0;
}

