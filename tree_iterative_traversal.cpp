/*********************************************************
            A                              1
          /   \                           / \
         D     Z                         2   3
        / \     \                       / \   \
       H   L     C                     4   5   8
           /      \                       / \  / 
		  P        E                     6   7 9
**********************************************************/
void
inorder(TreeNode *root, vector<int>& result)
{
	if (root) {
		inorder(root->left);
		//printf("% ", root->val);
		result.push_back(root->val);
		inorder(root->right);
	}
}

void inorder_iterative(TreeNode *root, vector<int>& result)
{
	if (root == NULL)
		return;

	stack<TreeNode *> st;
	TreeNode *cur = root;
	while (cur != NULL || !st.empty()) {
		if (cur != NULL) {
			st.push(cur);
			cur = cur->left;
		} else {
			cur = st.top();
			st.pop();
			result.push_back(cur->val);
			cur = cur->right;
		}
	}
}

void inorder_morris(TreeNode *root, vector<int>& result)
{
	if (root == NULL)
		return;

	TreeNode *cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			// no left child, store this in result and go right
			result.push_back(cur->val);
			cur = cur->right;
		} else {
			// if left child is not NULL, find inorder predecessor of cur
			// (rightmost node in left subtree)
			TreeNode *pred = cur->left;
			while (pred->right != NULL && pred->right != cur)
				pred = pred->right;

			// if pred right child is NULL, make cur to right child
			// and go left
			if (pred->right == NULL) {
				pred->right = cur;
				cur = cur->left;
			} else {
				// revert changes
				pred->right = NULL;
				result.push_back(cur->val);
				cur = cur->right;
			}
		}
	}
}


vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        //inorder(root, result);
        inorder_iterative(root, result);
        //inorder_morris(root, result);

        return result;
}

/************PREORDER*****************************/
void preorder(TreeNode *root, vector<int>& result) {
	if (root) {
		result.push_back(root->val);
		preorder(root->left, result);
		preorder(root->right, result);
	}
}

void preorder_iterative(TreeNode *root, vector<int>& result) {
	if (root == NULL)
		return;

	stack<TreeNode *> st;
	st.push(root);

	while (!st.empty()) {
		TreeNode *node = st.top();
		st.pop();
		result.push_back(node->val);
		if (node->right)
			st.push(node->right);
		if (node->left)
			st.push(node->left);
	}
}

void preorder_morris(TreeNode *root, vector<int>& result) {
	if (root == NULL)
		return;

	TreeNode *cur = root;
	while (cur) {
		if (cur->left == NULL) {
			result.push_back(cur->val);
			cur = cur->right;
		} else {
			TreeNode *prev = cur->left;
			while (prev->right != NULL && prev->right != cur)
				prev = prev->right;

			if (prev->right == NULL) {
				prev->right = cur;
				result.push_back(cur->val);
				cur = cur->left;
			} else {
				prev->right = NULL;
				cur = cur->right;
			}
		}
	}
}

vector<int> preorderTraversal(TreeNode* root) {
	vector<int> result;
	//preorder(root, result);
	preorder_iterative(root, result);
	//preorder_morris(root, result);
	return result;
}

/***************POSTORDER*******************************/
void postorder(TreeNode *root, vector<int>& result) {
	if (root) {
		postorder(root->left, result);
		postorder(root->right, result);
		result.push_back(root->val);
	}
}

void postorder_using_one_stack(TreeNode* root, vector<int>& result) {
	if (root == NULL)
		return;

	stack<TreeNode *> st;
	TreeNode *cur = root;
	TreeNode *prev = NULL;
	while (cur != NULL || !st.empty()) {
		if (cur != NULL) {
			st.push(cur);
			cur = cur->left;
		} else {
			cur = st.top();
			if (cur->right == NULL || cur->right == prev) {
				st.pop();
				result.push_back(cur->val);
				prev = cur;
				cur = NULL;
			} else
				cur = cur->right;
		}
	}
}

void postorder_using_two_stacks(TreeNode* root, vector<int>& result) {
	if (root == NULL)
		return;

	stack<TreeNode *> st1, st2;
	st1.push(root);
	while (!st1.empty()) {
		TreeNode *node = st1.top();
		st1.pop();
		st2.push(node);

		if (node->left)
			st1.push(node->left);
		if (node->right)
			st1.push(node->right);
	}

	while (!st2.empty()) {
		TreeNode *node = st2.top();
		st2.pop();
		result.push_back(node->val);
	}
}

void postorder_morris(TreeNode* root, vector<int>& result) {
	if (root == NULL)
		return;

	TreeNode* cur = root;
	while (cur != NULL) {
		if (cur->right == NULL) {
			result.push_back(cur->val);
			cur = cur->left;
		} else {
			TreeNode* prev = cur->right;
			while (prev->left != NULL && prev->left != cur)
				prev = prev->left;

			if (prev->left == NULL) {
				result.push_back(cur->val);
				prev->left = cur;
				cur = cur->right;
			} else {
				prev->left = NULL;
				cur = cur->left;
			}
		}
	}
	// reverse the res
	reverse(result.begin(), result.end());
}

vector<int> postorderTraversal(TreeNode* root) {
	vector<int> result;
	//postorder(root, result);
	//postorder_using_one_stack(root, result);
	//postorder_using_two_stacks(root, result);
	postorder_morris(root, result);
	return result;
}
