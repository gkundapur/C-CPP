#include <stdio.h>
 
// To heapify a subtree rooted with node i which is
// an index in arr[]. N is size of heap
void swap(int *a, int *b)
{
    int tmp = *a;
      *a = *b;
      *b = tmp;
}
 
void heapify(int arr[], int N, int i)
{
    int smallest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < N && arr[l] < arr[smallest])
        smallest = l;
 
    // If right child is larger than largest so far
    if (r < N && arr[r] < arr[smallest])
        smallest = r;
 
    // If largest is not root
    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, N, smallest);
    }
}
 
// Function to build a Max-Heap from the given array
void buildHeap(int arr[], int N)
{
    // Index of last non-leaf node
    int startIdx = (N / 2) - 1;
 
 	printf("startIdx = %d\n", startIdx);
    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
        heapify(arr, N, i);
    }
}
 
// A utility function to print the array
// representation of Heap
void printHeap(int arr[], int N)
{
    printf("Array representation of Heap is:\n");
 
    for (int i = 0; i < N; ++i)
        printf("%d ",arr[i]);
    printf("\n");
}
 
// Driver's Code
int main()
{
    // Binary Tree Representation
    // of input array
    //             1
    //           /    \
    //         3        5
    //       /  \     /  \
    //     4      6  13  10
    //    / \    / \
    //   9   8  15 17
    //int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
    int arr[] = {6, 3, 13, 10, 1, 5, 4, 9, 8, 15, 17};
 
    int N = sizeof(arr) / sizeof(arr[0]);
 
    // Function call
    buildHeap(arr, N);
    printHeap(arr, N);
   
    // Final Heap:
    //              17
    //            /    \
    //          15      13
    //         /  \     / \
    //        9     6  5   10
    //       / \   / \
    //      4   8 3   1
 
    return 0;
}
