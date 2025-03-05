#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
	struct node *parent;
} Node_t;

Node_t *
newnode(int data)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	return node;
}

Node_t *
FindMin(Node_t *node) 
{
	Node_t *curr = node;

	while (curr->left != NULL)
		curr = curr->left;
	return curr;
}

Node_t *
inorderSucc(Node_t *root, Node_t *n)
{
	if (n->right != NULL)
		return FindMin(n->right);

	Node_t *succ = NULL;

	while (root != NULL) {
		if (n->data < root->data) {
			succ = root;
			root = root->left;
		} else if (n->data > root->data)
			root = root->right;
		else
			break;
	}

	return succ;
}

Node_t *
insert(Node_t *root, int data)
{
	if (root == NULL)
		return newnode(data);
	else {
		Node_t *temp;

		if (data < root->data) {
			temp = insert(root->left, data);
			root->left = temp;
			temp->parent = root;
		} else {
			temp = insert(root->right, data);
			root->right = temp;
			temp->parent = root;
		}

		return root;
	}
}


/*********************************************
                       20
					  /  \
					 8   22
					/ \
				   4  12
				      / \
					 10 14
*********************************************/

int
main(void)
{
	Node_t *root = NULL, *temp, *succ, *min;

	root = insert(root, 20);
	root = insert(root, 8);
	root = insert(root, 22);
	root = insert(root, 4);
	root = insert(root, 12);
	root = insert(root, 10);
	root = insert(root, 14);
	temp = root->left->right->right;

	succ = inorderSucc(root, temp);
	if (succ != NULL)
		printf("Inorder successor of %d is %d\n", temp->data, succ->data);
	else
		printf("Inorder successor doesn't exist\n");

	return 0;
}


