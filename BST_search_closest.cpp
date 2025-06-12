#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode *insert(TreeNode *root, int key)
{
        if (root == NULL)
                return new TreeNode(key);

        if (key < root->val)
                root->left = insert(root->left, key);
        else if (key > root->val)
                root->right = insert(root->right, key);

        return root;
}

TreeNode *search_closest_iter(TreeNode *root, int k)
{
        TreeNode *closest = NULL;
        int minDiff = INT_MAX;

        while (root) {
                int diff = abs(root->val - k);
                if (diff < minDiff) {
                        minDiff = diff;
                        closest = root;
                }

                if (root->val == k)
                        return root;
                else if (k < root->val)
                        root = root->left;
                else
                        root = root->right;
        }

        return closest;
}

int
main(void)
{
        TreeNode *root = NULL;
        int k;

        int keys[] = {10, 5, 15, 2, 7, 12, 20};
        for (int key : keys)
                root = insert(root, key);

        k = 16;
        TreeNode *result = search_closest_iter(root, k);
        if (result && result->val == k)
                cout << "Exact match found: " << result->val << endl;
        else
                cout << "No exact match. Closest value: " << result->val << endl;

        return 0;
}
