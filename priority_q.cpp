#include <stdio.h>
 
// Function to swap the position of two elements
 
void swap(int* a, int* b)
{
 
    int temp = *a;
 
    *a = *b;
 
    *b = temp;
}
 
void printArray(int arr[], int N);
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i)
{
    // Find largest among root, left child and right child
 
    // Initialize largest as root
    int largest = i;
 
    // left = 2*i + 1
    int left = 2 * i + 1;
 
    // right = 2*i + 2
    int right = 2 * i + 2;
 
    // If left child is larger than root
    if (left < N && arr[left] > arr[largest])
 
        largest = left;
 
    // If right child is larger than largest
    // so far
    if (right < N && arr[right] > arr[largest])
 
        largest = right;
 
    // Swap and continue heapifying if root is not largest
    // If largest is not root
    if (largest != i) {
 
        swap(&arr[i], &arr[largest]);
 
        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
		printf("-------------------:");
		printArray(arr, N);
		printf("\n");
    }
}
 
void buildMaxHeap(int arr[], int N)
{
	for (int i = N/2 - 1; i >= 0; i--)
		heapify(arr, N, i);
}

void heapsort1(int arr[], int N)
{
	for (int n = N-1; n >= 0; n--) {
		swap(&arr[0], &arr[n]);
		heapify(arr, n, 0);
	}
}

// Main function to do heap sort
void heapSort(int arr[], int N)
{
 
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)
 
        heapify(arr, N, i);
	
	printf("array after heapify:");
	printArray(arr, N);
 
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
		printf("array after swapping %d<->%d: ", arr[0], arr[i]);
		printArray(arr, N);
 
        // Heapify root element to get highest element at
        // root again
        heapify(arr, i, 0);
		printf("array after heapifying at 0: ");
		printArray(arr, N);
		printf("\n");
    }
}
 
// A utility function to print array of size n
void printArray(int arr[], int N)
{
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
// Driver's code
int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int N = sizeof(arr) / sizeof(arr[0]);
 
    // Function call
    //heapSort(arr, N);
	buildMaxHeap(arr, N);
	heapsort1(arr, N);
    printf("Sorted array is\n");
    printArray(arr, N);
}
