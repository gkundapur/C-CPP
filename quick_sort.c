#include <stdio.h>

void print_array(int a[], int n);

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int
partition(int a[], int low, int high)
{
    //int i = low + 1;
    int i = low;
    int j = high;
    int pivot = a[low];

    while (i < j) {
        while (a[i]  <= pivot)
            i++;
        while (a[j] > pivot)
            j--;
        //if (i <= j) {
        if (i < j) {
            swap(&a[i], &a[j]);
            printf("array after swap(%d, %d): ", a[i], a[j]);
            print_array(a, high);
        }
    }

    //swap pivot=(a[low] and a[j]
    swap(&a[low], &a[j]); // swap a[j] and pivot
    //a[low] = a[j];
    //a[j] = pivot;
    printf("array after swap(%d, %d): ", a[low], a[j]);
    print_array(a, high);

    return j;
}
void
quicksort(int a[], int low, int high)
{
    if (low < high) {
        int pivot = partition(a, low, high);

        printf("pivot= %d is at = %d\n\n", a[pivot], pivot);

        quicksort(a, low, pivot - 1);

        quicksort(a, pivot + 1, high);
    }
}

void
print_array(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int
main(void)
{
    //int arr[] = {44, 75, 23, 43, 55, 12, 64, 77, 33};
    int arr[] = {35, 50, 15, 25, 80, 20, 90, 45};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Array before sorting: ");
    print_array(arr, n);

    quicksort(arr, 0, n-1);

    printf("Array after sorting: ");
    print_array(arr, n);

    return 0;
}
