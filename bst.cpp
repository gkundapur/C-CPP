#include <iostream>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int val) : val(val), left(NULL), right(NULL) {}
};


TreeNode *insert(TreeNode *root, int val)
{
	if (root == NULL)
		root = new TreeNode(val);
	else if (val < root->val)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);
	return root;
}

void inorder(TreeNode *root)
{
	if (root) {
		inorder(root->left);
		cout << root->val << " ";
		inorder(root->right);
	}
}

bool search(TreeNode *root, int val)
{
	if (root == NULL)
		return false;
	if (root->val == val)
		return true;
	if (val < root->val)
		return search(root->left, val);
	return search(root->right, val);
}

TreeNode *delete_rec(TreeNode *root, int x)
{
	if (root == NULL)
		return root;
	if (x < root->val)
		root->left = delete_rec(root->left, x);
	else if (x > root->val)
		root->right = delete_rec(root->right, x);
	else {
		// case 1: No child
		if (root->left == NULL && root->right == NULL) {
			delete (root);
			//root = NULL;
			return NULL;
		}
		// case 2: one child
		else if (root->left == NULL || root->right == NULL) {
			TreeNode *temp = root->left ? root->left : root->right;
			delete (root);
			return temp;
		}
		// case 3: two children
		else if (root->left != NULL && root->right != NULL) {
			TreeNode *min = root->right;
			while (min->left != NULL)
				min = min->left;
			root->val = min->val;
			root->right = delete_rec(root->right, root->val);
		}
	}
	return root;
}

TreeNode *delete_iter(TreeNode *root, int x)
{
	if (root == NULL)
		return root;

	TreeNode *parent = NULL;
	TreeNode *cur = root;
	while (cur != NULL && cur->val != x) {
		parent = cur;
		cur = x < cur->val ? cur->left : cur->right;
	}

	// x not present in BST
	if (cur == NULL) 
		return root;

	// case 1: no children
	if (cur->left == NULL && cur->right == NULL) {
		if (parent->left == cur)
			parent->left = NULL;
		else
			parent->right = NULL;
			printf("parent = %d, %d deleted\n", parent->val, cur->val);
			delete (cur);
	}

	// case 2a: Left child is not NULL and right child is NULL
	else if (cur->left != NULL || cur->right == NULL) {
		if (parent->left == cur)
			parent->left = cur->left;
		else
			parent->right = cur->right;
		printf("parent = %d, %d deleted\n", parent->val, cur->val);
		delete (cur);
	}

	// case 2b: left child NULL and right child is not NULL
	else if (cur->left == NULL && cur->right != NULL) {
		if (parent->left == cur)
			parent->left = cur->right;
		else
			parent->right = cur->left;
		printf("parent = %d, %d deleted\n", parent->val, cur->val);
		delete (cur);
	}

	// case 3: node having 2 children
	else if (cur->left != NULL && cur->right != NULL) {
		TreeNode *succParent, *succ;
		succParent = cur;
		succ = cur->right;
		while (succ->left != NULL) {
			succParent = succ;
			succ = succ->left;
		}

		if (succParent->left == succ)
			succParent->left = NULL;
		else
			succParent->right = NULL;
		cur->val = succ->val;
		delete (succ);
	}
	return root;
}

bool isBST_Util(TreeNode *root, TreeNode *minNode, TreeNode *maxNode)
{
	if (root == NULL)
		return true; // empty tree is valid bst

	if ((minNode && root->val <= minNode->val) ||
		(maxNode && root->val >= maxNode->val))
		return false;

	return isBST_Util(root->left, minNode, root) &&
		isBST_Util(root->right, root, maxNode);
}

bool isBST(TreeNode *root)
{
	return isBST_Util(root, NULL, NULL);
}

int
main(void)
{
	int a[] = {11, 7, 9, 4, 15, 12, 1, 10, 25, 20};
	int n = sizeof(a)/sizeof(a[0]);
	TreeNode *root = NULL;
	cout << "BST created from : ";
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
		if (root == NULL)
			root = insert(root, a[i]);
		else
			insert(root, a[i]);
	}
	cout << endl;

	cout << "Inorder traversal: ";
	inorder(root);
	cout << endl << endl;

	cout << "Is 4 present in BST: ";
	cout << search(root, 4) << endl;
	cout << "Is 10 present in BST: ";
	cout << search(root, 10) << endl;
	cout << "Is 16 present in BST: ";
	cout << search(root, 16) << endl;

	cout << "case 1(no child): Delete 10 from the BST" << endl;
	//root = delete_rec(root, 10);
	root = delete_iter(root, 10);
	cout << "Inorder traversal after deleting 10: ";
	inorder(root);
	cout << endl << endl;

	cout << "case 2(1 child): Delete 10 from the BST" << endl;
	//root = delete_rec(root, 4);
	root = delete_iter(root, 4);
	cout << "Inorder traversal after deleting 4: ";
	inorder(root);
	cout << endl << endl;

	cout << "case 3(2 child): Delete 15 from the BST" << endl;
	//root = delete_rec(root, 15);
	root = delete_iter(root, 15);
	cout << "Inorder traversal after deleting 4: ";
	inorder(root);
	cout << endl << endl;

	cout << "is it valid BST: ";
	cout << isBST(root) << endl;

	return 0;
}
	
