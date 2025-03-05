#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
} Node_t;


Node_t *
newNode(int data)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

Node_t *flattenBST(Node_t *root)
{
	if (root == NULL)
		return root;

	Node_t *head = flattenBST(root->left);
	root->left = NULL;

	if (head != NULL) {
		Node_t *temp = head;
		while (temp && temp->right)
			temp = temp->right;
		temp->right = root;
	} else
		head = root;
	
	root->right = flattenBST(root->right);

	return head;
}

void
flatten_using_stack(TreeNode *root)
{
	if (root == NULL)
		return;

	stack<TreeNode *> st;
	st.push(root);

	while (!st.empty()) {
		root = st.top();
		st.pop();

	if (root->right)
		st.push(root->right):

	if (root->left)
		st.push(root->left);

	if (!st.empty())
		root->right = st.top();
	root->left = NULL;
}

void
flatten_iterative(Node_t *root)
{
	if (root == NULL)
		return;

	Node_t *left = root->left;
	Node_t *right = root->right;

	root->left = NULL;
	flatten_iterative(left);
	flatten_iterative(right);

	root->right = left;
	Node_t *cur = root;
	while (cur->right)
		cur = cur->right;
	cur->right = right; 
}

void
flatten_inorder(Node_t *root, Node_t **head)
{
	if (root == NULL)
		return;

	static Node_t *prev = NULL;
	flatten_inorder(root->left, head);
	if (*head == NULL)
		*head = root;
	else {
		root->left = prev;
		prev->right = root;
	}
	prev = root;
	flatten_inorder(root->right, head);
}

void
flatten_morris(Node_t *root)
{
	while (root) { 
		if (root->left) {
			Node_t *rightMost = root->left;
			while (rightMost->right)
				rightMost = rightMost->right;

			rightMost->right = root->right;
			root->right = root->left;
			root->left = NULL;
		}
		root = root->right;
	}
}

void
flatten_morris_1(Node_t *root) 
{
	if (root == NULL)
		return;

	if (root->left) {
		flatten_morris_1(root->left);

		// find right most node of left subtree
		Node_t *temp = root->left;
		while (temp->right)
			temp = temp->right;

		// attach the original right subtree to the rightmost node of left subtree
		temp->right = root->right;

		root->right = root->left;
		root->left = NULL;
	}
	flatten_morris_1(root->right);
}


Node_t *prev = NULL;
void
flatten_reverse_postorder(Node_t *root)
{
	if (root == NULL)
		return;

	flatten_reverse_postorder(root->right);
	flatten_reverse_postorder(root->left);
	root->right = prev;
	root->left = NULL;
	prev = root;
#if 0 // using stack
	create a stack and push root node
	stack<Node_t *> stack;
	st.push(root);
	while (!stack.empty()) {
		cur = top of stack, pop from stack
		if (cur->right != NULL)
			push(cur->right);
		if (cur->left != NULL)
			push(cur->left);
		if (!stack.empty())
			cur->right = top of the stack
		cur->left = NULL;
#endif
}

void
printlist(Node_t *head)
{
	while (head) {
		printf("%d->", head->data);
		head = head->right;
	}
	printf("NULL\n");
}


void
inorder(Node_t *root)
{
	if(root) {
		inorder(root->left);
		printf("%d->", root->data);
		inorder(root->right);
	}
	//printf("NULL\n");
}

int
main(void)
{
	Node_t *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(5);

	root->left->left = newNode(3);
	root->left->right = newNode(4);

	//root->right->left = newNode(6);
	root->right->right = newNode(6);
	printf("Tree inorder: ");
	inorder(root);
	printf("NULL\n");

	//Node_t *head = flattenBST(root);
	//printlist(head);
	//flatten_iterative(root);
	flatten_morris_1(root);
	printlist(root);

	return 0;
}
