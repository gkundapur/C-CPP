#include <bits/stdc++.h>
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

int result = INT_MIN; // for approach 2

// BFS traversal to set parent of each tree node
void setParents(TreeNode* root, char start, TreeNode*& startNode, 
                unordered_map<TreeNode*,TreeNode*>& umParent)
{
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
        auto node = q.front();
        q.pop();
        if (node->val == start)
            startNode = node;
        if (node->left)
        {
            umParent[node->left] = node;
            q.push(node->left);
        }
        if (node->right)
        {
            umParent[node->right] = node;
            q.push(node->right);
        }
    }
}

void setParents_inorder(TreeNode* root, char start, TreeNode*& startNode, 
                unordered_map<TreeNode*,TreeNode*>& umParent)
{
	if (root) {
		if (root->val == start)
			startNode = root;

		if (root->left) 
			umParent[root->left] = root;
		setParents_inorder(root->left, start, startNode, umParent);

		if (root->right)
			umParent[root->right] = root;
		setParents_inorder(root->right, start, startNode, umParent);
	}
}

int burnTree(TreeNode* root, int start)
{
    TreeNode* startNode = NULL;
    unordered_map<TreeNode*, TreeNode*> umParent; // child -> parent

    //setParents(root, start, startNode, umParent);
    setParents_inorder(root, start, startNode, umParent);

    queue<pair<TreeNode*,int>> q; // {node, burnTime}
    q.push({startNode, 0});

    //unordered_set<TreeNode*> visited;
    unordered_map<TreeNode*, bool> visited;
    //visited.emplace(startNode);
	visited[startNode] = true;

    int treeBurnTime = 0;
    while (!q.empty()) {
        //auto [node, time] = q.front();
		auto p = q.front();
		TreeNode *node = p.first;
		int time = p.second;
        q.pop();
        treeBurnTime = max(treeBurnTime, time);

        // go LEFT
        if (node->left && !visited[node->left]) {
            q.push({node->left, time + 1});
            visited[node->left] = true;
        }

        // go RIGHT
        if (node->right && !visited[node->right]) {
            q.push({node->right, time + 1});
            visited[node->right] = true;
        }

        // go UP
        if (umParent[node] && !visited[umParent[node]]) {
            q.push({umParent[node], time + 1});
            visited[umParent[node]] = true;
        }
    }
    return treeBurnTime;
}

int
solve(TreeNode *root, int start)
{
	if (root == NULL)
		return 0;

	int LH = solve(root->left, start);
	int RH = solve(root->right, start);

	if (root->val == start) {
		result = max(LH, RH);
		return -1;
	} else if (LH >= 0 && RH >= 0)
		return max(LH, RH) + 1;
	else {
		int d = abs(LH) + abs(RH);
		result = max(result, d);
		return min(LH, RH) - 1;
	}

	return 0;
}
	

int main()
{
/****************************************************************
	                       A    t = 1
						 /   \
						D     Z t = 2
					  /  \   /
					 H    L B   t = 3
                    / \      \
				   K   P      C t = 4
*****************************************************************/
    TreeNode* root = new TreeNode('A');
    root->left = new TreeNode('D');
    root->left->left = new TreeNode('H');
    root->left->right = new TreeNode('L');
    root->left->left->left = new TreeNode('K');
    root->left->left->right = new TreeNode('P');
    root->right = new TreeNode('Z');
    root->right->left = new TreeNode('B');
    root->right->left->right = new TreeNode('C');

    int treeBurnTime = burnTree(root, 'A');
    cout << "Time taken to burn the tree starting from A: " << treeBurnTime << endl;

    treeBurnTime = burnTree(root, 'D');
    cout << "Time taken to burn the tree starting from D: " << treeBurnTime << endl;
 
    treeBurnTime = burnTree(root, 'C');
    cout << "Time taken to burn the tree starting from C: " << treeBurnTime << endl;

	// approach 2 using tree height
	result = INT_MIN;
	solve(root, 'A');
    cout << "approach2: Time taken to burn the tree starting from A: " << result << endl;

	result = INT_MIN;
	solve(root, 'D');
    cout << "approach2: Time taken to burn the tree starting from D: " << result << endl;

	result = INT_MIN;
	solve(root, 'C');
    cout << "approach2: Time taken to burn the tree starting from C: " << result << endl;

    return 0;
}
