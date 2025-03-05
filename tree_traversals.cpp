#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
	//int val;
	char val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(NULL), right(NULL) {}
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
};

//----------------------------------------------------------------
void preorder_rec(TreeNode *root)
{
	if (root != NULL) {
		cout << root->val << " ";
		preorder_rec(root->left);
		preorder_rec(root->right);
	}
}

void preorder_iter(TreeNode *root)
{
	if (root == NULL)
		return;

	stack<TreeNode *> st;
	st.push(root);

	while (!st.empty()) {
		root = st.top();
		st.pop();
		cout << root->val << " ";

		if (root->right)
			st.push(root->right);
		if (root->left)
			st.push(root->left);
	}
}

void preorder_morris(TreeNode *root)
{
	if (root == NULL)
		return;

	TreeNode *cur = root;
	while (cur) {
		if (cur->left == NULL) {
			cout << cur->val << " ";
			cur = cur->right;
		} else {
			TreeNode *pred = cur->left;
			while (pred->right != NULL && pred->right != cur)
				pred = pred->right;

			if (pred->right == NULL) {
				pred->right = cur;
				cout << cur->val << " ";
				cur = cur->left;
			} else {
				pred->right = NULL;
				cur = cur->right;
			}
		}
	}
}
//-----------------------------------------------------------
void inorder_rec(TreeNode *root)
{
	if (root != NULL) {
		inorder_rec(root->left);
		cout << root->val << " ";
		inorder_rec(root->right);
	}
}

void inorder_iter(TreeNode *root)
{
	if (root == NULL)
		return;

	TreeNode *cur = root;
	stack<TreeNode *> st;

	while (cur != NULL || !st.empty()) {
		if (cur != NULL) {
			st.push(cur);
			cur = cur->left;
		} else {
			cur = st.top();
			st.pop();
			cout << cur->val << " ";
			cur = cur->right;
		}
	}
}

void inorder_morris(TreeNode *root)
{
	if (root == NULL)
		return;

	TreeNode *cur = root;
	while (cur != NULL) {
		if (cur->left == NULL) {
			// no left child, print or store this node and go right
			cout << cur->val << " ";
			cur = cur->right;
		} else {
			// if left child is not NULL, find inorder predecessor of cur
			// (rightmost node in left subtree)
			TreeNode *pred = cur->left;
			while (pred->right != NULL && pred->right != cur)
				pred = pred->right;

			//cout << "pred of " << cur->val << " = " << pred->val << endl;
			// pred(A) = L, pred(D) = H, pred(L) = P, pred(A) = L
			// if pred's right child is NULL, make cur to right child
			if (pred->right == NULL) {
				pred->right = cur;
				cur = cur->left;
			} else {
				// revert changes
				pred->right = NULL;
				cout << cur->val << " ";
				cur = cur->right;
			}
		}
	}
}
//-----------------------------------------------------------
void postorder_rec(TreeNode *root)
{
	if (root) {
		postorder_rec(root->left);
		postorder_rec(root->right);
		cout << root->val << " ";
	}
}

void postorder_iter_two_stacks(TreeNode *root)
{
	if (root == NULL)
		return;

	stack<TreeNode *> st1, st2;

	st1.push(root);
	while (!st1.empty()) {
		root = st1.top();
		st1.pop();
		st2.push(root);

		if (root->left)
			st1.push(root->left);
		if (root->right)
			st1.push(root->right);
	}
	
	while (!st2.empty()) {
		root = st2.top();
		cout << root->val << " ";
		st2.pop();
	}
}

void postorder_iter_one_stack(TreeNode *root)
{
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
				cout << cur->val << " ";
				st.pop();
				prev = cur;
				cur = NULL;
			} else
				cur = cur->right;
		}
	}
}

//vector<char> postorder_morris(TreeNode *root)
void postorder_morris(TreeNode *root)
{
	if (root == NULL) {
		//return {}; // for returning vector<char>
		return;
	}

	vector<char> result;
	TreeNode *cur = root;
	while (cur != NULL) {
		if (cur->right == NULL) {
			//cout << cur->val << " ";
			result.push_back(cur->val);
			cur = cur->left;
		} else {
			TreeNode *pred = cur->right;
			while (pred->left != NULL && pred->left != cur)
				pred = pred->left;

			if (pred->left == NULL) {
				//cout << cur->val << " ";
				result.push_back(cur->val);
				pred->left = cur;
				cur = cur->right;
			} else {
				pred->left = NULL;
				cur = cur->left;
			}
		}
	}
	//reverse(result.begin(), result.end());
	//return result;
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << " ";
	cout << endl;
}

//-----------------------------------------------------------
void level_order_traversal(TreeNode *root)
{
	if (root == NULL)
		return;

	queue<TreeNode *> q;
	q.push(root);
	while (!q.empty()) {
		int n = q.size();
		while (n--) {
			root = q.front();
			cout << root->val << " ";
			q.pop();
			if (root->left)
				q.push(root->left);
			if (root->right)
				q.push(root->right);
		}
		cout << endl;
	}
}
		
int
main(void)
{
	TreeNode *root = new TreeNode('A');
	root->left = new TreeNode('D');
	root->left->left = new TreeNode('H');
	root->left->right = new TreeNode('L');
	root->left->right->left = new TreeNode('P');

	root->right = new TreeNode('Z');
	root->right->right = new TreeNode('C');
	root->right->right->right = new TreeNode('E');

	cout << "Preorder recursive	: ";
	preorder_rec(root);
	cout << endl;
	cout << "Preorder iterative	: ";
	preorder_iter(root);
	cout << endl;
	cout << "preorder morris		: ";
	preorder_morris(root);
	cout << endl << endl;

	cout << "Inorder recursive	: ";
	inorder_rec(root);
	cout << endl;
	cout << "Inorder iterative	: ";
	inorder_iter(root);
	cout << endl;
	cout << "Inorder morris		: ";
	inorder_morris(root);
	cout << endl << endl;

	cout << "postorder recursive		: ";
	postorder_rec(root);
	cout << endl;
	cout << "postorder iterative(2 stacks)	: ";
	postorder_iter_two_stacks(root);
	cout << endl;
	cout << "postorder iterative(1 stack)	: ";
	postorder_iter_one_stack(root);
	cout << endl;
	cout << "postorder morris		: ";
	postorder_morris(root);
	//vector<char> result = postorder_morris(root);
	//for (int i = 0; i < result.size(); i++)
	//	cout << result[i] << " ";
	//cout << endl << endl;;

	cout << "level order(bfs): " << endl;;
	level_order_traversal(root);
	cout << endl;

	return 0;
}


