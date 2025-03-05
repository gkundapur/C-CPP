#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure for a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = 
      (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Utility function to check if the tree is a BST
//int isBSTUtil(struct Node* root, struct Node** prev) {
int isBSTUtil(struct Node* root, struct Node** prev) {
    // Return true for null nodes
    if (root == NULL) 
        return 1;

    // Check the left subtree
    if (!isBSTUtil(root->left, prev))
        return 0;

    // Allows only distinct valued nodes
    if (*prev != NULL && root->data <= (*prev)->data)
        return 0;

    *prev = root; // Update previous node

    // Check the right subtree
    return isBSTUtil(root->right, prev);
}

// Function to check if a binary tree is a BST
int isBST(struct Node* root) {
    struct Node* prev = NULL;
    return isBSTUtil(root, &prev);
}

int checkbst(struct Node *root, int min, int max)
{
	if (root->data < min && 
		root->data > max &&
		checkbst(root->left, min, root->data) &&
		checkbst(root->right, root->data, max))
		return 1; // not a bst
	else
		return 0;
}

int isBST1(struct Node *root)
{
	return checkbst(root, INT_MIN, INT_MAX);
}

// Driver code
int main() {
    struct Node* root = newNode(3);
    root->left = newNode(2);
    root->right = newNode(5);
    root->left->left = newNode(1);
  
    // Note: This creates an invalid BST
    root->left->right = newNode(4); 

    // Function call
    if (isBST(root))
        printf("Is BST\n");
    else
        printf("Not a BST\n");

    if (isBST1(root))
        printf("Is BST\n");
    else
        printf("Not a BST\n");
    return 0;
}
