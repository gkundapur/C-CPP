#include <iostream>
#include <vector>
#include <algorithm> // for reverse
using namespace std;

void 
nextpermutation(vector<int>& nums)
{
	int n = nums.size();

	// breakpoint: Find index where nums[i] > nums[i-1] from the right end
	int idx = -1;
	for (int i = n-1; i > 0; i--) {
		if (nums[i] > nums[i-1]) {
			idx = i - 1;
			break;
		}
	}
	cout << "idx = " << idx << endl;

	// if break point exists: Find just greater element of nums[idx] from right end
	// swap it with nums[ids]
	if (idx != -1) {
		int swap_idx = idx;
		for (int i = n-1; i > idx; i--) {
			if (nums[i] > nums[idx]) {
				swap_idx = i;
				break;
			}
		}

		cout << "swap_idx = " << swap_idx << endl;
		cout << "swapping num[idx] = " << nums[idx] << " with nums[swap_idx] = " << nums[swap_idx] << endl;
		//swap nums[idx] with nums[swap_idx]
		swap(nums[idx], nums[swap_idx]);
	}

	// if breakpoint exists(if idx != -1), reverse after breakpoint to till end else
	// reverse the entire array
	cout << "reverse right half from << " << idx+1 << " to " << n-1 << endl;
	reverse(nums.begin() + idx + 1, nums.end());
}

int
main(void)
{
	vector<int> a1 = {1, 3, 2};
	nextpermutation(a1);
	cout << "next permutation of '1 3 2' = ";
	for (int i = 0; i < a1.size(); i++)
		cout << a1[i] << " ";
	cout << endl << endl;

	vector<int> a2 = {1, 2, 3};
	nextpermutation(a2);
	cout << "next permutation of '1 2 3' = ";
	for (int i = 0; i < a2.size(); i++)
		cout << a2[i] << " ";
	cout << endl << endl;

	vector<int> a3 = {3, 2, 1};
	nextpermutation(a3);
	cout << "next permutation of '3 2 1' = ";
	for (int i = 0; i < a3.size(); i++)
		cout << a3[i] << " ";
	cout << endl << endl;

	vector<int> a4 = {1, 1, 5};
	nextpermutation(a4);
	cout << "next permutation of '1 1 5' = ";
	for (int i = 0; i < a4.size(); i++)
		cout << a4[i] << " ";
	cout << endl;

	return 0;
}
