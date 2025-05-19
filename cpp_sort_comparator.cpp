#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct comparator
{
    bool operator() (pair<char, int> p1, pair<char, int>p2)
    {
        if (p1.second == p2.second)
            return p1.first < p2.first;
        return p1.second < p2.second;
    }
};

int
main(void)
{
    vector<int> v = {1, 5, 8, 9, 6, 7, 3, 4, 2, 0};

    sort(v.begin(), v.end());

    cout << "sorting in ascending order:";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    vector<int> v1 = {1, 5, 8, 9, 6, 7, 3, 4, 2, 0};
    sort(v1.begin(), v1.end(), greater<int>());
    cout << "sorting in descending order:";
    for (int i = 0; i < v1.size(); i++)
        cout << v1[i] << " ";
    cout << endl;

    vector<pair<char, int>> v2 = {
        {'D', 90},
        {'A', 95},
        {'G', 90},
        {'E', 95},
        {'C', 90}
    };

