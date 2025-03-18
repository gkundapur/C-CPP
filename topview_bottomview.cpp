#include <iostream>
#include <map>
using namespace std;

struct TreeNode
{
    char val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char data)
    {
        val = data;
        left = NULL;
        right = NULL;
    }
};

void top_view(TreeNode *node, map<int, pair<char,int>>& m, int dist, int level)
{
    if (node == NULL)
       return;
    if (m.count(dist) == 0 || m[dist].second > level)
        m[dist] = make_pair(node->val, level);

    top_view(node->left, m, dist-1, level + 1);
    top_view(node->right, m, dist+1, level + 1);
}

void top_view_iter(TreeNode *root)
{
    if (root == NULL)
       return;
  
    queue<pair<TreeNode*,int>> q;
    q.push({root,0});
    map<int,char> m;
    
    while (!q.empty())
    {
        TreeNode* curr = q.front().first;
        int dist = q.front().second;
        q.pop();

        if (m.count(dist) == 0)
            m[dist] = curr->val;

        if (curr->left != NULL)
            q.push({curr->left, dist-1});
        if (curr->right != NULL)
            q.push({curr->right, dist+1});
    }
    for (auto i : m)
        cout << i.second << " ";
}

void bottom_view(TreeNode *node, map<int, pair<char,int>>& m, int dist, int level)
{
    if (node == NULL)
       return;
    if (m.count(dist) == 0 || m[dist].second < level)
        m[dist] = make_pair(node->val, level);

    bottom_view(node->left, m, dist-1, level + 1);
    bottom_view(node->right, m, dist+1, level + 1);
}

void bottom_view_iter(TreeNode *root)
{
    if (root == NULL)
       return;
    queue<pair<TreeNode*,int>> q;
    q.push({root,0});
    map<int,char> m;

    while (!q.empty())
    {
        TreeNode* curr = q.front().first;
        int dist = q.front().second;
        q.pop();

        m[dist] = curr->val;

        if (curr->left != NULL)
            q.push({curr->left, dist-1});
        if (curr->right != NULL)
            q.push({curr->right, dist+1});
    }
    for (auto i : m)
        cout << i.second << " ";
}

int main()
{
    TreeNode* root = new TreeNode('A');
    root->left = new TreeNode('D');
    root->left->left = new TreeNode('H');
    root->left->right = new TreeNode('L');
    root->left->right->left = new TreeNode('K');
    root->left->right->right = new TreeNode('P');
    root->right = new TreeNode('Z');
    root->right->right = new TreeNode('C');
    root->right->right->right = new TreeNode('B');

    map<int, pair<char,int>> m;
    cout << "Top View of the tree (Recursive method): ";
    top_view(root, m, 0, 0);
    for (auto i : m)
        cout << i.second.first << " ";
    cout << endl;
    
    m.clear();
    cout << "Bottom View of the tree (Recursive method): ";
    bottom_view(root, m, 0, 0);
    for (auto i : m)
        cout << i.second.first << " ";
    cout << endl;

    return 0;
}
