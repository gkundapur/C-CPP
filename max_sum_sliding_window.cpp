#include <iostream>
#include <vector>
using namespace std;

int maxSum(vector<int>& arr, int k)
{
        int n = arr.size();
        cout << "n = " << n << endl;

        if (n <= k) {
                cout << "Invalid" << endl;
                return -1;
        }

        // Compute the sum of first window of size k
        int max_sum = 0;
        for (int i = 0; i < k; i++)
                max_sum += arr[i];

        cout << "Sum of first " << k << " elements = " << max_sum << endl;
        // compute sums of remaining window by removing
        // first element of prev window and adding last
        // element of current window
        int window_sum = max_sum;
        for (int i = k; i < n; i++) {
                window_sum += arr[i] - arr[i-k];
                max_sum = max(max_sum, window_sum);
        }

        return max_sum;
}


int
main(void)
{
        vector<int> arr = {1, 4, 2, 10, 2,3, 1, 0, 20};
        int k = 4;
        cout << maxSum(arr, k) << endl;

        return 0;
}
