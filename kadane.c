// largest sum contgous subarray
/*
-2, -3, 4, -1, -2, 1, 5, 3

4-1-2+1+5 = 7
*/

#include <stdio.h>
#include <limits.h>

// O(n^2)
int
max_sub_arr_sum_inefficient(int a[], int sz)
{
	int maxSum = a[0];

	for (int i = 0; i < sz; i++) {
		int curSum = 0;

		for (int j = i; j < sz; j++) {
			curSum += a[j];

			if (curSum > maxSum)
				maxSum = curSum;
		}
	}
	return maxSum;
}

// O(n) - linear time
int
max_sub_arr_sum(int a[], int sz)
{
    //int max_so_far = INT_MIN;
    int max_so_far = a[0];
    int max_ending_here = 0;
	int start = 0, end = 0, s = 0;

    for (int i = 0; i < sz; i++) {
        max_ending_here += a[i];
        if (max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
			start = s;
			end = i;
		}

        if (max_ending_here < 0) {
            max_ending_here = 0;
			s = i + 1;
		}
    }

	printf("start = %d, end = %d\n", start, end);
    return max_so_far;
}

int
main(void)
{
    //int a[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    //int a[] = {4, -3, -2, 2, 3, 1, -2, -3, 4, 2, -6, -3, -1, 3, 1, 2};
    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = sizeof(a)/sizeof(a[0]);
	int max_sum;

	max_sum = max_sub_arr_sum_inefficient(a, n);
	printf("Inefficient max conti sum = %d\n", max_sum);

    max_sum = max_sub_arr_sum(a, n);
    printf("Max conti sum = %d\n", max_sum);

    return 0;
}
