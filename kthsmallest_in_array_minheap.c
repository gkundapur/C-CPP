#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// A heapify function to maintain the min heap property
void minHeapify(int heap[], int n, int i) {
    int smallest = i;      // Initialize smallest as root
    int left = 2 * i + 1;  // Left child index
    int right = 2 * i + 2; // Right child index

    if (left < n && heap[left] < heap[smallest]) {
        smallest = left;
    }

    if (right < n && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

// Function to build a min heap
void buildMinHeap(int heap[], int n) {
    // Start from the last non-leaf node and heapify each one
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(heap, n, i);
    }
}

// Function to extract the minimum element from the heap
int extractMin(int heap[], int *n) {
    if (*n <= 0) {
        return -1; // Heap underflow
    }

    int root = heap[0];
    
    if (*n > 1) {
        heap[0] = heap[*n - 1];
        minHeapify(heap, *n - 1, 0);
    }
    (*n)--; // Reduce the heap size
    return root;
}

// Function to find the kth smallest element
int kthSmallest(int arr[], int n, int k) {
    buildMinHeap(arr, n);

    for (int i = 1; i < k; i++) {
        extractMin(arr, &n);
    }

    return extractMin(arr, &n); // kth smallest element
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    printf("Kth smallest element is %d\n", kthSmallest(arr, n, k));
    
    return 0;
}

