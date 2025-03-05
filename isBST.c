#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}Node;

/*************************************************************/
int isValidBST(Node *root, int min, int max)
{
	if (root == NULL)
		return 1;

	if (root->data < min || root->data > max)
		return 0; // false

	if (isValidBST(root->left, min, root->data) &&
		isValidBST(root->right, root->data, max))
		return 1;
	else
		return 0;
}

int isValidBST_NULL_MIN_MAX(Node *root, Node *minNode, Node *maxNode)
{
	if (root == NULL)
		return 1;  // empty tree is valid bst

	if ((minNode && root->val <= minNode->val) ||
		(maxNode && root->val >= maxNode->val))
		return false;
	return isValidBST_NULL_MIN_MAX(root->left, minNode, root) &&
			isValidBST_NULL_MIN_MAX(root->right, root, maxNode);
}

int isBST(Node *root)
{
	//return isValidBST(root, INT_MIN, INT_MAX);
	return isValidBST_NULL_MIN_MAX(root, NULL, NULL);
}

int
isValidBST_with_nodes(Node *root, Node *min, Node *max)
{
	if (root == NULL)
		return 1; // true

	if ((min && root->data <= min->data) ||
		(max && root->data >= max->data))
		return 0; // false
	
	return isValidBST_with_nodes(root->left, min, root) &&
			isValidBST_with_nodes(root->right, root, max);
}

int isBST_with_nodes(Node *root)
{
	return isValidBST_with_nodes(root, NULL, NULL);
}

/***********************************************************/
//Recursive inorder traversal

//Node *prev = NULL;
//int isValidBST1(Node *root, Node **prev)
//int isValidBST1(Node *root **prev)
int isValidBST1(Node *root)
{
	static Node *prev = NULL;
	if (root == NULL)
		return 1;

	//if (!isValidBST1(root->left, prev))
	if (!isValidBST1(root->left))
		return 0;

	//if (*prev != NULL && root->data <= (*prev)->data)
	if (prev != NULL && root->data <= prev->data)
		return 0;

	//*prev = root; // update prev node
	prev = root; // update prev node
	//return isValidBST1(root->right, prev);
	return isValidBST1(root->right);
}

int isBST1(Node *root)
{
	Node *prev = NULL;

	//return isValidBST1(root, &prev);
	return isValidBST1(root);
}

int
validate_bst_using_stack(Node *root)
{
	Node *cur = root;
	Node *prev = NULL;

	ST *st = CreateStack();
	while (cur != NULL || isEmpty(st)) {
		if (cur != NULL) {
			push(st, cur);
			cur = cur->left;
		} else {
			cur = Pop(st);
			if (prev && prev->data >= cur->data)
				return 0; //false
			prev = cur;
			cur = cur->right;
		}
	}
	return 1; //true
}
/**********************************************************/
Node *
createnode(int data)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->data = data;
	node->left = node->right = NULL;

	return node;
}
int 
main(void)
{
	Node *root = createnode(40);
	root->left = createnode(20);
	root->right = createnode(60);
	root->left->left = createnode(10);
	root->left->right = createnode(30);
	root->right->right = createnode(80);
	root->right->right->right = createnode(90);

	if (isBST(root))
		printf("Tree 1 is BST\n");
	else
		printf("Tree 1 is not BST\n");

	if (isBST1(root))
		printf("Tree 1 is BST\n");
	else
		printf("Tree 1 is not BST\n");

	Node *root1 = createnode(50);
	root1->left = createnode(20);
	root1->right = createnode(30);
	root1->left->left = createnode(70);
	root1->left->right = createnode(80);
	root1->left->left->left = createnode(10);
	root1->left->left->right = createnode(10);
	root1->left->right = createnode(80);
	root1->left->right->right = createnode(60);

	if (isBST1(root1))
		printf("Tree 1 is BST\n");
	else
		printf("Tree 1 is not BST\n");

	return 0;
}

	

