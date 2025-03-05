#include <stdio.h>
 
// To heapify a subtree rooted with node i which is
// an index in arr[]. N is size of heap
void swap(int *a, int *b)
{
    int tmp = *a;
      *a = *b;
      *b = tmp;
}
 
void printHeap(int a[], int N);

void heapify(int arr[], int N, int i)
{
    int largest = i; // Initialize largest as root
	printf("largest = %d, a[%d] = %d\n", largest, largest, arr[largest]);
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
	printf("l = %d, r = %d\n", l, r);
 
    // If left child is larger than root
    if (l < N && arr[l] > arr[largest])
        largest = l;
 
    // If right child is larger than largest so far
    if (r < N && arr[r] > arr[largest])
        largest = r;
 
	printf("largest after comparing left and right child = %d\n", arr[largest]);
    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
		printf("array after swapping %d and %d\n", arr[i], arr[largest]);
		printHeap(arr, N);
 
        // Recursively heapify the affected sub-tree
        heapify(arr, N, largest);
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
    printf("\n\n");
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
    int arr[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
 
    int N = sizeof(arr) / sizeof(arr[0]);
	printf("N = %d\n", N);
 
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
