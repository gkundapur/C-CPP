// C program for different tree traversals
#include <stdio.h>
#include <stdlib.h>
 
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node {
    int data;
    struct node* left;
    struct node* right;
};
 
/****************stack********************************/
#define ST_SIZE 100

typedef struct stack {
	int size;
	int top;
	struct node **array;
}ST;

ST *
CreateStack(int size)
{
	ST *st = (ST *)malloc(sizeof(ST));
	st->size = size;
	st->top = -1;
	st->array = (struct node **)malloc(st->size * sizeof(struct node *));
	return st;
}

void
DeleteStack(ST *st)
{
	free(st->array);
	free(st);
}

int 
isFull(ST *st)
{
	return st->top - 1 == st->size;
}

int
isEmpty(ST *st)
{
	return st->top == -1;
}

void
Push(ST *st, struct node *node)
{
	if (isFull(st))
		return;
	st->array[++st->top] = node;
}

struct node *
Pop(ST *st)
{
	if (isEmpty(st))
		return NULL;
	return st->array[st->top--];
}

struct node *
Top(ST *st)
{
	if (isEmpty(st))
		return NULL;
	return st->array[st->top];
}

void preorderIterative(struct node *root)
{
	ST *st = CreateStack(ST_SIZE);

	Push(st, root);
	while (!isEmpty(st)) {
		root = Pop(st);
		printf("%d ", root->data);

		if (root->right != NULL)
			Push(st, root->right);
		if (root->left != NULL)
			Push(st, root->left);
	}
	//printf("\n");
	DeleteStack(st);
}

void preorderIterative1(struct node *root)
{
	ST *st = CreateStack(ST_SIZE);

	while (1) {
		while (root) {
			printf("%d ", root->data);
			Push(st, root);
			root = root->left;
		}

		if (isEmpty(st))
			break;

		root = Pop(st);
		root = root->right;
	}
	//printf("\n");
	DeleteStack(st);
}

void
preorderIterative2(struct node *root)
{
	if (root == NULL)
		return;

	ST *st = CreateStack(ST_SIZE);

	while (!isEmpty(st) || root != NULL) {
		if (root != NULL) {
			printf("%d ", root->data);
			Push(st, root);
			root = root->left;
		} else {
			root = Pop(st);
			root = root->right;
		}
	}
	printf("\n");
	DeleteStack(st);
}

void
inorderIterative(struct node *root)
{
	ST *st = CreateStack(ST_SIZE);

	while (root != NULL || !isEmpty(st)) {
		if (root != NULL) {
			Push(st, root);
			root = root->left;
		} else {
			root = Pop(st);
			printf("%d ", root->data);
			root = root->right;
		}
	}
	printf("\n");
	DeleteStack(st);
}

void
inorderIterative1(struct node *root)
{
	ST *st = CreateStack(ST_SIZE);

	while (1) {
		while (root) {
			Push(st, root);
			root = root->left;
		}

		if (isEmpty(st))
			break;

		root = Pop(st);
		printf("%d ", root->data);
		root = root->right;
	}

	printf("\n");
	DeleteStack(st);
}

void
inorderIterative2(struct node *root)
{
	if (root == NULL) 
		return;

	ST *st = CreateStack(ST_SIZE);

	while (!isEmpty(st) || root != NULL) {
		if (root != NULL) {
			Push(st, root);
			root = root->left;
		} else {
			root = Pop(st);
			printf("%d ", root->data);
			root = root->right;
		}
	}
	printf("\n");
	DeleteStack(st);
}

// using 1 stack
void
postorderIterative_1stack(struct node *root)
{
	if (root == NULL)
		return;

	ST *st = CreateStack(ST_SIZE);
	struct node *cur = root;
	struct node *prev = NULL;

	while (cur != NULL || !isEmpty(st)) {
		if (cur != NULL) {
			Push(st, cur);
			cur = cur->left;
		} else {
			cur = Top(st);
			if (cur->right == NULL || cur->right == prev) {
				printf("%d ", cur->data);
				Pop(st);
				prev = cur;
				cur = NULL;
			} else
				cur = cur->right;
		}
	}
	//printf("\n");
	DeleteStack(st);
}

void
postorderIterative_1stack_1(struct node *root)
{
	ST *st = CreateStack(ST_SIZE);
	struct node *prev = NULL;

	do {
		while (root != NULL) {
			Push(st, root);
			root = root->left;
		}

		while (root != NULL && !isEmpty(st)) {
			root = Top(st);
			if (root->right == NULL || root->right == prev) {
				printf("%d ", root->data);
				Pop(st);
				prev = root;
				root = NULL;
			} else
				root = root->right;
		}
	} while (!isEmpty(st));

	printf("\n");
	DeleteStack(st);
}

void
postorderIterative_1stack_3(struct node *root)
{
	if (root == NULL)
		return;

	ST *st = CreateStack(ST_SIZE);
	while (root != NULL) {
		if (root->right != NULL)
			push(st, root->right):
		push(st, root);
		root = root->left;
	}
	while (!isEmpty(st)) {
		if (root != NULL) {
			while (root != NULL) {
				if (root->right != NULL)
					push(st, root->right);
				push(st, root);
				root = root->left;
			}
		} else {
			root = Top(st);
			pop(st);  // root = pop(st);
			if (!isEmpty(st) && root->right != NULL && root->right = Top(st)) {
				struct node *temp = Top(st);
				pop(st);
				push(st, root);
				root = temp;
			} else {
				printf("%d ", root->data);
				root = NULL;
			}
		}
	}
}

void
postorderIterative_1stack_2(struct node *root)
{
	if (root == NULL)
		return;

	ST *st = CreateStack(ST_SIZE);
	do {
		while (root) {
			// push root's right child and then root to stack
			if (root->right)
				push(st, root->right);
			push(st, root);

			// set root as root's left child
			root = root->left;
		}

		root = pop(st);
		// if popped item has right child, visit right child
		if (root->right && Top() == root->right) {
			pop(st);
			push(st, root);
			root = root->right;
		} else {
			printf("%d ", root->data);
			root = NULL;
		}
	} while (!isEmpty(st));
}

// using 2 stack
void
postorderIterative_2stack(struct node *root)
{
	ST *st1 = CreateStack(ST_SIZE);
	ST *st2 = CreateStack(ST_SIZE);

	Push(st1, root);
	while (!isEmpty(st1)) {
		root = Pop(st1);
		Push(st2, root);
		if (root->left != NULL)
			Push(st1, root->left);
		if (root->right != NULL)
			Push(st1, root->right);
	}

	while (!isEmpty(st2)) 
		printf("%d ", Pop(st2)->data);

	printf("\n");
	DeleteStack(st1);
	DeleteStack(st2);
}

/***********stack ends *******************************************/

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
{
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}
 
/* Given a binary tree, print its nodes according to the
  "bottom-up" postorder traversal. */
void printPostorder(struct node* node)
{
    if (node == NULL)
        return;
 
    // first recur on left subtree
    printPostorder(node->left);
 
    // then recur on right subtree
    printPostorder(node->right);
 
    // now deal with the node
    printf("%d ", node->data);
}
 
/* Given a binary tree, print its nodes in inorder*/
void printInorder(struct node* node)
{
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInorder(node->left);
 
    /* then print the data of node */
    printf("%d ", node->data);
 
    /* now recur on right child */
    printInorder(node->right);
}
 
/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct node* node)
{
    if (node == NULL)
        return;
 
    /* first print data of node */
    printf("%d ", node->data);
 
    /* then recur on left subtree */
    printPreorder(node->left);
 
    /* now recur on right subtree */
    printPreorder(node->right);
}
 
/* Driver code*/
int main()
{
    struct node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
 
    printf("\nPreorder traversal of binary tree is \n");
    printPreorder(root);
	printf("\nIterative Preorder of binary tree is\n");
	preorderIterative(root);
	printf("\nIterative Preorder-1 of binary tree is\n");
	preorderIterative1(root);
	printf("\nIterative Preorder-2 of binary tree is\n");
	preorderIterative2(root);
 
	printf("-------------------------------------------------\n");
    printf("\nInorder traversal of binary tree is \n");
    printInorder(root);
	printf("\nIterative Inorder of binary tree is\n");
	inorderIterative(root);
	printf("\nIterative Inorder-1 of binary tree is\n");
	inorderIterative1(root);
	printf("\nIterative Inorder-2 of binary tree is\n");
	inorderIterative2(root);
 
	printf("-------------------------------------------------\n");
    printf("\nPostorder traversal of binary tree is \n");
    printPostorder(root);
	printf("\nIterative postorder of binary tree is(1 stack)\n");
	postorderIterative_1stack(root);
	printf("\nIterative postorder_1 of binary tree is(1 stack)\n");
	postorderIterative_2stack(root);
	printf("\nIterative postorder of binary tree is(2 stack)\n");
	postorderIterative_2stack(root);
 
    return 0;
}
