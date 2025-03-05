#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Note that it is not a generic inorder successor
// function. It mainly works when the right child
// is not empty, which is  the case we need in
// BST delete.
struct Node* getSuccessor(struct Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

struct Node *FindMin(struct Node *root)
{
	while (root->left != NULL)
		root = root->left;
	return root;
}

/* works */
// This function deletes a given key x from the
// given BST  and returns the modified root of 
// the BST (if it is modified)
struct Node* delNode(struct Node* root, int x) {
  
    // Base case
    if (root == NULL)
        return root;

    // If key to be searched is in a subtree
    if (x < root->key)
        root->left = delNode(root->left, x);
    else if (x > root->key)
        root->right = delNode(root->right, x);
    else {
		// Case 1: No child
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
		} 

		// Case 2: One child
		// if left child is NULL, attach right child to parent
        else if (root->left == NULL) {
			struct Node *temp = root;
			root = root->right;
			free(temp);
        }

		// if right child is NULL, attach left child
        else if (root->right == NULL) {
			struct Node *temp = root;
			root = root->left;
			free(temp);
        }

        // Case 3: When both children are present
		else {
        	//struct Node* succ = getSuccessor(root);
			// replace node's key with successor's node key and delete successor node
			struct Node *succ = FindMin(root->right);
        	root->key = succ->key;
        	root->right = delNode(root->right, succ->key);
		}
    }
    return root;
}

struct Node* 
iterative_delete(struct Node *root, int x)
{
	struct Node *cur, *newCur, *parent, *succ;

	if (root == NULL)
		return root;

	parent = NULL;
	cur = root;
	while (cur != NULL && cur->key != x) {
		parent = cur;
		cur = x < cur->key ? cur->left : cur->right;
	}

	// key not present
	if (cur == NULL) {
		printf("%d not present\n", x);
		return root;
	}

	// Case 1: node doesn't have left/right child
	if (cur->left == NULL && cur->right == NULL) {
		if (parent->left == cur)
			parent->left = NULL;
		else
			parent->right = NULL;
		printf("parent = %d, %d deleted(case 1)\n", parent->key, cur->key);
		free(cur);
	}

	// Case 2: Deletion of node with one child
	// case 2a: left child not NULL and right child is NULL
	else if (cur->left != NULL && cur->right == NULL) {
		if (parent->left == cur)
			parent->left = cur->left;
		else
			parent->right = cur->right;
		printf("%d deleted\n", cur->key);
		free(cur);
	}
	//case 2b: left child is NULL and right child not NULL
	else if (cur->left == NULL && cur->right != NULL) {
		if (parent->left == cur)
			parent->left = cur->right;
		else
			parent->right = cur->right;
		printf("%d deleted\n", cur->key);
		free(cur);
	}

	// Case 3: Delete node with 2 children
	else if (cur->left != NULL && cur->right != NULL) {
		struct Node *succParent, *succ;

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

		cur->key = succ->key;
		free(succ);
	}
	return root;
}
struct Node* createNode(int key) {
    struct Node* newNode = 
       (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Utility function to do inorder traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

struct Node *
insert(struct Node *root, int data)
{
	struct Node *temp, *cur, *prev;

	temp = createNode(data);
	if (root == NULL) 
		return temp;

	prev = NULL;
	cur = root;
	while (cur != NULL) {
		prev = cur;
		cur = (data < cur->left->key) ? cur->left : cur->right;
	}

	if (data < prev->key)
		prev->left = temp;
	else
		prev->right = temp;

	return root;
}

struct Node *
rec_insert(struct Node* root, int data)
{
	if (root == NULL)
		return createNode(data);

	if (root->key > data)
		root->left = rec_insert(root->left, data);
	else
		root->right = rec_insert(root->right, data);

	return root;
}


// Driver code
int main() {
    struct Node* root = createNode(6);
    root->left = createNode(4);
    root->right = createNode(9);
	root->left->left = createNode(2);
	root->left->right = createNode(5);
    root->right->left = createNode(8);
    root->right->right = createNode(10);
    //int x = 15;
	int x = 2;

	printf("before deleting: ");
	inorder(root);
	printf("\n");

    //root = delNode(root, x);
	root = iterative_delete(root, x);
	printf("after deleting %d : ", x);
    inorder(root);
	printf("\n");
    return 0;
}
