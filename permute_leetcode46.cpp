#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<vector<int>> result;
int n;

void
solve(vector<int>& nums, vector<int>& temp, vector<vector<int>>& result, unordered_set<int>& st)
{
	if (temp.size() == n) {
		result.push_back(temp);
		return;
	}

	for (int i = 0; i < n; i++) {
		if (st.find(nums[i]) == st.end()) {
			temp.push_back(nums[i]);
			st.insert(nums[i]);

			solve(nums, temp, result, st);

			temp.pop_back();
			st.erase(nums[i]);
		}
	}
}

void
solve_1(vector<int>& nums, int left, int right, vector<vector<int>>& result, unordered_set<int>& st) 
{
	int i;

	if (left == right) {
		result.push_back(nums);
		return;
	}

	for (i = left; i <= right; i++) {
		if (st.find(nums[i]) == st.end()) {
			st.insert(nums[i]);
			swap(nums[left], nums[i]);
			solve_1(nums, left+1, right, result, st);
			swap(nums[left], nums[i]);
			st.erase(nums[i]);
		}
	}
}

vector<vector<int>>
permute(vector<int>& nums)
{
	n = nums.size();
	vector<vector<int>> result;
	unordered_set<int> st;
	vector<int> temp;

	//solve(nums, temp, result, st);
	solve_1(nums, 0, n-1, result, st);

	return result;
}

void print_result(vector<vector<int>> result)
{
	for (int i = 0; i < result.size(); i++) {
		for (int j = 0; j < result[i].size(); j++)
			cout << result[i][j];
		cout << endl;
	}
}

int
main(void)
{
	vector<vector<int>> result;
	vector<int> nums= {1, 2, 3};
	result = permute(nums);
	print_result(result);


	cout << "---------------------------------------" << endl;
	vector<int> nums1 = {1, 2, 1};
	result = permute(nums1);
	print_result(result);

	return 0;
}
