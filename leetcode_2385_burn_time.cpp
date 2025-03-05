/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void constuct_child_parent_map(TreeNode *root, int start, TreeNode *& startNode,
                        unordered_map<TreeNode *, TreeNode *>& umParent) {
        queue<TreeNode *> que;
        que.push(root);
        while (!que.empty()) {
            root = que.front();
            que.pop();
            if (root->val == start)
                startNode = root;

            if (root->left) {
                umParent[root->left] = root;
                que.push(root->left);
            }

            if (root->right) {
                umParent[root->right] = root;
                que.push(root->right);
            }

        }
    }

    int amountOfTime_bfs(TreeNode *root, int start) {
        if (root == NULL)
            return 0;

        TreeNode *startNode = NULL;
        unordered_map<TreeNode *, TreeNode *> umParent; /* child -> parent */
        constuct_child_parent_map(root, start, startNode, umParent);

        int total_time = 0;

        unordered_set<TreeNode *> visited;
        visited.insert(startNode);

        queue<pair<TreeNode *, int>> que; //{node, time}
        que.push({startNode, 0});

        while (!que.empty()) {
            pair<TreeNode *, int> p = que.front();
            TreeNode *node = p.first;
            int time = p.second;

            que.pop();

            total_time = max(total_time, time);

            // go left
            if (node->left && visited.find(node->left) == visited.end()) {
                visited.insert(node->left);
                que.push({node->left, time+1});
            }

            // go right
            if (node->right && visited.find(node->right) == visited.end()) {
                visited.insert(node->right);
                que.push({node->right, time+1});
            }

            // go to parent
            if (umParent.find(node) != umParent.end() && visited.find(umParent[node]) == visited.end()) {
                visited.insert(umParent[node]);
                que.push({umParent[node], time+1});
            }
        }
        return total_time;
    }

    int amountOfTime(TreeNode* root, int start) {
        return amountOfTime_bfs(root, start);        
    }
};

