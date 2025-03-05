#include <stdio.h>
#include <stdbool.h>

// Function to check if a subset with the given sum exists
bool isSubsetSum(int set[], int n, int sum) {
    // Base Cases
    if (sum == 0)
        return true;  // Found a subset
    if (n == 0 && sum != 0)
        return false; // No more elements to include

    // If the last element is greater than the sum, ignore it
    if (set[n - 1] > sum)
        return isSubsetSum(set, n - 1, sum);

    // Check if the sum can be obtained either by:
    // (1) including the last element or 
    // (2) excluding the last element
    return isSubsetSum(set, n - 1, sum) || isSubsetSum(set, n - 1, sum - set[n - 1]);
}

int main() {
    int set[] = {3, 34, 4, 12, 5, 2};
    //int sum = 9;
    int sum = 30;
    int n = sizeof(set) / sizeof(set[0]);

    if (isSubsetSum(set, n, sum))
        printf("Found a subset with the given sum\n");
    else
        printf("No subset with the given sum\n");

    return 0;
}

