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
    TreeNode *lca(TreeNode *root, int p, int q) {
        if (root == NULL || root->val == p || root->val == q)
            return root;

        TreeNode *left = lca(root->left, p, q);
        TreeNode *right = lca(root->right, p, q);
        if (left != NULL && right != NULL)
            return root;
        return left != NULL ? left : right;
    }

    bool getpath(TreeNode *node, int target, string& path) {
        if (node == NULL)
            return false;

        if (node->val == target)  // path already found
            return true;

        // go left
        path += 'L';
        //path.push_back('L');
        if (getpath(node->left, target, path) == true) // path found in left side
            return true;
        path.pop_back(); // revert for backtracking

        // go right
        path += 'R';
        //path.push_back('R');
        if (getpath(node->right, target, path) == true)
            return true;
        path.pop_back();
        
        return false;        
    }
    
    string getDirections_using_lca(TreeNode* root, int startValue, int destValue) {
        TreeNode *lcaNode = lca(root, startValue, destValue);

        string lca_to_start = "";
        string lca_to_dest = "";

        getpath(lcaNode, startValue, lca_to_start);
        cout << "lca_to_start: " << lca_to_start << endl;
        getpath(lcaNode, destValue, lca_to_dest);
        cout << "lca_to_dest: " << lca_to_dest << endl;

        string result = "";
        // change lca_to_start to start_to_lca
        for (int i = 0; i < lca_to_start.length(); i++) {
            result += 'U';
            //result.push_back('U');
        }
        
        result = result + lca_to_dest;
        return result;  
    }
    
    /******************************************************************************/
    unordered_map<TreeNode *, TreeNode *> umParent;
    TreeNode *startNode, *destNode;
    void construct_parent_map_dfs(TreeNode *root, int startValue, int destValue) {
        if (root == NULL)
            return;

        if (root->val == startValue)
            startNode = root;
        if (root->val == destValue)
            destNode = root;

        if (root->left)
            umParent[root->left] = root;
        if (root->right)
            umParent[root->right] = root;

        construct_parent_map_dfs(root->left, startValue, destValue);
        construct_parent_map_dfs(root->right, startValue, destValue);
    }

    void construct_parent_map_bfs(TreeNode *root, int startValue, int destValue) {
        if (root == NULL)
            return;

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            root = q.front();
            q.pop();

            if (root->val == startValue)
                startNode = root;
            if (root->val == destValue)
                destNode = root;

            if (root->left) {
                umParent[root->left] = root;
                q.push(root->left);                
            }
            if (root->right) {
                umParent[root->right] = root;
                q.push(root->right);
            }
        }
    }
    string getDirections_using_parant_map_bfs(TreeNode* root, int startValue, int destValue) {
        if (root == NULL)
            return "";

        construct_parent_map_dfs(root, startValue, destValue);

        unordered_set<TreeNode *> visited;
        visited.insert(startNode);

        queue<pair<TreeNode *, string>> q; // {node, direction}
        q.push({startNode, ""});
        while (!q.empty()) {
            pair<TreeNode*, string> p = q.front();
            q.pop();

            TreeNode *node = p.first;
            string dir = p.second;

            if (node == destNode)
                return dir;

            // go left
            if (node->left && visited.find(node->left) == visited.end()) {
                visited.insert(node->left);
                dir.push_back('L');
                q.push({node->left, dir});
                dir.pop_back();
            }

            // go right
            if (node->right && visited.find(node->right) == visited.end()) {
                visited.insert(node->right);
                dir.push_back('R');
                q.push({node->right, dir});
                dir.pop_back();
            }
            
            // go to parent
            if (umParent.find(node) != umParent.end() && visited.find(umParent[node]) == visited.end()) {
                visited.insert(umParent[node]);
                dir.push_back('U');
                q.push({umParent[node], dir});
                dir.pop_back();
            }
        }
        return "";
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        //return getDirections_using_lca(root, startValue, destValue);
        return getDirections_using_parant_map_bfs(root, startValue, destValue);
    }
};
