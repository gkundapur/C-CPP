#include <stdio.h>
 
// Function to swap the position of two elements
 
void swap(int* a, int* b)
{
 
    int temp = *a;
 
    *a = *b;
 
    *b = temp;
}
 
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void max_heapify(int arr[], int N, int i)
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
        max_heapify(arr, N, largest);
    }
}
 
/**************************************************************
Heap-Increase-Key(A, i, key)
Input: A - array representing a heap
       i - array index
	   key - new key greater than A[i]

output: A still representing heap where key of A[i] was increased to key
Running time: O(logn) where n = heap-size[A]
if key < A[i]
	error("New key must be larger than current key")
A[i] = key
while (i > 0 && A[Parent(i)] < A[i]
	exchange A[i] and A[parent(i)]
	i = Parent(i)

***************************************************************/
void
heap_increase_key(int arr[], int i, int key)
{
	if (key > arr[i]) {
		arr[i] = key;

		// heapify up
		while (i > 0 && arr[i/2] < arr[i]) {
			swap(&arr[i], arr[i/2]);
			i = i / 2;
		}
	}
}

void
heap_decrease_key(int arr[], int i, int key)
{
	if (key < arr[i])
		arr[i] = key;
	//heapify up
	while (i > 0 && arr[i/2] > arr[i]) {
		swap(&arr[i], &arr[i/2]);
		i = i/2;  // i = parent(i)
	}
}


/********************************************************
Algorith: Heap-Extract-Max(A)
 Input: A - array representing a heap
 Output: The max element of A and A as a heap with this element removed
 Running time: O(logn) where n = heap-size[A]
 max = A[0]
 A[0] = A[heap-size[A]]
 heap-size[A] = heap-size-1
 Max-Heapify(A, 0)
 return max

 TODO: No code?
 *******************************************************/
 
void
heap_decrease_key(int arr[], int i, int key)
{
	int N = sizeof(arr)/sizeof(arr[0]);

	if (arr[i] > key) {
		arr[i] = key;
		max_heapify(arr, N, i);
	}
}

void min_heapify(int arr[], int N, int i)
{
    // Find smallest among root, left child and right child
 
    // Initialize smallest as root
    int smallest = i;
 
    // left = 2*i + 1
    int left = 2 * i + 1;
 
    // right = 2*i + 2
    int right = 2 * i + 2;
 
    // If left child is larger than root
    if (left < N && arr[left] < arr[smallest])
 
        smallest = left;
 
    // If right child is larger than largest
    // so far
    if (right < N && arr[right] < arr[smallest])
 
        smallest = right;
 
    // Swap and continue heapifying if root is not largest
    // If largest is not root
    if (smallest != i) {
 
        swap(&arr[i], &arr[smallest]);
 
        // Recursively heapify the affected
        // sub-tree
        min_heapify(arr, N, smallest);
    }
}

// Main function to do heap sort
void heapSort_descending(int arr[], int N)
{
 
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)
 
        min_heapify(arr, N, i);
 
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
 
        // Heapify root element to get highest element at
        // root again
        min_heapify(arr, i, 0);
    }
}

void printArray(int arr[], int N);
void heapSort_ascending(int arr[], int N)
{
 
    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)
 
        max_heapify(arr, N, i);

	printf("array after building max heap: ");
	printArray(arr, N);
 
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);  // swap root with last element
		printf("array after swapping %d and %d: ", arr[0], arr[i]);
		printArray(arr, N);
 
        // Heapify root element to get highest element at
        // root again
		printf("heapify %d\n", arr[0]);
        max_heapify(arr, i, 0);
		printf("array after heapifying: ");
		printArray(arr, N);
    }
}
 
// A utility function to print array of size n
void printArray(int arr[], int N)
{
    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
}
 
// Driver's code
int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int N = sizeof(arr) / sizeof(arr[0]);
 
	printf("initial array\n");
	printArray(arr, N);
	
    //descending order 
    //heapSort_descending(arr, N);
    //printf("Sorted array is(descending)\n");
    //printArray(arr, N);

	heapSort_ascending(arr, N);
	printf("Sorted array in (ascending)\n");
	printArray(arr, N);
}
