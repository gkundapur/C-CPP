#include <iostream>
#include <stack>
#include <queue>
#include <deque>
using namespace std;

struct TreeNode {
	char val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(char val) : val(val), left(NULL), right(NULL) {}
};

int height(TreeNode *root)
{
	if (root == NULL)
		return 0;
	int lheight = height(root->left);
	int rheight = height(root->right);
	return max(lheight, rheight) + 1;
}

void print_level(TreeNode *root, int level, int ltr)
{
	if (root == NULL)
		return;
	else if (level == 1)
		cout << root->val << " ";
	else if (level > 0) {
		if (ltr == true) {
			print_level(root->left, level-1, ltr);
			print_level(root->right, level-1, ltr);
		} else {
			print_level(root->right, level-1, ltr);
			print_level(root->left, level-1, ltr);
		}
	}
}

void zigzag_levelorder_traversal_rec(TreeNode *root)
{
	bool ltr = true;
	int h = height(root);
	for (int lvl = 0; lvl <= h; lvl++) {
		print_level(root, lvl, ltr);
		cout << endl;
		ltr = !ltr;
	}
}

void zigzag_levelorder_queue_stack(TreeNode *root)
{
	queue<TreeNode *> q;
	stack<TreeNode *> st;
	bool ltr = false;

	q.push(root);
	while (!q.empty()) {
		int n = q.size();
		while(n--) {
			TreeNode *node = q.front();
			q.pop();
			
			if (ltr == true)
				cout << node->val << " ";
			else
				st.push(node);

			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
		if (ltr == false) {
			while (!st.empty()) {
				TreeNode *node = st.top();
				st.pop();
				cout << node->val << " ";
			}
		}
		ltr = !ltr;
		cout << endl;
	}
}

void zigzag_levelorder_twostacks(TreeNode *root)
{
	if (root == NULL)
		return;

	stack<TreeNode *> st1, st2;
	st1.push(root);
	while (!st1.empty() || !st2.empty()) {
		while (!st1.empty()) {
			root = st1.top();
			st1.pop();
			cout << root->val << " ";
			if (root->right)
				st2.push(root->right);
			if (root->left)
				st2.push(root->left);
		} 

		cout << endl;
		while (!st2.empty()) {
			root = st2.top();
			st2.pop();
			cout << root->val << " ";
			if (root->left)
				st1.push(root->left);
			if (root->right)
				st1.push(root->right);
		}
		cout << endl;
	}
}

void zigzag_levelorder_deque(TreeNode *root)
{
	if (root == NULL)
		return;

	deque<TreeNode *> dq;
	bool ltr = false;

	dq.push_back(root);
	while (!dq.empty()) {
		int n = dq.size();
		while (n--) {
			if (ltr == true) {
				root = dq.front();
				dq.pop_front();
				cout << root->val << " ";
				if (root->left)
					dq.push_back(root->left);
				if (root->right)
					dq.push_back(root->right);
			} else {
				root = dq.back();
				dq.pop_back();
				cout << root->val << " ";
				if (root->right)
					dq.push_front(root->right);
				if (root->left)
					dq.push_front(root->left);
			}
		}
		cout << endl;
		ltr = !ltr;
	}
}

//---------------------------------------------------------
//                         A
//                        / \
//                       D   Z
//                      / \   \
//                     H   L   C
//                         /     \
//					      P       E
//---------------------------------------------------------

int
main(void)
{
	TreeNode* root = new TreeNode('A');
    root->left = new TreeNode('D');
    root->left->left = new TreeNode('H');
    root->left->right = new TreeNode('L');
    root->left->right->left = new TreeNode('P');

    root->right = new TreeNode('Z');
    root->right->right = new TreeNode('C');
    root->right->right->right = new TreeNode('E');

	cout << "zigzag levelorder traversal using recursion" << endl;;
	zigzag_levelorder_traversal_rec(root);
	cout << endl;

	cout << "zigzag levelorder traversal using queue and stack" << endl;
	zigzag_levelorder_queue_stack(root);
	cout << endl;

	cout << "zigzag levelorder traversal using two stacks" << endl;
	zigzag_levelorder_twostacks(root);
	cout << endl;

	cout << "zigzag levelorder traversal using deque" << endl;
	zigzag_levelorder_deque(root);
	cout << endl;

	return 0;
}

