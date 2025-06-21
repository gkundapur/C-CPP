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

TreeNode *search_closest_rec(TreeNode *root, int k, int minDiff, TreeNode **closestNode)
{
        if (root == NULL)
                return *closestNode;

        int diff = abs(root->val - k);
        if (diff < minDiff) {
                minDiff = diff;
                *closestNode = root;
        }
        
        if (root->val == k)
                return root;
        else if (k < root->val)
                return search_closest_rec(root->left, k, minDiff, closestNode);
        else
                return search_closest_rec(root->right, k, minDiff, closestNode);
}

TreeNode *search_closest(TreeNode *root, int k)
{
        TreeNode *closestNode = NULL;
        return search_closest_rec(root, k, INT_MAX, &closestNode);
}


int
main(void)
{
        TreeNode *root = NULL;
        TreeNode *result = NULL;
        int k;

        int keys[] = {10, 5, 15, 2, 7, 12, 20};
        for (int key : keys)
                root = insert(root, key);

        k = 16;
        // iterative search
        result = search_closest_iter(root, k);
        if (result && result->val == k)
                cout << "(Iter)Exact match found: " << result->val << endl;
        else
                cout << "(Iter)No exact match. Closest value: " << result->val << endl;

        // recursive search
        k = 11;
        result = search_closest(root, k);
        if (result && result->val == k)
                cout << "(rec)Exact match found: " << result->val << endl;
        else
                cout << "(rec)No exact match. Closest value: " << result->val << endl;

        return 0;
}
